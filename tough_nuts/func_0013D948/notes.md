# func_0013D948 — parked

VRAM: 0x0013D948 (file_off 0x03D948)
Asm source: asm/nonmatchings/ios/thread/func_0013D948.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR)

**TU:** `ios/thread.c`

**Seed:** `tough_nuts/func_0013D948/func_0013D948.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632000, 1

.align 3
nonmatching func_0013D948, 0x80

glabel func_0013D948
    /* 3D948 0013D948 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 3D94C 0013D94C 1000B0FF */  sd         $16, 0x10($29)
    /* 3D950 0013D950 2000BFFF */  sd         $31, 0x20($29)
    /* 3D954 0013D954 2D808000 */  daddu      $16, $4, $0
    /* 3D958 0013D958 4800028E */  lw         $2, 0x48($16)
    /* 3D95C 0013D95C 0F004054 */  bnel       $2, $0, .L0013D99C
    /* 3D960 0013D960 4C00048E */   lw        $4, 0x4C($16)
    /* 3D964 0013D964 01000224 */  addiu      $2, $0, 0x1
    /* 3D968 0013D968 5500063C */  lui        $6, %hi(D_005578D0)
    /* 3D96C 0013D96C 1097848F */  lw         $4, (D_00632000) /* gp_rel: (D_00632000) */
    /* 3D970 0013D970 D078C624 */  addiu      $6, $6, %lo(D_005578D0)
    /* 3D974 0013D974 480002AE */  sw         $2, 0x48($16)
    /* 3D978 0013D978 50000524 */  addiu      $5, $0, 0x50
    /* 3D97C 0013D97C 3EE8040C */  jal        func_0013A0F8
    /* 3D980 0013D980 FA010724 */   addiu     $7, $0, 0x1FA
    /* 3D984 0013D984 2D204000 */  daddu      $4, $2, $0
    /* 3D988 0013D988 08000624 */  addiu      $6, $0, 0x8
    /* 3D98C 0013D98C 4C0002AE */  sw         $2, 0x4C($16)
    /* 3D990 0013D990 94E8040C */  jal        func_0013A250
    /* 3D994 0013D994 30008524 */   addiu     $5, $4, 0x30
    /* 3D998 0013D998 4C00048E */  lw         $4, 0x4C($16)
.align 2
  .L0013D99C:
    /* 3D99C 0013D99C 2D28A003 */  daddu      $5, $29, $0
    /* 3D9A0 0013D9A0 B0E9040C */  jal        func_0013A6C0
    /* 3D9A4 0013D9A4 01000624 */   addiu     $6, $0, 0x1
    /* 3D9A8 0013D9A8 5500043C */  lui        $4, %hi(D_00557980)
    /* 3D9AC 0013D9AC 8A9B060C */  jal        func_001A6E28
    /* 3D9B0 0013D9B0 80798424 */   addiu     $4, $4, %lo(D_00557980)
    /* 3D9B4 0013D9B4 0000A28F */  lw         $2, 0x0($29)
    /* 3D9B8 0013D9B8 2000BFDF */  ld         $31, 0x20($29)
    /* 3D9BC 0013D9BC 1000B0DF */  ld         $16, 0x10($29)
    /* 3D9C0 0013D9C0 0800E003 */  jr         $31
    /* 3D9C4 0013D9C4 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0013D948
```
