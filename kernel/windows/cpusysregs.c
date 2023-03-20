#include "cpusysregs.h"

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

// Called when the driver is initialized.

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
    NTSTATUS       status;
    UNICODE_STRING device_name;
    UNICODE_STRING link_name;
    PDEVICE_OBJECT device_object = NULL;

    UNREFERENCED_PARAMETER(registry_path);

    // Driver entry point in the driver object.
    driver_object->MajorFunction[IRP_MJ_CREATE] = csr_open_close;
    driver_object->MajorFunction[IRP_MJ_CLOSE] = csr_open_close;
    driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = csr_ioctl;
    driver_object->DriverUnload = csr_unload;

    // Create our device.
    RtlInitUnicodeString(&device_name, CSR_NT_DEVICE_NAME);
    status = IoCreateDevice(driver_object,             // Our Driver Object
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

// Called when the driver is unloaded.

void csr_unload(PDRIVER_OBJECT driver_object)
{
    PDEVICE_OBJECT device_object = driver_object->DeviceObject;
    UNICODE_STRING link_name;

    PAGED_CODE();

    // Delete the link from our device name to a name in the Win32 namespace.
    RtlInitUnicodeString(&link_name, CSR_DOS_DEVICE_NAME);
    IoDeleteSymbolicLink(&link_name);

    // Delete the device object.
    if (device_object != NULL) {
        IoDeleteDevice(device_object);
    }
}

// Called when the device is opened or closed.

NTSTATUS csr_open_close(PDEVICE_OBJECT device_object, PIRP irp)
{
    UNREFERENCED_PARAMETER(device_object);
    PAGED_CODE();

    irp->IoStatus.Status = STATUS_SUCCESS;
    irp->IoStatus.Information = 0;

    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

// Called to perform a device I/O control function.

NTSTATUS csr_ioctl(PDEVICE_OBJECT device_object, PIRP irp)
{
    NTSTATUS status = STATUS_SUCCESS;
    
    // Caller's I/O stack location
    PIO_STACK_LOCATION irp_sp = IoGetCurrentIrpStackLocation(irp);

    // Input and output data sizes.
    //ULONG in_length = irp_sp->Parameters.DeviceIoControl.InputBufferLength;
    //ULONG out_length = irp_sp->Parameters.DeviceIoControl.OutputBufferLength;

    // We use only buffered ioctl. The I/O manager allocates a buffer large enough to
    // to accommodate the larger of the user input buffer and output buffer, assigns
    // the address to irp->AssociatedIrp.SystemBuffer, and copies the content of the
    // user input buffer into this SystemBuffer. When the IRP is completed, the content
    // of the SystemBuffer is copied to the user output buffer and the SystemBuffer is freed.
    //void* buffer = irp->AssociatedIrp.SystemBuffer;

    PAGED_CODE();

    switch (irp_sp->Parameters.DeviceIoControl.IoControlCode) {
        //case CSR_IOCTL_FOO:
        //    // Use a csr_foo_t as input and output
        //    if (in_length < sizeof(csr_foo_t) || out_length < sizeof(csr_foo_t)) {
        //        status = STATUS_INVALID_PARAMETER;
        //    }
        //    else {
        //        // Use input data, update output buffer.
        //        csr_foo_t* data = (csr_foo_t*)(buffer);
        //        data->out = data->in + 1;

        //        // Return output data size.
        //        irp->IoStatus.Information = sizeof(csr_foo_t);
        //    }
        //    break;

        default:
            // The specified I/O control code is unrecognized by this driver.
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    // Complete the I/O.
    irp->IoStatus.Status = status;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return status;
}
