# func_0013C488 — parked

VRAM: 0x0013C488 (file_off 0x03C488)
Asm source: asm/matchings/ios/pad/func_0013C488.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (KEEP_LIVE_MEM)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013C488/func_0013C488.c`

Disassembly:

```
.align 3
nonmatching func_0013C488, 0x38

glabel func_0013C488
    /* 3C488 0013C488 000085AC */  sw         $5, 0x0($4)
    /* 3C48C 0013C48C 0A00A294 */  lhu        $2, 0xA($5)
    /* 3C490 0013C490 0200A694 */  lhu        $6, 0x2($5)
    /* 3C494 0013C494 0600A394 */  lhu        $3, 0x6($5)
    /* 3C498 0013C498 80100200 */  sll        $2, $2, 2
    /* 3C49C 0013C49C 80300600 */  sll        $6, $6, 2
    /* 3C4A0 0013C4A0 2110A200 */  addu       $2, $5, $2
    /* 3C4A4 0013C4A4 2130A600 */  addu       $6, $5, $6
    /* 3C4A8 0013C4A8 80180300 */  sll        $3, $3, 2
    /* 3C4AC 0013C4AC 2128A300 */  addu       $5, $5, $3
    /* 3C4B0 0013C4B0 0C0082AC */  sw         $2, 0xC($4)
    /* 3C4B4 0013C4B4 080085AC */  sw         $5, 0x8($4)
    /* 3C4B8 0013C4B8 0800E003 */  jr         $31
    /* 3C4BC 0013C4BC 040086AC */   sw        $6, 0x4($4)
endlabel func_0013C488
```
