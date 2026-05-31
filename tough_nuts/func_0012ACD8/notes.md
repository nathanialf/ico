# func_0012ACD8 — parked

VRAM: 0x0012ACD8 (file_off 0x02ACD8)
Asm source: asm/nonmatchings/src/StageAnimation/func_0012ACD8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/StageAnimation.c`

**Seed:** `tough_nuts/func_0012ACD8/func_0012ACD8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633C54, 1

.align 3
nonmatching func_0012ACD8, 0x64

glabel func_0012ACD8
    /* 2ACD8 0012ACD8 6700023C */  lui        $2, %hi(D_00674058)
    /* 2ACDC 0012ACDC 64B3898F */  lw         $9, (D_00633C54) /* gp_rel: (D_00633C54) */
    /* 2ACE0 0012ACE0 58404724 */  addiu      $7, $2, %lo(D_00674058)
    /* 2ACE4 0012ACE4 13002019 */  blez       $9, .L0012AD34
    /* 2ACE8 0012ACE8 2D400000 */   daddu     $8, $0, $0
    /* 2ACEC 0012ACEC 00000000 */  nop
.align 2
  .L0012ACF0:
    /* 2ACF0 0012ACF0 8002E28C */  lw         $2, 0x280($7)
    /* 2ACF4 0012ACF4 5800438C */  lw         $3, 0x58($2)
    /* 2ACF8 0012ACF8 0B008314 */  bne        $4, $3, .L0012AD28
    /* 2ACFC 0012ACFC 01000825 */   addiu     $8, $8, 0x1
    /* 2AD00 0012AD00 8402E28C */  lw         $2, 0x284($7)
    /* 2AD04 0012AD04 2400438C */  lw         $3, 0x24($2)
    /* 2AD08 0012AD08 0700A268 */  ldl        $2, 0x7($5)
    /* 2AD0C 0012AD0C 0000A26C */  ldr        $2, 0x0($5)
    /* 2AD10 0012AD10 270062B0 */  sdl        $2, 0x27($3)
    /* 2AD14 0012AD14 200062B4 */  sdr        $2, 0x20($3)
    /* 2AD18 0012AD18 8402E28C */  lw         $2, 0x284($7)
    /* 2AD1C 0012AD1C 2400438C */  lw         $3, 0x24($2)
    /* 2AD20 0012AD20 280066AC */  sw         $6, 0x28($3)
    /* 2AD24 0012AD24 64B3898F */  lw         $9, (D_00633C54) /* gp_rel: (D_00633C54) */
.align 2
  .L0012AD28:
    /* 2AD28 0012AD28 2A100901 */  slt        $2, $8, $9
    /* 2AD2C 0012AD2C F0FF4014 */  bnez       $2, .L0012ACF0
    /* 2AD30 0012AD30 9002E724 */   addiu     $7, $7, 0x290
.align 2
  .L0012AD34:
    /* 2AD34 0012AD34 0800E003 */  jr         $31
    /* 2AD38 0012AD38 00000000 */   nop
endlabel func_0012ACD8
    /* 2AD3C 0012AD3C 00000000 */  nop
```
