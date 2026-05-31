# func_001886D0 — parked

VRAM: 0x001886D0 (file_off 0x0886D0)
Asm source: asm/matchings/camera-ico2/func_001886D0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/camera-ico2.c`

**Seed:** `tough_nuts/func_001886D0/func_001886D0.c`

Disassembly:

```
.align 3
nonmatching func_001886D0, 0x24

glabel func_001886D0
    /* 886D0 001886D0 6D00023C */  lui        $2, %hi(D_006D04B4)
    /* 886D4 001886D4 01000324 */  addiu      $3, $0, 0x1
    /* 886D8 001886D8 FF008430 */  andi       $4, $4, 0xFF
    /* 886DC 001886DC 03008010 */  beqz       $4, .L001886EC
    /* 886E0 001886E0 B40443A0 */   sb        $3, %lo(D_006D04B4)($2)
    /* 886E4 001886E4 F8330608 */  j          func_0018CFE0
    /* 886E8 001886E8 00000000 */   nop
.align 2
  .L001886EC:
    /* 886EC 001886EC 0800E003 */  jr         $31
    /* 886F0 001886F0 00000000 */   nop
endlabel func_001886D0
    /* 886F4 001886F4 00000000 */  nop
```
