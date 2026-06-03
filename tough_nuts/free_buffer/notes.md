# free_buffer — parked

VRAM: 0x0019B120 (file_off 0x09B120)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_readbuf/free_buffer.s

## Attempt at 2026-06-03

**Reason parked:** rc5 near-miss: copy<->cond regalloc swap (copy wants a2/cond v1; gcc gives copy v1). Pure reg-swap, structurally exact (move/daddu/slt/movn/subu/sw all present). ~18 distinct hand forms across sessions; gcc reorders copy-before-slt and pins it v1 regardless of source order. Retired REG pin would fix; permuter live-range-split is the path.

**TU:** `ito/mpeg/mv_readbuf.c`

**Seed:** `tough_nuts/free_buffer/free_buffer.c`

Disassembly:

```
.align 3
nonmatching free_buffer, 0x1C

glabel free_buffer
    /* 9B120 0019B120 0C00828C */  lw         $2, 0xC($4)
    /* 9B124 0019B124 2D304000 */  daddu      $6, $2, $0
    /* 9B128 0019B128 2A18A200 */  slt        $3, $5, $2
    /* 9B12C 0019B12C 0B10A300 */  movn       $2, $5, $3
    /* 9B130 0019B130 2330C200 */  subu       $6, $6, $2
    /* 9B134 0019B134 0800E003 */  jr         $31
    /* 9B138 0019B138 0C0086AC */   sw        $6, 0xC($4)
endlabel free_buffer
    /* 9B13C 0019B13C 00000000 */  nop
```
