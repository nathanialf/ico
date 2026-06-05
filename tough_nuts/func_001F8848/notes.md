# func_001F8848 — parked

VRAM: 0x001F8848 (file_off 0x0F8848)
Asm source: asm/aug6/nonmatchings/seki/src/DmaPacket/func_001F8848.s

## Attempt at 2026-06-05

**Reason parked:** rc4 index-scale vs coloring coupling: ROM reads D[idx+1] as idx*4 + load-disp 4 (struct-member offset); simple int[] array D[idx+1] folds to (idx+1)*4 (correct a0/a1 coloring, best=4); struct slots[idx] fixes the scale but flips a0<->v1 %hi/&base coloring (rc10). 30-stall: ~15 distinct shapes (array, ptr-temp, struct x3 orderings, byte-arith, hybrid-cast, union, void-ptr-buf) — index-fix and coloring appear coupled. Permuter-class.

**TU:** `seki/src/DmaPacket.c`

**Seed:** `tough_nuts/func_001F8848/func_001F8848.c`

Disassembly:

```
.align 3
nonmatching func_001F8848, 0x34

glabel func_001F8848
    /* F8848 001F8848 4C00043C */  lui        $4, %hi(D_004C3850)
    /* F884C 001F884C 5038838C */  lw         $3, %lo(D_004C3850)($4)
    /* F8850 001F8850 50388524 */  addiu      $5, $4, %lo(D_004C3850)
    /* F8854 001F8854 01006338 */  xori       $3, $3, 0x1
    /* F8858 001F8858 80100300 */  sll        $2, $3, 2
    /* F885C 001F885C 503883AC */  sw         $3, %lo(D_004C3850)($4)
    /* F8860 001F8860 2110A200 */  addu       $2, $5, $2
    /* F8864 001F8864 0400438C */  lw         $3, 0x4($2)
    /* F8868 001F8868 1C00A0AC */  sw         $0, 0x1C($5)
    /* F886C 001F886C 1000A3AC */  sw         $3, 0x10($5)
    /* F8870 001F8870 1400A0AC */  sw         $0, 0x14($5)
    /* F8874 001F8874 0800E003 */  jr         $31
    /* F8878 001F8878 1800A0AC */   sw        $0, 0x18($5)
endlabel func_001F8848
    /* F887C 001F887C 00000000 */  nop
```
