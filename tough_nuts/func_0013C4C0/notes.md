# func_0013C4C0 — parked

VRAM: 0x0013C4C0 (file_off 0x03C4C0)
Asm source: asm/nonmatchings/ios/pad/func_0013C4C0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (KEEP_LIVE_MEM)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013C4C0/func_0013C4C0.c`

Disassembly:

```
.align 3
nonmatching func_0013C4C0, 0x50

glabel func_0013C4C0
    /* 3C4C0 0013C4C0 11000224 */  addiu      $2, $0, 0x11
    /* 3C4C4 0013C4C4 030088A0 */  sb         $8, 0x3($4)
    /* 3C4C8 0013C4C8 000082A0 */  sb         $2, 0x0($4)
    /* 3C4CC 0013C4CC 040085AC */  sw         $5, 0x4($4)
    /* 3C4D0 0013C4D0 140086AC */  sw         $6, 0x14($4)
    /* 3C4D4 0013C4D4 020087A0 */  sb         $7, 0x2($4)
    /* 3C4D8 0013C4D8 240080A0 */  sb         $0, 0x24($4)
    /* 3C4DC 0013C4DC 080080A4 */  sh         $0, 0x8($4)
    /* 3C4E0 0013C4E0 120080A4 */  sh         $0, 0x12($4)
    /* 3C4E4 0013C4E4 100080A4 */  sh         $0, 0x10($4)
    /* 3C4E8 0013C4E8 0C0080A4 */  sh         $0, 0xC($4)
    /* 3C4EC 0013C4EC 0A0080A4 */  sh         $0, 0xA($4)
    /* 3C4F0 0013C4F0 260080A0 */  sb         $0, 0x26($4)
    /* 3C4F4 0013C4F4 180080A4 */  sh         $0, 0x18($4)
    /* 3C4F8 0013C4F8 220080A4 */  sh         $0, 0x22($4)
    /* 3C4FC 0013C4FC 200080A4 */  sh         $0, 0x20($4)
    /* 3C500 0013C500 1C0080A4 */  sh         $0, 0x1C($4)
    /* 3C504 0013C504 1A0080A4 */  sh         $0, 0x1A($4)
    /* 3C508 0013C508 0800E003 */  jr         $31
    /* 3C50C 0013C50C 270080A0 */   sb        $0, 0x27($4)
endlabel func_0013C4C0
```
