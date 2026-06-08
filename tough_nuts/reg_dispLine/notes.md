# reg_dispLine — parked

VRAM: 0x00120298 (file_off 0x020298)
Asm source: asm/aug6/nonmatchings/seki/src/RegistPacket/reg_dispLine.s

## Attempt at 2026-06-08

**Reason parked:** best=rc4 (void-return, TCO j dl_GetPri correct). Residual: dpk_Init(2,D,4) delay-slot tie — ROM defers a0=2 to the jal delay (a1hi,a2,a1lo,[a0]); ee-gcc emits args L-to-R so a1lo (pointer %lo, last-ready via RAW chain) always fills the delay (a1hi,a0,a2,[a1lo]). 30+ distinct forms (return type void/int/long/void*, proto void*/int*/char/short/array/const/register, global ref D/&D[0]/D+1/scalar&/struct, enum/unsigned/comma/bare-call/two-stmt) + flag sweep (O1/O2/no-sched1/no-sched2) ALL rc4. a0=2 is a pure no-WAR constant (func_002590A0 defers const only via $4 WAR from an incoming arg; reg_dispLine is void(void)) so it can never schedule last by source. Permuter-class scheduler tie.

**TU:** `seki/src/RegistPacket.c`

**Seed:** `tough_nuts/reg_dispLine/reg_dispLine.c`

Disassembly:

```
.align 3
nonmatching reg_dispLine, 0x30

glabel reg_dispLine
    /* 20298 00120298 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 2029C 0012029C 0000BFFF */  sd         $31, 0x0($29)
    /* 202A0 001202A0 BAE1070C */  jal        dpk_SwapBuffer
    /* 202A4 001202A4 00000000 */   nop
    /* 202A8 001202A8 5500053C */  lui        $5, %hi(D_0054FBE0)
    /* 202AC 001202AC 04000624 */  addiu      $6, $0, 0x4
    /* 202B0 001202B0 E0FBA524 */  addiu      $5, $5, %lo(D_0054FBE0)
    /* 202B4 001202B4 C4E1070C */  jal        dpk_Init
    /* 202B8 001202B8 02000424 */   addiu     $4, $0, 0x2
    /* 202BC 001202BC 0000BFDF */  ld         $31, 0x0($29)
    /* 202C0 001202C0 48E10708 */  j          dl_GetPri
    /* 202C4 001202C4 1000BD27 */   addiu     $29, $29, 0x10
endlabel reg_dispLine
```
