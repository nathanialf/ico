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
