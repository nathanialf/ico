# MatrixDrive_GetTurnXAngleYZ — parked

VRAM: 0x00105DA8 (file_off 0x005DA8)
Asm source: asm/aug6/nonmatchings/sugipon/src/matrixDrive/MatrixDrive_GetTurnXAngleYZ.s

## Attempt at 2026-06-08

**Reason parked:** rc7 regalloc/addressing/scheduling near-miss (2026-06-08, FRESH). Structure CORRECT: save qword obj+0x30 to stack tmp, call func_002400F8(a0), restore. Residuals: (1) ROM addiu s0,a0,0x30 (compute ptr) vs gcc daddu s0,a0 + 48-disp accesses; (2) scratch qword reg a2 vs gcc v0; (3) ROM leaves jal delay nop + sq-save after vs gcc fills delay with sq. ~30 distinct shapes (ptr/array/struct-member/deref, char*/void*/long arg, scalar/array tmp) all rc7. mode(TI) qword -> permuter strips TI (like func_00118E38), can't fairly test. Clean dev seed = struct{char[0x30];Qw128 q;} member form.

**TU:** `sugipon/src/matrixDrive.c`

**Seed:** `tough_nuts/MatrixDrive_GetTurnXAngleYZ/MatrixDrive_GetTurnXAngleYZ.c`

Disassembly:

```
.align 3
nonmatching MatrixDrive_GetTurnXAngleYZ, 0x38

glabel MatrixDrive_GetTurnXAngleYZ
    /* 5DA8 00105DA8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5DAC 00105DAC 1000B0FF */  sd         $16, 0x10($29)
    /* 5DB0 00105DB0 30009024 */  addiu      $16, $4, 0x30
    /* 5DB4 00105DB4 2000BFFF */  sd         $31, 0x20($29)
    /* 5DB8 00105DB8 0000067A */  lq         $6, 0x0($16)
    /* 5DBC 00105DBC 0000A67F */  sq         $6, 0x0($29)
    /* 5DC0 00105DC0 3E00090C */  jal        func_002400F8
    /* 5DC4 00105DC4 00000000 */   nop
    /* 5DC8 00105DC8 0000A67B */  lq         $6, 0x0($29)
    /* 5DCC 00105DCC 0000067E */  sq         $6, 0x0($16)
    /* 5DD0 00105DD0 2000BFDF */  ld         $31, 0x20($29)
    /* 5DD4 00105DD4 1000B0DF */  ld         $16, 0x10($29)
    /* 5DD8 00105DD8 0800E003 */  jr         $31
    /* 5DDC 00105DDC 3000BD27 */   addiu     $29, $29, 0x30
endlabel MatrixDrive_GetTurnXAngleYZ
```
## Fire 6: re-attack rc7 qword save/restore; explicit ptr/byte-offset/pad-type ~35 forms all rc7-12; mode-TI strips permuter; stall=31 permute, valid run 18 out no rc0. (b)

## Pass 3 (2026-06-11): resume, ~20 distinct hand shapes -> rc7 floor, stall=31 -> permute
Grounded func_002400F8 (common/PObj): writes vf4-7 to obj+0x0..0x3F (OVERWRITES obj+0x30) -> the
save/restore of obj+0x30 is exact. Best = mode(TI) `Qw128 tmp[1]; tmp[0]=a0->q; func(a0); a0->q=tmp[0]`.
3 coupled residuals persist: (1) ROM `addiu s0,a0,0x30`+0-disp lq/sq vs gcc `daddu s0,a0`+48-disp
(gcc base+disp folding is unbreakable for the const 0x30 offset because a0 is live to the call, so
gcc keeps a0 as the base; pointer/Qw128*+3/char*-reassign/idx a0[3]/dual-root/secondlocal ALL fold
back to base+48); (2) qword scratch reg $6/a2 (ROM) vs $2/v0 (gcc) — no clean lever found; (3) jal
delay: volatile tmp moves the save before the jal but then the reload fills the delay (ROM has nop).
Tried: array/scalar/union/16B-struct(ld/sd rc10)/vector_size(rc9)/memcpy(rc10)/2-3arg-sig/volatile
member+tmp/const-src/various pads — all rc7-12. mode(TI) STRIPS in permuter import (hand-only domain);
vector_size survives import but only assembles to rc9. Permuter pass 3 (will likely (b) again).

---

## Attempt at 2026-06-11

**Reason parked:** rc7: mode(TI) qword save/restore; 3 coupled residuals (addiu-0disp-vs-daddu-48disp folding, qword reg a2-vs-v0, jal-delay-nop). ~20 hand shapes all rc7-12. permuter strips mode(TI). Pass 3.

**TU:** `sugipon/src/matrixDrive.c`

**Seed:** `tough_nuts/MatrixDrive_GetTurnXAngleYZ/MatrixDrive_GetTurnXAngleYZ.1.c`

Disassembly:

```
.align 3
nonmatching MatrixDrive_GetTurnXAngleYZ, 0x38

glabel MatrixDrive_GetTurnXAngleYZ
    /* 5DA8 00105DA8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5DAC 00105DAC 1000B0FF */  sd         $16, 0x10($29)
    /* 5DB0 00105DB0 30009024 */  addiu      $16, $4, 0x30
    /* 5DB4 00105DB4 2000BFFF */  sd         $31, 0x20($29)
    /* 5DB8 00105DB8 0000067A */  lq         $6, 0x0($16)
    /* 5DBC 00105DBC 0000A67F */  sq         $6, 0x0($29)
    /* 5DC0 00105DC0 3E00090C */  jal        func_002400F8
    /* 5DC4 00105DC4 00000000 */   nop
    /* 5DC8 00105DC8 0000A67B */  lq         $6, 0x0($29)
    /* 5DCC 00105DCC 0000067E */  sq         $6, 0x0($16)
    /* 5DD0 00105DD0 2000BFDF */  ld         $31, 0x20($29)
    /* 5DD4 00105DD4 1000B0DF */  ld         $16, 0x10($29)
    /* 5DD8 00105DD8 0800E003 */  jr         $31
    /* 5DDC 00105DDC 3000BD27 */   addiu     $29, $29, 0x30
endlabel MatrixDrive_GetTurnXAngleYZ
```
