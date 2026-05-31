# func_001D9BB8 — parked

VRAM: 0x001D9BB8 (file_off 0x0D9BB8)
Asm source: asm/nonmatchings/src/motionManager/func_001D9BB8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/motionManager.c`

**Seed:** `tough_nuts/func_001D9BB8/func_001D9BB8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633F40, 1
.extern D_00633F3C, 1

.align 3
nonmatching func_001D9BB8, 0xA0

glabel func_001D9BB8
    /* D9BB8 001D9BB8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* D9BBC 001D9BBC 0000B0FF */  sd         $16, 0x0($29)
    /* D9BC0 001D9BC0 1000BFFF */  sd         $31, 0x10($29)
    /* D9BC4 001D9BC4 9E14040C */  jal        func_00105278
    /* D9BC8 001D9BC8 00000000 */   nop
    /* D9BCC 001D9BCC 9E61040C */  jal        func_00118678
    /* D9BD0 001D9BD0 2D204000 */   daddu     $4, $2, $0
    /* D9BD4 001D9BD4 4CB6908F */  lw         $16, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9BD8 001D9BD8 2D280002 */  daddu      $5, $16, $0
    /* D9BDC 001D9BDC 06A3050C */  jal        func_00168C18
    /* D9BE0 001D9BE0 30010426 */   addiu     $4, $16, 0x130
    /* D9BE4 001D9BE4 4CB6828F */  lw         $2, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9BE8 001D9BE8 46030046 */  mov.s      $f13, $f0
    /* D9BEC 001D9BEC 00000CC6 */  lwc1       $f12, 0x0($16)
    /* D9BF0 001D9BF0 C214040C */  jal        func_00105308
    /* D9BF4 001D9BF4 08004EC4 */   lwc1      $f14, 0x8($2)
    /* D9BF8 001D9BF8 4CB6848F */  lw         $4, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9BFC 001D9BFC DC37040C */  jal        func_0010DF70
    /* D9C00 001D9C00 30008424 */   addiu     $4, $4, 0x30
    /* D9C04 001D9C04 C813040C */  jal        func_00104F20
    /* D9C08 001D9C08 00000000 */   nop
    /* D9C0C 001D9C0C 2466070C */  jal        func_001D9890
    /* D9C10 001D9C10 00000000 */   nop
    /* D9C14 001D9C14 9A14040C */  jal        func_00105268
    /* D9C18 001D9C18 00000000 */   nop
    /* D9C1C 001D9C1C 50B6828F */  lw         $2, (D_00633F40) /* gp_rel: (D_00633F40) */
    /* D9C20 001D9C20 E400438C */  lw         $3, 0xE4($2)
    /* D9C24 001D9C24 09006010 */  beqz       $3, .L001D9C4C
    /* D9C28 001D9C28 1000BFDF */   ld        $31, 0x10($29)
    /* D9C2C 001D9C2C C813040C */  jal        func_00104F20
    /* D9C30 001D9C30 00000000 */   nop
    /* D9C34 001D9C34 3C63070C */  jal        func_001D8CF0
    /* D9C38 001D9C38 00000000 */   nop
    /* D9C3C 001D9C3C 1000BFDF */  ld         $31, 0x10($29)
    /* D9C40 001D9C40 0000B0DF */  ld         $16, 0x0($29)
    /* D9C44 001D9C44 9A140408 */  j          func_00105268
    /* D9C48 001D9C48 2000BD27 */   addiu     $29, $29, 0x20
.align 2
  .L001D9C4C:
    /* D9C4C 001D9C4C 0000B0DF */  ld         $16, 0x0($29)
    /* D9C50 001D9C50 0800E003 */  jr         $31
    /* D9C54 001D9C54 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001D9BB8
```
