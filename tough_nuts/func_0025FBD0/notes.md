# func_0025FBD0 — parked

VRAM: 0x0025FBD0 (file_off 0x15FBD0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025FBD0.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025FBD0/func_0025FBD0.c`

Disassembly:

```
.align 3
nonmatching func_0025FBD0, 0x64

glabel func_0025FBD0
    /* 15FBD0 0025FBD0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 15FBD4 0025FBD4 4000B0FF */  sd         $16, 0x40($29)
    /* 15FBD8 0025FBD8 3000A427 */  addiu      $4, $29, 0x30
    /* 15FBDC 0025FBDC 5000BFFF */  sd         $31, 0x50($29)
    /* 15FBE0 0025FBE0 2D28A003 */  daddu      $5, $29, $0
    /* 15FBE4 0025FBE4 3000ACE7 */  swc1       $f12, 0x30($29)
    /* 15FBE8 0025FBE8 2C7E090C */  jal        func_0025F8B0
    /* 15FBEC 0025FBEC 3400ADE7 */   swc1      $f13, 0x34($29)
    /* 15FBF0 0025FBF0 1000B027 */  addiu      $16, $29, 0x10
    /* 15FBF4 0025FBF4 3400A427 */  addiu      $4, $29, 0x34
    /* 15FBF8 0025FBF8 2C7E090C */  jal        func_0025F8B0
    /* 15FBFC 0025FBFC 2D280002 */   daddu     $5, $16, $0
    /* 15FC00 0025FC00 1400A28F */  lw         $2, 0x14($29)
    /* 15FC04 0025FC04 2D280002 */  daddu      $5, $16, $0
    /* 15FC08 0025FC08 2000A627 */  addiu      $6, $29, 0x20
    /* 15FC0C 0025FC0C 2D20A003 */  daddu      $4, $29, $0
    /* 15FC10 0025FC10 01004238 */  xori       $2, $2, 0x1
    /* 15FC14 0025FC14 507E090C */  jal        func_0025F940
    /* 15FC18 0025FC18 1400A2AF */   sw        $2, 0x14($29)
    /* 15FC1C 0025FC1C E87D090C */  jal        func_0025F7A0
    /* 15FC20 0025FC20 2D204000 */   daddu     $4, $2, $0
    /* 15FC24 0025FC24 5000BFDF */  ld         $31, 0x50($29)
    /* 15FC28 0025FC28 4000B0DF */  ld         $16, 0x40($29)
    /* 15FC2C 0025FC2C 0800E003 */  jr         $31
    /* 15FC30 0025FC30 6000BD27 */   addiu     $29, $29, 0x60
endlabel func_0025FBD0
    /* 15FC34 0025FC34 00000000 */  nop
```
