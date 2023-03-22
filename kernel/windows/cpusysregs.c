//----------------------------------------------------------------------------
//
// Arm64 CPU system registers tools
// Copyright (c) 2023, Thierry Lelegard
// BSD-2-Clause license, see the LICENSE file.
//
// Windows kernel driver for \\.\cpusysregs.
// Reads the Arm64 CPU system registers and return them to userland.
// For test and educational purpose only, can have unexpected security effects.
//
//----------------------------------------------------------------------------

#include "cpusysregs.h"

// Global data: set of CPU features.

static int cpu_features = 0;

// Device driver routine declarations.

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD csr_unload;
_Dispatch_type_(IRP_MJ_CREATE) _Dispatch_type_(IRP_MJ_CLOSE) DRIVER_DISPATCH csr_open_close;
_Dispatch_type_(IRP_MJ_DEVICE_CONTROL) DRIVER_DISPATCH csr_ioctl;

#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, csr_open_close)
#pragma alloc_text(PAGE, csr_ioctl)
#pragma alloc_text(PAGE, csr_unload)
#endif


//----------------------------------------------------------------------------
// Called when the driver is initialized.
//----------------------------------------------------------------------------

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
    NTSTATUS       status;
    UNICODE_STRING device_name;
    UNICODE_STRING link_name;
    PDEVICE_OBJECT device_object = NULL;

    // Get CPU features we may need later.
    cpu_features = csr_get_cpu_features();

    // Driver entry point in the driver object.
    driver_object->MajorFunction[IRP_MJ_CREATE] = csr_open_close;
    driver_object->MajorFunction[IRP_MJ_CLOSE] = csr_open_close;
    driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = csr_ioctl;
    driver_object->DriverUnload = csr_unload;

    // Create our device.
    RtlInitUnicodeString(&device_name, CSR_NT_DEVICE_NAME);
    status = IoCreateDevice(driver_object,            // Our Driver Object
                            0,                        // No device extension
                            &device_name,             // Device name "\Device\xxxxx"
                            FILE_DEVICE_UNKNOWN,      // Device type
                            FILE_DEVICE_SECURE_OPEN,  // Device characteristics
                            FALSE,                    // Not an exclusive device
                            &device_object);          // Returned ptr to Device Object

    if (NT_SUCCESS(status)) {
        // Create a symbolic link between our device name and its Win32 name.
        RtlInitUnicodeString(&link_name, CSR_DOS_DEVICE_NAME);
        status = IoCreateSymbolicLink(&link_name, &device_name);
        if (!NT_SUCCESS(status)) {
            // Failed to create the symbolic link, delete the device.
            IoDeleteDevice(device_object);
        }
    }

    return status;
}


//----------------------------------------------------------------------------
// Called when the driver is unloaded.
//----------------------------------------------------------------------------

void csr_unload(PDRIVER_OBJECT driver_object)
{
    PAGED_CODE();

    PDEVICE_OBJECT device_object = driver_object->DeviceObject;
    UNICODE_STRING link_name;

    // Delete the link from our device name to a name in the Win32 namespace.
    RtlInitUnicodeString(&link_name, CSR_DOS_DEVICE_NAME);
    IoDeleteSymbolicLink(&link_name);

    // Delete the device object.
    if (device_object != NULL) {
        IoDeleteDevice(device_object);
    }
}


//----------------------------------------------------------------------------
// Called when the device is opened or closed.
//----------------------------------------------------------------------------

NTSTATUS csr_open_close(PDEVICE_OBJECT device_object, PIRP irp)
{
    PAGED_CODE();

    // Complete with success status.
    irp->IoStatus.Status = STATUS_SUCCESS;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}


//----------------------------------------------------------------------------
// Called to perform a device I/O control function.
//----------------------------------------------------------------------------

NTSTATUS csr_ioctl(PDEVICE_OBJECT device_object, PIRP irp)
{
    PAGED_CODE();

    // Caller's I/O stack location
    const PIO_STACK_LOCATION irp_sp = IoGetCurrentIrpStackLocation(irp);

    // Input and output data sizes.
    const ULONG in_length = irp_sp->Parameters.DeviceIoControl.InputBufferLength;
    const ULONG out_length = irp_sp->Parameters.DeviceIoControl.OutputBufferLength;

    // We use only buffered ioctl. The I/O manager allocates a buffer large
    // enough to accommodate the larger of the user input buffer and output buffer,
    // assigns the address to irp->AssociatedIrp.SystemBuffer, and copies the
    // content of the user input buffer into this SystemBuffer. When the IRP is
    // completed, the content of the SystemBuffer is copied to the user output
    // buffer and the SystemBuffer is freed.
    void* const buffer = irp->AssociatedIrp.SystemBuffer;

    // I/O control command.
    const ULONG cmd = irp_sp->Parameters.DeviceIoControl.IoControlCode;
    const int instr = csr_ioc_to_instr(cmd);
    const int regid = csr_ioc_to_regid(cmd);

    // Preset returned size to zero.
    irp->IoStatus.Information = 0;
    NTSTATUS status = STATUS_SUCCESS;

    if (METHOD_FROM_CTL_CODE(cmd) != METHOD_BUFFERED) {
        // We only accept buffered commands.
        status = STATUS_INVALID_DEVICE_REQUEST;
    }
    else if (instr != CSR_INSTR_INVALID) {
        // Execute a specific instruction.
        if (in_length < sizeof(csr_instr_t) || out_length < sizeof(csr_instr_t) || csr_exec_instr(instr, (csr_instr_t*)(buffer))) {
            status = STATUS_INVALID_PARAMETER;
        }
        else {
            // Update returned data size (the csr_instr_t is in/out).
            irp->IoStatus.Information = sizeof(csr_instr_t);
        }
    }
    else if (regid != CSR_REGID_INVALID) {
        // This is a register to read/write.
        const ULONG size = csr_regid_is_pair(regid) ? sizeof(csr_pair_t) : sizeof(csr_u64_t);
        if (csr_ioc_is_set_reg(cmd)) {
            // Set register value.
            if (in_length < size || csr_set_register(regid, (const csr_pair_t*)(buffer), cpu_features)) {
                status = STATUS_INVALID_PARAMETER;
            }
        }
        else {
            // Get register value.
            if (out_length < size || csr_get_register(regid, (csr_pair_t*)(buffer), cpu_features)) {
                status = STATUS_INVALID_PARAMETER;
            }
            else {
                // Update returned data size.
                irp->IoStatus.Information = size;
            }
        }
    }
    else {
        status = STATUS_INVALID_DEVICE_REQUEST;
    }

    // Complete the I/O.
    irp->IoStatus.Status = status;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return status;
}
