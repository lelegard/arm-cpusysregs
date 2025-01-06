# Bitfields in Arm System Registers for A-Profile

The following tables detail the bitfields in all known Arm system registers by name,
when bitfields are defined in the Arm specification.

The description texts are automatically extracted from the Arm-provided XML files.
This extraction can be rudimentary or even flawed. Just use the description as
an overview and refer to the Arm Architecture Reference Manual for more details.

The Python script `aarch/extract-arm-spec.py` automatically updates these tables,
based on reference JSON and XML files on the Arm public web site. This script should
be executed each time an update of the Arm architecture is published.

<!-- Do not remove the markers AUTOGEN-BEGIN and AUTOGEN-END. -->
<!-- @AUTOGEN-BEGIN -->

## ACCDATA_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ACCDATA  |    31:0 |   32 | Accelerator Data field. Holds bits[31:0] of the data that is stored by an ST64BV0 instruction.

## ALLINT bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ALLINT   |   13:13 |    1 | All interrupt mask. An interrupt is controlled by PSTATE.ALLINT when all of the following apply: SCTLR_ELx .NMI is 1. The interrupt is targeted at ELx. Execution is at ELx.

## AMCFGR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NCG      |   31:28 |    4 | Defines the number of counter groups implemented, minus one.
| HDBG     |   24:24 |    1 | Halt-on-debug supported. This feature must be supported, and so this bit is 0b1 .
| SIZE     |    13:8 |    6 | Defines the size of the activity monitor event counters, minus one. The counters are 64-bit, so the value of this field is 0b111111 . This field is used by software to determine the spacing of the counters in the memory-map. The counters are at doubleword-aligned addresses.
| N        |     7:0 |    8 | Defines the number of activity monitor event counters implemented in all groups, minus one.

## AMCG1IDR_EL0 bitfields

| Bitfield           | msb:lsb | Size | Description
| ------------------ | ------: | ---: | -----------
| AMEVCNTOFF1<n>_EL2 |   31:16 |   16 | Indicates which implemented auxiliary counters have a corresponding virtual offset register, AMEVCNTVOFF1<n>_EL2 implemented.
| AMEVCNTR1<n>_EL0   |    15:0 |   16 | Indicates which auxiliary counters AMEVCNTR1<n>_EL0 are implemented.

## AMCGCR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CG1NC    |    15:8 |    8 | Counter Group 1 Number of Counters. The number of counters in the auxiliary counter group.
| CG0NC    |     7:0 |    8 | Counter Group 0 Number of Counters. The number of counters in the architected counter group.

## AMCNTENCLR0_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P<n>     |     3:0 |    4 | Activity monitor event counter disable bit for AMEVCNTR0<n>_EL0 . AMCGCR_EL0 .CG0NC identifies the number of architected activity monitor event counters. In an implementation that includes FEAT_AMUv1 , the number of architected activity monitor event counters is 4. Possible values of each bit are:

## AMCNTENCLR1_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P<n>     |    15:0 |   16 | Activity monitor event counter disable bit for AMEVCNTR1<n>_EL0 . Possible values of each bit are:

## AMCNTENSET0_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P<n>     |     3:0 |    4 | Activity monitor event counter enable bit for AMEVCNTR0<n>_EL0 . AMCGCR_EL0 .CG0NC identifies the number of architected activity monitor event counters. In an implementation that includes FEAT_AMUv1 , the number of architected activity monitor event counters is 4. Possible values of each bit are:

## AMCNTENSET1_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P<n>     |    15:0 |   16 | Activity monitor event counter enable bit for AMEVCNTR1<n>_EL0 . Possible values of each bit are:

## AMCR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CG1RZ    |   17:17 |    1 | Counter Group 1 Read Zero.
| HDBG     |   10:10 |    1 | This bit controls whether activity monitor counting is halted when the PE is halted in Debug state.

## AMUSERENR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EN       |     0:0 |    1 | Traps EL0 accesses to the activity monitors registers to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, accesses to the following registers are trapped, reported using EC syndrome value 0x18 : AMCFGR_EL0 , AMCGCR_EL0 , AMCNTENCLR0_EL0 , AMCNTENCLR1_EL0 , AMCNTENSET0_EL0 , AMCNTENSET1_EL0 , AMCR_EL0 , AMEVCNTR0<n>_EL0 , AMEVCNTR1<n>_EL0 , AMEVTYPER0<n>_EL0 , and AMEVTYPER1<n>_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 , MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : AMCFGR , AMCGCR , AMCNTENCLR0 , AMCNTENCLR1 , AMCNTENSET0 , AMCNTENSET1 , AMCR , AMEVCNTR0<n> , AMEVCNTR1<n> , AMEVTYPER0<n> , and AMEVTYPER1<n> .

## BRBCR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| EXCEPTION |   23:23 |    1 | Enable the recording of entry to EL1 via an exception.
| ERTN      |   22:22 |    1 | Allow the recording Branch records for exception return instructions from EL1.
| FZPSS     |     9:9 |    1 | Freeze BRBE on PMU Snapshot.
| FZP       |     8:8 |    1 | Freeze BRBE on PMU overflow.
| TS        |     6:5 |    2 | Timestamp Control.
| MPRED     |     4:4 |    1 | Mask the recording of mispredicts.
| CC        |     3:3 |    1 | Enable the recording of cycle count information.
| E1BRE     |     1:1 |    1 | EL1 Branch recording enable.
| E0BRE     |     0:0 |    1 | EL0 Branch recording enable.

## BRBCR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| EXCEPTION |   23:23 |    1 | Enable the recording of entry to EL2 via an exception.
| ERTN      |   22:22 |    1 | Allow the recording Branch records for exception return instructions from EL2.
| FZPSS     |     9:9 |    1 | Freeze BRBE on PMU Snapshot.
| FZP       |     8:8 |    1 | Freeze BRBE on PMU overflow.
| TS        |     6:5 |    2 | Timestamp Control.
| MPRED     |     4:4 |    1 | Mask the recording of mispredicts.
| CC        |     3:3 |    1 | Enable the recording of cycle count information.
| E2BRE     |     1:1 |    1 | EL2 Branch recording enable.
| E0HBRE    |     0:0 |    1 | EL0 Branch recording enable.

## BRBFCR_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| BANK       |   29:28 |    2 | Branch record buffer bank access control.
| CONDDIR    |   22:22 |    1 | Match on conditional direct branch instructions.
| DIRCALL    |   21:21 |    1 | Match on direct branch with link instructions.
| INDCALL    |   20:20 |    1 | Match on indirect branch with link instructions.
| RTN        |   19:19 |    1 | Match on function return instructions.
| INDIRECT   |   18:18 |    1 | Match on indirect branch instructions.
| DIRECT     |   17:17 |    1 | Match on unconditional direct branch instructions.
| EnI        |   16:16 |    1 | Include or exclude matches.
| PAUSED     |     7:7 |    1 | Branch recording Paused status.
| LASTFAILED |     6:6 |    1 | Indicates transaction failure or cancellation.

## BRBIDR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CC       |   15:12 |    4 | Cycle counter support. Defined values are:
| FORMAT   |    11:8 |    4 | Data format of records of the Branch record buffer. Defined values are:
| NUMREC   |     7:0 |    8 | Number of records supported.

## BRBINFINJ_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| CCU        |   46:46 |    1 | The number of PE clock cycles since the last Branch record entry is UNKNOWN .
| CC         |   45:32 |   14 | The number of PE clock cycles since the last Branch record entry. The format of this field uses a mantissa and exponent to express the cycle count value, as follows: CC bits[7:0] indicate the mantissa M. CC bits[13:8] indicate the exponent E. The cycle count is expressed using the following function: if IsZero(E) then UInt(M) else UInt('1':M:Zeros(UInt(E)-1)) If required, the cycle count is rounded to a multiple of 2 (E-1) towards zero before being encoded. A value of all ones in both the mantissa and exponent indicates the cycle count value exceeded the size of the cycle counter.
| LASTFAILED |   17:17 |    1 | Indicates transaction failure or cancellation.
| T          |   16:16 |    1 | Transactional state.
| TYPE       |    13:8 |    6 | Branch type.
| EL         |     7:6 |    2 | The Exception level at the target address.
| MPRED      |     5:5 |    1 | Branch mispredict.
| VALID      |     1:0 |    2 | The Branch record is valid.

## CCSIDR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NumSets  |    23:0 |   24 | (Number of sets in cache) - 1, therefore a value of 0 indicates 1 set in the cache. The number of sets does not have to be a power of 2.

## CCSIDR_EL1 bitfields

| Bitfield      | msb:lsb | Size | Description
| ------------- | ------: | ---: | -----------
| NumSets       |   55:32 |   24 | (Number of sets in cache) - 1, therefore a value of 0 indicates 1 set in the cache. The number of sets does not have to be a power of 2.
| Associativity |    23:3 |   21 | (Associativity of cache) - 1, therefore a value of 0 indicates an associativity of 1. The associativity does not have to be a power of 2.
| LineSize      |     2:0 |    3 | (Log 2 (Number of bytes in cache line)) - 4. For example: For a line length of 16 bytes: Log 2 (16) = 4, LineSize entry = 0. This is the minimum line length. For a line length of 32 bytes: Log 2 (32) = 5, LineSize entry = 1. The C++ 17 specification has two defined parameters relating to the granularity of memory that does not interfere. For generic software and tools, Arm will set the hardware_destructive_interference_size parameter to 256 bytes and the hardware_constructive_interference_size parameter to 64 bytes. When FEAT_MTE2 is implemented, where a cache only holds Allocation tags, this field is RES0 .

## CLIDR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Ttype<n> |   46:33 |   14 | Tag cache type. Indicate the type of cache that is implemented and can be managed using the architected cache maintenance instructions that operate by set/way at each level, from Level 1 up to a maximum of seven levels of cache hierarchy.
| ICB      |   32:30 |    3 | Inner cache boundary. This field indicates the boundary for caching Inner Cacheable memory regions.
| LoUU     |   29:27 |    3 | Level of Unification Uniprocessor for the cache hierarchy. For a description of the values of this field, see Terminology for Clean, Invalidate, and Clean and Invalidate instructions . This field does not describe the requirements for instruction cache invalidation. See CTR_EL0 .DIC. When FEAT_S2FWB is implemented, the architecture requires that this field is zero so that no levels of data cache need to be cleaned in order to manage coherency with instruction fetches.
| LoC      |   26:24 |    3 | Level of Coherence for the cache hierarchy. For a description of the values of this field, see Terminology for Clean, Invalidate, and Clean and Invalidate instructions .
| LoUIS    |   23:21 |    3 | Level of Unification Inner Shareable for the cache hierarchy. For a description of the values of this field, see Terminology for Clean, Invalidate, and Clean and Invalidate instructions . This field does not describe the requirements for instruction cache invalidation. See CTR_EL0 .DIC. When FEAT_S2FWB is implemented, the architecture requires that this field is zero so that no levels of data cache need to be cleaned in order to manage coherency with instruction fetches.
| Ctype<n> |    20:0 |   21 | Cache Type fields. Indicate the type of cache that is implemented and can be managed using the architected cache maintenance instructions that operate by set/way at each level, from Level 1 up to a maximum of seven levels of cache hierarchy. Possible values of each field are:

## CNTFRQ_EL0 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| ClockFreq |    31:0 |   32 | Clock frequency. Indicates the system counter clock frequency, in Hz.

## CNTHCTL_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CNTPMASK |   19:19 |    1 |
| CNTVMASK |   18:18 |    1 |
| EVNTIS   |   17:17 |    1 | Controls the scale of the generation of the event stream.
| EL1NVVCT |   16:16 |    1 | When HCR_EL2 .TGE is 0 and the Effective value of HCR_EL2 .{NV2, NV1, NV} is {1, 0, 1}, traps EL1 accesses to the specified EL1 virtual timer registers using the EL02 descriptors to EL2 as follows: Accesses to CNTV_CTL_EL02 and CNTV_CVAL_EL02 are trapped to EL2 and reported with EC syndrome value 0x18 .
| EL1NVPCT |   15:15 |    1 | When HCR_EL2 .TGE is 0 and the Effective value of HCR_EL2 .{NV2, NV1, NV} is {1, 0, 1}, traps EL1 accesses to the specified EL1 physical timer registers using the EL02 descriptors to EL2 as follows: Accesses to CNTP_CTL_EL02 and CNTP_CVAL_EL02 are trapped to EL2 and reported with EC syndrome value 0x18 .
| EL1TVCT  |   14:14 |    1 | Traps EL0 and EL1 accesses to the EL1 virtual counter registers to EL2 when EL2 is enabled in the current Security state, as follows: In AArch64 state, accesses to CNTVCT_EL0 and CNTVCTSS_EL0 are trapped to EL2 and reported using EC syndrome value 0x18 , unless they are trapped by CNTKCTL_EL1 .EL0VCTEN. In AArch32 state, accesses to CNTVCT are trapped to EL2 and reported with EC syndrome value 0x04 , unless they are trapped by CNTKCTL_EL1 .EL0VCTEN or CNTKCTL .PL0VCTEN.
| EL1TVT   |   13:13 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps EL0 and EL1 accesses to the EL1 virtual timer registers to EL2, when EL2 is enabled for the current Security state, as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 , unless they are trapped by CNTKCTL_EL1 .EL0VTEN: CNTV_CTL_EL0 . CNTV_CVAL_EL0 . CNTV_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x03 , and MCRR and MRRC accesses are trapped to EL2 and reported using EC syndrome value 0x04 , unless they are trapped by CNTKCTL_EL1 .EL0VTEN or CNTKCTL .PL0VTEN: CNTV_CTL . CNTV_CVAL . CNTV_TVAL .
| ECV      |   12:12 |    1 | Enables the Enhanced Counter Virtualization functionality registers. When the Enhanced Counter Virtualization is enabled, the behavior is as follows: An MRS to CNTPCT_EL0 from either EL0 or EL1 that is not trapped will return the value ( PCount <63:0> - CNTPOFF_EL2 <63:0>). The EL1 physical timer interrupt is triggered when (( PCount <63:0> - CNTPOFF_EL2 <63:0>) - PCVal <63:0>) is greater than or equal to 0. PCount <63:0> is the physical count returned when CNTPCT_EL0 is read from EL2 or EL3. PCVal <63:0> is the EL1 physical timer compare value for this timer.
| EL1PTEN  |   11:11 |    1 | When HCR_EL2 .TGE is 0, traps EL0 and EL1 accesses to the EL1 physical timer registers to EL2 when EL2 is enabled in the current Security state, as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 , unless they are trapped by CNTKCTL_EL1 .EL0PTEN: CNTP_CTL_EL0 . CNTP_CVAL_EL0 . CNTP_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 and MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 , unless they are trapped by CNTKCTL_EL1 .EL0PTEN or CNTKCTL .PL0PTEN: CNTP_CTL . CNTP_CVAL . CNTP_TVAL .
| EL1PCTEN |   10:10 |    1 | When HCR_EL2 .TGE is 0, traps EL0 and EL1 accesses to the EL1 physical counter registers to EL2 when EL2 is enabled in the current Security state, as follows: In AArch64 state, accesses to CNTPCT_EL0 and CNTPCTSS_EL0 are trapped to EL2 and reported with EC syndrome value 0x18 , unless they are trapped by CNTKCTL_EL1 .EL0PCTEN. In AArch32 state, MRRC or MCRR accesses to CNTPCT are trapped to EL2 and reported with EC syndrome value 0x04 , unless they are trapped by CNTKCTL_EL1 .EL0PCTEN or CNTKCTL .PL0PCTEN.
| EL0PTEN  |     9:9 |    1 | When HCR_EL2 .TGE is 1, traps EL0 accesses to the physical timer registers to EL2, as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 : CNTP_CTL_EL0 . CNTP_CVAL_EL0 . CNTP_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 and MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTP_CTL . CNTP_CVAL . CNTP_TVAL .
| EL0VTEN  |     8:8 |    1 | When HCR_EL2 .TGE is 1, traps EL0 accesses to the virtual timer registers to EL2 as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 : CNTV_CTL_EL0 . CNTV_CVAL_EL0 . CNTV_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 and MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTV_CTL . CNTV_CVAL . CNTV_TVAL .
| EVNTI    |     7:4 |    4 | Selects which bit of CNTPCT_EL0 , as seen from EL2, is the trigger for the event stream generated from that counter when that stream is enabled. If FEAT_ECV is implemented, and CNTHCTL_EL2.EVNTIS is 1, this field selects a trigger bit in the range 8 to 23 of CNTPCT_EL0 . Otherwise, this field selects a trigger bit in the range 0 to 15 of CNTPCT_EL0 .
| EVNTDIR  |     3:3 |    1 | Controls which transition of the CNTPCT_EL0 trigger bit, as seen from EL2 and defined by EVNTI, generates an event when the event stream is enabled.
| EVNTEN   |     2:2 |    1 | Enables the generation of an event stream from CNTPCT_EL0 as seen from EL2.
| EL0VCTEN |     1:1 |    1 | When HCR_EL2 .TGE is 1, traps EL0 accesses to the frequency register and virtual counter registers to EL2, as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 : CNTVCT_EL0 . CNTVCTSS_EL0 . CNTFRQ_EL0 if CNTHCTL_EL2 .EL0PCTEN is 0. In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 and MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTVCT and if CNTHCTL .EL0PCTEN is 0, CNTFRQ .
| EL0PCTEN |     0:0 |    1 | Traps EL0 accesses to the frequency register and physical counter registers to EL2, as follows: In AArch64 state, accesses to the following registers are trapped to EL2 and reported with EC syndrome value 0x18 : CNTPCT_EL0 . CNTPCTSS_EL0 . CNTFRQ_EL0 if CNTHCTL_EL2 .EL0VCTEN is 0. In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 and MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTPCT and if CNTHCTL_EL2 .EL0VCTEN is 0, CNTFRQ .

## CNTHP_CTL_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTHP_TVAL_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL2 physical timer. On a read of this register: If CNTHP_CTL_EL2 .ENABLE is 0, the value returned is UNKNOWN . If CNTHP_CTL_EL2 .ENABLE is 1, the value returned is ( CNTHP_CVAL_EL2 - CNTPCT_EL0 ). On a write of this register, CNTHP_CVAL_EL2 is set to ( CNTPCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTHP_CTL_EL2 .ENABLE is 1, the timer condition is met when ( CNTPCT_EL0 - CNTHP_CVAL_EL2 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTHP_CTL_EL2 .ISTATUS is set to 1. If CNTHP_CTL_EL2 .IMASK is 0, an interrupt is generated. When CNTHP_CTL_EL2 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CNTHPS_CTL_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTHPS_TVAL_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL2 physical timer. On a read of this register: If CNTHPS_CTL_EL2 .ENABLE is 0, the value returned is UNKNOWN . If CNTHPS_CTL_EL2 .ENABLE is 1, the value returned is ( CNTHPS_CVAL_EL2 - CNTPCT_EL0 ). On a write of this register, CNTHPS_CVAL_EL2 is set to ( CNTPCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTHPS_CTL_EL2 .ENABLE is 1, the timer condition is met when ( CNTPCT_EL0 - CNTHPS_CVAL_EL2 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTHPS_CTL_EL2 .ISTATUS is set to 1. If CNTHPS_CTL_EL2 .IMASK is 0, an interrupt is generated. When CNTHPS_CTL_EL2 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CNTHV_CTL_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTHV_TVAL_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL2 virtual timer. On a read of this register: If CNTHV_CTL_EL2 .ENABLE is 0, the value returned is UNKNOWN . If CNTHV_CTL_EL2 .ENABLE is 1, the value returned is ( CNTHV_CVAL_EL2 - CNTVCT_EL0 ). On a write of this register, CNTHV_CVAL_EL2 is set to ( CNTVCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTHV_CTL_EL2 .ENABLE is 1, the timer condition is met when ( CNTVCT_EL0 - CNTHV_CVAL_EL2 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTHV_CTL_EL2 .ISTATUS is set to 1. If CNTHV_CTL_EL2 .IMASK is 0, an interrupt is generated. When CNTHV_CTL_EL2 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CNTHVS_CTL_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTHVS_TVAL_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL2 virtual timer. On a read of this register: If CNTHVS_CTL_EL2 .ENABLE is 0, the value returned is UNKNOWN . If CNTHVS_CTL_EL2 .ENABLE is 1, the value returned is ( CNTHVS_CVAL_EL2 - CNTVCT_EL0 ). On a write of this register, CNTHVS_CVAL_EL2 is set to ( CNTVCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTHVS_CTL_EL2 .ENABLE is 1, the timer condition is met when (( CNTVCT_EL0 - CNTHVS_CVAL_EL2 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTHVS_CTL_EL2 .ISTATUS is set to 1. If CNTHVS_CTL_EL2 .IMASK is 0, an interrupt is generated. When CNTHVS_CTL_EL2 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CNTKCTL_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CNTPMASK |   19:19 |    1 | Reserved for software use in nested virtualization.
| CNTVMASK |   18:18 |    1 | Reserved for software use in nested virtualization.
| EVNTIS   |   17:17 |    1 | Controls the scale of the generation of the event stream.
| EL1NVVCT |   16:16 |    1 | Reserved for software use in nested virtualization.
| EL1NVPCT |   15:15 |    1 | Reserved for software use in nested virtualization.
| EL1TVCT  |   14:14 |    1 | Reserved for software use in nested virtualization.
| EL1TVT   |   13:13 |    1 | Reserved for software use in nested virtualization.
| ECV      |   12:12 |    1 | Reserved for software use in nested virtualization.
| EL1PTEN  |   11:11 |    1 | Reserved for software use in nested virtualization.
| EL1PCTEN |   10:10 |    1 | Reserved for software use in nested virtualization.
| EL0PTEN  |     9:9 |    1 | Traps EL0 accesses to the physical timer registers to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, the following registers are trapped and reported using EC syndrome value 0x18 : CNTP_CTL_EL0 , CNTP_CVAL_EL0 , and CNTP_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 , MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTP_CTL , CNTP_CVAL , CNTP_TVAL .
| EL0VTEN  |     8:8 |    1 | Traps EL0 accesses to the virtual timer registers to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, accesses to the following registers are trapped and reported using EC syndrome value 0x18 : CNTV_CTL_EL0 , CNTV_CVAL_EL0 , and CNTV_TVAL_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 , MRRC and MCRR accesses are trapped using EC syndrome value 0x04 : CNTV_CTL , CNTV_CVAL , and CNTV_TVAL .
| EVNTI    |     7:4 |    4 | Selects which bit of CNTVCT_EL0 , as seen from EL1, is the trigger for the event stream generated from that counter when that stream is enabled. If FEAT_ECV is implemented, and CNTKCTL_EL1.EVNTIS is 1, this field selects a trigger bit in the range 8 to 23 of CNTVCT_EL0 . Otherwise, this field selects a trigger bit in the range 0 to 15 of CNTVCT_EL0 .
| EVNTDIR  |     3:3 |    1 | Controls which transition of the CNTVCT_EL0 trigger bit, as seen from EL1 and defined by EVNTI, generates an event when the event stream is enabled.
| EVNTEN   |     2:2 |    1 | When FEAT_VHE is not implemented, or the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, enables the generation of an event stream from CNTVCT_EL0 as seen from EL1.
| EL0VCTEN |     1:1 |    1 | Traps EL0 accesses to the frequency register and virtual counter registers to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, accesses to the following registers are trapped and reported using EC syndrome value 0x18 : CNTVCT_EL0 . CNTVCTSS_EL0 . If CNTKCTL_EL1.EL0PCTEN is 0, CNTFRQ_EL0 . In AArch32 state, MRC and MCR accesses to the following registers are trapped and reported using EC syndrome value 0x03 , MRRC and MCRR accesses are trapped and reported using EC syndrome value 0x04 : CNTVCT and if CNTKCTL_EL1.EL0PCTEN is 0, CNTFRQ .
| EL0PCTEN |     0:0 |    1 | Traps EL0 accesses to the frequency register and physical counter register to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, the following registers are trapped and reported using EC syndrome value 0x18 : CNTPCT_EL0 CNTPCTSS_EL0 If CNTKCTL_EL1.EL0VCTEN is 0, CNTFRQ_EL0 . In AArch32 state, MCR or MRC accesses the following registers are trapped and reported using EC syndrome value 0x03 , MCRR or MRRC accesses are trapped and reported using EC syndrome value 0x04 : CNTPCT and if CNTKCTL_EL1.EL0VCTEN is 0, CNTFRQ .

## CNTP_CTL_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTP_TVAL_EL0 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL1 physical timer. On a read of this register: If CNTP_CTL_EL0 .ENABLE is 0, the value returned is UNKNOWN . If CNTP_CTL_EL0 .ENABLE is 1, the value returned is ( CNTP_CVAL_EL0 - CNTPCT_EL0 ). On a write of this register, CNTP_CVAL_EL0 is set to ( CNTPCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTP_CTL_EL0 .ENABLE is 1, the timer condition is met when ( CNTPCT_EL0 - CNTP_CVAL_EL0 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTP_CTL_EL0 .ISTATUS is set to 1. If CNTP_CTL_EL0 .IMASK is 0, an interrupt is generated. When CNTP_CTL_EL0 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled. The value of CNTPCT_EL0 used in these calculations is the value seen at the Exception level that the CNTPCT_EL0 register is being read or written from.

## CNTPS_CTL_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTPS_TVAL_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the secure physical timer. On a read of this register: If CNTPS_CTL_EL1 .ENABLE is 0, the value returned is UNKNOWN . If CNTPS_CTL_EL1 .ENABLE is 1, the value returned is ( CNTPS_CVAL_EL1 - CNTPCT_EL0 ). On a write of this register, CNTPS_CVAL_EL1 is set to ( CNTPCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTPS_CTL_EL1 .ENABLE is 1, the timer condition is met when ( CNTPCT_EL0 - CNTPS_CVAL_EL1 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTPS_CTL_EL1 .ISTATUS is set to 1. If CNTPS_CTL_EL1 .IMASK is 0, an interrupt is generated. When CNTPS_CTL_EL1 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CNTV_CTL_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ISTATUS  |     2:2 |    1 | The status of the timer. This bit indicates whether the timer condition is met:
| IMASK    |     1:1 |    1 | Timer interrupt mask bit. Permitted values are:
| ENABLE   |     0:0 |    1 | Enables the timer. Permitted values are:

## CNTV_TVAL_EL0 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TimerValue |    31:0 |   32 | The TimerValue view of the EL1 virtual timer. On a read of this register: If CNTV_CTL_EL0 .ENABLE is 0, the value returned is UNKNOWN . If CNTV_CTL_EL0 .ENABLE is 1, the value returned is ( CNTV_CVAL_EL0 - CNTVCT_EL0 ). On a write of this register, CNTV_CVAL_EL0 is set to ( CNTVCT_EL0 + TimerValue), where TimerValue is treated as a signed 32-bit integer. When CNTV_CTL_EL0 .ENABLE is 1, the timer condition is met when ( CNTVCT_EL0 - CNTV_CVAL_EL0 ) is greater than or equal to zero. This means that TimerValue acts like a 32-bit downcounter timer. When the timer condition is met: CNTV_CTL_EL0 .ISTATUS is set to 1. If CNTV_CTL_EL0 .IMASK is 0, an interrupt is generated. When CNTV_CTL_EL0 .ENABLE is 0, the TimerValue cannot be read but continues to decrement. When the timer is enabled, the TimerValue represents the elapsed time whether that time was spent enabled or disabled.

## CONTEXTIDR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PROCID   |    31:0 |   32 | Process Identifier. This field must be programmed with a unique value that identifies the current process. In AArch32 state, when TTBCR .EAE is set to 0, CONTEXTIDR .ASID holds the ASID. In AArch64 state, CONTEXTIDR_EL1 is independent of the ASID, and for the EL1&0 translation regime either TTBR0_EL1 or TTBR1_EL1 holds the ASID.

## CONTEXTIDR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PROCID   |    31:0 |   32 | Process Identifier. This field must be programmed with a unique value that identifies the current process.

## CPACR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCPAC    |   31:31 |    1 | Reserved for software use in nested virtualization.
| TAM      |   30:30 |    1 | Reserved for software use in nested virtualization.
| E0POE    |   29:29 |    1 | Enable access to POR_EL0 . Traps EL0 accesses to POR_EL0 , from AArch64 state only to EL1, or to EL2 when it is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1. The exception is reported using EC syndrome value 0x18 .
| TTA      |   28:28 |    1 | Traps EL0 and EL1 System register accesses to all implemented trace registers from both Execution states to EL1, or to EL2 when it is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, accesses to trace registers are trapped, reported using EC syndrome value 0x18 . In AArch32 state, MRC and MCR accesses to trace registers are trapped, reported using EC syndrome value 0x05 . In AArch32 state, MRRC and MCRR accesses to trace registers are trapped, reported using EC syndrome value 0x0C .
| SMEN     |   25:24 |    2 | Traps execution at EL1 and EL0 of SME instructions, SVE instructions when FEAT_SVE is not implemented or the PE is in Streaming SVE mode, and instructions that directly access the SVCR or SMCR_EL1 System registers to EL1, or to EL2 when EL2 is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1. When instructions that directly access the SVCR System register are trapped with reference to this control, the MSR SVCRSM , MSR SVCRZA , and MSR SVCRSMZA instructions are also trapped. The exception is reported using EC syndrome value 0x1D , with an ISS code of 0x0000000 . This field does not affect whether Streaming SVE or SME register values are valid. A trap taken as a result of CPACR_EL1.SMEN has precedence over a trap taken as a result of CPACR_EL1.FPEN.
| FPEN     |   21:20 |    2 | Traps execution at EL1 and EL0 of instructions that access the Advanced SIMD and floating-point registers from both Execution states to EL1, reported using EC syndrome value 0x07 , or to EL2 reported using EC syndrome value 0x00 when EL2 is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1, as follows: In AArch64 state, accesses to FPMR , FPCR , FPSR , and any of the SIMD and floating-point registers V0-V31, including their views as D0-D31 registers or S0-31 registers. In AArch32 state, FPSCR , and any of the SIMD and floating-point registers Q0-15, including their views as D0-D31 registers or S0-31 registers. Traps execution at EL1 and EL0 of  SME and  SVE instructions  to EL1, or to EL2 when EL2 is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1. The exception is reported using EC syndrome value 0x07 . A trap taken as a result of CPACR_EL1.SMEN has precedence over a trap taken as a result of CPACR_EL1.FPEN. A trap taken as a result of CPACR_EL1.ZEN has precedence over a trap taken as a result of CPACR_EL1.FPEN.
| ZEN      |   17:16 |    2 | Traps execution at EL1 and EL0 of SVE instructions when the PE is not in Streaming SVE mode, and instructions that directly access the ZCR_EL1 System register to EL1, or to EL2 when EL2 is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1. The exception is reported using EC syndrome value 0x19 . A trap taken as a result of CPACR_EL1.ZEN has precedence over a trap taken as a result of CPACR_EL1.FPEN.

## CPACRMASK_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCPAC    |   31:31 |    1 | Mask bit for TCPAC.
| TAM      |   30:30 |    1 | Mask bit for TAM.
| E0POE    |   29:29 |    1 | Mask bit for E0POE.
| TTA      |   28:28 |    1 | Mask bit for TTA.
| SMEN     |   24:24 |    1 | Mask bit for SMEN.
| FPEN     |   20:20 |    1 | Mask bit for FPEN.
| ZEN      |   16:16 |    1 | Mask bit for ZEN.

## CPTR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCPAC    |   31:31 |    1 | In AArch64 state, traps accesses to CPACR_EL1 from EL1 to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x18 . In AArch32 state, traps accesses to CPACR from EL1 to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x03 .
| TAM      |   30:30 |    1 | Trap Activity Monitor access. Traps EL1 and EL0 accesses to all Activity Monitor registers to EL2, as follows: In AArch64 state, accesses to the following registers are trapped to EL2, reported using EC syndrome value 0x18 : AMUSERENR_EL0 , AMCFGR_EL0 , AMCGCR_EL0 , AMCNTENCLR0_EL0 , AMCNTENCLR1_EL0 , AMCNTENSET0_EL0 , AMCNTENSET1_EL0 , AMCR_EL0 , AMEVCNTR0<n>_EL0 , AMEVCNTR1<n>_EL0 , AMEVTYPER0<n>_EL0 , and AMEVTYPER1<n>_EL0 . In AArch32 state, MRC or MCR accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x03 : AMUSERENR , AMCFGR , AMCGCR , AMCNTENCLR0 , AMCNTENCLR1 , AMCNTENSET0 , AMCNTENSET1 , AMCR , AMEVTYPER0<n> , and AMEVTYPER1<n> . In AArch32 state, MRRC or MCRR accesses to AMEVCNTR0<n> and AMEVCNTR1<n> , are trapped to EL2, reported using EC syndrome value 0x04 .
| E0POE    |   29:29 |    1 | Enable access to POR_EL0 . Traps EL0 accesses to POR_EL0 to EL2, from AArch64 state only. The exception is reported using EC syndrome value 0x18 .
| TTA      |   28:28 |    1 | Traps System register accesses to all implemented trace registers from both Execution states to EL2, when EL2 is enabled in the current Security state, as follows: In AArch64 state, accesses to trace registers with op0=2, op1=1, and CRn< 0b1000 are trapped to EL2, reported using EC syndrome value 0x18 . In AArch32 state, MRC or MCR accesses to trace registers with cpnum=14, opc1=1, and CRn< 0b1000 are trapped to EL2, reported using EC syndrome value 0x05 .
| SMEN     |   25:24 |    2 | Traps execution at EL2, EL1, and EL0 of SME instructions, SVE instructions when FEAT_SVE is not implemented or the PE is in Streaming SVE mode, and instructions that directly access the SVCR , SMCR_EL1 , or SMCR_EL2 System registers to EL2, when EL2 is enabled in the current Security state. When instructions that directly access the SVCR System register are trapped with reference to this control, the MSR SVCRSM , MSR SVCRZA , and MSR SVCRSMZA instructions are also trapped. The exception is reported using EC syndrome value 0x1D , with an ISS code of 0x0000000 . This field does not affect whether Streaming SVE or SME register values are valid. A trap taken as a result of CPTR_EL2.SMEN has precedence over a trap taken as a result of CPTR_EL2.FPEN.
| FPEN     |   21:20 |    2 | Traps execution at EL2, EL1, and EL0 of instructions that access the Advanced SIMD and floating-point registers from both Execution states to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x07 . Traps execution at EL2, EL1, and EL0 of  SME and  SVE instructions  to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x07 . When FEAT_FPMR is implemented, traps execution at EL2, EL1, and EL0 of instructions that access FPMR to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x07 A trap taken as a result of CPTR_EL2.SMEN has precedence over a trap taken as a result of CPTR_EL2.FPEN. A trap taken as a result of CPTR_EL2.ZEN has precedence over a trap taken as a result of CPTR_EL2.FPEN.
| ZEN      |   17:16 |    2 | Traps execution at EL2, EL1, and EL0 of SVE instructions when the PE is not in Streaming SVE mode, and instructions that directly access the ZCR_EL1 or ZCR_EL2 System registers to EL2, when EL2 is enabled in the current Security state. The exception is reported using EC syndrome value 0x19 . A trap taken as a result of CPTR_EL2.ZEN has precedence over a trap taken as a result of CPTR_EL2.FPEN.

## CPTR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCPAC    |   31:31 |    1 | Traps all of the following to EL3, from both Execution states and any Security state. EL2 accesses to CPTR_EL2 , reported using EC syndrome value 0x18 , or HCPTR , reported using EC syndrome value 0x03 . EL2 and EL1 accesses to CPACR_EL1 reported using EC syndrome value 0x18 , or CPACR reported using EC syndrome value 0x03 . When CPTR_EL3.TCPAC is:
| TAM      |   30:30 |    1 | Trap Activity Monitor access. Traps EL2, EL1, and EL0 accesses to all Activity Monitor registers to EL3. Accesses to the Activity Monitors registers are trapped as follows: In AArch64 state, the following registers are trapped to EL3 and reported using EC syndrome value 0x18 : AMUSERENR_EL0 , AMCFGR_EL0 , AMCGCR_EL0 , AMCNTENCLR0_EL0 , AMCNTENCLR1_EL0 , AMCNTENSET0_EL0 , AMCNTENSET1_EL0 , AMCR_EL0 , AMEVCNTR0<n>_EL0 , AMEVCNTR1<n>_EL0 , AMEVTYPER0<n>_EL0 , and AMEVTYPER1<n>_EL0 . In AArch32 state, accesses with MRC or MCR to the following registers reported using EC syndrome value 0x03 : AMUSERENR , AMCFGR , AMCGCR , AMCNTENCLR0 , AMCNTENCLR1 , AMCNTENSET0 , AMCNTENSET1 , AMCR , AMEVTYPER0<n> , and AMEVTYPER1<n> . In AArch32 state, accesses with MRRC or MCRR to the following registers, reported using EC syndrome value 0x04 : AMEVCNTR0<n> , AMEVCNTR1<n> .
| TTA      |   20:20 |    1 | Traps System register accesses. Accesses to the trace registers, from all Exception levels, any Security state, and both Execution states are trapped to EL3 as follows: In AArch64 state, Trace registers with op0=2, op1=1, and CRn< 0b1000 are trapped to EL3 and reported using EC syndrome value 0x18 . In AArch32 state, accesses using MCR or MRC to the Trace registers with cpnum=14, opc1=1, and CRn< 0b1000 are reported using EC syndrome value 0x05 .
| ESM      |   12:12 |    1 | Traps execution of SME instructions, SVE instructions when FEAT_SVE is not implemented or the PE is in Streaming SVE mode, and instructions that directly access the SMCR_EL1 , SMCR_EL2 , SMCR_EL3 , SMPRI_EL1 , SMPRIMAP_EL2 , or SVCR System registers, from all Exception levels and any Security state, to EL3. When instructions that directly access the SVCR System register are trapped with reference to this control, the MSR SVCRSM , MSR SVCRZA , and MSR SVCRSMZA instructions are also trapped. When direct accesses to SMPRI_EL1 and SMPRIMAP_EL2 are trapped, the exception is reported using EC syndrome value 0x18 . Otherwise, the exception is reported using EC syndrome value 0x1D , with an ISS code of 0x0000000 . This field does not affect whether Streaming SVE or SME register values are valid. A trap taken as a result of CPTR_EL3.ESM has precedence over a trap taken as a result of CPTR_EL3.TFP.
| TFP      |   10:10 |    1 | Traps execution of instructions which access the Advanced SIMD and floating-point functionality, from all Exception levels, any Security state, and both Execution states, to EL3. This includes the following registers, all reported using EC syndrome value 0x07 : FPCR , FPSR , FPEXC32_EL2 , and any of the SIMD and floating-point registers V0-V31, including their views as D0-D31 registers or S0-S31 registers. If FEAT_FPMR is implemented, FPMR . MVFR0 , MVFR1 , MVFR2 , FPSCR , FPEXC , and any of the SIMD and floating-point registers Q0-Q15, including their views as D0-D31 registers or S0-S31 registers. VMSR accesses to FPSID . Permitted VMSR accesses to FPSID are ignored, but for the purposes of this trap the architecture defines a VMSR access to the FPSID from EL1 or higher as an access to a SIMD and floating-point register. Traps execution at all Exception levels of  SME and  SVE instructions  to EL3 from any Security state. The exception is reported using EC syndrome value 0x07 . A trap taken as a result of CPTR_EL3.ESM has precedence over a trap taken as a result of CPTR_EL3.TFP. A trap taken as a result of CPTR_EL3.EZ has precedence over a trap taken as a result of CPTR_EL3.TFP.
| EZ       |     8:8 |    1 | Traps execution of SVE instructions when the PE is not in Streaming SVE mode, and instructions that directly access the ZCR_EL3 , ZCR_EL2 , or ZCR_EL1 System registers, from all Exception levels and any Security state, to EL3. The exception is reported using EC syndrome value 0x19 . A trap taken as a result of CPTR_EL3.EZ has precedence over a trap taken as a result of CPTR_EL3.TFP.

## CPTRMASK_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCPAC    |   31:31 |    1 | Mask bit for TCPAC.
| TAM      |   30:30 |    1 | Mask bit for TAM.
| E0POE    |   29:29 |    1 | Mask bit for E0POE.
| TTA      |   28:28 |    1 | Mask bit for TTA.
| SMEN     |   24:24 |    1 | Mask bit for SMEN.
| FPEN     |   20:20 |    1 | Mask bit for FPEN.
| ZEN      |   16:16 |    1 | Mask bit for ZEN.

## CSSELR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TnD      |     4:4 |    1 | Allocation Tag not Data bit.
| Level    |     3:1 |    3 | Cache level of required cache.
| InD      |     0:0 |    1 | Instruction not Data bit.

## CTR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TminLine |   37:32 |    6 | Tag minimum Line. Log 2 of the number of words covered by Allocation Tags in the smallest cache line of all caches which can contain Allocation tags that are controlled by the PE. For an implementation with cache lines containing 64 bytes of data and 4 Allocation Tags, this will be log 2 (64/4) = 4. For an implementation with Allocations Tags in separate cache lines of 128 Allocation Tags per line, this will be log 2 (128*16/4) = 9.
| DIC      |   29:29 |    1 | Instruction cache invalidation requirements for data to instruction coherence.
| IDC      |   28:28 |    1 | Data cache clean requirements for instruction to data coherence. The meaning of this bit is:
| CWG      |   27:24 |    4 | Cache writeback granule. Log 2 of the number of words of the maximum size of memory that can be overwritten as a result of the eviction of a cache entry that has had a memory location in it modified. A value of 0b0000 indicates that this register does not provide Cache writeback granule information and either: The architectural maximum of 512 words (2KB) must be assumed. The Cache writeback granule can be determined from maximum cache line size encoded in the Cache Size ID Registers. Values greater than 0b1001 are reserved. Arm recommends that an implementation that does not support cache write-back implements this field as 0b0001 . This applies, for example, to an implementation that supports only write-through caches.
| ERG      |   23:20 |    4 | Exclusives reservation granule, and, if FEAT_TME is implemented, transactional reservation granule. Log 2 of the number of words of the maximum size of the reservation granule for the Load-Exclusive and Store-Exclusive instructions, and, if FEAT_TME is implemented, for detecting transactional conflicts. A value of 0b0000 indicates that this register does not provide granule information and the architectural maximum of 512 words (2KB) must be assumed. Value 0b0001 and values greater than 0b1001 are reserved.
| DminLine |   19:16 |    4 | Log 2 of the number of words in the smallest cache line of all the data caches and unified caches that are controlled by the PE.
| L1Ip     |   15:14 |    2 | Level 1 instruction cache policy. Indicates the indexing and tagging policy for the L1 instruction cache.
| IminLine |     3:0 |    4 | Log 2 of the number of words in the smallest cache line of all the instruction caches that are controlled by the PE.

## CURRENTEL bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EL       |     3:2 |    2 | Current Exception level.

## DACR32_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| D<n>     |    31:0 |   32 | Domain n access permission, where n = 0 to 15. Permitted values are:

## DAIF bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| D        |     9:9 |    1 | Process state D mask.
| A        |     8:8 |    1 | SError exception mask bit.
| I        |     7:7 |    1 | IRQ mask bit.
| F        |     6:6 |    1 | FIQ mask bit.

## DBGAUTHSTATUS_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RTNID    |   27:26 |    2 | Root non-invasive debug. This field has the same value as DBGAUTHSTATUS_EL1 .RTID.
| RTID     |   25:24 |    2 | Root invasive debug.
| RLNID    |   15:14 |    2 | Realm non-invasive debug. This field has the same value as DBGAUTHSTATUS_EL1 .RLID.
| RLID     |   13:12 |    2 | Realm invasive debug.
| SNID     |     7:6 |    2 | Secure non-invasive debug.
| SID      |     5:4 |    2 | Secure invasive debug.
| NSNID    |     3:2 |    2 | Non-secure non-invasive debug.
| NSID     |     1:0 |    2 | Non-secure invasive debug.

## DBGCLAIMCLR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CLAIM    |     7:0 |    8 | Read or clear CLAIM tag bits. Reading this field returns the current value of the CLAIM tag bits. Writing a 1 to one of these bits clears the corresponding CLAIM tag bit to 0. This is an indirect write to the CLAIM tag bits. A single write operation can clear multiple CLAIM tag bits to 0. Writing 0 to one of these bits has no effect.

## DBGCLAIMSET_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CLAIM    |     7:0 |    8 | Set CLAIM tag bits. This field is RAO. Writing a 1 to one of these bits sets the corresponding CLAIM tag bit to 1. This is an indirect write to the CLAIM tag bits. A single write operation can set multiple CLAIM tag bits to 1. Writing 0 to one of these bits has no effect.

## DBGDTR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| HighWord |   63:32 |   32 | Writes to this register set DTRRX to the value in this field and do not change RXfull. Reads of this register: If RXfull is 1, return the last value written to DTRTX. If RXfull is 0, return an UNKNOWN value. After the read, RXfull is cleared to 0.
| LowWord  |    31:0 |   32 | Writes to this register set DTRTX to the value in this field and set TXfull to 1. Reads of this register: If RXfull is 1, return the last value written to DTRRX. If RXfull is 0, return an UNKNOWN value. After the read, RXfull is cleared to 0.

## DBGDTRRX_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DTRRX    |    31:0 |   32 | DTRRX. Reads of this register: If RXfull is 1, return the last value written to DTRRX. If RXfull is 0, return an UNKNOWN value. After the read, RXfull is cleared to 0. For the full behavior of the Debug Communications Channel, see 'The Debug Communication Channel and Instruction Transfer Register' .

## DBGDTRTX_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DTRTX    |    31:0 |   32 | DTRTX. Writes to this register: If TXfull is 1, DTRTX is set to an UNKNOWN value. If TXfull is 0, update the value in DTRTX. After the write, TXfull is set to 1. For the full behavior of the Debug Communications Channel, see 'The Debug Communication Channel and Instruction Transfer Register' .

## DBGPRCR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| CORENPDRQ |     0:0 |    1 | Core no powerdown request. Requests emulation of powerdown. This request is typically passed to an external power controller. This means that whether a request causes power up is dependent on the IMPLEMENTATION DEFINED nature of the system. The power controller must not allow the Core power domain to switch off while this bit is 1.

## DBGVCR32_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NSF      |   31:31 |    1 | FIQ vector catch enable in Non-secure state. The exception vector offset is 0x1C .
| NSI      |   30:30 |    1 | IRQ vector catch enable in Non-secure state. The exception vector offset is 0x18 .
| NSD      |   28:28 |    1 | Data Abort exception vector catch enable in Non-secure state. The exception vector offset is 0x10 .
| NSP      |   27:27 |    1 | Prefetch Abort vector catch enable in Non-secure state. The exception vector offset is 0x0C .
| NSS      |   26:26 |    1 | Supervisor Call (SVC) vector catch enable in Non-secure state. The exception vector offset is 0x08 .
| NSU      |   25:25 |    1 | Undefined Instruction vector catch enable in Non-secure state. The exception vector offset is 0x04 .
| SF       |     7:7 |    1 | FIQ vector catch enable in Secure state. The exception vector offset is 0x1C .
| SI       |     6:6 |    1 | IRQ vector catch enable in Secure state. The exception vector offset is 0x18 .
| SD       |     4:4 |    1 | Data Abort exception vector catch enable in Secure state. The exception vector offset is 0x10 .
| SP       |     3:3 |    1 | Prefetch Abort vector catch enable in Secure state. The exception vector offset is 0x0C .
| SS       |     2:2 |    1 | Supervisor Call (SVC) vector catch enable in Secure state. The exception vector offset is 0x08 .
| SU       |     1:1 |    1 | Undefined Instruction vector catch enable in Secure state. The exception vector offset is 0x04 .

## DCZID_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DZP      |     4:4 |    1 | Data Zero Prohibited. This field indicates whether use of DC ZVA instructions is permitted or prohibited. If FEAT_MTE is implemented, this field also indicates whether use of the DC GVA and DC GZVA instructions are permitted or prohibited.
| BS       |     3:0 |    4 | Log 2 of the block size in words. The maximum size supported is 2KB, indicated by value 0b1001 . If FEAT_MTE2 is implemented, the minimum size supported is 16 bytes, indicated by value 0b0010 .

## DISR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| A        |   31:31 |    1 | Set to 1 when an ESB instruction defers an asynchronous SError exception. If the implementation does not include any sources of SError exception that can be synchronized by an Error Synchronization Barrier, then this bit is RES0 .
| IDS      |   24:24 |    1 | Indicates the deferred SError exception type.
| WU       |   17:16 |    2 | Write update. See the description of ESR_ELx .WU for an SError exception.
| AET      |   12:10 |    3 | Asynchronous Error Type. See the description of ESR_ELx .AET for an SError exception.
| EA       |     9:9 |    1 | External abort Type. See the description of ESR_ELx .EA for an SError exception.
| WnRV     |     7:7 |    1 | Write-not-Read Valid. See the description of ESR_ELx .WnRV for an SError exception.
| WnR      |     6:6 |    1 | Write-not-Read. See the description of ESR_ELx .WnR for an SError exception.
| DFSC     |     5:0 |    6 | Fault Status Code. See the description of ESR_ELx .DFSC for an SError exception.

## DIT bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DIT      |   24:24 |    1 | Data Independent Timing.

## DSPSR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| UINJ     |   36:36 |    1 | Inject Undefined Instruction exception. Copied to PSTATE.UINJ on exiting Debug state.
| PPEND    |   33:33 |    1 | PMU Profiling exception pending bit. Copied to PSTATE.PPEND on exiting Debug state.
| N        |   31:31 |    1 | Negative Condition flag. Copied to PSTATE.N on exiting Debug state.
| Z        |   30:30 |    1 | Zero Condition flag. Copied to PSTATE.Z on exiting Debug state.
| C        |   29:29 |    1 | Carry Condition flag. Copied to PSTATE.C on exiting Debug state.
| V        |   28:28 |    1 | Overflow Condition flag. Copied to PSTATE.V on exiting Debug state.
| Q        |   27:27 |    1 | Overflow or saturation flag. Copied to PSTATE.Q on exiting Debug state.
| IT       |   26:25 |    2 | If-Then. Copied to PSTATE.IT on exiting Debug state.
| DIT      |   24:24 |    1 | Data Independent Timing. Copied to PSTATE.DIT on exiting Debug state.
| SSBS     |   23:23 |    1 | Speculative Store Bypass. Copied to PSTATE.SSBS on exiting Debug state.
| PAN      |   22:22 |    1 | Privileged Access Never. Copied to PSTATE.PAN on exiting Debug state.
| SS       |   21:21 |    1 | Software Step. Copied to PSTATE.SS on exiting Debug state.
| IL       |   20:20 |    1 | Illegal Execution state. Copied to PSTATE.IL on exiting Debug state.
| GE       |   19:16 |    4 | Greater than or Equal flags. Copied to PSTATE.GE on exiting Debug state.
| IT[7:2]  |   15:10 |    6 | This field is bits[7:2] of IT[7:0]. See IT[1:0] for the field description.
| E        |     9:9 |    1 | Endianness. Copied to PSTATE.E on exiting Debug state.
| A        |     8:8 |    1 | SError exception mask. Copied to PSTATE.A on exiting Debug state.
| I        |     7:7 |    1 | IRQ interrupt mask. Copied to PSTATE.I on exiting Debug state.
| F        |     6:6 |    1 | FIQ interrupt mask. Copied to PSTATE.F on exiting Debug state.
| T        |     5:5 |    1 | T32 Instruction set state. Copied to PSTATE.T on exiting Debug state.
| M[4]     |     4:4 |    1 | Execution state. Copied to PSTATE.nRW on exiting Debug state.
| M[3:0]   |     3:0 |    4 | AArch32 Mode. Copied to PSTATE.M[3:0] on exiting Debug state.

## ERRIDR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NUM      |    15:0 |   16 | Highest numbered index of the records that can be accessed through the Error Record System registers plus one. Zero indicates no records can be accessed through the Error Record System registers. Each implemented record is owned by a node. A node might own multiple records.

## ERRSELR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SEL      |    15:0 |   16 | Selects the error record accessed through the ERX registers.

## ESR_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| ISS2         |   55:32 |   24 | ISS2 encoding for an exception, the bit assignments are:
| EC           |   31:26 |    6 | Exception Class. Indicates the reason for the exception that this register holds information about. For each EC value, the table references a subsection that gives information about: The cause of the exception, for example the configuration required to enable the trap. The encoding of the associated ISS. Possible values of the EC field are:
| IL           |   25:25 |    1 | Instruction Length for synchronous exceptions. Possible values of this bit are:
| CV           |   24:24 |    1 | Condition code valid.
| MemInst      |   24:24 |    1 | Indicates the memory instruction class causing the exception.
| ISV          |   24:24 |    1 | Instruction Syndrome Valid. Indicates whether the syndrome information in ISS[23:14] is valid.
| IDS          |   24:24 |    1 | IMPLEMENTATION DEFINED syndrome.
| ISV          |   24:24 |    1 | Instruction syndrome valid. Indicates whether the EX bit, ISS[6], is valid, as follows:
| isSETG       |   23:23 |    1 | Indicates whether the instruction belongs to SETGM* or SETGE* class of instruction.
| TFV          |   23:23 |    1 | Trapped Fault Valid bit. Indicates whether the IDF, IXF, UFF, OFF, DZF, and IOF bits hold valid information about trapped floating-point exceptions.
| SAS          |   23:22 |    2 | Syndrome Access Size. Indicates the size of the access attempted by the faulting operation.
| SSE          |   21:21 |    1 | Syndrome Sign Extend. For a byte, halfword, or word load operation, indicates whether the data item must be sign extended.
| COND         |   23:20 |    4 | For exceptions taken from AArch64, this field is set to 0b1110 . The condition code for the trapped instruction. This field is valid only for exceptions taken from AArch32, and only when the value of CV is 1. For exceptions taken from AArch32: When an A32 instruction is trapped, CV is set to 1 and: If the instruction is conditional, COND is set to the condition code field value from the instruction. If the instruction is unconditional, COND is set to 0b1110 . A conditional A32 instruction that is known to pass its condition code check can be presented either: With COND set to 0b1110 , the value for unconditional. With the COND value held in the instruction. When a T32 instruction is trapped, it is IMPLEMENTATION DEFINED whether: CV is set to 0 and COND is set to an UNKNOWN value. Software must examine the SPSR.IT field to determine the condition, if any, of the T32 instruction. CV is set to 1 and COND is set to the condition code for the condition that applied to the instruction. For an implementation that, for both T32 and A32 instructions, takes an exception on a trapped conditional instruction only if the instruction passes its condition code check, these definitions mean that when CV is set to 1 it is IMPLEMENTATION DEFINED whether the COND field is set to 0b1110 , or to the value of any condition that applied to the instruction.
| Op0          |   21:20 |    2 | The Op0 value from the issued instruction.
| ExType       |   23:20 |    4 | The first level classification of GCS exceptions.
| Options      |   22:19 |    4 | Options : the Options field of the instruction.
| FromEpilogue |   18:18 |    1 | Indicates whether the instruction belongs to the epilogue class of Memory Copy or Memory Set instructions.
| ELS          |   18:18 |    1 | Meaning of ELR_ELx.
| WPT          |   23:18 |    6 | Watchpoint number.
| Opc2         |   19:17 |    3 | The Opc2 value from the issued instruction. For a trapped VMRS access, holds the value 0b000 .
| WrongOption  |   17:17 |    1 | Algorithm option.
| Op2          |   19:17 |    3 | The Op2 value from the issued instruction.
| WPTV         |   17:17 |    1 | Watchpoint number Valid.
| Opc1         |   19:16 |    4 | The Opc1 value from the issued instruction.
| OptionA      |   16:16 |    1 | Algorithm type indicated by the PSTATE.C bit.
| SRT          |   20:16 |    5 |
| WU           |   20:16 |    5 | Write Update. Describes whether a store instruction that generated an External abort updated the location.
| WPF          |   16:16 |    1 | Watchpoint might be false-positive.
| SF           |   15:15 |    1 | Sixty Four bit general-purpose register transfer. Width of the register accessed by the instruction is 64-bit.
| FnP          |   15:15 |    1 | FAR not Precise.
| VFV          |   15:15 |    1 | FAR Valid. Indicates the FAR_EL1 register contains a valid virtual address.
| FnP          |   15:15 |    1 | FAR not Precise. This field only has meaning if the FAR is valid; that is, when the FnV field is 0. If the FnV field is 1, the FnP field is 0.
| Opc1         |   16:14 |    3 | The Opc1 value from the issued instruction. For a trapped VMRS access, holds the value 0b111 .
| Op1          |   16:14 |    3 | The Op1 value from the issued instruction.
| PFV          |   14:14 |    1 | FAR Valid. Describes whether the PFAR_EL1 register is valid.
| AR           |   14:14 |    1 | Acquire/Release.
| PFV          |   14:14 |    1 | FAR Valid. Describes whether the PFAR_EL1 register is valid.
| IESB         |   13:13 |    1 | Implicit error synchronization event.
| imm8         |   19:12 |    8 | The immediate value from the issued instruction.
| HDBSSF       |   11:11 |    1 | Indicates that the fault was caused by the HDBSS. When DFSC indicates a Permission fault, this field indicates whether that fault was caused by the HDBSS being full. When DFSC indicates a synchronous External abort on translation table walk or hardware update of translation table, this field indicates whether the fault was caused by a write to the HDBSS. When DFSC indicates a Granule Protection Fault on translation table walk or hardware update of translation table, this field indicates whether the fault was caused by a write to the HDBSS.
| SET          |   12:11 |    2 | Synchronous Error Type. Describes the PE error state after taking the Instruction Abort exception.
| LST          |   12:11 |    2 | Load/Store Type. Used when a Translation fault, Access flag fault, or Permission fault generates a Data Abort.
| SET          |   12:11 |    2 | Synchronous Error Type. Used when a synchronous External abort, not on a Translation table walk or hardware update of the Translation table, generated the Data Abort. Describes the PE error state after taking the Data Abort exception.
| TnD          |   10:10 |    1 | Tag not Data. If a memory access generates a Data Abort for a stage 1 Permission fault, this field indicates whether the fault is due to an Allocation Tag access.
| CRn          |   13:10 |    4 | The CRn value from the issued instruction. For a trapped VMRS access, holds the reg field from the VMRS instruction encoding.
| Rt2          |   14:10 |    5 | The Rt2 value from the issued instruction, the second general-purpose register used for the transfer. If the Rt2 value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt2 value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| destreg      |   14:10 |    5 | The destination register value from the issued instruction, containing the destination address.
| CRn          |   13:10 |    4 | The CRn value from the issued instruction.
| FnV          |   10:10 |    1 | FAR not Valid, for a synchronous External abort other than a synchronous External abort on a translation table walk.
| Raddr        |   14:10 |    5 | Indicates the data address register number supplied in the instruction that has been trapped.
| AET          |   12:10 |    3 | Asynchronous Error Type. Describes the PE error state after taking the SError exception.
| FnV          |   10:10 |    1 | FAR not Valid.
| TagAccess    |     9:9 |    1 | NoTagAccess fault. When EL2 provides information to EL1 regarding a Stage 2 Data Abort, this field indicates whether the fault is due to the NoTagAccess memory attribute.
| EA           |     9:9 |    1 | External abort type. This bit can provide an IMPLEMENTATION DEFINED classification of External aborts. For any abort other than an External abort this bit returns a value of 0.
| GCS          |     8:8 |    1 | Guarded Control Stack data access. If a memory access generates a Data Abort, this field indicates whether the fault is due to a Guarded Control Stack data access.
| CM           |     8:8 |    1 | Cache maintenance. Indicates whether the Data Abort came from a cache maintenance or address translation instruction:
| VECITR       |    10:8 |    3 | For a trapped floating-point exception from an instruction executed in AArch32 state this field is RES1 . For a trapped floating-point exception from an instruction executed in AArch64 state this field is UNKNOWN .
| CM           |     8:8 |    1 | Cache maintenance. Indicates whether the Watchpoint exception came from a cache maintenance instruction:
| AssuredOnly  |     7:7 |    1 | AssuredOnly flag. If EL2 provides information regarding a stage 2 Data Abort to EL1, then this field holds information about the fault. If this field is 1 and ESR_EL1.GCS is also 1 then the AssuredOnly check might have been the result of VTCR_EL2.GCSH configuration.
| S1PTW        |     7:7 |    1 | For a stage 2 fault, indicates whether the fault was a stage 2 fault on an access made for a stage 1 translation table walk:
| IDF          |     7:7 |    1 | Input Denormal floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| WnRV         |     7:7 |    1 | ESR_EL1.WnR valid.
| Overlay      |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| Rt           |     9:6 |    4 | The Rt value from the issued instruction, the general-purpose register used for the transfer. This value represents register pair of X[Rt:0], X[Rt:1].
| WnR          |     6:6 |    1 | Write not Read. Indicates whether a synchronous abort was caused by an instruction writing to a memory location, or by an instruction reading from a memory location.
| EX           |     6:6 |    1 | Exclusive operation. If the ISV bit is set to 1, this bit indicates whether a Load-Exclusive instruction was stepped.
| WnR          |     6:6 |    1 | Write not Read. Indicates whether the Watchpoint exception was caused by an instruction writing to a memory location, or by an instruction reading from a memory location.
| DirtyBit     |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| RN           |     9:5 |    5 | Register Number. Indicates the register number supplied for a WFET or WFIT instruction.
| Rt           |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. If the Rt value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| Rn           |     9:5 |    5 | The Rn value from the issued instruction, the general-purpose register used for the transfer. If the Rn value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rn value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' . This field is valid only when AM[2] is 0, indicating an immediate form of the LDC or STC instruction. When AM[2] is 1, indicating a literal form of the LDC or STC instruction, this field is UNKNOWN .
| srcreg       |     9:5 |    5 | The source register value from the issued instruction, containing either the source address or the source data.
| Rt           |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. For system instructions which require that the opcode Rt field is set to 0b11111 , but where the trapped instruction has a different value of Rt, an implementation is permitted to return the value 0b11111 , instead of the value of Rt from the trapped instruction.
| Rn           |     9:5 |    5 | Indicates a register number used by the instruction that caused the Guarded Control Stack Data Check Exception.
| Rvalue       |     9:5 |    5 | Indicates the data value register number supplied in the instruction that has been trapped.
| Rd           |     9:5 |    5 | The Rd value from the issued instruction, the general purpose register used for the destination.
| Offset       |     4:4 |    1 | Indicates whether the offset is added or subtracted:
| IXF          |     4:4 |    1 | Inexact floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| UFF          |     3:3 |    1 | Underflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| RV           |     2:2 |    1 | Register field Valid. If TI[1] == 1, then this field indicates whether RN holds a valid register number for the register argument to the trapped WFET or WFIT instruction.
| OFF          |     2:2 |    1 | Overflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| CRm          |     4:1 |    4 | The CRm value from the issued instruction. For a trapped VMRS access, holds the value 0b0000 .
| AM           |     3:1 |    3 | Addressing mode. The permitted values of this field are:
| FSC          |     5:1 |    5 | Indicates why the Profiling exception was generated.
| CRm          |     4:1 |    4 | The CRm value from the issued instruction.
| DZF          |     1:1 |    1 | Divide by Zero floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| DnI          |     1:1 |    1 | This field indicates whether the exception is as a result of an Instruction key or a Data key.
| Xs           |     4:0 |    5 | When FEAT_LS64_V is implemented, if a memory access generated by an ST64BV instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. When FEAT_LS64_ACCDATA is implemented, if a memory access generated by an ST64BV0 instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. Otherwise, this field is RES0 .
| ISS          |    24:0 |   25 | Instruction Specific Syndrome. Architecturally, this field can be defined independently for each defined Exception class. However, in practice, some ISS encodings are used for more than one Exception class. Typically, an ISS encoding has a number of subfields. When an ISS subfield holds a register number, the value returned in that field is the AArch64 view of the register number. For an exception taken from AArch32 state, see 'Mapping of the general-purpose registers between the Execution states' . If the AArch32 register descriptor is 0b1111 , then: If the instruction that generated the exception was not UNPREDICTABLE , the field takes the value 0b11111 . If the instruction that generated the exception was UNPREDICTABLE , the field takes an UNKNOWN value that must be either: The AArch64 view of the register number of a register that might have been used at the Exception level from which the exception was taken. The value 0b11111 .
| TI           |     1:0 |    2 | Trapped instruction. Possible values of this bit are:
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| ISS          |    24:0 |   25 |
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| SYNC         |     0:0 |    1 | Indicates whether the Profiling exception was taken synchronously or asynchronously.
| sizereg      |     4:0 |    5 | The size register value from the issued instruction, containing the number of bytes to be transfered or set.
| imm16        |    15:0 |   16 | The value of the immediate field from the HVC or SVC instruction. For an HVC instruction, and for an A64 SVC instruction, this is the value of the imm16 field of the issued instruction. For an A32 or T32 SVC instruction: If the instruction is unconditional, then: For the T32 instruction, this field is zero-extended from the imm8 field of the instruction. For the A32 instruction, this field is the bottom 16 bits of the imm24 field of the instruction. If the instruction is conditional, this field is UNKNOWN .
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| IFSC         |     5:0 |    6 | Instruction Fault Status Code.
| SMTC         |     2:0 |    3 | SME Trap Code. Identifies the reason for instruction trapping.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| IOF          |     0:0 |    1 | Invalid Operation floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| IT           |     4:0 |    5 | Type of the instruction that caused the Guarded Control Stack Data Check Exception.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| IFSC         |     5:0 |    6 | Instruction Fault Status Code.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| Comment      |    15:0 |   16 | Set to the instruction comment field value, zero extended as necessary. For the AArch32 BKPT instructions, the comment field is described as the immediate field.
| BTYPE        |     1:0 |    2 | This field is set to the PSTATE.BTYPE value that generated the Branch Target Exception.
| BnA          |     0:0 |    1 | This field indicates whether the exception is as a result of an A key or a B key.

## ESR_EL2 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| ISS2         |   55:32 |   24 | ISS2 encoding for an exception, the bit assignments are:
| EC           |   31:26 |    6 | Exception Class. Indicates the reason for the exception that this register holds information about. For each EC value, the table references a subsection that gives information about: The cause of the exception, for example the configuration required to enable the trap. The encoding of the associated ISS. Possible values of the EC field are:
| IL           |   25:25 |    1 | Instruction Length for synchronous exceptions. Possible values of this bit are:
| CV           |   24:24 |    1 | Condition code valid.
| MemInst      |   24:24 |    1 | Indicates the memory instruction class causing the exception.
| CV           |   24:24 |    1 | Condition code valid.
| ISV          |   24:24 |    1 | Instruction Syndrome Valid. Indicates whether the syndrome information in ISS[23:14] is valid.
| IDS          |   24:24 |    1 | IMPLEMENTATION DEFINED syndrome.
| ISV          |   24:24 |    1 | Instruction syndrome valid. Indicates whether the EX bit, ISS[6], is valid, as follows:
| isSETG       |   23:23 |    1 | Indicates whether the instruction belongs to SETGM* or SETGE* class of instruction.
| TFV          |   23:23 |    1 | Trapped Fault Valid bit. Indicates whether the IDF, IXF, UFF, OFF, DZF, and IOF bits hold valid information about trapped floating-point exceptions.
| SAS          |   23:22 |    2 | Syndrome Access Size. Indicates the size of the access attempted by the faulting operation.
| TopLevel     |   21:21 |    1 | Indicates if the fault was due to TopLevel.
| SSE          |   21:21 |    1 | Syndrome Sign Extend. For a byte, halfword, or word load operation, indicates whether the data item must be sign extended.
| TopLevel     |   21:21 |    1 | Indicates if the fault was due to TopLevel.
| COND         |   23:20 |    4 | For exceptions taken from AArch64, this field is set to 0b1110 . The condition code for the trapped instruction. This field is valid only for exceptions taken from AArch32, and only when the value of CV is 1. For exceptions taken from AArch32: When an A32 instruction is trapped, CV is set to 1 and: If the instruction is conditional, COND is set to the condition code field value from the instruction. If the instruction is unconditional, COND is set to 0b1110 . A conditional A32 instruction that is known to pass its condition code check can be presented either: With COND set to 0b1110 , the value for unconditional. With the COND value held in the instruction. When a T32 instruction is trapped, it is IMPLEMENTATION DEFINED whether: CV is set to 0 and COND is set to an UNKNOWN value. Software must examine the SPSR.IT field to determine the condition, if any, of the T32 instruction. CV is set to 1 and COND is set to the condition code for the condition that applied to the instruction. For an implementation that, for both T32 and A32 instructions, takes an exception on a trapped conditional instruction only if the instruction passes its condition code check, these definitions mean that when CV is set to 1 it is IMPLEMENTATION DEFINED whether the COND field is set to 0b1110 , or to the value of any condition that applied to the instruction.
| Op0          |   21:20 |    2 | The Op0 value from the issued instruction.
| ExType       |   23:20 |    4 | The first level classification of GCS exceptions.
| Options      |   22:19 |    4 | Options : the Options field of the instruction.
| CCKNOWNPASS  |   19:19 |    1 | Indicates whether the instruction might have failed its condition code check.
| FromEpilogue |   18:18 |    1 | Indicates whether the instruction belongs to the epilogue class of Memory Copy or Memory Set instructions.
| ELS          |   18:18 |    1 | Meaning of ELR_ELx.
| WPT          |   23:18 |    6 | Watchpoint number.
| Opc2         |   19:17 |    3 | The Opc2 value from the issued instruction. For a trapped VMRS access, holds the value 0b000 .
| WrongOption  |   17:17 |    1 | Algorithm option.
| Op2          |   19:17 |    3 | The Op2 value from the issued instruction.
| WPTV         |   17:17 |    1 | Watchpoint number Valid.
| Opc1         |   19:16 |    4 | The Opc1 value from the issued instruction.
| OptionA      |   16:16 |    1 | Algorithm type indicated by the PSTATE.C bit.
| SRT          |   20:16 |    5 |
| WU           |   20:16 |    5 | Write Update. Describes whether a store instruction that generated an External abort updated the location.
| WPF          |   16:16 |    1 | Watchpoint might be false-positive.
| SF           |   15:15 |    1 | Sixty Four bit general-purpose register transfer. Width of the register accessed by the instruction is 64-bit.
| FnP          |   15:15 |    1 | FAR not Precise.
| VFV          |   15:15 |    1 | FAR Valid. Indicates the FAR_EL2 register contains a valid virtual address.
| FnP          |   15:15 |    1 | FAR not Precise. This field only has meaning if the FAR is valid; that is, when the FnV field is 0. If the FnV field is 1, the FnP field is 0.
| Opc1         |   16:14 |    3 | The Opc1 value from the issued instruction. For a trapped VMRS access, holds the value 0b111 .
| Op1          |   16:14 |    3 | The Op1 value from the issued instruction.
| PFV          |   14:14 |    1 | FAR Valid. Describes whether the PFAR_EL2 register is valid.
| AR           |   14:14 |    1 | Acquire/Release.
| PFV          |   14:14 |    1 | FAR Valid. Describes whether the PFAR_EL2 register is valid.
| VNCR         |   13:13 |    1 | Indicates that the fault came from use of VNCR_EL2 register by EL1 code.
| IESB         |   13:13 |    1 | Implicit error synchronization event.
| VNCR         |   13:13 |    1 | Indicates that the watchpoint came from use of VNCR_EL2 register by EL1 code.
| imm8         |   19:12 |    8 | The immediate value from the issued instruction.
| HDBSSF       |   11:11 |    1 | Indicates that the fault was caused by the HDBSS. When DFSC indicates a Permission fault, this field indicates whether that fault was caused by the HDBSS being full. When DFSC indicates a synchronous External abort on translation table walk or hardware update of translation table, this field indicates whether the fault was caused by a write to the HDBSS. When DFSC indicates a Granule Protection Fault on translation table walk or hardware update of translation table, this field indicates whether the fault was caused by a write to the HDBSS.
| SET          |   12:11 |    2 | Synchronous Error Type. When IFSC is 0b010000 , describes the PE error state after taking the Instruction Abort exception.
| LST          |   12:11 |    2 | Load/Store Type. Used when a Translation fault, Access flag fault, or Permission fault generates a Data Abort.
| SET          |   12:11 |    2 | Synchronous Error Type. Used when a synchronous External abort, not on a Translation table walk or hardware update of the Translation table, generated the Data Abort. Describes the PE error state after taking the Data Abort exception.
| TnD          |   10:10 |    1 | Tag not Data. If a memory access generates a Data Abort for a stage 1 Permission fault, this field indicates whether the fault is due to an Allocation Tag access.
| CRn          |   13:10 |    4 | The CRn value from the issued instruction. For a trapped VMRS access, holds the reg field from the VMRS instruction encoding.
| Rt2          |   14:10 |    5 | The Rt2 value from the issued instruction, the second general-purpose register used for the transfer. If the Rt2 value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt2 value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| destreg      |   14:10 |    5 | The destination register value from the issued instruction, containing the destination address.
| CRn          |   13:10 |    4 | The CRn value from the issued instruction.
| FnV          |   10:10 |    1 | FAR not Valid, for a synchronous External abort other than a synchronous External abort on a translation table walk.
| Raddr        |   14:10 |    5 | Indicates the data address register number supplied in the instruction that has been trapped.
| AET          |   12:10 |    3 | Asynchronous Error Type. Describes the PE error state after taking the SError exception.
| FnV          |   10:10 |    1 | FAR not Valid.
| TagAccess    |     9:9 |    1 | NoTagAccess fault. If a memory access generates a Data Abort for a Permission fault, this field indicates whether the fault is due to the NoTagAccess memory attribute.
| EA           |     9:9 |    1 | External abort type. This bit can provide an IMPLEMENTATION DEFINED classification of External aborts. For any abort other than an External abort this bit returns a value of 0.
| GCS          |     8:8 |    1 | Guarded Control Stack data access. If a memory access generates a Data Abort, this field indicates whether the fault is due to a Guarded Control Stack data access.
| CM           |     8:8 |    1 | Cache maintenance. Indicates whether the Data Abort came from a cache maintenance or address translation instruction:
| VECITR       |    10:8 |    3 | For a trapped floating-point exception from an instruction executed in AArch32 state this field is RES1 . For a trapped floating-point exception from an instruction executed in AArch64 state this field is UNKNOWN .
| CM           |     8:8 |    1 | Cache maintenance. Indicates whether the Watchpoint exception came from a cache maintenance instruction:
| AssuredOnly  |     7:7 |    1 | AssuredOnly flag. If a memory access generates a Data Abort for a stage 2 Permission fault, this field holds information about the fault. If this field is 1 and ESR_EL2.GCS is 1, then the AssuredOnly check might have been the result of VTCR_EL2.GCSH configuration.
| S1PTW        |     7:7 |    1 | For a stage 2 fault, indicates whether the fault was a stage 2 fault on an access made for a stage 1 translation table walk:
| IDF          |     7:7 |    1 | Input Denormal floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| WnRV         |     7:7 |    1 | ESR_EL2.WnR valid.
| Overlay      |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, this field holds information about the fault.
| Rt           |     9:6 |    4 | The Rt value from the issued instruction, the general-purpose register used for the transfer. This value represents register pair of X[Rt:0], X[Rt:1].
| WnR          |     6:6 |    1 | Write not Read. Indicates whether a synchronous abort was caused by an instruction writing to a memory location, or by an instruction reading from a memory location.
| EX           |     6:6 |    1 | Exclusive operation. If the ISV bit is set to 1, this bit indicates whether a Load-Exclusive instruction was stepped.
| WnR          |     6:6 |    1 | Write not Read. Indicates whether the Watchpoint exception was caused by an instruction writing to a memory location, or by an instruction reading from a memory location.
| DirtyBit     |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, this field holds information about the fault.
| RN           |     9:5 |    5 | Register Number. Indicates the register number supplied for a WFET or WFIT instruction.
| Rt           |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. If the Rt value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| Rn           |     9:5 |    5 | The Rn value from the issued instruction, the general-purpose register used for the transfer. If the Rn value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rn value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' . This field is valid only when AM[2] is 0, indicating an immediate form of the LDC or STC instruction. When AM[2] is 1, indicating a literal form of the LDC or STC instruction, this field is UNKNOWN .
| srcreg       |     9:5 |    5 | The source register value from the issued instruction, containing either the source address or the source data.
| Rt           |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. For system instructions which require that the opcode Rt field is set to 0b11111 , but where the trapped instruction has a different value of Rt, an implementation is permitted to return the value 0b11111 , instead of the value of Rt from the trapped instruction.
| Rn           |     9:5 |    5 | Indicates a register number used by the instruction that caused the Guarded Control Stack Data Check Exception.
| Rvalue       |     9:5 |    5 | Indicates the data value register number supplied in the instruction that has been trapped.
| Rd           |     9:5 |    5 | The Rd value from the issued instruction, the general purpose register used for the destination.
| Offset       |     4:4 |    1 | Indicates whether the offset is added or subtracted:
| IXF          |     4:4 |    1 | Inexact floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| UFF          |     3:3 |    1 | Underflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| RV           |     2:2 |    1 | Register field Valid. If TI[1] == 1, then this field indicates whether RN holds a valid register number for the register argument to the trapped WFET or WFIT instruction.
| OFF          |     2:2 |    1 | Overflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| CRm          |     4:1 |    4 | The CRm value from the issued instruction. For a trapped VMRS access, holds the value 0b0000 .
| AM           |     3:1 |    3 | Addressing mode. The permitted values of this field are:
| FSC          |     5:1 |    5 | Indicates why the Profiling exception was generated.
| CRm          |     4:1 |    4 | The CRm value from the issued instruction.
| DZF          |     1:1 |    1 | Divide by Zero floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| ERET         |     1:1 |    1 | Indicates whether an ERET or ERETA* instruction was trapped to EL2.
| DnI          |     1:1 |    1 | This field indicates whether the exception is as a result of an Instruction key or a Data key.
| Xs           |     4:0 |    5 | When FEAT_LS64_V is implemented, if a memory access generated by an ST64BV instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. When FEAT_LS64_ACCDATA is implemented, if a memory access generated by an ST64BV0 instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. Otherwise, this field is RES0 .
| ISS          |    24:0 |   25 | Instruction Specific Syndrome. Architecturally, this field can be defined independently for each defined Exception class. However, in practice, some ISS encodings are used for more than one Exception class. Typically, an ISS encoding has a number of subfields. When an ISS subfield holds a register number, the value returned in that field is the AArch64 view of the register number. For an exception taken from AArch32 state, see 'Mapping of the general-purpose registers between the Execution states' . If the AArch32 register descriptor is 0b1111 , then: If the instruction that generated the exception was not UNPREDICTABLE , the field takes the value 0b11111 . If the instruction that generated the exception was UNPREDICTABLE , the field takes an UNKNOWN value that must be either: The AArch64 view of the register number of a register that might have been used at the Exception level from which the exception was taken. The value 0b11111 .
| TI           |     1:0 |    2 | Trapped instruction. Possible values of this bit are:
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| ISS          |    24:0 |   25 |
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| SYNC         |     0:0 |    1 | Indicates whether the Profiling exception was taken synchronously or asynchronously.
| sizereg      |     4:0 |    5 | The size register value from the issued instruction, containing the number of bytes to be transfered or set.
| imm16        |    15:0 |   16 | The value of the immediate field from the HVC or SVC instruction. For an HVC instruction, and for an A64 SVC instruction, this is the value of the imm16 field of the issued instruction. For an A32 or T32 SVC instruction: If the instruction is unconditional, then: For the T32 instruction, this field is zero-extended from the imm8 field of the instruction. For the A32 instruction, this field is the bottom 16 bits of the imm24 field of the instruction. If the instruction is conditional, this field is UNKNOWN .
| Direction    |     0:0 |    1 | Indicates the direction of the trapped instruction.
| IFSC         |     5:0 |    6 | Instruction Fault Status Code.
| SMTC         |     2:0 |    3 | SME Trap Code. Identifies the reason for instruction trapping.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| IOF          |     0:0 |    1 | Invalid Operation floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| IT           |     4:0 |    5 | Type of the instruction that caused the Guarded Control Stack Data Check Exception.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| IFSC         |     5:0 |    6 | Instruction Fault Status Code.
| DFSC         |     5:0 |    6 | Data Fault Status Code.
| Comment      |    15:0 |   16 | Set to the instruction comment field value, zero extended as necessary. For the AArch32 BKPT instructions, the comment field is described as the immediate field.
| ERETA        |     0:0 |    1 | Indicates whether an ERETAA or ERETAB instruction was trapped to EL2.
| BTYPE        |     1:0 |    2 | This field is set to the PSTATE.BTYPE value that generated the Branch Target Exception.
| BnA          |     0:0 |    1 | This field indicates whether the exception is as a result of an A key or a B key.

## ESR_EL3 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| ISS2                   |   55:32 |   24 | ISS2 encoding for an exception, the bit assignments are:
| EC                     |   31:26 |    6 | Exception Class. Indicates the reason for the exception that this register holds information about. For each EC value, the table references a subsection that gives information about: The cause of the exception, for example the configuration required to enable the trap. The encoding of the associated ISS. Possible values of the EC field are:
| IL                     |   25:25 |    1 | Instruction Length for synchronous exceptions. Possible values of this bit are:
| CV                     |   24:24 |    1 | Condition code valid.
| MemInst                |   24:24 |    1 | Indicates the memory instruction class causing the exception.
| CV                     |   24:24 |    1 | Condition code valid.
| ISV                    |   24:24 |    1 | Instruction Syndrome Valid. Indicates whether the syndrome information in ISS[23:14] is valid.
| IDS                    |   24:24 |    1 | IMPLEMENTATION DEFINED syndrome.
| isSETG                 |   23:23 |    1 | Indicates whether the instruction belongs to SETGM* or SETGE* class of instruction.
| TFV                    |   23:23 |    1 | Trapped Fault Valid bit. Indicates whether the IDF, IXF, UFF, OFF, DZF, and IOF bits hold valid information about trapped floating-point exceptions.
| SAS                    |   23:22 |    2 | Syndrome Access Size. Indicates the size of the access attempted by the faulting operation.
| S2PTW                  |   21:21 |    1 | Indicates whether the Granule Protection Check exception was on an access made for a stage 2 translation table walk.
| SSE                    |   21:21 |    1 | Syndrome Sign Extend. For a byte, halfword, or word load operation, indicates whether the data item must be sign extended.
| COND                   |   23:20 |    4 | For exceptions taken from AArch64, this field is set to 0b1110 . The condition code for the trapped instruction. This field is valid only for exceptions taken from AArch32, and only when the value of CV is 1. For exceptions taken from AArch32: When an A32 instruction is trapped, CV is set to 1 and: If the instruction is conditional, COND is set to the condition code field value from the instruction. If the instruction is unconditional, COND is set to 0b1110 . A conditional A32 instruction that is known to pass its condition code check can be presented either: With COND set to 0b1110 , the value for unconditional. With the COND value held in the instruction. When a T32 instruction is trapped, it is IMPLEMENTATION DEFINED whether: CV is set to 0 and COND is set to an UNKNOWN value. Software must examine the SPSR.IT field to determine the condition, if any, of the T32 instruction. CV is set to 1 and COND is set to the condition code for the condition that applied to the instruction. For an implementation that, for both T32 and A32 instructions, takes an exception on a trapped conditional instruction only if the instruction passes its condition code check, these definitions mean that when CV is set to 1 it is IMPLEMENTATION DEFINED whether the COND field is set to 0b1110 , or to the value of any condition that applied to the instruction.
| Op0                    |   21:20 |    2 | The Op0 value from the issued instruction.
| InD                    |   20:20 |    1 | Indicates whether the Granule Protection Check exception was on an instruction or data access.
| ExType                 |   23:20 |    4 | The first level classification of GCS exceptions.
| Options                |   22:19 |    4 | Options : the Options field of the instruction.
| CCKNOWNPASS            |   19:19 |    1 | Indicates whether the instruction might have failed its condition code check.
| FromEpilogue           |   18:18 |    1 | Indicates whether the instruction belongs to the epilogue class of Memory Copy or Memory Set instructions.
| ELS                    |   18:18 |    1 | Meaning of ELR_ELx.
| Opc2                   |   19:17 |    3 | The Opc2 value from the issued instruction. For a trapped VMRS access, holds the value 0b000 .
| WrongOption            |   17:17 |    1 | Algorithm option.
| Op2                    |   19:17 |    3 | The Op2 value from the issued instruction.
| Opc1                   |   19:16 |    4 | The Opc1 value from the issued instruction.
| OptionA                |   16:16 |    1 | Algorithm type indicated by the PSTATE.C bit.
| SRT                    |   20:16 |    5 |
| WU                     |   20:16 |    5 | Write Update. Describes whether a store instruction that generated an External abort updated the location.
| SF                     |   15:15 |    1 | Sixty Four bit general-purpose register transfer. Width of the register accessed by the instruction is 64-bit.
| FnP                    |   15:15 |    1 | FAR not Precise.
| VFV                    |   15:15 |    1 | FAR Valid. Indicates the FAR_EL3 register contains a valid virtual address.
| Opc1                   |   16:14 |    3 | The Opc1 value from the issued instruction. For a trapped VMRS access, holds the value 0b111 .
| Op1                    |   16:14 |    3 | The Op1 value from the issued instruction.
| PFV                    |   14:14 |    1 | FAR Valid. Describes whether the MFAR_EL3 register is valid.
| GPCSC                  |   19:14 |    6 | Granule Protection Check Status Code.
| AR                     |   14:14 |    1 | Acquire/Release.
| PFV                    |   14:14 |    1 | FAR Valid. Describes whether the MFAR_EL3 register is valid.
| VNCR                   |   13:13 |    1 | Indicates that the fault came from use of VNCR_EL2 register by EL1 code.
| IESB                   |   13:13 |    1 | Implicit error synchronization event.
| imm8                   |   19:12 |    8 | The immediate value from the issued instruction.
| HDBSSF                 |   11:11 |    1 | Indicates that the fault was caused by the HDBSS. When DFSC indicates a synchronous External abort on translation table walk or hardware update of translation table, this field indicates whether the fault was caused by a write to the HDBSS.
| SET                    |   12:11 |    2 | Synchronous Error Type. Describes the PE error state after taking the Instruction Abort exception.
| LST                    |   12:11 |    2 | Load/Store Type. Used when a Translation fault, Access flag fault, or Permission fault generates a Data Abort.
| SET                    |   12:11 |    2 | Synchronous Error Type. Used when a synchronous External abort, not on a Translation table walk or hardware update of the Translation table, generated the Data Abort. Describes the PE error state after taking the Data Abort exception.
| TnD                    |   10:10 |    1 | Tag not Data. If a memory access generates a Data Abort for a stage 1 Permission fault, this field indicates whether the fault is due to an Allocation Tag access.
| CRn                    |   13:10 |    4 | The CRn value from the issued instruction. For a trapped VMRS access, holds the reg field from the VMRS instruction encoding.
| Rt2                    |   14:10 |    5 | The Rt2 value from the issued instruction, the second general-purpose register used for the transfer. If the Rt2 value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt2 value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| destreg                |   14:10 |    5 | The destination register value from the issued instruction, containing the destination address.
| CRn                    |   13:10 |    4 | The CRn value from the issued instruction.
| FnV                    |   10:10 |    1 | FAR not Valid, for a synchronous External abort other than a synchronous External abort on a translation table walk.
| Raddr                  |   14:10 |    5 | Indicates the data address register number supplied in the instruction that has been trapped.
| AET                    |   12:10 |    3 | Asynchronous Error Type. Describes the PE error state after taking the SError exception.
| EA                     |     9:9 |    1 | External abort type. This bit can provide an IMPLEMENTATION DEFINED classification of External aborts. For any abort other than an External abort this bit returns a value of 0.
| GCS                    |     8:8 |    1 | Guarded Control Stack data access. If a memory access generates a Data Abort, this field indicates whether the fault is due to a Guarded Control Stack data access.
| CM                     |     8:8 |    1 | Cache maintenance. Indicates whether the Data Abort came from a cache maintenance or address translation instruction:
| VECITR                 |    10:8 |    3 | For a trapped floating-point exception from an instruction executed in AArch32 state this field is RES1 . For a trapped floating-point exception from an instruction executed in AArch64 state this field is UNKNOWN .
| S1PTW                  |     7:7 |    1 | For a stage 2 fault, indicates whether the fault was a stage 2 fault on an access made for a stage 1 translation table walk:
| IDF                    |     7:7 |    1 | Input Denormal floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| WnRV                   |     7:7 |    1 | ESR_EL3.WnR valid.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| Rt                     |     9:6 |    4 | The Rt value from the issued instruction, the general-purpose register used for the transfer. This value represents register pair of X[Rt:0], X[Rt:1].
| WnR                    |     6:6 |    1 | Write not Read. Indicates whether a synchronous abort was caused by an instruction writing to a memory location, or by an instruction reading from a memory location.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| RN                     |     9:5 |    5 | Register Number. Indicates the register number supplied for a WFET or WFIT instruction.
| Rt                     |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. If the Rt value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rt value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' .
| Rn                     |     9:5 |    5 | The Rn value from the issued instruction, the general-purpose register used for the transfer. If the Rn value is not 0b1111 , then the reported value gives the AArch64 view of the register. Otherwise, if the Rn value is 0b1111 : If the instruction that generated the exception is not UNPREDICTABLE , then the register specifier takes the value 0b11111 . If the instruction that generated the exception is UNPREDICTABLE , then the register specifier takes an UNKNOWN value, which is restricted to either: The AArch64 view of one of the registers that could have been used in AArch32 state at the Exception level that the instruction was executed at. The value 0b11111 . See 'Mapping of the general-purpose registers between the Execution states' . This field is valid only when AM[2] is 0, indicating an immediate form of the LDC or STC instruction. When AM[2] is 1, indicating a literal form of the LDC or STC instruction, this field is UNKNOWN .
| srcreg                 |     9:5 |    5 | The source register value from the issued instruction, containing either the source address or the source data.
| Rt                     |     9:5 |    5 | The Rt value from the issued instruction, the general-purpose register used for the transfer. For system instructions which require that the opcode Rt field is set to 0b11111 , but where the trapped instruction has a different value of Rt, an implementation is permitted to return the value 0b11111 , instead of the value of Rt from the trapped instruction.
| Rn                     |     9:5 |    5 | Indicates a register number used by the instruction that caused the Guarded Control Stack Data Check Exception.
| Rvalue                 |     9:5 |    5 | Indicates the data value register number supplied in the instruction that has been trapped.
| Rd                     |     9:5 |    5 | The Rd value from the issued instruction, the general purpose register used for the destination.
| Offset                 |     4:4 |    1 | Indicates whether the offset is added or subtracted:
| IXF                    |     4:4 |    1 | Inexact floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| UFF                    |     3:3 |    1 | Underflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| RV                     |     2:2 |    1 | Register field Valid. If TI[1] == 1, then this field indicates whether RN holds a valid register number for the register argument to the trapped WFET or WFIT instruction.
| OFF                    |     2:2 |    1 | Overflow floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| CRm                    |     4:1 |    4 | The CRm value from the issued instruction. For a trapped VMRS access, holds the value 0b0000 .
| AM                     |     3:1 |    3 | Addressing mode. The permitted values of this field are:
| FSC                    |     5:1 |    5 | Indicates why the Profiling exception was generated.
| CRm                    |     4:1 |    4 | The CRm value from the issued instruction.
| DZF                    |     1:1 |    1 | Divide by Zero floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| DnI                    |     1:1 |    1 | This field indicates whether the exception is as a result of an Instruction key or a Data key.
| Xs                     |     4:0 |    5 | When FEAT_LS64_V is implemented, if a memory access generated by an ST64BV instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. When FEAT_LS64_ACCDATA is implemented, if a memory access generated by an ST64BV0 instruction generates a Data Abort exception for a Translation fault, Access flag fault, or Permission fault, then this field holds register specifier, Xs. Otherwise, this field is RES0 .
| ISS                    |    24:0 |   25 | Instruction Specific Syndrome. Architecturally, this field can be defined independently for each defined Exception class. However, in practice, some ISS encodings are used for more than one Exception class. Typically, an ISS encoding has a number of subfields. When an ISS subfield holds a register number, the value returned in that field is the AArch64 view of the register number. For an exception taken from AArch32 state, see 'Mapping of the general-purpose registers between the Execution states' . If the AArch32 register descriptor is 0b1111 , then: If the instruction that generated the exception was not UNPREDICTABLE , the field takes the value 0b11111 . If the instruction that generated the exception was UNPREDICTABLE , the field takes an UNKNOWN value that must be either: The AArch64 view of the register number of a register that might have been used at the Exception level from which the exception was taken. The value 0b11111 .
| TI                     |     1:0 |    2 | Trapped instruction. Possible values of this bit are:
| Direction              |     0:0 |    1 | Indicates the direction of the trapped instruction.
| ISS                    |    24:0 |   25 |
| Direction              |     0:0 |    1 | Indicates the direction of the trapped instruction.
| SYNC                   |     0:0 |    1 | Indicates whether the Profiling exception was taken synchronously or asynchronously.
| sizereg                |     4:0 |    5 | The size register value from the issued instruction, containing the number of bytes to be transfered or set.
| imm16                  |    15:0 |   16 | The value of the immediate field from the HVC or SVC instruction. For an HVC instruction, and for an A64 SVC instruction, this is the value of the imm16 field of the issued instruction. For an A32 or T32 SVC instruction: If the instruction is unconditional, then: For the T32 instruction, this field is zero-extended from the imm8 field of the instruction. For the A32 instruction, this field is the bottom 16 bits of the imm24 field of the instruction. If the instruction is conditional, this field is UNKNOWN .
| Direction              |     0:0 |    1 | Indicates the direction of the trapped instruction.
| IMPLEMENTATION DEFINED |    24:0 |   25 | IMPLEMENTATION DEFINED .
| IFSC                   |     5:0 |    6 | Instruction Fault Status Code.
| SMTC                   |     2:0 |    3 | SME Trap Code. Identifies the reason for instruction trapping.
| xFSC                   |     5:0 |    6 | Instruction or Data Fault Status Code.
| DFSC                   |     5:0 |    6 | Data Fault Status Code.
| IOF                    |     0:0 |    1 | Invalid Operation floating-point exception trapped bit. If the TFV field is 0, this bit is UNKNOWN . Otherwise, the possible values of this bit are:
| IT                     |     4:0 |    5 | Type of the instruction that caused the Guarded Control Stack Data Check Exception.
| DFSC                   |     5:0 |    6 | Data Fault Status Code.
| Comment                |    15:0 |   16 | Set to the instruction comment field value, zero extended as necessary. For the AArch32 BKPT instructions, the comment field is described as the immediate field.
| BTYPE                  |     1:0 |    2 | This field is set to the PSTATE.BTYPE value that generated the Branch Target Exception.
| BnA                    |     0:0 |    1 | This field indicates whether the exception is as a result of an A key or a B key.

## FGWTE3_EL3 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| GPCBW_EL3      |   22:22 |    1 | Traps accesses of GPCBW_EL3 to EL3.
| VBAR_EL3       |   21:21 |    1 | Traps accesses of VBAR_EL3 to EL3.
| TTBR0_EL3      |   20:20 |    1 | Traps accesses of TTBR0_EL3 to EL3.
| TPIDR_EL3      |   19:19 |    1 | Traps accesses of TPIDR_EL3 to EL3.
| TCR_EL3        |   18:18 |    1 | Traps accesses of TCR_EL3 to EL3.
| SPMROOTCR_EL3  |   17:17 |    1 | Traps accesses of SPMROOTCR_EL3 to EL3.
| SCTLR2_EL3     |   16:16 |    1 | Traps accesses of SCTLR2_EL3 to EL3.
| SCTLR_EL3      |   15:15 |    1 | Traps accesses of SCTLR_EL3 to EL3.
| PIR_EL3        |   14:14 |    1 | Traps accesses of PIR_EL3 to EL3.
| MPAM3_EL3      |   13:13 |    1 | Traps accesses of MPAM3_EL3 to EL3.
| MECID_RL_A_EL3 |   12:12 |    1 | Traps accesses of MECID_RL_A_EL3 to EL3.
| MDCR_EL3       |   11:11 |    1 | Traps accesses of MDCR_EL3 to EL3.
| MAIR2_EL3      |   10:10 |    1 | Traps accesses of MAIR2_EL3 to EL3.
| MAIR_EL3       |     9:9 |    1 | Traps accesses of MAIR_EL3 to EL3.
| GPTBR_EL3      |     8:8 |    1 | Traps accesses of GPTBR_EL3 to EL3.
| GPCCR_EL3      |     7:7 |    1 | Traps accesses of GPCCR_EL3 to EL3.
| GCSPR_EL3      |     6:6 |    1 | Traps accesses of GCSPR_EL3 to EL3.
| GCSCR_EL3      |     5:5 |    1 | Traps accesses of GCSCR_EL3 to EL3.
| AMAIR2_EL3     |     4:4 |    1 | Traps accesses of AMAIR2_EL3 to EL3.
| AMAIR_EL3      |     3:3 |    1 | Traps accesses of AMAIR_EL3 to EL3.
| AFSR1_EL3      |     2:2 |    1 | Traps accesses of AFSR1_EL3 to EL3.
| AFSR0_EL3      |     1:1 |    1 | Traps accesses of AFSR0_EL3 to EL3.
| ACTLR_EL3      |     0:0 |    1 | Traps accesses of ACTLR_EL3 to EL3.

## FPCR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| AHP      |   26:26 |    1 | Alternative half-precision control bit.
| DN       |   25:25 |    1 | Default NaN use for NaN propagation.
| FZ       |   24:24 |    1 | Flushing denormalized numbers to zero control bit.
| RMode    |   23:22 |    2 | Rounding Mode control field.
| Stride   |   21:20 |    2 | This field has no function in AArch64 state, and nonzero values are ignored during execution in AArch64 state. This field is included only for context saving and restoration of the AArch32 FPSCR .Stride field.
| FZ16     |   19:19 |    1 | Flushing denormalized numbers to zero control bit on half-precision data-processing instructions.
| Len      |   18:16 |    3 | This field has no function in AArch64 state, and nonzero values are ignored during execution in AArch64 state. This field is included only for context saving and restoration of the AArch32 FPSCR .Len field.
| IDE      |   15:15 |    1 | Input Denormal floating-point exception trap enable.
| EBF      |   13:13 |    1 | The value of this bit controls the numeric behaviors of BFloat16 dot product calculations performed by the BFDOT, BFMMLA, BFMOPA, and BFMOPS instructions. If FEAT_SME2 is implemented, this also controls BFVDOT instruction. When ID_AA64ISAR1_EL1 .BF16 and ID_AA64ZFR0_EL1 .BF16 are 0b0010 , the PE supports the FPCR.EBF field. Otherwise, FPCR.EBF is RES0 .
| IXE      |   12:12 |    1 | Inexact floating-point exception trap enable.
| UFE      |   11:11 |    1 | Underflow floating-point exception trap enable.
| OFE      |   10:10 |    1 | Overflow floating-point exception trap enable.
| DZE      |     9:9 |    1 | Divide by Zero floating-point exception trap enable.
| IOE      |     8:8 |    1 | Invalid Operation floating-point exception trap enable.
| NEP      |     2:2 |    1 | Controls how the output elements other than the lowest element of the vector are determined for Advanced SIMD scalar instructions.
| AH       |     1:1 |    1 | Alternate Handling. Controls alternate handling of floating-point numbers.
| FIZ      |     0:0 |    1 | Flush Inputs to Zero. Controls whether single-precision, double-precision and BFloat16 input operands that are denormalized numbers are flushed to zero.

## FPEXC32_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EX       |   31:31 |    1 | Exception bit.
| EN       |   30:30 |    1 | Enables access to the Advanced SIMD and floating-point functionality from all Exception levels, except that setting this field to 0 does not disable the following: VMSR accesses to the FPEXC or FPSID . VMRS accesses from the FPEXC , FPSID , MVFR0 , MVFR1 , or MVFR2 .
| DEX      |   29:29 |    1 | Defined synchronous exception on floating-point execution. This field identifies whether a synchronous exception generated by the attempted execution of an instruction was generated by an unallocated encoding. The instruction must be in the encoding space that is identified by the pseudocode function ExecutingCP10or11Instr() returning TRUE. This field also indicates whether the FPEXC32_EL2.TFV field is valid. The meaning of this bit is:
| FP2V     |   28:28 |    1 | FPINST2 instruction Valid bit. From Armv8.0, this bit is RES0 .
| VV       |   27:27 |    1 | VECITR valid bit. From Armv8, this bit is RES0 .
| TFV      |   26:26 |    1 | Trapped Fault Valid bit. Valid only when the value of FPEXC32_EL2.DEX is 1. When valid, it indicates the cause of the exception and therefore whether FPEXC32_EL2.{IDF, IXF, UFF, OFF, DZF, IOF} are valid.
| VECITR   |    10:8 |    3 | Vector iteration count. From Armv8, this field is RES1 .
| IDF      |     7:7 |    1 | Input Denormal trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether an Input Denormal exception occurred while FPSCR .IDE was 1:
| IXF      |     4:4 |    1 | Inexact trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether an Inexact exception occurred while FPSCR .IXE was 1:
| UFF      |     3:3 |    1 | Underflow trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether an Underflow exception occurred while FPSCR .UFE was 1:
| OFF      |     2:2 |    1 | Overflow trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether an Overflow exception occurred while FPSCR .OFE was 1:
| DZF      |     1:1 |    1 | Divide by Zero trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether a Divide by Zero exception occurred while FPSCR .DZE was 1:
| IOF      |     0:0 |    1 | Invalid Operation trapped exception bit. Valid only when the value of FPEXC .TFV is 1. When valid, it indicates whether an Invalid Operation exception occurred while FPSCR .IOE was 1:

## FPMR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LSCALE2  |   37:32 |    6 | Downscaling value for instructions that convert the second FP8 input data stream to other floating-point formats. This value is an unsigned integer that is subtracted from the result exponent.
| NSCALE   |   31:24 |    8 | Scaling value for instructions that convert other floating-point formats to an FP8 format. This value is a signed integer that is added to the operand exponent.
| LSCALE   |   22:16 |    7 | Downscaling value. This value is an unsigned integer that is subtracted from: The product or the sum-of-products exponent, for multiplication instructions with FP8 operands. The result exponent, for instructions that convert the first FP8 input data stream to other floating-point formats.
| OSC      |   15:15 |    1 | Overflow saturation for FP8 convert instructions. Specifies the result when a floating-point Overflow exception is detected.
| OSM      |   14:14 |    1 | Overflow saturation for FP8 multiplication instructions. Specifies the result when a floating-point Overflow exception is detected.
| F8D      |     8:6 |    3 | Destination result format for instructions that convert other floating-point values to an FP8 format.
| F8S2     |     5:3 |    3 | Second FP8 input data stream format for multiplication instructions with FP8 operands, and the corresponding instructions that convert an FP8 format to other floating-point formats.
| F8S1     |     2:0 |    3 | First FP8 input data stream format for multiplication instructions with FP8 operands, and the corresponding instructions that convert an FP8 format to other floating-point formats.

## FPSR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| N        |   31:31 |    1 | Negative condition flag for AArch32 floating-point comparison operations. AArch64 floating-point comparisons set the PSTATE.N flag instead.
| Z        |   30:30 |    1 | Zero condition flag for AArch32 floating-point comparison operations. AArch64 floating-point comparisons set the PSTATE.Z flag instead.
| C        |   29:29 |    1 | Carry condition flag for AArch32 floating-point comparison operations. AArch64 floating-point comparisons set the PSTATE.C flag instead.
| V        |   28:28 |    1 | Overflow condition flag for AArch32 floating-point comparison operations. AArch64 floating-point comparisons set the PSTATE.V flag instead.
| QC       |   27:27 |    1 | Cumulative saturation bit, Advanced SIMD only. This bit is set to 1 to indicate that an Advanced SIMD integer operation has saturated since 0 was last written to this bit.
| IDC      |     7:7 |    1 | Input Denormal cumulative floating-point exception bit. This bit is set to 1 to indicate that the Input Denormal floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .IDE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .IDE is 0.
| IXC      |     4:4 |    1 | Inexact cumulative floating-point exception bit. This bit is set to 1 to indicate that the Inexact floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .IXE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .IXE is 0. The criteria for the Inexact floating-point exception to occur are affected by whether denormalized numbers are flushed to zero and by the value of the FPCR .AH bit. For more information, see 'Floating-point exceptions and exception traps' .
| UFC      |     3:3 |    1 | Underflow cumulative floating-point exception bit. This bit is set to 1 to indicate that the Underflow floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .UFE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .UFE is 0 or if flushing denormalized numbers to zero is enabled. The criteria for the Underflow floating-point exception to occur are affected by whether denormalized numbers are flushed to zero and by the value of the FPCR .AH bit. For more information, see 'Floating-point exceptions and exception traps' .
| OFC      |     2:2 |    1 | Overflow cumulative floating-point exception bit. This bit is set to 1 to indicate that the Overflow floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .OFE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .OFE is 0.
| DZC      |     1:1 |    1 | Divide by Zero cumulative floating-point exception bit. This bit is set to 1 to indicate that the Divide by Zero floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .DZE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .DZE is 0.
| IOC      |     0:0 |    1 | Invalid Operation cumulative floating-point exception bit. This bit is set to 1 to indicate that the Invalid Operation floating-point exception has occurred since 0 was last written to this bit. How scalar and Advanced SIMD floating-point instructions update this bit depends on the value of the FPCR .IOE bit. This bit is set to 1 to indicate a floating-point exception only if FPCR .IOE is 0. The criteria for the Invalid Operation floating-point exception to occur are affected by the value of the FPCR .AH bit. For more information, see 'Floating-point exceptions and exception traps' .

## GCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RRND     |   16:16 |    1 | Controls generation of tag values by the IRG instruction.
| Exclude  |    15:0 |   16 | Allocation Tag values excluded from selection by ChooseNonExcludedTag(). If all bits of GCR_EL1.Exclude are 1, then the Allocation Tag value 0 will be used.

## GCSCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| STREn    |     9:9 |    1 | Execution of the following instructions are trapped: GCSSTR. GCSSTTR if any of the following are true. PSTATE . UAO is 1. If EL2 is implemented and enabled in the current Security state and the Effective value of HCR_EL2 .{NV,NV1} is {1,1}.
| PUSHMEn  |     8:8 |    1 | Trap GCSPUSHM instruction.
| EXLOCKEN |     6:6 |    1 | Exception state lock. Prevents MSR instructions from writing to ELR_EL1 or SPSR_EL1 .
| RVCHKEN  |     5:5 |    1 | Return value check enable.
| PCRSEL   |     0:0 |    1 | Guarded Control Stack procedure call return enable selection.

## GCSCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| STREn    |     9:9 |    1 | Execution of the following instructions are trapped: GCSSTR. GCSSTTR if any of the following are true. The Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}. The Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, and PSTATE . UAO is 1.
| PUSHMEn  |     8:8 |    1 | Trap GCSPUSHM instruction.
| EXLOCKEN |     6:6 |    1 | Exception state lock. Prevents MSR instructions from writing to ELR_EL2 or SPSR_EL2 .
| RVCHKEN  |     5:5 |    1 | Return value check enable.
| PCRSEL   |     0:0 |    1 | Guarded Control Stack procedure call return enable selection.

## GCSCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| STREn    |     9:9 |    1 | Execution of the following instructions are trapped: GCSSTR. GCSSTTR.
| PUSHMEn  |     8:8 |    1 | Trap GCSPUSHM instruction.
| EXLOCKEN |     6:6 |    1 | Exception state lock. Prevents MSR instructions from writing to ELR_EL3 or SPSR_EL3 .
| RVCHKEN  |     5:5 |    1 | Return value check enable.
| PCRSEL   |     0:0 |    1 | Guarded Control Stack procedure call return enable selection.

## GCSCRE0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| nTR      |   10:10 |    1 | Trap GCS register accesses from EL0.
| STREn    |     9:9 |    1 | Execution of the following instructions are trapped: GCSSTR. GCSSTTR.
| PUSHMEn  |     8:8 |    1 | Trap GCSPUSHM instruction.
| RVCHKEN  |     5:5 |    1 | Return value check enable.
| PCRSEL   |     0:0 |    1 | Guarded Control Stack procedure call return enable selection.

## GCSPR_EL0 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| PTR[63:3] |    63:3 |   61 | EL0 Guarded Control Stack Pointer bits [63:3].

## GCSPR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| PTR[63:3] |    63:3 |   61 | EL1 Guarded Control Stack Pointer bits [63:3].

## GCSPR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| PTR[63:3] |    63:3 |   61 | EL2 Guarded Control Stack Pointer bits [63:3].

## GCSPR_EL3 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| PTR[63:3] |    63:3 |   61 | EL3 Guarded Control Stack Pointer bits [63:3].

## GMID_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BS       |     3:0 |    4 | Log 2 of the block size in words. The minimum supported size is 16B (value == 2) and the maximum is 256B (value == 6).

## GPCBW_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BWSIZE   |   39:37 |    3 | GPC Bypass Window Size. BWSIZE defines the size of the GPC bypass memory region.
| BWSTRIDE |   36:32 |    5 | GPC Bypass Window Stride. BWSTRIDE allows creating multiple GPC bypass memory regions in the memory map across a specific stride.
| BWADDR   |    25:0 |   26 | GPC Bypass window address. This field represents bits [55:30] of the GPC bypass window base address. The GPC bypass window is: Aligned in memory to the size of the window as specified by GPCBW_EL3.BWSIZE. Duplicated in PA space across a stride specified using GPCBW_EL3.BWSTRIDE. This means that only bits [gpcbwu:gpcbwl] of a PA are compared against bits [gpcbwu:gpcbwl] of the window base address derived from BWADDR when checking if a PA falls within the range of a window, where: gpcbwl is derived from GPCBW_EL3.BWSIZE as follows: BWSIZE gpcbwl 0b000 30 0b001 31 0b010 32 0b100 34 0b110 36 gpcbwu is derived from GPCBW_EL3.BWSTRIDE as follows: BWSTRIDE gpcbwu 0b00000 39 0b00010 41 0b00100 43 0b00110 45 0b00111 46 0b01000 47 0b01001 48 0b01010 49 0b10000 55 If the base address derived from BWADDR is not aligned to the size programmed in BWSIZE the configuration is invalid. An access to a PA falls within a GPC bypass window if the pseudocode function PAWithinGPCBypassWindow() returns TRUE.

## GPCCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| GPCBW    |   29:29 |    1 | GPC Bypass Window Enable. This field governs the behavior of the GPC bypass windows.
| NA7      |   28:28 |    1 | No access 7. This field governs the behavior of the GPI encoding for NA7.
| NA6      |   27:27 |    1 | No access 6. This field governs the behavior of the GPI encoding for NA6.
| NSP      |   26:26 |    1 | Non-secure Protected. This field governs the behavior of the GPI encoding for NSP.
| SA       |   25:25 |    1 | System Agent. This field governs the behavior of the GPI encoding for SA.
| APPSAA   |   24:24 |    1 | Above PPS All Access. This field governs the behavior of memory accesses to Secure, Realm and Root PA space, for physical addresses above the range configured by GPCCR_EL3.PPS.
| L0GPTSZ  |   23:20 |    4 | Level 0 GPT entry size. This field advertises the number of least-significant address bits protected by each entry in the level 0 GPT.
| NSO      |   19:19 |    1 | Non-secure Only. This field governs the behavior of the GPI encoding for NSO.
| TBGPCD   |   18:18 |    1 | Trace Buffer Granule Protection Check Disabled. Controls whether the Trace Buffer Unit accepts or rejects trace when Granule Protection Checks are disabled.
| GPCP     |   17:17 |    1 | Granule Protection Check Priority. This control governs behavior of granule protection checks on fetches of stage 2 Table descriptors.
| GPC      |   16:16 |    1 | Granule Protection Check Enable.
| PGS      |   15:14 |    2 | Physical Granule size.
| SH       |   13:12 |    2 | GPT fetch Shareability attribute
| ORGN     |   11:10 |    2 | GPT fetch Outer cacheability attribute.
| IRGN     |     9:8 |    2 | GPT fetch Inner cacheability attribute.
| SPAD     |     7:7 |    1 | Secure PA space Disable. This field controls access to the Secure PA space.
| NSPAD    |     6:6 |    1 | Non-secure PA space Disable. This field controls access to the Non-secure PA space.
| RLPAD    |     5:5 |    1 | Realm PA space Disable. This field controls access to the Realm PA space.
| PPS3     |     3:3 |    1 | This field extends GPCCR_EL3.PPS[2:0], creating a GPCCR_EL3.PPS[3:0] field. For a description of the values derived by evaluating PPS, see GPCCR_EL3.PPS[2:0]. The value of this field is permitted to be cached in a TLB.
| PPS      |     2:0 |    3 | Protected Physical Address Size. The size of the memory region protected by GPTBR_EL3 , in terms of the number of least-significant address bits. This field is evaluated with PPS3, as {PPS3, PPS} to give PPS[3:0], interpreted as: PPS[3:0] Meaning 0b0000 32 bits, 4GB protected address space. 0b0001 36 bits, 64GB protected address space. 0b0010 40 bits, 1TB protected address space. 0b0011 42 bits, 4TB protected address space. 0b0100 44 bits, 16TB protected address space. 0b1000 46 bits, 64TB protected address space. 0b1001 47 bits, 128TB protected address space. 0b0101 48 bits, 256TB protected address space. 0b0110 52 bits, 4PB protected address space. 0b0111 56 bits, 64PB protected address space.

## GPTBR_EL3 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| BADDR[43:40] |   43:40 |    4 | Extension to BADDR[39:0]. This field represents bit [55:52] of the level 0 GPT base address.
| BADDR        |    39:0 |   40 | Base address for the level 0 GPT. This field represents bits [51:12] of the level 0 GPT base address.

## HACDBSBR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BADDR    |   55:12 |   44 | HACDBS base address, bits [55:12]. Bits [55:12] of the base address are the value of this field. Bits [11:0] of the base address are 0. Bits of this field above the implemented physical address size, indicated in ID_AA64MMFR0_EL1 .PARange, are RES0 . Based on the value of the SZ field of this register, for encodings of the SZ field greater than 4KB, bits [(SZ+12-1):12] of this field are RES0 such that the base address of the HACDBS is aligned to its size.
| EN       |   11:11 |    1 | Enable use of HACDBS.
| SZ       |     3:0 |    4 | Size of the HACDBS.

## HACDBSCONS_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| ERR_REASON |   63:62 |    2 | Reason for HACDBS error.
| INDEX      |    18:0 |   19 | This field indicates the index of the HACDBS entry that will be read from next.

## HAFGRTR_EL2 bitfields

| Bitfield          | msb:lsb | Size | Description
| ----------------- | ------: | ---: | -----------
| AMEVTYPER1<x>_EL0 |   49:49 |    1 | Trap MRS reads of AMEVTYPER1<x>_EL0 at EL1 and EL0 using AArch64 and MRC reads of AMEVTYPER1<x> at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| AMEVCNTR1<x>_EL0  |   48:48 |    1 | Trap MRS reads of AMEVCNTR1<x>_EL0 at EL1 and EL0 using AArch64 and MRC reads of AMEVCNTR1<x> at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| AMCNTEN<x>        |   17:17 |    1 | Trap MRS reads and MRC reads of multiple System registers. Enables a trap to EL2 the following operations: At EL1 and EL0 using AArch64: MRS reads of AMCNTENCLR<x>_EL0 and AMCNTENSET<x>_EL0. At EL0 using AArch32 when EL1 is using AArch64: MRC reads of AMCNTENCLR<x> and AMCNTENSET<x>.
| AMCNTEN1          |   17:17 |    1 | Trap MRS reads and MRC reads of multiple System registers. Enables a trap to EL2 the following operations: At EL1 and EL0 using AArch64: MRS reads of AMCNTENCLR1_EL0 and AMCNTENSET1_EL0. At EL0 using AArch32 when EL1 is using AArch64: MRC reads of AMCNTENCLR1 and AMCNTENSET1.
| AMEVCNTR0<x>_EL0  |     4:1 |    4 | Trap MRS reads of AMEVCNTR0<x>_EL0 at EL1 and EL0 using AArch64 and MRC reads of AMEVCNTR0<x> at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| AMCNTEN0          |     0:0 |    1 | Trap MRS reads and MRC reads of multiple System registers. Enables a trap to EL2 the following operations: At EL1 and EL0 using AArch64: MRS reads of AMCNTENCLR0_EL0 and AMCNTENSET0_EL0. At EL0 using AArch32 when EL1 is using AArch64: MRC reads of AMCNTENCLR0 and AMCNTENSET0.

## HCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TWEDEL   |   63:60 |    4 | TWE Delay. A 4-bit unsigned number that, when HCR_EL2.TWEDEn is 1, encodes the minimum delay in taking a trap of WFE* caused by HCR_EL2.TWE as 2 (TWEDEL + 8) cycles.
| TWEDEn   |   59:59 |    1 | TWE Delay Enable. Enables a configurable delayed trap of the WFE* instruction caused by HCR_EL2.TWE.
| TID5     |   58:58 |    1 | Trap ID group 5. Traps the following register accesses to EL2, when EL2 is enabled in the current Security state: AArch64: GMID_EL1 .
| DCT      |   57:57 |    1 | Default Cacheability Tagging. When HCR_EL2.DC is in effect, controls whether EL1&0 stage 1 translations have the Tagged attribute.
| ATA      |   56:56 |    1 | Allocation Tag Access. Controls access to Allocation Tags, System registers for Memory tagging, and prevention of Tag checking, at EL1 and EL0
| TTLBOS   |   55:55 |    1 | Trap TLB maintenance instructions that operate on the Outer Shareable domain. Traps execution of those TLB maintenance instructions at EL1 using AArch64 to EL2, when EL2 is enabled in the current Security state. The following instructions are trapped and reported with EC syndrome value 0x18 : TLBI VMALLE1OS , TLBI VAE1OS , TLBI ASIDE1OS , TLBI VAAE1OS , TLBI VALE1OS , and TLBI VAALE1OS . If FEAT_TLBIRANGE is implemented, TLBI RVAE1OS , TLBI RVAAE1OS , TLBI RVALE1OS , and TLBI RVAALE1OS . If FEAT_XS is implemented then the *OSNXS variants are also trapped.
| TTLBIS   |   54:54 |    1 | Trap TLB maintenance instructions that operate on the Inner Shareable domain. Traps execution of those TLB maintenance instructions at EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, then the following instructions are trapped to EL2 and reported with EC syndrome value 0x18 : TLBI VMALLE1IS , TLBI VAE1IS , TLBI ASIDE1IS , TLBI VAAE1IS , TLBI VALE1IS , TLBI VAALE1IS , TLBI RVAE1IS , TLBI RVAAE1IS , TLBI RVALE1IS , and TLBI RVAALE1IS . If EL1 is using AArch32, then the following instructions are trapped to EL2 and reported with EC syndrome value 0x03 : TLBIALLIS , TLBIMVAIS , TLBIASIDIS , TLBIMVAAIS , TLBIMVALIS , and TLBIMVAALIS . If FEAT_XS is implemented then the *ISNXS variants are also trapped.
| EnSCXT   |   53:53 |    1 | Enable Access to the SCXTNUM_EL1 and SCXTNUM_EL0 registers. The defined values are:
| TOCU     |   52:52 |    1 | Trap cache maintenance instructions that operate to the Point of Unification. Traps execution of those cache maintenance instructions at EL0 and EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL0 is using AArch64, the value of SCTLR_EL1 .UCI is 1, and the Effective value of HCR_EL2.{E2H, TGE} is not {1, 1}, then the following instructions at EL0 are trapped to EL2 and reported with EC syndrome value 0x18 : IC IVAU , and DC CVAU . If EL1 is using AArch64, then the following instructions at EL1 are trapped to EL2 and reported with EC syndrome value 0x18 : IC IVAU , IC IALLU , and DC CVAU . If EL1 is using AArch32, then the following instructions are trapped at EL1 to EL2 and reported with EC syndrome value 0x03 : ICIMVAU , ICIALLU , and DCCMVAU . When SCTLR_EL1 .UCI is 0, the trap on execution of instructions at EL0 is higher priority than this control. An exception generated because an instruction is UNDEFINED at EL0 is higher priority than this trap to EL2. In addition: IC IALLUIS and IC IALLU are always UNDEFINED at EL0 using AArch64. ICIMVAU , ICIALLU , ICIALLUIS , and DCCMVAU are always UNDEFINED at EL0 using AArch32.
| AMVOFFEN |   51:51 |    1 | Activity Monitors Virtual Offsets Enable.
| TICAB    |   50:50 |    1 | Trap ICIALLUIS and IC IALLUIS cache maintenance instructions. Traps execution of those cache maintenance instructions at EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, then the following instruction is trapped to EL2 and reported with EC syndrome value 0x18 : IC IALLUIS . If EL1 is using AArch32, then the following instruction is trapped to EL2 and reported with EC syndrome value 0x03 : ICIALLUIS .
| TID4     |   49:49 |    1 | Trap ID group 4. Traps the following register accesses to EL2, when EL2 is enabled in the current Security state: AArch64: EL1 reads of CCSIDR_EL1 , CCSIDR2_EL1 , CLIDR_EL1 , and CSSELR_EL1 . EL1 writes to CSSELR_EL1 . AArch32: EL1 reads of CCSIDR , CCSIDR2 , CLIDR , and CSSELR . EL1 writes to CSSELR .
| GPF      |   48:48 |    1 | Controls the reporting of Granule protection faults at EL0 and EL1.
| FIEN     |   47:47 |    1 | Fault Injection Enable. Unless this bit is set to 1, accesses to the ERXPFGCDN_EL1 , ERXPFGCTL_EL1 , and ERXPFGF_EL1 registers from EL1 generate a Trap exception to EL2, when EL2 is enabled in the current Security state, reported using EC syndrome value 0x18 .
| FWB      |   46:46 |    1 | Forced Write-Back. Defines the combined cacheability attributes in a 2 stage translation regime.
| NV2      |   45:45 |    1 | Nested Virtualization. Changes the behaviors of HCR_EL2.{NV1, NV} to provide a mechanism for hardware to transform reads and writes from System registers into reads and writes from memory.
| AT       |   44:44 |    1 | Address Translation. EL1 execution of the following address translation instructions is trapped to EL2, when EL2 is enabled in the current Security state, reported using EC syndrome value 0x18 : AT S1E0R , AT S1E0W , AT S1E1R , AT S1E1W , AT S1E1RP , and AT S1E1WP . If FEAT_ATS1A is implemented, AT S1E1A .
| NV1      |   43:43 |    1 | Nested Virtualization.
| NV       |   42:42 |    1 | Nested Virtualization. When the Effective value of HCR_EL2.NV2 is 1, redefines register accesses so that: Instructions accessing the Special purpose registers SPSR_EL2 and ELR_EL2 instead access SPSR_EL1 and ELR_EL1 respectively. Instructions accessing the System registers ESR_EL2 and FAR_EL2 instead access ESR_EL1 and FAR_EL1 . When the Effective value of HCR_EL2.NV2 is 0, traps functionality that is permitted at EL2 and would be UNDEFINED at EL1 if this field was 0, when EL2 is enabled in the current Security state. This applies to the following operations: EL1 accesses to Special-purpose registers that are not UNDEFINED at EL2. EL1 accesses to System registers that are not UNDEFINED at EL2. Execution of EL1 or EL2 translation regime address translation and TLB maintenance instructions for EL2 and above.
| API      |   41:41 |    1 | Controls the use of instructions related to Pointer Authentication: PACGA. AUTDA, AUTDB, AUTDZA, AUTDZB, AUTIA, AUTIA1716, AUTIASP, AUTIAZ, AUTIB, AUTIB1716, AUTIBSP, AUTIBZ, AUTIZA, AUTIZB. PACDA, PACDB, PACDZA, PACDZB, PACIA, PACIA1716, PACIASP, PACIAZ, PACIB, PACIB1716, PACIBSP, PACIBZ, PACIZA, PACIZB. RETAA, RETAB, BRAA, BRAB, BLRAA, BLRAB, BRAAZ, BRABZ, BLRAAZ, BLRABZ. ERETAA, ERETAB, LDRAA, and LDRAB. When FEAT_PAuth_LR is implemented, AUTIASPPC, AUTIASPPCR, AUTIA171615, AUTIBSPPC, AUTIBSPPCR, AUTIB171615, PACIASPPC, PACNBIASPPC, PACIA171615, PACIBSPPC, PACNBIBSPPC, PACIB171615, RETAASPPC, RETAASPPCR, RETABSPPC, RETABSPPCR. This field is ignored if the instruction is disabled as a result of the SCTLR_ELx.{EnIB, EnIA, EnDA, EnDB} fields.
| APK      |   40:40 |    1 | Trap registers holding "key" values for Pointer Authentication. Traps accesses to the following registers from EL1 to EL2, when EL2 is enabled in the current Security state, reported using EC syndrome value 0x18 : APIAKeyLo_EL1 , APIAKeyHi_EL1 , APIBKeyLo_EL1 , APIBKeyHi_EL1 , APDAKeyLo_EL1 , APDAKeyHi_EL1 , APDBKeyLo_EL1 , APDBKeyHi_EL1 , APGAKeyLo_EL1 , and APGAKeyHi_EL1 .
| TME      |   39:39 |    1 | Enables access to the TSTART, TCOMMIT, TTEST, and TCANCEL instructions at EL0 and EL1.
| MIOCNCE  |   38:38 |    1 | Mismatched Inner/Outer Cacheable Non-Coherency Enable, for the EL1&0 translation regimes.
| TEA      |   37:37 |    1 | Route synchronous External abort exceptions to EL2.
| TERR     |   36:36 |    1 | Trap accesses of Error Record registers. Enables a trap to EL2 on accesses of Error Record registers.
| TLOR     |   35:35 |    1 | Trap LOR registers. Traps Non-secure EL1 accesses to LORSA_EL1 , LOREA_EL1 , LORN_EL1 , LORC_EL1 , and LORID_EL1 registers to EL2.
| E2H      |   34:34 |    1 | EL2 Host. Enables a configuration where a Host Operating System is running in EL2, and the Host Operating System's applications are running in EL0.
| ID       |   33:33 |    1 | Stage 2 Instruction access cacheability disable. For the EL1&0 translation regime, when EL2 is enabled in the current Security state and HCR_EL2.VM==1, this control forces all stage 2 translations for instruction accesses to Normal memory to be Non-cacheable.
| CD       |   32:32 |    1 | Stage 2 Data access cacheability disable. For the EL1&0 translation regime, when EL2 is enabled in the current Security state and HCR_EL2.VM==1, this control forces all stage 2 translations for data accesses and translation table walks to Normal memory to be Non-cacheable.
| RW       |   31:31 |    1 | Execution state control for lower Exception levels:
| TRVM     |   30:30 |    1 | Trap Reads of Virtual Memory controls. Traps reads of the virtual memory control registers to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, EL1 accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x18 for MRS and 0x14 for MRRS : SCTLR_EL1 , TTBR0_EL1 , TTBR1_EL1 , TCR_EL1 , ESR_EL1 , FAR_EL1 , AFSR0_EL1 , AFSR1_EL1 , MAIR_EL1 , AMAIR_EL1 , and CONTEXTIDR_EL1 . If FEAT_AIE is implemented, MAIR2_EL1 and AMAIR2_EL1 . If FEAT_S1PIE is implemented, PIRE0_EL1 and PIR_EL1 . If FEAT_S1POE is implemented, POR_EL0 and POR_EL1 . If FEAT_S2POE is implemented, S2POR_EL1 . If FEAT_TCR2 is implemented, TCR2_EL1 . If FEAT_SCTLR2 is implemented, SCTLR2_EL1 . If the Effective value of HCR_EL2.{E2H, TGE} is not {1, 1}, and EL0 is using AArch64, EL0 accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x18 for MRS : If FEAT_S1POE is implemented, POR_EL0 . If EL1 is using AArch32, EL1 accesses using MRC to the following registers are trapped to EL2 and reported using EC syndrome value 0x03 , accesses using MRRC are trapped to EL2 and reported using EC syndrome value 0x04 : SCTLR , TTBR0 , TTBR1 , TTBCR , TTBCR2 , DACR , DFSR , IFSR , DFAR , IFAR , ADFSR , AIFSR , PRRR , NMRR , MAIR0 , MAIR1 , AMAIR0 , AMAIR1 , and CONTEXTIDR .
| HCD      |   29:29 |    1 | HVC instruction disable. Disables EL1 execution of HVC instructions, from both Execution states, when EL2 is enabled in the current Security state, reported using EC syndrome value 0x00 .
| TDZ      |   28:28 |    1 | Trap DC ZVA instructions. Traps EL0 and EL1 execution of DC ZVA instructions to EL2, when EL2 is enabled in the current Security state, from AArch64 state only, reported using EC syndrome value 0x18 . If FEAT_MTE is implemented, this trap also applies to DC GVA and DC GZVA .
| TGE      |   27:27 |    1 | Trap General Exceptions, from EL0.
| TVM      |   26:26 |    1 | Trap Virtual Memory controls. Traps writes to the virtual memory control registers to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, the following registers are trapped to EL2 and reported using EC syndrome value 0x18 for MSR and 0x14 for MSRR : SCTLR_EL1 , TTBR0_EL1 , TTBR1_EL1 , TCR_EL1 , ESR_EL1 , FAR_EL1 , AFSR0_EL1 , AFSR1_EL1 , MAIR_EL1 , AMAIR_EL1 , and CONTEXTIDR_EL1 . If FEAT_AIE is implemented, MAIR2_EL1 and AMAIR2_EL1 . If FEAT_S1PIE is implemented, PIRE0_EL1 and PIR_EL1 . If FEAT_S1POE is implemented, POR_EL0 and POR_EL1 . If FEAT_S2POE is implemented, S2POR_EL1 . If FEAT_TCR2 is implemented, TCR2_EL1 . If FEAT_SCTLR2 is implemented, SCTLR2_EL1 . If the Effective value of HCR_EL2.{E2H, TGE} is not {1, 1}, and EL0 is using AArch64, EL0 accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x18 for MSR : If FEAT_S1POE is implemented, POR_EL0 . If EL1 is using AArch32, EL1 accesses using MCR to the following registers are trapped to EL2 and reported using EC syndrome value 0x03 , accesses using MCRR are trapped to EL2 and reported using EC syndrome value 0x04 : SCTLR , TTBR0 , TTBR1 , TTBCR , TTBCR2 , DACR , DFSR , IFSR , DFAR , IFAR , ADFSR , AIFSR , PRRR , NMRR , MAIR0 , MAIR1 , AMAIR0 , AMAIR1 , and CONTEXTIDR .
| TTLB     |   25:25 |    1 | Trap TLB maintenance instructions. Traps execution of TLB maintenance instructions at EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, then the following instructions are trapped to EL2 and reported using EC syndrome value 0x18 : TLBI VMALLE1 , TLBI VAE1 , TLBI ASIDE1 , TLBI VAAE1 , TLBI VALE1 , and TLBI VAALE1 . TLBI VMALLE1IS , TLBI VAE1IS , TLBI ASIDE1IS , TLBI VAAE1IS , TLBI VALE1IS , and TLBI VAALE1IS . If FEAT_TLBIOS is implemented, TLBI VMALLE1OS , TLBI VAE1OS , TLBI ASIDE1OS , TLBI VAAE1OS , TLBI VALE1OS , and TLBI VAALE1OS . If FEAT_TLBIRANGE is implemented, TLBI RVAE1 , TLBI RVAAE1 , TLBI RVALE1 , TLBI RVAALE1 , TLBI RVAE1IS , TLBI RVAAE1IS , TLBI RVALE1IS , and TLBI RVAALE1IS . If FEAT_TLBIOS and FEAT_TLBIRANGE are implemented, TLBI RVAE1OS , TLBI RVAAE1OS , TLBI RVALE1OS , and TLBI RVAALE1OS . If EL1 is using AArch32, then the following instructions are trapped to EL2 and reported using EC syndrome value 0x03 : TLBIALLIS , TLBIMVAIS , TLBIASIDIS , TLBIMVAAIS , TLBIMVALIS , and TLBIMVAALIS . TLBIALL , TLBIMVA , TLBIASID , TLBIMVAA , TLBIMVAL , and TLBIMVAAL ITLBIALL , ITLBIMVA , and ITLBIASID . DTLBIALL , DTLBIMVA , and DTLBIASID .
| TPU      |   24:24 |    1 | Trap cache maintenance instructions that operate to the Point of Unification. Traps execution of those cache maintenance instructions at EL0 and EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL0 is using AArch64 and the value of SCTLR_EL1 .UCI is 1, then the following instructions at EL0 are trapped to EL2 and reported with EC syndrome value 0x18 : IC IVAU and DC CVAU . If EL1 is using AArch64, then the following instructions at EL1 are trapped to EL2 and reported with EC syndrome value 0x18 : IC IVAU , IC IALLU , IC IALLUIS , and DC CVAU . If EL1 is using AArch32, then the following instructions are trapped to EL2 and reported with EC syndrome value 0x03 : ICIMVAU , ICIALLU , ICIALLUIS , and DCCMVAU . When SCTLR_EL1 .UCI is 0, the trap on execution of instructions at EL0 is higher priority than this control. An exception generated because an instruction is UNDEFINED at EL0 is higher priority than this trap to EL2. In addition: IC IALLUIS and IC IALLU are always UNDEFINED at EL0 using AArch64. ICIMVAU , ICIALLU , ICIALLUIS , and DCCMVAU are always UNDEFINED at EL0 using AArch32.
| TPCP     |   23:23 |    1 | Trap data or unified cache maintenance instructions that operate to the Point of Coherency, Persistence, or Physical Storage. When EL2 is enabled in the current Security state, traps execution of cache maintenance instructions at EL0 and EL1 to EL2 as follows: If EL0 is using AArch64 and the value of SCTLR_EL1 .UCI is 1, then the following instructions at EL0 are trapped to EL2 and reported using EC syndrome value 0x18 : DC CIVAC and DC CVAC . If FEAT_MTE is implemented, DC CIGVAC , DC CIGDVAC , DC CGVAC , and DC CGDVAC . If FEAT_DPB is implemented, DC CVAP . If FEAT_DPB and FEAT_MTE are implemented, DC CGVAP and DC CGDVAP . If FEAT_DPB2 is implemented, DC CVADP . If FEAT_DPB2 and FEAT_MTE are implemented, DC CGVADP and DC CGDVADP . If EL1 is using AArch64, then the following instructions at EL1 are trapped to EL2 and reported using EC syndrome value 0x18 : DC IVAC , DC CIVAC and DC CVAC . If FEAT_MTE is implemented, DC CIGVAC , DC CIGDVAC , DC IGVAC , DC IGDVAC , DC CGVAC , and DC CGDVAC . If FEAT_DPB is implemented, DC CVAP . If FEAT_DPB and FEAT_MTE are implemented, DC CGVAP and DC CGDVAP . If FEAT_DPB2 is implemented, DC CVADP . If FEAT_DPB2 and FEAT_MTE are implemented, DC CGVADP and DC CGDVADP . If FEAT_PoPS is implemented, DC CIVAPS . If FEAT_PoPS and FEAT_MTE2 are implemented, DC CIGDVAPS . If EL1 is using AArch32, then the following instructions at EL1 are trapped to EL2 and reported using EC syndrome value 0x03 : DCIMVAC , DCCIMVAC , and DCCMVAC . This field was previously named TPC. When SCTLR_EL1 .UCI is 0, the trap on execution of instructions at EL0 is higher priority than this control. An exception generated because an instruction is UNDEFINED at EL0 is higher priority than this trap to EL2. In addition: AArch64 instructions which invalidate by VA to the Point of Coherency or Physical Storage are always UNDEFINED at EL0 using AArch64. DCIMVAC , DCCIMVAC , and DCCMVAC are always UNDEFINED at EL0 using AArch32.
| TSW      |   22:22 |    1 | Trap data or unified cache maintenance instructions that operate by Set/Way. Traps execution of those cache maintenance instructions at EL1 to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, then the following instructions are trapped to EL2 and reported with EC syndrome value 0x18 : DC ISW , DC CSW , and DC CISW . If FEAT_MTE2 is implemented, DC IGSW , DC IGDSW , DC CGSW , DC CGDW , DC CIGSW , and DC CIGDSW . If EL1 is using AArch32, then the following instructions are trapped to EL2 and reported with EC syndrome value 0x03 : DCISW , DCCSW , and DCCISW . An exception generated because an instruction is UNDEFINED at EL0 is higher priority than this trap to EL2, and these instructions are always UNDEFINED at EL0.
| TACR     |   21:21 |    1 | Trap Auxiliary Control Registers. Traps EL1 accesses to the Auxiliary Control Registers to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, accesses to ACTLR_EL1 to EL2, are trapped to EL2 and reported using EC syndrome value 0x18 . If EL1 is using AArch32, accesses to ACTLR and, if implemented, ACTLR2 are trapped to EL2 and reported using EC syndrome value 0x03 .
| TIDCP    |   20:20 |    1 | Trap IMPLEMENTATION DEFINED functionality. Traps EL1 accesses to the encodings reserved for IMPLEMENTATION DEFINED functionality to EL2, when EL2 is enabled in the current Security state as follows: In AArch64 state, EL0 access to the encodings in the following reserved encoding spaces are trapped: IMPLEMENTATION DEFINED System instructions, which are accessed using SYS and SYSL, with CRn == {11, 15}, and are reported using EC syndrome value 0x18 . IMPLEMENTATION DEFINED System instructions, which are accessed using SYSP, with CRn == {11, 15}, and are reported using EC syndrome value 0x14 . IMPLEMENTATION DEFINED System registers, which are accessed using MRS and MSR with the S3_<op1>_<Cn>_<Cm>_<op2> register name, and are reported using EC syndrome 0x18 . IMPLEMENTATION DEFINED System registers, which are accessed using MRRS and MSRR with the S3_<op1>_<Cn>_<Cm>_<op2> register name, and are reported using EC syndrome 0x14 . In AArch32 state, MCR and MRC access to instructions with the following encodings are trapped and reported using EC syndrome value 0x03 : All coproc==p15, CRn==c9, opc1 == {0-7}, CRm == {c0-c2, c5-c8}, opc2 == {0-7}. All coproc==p15, CRn==c10, opc1 =={0-7}, CRm == {c0, c1, c4, c8}, opc2 == {0-7}. All coproc==p15, CRn==c11, opc1=={0-7}, CRm == {c0-c8, c15}, opc2 == {0-7}. When this functionality is accessed from EL0: If FEAT_TIDCP1 is implemented and the Effective value of SCTLR_EL1 .TIDCP is 1, any accesses from EL0 are trapped to EL1. Otherwise, if FEAT_TIDCP1 is implemented and the Effective value of SCTLR_EL2 .TIDCP is 1, any accesses from EL0 are trapped to EL2. Otherwise: If HCR_EL2.TIDCP is 1, it is IMPLEMENTATION DEFINED whether any accesses from EL0 are trapped to EL2. If HCR_EL2.TIDCP is 0, any accesses from EL0 are UNDEFINED and generate an exception that is taken to EL1 or EL2.
| TSC      |   19:19 |    1 | Trap SMC instructions. Traps EL1 execution of SMC instructions to EL2, when EL2 is enabled in the current Security state. If execution is in AArch64 state, the trap is reported using EC syndrome value 0x17 . If execution is in AArch32 state, the trap is reported using EC syndrome value 0x13 . HCR_EL2.TSC traps execution of the SMC instruction. It is not a routing control for the SMC exception. Trap exceptions and SMC exceptions have different preferred return addresses.
| TID3     |   18:18 |    1 | Trap ID group 3. Traps EL1 reads of group 3 ID registers to EL2, when EL2 is enabled in the current Security state, as follows: In AArch64 state: Reads of the following registers are trapped to EL2, reported using EC syndrome value 0x18 : ID_PFR0_EL1 , ID_PFR1_EL1 , ID_DFR0_EL1 , ID_AFR0_EL1 , ID_MMFR0_EL1 , ID_MMFR1_EL1 , ID_MMFR2_EL1 , ID_MMFR3_EL1 , ID_ISAR0_EL1 , ID_ISAR1_EL1 , ID_ISAR2_EL1 , ID_ISAR3_EL1 , ID_ISAR4_EL1 , ID_ISAR5_EL1 , MVFR0_EL1 , MVFR1_EL1 , and MVFR2_EL1 . ID_AA64PFR0_EL1 , ID_AA64PFR1_EL1 , ID_AA64DFR0_EL1 , ID_AA64DFR1_EL1 , ID_AA64ISAR0_EL1 , ID_AA64ISAR1_EL1 , ID_AA64MMFR0_EL1 , ID_AA64MMFR1_EL1 , ID_AA64AFR0_EL1 , and ID_AA64AFR1_EL1 . If FEAT_FGT is implemented, reads of the following registers are trapped to EL2. If FEAT_FGT is not implemented, reads of the following registers are trapped to EL2, unless the registers are implemented as RAZ, when it is IMPLEMENTATION DEFINED whether accesses are trapped to EL2. ID_PFR2_EL1 , ID_MMFR4_EL1 and ID_MMFR5_EL1 . ID_AA64MMFR3_EL1 . ID_AA64MMFR4_EL1 . ID_AA64PFR2_EL1 . ID_AA64MMFR2_EL1 and ID_ISAR6_EL1 . ID_DFR1_EL1 . ID_AA64ZFR0_EL1 . ID_AA64SMFR0_EL1 . ID_AA64ISAR2_EL1 . If FEAT_FGT is implemented, this field traps all MRS accesses to registers in the following range that are not already mentioned in this field description: op0 == 3, op1 == 0, CRn == 0, CRm == {2-7}, op2 == {0-7}. If FEAT_FGT is not implemented, it is IMPLEMENTATION DEFINED whether this field traps accesses to registers in the range. In AArch32 state: VMRS access to MVFR0 , MVFR1 , and MVFR2 , are trapped to EL2, reported using EC syndrome value 0x08 , unless access is also trapped by HCPTR which takes priority. MRC access to the following registers are trapped to EL2, reported using EC syndrome value 0x03 : ID_PFR0 , ID_PFR1 , ID_PFR2 , ID_DFR0 , ID_AFR0 , ID_MMFR0 , ID_MMFR1 , ID_MMFR2 , ID_MMFR3 , ID_ISAR0 , ID_ISAR1 , ID_ISAR2 , ID_ISAR3 , ID_ISAR4 , and ID_ISAR5 . If FEAT_FGT is implemented: ID_MMFR4 and ID_MMFR5 . ID_ISAR6 . ID_DFR1 . This field traps all MRC accesses to encodings in the following range that are not already mentioned in this field description: coproc == p15, opc1 == 0, CRn == c0, CRm == {c2-c7}, opc2 == {0-7}. If FEAT_FGT is not implemented: ID_MMFR4 and ID_MMFR5 are trapped to EL2, unless implemented as RAZ, when it is IMPLEMENTATION DEFINED whether accesses to ID_MMFR4 or ID_MMFR5 are trapped. ID_ISAR6 is trapped to EL2, unless implemented as RAZ, when it is IMPLEMENTATION DEFINED whether accesses to ID_ISAR6 are trapped to EL2. ID_DFR1 is trapped to EL2, unless implemented as RAZ, when it is IMPLEMENTATION DEFINED whether accesses to ID_DFR1 are trapped to EL2. Otherwise, it is IMPLEMENTATION DEFINED whether this bit traps all MRC accesses to registers in the following range not already mentioned in this field description with coproc == p15, opc1 == 0, CRn == c0, CRm == {c2-c7}, opc2 == {0-7}.
| TID2     |   17:17 |    1 | Trap ID group 2. Traps the following register accesses to EL2, when EL2 is enabled in the current Security state, as follows: If EL1 is using AArch64, reads of CTR_EL0 , CCSIDR_EL1 , CCSIDR2_EL1 , CLIDR_EL1 , and CSSELR_EL1 are trapped to EL2, reported using EC syndrome value 0x18 . If EL0 is using AArch64 and the value of SCTLR_EL1 .UCT is not 0, reads of CTR_EL0 are trapped to EL2, reported using EC syndrome value 0x18 . If the value of SCTLR_EL1 .UCT is 0, then EL0 reads of CTR_EL0 are trapped to EL1 and the resulting exception takes precedence over this trap. If EL1 is using AArch64, writes to CSSELR_EL1 are trapped to EL2, reported using EC syndrome value 0x18 . If EL1 is using AArch32, reads of CTR , CCSIDR , CCSIDR2 , CLIDR , and CSSELR are trapped to EL2, reported using EC syndrome value 0x03 . If EL1 is using AArch32, writes to CSSELR are trapped to EL2, reported using EC syndrome value 0x03 .
| TID1     |   16:16 |    1 | Trap ID group 1. Traps EL1 reads of the following registers to EL2, when EL2 is enabled in the current Security state as follows: In AArch64 state, accesses of REVIDR_EL1 , AIDR_EL1 , and SMIDR_EL1 , reported using EC syndrome value 0x18 . In AArch32 state, accesses of TCMTR , TLBTR , REVIDR , and AIDR , reported using EC syndrome value 0x03 .
| TID0     |   15:15 |    1 | Trap ID group 0. Traps the following register accesses to EL2: EL1 reads of the JIDR , reported using EC syndrome value 0x05 . If the JIDR is RAZ from EL0, EL0 reads of the JIDR , reported using EC syndrome value 0x05 . EL1 accesses using VMRS of the FPSID , reported using EC syndrome value 0x08 . It is IMPLEMENTATION DEFINED whether the JIDR is RAZ or UNDEFINED at EL0. If it is UNDEFINED at EL0, then any resulting exception takes precedence over this trap. The FPSID is not accessible at EL0 using AArch32. Writes to the FPSID are ignored, and not trapped by this control.
| TWE      |   14:14 |    1 | Traps EL0 and EL1 execution of WFE instructions to EL2, when EL2 is enabled in the current Security state, from both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFET instruction.
| TWI      |   13:13 |    1 | Traps EL0 and EL1 execution of WFI instructions to EL2, when EL2 is enabled in the current Security state, from both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFIT instruction.
| DC       |   12:12 |    1 | Default Cacheability.
| BSU      |   11:10 |    2 | Barrier Shareability upgrade. This field determines the minimum shareability domain that is applied to any barrier instruction executed from EL1 or EL0:
| FB       |     9:9 |    1 | Force broadcast. Causes the following instructions to be broadcast within the Inner Shareable domain when executed from EL1: AArch32: BPIALL , TLBIALL , TLBIMVA , TLBIASID , DTLBIALL , DTLBIMVA , DTLBIASID , ITLBIALL , ITLBIMVA , ITLBIASID , TLBIMVAA , ICIALLU , TLBIMVAL , and TLBIMVAAL . AArch64: TLBI VMALLE1 , TLBI VAE1 , TLBI ASIDE1 , TLBI VAAE1 , TLBI VALE1 , TLBI VAALE1 , IC IALLU , TLBI RVAE1 , TLBI RVAAE1 , TLBI RVALE1 , and TLBI RVAALE1 .
| VSE      |     8:8 |    1 | Virtual SError exception.
| VI       |     7:7 |    1 | Virtual IRQ Interrupt.
| VF       |     6:6 |    1 | Virtual FIQ Interrupt.
| AMO      |     5:5 |    1 | Physical SError exception routing.
| IMO      |     4:4 |    1 | Physical IRQ Routing.
| FMO      |     3:3 |    1 | Physical FIQ Routing.
| PTW      |     2:2 |    1 | Protected Table Walk. In the EL1&0 translation regime, a translation table access made as part of a stage 1 translation table walk is subject to a stage 2 translation. The combining of the memory type attributes from the two stages of translation means the access might be made to a type of Device memory. If this occurs, then the value of this bit determines the behavior:
| SWIO     |     1:1 |    1 | Set/Way Invalidation Override. Causes EL1 execution of the data cache invalidate by set/way instructions to perform a data cache clean and invalidate by set/way:
| VM       |     0:0 |    1 | Virtualization enable. Enables stage 2 address translation for the EL1&0 translation regime, when EL2 is enabled in the current Security state.

## HCRX_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| SRMASKEn  |   26:26 |    1 | If EL1 is using AArch64, accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x18 : CPACRMASK_EL1 . SCTLRMASK_EL1 . SCTLR2MASK_EL1 . TCRMASK_EL1 . TCR2MASK_EL1 . ACTLRMASK_EL1 , if it is implemented.
| PACMEn    |   24:24 |    1 | PACM Enable. Controls the effect of a PACM instruction at EL1 and EL0.
| EnFPM     |   23:23 |    1 | Enables direct and indirect accesses to FPMR from EL0 and EL1. When accesses to FPMR are disabled by this control: Direct accesses to FPMR from EL0 and EL1 are trapped to EL2 and reported using EC syndrome value 0x18 . Execution of FP8 data-processing instructions that indirectly access FPMR is UNDEFINED at EL0 and EL1.
| GCSEn     |   22:22 |    1 | Guarded Control Stack enable. Controls Guarded Control Stack behavior at EL1 and EL0.
| EnIDCP128 |   21:21 |    1 | Enables access to IMPLEMENTATION DEFINED 128-bit System registers.
| EnSDERR   |   20:20 |    1 | Enable Synchronous Device Read Error. Override SCTLR2_EL1 .EnADERR.
| TMEA      |   19:19 |    1 | Trap Masked External Aborts. Controls whether a masked error exception at a lower Exception level is taken to EL2.
| EnSNERR   |   18:18 |    1 | Enable Synchronous Normal Read Error. Override SCTLR2_EL1 .EnANERR.
| D128En    |   17:17 |    1 | 128-bit System Register trap control. Enable access to 128-bit System Registers that relate to VMSAv9-128 via MRRS , MSRR instructions. If EL1 is using AArch64, accesses to the following registers are trapped to EL2 and reported using EC syndrome value 0x14 : TTBR0_EL1 . TTBR1_EL1 . If FEAT_THE is implemented, RCWMASK_EL1 , RCWSMASK_EL1 . PAR_EL1 .
| PTTWI     |   16:16 |    1 | Permit Translation Table Walk Incoherence. Permits RCWS instructions to generate writes that have the Reduced Coherence property.
| SCTLR2En  |   15:15 |    1 | SCTLR2_EL1 Enable. In AArch64 state, accesses to SCTLR2_EL1 are trapped to EL2 and reported using EC syndrome value 0x18 .
| TCR2En    |   14:14 |    1 | TCR2_EL1 Enable. In AArch64 state, accesses to TCR2_EL1 are trapped to EL2 and reported using EC syndrome value 0x18 .
| MSCEn     |   11:11 |    1 | Memory Set and Memory Copy instructions Enable. Enables execution of the CPY*, SETG*, SETP*, SETM*, and SETE* instructions at EL1 or EL0.
| MCE2      |   10:10 |    1 | Controls Memory Copy and Memory Set exceptions generated as part of attempting to execute the Memory Copy and Memory Set instructions from EL1.
| CMOW      |     9:9 |    1 | Controls cache maintenance instruction permission for the following instructions executed at EL1 or EL0. IC IVAU and DC CIVAC . If FEAT_MTE is implemented, DC CIGDVAC and DC CIGVAC . If FEAT_PoPS is implemented, DC CIVAPS . If FEAT_PoPS and FEAT_MTE2 are implemented, DC CIGDVAPS . ICIMVAU and DCCIMVAC .
| VFNMI     |     8:8 |    1 | Virtual FIQ Interrupt with Superpriority. Enables signaling of virtual FIQ interrupts with Superpriority.
| VINMI     |     7:7 |    1 | Virtual IRQ Interrupt with Superpriority. Enables signaling of virtual IRQ interrupts with Superpriority.
| TALLINT   |     6:6 |    1 | Traps the following writes at EL1 using AArch64 to EL2, when EL2 is implemented and enabled: MSR (register) writes of ALLINT . MSR (immediate) writes of ALLINT with a value of 1.
| SMPME     |     5:5 |    1 | Streaming Mode Priority Mapping Enable. Controls mapping of the value of SMPRI_EL1 .Priority for streaming execution priority at EL0 or EL1.
| FGTnXS    |     4:4 |    1 | Determines if the fine-grained traps in HFGITR_EL2 that apply to each of the TLBI maintenance instructions that are accessible at EL1 also apply to the corresponding TLBI maintenance instructions with the nXS qualifier.
| FnXS      |     3:3 |    1 | Determines the behavior of TLBI instructions affected by the XS attribute. This control field also determines whether an AArch64 DSB instruction behaves as a DSB instruction with an nXS qualifier when executed at EL0 and EL1.
| EnASR     |     2:2 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an ST64BV instruction at EL0 or EL1 to EL2.
| EnALS     |     1:1 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an LD64B or ST64B instruction at EL0 or EL1 to EL2.
| EnAS0     |     0:0 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an ST64BV0 instruction at EL0 or EL1 to EL2.

## HDBSSBR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BADDR    |   55:12 |   44 | HDBSS base address, bits [55:12]. Bits [55:12] of the base address are the value of this field. Bits [11:0] of the base address are 0. Bits of this field above the implemented physical address size, indicated in ID_AA64MMFR0_EL1 .PARange, are RES0 . Based on the value of the SZ field of this register, for encodings of the SZ field greater than 4KB, bits [(SZ+12-1):12] of this field are RES0 such that the base address of the HDBSS is aligned to its size.
| SZ       |     3:0 |    4 | Size of the HDBSS.

## HDBSSPROD_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FSC      |   31:26 |    6 | Fault Status Code.
| INDEX    |    18:0 |   19 | This field indicates the index of the HDBSS entry that will be written to next.

## HDFGRTR2_EL2 bitfields

| Bitfield         | msb:lsb | Size | Description
| ---------------- | ------: | ---: | -----------
| nPMBMAR_EL1      |   24:24 |    1 | Trap MRS reads of PMBMAR_EL1 at EL1 using AArch64 to EL2.
| nMDSTEPOP_EL1    |   23:23 |    1 | Trap MRS reads of MDSTEPOP_EL1 at EL1 using AArch64 to EL2.
| nTRBMPAM_EL1     |   22:22 |    1 | Trap MRS reads of TRBMPAM_EL1 at EL1 using AArch64 to EL2.
| nTRCITECR_EL1    |   20:20 |    1 | Trap MRS reads of TRCITECR_EL1 at EL1 using AArch64 to EL2.
| nPMSDSFR_EL1     |   19:19 |    1 | Trap MRS reads of PMSDSFR_EL1 at EL1 using AArch64 to EL2.
| nSPMDEVAFF_EL1   |   18:18 |    1 | Trap MRS reads of SPMDEVAFF_EL1 at EL1 using AArch64 to EL2.
| nSPMID           |   17:17 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: SPMCFGR_EL1 . SPMCGCR<n>_EL1 . SPMDEVARCH_EL1 . SPMIIDR_EL1 .
| nSPMSCR_EL1      |   16:16 |    1 | Trap MRS reads of SPMSCR_EL1 at EL1 using AArch64 to EL2.
| nSPMACCESSR_EL1  |   15:15 |    1 | Trap MRS reads of SPMACCESSR_EL1 at EL1 using AArch64 to EL2.
| nSPMCR_EL0       |   14:14 |    1 | Trap MRS reads of SPMCR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSPMOVS          |   13:13 |    1 | Trap MRS reads at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMOVSCLR_EL0 . SPMOVSSET_EL0 .
| nSPMINTEN        |   12:12 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: SPMINTENCLR_EL1 . SPMINTENSET_EL1 .
| nSPMCNTEN        |   11:11 |    1 | Trap MRS reads at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMCNTENCLR_EL0 . SPMCNTENSET_EL0 .
| nSPMSELR_EL0     |   10:10 |    1 | Trap MRS reads of SPMSELR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSPMEVTYPERn_EL0 |     9:9 |    1 | Trap MRS reads at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMEVTYPER<n>_EL0 . SPMEVFILTR<n>_EL0 . SPMEVFILT2R<n>_EL0 .
| nSPMEVCNTRn_EL0  |     8:8 |    1 | Trap MRS reads of SPMEVCNTR<n>_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPMSSCR_EL1      |     7:7 |    1 | Trap MRS reads of PMSSCR_EL1 at EL1 using AArch64 to EL2.
| nPMSSDATA        |     6:6 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: PMCCNTSVR_EL1 . PMEVCNTSVR<n>_EL1 . PMICNTSVR_EL1 , if FEAT_PMUv3_ICNTR is implemented.
| nMDSELR_EL1      |     5:5 |    1 | Trap MRS reads of MDSELR_EL1 at EL1 using AArch64 to EL2.
| nPMUACR_EL1      |     4:4 |    1 | Trap MRS reads of PMUACR_EL1 at EL1 using AArch64 to EL2.
| nPMICFILTR_EL0   |     3:3 |    1 | Trap MRS reads of PMICFILTR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPMICNTR_EL0     |     2:2 |    1 | Trap MRS reads of PMICNTR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPMIAR_EL1       |     1:1 |    1 | Trap MRS reads of PMIAR_EL1 at EL1 using AArch64 to EL2.
| nPMECR_EL1       |     0:0 |    1 | Trap MRS reads of PMECR_EL1 at EL1 using AArch64 to EL2.

## HDFGRTR_EL2 bitfields

| Bitfield          | msb:lsb | Size | Description
| ----------------- | ------: | ---: | -----------
| PMBIDR_EL1        |   63:63 |    1 | Trap MRS reads of PMBIDR_EL1 at EL1 using AArch64 to EL2.
| nPMSNEVFR_EL1     |   62:62 |    1 | Trap MRS reads of PMSNEVFR_EL1 at EL1 using AArch64 to EL2.
| nBRBDATA          |   61:61 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: BRBINF<n>_EL1 . BRBINFINJ_EL1 . BRBSRC<n>_EL1 . BRBSRCINJ_EL1 . BRBTGT<n>_EL1 . BRBTGTINJ_EL1 . BRBTS_EL1 .
| nBRBCTL           |   60:60 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: BRBCR_EL1 . BRBFCR_EL1 .
| nBRBIDR           |   59:59 |    1 | Trap MRS reads of BRBIDR0_EL1 at EL1 using AArch64 to EL2.
| PMCEIDn_EL0       |   58:58 |    1 | Trap MRS reads of PMCEID<n>_EL0 at EL1 and EL0 using AArch64 and MRC reads of PMCEID<n> at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMUSERENR_EL0     |   57:57 |    1 | Trap MRS reads of PMUSERENR_EL0 at EL1 and EL0 using AArch64 and MRC reads of PMUSERENR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| TRBTRG_EL1        |   56:56 |    1 | Trap MRS reads of TRBTRG_EL1 at EL1 using AArch64 to EL2.
| TRBSR_EL1         |   55:55 |    1 | Trap MRS reads of TRBSR_EL1 at EL1 using AArch64 to EL2.
| TRBPTR_EL1        |   54:54 |    1 | Trap MRS reads of TRBPTR_EL1 at EL1 using AArch64 to EL2.
| TRBMAR_EL1        |   53:53 |    1 | Trap MRS reads of TRBMAR_EL1 at EL1 using AArch64 to EL2.
| TRBLIMITR_EL1     |   52:52 |    1 | Trap MRS reads of TRBLIMITR_EL1 at EL1 using AArch64 to EL2.
| TRBIDR_EL1        |   51:51 |    1 | Trap MRS reads of TRBIDR_EL1 at EL1 using AArch64 to EL2.
| TRBBASER_EL1      |   50:50 |    1 | Trap MRS reads of TRBBASER_EL1 at EL1 using AArch64 to EL2.
| TRCVICTLR         |   48:48 |    1 | In an Armv9 implementation, trap MRS reads of TRCVICTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCVICTLR at EL1 using AArch64 to EL2.
| TRCSTATR          |   47:47 |    1 | In an Armv9 implementation, trap MRS reads of TRCSTATR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCSTATR at EL1 using AArch64 to EL2.
| TRCSSCSRn         |   46:46 |    1 | In an Armv9 implementation, trap MRS reads of TRCSSCSR<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCSSCSR<n> at EL1 using AArch64 to EL2.
| TRCSEQSTR         |   45:45 |    1 | In an Armv9 implementation, trap MRS reads of TRCSEQSTR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCSEQSTR at EL1 using AArch64 to EL2.
| TRCPRGCTLR        |   44:44 |    1 | In an Armv9 implementation, trap MRS reads of TRCPRGCTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCPRGCTLR at EL1 using AArch64 to EL2.
| TRCOSLSR          |   43:43 |    1 | In an Armv9 implementation, trap MRS reads of TRCOSLSR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCOSLSR at EL1 using AArch64 to EL2.
| TRCIMSPECn        |   41:41 |    1 | In an Armv9 implementation, trap MRS reads of TRCIMSPEC<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCIMSPEC<n> at EL1 using AArch64 to EL2.
| TRCID             |   40:40 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: In an Armv9 implementation: TRCDEVARCH . TRCDEVID . All of the TRCIDR<n> registers. In an Armv8 implementation: ETM TRCDEVARCH. ETM TRCDEVID. All of the ETM TRCIDR<n> registers.
| TRCCNTVRn         |   37:37 |    1 | In an Armv9 implementation, trap MRS reads of TRCCNTVR<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCCNTVR<n> at EL1 using AArch64 to EL2.
| TRCCLAIM          |   36:36 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: In an Armv9 implementation: TRCCLAIMCLR and TRCCLAIMSET . In an Armv8 implementation: ETM TRCCLAIMCLR and ETM TRCCLAIMSET.
| TRCAUXCTLR        |   35:35 |    1 | In an Armv9 implementation, trap MRS reads of TRCAUXCTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCAUXCTLR at EL1 using AArch64 to EL2.
| TRCAUTHSTATUS     |   34:34 |    1 | In an Armv9 implementation, trap MRS reads of TRCAUTHSTATUS at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MRS reads of ETM TRCAUTHSTATUS at EL1 using AArch64 to EL2.
| TRC               |   33:33 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: In an Armv9 implementation: TRCACATR<n> . TRCACVR<n> . TRCBBCTLR . TRCCCCTLR . TRCCIDCCTLR0 . TRCCIDCCTLR1 . TRCCIDCVR<n> . TRCCNTCTLR<n> . TRCCNTRLDVR<n> . TRCCONFIGR . TRCEVENTCTL0R . TRCEVENTCTL1R . TRCEXTINSELR<n> . TRCQCTLR . TRCRSCTLR<n> . TRCRSR . TRCSEQEVR<n> . TRCSEQRSTEVR . TRCSSCCR<n> . TRCSSPCICR<n> . TRCSTALLCTLR . TRCSYNCPR . TRCTRACEIDR . TRCTSCTLR . TRCVIIECTLR . TRCVIPCSSCTLR . TRCVISSCTLR . TRCVMIDCCTLR0 . TRCVMIDCCTLR1 . TRCVMIDCVR<n> . In an Armv8 implementation: ETM TRCACATR<n>. ETM TRCACVR<n>. ETM TRCBBCTLR. ETM TRCCCCTLR. ETM TRCCIDCCTLR0. ETM TRCCIDCCTLR1. ETM TRCCIDCVR<n>. ETM TRCCNTCTLR<n>. ETM TRCCNTRLDVR<n>. ETM TRCCONFIGR. ETM TRCEVENTCTL0R. ETM TRCEVENTCTL1R. ETM TRCEXTINSELR. ETM TRCQCTLR. ETM TRCRSCTLR<n>. ETM TRCSEQEVR<n>. ETM TRCSEQRSTEVR. ETM TRCSSCCR<n>. ETM TRCSSPCICR<n>. ETM TRCSTALLCTLR. ETM TRCSYNCPR. ETM TRCTRACEIDR. ETM TRCTSCTLR. ETM TRCVIIECTLR. ETM TRCVIPCSSCTLR. ETM TRCVISSCTLR. ETM TRCVMIDCCTLR0. ETM TRCVMIDCCTLR1. ETM TRCVMIDCVR<n>.
| PMSLATFR_EL1      |   32:32 |    1 | Trap MRS reads of PMSLATFR_EL1 at EL1 using AArch64 to EL2.
| PMSIRR_EL1        |   31:31 |    1 | Trap MRS reads of PMSIRR_EL1 at EL1 using AArch64 to EL2.
| PMSIDR_EL1        |   30:30 |    1 | Trap MRS reads of PMSIDR_EL1 at EL1 using AArch64 to EL2.
| PMSICR_EL1        |   29:29 |    1 | Trap MRS reads of PMSICR_EL1 at EL1 using AArch64 to EL2.
| PMSFCR_EL1        |   28:28 |    1 | Trap MRS reads of PMSFCR_EL1 at EL1 using AArch64 to EL2.
| PMSEVFR_EL1       |   27:27 |    1 | Trap MRS reads of PMSEVFR_EL1 at EL1 using AArch64 to EL2.
| PMSCR_EL1         |   26:26 |    1 | Trap MRS reads of PMSCR_EL1 at EL1 using AArch64 to EL2.
| PMBSR_EL1         |   25:25 |    1 | Trap MRS reads of PMBSR_EL1 at EL1 using AArch64 to EL2.
| PMBPTR_EL1        |   24:24 |    1 | Trap MRS reads of PMBPTR_EL1 at EL1 using AArch64 to EL2.
| PMBLIMITR_EL1     |   23:23 |    1 | Trap MRS reads of PMBLIMITR_EL1 at EL1 using AArch64 to EL2.
| PMMIR_EL1         |   22:22 |    1 | Trap MRS reads of PMMIR_EL1 at EL1 using AArch64 to EL2.
| PMSELR_EL0        |   19:19 |    1 | Trap MRS reads of PMSELR_EL0 at EL1 and EL0 using AArch64 and MRC reads of PMSELR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMOVS             |   18:18 |    1 | Trap MRS reads and MRC reads of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMOVSCLR_EL0 and PMOVSSET_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMOVSR and PMOVSSET .
| PMINTEN           |   17:17 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: PMINTENCLR_EL1 . PMINTENSET_EL1 .
| PMCNTEN           |   16:16 |    1 | Trap MRS reads and MRC reads of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMCNTENCLR_EL0 and PMCNTENSET_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMCNTENCLR and PMCNTENSET .
| PMCCNTR_EL0       |   15:15 |    1 | Trap MRS reads of PMCCNTR_EL0 at EL1 and EL0 using AArch64 and MRC and MRRC reads of PMCCNTR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMCCFILTR_EL0     |   14:14 |    1 | Trap MRS reads of PMCCFILTR_EL0 at EL1 and EL0 using AArch64 and MRC reads of PMCCFILTR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMEVTYPERn_EL0    |   13:13 |    1 | Trap MRS reads and MRC reads of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMEVTYPER<n>_EL0 and PMXEVTYPER_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMEVTYPER<n> and PMXEVTYPER .
| PMEVCNTRn_EL0     |   12:12 |    1 | Trap MRS reads and MRC reads of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMEVCNTR<n>_EL0 and PMXEVCNTR_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMEVCNTR<n> and PMXEVCNTR .
| OSDLR_EL1         |   11:11 |    1 | Trap MRS reads of OSDLR_EL1 at EL1 using AArch64 to EL2.
| OSECCR_EL1        |   10:10 |    1 | Trap MRS reads of OSECCR_EL1 at EL1 using AArch64 to EL2.
| OSLSR_EL1         |     9:9 |    1 | Trap MRS reads of OSLSR_EL1 at EL1 using AArch64 to EL2.
| DBGPRCR_EL1       |     7:7 |    1 | Trap MRS reads of DBGPRCR_EL1 at EL1 using AArch64 to EL2.
| DBGAUTHSTATUS_EL1 |     6:6 |    1 | Trap MRS reads of DBGAUTHSTATUS_EL1 at EL1 using AArch64 to EL2.
| DBGCLAIM          |     5:5 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: DBGCLAIMCLR_EL1 . DBGCLAIMSET_EL1 .
| MDSCR_EL1         |     4:4 |    1 | Trap MRS reads of MDSCR_EL1 at EL1 using AArch64 to EL2.
| DBGWVRn_EL1       |     3:3 |    1 | Trap MRS reads of DBGWVR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGWCRn_EL1       |     2:2 |    1 | Trap MRS reads of DBGWCR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGBVRn_EL1       |     1:1 |    1 | Trap MRS reads of DBGBVR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGBCRn_EL1       |     0:0 |    1 | Trap MRS reads of DBGBCR<n>_EL1 at EL1 using AArch64 to EL2.

## HDFGWTR2_EL2 bitfields

| Bitfield         | msb:lsb | Size | Description
| ---------------- | ------: | ---: | -----------
| nPMBMAR_EL1      |   24:24 |    1 | Trap MSR writes of PMBMAR_EL1 at EL1 using AArch64 to EL2.
| nMDSTEPOP_EL1    |   23:23 |    1 | Trap MSR writes of MDSTEPOP_EL1 at EL1 using AArch64 to EL2.
| nTRBMPAM_EL1     |   22:22 |    1 | Trap MSR writes of TRBMPAM_EL1 at EL1 using AArch64 to EL2.
| nPMZR_EL0        |   21:21 |    1 | Trap MSR writes of PMZR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nTRCITECR_EL1    |   20:20 |    1 | Trap MSR writes of TRCITECR_EL1 at EL1 using AArch64 to EL2.
| nPMSDSFR_EL1     |   19:19 |    1 | Trap MSR writes of PMSDSFR_EL1 at EL1 using AArch64 to EL2.
| nSPMSCR_EL1      |   16:16 |    1 | Trap MSR writes of SPMSCR_EL1 at EL1 using AArch64 to EL2.
| nSPMACCESSR_EL1  |   15:15 |    1 | Trap MSR writes of SPMACCESSR_EL1 at EL1 using AArch64 to EL2.
| nSPMCR_EL0       |   14:14 |    1 | Trap MSR writes of SPMCR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSPMOVS          |   13:13 |    1 | Trap MSR writes at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMOVSCLR_EL0 . SPMOVSSET_EL0 .
| nSPMINTEN        |   12:12 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: SPMINTENCLR_EL1 . SPMINTENSET_EL1 .
| nSPMCNTEN        |   11:11 |    1 | Trap MSR writes at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMCNTENCLR_EL0 . SPMCNTENSET_EL0 .
| nSPMSELR_EL0     |   10:10 |    1 | Trap MSR writes of SPMSELR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSPMEVTYPERn_EL0 |     9:9 |    1 | Trap MSR writes at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMEVTYPER<n>_EL0 . SPMEVFILTR<n>_EL0 . SPMEVFILT2R<n>_EL0 .
| nSPMEVCNTRn_EL0  |     8:8 |    1 | Trap MSR writes at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: SPMEVCNTR<n>_EL0 . SPMZR_EL0 .
| nPMSSCR_EL1      |     7:7 |    1 | Trap MSR writes of PMSSCR_EL1 at EL1 using AArch64 to EL2.
| nMDSELR_EL1      |     5:5 |    1 | Trap MSR writes of MDSELR_EL1 at EL1 using AArch64 to EL2.
| nPMUACR_EL1      |     4:4 |    1 | Trap MSR writes of PMUACR_EL1 at EL1 using AArch64 to EL2.
| nPMICFILTR_EL0   |     3:3 |    1 | Trap MSR writes of PMICFILTR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPMICNTR_EL0     |     2:2 |    1 | Trap MSR writes of PMICNTR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPMIAR_EL1       |     1:1 |    1 | Trap MSR writes of PMIAR_EL1 at EL1 using AArch64 to EL2.
| nPMECR_EL1       |     0:0 |    1 | Trap MSR writes of PMECR_EL1 at EL1 using AArch64 to EL2.

## HDFGWTR_EL2 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| nPMSNEVFR_EL1  |   62:62 |    1 | Trap MSR writes of PMSNEVFR_EL1 at EL1 using AArch64 to EL2.
| nBRBDATA       |   61:61 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: BRBINFINJ_EL1 . BRBSRCINJ_EL1 . BRBTGTINJ_EL1 . BRBTS_EL1 .
| nBRBCTL        |   60:60 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: BRBCR_EL1 . BRBFCR_EL1 .
| PMUSERENR_EL0  |   57:57 |    1 | Trap MSR writes of PMUSERENR_EL0 at EL1 using AArch64 to EL2.
| TRBTRG_EL1     |   56:56 |    1 | Trap MSR writes of TRBTRG_EL1 at EL1 using AArch64 to EL2.
| TRBSR_EL1      |   55:55 |    1 | Trap MSR writes of TRBSR_EL1 at EL1 using AArch64 to EL2.
| TRBPTR_EL1     |   54:54 |    1 | Trap MSR writes of TRBPTR_EL1 at EL1 using AArch64 to EL2.
| TRBMAR_EL1     |   53:53 |    1 | Trap MSR writes of TRBMAR_EL1 at EL1 using AArch64 to EL2.
| TRBLIMITR_EL1  |   52:52 |    1 | Trap MSR writes of TRBLIMITR_EL1 at EL1 using AArch64 to EL2.
| TRBBASER_EL1   |   50:50 |    1 | Trap MSR writes of TRBBASER_EL1 at EL1 using AArch64 to EL2.
| TRFCR_EL1      |   49:49 |    1 | Trap MSR writes of TRFCR_EL1 at EL1 using AArch64 to EL2.
| TRCVICTLR      |   48:48 |    1 | In an Armv9 implementation, trap MSR writes of TRCVICTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCVICTLR at EL1 using AArch64 to EL2.
| TRCSSCSRn      |   46:46 |    1 | In an Armv9 implementation, trap MSR writes of TRCSSCSR<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCSSCSR<n> at EL1 using AArch64 to EL2.
| TRCSEQSTR      |   45:45 |    1 | In an Armv9 implementation, trap MSR writes of TRCSEQSTR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCSEQSTR at EL1 using AArch64 to EL2.
| TRCPRGCTLR     |   44:44 |    1 | In an Armv9 implementation, trap MSR writes of TRCPRGCTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCPRGCTLR at EL1 using AArch64 to EL2.
| TRCOSLAR       |   42:42 |    1 | In an Armv8 implementation, trap MSR writes of ETM TRCOSLAR at EL1 using AArch64 to EL2.
| TRCIMSPECn     |   41:41 |    1 | In an Armv9 implementation, trap MSR writes of TRCIMSPEC<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCIMSPEC<n> at EL1 using AArch64 to EL2.
| TRCCNTVRn      |   37:37 |    1 | In an Armv9 implementation, trap MSR writes of TRCCNTVR<n> at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCCNTVR<n> at EL1 using AArch64 to EL2.
| TRCCLAIM       |   36:36 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: In an Armv9 implementation: TRCCLAIMCLR and TRCCLAIMSET . In an Armv8 implementation: ETM TRCCLAIMCLR and ETM TRCCLAIMSET.
| TRCAUXCTLR     |   35:35 |    1 | In an Armv9 implementation, trap MSR writes of TRCAUXCTLR at EL1 using AArch64 to EL2. In an Armv8 implementation, trap MSR writes of ETM TRCAUXCTLR at EL1 using AArch64 to EL2.
| TRC            |   33:33 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: In an Armv9 implementation: TRCACATR<n> . TRCACVR<n> . TRCBBCTLR . TRCCCCTLR . TRCCIDCCTLR0 . TRCCIDCCTLR1 . TRCCIDCVR<n> . TRCCNTCTLR<n> . TRCCNTRLDVR<n> . TRCCONFIGR . TRCEVENTCTL0R . TRCEVENTCTL1R . TRCEXTINSELR<n> . TRCQCTLR . TRCRSCTLR<n> . TRCRSR . TRCSEQEVR<n> . TRCSEQRSTEVR . TRCSSCCR<n> . TRCSSPCICR<n> . TRCSTALLCTLR . TRCSYNCPR . TRCTRACEIDR . TRCTSCTLR . TRCVIIECTLR . TRCVIPCSSCTLR . TRCVISSCTLR . TRCVMIDCCTLR0 . TRCVMIDCCTLR1 . TRCVMIDCVR<n> . In an Armv8 implementation: ETM TRCACATR<n>. ETM TRCACVR<n>. ETM TRCBBCTLR. ETM TRCCCCTLR. ETM TRCCIDCCTLR0. ETM TRCCIDCCTLR1. ETM TRCCIDCVR<n>. ETM TRCCNTCTLR<n>. ETM TRCCNTRLDVR<n>. ETM TRCCONFIGR. ETM TRCEVENTCTL0R. ETM TRCEVENTCTL1R. ETM TRCEXTINSELR. ETM TRCQCTLR. ETM TRCRSCTLR<n>. ETM TRCSEQEVR<n>. ETM TRCSEQRSTEVR. ETM TRCSSCCR<n>. ETM TRCSSPCICR<n>. ETM TRCSTALLCTLR. ETM TRCSYNCPR. ETM TRCTRACEIDR. ETM TRCTSCTLR. ETM TRCVIIECTLR. ETM TRCVIPCSSCTLR. ETM TRCVISSCTLR. ETM TRCVMIDCCTLR0. ETM TRCVMIDCCTLR1. ETM TRCVMIDCVR<n>.
| PMSLATFR_EL1   |   32:32 |    1 | Trap MSR writes of PMSLATFR_EL1 at EL1 using AArch64 to EL2.
| PMSIRR_EL1     |   31:31 |    1 | Trap MSR writes of PMSIRR_EL1 at EL1 using AArch64 to EL2.
| PMSICR_EL1     |   29:29 |    1 | Trap MSR writes of PMSICR_EL1 at EL1 using AArch64 to EL2.
| PMSFCR_EL1     |   28:28 |    1 | Trap MSR writes of PMSFCR_EL1 at EL1 using AArch64 to EL2.
| PMSEVFR_EL1    |   27:27 |    1 | Trap MSR writes of PMSEVFR_EL1 at EL1 using AArch64 to EL2.
| PMSCR_EL1      |   26:26 |    1 | Trap MSR writes of PMSCR_EL1 at EL1 using AArch64 to EL2.
| PMBSR_EL1      |   25:25 |    1 | Trap MSR writes of PMBSR_EL1 at EL1 using AArch64 to EL2.
| PMBPTR_EL1     |   24:24 |    1 | Trap MSR writes of PMBPTR_EL1 at EL1 using AArch64 to EL2.
| PMBLIMITR_EL1  |   23:23 |    1 | Trap MSR writes of PMBLIMITR_EL1 at EL1 using AArch64 to EL2.
| PMCR_EL0       |   21:21 |    1 | Trap MSR writes of PMCR_EL0 at EL1 and EL0 using AArch64 and MCR writes of PMCR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMSWINC_EL0    |   20:20 |    1 | Trap MSR writes of PMSWINC_EL0 at EL1 and EL0 using AArch64 and MCR writes of PMSWINC at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMSELR_EL0     |   19:19 |    1 | Trap MSR writes of PMSELR_EL0 at EL1 and EL0 using AArch64 and MCR writes of PMSELR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMOVS          |   18:18 |    1 | Trap MSR writes and MCR writes of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMOVSCLR_EL0 and PMOVSSET_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMOVSR and PMOVSSET .
| PMINTEN        |   17:17 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: PMINTENCLR_EL1 . PMINTENSET_EL1 .
| PMCNTEN        |   16:16 |    1 | Trap MSR writes and MCR writes of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMCNTENCLR_EL0 and PMCNTENSET_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMCNTENCLR and PMCNTENSET .
| PMCCNTR_EL0    |   15:15 |    1 | Trap MSR writes of PMCCNTR_EL0 at EL1 and EL0 using AArch64 and MCR and MCRR writes of PMCCNTR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMCCFILTR_EL0  |   14:14 |    1 | Trap MSR writes of PMCCFILTR_EL0 at EL1 and EL0 using AArch64 and MCR writes of PMCCFILTR at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| PMEVTYPERn_EL0 |   13:13 |    1 | Trap MSR writes and MCR writes of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMEVTYPER<n>_EL0 and PMXEVTYPER_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMEVTYPER<n> and PMXEVTYPER .
| PMEVCNTRn_EL0  |   12:12 |    1 | Trap MSR writes and MCR writes of any of the following System registers to EL2: At EL1 and EL0 using AArch64: PMEVCNTR<n>_EL0 and PMXEVCNTR_EL0 . At EL0 using AArch32 when EL1 is using AArch64: PMEVCNTR<n> and PMXEVCNTR .
| OSDLR_EL1      |   11:11 |    1 | Trap MSR writes of OSDLR_EL1 at EL1 using AArch64 to EL2.
| OSECCR_EL1     |   10:10 |    1 | Trap MSR writes of OSECCR_EL1 at EL1 using AArch64 to EL2.
| OSLAR_EL1      |     8:8 |    1 | Trap MSR writes of OSLAR_EL1 at EL1 using AArch64 to EL2.
| DBGPRCR_EL1    |     7:7 |    1 | Trap MSR writes of DBGPRCR_EL1 at EL1 using AArch64 to EL2.
| DBGCLAIM       |     5:5 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: DBGCLAIMCLR_EL1 . DBGCLAIMSET_EL1 .
| MDSCR_EL1      |     4:4 |    1 | Trap MSR writes of MDSCR_EL1 at EL1 using AArch64 to EL2.
| DBGWVRn_EL1    |     3:3 |    1 | Trap MSR writes of DBGWVR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGWCRn_EL1    |     2:2 |    1 | Trap MSR writes of DBGWCR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGBVRn_EL1    |     1:1 |    1 | Trap MSR writes of DBGBVR<n>_EL1 at EL1 using AArch64 to EL2.
| DBGBCRn_EL1    |     0:0 |    1 | Trap MSR writes of DBGBCR<n>_EL1 at EL1 using AArch64 to EL2.

## HFGITR2_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| nDCCIVAPS |     1:1 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: DC CIVAPS . DC CIGDVAPS , if FEAT_MTE2 is implemented. If the Point of Physical Storage is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| TSBCSYNC  |     0:0 |    1 | Trap execution of TSB CSYNC at EL1 and EL0 using AArch64 to EL2.

## HFGITR_EL2 bitfields

| Bitfield      | msb:lsb | Size | Description
| ------------- | ------: | ---: | -----------
| PSBCSYNC      |   63:63 |    1 | Trap execution of PSB CSYNC at EL1 and EL0 using AArch64 to EL2.
| ATS1E1A       |   62:62 |    1 | Trap execution of AT S1E1A at EL1  using AArch64 to EL2.
| COSPRCTX      |   60:60 |    1 | Trap execution of COSP RCTX at EL1 and EL0 using AArch64 and execution of COSPRCTX at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| nGCSEPP       |   59:59 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: GCSPUSHX . GCSPOPCX .
| nGCSSTR_EL1   |   58:58 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: GCSSTR . GCSSTTR when PSTATE . UAO is 1. GCSSTTR when the Effective value of HCR_EL2 .{NV, NV1} is {1, 1}.
| nGCSPUSHM_EL1 |   57:57 |    1 | Trap execution of GCSPUSHM at EL1  using AArch64 to EL2.
| nBRBIALL      |   56:56 |    1 | Trap execution of BRB IALL at EL1  using AArch64 to EL2.
| nBRBINJ       |   55:55 |    1 | Trap execution of BRB INJ at EL1  using AArch64 to EL2.
| DCCVAC        |   54:54 |    1 | Trap execution of any of the following AArch64 instructions at EL1 and EL0 to EL2: DC CVAC . DC CGVAC , if FEAT_MTE is implemented. DC CGDVAC , if FEAT_MTE is implemented. DC CVAOC , if FEAT_OCCMO is implemented. DC CGDVAOC , if FEAT_OCCMO is implemented. If the Point of Coherence is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| SVC_EL1       |   53:53 |    1 | Trap execution of SVC at EL1  using AArch64 to EL2.
| SVC_EL0       |   52:52 |    1 | Trap execution of SVC at EL0 using AArch64 and execution of SVC at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| ERET          |   51:51 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: ERET . ERETAA , if FEAT_PAuth is implemented. ERETAB , if FEAT_PAuth is implemented.
| CPPRCTX       |   50:50 |    1 | Trap execution of CPP RCTX at EL1 and EL0 using AArch64 and execution of CPPRCTX at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| DVPRCTX       |   49:49 |    1 | Trap execution of DVP RCTX at EL1 and EL0 using AArch64 and execution of DVPRCTX at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| CFPRCTX       |   48:48 |    1 | Trap execution of CFP RCTX at EL1 and EL0 using AArch64 and execution of CFPRCTX at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| TLBIVAALE1    |   47:47 |    1 | Trap execution of TLBI VAALE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAALE1NXS .
| TLBIVALE1     |   46:46 |    1 | Trap execution of TLBI VALE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VALE1NXS .
| TLBIVAAE1     |   45:45 |    1 | Trap execution of TLBI VAAE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAAE1NXS .
| TLBIASIDE1    |   44:44 |    1 | Trap execution of TLBI ASIDE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI ASIDE1NXS .
| TLBIVAE1      |   43:43 |    1 | Trap execution of TLBI VAE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAE1NXS .
| TLBIVMALLE1   |   42:42 |    1 | Trap execution of TLBI VMALLE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VMALLE1NXS .
| TLBIRVAALE1   |   41:41 |    1 | Trap execution of TLBI RVAALE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAALE1NXS .
| TLBIRVALE1    |   40:40 |    1 | Trap execution of TLBI RVALE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVALE1NXS .
| TLBIRVAAE1    |   39:39 |    1 | Trap execution of TLBI RVAAE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAAE1NXS .
| TLBIRVAE1     |   38:38 |    1 | Trap execution of TLBI RVAE1 at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAE1NXS .
| TLBIRVAALE1IS |   37:37 |    1 | Trap execution of TLBI RVAALE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAALE1ISNXS .
| TLBIRVALE1IS  |   36:36 |    1 | Trap execution of TLBI RVALE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVALE1ISNXS .
| TLBIRVAAE1IS  |   35:35 |    1 | Trap execution of TLBI RVAAE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAAE1ISNXS .
| TLBIRVAE1IS   |   34:34 |    1 | Trap execution of TLBI RVAE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAE1ISNXS .
| TLBIVAALE1IS  |   33:33 |    1 | Trap execution of TLBI VAALE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAALE1ISNXS .
| TLBIVALE1IS   |   32:32 |    1 | Trap execution of TLBI VALE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VALE1ISNXS .
| TLBIVAAE1IS   |   31:31 |    1 | Trap execution of TLBI VAAE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAAE1ISNXS .
| TLBIASIDE1IS  |   30:30 |    1 | Trap execution of TLBI ASIDE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI ASIDE1ISNXS .
| TLBIVAE1IS    |   29:29 |    1 | Trap execution of TLBI VAE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAE1ISNXS .
| TLBIVMALLE1IS |   28:28 |    1 | Trap execution of TLBI VMALLE1IS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VMALLE1ISNXS .
| TLBIRVAALE1OS |   27:27 |    1 | Trap execution of TLBI RVAALE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAALE1OSNXS .
| TLBIRVALE1OS  |   26:26 |    1 | Trap execution of TLBI RVALE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVALE1OSNXS .
| TLBIRVAAE1OS  |   25:25 |    1 | Trap execution of TLBI RVAAE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAAE1OSNXS .
| TLBIRVAE1OS   |   24:24 |    1 | Trap execution of TLBI RVAE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI RVAE1OSNXS .
| TLBIVAALE1OS  |   23:23 |    1 | Trap execution of TLBI VAALE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAALE1OSNXS .
| TLBIVALE1OS   |   22:22 |    1 | Trap execution of TLBI VALE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VALE1OSNXS .
| TLBIVAAE1OS   |   21:21 |    1 | Trap execution of TLBI VAAE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAAE1OSNXS .
| TLBIASIDE1OS  |   20:20 |    1 | Trap execution of TLBI ASIDE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI ASIDE1OSNXS .
| TLBIVAE1OS    |   19:19 |    1 | Trap execution of TLBI VAE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VAE1OSNXS .
| TLBIVMALLE1OS |   18:18 |    1 | Trap execution of TLBI VMALLE1OS at EL1  using AArch64 to EL2. If FEAT_XS is implemented and HCRX_EL2 .FGTnXS == 0, this field also traps execution of TLBI VMALLE1OSNXS .
| ATS1E1WP      |   17:17 |    1 | Trap execution of AT S1E1WP at EL1  using AArch64 to EL2.
| ATS1E1RP      |   16:16 |    1 | Trap execution of AT S1E1RP at EL1  using AArch64 to EL2.
| ATS1E0W       |   15:15 |    1 | Trap execution of AT S1E0W at EL1  using AArch64 to EL2.
| ATS1E0R       |   14:14 |    1 | Trap execution of AT S1E0R at EL1  using AArch64 to EL2.
| ATS1E1W       |   13:13 |    1 | Trap execution of AT S1E1W at EL1  using AArch64 to EL2.
| ATS1E1R       |   12:12 |    1 | Trap execution of AT S1E1R at EL1  using AArch64 to EL2.
| DCZVA         |   11:11 |    1 | Trap execution of any of the following AArch64 instructions at EL1 and EL0 to EL2: DC ZVA . DC GVA , if FEAT_MTE is implemented. DC GZVA , if FEAT_MTE is implemented. Unlike HCR_EL2 .TDZ, this field has no effect on DCZID_EL0 .DZP.
| DCCIVAC       |   10:10 |    1 | Trap execution of any of the following AArch64 instructions at EL1 and EL0 to EL2: DC CIVAC . DC CIGVAC , if FEAT_MTE is implemented. DC CIGDVAC , if FEAT_MTE is implemented. DC CIVAOC , if FEAT_OCCMO is implemented. DC CIGDVAOC , if FEAT_OCCMO is implemented. If the Point of Coherence is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| DCCVADP       |     9:9 |    1 | Trap execution of any of the following AArch64 instructions at EL1 and EL0 to EL2: DC CVADP . DC CGVADP , if FEAT_MTE is implemented. DC CGDVADP , if FEAT_MTE is implemented. If the Point of Deep Persistence is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| DCCVAP        |     8:8 |    1 | Trap execution of any of the following AArch64 instructions at EL1 and EL0 to EL2: DC CVAP . DC CGVAP , if FEAT_MTE is implemented. DC CGDVAP , if FEAT_MTE is implemented. If the Point of Persistence is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| DCCVAU        |     7:7 |    1 | Trap execution of DC CVAU at EL1 and EL0 using AArch64 to EL2. If the Point of Unification is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| DCCISW        |     6:6 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: DC CISW . DC CIGSW , if FEAT_MTE2 is implemented. DC CIGDSW , if FEAT_MTE2 is implemented.
| DCCSW         |     5:5 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: DC CSW . DC CGSW , if FEAT_MTE2 is implemented. DC CGDSW , if FEAT_MTE2 is implemented.
| DCISW         |     4:4 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: DC ISW . DC IGSW , if FEAT_MTE2 is implemented. DC IGDSW , if FEAT_MTE2 is implemented.
| DCIVAC        |     3:3 |    1 | Trap execution of any of the following AArch64 instructions at EL1  to EL2: DC IVAC . DC IGVAC , if FEAT_MTE2 is implemented. DC IGDVAC , if FEAT_MTE2 is implemented. If the Point of Coherence is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| ICIVAU        |     2:2 |    1 | Trap execution of IC IVAU at EL1 and EL0 using AArch64 to EL2. If the Point of Unification is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| ICIALLU       |     1:1 |    1 | Trap execution of IC IALLU at EL1  using AArch64 to EL2. If the Point of Unification is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.
| ICIALLUIS     |     0:0 |    1 | Trap execution of IC IALLUIS at EL1  using AArch64 to EL2. If the Point of Unification is before any level of data cache, it is IMPLEMENTATION DEFINED whether the execution of the affected instruction is trapped when the value of this control is 1.

## HFGRTR2_EL2 bitfields

| Bitfield         | msb:lsb | Size | Description
| ---------------- | ------: | ---: | -----------
| nACTLRALIAS_EL1  |   14:14 |    1 | Trap MRS reads of ACTLRALIAS_EL1 at EL1 using AArch64 to EL2.
| nACTLRMASK_EL1   |   13:13 |    1 | Trap MRS reads of ACTLRMASK_EL1 at EL1 using AArch64 to EL2.
| nTCR2ALIAS_EL1   |   12:12 |    1 | Trap MRS reads of TCR2ALIAS_EL1 at EL1 using AArch64 to EL2.
| nTCRALIAS_EL1    |   11:11 |    1 | Trap MRS reads of TCRALIAS_EL1 at EL1 using AArch64 to EL2.
| nSCTLRALIAS2_EL1 |   10:10 |    1 | Trap MRS reads of SCTLRALIAS2_EL1 at EL1 using AArch64 to EL2.
| nSCTLRALIAS_EL1  |     9:9 |    1 | Trap MRS reads of SCTLRALIAS_EL1 at EL1 using AArch64 to EL2.
| nCPACRALIAS_EL1  |     8:8 |    1 | Trap MRS reads of CPACRALIAS_EL1 at EL1 using AArch64 to EL2.
| nTCR2MASK_EL1    |     7:7 |    1 | Trap MRS reads of TCR2MASK_EL1 at EL1 using AArch64 to EL2.
| nTCRMASK_EL1     |     6:6 |    1 | Trap MRS reads of TCRMASK_EL1 at EL1 using AArch64 to EL2.
| nSCTLR2MASK_EL1  |     5:5 |    1 | Trap MRS reads of SCTLR2MASK_EL1 at EL1 using AArch64 to EL2.
| nSCTLRMASK_EL1   |     4:4 |    1 | Trap MRS reads of SCTLRMASK_EL1 at EL1 using AArch64 to EL2.
| nCPACRMASK_EL1   |     3:3 |    1 | Trap MRS reads of CPACRMASK_EL1 at EL1 using AArch64 to EL2.
| nRCWSMASK_EL1    |     2:2 |    1 | Trap MRS or MRRS reads of RCWSMASK_EL1 at EL1 using AArch64 to EL2.
| nERXGSR_EL1      |     1:1 |    1 | Trap MRS reads of ERXGSR_EL1 at EL1 using AArch64 to EL2.
| nPFAR_EL1        |     0:0 |    1 | Trap MRS reads of PFAR_EL1 at EL1 using AArch64 to EL2.

## HFGRTR_EL2 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| nAMAIR2_EL1     |   63:63 |    1 | Trap MRS reads of AMAIR2_EL1 at EL1 using AArch64 to EL2.
| nMAIR2_EL1      |   62:62 |    1 | Trap MRS reads of MAIR2_EL1 at EL1 using AArch64 to EL2.
| nS2POR_EL1      |   61:61 |    1 | Trap MRS reads of S2POR_EL1 at EL1 using AArch64 to EL2.
| nPOR_EL1        |   60:60 |    1 | Trap MRS reads of POR_EL1 at EL1 using AArch64 to EL2.
| nPOR_EL0        |   59:59 |    1 | Trap MRS reads of POR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPIR_EL1        |   58:58 |    1 | Trap MRS reads of PIR_EL1 at EL1 using AArch64 to EL2.
| nPIRE0_EL1      |   57:57 |    1 | Trap MRS reads of PIRE0_EL1 at EL1 using AArch64 to EL2.
| nRCWMASK_EL1    |   56:56 |    1 | Trap MRS or MRRS reads of RCWMASK_EL1 at EL1 using AArch64 to EL2.
| nTPIDR2_EL0     |   55:55 |    1 | Trap MRS reads of TPIDR2_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSMPRI_EL1      |   54:54 |    1 | Trap MRS reads of SMPRI_EL1 at EL1 using AArch64 to EL2.
| nGCS_EL1        |   53:53 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: GCSCR_EL1 . GCSPR_EL1 .
| nGCS_EL0        |   52:52 |    1 | Trap MRS reads at EL1 and EL0 using AArch64 of any of the following AArch64 System registers to EL2: GCSCRE0_EL1 , at EL1 only. GCSPR_EL0 .
| nACCDATA_EL1    |   50:50 |    1 | Trap MRS reads of ACCDATA_EL1 at EL1 using AArch64 to EL2.
| ERXADDR_EL1     |   49:49 |    1 | Trap MRS reads of ERXADDR_EL1 at EL1 using AArch64 to EL2.
| ERXPFGCDN_EL1   |   48:48 |    1 | Trap MRS reads of ERXPFGCDN_EL1 at EL1 using AArch64 to EL2.
| ERXPFGCTL_EL1   |   47:47 |    1 | Trap MRS reads of ERXPFGCTL_EL1 at EL1 using AArch64 to EL2.
| ERXPFGF_EL1     |   46:46 |    1 | Trap MRS reads of ERXPFGF_EL1 at EL1 using AArch64 to EL2.
| ERXMISCn_EL1    |   45:45 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: ERXMISC0_EL1 . ERXMISC1_EL1 . ERXMISC2_EL1 . ERXMISC3_EL1 .
| ERXSTATUS_EL1   |   44:44 |    1 | Trap MRS reads of ERXSTATUS_EL1 at EL1 using AArch64 to EL2.
| ERXCTLR_EL1     |   43:43 |    1 | Trap MRS reads of ERXCTLR_EL1 at EL1 using AArch64 to EL2.
| ERXFR_EL1       |   42:42 |    1 | Trap MRS reads of ERXFR_EL1 at EL1 using AArch64 to EL2.
| ERRSELR_EL1     |   41:41 |    1 | Trap MRS reads of ERRSELR_EL1 at EL1 using AArch64 to EL2.
| ERRIDR_EL1      |   40:40 |    1 | Trap MRS reads of ERRIDR_EL1 at EL1 using AArch64 to EL2.
| ICC_IGRPENn_EL1 |   39:39 |    1 | Trap MRS reads of ICC_IGRPEN<n>_EL1 at EL1 using AArch64 to EL2.
| VBAR_EL1        |   38:38 |    1 | Trap MRS reads of VBAR_EL1 at EL1 using AArch64 to EL2.
| TTBR1_EL1       |   37:37 |    1 | Trap MRS or MRRS reads of TTBR1_EL1 at EL1 using AArch64 to EL2.
| TTBR0_EL1       |   36:36 |    1 | Trap MRS or MRRS reads of TTBR0_EL1 at EL1 using AArch64 to EL2.
| TPIDR_EL0       |   35:35 |    1 | Trap MRS reads of TPIDR_EL0 at EL1 and EL0 using AArch64 and MRC reads of TPIDRURW at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| TPIDRRO_EL0     |   34:34 |    1 | Trap MRS reads of TPIDRRO_EL0 at EL1 and EL0 using AArch64 and MRC reads of TPIDRURO at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| TPIDR_EL1       |   33:33 |    1 | Trap MRS reads of TPIDR_EL1 at EL1 using AArch64 to EL2.
| TCR_EL1         |   32:32 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: TCR_EL1 . TCR2_EL1 , if FEAT_TCR2 is implemented.
| SCXTNUM_EL0     |   31:31 |    1 | Trap MRS reads of SCXTNUM_EL0 at EL1 and EL0 using AArch64 to EL2.
| SCXTNUM_EL1     |   30:30 |    1 | Trap MRS reads of SCXTNUM_EL1 at EL1 using AArch64 to EL2.
| SCTLR_EL1       |   29:29 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: SCTLR_EL1 . SCTLR2_EL1 , if FEAT_SCTLR2 is implemented.
| REVIDR_EL1      |   28:28 |    1 | Trap MRS reads of REVIDR_EL1 at EL1 using AArch64 to EL2.
| PAR_EL1         |   27:27 |    1 | Trap MRS or MRRS reads of PAR_EL1 at EL1 using AArch64 to EL2.
| MPIDR_EL1       |   26:26 |    1 | Trap MRS reads of MPIDR_EL1 at EL1 using AArch64 to EL2.
| MIDR_EL1        |   25:25 |    1 | Trap MRS reads of MIDR_EL1 at EL1 using AArch64 to EL2.
| MAIR_EL1        |   24:24 |    1 | Trap MRS reads of MAIR_EL1 at EL1 using AArch64 to EL2.
| LORSA_EL1       |   23:23 |    1 | Trap MRS reads of LORSA_EL1 at EL1 using AArch64 to EL2.
| LORN_EL1        |   22:22 |    1 | Trap MRS reads of LORN_EL1 at EL1 using AArch64 to EL2.
| LORID_EL1       |   21:21 |    1 | Trap MRS reads of LORID_EL1 at EL1 using AArch64 to EL2.
| LOREA_EL1       |   20:20 |    1 | Trap MRS reads of LOREA_EL1 at EL1 using AArch64 to EL2.
| LORC_EL1        |   19:19 |    1 | Trap MRS reads of LORC_EL1 at EL1 using AArch64 to EL2.
| ISR_EL1         |   18:18 |    1 | Trap MRS reads of ISR_EL1 at EL1 using AArch64 to EL2.
| FAR_EL1         |   17:17 |    1 | Trap MRS reads of FAR_EL1 at EL1 using AArch64 to EL2.
| ESR_EL1         |   16:16 |    1 | Trap MRS reads of ESR_EL1 at EL1 using AArch64 to EL2.
| DCZID_EL0       |   15:15 |    1 | Trap MRS reads of DCZID_EL0 at EL1 and EL0 using AArch64 to EL2.
| CTR_EL0         |   14:14 |    1 | Trap MRS reads of CTR_EL0 at EL1 and EL0 using AArch64 to EL2.
| CSSELR_EL1      |   13:13 |    1 | Trap MRS reads of CSSELR_EL1 at EL1 using AArch64 to EL2.
| CPACR_EL1       |   12:12 |    1 | Trap MRS reads of CPACR_EL1 at EL1 using AArch64 to EL2.
| CONTEXTIDR_EL1  |   11:11 |    1 | Trap MRS reads of CONTEXTIDR_EL1 at EL1 using AArch64 to EL2.
| CLIDR_EL1       |   10:10 |    1 | Trap MRS reads of CLIDR_EL1 at EL1 using AArch64 to EL2.
| CCSIDR_EL1      |     9:9 |    1 | Trap MRS reads of CCSIDR_EL1 at EL1 using AArch64 to EL2.
| APIBKey         |     8:8 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APIBKeyHi_EL1 . APIBKeyLo_EL1 .
| APIAKey         |     7:7 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APIAKeyHi_EL1 . APIAKeyLo_EL1 .
| APGAKey         |     6:6 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APGAKeyHi_EL1 . APGAKeyLo_EL1 .
| APDBKey         |     5:5 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APDBKeyHi_EL1 . APDBKeyLo_EL1 .
| APDAKey         |     4:4 |    1 | Trap MRS reads at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APDAKeyHi_EL1 . APDAKeyLo_EL1 .
| AMAIR_EL1       |     3:3 |    1 | Trap MRS reads of AMAIR_EL1 at EL1 using AArch64 to EL2.
| AIDR_EL1        |     2:2 |    1 | Trap MRS reads of AIDR_EL1 at EL1 using AArch64 to EL2.
| AFSR1_EL1       |     1:1 |    1 | Trap MRS reads of AFSR1_EL1 at EL1 using AArch64 to EL2.
| AFSR0_EL1       |     0:0 |    1 | Trap MRS reads of AFSR0_EL1 at EL1 using AArch64 to EL2.

## HFGWTR2_EL2 bitfields

| Bitfield         | msb:lsb | Size | Description
| ---------------- | ------: | ---: | -----------
| nACTLRALIAS_EL1  |   14:14 |    1 | Trap MSR writes of ACTLRALIAS_EL1 at EL1 using AArch64 to EL2.
| nACTLRMASK_EL1   |   13:13 |    1 | Trap MSR writes of ACTLRMASK_EL1 at EL1 using AArch64 to EL2.
| nTCR2ALIAS_EL1   |   12:12 |    1 | Trap MSR writes of TCR2ALIAS_EL1 at EL1 using AArch64 to EL2.
| nTCRALIAS_EL1    |   11:11 |    1 | Trap MSR writes of TCRALIAS_EL1 at EL1 using AArch64 to EL2.
| nSCTLRALIAS2_EL1 |   10:10 |    1 | Trap MSR writes of SCTLRALIAS2_EL1 at EL1 using AArch64 to EL2.
| nSCTLRALIAS_EL1  |     9:9 |    1 | Trap MSR writes of SCTLRALIAS_EL1 at EL1 using AArch64 to EL2.
| nCPACRALIAS_EL1  |     8:8 |    1 | Trap MSR writes of CPACRALIAS_EL1 at EL1 using AArch64 to EL2.
| nTCR2MASK_EL1    |     7:7 |    1 | Trap MSR writes of TCR2MASK_EL1 at EL1 using AArch64 to EL2.
| nTCRMASK_EL1     |     6:6 |    1 | Trap MSR writes of TCRMASK_EL1 at EL1 using AArch64 to EL2.
| nSCTLR2MASK_EL1  |     5:5 |    1 | Trap MSR writes of SCTLR2MASK_EL1 at EL1 using AArch64 to EL2.
| nSCTLRMASK_EL1   |     4:4 |    1 | Trap MSR writes of SCTLRMASK_EL1 at EL1 using AArch64 to EL2.
| nCPACRMASK_EL1   |     3:3 |    1 | Trap MSR writes of CPACRMASK_EL1 at EL1 using AArch64 to EL2.
| nRCWSMASK_EL1    |     2:2 |    1 | Trap MSR or MSRR writes of RCWSMASK_EL1 at EL1 using AArch64 to EL2.
| nPFAR_EL1        |     0:0 |    1 | Trap MSR writes of PFAR_EL1 at EL1 using AArch64 to EL2.

## HFGWTR_EL2 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| nAMAIR2_EL1     |   63:63 |    1 | Trap MSR writes of AMAIR2_EL1 at EL1 using AArch64 to EL2.
| nMAIR2_EL1      |   62:62 |    1 | Trap MSR writes of MAIR2_EL1 at EL1 using AArch64 to EL2.
| nS2POR_EL1      |   61:61 |    1 | Trap MSR writes of S2POR_EL1 at EL1 using AArch64 to EL2.
| nPOR_EL1        |   60:60 |    1 | Trap MSR writes of POR_EL1 at EL1 using AArch64 to EL2.
| nPOR_EL0        |   59:59 |    1 | Trap MSR writes of POR_EL0 at EL1 and EL0 using AArch64 to EL2.
| nPIR_EL1        |   58:58 |    1 | Trap MSR writes of PIR_EL1 at EL1 using AArch64 to EL2.
| nPIRE0_EL1      |   57:57 |    1 | Trap MSR writes of PIRE0_EL1 at EL1 using AArch64 to EL2.
| nRCWMASK_EL1    |   56:56 |    1 | Trap MSR or MSRR writes of RCWMASK_EL1 at EL1 using AArch64 to EL2.
| nTPIDR2_EL0     |   55:55 |    1 | Trap MSR writes of TPIDR2_EL0 at EL1 and EL0 using AArch64 to EL2.
| nSMPRI_EL1      |   54:54 |    1 | Trap MSR writes of SMPRI_EL1 at EL1 using AArch64 to EL2.
| nGCS_EL1        |   53:53 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: GCSCR_EL1 . GCSPR_EL1 .
| nGCS_EL0        |   52:52 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: GCSCRE0_EL1 . GCSPR_EL0 .
| nACCDATA_EL1    |   50:50 |    1 | Trap MSR writes of ACCDATA_EL1 at EL1 using AArch64 to EL2.
| ERXADDR_EL1     |   49:49 |    1 | Trap MSR writes of ERXADDR_EL1 at EL1 using AArch64 to EL2.
| ERXPFGCDN_EL1   |   48:48 |    1 | Trap MSR writes of ERXPFGCDN_EL1 at EL1 using AArch64 to EL2.
| ERXPFGCTL_EL1   |   47:47 |    1 | Trap MSR writes of ERXPFGCTL_EL1 at EL1 using AArch64 to EL2.
| ERXMISCn_EL1    |   45:45 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: ERXMISC0_EL1 . ERXMISC1_EL1 . ERXMISC2_EL1 . ERXMISC3_EL1 .
| ERXSTATUS_EL1   |   44:44 |    1 | Trap MSR writes of ERXSTATUS_EL1 at EL1 using AArch64 to EL2.
| ERXCTLR_EL1     |   43:43 |    1 | Trap MSR writes of ERXCTLR_EL1 at EL1 using AArch64 to EL2.
| ERRSELR_EL1     |   41:41 |    1 | Trap MSR writes of ERRSELR_EL1 at EL1 using AArch64 to EL2.
| ICC_IGRPENn_EL1 |   39:39 |    1 | Trap MSR writes of ICC_IGRPEN<n>_EL1 at EL1 using AArch64 to EL2.
| VBAR_EL1        |   38:38 |    1 | Trap MSR writes of VBAR_EL1 at EL1 using AArch64 to EL2.
| TTBR1_EL1       |   37:37 |    1 | Trap MSR or MSRR writes of TTBR1_EL1 at EL1 using AArch64 to EL2.
| TTBR0_EL1       |   36:36 |    1 | Trap MSR or MSRR writes of TTBR0_EL1 at EL1 using AArch64 to EL2.
| TPIDR_EL0       |   35:35 |    1 | Trap MSR writes of TPIDR_EL0 at EL1 and EL0 using AArch64 and MCR writes of TPIDRURW at EL0 using AArch32 when EL1 is using AArch64 to EL2.
| TPIDRRO_EL0     |   34:34 |    1 | Trap MSR writes of TPIDRRO_EL0 at EL1 using AArch64 to EL2.
| TPIDR_EL1       |   33:33 |    1 | Trap MSR writes of TPIDR_EL1 at EL1 using AArch64 to EL2.
| TCR_EL1         |   32:32 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: TCR_EL1 . TCR2_EL1 , if FEAT_TCR2 is implemented.
| SCXTNUM_EL0     |   31:31 |    1 | Trap MSR writes of SCXTNUM_EL0 at EL1 and EL0 using AArch64 to EL2.
| SCXTNUM_EL1     |   30:30 |    1 | Trap MSR writes of SCXTNUM_EL1 at EL1 using AArch64 to EL2.
| SCTLR_EL1       |   29:29 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: SCTLR_EL1 . SCTLR2_EL1 , if FEAT_SCTLR2 is implemented.
| PAR_EL1         |   27:27 |    1 | Trap MSR or MSRR writes of PAR_EL1 at EL1 using AArch64 to EL2.
| MAIR_EL1        |   24:24 |    1 | Trap MSR writes of MAIR_EL1 at EL1 using AArch64 to EL2.
| LORSA_EL1       |   23:23 |    1 | Trap MSR writes of LORSA_EL1 at EL1 using AArch64 to EL2.
| LORN_EL1        |   22:22 |    1 | Trap MSR writes of LORN_EL1 at EL1 using AArch64 to EL2.
| LOREA_EL1       |   20:20 |    1 | Trap MSR writes of LOREA_EL1 at EL1 using AArch64 to EL2.
| LORC_EL1        |   19:19 |    1 | Trap MSR writes of LORC_EL1 at EL1 using AArch64 to EL2.
| FAR_EL1         |   17:17 |    1 | Trap MSR writes of FAR_EL1 at EL1 using AArch64 to EL2.
| ESR_EL1         |   16:16 |    1 | Trap MSR writes of ESR_EL1 at EL1 using AArch64 to EL2.
| CSSELR_EL1      |   13:13 |    1 | Trap MSR writes of CSSELR_EL1 at EL1 using AArch64 to EL2.
| CPACR_EL1       |   12:12 |    1 | Trap MSR writes of CPACR_EL1 at EL1 using AArch64 to EL2.
| CONTEXTIDR_EL1  |   11:11 |    1 | Trap MSR writes of CONTEXTIDR_EL1 at EL1 using AArch64 to EL2.
| APIBKey         |     8:8 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APIBKeyHi_EL1 . APIBKeyLo_EL1 .
| APIAKey         |     7:7 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APIAKeyHi_EL1 . APIAKeyLo_EL1 .
| APGAKey         |     6:6 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APGAKeyHi_EL1 . APGAKeyLo_EL1 .
| APDBKey         |     5:5 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APDBKeyHi_EL1 . APDBKeyLo_EL1 .
| APDAKey         |     4:4 |    1 | Trap MSR writes at EL1 using AArch64 of any of the following AArch64 System registers to EL2: APDAKeyHi_EL1 . APDAKeyLo_EL1 .
| AMAIR_EL1       |     3:3 |    1 | Trap MSR writes of AMAIR_EL1 at EL1 using AArch64 to EL2.
| AFSR1_EL1       |     1:1 |    1 | Trap MSR writes of AFSR1_EL1 at EL1 using AArch64 to EL2.
| AFSR0_EL1       |     0:0 |    1 | Trap MSR writes of AFSR0_EL1 at EL1 using AArch64 to EL2.

## HPFAR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NS       |   63:63 |    1 | Faulting IPA address space.
| FIPA     |    47:4 |   44 |

## HSTR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| T<n>     |   15:15 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T15      |   15:15 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T13      |   13:13 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T12      |   12:12 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T11      |   11:11 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T10      |   10:10 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T9       |     9:9 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T8       |     8:8 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T7       |     7:7 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T6       |     6:6 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T5       |     5:5 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T3       |     3:3 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T2       |     2:2 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T1       |     1:1 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .
| T0       |     0:0 |    1 | The remaining fields control whether EL0 and EL1 accesses, using MCR, MRC, MCRR, and MRRC instructions, to the System registers in the coproc == 0b1111 encoding space, are trapped to EL2 as follows: MCR or MRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x03 , unless the access is UNDEFINED . MCRR or MRRC accesses to these registers that are trapped to EL2 are reported using EC syndrome value 0x04 , unless the access is UNDEFINED .

## ICC_ASGI1R_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| Aff3       |   55:48 |    8 | The affinity 3 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| RS         |   47:44 |    4 | RangeSelector Controls which group of 16 values is represented by the TargetList field. TargetList[n] represents aff0 value ((RS * 16) + n). When ICC_CTLR_EL1 .RSS==0, RS is RES0 . When ICC_CTLR_EL1 .RSS==1 and GICD_TYPER .RSS==0, writing this register with RS != 0 is a CONSTRAINED UNPREDICTABLE choice of: The write is ignored. The RS field is treated as 0.
| IRM        |   40:40 |    1 | Interrupt Routing Mode. Determines how the generated interrupts are distributed to PEs. Possible values are:
| Aff2       |   39:32 |    8 | The affinity 2 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| INTID      |   27:24 |    4 | The INTID of the SGI.
| Aff1       |   23:16 |    8 | The affinity 1 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| TargetList |    15:0 |   16 | Target List. The set of PEs for which SGI interrupts will be generated. Each bit corresponds to the PE within a cluster with an Affinity 0 value equal to the bit number. If SRE is set only for EL3, software executing at EL3 might use the System register interface to generate SGIs. Therefore, the Distributor must always be able to receive and acknowledge Generate SGI packets received from CPU interface regardless of the ARE settings for a Security state. However, the Distributor might discard such packets. If the IRM bit is 1, this field is RES0 .

## ICC_BPR0_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BinaryPoint |     2:0 |    3 | The value of this field controls how the 8-bit interrupt priority field is split into a group priority field, that determines interrupt preemption, and a subpriority field. This is done as follows: Binary point value Group priority field Subpriority field Field with binary point 0 [7:1] [0] ggggggg.s 1 [7:2] [1:0] gggggg.ss 2 [7:3] [2:0] ggggg.sss 3 [7:4] [3:0] gggg.ssss 4 [7:5] [4:0] ggg.sssss 5 [7:6] [5:0] gg.ssssss 6 [7] [6:0] g.sssssss 7 No preemption [7:0] .ssssssss

## ICC_BPR1_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BinaryPoint |     2:0 |    3 | If the GIC is configured to use separate binary point fields for Group 0 and Group 1 interrupts, the value of this field controls how the 8-bit interrupt priority field is split into a group priority field, that determines interrupt preemption, and a subpriority field. For more information about priorities, see 'Priority grouping' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . The minimum value of the Non-secure copy of this register is the minimum value of ICC_BPR0_EL1 + 1. The minimum value of the Secure copy of this register is the minimum value of ICC_BPR0_EL1 . If EL3 is implemented and ICC_CTLR_EL3 .CBPR_EL1S is 1: Accesses to this register from Secure EL2 access the state of ICC_BPR0_EL1 . Accesses to this register from Secure EL1: When SCR_EL3 .EEL2 is 1 and HCR_EL2 .IMO is 1, access the state of ICV_BPR1_EL1 . Otherwise, access the state of ICC_BPR0_EL1 . If EL3 is implemented and ICC_CTLR_EL3 .CBPR_EL1NS is 1, Non-secure accesses to this register at EL1 and EL2 behave as follows, depending on the values of HCR_EL2 .IMO and SCR_EL3 .IRQ: HCR_EL2.IMO SCR_EL3.IRQ Behavior 0b0 0b0 Non-secure EL1 and EL2 reads return ICC_BPR0_EL1 + 1 saturated to 0b111 . Non-secure EL1 and EL2 writes are ignored. 0b0 0b1 Non-secure EL1 and EL2 accesses trap to EL3. 0b1 0b0 Non-secure EL1 accesses affect virtual interrupts. Non-secure EL2 reads return ICC_BPR0_EL1 + 1 saturated to 0b111 . Non-secure EL2 writes are ignored. 0b1 0b1 Non-secure EL1 accesses affect virtual interrupts. Non-secure EL2 accesses trap to EL3. If EL3 is not implemented and ICC_CTLR_EL1 .CBPR is 1, Non-secure accesses to this register at EL1 and EL2 behave as follows, depending on the values of HCR_EL2 .IMO: HCR_EL2.IMO Behavior 0b0 Non-secure EL1 and EL2 reads return ICC_BPR0_EL1 + 1 saturated to 0b111 . Non-secure EL1 and EL2 writes are ignored. 0b1 Non-secure EL1 accesses affect virtual interrupts. Non-secure EL2 reads return ICC_BPR0_EL1 + 1 saturated to 0b111 . Non-secure EL2 writes are ignored.

## ICC_CTLR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ExtRange |   19:19 |    1 | Extended INTID range (read-only).
| RSS      |   18:18 |    1 | Range Selector Support. Possible values are:
| A3V      |   15:15 |    1 | Affinity 3 Valid. Read-only and writes are ignored. Possible values are:
| SEIS     |   14:14 |    1 | SEI Support. Read-only and writes are ignored. Indicates whether the CPU interface supports local generation of SEIs:
| IDbits   |   13:11 |    3 | Identifier bits. Read-only and writes are ignored. The number of physical interrupt identifier bits supported:
| PRIbits  |    10:8 |    3 | Priority bits. Read-only and writes are ignored. The number of priority bits implemented, minus one. An implementation that supports two Security states must implement at least 32 levels of physical priority (5 priority bits). An implementation that supports only a single Security state must implement at least 16 levels of physical priority (4 priority bits). This field always returns the number of priority bits implemented, regardless of the Security state of the access or the value of GICD_CTLR .DS. For physical accesses, this field determines the minimum value of ICC_BPR0_EL1 . If EL3 is implemented, physical accesses return the value from ICC_CTLR_EL3 .PRIbits. If EL3 is not implemented, physical accesses return the value from this field.
| PMHE     |     6:6 |    1 | Priority Mask Hint Enable. Controls whether the priority mask register is used as a hint for interrupt distribution:
| EOImode  |     1:1 |    1 | EOI mode for the current Security state. Controls whether a write to an End of Interrupt register also deactivates the interrupt:
| CBPR     |     0:0 |    1 | Common Binary Point Register. Controls whether the same register is used for interrupt preemption of both Group 0 and Group 1 interrupts:

## ICC_CTLR_EL3 bitfields

| Bitfield      | msb:lsb | Size | Description
| ------------- | ------: | ---: | -----------
| ExtRange      |   19:19 |    1 | Extended INTID range (read-only).
| RSS           |   18:18 |    1 | Range Selector Support.
| nDS           |   17:17 |    1 | Disable Security not supported. Read-only and writes are ignored.
| A3V           |   15:15 |    1 | Affinity 3 Valid. Read-only and writes are ignored.
| SEIS          |   14:14 |    1 | SEI Support. Read-only and writes are ignored. Indicates whether the CPU interface supports generation of SEIs:
| IDbits        |   13:11 |    3 | Identifier bits. Read-only and writes are ignored. Indicates the number of physical interrupt identifier bits supported.
| PRIbits       |    10:8 |    3 | Priority bits. Read-only and writes are ignored. The number of priority bits implemented, minus one. An implementation that supports two Security states must implement at least 32 levels of physical priority (5 priority bits). An implementation that supports only a single Security state must implement at least 16 levels of physical priority (4 priority bits). This field always returns the number of priority bits implemented, regardless of the value of SCR_EL3 .NS or the value of GICD_CTLR .DS. The division between group priority and subpriority is defined in the binary point registers ICC_BPR0_EL1 and ICC_BPR1_EL1 . This field determines the minimum value of ICC_BPR0_EL1.
| PMHE          |     6:6 |    1 | Priority Mask Hint Enable.
| RM            |     5:5 |    1 | Routing Modifier. This bit controls whether EL3 can acknowledge, or observe as the Highest Priority Pending Interrupt, Secure Group 0 and Non-secure Group 1 interrupts.
| EOImode_EL1NS |     4:4 |    1 | EOI mode for interrupts handled at Non-secure EL1 and EL2. Controls whether a write to an End of Interrupt register also deactivates the interrupt.
| EOImode_EL1S  |     3:3 |    1 | EOI mode for interrupts handled at Secure EL1 and EL2. Controls whether a write to an End of Interrupt register also deactivates the interrupt.
| EOImode_EL3   |     2:2 |    1 | EOI mode for interrupts handled at EL3. Controls whether a write to an End of Interrupt register also deactivates the interrupt.
| CBPR_EL1NS    |     1:1 |    1 | Common Binary Point Register, EL1 Non-secure. Controls whether the same register is used for interrupt preemption of both Group 0 and Group 1 Non-secure interrupts at EL1 and EL2.
| CBPR_EL1S     |     0:0 |    1 | Common Binary Point Register, EL1 Secure. Controls whether the same register is used for interrupt preemption of both Group 0 and Group 1 Secure interrupts at EL1 and EL2.

## ICC_DIR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the interrupt to be deactivated. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_EOIR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID from the corresponding ICC_IAR0_EL1 access. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 . If the EOImode bit for the current Exception level and Security state is 0, a write to this register drops the priority for the interrupt, and also deactivates the interrupt. If the EOImode bit for the current Exception level and Security state is 1, a write to this register only drops the priority for the interrupt. Software must write to ICC_DIR_EL1 to deactivate the interrupt. The EOImode bit for the current Exception level and Security state is determined as follows: If EL3 is not implemented, the appropriate bit is ICC_CTLR_EL1 .EOIMode. If EL3 is implemented and the software is executing at EL3, the appropriate bit is ICC_CTLR_EL3 .EOImode_EL3. If EL3 is implemented and the software is not executing at EL3, the bit depends on the current Security state: If the software is executing in Secure state, the bit is ICC_CTLR_EL3 .EOImode_EL1S. If the software is executing in Non-secure state, the bit is ICC_CTLR_EL3 .EOImode_EL1NS.

## ICC_EOIR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID from the corresponding ICC_IAR1_EL1 access. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 . If the EOImode bit for the current Exception level and Security state is 0, a write to this register drops the priority for the interrupt, and also deactivates the interrupt. If the EOImode bit for the current Exception level and Security state is 1, a write to this register only drops the priority for the interrupt. Software must write to ICC_DIR_EL1 to deactivate the interrupt. The EOImode bit for the current Exception level and Security state is determined as follows: If EL3 is not implemented, the appropriate bit is ICC_CTLR_EL1 .EOIMode. If EL3 is implemented and the software is executing at EL3, the appropriate bit is ICC_CTLR_EL3 .EOImode_EL3. If EL3 is implemented and the software is not executing at EL3, the bit depends on the current Security state: If the software is executing in Secure state, the bit is ICC_CTLR_EL3 .EOImode_EL1S. If the software is executing in Non-secure state, the bit is ICC_CTLR_EL3 .EOImode_EL1NS.

## ICC_HPPIR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the highest priority pending interrupt, if that interrupt is observable at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. These special INTIDs can be one of: 1020, 1021, or 1023. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_HPPIR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the highest priority pending interrupt, if that interrupt is observable at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. These special INTIDs can be one of: 1020, 1021, or 1023. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_IAR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled interrupt. This is the INTID of the highest priority pending interrupt, if that interrupt is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_IAR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled interrupt. This is the INTID of the highest priority pending interrupt, if that interrupt is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_IGRPEN0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     0:0 |    1 | Enables Group 0 interrupts.

## ICC_IGRPEN1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     0:0 |    1 | Enables Group 1 interrupts for the current Security state.

## ICC_IGRPEN1_EL3 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| EnableGrp1S  |     1:1 |    1 | Enables Group 1 interrupts for the Secure state.
| EnableGrp1NS |     0:0 |    1 | Enables Group 1 interrupts for the Non-secure state.

## ICC_NMIAR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled interrupt. This is the INTID of the highest priority pending interrupt, if that interrupt has the Non-maskable property and is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICC_CTLR_EL1 .IDbits and ICC_CTLR_EL3 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICC_PMR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Priority |     7:0 |    8 | The priority mask level for the CPU interface. If the priority of an interrupt is higher than the value indicated by this field, the interface signals the interrupt to the PE. The possible priority field values are as follows: Implemented priority bits Possible priority field values Number of priority levels [7:0] 0x00 - 0xFF (0-255), all values 256 [7:1] 0x00 - 0xFE (0-254), even values only 128 [7:2] 0x00 - 0xFC (0-252), in steps of 4 64 [7:3] 0x00 - 0xF8 (0-248), in steps of 8 32 [7:4] 0x00 - 0xF0 (0-240), in steps of 16 16 Unimplemented priority bits are RAZ/WI.

## ICC_RPR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NMI      |   63:63 |    1 | Indicates whether the running priority is from a NMI.
| NMI_NS   |   62:62 |    1 | Indicates whether the running priority is from a Non-secure Group 1 NMI.
| Priority |     7:0 |    8 | The current running priority on the CPU interface. This is the group priority of the current active interrupt. The group priority of a Secure NMI, or NMI when GICD_CTLR.DS is 1, is 0x00 . The group priority of a Non-secure NMI is 0x80 , saturated to 0x00 for Non-secure reads. If there are no active interrupts on the CPU interface, or all active interrupts have undergone a priority drop, the value returned is the Idle priority. The priority returned is the group priority as if the BPR for the current Exception level and Security state was set to the minimum value of BPR for the number of implemented priority bits. If 8 bits of priority are implemented the group priority is bits[7:1] of the priority.

## ICC_SGI0R_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| Aff3       |   55:48 |    8 | The affinity 3 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| RS         |   47:44 |    4 | RangeSelector Controls which group of 16 values is represented by the TargetList field. TargetList[n] represents aff0 value ((RS * 16) + n). When ICC_CTLR_EL1 .RSS==0, RS is RES0 . When ICC_CTLR_EL1 .RSS==1 and GICD_TYPER .RSS==0, writing this register with RS != 0 is a CONSTRAINED UNPREDICTABLE choice of: The write is ignored. The RS field is treated as 0.
| IRM        |   40:40 |    1 | Interrupt Routing Mode. Determines how the generated interrupts are distributed to PEs. Possible values are:
| Aff2       |   39:32 |    8 | The affinity 2 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| INTID      |   27:24 |    4 | The INTID of the SGI.
| Aff1       |   23:16 |    8 | The affinity 1 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| TargetList |    15:0 |   16 | Target List. The set of PEs for which SGI interrupts will be generated. Each bit corresponds to the PE within a cluster with an Affinity 0 value equal to the bit number. If SRE is set only for EL3, software executing at EL3 might use the System register interface to generate SGIs. Therefore, the Distributor must always be able to receive and acknowledge Generate SGI packets received from CPU interface regardless of the ARE settings for a Security state. However, the Distributor might discard such packets. If the IRM bit is 1, this field is RES0 .

## ICC_SGI1R_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| Aff3       |   55:48 |    8 | The affinity 3 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| RS         |   47:44 |    4 | RangeSelector Controls which group of 16 values is represented by the TargetList field. TargetList[n] represents aff0 value ((RS * 16) + n). When ICC_CTLR_EL1 .RSS==0, RS is RES0 . When ICC_CTLR_EL1 .RSS==1 and GICD_TYPER .RSS==0, writing this register with RS != 0 is a CONSTRAINED UNPREDICTABLE choice of: The write is ignored. The RS field is treated as 0.
| IRM        |   40:40 |    1 | Interrupt Routing Mode. Determines how the generated interrupts are distributed to PEs. Possible values are:
| Aff2       |   39:32 |    8 | The affinity 2 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| INTID      |   27:24 |    4 | The INTID of the SGI.
| Aff1       |   23:16 |    8 | The affinity 1 value of the affinity path of the cluster for which SGI interrupts will be generated. If the IRM bit is 1, this field is RES0 .
| TargetList |    15:0 |   16 | Target List. The set of PEs for which SGI interrupts will be generated. Each bit corresponds to the PE within a cluster with an Affinity 0 value equal to the bit number. If SRE is set only for EL3, software executing at EL3 might use the System register interface to generate SGIs. Therefore, the Distributor must always be able to receive and acknowledge Generate SGI packets received from CPU interface regardless of the ARE settings for a Security state. However, the Distributor might discard such packets. If the IRM bit is 1, this field is RES0 .

## ICC_SRE_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DIB      |     2:2 |    1 | Disable IRQ bypass.
| DFB      |     1:1 |    1 | Disable FIQ bypass.
| SRE      |     0:0 |    1 | System Register Enable.

## ICC_SRE_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     3:3 |    1 | Enable. Enables lower Exception level access to ICC_SRE_EL1 .
| DIB      |     2:2 |    1 | Disable IRQ bypass.
| DFB      |     1:1 |    1 | Disable FIQ bypass.
| SRE      |     0:0 |    1 | System Register Enable.

## ICC_SRE_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     3:3 |    1 | Enable. Enables lower Exception level access to ICC_SRE_EL1 and ICC_SRE_EL2 .
| DIB      |     2:2 |    1 | Disable IRQ bypass.
| DFB      |     1:1 |    1 | Disable FIQ bypass.
| SRE      |     0:0 |    1 | System Register Enable.

## ICH_EISR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| Status<n> |    15:0 |   16 | EOI maintenance interrupt status bit for List register <n>:

## ICH_ELRSR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| Status<n> |    15:0 |   16 | Status bit for List register <n>, ICH_LR<n>_EL2 :

## ICH_HCR_EL2 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| EOIcount     |   31:27 |    5 | This field is incremented whenever a successful write to a virtual EOIR or DIR register would have resulted in a virtual interrupt deactivation. That is either: A virtual write to EOIR with a valid interrupt identifier that is not in the LPI range (that is < 8192) when EOI mode is zero and no List Register was found. A virtual write to DIR with a valid interrupt identifier that is not in the LPI range (that is < 8192) when EOI mode is one and no List Register was found. This allows software to manage more active interrupts than there are implemented List Registers. It is CONSTRAINED UNPREDICTABLE whether a virtual write to EOIR that does not clear a bit in the Active Priorities registers ( ICH_AP0R<n>_EL2 / ICH_AP1R<n>_EL2 ) increments EOIcount. Permitted behaviors are: Increment EOIcount. Leave EOIcount unchanged.
| DVIM         |   15:15 |    1 | Directly-injected Virtual Interrupt Mask.
| TDIR         |   14:14 |    1 | Trap EL1 writes to ICC_DIR_EL1 and ICV_DIR_EL1 .
| TSEI         |   13:13 |    1 | Trap all locally generated SEIs. This bit allows the hypervisor to intercept locally generated SEIs that would otherwise be taken at EL1.
| TALL1        |   12:12 |    1 | Trap all EL1 accesses to ICC_* and ICV_* System registers for Group 1 interrupts to EL2.
| TALL0        |   11:11 |    1 | Trap all EL1 accesses to ICC_* and ICV_* System registers for Group 0 interrupts to EL2.
| TC           |   10:10 |    1 | Trap all EL1 accesses to System registers that are common to Group 0 and Group 1 to EL2.
| vSGIEOICount |     8:8 |    1 | Controls whether deactivation of virtual SGIs can increment ICH_HCR_EL2.EOIcount
| VGrp1DIE     |     7:7 |    1 | VM Group 1 Disabled Interrupt Enable. Enables the signaling of a maintenance interrupt while signaling of Group 1 interrupts from the virtual CPU interface to the connected vPE is disabled:
| VGrp1EIE     |     6:6 |    1 | VM Group 1 Enabled Interrupt Enable. Enables the signaling of a maintenance interrupt while signaling of Group 1 interrupts from the virtual CPU interface to the connected vPE is enabled:
| VGrp0DIE     |     5:5 |    1 | VM Group 0 Disabled Interrupt Enable. Enables the signaling of a maintenance interrupt while signaling of Group 0 interrupts from the virtual CPU interface to the connected vPE is disabled:
| VGrp0EIE     |     4:4 |    1 | VM Group 0 Enabled Interrupt Enable. Enables the signaling of a maintenance interrupt while signaling of Group 0 interrupts from the virtual CPU interface to the connected vPE is enabled:
| NPIE         |     3:3 |    1 | No Pending Interrupt Enable. Enables the signaling of a maintenance interrupt when there are no List registers with the State field set to 0b01 (pending):
| LRENPIE      |     2:2 |    1 | List Register Entry Not Present Interrupt Enable. Enables the signaling of a maintenance interrupt while the virtual CPU interface does not have a corresponding valid List register entry for an EOI request:
| UIE          |     1:1 |    1 | Underflow Interrupt Enable. Enables the signaling of a maintenance interrupt when the List registers are empty, or hold only one valid entry:
| En           |     0:0 |    1 | Enable. Global enable bit for the virtual CPU interface:

## ICH_MISR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VGrp1D   |     7:7 |    1 | vPE Group 1 Disabled.
| VGrp1E   |     6:6 |    1 | vPE Group 1 Enabled.
| VGrp0D   |     5:5 |    1 | vPE Group 0 Disabled.
| VGrp0E   |     4:4 |    1 | vPE Group 0 Enabled.
| NP       |     3:3 |    1 | No Pending.
| LRENP    |     2:2 |    1 | List Register Entry Not Present.
| U        |     1:1 |    1 | Underflow.
| EOI      |     0:0 |    1 | End Of Interrupt.

## ICH_VMCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VPMR     |   31:24 |    8 | Virtual Priority Mask. The priority mask level for the virtual CPU interface. If the priority of a pending virtual interrupt is higher than the value indicated by this field, the interface signals the virtual interrupt to the PE. This field is an alias of ICV_PMR_EL1 .Priority.
| VBPR0    |   23:21 |    3 | Virtual Binary Point Register, Group 0. Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 0 interrupt preemption, and also determines Group 1 interrupt preemption if ICH_VMCR_EL2.VCBPR == 1. This field is an alias of ICV_BPR0_EL1 .BinaryPoint. The minimum value of this field is determined by ICH_VTR_EL2 .PREbits. An attempt to program the binary point field to a value less than the minimum value sets the field to the minimum value.
| VBPR1    |   20:18 |    3 | Virtual Binary Point Register, Group 1. Defines the point at which the priority value fields split into two parts, the group priority field and the subpriority field. The group priority field determines Group 1 interrupt preemption if ICH_VMCR_EL2 .VCBPR == 0. This field is an alias of ICV_BPR1_EL1 .BinaryPoint. This field is always accessible to EL2 accesses, regardless of the setting of the ICH_VMCR_EL2.VCBPR field. For Non-secure writes, the minimum value of this field is the minimum value of ICH_VMCR_EL2.VBPR0 plus one. For Secure writes, the minimum value of this field is the minimum value of ICH_VMCR_EL2.VBPR0. An attempt to program the binary point field to a value less than the minimum value sets the field to the minimum value.
| VEOIM    |     9:9 |    1 | Virtual EOI mode. Controls whether a write to an End of Interrupt register also deactivates the virtual interrupt:
| VCBPR    |     4:4 |    1 | Virtual Common Binary Point Register. Possible values of this bit are:
| VFIQEn   |     3:3 |    1 | Virtual FIQ enable. Possible values of this bit are:
| VAckCtl  |     2:2 |    1 | Virtual AckCtl. Possible values of this bit are:
| VENG1    |     1:1 |    1 | Virtual Group 1 interrupt enable. Possible values of this bit are:
| VENG0    |     0:0 |    1 | Virtual Group 0 interrupt enable. Possible values of this bit are:

## ICH_VTR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PRIbits  |   31:29 |    3 | Priority bits. Indicates the number of virtual priority bits implemented, minus one. An implementation must implement at least 32 levels of virtual priority (5 priority bits). This field is an alias of ICV_CTLR_EL1 .PRIbits.
| PREbits  |   28:26 |    3 | Preemption bits. Indicates the number of virtual preemption bits implemented, minus one. An implementation must implement at least 32 levels of virtual preemption priority (5 preemption bits). The value of this field must be less than or equal to the value of ICH_VTR_EL2.PRIbits. This field determines the minimum value of ICH_VMCR_EL2 .VBPR0.
| IDbits   |   25:23 |    3 | The number of virtual interrupt identifier bits supported:
| SEIS     |   22:22 |    1 | SEI Support. Indicates whether the virtual CPU interface supports generation of SEIs:
| A3V      |   21:21 |    1 | Affinity 3 Valid.
| nV4      |   20:20 |    1 | Direct injection of virtual interrupts not supported.
| TDS      |   19:19 |    1 | Separate trapping of EL1 writes to ICV_DIR_EL1 supported.
| DVIM     |   18:18 |    1 | Masking of directly-injected virtual interrupts.
| ListRegs |     4:0 |    5 | List Registers. Indicates the number of List registers implemented, minus one.

## ICV_BPR0_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BinaryPoint |     2:0 |    3 | The value of this field controls how the 8-bit interrupt priority field is split into a group priority field, that determines interrupt preemption, and a subpriority field. This is done as follows: Binary point value Group priority field Subpriority field Field with binary point 0 [7:1] [0] ggggggg.s 1 [7:2] [1:0] gggggg.ss 2 [7:3] [2:0] ggggg.sss 3 [7:4] [3:0] gggg.ssss 4 [7:5] [4:0] ggg.sssss 5 [7:6] [5:0] gg.ssssss 6 [7] [6:0] g.sssssss 7 No preemption [7:0] .ssssssss

## ICV_BPR1_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BinaryPoint |     2:0 |    3 | If the GIC is configured to use separate binary point fields for Group 0 and Group 1 interrupts, the value of this field controls how the 8-bit interrupt priority field is split into a group priority field, that determines interrupt preemption, and a subpriority field. For more information about priorities, see 'Priority grouping' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . An attempt to program this field to a value less than the minimum value sets the field to the minimum value. If ICV_CTLR_EL1 .CBPR is set to 1, Non-secure EL1 reads return ICV_BPR0_EL1 + 1 saturated to 0b111 . Non-secure EL1 writes are ignored. If ICV_CTLR_EL1 .CBPR is set to 1, Secure EL1 reads return ICV_BPR0_EL1 . Secure EL1 writes modify ICV_BPR0_EL1 .

## ICV_CTLR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ExtRange |   19:19 |    1 | Extended INTID range (read-only).
| RSS      |   18:18 |    1 | Range Selector Support.
| A3V      |   15:15 |    1 | Affinity 3 Valid. Read-only and writes are ignored.
| SEIS     |   14:14 |    1 | SEI Support. Read-only and writes are ignored. Indicates whether the virtual CPU interface supports local generation of SEIs.
| IDbits   |   13:11 |    3 | Identifier bits. Read-only and writes are ignored. Indicates the number of virtual interrupt identifier bits supported.
| PRIbits  |    10:8 |    3 | Indicates the number of virtual priority bits implemented. An implementation must implement at least 32 levels of virtual priority (5 priority bits). The division between group priority and subpriority is defined in the binary point registers ICV_BPR0_EL1 and ICV_BPR1_EL1 .
| EOImode  |     1:1 |    1 | Virtual EOI mode. Controls whether a write to an End of Interrupt register also deactivates the virtual interrupt:
| CBPR     |     0:0 |    1 | Common Binary Point Register. Controls whether the same register is used for interrupt preemption of both virtual Group 0 and virtual Group 1 interrupts:

## ICV_DIR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the virtual interrupt to be deactivated. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_EOIR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID from the corresponding ICV_IAR0_EL1 access. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 . If the ICV_CTLR_EL1 .EOImode bit is 0, a write to this register drops the priority for the virtual interrupt, and also deactivates the virtual interrupt. If the ICV_CTLR_EL1 .EOImode bit is 1, a write to this register only drops the priority for the virtual interrupt. Software must write to ICV_DIR_EL1 to deactivate the virtual interrupt.

## ICV_EOIR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID from the corresponding ICV_IAR1_EL1 access. This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 . If the ICV_CTLR_EL1 .EOImode bit is 0, a write to this register drops the priority for the virtual interrupt, and also deactivates the virtual interrupt. If the ICV_CTLR_EL1 .EOImode bit is 1, a write to this register only drops the priority for the virtual interrupt. Software must write to ICV_DIR_EL1 to deactivate the virtual interrupt.

## ICV_HPPIR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the highest priority pending virtual interrupt. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. This special INTID can take the value 1023 only. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_HPPIR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the highest priority pending virtual interrupt. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. This special INTID can take the value 1023 only. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_IAR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled virtual interrupt. This is the INTID of the highest priority pending virtual interrupt, if that interrupt is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_IAR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled virtual interrupt. This is the INTID of the highest priority pending virtual interrupt, if that interrupt is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_IGRPEN0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     0:0 |    1 | Enables virtual Group 0 interrupts.

## ICV_IGRPEN1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Enable   |     0:0 |    1 | Enables virtual Group 1 interrupts.

## ICV_NMIAR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTID    |    23:0 |   24 | The INTID of the signaled virtual interrupt. This is the INTID of the highest priority pending virtual interrupt, if that virtual interrupt has the Non-maskable property and is of sufficient priority for it to be signaled to the PE, and if it can be acknowledged at the current Security state and Exception level. If the highest priority pending interrupt is not observable, this field contains a special INTID to indicate the reason. For more information, see 'Special INTIDs' in ARM® Generic Interrupt Controller Architecture Specification, GIC architecture version 3.0 and version 4.0 (ARM IHI 0069) . This field has either 16 or 24 bits implemented. The number of implemented bits can be found in ICV_CTLR_EL1 .IDbits. If only 16 bits are implemented, bits [23:16] of this register are RES0 .

## ICV_PMR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Priority |     7:0 |    8 | The priority mask level for the virtual CPU interface. If the priority of a virtual interrupt is higher than the value indicated by this field, the interface signals the virtual interrupt to the PE. The possible priority field values are as follows: Implemented priority bits Possible priority field values Number of priority levels [7:0] 0x00 - 0xFF (0-255), all values 256 [7:1] 0x00 - 0xFE (0-254), even values only 128 [7:2] 0x00 - 0xFC (0-252), in steps of 4 64 [7:3] 0x00 - 0xF8 (0-248), in steps of 8 32 [7:4] 0x00 - 0xF0 (0-240), in steps of 16 16 Unimplemented priority bits are RAZ/WI.

## ICV_RPR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NMI      |   63:63 |    1 | Indicates whether the running priority is from a NMI.
| Priority |     7:0 |    8 | The current running priority on the virtual CPU interface. This is the group priority of the current active virtual interrupt. If there are no active interrupts on the virtual CPU interface, or all active interrupts have undergone a priority drop, the value returned is the Idle priority. The priority returned is the group priority as if the BPR for the current Exception level and Security state was set to the minimum value of BPR for the number of implemented priority bits. If 8 bits of priority are implemented the group priority is bits[7:1] of the priority.

## ID_AA64AFR0_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| IMPLEMENTATION DEFINED |   31:28 |    4 | IMPLEMENTATION DEFINED .

## ID_AA64DFR0_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| HPMN0       |   63:60 |    4 | Zero PMU event counters for a Guest operating system.
| ExtTrcBuff  |   59:56 |    4 | Trace Buffer External Mode Extension.
| BRBE        |   55:52 |    4 | Branch Record Buffer Extension.
| MTPMU       |   51:48 |    4 | Multi-threaded PMU extension.
| TraceBuffer |   47:44 |    4 | Trace Buffer Extension.
| TraceFilt   |   43:40 |    4 | Armv8.4 Self-hosted Trace Extension version.
| DoubleLock  |   39:36 |    4 | OS Double Lock implemented.
| PMSVer      |   35:32 |    4 | Statistical Profiling Extension version.
| CTX_CMPs    |   31:28 |    4 | Number of context-aware breakpoints, minus 1.
| SEBEP       |   27:24 |    4 | Synchronous-exception-based event profiling.
| WRPs        |   23:20 |    4 | Number of watchpoints, minus 1.
| PMSS        |   19:16 |    4 | PMU Snapshot extension.
| BRPs        |   15:12 |    4 | Number of breakpoints, minus 1.
| PMUVer      |    11:8 |    4 | Performance Monitors Extension version. This field does not follow the standard ID scheme, but uses the alternative ID scheme described in 'Alternative ID scheme used for the Performance Monitors Extension version' .
| TraceVer    |     7:4 |    4 | Trace support. Indicates whether System register interface to a trace unit is implemented.
| DebugVer    |     3:0 |    4 | Debug architecture version. Indicates presence of Armv8 debug architecture.

## ID_AA64DFR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ABL_CMPs |   63:56 |    8 | Number of breakpoints that support address linking, minus 1.
| DPFZS    |   55:52 |    4 | Behavior of the cycle counter when event counting is frozen by a Statistical Profiling management event.
| EBEP     |   51:48 |    4 | Exception-based event profiling.
| ITE      |   47:44 |    4 | Instrumentation Trace Extension.
| ABLE     |   43:40 |    4 | Address Breakpoint Linking Extension.
| PMICNTR  |   39:36 |    4 | PMU fixed-function instruction counter.
| SPMU     |   35:32 |    4 | System PMU extension.
| CTX_CMPs |   31:24 |    8 | Context-aware breakpoints.
| WRPs     |   23:16 |    8 | Watchpoints.
| BRPs     |    15:8 |    8 | Breakpoints.
| SYSPMUID |     7:0 |    8 | System PMU ID. Indicates the largest value that can be written to SPMSELR_EL0 .SYSPMUSEL.

## ID_AA64DFR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TRBE_EXC |   27:24 |    4 | TRBE Profiling exception extension. Describes support for reporting trace buffer management events as TRBE Profiling exceptions.
| SPE_nVM  |   23:20 |    4 | Profiling Buffer physical address mode supported. Describes support for defining the Profiling Buffer using physical addresses or intermediate physical addresses.
| SPE_EXC  |   19:16 |    4 | SPE Profiling exception extension. Describes support for reporting Profiling Buffer management events as SPE Profiling exceptions.
| BWE      |     7:4 |    4 | Breakpoints and watchpoint enhancements.
| STEP     |     3:0 |    4 | Enhanced Software Step Extension.

## ID_AA64FPFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F8CVT    |   31:31 |    1 | Indicates support for the following instructions: The Advanced SIMD floating-point scaling instruction FSCALE . The Advanced SIMD FP8 convert instructions BF1CVTL , BF1CVTL2 , BF2CVTL , BF2CVTL2 , F1CVTL , F1CVTL2 , F2CVTL , F2CVTL2 , FCVTN , and FCVTN2 . When FEAT_SVE2 or FEAT_SME2 is implemented, the SVE2 FP8 convert instructions BF1CVT , BF1CVTLT , BF2CVT , BF2CVTLT , F1CVT , F1CVTLT , F2CVT , F2CVTLT , BFCVTN , FCVTN , FCVTNB , and FCVTNT . When FEAT_SME2 is implemented, the SME2 multi-vector floating-point scaling instruction FSCALE and the SME2 FP8 convert instructions BF1CVT , BF1CVTL , BF2CVT , BF2CVTL , F1CVT , F1CVTL , F2CVT , F2CVTL , BFCVT , FCVT , and FCVTN .
| F8FMA    |   30:30 |    1 | Indicates support for the following instructions: The Advanced SIMD FP8 to single-precision and half-precision multiply-accumulate instructions FMLALB , FMLALT , FMLALLBB , FMLALLBT , FMLALLTB , and FMLALLTT . When FEAT_SVE2 is implemented and the PE is not in Streaming SVE mode, the SVE2 FP8 to single-precision and half-precision multiply-accumulate instructions FMLALB , FMLALT , FMLALLBB , FMLALLBT , FMLALLTB , and FMLALLTT .
| F8DP4    |   29:29 |    1 | Indicates support for the following instructions: Advanced SIMD FP8 to single-precision 4-way dot product FDOT (4-way) instructions. When FEAT_SVE2 is implemented and the PE is not in Streaming SVE mode, SVE FP8 to single-precision 4-way dot product FDOT (4-way) instructions.
| F8DP2    |   28:28 |    1 | Indicates support for the following instructions: Advanced SIMD FP8 to half-precision 2-way dot product FDOT (2-way) instructions. When FEAT_SVE2 is implemented and the PE is not in Streaming SVE mode, SVE FP8 to half-precision 2-way dot product FDOT (2-way) instructions.
| F8MM8    |   27:27 |    1 | Indicates support for the following instructions: Advanced SIMD FP8 to single-precision matrix multiply FMMLA (8-way, FP8 to FP32) instruction. If FEAT_SVE2 is implemented, SVE FP8 to single-precision matrix multiply FMMLA (widening, FP8 to FP32) instruction is implemented when the PE is not in Streaming SVE mode.
| F8MM4    |   26:26 |    1 | Indicates support for the following instructions: Advanced SIMD FP8 to half-precision matrix multiply FMMLA (4-way, FP8 to FP16) instruction. If FEAT_SVE2 is implemented, SVE FP8 to half-precision matrix multiply FMMLA (widening, FP8 to FP16) instruction is implemented when the PE is not in Streaming SVE mode.
| F8E4M3   |     1:1 |    1 | Indicates support for OFP8 E4M3 format and behavior for FP8 instructions.
| F8E5M2   |     0:0 |    1 | Indicates support for OFP8 E5M2 format and behavior for FP8 instructions.

## ID_AA64ISAR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RNDR     |   63:60 |    4 | Indicates support for Random Number instructions in AArch64 state. When FEAT_RNG_TRAP is implemented, the value returned by a direct read of ID_AA64ISAR0_EL1.RNDR is further controlled by the value of SCR_EL3 .TRNDR.
| TLB      |   59:56 |    4 | Indicates support for Outer Shareable and TLB range maintenance instructions.
| TS       |   55:52 |    4 | Indicates support for flag manipulation instructions.
| FHM      |   51:48 |    4 | Indicates support for FMLAL and FMLSL instructions.
| DP       |   47:44 |    4 | Indicates support for Dot Product instructions in AArch64 state.
| SM4      |   43:40 |    4 | Indicates support for SM4 instructions in AArch64 state.
| SM3      |   39:36 |    4 | Indicates support for the following SM3 instructions SM3SS1 , SM3TT1A , SM3TT1B , SM3TT2A , SM3TT2B , SM3PARTW1 , and SM3PARTW2 in AArch64 state.
| SHA3     |   35:32 |    4 | Indicates support for the following  SHA3 instructions EOR3 , RAX1 , XAR , and BCAX in AArch64 state.
| RDM      |   31:28 |    4 | Indicates support for SQRDMLAH and SQRDMLSH instructions in AArch64 state.
| TME      |   27:24 |    4 | Indicates support for the following TME instructions TCANCEL , TCOMMIT , TSTART , and TTEST .
| Atomic   |   23:20 |    4 | Indicates support for Atomic instructions in AArch64 state.
| CRC32    |   19:16 |    4 | Indicates support for the following CRC32 instructions CRC32B , CRC32H , CRC32W , CRC32X , CRC32CB , CRC32CH , CRC32CW , and CRC32CX in AArch64 state.
| SHA2     |   15:12 |    4 | Indicates support for SHA2 instructions in AArch64 state.
| SHA1     |    11:8 |    4 | Indicates support for the following SHA1 instructions SHA1C , SHA1P , SHA1M , SHA1H , SHA1SU0 , and SHA1SU1 in AArch64 state.
| AES      |     7:4 |    4 | Indicates support for AES instructions in AArch64 state.

## ID_AA64ISAR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LS64     |   63:60 |    4 | Indicates support for LD64B and ST64B* instructions, and the ACCDATA_EL1 register.
| XS       |   59:56 |    4 | Indicates support for the XS attribute, the TLBI and DSB instructions with the nXS qualifier, and the HCRX_EL2 .{FGTnXS, FnXS} fields in AArch64 state.
| I8MM     |   55:52 |    4 | Indicates support for the following Advanced SIMD Int8 matrix multiplication instructions SMMLA , SUDOT , UMMLA , USMMLA , and USDOT in AArch64 state.
| DGH      |   51:48 |    4 | Indicates support for the Data Gathering Hint instruction.
| BF16     |   47:44 |    4 | Indicates support for Advanced SIMD and floating-point BFloat16 instructions in AArch64 state.
| SPECRES  |   43:40 |    4 | Indicates support for prediction invalidation instructions in AArch64 state.
| SB       |   39:36 |    4 | Indicates support for SB instruction in AArch64 state.
| FRINTTS  |   35:32 |    4 | Indicates support for FRINT32Z , FRINT32X , FRINT64Z , and FRINT64X instructions.
| GPI      |   31:28 |    4 | Indicates support for an IMPLEMENTATION DEFINED algorithm is implemented in the PE for generic code authentication in AArch64 state.
| GPA      |   27:24 |    4 | Indicates whether the QARMA5 algorithm is implemented in the PE for generic code authentication in AArch64 state.
| LRCPC    |   23:20 |    4 | Indicates support for weaker release consistency, RCpc, based model.
| FCMA     |   19:16 |    4 | Indicates support for complex number addition and multiplication, where numbers are stored in vectors.
| JSCVT    |   15:12 |    4 | Indicates support for JavaScript conversion from double-precision floating-point values to integers in AArch64 state.
| API      |    11:8 |    4 | Indicates whether an IMPLEMENTATION DEFINED algorithm is implemented in the PE for address authentication, in AArch64 state. This applies to all Pointer Authentication instructions other than the PACGA instruction.
| APA      |     7:4 |    4 | Indicates whether the QARMA5 algorithm is implemented in the PE for address authentication, in AArch64 state. This applies to all Pointer Authentication instructions other than the PACGA instruction.
| DPB      |     3:0 |    4 | Data Persistence writeback. Indicates support for the DC CVAP and DC CVADP instructions in AArch64 state.

## ID_AA64ISAR2_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| ATS1A        |   63:60 |    4 | Indicates support for address translation instructions, which perform stage 1 address translation for the given virtual address without checking for stage 1 permissions.
| LUT          |   59:56 |    4 | Indicates support for Advanced SIMD and SVE2 lookup table instructions with 2-bit and 4-bit indices.
| CSSC         |   55:52 |    4 | Indicates support for common short sequence compression instructions. If FEAT_CMPBR is implemented, indicates support for compare and branch instructions.
| RPRFM        |   51:48 |    4 | RPRFM hint instruction.
| PCDPHINT     |   47:44 |    4 | Indicates support for producer-consumer data placement hints.
| PRFMSLC      |   43:40 |    4 | Indicates whether the PRFM instructions support a system level cache option.
| SYSINSTR_128 |   39:36 |    4 | SYSINSTR_128. Indicates support for System instructions that can take 128-bit inputs.
| SYSREG_128   |   35:32 |    4 | SYSREG_128. Indicates support for instructions to access 128-bit System Registers.
| CLRBHB       |   31:28 |    4 | Indicates support for the CLRBHB instruction in AArch64 state.
| PAC_frac     |   27:24 |    4 | Indicates which address bit is used to determine the size of the PAC field.
| BC           |   23:20 |    4 | Indicates support for the BC instruction in AArch64 state.
| MOPS         |   19:16 |    4 | Indicates support for the Memory Copy and Memory Set instructions in AArch64 state.
| APA3         |   15:12 |    4 | Indicates whether the QARMA3 algorithm is implemented in the PE for address authentication in AArch64 state. This applies to all Pointer Authentication instructions other than the PACGA instruction.
| GPA3         |    11:8 |    4 | Indicates whether the QARMA3 algorithm is implemented in the PE for generic code authentication in AArch64 state.
| RPRES        |     7:4 |    4 | Indicates support for 12 bits of mantissa in reciprocal and reciprocal square root instructions in AArch64 state, when FPCR .AH is 1.
| WFxT         |     3:0 |    4 | Indicates support for the WFET and WFIT instructions in AArch64 state.

## ID_AA64ISAR3_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FPRCVT   |   31:28 |    4 | Indicates support for the following conversions between floating-point and integer instructions with only scalar SIMD&FP register operands and results, and with different input and output register sizes: FCVTAS (scalar SIMD&FP), FCVTAU (scalar SIMD&FP). FCVTMS (scalar SIMD&FP), FCVTMU (scalar SIMD&FP). FCVTNS (scalar SIMD&FP), FCVTNU (scalar SIMD&FP). FCVTPS (scalar SIMD&FP), FCVTPU (scalar SIMD&FP). FCVTZS (scalar SIMD&FP), FCVTZU (scalar SIMD&FP). SCVTF (scalar SIMD&FP), UCVTF (scalar SIMD&FP). If FEAT_SME2p1 is implemented, FEAT_FPRCVT indicates support for the following conversions between floating-point and integer instructions with only scalar SIMD&FP register operands and results, and with the same input and output register sizes when the PE is in Streaming SVE mode: FCVTAS (vector), FCVTAU (vector). FCVTMS (vector), FCVTMU (vector). FCVTNS (vector), FCVTNU (vector). FCVTPS (vector), FCVTPU (vector). FCVTZS (vector), FCVTZU (vector). SCVTF (vector), UCVTF (vector).
| LSUI     |   27:24 |    4 | Support for the following load and store unprivileged instructions: LDTXR , STTXR . CAST , CASAT , CASALT , CASLT . CASP , CASPA , CASPAL , CASPL . LDTP , STTP . LDTP (SIMD&FP) , STTP (SIMD&FP) . LDTNP , STTNP . LDTNP (SIMD&FP) , STTNP (SIMD&FP) .
| OCCMO    |   23:20 |    4 | Indicates support for the following cache maintenance operation to the Outer cache level instructions: DC CIVAOC . DC CVAOC . If FEAT_MTE is implemented: DC CIGDVAOC . DC CGDVAOC .
| LSFE     |   19:16 |    4 | Indicates support for the following A64 Base atomic floating-point in-memory instructions: Floating-point atomic add in memory: LDFADD , LDFADDA , LDFADDAL , and LDFADDL . BFloat16 atomic add in memory: LDBFADD , LDBFADDA , LDBFADDAL , and LDBFADDL . Floating-point atomic maximum in memory: LDFMAX , LDFMAXA , LDFMAXAL , and LDFMAXL . BFloat16 atomic maximum in memory: LDBFMAX , LDBFMAXA , LDBFMAXAL , and LDBFMAXL . Floating-point atomic maximum number in memory: LDFMAXNM , LDFMAXNMA , LDFMAXNMAL , and LDFMAXNML . BFloat16 atomic maximum number in memory: LDBFMAXNM , LDBFMAXNMA , LDBFMAXNMAL , and LDBFMAXNML . Floating-point atomic minimum in memory: LDFMIN , LDFMINA , LDFMINAL , and LDFMINL . BFloat16 atomic minimum in memory: LDBFMIN , LDBFMINA , LDBFMINAL , and LDBFMINL . Floating-point atomic minimum number in memory: LDFMINNM , LDFMINNMA , LDFMINNMAL , and LDFMINNML . BFloat16 atomic minimum number in memory: LDBFMINNM , LDBFMINNMA , LDBFMINNMAL , and LDBFMINNML . Floating-point atomic add in memory, without return: STFADD and STFADDL . BFloat16 atomic add in memory, without return: STBFADD and STBFADDL . Floating-point atomic maximum in memory, without return: STFMAX and STFMAXL . BFloat16 atomic maximum in memory, without return: STBFMAX and STBFMAXL . Floating-point atomic maximum number in memory, without return: STFMAXNM and STFMAXNML . BFloat16 atomic maximum number in memory, without return: STBFMAXNM and STBFMAXNML . Floating-point atomic minimum in memory, without return: STFMIN and STFMINL . BFloat16 atomic minimum in memory, without return: STBFMIN and STBFMINL . Floating-point atomic minimum number in memory, without return: STFMINNM and STFMINNML . BFloat16 atomic minimum number in memory, without return: STBFMINNM and STBFMINNML .
| PACM     |   15:12 |    4 | Indicates the implementation of PSTATE.PACM.
| TLBIW    |    11:8 |    4 | Support for TLBI VMALL for Dirty state.
| FAMINMAX |     7:4 |    4 | Indicates support for the following Advanced SIMD, SVE2, and SME2 instructions that compute maximum and minimum absolute value: When Advanced SIMD is implemented, the Advanced SIMD instructions FAMAX and FAMIN . When FEAT_SVE2 or FEAT_SME2 is implemented, the SVE2 instructions FAMAX and FAMIN . When FEAT_SME2 is implemented, the SME2 instructions FAMAX (multiple and single vectors), FAMIN (multiple and single vectors), FAMAX (multiple vectors), and FAMIN (multiple vectors).
| CPA      |     3:0 |    4 | Indicates support for Checked Pointer Arithmetic instructions.

## ID_AA64MMFR0_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| ECV       |   63:60 |    4 | Indicates presence of Enhanced Counter Virtualization.
| FGT       |   59:56 |    4 | Indicates presence of the Fine-Grained Trap controls.
| ExS       |   47:44 |    4 | Indicates support for disabling context synchronizing exception entry and exit.
| TGran4_2  |   43:40 |    4 | Indicates support for 4KB memory granule size at stage 2.
| TGran64_2 |   39:36 |    4 | Indicates support for 64KB memory granule size at stage 2.
| TGran16_2 |   35:32 |    4 | Indicates support for 16KB memory granule size at stage 2.
| TGran4    |   31:28 |    4 | Indicates support for 4KB memory translation granule size.
| TGran64   |   27:24 |    4 | Indicates support for 64KB memory translation granule size.
| TGran16   |   23:20 |    4 | Indicates support for 16KB memory translation granule size.
| BigEndEL0 |   19:16 |    4 | Indicates support for mixed-endian at EL0 only.
| SNSMem    |   15:12 |    4 | Indicates support for a distinction between Secure and Non-secure Memory.
| BigEnd    |    11:8 |    4 | Indicates support for mixed-endian configuration.
| ASIDBits  |     7:4 |    4 | Number of ASID bits.
| PARange   |     3:0 |    4 | Physical Address range supported.

## ID_AA64MMFR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ECBHB    |   63:60 |    4 | Indicates support for restrictions on branch history speculation around exceptions.
| CMOW     |   59:56 |    4 | Indicates support for cache maintenance instruction permission.
| TIDCP1   |   55:52 |    4 | Indicates whether SCTLR_EL1 .TIDCP and SCTLR_EL2 .TIDCP are implemented in AArch64 state.
| nTLBPA   |   51:48 |    4 | Indicates support for intermediate caching of translation table walks.
| AFP      |   47:44 |    4 | Indicates support for FPCR .{AH, FIZ, NEP}.
| HCX      |   43:40 |    4 | Indicates support for HCRX_EL2 and its associated EL3 trap.
| ETS      |   39:36 |    4 | Indicates support for Enhanced Translation Synchronization.
| TWED     |   35:32 |    4 | Indicates support for the configurable delayed trapping of WFE.
| XNX      |   31:28 |    4 | Indicates support for execute-never control distinction by Exception level at stage 2.
| SpecSEI  |   27:24 |    4 | Describes whether the PE can generate SError exceptions from speculative reads of memory, including speculative instruction fetches.
| PAN      |   23:20 |    4 | Privileged Access Never. Indicates support for the PAN bit in PSTATE, SPSR_EL1 , SPSR_EL2 , SPSR_EL3 , and DSPSR_EL0 .
| LO       |   19:16 |    4 | LORegions. Indicates support for LORegions.
| HPDS     |   15:12 |    4 | Hierarchical Permission Disables. Indicates support for disabling hierarchical controls in translation tables.
| VH       |    11:8 |    4 | Virtualization Host Extensions.
| VMIDBits |     7:4 |    4 | Number of VMID bits.
| HAFDBS   |     3:0 |    4 | Hardware updates to Access flag and Dirty state in translation tables.

## ID_AA64MMFR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| E0PD     |   63:60 |    4 | Indicates support for the E0PD mechanism.
| EVT      |   59:56 |    4 | Enhanced Virtualization Traps. If EL2 is implemented, indicates support for the HCR_EL2 .{TTLBOS, TTLBIS, TOCU, TICAB, TID4} traps.
| BBM      |   55:52 |    4 | Allows identification of the requirements of the hardware to have break-before-make sequences when changing block size for a translation.
| TTL      |   51:48 |    4 | Indicates support for TTL field in address operations.
| FWB      |   43:40 |    4 | Indicates support for HCR_EL2 .FWB.
| IDS      |   39:36 |    4 | Indicates the value of ESR_ELx .EC that reports an exception generated by a read access to the feature ID space.
| AT       |   35:32 |    4 | Identifies support for unaligned single-copy atomicity and atomic functions.
| ST       |   31:28 |    4 | Identifies support for small translation tables.
| NV       |   27:24 |    4 | Nested Virtualization. If EL2 is implemented, indicates support for the use of nested virtualization.
| CCIDX    |   23:20 |    4 | Support for the use of revised CCSIDR_EL1 register format.
| VARange  |   19:16 |    4 | Indicates support for a larger virtual address.
| IESB     |   15:12 |    4 | Indicates support for the IESB bit in the SCTLR_ELx registers.
| LSM      |    11:8 |    4 | Indicates support for LSMAOE and nTLSMD bits in SCTLR_EL1 and SCTLR_EL2 .
| UAO      |     7:4 |    4 | User Access Override.
| CnP      |     3:0 |    4 | Indicates support for Common not Private translations.

## ID_AA64MMFR3_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| Spec_FPACC |   63:60 |    4 | Speculative behavior in the event of a PAC authentication failure in an implementation that includes FEAT_FPACCOMBINE .
| ADERR      |   59:56 |    4 | Asynchronous Device error exceptions. With ID_AA64MMFR3_EL1.SDERR, describes the PE behavior for External aborts signaled on Device memory loads.
| SDERR      |   55:52 |    4 | Synchronous Device error exceptions. With ID_AA64MMFR3_EL1.ADERR, describes the PE behavior for External aborts signaled on Device memory loads.
| ANERR      |   47:44 |    4 | Asynchronous Normal error exceptions. With ID_AA64MMFR3_EL1.SNERR, describes the PE behavior for External aborts signaled on Normal memory loads.
| SNERR      |   43:40 |    4 | Synchronous Normal error exceptions. With ID_AA64MMFR3_EL1.ANERR, describes the PE behavior for External aborts signaled on Normal memory loads.
| D128_2     |   39:36 |    4 | 128-bit translation table descriptor at stage 2. Indicates support for 128-bit translation table descriptor at stage 2.
| D128       |   35:32 |    4 | 128-bit translation table descriptor. Indicates support for 128-bit translation table descriptor.
| MEC        |   31:28 |    4 | Indicates support for Memory Encryption Contexts.
| AIE        |   27:24 |    4 | Attribute Indexing. Indicates support for the Attribute Index Enhancement.
| S2POE      |   23:20 |    4 | Stage 2 Permission Overlay. Indicates support for Permission Overlay at stage 2.
| S1POE      |   19:16 |    4 | Stage 1 Permission Overlay. Indicates support for Permission Overlay at stage 1.
| S2PIE      |   15:12 |    4 | Stage 2 Permission Indirection. Indicates support for Permission Indirection at stage 2.
| S1PIE      |    11:8 |    4 | Stage 1 Permission Indirection. Indicates support for Permission Indirection at stage 1.
| SCTLRX     |     7:4 |    4 | SCTLR Extension. Indicates support for extension of SCTLR_ELx .
| TCRX       |     3:0 |    4 | TCR Extension. Indicates support for extension of TCR_ELx .

## ID_AA64MMFR4_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SRMASK   |   47:44 |    4 | Indicates support for bitwise write masks for the following registers: ACTLR_EL1 . CPACR_EL1 . SCTLR_EL1 . SCTLR2_EL1 . TCR_EL1 . TCR2_EL1 . ACTLR_EL2 . CPTR_EL2 . SCTLR_EL2 . SCTLR2_EL2 . TCR_EL2 . TCR2_EL2 .
| E3DSE    |   39:36 |    4 | Delegated SError exceptions from EL3. Describes support for delegated SError injection from EL3.
| RMEGDI   |   31:28 |    4 | RME Granular Data Isolation.
| E2H0     |   27:24 |    4 | Indicates support for programming HCR_EL2 .E2H.
| NV_frac  |   23:20 |    4 | Indicates support for a subset of FEAT_NV and FEAT_NV2 behaviors.
| FGWTE3   |   19:16 |    4 | Indicates support for Fine Grained Write Trap EL3 feature.
| HACDBS   |   15:12 |    4 | Support for Hardware accelerator for cleaning Dirty state.
| ASID2    |    11:8 |    4 | Indicates support for concurrent use of two ASIDs.
| EIESB    |     7:4 |    4 | Early Implicit Error Synchronization event. Indicates whether the implicit Error synchronization event inserted on taking an exception to ELx when SCTLR_ELx.IESB is 1 is inserted before or after the exception is taken.
| PoPS     |     3:0 |    4 | Support for the clean and invalidate to the Point of Physical Storage instructions: DC CIVAPS . If FEAT_MTE2 is implemented, DC CIGDVAPS .

## ID_AA64PFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CSV3     |   63:60 |    4 | Speculative use of faulting data.
| CSV2     |   59:56 |    4 | Speculative use of out of context prediction resources.
| RME      |   55:52 |    4 | Realm Management Extension (RME).
| DIT      |   51:48 |    4 | Data Independent Timing.
| AMU      |   47:44 |    4 | Indicates support for Activity Monitors Extension.
| MPAM     |   43:40 |    4 | Indicates the major version number of support for the MPAM Extension.
| SEL2     |   39:36 |    4 | Secure EL2.
| SVE      |   35:32 |    4 | Scalable Vector Extension.
| RAS      |   31:28 |    4 | RAS Extension version.
| GIC      |   27:24 |    4 | System register GIC CPU interface.
| AdvSIMD  |   23:20 |    4 | Advanced SIMD.
| FP       |   19:16 |    4 | Floating-point.
| EL3      |   15:12 |    4 | EL3 Exception level handling.
| EL2      |    11:8 |    4 | EL2 Exception level handling.
| EL1      |     7:4 |    4 | EL1 Exception level handling.
| EL0      |     3:0 |    4 | EL0 Exception level handling.

## ID_AA64PFR1_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| PFAR      |   63:60 |    4 | Support for physical fault address registers, FEAT_PFAR .
| DF2       |   59:56 |    4 | Support for error exception routing extensions, FEAT_DoubleFault2 .
| MTEX      |   55:52 |    4 | Support for additional MTE tag checking modes.
| THE       |   51:48 |    4 | Support for Translation Hardening Extension.
| GCS       |   47:44 |    4 | Support for Guarded Control Stack.
| MTE_frac  |   43:40 |    4 | Support for Asynchronous reporting of a Tag Check Fault.
| NMI       |   39:36 |    4 | Non-maskable Interrupt. Indicates support for Non-maskable interrupts.
| CSV2_frac |   35:32 |    4 | CSV2 fractional field.
| RNDR_trap |   31:28 |    4 | Random Number trap to EL3 field.
| SME       |   27:24 |    4 | Scalable Matrix Extension.
| MPAM_frac |   19:16 |    4 | Indicates the minor version number of support for the MPAM Extension.
| RAS_frac  |   15:12 |    4 | RAS Extension fractional field.
| MTE       |    11:8 |    4 | Support for the Memory Tagging Extension.
| SSBS      |     7:4 |    4 | Speculative Store Bypassing controls in AArch64 state.
| BT        |     3:0 |    4 | Branch Target Identification mechanism support in AArch64 state.

## ID_AA64PFR2_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| FPMR         |   35:32 |    4 | Indicates support for FPMR .
| UINJ         |   19:16 |    4 | Support for software injection of Undefined Instruction exceptions.
| MTEFAR       |    11:8 |    4 | Indicates whether FAR_ELx[63:60] are UNKNOWN on a synchronous exception due to a Tag Check Fault.
| MTESTOREONLY |     7:4 |    4 | Support for Store-only Tag checking.
| MTEPERM      |     3:0 |    4 | Support for Allocation tag access permissions.

## ID_AA64SMFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FA64     |   63:63 |    1 | Indicates support at each Exception Level for execution of the full AArch64 Advanced SIMD and SVE instruction sets when the PE is in Streaming SVE mode.
| LUTv2    |   60:60 |    1 | Indicates support for the following additional variants of SME2 lookup table LUTI4 and MOVT instructions: A LUTI4 instruction with 8-bit result elements, two consecutively numbered source vectors, and four consecutively numbered destination vectors. If FEAT_SME2p1 is implemented, a LUTI4 instruction with 8-bit result elements, two consecutively numbered source vectors, and four destination vectors with strided register numbering. A MOVT instruction that copies a single Z source vector to ZT0.
| SMEver   |   59:56 |    4 | Indicates support for SME instructions when FEAT_SME is implemented.
| I16I64   |   55:52 |    4 | Indicates support for the following SME instructions that accumulate into 64-bit integer elements in the ZA array: The variants of the ADDHA , ADDVA , SMOPA , SMOPS , SUMOPA , SUMOPS , UMOPA , UMOPS , USMOPA , and USMOPS instructions that accumulate into 64-bit integer tiles. When FEAT_SME2 is implemented, the variants of the ADD , ADDA , SDOT , SMLALL , SMLSLL , SUB , SUBA , SVDOT , UDOT , UMLALL , UMLSLL , and UVDOT instructions that accumulate into 64-bit integer elements in ZA array vectors.
| F64F64   |   48:48 |    1 | Indicates support for the following SME instructions that accumulate into double-precision floating-point elements in the ZA array: The variants of the FMOPA and FMOPS instructions that accumulate into double-precision tiles. When FEAT_SME2 is implemented, the variants of the FADD , FMLA , FMLS , and FSUB instructions that accumulate into double-precision elements in ZA array vectors.
| I16I32   |   47:44 |    4 | Indicates support for SME2 SMOPA (2-way), SMOPS (2-way), UMOPA (2-way), and UMOPS (2-way) instructions that accumulate 16-bit outer products into 32-bit integer tiles.
| B16B16   |   43:43 |    1 | Indicates support for the SME ZA-targeting non-widening BFloat16 BFADD , BFMLA , BFMLS , BFMOPA , BFMOPS , and BFSUB instructions with BFloat16 operands and results.
| F16F16   |   42:42 |    1 | Indicates support for the following SME2 half-precision floating-point instructions: FMOPA and FMOPS instructions that accumulate half-precision outer-products into half-precision tiles. Multi-vector FADD , FMLA , FMLS , and FSUB instructions with half-precision operands and results. Multi-vector FCVT and FCVTL instructions that convert half-precision inputs to single-precision results.
| F8F16    |   41:41 |    1 | Indicates support for the following SME2 instructions: The ZA-targeting FP8 instructions FDOT (2-way), FMLAL , FMOPA (2-way), and FVDOT that accumulate into half-precision floating-point elements. ZA-targeting non-widening half-precision FADD and FSUB instructions.
| F8F32    |   40:40 |    1 | Indicates support for the SME2 ZA-targeting FP8 FDOT (4-way), FMLALL , FMOPA (4-way), FVDOTB , and FVDOTT instructions that accumulate into single-precision floating-point elements.
| I8I32    |   39:36 |    4 | Indicates support for SME SMOPA , SMOPS , SUMOPA , SUMOPS , UMOPA , UMOPS , USMOPA , and USMOPS instructions that accumulate 8-bit outer products into 32-bit tiles
| F16F32   |   35:35 |    1 | Indicates support for SME FMOPA and FMOPS instructions that accumulate half-precision floating-point outer products into single-precision floating-point tiles.
| B16F32   |   34:34 |    1 | Indicates support for SME BFMOPA and BFMOPS instructions that accumulate BFloat16 outer products into single-precision floating-point tiles.
| BI32I32  |   33:33 |    1 | Indicates support for SME BMOPA and BMOPS instructions that accumulate thirty-two 1-bit binary outer products into 32-bit integer tiles.
| F32F32   |   32:32 |    1 | Indicates support for SME FMOPA and FMOPS instructions that accumulate single-precision floating-point outer products into single-precision floating-point tiles.
| SF8FMA   |   30:30 |    1 | Indicates support for the SVE2 FP8 to single-precision and half-precision multiply-accumulate FMLALB , FMLALT , FMLALLBB , FMLALLBT , FMLALLTB , and FMLALLTT instructions when the PE is in Streaming SVE mode.
| SF8DP4   |   29:29 |    1 | Indicates support for the SVE2 FP8 to single-precision 4-way dot product FDOT (4-way) instructions when the PE is in Streaming SVE mode.
| SF8DP2   |   28:28 |    1 | Indicates support for the SVE2 FP8 to half-precision 2-way dot product FDOT (2-way) instructions when the PE is in Streaming SVE mode.
| SBitPerm |   25:25 |    1 | Indicates support for the SVE bit permute instructions identified as implemented by ID_AA64ZFR0_EL1 .BitPerm, when the PE is in Streaming SVE mode.
| AES      |   24:24 |    1 | Indicates support for the SVE AES and 128-bit polynomial multiply long instructions identified as implemented by ID_AA64ZFR0_EL1 .AES, when the PE is in Streaming SVE mode.
| SFEXPA   |   23:23 |    1 | Indicates support for the SVE FEXPA instruction when the PE is in Streaming SVE mode.
| STMOP    |   16:16 |    1 | Indicates support for the following SME Structured sparsity outer product instructions: BFTMOPA (non-widening), if FEAT_SME_B16B16 is implemented. BFTMOPA (widening, BF16 to FP32). FTMOPA (non-widening, FP16), if FEAT_SME_F16F16 is implemented. FTMOPA (non-widening, FP32). FTMOPA (widening, 2-way, FP16 to FP32). FTMOPA (widening, 2-way, FP8 to FP16), if FEAT_SME_F8F16 is implemented. FTMOPA (widening, 4-way, FP8 to FP32) if FEAT_SME_F8F32 is implemented. STMOPA , SUTMOPA , USTMOPA , UTMOPA (4-way, Int8 to Int32). STMOPA , UTMOPA (2-way, Int16 to Int32).
| SMOP4    |     0:0 |    1 | Indicates support for the following SME Quarter-tile outer product instructions: BFMOP4A , BFMOP4S (non-widening, BF16), if FEAT_SME_B16B16 is implemented. BFMOP4A , BFMOP4S (widening, 2-way, BF16 to FP32). FMOP4A , FMOP4S (non-widening, FP16), if FEAT_SME_F16F16 is implemented. FMOP4A , FMOP4S (non-widening, FP32). FMOP4A , FMOP4S (non-widening, FP64), if FEAT_SME_F64F64 is implemented. FMOP4A , FMOP4S (widening, 2-way, FP16 to FP32). FMOP4A (widening, 2-way, FP8 to FP16), if FEAT_SME_F8F16 is implemented. FMOP4A (widening, 4-way, FP8 to FP32) instruction, if FEAT_SME_F8F32 is implemented. SMOP4A , SMOP4S , SUMOP4A , SUMOP4S , UMOP4A , UMOP4S , USMOP4A , USMOP4S (4-way, Int8 to Int32). SMOP4A , SMOP4S , SUMOP4A , SUMOP4S , UMOP4A , UMOP4S , USMOP4A , USMOP4S (4-way, Int16 to Int64), if FEAT_SME_I16I64 is implemented. SMOP4A , SMOP4S , UMOP4A , UMOP4S (2-way, Int16 to Int32).

## ID_AA64ZFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F64MM    |   59:56 |    4 | Indicates support for the following SVE FP64 double-precision variant of the FMMLA instruction, the LD1RO* instructions, the 128-bit element variants of the SVE TRN1 , TRN2 , UZP1 , UZP2 , ZIP1 , and ZIP2 instructions.
| F32MM    |   55:52 |    4 | Indicates support for the SVE FP32 single-precision floating-point matrix multiplication instruction.
| F16MM    |   51:48 |    4 | Indicates support for the SVE half-precision to single-precision matrix multiply instruction FMMLA (widening, FP16 to FP32).
| I8MM     |   47:44 |    4 | Indicates support for the following SVE Int8 matrix multiplication instructions SVE SMMLA , SUDOT , UMMLA , USMMLA , and USDOT .
| SM4      |   43:40 |    4 | Indicates support for SVE SM4 instructions.
| SHA3     |   35:32 |    4 | Indicates support for the SVE SHA3 instructions.
| B16B16   |   27:24 |    4 | Indicates support for SVE non-widening BFloat16 instructions and SME multi-vector Z-targeting non-widening BFloat16 instructions.
| BF16     |   23:20 |    4 | Indicates support for SVE BFloat16 instructions.
| BitPerm  |   19:16 |    4 | Indicates support for the following SVE bit permute instructions SVE BDEP , BEXT , and BGRP .
| EltPerm  |   15:12 |    4 | If FEAT_SVE2p2 is implemented, the following SVE instructions are implemented when the PE is not in Streaming SVE mode: 8-bit and 16-bit element COMPACT . 8-bit, 16-bit, 32-bit, and 64-bit element EXPAND . If FEAT_SME2p2 is implemented, the following SVE instructions are implemented when the PE is in Streaming SVE mode: 8-bit, 16-bit, 32-bit, and 64-bit element COMPACT and EXPAND .
| AES      |     7:4 |    4 | Indicates support for SVE Advanced Encryption Standard instructions and 128-bit polynomial multiply long instructions.
| SVEver   |     3:0 |    4 | Indicates support for SVE instructions when FEAT_SME or FEAT_SVE is implemented.

## ID_AFR0_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| IMPLEMENTATION DEFINED |   15:12 |    4 | IMPLEMENTATION DEFINED .

## ID_DFR0_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| TraceFilt |   31:28 |    4 | Armv8.4 Self-hosted Trace Extension version.
| PerfMon   |   27:24 |    4 | Performance Monitors Extension version. This field does not follow the standard ID scheme, but uses the alternative ID scheme described in 'Alternative ID scheme used for the Performance Monitors Extension version'
| MProfDbg  |   23:20 |    4 | M-profile Debug. Support for memory-mapped debug model for M-profile processors.
| MMapTrc   |   19:16 |    4 | Memory-mapped Trace. Support for memory-mapped trace model.
| CopTrc    |   15:12 |    4 | Support for System registers-based trace model, using registers in the coproc == 0b1110 encoding space.
| MMapDbg   |    11:8 |    4 | Memory-mapped Debug. Support for Armv7 memory-mapped debug model for A and R-profile processors.
| CopSDbg   |     7:4 |    4 | Support for a System registers-based Secure debug model, using registers in the coproc = 0b1110 encoding space, for an A-profile processor that includes EL3. If EL3 is not implemented and the implemented Security state is Non-secure state, this field is RES0 . Otherwise, this field reads the same as bits [3:0].
| CopDbg    |     3:0 |    4 | Debug architecture version. Indicates presence of Armv8 debug architecture.

## ID_DFR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| HPMN0    |     7:4 |    4 | Zero PMU event counters for a Guest operating system.
| MTPMU    |     3:0 |    4 | Multi-threaded PMU extension.

## ID_ISAR0_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| Divide    |   27:24 |    4 | Indicates the implemented Divide instructions.
| Debug     |   23:20 |    4 | Indicates the implemented Debug instructions.
| Coproc    |   19:16 |    4 | Indicates the implemented System register access instructions.
| CmpBranch |   15:12 |    4 | Indicates the implemented combined Compare and Branch instructions in the T32 instruction set.
| BitField  |    11:8 |    4 | Indicates support for the following BitField instructions BFC , BFI , SBFX , and UBFX .
| BitCount  |     7:4 |    4 | Indicates the implemented Bit Counting instructions.
| Swap      |     3:0 |    4 | Indicates the implemented Swap instructions in the A32 instruction set.

## ID_ISAR1_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| Jazelle   |   31:28 |    4 | Indicates the implemented Jazelle extension instructions.
| Interwork |   27:24 |    4 | Indicates the implemented Interworking instructions.
| Immediate |   23:20 |    4 | Indicates support for the following data-processing instructions with long immediates: The MOVT instruction. The MOV instruction encodings with zero-extended 16-bit immediates. The T32 ADD and SUB instruction encodings with zero-extended 12-bit immediates, and the other ADD , ADR , and SUB encodings cross-referenced by the pseudocode for those encodings.
| IfThen    |   19:16 |    4 | Indicates the implemented If-Then instructions in the T32 instruction set.
| Extend    |   15:12 |    4 | Indicates the implemented Extend instructions.
| Except_AR |    11:8 |    4 | Indicates the implemented A and R-profile exception-handling instructions.
| Except    |     7:4 |    4 | Indicates the implemented exception-handling instructions in the A32 instruction set.
| Endian    |     3:0 |    4 | Indicates the implemented Endian instructions.

## ID_ISAR2_EL1 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| Reversal       |   31:28 |    4 | Indicates the implemented Reversal instructions.
| PSR_AR         |   27:24 |    4 | Indicates the implemented A and R-profile instructions to manipulate the PSR.
| MultU          |   23:20 |    4 | Indicates the implemented advanced unsigned Multiply instructions.
| MultS          |   19:16 |    4 | Indicates the implemented advanced signed Multiply instructions.
| Mult           |   15:12 |    4 | Indicates the implemented additional Multiply instructions.
| MultiAccessInt |    11:8 |    4 | Indicates the support for interruptible multi-access instructions.
| MemHint        |     7:4 |    4 | Indicates the implemented Memory Hint instructions.
| LoadStore      |     3:0 |    4 | Indicates the implemented additional load/store instructions.

## ID_ISAR3_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| T32EE     |   31:28 |    4 | Indicates the implemented T32EE instructions.
| TrueNOP   |   27:24 |    4 | Indicates the implemented true NOP instructions.
| T32Copy   |   23:20 |    4 | Indicates the support for T32 non flag-setting MOV instructions.
| TabBranch |   19:16 |    4 | Indicates the implemented Table Branch instructions in the T32 instruction set.
| SynchPrim |   15:12 |    4 | Used in conjunction with ID_ISAR4.SynchPrim_frac to indicate the implemented Synchronization Primitive instructions.
| SVC       |    11:8 |    4 | Indicates the implemented SVC instructions.
| SIMD      |     7:4 |    4 | Indicates the implemented SIMD instructions.
| Saturate  |     3:0 |    4 | Indicates the implemented Saturate instructions.

## ID_ISAR4_EL1 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| SWP_frac       |   31:28 |    4 | Indicates support for the memory system locking the bus for SWP or SWPB instructions.
| PSR_M          |   27:24 |    4 | Indicates the implemented M-profile instructions to modify the PSRs.
| SynchPrim_frac |   23:20 |    4 | Used in conjunction with ID_ISAR3 .SynchPrim to indicate the implemented Synchronization Primitive instructions.
| Barrier        |   19:16 |    4 | Indicates the implemented Barrier instructions in the T32 and A32 instruction sets.
| SMC            |   15:12 |    4 | Indicates the implemented SMC instructions.
| Writeback      |    11:8 |    4 | Indicates the support for Writeback addressing modes.
| WithShifts     |     7:4 |    4 | Indicates the support for instructions with shifts.
| Unpriv         |     3:0 |    4 | Indicates the implemented unprivileged instructions.

## ID_ISAR5_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VCMA     |   31:28 |    4 | Indicates AArch32 support for complex number addition and multiplication where numbers are stored in vectors.
| RDM      |   27:24 |    4 | Indicates whether the VQRDMLAH and VQRDMLSH instructions are implemented in AArch32 state.
| CRC32    |   19:16 |    4 | Indicates whether the CRC32 instructions CRC32B , CRC32H , CRC32W , CRC32CB , CRC32CH , and CRC32CW are implemented in AArch32 state.
| SHA2     |   15:12 |    4 | Indicates whether the SHA2 instructions SHA256H , SHA256H2 , SHA256SU0 , and SHA256SU1 are implemented in AArch32 state.
| SHA1     |    11:8 |    4 | Indicates whether the SHA1 instructions SHA1C , SHA1P , SHA1M , SHA1H , SHA1SU0 , and SHA1SU1 are implemented in AArch32 state.
| AES      |     7:4 |    4 | Indicates whether the AES instructions are implemented in AArch32 state.
| SEVL     |     3:0 |    4 | Indicates whether the SEVL instruction is implemented in AArch32 state.

## ID_ISAR6_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CLRBHB   |   31:28 |    4 | Indicates support for the CLRBHB instruction in AArch32 state.
| I8MM     |   27:24 |    4 | Indicates support for the following Advanced SIMD Int8 matrix multiplication instructions VSMMLA , VSUDOT , VUMMLA , VUSMMLA , and VUSDOT in AArch32 state.
| BF16     |   23:20 |    4 | Indicates support for the following Advanced SIMD and floating-point BFloat16 instructions VCVT , VCVTB , VCVTT , VDOT , VFMAB , VFMAT , and VMMLA instructions with BF16 operand or result types in AArch32 state.
| SPECRES  |   19:16 |    4 | Indicates support for prediction invalidation instructions in AArch32 state.
| SB       |   15:12 |    4 | Indicates support for the SB instruction in AArch32 state.
| FHM      |    11:8 |    4 | Indicates support for the following Advanced SIMD and floating-point VFMAL and VFMSL instructions in AArch32 state.
| DP       |     7:4 |    4 | Indicates support for dot product instructions in AArch32 state.
| JSCVT    |     3:0 |    4 | Indicates support for the VJCVT instruction in AArch32 state.

## ID_MMFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| InnerShr |   31:28 |    4 | Innermost Shareability. Indicates the innermost shareability domain implemented.
| FCSE     |   27:24 |    4 | Indicates whether the implementation includes the FCSE.
| AuxReg   |   23:20 |    4 | Auxiliary Registers. Indicates support for Auxiliary registers.
| TCM      |   19:16 |    4 | Indicates support for TCMs and associated DMAs.
| ShareLvl |   15:12 |    4 | Shareability Levels. Indicates the number of shareability levels implemented.
| OuterShr |    11:8 |    4 | Outermost Shareability. Indicates the outermost shareability domain implemented.
| PMSA     |     7:4 |    4 | Indicates support for a PMSA.
| VMSA     |     3:0 |    4 | Indicates support for a VMSA.

## ID_MMFR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BPred    |   31:28 |    4 | Branch Predictor. Indicates branch predictor management requirements.
| L1TstCln |   27:24 |    4 | Level 1 cache Test and Clean. Indicates the supported Level 1 data cache test and clean operations, for Harvard or unified cache implementations.
| L1Uni    |   23:20 |    4 | Level 1 Unified cache. Indicates the supported entire Level 1 cache maintenance operations for a unified cache implementation.
| L1Hvd    |   19:16 |    4 | Level 1 Harvard cache. Indicates the supported entire Level 1 cache maintenance operations for a Harvard cache implementation.
| L1UniSW  |   15:12 |    4 | Level 1 Unified cache by Set/Way. Indicates the supported Level 1 cache line maintenance operations by set/way, for a unified cache implementation.
| L1HvdSW  |    11:8 |    4 | Level 1 Harvard cache by Set/Way. Indicates the supported Level 1 cache line maintenance operations by set/way, for a Harvard cache implementation.
| L1UniVA  |     7:4 |    4 | Level 1 Unified cache by Virtual Address. Indicates the supported Level 1 cache line maintenance operations by VA, for a unified cache implementation.
| L1HvdVA  |     3:0 |    4 | Level 1 Harvard cache by Virtual Address. Indicates the supported Level 1 cache line maintenance operations by VA, for a Harvard cache implementation.

## ID_MMFR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| HWAccFlg |   31:28 |    4 | Hardware Access Flag. In earlier versions of the Arm Architecture, this field indicates support for a Hardware Access flag, as part of the VMSAv7 implementation.
| WFIStall |   27:24 |    4 | Wait For Interrupt Stall. Indicates the support for Wait For Interrupt (WFI) stalling.
| MemBarr  |   23:20 |    4 | Memory Barrier. Indicates the supported memory barrier System instructions in the (coproc== 0b1111 ) encoding space:
| UniTLB   |   19:16 |    4 | Unified TLB. Indicates the supported TLB maintenance operations, for a unified TLB implementation.
| HvdTLB   |   15:12 |    4 | If the Unified TLB field (UniTLB, bits [19:16]) is not 0000, then the meaning of this field is IMPLEMENTATION DEFINED . Arm deprecates the use of this field by software.
| L1HvdRng |    11:8 |    4 | Level 1 Harvard cache Range. Indicates the supported Level 1 cache maintenance range operations, for a Harvard cache implementation.
| L1HvdBG  |     7:4 |    4 | Level 1 Harvard cache Background fetch. Indicates the supported Level 1 cache background fetch operations, for a Harvard cache implementation. When supported, background fetch operations are non-blocking operations.
| L1HvdFG  |     3:0 |    4 | Level 1 Harvard cache Foreground fetch. Indicates the supported Level 1 cache foreground fetch operations, for a Harvard cache implementation. When supported, foreground fetch operations are blocking operations.

## ID_MMFR3_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| Supersec  |   31:28 |    4 | Supersections. On a VMSA implementation, indicates whether Supersections are supported.
| CMemSz    |   27:24 |    4 | Cached Memory Size. Indicates the physical memory size supported by the caches.
| CohWalk   |   23:20 |    4 | Coherent Walk. Indicates whether Translation table updates require a clean to the Point of Unification.:
| PAN       |   19:16 |    4 | Privileged Access Never. Indicates support for the PAN bit in CPSR , SPSR , and DSPSR in AArch32 state.
| MaintBcst |   15:12 |    4 | Maintenance Broadcast. Indicates whether Cache, TLB, and branch predictor operations are broadcast.
| BPMaint   |    11:8 |    4 | Branch Predictor Maintenance. Indicates the supported branch predictor maintenance operations in an implementation with hierarchical cache maintenance operations.
| CMaintSW  |     7:4 |    4 | Cache Maintenance by Set/Way. Indicates the supported cache maintenance operations by set/way, in an implementation with hierarchical caches.
| CMaintVA  |     3:0 |    4 | Cache Maintenance by Virtual Address. Indicates the supported cache maintenance operations by VA, in an implementation with hierarchical caches.

## ID_MMFR4_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EVT      |   31:28 |    4 | Enhanced Virtualization Traps. If EL2 is implemented, indicates support for the HCR2 .{TTLBIS, TOCU, TICAB, TID4} traps.
| CCIDX    |   27:24 |    4 | Support for use of the revised CCSIDR format and the presence of the CCSIDR2 is indicated.
| LSM      |   23:20 |    4 | Indicates support for LSMAOE and nTLSMD bits in HSCTLR and SCTLR .
| HPDS     |   19:16 |    4 | Hierarchical permission disables bits in translation tables.
| CnP      |   15:12 |    4 | Common not Private translations.
| XNX      |    11:8 |    4 | Support for execute-never control distinction by Exception level at stage 2.
| AC2      |     7:4 |    4 | Indicates the extension of the ACTLR and HACTLR registers using ACTLR2 and HACTLR2 .
| SpecSEI  |     3:0 |    4 | Describes whether the PE can generate SError exceptions from speculative reads of memory, including speculative instruction fetches.

## ID_MMFR5_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| nTLBPA   |     7:4 |    4 | Indicates support for intermediate caching of translation table walks.
| ETS      |     3:0 |    4 | Indicates support for Enhanced Translation Synchronization.

## ID_PFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RAS      |   31:28 |    4 | RAS Extension version.
| DIT      |   27:24 |    4 | Data Independent Timing.
| AMU      |   23:20 |    4 | Indicates support for Activity Monitors Extension.
| CSV2     |   19:16 |    4 | Speculative use of out of context branch targets.
| State3   |   15:12 |    4 | T32EE instruction set support.
| State2   |    11:8 |    4 | Jazelle extension support.
| State1   |     7:4 |    4 | T32 instruction set support.
| State0   |     3:0 |    4 | A32 instruction set support.

## ID_PFR1_EL1 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| GIC            |   31:28 |    4 | System register GIC CPU interface.
| Virt_frac      |   27:24 |    4 | Virtualization fractional field. When the Virtualization field is 0b0000 , determines the support for Virtualization Extensions.
| Sec_frac       |   23:20 |    4 | Security fractional field. When the Security field is 0b0000 , determines the support for Security Extensions.
| GenTimer       |   19:16 |    4 | Generic Timer support.
| Virtualization |   15:12 |    4 | Virtualization support.
| MProgMod       |    11:8 |    4 | M-profile programmers' model support.
| Security       |     7:4 |    4 | Security support.
| ProgMod        |     3:0 |    4 | Support for the standard programmers' model for Armv4 and later. Model must support User, FIQ, IRQ, Supervisor, Abort, Undefined, and System modes.

## ID_PFR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RAS_frac |    11:8 |    4 | RAS Extension fractional field.
| SSBS     |     7:4 |    4 | Speculative Store Bypassing controls in AArch64 state.
| CSV3     |     3:0 |    4 | Speculative use of faulting data.

## IFSR32_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FnV      |   16:16 |    1 | FAR not Valid, for a synchronous External abort other than a synchronous External abort on a translation table walk.
| ExT      |   12:12 |    1 | External abort type. This bit can be used to provide an IMPLEMENTATION DEFINED classification of External aborts. In an implementation that does not provide any classification of External aborts, this bit is RES0 . For aborts other than External aborts this bit always returns 0.
| FS       |   10:10 |    1 | Fault Status bits. Bits [10] and [3:0] are interpreted together.
| LPAE     |     9:9 |    1 | On taking a Data Abort exception, this bit is set as follows:
| FS[3:0]  |     3:0 |    4 | This field is bits[3:0] of FS[4:0]. See FS[4] for the field description.

## ISR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| IS       |   10:10 |    1 | IRQ with Superpriority pending bit. Indicates whether an IRQ interrupt with Superpriority is pending.
| FS       |     9:9 |    1 | FIQ with Superpriority pending bit. Indicates whether an FIQ interrupt with Superpriority is pending.
| A        |     8:8 |    1 | SError exception pending bit. Indicates whether an SError exception is pending.
| I        |     7:7 |    1 | IRQ pending bit. Indicates whether an IRQ interrupt is pending.
| F        |     6:6 |    1 | FIQ pending bit. Indicates whether an FIQ interrupt is pending.

## LORC_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DS       |     9:2 |    8 | Descriptor Select. Selects the current LORegion descriptor accessed by LORSA_EL1 , LOREA_EL1 , and LORN_EL1 . If this field points to an LORegion descriptor that is not supported by an implementation, then the registers LORN_EL1 , LOREA_EL1 , and LORSA_EL1 are RES0 .
| EN       |     0:0 |    1 | Enable. Indicates whether LORegions are enabled.

## LOREA_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| EA[55:52] |   55:52 |    4 | Extension to EA[47:16]. For more information, see EA[47:16].
| EA[51:48] |   51:48 |    4 | Extension to EA[47:16]. For more information, see EA[47:16].
| EA[47:16] |   47:16 |   32 | Bits [47:16] of the end physical address of an LORegion described in the current LORegion descriptor selected by LORC_EL1 .DS. Bits[15:0] of this address are 0xFFFF . For implementations with fewer than 48 bits, the upper bits of this field are RES0 . When FEAT_LPA is implemented and 52-bit addresses are in use, EA[51:48] form bits [51:48] of the end physical address of the LORegion. Otherwise, when 52-bit addresses are not in use, EA[51:48] is RES0 .

## LORID_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LD       |   23:16 |    8 | Number of LORegion descriptors supported by the PE. This is an 8-bit binary number.
| LR       |     7:0 |    8 | Number of LORegions supported by the PE. This is an 8-bit binary number. If LORID_EL1 indicates that no LORegions are implemented, then LoadLOAcquire and StoreLORelease will behave as LoadAcquire and StoreRelease.

## LORN_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Num      |     7:0 |    8 | Number of the LORegion described in the current LORegion descriptor selected by LORC_EL1 .DS. The maximum number of LORegions supported by the PE is 256. If the maximum number is less than 256, then bits[8:N] are RES0 , where N is (Log 2 (Number of LORegions supported by the PE)). If this field points to a LORegion that is not supported by the PE, then the current LORegion descriptor does not match any LORegion.

## LORSA_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SA       |   55:16 |   40 |
| Valid    |     0:0 |    1 | Indicates whether the current LORegion descriptor is enabled.

## MDCCINT_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RX       |   30:30 |    1 | DCC interrupt request enable control for DTRRX. Enables a common COMMIRQ interrupt request to be signaled based on the DCC status flags.
| TX       |   29:29 |    1 | DCC interrupt request enable control for DTRTX. Enables a common COMMIRQ interrupt request to be signaled based on the DCC status flags.

## MDCCSR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RXfull   |   30:30 |    1 | DTRRX full. Read-only view of the equivalent bit in the EDSCR .
| TXfull   |   29:29 |    1 | DTRTX full. Read-only view of the equivalent bit in the EDSCR .

## MDCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EnSTEPOP |   50:50 |    1 |
| EBWE     |   43:43 |    1 | Extended Breakpoint and Watchpoint Enable. Enables use of additional breakpoints or watchpoints.
| PMEE     |   41:40 |    2 | Performance Monitors Exception Enable. Controls the generation of the PMUIRQ signal and the PMU Profiling exception at EL0, EL1, and EL2.
| HPMFZS   |   36:36 |    1 | Hyp Performance Monitors Freeze-on-SPE event. Stop counters when PMBLIMITR_EL1 .{PMFZ,E} is {1,1} and profiling is stopped.
| PMSSE    |   31:30 |    2 | Performance Monitors Snapshot Enable. Controls the generation of Capture events.
| HPMFZO   |   29:29 |    1 | Hyp Performance Monitors Freeze-on-overflow. Stop event counters on overflow.
| MTPME    |   28:28 |    1 | Multi-threaded PMU Enable. Enables use of the PMEVTYPER<n>_EL0 .MT bits.
| TDCC     |   27:27 |    1 | Trap DCC. Traps use of the Debug Comms Channel at EL1 and EL0 to EL2.
| HLP      |   26:26 |    1 | Hypervisor Long Event Counter Enable. Determines which event counter bit generates an overflow recorded by PMOVSR [n].
| E2TB     |   25:24 |    2 | EL2 Trace Buffer. If EL2 is implemented and enabled in the Trace Buffer owning Security state, controls the owning translation regime. If EL2 is implemented and enabled in the current Security state, controls access to Trace Buffer control registers from EL1.
| HCCD     |   23:23 |    1 | Hypervisor Cycle Counter Disable. Prohibits PMCCNTR_EL0 from counting at EL2.
| TTRF     |   19:19 |    1 | Traps use of the Trace Filter Control registers at EL1 to EL2, as follows: Access to TRFCR_EL1 is trapped to EL2, reported using EC syndrome value 0x18 . Access to TRFCR is trapped to EL2, reported using EC syndrome value 0x03 .
| HPMD     |   17:17 |    1 | Guest Performance Monitors Disable. Controls PMU operation at EL2.
| EnSPM    |   15:15 |    1 | Enable access to System PMU registers. When disabled, accesses to System PMU registers generate a trap to EL2.
| TPMS     |   14:14 |    1 | Trap Performance Monitor Sampling. Enables a trap to EL2 on accesses of SPE registers.
| E2PB     |   13:12 |    2 | EL2 Profiling Buffer. If EL2 is implemented and enabled in the Profiling Buffer owning Security state, this field controls the owning translation regime. If EL2 is implemented and enabled in the current Security state, this field controls access to Profiling Buffer control registers from EL1.
| TDRA     |   11:11 |    1 | Trap Debug ROM Address register access. Traps System register accesses to the Debug ROM registers to EL2 when EL2 is enabled in the current Security state as follows: If EL1 is using AArch64, accesses to MDRAR_EL1 are trapped to EL2, reported using EC syndrome value 0x18 . If EL0 or EL1 is using AArch32 state, MRC or MCR accesses to the following registers are trapped to EL2, reported using EC syndrome value 0x05 and MRRC or MCRR accesses are trapped to EL2, reported using EC syndrome value 0x0C : DBGDRAR , DBGDSAR .
| TDOSA    |   10:10 |    1 | Trap debug OS-related register access. Traps EL1 System register accesses to the powerdown debug registers to EL2, from both Execution states as follows: In AArch64 state, accesses to the following registers are trapped to EL2, reported using EC syndrome value 0x18 : OSLAR_EL1 , OSLSR_EL1 , OSDLR_EL1 , and DBGPRCR_EL1 . Any IMPLEMENTATION DEFINED register with similar functionality that the implementation specifies as trapped by this bit. In AArch32 state, accesses to the following registers are trapped to EL2, reported using EC syndrome value 0x05 : DBGOSLSR , DBGOSLAR , DBGOSDLR , and DBGPRCR . Any IMPLEMENTATION DEFINED register with similar functionality that the implementation specifies as trapped by this bit.
| TDA      |     9:9 |    1 | Trap accesses of debug System registers. Enables a trap to EL2 on accesses of debug System registers.
| TDE      |     8:8 |    1 | Trap Debug Exceptions. Controls routing of Debug exceptions, and defines the debug target Exception level, EL D .
| HPME     |     7:7 |    1 | Hyp Enable.
| TPM      |     6:6 |    1 | Trap accesses of PMU registers. Enables a trap to EL2 on accesses of PMU registers.
| TPMCR    |     5:5 |    1 | Trap PMCR_EL0 or PMCR accesses. Traps EL0 and EL1 accesses to EL2, when EL2 is enabled in the current Security state, as follows: In AArch64 state, accesses to PMCR_EL0 are trapped to EL2, reported using EC syndrome value 0x18 . In AArch32 state, accesses to PMCR are trapped to EL2, reported using EC syndrome value 0x03 .
| HPMN     |     4:0 |    5 | Defines the number of event counters PMEVCNTR<n>_EL0 and, if FEAT_PMUv3_SS is implemented, event counter snapshot registers PMEVCNTSVR<n>_EL1 , that are accessible from EL1 and, if permitted, from EL0.

## MDCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EnPMS4   |   55:55 |    1 | Enable access to SPE registers. When disabled, accesses to SPE registers generate a trap to EL3.
| TRBEE    |   54:53 |    2 | Trace buffer management event Exception Enable.
| PMSEE    |   52:51 |    2 | Profiling Buffer management event Exception Enable.
| EnSTEPOP |   50:50 |    1 |
| ETBAD    |   49:48 |    2 | External Trace Buffer Access Disable. Controls access to the Trace Buffer registers from an external debugger.
| EnITE    |   47:47 |    1 | Enable access to Instrumentation trace registers. When disabled, accesses to Instrumentation trace registers generate a trap to EL3.
| EPMSSAD  |   46:45 |    2 | External PMU Snapshot Access Disable. Controls access to the PMU Snapshot registers from an external debugger. External accesses of the following registers are affected by this control: PMCCNTSVR_EL1 , PMEVCNTSVR<n>_EL1 , and PMSSCR_EL1 . If FEAT_PMUv3_ICNTR is implemented, PMICNTSVR_EL1 .
| EnPMSS   |   44:44 |    1 | Enable access to PMU Snapshot registers. When disabled, accesses to PMU Snapshot registers generate a trap to EL3.
| EBWE     |   43:43 |    1 | Extended Breakpoint and Watchpoint Enable. Enables use of additional breakpoints or watchpoints, and enables a trap to EL3 on accesses to debug registers.
| EnPMS3   |   42:42 |    1 | Enable access to SPE registers. When disabled, accesses to SPE registers generate a trap to EL3.
| PMEE     |   41:40 |    2 | Performance Monitors Exception Enable. Controls the generation of the PMUIRQ signal and the PMU Profiling exception at all Exception levels.
| EnTB2    |   39:39 |    1 | Enable access to Trace Buffer registers. When disabled, accesses to Trace Buffer registers generate a trap to EL3.
| E3BREC   |   38:38 |    1 | Branch Record Buffer EL3 Cold Reset Enable. With MDCR_EL3.E3BREW, controls branch recording at EL3.
| E3BREW   |   37:37 |    1 | Branch Record Buffer EL3 Warm Reset Enable. With MDCR_EL3.E3BREC, controls branch recording at EL3.
| EnPMSN   |   36:36 |    1 | Trap accesses to PMSNEVFR_EL1 . Controls access to Statistical Profiling PMSNEVFR_EL1 System register from EL2 and EL1.
| MPMX     |   35:35 |    1 | Monitor Performance Monitors Extended control. With MDCR_EL3.SPME, controls PMU operation at EL3.
| MCCD     |   34:34 |    1 | Monitor Cycle Counter Disable. Prohibits the Cycle Counter, PMCCNTR_EL0 , from counting at EL3.
| SBRBE    |   33:32 |    2 | Secure Branch Record Buffer Enable. Controls branch recording by the BRBE, and access to BRBE registers and instructions at EL2 and EL1.
| PMSSE    |   31:30 |    2 | Performance Monitors Snapshot Enable. Controls the generation of Capture events.
| MTPME    |   28:28 |    1 | Multi-threaded PMU Enable. Enables use of the PMEVTYPER<n>_EL0 .MT bits.
| TDCC     |   27:27 |    1 | Trap DCC. Traps use of the Debug Comms Channel at EL2, EL1, and EL0 to EL3.
| NSTBE    |   26:26 |    1 | Non-secure Trace Buffer Extended. Together with MDCR_EL3.NSTB, controls the trace buffer owning Security state and accesses to trace buffer System registers from EL2 and EL1.
| NSTB     |   25:24 |    2 | Non-secure Trace Buffer. Together with MDCR_EL3.NSTBE, controls the trace buffer owning Security state and accesses to trace buffer System registers from EL2 and EL1. NSTBE NSTB Meaning 0b0 0b00 Secure state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Realm and Non-secure states. Accesses to trace buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. When Secure state is not implemented, this encoding is reserved. 0b0 0b01 Secure state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Realm and Non-secure states. Accesses to trace buffer System registers at Realm and Non-secure EL2, and Realm and Non-secure EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. When Secure state is not implemented, this encoding is reserved. 0b0 0b10 Non-secure state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Secure and Realm states. Accesses to trace buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b0 0b11 Non-secure state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Secure and Realm states. Accesses to trace buffer System registers at Secure and Realm EL2, and Secure and Realm EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b1 0b10 Realm state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Secure and Non-secure states. Accesses to trace buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b1 0b11 Realm state owns the trace buffer. When TraceBufferEnabled()==TRUE, tracing is prohibited in Secure and Non-secure states. Accesses to trace buffer System registers at Secure and Non-secure EL2, and Secure and Non-secure EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. All other combinations of MDCR_EL3.NSTBE and MDCR_EL3.NSTB are reserved.
| SCCD     |   23:23 |    1 | Secure Cycle Counter Disable. Prohibits PMCCNTR_EL0 from counting in Secure state and EL3.
| ETAD     |   22:22 |    1 | External Trace Access Disable. Together with MDCR_EL3.ETADE, controls access to trace unit registers by an external debugger.
| EPMAD    |   21:21 |    1 | External Performance Monitors Access Disable. Together with MDCR_EL3.EPMADE, controls access to Performance Monitor registers by an external debugger. External accesses of the following Performance Monitor registers are affected by this control: PMCCFILTR_EL0 , PMCCNTR_EL0 , PMCFGR , PMCNTENCLR_EL0 , PMCNTENSET_EL0 , PMCR_EL0 , PMEVCNTR<n>_EL0 , PMEVTYPER<n>_EL0 , PMINTENCLR_EL1 , PMINTENSET_EL1 , PMOVSCLR_EL0 , and PMOVSSET_EL0 . If PMEVFILT2R<n> is implemented, PMEVFILT2R<n> . If implemented, PMIIDR . If PMSWINC_EL0 is implemented in the external view, PMSWINC_EL0 . If FEAT_PMUv3p4 is implemented, PMMIR . If FEAT_PMUv3_EXT64 is implemented, PMCNTEN , PMINTEN , and PMOVS . If FEAT_PMUv3p9 is implemented, PMZR_EL0 . If FEAT_PMUv3_ICNTR is implemented, PMCGCR0 , PMICFILTR_EL0 , and PMICNTR_EL0 . If FEAT_PCSRv8p9 is implemented, PMPCSCTL .
| EDAD     |   20:20 |    1 | External Debug Access Disable. Together with MDCR_EL3.EDADE, controls access to breakpoint registers, watchpoint registers, and OSLAR_EL1 by an external debugger. External accesses of the following debug registers are affected by this control: DBGBCR<n>_EL1 , DBGBVR<n>_EL1 , DBGWCR<n>_EL1 , DBGWVR<n>_EL1 , and OSLAR_EL1 .
| TTRF     |   19:19 |    1 | Trap Trace Filter controls. Traps use of the Trace Filter control registers at EL2 and EL1 to EL3. The Trace Filter registers trapped by this control are: TRFCR_EL2 , TRFCR_EL12, TRFCR_EL1 , reported using EC syndrome value 0x18 . HTRFCR and TRFCR , reported using EC syndrome value 0x03 .
| STE      |   18:18 |    1 | Secure Trace enable. Enables tracing in Secure state.
| SPME     |   17:17 |    1 | Secure Performance Monitors Enable. Controls PMU operation in Secure state and at EL3 when MDCR_EL3.MPMX is 0.
| SDD      |   16:16 |    1 | AArch64 Secure Self-hosted invasive debug disable. Disables Software debug exceptions in Secure state, other than Breakpoint Instruction exceptions.
| SPD32    |   15:14 |    2 | AArch32 Secure self-hosted privileged debug. Enables or disables debug exceptions from Secure EL1 using AArch32, other than Breakpoint Instruction exceptions.
| NSPB     |   13:12 |    2 | Non-secure Profiling Buffer. Together with MDCR_EL3.NSPBE, controls the Profiling Buffer owning Security state and accesses to Statistical Profiling and Profiling Buffer System registers from EL2 and EL1. NSPBE NSPB Meaning 0b0 0b00 Secure state owns the Profiling Buffer. Profiling is disabled in Realm and Non-secure states. Accesses to Statistical Profiling and Profiling Buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. When Secure state is not implemented, this encoding is reserved. 0b0 0b01 Secure state owns the Profiling Buffer. Profiling is disabled in Realm and Non-secure states. Accesses to Statistical Profiling and Profiling Buffer System registers at Realm and Non-secure EL2, and Realm and Non-secure EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. When Secure state is not implemented, this encoding is reserved. 0b0 0b10 Non-secure state owns the Profiling Buffer. Profiling is disabled in Secure and Realm states. Accesses to Statistical Profiling and Profiling Buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b0 0b11 Non-secure state owns the Profiling Buffer. Profiling is disabled in Secure and Realm states. Accesses to Statistical Profiling and Profiling Buffer System registers at Secure and Realm EL2, and Secure and Realm EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b1 0b10 Realm state owns the Profiling Buffer. Profiling is disabled in Secure and Non-secure states. Accesses to Statistical Profiling and Profiling Buffer System registers at EL2 and EL1 generate Trap exceptions to EL3, unless the access generates a higher priority exception. 0b1 0b11 Realm state owns the Profiling Buffer. Profiling is disabled in Secure and Non-secure states. Accesses to Statistical Profiling and Profiling Buffer System registers at Secure and Non-secure EL2, and Secure and Non-secure EL1, generate Trap exceptions to EL3, unless the access generates a higher priority exception. All other combinations of MDCR_EL3.NSPBE and MDCR_EL3.NSPB are reserved.
| NSPBE    |   11:11 |    1 | Non-secure Profiling Buffer Extended. Together with MDCR_EL3.NSPB, controls the Profiling Buffer owning Security state and accesses to Statistical Profiling and Profiling Buffer System registers from EL2 and EL1.
| TDOSA    |   10:10 |    1 | Trap debug OS-related register access. Traps EL2 and EL1 System register accesses to the powerdown debug registers to EL3. Accesses to the registers are trapped as follows: Accesses from AArch64 state, OSLAR_EL1 , OSLSR_EL1 , OSDLR_EL1 , DBGPRCR_EL1 , and any IMPLEMENTATION DEFINED register with similar functionality that the implementation specifies as trapped by this field, are trapped to EL3 and reported using EC syndrome value 0x18 . Accesses using MCR or MRC to DBGOSLAR , DBGOSLSR , DBGOSDLR , and DBGPRCR , are trapped to EL3 and reported using EC syndrome value 0x05 . Accesses to any IMPLEMENTATION DEFINED register with similar functionality that the implementation specifies as trapped by this field.
| TDA      |     9:9 |    1 | Trap accesses of debug System registers. Enables a trap to EL3 on accesses of debug System registers.
| EnPM2    |     7:7 |    1 | Enable access to PMU registers. When disabled, accesses to PMU registers generate a trap to EL3.
| TPM      |     6:6 |    1 | Trap accesses of PMU registers. Enables a trap to EL3 on accesses of PMU registers.
| EDADE    |     4:4 |    1 | External Debug Access Disable Extended. Together with MDCR_EL3.EDAD, controls access to breakpoint registers, watchpoint registers, and OSLAR_EL1 by an external debugger.
| ETADE    |     3:3 |    1 | External Trace Access Disable Extended. Together with MDCR_EL3.ETAD, controls access to trace unit registers by an external debugger.
| EPMADE   |     2:2 |    1 | External Performance Monitors Access Disable Extended. Together with MDCR_EL3.EPMAD, controls access to Performance Monitor registers by an external debugger.
| RLTE     |     0:0 |    1 | Realm Trace enable. Enables tracing in Realm state.

## MDRAR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ROMADDR  |   55:12 |   44 |
| Valid    |     1:0 |    2 | This field indicates whether the ROM Table address is valid.

## MDSCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EnSTEPOP |   50:50 |    1 | Software step control bit. Enable execution from MDSTEPOP_EL1 . Permitted values are:
| EHBWE    |   35:35 |    1 | Extended Halting Breakpoint and Watchpoint Enable. Used for save/restore of EDSCR2 .EHBWE.
| EnSPM    |   34:34 |    1 | Enable access to System PMU registers. When disabled, accesses to System PMU registers generate a trap to EL1.
| TTA      |   33:33 |    1 | Trap Trace Accesses. Used for save/restore of EDSCR2 .TTA.
| EMBWE    |   32:32 |    1 | Extended Monitor Breakpoint and Watchpoint Enable. Enables use of additional breakpoints or watchpoints.
| TFO      |   31:31 |    1 | Trace Filter override. Used for save/restore of EDSCR .TFO.
| RXfull   |   30:30 |    1 | Used for save/restore of EDSCR .RXfull. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .RXfull. Reads and writes of this bit are indirect accesses to EDSCR .RXfull.
| TXfull   |   29:29 |    1 | Used for save/restore of EDSCR .TXfull. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .TXfull. Reads and writes of this bit are indirect accesses to EDSCR .TXfull.
| RXO      |   27:27 |    1 | Used for save/restore of EDSCR .RXO. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .RXO. Reads and writes of this bit are indirect accesses to EDSCR .RXO. When OSLSR_EL1 .OSLK == 1, if bits [27,6] of the value written to MDSCR_EL1 are {1,0}, that is, the RXO bit is 1 and the ERR bit is 0, the PE sets EDSCR .{RXO,ERR} to UNKNOWN values.
| TXU      |   26:26 |    1 | Used for save/restore of EDSCR .TXU. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .TXU. Reads and writes of this bit are indirect accesses to EDSCR .TXU. When OSLSR_EL1 .OSLK == 1, if bits [26,6] of the value written to MDSCR_EL1 are {1,0}, that is, the TXU bit is 1 and the ERR bit is 0, the PE sets EDSCR .{TXU,ERR} to UNKNOWN values.
| INTdis   |   23:22 |    2 | Used for save/restore of EDSCR .INTdis. When OSLSR_EL1 .OSLK == 0, and software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this field holds the value of EDSCR .INTdis. Reads and writes of this field are indirect accesses to EDSCR .INTdis.
| TDA      |   21:21 |    1 | Used for save/restore of EDSCR .TDA. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .TDA. Reads and writes of this bit are indirect accesses to EDSCR .TDA.
| SC2      |   19:19 |    1 | Used for save/restore of EDSCR .SC2. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .SC2. Reads and writes of this bit are indirect accesses to EDSCR .SC2.
| MDE      |   15:15 |    1 | Monitor debug events. Enable Breakpoint, Watchpoint, and Vector Catch exceptions.
| HDE      |   14:14 |    1 | Used for save/restore of EDSCR .HDE. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .HDE. Reads and writes of this bit are indirect accesses to EDSCR .HDE.
| KDE      |   13:13 |    1 | Local (kernel) debug enable. If EL D is using AArch64, enable debug exceptions within EL D . Permitted values are:
| TDCC     |   12:12 |    1 | Traps EL0 accesses to the Debug Communication Channel (DCC) registers to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from both Execution states, as follows: In AArch64 state, MRS or MSR accesses to the following DCC registers are trapped, reported using EC syndrome value 0x18 : MDCCSR_EL0 . If not in Debug state, DBGDTR_EL0 , DBGDTRTX_EL0 , and DBGDTRRX_EL0 . In AArch32 state, MRC or MCR accesses to the following registers are trapped, reported using EC syndrome value 0x05 . DBGDSCRint , DBGDIDR , DBGDSAR , DBGDRAR . If not in Debug state, DBGDTRRXint , and DBGDTRTXint . In AArch32 state, LDC access to DBGDTRRXint and STC access to DBGDTRTXint are trapped, reported using EC syndrome value 0x06 . In AArch32 state, MRRC accesses to DBGDSAR and DBGDRAR are trapped, reported using EC syndrome value 0x0C .
| ERR      |     6:6 |    1 | Used for save/restore of EDSCR .ERR. When OSLSR_EL1 .OSLK == 0, software must treat this bit as UNK/SBZP. When OSLSR_EL1 .OSLK == 1, this bit holds the value of EDSCR .ERR. Reads and writes of this bit are indirect accesses to EDSCR .ERR.
| SS       |     0:0 |    1 | Software step control bit. If EL D is using AArch64, enable Software step. Permitted values are:

## MDSELR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BANK     |     5:4 |    2 | Breakpoint and watchpoint bank select.

## MDSTEPOP_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| OPCODE   |    31:0 |   32 | A64 instruction to be executed on the PE.

## MECID_A0_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## MECID_A1_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## MECID_P0_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## MECID_P1_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## MECID_RL_A_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## MECIDR_EL2 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| MECIDWidthm1 |     3:0 |    4 | MECID width minus 1. The value of this field plus 1 is the MECID width in bits, that this PE supports.

## MFAR_EL3 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| NS         |   63:63 |    1 | Together with MFAR_EL3.NSE, reports the physical address space of the access that triggered the exception. NSE NS Meaning 0b0 0b0 When Secure state is implemented, Secure. Otherwise reserved. 0b0 0b1 Non-secure. 0b1 0b0 Root. 0b1 0b1 Realm.
| NSE        |   62:62 |    1 | Together with MFAR_EL3.NS, reports the physical address space of the access that triggered the exception. For a description of the values derived by evaluating NS and NSE together, see MFAR_EL3.NS.
| FPA[55:52] |   55:52 |    4 | When FEAT_D128 is implemented, extension to MFAR_EL3.FPA[47:12].
| FPA[51:48] |   51:48 |    4 | When FEAT_LPA is implemented, extension to MFAR_EL3.FPA[47:12].
| FPA        |   47:12 |   36 | Bits [47:12] of the Faulting Physical Address.

## MIDR_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| Implementer  |   31:24 |    8 | The Implementer code. This field must hold an implementer code that has been assigned by Arm.
| Variant      |   23:20 |    4 | Variant number. Typically, this field is used to distinguish between different product variants, or major revisions of a product.
| Architecture |   19:16 |    4 | Architecture version.
| PartNum      |    15:4 |   12 | Primary Part Number for the device. On processors implemented by Arm, if the top four bits of the primary part number are 0x0 or 0x7 , the variant and architecture are encoded differently.
| Revision     |     3:0 |    4 | Revision number for the device.

## MPAM0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PMG_D    |   47:40 |    8 | Performance monitoring group property for PARTID_D.
| PMG_I    |   39:32 |    8 | Performance monitoring group property for PARTID_I.
| PARTID_D |   31:16 |   16 | Partition ID for data accesses, including load and store accesses, made from EL0.
| PARTID_I |    15:0 |   16 | Partition ID for instruction accesses made from EL0.

## MPAM1_EL1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| MPAMEN     |   63:63 |    1 | MPAM Enable. MPAM is enabled when MPAMEN == 1. When disabled, all PARTIDs and PMGs are output as their default value in the corresponding ID space.
| FORCED_NS  |   60:60 |    1 | In the Secure state, FORCED_NS indicates the state of MPAM3_EL3 .FORCE_NS.
| ALTSP_FRCD |   54:54 |    1 | Alternative PARTID forced for PARTIDs in this register.
| PMG_D      |   47:40 |    8 | Performance monitoring group property for PARTID_D.
| PMG_I      |   39:32 |    8 | Performance monitoring group property for PARTID_I.
| PARTID_D   |   31:16 |   16 | Partition ID for data accesses, including load and store accesses, made from EL1.
| PARTID_I   |    15:0 |   16 | Partition ID for instruction accesses made from EL1.

## MPAM2_EL2 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| MPAMEN       |   63:63 |    1 | MPAM Enable. MPAM is enabled when MPAMEN == 1. When disabled, all PARTIDs and PMGs are output as their default value in the corresponding ID space.
| TIDR         |   58:58 |    1 | TIDR traps accesses to MPAMIDR_EL1 from EL1 to EL2.
| ALTSP_HFC    |   56:56 |    1 | Hierarchical force of alternative PARTID space controls. When MPAM3_EL3 .ALTSP_HEN is 0, ALTSP controls in MPAM2_EL2 have no effect.  When MPAM3_EL3 .ALTSP_HEN is 1, this bit selects whether the PARTIDs in MPAM1_EL1 and MPAM0_EL1 are in the primary (0) or alternative (1) PARTID space for the security state.
| ALTSP_EL2    |   55:55 |    1 | Select alternative PARTID space for PARTIDs in MPAM2_EL2 when MPAM3_EL3 .ALTSP_HEN is 1.
| ALTSP_FRCD   |   54:54 |    1 | Alternative PARTID forced for PARTIDs in this register.
| EnMPAMSM     |   50:50 |    1 | Traps execution at EL1 of instructions that directly access the MPAMSM_EL1 register to EL2. The exception is reported using ESR_ELx .EC value 0x18 .
| TRAPMPAM0EL1 |   49:49 |    1 | Trap accesses from EL1 to the MPAM0_EL1 register trap to EL2.
| TRAPMPAM1EL1 |   48:48 |    1 | Trap accesses from EL1 to the MPAM1_EL1 register trap to EL2.
| PMG_D        |   47:40 |    8 | Performance monitoring group for data accesses.
| PMG_I        |   39:32 |    8 | Performance monitoring group for instruction accesses.
| PARTID_D     |   31:16 |   16 | Partition ID for data accesses, including load and store accesses, made from EL2.
| PARTID_I     |    15:0 |   16 | Partition ID for instruction accesses made from EL2.

## MPAM3_EL3 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| MPAMEN      |   63:63 |    1 | MPAM Enable. MPAM is enabled when MPAMEN == 1. When disabled, all PARTIDs and PMGs are output as their default value in the corresponding ID space. Values of this field are:
| TRAPLOWER   |   62:62 |    1 | Trap direct accesses to MPAM System registers that are not UNDEFINED from all ELn lower than EL3.
| SDEFLT      |   61:61 |    1 | SDEFLT overrides the PARTID and PMG with the default PARTID and default PMG when executing in the Secure state.
| FORCE_NS    |   60:60 |    1 | FORCE_NS forces MPAM_NS to always be 1 in the Secure state.
| ALTSP_HEN   |   57:57 |    1 | Hierarchical enable for alternative PARTID space controls. Alternative PARTID space controls in MPAM2_EL2 have no effect when this field is zero.
| ALTSP_HFC   |   56:56 |    1 | Hierarchical force of alternative PARTID space controls. When MPAM3_EL3.ALTSP_HEN is 0, the PARTID space for PARTIDs in MPAM2_EL2 , MPAM1_EL1 , and MPAM0_EL1 is selected by the value of this bit.
| ALTSP_EL3   |   55:55 |    1 | Select alternative PARTID space for PARTIDs in MPAM3_EL3.
| RT_ALTSP_NS |   52:52 |    1 | Selects whether the alternative PARTID space for the Root security state is the Secure PARTID space or the Non-secure PARTID space. MPAM3_EL3 .RT_ALTSP_NS selects the alternative PARTID space for the Root Security state when MPAM3_EL3 .ALTSP_EL3 == 1.
| PMG_D       |   47:40 |    8 | Performance monitoring group for data accesses.
| PMG_I       |   39:32 |    8 | Performance monitoring group for instruction accesses.
| PARTID_D    |   31:16 |   16 | Partition ID for data accesses, including load and store accesses, made from EL3.
| PARTID_I    |    15:0 |   16 | Partition ID for instruction accesses made from EL3.

## MPAMBW0_EL1 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBW0_EL1 .MAX value.
| ENABLED         |   62:62 |    1 | Enables the PE-side memory bandwidth control when in EL0.
| HARDLIM         |   61:61 |    1 | PE-side Maximum Bandwidth Limit Behavior Selection.
| MAX             |    31:0 |   32 |

## MPAMBW1_EL1 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBW1_EL1 .MAX value.
| ENABLED         |   62:62 |    1 | Enables the PE-side memory bandwidth control when in EL1.
| HARDLIM         |   61:61 |    1 | PE-side Maximum Bandwidth Limit Behavior Selection.
| MAX             |    31:0 |   32 |

## MPAMBW2_EL2 bitfields

| Bitfield            | msb:lsb | Size | Description
| ------------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE     |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBW2_EL2 .MAX value.
| ENABLED             |   62:62 |    1 | Enables the PE-side memory bandwidth control when in EL2.
| HARDLIM             |   61:61 |    1 | PE-side Maximum Bandwidth Limit Behavior Selection.
| nTRAP_MPAMBWIDR_EL1 |   52:52 |    1 | Traps accesses to MPAMBWIDR_EL1 from EL1 to EL2.
| nTRAP_MPAMBW0_EL1   |   51:51 |    1 | Traps accesses to MPAMBW0_EL1 from EL1 to EL2.
| nTRAP_MPAMBW1_EL1   |   50:50 |    1 | Traps accesses to MPAMBW1_EL1 from EL1 to EL2.
| nTRAP_MPAMBWSM_EL1  |   49:49 |    1 | Traps accesses to MPAMBWSM_EL1 from EL1 to EL2.
| MAX                 |    31:0 |   32 |

## MPAMBW3_EL3 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBW3_EL3 .MAX value.
| ENABLED         |   62:62 |    1 | Enables the PE-side memory bandwidth control when in EL3.
| HARDLIM         |   61:61 |    1 | PE-side Maximum Bandwidth Limit Behavior Selection.
| nTRAPLOWER      |   49:49 |    1 | Traps accesses to MPAMBW2_EL2 , MPAMBWCAP_EL2 , MPAMBW1_EL1 , MPAMBW0_EL1 , MPAMBWSM_EL1 , MPAMBWIDR_EL1 from any lower EL to EL3.
| MAX             |    31:0 |   32 |

## MPAMBWCAP_EL2 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBWCAP_EL2 .CAP value.
| ENABLED         |   62:62 |    1 | Enables the PE-side memory bandwidth control capping by EL2.
| CAP             |    31:0 |   32 |

## MPAMBWIDR_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| HAS_HW_SCALE |   63:63 |    1 | Indicates whether hardware support for auto-scaling of MPAMBWn_ELx.MAX, MPAMBWSM_EL1 .MAX and MPAMBWCAP_EL2 .CAP limits is available.
| MAX_LIM      |   31:30 |    2 | Indicates the implemented maximum-bandwidth limit partitioning behaviors.
| BWA_WD       |     5:0 |    6 | Indicates the number of implemented bits in the bandwidth allocation fields MPAMBWn_ELx.MAX, MPAMBWSM_EL1 .MAX and MPAMBWCAP_EL2 .CAP.

## MPAMBWSM_EL1 bitfields

| Bitfield        | msb:lsb | Size | Description
| --------------- | ------: | ---: | -----------
| HW_SCALE_ENABLE |   63:63 |    1 | Enables hardware bandwidth scaling of the MPAMBWSM_EL1 .MAX value.
| ENABLED         |   62:62 |    1 | Enables the PE-side memory bandwidth control for streaming PARTIDs.
| HARDLIM         |   61:61 |    1 | PE-side Maximum-bandwidth Limit Behavior Selection.
| MAX             |    31:0 |   32 |

## MPAMHCR_EL2 bitfields

| Bitfield         | msb:lsb | Size | Description
| ---------------- | ------: | ---: | -----------
| TRAP_MPAMIDR_EL1 |   31:31 |    1 | Trap accesses from EL1 to MPAMIDR_EL1 to EL2.
| GSTAPP_PLK       |     8:8 |    1 | Make the PARTIDs at EL0 the same as the PARTIDs at EL1. When executing at EL0, EL2 is enabled, HCR_EL2 .TGE == 0 and GSTAPP_PLK = 1, MPAM1_EL1 is used instead of MPAM0_EL1 to generate MPAM labels for memory requests.
| EL1_VPMEN        |     1:1 |    1 | Enable the virtual PARTID mapping of the PARTID fields in MPAM1_EL1 when executing at EL1. This bit also enables virtual PARTID mapping when MPAM1_EL1 is used to generate MPAM labels for memory requests at EL0 due to GSTAPP_PLK == 1.
| EL0_VPMEN        |     0:0 |    1 | Enable the virtual PARTID mapping of the PARTID fields of MPAM0_EL1 unless the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}. When the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, EL0_VPMEN is ignored and MPAM0_EL1 PARTID fields are not mapped. When MPAMHCR_EL2 .GSTAPP_PLK == 1 and HCR_EL2 .TGE == 0, MPAM1_EL1 is used as the source of PARTIDs and the virtual PARTID mapping of MPAM1_EL1 PARTIDs is controlled by MPAMHCR_EL2 .EL1_VPMEN.

## MPAMIDR_EL1 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| HAS_SDEFLT   |   61:61 |    1 | HAS_SDEFLT indicates support for MPAM3_EL3 .SDEFLT bit.
| HAS_FORCE_NS |   60:60 |    1 | HAS_FORCE_NS indicates support for MPAM3_EL3 .FORCE_NS bit.
| SP4          |   59:59 |    1 | Supports 4 MPAM PARTID spaces.
| HAS_TIDR     |   58:58 |    1 | HAS_TIDR indicates support for MPAM2_EL2 .TIDR bit.
| HAS_ALTSP    |   57:57 |    1 | HAS_ALTSP indicates support for alternative PARTID spaces.
| HAS_BW_CTRL  |   56:56 |    1 | HAS_BW_CTRL indicates support for PE-side bandwidth controls.
| PMG_MAX      |   39:32 |    8 | The largest value of PMG that the implementation can generate. The PMG_I and PMG_D fields of every MPAMn_ELx must implement at least enough bits to represent PMG_MAX.
| VPMR_MAX     |   20:18 |    3 | Indicates the maximum register index n for the MPAMVPM<n>_EL2 registers.
| HAS_HCR      |   17:17 |    1 | HAS_HCR indicates that the PE implementation supports MPAM virtualization, including MPAMHCR_EL2 , MPAMVPMV_EL2 , and MPAMVPM<n>_EL2 with n in the range 0 to VPMR_MAX. Must be 0 if EL2 is not implemented in either Security state.
| PARTID_MAX   |    15:0 |   16 | The largest value of PARTID that the implementation can generate. The PARTID_I and PARTID_D fields of every MPAMn_ELx must implement at least enough bits to represent PARTID_MAX.

## MPAMSM_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PMG_D    |   47:40 |    8 | Performance monitoring group property for PARTID_D.
| PARTID_D |   31:16 |   16 | Partition ID for requests issued due to the execution at any Exception level of SME load and store instructions and, when the PE is in Streaming SVE mode, SVE and SIMD&FP load and store instructions and SVE prefetch instructions.

## MPAMVPM0_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| PhyPARTID3 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 3.  PhyPARTID3 gives the mapping of virtual PARTID 3 to a physical PARTID.
| PhyPARTID2 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 2.  PhyPARTID2 gives the mapping of virtual PARTID 2 to a physical PARTID.
| PhyPARTID1 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 1.  PhyPARTID1 gives the mapping of virtual PARTID 1 to a physical PARTID.
| PhyPARTID0 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 0.  PhyPARTID0 gives the mapping of virtual PARTID 0 to a physical PARTID.

## MPAMVPM1_EL2 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| PhyPARTID7 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 7.  PhyPARTID7 gives the mapping of virtual PARTID 7 to a physical PARTID.
| PhyPARTID6 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 6.  PhyPARTID6 gives the mapping of virtual PARTID 6 to a physical PARTID.
| PhyPARTID5 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 5.  PhyPARTID5 gives the mapping of virtual PARTID 5 to a physical PARTID.
| PhyPARTID4 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 4.  PhyPARTID4 gives the mapping of virtual PARTID 4 to a physical PARTID.

## MPAMVPM2_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID11 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 11.  PhyPARTID11 gives the mapping of virtual PARTID 11 to a physical PARTID.
| PhyPARTID10 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 10.  PhyPARTID10 gives the mapping of virtual PARTID 10 to a physical PARTID.
| PhyPARTID9  |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 9.  PhyPARTID9 gives the mapping of virtual PARTID 9 to a physical PARTID.
| PhyPARTID8  |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 8.  PhyPARTID8 gives the mapping of virtual PARTID 8 to a physical PARTID.

## MPAMVPM3_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID15 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 15.  PhyPARTID15 gives the mapping of virtual PARTID 15 to a physical PARTID.
| PhyPARTID14 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 14.  PhyPARTID14 gives the mapping of virtual PARTID 14 to a physical PARTID.
| PhyPARTID13 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 13.  PhyPARTID13 gives the mapping of virtual PARTID 13 to a physical PARTID.
| PhyPARTID12 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 12.  PhyPARTID12 gives the mapping of virtual PARTID 12 to a physical PARTID.

## MPAMVPM4_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID19 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 19.  PhyPARTID19 gives the mapping of virtual PARTID 19 to a physical PARTID.
| PhyPARTID18 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 18.  PhyPARTID18 gives the mapping of virtual PARTID 18 to a physical PARTID.
| PhyPARTID17 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 17.  PhyPARTID17 gives the mapping of virtual PARTID 17 to a physical PARTID.
| PhyPARTID16 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 16.  PhyPARTID16 gives the mapping of virtual PARTID 16 to a physical PARTID.

## MPAMVPM5_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID23 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 23.  PhyPARTID23 gives the mapping of virtual PARTID 23 to a physical PARTID.
| PhyPARTID22 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 22.  PhyPARTID22 gives the mapping of virtual PARTID 22 to a physical PARTID.
| PhyPARTID21 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 21.  PhyPARTID21 gives the mapping of virtual PARTID 21 to a physical PARTID.
| PhyPARTID20 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 20.  PhyPARTID20 gives the mapping of virtual PARTID 20 to a physical PARTID.

## MPAMVPM6_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID27 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 27.  PhyPARTID27 gives the mapping of virtual PARTID 27 to a physical PARTID.
| PhyPARTID26 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 26.  PhyPARTID26 gives the mapping of virtual PARTID 26 to a physical PARTID.
| PhyPARTID25 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 25.  PhyPARTID25 gives the mapping of virtual PARTID 25 to a physical PARTID.
| PhyPARTID24 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 24.  PhyPARTID24 gives the mapping of virtual PARTID 24 to a physical PARTID.

## MPAMVPM7_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| PhyPARTID31 |   63:48 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 31.  PhyPARTID31 gives the mapping of virtual PARTID 31 to a physical PARTID.
| PhyPARTID30 |   47:32 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 30.  PhyPARTID30 gives the mapping of virtual PARTID 30 to a physical PARTID.
| PhyPARTID29 |   31:16 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 29.  PhyPARTID29 gives the mapping of virtual PARTID 29 to a physical PARTID.
| PhyPARTID28 |    15:0 |   16 | Virtual PARTID Mapping Entry for virtual PARTID 28.  PhyPARTID28 gives the mapping of virtual PARTID 28 to a physical PARTID.

## MPAMVPMV_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VPM_V<m> |    31:0 |   32 | Contains valid bit for virtual PARTID mapping entry corresponding to virtual PARTID<m>.

## MPIDR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Aff3     |   39:32 |    8 | Affinity level 3. See the description of Aff0 for more information. Aff3 is not supported in AArch32 state.
| U        |   30:30 |    1 | Indicates a Uniprocessor system, as distinct from PE 0 in a multiprocessor system.
| MT       |   24:24 |    1 | Indicates whether the lowest level of affinity consists of logical PEs that are implemented using an interdependent approach, such as multithreading. See the description of Aff0 for more information about affinity levels.
| Aff2     |   23:16 |    8 | Affinity level 2. See the description of Aff0 for more information.
| Aff1     |    15:8 |    8 | Affinity level 1. See the description of Aff0 for more information.
| Aff0     |     7:0 |    8 | Affinity level 0. The value of the MPIDR .{Aff2, Aff1, Aff0} or MPIDR_EL1 .{Aff3, Aff2, Aff1, Aff0} set of fields of each PE must be unique within the system as a whole.

## MVFR0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FPRound  |   31:28 |    4 | Floating-Point Rounding modes. Indicates whether the floating-point implementation provides support for rounding modes.
| FPShVec  |   27:24 |    4 | Short Vectors. Indicates whether the floating-point implementation provides support for the use of short vectors.
| FPSqrt   |   23:20 |    4 | Square Root. Indicates whether the floating-point implementation provides support for the ARMv6 VFP square root operations.
| FPDivide |   19:16 |    4 | Indicates whether the floating-point implementation provides support for VFP divide operations.
| FPTrap   |   15:12 |    4 | Floating-Point Exception Trapping. Indicates whether the floating-point implementation provides support for exception trapping.
| FPDP     |    11:8 |    4 | Floating-Point Double-Precision. Indicates whether the floating-point implementation provides support for double-precision operations.
| FPSP     |     7:4 |    4 | Floating-Point Single-Precision. Indicates whether the floating-point implementation provides support for single-precision operations.
| SIMDReg  |     3:0 |    4 | Advanced SIMD registers. Indicates whether the Advanced SIMD and floating-point implementation provides support for the Advanced SIMD and floating-point register bank.

## MVFR1_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SIMDFMAC |   31:28 |    4 | Advanced SIMD Fused Multiply-Accumulate. Indicates whether the Advanced SIMD implementation provides fused multiply accumulate instructions.
| FPHP     |   27:24 |    4 | Floating-Point Half-Precision. Indicates the level of half-precision floating-point support.
| SIMDHP   |   23:20 |    4 | Advanced SIMD Half-Precision. Indicates the level of half-precision floating-point support.
| SIMDSP   |   19:16 |    4 | Advanced SIMD Single-Precision. Indicates whether the Advanced SIMD and floating-point implementation provides single-precision floating-point instructions.
| SIMDInt  |   15:12 |    4 | Advanced SIMD Integer. Indicates whether the Advanced SIMD and floating-point implementation provides integer instructions.
| SIMDLS   |    11:8 |    4 | Advanced SIMD Load/Store. Indicates whether the Advanced SIMD and floating-point implementation provides load/store instructions.
| FPDNaN   |     7:4 |    4 | Default NaN mode. Indicates whether the floating-point implementation provides support only for the Default NaN mode.
| FPFtZ    |     3:0 |    4 | Flush to Zero mode. Indicates whether the floating-point implementation provides support only for the Flush-to-Zero mode of operation.

## MVFR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FPMisc   |     7:4 |    4 | Indicates whether the floating-point implementation provides support for miscellaneous VFP features.
| SIMDMisc |     3:0 |    4 | Indicates whether the Advanced SIMD implementation provides support for miscellaneous Advanced SIMD features.

## NZCV bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| N        |   31:31 |    1 | Negative condition flag. Set to 1 if the result of the last flag-setting instruction was negative.
| Z        |   30:30 |    1 | Zero condition flag. Set to 1 if the result of the last flag-setting instruction was zero, and to 0 otherwise. A result of zero often indicates an equal result from a comparison.
| C        |   29:29 |    1 | Carry condition flag. Set to 1 if the last flag-setting instruction resulted in a carry condition, for example an unsigned overflow on an addition.
| V        |   28:28 |    1 | Overflow condition flag. Set to 1 if the last flag-setting instruction resulted in an overflow condition, for example a signed overflow on an addition.

## OSDLR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DLK      |     0:0 |    1 | OS Double Lock control bit.

## OSDTRRX_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DTRRX    |    31:0 |   32 | Update DTRRX without side-effect. Writes to this register update the value in DTRRX and do not change RXfull. Reads of this register return the last value written to DTRRX and do not change RXfull. For the full behavior of the Debug Communications Channel, see 'The Debug Communication Channel and Instruction Transfer Register' .

## OSDTRTX_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DTRTX    |    31:0 |   32 | Return DTRTX without side-effect. Reads of this register return the value in DTRTX and do not change TXfull. Writes of this register update the value in DTRTX and do not change TXfull. For the full behavior of the Debug Communications Channel, see 'The Debug Communication Channel and Instruction Transfer Register' .

## OSECCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EDECCR   |    31:0 |   32 | Used for save/restore to EDECCR over powerdown. Reads or writes to this field are indirect accesses to EDECCR .

## OSLAR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| OSLK     |     0:0 |    1 | On writes to OSLAR_EL1, bit[0] is copied to the OS Lock. Use OSLSR_EL1 .OSLK to check the current status of the lock.

## OSLSR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| OSLM     |     3:3 |    1 | OS Lock model implemented. Identifies the form of OS save and restore mechanism implemented.
| nTT      |     2:2 |    1 | Not 32-bit access. This bit is always RAZ. It indicates that a 32-bit access is needed to write the key to the OS Lock Access Register.
| OSLK     |     1:1 |    1 | OS Lock Status.
| OSLM[0]  |     0:0 |    1 | This field is bit[0] of OSLM[1:0]. See OSLM[1] for the field description.

## PAN bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PAN      |   22:22 |    1 | Privileged Access Never.

## PAR_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| PA                     |  119:76 |   44 | Output address. The output address (OA) corresponding to the supplied input address. This field returns address bits[55:12].
| D128                   |   64:64 |    1 | Indicates if the PAR_EL1 uses the 128-bit format.
| ATTR                   |   63:56 |    8 | Memory attributes for the returned output address. This field uses the same encoding as the Attr<n> fields in MAIR_EL1 , MAIR_EL2 , and MAIR_EL3 . If FEAT_MTE_PERM is implemented and the instruction performed a stage 2 translation, the following additional encoding is defined: ATTR Meaning 0b11100000 Tagged NoTagAccess Normal Inner Write-Back, Outer Write-Back, Read-Allocate, Write-Allocate Non-transient memory. This encoding in MAIR_ELx is Reserved. The value returned in this field can be the resulting attribute that is actually implemented by the implementation, as determined by any permitted implementation choices and any applicable configuration bits, instead of the value that appears in the Translation table descriptor. The attributes presented are consistent with the stages of translation applied in the address translation instruction. If the instruction performed a stage 1 translation only, the attributes are from the stage 1 translation. If the instruction performed a stage 1 and stage 2 translation, the attributes are from the combined stage 1 and stage 2 translation.
| NSE                    |   11:11 |    1 | Reports the NSE attribute for a translation table descriptor from the EL3 translation regime. For a description of the values derived by evaluating NS and NSE together, see PAR_EL1.NS. For a result from a Secure, Non-secure, or Realm translation regime, this bit is unknown.
| IMPLEMENTATION DEFINED |   10:10 |    1 | IMPLEMENTATION DEFINED .
| NS                     |     9:9 |    1 | Non-secure. The NS attribute for a translation table entry from a Secure translation regime, a Realm translation regime, and the EL3 translation regime.
| SH                     |     8:7 |    2 | Shareability attribute, for the returned output address.
| F                      |     0:0 |    1 | Indicates whether the instruction performed a successful address translation.

## PFAR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| NS        |   63:63 |    1 | Together with PFAR_EL1.NSE, reports the physical address space of the access that triggered the exception. NSE NS Meaning 0b0 0b0 When Secure state is implemented, Secure. Otherwise reserved. 0b0 0b1 Non-secure. 0b1 0b0 Reserved. 0b1 0b1 Realm.
| NSE       |   62:62 |    1 | Together with PFAR_EL1.NS, reports the physical address space of the access that triggered the exception. For a description of the values derived by evaluating NS and NSE together, see MFAR_EL3.NS.
| PA[55:52] |   55:52 |    4 | When FEAT_D128 is implemented, extension to PFAR_EL1.PA[47:0].
| PA[51:48] |   51:48 |    4 | When FEAT_LPA is implemented, extension to PFAR_EL1.PA[47:0].
| PA        |    47:0 |   48 | Physical Address. Bits [47:0] of the aborting physical address.

## PFAR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| NS        |   63:63 |    1 | Together with PFAR_EL2.NSE, reports the physical address space of the access that triggered the exception. NSE NS Meaning 0b0 0b0 When Secure state is implemented, Secure. Otherwise reserved. 0b0 0b1 Non-secure. 0b1 0b0 Reserved. 0b1 0b1 Realm.
| NSE       |   62:62 |    1 | Together with PFAR_EL2.NS, reports the physical address space of the access that triggered the exception. For a description of the values derived by evaluating NS and NSE together, see MFAR_EL3.NS.
| PA[55:52] |   55:52 |    4 | When FEAT_D128 is implemented, extension to PFAR_EL2.PA[47:0].
| PA[51:48] |   51:48 |    4 | When FEAT_LPA is implemented, extension to PFAR_EL2.PA[47:0].
| PA        |    47:0 |   48 | Physical Address. Bits [47:0] of the aborting physical address.

## PM bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PM       |   32:32 |    1 | PMU Exception Mask.

## PMBIDR_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| MaxBuffSize |   47:32 |   16 | Maximum supported Profiling Buffer size. Reserved for software use.
| EA          |    11:8 |    4 | External Abort handling. Describes how the PE manages External aborts on writes made by the Statistical Profiling Unit to the Profiling Buffer.
| AddrMode    |     7:6 |    2 | Address Modes. Describes the addressing modes available for the Profiling Buffer.
| F           |     5:5 |    1 | Flag updates. Describes how address translations performed by the Statistical Profiling Unit manage the Access flag and dirty state.
| P           |     4:4 |    1 | Programming not allowed. When read at EL3, this field reads as zero. Otherwise, indicates that the Profiling Buffer is owned by a higher Exception level or another Security state.
| Align       |     3:0 |    4 | Defines the minimum alignment constraint for writes to PMBPTR_EL1 .

## PMBLIMITR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LIMIT    |   63:12 |   52 | Limit address. PMBLIMITR_EL1.LIMIT:Zeros(12) is the address of the first byte in memory after the last byte in the profiling buffer. If the smallest implemented translation granule is not 4KB, then bits[N-1:12] are RES0 , where N is the IMPLEMENTATION DEFINED value, Log 2 (smallest implemented translation granule).
| nVM      |     7:7 |    1 | Address mode.
| PMFZ     |     5:5 |    1 | Freeze PMU on SPE event. Stop PMU event counters when PMBSR_EL1 .S == 1.
| FM       |     2:1 |    2 | Fill mode.
| E        |     0:0 |    1 | Profiling Buffer enable

## PMBMAR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SH       |     9:8 |    2 | Profiling Buffer shareability domain. Defines the shareability domain for Normal memory used by the Profiling Buffer.
| Attr     |     7:0 |    8 | Profiling Buffer memory type and attributes. Defines the memory type and, for Normal memory, the cacheability attributes, for memory addressed by the Profiling Buffer. The encoding of this field is the same as that of a MAIR_ELx .Attr<n> field, as follows: Attr Meaning 0b0000dd00 Device memory. See encoding of 'dd' for the type of Device memory. 0b0000dd01 If FEAT_XS is implemented: Device memory with the XS attribute set to 0. See encoding of 'dd' for the type of Device memory. Otherwise, UNPREDICTABLE . 0b0000dd1x UNPREDICTABLE . 0booooiiii where oooo != 0000 and iiii != 0000 Normal memory. See encoding of 'oooo' and 'iiii' for the type of Normal memory. 0b01000000 If FEAT_XS is implemented: Normal Inner Non-cacheable, Outer Non-cacheable memory with the XS attribute set to 0. Otherwise, UNPREDICTABLE . 0b10100000 If FEAT_XS is implemented: Normal Inner Write-through Cacheable, Outer Write-through Cacheable, Read-Allocate, No-Write Allocate, Non-transient memory with the XS attribute set to 0. Otherwise, UNPREDICTABLE . 0b11110000 If FEAT_MTE2 is implemented: Tagged Normal Inner Write-Back, Outer Write-Back, Read-Allocate, Write-Allocate Non-transient memory. Otherwise, UNPREDICTABLE . 0bxxxx0000 where xxxx != 0000 and xxxx != 0100 and xxxx != 1010 and xxxx != 1111 UNPREDICTABLE . dd is encoded as follows: 'dd' Meaning 0b00 Device-nGnRnE memory. 0b01 Device-nGnRE memory. 0b10 Device-nGRE memory. 0b11 Device-GRE memory. oooo is encoded as follows: 'oooo' Meaning 0b0000 See encoding of Attr. 0b00RW where RW != 00 Normal memory, Outer Write-Through Transient. 0b0100 Normal memory, Outer Non-cacheable. 0b01RW where RW != 00 Normal memory, Outer Write-Back Transient. 0b10RW Normal memory, Outer Write-Through Non-transient. 0b11RW Normal memory, Outer Write-Back Non-transient. R encodes the Outer Read-Allocate policy and W encodes the Outer Write-Allocate policy. iiii is encoded as follows: 'iiii' Meaning 0b0000 See encoding of Attr. 0b00RW where RW != 00 Normal memory, Inner Write-Through Transient. 0b0100 Normal memory, Inner Non-cacheable. 0b01RW where RW != 00 Normal memory, Inner Write-Back Transient. 0b10RW Normal memory, Inner Write-Through Non-transient. 0b11RW Normal memory, Inner Write-Back Non-transient. R encodes the Inner Read-Allocate policy and W encodes the Inner Write-Allocate policy. In oooo and iiii , R and W are encoded as follows: 'R' or 'W' Meaning 0b0 No Allocate. 0b1 Allocate. When FEAT_XS is implemented, stage 1 Inner Write-Back Cacheable, Outer Write-Back Cacheable memory types have the XS attribute set to 0.

## PMBSR_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the Profiling Buffer management event.
| DL                     |   19:19 |    1 | Partial record lost. Following a buffer management event other than an asynchronous External abort, indicates whether the last record written to the Profiling Buffer is complete.
| EA                     |   18:18 |    1 | External abort.
| S                      |   17:17 |    1 | Service. Indicates that a Profiling Buffer management event has been recorded.
| COLL                   |   16:16 |    1 | Collision detected.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the Profiling Buffer management event. The syndrome contents for each Profiling Buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Profiling Buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## PMBSR_EL2 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the Profiling Buffer management event.
| DL                     |   19:19 |    1 | Partial record lost. Following a buffer management event other than an asynchronous External abort, indicates whether the last record written to the Profiling Buffer is complete.
| EA                     |   18:18 |    1 | External abort.
| S                      |   17:17 |    1 | Service. Indicates that a Profiling Buffer management event has been recorded.
| COLL                   |   16:16 |    1 | Collision detected.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the Profiling Buffer management event. The syndrome contents for each Profiling Buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Profiling Buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## PMBSR_EL3 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the Profiling Buffer management event.
| DL                     |   19:19 |    1 | Partial record lost. Following a buffer management event other than an asynchronous External abort, indicates whether the last record written to the Profiling Buffer is complete.
| EA                     |   18:18 |    1 | External abort.
| S                      |   17:17 |    1 | Service. Indicates that a Profiling Buffer management event has been recorded.
| COLL                   |   16:16 |    1 | Collision detected.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the Profiling Buffer management event. The syndrome contents for each Profiling Buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Profiling Buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## PMCCFILTR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VS       |   57:56 |    2 | SVE mode filtering. Controls counting cycles in Streaming and Non-streaming SVE modes.
| P        |   31:31 |    1 | EL1 filtering. Controls counting cycles in EL1.
| U        |   30:30 |    1 | EL0 filtering. Controls counting cycles in EL0.
| NSK      |   29:29 |    1 | Non-secure EL1 filtering. Controls counting cycles in Non-secure EL1. If PMCCFILTR_EL0.NSK is not equal to PMCCFILTR_EL0.P, then the PE does not count cycles in Non-secure EL1. Otherwise, this mechanism has no effect on filtering of cycles in Non-secure EL1.
| NSU      |   28:28 |    1 | Non-secure EL0 filtering. Controls counting cycles in Non-secure EL0. If PMCCFILTR_EL0.NSU is not equal to PMCCFILTR_EL0.U, then the PE does not count cycles in Non-secure EL0. Otherwise, this mechanism has no effect on filtering of cycles in Non-secure EL0.
| NSH      |   27:27 |    1 | EL2 filtering. Controls counting cycles in EL2.
| M        |   26:26 |    1 | EL3 filtering. Controls counting cycles in  EL3. If PMCCFILTR_EL0.M is not equal to PMCCFILTR_EL0.P, then the PE does not count cycles in  EL3. Otherwise, this mechanism has no effect on filtering of cycles in  EL3.
| SH       |   24:24 |    1 | Secure EL2 filtering. Controls counting cycles in Secure EL2. If PMCCFILTR_EL0.SH is equal to PMCCFILTR_EL0.NSH, then the PE does not count cycles in Secure EL2. Otherwise, this mechanism has no effect on filtering of cycles in Secure EL2.
| T        |   23:23 |    1 | Non-Transactional state filtering field. Controls counting of cycles in Non-transactional state.
| RLK      |   22:22 |    1 | Realm EL1 filtering. Controls counting cycles in Realm EL1. If PMCCFILTR_EL0.RLK is not equal to PMCCFILTR_EL0.P, then the PE does not count cycles in Realm EL1. Otherwise, this mechanism has no effect on filtering of cycles in Realm EL1.
| RLU      |   21:21 |    1 | Realm EL0 filtering. Controls counting cycles in Realm EL0. If PMCCFILTR_EL0.RLU is not equal to PMCCFILTR_EL0.U, then the PE does not count cycles in Realm EL0. Otherwise, this mechanism has no effect on filtering of cycles in Realm EL0.
| RLH      |   20:20 |    1 | Realm EL2 filtering. Controls counting cycles in Realm EL2. If PMCCFILTR_EL0.RLH is equal to PMCCFILTR_EL0.NSH, then the PE does not count cycles in Realm EL2. Otherwise, this mechanism has no effect on filtering of cycles in Realm EL2.

## PMCEID0_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| IDhi<n>  |   63:32 |   32 | IDhi[n] corresponds to Common event ( 0x4000 + n). For each bit:
| ID<n>    |    31:0 |   32 | ID[n] corresponds to Common event n. For each bit:

## PMCEID1_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| IDhi<n>  |   63:32 |   32 | IDhi[n] corresponds to Common event ( 0x4020 + n). For each bit:
| ID<n>    |    31:0 |   32 | ID[n] corresponds to Common event ( 0x0020 + n). For each bit:

## PMCNTENCLR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Fixed-function counter <m> disable. On writes, allows software to disable fixed-function counter <m>. On reads, returns the fixed-function counter <m> enable status.
| C        |   31:31 |    1 | PMCCNTR_EL0 disable. On writes, allows software to disable PMCCNTR_EL0 . On reads, returns the PMCCNTR_EL0 enable status.
| P<m>     |    30:0 |   31 | PMEVCNTR<m>_EL0 disable. On writes, allows software to disable PMEVCNTR<m>_EL0 . On reads, returns the PMEVCNTR<m>_EL0 enable status.

## PMCNTENSET_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Fixed-function counter <m> enable. On writes, allows software to enable fixed-function counter <m>. On reads, returns the fixed-function counter <m> enable status.
| C        |   31:31 |    1 | PMCCNTR_EL0 enable. On writes, allows software to enable PMCCNTR_EL0 . On reads, returns the PMCCNTR_EL0 enable status.
| P<m>     |    30:0 |   31 | PMEVCNTR<m>_EL0 enable. On writes, allows software to enable PMEVCNTR<m>_EL0 . On reads, returns the PMEVCNTR<m>_EL0 enable status.

## PMCR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FZS      |   32:32 |    1 | Freeze-on-SPE event. Stop counters when PMBLIMITR_EL1 .{PMFZ,E} is {1,1} and profiling is stopped.
| IMP      |   31:24 |    8 | Implementer code. If this field is zero, then PMCR_EL0.IDCODE is RES0 and software must use MIDR_EL1 to identify the PE. Otherwise, this field and PMCR_EL0.IDCODE identify the PMU implementation to software. The implementer codes are allocated by Arm. A nonzero value has the same interpretation as MIDR_EL1 .Implementer.
| IDCODE   |   23:16 |    8 | Identification code. Arm deprecates use of this field. Each implementer must maintain a list of identification codes that are specific to the implementer. A specific implementation is identified by the combination of the implementer code and the identification code.
| N        |   15:11 |    5 | Indicates the number of event counters implemented. This value is in the range of 0b00000 - 0b11111 . If the value is 0b00000 , then only PMCCNTR_EL0 is implemented. If the value is 0b11111 , then PMCCNTR_EL0 and 31 event counters are implemented. When EL2 is implemented and enabled for the current Security state, reads of this field from EL1 and EL0 return the Effective value of MDCR_EL2 .HPMN.
| FZO      |     9:9 |    1 | Freeze-on-overflow. Stop event counters on overflow.
| LP       |     7:7 |    1 | Long event counter enable. Determines when unsigned overflow is recorded by PMOVSCLR_EL0 .P[n].
| LC       |     6:6 |    1 | Long cycle counter enable. Determines when unsigned overflow is recorded by PMOVSCLR_EL0 .C.
| DP       |     5:5 |    1 | Disable cycle counter when event counting is prohibited.
| X        |     4:4 |    1 | Enable export of events in an IMPLEMENTATION DEFINED PMU event export bus.
| D        |     3:3 |    1 | Clock divider.
| C        |     2:2 |    1 | Cycle counter reset. The effects of writing to this field are:
| P        |     1:1 |    1 | Event counter reset.
| E        |     0:0 |    1 | Enable.

## PMECR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SSE      |     4:3 |    2 | Snapshot Enable. Controls the generation of Capture events.
| KPME     |     2:2 |    1 | Local (Kernel) PMU Exception Enable. Enables PMU Profiling exceptions taken to the current Exception level.
| PMEE     |     1:0 |    2 | Performance Monitors Exception Enable. Controls the generation of the PMUIRQ signal and the PMU Profiling exception at EL0 and EL1.

## PMICFILTR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SYNC     |   58:58 |    1 | Synchronous mode. Controls whether a PMU Profiling exception generated by the counter is synchronous or asynchronous.
| VS       |   57:56 |    2 | SVE mode filtering. Controls counting instructions in Streaming and Non-streaming SVE modes.
| P        |   31:31 |    1 | EL1 filtering. Controls counting instructions in EL1.
| U        |   30:30 |    1 | EL0 filtering. Controls counting instructions in EL0.
| NSK      |   29:29 |    1 | Non-secure EL1 filtering. Controls counting instructions in Non-secure EL1. If PMICFILTR_EL0.NSK is not equal to PMICFILTR_EL0.P, then the PE does not count instructions in Non-secure EL1. Otherwise, this mechanism has no effect on filtering of instructions in Non-secure EL1.
| NSU      |   28:28 |    1 | Non-secure EL0 filtering. Controls counting instructions in Non-secure EL0. If PMICFILTR_EL0.NSU is not equal to PMICFILTR_EL0.U, then the PE does not count instructions in Non-secure EL0. Otherwise, this mechanism has no effect on filtering of instructions in Non-secure EL0.
| NSH      |   27:27 |    1 | EL2 filtering. Controls counting instructions in EL2.
| M        |   26:26 |    1 | EL3 filtering. Controls counting instructions in  EL3. If PMICFILTR_EL0.M is not equal to PMICFILTR_EL0.P, then the PE does not count instructions in  EL3. Otherwise, this mechanism has no effect on filtering of instructions in  EL3.
| SH       |   24:24 |    1 | Secure EL2 filtering. Controls counting instructions in Secure EL2. If PMICFILTR_EL0.SH is equal to PMICFILTR_EL0.NSH, then the PE does not count instructions in Secure EL2. Otherwise, this mechanism has no effect on filtering of instructions in Secure EL2.
| T        |   23:23 |    1 | Non-Transactional state filtering field. Controls counting of instructions in Non-transactional state.
| RLK      |   22:22 |    1 | Realm EL1 filtering. Controls counting instructions in Realm EL1. If PMICFILTR_EL0.RLK is not equal to PMICFILTR_EL0.P, then the PE does not count instructions in Realm EL1. Otherwise, this mechanism has no effect on filtering of instructions in Realm EL1.
| RLU      |   21:21 |    1 | Realm EL0 filtering. Controls counting instructions in Realm EL0. If PMICFILTR_EL0.RLU is not equal to PMICFILTR_EL0.U, then the PE does not count instructions in Realm EL0. Otherwise, this mechanism has no effect on filtering of instructions in Realm EL0.
| RLH      |   20:20 |    1 | Realm EL2 filtering. Controls counting instructions in Realm EL2. If PMICFILTR_EL0.RLH is equal to PMICFILTR_EL0.NSH, then the PE does not count instructions in Realm EL2. Otherwise, this mechanism has no effect on filtering of instructions in Realm EL2.
| evtCount |    15:0 |   16 | Event to count.

## PMINTENCLR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m> disable. On writes, allows software to disable the interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m>. On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m> enable status.
| C        |   31:31 |    1 | Interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 disable. On writes, allows software to disable the interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 . On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 enable status.
| P<m>     |    30:0 |   31 | Interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 disable. On writes, allows software to disable the interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 . On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 enable status.

## PMINTENSET_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m> enable. On writes, allows software to enable the interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m>. On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of fixed-function counter <m> enable status.
| C        |   31:31 |    1 | Interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 enable. On writes, allows software to enable the interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 . On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of PMCCNTR_EL0 enable status.
| P<m>     |    30:0 |   31 | Interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 enable. On writes, allows software to enable the interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 . On reads, returns the interrupt request or PMU Profiling exception on unsigned overflow of PMEVCNTR<m>_EL0 enable status.

## PMMIR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| SME       |   28:28 |    1 | PMUv3 for SME. Adds support for the Streaming SVE mode filter.
| EDGE      |   27:24 |    4 | PMU event edge detection. With PMMIR_EL1.THWIDTH, indicates implementation of event counter thresholding features.
| THWIDTH   |   23:20 |    4 | PMEVTYPER<n>_EL0 .TH width. Indicates implementation of the FEAT_PMUv3_TH feature, and, if implemented, the size of the PMEVTYPER<n>_EL0 .TH field.
| BUS_WIDTH |   19:16 |    4 | Bus width. Indicates the number of bytes each BUS_ACCESS event relates to. Encoded as Log 2 (number of bytes), plus one.
| BUS_SLOTS |    15:8 |    8 | Bus count. The largest value by which the BUS_ACCESS event might increment in a single BUS_CYCLES cycle.
| SLOTS     |     7:0 |    8 | Operation width. The largest value by which the STALL_SLOT event might increment in a single cycle. If the STALL_SLOT event is not implemented, this field might read as zero.

## PMOVSCLR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Unsigned overflow flag for fixed-function counter <m> clear. On writes, allows software to clear the unsigned overflow flag for fixed-function counter <m> to 0. On reads, returns the unsigned overflow flag for fixed-function counter <m> overflow status.
| C        |   31:31 |    1 | Unsigned overflow flag for PMCCNTR_EL0 clear. On writes, allows software to clear the unsigned overflow flag for PMCCNTR_EL0 to 0. On reads, returns the unsigned overflow flag for PMCCNTR_EL0 overflow status.
| P<m>     |    30:0 |   31 | Unsigned overflow flag for PMEVCNTR<m>_EL0 clear. On writes, allows software to clear the unsigned overflow flag for PMEVCNTR<m>_EL0 to 0. On reads, returns the unsigned overflow flag for PMEVCNTR<m>_EL0 overflow status.

## PMOVSSET_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Unsigned overflow flag for fixed-function counter <m> set. On writes, allows software to set the unsigned overflow flag for fixed-function counter <m> to 1. On reads, returns the unsigned overflow flag for fixed-function counter <m> overflow status.
| C        |   31:31 |    1 | Unsigned overflow flag for PMCCNTR_EL0 set. On writes, allows software to set the unsigned overflow flag for PMCCNTR_EL0 to 1. On reads, returns the unsigned overflow flag for PMCCNTR_EL0 overflow status.
| P<m>     |    30:0 |   31 | Unsigned overflow flag for PMEVCNTR<m>_EL0 set. On writes, allows software to set the unsigned overflow flag for PMEVCNTR<m>_EL0 to 1. On reads, returns the unsigned overflow flag for PMEVCNTR<m>_EL0 overflow status.

## PMSCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EnVM     |   11:11 |    1 | Reserved for software use in nested virtualization. See also PMSCR_EL2 .EnVM.
| KE       |   10:10 |    1 | Kernel exception enable for SPE Profiling exceptions taken to EL1.
| EE       |     9:8 |    2 | Exception Enable.
| PCT      |     7:6 |    2 | Physical Timestamp. If timestamp sampling is enabled and the Profiling Buffer is owned by EL1, requests which timestamp counter value is collected. If FEAT_ECV is implemented, this is a two-bit field as shown. Otherwise, bit[7] is RES0 .
| TS       |     5:5 |    1 | Timestamp enable.
| PA       |     4:4 |    1 | Physical Address sample enable.
| CX       |     3:3 |    1 | CONTEXTIDR_EL1 sample enable.
| E1SPE    |     1:1 |    1 | EL1 Statistical Profiling Enable.
| E0SPE    |     0:0 |    1 | EL0 Statistical Profiling Enable. Controls sampling at EL0 when HCR_EL2 .TGE == 0 or if EL2 is disabled or not implemented.

## PMSCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EnVM     |   11:11 |    1 | Enable use of physical address Profiling Buffer pointers.
| KE       |   10:10 |    1 | Kernel exception enable for SPE Profiling exceptions taken to EL2.
| EE       |     9:8 |    2 | Exception Enable.
| PCT      |     7:6 |    2 | Physical Timestamp. If timestamp sampling is enabled, determines which counter is collected. The behavior depends on the Profiling Buffer owning Exception level. If FEAT_ECV is implemented, this is a two-bit field as shown. Otherwise, bit[7] is RES0 .
| TS       |     5:5 |    1 | Timestamp Enable.
| PA       |     4:4 |    1 | Physical Address Sample Enable.
| CX       |     3:3 |    1 | CONTEXTIDR_EL2 Sample Enable.
| E2SPE    |     1:1 |    1 | EL2 Statistical Profiling Enable.
| E0HSPE   |     0:0 |    1 | EL0 Statistical Profiling Enable.

## PMSELR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SEL      |     4:0 |    5 | Event counter select. Selects the counter accessed by subsequent accesses to PMXEVTYPER_EL0 and PMXEVCNTR_EL0 .

## PMSEVFR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| E[63]    |   63:63 |    1 | Filter on IMPLEMENTATION DEFINED event 63.
| E[62]    |   62:62 |    1 | Filter on IMPLEMENTATION DEFINED event 62.
| E[61]    |   61:61 |    1 | Filter on IMPLEMENTATION DEFINED event 61.
| E[60]    |   60:60 |    1 | Filter on IMPLEMENTATION DEFINED event 60.
| E[59]    |   59:59 |    1 | Filter on IMPLEMENTATION DEFINED event 59.
| E[58]    |   58:58 |    1 | Filter on IMPLEMENTATION DEFINED event 58.
| E[57]    |   57:57 |    1 | Filter on IMPLEMENTATION DEFINED event 57.
| E[56]    |   56:56 |    1 | Filter on IMPLEMENTATION DEFINED event 56.
| E[55]    |   55:55 |    1 | Filter on IMPLEMENTATION DEFINED event 55.
| E[54]    |   54:54 |    1 | Filter on IMPLEMENTATION DEFINED event 54.
| E[53]    |   53:53 |    1 | Filter on IMPLEMENTATION DEFINED event 53.
| E[52]    |   52:52 |    1 | Filter on IMPLEMENTATION DEFINED event 52.
| E[51]    |   51:51 |    1 | Filter on IMPLEMENTATION DEFINED event 51.
| E[50]    |   50:50 |    1 | Filter on IMPLEMENTATION DEFINED event 50.
| E[49]    |   49:49 |    1 | Filter on IMPLEMENTATION DEFINED event 49.
| E[48]    |   48:48 |    1 | Filter on IMPLEMENTATION DEFINED event 48.
| E[31]    |   31:31 |    1 | Filter on IMPLEMENTATION DEFINED event 31.
| E[30]    |   30:30 |    1 | Filter on IMPLEMENTATION DEFINED event 30.
| E[29]    |   29:29 |    1 | Filter on IMPLEMENTATION DEFINED event 29.
| E[28]    |   28:28 |    1 | Filter on IMPLEMENTATION DEFINED event 28.
| E[27]    |   27:27 |    1 | Filter on IMPLEMENTATION DEFINED event 27.
| E[26]    |   26:26 |    1 | Filter on IMPLEMENTATION DEFINED event 26.
| E[25]    |   25:25 |    1 | Filter on  SMCU or external coprocessor operation  event.
| E[24]    |   24:24 |    1 | Filter on  Streaming SVE mode  event.
| E[23]    |   23:23 |    1 | Filter on  Data snooped  event.
| E[22]    |   22:22 |    1 | Filter on  Recently fetched  event.
| E[21]    |   21:21 |    1 | Filter on  Cache data modified  event.
| E[20]    |   20:20 |    1 | Filter on  Level 2 data cache miss  event.
| E[19]    |   19:19 |    1 | Filter on  Level 2 data cache access  event.
| E[18]    |   18:18 |    1 | Filter on  Empty predicate  event.
| E[17]    |   17:17 |    1 | Filter on  Partial or empty predicate  event.
| E[16]    |   16:16 |    1 | Filter on  Transactional  event.
| E[15]    |   15:15 |    1 | Filter on IMPLEMENTATION DEFINED event 15.
| E[14]    |   14:14 |    1 | Filter on IMPLEMENTATION DEFINED event 14.
| E[13]    |   13:13 |    1 | Filter on IMPLEMENTATION DEFINED event 13.
| E[12]    |   12:12 |    1 | Filter on IMPLEMENTATION DEFINED event 12.
| E[11]    |   11:11 |    1 | Filter on  Misalignment  event.
| E[10]    |   10:10 |    1 | Filter on  Remote access  event.
| E[9]     |     9:9 |    1 | Filter on  Last Level cache miss  event.
| E[8]     |     8:8 |    1 | Filter on  Last Level cache access  event.
| E[7]     |     7:7 |    1 | Filter on  Mispredicted  event.
| E[6]     |     6:6 |    1 | Filter on  Not taken  event.
| E[5]     |     5:5 |    1 | Filter on  TLB walk  event.
| E[4]     |     4:4 |    1 | Filter on  TLB access  event.
| E[3]     |     3:3 |    1 | Filter on  Level 1 data cache refill or miss  event.
| E[2]     |     2:2 |    1 | Filter on  Level 1 data cache access  event.
| E[1]     |     1:1 |    1 | Filter on  Architecturally retired  event.

## PMSFCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SIMDm    |   52:52 |    1 | SIMD filter mask.
| FPm      |   51:51 |    1 | Floating-point filter mask.
| STm      |   50:50 |    1 | Store filter mask.
| LDm      |   49:49 |    1 | Load filter mask.
| Bm       |   48:48 |    1 | Branch filter mask.
| SIMD     |   20:20 |    1 | SIMD filter enable.
| FP       |   19:19 |    1 | Floating-point filter enable.
| ST       |   18:18 |    1 | Store filter enable.
| LD       |   17:17 |    1 | Load filter enable.
| B        |   16:16 |    1 | Branch filter enable.
| FDS      |     4:4 |    1 | Filter by Data Source.
| FnE      |     3:3 |    1 | Filter by event, inverted.
| FL       |     2:2 |    1 | Filter by latency
| FT       |     1:1 |    1 | Filter by operation type. The filter is the logical OR of the ST, LD and B bits. For example, if LD and ST are both set, both load and store operations are recorded
| FE       |     0:0 |    1 | Filter by event.

## PMSICR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ECOUNT   |   63:56 |    8 | Secondary sample interval counter. This field provides the secondary counter used after the primary counter reaches zero. Whilst the secondary counter is nonzero and profiling is enabled, the secondary counter decrements by 1 for each member of the sample population. The primary counter also continues to decrement since it is also nonzero. When the secondary counter reaches zero, a member of the sampling population is selected for sampling.
| COUNT    |    31:0 |   32 | Primary sample interval counter Provides the primary counter used for sampling. The primary counter is reloaded when the value of this register is zero and the PE moves from a state or Exception level where profiling is disabled to a state or Exception level where profiling is enabled Whilst the primary counter is nonzero and sampling is enabled, the primary counter decrements by 1 for each member of the sample population When the counter reaches zero, the behavior depends on the values of PMSIDR_EL1.ERnd and PMSIRR_EL1.RND If PMSIRR_EL1 .RND == 0 or PMSIDR_EL1.ERnd == 0: A member of the sampling population is selected for sampling The primary counter is reloaded If PMSIRR_EL1 .RND == 1 and PMSIDR_EL1 .ERnd == 1: The secondary counter is set to a random or pseudorandom value in the range 0x00 to 0xFF The primary counter is reloaded

## PMSIDR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| SME       |   32:32 |    1 | SPE for SME. Adds support for the Scalable Matrix Extensions to Statistical Profiling.
| ALTCLK    |   31:28 |    4 | Alternate clock domain.
| FPF       |   27:27 |    1 | Floating-point flag.
| EFT       |   26:26 |    1 | Extended filtering by operation type.
| CRR       |   25:25 |    1 | Call Return branch records.
| PBT       |   24:24 |    1 | Previous branch target Address packet.
| Format    |   23:20 |    4 | Defines the format of the sample records.
| CountSize |   19:16 |    4 | Defines the size of the counters.
| MaxSize   |   15:12 |    4 | Defines the largest size for a single record, rounded up to a power-of-two. If this is the same as the minimum alignment ( PMBIDR_EL1 .Align), then each record is exactly this size.
| Interval  |    11:8 |    4 | Recommended minimum sampling interval. This provides guidance from the implementer to the smallest minimum sampling interval, N.
| FDS       |     7:7 |    1 | Filter by data source.
| FnE       |     6:6 |    1 | Filtering by events, inverted.
| ERnd      |     5:5 |    1 | Defines how the random number generator is used in determining the interval between samples, when enabled by PMSIRR_EL1 .RND.
| LDS       |     4:4 |    1 | Data source indicator for sampled load instructions.
| ArchInst  |     3:3 |    1 | Architectural instruction profiling.
| FL        |     2:2 |    1 | Filtering by latency.
| FT        |     1:1 |    1 | Filtering by operation type.
| FE        |     0:0 |    1 | Filtering by events.

## PMSIRR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| INTERVAL |    31:8 |   24 | Bits [31:8] of the PMSICR_EL1 interval counter reload value. Software must set this to a nonzero value. If software sets this to zero, an UNKNOWN sampling interval is used. Arm recommends that software sets this field to a value greater than or equal to the minimum indicated by PMSIDR_EL1 .Interval. Setting this field to a smaller nonzero value is likely to cause a large number of sample collisions. See Sample collisions .
| RND      |     0:0 |    1 | Controls randomization of the sampling interval.

## PMSLATFR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MINLAT   |    15:0 |   16 | Minimum latency. When PMSFCR_EL1 .FL is 1, defines the minimum total latency for filtered operations. Samples with a total latency less than PMSLATFR_EL1.MINLAT are not recorded.

## PMSNEVFR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| E[63]    |   63:63 |    1 | Filter on IMPLEMENTATION DEFINED event 63.
| E[62]    |   62:62 |    1 | Filter on IMPLEMENTATION DEFINED event 62.
| E[61]    |   61:61 |    1 | Filter on IMPLEMENTATION DEFINED event 61.
| E[60]    |   60:60 |    1 | Filter on IMPLEMENTATION DEFINED event 60.
| E[59]    |   59:59 |    1 | Filter on IMPLEMENTATION DEFINED event 59.
| E[58]    |   58:58 |    1 | Filter on IMPLEMENTATION DEFINED event 58.
| E[57]    |   57:57 |    1 | Filter on IMPLEMENTATION DEFINED event 57.
| E[56]    |   56:56 |    1 | Filter on IMPLEMENTATION DEFINED event 56.
| E[55]    |   55:55 |    1 | Filter on IMPLEMENTATION DEFINED event 55.
| E[54]    |   54:54 |    1 | Filter on IMPLEMENTATION DEFINED event 54.
| E[53]    |   53:53 |    1 | Filter on IMPLEMENTATION DEFINED event 53.
| E[52]    |   52:52 |    1 | Filter on IMPLEMENTATION DEFINED event 52.
| E[51]    |   51:51 |    1 | Filter on IMPLEMENTATION DEFINED event 51.
| E[50]    |   50:50 |    1 | Filter on IMPLEMENTATION DEFINED event 50.
| E[49]    |   49:49 |    1 | Filter on IMPLEMENTATION DEFINED event 49.
| E[48]    |   48:48 |    1 | Filter on IMPLEMENTATION DEFINED event 48.
| E[31]    |   31:31 |    1 | Filter on IMPLEMENTATION DEFINED event 31.
| E[30]    |   30:30 |    1 | Filter on IMPLEMENTATION DEFINED event 30.
| E[29]    |   29:29 |    1 | Filter on IMPLEMENTATION DEFINED event 29.
| E[28]    |   28:28 |    1 | Filter on IMPLEMENTATION DEFINED event 28.
| E[27]    |   27:27 |    1 | Filter on IMPLEMENTATION DEFINED event 27.
| E[26]    |   26:26 |    1 | Filter on IMPLEMENTATION DEFINED event 26.
| E[25]    |   25:25 |    1 | Filter on  Not SMCU or coprocessor operation  event.
| E[24]    |   24:24 |    1 | Filter on  Non-streaming SVE mode  event.
| E[23]    |   23:23 |    1 | Filter on  Data not snooped  event.
| E[22]    |   22:22 |    1 | Filter on  Not recently fetched  event.
| E[21]    |   21:21 |    1 | Filter on  Cache data not modified  event.
| E[20]    |   20:20 |    1 | Filter on  Level 2 data cache hit  event.
| E[19]    |   19:19 |    1 | Filter on  No level 2 data cache access  event.
| E[18]    |   18:18 |    1 | Filter on  Not empty predicate  event.
| E[17]    |   17:17 |    1 | Filter on  Not partial predicate  event.
| E[16]    |   16:16 |    1 | Filter on  Not transactional  event.
| E[15]    |   15:15 |    1 | Filter on IMPLEMENTATION DEFINED event 15.
| E[14]    |   14:14 |    1 | Filter on IMPLEMENTATION DEFINED event 14.
| E[13]    |   13:13 |    1 | Filter on IMPLEMENTATION DEFINED event 13.
| E[12]    |   12:12 |    1 | Filter on IMPLEMENTATION DEFINED event 12.
| E[11]    |   11:11 |    1 | Filter on  Aligned  event.
| E[10]    |   10:10 |    1 | Filter on  No remote access  event.
| E[9]     |     9:9 |    1 | Filter on  Last Level cache hit  event.
| E[8]     |     8:8 |    1 | Filter on  No Last Level cache access  event.
| E[7]     |     7:7 |    1 | Filter on  Correctly predicted  event.
| E[6]     |     6:6 |    1 | Filter on  Taken  event.
| E[5]     |     5:5 |    1 | Filter on  TLB hit  event.
| E[4]     |     4:4 |    1 | Filter on  No TLB access  event.
| E[3]     |     3:3 |    1 | Filter on  Level 1 data cache hit  event.
| E[2]     |     2:2 |    1 | Filter on  No Level 1 data cache access  event.
| E[1]     |     1:1 |    1 | Filter on  Speculative  event.

## PMSSCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NC       |   32:32 |    1 | No Capture. Indicates whether the PMU counters have been captured.
| SS       |     0:0 |    1 | Snapshot Capture and Status.

## PMSWINC_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P<m>     |    30:0 |   31 | Software increment.

## PMUACR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | EL0 accesses to fixed-function counter <m> enable.
| C        |   31:31 |    1 | EL0 accesses to PMCCNTR_EL0 enable.
| P<m>     |    30:0 |   31 | EL0 accesses to PMEVCNTR<m>_EL0 enable.

## PMUSERENR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TID      |     6:6 |    1 | Trap ID registers. Traps EL0 read access to common event identification registers.
| IR       |     5:5 |    1 | Instruction counter Read-only. When PMUSERENR_EL0.UEN is 1, EL0 reads of the instruction counter and EL0 writes to PMZR_EL0 are enabled by PMUSERENR_EL0.UEN, unless trapped by another control, and PMUSERENR_EL0.IR controls the behavior of EL0 writes to the instruction counter and PMZR_EL0 .
| UEN      |     4:4 |    1 | User Enable, with access controlled by PMUACR_EL1 . Enables EL0 read/write access to PMU registers, other than PMCR_EL0 .
| ER       |     3:3 |    1 | Event counters Read enable or Read-only. When PMUSERENR_EL0.{UEN,EN} is {0,0}, PMUSERENR_EL0.ER enables EL0 reads of the event counters and EL0 reads and writes of the select register. When PMUSERENR_EL0.UEN is 1, EL0 reads of the event counters and EL0 writes to PMZR_EL0 are enabled by PMUSERENR_EL0.UEN, unless trapped by another control, and PMUSERENR_EL0.ER controls the behavior of EL0 writes to the event counters and PMZR_EL0 .
| CR       |     2:2 |    1 | Cycle counter Read enable or Read-only. When PMUSERENR_EL0.{UEN,EN} is {0,0}, PMUSERENR_EL0.CR enables EL0 reads of the cycle counter. When PMUSERENR_EL0.UEN is 1, EL0 reads of the cycle counter and EL0 writes to PMZR_EL0 are enabled by PMUSERENR_EL0.UEN, unless trapped by another control, and PMUSERENR_EL0.CR controls the behavior of EL0 writes to the cycle counter and PMZR_EL0 .
| SW       |     1:1 |    1 | Software increment register Write enable. When PMUSERENR_EL0.UEN is 0, PMUSERENR_EL0.SW enables EL0 writes to the Software increment register. When PMUSERENR_EL0.UEN is 1, EL0 writes to the Software increment register are enabled by PMUSERENR_EL0.UEN, unless trapped by another control, and PMUSERENR_EL0.SW controls the behavior of EL0 writes to the Software increment register.
| EN       |     0:0 |    1 | Enable. Enables EL0 read/write access to PMU registers, other than the instruction counter.

## PMZR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| F<m>     |   32:32 |    1 | Zero fixed-function counter <m>.
| C        |   31:31 |    1 | Zero PMCCNTR_EL0 .
| P<m>     |    30:0 |   31 | Zero PMEVCNTR<m>_EL0 .

## RGSR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SEED     |    23:8 |   16 | Seed register used for generating values returned by RandomAllocationTag().
| TAG      |     3:0 |    4 | Tag generated by the most recent IRG instruction.

## RMR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RR       |     1:1 |    1 | Reset Request. Setting this bit to 1 requests a Warm reset.
| AA64     |     0:0 |    1 | When EL1 can use AArch32, determines which Execution state the PE boots into after a Warm reset:

## RMR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RR       |     1:1 |    1 | Reset Request. Setting this bit to 1 requests a Warm reset.
| AA64     |     0:0 |    1 | When EL2 can use AArch32, determines which Execution state the PE boots into after a Warm reset:

## RMR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RR       |     1:1 |    1 | Reset Request. Setting this bit to 1 requests a Warm reset.
| AA64     |     0:0 |    1 | When EL3 can use AArch32, determines which Execution state the PE boots into after a Warm reset:

## SCR_EL3 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| NSE       |   62:62 |    1 | This field, evaluated with SCR_EL3.NS, selects the Security state of EL2 and lower Exception levels.
| HACDBSEn  |   61:61 |    1 | Enables access to the HACDBSBR_EL2 and HACDBSCONS_EL2 registers at EL2.
| HDBSSEn   |   60:60 |    1 | Enables access to HDBSSBR_EL2 and HDBSSPROD_EL2 registers at EL2.
| FGTEn2    |   59:59 |    1 | Fine-Grained Traps Enable 2. When EL2 is implemented, enables the traps to EL2 controlled by HDFGRTR2_EL2 , HDFGWTR2_EL2 , HFGITR2_EL2 , HFGRTR2_EL2 , and HFGWTR2_EL2 , and controls access to those registers.
| EnDSE     |   58:58 |    1 | Enable for delegated SError exceptions pended by SCR_EL3.DSE.
| DSE       |   57:57 |    1 | Delegated SError exception for EL2, EL1, and EL0.
| EnIDCP128 |   55:55 |    1 | Enables access to IMPLEMENTATION DEFINED 128-bit System registers.
| SRMASKEn  |   54:54 |    1 | Enables access to the following MASK registers: CPACRMASK_EL1 , and CPACRMASK_EL12 . SCTLRMASK_EL1 , and SCTLRMASK_EL12 . SCTLR2MASK_EL1 , and SCTLR2MASK_EL12 . TCRMASK_EL1 , and TCRMASK_EL12 . TCR2MASK_EL1 , and TCR2MASK_EL12 . ACTLRMASK_EL1 and ACTLRMASK_EL12 , if they are implemented. CPTRMASK_EL2 . SCTLRMASK_EL2 . SCTLR2MASK_EL2 . TCRMASK_EL2 . TCR2MASK_EL2 . ACTLRMASK_EL2 , if it is implemented.
| PFAREn    |   53:53 |    1 | Enable access to Physical Fault Address Registers. When disabled, accesses to Physical Fault Address Registers generate a trap to EL3.
| TWERR     |   52:52 |    1 | Trap writes of Error Record registers. Enables a trap to EL3 on writes of Error Record registers.
| TMEA      |   51:51 |    1 | Trap Masked External Aborts. Controls whether a masked error exception at a lower Exception level is taken to EL3.
| EnFPM     |   50:50 |    1 | Enables direct and indirect accesses to FPMR from EL2, EL1, and EL0. When accesses to FPMR are disabled by this control: Direct accesses to FPMR from EL2, EL1, and EL0 are trapped to EL3 and reported with EC syndrome value 0x18 . Execution of FP8 data-processing instructions that indirectly access FPMR is UNDEFINED at EL2, EL1 and EL0.
| MECEn     |   49:49 |    1 | Enables access to the following EL2 MECID registers, from EL2: MECID_P0_EL2 . MECID_A0_EL2 MECID_P1_EL2 MECID_A1_EL2 VMECID_P_EL2 VMECID_A_EL2 Accesses to these registers are trapped and reported using EC syndrome value 0x18 .
| GPF       |   48:48 |    1 | Controls the reporting of Granule protection faults at EL0, EL1 and EL2.
| D128En    |   47:47 |    1 | 128-bit System Register trap control. Enables access to 128-bit System Registers via MRRS , MSRR instructions. MRRS and MSRR accesses from EL1 and EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x14 : TTBR0_EL1 . TTBR1_EL1 . RCWMASK_EL1 , RCWSMASK_EL1 . PAR_EL1 . MRRS and MSRR accesses from EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x14 : TTBR1_EL2 and accesses using the register name TTBR1_EL12. TTBR0_EL2 and accesses using the register name TTBR0_EL12. VTTBR_EL2 .
| AIEn      |   46:46 |    1 | MAIR2_ELx, AMAIR2_ELx Register access trap control. Accesses from EL1 and EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x18 : AMAIR2_EL1 . MAIR2_EL1 . Accesses from EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x18 : AMAIR2_EL2 and accesses using the register name AMAIR2_EL12. MAIR2_EL2 and accesses using the register name MAIR2_EL12.
| PIEn      |   45:45 |    1 | Permission Indirection, Overlay Register access trap control. Enables access to Permission Indirection and Overlay registers. Accesses from EL0, EL1 and EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x18 : POR_EL0 . Accesses from EL1 and EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x18 : PIRE0_EL1 . PIR_EL1 . POR_EL1 . S2POR_EL1 . Accesses from EL2 using AArch64 to the following registers are trapped and reported using EC syndrome value 0x18 : PIRE0_EL2 and accesses using the register name PIRE0_EL12. PIR_EL2 and accesses using the register name PIR_EL12. POR_EL2 and accesses using the register name POR_EL12. S2PIR_EL2 .
| SCTLR2En  |   44:44 |    1 | SCTLR2_ELx register trap control. Enables access to SCTLR2_EL1 and SCTLR2_EL2 registers.
| TCR2En    |   43:43 |    1 | TCR2_ELx register trap control. Enables access to TCR2_EL1 and TCR2_EL2 registers.
| RCWMASKEn |   42:42 |    1 | RCW and RCWS Mask register trap control. Enables access to RCWMASK_EL1 , RCWSMASK_EL1 .
| EnTP2     |   41:41 |    1 | Traps instructions executed at EL2, EL1, and EL0 that access TPIDR2_EL0 to EL3. The exception is reported using EC syndrome value 0x18 .
| TRNDR     |   40:40 |    1 | Controls trapping of reads of RNDR and RNDRRS . The exception is reported using EC syndrome value 0x18 .
| GCSEn     |   39:39 |    1 | Guarded Control Stack enable. Controls access to the Guarded Control Stack registers from EL2, EL1, and EL0, and controls whether the Guarded Control Stack is enabled. The Guarded Control Stack registers trapped by this mechanism are: GCSCRE0_EL1 . GCSCR_EL1 . GCSCR_EL2 . GCSCR_EL12. GCSPR_EL0 . GCSPR_EL1 . GCSPR_EL2 . GCSPR_EL12.
| HXEn      |   38:38 |    1 | Enables access to the HCRX_EL2 register at EL2 from EL3.
| ADEn      |   37:37 |    1 | Enables access to the ACCDATA_EL1 register at EL1 and EL2.
| EnAS0     |   36:36 |    1 | Traps execution of an ST64BV0 instruction at EL0, EL1, or EL2 to EL3.
| AMVOFFEN  |   35:35 |    1 | Activity Monitors Virtual Offsets Enable.
| TME       |   34:34 |    1 | Enables access to the TSTART, TCOMMIT, TTEST and TCANCEL instructions at EL0, EL1 and EL2.
| TWEDEL    |   33:30 |    4 | TWE Delay. A 4-bit unsigned number that, when SCR_EL3.TWEDEn is 1, encodes the minimum delay in taking a trap of WFE* caused by SCR_EL3.TWE as 2 (TWEDEL + 8) cycles.
| TWEDEn    |   29:29 |    1 | TWE Delay Enable. Enables a configurable delayed trap of the WFE* instruction caused by SCR_EL3.TWE. Traps are reported using EC syndrome value 0x01 .
| ECVEn     |   28:28 |    1 | ECV Enable. Enables access to the CNTPOFF_EL2 register.
| FGTEn     |   27:27 |    1 | Fine-Grained Traps Enable. When EL2 is implemented, enables the traps to EL2 controlled by HAFGRTR_EL2 , HDFGRTR_EL2 , HDFGWTR_EL2 , HFGRTR_EL2 , HFGITR_EL2 , and HFGWTR_EL2 , and controls access to those registers. If EL2 is not implemented but EL3 is implemented, FEAT_FGT implements the MDCR_EL3 .TDCC traps.
| ATA       |   26:26 |    1 | Allocation Tag Access. Controls access to Allocation Tags, System registers for Memory tagging, and prevention of Tag checking, at EL2, EL1 and EL0.
| EnSCXT    |   25:25 |    1 | Enables access to the SCXTNUM_EL2 , SCXTNUM_EL1 , and SCXTNUM_EL0 registers.
| TID5      |   23:23 |    1 | Trap ID group 5. EL2 and EL1 reads of the group 5 ID register GMID_EL1 are trapped to EL3, reported using EC syndrome value 0x18 , unless the instruction generates a higher priority exception.
| TID3      |   22:22 |    1 | Trap ID group 3. EL2 and EL1 reads of the following group 3 registers are trapped to EL3, reported using EC syndrome value 0x18 , unless the instruction generates a higher priority exception: ID_PFR0_EL1 , ID_PFR1_EL1 , ID_DFR0_EL1 , ID_AFR0_EL1 , ID_MMFR0_EL1 , ID_MMFR1_EL1 , ID_MMFR2_EL1 , ID_MMFR3_EL1 , ID_ISAR0_EL1 , ID_ISAR1_EL1 , ID_ISAR2_EL1 , ID_ISAR3_EL1 , ID_ISAR4_EL1 , ID_ISAR5_EL1 , MVFR0_EL1 , MVFR1_EL1 , and MVFR2_EL1 . ID_AA64PFR0_EL1 , ID_AA64PFR1_EL1 , ID_AA64DFR0_EL1 , ID_AA64DFR1_EL1 , ID_AA64ISAR0_EL1 , ID_AA64ISAR1_EL1 , ID_AA64MMFR0_EL1 , ID_AA64MMFR1_EL1 , ID_AA64AFR0_EL1 , and ID_AA64AFR1_EL1 . ID_PFR2_EL1 , ID_MMFR4_EL1 and ID_MMFR5_EL1 . ID_AA64MMFR3_EL1 . ID_AA64MMFR4_EL1 . ID_AA64PFR2_EL1 . ID_AA64MMFR2_EL1 and ID_ISAR6_EL1 . ID_DFR1_EL1 . ID_AA64ZFR0_EL1 . ID_AA64SMFR0_EL1 . ID_AA64ISAR2_EL1 . This field traps all MRS accesses to registers in the following range that are not already mentioned in this field description: op0 == 3, op1 == 0, CRn == 0, CRm == {2-7}, op2 == {0-7}.
| FIEN      |   21:21 |    1 | Fault Injection enable. Trap accesses to the registers ERXPFGCDN_EL1 , ERXPFGCTL_EL1 , and ERXPFGF_EL1 from EL1 and EL2 to EL3, reported using EC syndrome value 0x18 .
| NMEA      |   20:20 |    1 | Non-maskable External Aborts. Controls whether PSTATE.A masks SError exceptions at EL3.
| EASE      |   19:19 |    1 | External aborts to SError exception vector.
| EEL2      |   18:18 |    1 | Secure EL2 Enable.
| API       |   17:17 |    1 | Controls the use of the following instructions related to Pointer Authentication. PACGA. AUTDA, AUTDB, AUTDZA, AUTDZB, AUTIA, AUTIA1716, AUTIASP, AUTIAZ, AUTIB, AUTIB1716, AUTIBSP, AUTIBZ, AUTIZA, AUTIZB, PACDA, PACDB, PACDZA, PACDZB, PACIA, PACIA1716, PACIASP, PACIAZ, PACIB, PACIB1716, PACIBSP, PACIBZ, PACIZA, PACIZB, RETAA, RETAB, BRAA, BRAB, BLRAA, BLRAB, BRAAZ, BRABZ, BLRAAZ, BLRABZ, ERETAA, ERETAB, LDRAA and LDRAB, when any of the following are true: In EL0, when the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, and the associated SCTLR_EL1 .En<N><M> == 1. In EL0, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, and the associated SCTLR_EL2 .En<N><M> == 1. In EL1, when the associated SCTLR_EL1 .En<N><M> == 1. In EL2, when the associated SCTLR_EL2 .En<N><M> == 1. When FEAT_PAuth_LR is implemented, AUTIASPPC, AUTIASPPCR, AUTIA171615, AUTIBSPPC, AUTIBSPPCR, AUTIB171615, PACIASPPC, PACNBIASPPC, PACIA171615, PACIBSPPC, PACNBIBSPPC, PACIB171615, RETAASPPC, RETAASPPCR, RETABSPPC, RETABSPPCR, when any of the following are true: In EL0, when the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, and the associated SCTLR_EL1 .En<N><M> == 1. In EL0, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, and the associated SCTLR_EL2 .En<N><M> == 1. In EL1, when the associated SCTLR_EL1 .En<N><M> == 1. In EL2, when the associated SCTLR_EL2 .En<N><M> == 1.
| APK       |   16:16 |    1 | Trap registers holding "key" values for Pointer Authentication. Traps accesses to the following registers, using EC syndrome value 0x18 , from EL1 or EL2 to EL3 unless they are trapped to EL2 as a result of the HCR_EL2.APK bit or other traps: APIAKeyLo_EL1 , APIAKeyHi_EL1 , APIBKeyLo_EL1 , APIBKeyHi_EL1 . APDAKeyLo_EL1 , APDAKeyHi_EL1 , APDBKeyLo_EL1 , APDBKeyHi_EL1 . APGAKeyLo_EL1 , and APGAKeyHi_EL1 .
| TERR      |   15:15 |    1 | Trap accesses of Error Record registers. Enables a trap to EL3 on accesses of Error Record registers.
| TLOR      |   14:14 |    1 | Trap LOR registers. Traps accesses to the LORSA_EL1 , LOREA_EL1 , LORN_EL1 , LORC_EL1 , and LORID_EL1 registers from EL1 and EL2 to EL3, unless the access has been trapped to EL2.
| TWE       |   13:13 |    1 | Traps EL2, EL1, and EL0 execution of WFE instructions to EL3, from any Security state and both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFET instruction.
| TWI       |   12:12 |    1 | Traps EL2, EL1, and EL0 execution of WFI instructions to EL3, from any Security state and both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFIT instruction.
| ST        |   11:11 |    1 | Traps Secure EL1 accesses to the Counter-timer Physical Secure timer registers to EL3, from AArch64 state only, reported using EC syndrome value 0x18 .
| RW        |   10:10 |    1 | Execution state control for lower Exception levels.
| SIF       |     9:9 |    1 | Secure instruction fetch. When the PE is in Secure state, this bit disables instruction execution from memory marked in the first stage of translation as being Non-secure.
| HCE       |     8:8 |    1 | Hypervisor Call instruction enable. Enables HVC instructions at EL3 and, if EL2 is enabled in the current Security state, at EL2 and EL1, in both Execution states, reported using EC syndrome value 0x00 .
| SMD       |     7:7 |    1 | Secure Monitor Call disable. Disables SMC instructions at EL1 and above, from any Security state and both Execution states, reported using EC syndrome value 0x00 .
| EA        |     3:3 |    1 | External Abort and SError exception routing.
| FIQ       |     2:2 |    1 | Physical FIQ Routing.
| IRQ       |     1:1 |    1 | Physical IRQ Routing.
| NS        |     0:0 |    1 | Non-secure bit. This field is used in combination with SCR_EL3.NSE to select the Security state of EL2 and lower Exception levels.

## SCTLR2_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| CPTM0     |   12:12 |    1 | This field controls unprivileged Checked Pointer Arithmetic for Multiplication.
| CPTM      |   11:11 |    1 | This field controls Checked Pointer Arithmetic for Multiplication at EL1.
| CPTA0     |   10:10 |    1 | This field controls unprivileged Checked Pointer Arithmetic for Addition.
| CPTA      |     9:9 |    1 | This field controls Checked Pointer Arithmetic for Addition at EL1.
| EnPACM0   |     8:8 |    1 | PACM Enable at EL0. Controls the effect of a PACM instruction at EL0.
| EnPACM    |     7:7 |    1 | PACM Enable at EL1. Controls the effect of a PACM instruction at EL1.
| EnIDCP128 |     6:6 |    1 | Enables access to IMPLEMENTATION DEFINED 128-bit System registers.
| EASE      |     5:5 |    1 | External Aborts to SError exception vector.
| EnANERR   |     4:4 |    1 | Enable Asynchronous Normal Read Error.
| EnADERR   |     3:3 |    1 | Enable Asynchronous Device Read Error.
| NMEA      |     2:2 |    1 | Non-maskable External Aborts. Controls whether PSTATE.A masks SError exceptions at EL1.

## SCTLR2_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| CPTM0     |   12:12 |    1 | This field controls unprivileged Checked Pointer Arithmetic for Multiplication.
| CPTM      |   11:11 |    1 | This field controls Checked Pointer Arithmetic for Multiplication at EL2.
| CPTA0     |   10:10 |    1 | This field controls unprivileged Checked Pointer Arithmetic for Addition.
| CPTA      |     9:9 |    1 | This field controls Checked Pointer Arithmetic for Addition at EL2.
| EnPACM0   |     8:8 |    1 | PACM Enable at EL0. Controls the effect of a PACM instruction at EL0.
| EnPACM    |     7:7 |    1 | PACM Enable at EL2. Controls the effect of a PACM instruction at EL2.
| EnIDCP128 |     6:6 |    1 | Enables access to IMPLEMENTATION DEFINED 128-bit System registers.
| EASE      |     5:5 |    1 | External Aborts to SError exception vector.
| EnANERR   |     4:4 |    1 | Enable Asynchronous Normal Read Error.
| EnADERR   |     3:3 |    1 | Enable Asynchronous Device Read Error.
| NMEA      |     2:2 |    1 | Non-maskable External Aborts. Controls whether PSTATE.A masks SError exceptions at EL2.
| EMEC      |     1:1 |    1 | Enables MEC. When enabled, memory accesses to the Realm physical address space are associated with a MECID.

## SCTLR2_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CPTM     |   11:11 |    1 | This field controls Checked Pointer Arithmetic for Multiplication at EL3.
| CPTA     |     9:9 |    1 | This field controls Checked Pointer Arithmetic for Addition at EL3.
| EnPACM   |     7:7 |    1 | PACM Enable at EL3. Controls the effect of a PACM instruction at EL3.
| EnANERR  |     4:4 |    1 | Enable Asynchronous Normal Read Error.
| EnADERR  |     3:3 |    1 | Enable Asynchronous Device Read Error.
| EMEC     |     1:1 |    1 | Enables MEC. When enabled, memory accesses to the Realm physical address space are associated with MECID_RL_A_EL3 .

## SCTLR2MASK_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| CPTM0     |   12:12 |    1 | Mask bit for CPTM0.
| CPTM      |   11:11 |    1 | Mask bit for CPTM.
| CPTA0     |   10:10 |    1 | Mask bit for CPTA0.
| CPTA      |     9:9 |    1 | Mask bit for CPTA.
| EnPACM0   |     8:8 |    1 | Mask bit for EnPACM0.
| EnPACM    |     7:7 |    1 | Mask bit for EnPACM.
| EnIDCP128 |     6:6 |    1 | Mask bit for EnIDCP128.
| EASE      |     5:5 |    1 | Mask bit for EASE.
| EnANERR   |     4:4 |    1 | Mask bit for EnANERR.
| EnADERR   |     3:3 |    1 | Mask bit for EnADERR.
| NMEA      |     2:2 |    1 | Mask bit for NMEA.

## SCTLR2MASK_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| CPTM0     |   12:12 |    1 | Mask bit for CPTM0.
| CPTM      |   11:11 |    1 | Mask bit for CPTM.
| CPTA0     |   10:10 |    1 | Mask bit for CPTA0.
| CPTA      |     9:9 |    1 | Mask bit for CPTA.
| EnPACM0   |     8:8 |    1 | Mask bit for EnPACM0.
| EnPACM    |     7:7 |    1 | Mask bit for EnPACM.
| EnIDCP128 |     6:6 |    1 | Mask bit for EnIDCP128.
| EASE      |     5:5 |    1 | Mask bit for EASE.
| EnANERR   |     4:4 |    1 | Mask bit for EnANERR.
| EnADERR   |     3:3 |    1 | Mask bit for EnADERR.
| NMEA      |     2:2 |    1 | Mask bit for NMEA.
| EMEC      |     1:1 |    1 | Mask bit for EMEC.

## SCTLR_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| TIDCP     |   63:63 |    1 | Trap IMPLEMENTATION DEFINED functionality. When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps EL0 accesses to the encodings reserved for IMPLEMENTATION DEFINED functionality to EL1.
| SPINTMASK |   62:62 |    1 | SP Interrupt Mask enable. When SCTLR_EL1.NMI is 1, controls whether PSTATE.SP acts as an interrupt mask, and controls the value of PSTATE.ALLINT on taking an exception to EL1.
| NMI       |   61:61 |    1 | Non-maskable Interrupt enable.
| EnTP2     |   60:60 |    1 | Traps instructions executed at EL0 that access TPIDR2_EL0 to EL1, or to EL2 when EL2 is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1. The exception is reported using EC syndrome value 0x18 .
| TCSO      |   59:59 |    1 | Tag Checking Store Only.
| TCSO0     |   58:58 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, Tag Checking Store Only in EL0.
| EPAN      |   57:57 |    1 | Enhanced Privileged Access Never. When PSTATE.PAN is 1, determines whether an EL1 data access to a page with stage 1 EL0 instruction access permission generates a Permission fault as a result of the Privileged Access Never mechanism.
| EnALS     |   56:56 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an LD64B or ST64B instruction at EL0 to EL1.
| EnAS0     |   55:55 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an ST64BV0 instruction at EL0 to EL1.
| EnASR     |   54:54 |    1 | When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, traps execution of an ST64BV instruction at EL0 to EL1.
| TME       |   53:53 |    1 | Enables the Transactional Memory Extension at EL1.
| TME0      |   52:52 |    1 | Enables the Transactional Memory Extension at EL0.
| TMT       |   51:51 |    1 | Forces a trivial implementation of the Transactional Memory Extension at EL1.
| TMT0      |   50:50 |    1 | Forces a trivial implementation of the Transactional Memory Extension at EL0.
| TWEDEL    |   49:46 |    4 | TWE Delay. A 4-bit unsigned number that, when SCTLR_EL1.TWEDEn is 1, encodes the minimum delay in taking a trap of WFE* caused by SCTLR_EL1.nTWE as 2 (TWEDEL + 8) cycles.
| TWEDEn    |   45:45 |    1 | TWE Delay Enable. Enables a configurable delayed trap of the WFE* instruction caused by SCTLR_EL1.nTWE.
| DSSBS     |   44:44 |    1 | Default PSTATE.SSBS value on Exception Entry.
| ATA       |   43:43 |    1 | Allocation Tag Access in EL1. When SCR_EL3 .ATA == 1 and HCR_EL2 .ATA == 1, controls access to Allocation Tags and Tag Check operations in EL1.
| ATA0      |   42:42 |    1 | Allocation Tag Access in EL0. When SCR_EL3 .ATA == 1, HCR_EL2 .ATA == 1, and the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, controls access to Allocation Tags and Tag Check operations in EL0.
| TCF       |   41:40 |    2 | Tag Check Fault in EL1. Controls the effect of Tag Check Faults due to Loads and Stores in EL1.
| TCF0      |   39:38 |    2 | Tag Check Fault in EL0. When the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, controls the effect of Tag Check Faults due to Loads and Stores in EL0.
| ITFSB     |   37:37 |    1 | When synchronous exceptions are not being generated by Tag Check Faults, this field controls whether on exception entry into EL1, all Tag Check Faults due to instructions executed before exception entry, that are reported asynchronously, are synchronized into TFSRE0_EL1 and TFSR_EL1 registers.
| BT1       |   36:36 |    1 | Configures the Branch Type compatibility of the implicit BTI behavior for the following instructions at EL1: PACIASP . PACIBSP . If FEAT_PAuth_LR is implemented, PACIASPPC . If FEAT_PAuth_LR is implemented, PACIBSPPC .
| BT0       |   35:35 |    1 | Configures the Branch Type compatibility of the implicit BTI behavior for the following instructions at EL0: PACIASP . PACIBSP . If FEAT_PAuth_LR is implemented, PACIASPPC . If FEAT_PAuth_LR is implemented, PACIBSPPC .
| EnFPM     |   34:34 |    1 | Enables direct and indirect accesses to FPMR from EL0. When accesses to FPMR are disabled by this control: Direct accesses to FPMR from EL0 are trapped to EL1, or to EL2 when EL2 is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1. These exceptions are reported using EC syndrome value 0x18 . Execution of FP8 data-processing instructions that indirectly access FPMR is UNDEFINED at EL0.
| MSCEn     |   33:33 |    1 | Memory Copy and Memory Set instructions Enable. Enables execution of the Memory Copy and Memory Set instructions at EL0.
| CMOW      |   32:32 |    1 | Controls cache maintenance instruction permission for the following instructions executed at EL0. IC IVAU and DC CIVAC . If FEAT_MTE is implemented, DC CIGDVAC and DC CIGVAC .
| EnIA      |   31:31 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIAKey_EL1 key, in the EL1&0 translation regime.
| EnIB      |   30:30 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIBKey_EL1 key, in the EL1&0 translation regime.
| LSMAOE    |   29:29 |    1 | Load Multiple and Store Multiple Atomicity and Ordering Enable.
| nTLSMD    |   28:28 |    1 | No Trap Load Multiple and Store Multiple to Device-nGRE/Device-nGnRE/Device-nGnRnE memory.
| EnDA      |   27:27 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDAKey_EL1 key, in the EL1&0 translation regime.
| UCI       |   26:26 |    1 | Traps EL0 execution of cache maintenance instructions, to EL1, or to EL2 when it is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1, from AArch64 state only, reported using EC syndrome value 0x18 , as follows: DC CVAU , DC CIVAC , DC CVAC , and IC IVAU . If FEAT_MTE is implemented, DC CIGVAC , DC CIGDVAC , DC CGVAC , and DC CGDVAC . If FEAT_DPB is implemented, DC CVAP . If FEAT_DPB and FEAT_MTE are implemented, DC CGVAP and DC CGDVAP . If FEAT_DPB2 is implemented, DC CVADP . If FEAT_DPB2 and FEAT_MTE are implemented, DC CGVADP and DC CGDVADP .
| EE        |   25:25 |    1 | Endianness of data accesses at EL1, and stage 1 translation table walks in the EL1&0 translation regime.
| E0E       |   24:24 |    1 | Endianness of data accesses at EL0.
| SPAN      |   23:23 |    1 | Set Privileged Access Never, on taking an exception to EL1.
| EIS       |   22:22 |    1 | Exception Entry is Context Synchronizing.
| IESB      |   21:21 |    1 | Implicit Error Synchronization event enable. Possible values are:
| TSCXT     |   20:20 |    1 | Trap EL0 Access to the SCXTNUM_EL0 register, when EL0 is using AArch64.
| WXN       |   19:19 |    1 | Write permission implies XN (Execute-never). For the EL1&0 translation regime, this bit can restrict execute permissions on writeable pages.
| nTWE      |   18:18 |    1 | Traps EL0 execution of WFE instructions to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFET instruction.
| nTWI      |   16:16 |    1 | Traps EL0 execution of WFI instructions to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from both Execution states, reported using EC syndrome value 0x01 . When FEAT_WFxT is implemented, this trap also applies to the WFIT instruction.
| UCT       |   15:15 |    1 | Traps EL0 accesses to the CTR_EL0 to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from AArch64 state only, reported using EC syndrome value 0x18 .
| DZE       |   14:14 |    1 | Traps EL0 execution of DC ZVA instructions to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from AArch64 state only, reported using EC syndrome value 0x18 . If FEAT_MTE is implemented, this trap also applies to DC GVA and DC GZVA .
| EnDB      |   13:13 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDBKey_EL1 key, in the EL1&0 translation regime.
| I         |   12:12 |    1 | Stage 1 instruction access Cacheability control, for accesses at EL0 and EL1:
| EOS       |   11:11 |    1 | Exception Exit is Context Synchronizing.
| EnRCTX    |   10:10 |    1 | Enable EL0 access to the following System instructions: CFPRCTX , DVPRCTX and CPPRCTX instructions. If FEAT_SPECRES2 is implemented, COSPRCTX . CFP RCTX , DVP RCTX and CPP RCTX instructions. If FEAT_SPECRES2 is implemented, COSP RCTX .
| UMA       |     9:9 |    1 | User Mask Access. Traps EL0 execution of MSR and MRS instructions that access the PSTATE.{D, A, I, F} masks to EL1, or to EL2 when it is implemented and enabled for the current Security state and HCR_EL2 .TGE is 1, from AArch64 state only, reported using EC syndrome value 0x18 .
| SED       |     8:8 |    1 | SETEND instruction disable. Disables SETEND instructions at EL0 using AArch32.
| ITD       |     7:7 |    1 | IT Disable. Disables some uses of IT instructions at EL0 using AArch32.
| nAA       |     6:6 |    1 | Non-aligned access. This bit controls generation of Alignment faults at EL1 and EL0 under certain conditions. The following instructions generate an Alignment fault if all bytes being accessed are not within a single 16-byte quantity, aligned to 16 bytes for access: LDAPR, LDAPRH, LDAPUR, LDAPURH, LDAPURSH, LDAPURSW, LDAR, LDARH, LDLAR, LDLARH. STLLR, STLLRH, STLR, STLRH, STLUR, and STLURH. If FEAT_LRCPC3 is implemented, the following instructions generate an Alignment fault if all bytes being accessed for a single register are not within a single 16-byte quantity, aligned to 16 bytes for access: LDIAPP, STILP, the post index versions of LDAPR and the pre index versions of STLR. If Advanced SIMD and floating-point instructions are implemented, LDAPUR (SIMD&FP), LDAP1 (SIMD&FP), STLUR (SIMD&FP), and STL1 (SIMD&FP).
| CP15BEN   |     5:5 |    1 | System instruction memory barrier enable. Enables accesses to the DMB, DSB, and ISB System instructions in the (coproc== 0b1111 ) encoding space from EL0:
| SA0       |     4:4 |    1 | SP Alignment check enable for EL0. When set to 1, if a load or store instruction executed at EL0 uses the SP as the base address and the SP is not aligned to a 16-byte boundary, then an SP alignment fault exception is generated. For more information, see 'SP alignment checking' . When the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, this bit has no effect on execution at EL0.
| SA        |     3:3 |    1 | SP Alignment check enable. When set to 1, if a load or store instruction executed at EL1 uses the SP as the base address and the SP is not aligned to a 16-byte boundary, then an SP alignment fault exception is generated. For more information, see 'SP alignment checking' . When the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, this bit has no effect on the PE.
| C         |     2:2 |    1 | Stage 1 Cacheability control, for data accesses.
| A         |     1:1 |    1 | Alignment check enable. This is the enable bit for Alignment fault checking at EL1 and EL0.
| M         |     0:0 |    1 | MMU enable for EL1&0 stage 1 address translation.

## SCTLR_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| TIDCP     |   63:63 |    1 | Trap IMPLEMENTATION DEFINED functionality. Traps EL0 accesses to the encodings reserved for IMPLEMENTATION DEFINED functionality to EL2.
| SPINTMASK |   62:62 |    1 | SP Interrupt Mask enable. When SCTLR_EL2.NMI is 1, controls whether PSTATE.SP acts as an interrupt mask, and controls the value of PSTATE.ALLINT on taking an exception to EL2.
| NMI       |   61:61 |    1 | Non-maskable Interrupt enable.
| EnTP2     |   60:60 |    1 | Traps instructions executed at EL0 that access TPIDR2_EL0 to EL2 when EL2 is implemented and enabled for the current Security state. The exception is reported using EC syndrome value 0x18 .
| TCSO      |   59:59 |    1 | Tag Checking Store Only.
| TCSO0     |   58:58 |    1 | Tag Checking Store Only in EL0.
| EPAN      |   57:57 |    1 | Enhanced Privileged Access Never. When PSTATE.PAN is 1, determines whether an EL2 data access to a page with EL0 instruction access permission generates a Permission fault as a result of the Privileged Access Never mechanism.
| EnALS     |   56:56 |    1 | Traps execution of an LD64B or ST64B instruction at EL0 to EL2.
| EnAS0     |   55:55 |    1 | Traps execution of an ST64BV0 instruction at EL0 to EL2.
| EnASR     |   54:54 |    1 | Traps execution of an ST64BV instruction at EL0 to EL2.
| TME       |   53:53 |    1 | Enables the Transactional Memory Extension at EL2.
| TME0      |   52:52 |    1 | Enables the Transactional Memory Extension at EL0.
| TMT       |   51:51 |    1 | Forces a trivial implementation of the Transactional Memory Extension at EL2.
| TMT0      |   50:50 |    1 | Forces a trivial implementation of the Transactional Memory Extension at EL0.
| TWEDEL    |   49:46 |    4 | TWE Delay. A 4-bit unsigned number that, when SCTLR_EL2.TWEDEn is 1, encodes the minimum delay in taking a trap of WFE caused by SCTLR_EL2.nTWE as 2 (TWEDEL + 8) cycles.
| TWEDEn    |   45:45 |    1 | TWE Delay Enable. Enables a configurable delayed trap of the WFE instruction caused by SCTLR_EL2.nTWE.
| DSSBS     |   44:44 |    1 | Default PSTATE.SSBS value on exception entry.
| ATA       |   43:43 |    1 | Allocation Tag Access in EL2. When SCR_EL3 .ATA is 1, controls access to Allocation Tags and Tag Check operations in EL2.
| ATA0      |   42:42 |    1 | Allocation Tag Access in EL0. When SCR_EL3 .ATA is 1, controls access to Allocation Tags and Tag Check operations in EL0.
| TCF       |   41:40 |    2 | Tag Check Fault in EL2. Controls the effect of Tag Check Faults due to Loads and Stores in EL2.
| TCF0      |   39:38 |    2 | Tag Check Fault in EL0. Controls the effect of Tag Check Faults due to Loads and Stores in EL0.
| ITFSB     |   37:37 |    1 | When synchronous exceptions are not being generated by Tag Check Faults, this field controls whether on exception entry into EL2, all Tag Check Faults due to instructions executed before exception entry, that are reported asynchronously, are synchronized into TFSRE0_EL1 , TFSR_EL1 , and TFSR_EL2 registers.
| BT        |   36:36 |    1 | Indicates the Branch Type compatibility of the implicit BTI behavior for the following instructions at EL2: PACIASP . PACIBSP . If FEAT_PAuth_LR is implemented, PACIASPPC . If FEAT_PAuth_LR is implemented, PACIBSPPC . When the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, this bit is named BT1.
| BT0       |   35:35 |    1 | Indicates the Branch Type compatibility of the implicit BTI behavior for the following instructions at EL0: PACIASP . PACIBSP . If FEAT_PAuth_LR is implemented, PACIASPPC . If FEAT_PAuth_LR is implemented, PACIBSPPC .
| EnFPM     |   34:34 |    1 | Enables direct and indirect accesses to FPMR from EL0. When accesses to FPMR are disabled by this control: Direct accesses to FPMR from EL0 are trapped to EL2 and reported using EC syndrome value 0x18 . Execution of FP8 data-processing instructions that indirectly access FPMR is UNDEFINED at EL0.
| MSCEn     |   33:33 |    1 | Memory Copy and Memory Set instructions Enable. Enables execution of the Memory Copy and Memory Set instructions at EL0.
| CMOW      |   32:32 |    1 | Controls cache maintenance instruction permission for the following instructions executed at EL0. IC IVAU and DC CIVAC . If FEAT_MTE is implemented, DC CIGDVAC and DC CIGVAC .
| EnIA      |   31:31 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIAKey_EL1 key, in the EL2 or EL2&0 translation regime.
| EnIB      |   30:30 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIBKey_EL1 key, in the EL2 or EL2&0 translation regime.
| LSMAOE    |   29:29 |    1 | Load Multiple and Store Multiple Atomicity and Ordering Enable.
| nTLSMD    |   28:28 |    1 | No Trap Load Multiple and Store Multiple to Device-nGRE/Device-nGnRE/Device-nGnRnE memory.
| EnDA      |   27:27 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDAKey_EL1 key, in the EL2 or EL2&0 translation regime.
| UCI       |   26:26 |    1 | Traps execution of cache maintenance instructions at EL0 to EL2, from AArch64 state only, reported using EC syndrome value 0x18 , as follows: DC CVAU , DC CIVAC , DC CVAC , and IC IVAU . If FEAT_MTE is implemented, DC CIGVAC , DC CIGDVAC , DC CGVAC , and DC CGDVAC . If FEAT_DPB is implemented, DC CVAP . If FEAT_DPB and FEAT_MTE are implemented, DC CGVAP and DC CGDVAP . If FEAT_DPB2 is implemented, DC CVADP . If FEAT_DPB2 and FEAT_MTE are implemented, DC CGVADP and DC CGDVADP .
| EE        |   25:25 |    1 | Endianness of data accesses at EL2, stage 1 translation table walks in the EL2 or EL2&0 translation regime, and stage 2 translation table walks in the EL1&0 translation regime.
| E0E       |   24:24 |    1 | Endianness of data accesses at EL0.
| SPAN      |   23:23 |    1 | Set Privileged Access Never, on taking an exception to EL2.
| EIS       |   22:22 |    1 | Exception entry is a context synchronization event.
| IESB      |   21:21 |    1 | Implicit Error Synchronization event enable.
| TSCXT     |   20:20 |    1 | Trap EL0 Access to the SCXTNUM_EL0 register, when EL0 is using AArch64.
| WXN       |   19:19 |    1 | Write permission implies XN (Execute-never). For the EL2 or EL2&0 translation regime, this bit can restrict execute permissions on writeable pages.
| nTWE      |   18:18 |    1 | Traps execution of WFE instructions at EL0 to EL2, from both Execution states. When FEAT_WFxT is implemented, this trap also applies to the WFET instruction.
| nTWI      |   16:16 |    1 | Traps execution of WFI instructions at EL0 to EL2, from both Execution states. When FEAT_WFxT is implemented, this trap also applies to the WFIT instruction.
| UCT       |   15:15 |    1 | Traps EL0 accesses to the CTR_EL0 to EL2, from AArch64 state only.
| DZE       |   14:14 |    1 | Traps execution of DC ZVA instructions at EL0 to EL2, from AArch64 state only. If FEAT_MTE is implemented, this trap also applies to DC GVA and DC GZVA .
| EnDB      |   13:13 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDBKey_EL1 key, in the EL2 or EL2&0 translation regime.
| I         |   12:12 |    1 | Instruction access Cacheability control, for accesses at EL2 and, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, EL0.
| EOS       |   11:11 |    1 | Exception exit is a context synchronization event.
| EnRCTX    |   10:10 |    1 | Enable EL0 access to the following System instructions: CFPRCTX , DVPRCTX and CPPRCTX instructions. If FEAT_SPECRES2 is implemented, COSPRCTX . CFP RCTX , DVP RCTX and CPP RCTX instructions. If FEAT_SPECRES2 is implemented, COSP RCTX .
| SED       |     8:8 |    1 | SETEND instruction disable. Disables SETEND instructions at EL0 using AArch32.
| ITD       |     7:7 |    1 | IT Disable. Disables some uses of IT instructions at EL0 using AArch32.
| nAA       |     6:6 |    1 | Non-aligned access. This bit controls generation of Alignment faults under certain conditions at EL2, and, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, EL0. The following instructions generate an Alignment fault if all bytes being accessed are not within a single 16-byte quantity, aligned to 16 bytes for access: LDAPR, LDAPRH, LDAPUR, LDAPURH, LDAPURSH, LDAPURSW, LDAR, LDARH, LDLAR, LDLARH. STLLR, STLLRH, STLR, STLRH, STLUR, and STLURH If FEAT_LRCPC3 is implemented,the following instructions generate an Alignment fault if all bytes being accessed for a single register are not within a single 16-byte quantity, aligned to 16 bytes for access: LDIAPP, STILP, the post index versions of LDAPR and the pre index versions of STLR. If Advanced SIMD and floating-point instructions are implemented, LDAPUR (SIMD&FP), LDAP1 (SIMD&FP), STLUR (SIMD&FP), and STL1 (SIMD&FP).
| CP15BEN   |     5:5 |    1 | System instruction memory barrier enable. Enables accesses to the DMB, DSB, and ISB System instructions in the (coproc== 0b1111 ) encoding space from EL0:
| SA0       |     4:4 |    1 | SP Alignment check enable for EL0. When set to 1, if a load or store instruction executed at EL0 uses the SP as the base address and the SP is not aligned to a 16-byte boundary, then an SP alignment fault exception is generated. For more information, see 'SP alignment checking' .
| SA        |     3:3 |    1 | SP Alignment check enable. When set to 1, if a load or store instruction executed at EL2 uses the SP as the base address and the SP is not aligned to a 16-byte boundary, then an SP alignment fault exception is generated. For more information, see 'SP alignment checking' .
| C         |     2:2 |    1 | Data access Cacheability control, for accesses at EL2 and, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, EL0
| A         |     1:1 |    1 | Alignment check enable. This is the enable bit for Alignment fault checking at EL2 and, when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}, EL0.
| M         |     0:0 |    1 | MMU enable for EL2 or EL2&0 stage 1 address translation.

## SCTLR_EL3 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| SPINTMASK |   62:62 |    1 | SP Interrupt Mask enable. When SCTLR_EL3.NMI is 1, controls whether PSTATE.SP acts as an interrupt mask, and controls the value of PSTATE.ALLINT on taking an exception to EL3.
| NMI       |   61:61 |    1 | Non-maskable Interrupt enable.
| TCSO      |   59:59 |    1 | Tag Checking Store Only.
| TME       |   53:53 |    1 | Enables the Transactional Memory Extension at EL3.
| TMT       |   51:51 |    1 | Forces a trivial implementation of the Transactional Memory Extension at EL3.
| DSSBS     |   44:44 |    1 | Default PSTATE.SSBS value on Exception Entry.
| ATA       |   43:43 |    1 | Allocation Tag Access in EL3. Controls access to Allocation Tags and Tag Check operations in EL3.
| TCF       |   41:40 |    2 | Tag Check Fault in EL3. Controls the effect of Tag Check Faults due to Loads and Stores in EL3.
| ITFSB     |   37:37 |    1 | When synchronous exceptions are not being generated by Tag Check Faults, this field controls whether on exception entry into EL3, all Tag Check Faults due to instructions executed before exception entry, that are reported asynchronously, are synchronized into TFSRE0_EL1 and TFSR_ELx registers.
| BT        |   36:36 |    1 | Indicates the Branch Type compatibility of the implicit BTI behavior for the following instructions at EL3: PACIASP . PACIBSP . If FEAT_PAuth_LR is implemented, PACIASPPC . If FEAT_PAuth_LR is implemented, PACIBSPPC .
| EnIA      |   31:31 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIAKey_EL1 key, in the EL3 translation regime. Possible values of this bit are:
| EnIB      |   30:30 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APIBKey_EL1 key, in the EL3 translation regime. Possible values of this bit are:
| EnDA      |   27:27 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDAKey_EL1 key, in the EL3 translation regime.
| EE        |   25:25 |    1 | Endianness of data accesses at EL3, and stage 1 translation table walks in the EL3 translation regime.
| EIS       |   22:22 |    1 | Exception Entry is Context Synchronizing.
| IESB      |   21:21 |    1 | Implicit Error Synchronization event enable.
| WXN       |   19:19 |    1 | Write permission implies XN (Execute-never). For the EL3 translation regime, this bit can force all memory regions that are writable to be treated as XN.
| EnDB      |   13:13 |    1 | Controls enabling of pointer authentication of instruction addresses, using the APDBKey_EL1 key, in the EL3 translation regime.
| I         |   12:12 |    1 | Instruction access Cacheability control, for accesses at EL3:
| EOS       |   11:11 |    1 | Exception Exit is Context Synchronizing.
| nAA       |     6:6 |    1 | Non-aligned access. This bit controls generation of Alignment faults at EL3 under certain conditions. The following instructions generate an Alignment fault if all bytes being accessed are not within a single 16-byte quantity, aligned to 16 bytes for access: LDAPR, LDAPRH, LDAPUR, LDAPURH, LDAPURSH, LDAPURSW, LDAR, LDARH, LDLAR, LDLARH. STLLR, STLLRH, STLR, STLRH, STLUR, and STLURH If FEAT_LRCPC3 is implemented, the following instructions generate an Alignment fault if all bytes being accessed for a single register are not within a single 16-byte quantity, aligned to 16 bytes for access: LDIAPP, STILP, the post index versions of LDAPR and the pre index versions of STLR. If Advanced SIMD and floating-point instructions are implemented, LDAPUR (SIMD&FP), LDAP1 (SIMD&FP), STLUR (SIMD&FP), and STL1 (SIMD&FP).
| SA        |     3:3 |    1 | SP Alignment check enable. When set to 1, if a load or store instruction executed at EL3 uses the SP as the base address and the SP is not aligned to a 16-byte boundary, then a SP alignment fault exception is generated. For more information, see 'SP alignment checking' .
| C         |     2:2 |    1 | Cacheability control, for data accesses.
| A         |     1:1 |    1 | Alignment check enable. This is the enable bit for Alignment fault checking at EL3.
| M         |     0:0 |    1 | MMU enable for EL3 stage 1 address translation. Possible values of this bit are:

## SCTLRMASK_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| TIDCP     |   63:63 |    1 | Mask bit for TIDCP.
| SPINTMASK |   62:62 |    1 | Mask bit for SPINTMASK.
| NMI       |   61:61 |    1 | Mask bit for NMI.
| EnTP2     |   60:60 |    1 | Mask bit for EnTP2.
| TCSO      |   59:59 |    1 | Mask bit for TCSO.
| TCSO0     |   58:58 |    1 | Mask bit for TCSO0.
| EPAN      |   57:57 |    1 | Mask bit for EPAN.
| EnALS     |   56:56 |    1 | Mask bit for EnALS.
| EnAS0     |   55:55 |    1 | Mask bit for EnAS0.
| EnASR     |   54:54 |    1 | Mask bit for EnASR.
| TME       |   53:53 |    1 | Mask bit for TME.
| TME0      |   52:52 |    1 | Mask bit for TME0.
| TMT       |   51:51 |    1 | Mask bit for TMT.
| TMT0      |   50:50 |    1 | Mask bit for TMT0.
| TWEDEL    |   46:46 |    1 | Mask bit for TWEDEL.
| TWEDEn    |   45:45 |    1 | Mask bit for TWEDEn.
| DSSBS     |   44:44 |    1 | Mask bit for DSSBS.
| ATA       |   43:43 |    1 | Mask bit for ATA.
| ATA0      |   42:42 |    1 | Mask bit for ATA0.
| TCF       |   40:40 |    1 | Mask bit for TCF.
| TCF0      |   38:38 |    1 | Mask bit for TCF0.
| ITFSB     |   37:37 |    1 | Mask bit for ITFSB.
| BT1       |   36:36 |    1 | Mask bit for BT1.
| BT0       |   35:35 |    1 | Mask bit for BT0.
| EnFPM     |   34:34 |    1 | Mask bit for EnFPM.
| MSCEn     |   33:33 |    1 | Mask bit for MSCEn.
| CMOW      |   32:32 |    1 | Mask bit for CMOW.
| EnIA      |   31:31 |    1 | Mask bit for EnIA.
| EnIB      |   30:30 |    1 | Mask bit for EnIB.
| LSMAOE    |   29:29 |    1 | Mask bit for LSMAOE.
| nTLSMD    |   28:28 |    1 | Mask bit for nTLSMD.
| EnDA      |   27:27 |    1 | Mask bit for EnDA.
| UCI       |   26:26 |    1 | Mask bit for UCI.
| EE        |   25:25 |    1 | Mask bit for EE.
| E0E       |   24:24 |    1 | Mask bit for E0E.
| SPAN      |   23:23 |    1 | Mask bit for SPAN.
| EIS       |   22:22 |    1 | Mask bit for EIS.
| IESB      |   21:21 |    1 | Mask bit for IESB.
| TSCXT     |   20:20 |    1 | Mask bit for TSCXT.
| WXN       |   19:19 |    1 | Mask bit for WXN.
| nTWE      |   18:18 |    1 | Mask bit for nTWE.
| nTWI      |   16:16 |    1 | Mask bit for nTWI.
| UCT       |   15:15 |    1 | Mask bit for UCT.
| DZE       |   14:14 |    1 | Mask bit for DZE.
| EnDB      |   13:13 |    1 | Mask bit for EnDB.
| I         |   12:12 |    1 | Mask bit for I.
| EOS       |   11:11 |    1 | Mask bit for EOS.
| EnRCTX    |   10:10 |    1 | Mask bit for EnRCTX.
| UMA       |     9:9 |    1 | Mask bit for UMA.
| SED       |     8:8 |    1 | Mask bit for SED.
| ITD       |     7:7 |    1 | Mask bit for ITD.
| nAA       |     6:6 |    1 | Mask bit for nAA.
| CP15BEN   |     5:5 |    1 | Mask bit for CP15BEN.
| SA0       |     4:4 |    1 | Mask bit for SA0.
| SA        |     3:3 |    1 | Mask bit for SA.
| C         |     2:2 |    1 | Mask bit for C.
| A         |     1:1 |    1 | Mask bit for A.
| M         |     0:0 |    1 | Mask bit for M.

## SCTLRMASK_EL2 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| TIDCP     |   63:63 |    1 | Mask bit for TIDCP.
| SPINTMASK |   62:62 |    1 | Mask bit for SPINTMASK.
| NMI       |   61:61 |    1 | Mask bit for NMI.
| EnTP2     |   60:60 |    1 | Mask bit for EnTP2.
| TCSO      |   59:59 |    1 | Mask bit for TCSO.
| TCSO0     |   58:58 |    1 | Mask bit for TCSO0.
| EPAN      |   57:57 |    1 | Mask bit for EPAN.
| EnALS     |   56:56 |    1 | Mask bit for EnALS.
| EnAS0     |   55:55 |    1 | Mask bit for EnAS0.
| EnASR     |   54:54 |    1 | Mask bit for EnASR.
| TME       |   53:53 |    1 | Mask bit for TME.
| TME0      |   52:52 |    1 | Mask bit for TME0.
| TMT       |   51:51 |    1 | Mask bit for TMT.
| TMT0      |   50:50 |    1 | Mask bit for TMT0.
| TWEDEL    |   46:46 |    1 | Mask bit for TWEDEL.
| TWEDEn    |   45:45 |    1 | Mask bit for TWEDEn.
| DSSBS     |   44:44 |    1 | Mask bit for DSSBS.
| ATA       |   43:43 |    1 | Mask bit for ATA.
| ATA0      |   42:42 |    1 | Mask bit for ATA0.
| TCF       |   40:40 |    1 | Mask bit for TCF.
| TCF0      |   38:38 |    1 | Mask bit for TCF0.
| ITFSB     |   37:37 |    1 | Mask bit for ITFSB.
| BT        |   36:36 |    1 | Mask bit for BT.
| BT0       |   35:35 |    1 | Mask bit for BT0.
| EnFPM     |   34:34 |    1 | Mask bit for EnFPM.
| MSCEn     |   33:33 |    1 | Mask bit for MSCEn.
| CMOW      |   32:32 |    1 | Mask bit for CMOW.
| EnIA      |   31:31 |    1 | Mask bit for EnIA.
| EnIB      |   30:30 |    1 | Mask bit for EnIB.
| LSMAOE    |   29:29 |    1 | Mask bit for LSMAOE.
| nTLSMD    |   28:28 |    1 | Mask bit for nTLSMD.
| EnDA      |   27:27 |    1 | Mask bit for EnDA.
| UCI       |   26:26 |    1 | Mask bit for UCI.
| EE        |   25:25 |    1 | Mask bit for EE.
| E0E       |   24:24 |    1 | Mask bit for E0E.
| SPAN      |   23:23 |    1 | Mask bit for SPAN.
| EIS       |   22:22 |    1 | Mask bit for EIS.
| IESB      |   21:21 |    1 | Mask bit for IESB.
| TSCXT     |   20:20 |    1 | Mask bit for TSCXT.
| WXN       |   19:19 |    1 | Mask bit for WXN.
| nTWE      |   18:18 |    1 | Mask bit for nTWE.
| nTWI      |   16:16 |    1 | Mask bit for nTWI.
| UCT       |   15:15 |    1 | Mask bit for UCT.
| DZE       |   14:14 |    1 | Mask bit for DZE.
| EnDB      |   13:13 |    1 | Mask bit for EnDB.
| I         |   12:12 |    1 | Mask bit for I.
| EOS       |   11:11 |    1 | Mask bit for EOS.
| EnRCTX    |   10:10 |    1 | Mask bit for EnRCTX.
| SED       |     8:8 |    1 | Mask bit for SED.
| ITD       |     7:7 |    1 | Mask bit for ITD.
| nAA       |     6:6 |    1 | Mask bit for nAA.
| CP15BEN   |     5:5 |    1 | Mask bit for CP15BEN.
| SA0       |     4:4 |    1 | Mask bit for SA0.
| SA        |     3:3 |    1 | Mask bit for SA.
| C         |     2:2 |    1 | Mask bit for C.
| A         |     1:1 |    1 | Mask bit for A.
| M         |     0:0 |    1 | Mask bit for M.

## SDER32_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SUNIDEN  |     1:1 |    1 | Secure User Non-Invasive Debug Enable.
| SUIDEN   |     0:0 |    1 | Secure User Invasive Debug Enable.

## SDER32_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SUNIDEN  |     1:1 |    1 | Secure User Non-Invasive Debug Enable.
| SUIDEN   |     0:0 |    1 | Secure User Invasive Debug Enable.

## SMCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FA64     |   31:31 |    1 | Controls whether execution of an A64 instruction is considered legal when the PE is in Streaming SVE mode.
| EZT0     |   30:30 |    1 | Traps execution at EL1 and EL0 of the LDR, LUTI2, LUTI4, MOVT, STR, and ZERO instructions that access the ZT0 register to  EL1, or to EL2 when EL2 is implemented and enabled in the current Security state and HCR_EL2 .TGE is 1. The exception is reported using ESR_EL1 .EC or ESR_EL2 .EC value 0x1D , with an ISS code of 0x0000004 , at a lower priority than a trap due to PSTATE.SM or PSTATE.ZA.
| LEN      |     3:0 |    4 | Requests an Effective Streaming SVE vector length (SVL) at EL1 of (LEN+1)*128 bits. This field also defines the Effective Streaming SVE vector length at EL0 when EL2 is not implemented, or EL2 is not enabled in the current Security state, or the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}. The Streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support any subset of the architecturally permitted lengths. When the PE is in Streaming SVE mode, the Effective SVE vector length (VL) is equal to SVL. When FEAT_SVE is implemented, and the PE is not in Streaming SVE mode, VL is equal to the Effective Non-streaming SVE vector length. See ZCR_EL1 . For all purposes other than returning the result of a direct read of SMCR_EL1, the PE selects the Effective Streaming SVE vector length by performing checks in the following order: If the requested length is less than the minimum implemented Streaming SVE vector length, then the Effective length is the minimum implemented Streaming SVE vector length. If EL2 is implemented and enabled in the current Security state, and the requested length is greater than the Effective length at EL2, then the Effective length at EL2 is used. If EL3 is implemented and the requested length is greater than the Effective length at EL3, then the Effective length at EL3 is used. Otherwise, the Effective length is the highest supported Streaming SVE vector length that is less than or equal to the requested length. An indirect read of SMCR_EL1.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.

## SMCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FA64     |   31:31 |    1 | Controls whether execution of an A64 instruction is considered legal when the PE is in Streaming SVE mode.
| EZT0     |   30:30 |    1 | Traps execution at EL2, EL1, and EL0 of the LDR, LUTI2, LUTI4, MOVT, STR, and ZERO instructions that access the ZT0 register to  EL2, when EL2 is enabled in the current Security state. The exception is reported using ESR_EL2 .EC value 0x1D , with an ISS code of 0x0000004 , at a lower priority than a trap due to PSTATE.SM or PSTATE.ZA.
| LEN      |     3:0 |    4 | Requests an Effective Streaming SVE vector length (SVL) at EL2 of (LEN+1)*128 bits. This field also defines the Effective Streaming SVE vector length at EL0 when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}. The Streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support any subset of the architecturally permitted lengths. When the PE is in Streaming SVE mode, the Effective SVE vector length (VL) is equal to SVL. When FEAT_SVE is implemented, and the PE is not in Streaming SVE mode, VL is equal to the Effective Non-streaming SVE vector length. See ZCR_EL2 . For all purposes other than returning the result of a direct read of SMCR_EL2, the PE selects the Effective Streaming SVE vector length by performing checks in the following order: If the requested length is less than the minimum implemented Streaming SVE vector length, then the Effective length is the minimum implemented Streaming SVE vector length. If EL3 is implemented and the requested length is greater than the Effective length at EL3, then the Effective length at EL3 is used. Otherwise, the Effective length is the highest supported Streaming SVE vector length that is less than or equal to the requested length. An indirect read of SMCR_EL2.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.

## SMCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FA64     |   31:31 |    1 | Controls whether execution of an A64 instruction is considered legal when the PE is in Streaming SVE mode.
| EZT0     |   30:30 |    1 | Traps execution at all Exception levels of the LDR, LUTI2, LUTI4, MOVT, STR, and ZERO instructions that access the ZT0 register to  EL3. The exception is reported using ESR_EL3 .EC value 0x1D , with an ISS code of 0x0000004 , at a lower priority than a trap due to PSTATE.SM or PSTATE.ZA.
| LEN      |     3:0 |    4 | Requests an Effective Streaming SVE vector length (SVL) at EL3 of (LEN+1)*128 bits. The Streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support any subset of the architecturally permitted lengths. When the PE is in Streaming SVE mode, the Effective SVE vector length (VL) is equal to SVL. When FEAT_SVE is implemented, and the PE is not in Streaming SVE mode, VL is equal to the Effective Non-streaming SVE vector length. See ZCR_EL3 . For all purposes other than returning the result of a direct read of SMCR_EL3, the PE selects the Effective Streaming SVE vector length by performing checks in the following order: If the requested length is less than the minimum implemented Streaming SVE vector length, then the Effective length is the minimum implemented Streaming SVE vector length. Otherwise, the Effective length is the highest supported Streaming SVE vector length that is less than or equal to the requested length. An indirect read of SMCR_EL3.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.

## SMIDR_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| NSMC        |   59:56 |    4 | If SMIDR_EL1.{SH,Affinity} indicates that the implementation of Streaming SVE mode is shared, then this field identifies the number of SMCUs, minus 1, associated with the concatenated SMIDR_EL1.{Affinity2,Affinity} 32-bit value. If SMIDR_EL1.{SH,Affinity} indicates that the implementation of Streaming SVE mode is not shared, then this field is zero and should be ignored by software.
| HIP         |   55:52 |    4 | Highest Implemented Priority. If Streaming SVE mode execution priority is supported, this field indicates the range of priority levels implemented by the PE, and the Highest Implemented Priority value.
| Affinity2   |   51:32 |   20 | The most significant 20 bits of the SMCU affinity for this PE, to be used in conjunction with SMIDR_EL1.Affinity.
| Implementer |   31:24 |    8 | The Implementer code. This field must hold an implementer code that has been assigned by Arm.
| Revision    |   23:16 |    8 | Revision number for the Streaming Mode Compute Unit (SMCU).
| SMPS        |   15:15 |    1 | Indicates support for Streaming SVE mode execution priority.
| SH          |   14:13 |    2 | Indicates whether the implementation of Streaming SVE mode in this PE is shared with other PEs.
| Affinity    |    11:0 |   12 | The least significant 12 bits of the SMCU affinity for this PE.

## SMPRI_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Priority |     3:0 |    4 | Streaming execution priority value. Either this value is used directly, or it is mapped into an effective priority value using SMPRIMAP_EL2 . This value is used directly when any of the following are true: The current Exception level is EL3 or EL2. The current Exception level is EL1 or EL0, if EL2 is implemented and enabled in the current Security state and HCRX_EL2 .SMPME is '0'. The current Exception level is EL1 or EL0, if EL2 is either not implemented or not enabled in the current Security state.

## SMPRIMAP_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| P15      |   63:60 |    4 | Priority Mapping Entry 15. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '15'. This value is the highest streaming execution priority.
| P14      |   59:56 |    4 | Priority Mapping Entry 14. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '14'.
| P13      |   55:52 |    4 | Priority Mapping Entry 13. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '13'.
| P12      |   51:48 |    4 | Priority Mapping Entry 12. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '12'.
| P11      |   47:44 |    4 | Priority Mapping Entry 11. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '11'.
| P10      |   43:40 |    4 | Priority Mapping Entry 10. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '10'.
| P9       |   39:36 |    4 | Priority Mapping Entry 9. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '9'.
| P8       |   35:32 |    4 | Priority Mapping Entry 8. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '8'.
| P7       |   31:28 |    4 | Priority Mapping Entry 7. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '7'.
| P6       |   27:24 |    4 | Priority Mapping Entry 6. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '6'.
| P5       |   23:20 |    4 | Priority Mapping Entry 5. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '5'.
| P4       |   19:16 |    4 | Priority Mapping Entry 4. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '4'.
| P3       |   15:12 |    4 | Priority Mapping Entry 3. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '3'.
| P2       |    11:8 |    4 | Priority Mapping Entry 2. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '2'.
| P1       |     7:4 |    4 | Priority Mapping Entry 1. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '1'.
| P0       |     3:0 |    4 | Priority Mapping Entry 0. This entry is used when priority mapping is supported and enabled, and the SMPRI_EL1 .Priority value is '0'. This value is the lowest streaming execution priority.

## SPMCFGR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NCG      |   31:28 |    4 | Counter Groups. Defines the number of counter groups implemented by System PMU <s>, minus one. If this field is zero, then one counter group is implemented and SPMCGCR<n>_EL1 read-as-zero. Otherwise, for each counter group <m>, SPMCGCR<m DIV 8>_EL1.N<m MOD 8> defines the number of counters in the group. Locating the first counter in each group depends on the number of implemented groups. Each counter group starts with counter: SPMEVTYPER<m×32>_EL0, meaning there are at most 32 counters per group, if there are 2 counter groups. SPMEVTYPER<m×16>_EL0, meaning there are at most 16 counters per group, if there are 3 or 4 counter groups. SPMEVTYPER<m×8>_EL0, meaning there are at most 8 counters per group, if there are between 5 and 8 counter groups. SPMEVTYPER<m×4>_EL0, meaning there are at most 4 counters per group, if there are more than 8 counter groups.
| HDBG     |   24:24 |    1 | Halt-on-debug supported. For more information on this field, see 'CoreSight PMU Architecture'.
| TRO      |   23:23 |    1 | Trace output supported. For more information on this field, see 'CoreSight PMU Architecture'.
| SS       |   22:22 |    1 | Snapshot supported. For more information on this field, see 'CoreSight PMU Architecture'.
| FZO      |   21:21 |    1 | Freeze-on-overflow supported. For more information on this field, see 'CoreSight PMU Architecture'.
| MSI      |   20:20 |    1 | Message-signaled interrupts supported. For more information on this field, see 'CoreSight PMU Architecture'.
| NA       |   17:17 |    1 | No write access when running. For more information on this field, see 'CoreSight PMU Architecture'.
| EX       |   16:16 |    1 | Export supported. For more information on this field, see 'CoreSight PMU Architecture'.
| SIZE     |    13:8 |    6 | Counter size. The size of the largest counter implemented by System PMU <s>.
| N        |     7:0 |    8 | Number of event counters implemented by System PMU <s>, minus 1.

## SPMCR_EL0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TRO      |   11:11 |    1 | Trace enable. For more information on this field, see 'CoreSight PMU Architecture'.
| HDBG     |   10:10 |    1 | Halt-on-debug. For more information on this field, see 'CoreSight PMU Architecture'.
| FZO      |     9:9 |    1 | Freeze-on-overflow. For more information on this field, see 'CoreSight PMU Architecture'.
| NA       |     8:8 |    1 | Not accessible. For more information on this field, see 'CoreSight PMU Architecture'.
| EX       |     4:4 |    1 | Export enable. For more information on this field, see 'CoreSight PMU Architecture'.
| P        |     1:1 |    1 | Event counter reset.
| E        |     0:0 |    1 | Count enable. This field controls System PMU <s>.

## SPMDEVAFF_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Aff3     |   39:32 |    8 | PE affinity level 3. The MPIDR_EL1 .Aff3 field, viewed from the highest Exception level of the associated PE or PEs.
| F0V      |   31:31 |    1 | Indicates that the SPMDEVAFF_EL1.Aff0 field is valid.
| U        |   30:30 |    1 | Uniprocessor. The MPIDR_EL1 .U field, viewed from the highest Exception level of the associated PE.
| MT       |   24:24 |    1 | Multithreaded. The MPIDR_EL1 .MT field, viewed from the highest Exception level of the associated PE.
| Aff2     |   23:16 |    8 | PE affinity level 2. The MPIDR_EL1 .Aff2 field, viewed from the highest Exception level of the associated PE or PEs.
| Aff1     |    15:8 |    8 | PE affinity level 1. The MPIDR_EL1 .Aff1 field, viewed from the highest Exception level of the associated PE or PEs.
| Aff0     |     7:0 |    8 | PE affinity level 0. The MPIDR_EL1 .Aff0 field, viewed from the highest Exception level of the associated PE.

## SPMDEVARCH_EL1 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| ARCHITECT |   31:21 |   11 | Architect. Defines the architect of the component. Bits [31:28] are the JEP106 continuation code (JEP106 bank ID, minus 1) and bits [27:21] are the JEP106 ID code.
| PRESENT   |   20:20 |    1 | DEVARCH present. Defines that SPMDEVARCH_EL1 register is present.
| REVISION  |   19:16 |    4 | Revision. Defines the architecture revision of the component.
| ARCHVER   |   15:12 |    4 | Architecture Version. Defines the architecture version of the component.
| ARCHPART  |    11:0 |   12 | Architecture Part. Defines the architecture of the component.

## SPMIIDR_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| ProductID   |   31:20 |   12 | Part number, bits [11:0]. The part number is selected by the designer of the component.
| Variant     |   19:16 |    4 | Component major revision. Defines either a variant of the component defined by SPMIIDR_EL1.ProductID, or the major revision of the component. When defining a major revision, SPMIIDR_EL1.Variant and SPMIIDR_EL1.Revision together form the revision number of the component, with SPMIIDR_EL1.Variant being the most significant part and SPMIIDR_EL1.Revision the least significant part. When a component is changed, SPMIIDR_EL1.Variant or SPMIIDR_EL1.Revision is increased to ensure that software can differentiate the different revisions of the component. If SPMIIDR_EL1.Variant is increased then SPMIIDR_EL1.Revision should be set to 0b0000 .
| Revision    |   15:12 |    4 | Component minor revision. When a component is changed: If SPMIIDR_EL1.Variant and SPMIIDR_EL1.Revision together form the revision number of the component then: SPMIIDR_EL1.Variant or SPMIIDR_EL1.Revision is increased to ensure that software can differentiate the different revisions of the component. If Variant is increased then Revision should be set to 0b0000 . Otherwise, SPMIIDR_EL1.Revision is increased to ensure that software can differentiate the different revisions of the component.
| Implementer |    11:0 |   12 | Contains the JEP106 manufacturer's identification code of the designer of the System PMU. The code identifies the designer of the component, which might not be the same as the implementer of the device containing the component. For an implementation designed by Arm, this field reads as 0x43B .

## SPMROOTCR_EL3 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| IMPLEMENTATION DEFINED |   63:32 |   32 | IMPLEMENTATION DEFINED observation controls. Additional IMPLEMENTATION DEFINED bits to control certain types of filter or events by System PMU <s>.
| NAO                    |     3:3 |    1 | Non-attributable Observation. Controls whether events or monitorable characteristics not attributable with any source can be monitored by System PMU <s>.
| RLO                    |     1:1 |    1 | Realm Observation. Controls whether events or monitorable characteristics attributable to a Realm event source can be monitored by System PMU <s>.
| RTO                    |     0:0 |    1 | Root Observation. Controls whether events or monitorable characteristics attributable to a Root event source can be monitored by System PMU <s>.

## SPMSCR_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| IMPLEMENTATION DEFINED |   63:32 |   32 | IMPLEMENTATION DEFINED observation controls. Additional IMPLEMENTATION DEFINED bits to control certain types of filter or events by System PMU <s>.
| NAO                    |     4:4 |    1 | Non-attributable Observation. Controls whether events or monitorable characteristics not attributable with any source can be monitored by System PMU <s>.
| SO                     |     0:0 |    1 | Secure Observation. Controls whether events or monitorable characteristics attributable to a Secure event source can be monitored by System PMU <s>.

## SPMSELR_EL0 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| SYSPMUSEL |     9:4 |    6 | System PMU Select. Selects a System PMU <s> to access.
| BANK      |     1:0 |    2 | System PMU bank access control. Selects a bank of 16 System PMU event counters and related controls to access.

## SPSEL bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SP       |     0:0 |    1 | Stack pointer to use. Possible values of this bit are:

## SPSR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| UINJ     |   36:36 |    1 | Inject Undefined Instruction exception. Set to 0 on taking an exception to EL1, and  copied to PSTATE.UINJ on executing an exception return operation in EL1.
| PPEND    |   33:33 |    1 | PMU Profiling exception pending bit. Set to the value of PSTATE.PPEND on taking an exception to EL1, and conditionally  copied to PSTATE.PPEND on executing an exception return operation in EL1.
| N        |   31:31 |    1 | Negative Condition flag. Set to the value of PSTATE.N on taking an exception to EL1, and  copied to PSTATE.N on executing an exception return operation in EL1.
| Z        |   30:30 |    1 | Zero Condition flag. Set to the value of PSTATE.Z on taking an exception to EL1, and  copied to PSTATE.Z on executing an exception return operation in EL1.
| C        |   29:29 |    1 | Carry Condition flag. Set to the value of PSTATE.C on taking an exception to EL1, and  copied to PSTATE.C on executing an exception return operation in EL1.
| V        |   28:28 |    1 | Overflow Condition flag. Set to the value of PSTATE.V on taking an exception to EL1, and  copied to PSTATE.V on executing an exception return operation in EL1.
| Q        |   27:27 |    1 | Overflow or saturation flag. Set to the value of PSTATE.Q on taking an exception to EL1, and  copied to PSTATE.Q on executing an exception return operation in EL1.
| IT       |   26:25 |    2 | If-Then. Set to the value of PSTATE.IT on taking an exception to EL1, and  copied to PSTATE.IT on executing an exception return operation in EL1.
| DIT      |   24:24 |    1 | Data Independent Timing. Set to the value of PSTATE.DIT on taking an exception to EL1, and  copied to PSTATE.DIT on executing an exception return operation in EL1.
| SSBS     |   23:23 |    1 | Speculative Store Bypass. Set to the value of PSTATE.SSBS on taking an exception to EL1, and  copied to PSTATE.SSBS on executing an exception return operation in EL1.
| PAN      |   22:22 |    1 | Privileged Access Never. Set to the value of PSTATE.PAN on taking an exception to EL1, and  copied to PSTATE.PAN on executing an exception return operation in EL1.
| SS       |   21:21 |    1 | Software Step. Set to the value of PSTATE.SS on taking an exception to EL1, and conditionally  copied to PSTATE.SS on executing an exception return operation in EL1.
| IL       |   20:20 |    1 | Illegal Execution state. Set to the value of PSTATE.IL on taking an exception to EL1, and  copied to PSTATE.IL on executing an exception return operation in EL1.
| GE       |   19:16 |    4 | Greater than or Equal flags. Set to the value of PSTATE.GE on taking an exception to EL1, and  copied to PSTATE.GE on executing an exception return operation in EL1.
| IT[7:2]  |   15:10 |    6 | This field is bits[7:2] of IT[7:0]. See IT[1:0] for the field description.
| E        |     9:9 |    1 | Endianness. Set to the value of PSTATE.E on taking an exception to EL1, and  copied to PSTATE.E on executing an exception return operation in EL1.
| A        |     8:8 |    1 | SError exception mask. Set to the value of PSTATE.A on taking an exception to EL1, and  copied to PSTATE.A on executing an exception return operation in EL1.
| I        |     7:7 |    1 | IRQ interrupt mask. Set to the value of PSTATE.I on taking an exception to EL1, and  copied to PSTATE.I on executing an exception return operation in EL1.
| F        |     6:6 |    1 | FIQ interrupt mask. Set to the value of PSTATE.F on taking an exception to EL1, and  copied to PSTATE.F on executing an exception return operation in EL1.
| T        |     5:5 |    1 | T32 Instruction set state. Set to the value of PSTATE.T on taking an exception to EL1, and  copied to PSTATE.T on executing an exception return operation in EL1.
| M[4]     |     4:4 |    1 | Execution state. Set to 0b1 , the value of PSTATE.nRW, on taking an exception to EL1 from AArch32 state, and copied to PSTATE.nRW on executing an exception return operation in EL1.
| M[3:0]   |     3:0 |    4 | AArch32 Mode. Set to the value of PSTATE.M[3:0] on taking an exception to EL1, and  copied to PSTATE.M[3:0] on executing an exception return operation in EL1.

## SPSR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| UINJ     |   36:36 |    1 | Inject Undefined Instruction exception. Set to 0 on taking an exception to EL2, and  copied to PSTATE.UINJ on executing an exception return operation in EL2.
| PPEND    |   33:33 |    1 | PMU Profiling exception pending bit. Set to the value of PSTATE.PPEND on taking an exception to EL2, and conditionally  copied to PSTATE.PPEND on executing an exception return operation in EL2.
| N        |   31:31 |    1 | Negative Condition flag. Set to the value of PSTATE.N on taking an exception to EL2, and  copied to PSTATE.N on executing an exception return operation in EL2.
| Z        |   30:30 |    1 | Zero Condition flag. Set to the value of PSTATE.Z on taking an exception to EL2, and  copied to PSTATE.Z on executing an exception return operation in EL2.
| C        |   29:29 |    1 | Carry Condition flag. Set to the value of PSTATE.C on taking an exception to EL2, and  copied to PSTATE.C on executing an exception return operation in EL2.
| V        |   28:28 |    1 | Overflow Condition flag. Set to the value of PSTATE.V on taking an exception to EL2, and  copied to PSTATE.V on executing an exception return operation in EL2.
| Q        |   27:27 |    1 | Overflow or saturation flag. Set to the value of PSTATE.Q on taking an exception to EL2, and  copied to PSTATE.Q on executing an exception return operation in EL2.
| IT       |   26:25 |    2 | If-Then. Set to the value of PSTATE.IT on taking an exception to EL2, and  copied to PSTATE.IT on executing an exception return operation in EL2.
| DIT      |   24:24 |    1 | Data Independent Timing. Set to the value of PSTATE.DIT on taking an exception to EL2, and  copied to PSTATE.DIT on executing an exception return operation in EL2.
| SSBS     |   23:23 |    1 | Speculative Store Bypass. Set to the value of PSTATE.SSBS on taking an exception to EL2, and  copied to PSTATE.SSBS on executing an exception return operation in EL2.
| PAN      |   22:22 |    1 | Privileged Access Never. Set to the value of PSTATE.PAN on taking an exception to EL2, and  copied to PSTATE.PAN on executing an exception return operation in EL2.
| SS       |   21:21 |    1 | Software Step. Set to the value of PSTATE.SS on taking an exception to EL2, and conditionally  copied to PSTATE.SS on executing an exception return operation in EL2.
| IL       |   20:20 |    1 | Illegal Execution state. Set to the value of PSTATE.IL on taking an exception to EL2, and  copied to PSTATE.IL on executing an exception return operation in EL2.
| GE       |   19:16 |    4 | Greater than or Equal flags. Set to the value of PSTATE.GE on taking an exception to EL2, and  copied to PSTATE.GE on executing an exception return operation in EL2.
| IT[7:2]  |   15:10 |    6 | This field is bits[7:2] of IT[7:0]. See IT[1:0] for the field description.
| E        |     9:9 |    1 | Endianness. Set to the value of PSTATE.E on taking an exception to EL2, and  copied to PSTATE.E on executing an exception return operation in EL2.
| A        |     8:8 |    1 | SError exception mask. Set to the value of PSTATE.A on taking an exception to EL2, and  copied to PSTATE.A on executing an exception return operation in EL2.
| I        |     7:7 |    1 | IRQ interrupt mask. Set to the value of PSTATE.I on taking an exception to EL2, and  copied to PSTATE.I on executing an exception return operation in EL2.
| F        |     6:6 |    1 | FIQ interrupt mask. Set to the value of PSTATE.F on taking an exception to EL2, and  copied to PSTATE.F on executing an exception return operation in EL2.
| T        |     5:5 |    1 | T32 Instruction set state. Set to the value of PSTATE.T on taking an exception to EL2, and  copied to PSTATE.T on executing an exception return operation in EL2.
| M[4]     |     4:4 |    1 | Execution state. Set to 0b1 , the value of PSTATE.nRW, on taking an exception to EL2 from AArch32 state, and copied to PSTATE.nRW on executing an exception return operation in EL2.
| M[3:0]   |     3:0 |    4 | AArch32 Mode. Set to the value of PSTATE.M[3:0] on taking an exception to EL2, and  copied to PSTATE.M[3:0] on executing an exception return operation in EL2.

## SPSR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| UINJ     |   36:36 |    1 | Inject Undefined Instruction exception. Set to 0 on taking an exception to EL3, and  copied to PSTATE.UINJ on executing an exception return operation in EL3.
| PPEND    |   33:33 |    1 | PMU Profiling exception pending bit. Set to the value of PSTATE.PPEND on taking an exception to EL3, and conditionally  copied to PSTATE.PPEND on executing an exception return operation in EL3.
| N        |   31:31 |    1 | Negative Condition flag. Set to the value of PSTATE.N on taking an exception to EL3, and  copied to PSTATE.N on executing an exception return operation in EL3.
| Z        |   30:30 |    1 | Zero Condition flag. Set to the value of PSTATE.Z on taking an exception to EL3, and  copied to PSTATE.Z on executing an exception return operation in EL3.
| C        |   29:29 |    1 | Carry Condition flag. Set to the value of PSTATE.C on taking an exception to EL3, and  copied to PSTATE.C on executing an exception return operation in EL3.
| V        |   28:28 |    1 | Overflow Condition flag. Set to the value of PSTATE.V on taking an exception to EL3, and  copied to PSTATE.V on executing an exception return operation in EL3.
| Q        |   27:27 |    1 | Overflow or saturation flag. Set to the value of PSTATE.Q on taking an exception to EL3, and  copied to PSTATE.Q on executing an exception return operation in EL3.
| IT       |   26:25 |    2 | If-Then. Set to the value of PSTATE.IT on taking an exception to EL3, and  copied to PSTATE.IT on executing an exception return operation in EL3.
| DIT      |   24:24 |    1 | Data Independent Timing. Set to the value of PSTATE.DIT on taking an exception to EL3, and  copied to PSTATE.DIT on executing an exception return operation in EL3.
| SSBS     |   23:23 |    1 | Speculative Store Bypass. Set to the value of PSTATE.SSBS on taking an exception to EL3, and  copied to PSTATE.SSBS on executing an exception return operation in EL3.
| PAN      |   22:22 |    1 | Privileged Access Never. Set to the value of PSTATE.PAN on taking an exception to EL3, and  copied to PSTATE.PAN on executing an exception return operation in EL3.
| SS       |   21:21 |    1 | Software Step. Set to the value of PSTATE.SS on taking an exception to EL3, and conditionally  copied to PSTATE.SS on executing an exception return operation in EL3.
| IL       |   20:20 |    1 | Illegal Execution state. Set to the value of PSTATE.IL on taking an exception to EL3, and  copied to PSTATE.IL on executing an exception return operation in EL3.
| GE       |   19:16 |    4 | Greater than or Equal flags. Set to the value of PSTATE.GE on taking an exception to EL3, and  copied to PSTATE.GE on executing an exception return operation in EL3.
| IT[7:2]  |   15:10 |    6 | This field is bits[7:2] of IT[7:0]. See IT[1:0] for the field description.
| E        |     9:9 |    1 | Endianness. Set to the value of PSTATE.E on taking an exception to EL3, and  copied to PSTATE.E on executing an exception return operation in EL3.
| A        |     8:8 |    1 | SError exception mask. Set to the value of PSTATE.A on taking an exception to EL3, and  copied to PSTATE.A on executing an exception return operation in EL3.
| I        |     7:7 |    1 | IRQ interrupt mask. Set to the value of PSTATE.I on taking an exception to EL3, and  copied to PSTATE.I on executing an exception return operation in EL3.
| F        |     6:6 |    1 | FIQ interrupt mask. Set to the value of PSTATE.F on taking an exception to EL3, and  copied to PSTATE.F on executing an exception return operation in EL3.
| T        |     5:5 |    1 | T32 Instruction set state. Set to the value of PSTATE.T on taking an exception to EL3, and  copied to PSTATE.T on executing an exception return operation in EL3.
| M[4]     |     4:4 |    1 | Execution state. Set to 0b1 , the value of PSTATE.nRW, on taking an exception to EL3 from AArch32 state, and copied to PSTATE.nRW on executing an exception return operation in EL3.
| M[3:0]   |     3:0 |    4 | AArch32 Mode. Set to the value of PSTATE.M[3:0] on taking an exception to EL3, and  copied to PSTATE.M[3:0] on executing an exception return operation in EL3.

## SSBS bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SSBS     |   12:12 |    1 | Speculative Store Bypass Safe. Prohibits speculative loads or stores which might practically allow a cache timing side channel. A speculative value in a register is used in a potentially speculatively exploitable manner if it is used to form an address, generate condition codes, or generate SVE predicate values to be used by other instructions in the speculative sequence or if the execution timing of any other instructions in the speculative sequence is a function of the data loaded under speculation.

## SVCR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ZA       |     1:1 |    1 | Enables SME ZA storage. If FEAT_SME2 is implemented, also enables SME2 ZT0 storage. When this storage is disabled, execution of an instruction which can access it is trapped. The exception is reported using an ESR_ELx .{EC, SMTC} value of { 0x1D , 0x3 }. The possible values of this bit are:
| SM       |     0:0 |    1 | Enables Streaming SVE mode. When the PE is in Streaming SVE mode, the Streaming SVE vector length (SVL) applies to SVE instructions, and execution at any Exception level of an instruction which is illegal in that mode is trapped. The exception is reported using an ESR_ELx .{EC, SMTC} value of { 0x1D , 0x1 }. When the PE is not in Streaming SVE mode, the SVE vector length (VL) applies to SVE instructions, and execution at any Exception level of an instruction which is only legal in that mode is trapped. The exception is reported using an ESR_ELx .{EC, SMTC} value of { 0x1D , 0x2 }. The possible values of this bit are:

## TCO bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TCO      |   25:25 |    1 | Allows memory tag checks to be globally disabled.

## TCR2_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FNGNA1   |   21:21 |    1 | Force non-global for unassured translations using TTBR1_EL1 .
| FNGNA0   |   20:20 |    1 | Force non-global for unassured translations using TTBR0_EL1 .
| FNG1     |   18:18 |    1 | Force non-global translations for TTBR1_EL1 .
| FNG0     |   17:17 |    1 | Force non-global translations for TTBR0_EL1 .
| A2       |   16:16 |    1 | Enable use of two ASIDs.
| DisCH1   |   15:15 |    1 | Disable the Contiguous bit for the Start Table for TTBR1_EL1 .
| DisCH0   |   14:14 |    1 | Disable the Contiguous bit for the Start Table for TTBR0_EL1 .
| HAFT     |   11:11 |    1 | Hardware managed Access Flag for Table descriptors. Enables the Hardware managed Access Flag for Table descriptors.
| PTTWI    |   10:10 |    1 | Permit Translation table walk Incoherence. Permits RCWS instructions to generate writes that have the Reduced Coherence property.
| D128     |     5:5 |    1 | Enables VMSAv9-128 translation system.
| AIE      |     4:4 |    1 | Enable Attribute Indexing Extension.
| POE      |     3:3 |    1 | Enables Permission Overlays for privileged accesses from EL1&0 translation regime.
| E0POE    |     2:2 |    1 | Enables Permission Overlays for unprivileged accesses from EL1&0 translation regime.
| PIE      |     1:1 |    1 | Enables usage of Indirect Permission Scheme.
| PnCH     |     0:0 |    1 | Protected attribute enable.Indicates use of bit[52] of the stage 1 translation table entry.

## TCR2_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| AMEC0    |   12:12 |    1 | This field controls the enabling of the Alternate MECID translations for the EL2 translation regime. TCR2_EL2.AMEC0 is provided to enable the safe update of MECID_A0_EL2 , by disabling access and speculation to AMEC==1 Block or Page descriptors during the update.
| HAFT     |   11:11 |    1 | Hardware managed Access Flag for Table descriptors. Enables the Hardware managed Access Flag for Table descriptors.
| PTTWI    |   10:10 |    1 | Permit Translation table walk Incoherence. Permits RCWS instructions to generate writes that have the Reduced Coherence property.
| AIE      |     4:4 |    1 | Enable Attribute Indexing Extension.
| POE      |     3:3 |    1 | Enables Permission Overlay for EL2 accesses.
| PIE      |     1:1 |    1 | Enables usage of Indirect Permission Scheme.
| PnCH     |     0:0 |    1 | Protected attribute enable.Indicates use of bit[52] of the stage 1 translation table entry.

## TCR2MASK_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| FNGNA1   |   21:21 |    1 | Mask bit for FNGNA1.
| FNGNA0   |   20:20 |    1 | Mask bit for FNGNA0.
| FNG1     |   18:18 |    1 | Mask bit for FNG1.
| FNG0     |   17:17 |    1 | Mask bit for FNG0.
| A2       |   16:16 |    1 | Mask bit for A2.
| DisCH1   |   15:15 |    1 | Mask bit for DisCH1.
| DisCH0   |   14:14 |    1 | Mask bit for DisCH0.
| HAFT     |   11:11 |    1 | Mask bit for HAFT.
| PTTWI    |   10:10 |    1 | Mask bit for PTTWI.
| D128     |     5:5 |    1 | Mask bit for D128.
| AIE      |     4:4 |    1 | Mask bit for AIE.
| POE      |     3:3 |    1 | Mask bit for POE.
| E0POE    |     2:2 |    1 | Mask bit for E0POE.
| PIE      |     1:1 |    1 | Mask bit for PIE.
| PnCH     |     0:0 |    1 | Mask bit for PnCH.

## TCR2MASK_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| AMEC0    |   12:12 |    1 | Mask bit for AMEC0.
| HAFT     |   11:11 |    1 | Mask bit for HAFT.
| PTTWI    |   10:10 |    1 | Mask bit for PTTWI.
| AIE      |     4:4 |    1 | Mask bit for AIE.
| POE      |     3:3 |    1 | Mask bit for POE.
| PIE      |     1:1 |    1 | Mask bit for PIE.
| PnCH     |     0:0 |    1 | Mask bit for PnCH.

## TCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MTX1     |   61:61 |    1 | Extended memory tag checking. This field controls address generation and tag checking when EL0 and EL1 are using AArch64 where the data address would be translated by tables pointed to by TTBR1_EL1 . This control has an effect regardless of whether stage 1 of the EL1&0 translation regime is enabled or not.
| MTX0     |   60:60 |    1 | Extended memory tag checking. This field controls address generation and tag checking when EL0 and EL1 are using AArch64 where the data address would be translated by tables pointed to by TTBR0_EL1 . This control has an effect regardless of whether stage 1 of the EL1&0 translation regime is enabled or not.
| DS       |   59:59 |    1 | This field affects: Whether a 52-bit output address can be described by the translation tables of the 4KB or 16KB translation granules. The minimum value of TCR_EL1.{T0SZ,T1SZ}. How and where shareability for Block and Page descriptors are encoded.
| TCMA1    |   58:58 |    1 | Controls the generation of Unchecked accesses at EL1, and at EL0 if the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, when address[59:55] = 0b11111 .
| TCMA0    |   57:57 |    1 | Controls the generation of Unchecked accesses at EL1, and at EL0 if the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}, when address[59:55] = 0b00000 .
| E0PD1    |   56:56 |    1 | Faulting control for unprivileged access to any address translated by TTBR0_EL1 .
| E0PD0    |   55:55 |    1 | Faulting control for unprivileged access to any address translated by TTBR0_EL1 .
| NFD1     |   54:54 |    1 | Non-Fault translation timing Disable when using TTBR1_EL1 . Controls how a TLB miss is reported in response to a non-fault unprivileged access for a virtual address that is translated using TTBR1_EL1 . If SVE is implemented, the affected access types include: All accesses due to an SVE non-fault contiguous load instruction. Accesses due to an SVE first-fault gather load instruction that are not for the First active element. Accesses due to an SVE first-fault contiguous load instruction are not affected. Accesses due to prefetch instructions might be affected, but the effect is not architecturally visible. If FEAT_TME is implemented, the affected access types include all accesses generated by a load or store instruction in Transactional state.
| NFD0     |   53:53 |    1 | Non-Fault translation timing Disable when using TTBR0_EL1 . Controls how a TLB miss is reported in response to a non-fault unprivileged access for a virtual address that is translated using TTBR0_EL1 . If SVE is implemented, the affected access types include: All accesses due to an SVE non-fault contiguous load instruction. Accesses due to an SVE first-fault gather load instruction that are not for the First active element. Accesses due to an SVE first-fault contiguous load instruction are not affected. Accesses due to prefetch instructions might be affected, but the effect is not architecturally visible. If FEAT_TME is implemented, the affected access types include all accesses generated by a load or store instruction in Transactional state.
| TBID1    |   52:52 |    1 | Controls the use of the top byte of instruction addresses for address matching. For the purpose of this field, all cache maintenance and address translation instructions that perform address translation are treated as data accesses. For more information, see 'Address tagging' .
| TBID0    |   51:51 |    1 | Controls the use of the top byte of instruction addresses for address matching. For the purpose of this field, all cache maintenance and address translation instructions that perform address translation are treated as data accesses. For more information, see 'Address tagging' .
| HWU162   |   50:50 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[62] of the stage 1 translation table Block or Page entry for translations using TTBR1_EL1 .
| HWU161   |   49:49 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[61] of the stage 1 translation table Block or Page entry for translations using TTBR1_EL1 .
| HWU160   |   48:48 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[60] of the stage 1 translation table Block or Page entry for translations using TTBR1_EL1 .
| HWU159   |   47:47 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[59] of the stage 1 translation table Block or Page entry for translations using TTBR1_EL1 .
| HWU062   |   46:46 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[62] of the stage 1 translation table Block or Page entry for translations using TTBR0_EL1 .
| HWU061   |   45:45 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[61] of the stage 1 translation table Block or Page entry for translations using TTBR0_EL1 .
| HWU060   |   44:44 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[60] of the stage 1 translation table Block or Page entry for translations using TTBR0_EL1 .
| HWU059   |   43:43 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[59] of the stage 1 translation table Block or Page entry for translations using TTBR0_EL1 .
| HPD1     |   42:42 |    1 | Hierarchical Permission Disables. This affects the hierarchical control bits, APTable, PXNTable, and UXNTable, except NSTable, in the translation tables pointed to by TTBR1_EL1 .
| HPD0     |   41:41 |    1 | Hierarchical Permission Disables. This affects the hierarchical control bits, APTable, PXNTable, and UXNTable, except NSTable, in the translation tables pointed to by TTBR0_EL1 .
| HD       |   40:40 |    1 | Hardware management of dirty state in stage 1 translations from EL0 and EL1.
| HA       |   39:39 |    1 | Hardware Access flag update in stage 1 translations from EL0 and EL1.
| TBI1     |   38:38 |    1 | Top Byte ignored. Indicates whether the top byte of an address is used for address match for the TTBR1_EL1 region, or ignored and used for tagged addresses.
| TBI0     |   37:37 |    1 | Top Byte ignored. Indicates whether the top byte of an address is used for address match for the TTBR0_EL1 region, or ignored and used for tagged addresses.
| AS       |   36:36 |    1 | ASID Size.
| IPS      |   34:32 |    3 | Intermediate Physical Address Size.
| TG1      |   31:30 |    2 | Granule size for the TTBR1_EL1 .
| SH1      |   29:28 |    2 | Shareability attribute for memory associated with translation table walks using TTBR1_EL1 .
| ORGN1    |   27:26 |    2 | Outer cacheability attribute for memory associated with translation table walks using TTBR1_EL1 .
| IRGN1    |   25:24 |    2 | Inner cacheability attribute for memory associated with translation table walks using TTBR1_EL1 .
| EPD1     |   23:23 |    1 | Translation table walk disable for translations using TTBR1_EL1 . This bit controls whether a translation table walk is performed on a TLB miss, for an address that is translated using TTBR1_EL1 . The encoding of this bit is:
| A1       |   22:22 |    1 | Selects whether TTBR0_EL1 or TTBR1_EL1 defines the ASID. The encoding of this bit is:
| T1SZ     |   21:16 |    6 | The size offset of the memory region addressed by TTBR1_EL1 . The region size is 2 (64-T1SZ) bytes. The maximum and minimum possible values for T1SZ depend on the level of translation table and the memory translation granule size, as described in the AArch64 Virtual Memory System Architecture chapter. For the 4KB translation granule, if FEAT_LPA2 is implemented, TCR_EL1.DS is 1, and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented, TCR_EL1.DS is 1, and this field is less than 17, the translation table walk begins with a level 0 initial lookup.
| TG0      |   15:14 |    2 | Granule size for the TTBR0_EL1 .
| SH0      |   13:12 |    2 | Shareability attribute for memory associated with translation table walks using TTBR0_EL1 .
| ORGN0    |   11:10 |    2 | Outer cacheability attribute for memory associated with translation table walks using TTBR0_EL1 .
| IRGN0    |     9:8 |    2 | Inner cacheability attribute for memory associated with translation table walks using TTBR0_EL1 .
| EPD0     |     7:7 |    1 | Translation table walk disable for translations using TTBR0_EL1 . This bit controls whether a translation table walk is performed on a TLB miss, for an address that is translated using TTBR0_EL1 . The encoding of this bit is:
| T0SZ     |     5:0 |    6 | The size offset of the memory region addressed by TTBR0_EL1 . The region size is 2 (64-T0SZ) bytes. The maximum and minimum possible values for T0SZ depend on the level of translation table and the memory translation granule size, as described in the AArch64 Virtual Memory System Architecture chapter. For the 4KB translation granule, if FEAT_LPA2 is implemented, TCR_EL1.DS is 1, and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented, TCR_EL1.DS is 1, and this field is less than 17, the translation table walk begins with a level 0 initial lookup.

## TCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MTX      |   33:33 |    1 | Extended memory tag checking. This field controls address generation and tag checking when EL2 is using AArch64 where the data address would be translated by tables pointed to by TTBR0_EL2 . This control has an effect regardless of whether stage 1 of the EL2 translation regime is enabled or not.
| DS       |   32:32 |    1 | This field affects: Whether a 52-bit output address can be described by the translation tables of the 4KB or 16KB translation granules. The minimum value of TCR_EL2.T0SZ. How and where shareability for Block and Page descriptors are encoded.
| TCMA     |   30:30 |    1 | Controls the generation of Unchecked accesses at EL2 when address [59:56] = 0b0000 .
| TBID     |   29:29 |    1 | Controls the use of the top byte of instruction addresses for address matching. For the purpose of this field, all cache maintenance and address translation instructions that perform address translation are treated as data accesses. For more information, see 'Address tagging' .
| HWU62    |   28:28 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[62] of the stage 1 translation table Block or Page entry.
| HWU61    |   27:27 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[61] of the stage 1 translation table Block or Page entry.
| HWU60    |   26:26 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[60] of the stage 1 translation table Block or Page entry.
| HWU59    |   25:25 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[59] of the stage 1 translation table Block or Page entry.
| HPD      |   24:24 |    1 | Hierarchical Permission Disables. This affects the hierarchical control bits, APTable, PXNTable, and UXNTable, except NSTable, in the translation tables pointed to by TTBR0_EL2 .
| HD       |   22:22 |    1 | Hardware management of dirty state in stage 1 translations from EL2.
| HA       |   21:21 |    1 | Hardware Access flag update in stage 1 translations from EL2.
| TBI      |   20:20 |    1 | Top Byte Ignored. Indicates whether the top byte of an address is used for address match for the TTBR0_EL2 region, or ignored and used for tagged addresses. For more information, see 'Address tagging' .
| PS       |   18:16 |    3 | Physical Address Size.
| TG0      |   15:14 |    2 | Granule size for the TTBR0_EL2 .
| SH0      |   13:12 |    2 | Shareability attribute for memory associated with translation table walks using TTBR0_EL2 .
| ORGN0    |   11:10 |    2 | Outer cacheability attribute for memory associated with translation table walks using TTBR0_EL2 .
| IRGN0    |     9:8 |    2 | Inner cacheability attribute for memory associated with translation table walks using TTBR0_EL2 .
| T0SZ     |     5:0 |    6 | The size offset of the memory region addressed by TTBR0_EL2 . The region size is 2 (64-T0SZ) bytes. The maximum and minimum possible values for T0SZ depend on the level of translation table and the memory translation granule size, as described in the AArch64 Virtual Memory System Architecture chapter. For the 4KB translation granule, if FEAT_LPA2 is implemented, TCR_EL2.DS is 1, and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented, TCR_EL2.DS is 1, and this field is less than 17, the translation table walk begins with a level 0 initial lookup.

## TCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DisCH0   |   43:43 |    1 | Disable the Contiguous bit for the Start Table.
| HAFT     |   42:42 |    1 | Hardware managed Access Flag for Table descriptors. Enables the Hardware managed Access Flag for Table descriptors.
| PTTWI    |   41:41 |    1 | Permit Translation table walk Incoherence. Permits RCWS instructions to generate writes that have the Reduced Coherence property.
| D128     |   38:38 |    1 | Enables VMSAv9-128 translation system.
| AIE      |   37:37 |    1 | Enable Attribute Indexing Extension.
| POE      |   36:36 |    1 | Enables Permission Overlay for EL3 accesses.
| PIE      |   35:35 |    1 | Enables usage of Indirect Permission Scheme.
| PnCH     |   34:34 |    1 | Protected attribute enable. Indicates use of bit[52] of the stage 1 translation table entry for translations using TTBR0_EL3 .
| MTX      |   33:33 |    1 | Extended memory tag checking. This field controls address generation and tag checking when EL3 is using AArch64 where the data address would be translated by tables pointed to by TTBR0_EL3 . This control has an effect regardless of whether stage 1 of the EL3 translation regime is enabled or not.
| DS       |   32:32 |    1 | This field affects: Whether a 52-bit output address can be described by the translation tables of the 4KB or 16KB translation granules. The minimum value of TCR_EL3.T0SZ. How and where shareability for Block and Page descriptors are encoded.
| TCMA     |   30:30 |    1 | Controls the generation of Unchecked accesses at EL3 when address [59:56] = 0b0000 .
| TBID     |   29:29 |    1 | Controls the use of the top byte of instruction addresses for address matching.
| HWU62    |   28:28 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[62] of the stage 1 translation table Block or Page entry.
| HWU61    |   27:27 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[61] of the stage 1 translation table Block or Page entry.
| HWU60    |   26:26 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[60] of the stage 1 translation table Block or Page entry.
| HWU59    |   25:25 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[59] of the stage 1 translation table Block or Page entry.
| HPD      |   24:24 |    1 | Hierarchical Permission Disables. This affects the hierarchical control bits, APTable, PXNTable, and UXNTable, except NSTable, in the translation tables pointed to by TTBR0_EL3 .
| HD       |   22:22 |    1 | Hardware management of dirty state in stage 1 translations from EL3.
| HA       |   21:21 |    1 | Hardware Access flag update in stage 1 translations from EL3.
| TBI      |   20:20 |    1 | Top Byte Ignored. Indicates whether the top byte of an address is used for address match for the TTBR0_EL3 region, or ignored and used for tagged addresses.
| PS       |   18:16 |    3 | Physical Address Size.
| TG0      |   15:14 |    2 | Granule size for the TTBR0_EL3 .
| SH0      |   13:12 |    2 | Shareability attribute for memory associated with translation table walks using TTBR0_EL3 .
| ORGN0    |   11:10 |    2 | Outer cacheability attribute for memory associated with translation table walks using TTBR0_EL3 .
| IRGN0    |     9:8 |    2 | Inner cacheability attribute for memory associated with translation table walks using TTBR0_EL3 .
| T0SZ     |     5:0 |    6 | The size offset of the memory region addressed by TTBR0_EL3 . The region size is 2 (64-T0SZ) bytes. The maximum and minimum possible values for T0SZ depend on the level of translation table and the memory translation granule size, as described in the AArch64 Virtual Memory System Architecture chapter. For the 4KB translation granule, if FEAT_LPA2 is implemented, TCR_EL3.DS is 1, and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented, TCR_EL3.DS is 1, and this field is less than 17, the translation table walk begins with a level 0 initial lookup.

## TCRMASK_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MTX1     |   61:61 |    1 | Mask bit for MTX1.
| MTX0     |   60:60 |    1 | Mask bit for MTX0.
| DS       |   59:59 |    1 | Mask bit for DS.
| TCMA1    |   58:58 |    1 | Mask bit for TCMA1.
| TCMA0    |   57:57 |    1 | Mask bit for TCMA0.
| E0PD1    |   56:56 |    1 | Mask bit for E0PD1.
| E0PD0    |   55:55 |    1 | Mask bit for E0PD0.
| NFD1     |   54:54 |    1 | Mask bit for NFD1.
| NFD0     |   53:53 |    1 | Mask bit for NFD0.
| TBID1    |   52:52 |    1 | Mask bit for TBID1.
| TBID0    |   51:51 |    1 | Mask bit for TBID0.
| HWU162   |   50:50 |    1 | Mask bit for HWU162.
| HWU161   |   49:49 |    1 | Mask bit for HWU161.
| HWU160   |   48:48 |    1 | Mask bit for HWU160.
| HWU159   |   47:47 |    1 | Mask bit for HWU159.
| HWU062   |   46:46 |    1 | Mask bit for HWU062.
| HWU061   |   45:45 |    1 | Mask bit for HWU061.
| HWU060   |   44:44 |    1 | Mask bit for HWU060.
| HWU059   |   43:43 |    1 | Mask bit for HWU059.
| HPD1     |   42:42 |    1 | Mask bit for HPD1.
| HPD0     |   41:41 |    1 | Mask bit for HPD0.
| HD       |   40:40 |    1 | Mask bit for HD.
| HA       |   39:39 |    1 | Mask bit for HA.
| TBI1     |   38:38 |    1 | Mask bit for TBI1.
| TBI0     |   37:37 |    1 | Mask bit for TBI0.
| AS       |   36:36 |    1 | Mask bit for AS.
| IPS      |   32:32 |    1 | Mask bit for IPS.
| TG1      |   30:30 |    1 | Mask bit for TG1.
| SH1      |   28:28 |    1 | Mask bit for SH1.
| ORGN1    |   26:26 |    1 | Mask bit for ORGN1.
| IRGN1    |   24:24 |    1 | Mask bit for IRGN1.
| EPD1     |   23:23 |    1 | Mask bit for EPD1.
| A1       |   22:22 |    1 | Mask bit for A1.
| T1SZ     |   16:16 |    1 | Mask bit for T1SZ.
| TG0      |   14:14 |    1 | Mask bit for TG0.
| SH0      |   12:12 |    1 | Mask bit for SH0.
| ORGN0    |   10:10 |    1 | Mask bit for ORGN0.
| IRGN0    |     8:8 |    1 | Mask bit for IRGN0.
| EPD0     |     7:7 |    1 | Mask bit for EPD0.
| T0SZ     |     0:0 |    1 | Mask bit for T0SZ.

## TCRMASK_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MTX      |   33:33 |    1 | Mask bit for MTX.
| DS       |   32:32 |    1 | Mask bit for DS.
| TCMA     |   30:30 |    1 | Mask bit for TCMA.
| TBID     |   29:29 |    1 | Mask bit for TBID.
| HWU62    |   28:28 |    1 | Mask bit for HWU62.
| HWU61    |   27:27 |    1 | Mask bit for HWU61.
| HWU60    |   26:26 |    1 | Mask bit for HWU60.
| HWU59    |   25:25 |    1 | Mask bit for HWU59.
| HPD      |   24:24 |    1 | Mask bit for HPD.
| HD       |   22:22 |    1 | Mask bit for HD.
| HA       |   21:21 |    1 | Mask bit for HA.
| TBI      |   20:20 |    1 | Mask bit for TBI.
| PS       |   16:16 |    1 | Mask bit for PS.
| TG0      |   14:14 |    1 | Mask bit for TG0.
| SH0      |   12:12 |    1 | Mask bit for SH0.
| ORGN0    |   10:10 |    1 | Mask bit for ORGN0.
| IRGN0    |     8:8 |    1 | Mask bit for IRGN0.
| T0SZ     |     0:0 |    1 | Mask bit for T0SZ.

## TFSR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TF1      |     1:1 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b1 occurs.
| TF0      |     0:0 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b0 occurs.

## TFSR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TF1      |     1:1 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b1 occurs.
| TF0      |     0:0 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b0 occurs.

## TFSR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TF0      |     0:0 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b0 occurs.

## TFSRE0_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TF1      |     1:1 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b1 occurs.
| TF0      |     0:0 |    1 | Tag Check Fault. Asynchronously set to 1 when a Tag Check Fault using a virtual address with bit[55] == 0b0 occurs.

## TRBBASER_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BASE     |   63:12 |   52 | Trace Buffer Base pointer address. (TRBBASER_EL1.BASE << 12) is the address of the first byte in the trace buffer. Bits [11:0] of the Base pointer address are always zero. If the smallest implemented translation granule is not 4KB, then TRBBASER_EL1[N-1:12] are RES0 , where N is the IMPLEMENTATION DEFINED value Log 2 (smallest implemented translation granule).

## TRBIDR_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| MaxBuffSize |   47:32 |   16 | Maximum supported trace buffer size. Reserved for software use.
| MPAM        |   15:12 |    4 | MPAM extensions. Indicates Memory Partitioning and Monitoring (MPAM) support in the Trace Buffer Unit when using External mode.
| EA          |    11:8 |    4 | External Abort handling. Describes how the PE manages External aborts on writes made by the Trace Buffer Unit to the trace buffer.
| AddrMode    |     7:6 |    2 | Address Modes. Describes the addressing modes available for the trace buffer.
| F           |     5:5 |    1 | Flag updates. Describes how address translations performed by the Trace Buffer Unit manage the Access flag and dirty state.
| P           |     4:4 |    1 | Programming not allowed. When read at EL3, this field reads as zero. Otherwise, indicates that the trace buffer is owned by a higher Exception level or another Security state.
| Align       |     3:0 |    4 | Defines the minimum alignment constraint for writes to TRBPTR_EL1 and TRBTRG_EL1 .

## TRBLIMITR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LIMIT    |   63:12 |   52 | Trace Buffer Limit pointer address. (TRBLIMITR_EL1.LIMIT << 12) is the address of the last byte in the trace buffer plus one. Bits [11:0] of the Limit pointer address are always zero. If the smallest implemented translation granule is not 4KB, then TRBLIMITR_EL1[N-1:12] are RES0 , where N is the IMPLEMENTATION DEFINED value Log 2 (smallest implemented translation granule).
| XE       |     6:6 |    1 | Trace Buffer Unit External mode enable. Used for save/restore of TRBLIMITR_EL1 .XE.
| nVM      |     5:5 |    1 | Address mode.
| TM       |     4:3 |    2 | Trigger mode.
| FM       |     2:1 |    2 | Trace buffer mode.
| E        |     0:0 |    1 | Trace Buffer Unit enable. Controls whether the Trace Buffer Unit is enabled when SelfHostedTraceEnabled() == TRUE.

## TRBMAR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PAS      |   11:10 |    2 | Physical address specifier. Defines the PAS attribute for memory addressed by the buffer in External mode.
| SH       |     9:8 |    2 | Trace buffer shareability domain. Defines the shareability domain for Normal memory used by the trace buffer.
| Attr     |     7:0 |    8 | Trace buffer memory type and attributes. Defines the memory type and, for Normal memory, the cacheability attributes, for memory addressed by the trace buffer. The encoding of this field is the same as that of a MAIR_ELx .Attr<n> field, as follows: Attr Meaning 0b0000dd00 Device memory. See encoding of 'dd' for the type of Device memory. 0b0000dd01 If FEAT_XS is implemented: Device memory with the XS attribute set to 0. See encoding of 'dd' for the type of Device memory. Otherwise, UNPREDICTABLE . 0b0000dd1x UNPREDICTABLE . 0booooiiii where oooo != 0000 and iiii != 0000 Normal memory. See encoding of 'oooo' and 'iiii' for the type of Normal memory. 0b01000000 If FEAT_XS is implemented: Normal Inner Non-cacheable, Outer Non-cacheable memory with the XS attribute set to 0. Otherwise, UNPREDICTABLE . 0b10100000 If FEAT_XS is implemented: Normal Inner Write-through Cacheable, Outer Write-through Cacheable, Read-Allocate, No-Write Allocate, Non-transient memory with the XS attribute set to 0. Otherwise, UNPREDICTABLE . 0b11110000 If FEAT_MTE2 is implemented: Tagged Normal Inner Write-Back, Outer Write-Back, Read-Allocate, Write-Allocate Non-transient memory. Otherwise, UNPREDICTABLE . 0bxxxx0000 where xxxx != 0000 and xxxx != 0100 and xxxx != 1010 and xxxx != 1111 UNPREDICTABLE . dd is encoded as follows: 'dd' Meaning 0b00 Device-nGnRnE memory. 0b01 Device-nGnRE memory. 0b10 Device-nGRE memory. 0b11 Device-GRE memory. oooo is encoded as follows: 'oooo' Meaning 0b0000 See encoding of Attr. 0b00RW where RW != 00 Normal memory, Outer Write-Through Transient. 0b0100 Normal memory, Outer Non-cacheable. 0b01RW where RW != 00 Normal memory, Outer Write-Back Transient. 0b10RW Normal memory, Outer Write-Through Non-transient. 0b11RW Normal memory, Outer Write-Back Non-transient. R encodes the Outer Read-Allocate policy and W encodes the Outer Write-Allocate policy. iiii is encoded as follows: 'iiii' Meaning 0b0000 See encoding of Attr. 0b00RW where RW != 00 Normal memory, Inner Write-Through Transient. 0b0100 Normal memory, Inner Non-cacheable. 0b01RW where RW != 00 Normal memory, Inner Write-Back Transient. 0b10RW Normal memory, Inner Write-Through Non-transient. 0b11RW Normal memory, Inner Write-Back Non-transient. R encodes the Inner Read-Allocate policy and W encodes the Inner Write-Allocate policy. In oooo and iiii , R and W are encoded as follows: 'R' or 'W' Meaning 0b0 No Allocate. 0b1 Allocate. When FEAT_XS is implemented, stage 1 Inner Write-Back Cacheable, Outer Write-Back Cacheable memory types have the XS attribute set to 0.

## TRBMPAM_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EN       |   26:26 |    1 | Enable. Enables use of non-default MPAM values.
| MPAM_SP  |   25:24 |    2 | Partition Identifier space. Selects the PARTID space.
| PMG      |   23:16 |    8 | Performance Monitoring Group. Selects the PMG.
| PARTID   |    15:0 |   16 | Partition Identifier. Selects the PARTID.

## TRBSR_EL1 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the trace buffer management event.
| IRQ                    |   22:22 |    1 | Maintenance status. Indicates that a trace buffer management event has been recorded.
| TRG                    |   21:21 |    1 | Triggered.
| WRAP                   |   20:20 |    1 | Wrapped.
| EA                     |   18:18 |    1 | Reserved, RES0 .
| S                      |   17:17 |    1 | Stopped.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the trace buffer management event. The syndrome contents for each trace buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Trace buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## TRBSR_EL2 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the trace buffer management event.
| IRQ                    |   22:22 |    1 | Maintenance status. Indicates that a trace buffer management event has been recorded.
| TRG                    |   21:21 |    1 | Triggered.
| WRAP                   |   20:20 |    1 | Wrapped.
| EA                     |   18:18 |    1 | Reserved, RES0 .
| S                      |   17:17 |    1 | Stopped.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the trace buffer management event. The syndrome contents for each trace buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Trace buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## TRBSR_EL3 bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| MSS2                   |   55:32 |   24 | Management event Specific Syndrome 2. Contains syndrome specific to the management event. The syndrome contents for each management event are described in the following sections.
| EC                     |   31:26 |    6 | Event class. Top-level description of the cause of the trace buffer management event.
| IRQ                    |   22:22 |    1 | Maintenance status. Indicates that a trace buffer management event has been recorded.
| TRG                    |   21:21 |    1 | Triggered.
| WRAP                   |   20:20 |    1 | Wrapped.
| EA                     |   18:18 |    1 | Reserved, RES0 .
| S                      |   17:17 |    1 | Stopped.
| TopLevel               |     8:8 |    1 | TopLevel. Indicates if the fault was due to TopLevel.
| AssuredOnly            |     7:7 |    1 | AssuredOnly flag. If a memory access generates a stage 2 Data Abort, then this field holds information about the fault.
| Overlay                |     6:6 |    1 | Overlay flag. If a memory access generates a Data Abort for a Permission fault, then this field holds information about the fault.
| DirtyBit               |     5:5 |    1 | DirtyBit flag. If a write access to memory generates a Data Abort for a Permission fault using Indirect Permission, then this field holds information about the fault.
| IMPLEMENTATION DEFINED |    23:0 |   24 | IMPLEMENTATION DEFINED .
| MSS                    |    15:0 |   16 | Management Event Specific Syndrome. Contains syndrome specific to the trace buffer management event. The syndrome contents for each trace buffer management event are described in the following sections.
| BSC                    |     5:0 |    6 | Trace buffer status code
| FSC                    |     5:0 |    6 | Fault status code
| IMPLEMENTATION DEFINED |    15:0 |   16 | IMPLEMENTATION DEFINED .

## TRBTRG_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TRG      |    31:0 |   32 | Trigger count. Specifies the number of bytes of trace to capture following a Detected Trigger before a Trigger Event. TRBTRG_EL1 decrements by 1 for every byte of trace written to the trace buffer when all of the following are true: TRBTRG_EL1 is nonzero. TRBSR_EL1 .TRG is 1. The architecture places restrictions on the values that software can write to the counter.

## TRCAUTHSTATUS bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RTNID    |   27:26 |    2 | Root non-invasive debug. This field has the same value as DBGAUTHSTATUS_EL1 .RTNID.
| RTID     |   25:24 |    2 | Root invasive debug.
| RLNID    |   15:14 |    2 | Realm non-invasive debug. This field has the same value as DBGAUTHSTATUS_EL1 .RLNID.
| RLID     |   13:12 |    2 | Realm invasive debug.
| HNID     |   11:10 |    2 | Hyp Non-invasive Debug. Indicates whether a separate enable control for EL2 non-invasive debug features is implemented and enabled.
| HID      |     9:8 |    2 | Hyp Invasive Debug. Indicates whether a separate enable control for EL2 invasive debug features is implemented and enabled.
| SNID     |     7:6 |    2 | Secure Non-invasive Debug. Indicates whether Secure non-invasive debug features are implemented and enabled.
| SID      |     5:4 |    2 | Secure Invasive Debug. Indicates whether Secure invasive debug features are implemented and enabled.
| NSNID    |     3:2 |    2 | Non-secure Non-invasive Debug. Indicates whether Non-secure non-invasive debug features are implemented and enabled.
| NSID     |     1:0 |    2 | Non-secure Invasive Debug. Indicates whether Non-secure invasive debug features are implemented and enabled.

## TRCAUXCTLR bitfields

| Bitfield               | msb:lsb | Size | Description
| ---------------------- | ------: | ---: | -----------
| IMPLEMENTATION DEFINED |    31:0 |   32 | IMPLEMENTATION DEFINED .

## TRCBBCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| MODE       |     8:8 |    1 | Mode.
| RANGE[<m>] |     7:0 |    8 | Selects whether Address Range Comparator <m> is used with branch broadcasting.

## TRCCCCTLR bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| THRESHOLD |    11:0 |   12 | Sets the threshold value for instruction trace cycle counting. The minimum threshold value that can be programmed into THRESHOLD is given in TRCIDR3 .CCITMIN. If the THRESHOLD value is smaller than the value in TRCIDR3 .CCITMIN then the behavior is CONSTRAINED UNPREDICTABLE . That is, cycle counts might or might not be included in the trace and the cycle count threshold is not known. Writing a value of zero when TRCCONFIGR .CCI enables instruction trace cycle counting results in CONSTRAINED UNPREDICTABLE behavior. That is, cycle counts might or might not be included in the trace and the cycle count threshold is not known.

## TRCCIDCCTLR0 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| COMP3[<m>] |   31:24 |    8 | TRCCIDCVR3 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR3. Each bit in this field corresponds to a byte in TRCCIDCVR3.
| COMP2[<m>] |   23:16 |    8 | TRCCIDCVR2 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR2. Each bit in this field corresponds to a byte in TRCCIDCVR2.
| COMP1[<m>] |    15:8 |    8 | TRCCIDCVR1 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR1. Each bit in this field corresponds to a byte in TRCCIDCVR1.
| COMP0[<m>] |     7:0 |    8 | TRCCIDCVR0 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR0. Each bit in this field corresponds to a byte in TRCCIDCVR0.

## TRCCIDCCTLR1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| COMP7[<m>] |   31:24 |    8 | TRCCIDCVR7 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR7. Each bit in this field corresponds to a byte in TRCCIDCVR7.
| COMP6[<m>] |   23:16 |    8 | TRCCIDCVR6 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR6. Each bit in this field corresponds to a byte in TRCCIDCVR6.
| COMP5[<m>] |    15:8 |    8 | TRCCIDCVR5 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR5. Each bit in this field corresponds to a byte in TRCCIDCVR5.
| COMP4[<m>] |     7:0 |    8 | TRCCIDCVR4 mask control. Specifies the mask value that the trace unit applies to TRCCIDCVR4. Each bit in this field corresponds to a byte in TRCCIDCVR4.

## TRCCLAIMCLR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| CLR[<m>] |    31:0 |   32 | Claim Tag Clear. Indicates the current status of Claim Tag bit <m>, and is used to clear Claim Tag bit <m> to 0.

## TRCCLAIMSET bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SET[<m>] |    31:0 |   32 | Claim Tag Set. Indicates whether Claim Tag bit <m> is implemented, and is used to set Claim Tag bit <m> to 1.

## TRCCONFIGR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| ITO      |   18:18 |    1 | Instrumentation Trace Override.
| VMIDOPT  |   15:15 |    1 | Virtual context identifier selection control.
| QE       |   14:13 |    2 | Q element generation control.
| RS       |   12:12 |    1 | Return stack control.
| TS       |   11:11 |    1 | Global timestamp tracing control.
| VMID     |     7:7 |    1 | Virtual context identifier tracing control.
| CID      |     6:6 |    1 | Context identifier tracing control.
| CCI      |     4:4 |    1 | Cycle counting instruction tracing control.
| BB       |     3:3 |    1 | Branch broadcasting control.

## TRCDEVARCH bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| ARCHITECT |   31:21 |   11 | Defines the architect of the component. For Trace, this is Arm Limited. Bits [31:28] are the JEP106 continuation code, 0b0100 . Bits [27:21] are the JEP106 identification code, 0b0111011 .
| PRESENT   |   20:20 |    1 | DEVARCH present. Indicates that the TRCDEVARCH register is present.
| REVISION  |   19:16 |    4 | Revision. Defines the architecture revision of the component.
| ARCHVER   |   15:12 |    4 | Architecture Version. Defines the architecture version of the component.
| ARCHPART  |    11:0 |   12 | Architecture Part. Defines the architecture of the component.

## TRCEVENTCTL0R bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| EVENT3_TYPE |   31:31 |    1 | Chooses the type of Resource Selector.
| EVENT3_SEL  |   28:24 |    5 | When any of the selected resource events occurs and TRCEVENTCTL1R .INSTEN[3] == 1, then Event element 3 is generated in the instruction trace element stream. Defines the selected Resource Selector or pair of Resource Selectors. TRCEVENTCTL0R.EVENT3.TYPE controls whether TRCEVENTCTL0R.EVENT3.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.
| EVENT2_TYPE |   23:23 |    1 | Chooses the type of Resource Selector.
| EVENT2_SEL  |   20:16 |    5 | When any of the selected resource events occurs and TRCEVENTCTL1R .INSTEN[2] == 1, then Event element 2 is generated in the instruction trace element stream. Defines the selected Resource Selector or pair of Resource Selectors. TRCEVENTCTL0R.EVENT2.TYPE controls whether TRCEVENTCTL0R.EVENT2.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.
| EVENT1_TYPE |   15:15 |    1 | Chooses the type of Resource Selector.
| EVENT1_SEL  |    12:8 |    5 | When any of the selected resource events occurs and TRCEVENTCTL1R .INSTEN[1] == 1, then Event element 1 is generated in the instruction trace element stream. Defines the selected Resource Selector or pair of Resource Selectors. TRCEVENTCTL0R.EVENT1.TYPE controls whether TRCEVENTCTL0R.EVENT1.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.
| EVENT0_TYPE |     7:7 |    1 | Chooses the type of Resource Selector.
| EVENT0_SEL  |     4:0 |    5 | When any of the selected resource events occurs and TRCEVENTCTL1R .INSTEN[0] == 1, then Event element 0 is generated in the instruction trace element stream. Defines the selected Resource Selector or pair of Resource Selectors. TRCEVENTCTL0R.EVENT0.TYPE controls whether TRCEVENTCTL0R.EVENT0.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.

## TRCEVENTCTL1R bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| OE          |   13:13 |    1 | ETE Trace Output Enable control.
| LPOVERRIDE  |   12:12 |    1 | Low-power Override Mode select.
| ATB         |   11:11 |    1 | AMBA Trace Bus (ATB) trigger enable. If a CoreSight ATB interface is implemented then when ETEEvent 0 occurs the trace unit sets: ATID == 0x7D . ATDATA to the value of TRCTRACEIDR . If the width of ATDATA is greater than the width of TRCTRACEIDR .TRACEID then the trace unit zeros the upper ATDATA bits. If ETEEvent 0 is programmed to occur based on program execution, such as an Address Comparator, the ATB trigger might not be inserted into the ATB stream at the same time as any trace generated by that program execution is output by the trace unit. Typically, the generated trace might be buffered in a trace unit which means that the ATB trigger would be output before the associated trace is output. If ETEEvent 0 is asserted multiple times in close succession, the trace unit is required to generate an ATB trigger for the first assertion, but might ignore one or more of the subsequent assertions. Arm recommends that the window in which ETEEvent 0 is ignored is limited only by the time taken to output an ATB trigger.
| INSTEN[<m>] |     3:0 |    4 | Event element control.

## TRCIDR0 bitfields

| Bitfield  | msb:lsb | Size | Description
| --------- | ------: | ---: | -----------
| COMMTRANS |   30:30 |    1 | Transaction Start element behavior.
| COMMOPT   |   29:29 |    1 | Indicates the contents and encodings of Cycle count packets.
| TSSIZE    |   28:24 |    5 | Indicates that the trace unit implements Global timestamping and the size of the timestamp value.
| TSMARK    |   23:23 |    1 | Indicates whether Timestamp Marker elements are generated.
| ITE       |   22:22 |    1 | Indicates whether Instrumentation Trace is implemented.
| TRCEXDATA |   17:17 |    1 | Indicates if the trace unit implements tracing of data transfers for exceptions and exception returns. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.
| QSUPP     |   16:15 |    2 | Indicates that the trace unit implements Q element support.
| QFILT     |   14:14 |    1 | Indicates if the trace unit implements Q element filtering.
| CONDTYPE  |   13:12 |    2 | Indicates how conditional instructions are traced. Conditional instruction tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.
| NUMEVENT  |   11:10 |    2 | Indicates the number of ETEEvents implemented.
| RETSTACK  |     9:9 |    1 | Indicates if the trace unit supports the return stack.
| TRCCCI    |     7:7 |    1 | Indicates if the trace unit implements cycle counting.
| TRCCOND   |     6:6 |    1 | Indicates if the trace unit implements conditional instruction tracing. Conditional instruction tracing is not implemented in ETE and this field is reserved for other trace architectures.
| TRCBB     |     5:5 |    1 | Indicates if the trace unit implements branch broadcasting.
| TRCDATA   |     4:3 |    2 | Indicates if the trace unit implements data tracing. Data tracing is not implemented in ETE and this field is reserved for other trace architectures.
| INSTP0    |     2:1 |    2 | Indicates if load and store instructions are P0 instructions. Load and store instructions as P0 instructions is not implemented in ETE and this field is reserved for other trace architectures.

## TRCIDR1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| DESIGNER   |   31:24 |    8 | Indicates which company designed the trace unit. The permitted values of this field are the same as MIDR_EL1 .Implementer.
| TRCARCHMAJ |    11:8 |    4 | Major architecture version.
| TRCARCHMIN |     7:4 |    4 | Minor architecture version.
| REVISION   |     3:0 |    4 | Implementation revision. Returns an IMPLEMENTATION DEFINED value that identifies the revision of the trace unit. Arm deprecates any use of this field and recommends that implementations set this field to zero.

## TRCIDR10 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NUMP1KEY |    31:0 |   32 | Indicates the number of P1 right-hand keys. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.

## TRCIDR11 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NUMP1SPC |    31:0 |   32 | Indicates the number of special P1 right-hand keys. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.

## TRCIDR12 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| NUMCONDKEY |    31:0 |   32 | Indicates the number of conditional instruction right-hand keys. Conditional instruction tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.

## TRCIDR13 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| NUMCONDSPC |    31:0 |   32 | Indicates the number of special conditional instruction right-hand keys. Conditional instruction tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.

## TRCIDR2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| WFXMODE  |   31:31 |    1 | Indicates whether WFI , WFIT , WFE , and WFET instructions are classified as P0 instructions:
| VMIDOPT  |   30:29 |    2 | Indicates the options for Virtual context identifier selection.
| CCSIZE   |   28:25 |    4 | Indicates the size of the cycle counter.
| DVSIZE   |   24:20 |    5 | Indicates the data value size in bytes. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.
| DASIZE   |   19:15 |    5 | Indicates the data address size in bytes. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.
| VMIDSIZE |   14:10 |    5 | Indicates the trace unit Virtual context identifier size.
| CIDSIZE  |     9:5 |    5 | Indicates the Context identifier size.
| IASIZE   |     4:0 |    5 | Virtual instruction address size.

## TRCIDR3 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| NOOVERFLOW     |   31:31 |    1 | Indicates if overflow prevention is implemented.
| NUMPROC        |   30:28 |    3 | Indicates the number of PEs available for tracing.
| SYSSTALL       |   27:27 |    1 | Indicates if stalling of the PE is permitted.
| STALLCTL       |   26:26 |    1 | Indicates if trace unit implements stalling of the PE.
| SYNCPR         |   25:25 |    1 | Indicates if an implementation has a fixed synchronization period.
| TRCERR         |   24:24 |    1 | Indicates forced tracing of System Error exceptions is implemented.
| EXLEVEL_NS_EL2 |   22:22 |    1 | Indicates if Non-secure EL2 is implemented.
| EXLEVEL_NS_EL1 |   21:21 |    1 | Indicates if Non-secure EL1 is implemented.
| EXLEVEL_NS_EL0 |   20:20 |    1 | Indicates if Non-secure EL0 is implemented.
| EXLEVEL_S_EL3  |   19:19 |    1 | Indicates if EL3 is implemented.
| EXLEVEL_S_EL2  |   18:18 |    1 | Indicates if Secure EL2 is implemented.
| EXLEVEL_S_EL1  |   17:17 |    1 | Indicates if Secure EL1 is implemented.
| EXLEVEL_S_EL0  |   16:16 |    1 | Indicates if Secure EL0 is implemented.
| NUMPROC[4:3]   |   13:12 |    2 | This field is bits[4:3] of NUMPROC[4:0]. See NUMPROC[2:0] for the field description.
| CCITMIN        |    11:0 |   12 | Indicates the minimum value that can be programmed in TRCCCCTLR .THRESHOLD.

## TRCIDR4 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| NUMVMIDC   |   31:28 |    4 | Indicates the number of Virtual Context Identifier Comparators that are available for tracing.
| NUMCIDC    |   27:24 |    4 | Indicates the number of Context Identifier Comparators that are available for tracing.
| NUMSSCC    |   23:20 |    4 | Indicates the number of Single-shot Comparator Controls that are available for tracing.
| NUMRSPAIR  |   19:16 |    4 | Indicates the number of resource selector pairs that are available for tracing.
| NUMPC      |   15:12 |    4 | Indicates the number of PE Comparator Inputs that are available for tracing.
| SUPPDAC    |     8:8 |    1 | Indicates whether data address comparisons are implemented. Data address comparisons are not implemented in ETE and are reserved for other trace architectures. Allocated in other trace architectures.
| NUMDVC     |     7:4 |    4 | Indicates the number of data value comparators. Data value comparators are not implemented in ETE and are reserved for other trace architectures. Allocated in other trace architectures.
| NUMACPAIRS |     3:0 |    4 | Indicates the number of Address Comparator pairs that are available for tracing.

## TRCIDR5 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| OE          |   31:31 |    1 | Indicates support for the ETE Trace Output Enable.
| NUMCNTR     |   30:28 |    3 | Indicates the number of Counters that are available for tracing.
| NUMSEQSTATE |   27:25 |    3 | Indicates if the Sequencer is implemented and the number of Sequencer states that are implemented.
| LPOVERRIDE  |   23:23 |    1 | Indicates support for Low-power Override Mode.
| ATBTRIG     |   22:22 |    1 | Indicates if the implementation can support ATB triggers.
| TRACEIDSIZE |   21:16 |    6 | Indicates the trace ID width.
| NUMEXTINSEL |    11:9 |    3 | Indicates how many External Input Selector resources are implemented.
| NUMEXTIN    |     8:0 |    9 | Indicates how many External Inputs are implemented.

## TRCIDR6 bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| EXLEVEL_RL_EL2 |     2:2 |    1 | Indicates if Realm EL2 is implemented.
| EXLEVEL_RL_EL1 |     1:1 |    1 | Indicates if Realm EL1 is implemented.
| EXLEVEL_RL_EL0 |     0:0 |    1 | Indicates if Realm EL0 is implemented.

## TRCIDR8 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MAXSPEC  |    31:0 |   32 | Indicates the maximum speculation depth of the instruction trace element stream. This is the maximum number of P0 elements in the trace element stream that can be speculative at any time.

## TRCIDR9 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| NUMP0KEY |    31:0 |   32 | Indicates the number of P0 right-hand keys. Data tracing is not implemented in ETE and this field is reserved for other trace architectures. Allocated in other trace architectures.

## TRCIMSPEC0 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EN       |     7:4 |    4 | Enable. Controls whether the IMPLEMENTATION DEFINED features are enabled.
| SUPPORT  |     3:0 |    4 | Indicates whether the implementation supports IMPLEMENTATION DEFINED features.

## TRCITECR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| E1E      |     1:1 |    1 | EL1 Instrumentation Trace Enable.
| E0E      |     0:0 |    1 | EL0 Instrumentation Trace Enable.

## TRCITECR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| E2E      |     1:1 |    1 | EL2 Instrumentation Trace Enable.
| E0HE     |     0:0 |    1 | EL0 Instrumentation Trace Enable.

## TRCITEEDCR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RL       |     6:6 |    1 | Instrumentation Trace in Realm state.
| S        |     5:5 |    1 | Instrumentation Trace in Secure state.
| NS       |     4:4 |    1 | Instrumentation Trace in Non-secure state.
| E3       |     3:3 |    1 | Instrumentation Trace Enable at EL3.
| E<m>     |     2:0 |    3 | Instrumentation Trace Enable at EL<m>.

## TRCOSLSR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| OSLM     |     4:3 |    2 | OS Lock model.
| OSLK     |     1:1 |    1 | OS Lock status.
| OSLM[0]  |     0:0 |    1 | This field is bit[0] of OSLM[2:0]. See OSLM[2:1] for the field description.

## TRCPRGCTLR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| EN       |     0:0 |    1 | Trace unit enable.

## TRCQCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| MODE       |     8:8 |    1 | Selects whether the Address Range Comparators selected by TRCQCTLR.RANGE indicate address ranges where the trace unit is permitted to generate Q elements or address ranges where the trace unit is not permitted to generate Q elements:
| RANGE[<m>] |     7:0 |    8 | Specifies whether Address Range Comparator <m> controls Q elements.

## TRCRSR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| TA         |   12:12 |    1 | Tracing active.
| EVENT[<m>] |    11:8 |    4 | Untraced status of ETEEvents.
| EXTIN[<m>] |     3:0 |    4 | The sticky status of the External Input Selectors.

## TRCSEQRSTEVR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RST_TYPE |     7:7 |    1 | Reset field. Selects an event that causes the Sequencer to move to state 0. Chooses the type of Resource Selector.
| RST_SEL  |     4:0 |    5 | Reset field. Selects an event that causes the Sequencer to move to state 0. Defines the selected Resource Selector or pair of Resource Selectors. TRCSEQRSTEVR.RST.TYPE controls whether TRCSEQRSTEVR.RST.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.

## TRCSEQSTR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| STATE    |     1:0 |    2 | Set or returns the state of the Sequencer.

## TRCSTALLCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| NOOVERFLOW |   13:13 |    1 | Trace overflow prevention.
| ISTALL     |     8:8 |    1 | Instruction stall control. Controls if a trace unit can stall the PE when the trace buffer space is less than LEVEL.
| LEVEL      |     3:0 |    4 | Threshold level field. The field can support 16 monotonic levels from 0b0000 to 0b1111 . The value 0b0000 defines the Minimal invasion level. This setting has a greater risk of a trace unit buffer overflow. The value 0b1111 defines the Maximum invasion level. This setting has a reduced risk of a trace unit buffer overflow.

## TRCSTATR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PMSTABLE |     1:1 |    1 | Programmers' model stable.
| IDLE     |     0:0 |    1 | Idle status.

## TRCSYNCPR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| PERIOD   |     4:0 |    5 | Defines the number of bytes of trace between each periodic trace protocol synchronization request.

## TRCTRACEIDR bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| TRACEID  |     6:0 |    7 | Trace ID field. Sets the trace ID value for instruction trace. The width of the field is indicated by the value of TRCIDR5 .TRACEIDSIZE. Unimplemented bits are RES0 .

## TRCTSCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| EVENT_TYPE |     7:7 |    1 | Chooses the type of Resource Selector.
| EVENT_SEL  |     4:0 |    5 | Defines the selected Resource Selector or pair of Resource Selectors. TRCTSCTLR.EVENT.TYPE controls whether TRCTSCTLR.EVENT.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.

## TRCVICTLR bitfields

| Bitfield       | msb:lsb | Size | Description
| -------------- | ------: | ---: | -----------
| EXLEVEL_RL_EL2 |   26:26 |    1 | Filter instruction trace for EL2 in Realm state.
| EXLEVEL_RL_EL1 |   25:25 |    1 | Filter instruction trace for EL1 in Realm state.
| EXLEVEL_RL_EL0 |   24:24 |    1 | Filter instruction trace for EL0 in Realm state.
| EXLEVEL_NS_EL2 |   22:22 |    1 | Filter instruction trace for EL2 in Non-secure state.
| EXLEVEL_NS_EL1 |   21:21 |    1 | Filter instruction trace for EL1 in Non-secure state.
| EXLEVEL_NS_EL0 |   20:20 |    1 | Filter instruction trace for EL0 in Non-secure state.
| EXLEVEL_S_EL3  |   19:19 |    1 | Filter instruction trace for EL3.
| EXLEVEL_S_EL2  |   18:18 |    1 | Filter instruction trace for EL2 in Secure state.
| EXLEVEL_S_EL1  |   17:17 |    1 | Filter instruction trace for EL1 in Secure state.
| EXLEVEL_S_EL0  |   16:16 |    1 | Filter instruction trace for EL0 in Secure state.
| TRCERR         |   11:11 |    1 | Controls the forced tracing of System Error exceptions.
| TRCRESET       |   10:10 |    1 | Controls the forced tracing of PE Resets.
| SSSTATUS       |     9:9 |    1 | ViewInst start/stop function status.
| EVENT_TYPE     |     7:7 |    1 | Chooses the type of Resource Selector.
| EVENT_SEL      |     4:0 |    5 | Defines the selected Resource Selector or pair of Resource Selectors. TRCVICTLR.EVENT.TYPE controls whether TRCVICTLR.EVENT.SEL is the index of a single Resource Selector, or the index of a pair of Resource Selectors.
| Reserved       |     4:0 |    5 | This field is reserved: Bits [4:1] are RES0 . Bit [0] is RES1 .

## TRCVIIECTLR bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| EXCLUDE[<m>] |   23:16 |    8 | Exclude Address Range Comparator <m>. Selects whether Address Range Comparator <m> is in use with the ViewInst exclude function.
| INCLUDE[<m>] |     7:0 |    8 | Include Address Range Comparator <m>. Selects whether Address Range Comparator <m> is in use with the ViewInst include function. Selecting no comparators for the ViewInst include function indicates that all instructions are included by default. The ViewInst exclude function then indicates which ranges are excluded.

## TRCVIPCSSCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| STOP[<m>]  |   23:16 |    8 | Selects whether PE Comparator Input <m> is in use with the ViewInst start/stop function for the purpose of stopping trace.
| START[<m>] |     7:0 |    8 | Selects whether PE Comparator Input <m> is in use with the ViewInst start/stop function for the purpose of starting trace.

## TRCVISSCTLR bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| STOP[<m>]  |   31:16 |   16 | Selects whether Single Address Comparator <m> is used with the ViewInst start/stop function for the purpose of stopping trace.
| START[<m>] |    15:0 |   16 | Selects whether Single Address Comparator <m> is used with the ViewInst start/stop function for the purpose of starting trace.

## TRCVMIDCCTLR0 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| COMP3[<m>] |   31:24 |    8 | TRCVMIDCVR3 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR3. Each bit in this field corresponds to a byte in TRCVMIDCVR3.
| COMP2[<m>] |   23:16 |    8 | TRCVMIDCVR2 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR2. Each bit in this field corresponds to a byte in TRCVMIDCVR2.
| COMP1[<m>] |    15:8 |    8 | TRCVMIDCVR1 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR1. Each bit in this field corresponds to a byte in TRCVMIDCVR1.
| COMP0[<m>] |     7:0 |    8 | TRCVMIDCVR0 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR0. Each bit in this field corresponds to a byte in TRCVMIDCVR0.

## TRCVMIDCCTLR1 bitfields

| Bitfield   | msb:lsb | Size | Description
| ---------- | ------: | ---: | -----------
| COMP7[<m>] |   31:24 |    8 | TRCVMIDCVR7 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR7. Each bit in this field corresponds to a byte in TRCVMIDCVR7.
| COMP6[<m>] |   23:16 |    8 | TRCVMIDCVR6 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR6. Each bit in this field corresponds to a byte in TRCVMIDCVR6.
| COMP5[<m>] |    15:8 |    8 | TRCVMIDCVR5 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR5. Each bit in this field corresponds to a byte in TRCVMIDCVR5.
| COMP4[<m>] |     7:0 |    8 | TRCVMIDCVR4 mask control. Specifies the mask value that the trace unit applies to TRCVMIDCVR4. Each bit in this field corresponds to a byte in TRCVMIDCVR4.

## TRFCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DnVM     |   11:11 |    1 | Reserved for software use in nested virtualization. See also TRFCR_EL2 .DnVM.
| KE       |   10:10 |    1 | Kernel exception enable for TRBE Profiling exceptions taken to EL1.
| EE       |     9:8 |    2 | Exception Enable.
| TS       |     6:5 |    2 | Timestamp Control. Controls which timebase is used for trace timestamps.
| CX       |     3:3 |    1 | Reserved for software use in nested virtualization. See also TRFCR_EL2 .CX.
| E1TRE    |     1:1 |    1 | EL1 Trace Enable.
| E0TRE    |     0:0 |    1 | EL0 Trace Enable.

## TRFCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| DnVM     |   11:11 |    1 | Disable use of physical address trace buffer pointers.
| KE       |   10:10 |    1 | Kernel exception enable for TRBE Profiling exceptions taken to EL2.
| EE       |     9:8 |    2 | Exception Enable.
| TS       |     6:5 |    2 | Timestamp Control. Controls which timebase is used for trace timestamps.
| CX       |     3:3 |    1 | CONTEXTIDR_EL2 and VMID trace enable.
| E2TRE    |     1:1 |    1 | EL2 Trace Enable.
| E0HTRE   |     0:0 |    1 | EL0 Trace Enable.

## TTBR0_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BADDR       |   87:80 |    8 | Translation table base address: Bits A[55:x] of the stage 1 translation table base address bits are in register bits[87:80, 47:x]. Bits A[(x-1):0] of the stage 1 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| ASID        |   63:48 |   16 | An ASID for the translation table base address. The TCR_EL1 .A1 field selects either TTBR0_EL1.ASID or TTBR1_EL1 .ASID. If the implementation has only 8 bits of ASID, then the upper 8 bits of this field are RES0 .
| BADDR[42:0] |    47:5 |   43 | This field is bits[42:0] of BADDR[50:0]. See BADDR[50:43] for the field description.
| SKL         |     2:1 |    2 | Skip Level associated with translation table walks using TTBR0_EL1. This determines the number of levels to be skipped from the regular start level of the stage 1 EL1&0 translation table walks using TTBR0_EL1 .
| CnP         |     0:0 |    1 | Common not Private. This bit indicates whether each entry that is pointed to by TTBR0_EL1 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of TTBR0_EL1.CnP is 1.

## TTBR0_EL2 bitfields

| Bitfield          | msb:lsb | Size | Description
| ----------------- | ------: | ---: | -----------
| BADDR[55:5]       |   87:80 |    8 | Translation table base address: Bits A[55:x] of the stage 1 translation table base address bits are in register bits[87:80, 47:x]. Bits A[(x-1):0] of the stage 1 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| ASID              |   63:48 |   16 | When the Effective value of HCR_EL2 .E2H is 1, it holds an ASID for the translation table base address. The TCR_EL2 .A1 field selects either TTBR0_EL2.ASID or TTBR1_EL2 .ASID. If the implementation has only 8 bits of ASID, then the upper 8 bits of this field are RES0 .
| BADDR[55:5][42:0] |    47:5 |   43 | This field is bits[42:0] of BADDR[55:5][50:0]. See BADDR[55:5][50:43] for the field description.
| SKL               |     2:1 |    2 | Skip Level associated with translation table walks using TTBR0_EL2. This determines the number of levels to be skipped from the regular start level of the stage 1 EL2&0 translation table walks using TTBR0_EL2 .
| CnP               |     0:0 |    1 | Common not Private. This bit indicates whether each entry that is pointed to by TTBR0_EL2 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of TTBR0_EL2.CnP is 1.

## TTBR0_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BADDR    |    55:5 |   51 | Bits A[55:x] of the stage 1 translation table base address bits are in register bits[55:x]. Bits A[(x-1):0] of the stage 1 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| SKL      |     2:1 |    2 | Skip Level associated with translation table walks using TTBR0_EL3. This determines the number of levels to be skipped from the regular start level of the stage 1 EL3 translation table walks using TTBR0_EL3 .
| CnP      |     0:0 |    1 | Common not Private, for stage 2 of the Secure EL1&0 translation regime. In an implementation that includes FEAT_TTCNP , indicates whether each entry that is pointed to by VSTTBR_EL2 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of VSTTBR_EL2.CnP is 1.

## TTBR1_EL1 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BADDR       |   87:80 |    8 | Translation table base address: Bits A[55:x] of the stage 1 translation table base address bits are in register bits[87:80, 47:x]. Bits A[(x-1):0] of the stage 1 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| ASID        |   63:48 |   16 | An ASID for the translation table base address. The TCR_EL1 .A1 field selects either TTBR0_EL1 .ASID or TTBR1_EL1.ASID. If the implementation has only 8 bits of ASID, then the upper 8 bits of this field are RES0 .
| BADDR[42:0] |    47:5 |   43 | This field is bits[42:0] of BADDR[50:0]. See BADDR[50:43] for the field description.
| SKL         |     2:1 |    2 | Skip Level associated with translation table walks using TTBR1_EL1. This determines the number of levels to be skipped from the regular start level of the stage 1 EL1&0 translation table walks using TTBR1_EL1 .
| CnP         |     0:0 |    1 | Common not Private. This bit indicates whether each entry that is pointed to by TBR1_EL1 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of TTBR1_EL1.CnP is 1.

## TTBR1_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BADDR       |   87:80 |    8 | Translation table base address: Bits A[55:x] of the stage 1 translation table base address bits are in register bits[87:80, 47:x]. Bits A[(x-1):0] of the stage 1 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| ASID        |   63:48 |   16 | An ASID for the translation table base address. The TCR_EL2 .A1 field selects either TTBR0_EL2.ASID or TTBR1_EL2.ASID. If the implementation has only 8 bits of ASID, then the upper 8 bits of this field are RES0 .
| BADDR[42:0] |    47:5 |   43 | This field is bits[42:0] of BADDR[50:0]. See BADDR[50:43] for the field description.
| SKL         |     2:1 |    2 | Skip Level associated with translation table walks using TTBR1_EL2. This determines the number of levels to be skipped from the regular start level of the stage 1 EL2&0 translation table walks using TTBR1_EL2 .
| CnP         |     0:0 |    1 | Common not Private. This bit indicates whether each entry that is pointed to by TBR1_EL2 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of TTBR1_EL2.CnP is 1.

## UAO bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| UAO      |   23:23 |    1 | User Access Override.

## VBAR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VBA      |   63:11 |   53 | Vector Base Address. Base address of the exception vectors for exceptions taken to EL1. If the implementation supports FEAT_LVA3 , then: If tagged addresses are not being used, bits [63:56] of VBAR_EL1 must be the same or else the use of the vector address will result in a recursive exception. Otherwise: If the implementation supports FEAT_LVA , then: If tagged addresses are being used, bits [55:52] of VBAR_EL1 must be the same or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:52] of VBAR_EL1 must be the same or else the use of the vector address will result in a recursive exception. If the implementation does not support FEAT_LVA , then: If tagged addresses are being used, bits [55:48] of VBAR_EL1 must be the same or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:48] of VBAR_EL1 must be the same or else the use of the vector address will result in a recursive exception.

## VBAR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VBA      |   63:11 |   53 | Vector Base Address. Base address of the exception vectors for exceptions taken to EL2. If FEAT_LVA3 is implemented: If the Effective value of HCR_EL2 .E2H is 1: If tagged addresses are not being used, bits [63:56] of VBAR_EL2 must be the same or else the use of the vector address will result in a recursive exception. If the Effective value of HCR_EL2 .E2H is not 1: If tagged addresses are not being used, bits [63:56] of VBAR_EL2 must be 0 or else the use of the vector address will result in a recursive exception. Otherwise : If FEAT_LVA is implemented: If the Effective value of HCR_EL2 .E2H is 1: If tagged addresses are being used, bits [55:52] of VBAR_EL2 must be the same or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:52] of VBAR_EL2 must be the same or else the use of the vector address will result in a recursive exception. If the Effective value of HCR_EL2 .E2H is not 1: If tagged addresses are being used, bits [55:52] of VBAR_EL2 must be 0 or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:52] of VBAR_EL2 must be 0 or else the use of the vector address will result in a recursive exception. If FEAT_LVA is not implemented: If the Effective value of HCR_EL2 .E2H is 1: If tagged addresses are being used, bits [55:48] of VBAR_EL2 must be the same or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:48] of VBAR_EL2 must be the same or else the use of the vector address will result in a recursive exception. If the Effective value of HCR_EL2 .E2H is not 1: If tagged addresses are being used, bits [55:48] of VBAR_EL2 must be 0 or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:48] of VBAR_EL2 must be 0 or else the use of the vector address will result in a recursive exception.

## VBAR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| VBA      |   63:11 |   53 | Vector Base Address. Base address of the exception vectors for exceptions taken to EL3. If the implementation supports FEAT_LVA3 , then: If tagged addresses are not being used, bits [63:56] of VBAR_EL3 must be 0 or else the use of the vector address will result in a recursive exception. Otherwise: If the implementation supports FEAT_LVA , then: If tagged addresses are being used, bits [55:52] of VBAR_EL3 must be 0 or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:52] of VBAR_EL3 must be 0 or else the use of the vector address will result in a recursive exception. If the implementation does not support FEAT_LVA , then: If tagged addresses are being used, bits [55:48] of VBAR_EL3 must be 0 or else the use of the vector address will result in a recursive exception. If tagged addresses are not being used, bits [63:48] of VBAR_EL3 must be 0 or else the use of the vector address will result in a recursive exception.

## VDISR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| A        |   31:31 |    1 | Set to 1 when an ESB instruction defers a virtual SError exception.
| IDS      |   24:24 |    1 | The value copied from VSESR_EL2 .IDS.
| ISS      |    23:0 |   24 | The value copied from VSESR_EL2 .ISS.

## VDISR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| A        |   31:31 |    1 | Set to 1 when an ESB instruction defers a delegated SError exception.
| IDS      |   24:24 |    1 | The value copied from VSESR_EL3 .IDS.
| ISS      |    23:0 |   24 | The value copied from VSESR_EL3 .ISS.

## VMECID_A_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## VMECID_P_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| MECID    |    15:0 |   16 | If MECIDWidth is less than 16 bits, bits[15:MECIDWidth] are RES0 . MECIDWidth is defined in MECIDR_EL2 .MECIDWidthm1.

## VMPIDR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| Aff3     |   39:32 |    8 | Affinity level 3. See the description of VMPIDR_EL2.Aff0 for more information. Aff3 is not supported in AArch32 state.
| U        |   30:30 |    1 | Indicates a Uniprocessor system, as distinct from PE 0 in a multiprocessor system.
| MT       |   24:24 |    1 | Indicates whether the lowest level of affinity consists of logical PEs that are implemented using a multithreading type approach. See the description of VMPIDR_EL2.Aff0 for more information about affinity levels.
| Aff2     |   23:16 |    8 | Affinity level 2. See the description of VMPIDR_EL2.Aff0 for more information.
| Aff1     |    15:8 |    8 | Affinity level 1. See the description of VMPIDR_EL2.Aff0 for more information.
| Aff0     |     7:0 |    8 | Affinity level 0. This is the affinity level that is most significant for determining PE behavior. Higher affinity levels are increasingly less significant in determining PE behavior. The assigned value of the MPIDR .{Aff2, Aff1, Aff0} or MPIDR_EL1 .{Aff3, Aff2, Aff1, Aff0} set of fields of each PE must be unique within the system as a whole.

## VNCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| RESS     |   63:57 |    7 | Reserved, Sign extended. If the bits marked as RESS do not all have the same value, then there is a CONSTRAINED UNPREDICTABLE choice between: Generating an EL2 translation regime Translation abort on use of the VNCR_EL2 register. If FEAT_D128 is implemented: If the virtual address space for EL2 supports 56 bits, bits[63:57] of VNCR_EL2 are treated as the same value as bit[56] for all purposes other than reading back the register. If the virtual address space for EL2 supports 56 bits, bits[63:57] of VNCR_EL2 are treated as the same value as bit[56]. If the virtual address space for EL2 supports 52 bits, bits[63:53] of VNCR_EL2 are treated as the same value as bit[52] for all purposes other than reading back the register. If the virtual address space for EL2 supports 52 bits, bits[63:53] of VNCR_EL2 are treated as the same value as bit[52]. Bits[63:49] of VNCR_EL2 are treated as the same value as bit[48] for all purposes other than reading back the register. Bits[63:49] of VNCR_EL2 are treated as the same value as bit[48] for all purposes. Where the EL2 translation regime has upper and lower address ranges, bit[56] is used to select between those address ranges to determine the number of bits supported by the address space.
| BADDR    |   56:12 |   45 | Base Address. If the virtual address space for EL2 does not support more than 48 bits, then bits [56:49] are RESS. If the virtual address space for EL2 does not support more than 52 bits, then bits [56:53] are RESS

## VPIDR_EL2 bitfields

| Bitfield     | msb:lsb | Size | Description
| ------------ | ------: | ---: | -----------
| Implementer  |   31:24 |    8 | The Implementer code. This field must hold an implementer code that has been assigned by Arm.
| Variant      |   23:20 |    4 | An IMPLEMENTATION DEFINED variant number. Typically, this field is used to distinguish between different product variants, or major revisions of a product.
| Architecture |   19:16 |    4 | Architecture version.
| PartNum      |    15:4 |   12 | An IMPLEMENTATION DEFINED primary part number for the device. On processors implemented by Arm, if the top four bits of the primary part number are 0x0 or 0x7 , the variant and architecture are encoded differently.
| Revision     |     3:0 |    4 | An IMPLEMENTATION DEFINED revision number for the device.

## VSESR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| AET      |   15:14 |    2 | When a virtual SError exception is taken to EL1 using AArch32, DFSR [15:14] is set to VSESR_EL2.AET. When a virtual SError exception is deferred by an ESB instruction, VDISR_EL2 [15:14] is set to VSESR_EL2.AET.
| ExT      |   12:12 |    1 | When a virtual SError exception is taken to EL1 using AArch32, DFSR [12] is set to VSESR_EL2.ExT. When a virtual SError exception is deferred by an ESB instruction, VDISR_EL2 [12] is set to VSESR_EL2.ExT.

## VSESR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| IDS      |   24:24 |    1 | When a delegated SError exception triggered by SCR_EL3 .DSE is taken to EL2 or EL1 using AArch64, ESR_ELx [24] is set to VSESR_EL3.IDS. When a delegated SError exception triggered by SCR_EL3 .DSE is deferred by an ESB instruction, VDISR_EL3 [24] is set to VSESR_EL3.IDS.
| ISS      |    23:0 |   24 | When a delegated SError exception triggered by SCR_EL3 .DSE is taken to EL2 or EL1 using AArch64, ESR_ELx [23:0] is set to VSESR_EL3.ISS. When a delegated SError exception triggered by SCR_EL3 .DSE is deferred by an ESB instruction, VDISR_EL3 [23:0] is set to VSESR_EL3.ISS.

## VSTCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| SL2      |   33:33 |    1 | Starting level of the Secure stage 2 translation lookup controlled by VSTCR_EL2. If VTCR_EL2 .DS == 1, then VSTCR_EL2.SL2, in combination with VSTCR_EL2.SL0, gives encodings for the Secure stage 2 translation table walk initial lookup level. If VTCR_EL2 .DS == 0, then VSTCR_EL2.SL2 is RES0 . If the translation granule size is not 4KB, then this field is RES0 .
| SA       |   30:30 |    1 | Secure stage 2 translation output address space.
| SW       |   29:29 |    1 | Secure stage 2 translation address space.
| TG0      |   15:14 |    2 | Secure stage 2 granule size for VSTTBR_EL2 .
| SL0      |     7:6 |    2 | Starting level of the Secure stage 2 translation lookup, controlled by VSTCR_EL2. The meaning of this field depends on the value of VSTCR_EL2.TG0.
| T0SZ     |     5:0 |    6 | The size offset of the memory region addressed by VSTTBR_EL2 . The region size is 2 (64-T0SZ) bytes. The maximum and minimum possible values for this field depend on the level of translation table and the memory translation granule size, as described in the AArch64 Virtual Memory System Architecture chapter. If this field is programmed to a value that is not consistent with the programming of SL0, then a stage 2 level 0 Translation fault is generated. For the 4KB translation granule, if FEAT_LPA2 is implemented and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented and this field is less than 17, the translation table walk begins with a level 0 initial lookup.

## VSTTBR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| BADDR    |    55:5 |   51 | Bits A[55:x] of the stage 2 translation table base address bits are in register bits[55:x]. Bits A[(x-1):0] of the stage 2 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| SKL      |     2:1 |    2 | Skip Level. Skip Level determines the number of levels to be skipped from the regular start level of the Secure stage 2 translation table walk.
| CnP      |     0:0 |    1 | Common not Private, for stage 2 of the Secure EL1&0 translation regime. In an implementation that includes FEAT_TTCNP , indicates whether each entry that is pointed to by VSTTBR_EL2 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of VSTTBR_EL2.CnP is 1.

## VTCR_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| HDBSS       |   45:45 |    1 | Enable use of HDBSS.
| HAFT        |   44:44 |    1 | Hardware managed Access Flag for Table descriptors. Enables the Hardware managed Access Flag for Table descriptors.
| TL0         |   41:41 |    1 | Control bit to check for presence of MMU TopLevel0 permission attribute.
| GCSH        |   40:40 |    1 | Assured stage 1 translations for Guarded Control Stacks. Enforces use of the AssuredOnly attribute in stage 2 for the memory accessed by privileged Guarded Control Stack data accesses.
| D128        |   38:38 |    1 | Enables VMSAv9-128 translation system for stage 2 translation.
| S2POE       |   37:37 |    1 | Enable Permission Overlay. Enables permission overlay in stage 2 Permission model.
| S2PIE       |   36:36 |    1 | Select Permission Model. Enables usage of permission indirection in stage 2 Permission model.
| TL1         |   35:35 |    1 | Control bit to check for presence of MMU TopLevel1 permission attribute.
| AssuredOnly |   34:34 |    1 | AssuredOnly attribute enable for VMSAv8-64. Configures use of bit[58] of the stage 2 translation table Block or Page descriptor.
| SL2         |   33:33 |    1 | Starting level of the stage 2 translation lookup controlled by VTCR_EL2. If VTCR_EL2.DS == 1, then VTCR_EL2.SL2, in combination with VTCR_EL2.SL0, gives encodings for the stage 2 translation table walk initial lookup level. If VTCR_EL2.DS == 0, then VTCR_EL2.SL2 is RES0 . If the translation granule size is not 4KB, then this field is RES0 .
| DS          |   32:32 |    1 | This field affects: Whether a 52-bit output address can be described by the translation tables of the 4KB or 16KB translation granules. The minimum value of VTCR_EL2.T0SZ and VSTCR_EL2.T0SZ. How and where shareability for Block and Page descriptors are encoded.
| NSA         |   30:30 |    1 | Non-secure stage 2 translation output address space for the Secure EL1&0 translation regime.
| NSW         |   29:29 |    1 | Non-secure stage 2 translation table address space for the Secure EL1&0 translation regime.
| HWU62       |   28:28 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[62] of the stage 2 translation table Block or Page entry.
| HWU61       |   27:27 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[61] of the stage 2 translation table Block or Page entry.
| HWU60       |   26:26 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[60] of the stage 2 translation table Block or Page entry.
| HWU59       |   25:25 |    1 | Hardware Use. Indicates IMPLEMENTATION DEFINED hardware use of bit[59] of the stage 2 translation table Block or Page entry.
| HD          |   22:22 |    1 | Hardware management of dirty state in stage 2 translations when EL2 is enabled in the current Security state.
| HA          |   21:21 |    1 | Hardware Access flag update in stage 2 translations when EL2 is enabled in the current Security state.
| VS          |   19:19 |    1 | VMID Size.
| PS          |   18:16 |    3 | Physical address Size for the second stage of translation.
| TG0         |   15:14 |    2 | Granule size for the VTTBR_EL2 .
| SH0         |   13:12 |    2 | Shareability attribute for memory associated with translation table walks using VTTBR_EL2 or VSTTBR_EL2 .
| ORGN0       |   11:10 |    2 | Outer cacheability attribute for memory associated with translation table walks using VTTBR_EL2 or VSTTBR_EL2 .
| IRGN0       |     9:8 |    2 | Inner cacheability attribute for memory associated with translation table walks using VTTBR_EL2 or VSTTBR_EL2 .
| SL0         |     7:6 |    2 | Starting level of the stage 2 translation lookup, controlled by VTCR_EL2. The meaning of this field depends on the value of VTCR_EL2.TG0.
| T0SZ        |     5:0 |    6 | The size offset of the memory region addressed by VTTBR_EL2 . The region size is 2 (64-T0SZ) bytes. The maximum and minimum possible values for T0SZ depend on the level of translation table and the memory translation granule size, as described in 'The AArch64 Virtual Memory System Architecture' . If this field is programmed to a value that is not consistent with the programming of SL0, then a stage 2 level 0 Translation fault is generated. For the 4KB translation granule, if FEAT_LPA2 is implemented, VTCR_EL2.DS is 1, and this field is less than 16, the translation table walk begins with a level -1 initial lookup. For the 16KB translation granule, if FEAT_LPA2 is implemented, VTCR_EL2.DS is 1, and this field is less than 17, the translation table walk begins with a level 0 initial lookup.

## VTTBR_EL2 bitfields

| Bitfield    | msb:lsb | Size | Description
| ----------- | ------: | ---: | -----------
| BADDR       |   87:80 |    8 | Translation table base address: Bits A[55:x] of the stage 2 translation table base address bits are in register bits[87:80, 47:x]. Bits A[(x-1):0] of the stage 2 translation table base address are zero. Address bit x is the minimum address bit required to align the translation table to the size of the table. x is calculated based on LOG2(StartTableSize), as described in VMSAv9-128. The smallest permitted value of x is 5.
| VMID        |   63:48 |   16 |
| BADDR[42:0] |    47:5 |   43 | This field is bits[42:0] of BADDR[50:0]. See BADDR[50:43] for the field description.
| SKL         |     2:1 |    2 | Skip Level. Skip Level determines the number of levels to be skipped from the regular start level of the Non-Secure stage 2 translation table walk.
| VMID        |    15:0 |   16 | The VMID for the translation table. If the implementation has an 8-bit VMID, bits [15:8] of this field are RES0 .
| CnP         |     0:0 |    1 | Common not Private. This bit indicates whether each entry that is pointed to by VTTBR_EL2 is a member of a common set that can be used by every PE in the Inner Shareable domain for which the value of VTTBR_EL2.CnP is 1.

## ZCR_EL1 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LEN      |     3:0 |    4 | Requests an Effective Non-streaming SVE vector length at EL1 of (LEN+1)*128 bits. This field also defines the Effective Non-streaming SVE vector length at EL0 when EL2 is not implemented, or EL2 is not enabled in the current Security state, or the Effective value of HCR_EL2 .{E2H, TGE} is not {1, 1}. The Non-streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support a subset of the architecturally permitted lengths. An implementation is required to support all lengths that are powers of two, from 128 bits up to its maximum implemented Non-streaming SVE vector length. When FEAT_SME is not implemented, or the PE is not in Streaming SVE mode, the Effective SVE vector length (VL) is equal to the Effective Non-streaming SVE vector length. When FEAT_SME is implemented and the PE is in Streaming SVE mode, VL is equal to the Effective Streaming SVE vector length. See SMCR_EL1 . For all purposes other than returning the result of a direct read of ZCR_EL1, the PE selects the Effective Non-streaming SVE vector length by performing checks in the following order: If EL2 is implemented and enabled in the current Security state, and the requested length is greater than the Effective length at EL2, then the Effective length at EL2 is used. If EL3 is implemented and the requested length is greater than the Effective length at EL3, then the Effective length at EL3 is used. Otherwise, the Effective length is the highest supported Non-streaming SVE vector length that is less than or equal to the requested length. An indirect read of ZCR_EL1.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.

## ZCR_EL2 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LEN      |     3:0 |    4 | Requests an Effective Non-streaming SVE vector length at EL2 of (LEN+1)*128 bits. This field also defines the Effective Non-streaming SVE vector length at EL0 when the Effective value of HCR_EL2 .{E2H, TGE} is {1, 1}. The Non-streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support a subset of the architecturally permitted lengths. An implementation is required to support all lengths that are powers of two, from 128 bits up to its maximum implemented Non-streaming SVE vector length. When FEAT_SME is not implemented, or the PE is not in Streaming SVE mode, the Effective SVE vector length (VL) is equal to the Effective Non-streaming SVE vector length. When FEAT_SME is implemented and the PE is in Streaming SVE mode, VL is equal to the Effective Streaming SVE vector length. See SMCR_EL2 . For all purposes other than returning the result of a direct read of ZCR_EL2, the PE selects the Effective Non-streaming SVE vector length by performing checks in the following order: If EL3 is implemented and the requested length is greater than the Effective length at EL3, then the Effective length at EL3 is used. Otherwise, the Effective length is the highest supported Non-streaming SVE vector length that is less than or equal to the requested length. An indirect read of ZCR_EL2.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.

## ZCR_EL3 bitfields

| Bitfield | msb:lsb | Size | Description
| -------- | ------: | ---: | -----------
| LEN      |     3:0 |    4 | Requests an Effective Non-streaming SVE vector length at EL3 of (LEN+1)*128 bits. The Non-streaming SVE vector length can be any power of two from 128 bits to 2048 bits inclusive. An implementation can support a subset of the architecturally permitted lengths. An implementation is required to support all lengths that are powers of two, from 128 bits up to its maximum implemented Non-streaming SVE vector length. When FEAT_SME is not implemented, or the PE is not in Streaming SVE mode, the Effective SVE vector length (VL) is equal to the Effective Non-streaming SVE vector length. When FEAT_SME is implemented and the PE is in Streaming SVE mode, VL is equal to the Effective Streaming SVE vector length. See SMCR_EL3 . For all purposes other than returning the result of a direct read of ZCR_EL3, the PE selects the highest supported Non-streaming SVE vector length that is less than or equal to the requested length. An indirect read of ZCR_EL3.LEN appears to occur in program order relative to a direct write of the same register, without the need for explicit synchronization.
<!-- @AUTOGEN-END -->
