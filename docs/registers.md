# Arm System Registers for A-Profile

The following table lists all known Arm system registers by name.

The Python script `../aarch/extract-arm-spec.py` automatically generates this table,
based on reference JSON and XML files on the Arm public web site. This script may be
executed each time an update of the Arm architecture is published.

Total: 604 system registers.

| System Register   | Description
| ----------------- | -----------
| ACCDATA_EL1       | Accelerator Data
| ACTLR_EL1         | Auxiliary Control Register (EL1)
| ACTLR_EL12        | Auxiliary Control Register (EL1&2)
| ACTLR_EL2         | Auxiliary Control Register (EL2)
| ACTLR_EL3         | Auxiliary Control Register (EL3)
| ACTLRALIAS_EL1    | 
| ACTLRMASK_EL1     | Auxiliary Control Masking Register (EL1)
| ACTLRMASK_EL12    | Auxiliary Control Masking Register (EL1&2)
| ACTLRMASK_EL2     | Auxiliary Control Masking Register (EL2)
| AFSR0_EL1         | Auxiliary Fault Status Register 0 (EL1)
| AFSR0_EL12        | Auxiliary Fault Status Register 0 (EL1&2)
| AFSR0_EL2         | Auxiliary Fault Status Register 0 (EL2)
| AFSR0_EL3         | Auxiliary Fault Status Register 0 (EL3)
| AFSR1_EL1         | Auxiliary Fault Status Register 1 (EL1)
| AFSR1_EL12        | Auxiliary Fault Status Register 1 (EL1&2)
| AFSR1_EL2         | Auxiliary Fault Status Register 1 (EL2)
| AFSR1_EL3         | Auxiliary Fault Status Register 1 (EL3)
| AIDR_EL1          | Auxiliary ID Register
| ALLINT            | All Interrupt Mask Bit
| AMAIR2_EL1        | Extended Auxiliary Memory Attribute Indirection Register (EL1)
| AMAIR2_EL12       | Extended Auxiliary Memory Attribute Indirection Register (EL1&2)
| AMAIR2_EL2        | Extended Auxiliary Memory Attribute Indirection Register (EL2)
| AMAIR2_EL3        | Extended Auxiliary Memory Attribute Indirection Register (EL3)
| AMAIR_EL1         | Auxiliary Memory Attribute Indirection Register (EL1)
| AMAIR_EL12        | Auxiliary Memory Attribute Indirection Register (EL1&2)
| AMAIR_EL2         | Auxiliary Memory Attribute Indirection Register (EL2)
| AMAIR_EL3         | Auxiliary Memory Attribute Indirection Register (EL3)
| AMCFGR_EL0        | Activity Monitors Configuration Register
| AMCG1IDR_EL0      | Activity Monitors Counter Group 1 Identification Register
| AMCGCR_EL0        | Activity Monitors Counter Group Configuration Register
| AMCNTENCLR0_EL0   | Activity Monitors Count Enable Clear Register 0
| AMCNTENCLR1_EL0   | Activity Monitors Count Enable Clear Register 1
| AMCNTENSET0_EL0   | Activity Monitors Count Enable Set Register 0
| AMCNTENSET1_EL0   | Activity Monitors Count Enable Set Register 1
| AMCR_EL0          | Activity Monitors Control Register
| AMUSERENR_EL0     | Activity Monitors User Enable Register
| APDAKEYHI_EL1     | Pointer Authentication Key A for Data (bits[127:64])
| APDAKEYLO_EL1     | Pointer Authentication Key A for Data (bits[63:0])
| APDBKEYHI_EL1     | Pointer Authentication Key B for Data (bits[127:64])
| APDBKEYLO_EL1     | Pointer Authentication Key B for Data (bits[63:0])
| APGAKEYHI_EL1     | Pointer Authentication Key A for Code (bits[127:64])
| APGAKEYLO_EL1     | Pointer Authentication Key A for Code (bits[63:0])
| APIAKEYHI_EL1     | Pointer Authentication Key A for Instruction (bits[127:64])
| APIAKEYLO_EL1     | Pointer Authentication Key A for Instruction (bits[63:0])
| APIBKEYHI_EL1     | Pointer Authentication Key B for Instruction (bits[127:64])
| APIBKEYLO_EL1     | Pointer Authentication Key B for Instruction (bits[63:0])
| BRBCR_EL1         | Branch Record Buffer Control Register (EL1)
| BRBCR_EL12        | Branch Record Buffer Control Register (EL1&2)
| BRBCR_EL2         | Branch Record Buffer Control Register (EL2)
| BRBFCR_EL1        | Branch Record Buffer Function Control Register
| BRBIDR0_EL1       | Branch Record Buffer ID0 Register
| BRBINFINJ_EL1     | Branch Record Buffer Information Injection Register
| BRBSRCINJ_EL1     | Branch Record Buffer Source Address Injection Register
| BRBTGTINJ_EL1     | Branch Record Buffer Target Address Injection Register
| BRBTS_EL1         | Branch Record Buffer Timestamp Register
| CCSIDR2_EL1       | Current Cache Size ID Register 2
| CCSIDR_EL1        | Current Cache Size ID Register
| CLIDR_EL1         | Cache Level ID Register
| CNTFRQ_EL0        | Counter-timer Frequency Register
| CNTHCTL_EL2       | Counter-timer Hypervisor Control Register
| CNTHP_CTL_EL2     | Counter-timer Hypervisor Physical Timer Control Register
| CNTHP_CVAL_EL2    | Counter-timer Physical Timer CompareValue Register (EL2)
| CNTHP_TVAL_EL2    | Counter-timer Physical Timer TimerValue Register (EL2)
| CNTHPS_CTL_EL2    | Counter-timer Secure Physical Timer Control Register (EL2)
| CNTHPS_CVAL_EL2   | Counter-timer Secure Physical Timer CompareValue Register (EL2)
| CNTHPS_TVAL_EL2   | Counter-timer Secure Physical Timer TimerValue Register (EL2)
| CNTHV_CTL_EL2     | Counter-timer Virtual Timer Control Register (EL2)
| CNTHV_CVAL_EL2    | Counter-timer Virtual Timer CompareValue Register (EL2)
| CNTHV_TVAL_EL2    | Counter-timer Virtual Timer TimerValue Register (EL2)
| CNTHVS_CTL_EL2    | Counter-timer Secure Virtual Timer Control Register (EL2)
| CNTHVS_CVAL_EL2   | Counter-timer Secure Virtual Timer CompareValue Register (EL2)
| CNTHVS_TVAL_EL2   | Counter-timer Secure Virtual Timer TimerValue Register (EL2)
| CNTKCTL_EL1       | Counter-timer Kernel Control Register
| CNTKCTL_EL12      | Counter-timer Kernel Control Register
| CNTP_CTL_EL0      | Counter-timer Physical Timer Control Register
| CNTP_CTL_EL02     | Counter-timer Physical Timer Control Register
| CNTP_CVAL_EL0     | Counter-timer Physical Timer CompareValue Register
| CNTP_CVAL_EL02    | Counter-timer Physical Timer CompareValue Register
| CNTP_TVAL_EL0     | Counter-timer Physical Timer TimerValue Register
| CNTP_TVAL_EL02    | Counter-timer Physical Timer TimerValue Register
| CNTPCT_EL0        | Counter-timer Physical Count Register
| CNTPCTSS_EL0      | Counter-timer Self-Synchronized Physical Count Register
| CNTPOFF_EL2       | Counter-timer Physical Offset Register
| CNTPS_CTL_EL1     | Counter-timer Physical Secure Timer Control Register
| CNTPS_CVAL_EL1    | Counter-timer Physical Secure Timer CompareValue Register
| CNTPS_TVAL_EL1    | Counter-timer Physical Secure Timer TimerValue Register
| CNTV_CTL_EL0      | Counter-timer Virtual Timer Control Register
| CNTV_CTL_EL02     | Counter-timer Virtual Timer Control Register
| CNTV_CVAL_EL0     | Counter-timer Virtual Timer CompareValue Register
| CNTV_CVAL_EL02    | Counter-timer Virtual Timer CompareValue Register
| CNTV_TVAL_EL0     | Counter-timer Virtual Timer TimerValue Register
| CNTV_TVAL_EL02    | Counter-timer Virtual Timer TimerValue Register
| CNTVCT_EL0        | Counter-timer Virtual Count Register
| CNTVCTSS_EL0      | Counter-timer Self-Synchronized Virtual Count Register
| CNTVOFF_EL2       | Counter-timer Virtual Offset Register
| CONTEXTIDR_EL1    | Context ID Register (EL1)
| CONTEXTIDR_EL12   | Context ID Register (EL1&2)
| CONTEXTIDR_EL2    | Context ID Register (EL2)
| CPACR_EL1         | Architectural Feature Access Control Register
| CPACR_EL12        | Architectural Feature Access Control Register
| CPACRALIAS_EL1    | 
| CPACRMASK_EL1     | Architectural Feature Access Control Masking Register
| CPACRMASK_EL12    | Architectural Feature Access Control Masking Register
| CPTR_EL2          | Architectural Feature Trap Register (EL2)
| CPTR_EL3          | Architectural Feature Trap Register (EL3)
| CPTRMASK_EL2      | Architectural Feature Trap Masking Register
| CSSELR_EL1        | Cache Size Selection Register
| CTR_EL0           | Cache Type Register
| CURRENTEL         | Current Exception Level
| DACR32_EL2        | Domain Access Control Register
| DAIF              | Interrupt Mask Bits
| DBGAUTHSTATUS_EL1 | Debug Authentication Status Register
| DBGCLAIMCLR_EL1   | Debug CLAIM Tag Clear Register
| DBGCLAIMSET_EL1   | Debug CLAIM Tag Set Register
| DBGDTR_EL0        | Debug Data Transfer Register, half-duplex
| DBGDTRRX_EL0      | Debug Data Transfer Register, Receive
| DBGDTRTX_EL0      | Debug Data Transfer Register, Transmit
| DBGPRCR_EL1       | Debug Power Control Register
| DBGVCR32_EL2      | Debug Vector Catch Register
| DCZID_EL0         | Data Cache Zero ID Register
| DISR_EL1          | Deferred Interrupt Status Register
| DIT               | Data Independent Timing
| DLR_EL0           | Debug Link Register
| DSPSR_EL0         | Debug Saved Program Status Register
| ELR_EL1           | Exception Link Register (EL1)
| ELR_EL12          | Exception Link Register (EL1&2)
| ELR_EL2           | Exception Link Register (EL2)
| ELR_EL3           | Exception Link Register (EL3)
| ERRIDR_EL1        | Error Record ID Register
| ERRSELR_EL1       | Error Record Select Register
| ERXADDR_EL1       | Selected Error Record Address Register
| ERXCTLR_EL1       | Selected Error Record Control Register
| ERXFR_EL1         | Selected Error Record Feature Register
| ERXGSR_EL1        | Selected Error Record Group Status Register
| ERXMISC0_EL1      | Selected Error Record Miscellaneous Register 0
| ERXMISC1_EL1      | Selected Error Record Miscellaneous Register 1
| ERXMISC2_EL1      | Selected Error Record Miscellaneous Register 2
| ERXMISC3_EL1      | Selected Error Record Miscellaneous Register 3
| ERXPFGCDN_EL1     | Selected Pseudo-fault Generation Countdown Register
| ERXPFGCTL_EL1     | Selected Pseudo-fault Generation Control Register
| ERXPFGF_EL1       | Selected Pseudo-fault Generation Feature Register
| ERXSTATUS_EL1     | Selected Error Record Primary Status Register
| ESR_EL1           | Exception Syndrome Register (EL1)
| ESR_EL12          | Exception Syndrome Register (EL1&2)
| ESR_EL2           | Exception Syndrome Register (EL2)
| ESR_EL3           | Exception Syndrome Register (EL3)
| FAR_EL1           | Fault Address Register (EL1)
| FAR_EL12          | Fault Address Register (EL1&2)
| FAR_EL2           | Fault Address Register (EL2)
| FAR_EL3           | Fault Address Register (EL3)
| FGWTE3_EL3        | Fine-Grained Write Traps EL3
| FPCR              | Floating-point Control Register
| FPEXC32_EL2       | Floating-Point Exception Control Register
| FPMR              | Floating-point Mode Register
| FPSR              | Floating-point Status Register
| GCR_EL1           | Tag Control Register.
| GCSCR_EL1         | Guarded Control Stack Control Register (EL1)
| GCSCR_EL12        | Guarded Control Stack Control Register (EL1&2)
| GCSCR_EL2         | Guarded Control Stack Control Register (EL2)
| GCSCR_EL3         | Guarded Control Stack Control Register (EL3)
| GCSCRE0_EL1       | Guarded Control Stack Control Register (EL0)
| GCSPR_EL0         | Guarded Control Stack Pointer Register (EL0)
| GCSPR_EL1         | Guarded Control Stack Pointer Register (EL1)
| GCSPR_EL12        | Guarded Control Stack Pointer Register (EL1&2)
| GCSPR_EL2         | Guarded Control Stack Pointer Register (EL2)
| GCSPR_EL3         | Guarded Control Stack Pointer Register (EL3)
| GMID_EL1          | Multiple tag transfer ID Register
| GPCBW_EL3         | Granule Protection Check Bypass Window Register (EL3)
| GPCCR_EL3         | Granule Protection Check Control Register (EL3)
| GPTBR_EL3         | Granule Protection Table Base Register
| HACDBSBR_EL2      | Hardware Accelerator for Cleaning Dirty State Base Register
| HACDBSCONS_EL2    | Hardware Accelerator for Cleaning Dirty State Consumer Register
| HACR_EL2          | Hypervisor Auxiliary Control Register
| HAFGRTR_EL2       | Hypervisor Activity Monitors Fine-Grained Read Trap Register
| HCR_EL2           | Hypervisor Configuration Register
| HCRX_EL2          | Extended Hypervisor Configuration Register
| HDBSSBR_EL2       | Hardware Dirty State Tracking Structure Base Register
| HDBSSPROD_EL2     | Hardware Dirty State Tracking Structure Producer Register
| HDFGRTR2_EL2      | Hypervisor Debug Fine-Grained Read Trap Register 2
| HDFGRTR_EL2       | Hypervisor Debug Fine-Grained Read Trap Register
| HDFGWTR2_EL2      | Hypervisor Debug Fine-Grained Write Trap Register 2
| HDFGWTR_EL2       | Hypervisor Debug Fine-Grained Write Trap Register
| HFGITR2_EL2       | Hypervisor Fine-Grained Instruction Trap Register 2
| HFGITR_EL2        | Hypervisor Fine-Grained Instruction Trap Register
| HFGRTR2_EL2       | Hypervisor Fine-Grained Read Trap Register 2
| HFGRTR_EL2        | Hypervisor Fine-Grained Read Trap Register
| HFGWTR2_EL2       | Hypervisor Fine-Grained Write Trap Register 2
| HFGWTR_EL2        | Hypervisor Fine-Grained Write Trap Register
| HPFAR_EL2         | Hypervisor IPA Fault Address Register
| HSTR_EL2          | Hypervisor System Trap Register
| ICC_ASGI1R_EL1    | Interrupt Controller Alias Software Generated Interrupt Group 1 Register
| ICC_BPR0_EL1      | Interrupt Controller Binary Point Register 0
| ICC_BPR1_EL1      | Interrupt Controller Binary Point Register 1
| ICC_CTLR_EL1      | Interrupt Controller Control Register (EL1)
| ICC_CTLR_EL3      | Interrupt Controller Control Register (EL3)
| ICC_DIR_EL1       | Interrupt Controller Deactivate Interrupt Register
| ICC_EOIR0_EL1     | Interrupt Controller End Of Interrupt Register 0
| ICC_EOIR1_EL1     | Interrupt Controller End Of Interrupt Register 1
| ICC_HPPIR0_EL1    | Interrupt Controller Highest Priority Pending Interrupt Register 0
| ICC_HPPIR1_EL1    | Interrupt Controller Highest Priority Pending Interrupt Register 1
| ICC_IAR0_EL1      | Interrupt Controller Interrupt Acknowledge Register 0
| ICC_IAR1_EL1      | Interrupt Controller Interrupt Acknowledge Register 1
| ICC_IGRPEN0_EL1   | Interrupt Controller Interrupt Group 0 Enable Register
| ICC_IGRPEN1_EL1   | Interrupt Controller Interrupt Group 1 Enable Register
| ICC_IGRPEN1_EL3   | Interrupt Controller Interrupt Group 1 Enable Register (EL3)
| ICC_NMIAR1_EL1    | Interrupt Controller Non-maskable Interrupt Acknowledge Register 1
| ICC_PMR_EL1       | Interrupt Controller Interrupt Priority Mask Register
| ICC_RPR_EL1       | Interrupt Controller Running Priority Register
| ICC_SGI0R_EL1     | Interrupt Controller Software Generated Interrupt Group 0 Register
| ICC_SGI1R_EL1     | Interrupt Controller Software Generated Interrupt Group 1 Register
| ICC_SRE_EL1       | Interrupt Controller System Register Enable Register (EL1)
| ICC_SRE_EL2       | Interrupt Controller System Register Enable Register (EL2)
| ICC_SRE_EL3       | Interrupt Controller System Register Enable Register (EL3)
| ICH_EISR_EL2      | Interrupt Controller End of Interrupt Status Register
| ICH_ELRSR_EL2     | Interrupt Controller Empty List Register Status Register
| ICH_HCR_EL2       | Interrupt Controller Hyp Control Register
| ICH_MISR_EL2      | Interrupt Controller Maintenance Interrupt State Register
| ICH_VMCR_EL2      | Interrupt Controller Virtual Machine Control Register
| ICH_VTR_EL2       | Interrupt Controller VGIC Type Register
| ICV_BPR0_EL1      | Interrupt Controller Virtual Binary Point Register 0
| ICV_BPR1_EL1      | Interrupt Controller Virtual Binary Point Register 1
| ICV_CTLR_EL1      | Interrupt Controller Virtual Control Register
| ICV_DIR_EL1       | Interrupt Controller Deactivate Virtual Interrupt Register
| ICV_EOIR0_EL1     | Interrupt Controller Virtual End Of Interrupt Register 0
| ICV_EOIR1_EL1     | Interrupt Controller Virtual End Of Interrupt Register 1
| ICV_HPPIR0_EL1    | Interrupt Controller Virtual Highest Priority Pending Interrupt Register 0
| ICV_HPPIR1_EL1    | Interrupt Controller Virtual Highest Priority Pending Interrupt Register 1
| ICV_IAR0_EL1      | Interrupt Controller Virtual Interrupt Acknowledge Register 0
| ICV_IAR1_EL1      | Interrupt Controller Virtual Interrupt Acknowledge Register 1
| ICV_IGRPEN0_EL1   | Interrupt Controller Virtual Interrupt Group 0 Enable Register
| ICV_IGRPEN1_EL1   | Interrupt Controller Virtual Interrupt Group 1 Enable Register
| ICV_NMIAR1_EL1    | Interrupt Controller Virtual Non-maskable Interrupt Acknowledge Register 1
| ICV_PMR_EL1       | Interrupt Controller Virtual Interrupt Priority Mask Register
| ICV_RPR_EL1       | Interrupt Controller Virtual Running Priority Register
| ID_AA64AFR0_EL1   | AArch64 Auxiliary Feature Register 0
| ID_AA64AFR1_EL1   | AArch64 Auxiliary Feature Register 1
| ID_AA64DFR0_EL1   | AArch64 Debug Feature Register 0
| ID_AA64DFR1_EL1   | AArch64 Debug Feature Register 1
| ID_AA64DFR2_EL1   | Debug Feature Register 2
| ID_AA64FPFR0_EL1  | AArch64 Floating-point Feature Register 0
| ID_AA64ISAR0_EL1  | AArch64 Instruction Set Attribute Register 0
| ID_AA64ISAR1_EL1  | AArch64 Instruction Set Attribute Register 1
| ID_AA64ISAR2_EL1  | AArch64 Instruction Set Attribute Register 2
| ID_AA64ISAR3_EL1  | AArch64 Instruction Set Attribute Register 3
| ID_AA64MMFR0_EL1  | AArch64 Memory Model Feature Register 0
| ID_AA64MMFR1_EL1  | AArch64 Memory Model Feature Register 1
| ID_AA64MMFR2_EL1  | AArch64 Memory Model Feature Register 2
| ID_AA64MMFR3_EL1  | AArch64 Memory Model Feature Register 3
| ID_AA64MMFR4_EL1  | AArch64 Memory Model Feature Register 4
| ID_AA64PFR0_EL1   | AArch64 Processor Feature Register 0
| ID_AA64PFR1_EL1   | AArch64 Processor Feature Register 1
| ID_AA64PFR2_EL1   | AArch64 Processor Feature Register 2
| ID_AA64SMFR0_EL1  | SME Feature ID Register 0
| ID_AA64ZFR0_EL1   | SVE Feature ID Register 0
| ID_AFR0_EL1       | AArch32 Auxiliary Feature Register 0
| ID_DFR0_EL1       | AArch32 Debug Feature Register 0
| ID_DFR1_EL1       | Debug Feature Register 1
| ID_ISAR0_EL1      | AArch32 Instruction Set Attribute Register 0
| ID_ISAR1_EL1      | AArch32 Instruction Set Attribute Register 1
| ID_ISAR2_EL1      | AArch32 Instruction Set Attribute Register 2
| ID_ISAR3_EL1      | AArch32 Instruction Set Attribute Register 3
| ID_ISAR4_EL1      | AArch32 Instruction Set Attribute Register 4
| ID_ISAR5_EL1      | AArch32 Instruction Set Attribute Register 5
| ID_ISAR6_EL1      | AArch32 Instruction Set Attribute Register 6
| ID_MMFR0_EL1      | AArch32 Memory Model Feature Register 0
| ID_MMFR1_EL1      | AArch32 Memory Model Feature Register 1
| ID_MMFR2_EL1      | AArch32 Memory Model Feature Register 2
| ID_MMFR3_EL1      | AArch32 Memory Model Feature Register 3
| ID_MMFR4_EL1      | AArch32 Memory Model Feature Register 4
| ID_MMFR5_EL1      | AArch32 Memory Model Feature Register 5
| ID_PFR0_EL1       | AArch32 Processor Feature Register 0
| ID_PFR1_EL1       | AArch32 Processor Feature Register 1
| ID_PFR2_EL1       | AArch32 Processor Feature Register 2
| IFSR32_EL2        | Instruction Fault Status Register (EL2)
| ISR_EL1           | Interrupt Status Register
| LORC_EL1          | LORegion Control (EL1)
| LOREA_EL1         | LORegion End Address (EL1)
| LORID_EL1         | LORegionID (EL1)
| LORN_EL1          | LORegion Number (EL1)
| LORSA_EL1         | LORegion Start Address (EL1)
| MAIR2_EL1         | Extended Memory Attribute Indirection Register (EL1)
| MAIR2_EL12        | Extended Memory Attribute Indirection Register (EL1&2)
| MAIR2_EL2         | Extended Memory Attribute Indirection Register (EL2)
| MAIR2_EL3         | Extended Memory Attribute Indirection Register (EL3)
| MAIR_EL1          | Memory Attribute Indirection Register (EL1)
| MAIR_EL12         | Memory Attribute Indirection Register (EL1&2)
| MAIR_EL2          | Memory Attribute Indirection Register (EL2)
| MAIR_EL3          | Memory Attribute Indirection Register (EL3)
| MDCCINT_EL1       | Monitor DCC Interrupt Enable Register
| MDCCSR_EL0        | Monitor DCC Status Register
| MDCR_EL2          | Monitor Debug Configuration Register (EL2)
| MDCR_EL3          | Monitor Debug Configuration Register (EL3)
| MDRAR_EL1         | Monitor Debug ROM Address Register
| MDSCR_EL1         | Monitor Debug System Control Register
| MDSELR_EL1        | Breakpoint and Watchpoint Selection Register
| MDSTEPOP_EL1      | Monitor Debug Step Opcode Register
| MECID_A0_EL2      | Alternate MECID for EL2 and EL2&0 translation regimes
| MECID_A1_EL2      | Alternate MECID for EL2&0 translation regimes.
| MECID_P0_EL2      | Primary MECID for EL2 and EL2&0 translation regimes
| MECID_P1_EL2      | Primary MECID for EL2&0 translation regimes
| MECID_RL_A_EL3    | Realm PA space Alternate MECID for EL3 stage 1 translation regime
| MECIDR_EL2        | MEC Identification Register
| MFAR_EL3          | Physical Fault Address Register (EL3)
| MIDR_EL1          | Main ID Register
| MPAM0_EL1         | MPAM0 Register (EL1)
| MPAM1_EL1         | MPAM1 Register (EL1)
| MPAM1_EL12        | MPAM1 Register (EL1&2)
| MPAM2_EL2         | MPAM2 Register (EL2)
| MPAM3_EL3         | MPAM3 Register (EL3)
| MPAMBW0_EL1       | MPAM PE-side Maximum-bandwidth Control Register (EL0)
| MPAMBW1_EL1       | MPAM PE-side Maximum-bandwidth Control Register (EL1)
| MPAMBW1_EL12      | MPAM PE-side Maximum-bandwidth Control Register (EL1&2)
| MPAMBW2_EL2       | MPAM PE-side Maximum-bandwidth Control Register (EL2)
| MPAMBW3_EL3       | MPAM PE-side Maximum-bandwidth Control Register (EL3)
| MPAMBWCAP_EL2     | MPAM PE-side Maximum-bandwidth Limit Virtualization Register
| MPAMBWIDR_EL1     | MPAM PE-side Bandwidth Controls ID Register
| MPAMBWSM_EL1      | MPAM Streaming Mode Bandwidth Control Register (EL1)
| MPAMHCR_EL2       | MPAM Hypervisor Control Register (EL2)
| MPAMIDR_EL1       | MPAM ID Register (EL1)
| MPAMSM_EL1        | MPAM Streaming Mode Register
| MPAMVPM0_EL2      | MPAM Virtual PARTID Mapping Register 0
| MPAMVPM1_EL2      | MPAM Virtual PARTID Mapping Register 1
| MPAMVPM2_EL2      | MPAM Virtual PARTID Mapping Register 2
| MPAMVPM3_EL2      | MPAM Virtual PARTID Mapping Register 3
| MPAMVPM4_EL2      | MPAM Virtual PARTID Mapping Register 4
| MPAMVPM5_EL2      | MPAM Virtual PARTID Mapping Register 5
| MPAMVPM6_EL2      | MPAM Virtual PARTID Mapping Register 6
| MPAMVPM7_EL2      | MPAM Virtual PARTID Mapping Register 7
| MPAMVPMV_EL2      | MPAM Virtual Partition Mapping Valid Register
| MPIDR_EL1         | Multiprocessor Affinity Register
| MVFR0_EL1         | AArch32 Media and VFP Feature Register 0
| MVFR1_EL1         | AArch32 Media and VFP Feature Register 1
| MVFR2_EL1         | AArch32 Media and VFP Feature Register 2
| NZCV              | Condition Flags
| OSDLR_EL1         | OS Double Lock Register
| OSDTRRX_EL1       | OS Lock Data Transfer Register, Receive
| OSDTRTX_EL1       | OS Lock Data Transfer Register, Transmit
| OSECCR_EL1        | OS Lock Exception Catch Control Register
| OSLAR_EL1         | OS Lock Access Register
| OSLSR_EL1         | OS Lock Status Register
| PAN               | Privileged Access Never
| PAR_EL1           | Physical Address Register
| PFAR_EL1          | Physical Fault Address Register (EL1)
| PFAR_EL12         | Physical Fault Address Register (EL1&2)
| PFAR_EL2          | Physical Fault Address Register (EL2)
| PIR_EL1           | Permission Indirection Register 1 (EL1)
| PIR_EL12          | Permission Indirection Register 1 (EL1&2)
| PIR_EL2           | Permission Indirection Register 2 (EL2)
| PIR_EL3           | Permission Indirection Register 3 (EL3)
| PIRE0_EL1         | Permission Indirection Register 0 (EL1)
| PIRE0_EL12        | Permission Indirection Register 0 (EL1&2)
| PIRE0_EL2         | Permission Indirection Register 0 (EL2)
| PM                | Profiling Exception Mask
| PMBIDR_EL1        | Profiling Buffer ID Register
| PMBLIMITR_EL1     | Profiling Buffer Limit Address Register
| PMBMAR_EL1        | Profiling Buffer Memory Attribute Register
| PMBPTR_EL1        | Profiling Buffer Write Pointer Register
| PMBSR_EL1         | Profiling Buffer Status/syndrome Register (EL1)
| PMBSR_EL12        | Profiling Buffer Status/syndrome Register (EL1&2)
| PMBSR_EL2         | Profiling Buffer Syndrome Register (EL2)
| PMBSR_EL3         | Profiling Buffer Syndrome Register (EL3)
| PMCCFILTR_EL0     | Performance Monitors Cycle Count Filter Register
| PMCCNTR_EL0       | Performance Monitors Cycle Count Register
| PMCCNTSVR_EL1     | Performance Monitors Cycle Count Saved Value Register
| PMCEID0_EL0       | Performance Monitors Common Event Identification Register 0
| PMCEID1_EL0       | Performance Monitors Common Event Identification Register 1
| PMCNTENCLR_EL0    | Performance Monitors Count Enable Clear Register
| PMCNTENSET_EL0    | Performance Monitors Count Enable Set Register
| PMCR_EL0          | Performance Monitors Control Register
| PMECR_EL1         | Performance Monitors Extended Control Register (EL1)
| PMIAR_EL1         | Performance Monitors Instruction Address Register
| PMICFILTR_EL0     | Performance Monitors Instruction Counter Filter Register
| PMICNTR_EL0       | Performance Monitors Instruction Counter Register
| PMICNTSVR_EL1     | Performance Monitors Instruction Count Saved Value Register
| PMINTENCLR_EL1    | Performance Monitors Interrupt Enable Clear Register
| PMINTENSET_EL1    | Performance Monitors Interrupt Enable Set Register
| PMMIR_EL1         | Performance Monitors Machine Identification Register
| PMOVSCLR_EL0      | Performance Monitors Overflow Flag Status Clear Register
| PMOVSSET_EL0      | Performance Monitors Overflow Flag Status Set Register
| PMSCR_EL1         | Statistical Profiling Control Register (EL1)
| PMSCR_EL12        | Statistical Profiling Control Register (EL1&2)
| PMSCR_EL2         | Statistical Profiling Control Register (EL2)
| PMSDSFR_EL1       | Sampling Data Source Filter Register
| PMSELR_EL0        | Performance Monitors Event Counter Selection Register
| PMSEVFR_EL1       | Sampling Event Filter Register
| PMSFCR_EL1        | Sampling Filter Control Register
| PMSICR_EL1        | Sampling Interval Counter Register
| PMSIDR_EL1        | Sampling Profiling ID Register
| PMSIRR_EL1        | Sampling Interval Reload Register
| PMSLATFR_EL1      | Sampling Latency Filter Register
| PMSNEVFR_EL1      | Sampling Inverted Event Filter Register
| PMSSCR_EL1        | Performance Monitors Snapshot Status and Capture Register
| PMSWINC_EL0       | Performance Monitors Software Increment Register
| PMUACR_EL1        | Performance Monitors User Access Control Register
| PMUSERENR_EL0     | Performance Monitors User Enable Register
| PMXEVCNTR_EL0     | Performance Monitors Selected Event Count Register
| PMXEVTYPER_EL0    | Performance Monitors Selected Event Type Register
| PMZR_EL0          | Performance Monitors Zero with Mask
| POR_EL0           | Permission Overlay Register 0 (EL0)
| POR_EL1           | Permission Overlay Register 1 (EL1)
| POR_EL12          | Permission Overlay Register 1 (EL1&2)
| POR_EL2           | Permission Overlay Register 2 (EL2)
| POR_EL3           | Permission Overlay Register 3 (EL3)
| RCWMASK_EL1       | Read Check Write Instruction Mask (EL1)
| RCWSMASK_EL1      | Software Read Check Write Instruction Mask (EL1)
| REVIDR_EL1        | Revision ID Register
| RGSR_EL1          | Random Allocation Tag Seed Register.
| RMR_EL1           | Reset Management Register (EL1)
| RMR_EL2           | Reset Management Register (EL2)
| RMR_EL3           | Reset Management Register (EL3)
| RNDR              | Random Number
| RNDRRS            | Random Number Full Entropy
| RVBAR_EL1         | Reset Vector Base Address Register (if EL2 and EL3 not implemented)
| RVBAR_EL2         | Reset Vector Base Address Register (if EL3 not implemented)
| RVBAR_EL3         | Reset Vector Base Address Register (if EL3 implemented)
| S2PIR_EL2         | Stage 2 Permission Indirection Register (EL2)
| S2POR_EL1         | Stage 2 Permission Overlay Register (EL1)
| SCR_EL3           | Secure Configuration Register
| SCTLR2_EL1        | System Control Register (EL1)
| SCTLR2_EL12       | System Control Register (EL1&2)
| SCTLR2_EL2        | System Control Register (EL2)
| SCTLR2_EL3        | System Control Register (EL3)
| SCTLR2ALIAS_EL1   | 
| SCTLR2MASK_EL1    | Extended System Control Masking Register (EL1)
| SCTLR2MASK_EL12   | Extended System Control Masking Register (EL1&2)
| SCTLR2MASK_EL2    | Extended System Control Masking Register (EL2)
| SCTLR_EL1         | System Control Register (EL1)
| SCTLR_EL12        | System Control Register (EL1&2)
| SCTLR_EL2         | System Control Register (EL2)
| SCTLR_EL3         | System Control Register (EL3)
| SCTLRALIAS_EL1    | 
| SCTLRMASK_EL1     | System Control Masking Register (EL1)
| SCTLRMASK_EL12    | System Control Masking Register (EL1&2)
| SCTLRMASK_EL2     | System Control Masking Register (EL2)
| SCXTNUM_EL0       | EL0 Read/Write Software Context Number
| SCXTNUM_EL1       | EL1 Read/Write Software Context Number
| SCXTNUM_EL12      | EL1&2 Read/Write Software Context Number
| SCXTNUM_EL2       | EL2 Read/Write Software Context Number
| SCXTNUM_EL3       | EL3 Read/Write Software Context Number
| SDER32_EL2        | AArch32 Secure Debug Enable Register
| SDER32_EL3        | AArch32 Secure Debug Enable Register
| SMCR_EL1          | SME Control Register (EL1)
| SMCR_EL12         | SME Control Register (EL1&2)
| SMCR_EL2          | SME Control Register (EL2)
| SMCR_EL3          | SME Control Register (EL3)
| SMIDR_EL1         | Streaming Mode Identification Register
| SMPRI_EL1         | Streaming Mode Priority Register
| SMPRIMAP_EL2      | Streaming Mode Priority Mapping Register
| SP_EL0            | Stack Pointer (EL0)
| SP_EL1            | Stack Pointer (EL1)
| SP_EL2            | Stack Pointer (EL2)
| SP_EL3            | Stack Pointer (EL3)
| SPMACCESSR_EL1    | System Performance Monitors Access Register (EL1)
| SPMACCESSR_EL12   | System Performance Monitors Access Register (EL1&2)
| SPMACCESSR_EL2    | System Performance Monitors Access Register (EL2)
| SPMACCESSR_EL3    | System Performance Monitors Access Register (EL3)
| SPMCFGR_EL1       | System Performance Monitors Configuration Register
| SPMCNTENCLR_EL0   | System Performance Monitors Count Enable Clear Register
| SPMCNTENSET_EL0   | System Performance Monitors Count Enable Set Register
| SPMCR_EL0         | System Performance Monitor Control Register
| SPMDEVAFF_EL1     | System Performance Monitors Device Affinity Register
| SPMDEVARCH_EL1    | System Performance Monitors Device Architecture Register
| SPMIIDR_EL1       | System PMU Implementation Identification Register
| SPMINTENCLR_EL1   | System Performance Monitors Interrupt Enable Clear Register
| SPMINTENSET_EL1   | System Performance Monitors Interrupt Enable Set Register
| SPMOVSCLR_EL0     | System Performance Monitors Overflow Flag Status Clear Register
| SPMOVSSET_EL0     | System Performance Monitors Overflow Flag Status Set Register
| SPMROOTCR_EL3     | System Performance Monitors Root and Realm Control Register
| SPMSCR_EL1        | System Performance Monitors Secure Control Register
| SPMSELR_EL0       | System Performance Monitors Select Register
| SPMZR_EL0         | System Performance Monitors Zero with Mask
| SPSEL             | Stack Pointer Select
| SPSR_ABT          | Saved Program Status Register (Abort mode)
| SPSR_EL1          | Saved Program Status Register (EL1)
| SPSR_EL12         | Saved Program Status Register (EL1&2)
| SPSR_EL2          | Saved Program Status Register (EL2)
| SPSR_EL3          | Saved Program Status Register (EL3)
| SPSR_FIQ          | Saved Program Status Register (FIQ mode)
| SPSR_IRQ          | Saved Program Status Register (IRQ mode)
| SPSR_UND          | Saved Program Status Register (Undefined mode)
| SSBS              | Speculative Store Bypass Safe
| SVCR              | Streaming Vector Control Register
| SVCRSM            | 
| SVCRSMZA          | 
| SVCRZA            | 
| TCO               | Tag Check Override
| TCR2_EL1          | Extended Translation Control Register (EL1)
| TCR2_EL12         | Extended Translation Control Register (EL1&2)
| TCR2_EL2          | Extended Translation Control Register (EL2)
| TCR2ALIAS_EL1     | 
| TCR2MASK_EL1      | Extended Translation Control Masking Register (EL1)
| TCR2MASK_EL12     | Extended Translation Control Masking Register (EL1&2)
| TCR2MASK_EL2      | Extended Translation Control Masking Register (EL2)
| TCR_EL1           | Translation Control Register (EL1)
| TCR_EL12          | Translation Control Register (EL1&2)
| TCR_EL2           | Translation Control Register (EL2)
| TCR_EL3           | Translation Control Register (EL3)
| TCRALIAS_EL1      | 
| TCRMASK_EL1       | Translation Control Masking Register (EL1)
| TCRMASK_EL12      | Translation Control Masking Register (EL1&2)
| TCRMASK_EL2       | Translation Control Masking Register (EL2)
| TFSR_EL1          | Tag Fault Status Register (EL1)
| TFSR_EL12         | Tag Fault Status Register (EL1&2)
| TFSR_EL2          | Tag Fault Status Register (EL2)
| TFSR_EL3          | Tag Fault Status Register (EL3)
| TFSRE0_EL1        | Tag Fault Status Register (EL0).
| TPIDR2_EL0        | EL0 Read/Write Software Thread ID Register 2
| TPIDR_EL0         | EL0 Read/Write Software Thread ID Register
| TPIDR_EL1         | EL1 Software Thread ID Register
| TPIDR_EL2         | EL2 Software Thread ID Register
| TPIDR_EL3         | EL3 Software Thread ID Register
| TPIDRRO_EL0       | EL0 Read-Only Software Thread ID Register
| TRBBASER_EL1      | Trace Buffer Base Address Register
| TRBIDR_EL1        | Trace Buffer ID Register
| TRBLIMITR_EL1     | Trace Buffer Limit Address Register
| TRBMAR_EL1        | Trace Buffer Memory Attribute Register
| TRBMPAM_EL1       | Trace Buffer MPAM Configuration Register
| TRBPTR_EL1        | Trace Buffer Write Pointer Register
| TRBSR_EL1         | Trace Buffer Status/syndrome Register (EL1)
| TRBSR_EL12        | Trace Buffer Status/syndrome Register (EL1&2)
| TRBSR_EL2         | Trace Buffer Syndrome Register (EL2)
| TRBSR_EL3         | Trace Buffer Syndrome Register (EL3)
| TRBTRG_EL1        | Trace Buffer Trigger Counter Register
| TRCAUTHSTATUS     | Trace Authentication Status Register
| TRCAUXCTLR        | Trace Auxiliary Control Register
| TRCBBCTLR         | Trace Branch Broadcast Control Register
| TRCCCCTLR         | Trace Cycle Count Control Register
| TRCCIDCCTLR0      | Trace Context Identifier Comparator Control Register 0
| TRCCIDCCTLR1      | Trace Context Identifier Comparator Control Register 1
| TRCCLAIMCLR       | Trace Claim Tag Clear Register
| TRCCLAIMSET       | Trace Claim Tag Set Register
| TRCCONFIGR        | Trace Configuration Register
| TRCDEVARCH        | Trace Device Architecture Register
| TRCDEVID          | Trace Device Configuration Register
| TRCEVENTCTL0R     | Trace Event Control 0 Register
| TRCEVENTCTL1R     | Trace Event Control 1 Register
| TRCIDR0           | Trace ID Register 0
| TRCIDR1           | Trace ID Register 1
| TRCIDR10          | Trace ID Register 10
| TRCIDR11          | Trace ID Register 11
| TRCIDR12          | Trace ID Register 12
| TRCIDR13          | Trace ID Register 13
| TRCIDR2           | Trace ID Register 2
| TRCIDR3           | Trace ID Register 3
| TRCIDR4           | Trace ID Register 4
| TRCIDR5           | Trace ID Register 5
| TRCIDR6           | Trace ID Register 6
| TRCIDR7           | Trace ID Register 7
| TRCIDR8           | Trace ID Register 8
| TRCIDR9           | Trace ID Register 9
| TRCIMSPEC0        | Trace IMP DEF Register 0
| TRCITECR_EL1      | Instrumentation Trace Control Register (EL1)
| TRCITECR_EL12     | Instrumentation Trace Control Register (EL1&2)
| TRCITECR_EL2      | Instrumentation Trace Control Register (EL2)
| TRCITEEDCR        | Instrumentation Trace Extension External Debug Control Register
| TRCOSLSR          | Trace OS Lock Status Register
| TRCPRGCTLR        | Trace Programming Control Register
| TRCQCTLR          | Trace Q Element Control Register
| TRCRSR            | Trace Resources Status Register
| TRCSEQRSTEVR      | Trace Sequencer Reset Control Register
| TRCSEQSTR         | Trace Sequencer State Register
| TRCSTALLCTLR      | Trace Stall Control Register
| TRCSTATR          | Trace Status Register
| TRCSYNCPR         | Trace Synchronization Period Register
| TRCTRACEIDR       | Trace ID Register
| TRCTSCTLR         | Trace Timestamp Control Register
| TRCVICTLR         | Trace ViewInst Main Control Register
| TRCVIIECTLR       | Trace ViewInst Include/Exclude Control Register
| TRCVIPCSSCTLR     | Trace ViewInst Start/Stop PE Comparator Control Register
| TRCVISSCTLR       | Trace ViewInst Start/Stop Control Register
| TRCVMIDCCTLR0     | Trace Virtual Context Identifier Comparator Control Register 0
| TRCVMIDCCTLR1     | Trace Virtual Context Identifier Comparator Control Register 1
| TRFCR_EL1         | Trace Filter Control Register (EL1)
| TRFCR_EL12        | Trace Filter Control Register (EL1&2)
| TRFCR_EL2         | Trace Filter Control Register (EL2)
| TTBR0_EL1         | Translation Table Base Register 0 (EL1)
| TTBR0_EL12        | Translation Table Base Register 0 (EL1&2)
| TTBR0_EL2         | Translation Table Base Register 0 (EL2)
| TTBR0_EL3         | Translation Table Base Register 0 (EL3)
| TTBR1_EL1         | Translation Table Base Register 1 (EL1)
| TTBR1_EL12        | Translation Table Base Register 1 (EL1&2)
| TTBR1_EL2         | Translation Table Base Register 1 (EL2)
| UAO               | User Access Override
| VBAR_EL1          | Vector Base Address Register (EL1)
| VBAR_EL12         | Vector Base Address Register (EL1&2)
| VBAR_EL2          | Vector Base Address Register (EL2)
| VBAR_EL3          | Vector Base Address Register (EL3)
| VDISR_EL2         | Virtual Deferred Interrupt Status Register (EL2)
| VDISR_EL3         | Virtual Deferred Interrupt Status Register (EL3)
| VMECID_A_EL2      | Alternate MECID for EL1&0 stage 2 translation regime
| VMECID_P_EL2      | Primary MECID for EL1&0 stage 2 translation regime
| VMPIDR_EL2        | Virtualization Multiprocessor ID Register
| VNCR_EL2          | Virtual Nested Control Register
| VPIDR_EL2         | Virtualization Processor ID Register
| VSESR_EL2         | Virtual SError Exception Syndrome Register
| VSESR_EL3         | Virtual SError Exception Syndrome Register (EL3)
| VSTCR_EL2         | Virtualization Secure Translation Control Register
| VSTTBR_EL2        | Virtualization Secure Translation Table Base Register
| VTCR_EL2          | Virtualization Translation Control Register
| VTTBR_EL2         | Virtualization Translation Table Base Register
| ZCR_EL1           | SVE Control Register (EL1)
| ZCR_EL12          | SVE Control Register (EL1&2)
| ZCR_EL2           | SVE Control Register (EL2)
| ZCR_EL3           | SVE Control Register (EL3)
