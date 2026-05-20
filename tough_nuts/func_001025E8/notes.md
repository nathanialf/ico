# func_001025E8 — parked

VRAM: 0x001025E8 (file_off 0x0025E8)
Asm source: asm/nonmatchings/src/delayFreeManager/func_001025E8.s

## Attempt at 2026-05-20

**Reason parked:** 3 identical zero-loops; loop 1 matches with p=D_X; p+=0xFF split, but loops 2/3 emit '+1020; +1024' instead of '+0; +2044' — gcc fold heuristic

**TU:** `src/delayFreeManager.c`

**Seed:** `tough_nuts/func_001025E8/func_001025E8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631B20, 1
.extern D_00631B24, 1

.align 3
nonmatching func_001025E8, 0x98

glabel func_001025E8
    /* 25E8 001025E8 6600023C */  lui        $2, %hi(D_0065ED40)
    /* 25EC 001025EC FF000324 */  addiu      $3, $0, 0xFF
    /* 25F0 001025F0 40ED4224 */  addiu      $2, $2, %lo(D_0065ED40)
    /* 25F4 001025F4 FC034224 */  addiu      $2, $2, 0x3FC
.align 2
  .L001025F8:
    /* 25F8 001025F8 000040AC */  sw         $0, 0x0($2)
    /* 25FC 001025FC FFFF6324 */  addiu      $3, $3, -0x1
    /* 2600 00102600 FCFF4224 */  addiu      $2, $2, -0x4
    /* 2604 00102604 00000000 */  nop
    /* 2608 00102608 00000000 */  nop
    /* 260C 0010260C FAFF6104 */  bgez       $3, .L001025F8
    /* 2610 00102610 00000000 */   nop
    /* 2614 00102614 6600023C */  lui        $2, %hi(D_0065ED40)
    /* 2618 00102618 FF000324 */  addiu      $3, $0, 0xFF
    /* 261C 0010261C 40ED4224 */  addiu      $2, $2, %lo(D_0065ED40)
    /* 2620 00102620 FC074224 */  addiu      $2, $2, 0x7FC
    /* 2624 00102624 00000000 */  nop
.align 2
  .L00102628:
    /* 2628 00102628 000040AC */  sw         $0, 0x0($2)
    /* 262C 0010262C FFFF6324 */  addiu      $3, $3, -0x1
    /* 2630 00102630 FCFF4224 */  addiu      $2, $2, -0x4
    /* 2634 00102634 00000000 */  nop
    /* 2638 00102638 00000000 */  nop
    /* 263C 0010263C FAFF6104 */  bgez       $3, .L00102628
    /* 2640 00102640 00000000 */   nop
    /* 2644 00102644 6600023C */  lui        $2, %hi(D_0065ED40)
    /* 2648 00102648 FF000324 */  addiu      $3, $0, 0xFF
    /* 264C 0010264C 40ED4224 */  addiu      $2, $2, %lo(D_0065ED40)
    /* 2650 00102650 FC0B4224 */  addiu      $2, $2, 0xBFC
    /* 2654 00102654 00000000 */  nop
.align 2
  .L00102658:
    /* 2658 00102658 000040AC */  sw         $0, 0x0($2)
    /* 265C 0010265C FFFF6324 */  addiu      $3, $3, -0x1
    /* 2660 00102660 FCFF4224 */  addiu      $2, $2, -0x4
    /* 2664 00102664 00000000 */  nop
    /* 2668 00102668 00000000 */  nop
    /* 266C 0010266C FAFF6104 */  bgez       $3, .L00102658
    /* 2670 00102670 00000000 */   nop
    /* 2674 00102674 349280AF */  sw         $0, (D_00631B24) /* gp_rel: (D_00631B24) */
    /* 2678 00102678 0800E003 */  jr         $31
    /* 267C 0010267C 309280AF */   sw        $0, (D_00631B20) /* gp_rel: (D_00631B20) */
endlabel func_001025E8
```
