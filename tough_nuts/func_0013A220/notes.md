# func_0013A220 — parked

VRAM: 0x0013A220 (file_off 0x03A220)
Asm source: asm/matchings/ios/message/func_0013A220.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `ios/message.c`

**Seed:** `tough_nuts/func_0013A220/func_0013A220.c`

Disassembly:

```
.align 3
nonmatching func_0013A220, 0x2C

glabel func_0013A220
    /* 3A220 0013A220 2D188000 */  daddu      $3, $4, $0
    /* 3A224 0013A224 1000658C */  lw         $5, 0x10($3)
    /* 3A228 0013A228 0600A010 */  beqz       $5, .L0013A244
    /* 3A22C 0013A22C 00000000 */   nop
    /* 3A230 0013A230 4400A28C */  lw         $2, 0x44($5)
    /* 3A234 0013A234 2C00648C */  lw         $4, 0x2C($3)
    /* 3A238 0013A238 100062AC */  sw         $2, 0x10($3)
    /* 3A23C 0013A23C 50010408 */  j          func_00100540
    /* 3A240 0013A240 4400A0AC */   sw        $0, 0x44($5)
.align 2
  .L0013A244:
    /* 3A244 0013A244 0800E003 */  jr         $31
    /* 3A248 0013A248 00000000 */   nop
endlabel func_0013A220
    /* 3A24C 0013A24C 00000000 */  nop
```
