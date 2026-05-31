# func_001D9C58 — parked

VRAM: 0x001D9C58 (file_off 0x0D9C58)
Asm source: asm/nonmatchings/src/motionManager/func_001D9C58.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/motionManager.c`

**Seed:** `tough_nuts/func_001D9C58/func_001D9C58.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633F3C, 1

.align 3
nonmatching func_001D9C58, 0x58

glabel func_001D9C58
    /* D9C58 001D9C58 F0FFBD27 */  addiu      $29, $29, -0x10
    /* D9C5C 001D9C5C 0000BFFF */  sd         $31, 0x0($29)
    /* D9C60 001D9C60 9E14040C */  jal        func_00105278
    /* D9C64 001D9C64 00000000 */   nop
    /* D9C68 001D9C68 9E61040C */  jal        func_00118678
    /* D9C6C 001D9C6C 2D204000 */   daddu     $4, $2, $0
    /* D9C70 001D9C70 4CB6828F */  lw         $2, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9C74 001D9C74 2041013C */  lui        $1, (0x41200000 >> 16)
    /* D9C78 001D9C78 00088144 */  mtc1       $1, $f1
    /* D9C7C 001D9C7C 04004DC4 */  lwc1       $f13, 0x4($2)
    /* D9C80 001D9C80 D00140C4 */  lwc1       $f0, 0x1D0($2)
    /* D9C84 001D9C84 08004EC4 */  lwc1       $f14, 0x8($2)
    /* D9C88 001D9C88 406B0046 */  add.s      $f13, $f13, $f0
    /* D9C8C 001D9C8C 00004CC4 */  lwc1       $f12, 0x0($2)
    /* D9C90 001D9C90 C214040C */  jal        func_00105308
    /* D9C94 001D9C94 406B0146 */   add.s     $f13, $f13, $f1
    /* D9C98 001D9C98 4CB6848F */  lw         $4, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9C9C 001D9C9C DC37040C */  jal        func_0010DF70
    /* D9CA0 001D9CA0 30008424 */   addiu     $4, $4, 0x30
    /* D9CA4 001D9CA4 0000BFDF */  ld         $31, 0x0($29)
    /* D9CA8 001D9CA8 24660708 */  j          func_001D9890
    /* D9CAC 001D9CAC 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_001D9C58
```
