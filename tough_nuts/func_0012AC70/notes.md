# func_0012AC70 — parked

VRAM: 0x0012AC70 (file_off 0x02AC70)
Asm source: asm/nonmatchings/src/StageAnimation/func_0012AC70.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/StageAnimation.c`

**Seed:** `tough_nuts/func_0012AC70/func_0012AC70.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633C54, 1

.align 3
nonmatching func_0012AC70, 0x64

glabel func_0012AC70
    /* 2AC70 0012AC70 6700023C */  lui        $2, %hi(D_00674058)
    /* 2AC74 0012AC74 64B3888F */  lw         $8, (D_00633C54) /* gp_rel: (D_00633C54) */
    /* 2AC78 0012AC78 58404624 */  addiu      $6, $2, %lo(D_00674058)
    /* 2AC7C 0012AC7C 01000924 */  addiu      $9, $0, 0x1
    /* 2AC80 0012AC80 12000019 */  blez       $8, .L0012ACCC
    /* 2AC84 0012AC84 2D380000 */   daddu     $7, $0, $0
.align 2
  .L0012AC88:
    /* 2AC88 0012AC88 8002C28C */  lw         $2, 0x280($6)
    /* 2AC8C 0012AC8C 5800438C */  lw         $3, 0x58($2)
    /* 2AC90 0012AC90 0B008314 */  bne        $4, $3, .L0012ACC0
    /* 2AC94 0012AC94 0100E724 */   addiu     $7, $7, 0x1
    /* 2AC98 0012AC98 8402C28C */  lw         $2, 0x284($6)
    /* 2AC9C 0012AC9C 2400438C */  lw         $3, 0x24($2)
    /* 2ACA0 0012ACA0 0700A268 */  ldl        $2, 0x7($5)
    /* 2ACA4 0012ACA4 0000A26C */  ldr        $2, 0x0($5)
    /* 2ACA8 0012ACA8 270062B0 */  sdl        $2, 0x27($3)
    /* 2ACAC 0012ACAC 200062B4 */  sdr        $2, 0x20($3)
    /* 2ACB0 0012ACB0 8402C28C */  lw         $2, 0x284($6)
    /* 2ACB4 0012ACB4 2400438C */  lw         $3, 0x24($2)
    /* 2ACB8 0012ACB8 280069AC */  sw         $9, 0x28($3)
    /* 2ACBC 0012ACBC 64B3888F */  lw         $8, (D_00633C54) /* gp_rel: (D_00633C54) */
.align 2
  .L0012ACC0:
    /* 2ACC0 0012ACC0 2A10E800 */  slt        $2, $7, $8
    /* 2ACC4 0012ACC4 F0FF4014 */  bnez       $2, .L0012AC88
    /* 2ACC8 0012ACC8 9002C624 */   addiu     $6, $6, 0x290
.align 2
  .L0012ACCC:
    /* 2ACCC 0012ACCC 0800E003 */  jr         $31
    /* 2ACD0 0012ACD0 00000000 */   nop
endlabel func_0012AC70
    /* 2ACD4 0012ACD4 00000000 */  nop
```
