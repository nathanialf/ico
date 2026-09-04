# executeSEPackageWithNoGObj — parked

VRAM: 0x001CE4F0 (file_off 0x0CE4F0)
Asm source: asm/aug6/nonmatchings/sugipon/src/frameDependSequence/executeSEPackageWithNoGObj.s

## Attempt at 2026-06-09

**Reason parked:** best **rc3** (from 46). Progress: rc12 hand → permuter found `stride = i*(stride=12)` (self-ref forces mflo to reuse the stride reg → v0/v1 swap FIXED) → adopted rc9 → hand found the double-test via a COMPOUND condition: `term != -1 && term != end` (order matters: `!=-1` first = the exit `beq` vs literal -1; `!=end` second = the loop-back `bne` vs `end`/a2). That gcc-CSEs to one load + beq + bne = ROM's loop1. rc9→8→3.

SEED (rc3 best):
```c
int stride = 12, end = -1, i = a0, flag = D_0062AF94; int *p, n;
while (((SeReq*)((char*)D_00535F68 + (stride = i*(stride=12))))->term != -1 &&
       ((SeReq*)((char*)D_00535F68 + stride))->term != end) { i++; }
if (flag) debug_StdPrintfDummy(D_006117C8, flag);
p = (int*)&D_00535F68[i];
for (n=1; n>=0; n--) { if(*p){ soundSeDefPlayWithVolumeRate(*p,0xFFFFFFFF,0,1);
    if(D_0062AF94) debug_StdPrintfDummy(D_00611700, D_005CD670[*p], 0xFFFFFFFF);} p++; }
```

RESIDUAL (rc3, all PURE SCHEDULING TIES, confirmed robust across ~10 hand forms):
- B0: guard `addu v0,a3,v0` (base+product) vs built `addu v0,v0,a3` (product+base). Per-instance: ROM's guard is base-first but its loop is product-first (`v1,a3`), from the SAME source expr — uncontrollable via shared source.
- B6: loop2 preheader two independent `addiu` consts — ROM `addiu s2,60; addiu s1,1` vs built `s1,1; s2,60` (counter vs 0x3C name-stride order).
Both are gcc sched1/sched2 ties → permuter food (it cracked the v0/v1 mflo the same way). Re-permute from this rc3 seed at the next 30-stall.

## RESOLUTION (b) — permuter-exhausted at rc2 (2026-06-09)

Reached the genuine 30-stall at **best=rc2** (the rc3 notes above were superseded:
the permuter's `stride=i*(stride=12)` fixed v0/v1 → rc9; the hand compound
`term!=-1 && term!=end` gave the loop1 double-test → rc3; the permuter's
`base-(-product)` negate-subtract fixed the guard `addu` order → **rc2**).

The seed (`executeSEPackageWithNoGObj.c`) is the rc2 form. THREE permuter shots (~50k iterations
total, incl. one at the stall-30 gate) found **nothing below rc2** — the lone
residual is B6: loop2's two independent preheader consts `addiu 1` (counter) and
`addiu 60` (D_005CD670 name stride) emit in swapped order vs ROM. It's a pure
sched2 register-order tie ($17 vs $18): the counter is RTL-early (for-init), the
60 RTL-late (assert-hoisted), so source-order can't reorder them, and the
permuter's mutation space doesn't include flipping two independent `li`s. A true
floor at rc2 (like func_001354B8 @2). RESUME: re-attack B6 with a fresh idea that
makes the 60 RTL-early or the counter RTL-late.

**TU:** `sugipon/src/frameDependSequence.c`

**Seed:** `tough_nuts/executeSEPackageWithNoGObj/executeSEPackageWithNoGObj.c`

Disassembly:

