# func_00246608 — parked

VRAM: 0x00246608 (file_off 0x146608)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00246608.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00246608/func_00246608.c`

Disassembly:

```
.align 3
nonmatching func_00246608, 0x88

glabel func_00246608
    /* 146608 00246608 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14660C 0024660C 1000B1FF */  sd         $17, 0x10($29)
    /* 146610 00246610 2000BFFF */  sd         $31, 0x20($29)
    /* 146614 00246614 7100113C */  lui        $17, %hi(D_0070F600)
    /* 146618 00246618 0A000010 */  b          .L00246644
    /* 14661C 0024661C 0000B0FF */   sd        $16, 0x0($29)
.align 2
  .L00246620:
    /* 146620 00246620 1000023C */  lui        $2, %hi(D_FFFFF)
    /* 146624 00246624 FFFF0324 */  addiu      $3, $0, -0x1
.align 2
  .L00246628:
    /* 146628 00246628 FFFF4224 */  addiu      $2, $2, %lo(D_FFFFF)
    /* 14662C 0024662C 00000000 */  nop
    /* 146630 00246630 00000000 */  nop
    /* 146634 00246634 00000000 */  nop
    /* 146638 00246638 00000000 */  nop
    /* 14663C 0024663C FAFF4314 */  bne        $2, $3, .L00246628
    /* 146640 00246640 00000000 */   nop
.align 2
  .L00246644:
    /* 146644 00246644 00F63026 */  addiu      $16, $17, %lo(D_0070F600)
    /* 146648 00246648 0080053C */  lui        $5, (0x80000003 >> 16)
    /* 14664C 0024664C 2D200002 */  daddu      $4, $16, $0
    /* 146650 00246650 0300A534 */  ori        $5, $5, (0x80000003 & 0xFFFF)
    /* 146654 00246654 EA09090C */  jal        func_002427A8
    /* 146658 00246658 2D300000 */   daddu     $6, $0, $0
    /* 14665C 0024665C 03004304 */  bgezl      $2, .L0024666C
    /* 146660 00246660 2400028E */   lw        $2, 0x24($16)
    /* 146664 00246664 05000010 */  b          .L0024667C
    /* 146668 00246668 FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L0024666C:
    /* 14666C 0024666C ECFF4010 */  beqz       $2, .L00246620
    /* 146670 00246670 5500023C */   lui       $2, %hi(D_0054AB34)
    /* 146674 00246674 34AB40AC */  sw         $0, %lo(D_0054AB34)($2)
    /* 146678 00246678 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0024667C:
    /* 14667C 0024667C 2000BFDF */  ld         $31, 0x20($29)
    /* 146680 00246680 1000B1DF */  ld         $17, 0x10($29)
    /* 146684 00246684 0000B0DF */  ld         $16, 0x0($29)
    /* 146688 00246688 0800E003 */  jr         $31
    /* 14668C 0024668C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_00246608
```

## Session 2026-06-13 findings (could not resolve)
- Permuter fired REAL run (3600+ iterations, 88KB log, base score ~80): NO
  score-0 crack. The counter-register tie ($v0 vs $v1) survives permutation.
- match_loop/match_diff COMPILE-FAILS on this seed (real_count -1): quick_diff
  output has no `===` diff blocks → parse_blocks() returns None → reported as
  compile-fail. compile_c.sh itself SUCCEEDS (only unrelated warnings). The
  inline `__asm__("nop\nnop\nnop\nnop")` 4-nop timing block is the likely cause —
  the asm-differ can't align/emit blocks for the func, so it cannot be measured
  or hand-iterated via the loop. NEXT SESSION: first fix the quick_diff/differ
  path for inline-asm coalesced-TU funcs (or find a non-asm way to emit the 4
  timing nops), THEN attack the $v0/$v1 counter tie. Until measurable, neither
  hand-iteration nor a fair stall count is possible.
- Still owed by the stop-hook (best=8, stall<30, no match).

## Session 2026-06-13 BREAKTHROUGH (differ unblocked, counter tie solved)
1. The "compile-fail" was NOT the inline asm — it was MISSING EXTERNS. D_0070F600
   and D_0054AB34 are declared in the TU AFTER func_00246608 (lines ~1060-62),
   so they're undeclared at this function. FIX: add `extern int D_0070F600[];
   extern int D_0054AB34[];` (plus `extern char D_FFFFF[];`) immediately before
   the function. With those, match_loop diff WORKS (measurable, rc9/rc10).
2. COUNTER-REG TIE SOLVED: the goto/do-while-via-goto form puts the loop counter
   in $v1 (wrong); a `for (i=0x100000; i!=-1; i--)` OR a structured `do{}while`
   puts it in $v0 (matches ROM) with `-1` in $v1. `i=0x100000` (literal) is
   byte-equal to `lui %hi(D_FFFFF)` / `addiu %lo(D_FFFFF)` (the assembler
   reloc-matches; differ shows false 0x10-vs-reloc diffs).
3. REMAINING (2 real diffs, ninja still fails):
   (a) busy-wait NOP PLACEMENT: ROM loop = `addiu i--; nop×4; bne; nop(delay)`.
       Built reorders the bare `__asm__("nop\nnop\nnop\nnop")` to the loop TOP
       (nop×4 BEFORE the addiu) and pads 3 extra nops after — total 7-8 nops vs
       ROM's 4+delay. Tying the asm to i via `: : "r"(i)` did NOT fix it (loop
       rotation / bne-delay-fill places the asm first). NEXT: find the construct
       that emits exactly `addiu; nop×4; bne; nop` — maybe a specific asm form,
       or block gcc's bne-delay-fill so the addiu stays at the loop head.
   (b) final store `D_0054AB34[0]=0; return 0`: ROM puts the %hi addr in $v0
       (reused for the return-0), built uses $v1 (return-0 set before the store).
- Now MEASURABLE + counter tie solved → close. Still owed (no match, stall<30).
