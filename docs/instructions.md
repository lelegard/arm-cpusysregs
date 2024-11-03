# Arm Instruction Set

The following table lists all known Arm instructions.

The Python script `aarch/extract-arm-spec.py` automatically updates this table,
based on reference JSON and XML files on the Arm public web site. This script should
be executed each time an update of the Arm architecture is published.

<!-- Do not remove the markers AUTOGEN-BEGIN and AUTOGEN-END. -->
<!-- @AUTOGEN-BEGIN -->
Version: 2024-09

## Number of instructions per class

| Class | Instructions
| ----- | ------------
| Base  | 826
| SIMD  | 580
| SVE   | 971
| SME   | 354
| Total | 2731

## All instructions

| Opcode | Class | Description
| ------ | ----- | -----------
| ABS | Base | Absolute value.
| ABS | SIMD | Absolute value (vector).
| ABS | SVE | Absolute value (predicated).
| ADC | Base | Add with carry.
| ADCLB | SVE | Add with carry long (bottom).
| ADCLT | SVE | Add with carry long (top).
| ADCS | Base | Add with carry, setting flags.
| ADD (array accumulators) | SME | Add multi-vector to ZA array vector accumulators.
| ADD (array results, multiple and single vector) | SME | Add replicated single vector to multi-vector with ZA array vector results.
| ADD (array results, multiple vectors) | SME | Add multi-vector to multi-vector with ZA array vector results.
| ADD (extended register) | Base | Add extended and scaled register.
| ADD (immediate) | Base | Add immediate value.
| ADD (immediate) | SVE | Add immediate (unpredicated).
| ADD (shifted register) | Base | Add optionally-shifted register.
| ADD (to vector) | SME | Add replicated single vector to multi-vector with multi-vector result.
| ADD (vector) | SIMD | Add (vector).
| ADD (vectors, predicated) | SVE | Add vectors (predicated).
| ADD (vectors, unpredicated) | SVE | Add vectors (unpredicated).
| ADDG | Base | Add with tag.
| ADDHA | SME | Add horizontally vector elements to ZA tile.
| ADDHN | SIMD | Add returning high narrow.
| ADDHN2 | SIMD | Add returning high narrow.
| ADDHNB | SVE | Add narrow high part (bottom).
| ADDHNT | SVE | Add narrow high part (top).
| ADDP | SVE | Add pairwise.
| ADDP (scalar) | SIMD | Add pair of elements (scalar).
| ADDP (vector) | SIMD | Add pairwise (vector).
| ADDPL | SVE | Add multiple of predicate register size to scalar register.
| ADDPT | Base | Add checked pointer.
| ADDPT (predicated) | SVE | Add checked pointer vectors (predicated).
| ADDPT (unpredicated) | SVE | Add checked pointer vectors (unpredicated).
| ADDQV | SVE | Unsigned add reduction of quadword vector segments.
| ADDS (extended register) | Base | Add extended and scaled register, setting flags.
| ADDS (immediate) | Base | Add immediate value, setting flags.
| ADDS (shifted register) | Base | Add optionally-shifted register, setting flags.
| ADDSPL | SME | Add multiple of Streaming SVE predicate register size to scalar register.
| ADDSVL | SME | Add multiple of Streaming SVE vector register size to scalar register.
| ADDV | SIMD | Add across vector.
| ADDVA | SME | Add vertically vector elements to ZA tile.
| ADDVL | SVE | Add multiple of vector register size to scalar register.
| ADR | Base | Form PC-relative address.
| ADR | SVE | Compute vector address.
| ADRP | Base | Form PC-relative address to 4KB page.
| AESD | SIMD | AES single round decryption.
| AESD (indexed) | SVE | Multi-vector AES single round decryption.
| AESD (vectors) | SVE | AES single round decryption.
| AESDIMC | SVE | Multi-vector AES single round decryption and inverse mix columns.
| AESE | SIMD | AES single round encryption.
| AESE (indexed) | SVE | Multi-vector AES single round encryption.
| AESE (vectors) | SVE | AES single round encryption.
| AESEMC | SVE | Multi-vector AES single round encryption and mix columns.
| AESIMC | SIMD | AES inverse mix columns.
| AESIMC | SVE | AES inverse mix columns.
| AESMC | SIMD | AES mix columns.
| AESMC | SVE | AES mix columns.
| AND (immediate) | Base | Bitwise AND (immediate).
| AND (immediate) | SVE | Bitwise AND with immediate (unpredicated).
| AND (predicates) | SVE | Bitwise AND predicates.
| AND (shifted register) | Base | Bitwise AND (shifted register).
| AND (vector) | SIMD | Bitwise AND (vector).
| AND (vectors, predicated) | SVE | Bitwise AND vectors (predicated).
| AND (vectors, unpredicated) | SVE | Bitwise AND vectors (unpredicated).
| ANDQV | SVE | Bitwise AND reduction of quadword vector segments.
| ANDS | SVE | Bitwise AND predicates, setting the condition flags.
| ANDS (immediate) | Base | Bitwise AND (immediate), setting flags.
| ANDS (shifted register) | Base | Bitwise AND (shifted register), setting flags.
| ANDV | SVE | Bitwise AND reduction to scalar.
| APAS | Base | Associate physical address space: an alias of SYS.
| ASR (immediate) | Base | Arithmetic shift right (immediate): an alias of SBFM.
| ASR (immediate, predicated) | SVE | Arithmetic shift right by immediate (predicated).
| ASR (immediate, unpredicated) | SVE | Arithmetic shift right by immediate (unpredicated).
| ASR (register) | Base | Arithmetic shift right (register): an alias of ASRV.
| ASR (vectors) | SVE | Arithmetic shift right by vector (predicated).
| ASR (wide elements, predicated) | SVE | Arithmetic shift right by 64-bit wide elements (predicated).
| ASR (wide elements, unpredicated) | SVE | Arithmetic shift right by 64-bit wide elements (unpredicated).
| ASRD | SVE | Arithmetic shift right for divide by immediate (predicated).
| ASRR | SVE | Reversed arithmetic shift right by vector (predicated).
| ASRV | Base | Arithmetic shift right variable.
| AT | Base | Address translate: an alias of SYS.
| AUTDA | Base | Authenticate data address, using key A.
| AUTDB | Base | Authenticate data address, using key B.
| AUTDZA | Base | Authenticate data address, using key A.
| AUTDZB | Base | Authenticate data address, using key B.
| AUTIA | Base | Authenticate instruction address, using key A.
| AUTIA1716 | Base | Authenticate instruction address, using key A.
| AUTIA171615 | Base | Authenticate instruction address, using key A.
| AUTIASP | Base | Authenticate instruction address, using key A.
| AUTIASPPC | Base | Authenticate return address using key A, using an immediate offset.
| AUTIASPPCR | Base | Authenticate return address using key A, using a register.
| AUTIAZ | Base | Authenticate instruction address, using key A.
| AUTIB | Base | Authenticate instruction address, using key B.
| AUTIB1716 | Base | Authenticate instruction address, using key B.
| AUTIB171615 | Base | Authenticate instruction address, using key B.
| AUTIBSP | Base | Authenticate instruction address, using key B.
| AUTIBSPPC | Base | Authenticate return address using key B, using an immediate offset.
| AUTIBSPPCR | Base | Authenticate return address using key B, using a register.
| AUTIBZ | Base | Authenticate instruction address, using key B.
| AUTIZA | Base | Authenticate instruction address, using key A.
| AUTIZB | Base | Authenticate instruction address, using key B.
| AXFLAG | Base | Convert floating-point condition flags from Arm to external format.
| B | Base | Branch.
| B.cond | Base | Branch conditionally.
| BC.cond | Base | Branch consistent conditionally.
| BCAX | SIMD | Bit clear and exclusive-OR.
| BCAX | SVE | Bitwise clear and exclusive OR.
| BDEP | SVE | Scatter lower bits into positions selected by bitmask.
| BEXT | SVE | Gather lower bits from positions selected by bitmask.
| BF1CVT | SVE | 8-bit floating-point convert to BFloat16.
| BF1CVT | SME | Multi-vector floating-point convert from 8-bit floating-point to BFloat16 (in-order).
| BF1CVTL | SIMD | 8-bit floating-point convert to BFloat16 (vector).
| BF1CVTL | SME | Multi-vector floating-point convert from 8-bit floating-point to deinterleaved BFloat16.
| BF1CVTL2 | SIMD | 8-bit floating-point convert to BFloat16 (vector).
| BF1CVTLT | SVE | 8-bit floating-point convert to BFloat16 (top).
| BF2CVT | SVE | 8-bit floating-point convert to BFloat16.
| BF2CVT | SME | Multi-vector floating-point convert from 8-bit floating-point to BFloat16 (in-order).
| BF2CVTL | SIMD | 8-bit floating-point convert to BFloat16 (vector).
| BF2CVTL | SME | Multi-vector floating-point convert from 8-bit floating-point to deinterleaved BFloat16.
| BF2CVTL2 | SIMD | 8-bit floating-point convert to BFloat16 (vector).
| BF2CVTLT | SVE | 8-bit floating-point convert to BFloat16 (top).
| BFADD | SME | BFloat16 floating-point add multi-vector to ZA array vector accumulators.
| BFADD (predicated) | SVE | BFloat16 floating-point add vectors (predicated).
| BFADD (unpredicated) | SVE | BFloat16 floating-point add vectors (unpredicated).
| BFC | Base | Bitfield clear: an alias of BFM.
| BFCLAMP | SVE | BFloat16 floating-point clamp to minimum/maximum number.
| BFCLAMP | SME | Multi-vector BFloat16 floating-point clamp to minimum/maximum number.
| BFCVT | SIMD | Floating-point convert from single-precision to BFloat16 format (scalar).
| BFCVT | SVE | Floating-point down convert to BFloat16 format (predicated).
| BFCVT | SME | Multi-vector floating-point convert from single-precision to packed BFloat16 format.
| BFCVT | SME | Multi-vector floating-point convert from BFloat16 to packed 8-bit floating-point format.
| BFCVTN | SIMD | Floating-point convert from single-precision to BFloat16 format (vector).
| BFCVTN | SVE | BFloat16 convert, narrow and interleave to 8-bit floating-point.
| BFCVTN | SME | Multi-vector floating-point convert from single-precision to interleaved BFloat16 format.
| BFCVTN2 | SIMD | Floating-point convert from single-precision to BFloat16 format (vector).
| BFCVTNT | SVE | Floating-point down convert and narrow to BFloat16 (top, predicated).
| BFDOT (by element) | SIMD | BFloat16 floating-point dot product (vector, by element).
| BFDOT (indexed) | SVE | BFloat16 floating-point indexed dot product.
| BFDOT (multiple and indexed vector) | SME | Multi-vector BFloat16 floating-point dot-product by indexed element.
| BFDOT (multiple and single vector) | SME | Multi-vector BFloat16 floating-point dot-product by vector.
| BFDOT (multiple vectors) | SME | Multi-vector BFloat16 floating-point dot-product.
| BFDOT (vector) | SIMD | BFloat16 floating-point dot product (vector).
| BFDOT (vectors) | SVE | BFloat16 floating-point dot product.
| BFI | Base | Bitfield insert: an alias of BFM.
| BFM | Base | Bitfield move.
| BFMAX | SVE | BFloat16 floating-point maximum (predicated).
| BFMAX (multiple and single vector) | SME | Multi-vector BFloat16 floating-point maximum by vector.
| BFMAX (multiple vectors) | SME | Multi-vector BFloat16 floating-point maximum.
| BFMAXNM | SVE | BFloat16 floating-point maximum number (predicated).
| BFMAXNM (multiple and single vector) | SME | Multi-vector BFloat16 floating-point maximum number by vector.
| BFMAXNM (multiple vectors) | SME | Multi-vector BFloat16 floating-point maximum number.
| BFMIN | SVE | BFloat16 floating-point minimum (predicated).
| BFMIN (multiple and single vector) | SME | Multi-vector BFloat16 floating-point minimum by vector.
| BFMIN (multiple vectors) | SME | Multi-vector BFloat16 floating-point minimum.
| BFMINNM | SVE | BFloat16 floating-point minimum number (predicated).
| BFMINNM (multiple and single vector) | SME | Multi-vector BFloat16 floating-point minimum number by vector.
| BFMINNM (multiple vectors) | SME | Multi-vector BFloat16 floating-point minimum number.
| BFMLA (indexed) | SVE | BFloat16 floating-point fused multiply-add vectors by indexed elements.
| BFMLA (multiple and indexed vector) | SME | Multi-vector BFloat16 floating-point fused multiply-add by indexed element.
| BFMLA (multiple and single vector) | SME | Multi-vector BFloat16 floating-point fused multiply-add by vector.
| BFMLA (multiple vectors) | SME | Multi-vector BFloat16 floating-point fused multiply-add.
| BFMLA (vectors) | SVE | BFloat16 floating-point fused multiply-add vectors.
| BFMLAL (multiple and indexed vector) | SME | Multi-vector BFloat16 floating-point multiply-add long by indexed element.
| BFMLAL (multiple and single vector) | SME | Multi-vector BFloat16 floating-point multiply-add long by vector.
| BFMLAL (multiple vectors) | SME | Multi-vector BFloat16 floating-point multiply-add long.
| BFMLALB | SIMD | BFloat16 floating-point widening multiply-add long (by element).
| BFMLALB | SIMD | BFloat16 floating-point widening multiply-add long (vector).
| BFMLALB (indexed) | SVE | BFloat16 floating-point multiply-add long to single-precision (bottom, indexed).
| BFMLALB (vectors) | SVE | BFloat16 floating-point multiply-add long to single-precision (bottom).
| BFMLALT (by element) | SIMD | BFloat16 floating-point widening multiply-add long (by element).
| BFMLALT (indexed) | SVE | BFloat16 floating-point multiply-add long to single-precision (top, indexed).
| BFMLALT (vector) | SIMD | BFloat16 floating-point widening multiply-add long (vector).
| BFMLALT (vectors) | SVE | BFloat16 floating-point multiply-add long to single-precision (top).
| BFMLS (indexed) | SVE | BFloat16 floating-point fused multiply-subtract vectors by indexed elements.
| BFMLS (multiple and indexed vector) | SME | Multi-vector BFloat16 floating-point fused multiply-subtract by indexed element.
| BFMLS (multiple and single vector) | SME | Multi-vector BFloat16 floating-point fused multiply-subtract by vector.
| BFMLS (multiple vectors) | SME | Multi-vector BFloat16 floating-point fused multiply-subtract.
| BFMLS (vectors) | SVE | BFloat16 floating-point fused multiply-subtract vectors.
| BFMLSL (multiple and indexed vector) | SME | Multi-vector BFloat16 floating-point multiply-subtract long by indexed element.
| BFMLSL (multiple and single vector) | SME | Multi-vector BFloat16 floating-point multiply-subtract long by vector.
| BFMLSL (multiple vectors) | SME | Multi-vector BFloat16 floating-point multiply-subtract long.
| BFMLSLB (indexed) | SVE | BFloat16 floating-point multiply-subtract long from single-precision (bottom, indexed).
| BFMLSLB (vectors) | SVE | BFloat16 floating-point multiply-subtract long from single-precision (bottom).
| BFMLSLT (indexed) | SVE | BFloat16 floating-point multiply-subtract long from single-precision (top, indexed).
| BFMLSLT (vectors) | SVE | BFloat16 floating-point multiply-subtract long from single-precision (top).
| BFMMLA | SIMD | BFloat16 floating-point matrix multiply-accumulate into 2x2 matrix.
| BFMMLA | SVE | BFloat16 floating-point matrix multiply-accumulate into 2×2 matrices.
| BFMOP4A (non-widening) | SME | BFloat16 quarter-tile outer products, accumulating.
| BFMOP4A (widening) | SME | BFloat16 quarter-tile sums of two outer products, accumulating.
| BFMOP4S (non-widening) | SME | BFloat16 quarter-tile outer products, subtracting.
| BFMOP4S (widening) | SME | BFloat16 quarter-tile sums of two outer products, subtracting.
| BFMOPA (non-widening) | SME | BFloat16 floating-point outer product and accumulate.
| BFMOPA (widening) | SME | BFloat16 sum of outer products and accumulate.
| BFMOPS (non-widening) | SME | BFloat16 floating-point outer product and subtract.
| BFMOPS (widening) | SME | BFloat16 sum of outer products and subtract.
| BFMUL (indexed) | SVE | BFloat16 floating-point multiply vectors by indexed elements.
| BFMUL (multiple and single vector) | SME | Multi-vector BFloat16 floating-point multiply by vector.
| BFMUL (multiple vectors) | SME | Multi-vector BFloat16 floating-point multiply.
| BFMUL (vectors, predicated) | SVE | BFloat16 floating-point multiply vectors (predicated).
| BFMUL (vectors, unpredicated) | SVE | BFloat16 floating-point multiply vectors (unpredicated).
| BFSCALE | SVE | BFloat16 adjust exponent by vector (predicated).
| BFSCALE (multiple and single vector) | SME | Multi-vector BFloat16 adjust exponent by vector.
| BFSCALE (multiple vectors) | SME | Multi-vector BFloat16 adjust exponent.
| BFSUB | SME | BFloat16 floating-point subtract multi-vector from ZA array vector accumulators.
| BFSUB (predicated) | SVE | BFloat16 floating-point subtract vectors (predicated).
| BFSUB (unpredicated) | SVE | BFloat16 floating-point subtract vectors (unpredicated).
| BFTMOPA (non-widening) | SME | BFloat16 sparse outer product, accumulating.
| BFTMOPA (widening) | SME | BFloat16 sparse sum of two outer products, accumulating.
| BFVDOT | SME | Multi-vector BFloat16 floating-point vertical dot-product by indexed element.
| BFXIL | Base | Bitfield extract and insert at low end: an alias of BFM.
| BGRP | SVE | Group bits to right or left as selected by bitmask.
| BIC (immediate) | SVE | Bitwise clear bits using immediate (unpredicated): an alias of AND (immediate).
| BIC (predicates) | SVE | Bitwise clear predicates.
| BIC (shifted register) | Base | Bitwise bit clear (shifted register).
| BIC (vector, immediate) | SIMD | Bitwise bit clear (vector, immediate).
| BIC (vector, register) | SIMD | Bitwise bit clear (vector, register).
| BIC (vectors, predicated) | SVE | Bitwise clear vectors (predicated).
| BIC (vectors, unpredicated) | SVE | Bitwise clear vectors (unpredicated).
| BICS | SVE | Bitwise clear predicates, setting the condition flags.
| BICS (shifted register) | Base | Bitwise bit clear (shifted register), setting flags.
| BIF | SIMD | Bitwise insert if false.
| BIT | SIMD | Bitwise insert if true.
| BL | Base | Branch with link.
| BLR | Base | Branch with link to register.
| BLRAA | Base | Branch with link to register, with pointer authentication.
| BLRAAZ | Base | Branch with link to register, with pointer authentication.
| BLRAB | Base | Branch with link to register, with pointer authentication.
| BLRABZ | Base | Branch with link to register, with pointer authentication.
| BMOPA | SME | Bitwise exclusive NOR population count outer product and accumulate.
| BMOPS | SME | Bitwise exclusive NOR population count outer product and subtract.
| BR | Base | Branch to register.
| BRAA | Base | Branch to register, with pointer authentication.
| BRAAZ | Base | Branch to register, with pointer authentication.
| BRAB | Base | Branch to register, with pointer authentication.
| BRABZ | Base | Branch to register, with pointer authentication.
| BRB | Base | Branch record buffer: an alias of SYS.
| BRK | Base | Breakpoint instruction.
| BRKA | SVE | Break after first true condition.
| BRKAS | SVE | Break after first true condition, setting the condition flags.
| BRKB | SVE | Break before first true condition.
| BRKBS | SVE | Break before first true condition, setting the condition flags.
| BRKN | SVE | Propagate break to next partition.
| BRKNS | SVE | Propagate break to next partition, setting the condition flags.
| BRKPA | SVE | Break after first true condition, propagating from previous partition.
| BRKPAS | SVE | Break after first true condition, propagating from previous partition and setting the condition flags.
| BRKPB | SVE | Break before first true condition, propagating from previous partition.
| BRKPBS | SVE | Break before first true condition, propagating from previous partition and setting the condition flags.
| BSL | SIMD | Bitwise select.
| BSL | SVE | Bitwise select.
| BSL1N | SVE | Bitwise select with first input inverted.
| BSL2N | SVE | Bitwise select with second input inverted.
| BTI | Base | Branch target identification.
| CADD | SVE | Complex integer add with rotate.
| CAS | Base | Compare and swap word or doubleword in memory.
| CASA | Base | Compare and swap word or doubleword in memory.
| CASAB | Base | Compare and swap byte in memory.
| CASAH | Base | Compare and swap halfword in memory.
| CASAL | Base | Compare and swap word or doubleword in memory.
| CASALB | Base | Compare and swap byte in memory.
| CASALH | Base | Compare and swap halfword in memory.
| CASALT | Base | Compare and swap unprivileged.
| CASAT | Base | Compare and swap unprivileged.
| CASB | Base | Compare and swap byte in memory.
| CASH | Base | Compare and swap halfword in memory.
| CASL | Base | Compare and swap word or doubleword in memory.
| CASLB | Base | Compare and swap byte in memory.
| CASLH | Base | Compare and swap halfword in memory.
| CASLT | Base | Compare and swap unprivileged.
| CASP | Base | Compare and swap pair of words or doublewords in memory.
| CASPA | Base | Compare and swap pair of words or doublewords in memory.
| CASPAL | Base | Compare and swap pair of words or doublewords in memory.
| CASPALT | Base | Compare and swap pair unprivileged.
| CASPAT | Base | Compare and swap pair unprivileged.
| CASPL | Base | Compare and swap pair of words or doublewords in memory.
| CASPLT | Base | Compare and swap pair unprivileged.
| CASPT | Base | Compare and swap pair unprivileged.
| CAST | Base | Compare and swap unprivileged.
| CB<cc> (immediate) | Base | Compare register with immediate and branch.
| CB<cc> (register) | Base | Compare registers and branch.
| CBB<cc> | Base | Compare bytes and branch.
| CBBLE | Base | Compare signed less than or equal bytes and branch: an alias of CBB<cc>.
| CBBLO | Base | Compare unsigned lower than bytes and branch: an alias of CBB<cc>.
| CBBLS | Base | Compare unsigned lower than or equal bytes and branch: an alias of CBB<cc>.
| CBBLT | Base | Compare signed less than bytes and branch: an alias of CBB<cc>.
| CBGE (immediate) | Base | Compare signed greater than or equal immediate and branch: an alias of CB<cc> (immediate).
| CBH<cc> | Base | Compare halfwords and branch.
| CBHLE | Base | Compare signed less than or equal halfwords and branch: an alias of CBH<cc>.
| CBHLO | Base | Compare unsigned lower than halfwords and branch: an alias of CBH<cc>.
| CBHLS | Base | Compare unsigned lower than or equal halfwords and branch: an alias of CBH<cc>.
| CBHLT | Base | Compare signed less than halfwords and branch: an alias of CBH<cc>.
| CBHS (immediate) | Base | Compare unsigned greater than or equal immediate and branch: an alias of CB<cc> (immediate).
| CBLE (immediate) | Base | Compare signed less than or equal immediate and branch: an alias of CB<cc> (immediate).
| CBLE (register) | Base | Compare signed less than or equal register and branch: an alias of CB<cc> (register).
| CBLO (register) | Base | Compare unsigned lower than register and branch: an alias of CB<cc> (register).
| CBLS (immediate) | Base | Compare unsigned lower than or equal immediate and branch: an alias of CB<cc> (immediate).
| CBLS (register) | Base | Compare unsigned lower than or equal register and branch: an alias of CB<cc> (register).
| CBLT (register) | Base | Compare signed less than register and branch: an alias of CB<cc> (register).
| CBNZ | Base | Compare and branch on nonzero.
| CBZ | Base | Compare and branch on zero.
| CCMN (immediate) | Base | Conditional compare negative (immediate).
| CCMN (register) | Base | Conditional compare negative (register).
| CCMP (immediate) | Base | Conditional compare (immediate).
| CCMP (register) | Base | Conditional compare (register).
| CDOT (indexed) | SVE | Complex integer dot product (indexed).
| CDOT (vectors) | SVE | Complex integer dot product.
| CFINV | Base | Invert carry flag.
| CFP | Base | Control flow prediction restriction by context: an alias of SYS.
| CHKFEAT | Base | Check feature status.
| CINC | Base | Conditional increment: an alias of CSINC.
| CINV | Base | Conditional invert: an alias of CSINV.
| CLASTA (SIMD&FP scalar) | SVE | Conditionally extract element after last to SIMD&FP scalar register.
| CLASTA (scalar) | SVE | Conditionally extract element after last to general-purpose register.
| CLASTA (vectors) | SVE | Conditionally extract element after last to vector register.
| CLASTB (SIMD&FP scalar) | SVE | Conditionally extract last element to SIMD&FP scalar register.
| CLASTB (scalar) | SVE | Conditionally extract last element to general-purpose register.
| CLASTB (vectors) | SVE | Conditionally extract last element to vector register.
| CLRBHB | Base | Clear branch history.
| CLREX | Base | Clear exclusive.
| CLS | Base | Count leading sign bits.
| CLS | SVE | Count leading sign bits (predicated).
| CLS (vector) | SIMD | Count leading sign bits (vector).
| CLZ | Base | Count leading zeros.
| CLZ | SVE | Count leading zero bits (predicated).
| CLZ (vector) | SIMD | Count leading zero bits (vector).
| CMEQ (register) | SIMD | Compare bitwise equal (vector).
| CMEQ (zero) | SIMD | Compare bitwise equal to zero (vector).
| CMGE (register) | SIMD | Compare signed greater than or equal (vector).
| CMGE (zero) | SIMD | Compare signed greater than or equal to zero (vector).
| CMGT (register) | SIMD | Compare signed greater than (vector).
| CMGT (zero) | SIMD | Compare signed greater than zero (vector).
| CMHI (register) | SIMD | Compare unsigned higher (vector).
| CMHS (register) | SIMD | Compare unsigned higher or same (vector).
| CMLA (indexed) | SVE | Complex integer multiply-add with rotate (indexed).
| CMLA (vectors) | SVE | Complex integer multiply-add with rotate.
| CMLE (zero) | SIMD | Compare signed less than or equal to zero (vector).
| CMLT (zero) | SIMD | Compare signed less than zero (vector).
| CMN (extended register) | Base | Compare negative (extended register): an alias of ADDS (extended register).
| CMN (immediate) | Base | Compare negative (immediate): an alias of ADDS (immediate).
| CMN (shifted register) | Base | Compare negative (shifted register): an alias of ADDS (shifted register).
| CMP (extended register) | Base | Compare (extended register): an alias of SUBS (extended register).
| CMP (immediate) | Base | Compare (immediate): an alias of SUBS (immediate).
| CMP (shifted register) | Base | Compare (shifted register): an alias of SUBS (shifted register).
| CMP<cc> (immediate) | SVE | Compare vector to immediate.
| CMP<cc> (vectors) | SVE | Compare vectors.
| CMP<cc> (wide elements) | SVE | Compare vector to 64-bit wide elements.
| CMPLE (vectors) | SVE | Compare signed less than or equal to vector, setting the condition flags: an alias of CMP<cc> (vectors).
| CMPLO (vectors) | SVE | Compare unsigned lower than vector, setting the condition flags: an alias of CMP<cc> (vectors).
| CMPLS (vectors) | SVE | Compare unsigned lower or same as vector, setting the condition flags: an alias of CMP<cc> (vectors).
| CMPLT (vectors) | SVE | Compare signed less than vector, setting the condition flags: an alias of CMP<cc> (vectors).
| CMPP | Base | Compare with tag: an alias of SUBPS.
| CMTST | SIMD | Compare bitwise test bits nonzero (vector).
| CNEG | Base | Conditional negate: an alias of CSNEG.
| CNOT | SVE | Logically invert boolean condition in vector (predicated).
| CNT | Base | Count bits.
| CNT | SIMD | Population count per byte.
| CNT | SVE | Count non-zero bits (predicated).
| CNTB | SVE | Set scalar to multiple of predicate constraint element count.
| CNTD | SVE | Set scalar to multiple of predicate constraint element count.
| CNTH | SVE | Set scalar to multiple of predicate constraint element count.
| CNTP (predicate as counter) | SVE | Set scalar to count from predicate-as-counter.
| CNTP (predicate) | SVE | Set scalar to count of true predicate elements.
| CNTW | SVE | Set scalar to multiple of predicate constraint element count.
| COMPACT | SVE | Copy active vector elements to lower-numbered elements.
| COSP | Base | Clear other speculative prediction restriction by context: an alias of SYS.
| CPP | Base | Cache prefetch prediction restriction by context: an alias of SYS.
| CPY (SIMD&FP scalar) | SVE | Copy SIMD&FP scalar register to vector elements (predicated).
| CPY (immediate, merging) | SVE | Copy signed integer immediate to vector elements (merging).
| CPY (immediate, zeroing) | SVE | Copy signed integer immediate to vector elements (zeroing).
| CPY (scalar) | SVE | Copy general-purpose register to vector elements (predicated).
| CPYE | Base | Memory copy.
| CPYEN | Base | Memory copy, reads and writes non-temporal.
| CPYERN | Base | Memory copy, reads non-temporal.
| CPYERT | Base | Memory copy, reads unprivileged.
| CPYERTN | Base | Memory copy, reads unprivileged, reads and writes non-temporal.
| CPYERTRN | Base | Memory copy, reads unprivileged and non-temporal.
| CPYERTWN | Base | Memory copy, reads unprivileged, writes non-temporal.
| CPYET | Base | Memory copy, reads and writes unprivileged.
| CPYETN | Base | Memory copy, reads and writes unprivileged and non-temporal.
| CPYETRN | Base | Memory copy, reads and writes unprivileged, reads non-temporal.
| CPYETWN | Base | Memory copy, reads and writes unprivileged, writes non-temporal.
| CPYEWN | Base | Memory copy, writes non-temporal.
| CPYEWT | Base | Memory copy, writes unprivileged.
| CPYEWTN | Base | Memory copy, writes unprivileged, reads and writes non-temporal.
| CPYEWTRN | Base | Memory copy, writes unprivileged, reads non-temporal.
| CPYEWTWN | Base | Memory copy, writes unprivileged and non-temporal.
| CPYFE | Base | Memory copy forward-only.
| CPYFEN | Base | Memory copy forward-only, reads and writes non-temporal.
| CPYFERN | Base | Memory copy forward-only, reads non-temporal.
| CPYFERT | Base | Memory copy forward-only, reads unprivileged.
| CPYFERTN | Base | Memory copy forward-only, reads unprivileged, reads and writes non-temporal.
| CPYFERTRN | Base | Memory copy forward-only, reads unprivileged and non-temporal.
| CPYFERTWN | Base | Memory copy forward-only, reads unprivileged, writes non-temporal.
| CPYFET | Base | Memory copy forward-only, reads and writes unprivileged.
| CPYFETN | Base | Memory copy forward-only, reads and writes unprivileged and non-temporal.
| CPYFETRN | Base | Memory copy forward-only, reads and writes unprivileged, reads non-temporal.
| CPYFETWN | Base | Memory copy forward-only, reads and writes unprivileged, writes non-temporal.
| CPYFEWN | Base | Memory copy forward-only, writes non-temporal.
| CPYFEWT | Base | Memory copy forward-only, writes unprivileged.
| CPYFEWTN | Base | Memory copy forward-only, writes unprivileged, reads and writes non-temporal.
| CPYFEWTRN | Base | Memory copy forward-only, writes unprivileged, reads non-temporal.
| CPYFEWTWN | Base | Memory copy forward-only, writes unprivileged and non-temporal.
| CPYFM | Base | Memory copy forward-only.
| CPYFMN | Base | Memory copy forward-only, reads and writes non-temporal.
| CPYFMRN | Base | Memory copy forward-only, reads non-temporal.
| CPYFMRT | Base | Memory copy forward-only, reads unprivileged.
| CPYFMRTN | Base | Memory copy forward-only, reads unprivileged, reads and writes non-temporal.
| CPYFMRTRN | Base | Memory copy forward-only, reads unprivileged and non-temporal.
| CPYFMRTWN | Base | Memory copy forward-only, reads unprivileged, writes non-temporal.
| CPYFMT | Base | Memory copy forward-only, reads and writes unprivileged.
| CPYFMTN | Base | Memory copy forward-only, reads and writes unprivileged and non-temporal.
| CPYFMTRN | Base | Memory copy forward-only, reads and writes unprivileged, reads non-temporal.
| CPYFMTWN | Base | Memory copy forward-only, reads and writes unprivileged, writes non-temporal.
| CPYFMWN | Base | Memory copy forward-only, writes non-temporal.
| CPYFMWT | Base | Memory copy forward-only, writes unprivileged.
| CPYFMWTN | Base | Memory copy forward-only, writes unprivileged, reads and writes non-temporal.
| CPYFMWTRN | Base | Memory copy forward-only, writes unprivileged, reads non-temporal.
| CPYFMWTWN | Base | Memory copy forward-only, writes unprivileged and non-temporal.
| CPYFP | Base | Memory copy forward-only.
| CPYFPN | Base | Memory copy forward-only, reads and writes non-temporal.
| CPYFPRN | Base | Memory copy forward-only, reads non-temporal.
| CPYFPRT | Base | Memory copy forward-only, reads unprivileged.
| CPYFPRTN | Base | Memory copy forward-only, reads unprivileged, reads and writes non-temporal.
| CPYFPRTRN | Base | Memory copy forward-only, reads unprivileged and non-temporal.
| CPYFPRTWN | Base | Memory copy forward-only, reads unprivileged, writes non-temporal.
| CPYFPT | Base | Memory copy forward-only, reads and writes unprivileged.
| CPYFPTN | Base | Memory copy forward-only, reads and writes unprivileged and non-temporal.
| CPYFPTRN | Base | Memory copy forward-only, reads and writes unprivileged, reads non-temporal.
| CPYFPTWN | Base | Memory copy forward-only, reads and writes unprivileged, writes non-temporal.
| CPYFPWN | Base | Memory copy forward-only, writes non-temporal.
| CPYFPWT | Base | Memory copy forward-only, writes unprivileged.
| CPYFPWTN | Base | Memory copy forward-only, writes unprivileged, reads and writes non-temporal.
| CPYFPWTRN | Base | Memory copy forward-only, writes unprivileged, reads non-temporal.
| CPYFPWTWN | Base | Memory copy forward-only, writes unprivileged and non-temporal.
| CPYM | Base | Memory copy.
| CPYMN | Base | Memory copy, reads and writes non-temporal.
| CPYMRN | Base | Memory copy, reads non-temporal.
| CPYMRT | Base | Memory copy, reads unprivileged.
| CPYMRTN | Base | Memory copy, reads unprivileged, reads and writes non-temporal.
| CPYMRTRN | Base | Memory copy, reads unprivileged and non-temporal.
| CPYMRTWN | Base | Memory copy, reads unprivileged, writes non-temporal.
| CPYMT | Base | Memory copy, reads and writes unprivileged.
| CPYMTN | Base | Memory copy, reads and writes unprivileged and non-temporal.
| CPYMTRN | Base | Memory copy, reads and writes unprivileged, reads non-temporal.
| CPYMTWN | Base | Memory copy, reads and writes unprivileged, writes non-temporal.
| CPYMWN | Base | Memory copy, writes non-temporal.
| CPYMWT | Base | Memory copy, writes unprivileged.
| CPYMWTN | Base | Memory copy, writes unprivileged, reads and writes non-temporal.
| CPYMWTRN | Base | Memory copy, writes unprivileged, reads non-temporal.
| CPYMWTWN | Base | Memory copy, writes unprivileged and non-temporal.
| CPYP | Base | Memory copy.
| CPYPN | Base | Memory copy, reads and writes non-temporal.
| CPYPRN | Base | Memory copy, reads non-temporal.
| CPYPRT | Base | Memory copy, reads unprivileged.
| CPYPRTN | Base | Memory copy, reads unprivileged, reads and writes non-temporal.
| CPYPRTRN | Base | Memory copy, reads unprivileged and non-temporal.
| CPYPRTWN | Base | Memory copy, reads unprivileged, writes non-temporal.
| CPYPT | Base | Memory copy, reads and writes unprivileged.
| CPYPTN | Base | Memory copy, reads and writes unprivileged and non-temporal.
| CPYPTRN | Base | Memory copy, reads and writes unprivileged, reads non-temporal.
| CPYPTWN | Base | Memory copy, reads and writes unprivileged, writes non-temporal.
| CPYPWN | Base | Memory copy, writes non-temporal.
| CPYPWT | Base | Memory copy, writes unprivileged.
| CPYPWTN | Base | Memory copy, writes unprivileged, reads and writes non-temporal.
| CPYPWTRN | Base | Memory copy, writes unprivileged, reads non-temporal.
| CPYPWTWN | Base | Memory copy, writes unprivileged and non-temporal.
| CRC32B | Base | CRC32 checksum.
| CRC32CB | Base | CRC32C checksum.
| CRC32CH | Base | CRC32C checksum.
| CRC32CW | Base | CRC32C checksum.
| CRC32CX | Base | CRC32C checksum.
| CRC32H | Base | CRC32 checksum.
| CRC32W | Base | CRC32 checksum.
| CRC32X | Base | CRC32 checksum.
| CSDB | Base | Consumption of speculative data barrier.
| CSEL | Base | Conditional select.
| CSET | Base | Conditional set: an alias of CSINC.
| CSETM | Base | Conditional set mask: an alias of CSINV.
| CSINC | Base | Conditional select increment.
| CSINV | Base | Conditional select invert.
| CSNEG | Base | Conditional select negation.
| CTERMEQ | SVE | Compare and terminate loop.
| CTERMNE | SVE | Compare and terminate loop.
| CTZ | Base | Count trailing zeros.
| DC | Base | Data cache operation: an alias of SYS.
| DCPS1 | Base | Debug change PE state to EL1.
| DCPS2 | Base | Debug change PE state to EL2.
| DCPS3 | Base | Debug change PE state to EL3.
| DECB | SVE | Decrement scalar by multiple of predicate constraint element count.
| DECD | SVE | Decrement scalar by multiple of predicate constraint element count.
| DECD | SVE | Decrement vector by multiple of predicate constraint element count.
| DECH | SVE | Decrement scalar by multiple of predicate constraint element count.
| DECH | SVE | Decrement vector by multiple of predicate constraint element count.
| DECP (scalar) | SVE | Decrement scalar by count of true predicate elements.
| DECP (vector) | SVE | Decrement vector by count of true predicate elements.
| DECW (scalar) | SVE | Decrement scalar by multiple of predicate constraint element count.
| DECW (vector) | SVE | Decrement vector by multiple of predicate constraint element count.
| DGH | Base | Data gathering hint.
| DMB | Base | Data memory barrier.
| DRPS | Base | Debug restore PE state.
| DSB | Base | Data synchronization barrier.
| DUP (element) | SIMD | Duplicate vector element to vector or scalar.
| DUP (general) | SIMD | Duplicate general-purpose register to vector.
| DUP (immediate) | SVE | Broadcast signed immediate to vector elements (unpredicated).
| DUP (indexed) | SVE | Broadcast indexed element to vector (unpredicated).
| DUP (scalar) | SVE | Broadcast general-purpose register to vector elements (unpredicated).
| DUPM | SVE | Broadcast logical bitmask immediate to vector (unpredicated).
| DUPQ | SVE | Broadcast indexed element within each quadword vector segment (unpredicated).
| DVP | Base | Data value prediction restriction by context: an alias of SYS.
| EON | SVE | Bitwise exclusive OR with inverted immediate (unpredicated): an alias of EOR (immediate).
| EON (shifted register) | Base | Bitwise exclusive-OR NOT (shifted register).
| EOR (immediate) | Base | Bitwise exclusive-OR (immediate).
| EOR (immediate) | SVE | Bitwise exclusive OR with immediate (unpredicated).
| EOR (predicates) | SVE | Bitwise exclusive OR predicates.
| EOR (shifted register) | Base | Bitwise exclusive-OR (shifted register).
| EOR (vector) | SIMD | Bitwise exclusive-OR (vector).
| EOR (vectors, predicated) | SVE | Bitwise exclusive OR vectors (predicated).
| EOR (vectors, unpredicated) | SVE | Bitwise exclusive OR vectors (unpredicated).
| EOR3 | SIMD | Three-way exclusive-OR.
| EOR3 | SVE | Bitwise exclusive OR of three vectors.
| EORBT | SVE | Interleaving exclusive OR (bottom, top).
| EORQV | SVE | Bitwise exclusive OR reduction of quadword vector segments.
| EORS | SVE | Bitwise exclusive OR predicates, setting the condition flags.
| EORTB | SVE | Interleaving exclusive OR (top, bottom).
| EORV | SVE | Bitwise exclusive OR reduction to scalar.
| ERET | Base | Exception return.
| ERETAA | Base | Exception return, with pointer authentication.
| ERETAB | Base | Exception return, with pointer authentication.
| ESB | Base | Error synchronization barrier.
| EXPAND | SVE | Copy lower-numbered vector elements to active elements.
| EXT | SIMD | Extract vector from pair of vectors.
| EXT | SVE | Extract vector from pair of vectors.
| EXTQ | SVE | Extract vector segment from each pair of quadword vector segments.
| EXTR | Base | Extract register.
| F1CVT | SVE | 8-bit floating-point convert to half-precision.
| F1CVT | SME | Multi-vector floating-point convert from 8-bit floating-point to half-precision (in-order).
| F1CVTL | SIMD | 8-bit floating-point convert to half-precision (vector).
| F1CVTL | SME | Multi-vector floating-point convert from 8-bit floating-point to deinterleaved half-precision.
| F1CVTL2 | SIMD | 8-bit floating-point convert to half-precision (vector).
| F1CVTLT | SVE | 8-bit floating-point convert to half-precision (top).
| F2CVT | SVE | 8-bit floating-point convert to half-precision.
| F2CVT | SME | Multi-vector floating-point convert from 8-bit floating-point to half-precision (in-order).
| F2CVTL | SIMD | 8-bit floating-point convert to half-precision (vector).
| F2CVTL | SME | Multi-vector floating-point convert from 8-bit floating-point to deinterleaved half-precision.
| F2CVTL2 | SIMD | 8-bit floating-point convert to half-precision (vector).
| F2CVTLT | SVE | 8-bit floating-point convert to half-precision (top).
| FABD | SIMD | Floating-point absolute difference (vector).
| FABD | SVE | Floating-point absolute difference (predicated).
| FABS | SVE | Floating-point absolute value (predicated).
| FABS (scalar) | SIMD | Floating-point absolute value (scalar).
| FABS (vector) | SIMD | Floating-point absolute value (vector).
| FAC<cc> | SVE | Floating-point absolute compare vectors.
| FACGE | SIMD | Floating-point absolute compare greater than or equal (vector).
| FACGT | SIMD | Floating-point absolute compare greater than (vector).
| FACLE | SVE | Floating-point absolute compare less than or equal: an alias of FAC<cc>.
| FACLT | SVE | Floating-point absolute compare less than: an alias of FAC<cc>.
| FADD | SME | Floating-point add multi-vector to ZA array vector accumulators.
| FADD (immediate) | SVE | Floating-point add immediate (predicated).
| FADD (scalar) | SIMD | Floating-point add (scalar).
| FADD (vector) | SIMD | Floating-point add (vector).
| FADD (vectors, predicated) | SVE | Floating-point add vector (predicated).
| FADD (vectors, unpredicated) | SVE | Floating-point add vector (unpredicated).
| FADDA | SVE | Floating-point add strictly-ordered reduction, accumulating in scalar.
| FADDP | SVE | Floating-point add pairwise.
| FADDP (scalar) | SIMD | Floating-point add pair of elements (scalar).
| FADDP (vector) | SIMD | Floating-point add pairwise (vector).
| FADDQV | SVE | Floating-point add recursive reduction of quadword vector segments.
| FADDV | SVE | Floating-point add recursive reduction to scalar.
| FAMAX | SIMD | Floating-point absolute maximum.
| FAMAX | SVE | Floating-point absolute maximum (predicated).
| FAMAX | SME | Multi-vector floating-point absolute maximum.
| FAMIN | SIMD | Floating-point absolute minimum.
| FAMIN | SVE | Floating-point absolute minimum (predicated).
| FAMIN | SME | Multi-vector floating-point absolute minimum.
| FCADD | SIMD | Floating-point complex add.
| FCADD | SVE | Floating-point complex add with rotate (predicated).
| FCCMP | SIMD | Floating-point conditional quiet compare (scalar).
| FCCMPE | SIMD | Floating-point conditional signaling compare (scalar).
| FCLAMP | SVE | Floating-point clamp to minimum/maximum number.
| FCLAMP | SME | Multi-vector floating-point clamp to minimum/maximum number.
| FCM<cc> (vectors) | SVE | Floating-point compare vectors.
| FCM<cc> (zero) | SVE | Floating-point compare vector with zero.
| FCMEQ (register) | SIMD | Floating-point compare equal (vector).
| FCMEQ (zero) | SIMD | Floating-point compare equal to zero (vector).
| FCMGE (register) | SIMD | Floating-point compare greater than or equal (vector).
| FCMGE (zero) | SIMD | Floating-point compare greater than or equal to zero (vector).
| FCMGT (register) | SIMD | Floating-point compare greater than (vector).
| FCMGT (zero) | SIMD | Floating-point compare greater than zero (vector).
| FCMLA | SIMD | Floating-point complex multiply accumulate.
| FCMLA (by element) | SIMD | Floating-point complex multiply accumulate (by element).
| FCMLA (indexed) | SVE | Floating-point complex multiply-add by indexed values with rotate.
| FCMLA (vectors) | SVE | Floating-point complex multiply-add with rotate (predicated).
| FCMLE (vectors) | SVE | Floating-point compare less than or equal to vector: an alias of FCM<cc> (vectors).
| FCMLE (zero) | SIMD | Floating-point compare less than or equal to zero (vector).
| FCMLT (vectors) | SVE | Floating-point compare less than vector: an alias of FCM<cc> (vectors).
| FCMLT (zero) | SIMD | Floating-point compare less than zero (vector).
| FCMP | SIMD | Floating-point quiet compare (scalar).
| FCMPE | SIMD | Floating-point signaling compare (scalar).
| FCPY | SVE | Copy 8-bit floating-point immediate to vector elements (predicated).
| FCSEL | SIMD | Floating-point conditional select (scalar).
| FCVT | SIMD | Floating-point convert precision (scalar).
| FCVT | SVE | Floating-point convert precision (predicated).
| FCVT (narrowing, FP16 to FP8) | SME | Multi-vector floating-point convert from half-precision to packed 8-bit floating-point format.
| FCVT (narrowing, FP32 to FP16) | SME | Multi-vector floating-point convert from single-precision to packed half-precision.
| FCVT (narrowing, FP32 to FP8) | SME | Multi-vector floating-point convert from single-precision to packed 8-bit floating-point format.
| FCVT (widening) | SME | Multi-vector floating-point convert from half-precision to single-precision (in-order).
| FCVTAS (scalar SIMD&FP) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to away (scalar SIMD&FP).
| FCVTAS (scalar) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to away (scalar).
| FCVTAS (vector) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to away (vector).
| FCVTAU (scalar SIMD&FP) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to away (scalar SIMD&FP).
| FCVTAU (scalar) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to away (scalar).
| FCVTAU (vector) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to away (vector).
| FCVTL | SIMD | Floating-point convert to higher precision long (vector).
| FCVTL | SME | Multi-vector floating-point convert from half-precision to deinterleaved single-precision.
| FCVTL2 | SIMD | Floating-point convert to higher precision long (vector).
| FCVTLT | SVE | Floating-point up convert long (top, predicated).
| FCVTMS (scalar SIMD&FP) | SIMD | Floating-point convert to signed integer, rounding toward minus infinity (scalar SIMD&FP).
| FCVTMS (scalar) | SIMD | Floating-point convert to signed integer, rounding toward minus infinity (scalar).
| FCVTMS (vector) | SIMD | Floating-point convert to signed integer, rounding toward minus infinity (vector).
| FCVTMU (scalar SIMD&FP) | SIMD | Floating-point convert to unsigned integer, rounding toward minus infinity (scalar SIMD&FP).
| FCVTMU (scalar) | SIMD | Floating-point convert to unsigned integer, rounding toward minus infinity (scalar).
| FCVTMU (vector) | SIMD | Floating-point convert to unsigned integer, rounding toward minus infinity (vector).
| FCVTN | SIMD | Floating-point convert to lower precision narrow (vector).
| FCVTN | SIMD | Single-precision to 8-bit floating-point convert and narrow (vector).
| FCVTN | SVE | Half-precision convert, narrow and interleave to 8-bit floating-point.
| FCVTN (FP32 to FP16) | SME | Multi-vector floating-point convert from single-precision to interleaved half-precision.
| FCVTN (FP32 to FP8) | SME | Multi-vector floating-point convert from single-precision to interleaved 8-bit floating-point format.
| FCVTN (half-precision to 8-bit floating-point) | SIMD | Half-precision to 8-bit floating-point convert and narrow (vector).
| FCVTN2 (double to single-precision, single to half-precision) | SIMD | Floating-point convert to lower precision narrow (vector).
| FCVTN2 (single-precision to 8-bit floating-point) | SIMD | Single-precision to 8-bit floating-point convert and narrow (vector).
| FCVTNB | SVE | Single-precision convert, narrow and interleave to 8-bit floating-point (bottom).
| FCVTNS (scalar SIMD&FP) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to even (scalar SIMD&FP).
| FCVTNS (scalar) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to even (scalar).
| FCVTNS (vector) | SIMD | Floating-point convert to signed integer, rounding to nearest with ties to even (vector).
| FCVTNT (predicated) | SVE | Floating-point down convert and narrow (top, predicated).
| FCVTNT (unpredicated) | SVE | Single-precision convert, narrow and interleave to 8-bit floating-point (top).
| FCVTNU (scalar SIMD&FP) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to even (scalar SIMD&FP).
| FCVTNU (scalar) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to even (scalar).
| FCVTNU (vector) | SIMD | Floating-point convert to unsigned integer, rounding to nearest with ties to even (vector).
| FCVTPS (scalar SIMD&FP) | SIMD | Floating-point convert to signed integer, rounding toward plus infinity (scalar SIMD&FP).
| FCVTPS (scalar) | SIMD | Floating-point convert to signed integer, rounding toward plus infinity (scalar).
| FCVTPS (vector) | SIMD | Floating-point convert to signed integer, rounding toward plus infinity (vector).
| FCVTPU (scalar SIMD&FP) | SIMD | Floating-point convert to unsigned integer, rounding toward plus infinity (scalar SIMD&FP).
| FCVTPU (scalar) | SIMD | Floating-point convert to unsigned integer, rounding toward plus infinity (scalar).
| FCVTPU (vector) | SIMD | Floating-point convert to unsigned integer, rounding toward plus infinity (vector).
| FCVTX | SVE | Floating-point down convert, rounding to odd (predicated).
| FCVTXN | SIMD | Floating-point convert to lower precision narrow, rounding to odd (vector).
| FCVTXN2 | SIMD | Floating-point convert to lower precision narrow, rounding to odd (vector).
| FCVTXNT | SVE | Floating-point down convert, rounding to odd (top, predicated).
| FCVTZS | SVE | Floating-point convert to signed integer, rounding toward zero (predicated).
| FCVTZS | SME | Multi-vector floating-point convert to signed integer, rounding toward zero.
| FCVTZS (scalar SIMD&FP) | SIMD | Floating-point convert to signed integer, rounding toward zero (scalar SIMD&FP).
| FCVTZS (scalar, fixed-point) | SIMD | Floating-point convert to signed fixed-point, rounding toward zero (scalar).
| FCVTZS (scalar, integer) | SIMD | Floating-point convert to signed integer, rounding toward zero (scalar).
| FCVTZS (vector, fixed-point) | SIMD | Floating-point convert to signed fixed-point, rounding toward zero (vector).
| FCVTZS (vector, integer) | SIMD | Floating-point convert to signed integer, rounding toward zero (vector).
| FCVTZU | SVE | Floating-point convert to unsigned integer, rounding toward zero (predicated).
| FCVTZU | SME | Multi-vector floating-point convert to unsigned integer, rounding toward zero.
| FCVTZU (scalar SIMD&FP) | SIMD | Floating-point convert to unsigned integer, rounding toward zero (scalar SIMD&FP).
| FCVTZU (scalar, fixed-point) | SIMD | Floating-point convert to unsigned fixed-point, rounding toward zero (scalar).
| FCVTZU (scalar, integer) | SIMD | Floating-point convert to unsigned integer, rounding toward zero (scalar).
| FCVTZU (vector, fixed-point) | SIMD | Floating-point convert to unsigned fixed-point, rounding toward zero (vector).
| FCVTZU (vector, integer) | SIMD | Floating-point convert to unsigned integer, rounding toward zero (vector).
| FDIV | SVE | Floating-point divide by vector (predicated).
| FDIV (scalar) | SIMD | Floating-point divide (scalar).
| FDIV (vector) | SIMD | Floating-point divide (vector).
| FDIVR | SVE | Floating-point reversed divide by vector (predicated).
| FDOT (2-way, indexed, FP16 to FP32) | SVE | Half-precision floating-point indexed dot product.
| FDOT (2-way, indexed, FP8 to FP16) | SVE | 8-bit floating-point indexed dot product to half-precision.
| FDOT (2-way, multiple and indexed vector, FP16 to FP32) | SME | Multi-vector half-precision floating-point dot-product by indexed element.
| FDOT (2-way, multiple and indexed vector, FP8 to FP16) | SME | Multi-vector 8-bit floating-point dot-product by indexed element to half-precision.
| FDOT (2-way, multiple and single vector, FP16 to FP32) | SME | Multi-vector half-precision floating-point dot-product by vector.
| FDOT (2-way, multiple and single vector, FP8 to FP16) | SME | Multi-vector 8-bit floating-point dot-product by vector to half-precision.
| FDOT (2-way, multiple vectors, FP16 to FP32) | SME | Multi-vector half-precision floating-point dot-product.
| FDOT (2-way, multiple vectors, FP8 to FP16) | SME | Multi-vector 8-bit floating-point dot-product to half-precision.
| FDOT (2-way, vectors, FP16 to FP32) | SVE | Half-precision floating-point dot product.
| FDOT (2-way, vectors, FP8 to FP16) | SVE | 8-bit floating-point dot product to half-precision.
| FDOT (4-way, indexed) | SVE | 8-bit floating-point indexed dot product to single-precision.
| FDOT (4-way, multiple and indexed vector) | SME | Multi-vector 8-bit floating-point dot-product by indexed element to single-precision.
| FDOT (4-way, multiple and single vector) | SME | Multi-vector 8-bit floating-point dot-product by vector to single-precision.
| FDOT (4-way, multiple vectors) | SME | Multi-vector 8-bit floating-point dot-product to single-precision.
| FDOT (4-way, vectors) | SVE | 8-bit floating-point dot product to single-precision.
| FDOT (8-bit floating-point to half-precision, by element) | SIMD | 8-bit floating-point dot product to half-precision (vector, by element).
| FDOT (8-bit floating-point to half-precision, vector) | SIMD | 8-bit floating-point dot product to half-precision (vector).
| FDOT (8-bit floating-point to single-precision, by element) | SIMD | 8-bit floating-point dot product to single-precision (vector, by element).
| FDOT (8-bit floating-point to single-precision, vector) | SIMD | 8-bit floating-point dot product to single-precision (vector).
| FDUP | SVE | Broadcast 8-bit floating-point immediate to vector elements (unpredicated).
| FEXPA | SVE | Floating-point exponential accelerator.
| FIRSTP | SVE | Scalar index of first true predicate element (predicated).
| FJCVTZS | SIMD | Floating-point Javascript convert to signed fixed-point, rounding toward zero.
| FLOGB | SVE | Floating-point base 2 logarithm as integer.
| FMAD | SVE | Floating-point fused multiply-add vectors (predicated), writing multiplicand [Zdn = Za + Zdn * Zm].
| FMADD | SIMD | Floating-point fused multiply-add (scalar).
| FMAX (immediate) | SVE | Floating-point maximum with immediate (predicated).
| FMAX (multiple and single vector) | SME | Multi-vector floating-point maximum by vector.
| FMAX (multiple vectors) | SME | Multi-vector floating-point maximum.
| FMAX (scalar) | SIMD | Floating-point maximum (scalar).
| FMAX (vector) | SIMD | Floating-point maximum (vector).
| FMAX (vectors) | SVE | Floating-point maximum (predicated).
| FMAXNM (immediate) | SVE | Floating-point maximum number with immediate (predicated).
| FMAXNM (multiple and single vector) | SME | Multi-vector floating-point maximum number by vector.
| FMAXNM (multiple vectors) | SME | Multi-vector floating-point maximum number.
| FMAXNM (scalar) | SIMD | Floating-point maximum number (scalar).
| FMAXNM (vector) | SIMD | Floating-point maximum number (vector).
| FMAXNM (vectors) | SVE | Floating-point maximum number (predicated).
| FMAXNMP | SVE | Floating-point maximum number pairwise.
| FMAXNMP (scalar) | SIMD | Floating-point maximum number of pair of elements (scalar).
| FMAXNMP (vector) | SIMD | Floating-point maximum number pairwise (vector).
| FMAXNMQV | SVE | Floating-point maximum number recursive reduction of quadword vector segments.
| FMAXNMV | SIMD | Floating-point maximum number across vector.
| FMAXNMV | SVE | Floating-point maximum number recursive reduction to scalar.
| FMAXP | SVE | Floating-point maximum pairwise.
| FMAXP (scalar) | SIMD | Floating-point maximum of pair of elements (scalar).
| FMAXP (vector) | SIMD | Floating-point maximum pairwise (vector).
| FMAXQV | SVE | Floating-point maximum reduction of quadword vector segments.
| FMAXV | SIMD | Floating-point maximum across vector.
| FMAXV | SVE | Floating-point maximum recursive reduction to scalar.
| FMIN (immediate) | SVE | Floating-point minimum with immediate (predicated).
| FMIN (multiple and single vector) | SME | Multi-vector floating-point minimum by vector.
| FMIN (multiple vectors) | SME | Multi-vector floating-point minimum.
| FMIN (scalar) | SIMD | Floating-point minimum (scalar).
| FMIN (vector) | SIMD | Floating-point minimum (vector).
| FMIN (vectors) | SVE | Floating-point minimum (predicated).
| FMINNM (immediate) | SVE | Floating-point minimum number with immediate (predicated).
| FMINNM (multiple and single vector) | SME | Multi-vector floating-point minimum number by vector.
| FMINNM (multiple vectors) | SME | Multi-vector floating-point minimum number.
| FMINNM (scalar) | SIMD | Floating-point minimum number (scalar).
| FMINNM (vector) | SIMD | Floating-point minimum number (vector).
| FMINNM (vectors) | SVE | Floating-point minimum number (predicated).
| FMINNMP | SVE | Floating-point minimum number pairwise.
| FMINNMP (scalar) | SIMD | Floating-point minimum number of pair of elements (scalar).
| FMINNMP (vector) | SIMD | Floating-point minimum number pairwise (vector).
| FMINNMQV | SVE | Floating-point minimum number recursive reduction of quadword vector segments.
| FMINNMV | SIMD | Floating-point minimum number across vector.
| FMINNMV | SVE | Floating-point minimum number recursive reduction to scalar.
| FMINP | SVE | Floating-point minimum pairwise.
| FMINP (scalar) | SIMD | Floating-point minimum of pair of elements (scalar).
| FMINP (vector) | SIMD | Floating-point minimum pairwise (vector).
| FMINQV | SVE | Floating-point minimum recursive reduction of quadword vector segments.
| FMINV | SIMD | Floating-point minimum across vector.
| FMINV | SVE | Floating-point minimum recursive reduction to scalar.
| FMLA (by element) | SIMD | Floating-point fused multiply-add to accumulator (by element).
| FMLA (indexed) | SVE | Floating-point fused multiply-add by indexed elements (Zda = Zda + Zn * Zm[indexed]).
| FMLA (multiple and indexed vector) | SME | Multi-vector floating-point fused multiply-add by indexed element.
| FMLA (multiple and single vector) | SME | Multi-vector floating-point fused multiply-add by vector.
| FMLA (multiple vectors) | SME | Multi-vector floating-point fused multiply-add.
| FMLA (vector) | SIMD | Floating-point fused multiply-add to accumulator (vector).
| FMLA (vectors) | SVE | Floating-point fused multiply-add vectors (predicated), writing addend [Zda = Zda + Zn * Zm].
| FMLAL | SIMD | Floating-point fused multiply-add long to accumulator (by element).
| FMLAL | SIMD | Floating-point fused multiply-add long to accumulator (vector).
| FMLAL (multiple and indexed vector, FP16 to FP32) | SME | Multi-vector floating-point multiply-add long by indexed element.
| FMLAL (multiple and indexed vector, FP8 to FP16) | SME | Multi-vector 8-bit floating-point multiply-add long by indexed element to half-precision.
| FMLAL (multiple and single vector, FP16 to FP32) | SME | Multi-vector floating-point multiply-add long by vector.
| FMLAL (multiple and single vector, FP8 to FP16) | SME | Multi-vector 8-bit floating-point multiply-add long by vector to half-precision.
| FMLAL (multiple vectors, FP16 to FP32) | SME | Multi-vector floating-point multiply-add long.
| FMLAL (multiple vectors, FP8 to FP16) | SME | Multi-vector 8-bit floating-point multiply-add long to half-precision.
| FMLAL2 (by element) | SIMD | Floating-point fused multiply-add long to accumulator (by element).
| FMLAL2 (vector) | SIMD | Floating-point fused multiply-add long to accumulator (vector).
| FMLALB | SIMD | 8-bit floating-point multiply-add long to half-precision (vector, by element).
| FMLALB | SIMD | 8-bit floating-point multiply-add long to half-precision (vector).
| FMLALB (indexed, FP16 to FP32) | SVE | Half-precision floating-point multiply-add long to single-precision (bottom, indexed).
| FMLALB (indexed, FP8 to FP16) | SVE | 8-bit floating-point multiply-add long to half-precision (bottom, indexed).
| FMLALB (vectors, FP16 to FP32) | SVE | Half-precision floating-point multiply-add long to single-precision (bottom).
| FMLALB (vectors, FP8 to FP16) | SVE | 8-bit floating-point multiply-add long to half-precision (bottom).
| FMLALL (multiple and indexed vector) | SME | Multi-vector 8-bit floating-point multiply-add long-long by indexed element to single-precision.
| FMLALL (multiple and single vector) | SME | Multi-vector 8-bit floating-point multiply-add long-long by vector to single-precision.
| FMLALL (multiple vectors) | SME | Multi-vector 8-bit floating-point multiply-add long-long to single-precision.
| FMLALLBB | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector, by element).
| FMLALLBB | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector).
| FMLALLBB (indexed) | SVE | 8-bit floating-point multiply-add long long to single-precision (bottom bottom, indexed).
| FMLALLBB (vectors) | SVE | 8-bit floating-point multiply-add long long to single-precision (bottom bottom).
| FMLALLBT | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector, by element).
| FMLALLBT | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector).
| FMLALLBT (indexed) | SVE | 8-bit floating-point multiply-add long long to single-precision (bottom top, indexed).
| FMLALLBT (vectors) | SVE | 8-bit floating-point multiply-add long long to single-precision (bottom top).
| FMLALLTB | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector, by element).
| FMLALLTB | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector).
| FMLALLTB (indexed) | SVE | 8-bit floating-point multiply-add long long to single-precision (top bottom, indexed).
| FMLALLTB (vectors) | SVE | 8-bit floating-point multiply-add long long to single-precision (top bottom).
| FMLALLTT (by element) | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector, by element).
| FMLALLTT (indexed) | SVE | 8-bit floating-point multiply-add long long to single-precision (top top, indexed).
| FMLALLTT (vector) | SIMD | 8-bit floating-point multiply-add long-long to single-precision (vector).
| FMLALLTT (vectors) | SVE | 8-bit floating-point multiply-add long long to single-precision (top top).
| FMLALT (by element) | SIMD | 8-bit floating-point multiply-add long to half-precision (vector, by element).
| FMLALT (indexed, FP16 to FP32) | SVE | Half-precision floating-point multiply-add long to single-precision (top, indexed).
| FMLALT (indexed, FP8 to FP16) | SVE | 8-bit floating-point multiply-add long to half-precision (top, indexed).
| FMLALT (vector) | SIMD | 8-bit floating-point multiply-add long to half-precision (vector).
| FMLALT (vectors, FP16 to FP32) | SVE | Half-precision floating-point multiply-add long to single-precision (top).
| FMLALT (vectors, FP8 to FP16) | SVE | 8-bit floating-point multiply-add long to half-precision (top).
| FMLS (by element) | SIMD | Floating-point fused multiply-subtract from accumulator (by element).
| FMLS (indexed) | SVE | Floating-point fused multiply-subtract by indexed elements (Zda = Zda + -Zn * Zm[indexed]).
| FMLS (multiple and indexed vector) | SME | Multi-vector floating-point fused multiply-subtract by indexed element.
| FMLS (multiple and single vector) | SME | Multi-vector floating-point fused multiply-subtract by vector.
| FMLS (multiple vectors) | SME | Multi-vector floating-point fused multiply-subtract.
| FMLS (vector) | SIMD | Floating-point fused multiply-subtract from accumulator (vector).
| FMLS (vectors) | SVE | Floating-point fused multiply-subtract vectors (predicated), writing addend [Zda = Zda + -Zn * Zm].
| FMLSL | SIMD | Floating-point fused multiply-subtract long from accumulator (by element).
| FMLSL | SIMD | Floating-point fused multiply-subtract long from accumulator (vector).
| FMLSL (multiple and indexed vector) | SME | Multi-vector floating-point multiply-subtract long by indexed element.
| FMLSL (multiple and single vector) | SME | Multi-vector floating-point multiply-subtract long by vector.
| FMLSL (multiple vectors) | SME | Multi-vector floating-point multiply-subtract long.
| FMLSL2 (by element) | SIMD | Floating-point fused multiply-subtract long from accumulator (by element).
| FMLSL2 (vector) | SIMD | Floating-point fused multiply-subtract long from accumulator (vector).
| FMLSLB (indexed) | SVE | Half-precision floating-point multiply-subtract long from single-precision (bottom, indexed).
| FMLSLB (vectors) | SVE | Half-precision floating-point multiply-subtract long from single-precision (bottom).
| FMLSLT (indexed) | SVE | Half-precision floating-point multiply-subtract long from single-precision (top, indexed).
| FMLSLT (vectors) | SVE | Half-precision floating-point multiply-subtract long from single-precision (top).
| FMMLA (8-bit floating-point to half-precision) | SIMD | 8-bit floating-point matrix multiply-accumulate into 2x2 half-precision matrix.
| FMMLA (8-bit floating-point to single-precision) | SIMD | 8-bit floating-point matrix multiply-accumulate into 2x2 single-precision matrix.
| FMMLA (non-widening) | SVE | Floating-point matrix multiply-accumulate.
| FMMLA (widening, FP16 to FP32) | SVE | Half-precision floating-point matrix multiply-accumulate to single-precision.
| FMMLA (widening, FP8 to FP16) | SVE | 8-bit floating-point matrix multiply-accumulate to half-precision.
| FMMLA (widening, FP8 to FP32) | SVE | 8-bit floating-point matrix multiply-accumulate to single-precision.
| FMOP4A (non-widening) | SME | Floating-point quarter-tile outer products, accumulating.
| FMOP4A (widening, 2-way, FP16 to FP32) | SME | Half-precision quarter-tile sums of two outer products, accumulating.
| FMOP4A (widening, 2-way, FP8 to FP16) | SME | 8-bit floating-point quarter-tile sums of two outer products, accumulating.
| FMOP4A (widening, 4-way) | SME | 8-bit floating-point quarter-tile sums of four outer products, accumulating.
| FMOP4S (non-widening) | SME | Floating-point quarter-tile outer products, subtracting.
| FMOP4S (widening) | SME | Half-precision quarter-tile sums of two outer products, subtracting.
| FMOPA (non-widening) | SME | Floating-point outer product and accumulate.
| FMOPA (widening, 2-way, FP16 to FP32) | SME | Half-precision floating-point sum of outer products and accumulate.
| FMOPA (widening, 2-way, FP8 to FP16) | SME | 8-bit floating-point sum of outer products and accumulate.
| FMOPA (widening, 4-way) | SME | 8-bit floating-point sum of outer products and accumulate.
| FMOPS (non-widening) | SME | Floating-point outer product and subtract.
| FMOPS (widening) | SME | Half-precision floating-point sum of outer products and subtract.
| FMOV (general) | SIMD | Floating-point move to or from general-purpose register without conversion.
| FMOV (immediate, predicated) | SVE | Move 8-bit floating-point immediate to vector elements (predicated): an alias of FCPY.
| FMOV (immediate, unpredicated) | SVE | Move 8-bit floating-point immediate to vector elements (unpredicated): an alias of FDUP.
| FMOV (register) | SIMD | Floating-point move register without conversion.
| FMOV (scalar, immediate) | SIMD | Floating-point move immediate (scalar).
| FMOV (vector, immediate) | SIMD | Floating-point move immediate (vector).
| FMOV (zero, predicated) | SVE | Move floating-point +0.0 to vector elements (predicated): an alias of CPY (immediate, merging).
| FMOV (zero, unpredicated) | SVE | Move floating-point +0.0 to vector elements (unpredicated): an alias of DUP (immediate).
| FMSB | SVE | Floating-point fused multiply-subtract vectors (predicated), writing multiplicand [Zdn = Za + -Zdn * Zm].
| FMSUB | SIMD | Floating-point fused multiply-subtract (scalar).
| FMUL (by element) | SIMD | Floating-point multiply (by element).
| FMUL (immediate) | SVE | Floating-point multiply by immediate (predicated).
| FMUL (indexed) | SVE | Floating-point multiply by indexed elements.
| FMUL (multiple and single vector) | SME | Multi-vector floating-point multiply by vector.
| FMUL (multiple vectors) | SME | Multi-vector floating-point multiply.
| FMUL (scalar) | SIMD | Floating-point multiply (scalar).
| FMUL (vector) | SIMD | Floating-point multiply (vector).
| FMUL (vectors, predicated) | SVE | Floating-point multiply vectors (predicated).
| FMUL (vectors, unpredicated) | SVE | Floating-point multiply vectors (unpredicated).
| FMULX | SIMD | Floating-point multiply extended.
| FMULX | SVE | Floating-point multiply-extended vectors (predicated).
| FMULX (by element) | SIMD | Floating-point multiply extended (by element).
| FNEG | SVE | Floating-point negate (predicated).
| FNEG (scalar) | SIMD | Floating-point negate (scalar).
| FNEG (vector) | SIMD | Floating-point negate (vector).
| FNMAD | SVE | Floating-point negated fused multiply-add vectors (predicated), writing multiplicand [Zdn = -Za + -Zdn * Zm].
| FNMADD | SIMD | Floating-point negated fused multiply-add (scalar).
| FNMLA | SVE | Floating-point negated fused multiply-add vectors (predicated), writing addend [Zda = -Zda + -Zn * Zm].
| FNMLS | SVE | Floating-point negated fused multiply-subtract vectors (predicated), writing addend [Zda = -Zda + Zn * Zm].
| FNMSB | SVE | Floating-point negated fused multiply-subtract vectors (predicated), writing multiplicand [Zdn = -Za + Zdn * Zm].
| FNMSUB | SIMD | Floating-point negated fused multiply-subtract (scalar).
| FNMUL (scalar) | SIMD | Floating-point multiply-negate (scalar).
| FRECPE | SIMD | Floating-point reciprocal estimate.
| FRECPE | SVE | Floating-point reciprocal estimate (unpredicated).
| FRECPS | SIMD | Floating-point reciprocal step.
| FRECPS | SVE | Floating-point reciprocal step (unpredicated).
| FRECPX | SIMD | Floating-point reciprocal exponent (scalar).
| FRECPX | SVE | Floating-point reciprocal exponent (predicated).
| FRINT32X | SVE | Floating-point round to 32-bit integer, using current rounding mode (predicated).
| FRINT32X (scalar) | SIMD | Floating-point round to 32-bit integer, using current rounding mode (scalar).
| FRINT32X (vector) | SIMD | Floating-point round to 32-bit integer, using current rounding mode (vector).
| FRINT32Z | SVE | Floating-point round to 32-bit integer, toward zero (predicated).
| FRINT32Z (scalar) | SIMD | Floating-point round to 32-bit integer toward zero (scalar).
| FRINT32Z (vector) | SIMD | Floating-point round to 32-bit integer toward zero (vector).
| FRINT64X | SVE | Floating-point round to 64-bit integer, using current rounding mode (predicated).
| FRINT64X (scalar) | SIMD | Floating-point round to 64-bit integer, using current rounding mode (scalar).
| FRINT64X (vector) | SIMD | Floating-point round to 64-bit integer, using current rounding mode (vector).
| FRINT64Z | SVE | Floating-point round to 64-bit integer, toward zero (predicated).
| FRINT64Z (scalar) | SIMD | Floating-point round to 64-bit integer toward zero (scalar).
| FRINT64Z (vector) | SIMD | Floating-point round to 64-bit integer toward zero (vector).
| FRINT<r> | SVE | Floating-point round to integral value (predicated).
| FRINTA | SME | Multi-vector floating-point round to integral value, to nearest with ties away from zero.
| FRINTA (scalar) | SIMD | Floating-point round to integral, to nearest with ties to away (scalar).
| FRINTA (vector) | SIMD | Floating-point round to integral, to nearest with ties to away (vector).
| FRINTI (scalar) | SIMD | Floating-point round to integral, using current rounding mode (scalar).
| FRINTI (vector) | SIMD | Floating-point round to integral, using current rounding mode (vector).
| FRINTM | SME | Multi-vector floating-point round to integral value, toward minus Infinity.
| FRINTM (scalar) | SIMD | Floating-point round to integral, toward minus infinity (scalar).
| FRINTM (vector) | SIMD | Floating-point round to integral, toward minus infinity (vector).
| FRINTN | SME | Multi-vector floating-point round to integral value, to nearest with ties to even.
| FRINTN (scalar) | SIMD | Floating-point round to integral, to nearest with ties to even (scalar).
| FRINTN (vector) | SIMD | Floating-point round to integral, to nearest with ties to even (vector).
| FRINTP | SME | Multi-vector floating-point round to integral value, toward plus Infinity.
| FRINTP (scalar) | SIMD | Floating-point round to integral, toward plus infinity (scalar).
| FRINTP (vector) | SIMD | Floating-point round to integral, toward plus infinity (vector).
| FRINTX (scalar) | SIMD | Floating-point round to integral exact, using current rounding mode (scalar).
| FRINTX (vector) | SIMD | Floating-point round to integral exact, using current rounding mode (vector).
| FRINTZ (scalar) | SIMD | Floating-point round to integral, toward zero (scalar).
| FRINTZ (vector) | SIMD | Floating-point round to integral, toward zero (vector).
| FRSQRTE | SIMD | Floating-point reciprocal square root estimate.
| FRSQRTE | SVE | Floating-point reciprocal square root estimate (unpredicated).
| FRSQRTS | SIMD | Floating-point reciprocal square root step.
| FRSQRTS | SVE | Floating-point reciprocal square root step (unpredicated).
| FSCALE | SIMD | Floating-point adjust exponent by vector.
| FSCALE | SVE | Floating-point adjust exponent by vector (predicated).
| FSCALE (multiple and single vector) | SME | Multi-vector floating-point adjust exponent by vector.
| FSCALE (multiple vectors) | SME | Multi-vector floating-point adjust exponent.
| FSQRT | SVE | Floating-point square root (predicated).
| FSQRT (scalar) | SIMD | Floating-point square root (scalar).
| FSQRT (vector) | SIMD | Floating-point square root (vector).
| FSUB | SME | Floating-point subtract multi-vector from ZA array vector accumulators.
| FSUB (immediate) | SVE | Floating-point subtract immediate (predicated).
| FSUB (scalar) | SIMD | Floating-point subtract (scalar).
| FSUB (vector) | SIMD | Floating-point subtract (vector).
| FSUB (vectors, predicated) | SVE | Floating-point subtract vectors (predicated).
| FSUB (vectors, unpredicated) | SVE | Floating-point subtract vectors (unpredicated).
| FSUBR (immediate) | SVE | Floating-point reversed subtract from immediate (predicated).
| FSUBR (vectors) | SVE | Floating-point reversed subtract vectors (predicated).
| FTMAD | SVE | Floating-point trigonometric multiply-add coefficient.
| FTMOPA (non-widening) | SME | Floating-point sparse outer product, accumulating.
| FTMOPA (widening, 2-way, FP16 to FP32) | SME | Half-precision sparse sum of two outer products, accumulating.
| FTMOPA (widening, 2-way, FP8 to FP16) | SME | 8-bit floating-point sparse sum of two outer products, accumulating.
| FTMOPA (widening, 4-way) | SME | 8-bit floating-point sparse sum of four outer products, accumulating.
| FTSMUL | SVE | Floating-point trigonometric starting value.
| FTSSEL | SVE | Floating-point trigonometric select coefficient.
| FVDOT (FP16 to FP32) | SME | Multi-vector half-precision floating-point vertical dot-product by indexed element.
| FVDOT (FP8 to FP16) | SME | Multi-vector 8-bit floating-point vertical dot-product by indexed element to half-precision.
| FVDOTB | SME | Multi-vector 8-bit floating-point vertical dot-product by indexed element to single-precision (bottom).
| FVDOTT | SME | Multi-vector 8-bit floating-point vertical dot-product by indexed element to single-precision (top).
| GCSB | Base | Guarded Control Stack barrier.
| GCSPOPCX | Base | Guarded Control Stack pop and compare exception return record: an alias of SYS.
| GCSPOPM | Base | Guarded Control Stack pop: an alias of SYSL.
| GCSPOPX | Base | Guarded Control Stack pop exception return record: an alias of SYS.
| GCSPUSHM | Base | Guarded Control Stack push: an alias of SYS.
| GCSPUSHX | Base | Guarded Control Stack push exception return record: an alias of SYS.
| GCSSS1 | Base | Guarded Control Stack switch stack 1: an alias of SYS.
| GCSSS2 | Base | Guarded Control Stack switch stack 2: an alias of SYSL.
| GCSSTR | Base | Guarded Control Stack store register.
| GCSSTTR | Base | Guarded Control Stack store register (unprivileged).
| GMI | Base | Tag mask insert.
| HINT | Base | Hint instruction.
| HISTCNT | SVE | Count matching elements in vector.
| HISTSEG | SVE | Count matching elements in vector segments.
| HLT | Base | Halt instruction.
| HVC | Base | Hypervisor call.
| IC | Base | Instruction cache operation: an alias of SYS.
| INCB | SVE | Increment scalar by multiple of predicate constraint element count.
| INCD | SVE | Increment scalar by multiple of predicate constraint element count.
| INCD | SVE | Increment vector by multiple of predicate constraint element count.
| INCH | SVE | Increment scalar by multiple of predicate constraint element count.
| INCH | SVE | Increment vector by multiple of predicate constraint element count.
| INCP (scalar) | SVE | Increment scalar by count of true predicate elements.
| INCP (vector) | SVE | Increment vector by count of true predicate elements.
| INCW (scalar) | SVE | Increment scalar by multiple of predicate constraint element count.
| INCW (vector) | SVE | Increment vector by multiple of predicate constraint element count.
| INDEX (immediate, scalar) | SVE | Create index starting from immediate and incremented by general-purpose register.
| INDEX (immediates) | SVE | Create index starting from and incremented by immediate.
| INDEX (scalar, immediate) | SVE | Create index starting from general-purpose register and incremented by immediate.
| INDEX (scalars) | SVE | Create index starting from and incremented by general-purpose register.
| INS (element) | SIMD | Insert vector element from another vector element.
| INS (general) | SIMD | Insert vector element from general-purpose register.
| INSR (SIMD&FP scalar) | SVE | Insert SIMD&FP scalar register in shifted vector.
| INSR (scalar) | SVE | Insert general-purpose register in shifted vector.
| IRG | Base | Insert random tag.
| ISB | Base | Instruction synchronization barrier.
| LASTA (SIMD&FP scalar) | SVE | Extract element after last to SIMD&FP scalar register.
| LASTA (scalar) | SVE | Extract element after last to general-purpose register.
| LASTB (SIMD&FP scalar) | SVE | Extract last element to SIMD&FP scalar register.
| LASTB (scalar) | SVE | Extract last element to general-purpose register.
| LASTP | SVE | Scalar index of last true predicate element (predicated).
| LD1 (multiple structures) | SIMD | Load multiple single-element structures to one, two, three, or four registers.
| LD1 (single structure) | SIMD | Load one single-element structure to one lane of one register.
| LD1B (scalar plus immediate, consecutive registers) | SVE | Contiguous load of bytes to multiple consecutive vectors (immediate index).
| LD1B (scalar plus immediate, single register) | SVE | Contiguous load unsigned bytes to vector (immediate index).
| LD1B (scalar plus immediate, strided registers) | SME | Contiguous load of bytes to multiple strided vectors (immediate index).
| LD1B (scalar plus scalar, consecutive registers) | SVE | Contiguous load of bytes to multiple consecutive vectors (scalar index).
| LD1B (scalar plus scalar, single register) | SVE | Contiguous load unsigned bytes to vector (scalar index).
| LD1B (scalar plus scalar, strided registers) | SME | Contiguous load of bytes to multiple strided vectors (scalar index).
| LD1B (scalar plus scalar, tile slice) | SME | Contiguous load of bytes to 8-bit element ZA tile slice.
| LD1B (scalar plus vector) | SVE | Gather load unsigned bytes to vector (vector index).
| LD1B (vector plus immediate) | SVE | Gather load unsigned bytes to vector (immediate index).
| LD1D (scalar plus immediate, consecutive registers) | SVE | Contiguous load of doublewords to multiple consecutive vectors (immediate index).
| LD1D (scalar plus immediate, single register) | SVE | Contiguous load unsigned doublewords to vector (immediate index).
| LD1D (scalar plus immediate, strided registers) | SME | Contiguous load of doublewords to multiple strided vectors (immediate index).
| LD1D (scalar plus scalar, consecutive registers) | SVE | Contiguous load of doublewords to multiple consecutive vectors (scalar index).
| LD1D (scalar plus scalar, single register) | SVE | Contiguous load unsigned doublewords to vector (scalar index).
| LD1D (scalar plus scalar, strided registers) | SME | Contiguous load of doublewords to multiple strided vectors (scalar index).
| LD1D (scalar plus scalar, tile slice) | SME | Contiguous load of doublewords to 64-bit element ZA tile slice.
| LD1D (scalar plus vector) | SVE | Gather load doublewords to vector (vector index).
| LD1D (vector plus immediate) | SVE | Gather load doublewords to vector (immediate index).
| LD1H (scalar plus immediate, consecutive registers) | SVE | Contiguous load of halfwords to multiple consecutive vectors (immediate index).
| LD1H (scalar plus immediate, single register) | SVE | Contiguous load unsigned halfwords to vector (immediate index).
| LD1H (scalar plus immediate, strided registers) | SME | Contiguous load of halfwords to multiple strided vectors (immediate index).
| LD1H (scalar plus scalar, consecutive registers) | SVE | Contiguous load of halfwords to multiple consecutive vectors (scalar index).
| LD1H (scalar plus scalar, single register) | SVE | Contiguous load unsigned halfwords to vector (scalar index).
| LD1H (scalar plus scalar, strided registers) | SME | Contiguous load of halfwords to multiple strided vectors (scalar index).
| LD1H (scalar plus scalar, tile slice) | SME | Contiguous load of halfwords to 16-bit element ZA tile slice.
| LD1H (scalar plus vector) | SVE | Gather load unsigned halfwords to vector (vector index).
| LD1H (vector plus immediate) | SVE | Gather load unsigned halfwords to vector (immediate index).
| LD1Q | SVE | Gather load quadwords.
| LD1Q | SME | Contiguous load of quadwords to 128-bit element ZA tile slice.
| LD1R | SIMD | Load one single-element structure and replicate to all lanes (of one register).
| LD1RB | SVE | Load and broadcast unsigned byte to vector.
| LD1RD | SVE | Load and broadcast doubleword to vector.
| LD1RH | SVE | Load and broadcast unsigned halfword to vector.
| LD1ROB (scalar plus immediate) | SVE | Contiguous load and replicate thirty-two bytes (immediate index).
| LD1ROB (scalar plus scalar) | SVE | Contiguous load and replicate thirty-two bytes (scalar index).
| LD1ROD (scalar plus immediate) | SVE | Contiguous load and replicate four doublewords (immediate index).
| LD1ROD (scalar plus scalar) | SVE | Contiguous load and replicate four doublewords (scalar index).
| LD1ROH (scalar plus immediate) | SVE | Contiguous load and replicate sixteen halfwords (immediate index).
| LD1ROH (scalar plus scalar) | SVE | Contiguous load and replicate sixteen halfwords (scalar index).
| LD1ROW (scalar plus immediate) | SVE | Contiguous load and replicate eight words (immediate index).
| LD1ROW (scalar plus scalar) | SVE | Contiguous load and replicate eight words (scalar index).
| LD1RQB (scalar plus immediate) | SVE | Contiguous load and replicate sixteen bytes (immediate index).
| LD1RQB (scalar plus scalar) | SVE | Contiguous load and replicate sixteen bytes (scalar index).
| LD1RQD (scalar plus immediate) | SVE | Contiguous load and replicate two doublewords (immediate index).
| LD1RQD (scalar plus scalar) | SVE | Contiguous load and replicate two doublewords (scalar index).
| LD1RQH (scalar plus immediate) | SVE | Contiguous load and replicate eight halfwords (immediate index).
| LD1RQH (scalar plus scalar) | SVE | Contiguous load and replicate eight halfwords (scalar index).
| LD1RQW (scalar plus immediate) | SVE | Contiguous load and replicate four words (immediate index).
| LD1RQW (scalar plus scalar) | SVE | Contiguous load and replicate four words (scalar index).
| LD1RSB | SVE | Load and broadcast signed byte to vector.
| LD1RSH | SVE | Load and broadcast signed halfword to vector.
| LD1RSW | SVE | Load and broadcast signed word to vector.
| LD1RW | SVE | Load and broadcast unsigned word to vector.
| LD1SB (scalar plus immediate) | SVE | Contiguous load signed bytes to vector (immediate index).
| LD1SB (scalar plus scalar) | SVE | Contiguous load signed bytes to vector (scalar index).
| LD1SB (scalar plus vector) | SVE | Gather load signed bytes to vector (vector index).
| LD1SB (vector plus immediate) | SVE | Gather load signed bytes to vector (immediate index).
| LD1SH (scalar plus immediate) | SVE | Contiguous load signed halfwords to vector (immediate index).
| LD1SH (scalar plus scalar) | SVE | Contiguous load signed halfwords to vector (scalar index).
| LD1SH (scalar plus vector) | SVE | Gather load signed halfwords to vector (vector index).
| LD1SH (vector plus immediate) | SVE | Gather load signed halfwords to vector (immediate index).
| LD1SW (scalar plus immediate) | SVE | Contiguous load signed words to vector (immediate index).
| LD1SW (scalar plus scalar) | SVE | Contiguous load signed words to vector (scalar index).
| LD1SW (scalar plus vector) | SVE | Gather load signed words to vector (vector index).
| LD1SW (vector plus immediate) | SVE | Gather load signed words to vector (immediate index).
| LD1W (scalar plus immediate, consecutive registers) | SVE | Contiguous load of words to multiple consecutive vectors (immediate index).
| LD1W (scalar plus immediate, single register) | SVE | Contiguous load unsigned words to vector (immediate index).
| LD1W (scalar plus immediate, strided registers) | SME | Contiguous load of words to multiple strided vectors (immediate index).
| LD1W (scalar plus scalar, consecutive registers) | SVE | Contiguous load of words to multiple consecutive vectors (scalar index).
| LD1W (scalar plus scalar, single register) | SVE | Contiguous load unsigned words to vector (scalar index).
| LD1W (scalar plus scalar, strided registers) | SME | Contiguous load of words to multiple strided vectors (scalar index).
| LD1W (scalar plus scalar, tile slice) | SME | Contiguous load of words to 32-bit element ZA tile slice.
| LD1W (scalar plus vector) | SVE | Gather load unsigned words to vector (vector index).
| LD1W (vector plus immediate) | SVE | Gather load unsigned words to vector (immediate index).
| LD2 (multiple structures) | SIMD | Load multiple 2-element structures to two registers.
| LD2 (single structure) | SIMD | Load single 2-element structure to one lane of two registers.
| LD2B (scalar plus immediate) | SVE | Contiguous load two-byte structures to two vectors (immediate index).
| LD2B (scalar plus scalar) | SVE | Contiguous load two-byte structures to two vectors (scalar index).
| LD2D (scalar plus immediate) | SVE | Contiguous load two-doubleword structures to two vectors (immediate index).
| LD2D (scalar plus scalar) | SVE | Contiguous load two-doubleword structures to two vectors (scalar index).
| LD2H (scalar plus immediate) | SVE | Contiguous load two-halfword structures to two vectors (immediate index).
| LD2H (scalar plus scalar) | SVE | Contiguous load two-halfword structures to two vectors (scalar index).
| LD2Q (scalar plus immediate) | SVE | Contiguous load two-quadword structures to two vectors (immediate index).
| LD2Q (scalar plus scalar) | SVE | Contiguous load two-quadword structures to two vectors (scalar index).
| LD2R | SIMD | Load single 2-element structure and replicate to all lanes of two registers.
| LD2W (scalar plus immediate) | SVE | Contiguous load two-word structures to two vectors (immediate index).
| LD2W (scalar plus scalar) | SVE | Contiguous load two-word structures to two vectors (scalar index).
| LD3 (multiple structures) | SIMD | Load multiple 3-element structures to three registers.
| LD3 (single structure) | SIMD | Load single 3-element structure to one lane of three registers.
| LD3B (scalar plus immediate) | SVE | Contiguous load three-byte structures to three vectors (immediate index).
| LD3B (scalar plus scalar) | SVE | Contiguous load three-byte structures to three vectors (scalar index).
| LD3D (scalar plus immediate) | SVE | Contiguous load three-doubleword structures to three vectors (immediate index).
| LD3D (scalar plus scalar) | SVE | Contiguous load three-doubleword structures to three vectors (scalar index).
| LD3H (scalar plus immediate) | SVE | Contiguous load three-halfword structures to three vectors (immediate index).
| LD3H (scalar plus scalar) | SVE | Contiguous load three-halfword structures to three vectors (scalar index).
| LD3Q (scalar plus immediate) | SVE | Contiguous load three-quadword structures to three vectors (immediate index).
| LD3Q (scalar plus scalar) | SVE | Contiguous load three-quadword structures to three vectors (scalar index).
| LD3R | SIMD | Load single 3-element structure and replicate to all lanes of three registers.
| LD3W (scalar plus immediate) | SVE | Contiguous load three-word structures to three vectors (immediate index).
| LD3W (scalar plus scalar) | SVE | Contiguous load three-word structures to three vectors (scalar index).
| LD4 (multiple structures) | SIMD | Load multiple 4-element structures to four registers.
| LD4 (single structure) | SIMD | Load single 4-element structure to one lane of four registers.
| LD4B (scalar plus immediate) | SVE | Contiguous load four-byte structures to four vectors (immediate index).
| LD4B (scalar plus scalar) | SVE | Contiguous load four-byte structures to four vectors (scalar index).
| LD4D (scalar plus immediate) | SVE | Contiguous load four-doubleword structures to four vectors (immediate index).
| LD4D (scalar plus scalar) | SVE | Contiguous load four-doubleword structures to four vectors (scalar index).
| LD4H (scalar plus immediate) | SVE | Contiguous load four-halfword structures to four vectors (immediate index).
| LD4H (scalar plus scalar) | SVE | Contiguous load four-halfword structures to four vectors (scalar index).
| LD4Q (scalar plus immediate) | SVE | Contiguous load four-quadword structures to four vectors (immediate index).
| LD4Q (scalar plus scalar) | SVE | Contiguous load four-quadword structures to four vectors (scalar index).
| LD4R | SIMD | Load single 4-element structure and replicate to all lanes of four registers.
| LD4W (scalar plus immediate) | SVE | Contiguous load four-word structures to four vectors (immediate index).
| LD4W (scalar plus scalar) | SVE | Contiguous load four-word structures to four vectors (scalar index).
| LD64B | Base | Single-copy atomic 64-byte Load.
| LDADD | Base | Atomic add on word or doubleword in memory.
| LDADDA | Base | Atomic add on word or doubleword in memory.
| LDADDAB | Base | Atomic add on byte in memory.
| LDADDAH | Base | Atomic add on halfword in memory.
| LDADDAL | Base | Atomic add on word or doubleword in memory.
| LDADDALB | Base | Atomic add on byte in memory.
| LDADDALH | Base | Atomic add on halfword in memory.
| LDADDB | Base | Atomic add on byte in memory.
| LDADDH | Base | Atomic add on halfword in memory.
| LDADDL | Base | Atomic add on word or doubleword in memory.
| LDADDLB | Base | Atomic add on byte in memory.
| LDADDLH | Base | Atomic add on halfword in memory.
| LDAP1 (SIMD&FP) | SIMD | Load-acquire RCpc one single-element structure to one lane of one register.
| LDAPR | Base | Load-acquire RCpc register.
| LDAPRB | Base | Load-acquire RCpc register byte.
| LDAPRH | Base | Load-acquire RCpc register halfword.
| LDAPUR | Base | Load-acquire RCpc register (unscaled).
| LDAPUR (SIMD&FP) | SIMD | Load-acquire RCpc SIMD&FP register (unscaled offset).
| LDAPURB | Base | Load-acquire RCpc register byte (unscaled).
| LDAPURH | Base | Load-acquire RCpc register halfword (unscaled).
| LDAPURSB | Base | Load-acquire RCpc register signed byte (unscaled).
| LDAPURSH | Base | Load-acquire RCpc register signed halfword (unscaled).
| LDAPURSW | Base | Load-acquire RCpc register signed word (unscaled).
| LDAR | Base | Load-acquire register.
| LDARB | Base | Load-acquire register byte.
| LDARH | Base | Load-acquire register halfword.
| LDATXR | Base | Load-acquire unprivileged exclusive register.
| LDAXP | Base | Load-acquire exclusive pair of registers.
| LDAXR | Base | Load-acquire exclusive register.
| LDAXRB | Base | Load-acquire exclusive register byte.
| LDAXRH | Base | Load-acquire exclusive register halfword.
| LDBFADD | SIMD | BFloat16 floating-point add in memory.
| LDBFADDA | SIMD | BFloat16 floating-point add in memory.
| LDBFADDAL | SIMD | BFloat16 floating-point add in memory.
| LDBFADDL | SIMD | BFloat16 floating-point add in memory.
| LDBFMAX | SIMD | BFloat16 floating-point atomic maximum in memory.
| LDBFMAXA | SIMD | BFloat16 floating-point atomic maximum in memory.
| LDBFMAXAL | SIMD | BFloat16 floating-point atomic maximum in memory.
| LDBFMAXL | SIMD | BFloat16 floating-point atomic maximum in memory.
| LDBFMAXNM | SIMD | BFloat16 floating-point atomic maximum number in memory.
| LDBFMAXNMA | SIMD | BFloat16 floating-point atomic maximum number in memory.
| LDBFMAXNMAL | SIMD | BFloat16 floating-point atomic maximum number in memory.
| LDBFMAXNML | SIMD | BFloat16 floating-point atomic maximum number in memory.
| LDBFMIN | SIMD | BFloat16 floating-point atomic minimum in memory.
| LDBFMINA | SIMD | BFloat16 floating-point atomic minimum in memory.
| LDBFMINAL | SIMD | BFloat16 floating-point atomic minimum in memory.
| LDBFMINL | SIMD | BFloat16 floating-point atomic minimum in memory.
| LDBFMINNM | SIMD | BFloat16 floating-point atomic minimum number in memory.
| LDBFMINNMA | SIMD | BFloat16 floating-point atomic minimum number in memory.
| LDBFMINNMAL | SIMD | BFloat16 floating-point atomic minimum number in memory.
| LDBFMINNML | SIMD | BFloat16 floating-point atomic minimum number in memory.
| LDCLR | Base | Atomic bit clear on word or doubleword in memory.
| LDCLRA | Base | Atomic bit clear on word or doubleword in memory.
| LDCLRAB | Base | Atomic bit clear on byte in memory.
| LDCLRAH | Base | Atomic bit clear on halfword in memory.
| LDCLRAL | Base | Atomic bit clear on word or doubleword in memory.
| LDCLRALB | Base | Atomic bit clear on byte in memory.
| LDCLRALH | Base | Atomic bit clear on halfword in memory.
| LDCLRB | Base | Atomic bit clear on byte in memory.
| LDCLRH | Base | Atomic bit clear on halfword in memory.
| LDCLRL | Base | Atomic bit clear on word or doubleword in memory.
| LDCLRLB | Base | Atomic bit clear on byte in memory.
| LDCLRLH | Base | Atomic bit clear on halfword in memory.
| LDCLRP | Base | Atomic bit clear on quadword in memory.
| LDCLRPA | Base | Atomic bit clear on quadword in memory.
| LDCLRPAL | Base | Atomic bit clear on quadword in memory.
| LDCLRPL | Base | Atomic bit clear on quadword in memory.
| LDEOR | Base | Atomic exclusive-OR on word or doubleword in memory.
| LDEORA | Base | Atomic exclusive-OR on word or doubleword in memory.
| LDEORAB | Base | Atomic exclusive-OR on byte in memory.
| LDEORAH | Base | Atomic exclusive-OR on halfword in memory.
| LDEORAL | Base | Atomic exclusive-OR on word or doubleword in memory.
| LDEORALB | Base | Atomic exclusive-OR on byte in memory.
| LDEORALH | Base | Atomic exclusive-OR on halfword in memory.
| LDEORB | Base | Atomic exclusive-OR on byte in memory.
| LDEORH | Base | Atomic exclusive-OR on halfword in memory.
| LDEORL | Base | Atomic exclusive-OR on word or doubleword in memory.
| LDEORLB | Base | Atomic exclusive-OR on byte in memory.
| LDEORLH | Base | Atomic exclusive-OR on halfword in memory.
| LDFADD | SIMD | Floating-point atomic add in memory.
| LDFADDA | SIMD | Floating-point atomic add in memory.
| LDFADDAL | SIMD | Floating-point atomic add in memory.
| LDFADDL | SIMD | Floating-point atomic add in memory.
| LDFF1B (scalar plus scalar) | SVE | Contiguous load first-fault unsigned bytes to vector (scalar index).
| LDFF1B (scalar plus vector) | SVE | Gather load first-fault unsigned bytes to vector (vector index).
| LDFF1B (vector plus immediate) | SVE | Gather load first-fault unsigned bytes to vector (immediate index).
| LDFF1D (scalar plus scalar) | SVE | Contiguous load first-fault doublewords to vector (scalar index).
| LDFF1D (scalar plus vector) | SVE | Gather load first-fault doublewords to vector (vector index).
| LDFF1D (vector plus immediate) | SVE | Gather load first-fault doublewords to vector (immediate index).
| LDFF1H (scalar plus scalar) | SVE | Contiguous load first-fault unsigned halfwords to vector (scalar index).
| LDFF1H (scalar plus vector) | SVE | Gather load first-fault unsigned halfwords to vector (vector index).
| LDFF1H (vector plus immediate) | SVE | Gather load first-fault unsigned halfwords to vector (immediate index).
| LDFF1SB (scalar plus scalar) | SVE | Contiguous load first-fault signed bytes to vector (scalar index).
| LDFF1SB (scalar plus vector) | SVE | Gather load first-fault signed bytes to vector (vector index).
| LDFF1SB (vector plus immediate) | SVE | Gather load first-fault signed bytes to vector (immediate index).
| LDFF1SH (scalar plus scalar) | SVE | Contiguous load first-fault signed halfwords to vector (scalar index).
| LDFF1SH (scalar plus vector) | SVE | Gather load first-fault signed halfwords to vector (vector index).
| LDFF1SH (vector plus immediate) | SVE | Gather load first-fault signed halfwords to vector (immediate index).
| LDFF1SW (scalar plus scalar) | SVE | Contiguous load first-fault signed words to vector (scalar index).
| LDFF1SW (scalar plus vector) | SVE | Gather load first-fault signed words to vector (vector index).
| LDFF1SW (vector plus immediate) | SVE | Gather load first-fault signed words to vector (immediate index).
| LDFF1W (scalar plus scalar) | SVE | Contiguous load first-fault unsigned words to vector (scalar index).
| LDFF1W (scalar plus vector) | SVE | Gather load first-fault unsigned words to vector (vector index).
| LDFF1W (vector plus immediate) | SVE | Gather load first-fault unsigned words to vector (immediate index).
| LDFMAX | SIMD | Floating-point atomic maximum in memory.
| LDFMAXA | SIMD | Floating-point atomic maximum in memory.
| LDFMAXAL | SIMD | Floating-point atomic maximum in memory.
| LDFMAXL | SIMD | Floating-point atomic maximum in memory.
| LDFMAXNM | SIMD | Floating-point atomic maximum number in memory.
| LDFMAXNMA | SIMD | Floating-point atomic maximum number in memory.
| LDFMAXNMAL | SIMD | Floating-point atomic maximum number in memory.
| LDFMAXNML | SIMD | Floating-point atomic maximum number in memory.
| LDFMIN | SIMD | Floating-point atomic minimum in memory.
| LDFMINA | SIMD | Floating-point atomic minimum in memory.
| LDFMINAL | SIMD | Floating-point atomic minimum in memory.
| LDFMINL | SIMD | Floating-point atomic minimum in memory.
| LDFMINNM | SIMD | Floating-point atomic minimum number in memory.
| LDFMINNMA | SIMD | Floating-point atomic minimum number in memory.
| LDFMINNMAL | SIMD | Floating-point atomic minimum number in memory.
| LDFMINNML | SIMD | Floating-point atomic minimum number in memory.
| LDG | Base | Load Allocation Tag.
| LDGM | Base | Load tag multiple.
| LDIAPP | Base | Load-Acquire RCpc ordered pair of registers.
| LDLAR | Base | Load LOAcquire register.
| LDLARB | Base | Load LOAcquire register byte.
| LDLARH | Base | Load LOAcquire register halfword.
| LDNF1B | SVE | Contiguous load non-fault unsigned bytes to vector (immediate index).
| LDNF1D | SVE | Contiguous load non-fault doublewords to vector (immediate index).
| LDNF1H | SVE | Contiguous load non-fault unsigned halfwords to vector (immediate index).
| LDNF1SB | SVE | Contiguous load non-fault signed bytes to vector (immediate index).
| LDNF1SH | SVE | Contiguous load non-fault signed halfwords to vector (immediate index).
| LDNF1SW | SVE | Contiguous load non-fault signed words to vector (immediate index).
| LDNF1W | SVE | Contiguous load non-fault unsigned words to vector (immediate index).
| LDNP | Base | Load pair of registers, with non-temporal hint.
| LDNP (SIMD&FP) | SIMD | Load pair of SIMD&FP registers, with non-temporal hint.
| LDNT1B (scalar plus immediate, consecutive registers) | SVE | Contiguous load non-temporal of bytes to multiple consecutive vectors (immediate index).
| LDNT1B (scalar plus immediate, single register) | SVE | Contiguous load non-temporal bytes to vector (immediate index).
| LDNT1B (scalar plus immediate, strided registers) | SME | Contiguous load non-temporal of bytes to multiple strided vectors (immediate index).
| LDNT1B (scalar plus scalar, consecutive registers) | SVE | Contiguous load non-temporal of bytes to multiple consecutive vectors (scalar index).
| LDNT1B (scalar plus scalar, single register) | SVE | Contiguous load non-temporal bytes to vector (scalar index).
| LDNT1B (scalar plus scalar, strided registers) | SME | Contiguous load non-temporal of bytes to multiple strided vectors (scalar index).
| LDNT1B (vector plus scalar) | SVE | Gather load non-temporal unsigned bytes.
| LDNT1D (scalar plus immediate, consecutive registers) | SVE | Contiguous load non-temporal of doublewords to multiple consecutive vectors (immediate index).
| LDNT1D (scalar plus immediate, single register) | SVE | Contiguous load non-temporal doublewords to vector (immediate index).
| LDNT1D (scalar plus immediate, strided registers) | SME | Contiguous load non-temporal of doublewords to multiple strided vectors (immediate index).
| LDNT1D (scalar plus scalar, consecutive registers) | SVE | Contiguous load non-temporal of doublewords to multiple consecutive vectors (scalar index).
| LDNT1D (scalar plus scalar, single register) | SVE | Contiguous load non-temporal doublewords to vector (scalar index).
| LDNT1D (scalar plus scalar, strided registers) | SME | Contiguous load non-temporal of doublewords to multiple strided vectors (scalar index).
| LDNT1D (vector plus scalar) | SVE | Gather load non-temporal unsigned doublewords.
| LDNT1H (scalar plus immediate, consecutive registers) | SVE | Contiguous load non-temporal of halfwords to multiple consecutive vectors (immediate index).
| LDNT1H (scalar plus immediate, single register) | SVE | Contiguous load non-temporal halfwords to vector (immediate index).
| LDNT1H (scalar plus immediate, strided registers) | SME | Contiguous load non-temporal of halfwords to multiple strided vectors (immediate index).
| LDNT1H (scalar plus scalar, consecutive registers) | SVE | Contiguous load non-temporal of halfwords to multiple consecutive vectors (scalar index).
| LDNT1H (scalar plus scalar, single register) | SVE | Contiguous load non-temporal halfwords to vector (scalar index).
| LDNT1H (scalar plus scalar, strided registers) | SME | Contiguous load non-temporal of halfwords to multiple strided vectors (scalar index).
| LDNT1H (vector plus scalar) | SVE | Gather load non-temporal unsigned halfwords.
| LDNT1SB | SVE | Gather load non-temporal signed bytes.
| LDNT1SH | SVE | Gather load non-temporal signed halfwords.
| LDNT1SW | SVE | Gather load non-temporal signed words.
| LDNT1W (scalar plus immediate, consecutive registers) | SVE | Contiguous load non-temporal of words to multiple consecutive vectors (immediate index).
| LDNT1W (scalar plus immediate, single register) | SVE | Contiguous load non-temporal words to vector (immediate index).
| LDNT1W (scalar plus immediate, strided registers) | SME | Contiguous load non-temporal of words to multiple strided vectors (immediate index).
| LDNT1W (scalar plus scalar, consecutive registers) | SVE | Contiguous load non-temporal of words to multiple consecutive vectors (scalar index).
| LDNT1W (scalar plus scalar, single register) | SVE | Contiguous load non-temporal words to vector (scalar index).
| LDNT1W (scalar plus scalar, strided registers) | SME | Contiguous load non-temporal of words to multiple strided vectors (scalar index).
| LDNT1W (vector plus scalar) | SVE | Gather load non-temporal unsigned words.
| LDP | Base | Load pair of registers.
| LDP (SIMD&FP) | SIMD | Load pair of SIMD&FP registers.
| LDPSW | Base | Load pair of registers signed word.
| LDR (array vector) | SME | Load ZA array vector.
| LDR (immediate) | Base | Load register (immediate).
| LDR (immediate, SIMD&FP) | SIMD | Load SIMD&FP register (immediate offset).
| LDR (literal) | Base | Load register (literal).
| LDR (literal, SIMD&FP) | SIMD | Load SIMD&FP register (PC-relative literal).
| LDR (predicate) | SVE | Load predicate register.
| LDR (register) | Base | Load register (register).
| LDR (register, SIMD&FP) | SIMD | Load SIMD&FP register (register offset).
| LDR (table) | SME | Load ZT0 register.
| LDR (vector) | SVE | Load vector register.
| LDRAA | Base | Load register, with pointer authentication.
| LDRAB | Base | Load register, with pointer authentication.
| LDRB (immediate) | Base | Load register byte (immediate).
| LDRB (register) | Base | Load register byte (register).
| LDRH (immediate) | Base | Load register halfword (immediate).
| LDRH (register) | Base | Load register halfword (register).
| LDRSB (immediate) | Base | Load register signed byte (immediate).
| LDRSB (register) | Base | Load register signed byte (register).
| LDRSH (immediate) | Base | Load register signed halfword (immediate).
| LDRSH (register) | Base | Load register signed halfword (register).
| LDRSW (immediate) | Base | Load register signed word (immediate).
| LDRSW (literal) | Base | Load register signed word (literal).
| LDRSW (register) | Base | Load register signed word (register).
| LDSET | Base | Atomic bit set on word or doubleword in memory.
| LDSETA | Base | Atomic bit set on word or doubleword in memory.
| LDSETAB | Base | Atomic bit set on byte in memory.
| LDSETAH | Base | Atomic bit set on halfword in memory.
| LDSETAL | Base | Atomic bit set on word or doubleword in memory.
| LDSETALB | Base | Atomic bit set on byte in memory.
| LDSETALH | Base | Atomic bit set on halfword in memory.
| LDSETB | Base | Atomic bit set on byte in memory.
| LDSETH | Base | Atomic bit set on halfword in memory.
| LDSETL | Base | Atomic bit set on word or doubleword in memory.
| LDSETLB | Base | Atomic bit set on byte in memory.
| LDSETLH | Base | Atomic bit set on halfword in memory.
| LDSETP | Base | Atomic bit set on quadword in memory.
| LDSETPA | Base | Atomic bit set on quadword in memory.
| LDSETPAL | Base | Atomic bit set on quadword in memory.
| LDSETPL | Base | Atomic bit set on quadword in memory.
| LDSMAX | Base | Atomic signed maximum on word or doubleword in memory.
| LDSMAXA | Base | Atomic signed maximum on word or doubleword in memory.
| LDSMAXAB | Base | Atomic signed maximum on byte in memory.
| LDSMAXAH | Base | Atomic signed maximum on halfword in memory.
| LDSMAXAL | Base | Atomic signed maximum on word or doubleword in memory.
| LDSMAXALB | Base | Atomic signed maximum on byte in memory.
| LDSMAXALH | Base | Atomic signed maximum on halfword in memory.
| LDSMAXB | Base | Atomic signed maximum on byte in memory.
| LDSMAXH | Base | Atomic signed maximum on halfword in memory.
| LDSMAXL | Base | Atomic signed maximum on word or doubleword in memory.
| LDSMAXLB | Base | Atomic signed maximum on byte in memory.
| LDSMAXLH | Base | Atomic signed maximum on halfword in memory.
| LDSMIN | Base | Atomic signed minimum on word or doubleword in memory.
| LDSMINA | Base | Atomic signed minimum on word or doubleword in memory.
| LDSMINAB | Base | Atomic signed minimum on byte in memory.
| LDSMINAH | Base | Atomic signed minimum on halfword in memory.
| LDSMINAL | Base | Atomic signed minimum on word or doubleword in memory.
| LDSMINALB | Base | Atomic signed minimum on byte in memory.
| LDSMINALH | Base | Atomic signed minimum on halfword in memory.
| LDSMINB | Base | Atomic signed minimum on byte in memory.
| LDSMINH | Base | Atomic signed minimum on halfword in memory.
| LDSMINL | Base | Atomic signed minimum on word or doubleword in memory.
| LDSMINLB | Base | Atomic signed minimum on byte in memory.
| LDSMINLH | Base | Atomic signed minimum on halfword in memory.
| LDTADD | Base | Atomic add unprivileged.
| LDTADDA | Base | Atomic add unprivileged.
| LDTADDAL | Base | Atomic add unprivileged.
| LDTADDL | Base | Atomic add unprivileged.
| LDTCLR | Base | Atomic bit clear unprivileged.
| LDTCLRA | Base | Atomic bit clear unprivileged.
| LDTCLRAL | Base | Atomic bit clear unprivileged.
| LDTCLRL | Base | Atomic bit clear unprivileged.
| LDTNP | Base | Load unprivileged pair of registers, with non-temporal hint.
| LDTNP (SIMD&FP) | SIMD | Load unprivileged pair of SIMD&FP registers, with non-temporal hint.
| LDTP | Base | Load unprivileged pair of registers.
| LDTP (SIMD&FP) | SIMD | Load unprivileged pair of SIMD&FP registers.
| LDTR | Base | Load register (unprivileged).
| LDTRB | Base | Load register byte (unprivileged).
| LDTRH | Base | Load register halfword (unprivileged).
| LDTRSB | Base | Load register signed byte (unprivileged).
| LDTRSH | Base | Load register signed halfword (unprivileged).
| LDTRSW | Base | Load register signed word (unprivileged).
| LDTSET | Base | Atomic bit set unprivileged.
| LDTSETA | Base | Atomic bit set unprivileged.
| LDTSETAL | Base | Atomic bit set unprivileged.
| LDTSETL | Base | Atomic bit set unprivileged.
| LDTXR | Base | Load unprivileged exclusive register.
| LDUMAX | Base | Atomic unsigned maximum on word or doubleword in memory.
| LDUMAXA | Base | Atomic unsigned maximum on word or doubleword in memory.
| LDUMAXAB | Base | Atomic unsigned maximum on byte in memory.
| LDUMAXAH | Base | Atomic unsigned maximum on halfword in memory.
| LDUMAXAL | Base | Atomic unsigned maximum on word or doubleword in memory.
| LDUMAXALB | Base | Atomic unsigned maximum on byte in memory.
| LDUMAXALH | Base | Atomic unsigned maximum on halfword in memory.
| LDUMAXB | Base | Atomic unsigned maximum on byte in memory.
| LDUMAXH | Base | Atomic unsigned maximum on halfword in memory.
| LDUMAXL | Base | Atomic unsigned maximum on word or doubleword in memory.
| LDUMAXLB | Base | Atomic unsigned maximum on byte in memory.
| LDUMAXLH | Base | Atomic unsigned maximum on halfword in memory.
| LDUMIN | Base | Atomic unsigned minimum on word or doubleword in memory.
| LDUMINA | Base | Atomic unsigned minimum on word or doubleword in memory.
| LDUMINAB | Base | Atomic unsigned minimum on byte in memory.
| LDUMINAH | Base | Atomic unsigned minimum on halfword in memory.
| LDUMINAL | Base | Atomic unsigned minimum on word or doubleword in memory.
| LDUMINALB | Base | Atomic unsigned minimum on byte in memory.
| LDUMINALH | Base | Atomic unsigned minimum on halfword in memory.
| LDUMINB | Base | Atomic unsigned minimum on byte in memory.
| LDUMINH | Base | Atomic unsigned minimum on halfword in memory.
| LDUMINL | Base | Atomic unsigned minimum on word or doubleword in memory.
| LDUMINLB | Base | Atomic unsigned minimum on byte in memory.
| LDUMINLH | Base | Atomic unsigned minimum on halfword in memory.
| LDUR | Base | Load register (unscaled).
| LDUR (SIMD&FP) | SIMD | Load SIMD&FP register (unscaled offset).
| LDURB | Base | Load register byte (unscaled).
| LDURH | Base | Load register halfword (unscaled).
| LDURSB | Base | Load register signed byte (unscaled).
| LDURSH | Base | Load register signed halfword (unscaled).
| LDURSW | Base | Load register signed word (unscaled).
| LDXP | Base | Load exclusive pair of registers.
| LDXR | Base | Load exclusive register.
| LDXRB | Base | Load exclusive register byte.
| LDXRH | Base | Load exclusive register halfword.
| LSL (immediate) | Base | Logical shift left (immediate): an alias of UBFM.
| LSL (immediate, predicated) | SVE | Logical shift left by immediate (predicated).
| LSL (immediate, unpredicated) | SVE | Logical shift left by immediate (unpredicated).
| LSL (register) | Base | Logical shift left (register): an alias of LSLV.
| LSL (vectors) | SVE | Logical shift left by vector (predicated).
| LSL (wide elements, predicated) | SVE | Logical shift left by 64-bit wide elements (predicated).
| LSL (wide elements, unpredicated) | SVE | Logical shift left by 64-bit wide elements (unpredicated).
| LSLR | SVE | Reversed logical shift left by vector (predicated).
| LSLV | Base | Logical shift left variable.
| LSR (immediate) | Base | Logical shift right (immediate): an alias of UBFM.
| LSR (immediate, predicated) | SVE | Logical shift right by immediate (predicated).
| LSR (immediate, unpredicated) | SVE | Logical shift right by immediate (unpredicated).
| LSR (register) | Base | Logical shift right (register): an alias of LSRV.
| LSR (vectors) | SVE | Logical shift right by vector (predicated).
| LSR (wide elements, predicated) | SVE | Logical shift right by 64-bit wide elements (predicated).
| LSR (wide elements, unpredicated) | SVE | Logical shift right by 64-bit wide elements (unpredicated).
| LSRR | SVE | Reversed logical shift right by vector (predicated).
| LSRV | Base | Logical shift right variable.
| LUTI2 | SIMD | Lookup table read with 2-bit indices.
| LUTI2 | SVE | Lookup table read with 2-bit indices.
| LUTI2 (four registers) | SME | Lookup table read with 2-bit indexes.
| LUTI2 (single) | SME | Lookup table read with 2-bit indexes.
| LUTI2 (two registers) | SME | Lookup table read with 2-bit indexes.
| LUTI4 | SIMD | Lookup table read with 4-bit indices.
| LUTI4 | SVE | Lookup table read with 4-bit indices.
| LUTI4 (four registers, 16-bit & 32-bit) | SME | Lookup table read with 4-bit indexes.
| LUTI4 (four registers, 8-bit) | SME | Lookup table read with 4-bit indexes and 8-bit elements.
| LUTI4 (single) | SME | Lookup table read with 4-bit indexes.
| LUTI4 (two registers) | SME | Lookup table read with 4-bit indexes.
| MAD | SVE | Multiply-add vectors (predicated), writing multiplicand [Zdn = Za + Zdn * Zm].
| MADD | Base | Multiply-add.
| MADDPT | Base | Multiply-add checked pointer.
| MADPT | SVE | Multiply-add checked pointer vectors, writing multiplicand [Zdn = Za + Zdn * Zm].
| MATCH | SVE | Detect any matching elements, setting the condition flags.
| MLA (by element) | SIMD | Multiply-add to accumulator (vector, by element).
| MLA (indexed) | SVE | Multiply-add to accumulator (indexed).
| MLA (vector) | SIMD | Multiply-add to accumulator (vector).
| MLA (vectors) | SVE | Multiply-add vectors (predicated), writing addend [Zda = Zda + Zn * Zm].
| MLAPT | SVE | Multiply-add checked pointer vectors, writing addend [Zda = Zda + Zn * Zm].
| MLS (by element) | SIMD | Multiply-subtract from accumulator (vector, by element).
| MLS (indexed) | SVE | Multiply-subtract from accumulator (indexed).
| MLS (vector) | SIMD | Multiply-subtract from accumulator (vector).
| MLS (vectors) | SVE | Multiply-subtract vectors (predicated), writing addend [Zda = Zda - Zn * Zm].
| MNEG | Base | Multiply-negate: an alias of MSUB.
| MOV | SVE | Move logical bitmask immediate to vector (unpredicated): an alias of DUPM.
| MOV | SVE | Move predicate (unpredicated): an alias of ORR (predicates).
| MOV (SIMD&FP scalar, predicated) | SVE | Move SIMD&FP scalar register to vector elements (predicated): an alias of CPY (SIMD&FP scalar).
| MOV (SIMD&FP scalar, unpredicated) | SVE | Move indexed element or SIMD&FP scalar to vector (unpredicated): an alias of DUP (indexed).
| MOV (array to vector, four registers) | SME | Move four ZA single-vector groups to four vector registers: an alias of MOVA (array to vector, four registers).
| MOV (array to vector, two registers) | SME | Move two ZA single-vector groups to two vector registers: an alias of MOVA (array to vector, two registers).
| MOV (bitmask immediate) | Base | Move bitmask immediate value: an alias of ORR (immediate).
| MOV (element) | SIMD | Move vector element to another vector element: an alias of INS (element).
| MOV (from general) | SIMD | Move general-purpose register to a vector element: an alias of INS (general).
| MOV (immediate, predicated, merging) | SVE | Move signed integer immediate to vector elements (merging): an alias of CPY (immediate, merging).
| MOV (immediate, predicated, zeroing) | SVE | Move signed integer immediate to vector elements (zeroing): an alias of CPY (immediate, zeroing).
| MOV (immediate, unpredicated) | SVE | Move signed immediate to vector elements (unpredicated): an alias of DUP (immediate).
| MOV (inverted wide immediate) | Base | Move inverted wide immediate value: an alias of MOVN.
| MOV (predicate, predicated, merging) | SVE | Move predicates (merging): an alias of SEL (predicates).
| MOV (predicate, predicated, zeroing) | SVE | Move predicates (zeroing): an alias of AND (predicates).
| MOV (register) | Base | Move register value: an alias of ORR (shifted register).
| MOV (scalar) | SIMD | Move vector element to scalar: an alias of DUP (element).
| MOV (scalar, predicated) | SVE | Move general-purpose register to vector elements (predicated): an alias of CPY (scalar).
| MOV (scalar, unpredicated) | SVE | Move general-purpose register to vector elements (unpredicated): an alias of DUP (scalar).
| MOV (tile to vector, four registers) | SME | Move four ZA tile slices to four vector registers: an alias of MOVA (tile to vector, four registers).
| MOV (tile to vector, single) | SME | Move ZA tile slice to vector register: an alias of MOVA (tile to vector, single).
| MOV (tile to vector, two registers) | SME | Move two ZA tile slices to two vector registers: an alias of MOVA (tile to vector, two registers).
| MOV (to general) | SIMD | Move vector element to general-purpose register: an alias of UMOV.
| MOV (to/from SP) | Base | Move register value to or from SP: an alias of ADD (immediate).
| MOV (vector to array, four registers) | SME | Move four vector registers to four ZA single-vector groups: an alias of MOVA (vector to array, four registers).
| MOV (vector to array, two registers) | SME | Move two vector registers to two ZA single-vector groups: an alias of MOVA (vector to array, two registers).
| MOV (vector to tile, four registers) | SME | Move four vector registers to four ZA tile slices: an alias of MOVA (vector to tile, four registers).
| MOV (vector to tile, single) | SME | Move vector register to ZA tile slice: an alias of MOVA (vector to tile, single).
| MOV (vector to tile, two registers) | SME | Move two vector registers to two ZA tile slices: an alias of MOVA (vector to tile, two registers).
| MOV (vector) | SIMD | Move vector: an alias of ORR (vector, register).
| MOV (vector, predicated) | SVE | Move vector elements (predicated): an alias of SEL (vectors).
| MOV (vector, unpredicated) | SVE | Move vector register (unpredicated): an alias of ORR (vectors, unpredicated).
| MOV (wide immediate) | Base | Move wide immediate value: an alias of MOVZ.
| MOVA (array to vector, four registers) | SME | Move four ZA single-vector groups to four vector registers.
| MOVA (array to vector, two registers) | SME | Move two ZA single-vector groups to two vector registers.
| MOVA (tile to vector, four registers) | SME | Move four ZA tile slices to four vector registers.
| MOVA (tile to vector, single) | SME | Move ZA tile slice to vector register.
| MOVA (tile to vector, two registers) | SME | Move two ZA tile slices to two vector registers.
| MOVA (vector to array, four registers) | SME | Move four vector registers to four ZA single-vector groups.
| MOVA (vector to array, two registers) | SME | Move two vector registers to two ZA single-vector groups.
| MOVA (vector to tile, four registers) | SME | Move four vector registers to four ZA tile slices.
| MOVA (vector to tile, single) | SME | Move vector register to ZA tile slice.
| MOVA (vector to tile, two registers) | SME | Move two vector registers to two ZA tile slices.
| MOVAZ (array to vector, four registers) | SME | Move and zero four ZA single-vector groups to vector registers.
| MOVAZ (array to vector, two registers) | SME | Move and zero two ZA single-vector groups to vector registers.
| MOVAZ (tile to vector, four registers) | SME | Move and zero four ZA tile slices to vector registers.
| MOVAZ (tile to vector, single) | SME | Move and zero ZA tile slice to vector register.
| MOVAZ (tile to vector, two registers) | SME | Move and zero two ZA tile slices to vector registers.
| MOVI | SIMD | Move immediate (vector).
| MOVK | Base | Move wide with keep.
| MOVN | Base | Move wide with NOT.
| MOVPRFX (predicated) | SVE | Move prefix (predicated).
| MOVPRFX (unpredicated) | SVE | Move prefix (unpredicated).
| MOVS (predicated) | SVE | Move predicates (zeroing), setting the condition flags: an alias of ANDS.
| MOVS (unpredicated) | SVE | Move predicate (unpredicated), setting the condition flags: an alias of ORRS.
| MOVT (scalar to table) | SME | Move 8 bytes from general-purpose register to ZT0.
| MOVT (table to scalar) | SME | Move 8 bytes from ZT0 to general-purpose register.
| MOVT (vector to table) | SME | Move vector register to ZT0.
| MOVZ | Base | Move wide with zero.
| MRRS | Base | Move System register to two adjacent general-purpose registers.
| MRS | Base | Move System register to general-purpose register.
| MSB | SVE | Multiply-subtract vectors (predicated), writing multiplicand [Zdn = Za - Zdn * Zm].
| MSR (immediate) | Base | Move immediate value to special register.
| MSR (register) | Base | Move general-purpose register to System register.
| MSRR | Base | Move two adjacent general-purpose registers to System register.
| MSUB | Base | Multiply-subtract.
| MSUBPT | Base | Multiply-subtract checked pointer.
| MUL | Base | Multiply: an alias of MADD.
| MUL (by element) | SIMD | Multiply (vector, by element).
| MUL (immediate) | SVE | Multiply by immediate (unpredicated).
| MUL (indexed) | SVE | Multiply (indexed).
| MUL (vector) | SIMD | Multiply (vector).
| MUL (vectors, predicated) | SVE | Multiply vectors (predicated).
| MUL (vectors, unpredicated) | SVE | Multiply vectors (unpredicated).
| MVN | Base | Bitwise NOT: an alias of ORN (shifted register).
| MVN | SIMD | Bitwise NOT (vector): an alias of NOT.
| MVNI | SIMD | Move inverted immediate (vector).
| NAND | SVE | Bitwise NAND predicates.
| NANDS | SVE | Bitwise NAND predicates, setting the condition flags.
| NBSL | SVE | Bitwise inverted select.
| NEG | SVE | Negate (predicated).
| NEG (shifted register) | Base | Negate (shifted register): an alias of SUB (shifted register).
| NEG (vector) | SIMD | Negate (vector).
| NEGS | Base | Negate, setting flags: an alias of SUBS (shifted register).
| NGC | Base | Negate with carry: an alias of SBC.
| NGCS | Base | Negate with carry, setting flags: an alias of SBCS.
| NMATCH | SVE | Detect no matching elements, setting the condition flags.
| NOP | Base | No operation.
| NOR | SVE | Bitwise NOR predicates.
| NORS | SVE | Bitwise NOR predicates, setting the condition flags.
| NOT | SIMD | Bitwise NOT (vector).
| NOT (predicate) | SVE | Bitwise invert predicate: an alias of EOR (predicates).
| NOT (vector) | SVE | Bitwise invert vector (predicated).
| NOTS | SVE | Bitwise invert predicate, setting the condition flags: an alias of EORS.
| ORN (immediate) | SVE | Bitwise inclusive OR with inverted immediate (unpredicated): an alias of ORR (immediate).
| ORN (predicates) | SVE | Bitwise inclusive OR inverted predicate.
| ORN (shifted register) | Base | Bitwise OR NOT (shifted register).
| ORN (vector) | SIMD | Bitwise inclusive OR NOT (vector).
| ORNS | SVE | Bitwise inclusive OR inverted predicate, setting the condition flags.
| ORQV | SVE | Bitwise inclusive OR reduction of quadword vector segments.
| ORR (immediate) | Base | Bitwise OR (immediate).
| ORR (immediate) | SVE | Bitwise inclusive OR with immediate (unpredicated).
| ORR (predicates) | SVE | Bitwise inclusive OR predicates.
| ORR (shifted register) | Base | Bitwise OR (shifted register).
| ORR (vector, immediate) | SIMD | Bitwise inclusive OR (vector, immediate).
| ORR (vector, register) | SIMD | Bitwise inclusive OR (vector, register).
| ORR (vectors, predicated) | SVE | Bitwise inclusive OR vectors (predicated).
| ORR (vectors, unpredicated) | SVE | Bitwise inclusive OR vectors (unpredicated).
| ORRS | SVE | Bitwise inclusive OR predicates, setting the condition flags.
| ORV | SVE | Bitwise inclusive OR reduction to scalar.
| PACDA | Base | Pointer Authentication Code for data address, using key A.
| PACDB | Base | Pointer Authentication Code for data address, using key B.
| PACDZA | Base | Pointer Authentication Code for data address, using key A.
| PACDZB | Base | Pointer Authentication Code for data address, using key B.
| PACGA | Base | Pointer Authentication Code, using generic key.
| PACIA | Base | Pointer Authentication Code for instruction address, using key A.
| PACIA1716 | Base | Pointer Authentication Code for instruction address, using key A.
| PACIA171615 | Base | Pointer Authentication Code for instruction address, using key A.
| PACIASP | Base | Pointer Authentication Code for instruction address, using key A.
| PACIASPPC | Base | Pointer Authentication Code for return address, using key A.
| PACIAZ | Base | Pointer Authentication Code for instruction address, using key A.
| PACIB | Base | Pointer Authentication Code for instruction address, using key B.
| PACIB1716 | Base | Pointer Authentication Code for instruction address, using key B.
| PACIB171615 | Base | Pointer Authentication Code for instruction address, using key B.
| PACIBSP | Base | Pointer Authentication Code for instruction address, using key B.
| PACIBSPPC | Base | Pointer Authentication Code for return address, using key B.
| PACIBZ | Base | Pointer Authentication Code for instruction address, using key B.
| PACIZA | Base | Pointer Authentication Code for instruction address, using key A.
| PACIZB | Base | Pointer Authentication Code for instruction address, using key B.
| PACM | Base | Pointer authentication modifier.
| PACNBIASPPC | Base | Pointer Authentication Code for return address, using key A, not a branch target.
| PACNBIBSPPC | Base | Pointer Authentication Code for return address, using key B, not a branch target.
| PEXT (predicate pair) | SVE | Predicate extract pair from predicate-as-counter.
| PEXT (predicate) | SVE | Predicate extract from predicate-as-counter.
| PFALSE | SVE | Set all predicate elements to false.
| PFIRST | SVE | Set the first active predicate element to true.
| PMLAL | SVE | Multi-vector polynomial multiply long and accumulate vectors.
| PMOV (to predicate) | SVE | Move predicate from vector.
| PMOV (to vector) | SVE | Move predicate to vector.
| PMUL | SIMD | Polynomial multiply.
| PMUL | SVE | Polynomial multiply vectors (unpredicated).
| PMULL | SIMD | Polynomial multiply long.
| PMULL | SVE | Multi-vector polynomial multiply long.
| PMULL2 | SIMD | Polynomial multiply long.
| PMULLB | SVE | Polynomial multiply long (bottom).
| PMULLT | SVE | Polynomial multiply long (top).
| PNEXT | SVE | Find next active predicate.
| PRFB (scalar plus immediate) | SVE | Contiguous prefetch bytes (immediate index).
| PRFB (scalar plus scalar) | SVE | Contiguous prefetch bytes (scalar index).
| PRFB (scalar plus vector) | SVE | Gather prefetch bytes (scalar plus vector).
| PRFB (vector plus immediate) | SVE | Gather prefetch bytes (vector plus immediate).
| PRFD (scalar plus immediate) | SVE | Contiguous prefetch doublewords (immediate index).
| PRFD (scalar plus scalar) | SVE | Contiguous prefetch doublewords (scalar index).
| PRFD (scalar plus vector) | SVE | Gather prefetch doublewords (scalar plus vector).
| PRFD (vector plus immediate) | SVE | Gather prefetch doublewords (vector plus immediate).
| PRFH (scalar plus immediate) | SVE | Contiguous prefetch halfwords (immediate index).
| PRFH (scalar plus scalar) | SVE | Contiguous prefetch halfwords (scalar index).
| PRFH (scalar plus vector) | SVE | Gather prefetch halfwords (scalar plus vector).
| PRFH (vector plus immediate) | SVE | Gather prefetch halfwords (vector plus immediate).
| PRFM (immediate) | Base | Prefetch memory (immediate).
| PRFM (literal) | Base | Prefetch memory (literal).
| PRFM (register) | Base | Prefetch memory (register).
| PRFUM | Base | Prefetch memory (unscaled offset).
| PRFW (scalar plus immediate) | SVE | Contiguous prefetch words (immediate index).
| PRFW (scalar plus scalar) | SVE | Contiguous prefetch words (scalar index).
| PRFW (scalar plus vector) | SVE | Gather prefetch words (scalar plus vector).
| PRFW (vector plus immediate) | SVE | Gather prefetch words (vector plus immediate).
| PSB | Base | Profiling synchronization barrier.
| PSEL | SVE | Predicate select between predicate register or all-false.
| PSSBB | Base | Physical speculative store bypass barrier: an alias of DSB.
| PTEST | SVE | Set condition flags for predicate.
| PTRUE (predicate as counter) | SVE | Initialise predicate-as-counter to all active.
| PTRUE (predicate) | SVE | Initialise predicate from named constraint.
| PTRUES | SVE | Initialise predicate from named constraint and set the condition flags.
| PUNPKHI | SVE | Unpack and widen half of predicate.
| PUNPKLO | SVE | Unpack and widen half of predicate.
| RADDHN | SIMD | Rounding add returning high narrow.
| RADDHN2 | SIMD | Rounding add returning high narrow.
| RADDHNB | SVE | Rounding add narrow high part (bottom).
| RADDHNT | SVE | Rounding add narrow high part (top).
| RAX1 | SIMD | Rotate and exclusive-OR.
| RAX1 | SVE | Bitwise rotate left by 1 and exclusive OR.
| RBIT | Base | Reverse bits.
| RBIT | SVE | Reverse bits (predicated).
| RBIT (vector) | SIMD | Reverse bit order (vector).
| RCWCAS | Base | Read check write compare and swap doubleword in memory.
| RCWCASA | Base | Read check write compare and swap doubleword in memory.
| RCWCASAL | Base | Read check write compare and swap doubleword in memory.
| RCWCASL | Base | Read check write compare and swap doubleword in memory.
| RCWCASP | Base | Read check write compare and swap quadword in memory.
| RCWCASPA | Base | Read check write compare and swap quadword in memory.
| RCWCASPAL | Base | Read check write compare and swap quadword in memory.
| RCWCASPL | Base | Read check write compare and swap quadword in memory.
| RCWCLR | Base | Read check write atomic bit clear on doubleword in memory.
| RCWCLRA | Base | Read check write atomic bit clear on doubleword in memory.
| RCWCLRAL | Base | Read check write atomic bit clear on doubleword in memory.
| RCWCLRL | Base | Read check write atomic bit clear on doubleword in memory.
| RCWCLRP | Base | Read check write atomic bit clear on quadword in memory.
| RCWCLRPA | Base | Read check write atomic bit clear on quadword in memory.
| RCWCLRPAL | Base | Read check write atomic bit clear on quadword in memory.
| RCWCLRPL | Base | Read check write atomic bit clear on quadword in memory.
| RCWSCAS | Base | Read check write software compare and swap doubleword in memory.
| RCWSCASA | Base | Read check write software compare and swap doubleword in memory.
| RCWSCASAL | Base | Read check write software compare and swap doubleword in memory.
| RCWSCASL | Base | Read check write software compare and swap doubleword in memory.
| RCWSCASP | Base | Read check write software compare and swap quadword in memory.
| RCWSCASPA | Base | Read check write software compare and swap quadword in memory.
| RCWSCASPAL | Base | Read check write software compare and swap quadword in memory.
| RCWSCASPL | Base | Read check write software compare and swap quadword in memory.
| RCWSCLR | Base | Read check write software atomic bit clear on doubleword in memory.
| RCWSCLRA | Base | Read check write software atomic bit clear on doubleword in memory.
| RCWSCLRAL | Base | Read check write software atomic bit clear on doubleword in memory.
| RCWSCLRL | Base | Read check write software atomic bit clear on doubleword in memory.
| RCWSCLRP | Base | Read check write software atomic bit clear on quadword in memory.
| RCWSCLRPA | Base | Read check write software atomic bit clear on quadword in memory.
| RCWSCLRPAL | Base | Read check write software atomic bit clear on quadword in memory.
| RCWSCLRPL | Base | Read check write software atomic bit clear on quadword in memory.
| RCWSET | Base | Read check write atomic bit set on doubleword in memory.
| RCWSETA | Base | Read check write atomic bit set on doubleword in memory.
| RCWSETAL | Base | Read check write atomic bit set on doubleword in memory.
| RCWSETL | Base | Read check write atomic bit set on doubleword in memory.
| RCWSETP | Base | Read check write atomic bit set on quadword in memory.
| RCWSETPA | Base | Read check write atomic bit set on quadword in memory.
| RCWSETPAL | Base | Read check write atomic bit set on quadword in memory.
| RCWSETPL | Base | Read check write atomic bit set on quadword in memory.
| RCWSSET | Base | Read check write software atomic bit set on doubleword in memory.
| RCWSSETA | Base | Read check write software atomic bit set on doubleword in memory.
| RCWSSETAL | Base | Read check write software atomic bit set on doubleword in memory.
| RCWSSETL | Base | Read check write software atomic bit set on doubleword in memory.
| RCWSSETP | Base | Read check write software atomic bit set on quadword in memory.
| RCWSSETPA | Base | Read check write software atomic bit set on quadword in memory.
| RCWSSETPAL | Base | Read check write software atomic bit set on quadword in memory.
| RCWSSETPL | Base | Read check write software atomic bit set on quadword in memory.
| RCWSSWP | Base | Read check write software swap doubleword in memory.
| RCWSSWPA | Base | Read check write software swap doubleword in memory.
| RCWSSWPAL | Base | Read check write software swap doubleword in memory.
| RCWSSWPL | Base | Read check write software swap doubleword in memory.
| RCWSSWPP | Base | Read check write software swap quadword in memory.
| RCWSSWPPA | Base | Read check write software swap quadword in memory.
| RCWSSWPPAL | Base | Read check write software swap quadword in memory.
| RCWSSWPPL | Base | Read check write software swap quadword in memory.
| RCWSWP | Base | Read check write swap doubleword in memory.
| RCWSWPA | Base | Read check write swap doubleword in memory.
| RCWSWPAL | Base | Read check write swap doubleword in memory.
| RCWSWPL | Base | Read check write swap doubleword in memory.
| RCWSWPP | Base | Read check write swap quadword in memory.
| RCWSWPPA | Base | Read check write swap quadword in memory.
| RCWSWPPAL | Base | Read check write swap quadword in memory.
| RCWSWPPL | Base | Read check write swap quadword in memory.
| RDFFR (predicated) | SVE | Return predicate of succesfully loaded elements.
| RDFFR (unpredicated) | SVE | Read the first-fault register.
| RDFFRS | SVE | Return predicate of succesfully loaded elements, setting the condition flags.
| RDSVL | SME | Read multiple of Streaming SVE vector register size to scalar register.
| RDVL | SVE | Read multiple of vector register size to scalar register.
| RET | Base | Return from subroutine.
| RETAA | Base | Return from subroutine, with pointer authentication.
| RETAASPPC | Base | Return from subroutine, with enhanced pointer authentication return using an immediate offset.
| RETAASPPCR | Base | Return from subroutine, with enhanced pointer authentication return using a register.
| RETAB | Base | Return from subroutine, with pointer authentication.
| RETABSPPC | Base | Return from subroutine, with enhanced pointer authentication return using an immediate offset.
| RETABSPPCR | Base | Return from subroutine, with enhanced pointer authentication return using a register.
| REV | Base | Reverse bytes.
| REV (predicate) | SVE | Reverse all elements in a predicate.
| REV (vector) | SVE | Reverse all elements in a vector (unpredicated).
| REV16 | Base | Reverse bytes in 16-bit halfwords.
| REV16 (vector) | SIMD | Reverse elements in 16-bit halfwords (vector).
| REV32 | Base | Reverse bytes in 32-bit words.
| REV32 (vector) | SIMD | Reverse elements in 32-bit words (vector).
| REV64 | Base | Reverse bytes: an alias of REV.
| REV64 | SIMD | Reverse elements in 64-bit doublewords (vector).
| REVB | SVE | Reverse bytes / halfwords / words within elements (predicated).
| REVD | SVE | Reverse 64-bit doublewords in elements (predicated).
| REVH | SVE | Reverse bytes / halfwords / words within elements (predicated).
| REVW | SVE | Reverse bytes / halfwords / words within elements (predicated).
| RMIF | Base | Rotate, mask insert flags.
| ROR (immediate) | Base | Rotate right (immediate): an alias of EXTR.
| ROR (register) | Base | Rotate right (register): an alias of RORV.
| RORV | Base | Rotate right variable.
| RPRFM | Base | Range prefetch memory.
| RSHRN | SIMD | Rounding shift right narrow (immediate).
| RSHRN2 | SIMD | Rounding shift right narrow (immediate).
| RSHRNB | SVE | Rounding shift right narrow by immediate (bottom).
| RSHRNT | SVE | Rounding shift right narrow by immediate (top).
| RSUBHN | SIMD | Rounding subtract returning high narrow.
| RSUBHN2 | SIMD | Rounding subtract returning high narrow.
| RSUBHNB | SVE | Rounding subtract narrow high part (bottom).
| RSUBHNT | SVE | Rounding subtract narrow high part (top).
| SABA | SIMD | Signed absolute difference and accumulate.
| SABA | SVE | Signed absolute difference and accumulate.
| SABAL | SIMD | Signed absolute difference and accumulate long.
| SABAL2 | SIMD | Signed absolute difference and accumulate long.
| SABALB | SVE | Signed absolute difference and accumulate long (bottom).
| SABALT | SVE | Signed absolute difference and accumulate long (top).
| SABD | SIMD | Signed absolute difference.
| SABD | SVE | Signed absolute difference (predicated).
| SABDL | SIMD | Signed absolute difference long.
| SABDL2 | SIMD | Signed absolute difference long.
| SABDLB | SVE | Signed absolute difference long (bottom).
| SABDLT | SVE | Signed absolute difference long (top).
| SADALP | SIMD | Signed add and accumulate long pairwise.
| SADALP | SVE | Signed add and accumulate long pairwise.
| SADDL | SIMD | Signed add long (vector).
| SADDL2 | SIMD | Signed add long (vector).
| SADDLB | SVE | Signed add long (bottom).
| SADDLBT | SVE | Signed add long (bottom + top).
| SADDLP | SIMD | Signed add long pairwise.
| SADDLT | SVE | Signed add long (top).
| SADDLV | SIMD | Signed add long across vector.
| SADDV | SVE | Signed add reduction to scalar.
| SADDW | SIMD | Signed add wide.
| SADDW2 | SIMD | Signed add wide.
| SADDWB | SVE | Signed add wide (bottom).
| SADDWT | SVE | Signed add wide (top).
| SB | Base | Speculation barrier.
| SBC | Base | Subtract with carry.
| SBCLB | SVE | Subtract with carry long (bottom).
| SBCLT | SVE | Subtract with carry long (top).
| SBCS | Base | Subtract with carry, setting flags.
| SBFIZ | Base | Signed bitfield insert in zeros: an alias of SBFM.
| SBFM | Base | Signed bitfield move.
| SBFX | Base | Signed bitfield extract: an alias of SBFM.
| SCLAMP | SVE | Signed clamp to minimum/maximum vector.
| SCLAMP | SME | Multi-vector signed clamp to minimum/maximum vector.
| SCVTF | SVE | Signed integer convert to floating-point (predicated).
| SCVTF | SME | Multi-vector signed integer convert to floating-point.
| SCVTF (scalar SIMD&FP) | SIMD | Signed integer convert to floating-point (scalar SIMD&FP).
| SCVTF (scalar, fixed-point) | SIMD | Signed fixed-point convert to floating-point (scalar).
| SCVTF (scalar, integer) | SIMD | Signed integer convert to floating-point (scalar).
| SCVTF (vector, fixed-point) | SIMD | Signed fixed-point convert to floating-point (vector).
| SCVTF (vector, integer) | SIMD | Signed integer convert to floating-point (vector).
| SDIV | Base | Signed divide.
| SDIV | SVE | Signed divide (predicated).
| SDIVR | SVE | Signed reversed divide (predicated).
| SDOT (2-way, indexed) | SVE | Signed integer indexed dot product.
| SDOT (2-way, multiple and indexed vector) | SME | Multi-vector signed integer dot-product by indexed element.
| SDOT (2-way, multiple and single vector) | SME | Multi-vector signed integer dot-product by vector.
| SDOT (2-way, multiple vectors) | SME | Multi-vector signed integer dot-product.
| SDOT (2-way, vectors) | SVE | Signed integer dot product.
| SDOT (4-way, indexed) | SVE | Signed integer indexed dot product.
| SDOT (4-way, multiple and indexed vector) | SME | Multi-vector signed integer dot-product by indexed element.
| SDOT (4-way, multiple and single vector) | SME | Multi-vector signed integer dot-product by vector.
| SDOT (4-way, multiple vectors) | SME | Multi-vector signed integer dot-product.
| SDOT (4-way, vectors) | SVE | Signed integer dot product.
| SDOT (by element) | SIMD | Dot product signed arithmetic (vector, by element).
| SDOT (vector) | SIMD | Dot product signed arithmetic (vector).
| SEL | SME | Multi-vector conditionally select elements from two vectors.
| SEL (predicates) | SVE | Conditionally select elements from two predicates.
| SEL (vectors) | SVE | Conditionally select elements from two vectors.
| SETE | Base | Memory set.
| SETEN | Base | Memory set, non-temporal.
| SETET | Base | Memory set, unprivileged.
| SETETN | Base | Memory set, unprivileged and non-temporal.
| SETF16 | Base | Evaluation of 8-bit or 16-bit flag values.
| SETF8 | Base | Evaluation of 8-bit or 16-bit flag values.
| SETFFR | SVE | Initialise the first-fault register to all true.
| SETGE | Base | Memory set with tag setting.
| SETGEN | Base | Memory set with tag setting, non-temporal.
| SETGET | Base | Memory set with tag setting, unprivileged.
| SETGETN | Base | Memory set with tag setting, unprivileged and non-temporal.
| SETGM | Base | Memory set with tag setting.
| SETGMN | Base | Memory set with tag setting, non-temporal.
| SETGMT | Base | Memory set with tag setting, unprivileged.
| SETGMTN | Base | Memory set with tag setting, unprivileged and non-temporal.
| SETGP | Base | Memory set with tag setting.
| SETGPN | Base | Memory set with tag setting, non-temporal.
| SETGPT | Base | Memory set with tag setting, unprivileged.
| SETGPTN | Base | Memory set with tag setting, unprivileged and non-temporal.
| SETM | Base | Memory set.
| SETMN | Base | Memory set, non-temporal.
| SETMT | Base | Memory set, unprivileged.
| SETMTN | Base | Memory set, unprivileged and non-temporal.
| SETP | Base | Memory set.
| SETPN | Base | Memory set, non-temporal.
| SETPT | Base | Memory set, unprivileged.
| SETPTN | Base | Memory set, unprivileged and non-temporal.
| SEV | Base | Send event.
| SEVL | Base | Send event local.
| SHA1C | SIMD | SHA1 hash update (choose).
| SHA1H | SIMD | SHA1 fixed rotate.
| SHA1M | SIMD | SHA1 hash update (majority).
| SHA1P | SIMD | SHA1 hash update (parity).
| SHA1SU0 | SIMD | SHA1 schedule update 0.
| SHA1SU1 | SIMD | SHA1 schedule update 1.
| SHA256H | SIMD | SHA256 hash update (part 1).
| SHA256H2 | SIMD | SHA256 hash update (part 2).
| SHA256SU0 | SIMD | SHA256 schedule update 0.
| SHA256SU1 | SIMD | SHA256 schedule update 1.
| SHA512H | SIMD | SHA512 hash update part 1.
| SHA512H2 | SIMD | SHA512 hash update part 2.
| SHA512SU0 | SIMD | SHA512 schedule update 0.
| SHA512SU1 | SIMD | SHA512 schedule update 1.
| SHADD | SIMD | Signed halving add.
| SHADD | SVE | Signed halving addition.
| SHL | SIMD | Shift left (immediate).
| SHLL | SIMD | Shift left long (by element size).
| SHLL2 | SIMD | Shift left long (by element size).
| SHRN | SIMD | Shift right narrow (immediate).
| SHRN2 | SIMD | Shift right narrow (immediate).
| SHRNB | SVE | Shift right narrow by immediate (bottom).
| SHRNT | SVE | Shift right narrow by immediate (top).
| SHSUB | SIMD | Signed halving subtract.
| SHSUB | SVE | Signed halving subtract.
| SHSUBR | SVE | Signed halving subtract reversed vectors.
| SLI | SIMD | Shift left and insert (immediate).
| SLI | SVE | Shift left and insert (immediate).
| SM3PARTW1 | SIMD | SM3PARTW1.
| SM3PARTW2 | SIMD | SM3PARTW2.
| SM3SS1 | SIMD | SM3SS1.
| SM3TT1A | SIMD | SM3TT1A.
| SM3TT1B | SIMD | SM3TT1B.
| SM3TT2A | SIMD | SM3TT2A.
| SM3TT2B | SIMD | SM3TT2B.
| SM4E | SIMD | SM4 encode.
| SM4E | SVE | SM4 encryption and decryption.
| SM4EKEY | SIMD | SM4 key.
| SM4EKEY | SVE | SM4 key updates.
| SMADDL | Base | Signed multiply-add long.
| SMAX | SIMD | Signed maximum (vector).
| SMAX (immediate) | Base | Signed maximum (immediate).
| SMAX (immediate) | SVE | Signed maximum with immediate (unpredicated).
| SMAX (multiple and single vector) | SME | Multi-vector signed maximum by vector.
| SMAX (multiple vectors) | SME | Multi-vector signed maximum.
| SMAX (register) | Base | Signed maximum (register).
| SMAX (vectors) | SVE | Signed maximum vectors (predicated).
| SMAXP | SIMD | Signed maximum pairwise.
| SMAXP | SVE | Signed maximum pairwise.
| SMAXQV | SVE | Signed maximum reduction of quadword vector segments.
| SMAXV | SIMD | Signed maximum across vector.
| SMAXV | SVE | Signed maximum reduction to scalar.
| SMC | Base | Secure monitor call.
| SMIN | SIMD | Signed minimum (vector).
| SMIN (immediate) | Base | Signed minimum (immediate).
| SMIN (immediate) | SVE | Signed minimum with immediate (unpredicated).
| SMIN (multiple and single vector) | SME | Multi-vector signed minimum by vector.
| SMIN (multiple vectors) | SME | Multi-vector signed minimum.
| SMIN (register) | Base | Signed minimum (register).
| SMIN (vectors) | SVE | Signed minimum vectors (predicated).
| SMINP | SIMD | Signed minimum pairwise.
| SMINP | SVE | Signed minimum pairwise.
| SMINQV | SVE | Signed minimum reduction of quadword vector segments.
| SMINV | SIMD | Signed minimum across vector.
| SMINV | SVE | Signed minimum reduction to scalar.
| SMLAL | SIMD | Signed multiply-add long (vector, by element).
| SMLAL | SIMD | Signed multiply-add long (vector).
| SMLAL (multiple and indexed vector) | SME | Multi-vector signed integer multiply-add long by indexed element.
| SMLAL (multiple and single vector) | SME | Multi-vector signed integer multiply-add long by vector.
| SMLAL (multiple vectors) | SME | Multi-vector signed integer multiply-add long.
| SMLAL2 (by element) | SIMD | Signed multiply-add long (vector, by element).
| SMLAL2 (vector) | SIMD | Signed multiply-add long (vector).
| SMLALB (indexed) | SVE | Signed multiply-add long to accumulator (bottom, indexed).
| SMLALB (vectors) | SVE | Signed multiply-add long to accumulator (bottom).
| SMLALL (multiple and indexed vector) | SME | Multi-vector signed integer multiply-add long-long by indexed element.
| SMLALL (multiple and single vector) | SME | Multi-vector signed integer multiply-add long-long by vector.
| SMLALL (multiple vectors) | SME | Multi-vector signed integer multiply-add long-long.
| SMLALT (indexed) | SVE | Signed multiply-add long to accumulator (top, indexed).
| SMLALT (vectors) | SVE | Signed multiply-add long to accumulator (top).
| SMLSL | SIMD | Signed multiply-subtract long (vector, by element).
| SMLSL | SIMD | Signed multiply-subtract long (vector).
| SMLSL (multiple and indexed vector) | SME | Multi-vector signed integer multiply-subtract long by indexed element.
| SMLSL (multiple and single vector) | SME | Multi-vector signed integer multiply-subtract long by vector.
| SMLSL (multiple vectors) | SME | Multi-vector signed integer multiply-subtract long.
| SMLSL2 (by element) | SIMD | Signed multiply-subtract long (vector, by element).
| SMLSL2 (vector) | SIMD | Signed multiply-subtract long (vector).
| SMLSLB (indexed) | SVE | Signed multiply-subtract long from accumulator (bottom, indexed).
| SMLSLB (vectors) | SVE | Signed multiply-subtract long from accumulator (bottom).
| SMLSLL (multiple and indexed vector) | SME | Multi-vector signed integer multiply-subtract long-long by indexed element.
| SMLSLL (multiple and single vector) | SME | Multi-vector signed integer multiply-subtract long-long by vector.
| SMLSLL (multiple vectors) | SME | Multi-vector signed integer multiply-subtract long-long.
| SMLSLT (indexed) | SVE | Signed multiply-subtract long from accumulator (top, indexed).
| SMLSLT (vectors) | SVE | Signed multiply-subtract long from accumulator (top).
| SMMLA | SVE | Signed integer matrix multiply-accumulate.
| SMMLA (vector) | SIMD | Signed 8-bit integer matrix multiply-accumulate (vector).
| SMNEGL | Base | Signed multiply-negate long: an alias of SMSUBL.
| SMOP4A (2-way) | SME | Signed integer quarter-tile sums of two outer products, accumulating.
| SMOP4A (4-way) | SME | Signed integer quarter-tile sums of four outer products, accumulating.
| SMOP4S (2-way) | SME | Signed integer quarter-tile sums of two outer products, subtracting.
| SMOP4S (4-way) | SME | Signed integer quarter-tile sums of four outer products, subtracting.
| SMOPA (2-way) | SME | Signed integer sum of outer products and accumulate.
| SMOPA (4-way) | SME | Signed integer sum of outer products and accumulate.
| SMOPS (2-way) | SME | Signed integer sum of outer products and subtract.
| SMOPS (4-way) | SME | Signed integer sum of outer products and subtract.
| SMOV | SIMD | Signed move vector element to general-purpose register.
| SMSTART | Base | Enables access to Streaming SVE mode and SME architectural state: an alias of MSR (immediate).
| SMSTOP | Base | Disables access to Streaming SVE mode and SME architectural state: an alias of MSR (immediate).
| SMSUBL | Base | Signed multiply-subtract long.
| SMULH | Base | Signed multiply high.
| SMULH (predicated) | SVE | Signed multiply returning high half (predicated).
| SMULH (unpredicated) | SVE | Signed multiply returning high half (unpredicated).
| SMULL | Base | Signed multiply long: an alias of SMADDL.
| SMULL | SIMD | Signed multiply long (vector, by element).
| SMULL | SIMD | Signed multiply long (vector).
| SMULL2 (by element) | SIMD | Signed multiply long (vector, by element).
| SMULL2 (vector) | SIMD | Signed multiply long (vector).
| SMULLB (indexed) | SVE | Signed multiply long (bottom, indexed).
| SMULLB (vectors) | SVE | Signed multiply long (bottom).
| SMULLT (indexed) | SVE | Signed multiply long (top, indexed).
| SMULLT (vectors) | SVE | Signed multiply long (top).
| SPLICE | SVE | Splice two vectors under predicate control.
| SQABS | SIMD | Signed saturating absolute value.
| SQABS | SVE | Signed saturating absolute value.
| SQADD | SIMD | Signed saturating add.
| SQADD (immediate) | SVE | Signed saturating add immediate (unpredicated).
| SQADD (vectors, predicated) | SVE | Signed saturating addition (predicated).
| SQADD (vectors, unpredicated) | SVE | Signed saturating add vectors (unpredicated).
| SQCADD | SVE | Saturating complex integer add with rotate.
| SQCVT (four registers) | SME | Multi-vector signed saturating extract narrow.
| SQCVT (two registers) | SME | Multi-vector signed saturating extract narrow.
| SQCVTN | SVE | Signed saturating extract narrow and interleave.
| SQCVTN | SME | Multi-vector signed saturating extract narrow and interleave.
| SQCVTU (four registers) | SME | Multi-vector signed saturating unsigned extract narrow.
| SQCVTU (two registers) | SME | Multi-vector signed saturating unsigned extract narrow.
| SQCVTUN | SVE | Signed saturating unsigned extract narrow and interleave.
| SQCVTUN | SME | Multi-vector signed saturating unsigned extract narrow and interleave.
| SQDECB | SVE | Signed saturating decrement scalar by multiple of 8-bit predicate constraint element count.
| SQDECD (scalar) | SVE | Signed saturating decrement scalar by multiple of 64-bit predicate constraint element count.
| SQDECD (vector) | SVE | Signed saturating decrement vector by multiple of 64-bit predicate constraint element count.
| SQDECH (scalar) | SVE | Signed saturating decrement scalar by multiple of 16-bit predicate constraint element count.
| SQDECH (vector) | SVE | Signed saturating decrement vector by multiple of 16-bit predicate constraint element count.
| SQDECP (scalar) | SVE | Signed saturating decrement scalar by count of true predicate elements.
| SQDECP (vector) | SVE | Signed saturating decrement vector by count of true predicate elements.
| SQDECW (scalar) | SVE | Signed saturating decrement scalar by multiple of 32-bit predicate constraint element count.
| SQDECW (vector) | SVE | Signed saturating decrement vector by multiple of 32-bit predicate constraint element count.
| SQDMLAL | SIMD | Signed saturating doubling multiply-add long (by element).
| SQDMLAL | SIMD | Signed saturating doubling multiply-add long.
| SQDMLAL2 (by element) | SIMD | Signed saturating doubling multiply-add long (by element).
| SQDMLAL2 (vector) | SIMD | Signed saturating doubling multiply-add long.
| SQDMLALB (indexed) | SVE | Signed saturating doubling multiply-add long to accumulator (bottom, indexed).
| SQDMLALB (vectors) | SVE | Signed saturating doubling multiply-add long to accumulator (bottom).
| SQDMLALBT | SVE | Signed saturating doubling multiply-add long to accumulator (bottom × top).
| SQDMLALT (indexed) | SVE | Signed saturating doubling multiply-add long to accumulator (top, indexed).
| SQDMLALT (vectors) | SVE | Signed saturating doubling multiply-add long to accumulator (top).
| SQDMLSL | SIMD | Signed saturating doubling multiply-subtract long (by element).
| SQDMLSL | SIMD | Signed saturating doubling multiply-subtract long.
| SQDMLSL2 (by element) | SIMD | Signed saturating doubling multiply-subtract long (by element).
| SQDMLSL2 (vector) | SIMD | Signed saturating doubling multiply-subtract long.
| SQDMLSLB (indexed) | SVE | Signed saturating doubling multiply-subtract long from accumulator (bottom, indexed).
| SQDMLSLB (vectors) | SVE | Signed saturating doubling multiply-subtract long from accumulator (bottom).
| SQDMLSLBT | SVE | Signed saturating doubling multiply-subtract long from accumulator (bottom × top).
| SQDMLSLT (indexed) | SVE | Signed saturating doubling multiply-subtract long from accumulator (top, indexed).
| SQDMLSLT (vectors) | SVE | Signed saturating doubling multiply-subtract long from accumulator (top).
| SQDMULH (by element) | SIMD | Signed saturating doubling multiply returning high half (by element).
| SQDMULH (indexed) | SVE | Signed saturating doubling multiply high (indexed).
| SQDMULH (multiple and single vector) | SME | Multi-vector signed saturating doubling multiply high by vector.
| SQDMULH (multiple vectors) | SME | Multi-vector signed saturating doubling multiply high.
| SQDMULH (vector) | SIMD | Signed saturating doubling multiply returning high half.
| SQDMULH (vectors) | SVE | Signed saturating doubling multiply high (unpredicated).
| SQDMULL | SIMD | Signed saturating doubling multiply long (by element).
| SQDMULL | SIMD | Signed saturating doubling multiply long.
| SQDMULL2 (by element) | SIMD | Signed saturating doubling multiply long (by element).
| SQDMULL2 (vector) | SIMD | Signed saturating doubling multiply long.
| SQDMULLB (indexed) | SVE | Signed saturating doubling multiply long (bottom, indexed).
| SQDMULLB (vectors) | SVE | Signed saturating doubling multiply long (bottom).
| SQDMULLT (indexed) | SVE | Signed saturating doubling multiply long (top, indexed).
| SQDMULLT (vectors) | SVE | Signed saturating doubling multiply long (top).
| SQINCB | SVE | Signed saturating increment scalar by multiple of 8-bit predicate constraint element count.
| SQINCD (scalar) | SVE | Signed saturating increment scalar by multiple of 64-bit predicate constraint element count.
| SQINCD (vector) | SVE | Signed saturating increment vector by multiple of 64-bit predicate constraint element count.
| SQINCH (scalar) | SVE | Signed saturating increment scalar by multiple of 16-bit predicate constraint element count.
| SQINCH (vector) | SVE | Signed saturating increment vector by multiple of 16-bit predicate constraint element count.
| SQINCP (scalar) | SVE | Signed saturating increment scalar by count of true predicate elements.
| SQINCP (vector) | SVE | Signed saturating increment vector by count of true predicate elements.
| SQINCW (scalar) | SVE | Signed saturating increment scalar by multiple of 32-bit predicate constraint element count.
| SQINCW (vector) | SVE | Signed saturating increment vector by multiple of 32-bit predicate constraint element count.
| SQNEG | SIMD | Signed saturating negate.
| SQNEG | SVE | Signed saturating negate.
| SQRDCMLAH (indexed) | SVE | Saturating rounding doubling complex integer multiply-add high with rotate (indexed).
| SQRDCMLAH (vectors) | SVE | Saturating rounding doubling complex integer multiply-add high with rotate.
| SQRDMLAH (by element) | SIMD | Signed saturating rounding doubling multiply accumulate returning high half (by element).
| SQRDMLAH (indexed) | SVE | Signed saturating rounding doubling multiply-add high to accumulator (indexed).
| SQRDMLAH (vector) | SIMD | Signed saturating rounding doubling multiply accumulate returning high half (vector).
| SQRDMLAH (vectors) | SVE | Signed saturating rounding doubling multiply-add high to accumulator (unpredicated).
| SQRDMLSH (by element) | SIMD | Signed saturating rounding doubling multiply subtract returning high half (by element).
| SQRDMLSH (indexed) | SVE | Signed saturating rounding doubling multiply-subtract high from accumulator (indexed).
| SQRDMLSH (vector) | SIMD | Signed saturating rounding doubling multiply subtract returning high half (vector).
| SQRDMLSH (vectors) | SVE | Signed saturating rounding doubling multiply-subtract high from accumulator (unpredicated).
| SQRDMULH (by element) | SIMD | Signed saturating rounding doubling multiply returning high half (by element).
| SQRDMULH (indexed) | SVE | Signed saturating rounding doubling multiply high (indexed).
| SQRDMULH (vector) | SIMD | Signed saturating rounding doubling multiply returning high half.
| SQRDMULH (vectors) | SVE | Signed saturating rounding doubling multiply high (unpredicated).
| SQRSHL | SIMD | Signed saturating rounding shift left (register).
| SQRSHL | SVE | Signed saturating rounding shift left by vector (predicated).
| SQRSHLR | SVE | Signed saturating rounding shift left reversed vectors (predicated).
| SQRSHR (four registers) | SME | Multi-vector signed saturating rounding shift right narrow by immediate.
| SQRSHR (two registers) | SME | Multi-vector signed saturating rounding shift right narrow by immediate.
| SQRSHRN | SIMD | Signed saturating rounded shift right narrow (immediate).
| SQRSHRN | SVE | Signed saturating rounding shift right narrow by immediate and interleave.
| SQRSHRN | SME | Multi-vector signed saturating rounding shift right narrow by immediate and interleave.
| SQRSHRN2 | SIMD | Signed saturating rounded shift right narrow (immediate).
| SQRSHRNB | SVE | Signed saturating rounding shift right narrow by immediate (bottom).
| SQRSHRNT | SVE | Signed saturating rounding shift right narrow by immediate (top).
| SQRSHRU (four registers) | SME | Multi-vector signed saturating rounding shift right unsigned narrow by immediate.
| SQRSHRU (two registers) | SME | Multi-vector signed saturating rounding shift right unsigned narrow by immediate.
| SQRSHRUN | SIMD | Signed saturating rounded shift right unsigned narrow (immediate).
| SQRSHRUN | SVE | Signed saturating rounding shift right unsigned narrow by immediate and interleave.
| SQRSHRUN | SME | Multi-vector signed saturating rounding shift right unsigned narrow by immediate and interleave.
| SQRSHRUN2 | SIMD | Signed saturating rounded shift right unsigned narrow (immediate).
| SQRSHRUNB | SVE | Signed saturating rounding shift right unsigned narrow by immediate (bottom).
| SQRSHRUNT | SVE | Signed saturating rounding shift right unsigned narrow by immediate (top).
| SQSHL (immediate) | SIMD | Signed saturating shift left (immediate).
| SQSHL (immediate) | SVE | Signed saturating shift left by immediate.
| SQSHL (register) | SIMD | Signed saturating shift left (register).
| SQSHL (vectors) | SVE | Signed saturating shift left by vector (predicated).
| SQSHLR | SVE | Signed saturating shift left reversed vectors (predicated).
| SQSHLU | SIMD | Signed saturating shift left unsigned (immediate).
| SQSHLU | SVE | Signed saturating shift left unsigned by immediate.
| SQSHRN | SIMD | Signed saturating shift right narrow (immediate).
| SQSHRN2 | SIMD | Signed saturating shift right narrow (immediate).
| SQSHRNB | SVE | Signed saturating shift right narrow by immediate (bottom).
| SQSHRNT | SVE | Signed saturating shift right narrow by immediate (top).
| SQSHRUN | SIMD | Signed saturating shift right unsigned narrow (immediate).
| SQSHRUN2 | SIMD | Signed saturating shift right unsigned narrow (immediate).
| SQSHRUNB | SVE | Signed saturating shift right unsigned narrow by immediate (bottom).
| SQSHRUNT | SVE | Signed saturating shift right unsigned narrow by immediate (top).
| SQSUB | SIMD | Signed saturating subtract.
| SQSUB (immediate) | SVE | Signed saturating subtract immediate (unpredicated).
| SQSUB (vectors, predicated) | SVE | Signed saturating subtraction (predicated).
| SQSUB (vectors, unpredicated) | SVE | Signed saturating subtract vectors (unpredicated).
| SQSUBR | SVE | Signed saturating subtraction reversed vectors (predicated).
| SQXTN | SIMD | Signed saturating extract narrow.
| SQXTN2 | SIMD | Signed saturating extract narrow.
| SQXTNB | SVE | Signed saturating extract narrow (bottom).
| SQXTNT | SVE | Signed saturating extract narrow (top).
| SQXTUN | SIMD | Signed saturating extract unsigned narrow.
| SQXTUN2 | SIMD | Signed saturating extract unsigned narrow.
| SQXTUNB | SVE | Signed saturating unsigned extract narrow (bottom).
| SQXTUNT | SVE | Signed saturating unsigned extract narrow (top).
| SRHADD | SIMD | Signed rounding halving add.
| SRHADD | SVE | Signed rounding halving addition.
| SRI | SIMD | Shift right and insert (immediate).
| SRI | SVE | Shift right and insert (immediate).
| SRSHL | SIMD | Signed rounding shift left (register).
| SRSHL | SVE | Signed rounding shift left by vector (predicated).
| SRSHL (multiple and single vector) | SME | Multi-vector signed rounding shift left by vector.
| SRSHL (multiple vectors) | SME | Multi-vector signed rounding shift left.
| SRSHLR | SVE | Signed rounding shift left reversed vectors (predicated).
| SRSHR | SIMD | Signed rounding shift right (immediate).
| SRSHR | SVE | Signed rounding shift right by immediate.
| SRSRA | SIMD | Signed rounding shift right and accumulate (immediate).
| SRSRA | SVE | Signed rounding shift right and accumulate (immediate).
| SSBB | Base | Speculative store bypass barrier: an alias of DSB.
| SSHL | SIMD | Signed shift left (register).
| SSHLL | SIMD | Signed shift left long (immediate).
| SSHLL2 | SIMD | Signed shift left long (immediate).
| SSHLLB | SVE | Signed shift left long by immediate (bottom).
| SSHLLT | SVE | Signed shift left long by immediate (top).
| SSHR | SIMD | Signed shift right (immediate).
| SSRA | SIMD | Signed shift right and accumulate (immediate).
| SSRA | SVE | Signed shift right and accumulate (immediate).
| SSUBL | SIMD | Signed subtract long.
| SSUBL2 | SIMD | Signed subtract long.
| SSUBLB | SVE | Signed subtract long (bottom).
| SSUBLBT | SVE | Signed subtract long (bottom - top).
| SSUBLT | SVE | Signed subtract long (top).
| SSUBLTB | SVE | Signed subtract long (top - bottom).
| SSUBW | SIMD | Signed subtract wide.
| SSUBW2 | SIMD | Signed subtract wide.
| SSUBWB | SVE | Signed subtract wide (bottom).
| SSUBWT | SVE | Signed subtract wide (top).
| ST1 (multiple structures) | SIMD | Store multiple single-element structures from one, two, three, or four registers.
| ST1 (single structure) | SIMD | Store a single-element structure from one lane of one register.
| ST1B (scalar plus immediate, consecutive registers) | SVE | Contiguous store of bytes from multiple consecutive vectors (immediate index).
| ST1B (scalar plus immediate, single register) | SVE | Contiguous store bytes from vector (immediate index).
| ST1B (scalar plus immediate, strided registers) | SME | Contiguous store of bytes from multiple strided vectors (immediate index).
| ST1B (scalar plus scalar, consecutive registers) | SVE | Contiguous store of bytes from multiple consecutive vectors (scalar index).
| ST1B (scalar plus scalar, single register) | SVE | Contiguous store bytes from vector (scalar index).
| ST1B (scalar plus scalar, strided registers) | SME | Contiguous store of bytes from multiple strided vectors (scalar index).
| ST1B (scalar plus scalar, tile slice) | SME | Contiguous store of bytes from 8-bit element ZA tile slice.
| ST1B (scalar plus vector) | SVE | Scatter store bytes from a vector (vector index).
| ST1B (vector plus immediate) | SVE | Scatter store bytes from a vector (immediate index).
| ST1D (scalar plus immediate, consecutive registers) | SVE | Contiguous store of doublewords from multiple consecutive vectors (immediate index).
| ST1D (scalar plus immediate, single register) | SVE | Contiguous store doublewords from vector (immediate index).
| ST1D (scalar plus immediate, strided registers) | SME | Contiguous store of doublewords from multiple strided vectors (immediate index).
| ST1D (scalar plus scalar, consecutive registers) | SVE | Contiguous store of doublewords from multiple consecutive vectors (scalar index).
| ST1D (scalar plus scalar, single register) | SVE | Contiguous store doublewords from vector (scalar index).
| ST1D (scalar plus scalar, strided registers) | SME | Contiguous store of doublewords from multiple strided vectors (scalar index).
| ST1D (scalar plus scalar, tile slice) | SME | Contiguous store of doublewords from 64-bit element ZA tile slice.
| ST1D (scalar plus vector) | SVE | Scatter store doublewords from a vector (vector index).
| ST1D (vector plus immediate) | SVE | Scatter store doublewords from a vector (immediate index).
| ST1H (scalar plus immediate, consecutive registers) | SVE | Contiguous store of halfwords from multiple consecutive vectors (immediate index).
| ST1H (scalar plus immediate, single register) | SVE | Contiguous store halfwords from vector (immediate index).
| ST1H (scalar plus immediate, strided registers) | SME | Contiguous store of halfwords from multiple strided vectors (immediate index).
| ST1H (scalar plus scalar, consecutive registers) | SVE | Contiguous store of halfwords from multiple consecutive vectors (scalar index).
| ST1H (scalar plus scalar, single register) | SVE | Contiguous store halfwords from vector (scalar index).
| ST1H (scalar plus scalar, strided registers) | SME | Contiguous store of halfwords from multiple strided vectors (scalar index).
| ST1H (scalar plus scalar, tile slice) | SME | Contiguous store of halfwords from 16-bit element ZA tile slice.
| ST1H (scalar plus vector) | SVE | Scatter store halfwords from a vector (vector index).
| ST1H (vector plus immediate) | SVE | Scatter store halfwords from a vector (immediate index).
| ST1Q | SVE | Scatter store quadwords.
| ST1Q | SME | Contiguous store of quadwords from 128-bit element ZA tile slice.
| ST1W (scalar plus immediate, consecutive registers) | SVE | Contiguous store of words from multiple consecutive vectors (immediate index).
| ST1W (scalar plus immediate, single register) | SVE | Contiguous store words from vector (immediate index).
| ST1W (scalar plus immediate, strided registers) | SME | Contiguous store of words from multiple strided vectors (immediate index).
| ST1W (scalar plus scalar, consecutive registers) | SVE | Contiguous store of words from multiple consecutive vectors (scalar index).
| ST1W (scalar plus scalar, single register) | SVE | Contiguous store words from vector (scalar index).
| ST1W (scalar plus scalar, strided registers) | SME | Contiguous store of words from multiple strided vectors (scalar index).
| ST1W (scalar plus scalar, tile slice) | SME | Contiguous store of words from 32-bit element ZA tile slice.
| ST1W (scalar plus vector) | SVE | Scatter store words from a vector (vector index).
| ST1W (vector plus immediate) | SVE | Scatter store words from a vector (immediate index).
| ST2 (multiple structures) | SIMD | Store multiple 2-element structures from two registers.
| ST2 (single structure) | SIMD | Store single 2-element structure from one lane of two registers.
| ST2B (scalar plus immediate) | SVE | Contiguous store two-byte structures from two vectors (immediate index).
| ST2B (scalar plus scalar) | SVE | Contiguous store two-byte structures from two vectors (scalar index).
| ST2D (scalar plus immediate) | SVE | Contiguous store two-doubleword structures from two vectors (immediate index).
| ST2D (scalar plus scalar) | SVE | Contiguous store two-doubleword structures from two vectors (scalar index).
| ST2G | Base | Store Allocation Tags.
| ST2H (scalar plus immediate) | SVE | Contiguous store two-halfword structures from two vectors (immediate index).
| ST2H (scalar plus scalar) | SVE | Contiguous store two-halfword structures from two vectors (scalar index).
| ST2Q (scalar plus immediate) | SVE | Contiguous store two-quadword structures from two vectors (immediate index).
| ST2Q (scalar plus scalar) | SVE | Contiguous store two-quadword structures from two vectors (scalar index).
| ST2W (scalar plus immediate) | SVE | Contiguous store two-word structures from two vectors (immediate index).
| ST2W (scalar plus scalar) | SVE | Contiguous store two-word structures from two vectors (scalar index).
| ST3 (multiple structures) | SIMD | Store multiple 3-element structures from three registers.
| ST3 (single structure) | SIMD | Store single 3-element structure from one lane of three registers.
| ST3B (scalar plus immediate) | SVE | Contiguous store three-byte structures from three vectors (immediate index).
| ST3B (scalar plus scalar) | SVE | Contiguous store three-byte structures from three vectors (scalar index).
| ST3D (scalar plus immediate) | SVE | Contiguous store three-doubleword structures from three vectors (immediate index).
| ST3D (scalar plus scalar) | SVE | Contiguous store three-doubleword structures from three vectors (scalar index).
| ST3H (scalar plus immediate) | SVE | Contiguous store three-halfword structures from three vectors (immediate index).
| ST3H (scalar plus scalar) | SVE | Contiguous store three-halfword structures from three vectors (scalar index).
| ST3Q (scalar plus immediate) | SVE | Contiguous store three-quadword structures from three vectors (immediate index).
| ST3Q (scalar plus scalar) | SVE | Contiguous store three-quadword structures from three vectors (scalar index).
| ST3W (scalar plus immediate) | SVE | Contiguous store three-word structures from three vectors (immediate index).
| ST3W (scalar plus scalar) | SVE | Contiguous store three-word structures from three vectors (scalar index).
| ST4 (multiple structures) | SIMD | Store multiple 4-element structures from four registers.
| ST4 (single structure) | SIMD | Store single 4-element structure from one lane of four registers.
| ST4B (scalar plus immediate) | SVE | Contiguous store four-byte structures from four vectors (immediate index).
| ST4B (scalar plus scalar) | SVE | Contiguous store four-byte structures from four vectors (scalar index).
| ST4D (scalar plus immediate) | SVE | Contiguous store four-doubleword structures from four vectors (immediate index).
| ST4D (scalar plus scalar) | SVE | Contiguous store four-doubleword structures from four vectors (scalar index).
| ST4H (scalar plus immediate) | SVE | Contiguous store four-halfword structures from four vectors (immediate index).
| ST4H (scalar plus scalar) | SVE | Contiguous store four-halfword structures from four vectors (scalar index).
| ST4Q (scalar plus immediate) | SVE | Contiguous store four-quadword structures from four vectors (immediate index).
| ST4Q (scalar plus scalar) | SVE | Contiguous store four-quadword structures from four vectors (scalar index).
| ST4W (scalar plus immediate) | SVE | Contiguous store four-word structures from four vectors (immediate index).
| ST4W (scalar plus scalar) | SVE | Contiguous store four-word structures from four vectors (scalar index).
| ST64B | Base | Single-copy atomic 64-byte store without status result.
| ST64BV | Base | Single-copy atomic 64-byte store with status result.
| ST64BV0 | Base | Single-copy atomic 64-byte EL0 store with status result.
| STADD | Base | Atomic add on word or doubleword in memory, without return: an alias of LDADD, LDADDA, LDADDAL, LDADDL.
| STADDB | Base | Atomic add on byte in memory, without return: an alias of LDADDB, LDADDAB, LDADDALB, LDADDLB.
| STADDH | Base | Atomic add on halfword in memory, without return: an alias of LDADDH, LDADDAH, LDADDALH, LDADDLH.
| STADDL | Base | Atomic add on word or doubleword in memory, without return: an alias of LDADD, LDADDA, LDADDAL, LDADDL.
| STADDLB | Base | Atomic add on byte in memory, without return: an alias of LDADDB, LDADDAB, LDADDALB, LDADDLB.
| STADDLH | Base | Atomic add on halfword in memory, without return: an alias of LDADDH, LDADDAH, LDADDALH, LDADDLH.
| STBFADD | SIMD | BFloat16 floating-point atomic add in memory, without return.
| STBFADDL | SIMD | BFloat16 floating-point atomic add in memory, without return.
| STBFMAX | SIMD | BFloat16 floating-point atomic maximum in memory, without return.
| STBFMAXL | SIMD | BFloat16 floating-point atomic maximum in memory, without return.
| STBFMAXNM | SIMD | BFloat16 floating-point atomic maximum number in memory, without return.
| STBFMAXNML | SIMD | BFloat16 floating-point atomic maximum number in memory, without return.
| STBFMIN | SIMD | BFloat16 floating-point atomic minimum in memory, without return.
| STBFMINL | SIMD | BFloat16 floating-point atomic minimum in memory, without return.
| STBFMINNM | SIMD | BFloat16 floating-point atomic minimum number in memory, without return.
| STBFMINNML | SIMD | BFloat16 floating-point atomic minimum number in memory, without return.
| STCLR | Base | Atomic bit clear on word or doubleword in memory, without return: an alias of LDCLR, LDCLRA, LDCLRAL, LDCLRL.
| STCLRB | Base | Atomic bit clear on byte in memory, without return: an alias of LDCLRB, LDCLRAB, LDCLRALB, LDCLRLB.
| STCLRH | Base | Atomic bit clear on halfword in memory, without return: an alias of LDCLRH, LDCLRAH, LDCLRALH, LDCLRLH.
| STCLRL | Base | Atomic bit clear on word or doubleword in memory, without return: an alias of LDCLR, LDCLRA, LDCLRAL, LDCLRL.
| STCLRLB | Base | Atomic bit clear on byte in memory, without return: an alias of LDCLRB, LDCLRAB, LDCLRALB, LDCLRLB.
| STCLRLH | Base | Atomic bit clear on halfword in memory, without return: an alias of LDCLRH, LDCLRAH, LDCLRALH, LDCLRLH.
| STEOR | Base | Atomic exclusive-OR on word or doubleword in memory, without return: an alias of LDEOR, LDEORA, LDEORAL, LDEORL.
| STEORB | Base | Atomic exclusive-OR on byte in memory, without return: an alias of LDEORB, LDEORAB, LDEORALB, LDEORLB.
| STEORH | Base | Atomic exclusive-OR on halfword in memory, without return: an alias of LDEORH, LDEORAH, LDEORALH, LDEORLH.
| STEORL | Base | Atomic exclusive-OR on word or doubleword in memory, without return: an alias of LDEOR, LDEORA, LDEORAL, LDEORL.
| STEORLB | Base | Atomic exclusive-OR on byte in memory, without return: an alias of LDEORB, LDEORAB, LDEORALB, LDEORLB.
| STEORLH | Base | Atomic exclusive-OR on halfword in memory, without return: an alias of LDEORH, LDEORAH, LDEORALH, LDEORLH.
| STFADD | SIMD | Floating-point atomic add in memory, without return.
| STFADDL | SIMD | Floating-point atomic add in memory, without return.
| STFMAX | SIMD | Floating-point atomic maximum in memory, without return.
| STFMAXL | SIMD | Floating-point atomic maximum in memory, without return.
| STFMAXNM | SIMD | Floating-point atomic maximum number in memory, without return.
| STFMAXNML | SIMD | Floating-point atomic maximum number in memory, without return.
| STFMIN | SIMD | Floating-point atomic minimum in memory, without return.
| STFMINL | SIMD | Floating-point atomic minimum in memory, without return.
| STFMINNM | SIMD | Floating-point atomic minimum number in memory, without return.
| STFMINNML | SIMD | Floating-point atomic minimum number in memory, without return.
| STG | Base | Store Allocation Tag.
| STGM | Base | Store Allocation Tag multiple.
| STGP | Base | Store Allocation Tag and pair of registers.
| STILP | Base | Store-release ordered pair of registers.
| STL1 (SIMD&FP) | SIMD | Store-release a single-element structure from one lane of one register.
| STLLR | Base | Store LORelease register.
| STLLRB | Base | Store LORelease register byte.
| STLLRH | Base | Store LORelease register halfword.
| STLR | Base | Store-release register.
| STLRB | Base | Store-release register byte.
| STLRH | Base | Store-release register halfword.
| STLTXR | Base | Store-release unprivileged exclusive register.
| STLUR | Base | Store-release register (unscaled).
| STLUR (SIMD&FP) | SIMD | Store-release SIMD&FP register (unscaled offset).
| STLURB | Base | Store-release register byte (unscaled).
| STLURH | Base | Store-release register halfword (unscaled).
| STLXP | Base | Store-release exclusive pair of registers.
| STLXR | Base | Store-release exclusive register.
| STLXRB | Base | Store-release exclusive register byte.
| STLXRH | Base | Store-release exclusive register halfword.
| STMOPA (2-way) | SME | Signed integer sparse sum of two outer products, accumulating.
| STMOPA (4-way) | SME | Signed integer sparse sum of four outer products, accumulating.
| STNP | Base | Store pair of registers, with non-temporal hint.
| STNP (SIMD&FP) | SIMD | Store pair of SIMD&FP registers, with non-temporal hint.
| STNT1B (scalar plus immediate, consecutive registers) | SVE | Contiguous store non-temporal of bytes from multiple consecutive vectors (immediate index).
| STNT1B (scalar plus immediate, single register) | SVE | Contiguous store non-temporal bytes from vector (immediate index).
| STNT1B (scalar plus immediate, strided registers) | SME | Contiguous store non-temporal of bytes from multiple strided vectors (immediate index).
| STNT1B (scalar plus scalar, consecutive registers) | SVE | Contiguous store non-temporal of bytes from multiple consecutive vectors (scalar index).
| STNT1B (scalar plus scalar, single register) | SVE | Contiguous store non-temporal bytes from vector (scalar index).
| STNT1B (scalar plus scalar, strided registers) | SME | Contiguous store non-temporal of bytes from multiple strided vectors (scalar index).
| STNT1B (vector plus scalar) | SVE | Scatter store non-temporal bytes.
| STNT1D (scalar plus immediate, consecutive registers) | SVE | Contiguous store non-temporal of doublewords from multiple consecutive vectors (immediate index).
| STNT1D (scalar plus immediate, single register) | SVE | Contiguous store non-temporal doublewords from vector (immediate index).
| STNT1D (scalar plus immediate, strided registers) | SME | Contiguous store non-temporal of doublewords from multiple strided vectors (immediate index).
| STNT1D (scalar plus scalar, consecutive registers) | SVE | Contiguous store non-temporal of doublewords from multiple consecutive vectors (scalar index).
| STNT1D (scalar plus scalar, single register) | SVE | Contiguous store non-temporal doublewords from vector (scalar index).
| STNT1D (scalar plus scalar, strided registers) | SME | Contiguous store non-temporal of doublewords from multiple strided vectors (scalar index).
| STNT1D (vector plus scalar) | SVE | Scatter store non-temporal doublewords.
| STNT1H (scalar plus immediate, consecutive registers) | SVE | Contiguous store non-temporal of halfwords from multiple consecutive vectors (immediate index).
| STNT1H (scalar plus immediate, single register) | SVE | Contiguous store non-temporal halfwords from vector (immediate index).
| STNT1H (scalar plus immediate, strided registers) | SME | Contiguous store non-temporal of halfwords from multiple strided vectors (immediate index).
| STNT1H (scalar plus scalar, consecutive registers) | SVE | Contiguous store non-temporal of halfwords from multiple consecutive vectors (scalar index).
| STNT1H (scalar plus scalar, single register) | SVE | Contiguous store non-temporal halfwords from vector (scalar index).
| STNT1H (scalar plus scalar, strided registers) | SME | Contiguous store non-temporal of halfwords from multiple strided vectors (scalar index).
| STNT1H (vector plus scalar) | SVE | Scatter store non-temporal halfwords.
| STNT1W (scalar plus immediate, consecutive registers) | SVE | Contiguous store non-temporal of words from multiple consecutive vectors (immediate index).
| STNT1W (scalar plus immediate, single register) | SVE | Contiguous store non-temporal words from vector (immediate index).
| STNT1W (scalar plus immediate, strided registers) | SME | Contiguous store non-temporal of words from multiple strided vectors (immediate index).
| STNT1W (scalar plus scalar, consecutive registers) | SVE | Contiguous store non-temporal of words from multiple consecutive vectors (scalar index).
| STNT1W (scalar plus scalar, single register) | SVE | Contiguous store non-temporal words from vector (scalar index).
| STNT1W (scalar plus scalar, strided registers) | SME | Contiguous store non-temporal of words from multiple strided vectors (scalar index).
| STNT1W (vector plus scalar) | SVE | Scatter store non-temporal words.
| STP | Base | Store pair of registers.
| STP (SIMD&FP) | SIMD | Store pair of SIMD&FP registers.
| STR (array vector) | SME | Store ZA array vector.
| STR (immediate) | Base | Store register (immediate).
| STR (immediate, SIMD&FP) | SIMD | Store SIMD&FP register (immediate offset).
| STR (predicate) | SVE | Store predicate register.
| STR (register) | Base | Store register (register).
| STR (register, SIMD&FP) | SIMD | Store SIMD&FP register (register offset).
| STR (table) | SME | Store ZT0 register.
| STR (vector) | SVE | Store vector register.
| STRB (immediate) | Base | Store register byte (immediate).
| STRB (register) | Base | Store register byte (register).
| STRH (immediate) | Base | Store register halfword (immediate).
| STRH (register) | Base | Store register halfword (register).
| STSET | Base | Atomic bit set on word or doubleword in memory, without return: an alias of LDSET, LDSETA, LDSETAL, LDSETL.
| STSETB | Base | Atomic bit set on byte in memory, without return: an alias of LDSETB, LDSETAB, LDSETALB, LDSETLB.
| STSETH | Base | Atomic bit set on halfword in memory, without return: an alias of LDSETH, LDSETAH, LDSETALH, LDSETLH.
| STSETL | Base | Atomic bit set on word or doubleword in memory, without return: an alias of LDSET, LDSETA, LDSETAL, LDSETL.
| STSETLB | Base | Atomic bit set on byte in memory, without return: an alias of LDSETB, LDSETAB, LDSETALB, LDSETLB.
| STSETLH | Base | Atomic bit set on halfword in memory, without return: an alias of LDSETH, LDSETAH, LDSETALH, LDSETLH.
| STSHH | Base | Store shared hint.
| STSMAX | Base | Atomic signed maximum on word or doubleword in memory, without return: an alias of LDSMAX, LDSMAXA, LDSMAXAL, LDSMAXL.
| STSMAXB | Base | Atomic signed maximum on byte in memory, without return: an alias of LDSMAXB, LDSMAXAB, LDSMAXALB, LDSMAXLB.
| STSMAXH | Base | Atomic signed maximum on halfword in memory, without return: an alias of LDSMAXH, LDSMAXAH, LDSMAXALH, LDSMAXLH.
| STSMAXL | Base | Atomic signed maximum on word or doubleword in memory, without return: an alias of LDSMAX, LDSMAXA, LDSMAXAL, LDSMAXL.
| STSMAXLB | Base | Atomic signed maximum on byte in memory, without return: an alias of LDSMAXB, LDSMAXAB, LDSMAXALB, LDSMAXLB.
| STSMAXLH | Base | Atomic signed maximum on halfword in memory, without return: an alias of LDSMAXH, LDSMAXAH, LDSMAXALH, LDSMAXLH.
| STSMIN | Base | Atomic signed minimum on word or doubleword in memory, without return: an alias of LDSMIN, LDSMINA, LDSMINAL, LDSMINL.
| STSMINB | Base | Atomic signed minimum on byte in memory, without return: an alias of LDSMINB, LDSMINAB, LDSMINALB, LDSMINLB.
| STSMINH | Base | Atomic signed minimum on halfword in memory, without return: an alias of LDSMINH, LDSMINAH, LDSMINALH, LDSMINLH.
| STSMINL | Base | Atomic signed minimum on word or doubleword in memory, without return: an alias of LDSMIN, LDSMINA, LDSMINAL, LDSMINL.
| STSMINLB | Base | Atomic signed minimum on byte in memory, without return: an alias of LDSMINB, LDSMINAB, LDSMINALB, LDSMINLB.
| STSMINLH | Base | Atomic signed minimum on halfword in memory, without return: an alias of LDSMINH, LDSMINAH, LDSMINALH, LDSMINLH.
| STTADD | Base | Atomic add unprivileged, without return: an alias of LDTADD, LDTADDA, LDTADDAL, LDTADDL.
| STTADDL | Base | Atomic add unprivileged, without return: an alias of LDTADD, LDTADDA, LDTADDAL, LDTADDL.
| STTCLR | Base | Atomic bit clear unprivileged, without return: an alias of LDTCLR, LDTCLRA, LDTCLRAL, LDTCLRL.
| STTCLRL | Base | Atomic bit clear unprivileged, without return: an alias of LDTCLR, LDTCLRA, LDTCLRAL, LDTCLRL.
| STTNP | Base | Store unprivileged pair of registers, with non-temporal hint.
| STTNP (SIMD&FP) | SIMD | Store unprivileged pair of SIMD&FP registers, with non-temporal hint.
| STTP | Base | Store unprivileged pair of registers.
| STTP (SIMD&FP) | SIMD | Store unprivileged pair of SIMD&FP registers.
| STTR | Base | Store register (unprivileged).
| STTRB | Base | Store register byte (unprivileged).
| STTRH | Base | Store register halfword (unprivileged).
| STTSET | Base | Atomic bit set unprivileged, without return: an alias of LDTSET, LDTSETA, LDTSETAL, LDTSETL.
| STTSETL | Base | Atomic bit set unprivileged, without return: an alias of LDTSET, LDTSETA, LDTSETAL, LDTSETL.
| STTXR | Base | Store unprivileged exclusive register.
| STUMAX | Base | Atomic unsigned maximum on word or doubleword in memory, without return: an alias of LDUMAX, LDUMAXA, LDUMAXAL, LDUMAXL.
| STUMAXB | Base | Atomic unsigned maximum on byte in memory, without return: an alias of LDUMAXB, LDUMAXAB, LDUMAXALB, LDUMAXLB.
| STUMAXH | Base | Atomic unsigned maximum on halfword in memory, without return: an alias of LDUMAXH, LDUMAXAH, LDUMAXALH, LDUMAXLH.
| STUMAXL | Base | Atomic unsigned maximum on word or doubleword in memory, without return: an alias of LDUMAX, LDUMAXA, LDUMAXAL, LDUMAXL.
| STUMAXLB | Base | Atomic unsigned maximum on byte in memory, without return: an alias of LDUMAXB, LDUMAXAB, LDUMAXALB, LDUMAXLB.
| STUMAXLH | Base | Atomic unsigned maximum on halfword in memory, without return: an alias of LDUMAXH, LDUMAXAH, LDUMAXALH, LDUMAXLH.
| STUMIN | Base | Atomic unsigned minimum on word or doubleword in memory, without return: an alias of LDUMIN, LDUMINA, LDUMINAL, LDUMINL.
| STUMINB | Base | Atomic unsigned minimum on byte in memory, without return: an alias of LDUMINB, LDUMINAB, LDUMINALB, LDUMINLB.
| STUMINH | Base | Atomic unsigned minimum on halfword in memory, without return: an alias of LDUMINH, LDUMINAH, LDUMINALH, LDUMINLH.
| STUMINL | Base | Atomic unsigned minimum on word or doubleword in memory, without return: an alias of LDUMIN, LDUMINA, LDUMINAL, LDUMINL.
| STUMINLB | Base | Atomic unsigned minimum on byte in memory, without return: an alias of LDUMINB, LDUMINAB, LDUMINALB, LDUMINLB.
| STUMINLH | Base | Atomic unsigned minimum on halfword in memory, without return: an alias of LDUMINH, LDUMINAH, LDUMINALH, LDUMINLH.
| STUR | Base | Store register (unscaled).
| STUR (SIMD&FP) | SIMD | Store SIMD&FP register (unscaled offset).
| STURB | Base | Store register byte (unscaled).
| STURH | Base | Store register halfword (unscaled).
| STXP | Base | Store exclusive pair of registers.
| STXR | Base | Store exclusive register.
| STXRB | Base | Store exclusive register byte.
| STXRH | Base | Store exclusive register halfword.
| STZ2G | Base | Store Allocation Tags, zeroing.
| STZG | Base | Store Allocation Tag, zeroing.
| STZGM | Base | Store Allocation Tag and zero multiple.
| SUB (array accumulators) | SME | Subtract multi-vector from ZA array vector accumulators.
| SUB (array results, multiple and single vector) | SME | Subtract replicated single vector from multi-vector with ZA array vector results.
| SUB (array results, multiple vectors) | SME | Subtract multi-vector from multi-vector with ZA array vector results.
| SUB (extended register) | Base | Subtract extended and scaled register.
| SUB (immediate) | Base | Subtract immediate value.
| SUB (immediate) | SVE | Subtract immediate (unpredicated).
| SUB (shifted register) | Base | Subtract optionally-shifted register.
| SUB (vector) | SIMD | Subtract (vector).
| SUB (vectors, predicated) | SVE | Subtract vectors (predicated).
| SUB (vectors, unpredicated) | SVE | Subtract vectors (unpredicated).
| SUBG | Base | Subtract with tag.
| SUBHN | SIMD | Subtract returning high narrow.
| SUBHN2 | SIMD | Subtract returning high narrow.
| SUBHNB | SVE | Subtract narrow high part (bottom).
| SUBHNT | SVE | Subtract narrow high part (top).
| SUBP | Base | Subtract pointer.
| SUBPS | Base | Subtract pointer, setting flags.
| SUBPT | Base | Subtract checked pointer.
| SUBPT (predicated) | SVE | Subtract checked pointer vectors (predicated).
| SUBPT (unpredicated) | SVE | Subtract checked pointer vectors (unpredicated).
| SUBR (immediate) | SVE | Reversed subtract from immediate (unpredicated).
| SUBR (vectors) | SVE | Reversed subtract vectors (predicated).
| SUBS (extended register) | Base | Subtract extended and scaled register, setting flags.
| SUBS (immediate) | Base | Subtract immediate value, setting flags.
| SUBS (shifted register) | Base | Subtract optionally-shifted register, setting flags.
| SUDOT | SVE | Signed by unsigned integer indexed dot product.
| SUDOT (by element) | SIMD | Dot product with signed and unsigned integers (vector, by element).
| SUDOT (multiple and indexed vector) | SME | Multi-vector signed by unsigned integer dot-product by indexed elements.
| SUDOT (multiple and single vector) | SME | Multi-vector signed by unsigned integer dot-product by vector.
| SUMLALL (multiple and indexed vector) | SME | Multi-vector signed by unsigned integer multiply-add long-long by indexed element.
| SUMLALL (multiple and single vector) | SME | Multi-vector signed by unsigned integer multiply-add long-long by vector.
| SUMOP4A | SME | Signed by unsigned integer quarter-tile sums of four outer products, accumulating.
| SUMOP4S | SME | Signed by unsigned integer quarter-tile sums of four outer products, subtracting.
| SUMOPA | SME | Signed by unsigned integer sum of outer products and accumulate.
| SUMOPS | SME | Signed by unsigned integer sum of outer products and subtract.
| SUNPK | SME | Unpack and sign-extend multi-vector elements.
| SUNPKHI | SVE | Signed unpack and extend half of vector.
| SUNPKLO | SVE | Signed unpack and extend half of vector.
| SUQADD | SIMD | Signed saturating accumulate of unsigned value.
| SUQADD | SVE | Signed saturating addition of unsigned value.
| SUTMOPA | SME | Signed by unsigned integer sparse sum of four outer products, accumulating.
| SUVDOT | SME | Multi-vector signed by unsigned integer vertical dot-product by indexed element.
| SVC | Base | Supervisor call.
| SVDOT (2-way) | SME | Multi-vector signed integer vertical dot-product by indexed element.
| SVDOT (4-way) | SME | Multi-vector signed integer vertical dot-product by indexed element.
| SWP | Base | Swap word or doubleword in memory.
| SWPA | Base | Swap word or doubleword in memory.
| SWPAB | Base | Swap byte in memory.
| SWPAH | Base | Swap halfword in memory.
| SWPAL | Base | Swap word or doubleword in memory.
| SWPALB | Base | Swap byte in memory.
| SWPALH | Base | Swap halfword in memory.
| SWPB | Base | Swap byte in memory.
| SWPH | Base | Swap halfword in memory.
| SWPL | Base | Swap word or doubleword in memory.
| SWPLB | Base | Swap byte in memory.
| SWPLH | Base | Swap halfword in memory.
| SWPP | Base | Swap quadword in memory.
| SWPPA | Base | Swap quadword in memory.
| SWPPAL | Base | Swap quadword in memory.
| SWPPL | Base | Swap quadword in memory.
| SWPT | Base | Swap unprivileged.
| SWPTA | Base | Swap unprivileged.
| SWPTAL | Base | Swap unprivileged.
| SWPTL | Base | Swap unprivileged.
| SXTB | Base | Signed extend byte: an alias of SBFM.
| SXTB | SVE | Signed byte / halfword / word extend (predicated).
| SXTH | Base | Sign extend halfword: an alias of SBFM.
| SXTH | SVE | Signed byte / halfword / word extend (predicated).
| SXTL | SIMD | Signed extend long: an alias of SSHLL, SSHLL2.
| SXTL2 | SIMD | Signed extend long: an alias of SSHLL, SSHLL2.
| SXTW | Base | Sign extend word: an alias of SBFM.
| SXTW | SVE | Signed byte / halfword / word extend (predicated).
| SYS | Base | System instruction.
| SYSL | Base | System instruction with result.
| SYSP | Base | 128-bit system instruction.
| TBL | SIMD | Table vector lookup.
| TBL | SVE | Programmable table lookup in one or two vector table (zeroing).
| TBLQ | SVE | Programmable table lookup within each quadword vector segment (zeroing).
| TBNZ | Base | Test bit and branch if nonzero.
| TBX | SIMD | Table vector lookup extension.
| TBX | SVE | Programmable table lookup in single vector table (merging).
| TBXQ | SVE | Programmable table lookup within each quadword vector segment (merging).
| TBZ | Base | Test bit and branch if zero.
| TCANCEL | Base | Cancel current transaction.
| TCOMMIT | Base | Commit current transaction.
| TLBI | Base | TLB invalidate operation: an alias of SYS.
| TLBIP | Base | TLB invalidate pair operation: an alias of SYSP.
| TRCIT | Base | Trace instrumentation: an alias of SYS.
| TRN1 | SIMD | Transpose vectors (primary).
| TRN1 | SVE | Interleave even or odd elements from two predicates.
| TRN1 | SVE | Interleave even or odd elements from two vectors.
| TRN2 | SIMD | Transpose vectors (secondary).
| TRN2 (predicates) | SVE | Interleave even or odd elements from two predicates.
| TRN2 (vectors) | SVE | Interleave even or odd elements from two vectors.
| TSB | Base | Trace synchronization barrier.
| TST (immediate) | Base | Test bits (immediate): an alias of ANDS (immediate).
| TST (shifted register) | Base | Test (shifted register): an alias of ANDS (shifted register).
| TSTART | Base | Start transaction.
| TTEST | Base | Test transaction state.
| UABA | SIMD | Unsigned absolute difference and accumulate.
| UABA | SVE | Unsigned absolute difference and accumulate.
| UABAL | SIMD | Unsigned absolute difference and accumulate long.
| UABAL2 | SIMD | Unsigned absolute difference and accumulate long.
| UABALB | SVE | Unsigned absolute difference and accumulate long (bottom).
| UABALT | SVE | Unsigned absolute difference and accumulate long (top).
| UABD | SIMD | Unsigned absolute difference (vector).
| UABD | SVE | Unsigned absolute difference (predicated).
| UABDL | SIMD | Unsigned absolute difference long.
| UABDL2 | SIMD | Unsigned absolute difference long.
| UABDLB | SVE | Unsigned absolute difference long (bottom).
| UABDLT | SVE | Unsigned absolute difference long (top).
| UADALP | SIMD | Unsigned add and accumulate long pairwise.
| UADALP | SVE | Unsigned add and accumulate long pairwise.
| UADDL | SIMD | Unsigned add long (vector).
| UADDL2 | SIMD | Unsigned add long (vector).
| UADDLB | SVE | Unsigned add long (bottom).
| UADDLP | SIMD | Unsigned add long pairwise.
| UADDLT | SVE | Unsigned add long (top).
| UADDLV | SIMD | Unsigned sum long across vector.
| UADDV | SVE | Unsigned add reduction to scalar.
| UADDW | SIMD | Unsigned add wide.
| UADDW2 | SIMD | Unsigned add wide.
| UADDWB | SVE | Unsigned add wide (bottom).
| UADDWT | SVE | Unsigned add wide (top).
| UBFIZ | Base | Unsigned bitfield insert in zeros: an alias of UBFM.
| UBFM | Base | Unsigned bitfield move.
| UBFX | Base | Unsigned bitfield extract: an alias of UBFM.
| UCLAMP | SVE | Unsigned clamp to minimum/maximum vector.
| UCLAMP | SME | Multi-vector unsigned clamp to minimum/maximum vector.
| UCVTF | SVE | Unsigned integer convert to floating-point (predicated).
| UCVTF | SME | Multi-vector unsigned integer convert to floating-point.
| UCVTF (scalar SIMD&FP) | SIMD | Unsigned integer convert to floating-point (scalar SIMD&FP).
| UCVTF (scalar, fixed-point) | SIMD | Unsigned fixed-point convert to floating-point (scalar).
| UCVTF (scalar, integer) | SIMD | Unsigned integer convert to floating-point (scalar).
| UCVTF (vector, fixed-point) | SIMD | Unsigned fixed-point convert to floating-point (vector).
| UCVTF (vector, integer) | SIMD | Unsigned integer convert to floating-point (vector).
| UDF | Base | Permanently undefined.
| UDIV | Base | Unsigned divide.
| UDIV | SVE | Unsigned divide (predicated).
| UDIVR | SVE | Unsigned reversed divide (predicated).
| UDOT (2-way, indexed) | SVE | Unsigned integer indexed dot product.
| UDOT (2-way, multiple and indexed vector) | SME | Multi-vector unsigned integer dot-product by indexed element.
| UDOT (2-way, multiple and single vector) | SME | Multi-vector unsigned integer dot-product by vector.
| UDOT (2-way, multiple vectors) | SME | Multi-vector unsigned integer dot-product.
| UDOT (2-way, vectors) | SVE | Unsigned integer dot product.
| UDOT (4-way, indexed) | SVE | Unsigned integer indexed dot product.
| UDOT (4-way, multiple and indexed vector) | SME | Multi-vector unsigned integer dot-product by indexed element.
| UDOT (4-way, multiple and single vector) | SME | Multi-vector unsigned integer dot-product by vector.
| UDOT (4-way, multiple vectors) | SME | Multi-vector unsigned integer dot-product.
| UDOT (4-way, vectors) | SVE | Unsigned integer dot product.
| UDOT (by element) | SIMD | Dot product unsigned arithmetic (vector, by element).
| UDOT (vector) | SIMD | Dot product unsigned arithmetic (vector).
| UHADD | SIMD | Unsigned halving add.
| UHADD | SVE | Unsigned halving addition.
| UHSUB | SIMD | Unsigned halving subtract.
| UHSUB | SVE | Unsigned halving subtract.
| UHSUBR | SVE | Unsigned halving subtract reversed vectors.
| UMADDL | Base | Unsigned multiply-add long.
| UMAX | SIMD | Unsigned maximum (vector).
| UMAX (immediate) | Base | Unsigned maximum (immediate).
| UMAX (immediate) | SVE | Unsigned maximum with immediate (unpredicated).
| UMAX (multiple and single vector) | SME | Multi-vector unsigned maximum by vector.
| UMAX (multiple vectors) | SME | Multi-vector unsigned maximum.
| UMAX (register) | Base | Unsigned maximum (register).
| UMAX (vectors) | SVE | Unsigned maximum vectors (predicated).
| UMAXP | SIMD | Unsigned maximum pairwise.
| UMAXP | SVE | Unsigned maximum pairwise.
| UMAXQV | SVE | Unsigned maximum reduction of quadword vector segments.
| UMAXV | SIMD | Unsigned maximum across vector.
| UMAXV | SVE | Unsigned maximum reduction to scalar.
| UMIN | SIMD | Unsigned minimum (vector).
| UMIN (immediate) | Base | Unsigned minimum (immediate).
| UMIN (immediate) | SVE | Unsigned minimum with immediate (unpredicated).
| UMIN (multiple and single vector) | SME | Multi-vector unsigned minimum by vector.
| UMIN (multiple vectors) | SME | Multi-vector unsigned minimum.
| UMIN (register) | Base | Unsigned minimum (register).
| UMIN (vectors) | SVE | Unsigned minimum vectors (predicated).
| UMINP | SIMD | Unsigned minimum pairwise.
| UMINP | SVE | Unsigned minimum pairwise.
| UMINQV | SVE | Unsigned minimum reduction of quadword vector segments.
| UMINV | SIMD | Unsigned minimum across vector.
| UMINV | SVE | Unsigned minimum reduction to scalar.
| UMLAL | SIMD | Unsigned multiply-add long (vector, by element).
| UMLAL | SIMD | Unsigned multiply-add long (vector).
| UMLAL (multiple and indexed vector) | SME | Multi-vector unsigned integer multiply-add long by indexed element.
| UMLAL (multiple and single vector) | SME | Multi-vector unsigned integer multiply-add long by vector.
| UMLAL (multiple vectors) | SME | Multi-vector unsigned integer multiply-add long.
| UMLAL2 (by element) | SIMD | Unsigned multiply-add long (vector, by element).
| UMLAL2 (vector) | SIMD | Unsigned multiply-add long (vector).
| UMLALB (indexed) | SVE | Unsigned multiply-add long to accumulator (bottom, indexed).
| UMLALB (vectors) | SVE | Unsigned multiply-add long to accumulator (bottom).
| UMLALL (multiple and indexed vector) | SME | Multi-vector unsigned integer multiply-add long-long by indexed element.
| UMLALL (multiple and single vector) | SME | Multi-vector unsigned integer multiply-add long-long by vector.
| UMLALL (multiple vectors) | SME | Multi-vector unsigned integer multiply-add long-long.
| UMLALT (indexed) | SVE | Unsigned multiply-add long to accumulator (top, indexed).
| UMLALT (vectors) | SVE | Unsigned multiply-add long to accumulator (top).
| UMLSL | SIMD | Unsigned multiply-subtract long (vector, by element).
| UMLSL | SIMD | Unsigned multiply-subtract long (vector).
| UMLSL (multiple and indexed vector) | SME | Multi-vector unsigned integer multiply-subtract long by indexed element.
| UMLSL (multiple and single vector) | SME | Multi-vector unsigned integer multiply-subtract long by vector.
| UMLSL (multiple vectors) | SME | Multi-vector unsigned integer multiply-subtract long.
| UMLSL2 (by element) | SIMD | Unsigned multiply-subtract long (vector, by element).
| UMLSL2 (vector) | SIMD | Unsigned multiply-subtract long (vector).
| UMLSLB (indexed) | SVE | Unsigned multiply-subtract long from accumulator (bottom, indexed).
| UMLSLB (vectors) | SVE | Unsigned multiply-subtract long from accumulator (bottom).
| UMLSLL (multiple and indexed vector) | SME | Multi-vector unsigned integer multiply-subtract long-long by indexed element.
| UMLSLL (multiple and single vector) | SME | Multi-vector unsigned integer multiply-subtract long-long by vector.
| UMLSLL (multiple vectors) | SME | Multi-vector unsigned integer multiply-subtract long-long.
| UMLSLT (indexed) | SVE | Unsigned multiply-subtract long from accumulator (top, indexed).
| UMLSLT (vectors) | SVE | Unsigned multiply-subtract long from accumulator (top).
| UMMLA | SVE | Unsigned integer matrix multiply-accumulate.
| UMMLA (vector) | SIMD | Unsigned 8-bit integer matrix multiply-accumulate (vector).
| UMNEGL | Base | Unsigned multiply-negate long: an alias of UMSUBL.
| UMOP4A (2-way) | SME | Unsigned integer quarter-tile sums of two outer products, accumulating.
| UMOP4A (4-way) | SME | Unsigned integer quarter-tile sums of four outer products, accumulating.
| UMOP4S (2-way) | SME | Unsigned integer quarter-tile sums of two outer products, subtracting.
| UMOP4S (4-way) | SME | Unsigned integer quarter-tile sums of four outer products, subtracting.
| UMOPA (2-way) | SME | Unsigned integer sum of outer products and accumulate.
| UMOPA (4-way) | SME | Unsigned integer sum of outer products and accumulate.
| UMOPS (2-way) | SME | Unsigned integer sum of outer products and subtract.
| UMOPS (4-way) | SME | Unsigned integer sum of outer products and subtract.
| UMOV | SIMD | Unsigned move vector element to general-purpose register.
| UMSUBL | Base | Unsigned multiply-subtract long.
| UMULH | Base | Unsigned multiply high.
| UMULH (predicated) | SVE | Unsigned multiply returning high half (predicated).
| UMULH (unpredicated) | SVE | Unsigned multiply returning high half (unpredicated).
| UMULL | Base | Unsigned multiply long: an alias of UMADDL.
| UMULL | SIMD | Unsigned multiply long (vector, by element).
| UMULL | SIMD | Unsigned multiply long (vector).
| UMULL2 (by element) | SIMD | Unsigned multiply long (vector, by element).
| UMULL2 (vector) | SIMD | Unsigned multiply long (vector).
| UMULLB (indexed) | SVE | Unsigned multiply long (bottom, indexed).
| UMULLB (vectors) | SVE | Unsigned multiply long (bottom).
| UMULLT (indexed) | SVE | Unsigned multiply long (top, indexed).
| UMULLT (vectors) | SVE | Unsigned multiply long (top).
| UQADD | SIMD | Unsigned saturating add.
| UQADD (immediate) | SVE | Unsigned saturating add immediate (unpredicated).
| UQADD (vectors, predicated) | SVE | Unsigned saturating addition (predicated).
| UQADD (vectors, unpredicated) | SVE | Unsigned saturating add vectors (unpredicated).
| UQCVT (four registers) | SME | Multi-vector unsigned saturating extract narrow.
| UQCVT (two registers) | SME | Multi-vector unsigned saturating extract narrow.
| UQCVTN | SVE | Unsigned saturating extract narrow and interleave.
| UQCVTN | SME | Multi-vector unsigned saturating extract narrow and interleave.
| UQDECB | SVE | Unsigned saturating decrement scalar by multiple of 8-bit predicate constraint element count.
| UQDECD (scalar) | SVE | Unsigned saturating decrement scalar by multiple of 64-bit predicate constraint element count.
| UQDECD (vector) | SVE | Unsigned saturating decrement vector by multiple of 64-bit predicate constraint element count.
| UQDECH (scalar) | SVE | Unsigned saturating decrement scalar by multiple of 16-bit predicate constraint element count.
| UQDECH (vector) | SVE | Unsigned saturating decrement vector by multiple of 16-bit predicate constraint element count.
| UQDECP (scalar) | SVE | Unsigned saturating decrement scalar by count of true predicate elements.
| UQDECP (vector) | SVE | Unsigned saturating decrement vector by count of true predicate elements.
| UQDECW (scalar) | SVE | Unsigned saturating decrement scalar by multiple of 32-bit predicate constraint element count.
| UQDECW (vector) | SVE | Unsigned saturating decrement vector by multiple of 32-bit predicate constraint element count.
| UQINCB | SVE | Unsigned saturating increment scalar by multiple of 8-bit predicate constraint element count.
| UQINCD (scalar) | SVE | Unsigned saturating increment scalar by multiple of 64-bit predicate constraint element count.
| UQINCD (vector) | SVE | Unsigned saturating increment vector by multiple of 64-bit predicate constraint element count.
| UQINCH (scalar) | SVE | Unsigned saturating increment scalar by multiple of 16-bit predicate constraint element count.
| UQINCH (vector) | SVE | Unsigned saturating increment vector by multiple of 16-bit predicate constraint element count.
| UQINCP (scalar) | SVE | Unsigned saturating increment scalar by count of true predicate elements.
| UQINCP (vector) | SVE | Unsigned saturating increment vector by count of true predicate elements.
| UQINCW (scalar) | SVE | Unsigned saturating increment scalar by multiple of 32-bit predicate constraint element count.
| UQINCW (vector) | SVE | Unsigned saturating increment vector by multiple of 32-bit predicate constraint element count.
| UQRSHL | SIMD | Unsigned saturating rounding shift left (register).
| UQRSHL | SVE | Unsigned saturating rounding shift left by vector (predicated).
| UQRSHLR | SVE | Unsigned saturating rounding shift left reversed vectors (predicated).
| UQRSHR (four registers) | SME | Multi-vector unsigned saturating rounding shift right narrow by immediate.
| UQRSHR (two registers) | SME | Multi-vector unsigned saturating rounding shift right narrow by immediate.
| UQRSHRN | SIMD | Unsigned saturating rounded shift right narrow (immediate).
| UQRSHRN | SVE | Unsigned saturating rounding shift right narrow by immediate and interleave.
| UQRSHRN | SME | Multi-vector unsigned saturating rounding shift right narrow by immediate and interleave.
| UQRSHRN2 | SIMD | Unsigned saturating rounded shift right narrow (immediate).
| UQRSHRNB | SVE | Unsigned saturating rounding shift right narrow by immediate (bottom).
| UQRSHRNT | SVE | Unsigned saturating rounding shift right narrow by immediate (top).
| UQSHL (immediate) | SIMD | Unsigned saturating shift left (immediate).
| UQSHL (immediate) | SVE | Unsigned saturating shift left by immediate.
| UQSHL (register) | SIMD | Unsigned saturating shift left (register).
| UQSHL (vectors) | SVE | Unsigned saturating shift left by vector (predicated).
| UQSHLR | SVE | Unsigned saturating shift left reversed vectors (predicated).
| UQSHRN | SIMD | Unsigned saturating shift right narrow (immediate).
| UQSHRN2 | SIMD | Unsigned saturating shift right narrow (immediate).
| UQSHRNB | SVE | Unsigned saturating shift right narrow by immediate (bottom).
| UQSHRNT | SVE | Unsigned saturating shift right narrow by immediate (top).
| UQSUB | SIMD | Unsigned saturating subtract.
| UQSUB (immediate) | SVE | Unsigned saturating subtract immediate (unpredicated).
| UQSUB (vectors, predicated) | SVE | Unsigned saturating subtraction (predicated).
| UQSUB (vectors, unpredicated) | SVE | Unsigned saturating subtract vectors (unpredicated).
| UQSUBR | SVE | Unsigned saturating subtraction reversed vectors (predicated).
| UQXTN | SIMD | Unsigned saturating extract narrow.
| UQXTN2 | SIMD | Unsigned saturating extract narrow.
| UQXTNB | SVE | Unsigned saturating extract narrow (bottom).
| UQXTNT | SVE | Unsigned saturating extract narrow (top).
| URECPE | SIMD | Unsigned reciprocal estimate.
| URECPE | SVE | Unsigned reciprocal estimate (predicated).
| URHADD | SIMD | Unsigned rounding halving add.
| URHADD | SVE | Unsigned rounding halving addition.
| URSHL | SIMD | Unsigned rounding shift left (register).
| URSHL | SVE | Unsigned rounding shift left by vector (predicated).
| URSHL (multiple and single vector) | SME | Multi-vector unsigned rounding shift left by vector.
| URSHL (multiple vectors) | SME | Multi-vector unsigned rounding shift left.
| URSHLR | SVE | Unsigned rounding shift left reversed vectors (predicated).
| URSHR | SIMD | Unsigned rounding shift right (immediate).
| URSHR | SVE | Unsigned rounding shift right by immediate.
| URSQRTE | SIMD | Unsigned reciprocal square root estimate.
| URSQRTE | SVE | Unsigned reciprocal square root estimate (predicated).
| URSRA | SIMD | Unsigned rounding shift right and accumulate (immediate).
| URSRA | SVE | Unsigned rounding shift right and accumulate (immediate).
| USDOT (by element) | SIMD | Dot product with unsigned and signed integers (vector, by element).
| USDOT (indexed) | SVE | Unsigned by signed integer indexed dot product.
| USDOT (multiple and indexed vector) | SME | Multi-vector unsigned by signed integer dot-product by indexed element.
| USDOT (multiple and single vector) | SME | Multi-vector unsigned by signed integer dot-product by vector.
| USDOT (multiple vectors) | SME | Multi-vector unsigned by signed integer dot-product.
| USDOT (vector) | SIMD | Dot product with unsigned and signed integers (vector).
| USDOT (vectors) | SVE | Unsigned by signed integer dot product.
| USHL | SIMD | Unsigned shift left (register).
| USHLL | SIMD | Unsigned shift left long (immediate).
| USHLL2 | SIMD | Unsigned shift left long (immediate).
| USHLLB | SVE | Unsigned shift left long by immediate (bottom).
| USHLLT | SVE | Unsigned shift left long by immediate (top).
| USHR | SIMD | Unsigned shift right (immediate).
| USMLALL (multiple and indexed vector) | SME | Multi-vector unsigned by signed integer multiply-add long-long by indexed element.
| USMLALL (multiple and single vector) | SME | Multi-vector unsigned by signed integer multiply-add long-long by vector.
| USMLALL (multiple vectors) | SME | Multi-vector unsigned by signed integer multiply-add long-long.
| USMMLA | SVE | Unsigned by signed integer matrix multiply-accumulate.
| USMMLA (vector) | SIMD | Unsigned and signed 8-bit integer matrix multiply-accumulate (vector).
| USMOP4A | SME | Unsigned by signed integer quarter-tile sums of four outer products, accumulating.
| USMOP4S | SME | Unsigned by signed integer quarter-tile sums of four outer products, subtracting.
| USMOPA | SME | Unsigned by signed integer sum of outer products and accumulate.
| USMOPS | SME | Unsigned by signed integer sum of outer products and subtract.
| USQADD | SIMD | Unsigned saturating accumulate of signed value.
| USQADD | SVE | Unsigned saturating addition of signed value.
| USRA | SIMD | Unsigned shift right and accumulate (immediate).
| USRA | SVE | Unsigned shift right and accumulate (immediate).
| USTMOPA | SME | Unsigned by signed integer sparse sum of four outer products, accumulating.
| USUBL | SIMD | Unsigned subtract long.
| USUBL2 | SIMD | Unsigned subtract long.
| USUBLB | SVE | Unsigned subtract long (bottom).
| USUBLT | SVE | Unsigned subtract long (top).
| USUBW | SIMD | Unsigned subtract wide.
| USUBW2 | SIMD | Unsigned subtract wide.
| USUBWB | SVE | Unsigned subtract wide (bottom).
| USUBWT | SVE | Unsigned subtract wide (top).
| USVDOT | SME | Multi-vector unsigned by signed integer vertical dot-product by indexed element.
| UTMOPA (2-way) | SME | Unsigned integer sparse sum of two outer products, accumulating.
| UTMOPA (4-way) | SME | Unsigned integer sparse sum of four outer products, accumulating.
| UUNPK | SME | Unpack and zero-extend multi-vector elements.
| UUNPKHI | SVE | Unsigned unpack and extend half of vector.
| UUNPKLO | SVE | Unsigned unpack and extend half of vector.
| UVDOT (2-way) | SME | Multi-vector unsigned integer vertical dot-product by indexed element.
| UVDOT (4-way) | SME | Multi-vector unsigned integer vertical dot-product by indexed element.
| UXTB | Base | Unsigned extend byte: an alias of UBFM.
| UXTB | SVE | Unsigned byte / halfword / word extend (predicated).
| UXTH | Base | Unsigned extend halfword: an alias of UBFM.
| UXTH | SVE | Unsigned byte / halfword / word extend (predicated).
| UXTL | SIMD | Unsigned extend long: an alias of USHLL, USHLL2.
| UXTL2 | SIMD | Unsigned extend long: an alias of USHLL, USHLL2.
| UXTW | SVE | Unsigned byte / halfword / word extend (predicated).
| UZP (four registers) | SME | Concatenate elements from four vectors.
| UZP (two registers) | SME | Concatenate elements from two vectors.
| UZP1 | SIMD | Unzip vectors (primary).
| UZP1 | SVE | Concatenate even or odd elements from two predicates.
| UZP1 | SVE | Concatenate even or odd elements from two vectors.
| UZP2 | SIMD | Unzip vectors (secondary).
| UZP2 (predicates) | SVE | Concatenate even or odd elements from two predicates.
| UZP2 (vectors) | SVE | Concatenate even or odd elements from two vectors.
| UZPQ1 | SVE | Concatenate even elements within each pair of quadword vector segments.
| UZPQ2 | SVE | Concatenate odd elements within each pair of quadword vector segments.
| WFE | Base | Wait for event.
| WFET | Base | Wait for event with timeout.
| WFI | Base | Wait for interrupt.
| WFIT | Base | Wait for interrupt with timeout.
| WHILEGE (predicate as counter) | SVE | While decrementing signed scalar greater than or equal to scalar (predicate-as-counter).
| WHILEGE (predicate pair) | SVE | While decrementing signed scalar greater than or equal to scalar (pair of predicates).
| WHILEGE (predicate) | SVE | While decrementing signed scalar greater than or equal to scalar.
| WHILEGT (predicate as counter) | SVE | While decrementing signed scalar greater than scalar (predicate-as-counter).
| WHILEGT (predicate pair) | SVE | While decrementing signed scalar greater than scalar (pair of predicates).
| WHILEGT (predicate) | SVE | While decrementing signed scalar greater than scalar.
| WHILEHI (predicate as counter) | SVE | While decrementing unsigned scalar higher than scalar (predicate-as-counter).
| WHILEHI (predicate pair) | SVE | While decrementing unsigned scalar higher than scalar (pair of predicates).
| WHILEHI (predicate) | SVE | While decrementing unsigned scalar higher than scalar.
| WHILEHS (predicate as counter) | SVE | While decrementing unsigned scalar higher or same as scalar (predicate-as-counter).
| WHILEHS (predicate pair) | SVE | While decrementing unsigned scalar higher or same as scalar (pair of predicates).
| WHILEHS (predicate) | SVE | While decrementing unsigned scalar higher or same as scalar.
| WHILELE (predicate as counter) | SVE | While incrementing signed scalar less than or equal to scalar (predicate-as-counter).
| WHILELE (predicate pair) | SVE | While incrementing signed scalar less than or equal to scalar (pair of predicates).
| WHILELE (predicate) | SVE | While incrementing signed scalar less than or equal to scalar.
| WHILELO (predicate as counter) | SVE | While incrementing unsigned scalar lower than scalar (predicate-as-counter).
| WHILELO (predicate pair) | SVE | While incrementing unsigned scalar lower than scalar (pair of predicates).
| WHILELO (predicate) | SVE | While incrementing unsigned scalar lower than scalar.
| WHILELS (predicate as counter) | SVE | While incrementing unsigned scalar lower or same as scalar (predicate-as-counter).
| WHILELS (predicate pair) | SVE | While incrementing unsigned scalar lower or same as scalar (pair of predicates).
| WHILELS (predicate) | SVE | While incrementing unsigned scalar lower or same as scalar.
| WHILELT (predicate as counter) | SVE | While incrementing signed scalar less than scalar (predicate-as-counter).
| WHILELT (predicate pair) | SVE | While incrementing signed scalar less than scalar (pair of predicates).
| WHILELT (predicate) | SVE | While incrementing signed scalar less than scalar.
| WHILERW | SVE | While free of read-after-write conflicts.
| WHILEWR | SVE | While free of write-after-read/write conflicts.
| WRFFR | SVE | Write the first-fault register.
| XAFLAG | Base | Convert floating-point condition flags from external format to Arm format.
| XAR | SIMD | Exclusive-OR and rotate.
| XAR | SVE | Bitwise exclusive OR and rotate right by immediate.
| XPACD | Base | Strip Pointer Authentication Code.
| XPACI | Base | Strip Pointer Authentication Code.
| XPACLRI | Base | Strip Pointer Authentication Code.
| XTN | SIMD | Extract narrow.
| XTN2 | SIMD | Extract narrow.
| YIELD | Base | Yield.
| ZERO (double-vector) | SME | Zero ZA double-vector groups.
| ZERO (quad-vector) | SME | Zero ZA quad-vector groups.
| ZERO (single-vector) | SME | Zero ZA single-vector groups.
| ZERO (table) | SME | Zero ZT0.
| ZERO (tiles) | SME | Zero a list of 64-bit element ZA tiles.
| ZIP (four registers) | SME | Interleave elements from four vectors.
| ZIP (two registers) | SME | Interleave elements from two vectors.
| ZIP1 | SIMD | Zip vectors (primary).
| ZIP1 | SVE | Interleave elements from two half predicates.
| ZIP1 | SVE | Interleave elements from two half vectors.
| ZIP2 | SIMD | Zip vectors (secondary).
| ZIP2 (predicates) | SVE | Interleave elements from two half predicates.
| ZIP2 (vectors) | SVE | Interleave elements from two half vectors.
| ZIPQ1 | SVE | Interleave elements from low halves of each pair of quadword vector segments.
| ZIPQ2 | SVE | Interleave elements from high halves of each pair of quadword vector segments.
<!-- @AUTOGEN-END -->