```
.align 3
nonmatching executeSEPackageWithNoGObj, 0x12C

glabel executeSEPackageWithNoGObj
    /* CE4F0 001CE4F0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* CE4F4 001CE4F4 0C000224 */  addiu      $2, $0, 0xC
    /* CE4F8 001CE4F8 0000B0FF */  sd         $16, 0x0($29)
    /* CE4FC 001CE4FC FFFF0624 */  addiu      $6, $0, -0x1
    /* CE500 001CE500 2D808000 */  daddu      $16, $4, $0
    /* CE504 001CE504 1000B1FF */  sd         $17, 0x10($29)
    /* CE508 001CE508 18100202 */  mult       $2, $16, $2
    /* CE50C 001CE50C 5300113C */  lui        $17, %hi(D_00535F68)
    /* CE510 001CE510 5000BFFF */  sd         $31, 0x50($29)
    /* CE514 001CE514 685F2726 */  addiu      $7, $17, %lo(D_00535F68)
    /* CE518 001CE518 4000B4FF */  sd         $20, 0x40($29)
    /* CE51C 001CE51C 3000B3FF */  sd         $19, 0x30($29)
    /* CE520 001CE520 2000B2FF */  sd         $18, 0x20($29)
    /* CE524 001CE524 2110E200 */  addu       $2, $7, $2
    /* CE528 001CE528 0800438C */  lw         $3, 0x8($2)
    /* CE52C 001CE52C 0F006610 */  beq        $3, $6, .L001CE56C
    /* CE530 001CE530 A4A3858F */   lw        $5, %gp_rel(D_0062AF94)($28)
    /* CE534 001CE534 6100043C */  lui        $4, %hi(D_006117C8)
    /* CE538 001CE538 6100143C */  lui        $20, %hi(D_00611700)
    /* CE53C 001CE53C 0C000224 */  addiu      $2, $0, 0xC
.align 2
  .L001CE540:
    /* CE540 001CE540 01001026 */  addiu      $16, $16, 0x1
    /* CE544 001CE544 18180202 */  mult       $3, $16, $2
    /* CE548 001CE548 21106700 */  addu       $2, $3, $7
    /* CE54C 001CE54C 0800428C */  lw         $2, 0x8($2)
    /* CE550 001CE550 FFFF0324 */  addiu      $3, $0, -0x1
    /* CE554 001CE554 07004310 */  beq        $2, $3, .L001CE574
    /* CE558 001CE558 00000000 */   nop
    /* CE55C 001CE55C F8FF4614 */  bne        $2, $6, .L001CE540
    /* CE560 001CE560 0C000224 */   addiu     $2, $0, 0xC
    /* CE564 001CE564 03000010 */  b          .L001CE574
    /* CE568 001CE568 00000000 */   nop
.align 2
  .L001CE56C:
    /* CE56C 001CE56C 6100043C */  lui        $4, %hi(D_006117C8)
    /* CE570 001CE570 6100143C */  lui        $20, %hi(D_00611700)
.align 2
  .L001CE574:
    /* CE574 001CE574 0400A010 */  beqz       $5, .L001CE588
    /* CE578 001CE578 0C000324 */   addiu     $3, $0, 0xC
    /* CE57C 001CE57C F290060C */  jal        debug_StdPrintfDummy
    /* CE580 001CE580 C8178424 */   addiu     $4, $4, %lo(D_006117C8)
    /* CE584 001CE584 0C000324 */  addiu      $3, $0, 0xC
.align 2
  .L001CE588:
    /* CE588 001CE588 685F2426 */  addiu      $4, $17, %lo(D_00535F68)
    /* CE58C 001CE58C 18180302 */  mult       $3, $16, $3
    /* CE590 001CE590 5D00023C */  lui        $2, %hi(D_005CD670)
    /* CE594 001CE594 70D65324 */  addiu      $19, $2, %lo(D_005CD670)
    /* CE598 001CE598 3C001224 */  addiu      $18, $0, 0x3C
    /* CE59C 001CE59C 01001124 */  addiu      $17, $0, 0x1
    /* CE5A0 001CE5A0 21806400 */  addu       $16, $3, $4
    /* CE5A4 001CE5A4 00000000 */  nop
.align 2
  .L001CE5A8:
    /* CE5A8 001CE5A8 0000028E */  lw         $2, 0x0($16)
    /* CE5AC 001CE5AC FFFF053C */  lui        $5, (0xFFFFFFFF >> 16)
    /* CE5B0 001CE5B0 2D300000 */  daddu      $6, $0, $0
    /* CE5B4 001CE5B4 FFFFA534 */  ori        $5, $5, (0xFFFFFFFF & 0xFFFF)
    /* CE5B8 001CE5B8 01000724 */  addiu      $7, $0, 0x1
    /* CE5BC 001CE5BC FFFF3126 */  addiu      $17, $17, -0x1
    /* CE5C0 001CE5C0 0C004010 */  beqz       $2, .L001CE5F4
    /* CE5C4 001CE5C4 2D204000 */   daddu     $4, $2, $0
    /* CE5C8 001CE5C8 F60A050C */  jal        soundSeDefPlayWithVolumeRate
    /* CE5CC 001CE5CC 00000000 */   nop
    /* CE5D0 001CE5D0 FFFF063C */  lui        $6, (0xFFFFFFFF >> 16)
    /* CE5D4 001CE5D4 A4A3828F */  lw         $2, %gp_rel(D_0062AF94)($28)
    /* CE5D8 001CE5D8 00178426 */  addiu      $4, $20, %lo(D_00611700)
    /* CE5DC 001CE5DC 05004010 */  beqz       $2, .L001CE5F4
    /* CE5E0 001CE5E0 FFFFC634 */   ori       $6, $6, (0xFFFFFFFF & 0xFFFF)
    /* CE5E4 001CE5E4 0000058E */  lw         $5, 0x0($16)
    /* CE5E8 001CE5E8 1810B200 */  mult       $2, $5, $18
    /* CE5EC 001CE5EC F290060C */  jal        debug_StdPrintfDummy
    /* CE5F0 001CE5F0 21285300 */   addu      $5, $2, $19
.align 2
  .L001CE5F4:
    /* CE5F4 001CE5F4 ECFF2106 */  bgez       $17, .L001CE5A8
    /* CE5F8 001CE5F8 04001026 */   addiu     $16, $16, 0x4
    /* CE5FC 001CE5FC 5000BFDF */  ld         $31, 0x50($29)
    /* CE600 001CE600 4000B4DF */  ld         $20, 0x40($29)
    /* CE604 001CE604 3000B3DF */  ld         $19, 0x30($29)
    /* CE608 001CE608 2000B2DF */  ld         $18, 0x20($29)
    /* CE60C 001CE60C 1000B1DF */  ld         $17, 0x10($29)
    /* CE610 001CE610 0000B0DF */  ld         $16, 0x0($29)
    /* CE614 001CE614 0800E003 */  jr         $31
    /* CE618 001CE618 6000BD27 */   addiu     $29, $29, 0x60
endlabel executeSEPackageWithNoGObj
    /* CE61C 001CE61C 00000000 */  nop
```
