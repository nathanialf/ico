# _sysbitNext — parked 2026-08-17 (supersedes the 2026-08-06 park)

VMA 0x00258450 · 7 insns · 0x1C bytes · `src/cod/vendor_2575C0.c`
Identical-residual sibling: `ftoi` (`src/cod/vendor_100C90.c`, 36 insns, still a stub).
These are the only two sites in the ROM ending `dsll32 / jr / dsra32`.

```
ld     $2, 0x0($4)
addiu  $3, $0, 0x40
subu   $3, $3, $5
dsrlv  $2, $2, $3
dsll32 $2, $2, 0
jr     $31
 dsra32 $2, $2, 0     <- in the jr delay slot
```

## READ THIS FIRST — the 2026-08-06 notes were wrong about the residual

They described this as a coloring/allocation problem and framed the parked seed as one instruction
away. **That seed could never have matched, for a structural reason.** `define_delay`
(`mips.md:131-134`) requires `length == 1`. `truncdisi2` (`mips.md:4066`) is ONE insn of length 2,
and the combiner pattern at `mips.md:4113-4136` — `(truncate:SI (ashiftrt:DI x K))` — also carries a
hard `(set_attr "length" "2")` even though it prints a single `dsra` when `K >= 32`. **So every
`int`-returning spelling has a length-2 final insn and is structurally ineligible for the `jr`
slot.** Measured both ways (`probes/01`, `probes/04`).

Consequence: **the function returns `long long`.** ROM's split pair can only be
`ashldi3_internal4` / `ashrdi3_internal4` (`mips.md:7447/7802`), the only patterns printing
`dsll %0,%1,32` / `dsra %0,%1,32` at length 1, and both are DImode.

Their other claim — that the pair can survive inside one basic block — holds only when an extra use
of the `<< 32` result exists, and every such use costs bytes (see §3).

## What the function IS (recovered from the siblings and the call sites)

`src/cod/vendor_2575C0.c` is a bitstream reader. The struct, from the matched siblings:
`{ u64 w; u8 *cur; u8 *fill; int nbits; …; long long bitpos; u8 *start, *end; int size; }`.
`_sysbitFlush` is `advance(bs, n)` (`w <<= n; nbits -= n;` plus a byte-refill loop to `nbits >= 57`),
so **`_sysbitNext` is `showBits(bs, n) = w >> (64 - n)`, narrowed to 32 bits**;
`_sysbitGet` is `getBits`, `_sysbitMarker` is `getBit`. Callers request n ∈ {1,3,9,15,30,32,34,56}.

Provenance (via `baserom/aug6/MAIN.MAP`): this lives in `libsndn2.a(sound.o)` and is file-local.
The sibling is in `libkernl.a(kprintf.o)`. The aug6 prototype's copy is **byte-identical to retail**,
so the prototype offers no extra shape information, and the ELF is stripped (no `.mdebug`).

## §3 — why the natural C cannot produce the split pair

`make_compound_operation`'s ASHIFTRT case (`combine.c:6178-6194`) calls
`make_extraction(DImode, inner, pos = rhs - lhs, len = 64 - rhs)`. Its first clause
(`combine.c:5670-5673`) requires `pos % BITS_PER_WORD == 0`, and `BITS_PER_WORD == 64` here — so
`(x << A) >> 32` folds to `(sign_extend:DI (subreg:SI X))` = `extendsidi2` = a bare `move`
**only when A == 32**, which is exactly ROM's amount. Measured: A ∈ {0,1,8,16,31,33,48} all survive
as two length-1 insns with `dsra` in the slot. `inner` is always a REG here (the `dsrlv` is its own
insn), so the `force_to_mode` escape at `combine.c:5722` is unreachable.

The fold is defeated by either a basic-block boundary or an earlier use of the `<< 32` result:

- **BB boundary.** `flow.c:3374-3392` builds one LOG_LINK per def, to the first use *in the same
  block*; `find_basic_blocks_1` starts a block only at a `CODE_LABEL`, `JUMP_INSN`, `BARRIER` or
  abnormal call. Compiled and collapsed before combine: `goto`+label, `do{}while(0)`, empty `switch`,
  `?:`, `for`/`while`+`break`, an inlined `static __inline__` helper (its return label does not
  survive), a non-static `__inline__` out-of-line body (byte-identical to plain), duplicated
  `return`s. **Only a statement-level `if/else` survives**, because the early `jump_optimize` runs
  with `cross_jump = 0` so the arms stay two blocks through combine, and only the post-reload `jump2`
  cross-jumps them and deletes the branch.
- **Earlier use.** Any earlier use defeats the fold automatically (`added_sets_2`, `combine.c:1601`,
  forces a PARALLEL that fails recog) — verified with a store (`probes/08`). But a *dead* use is
  deleted by `life_analysis` before links are built, and a use combine deletes has its link re-placed
  on the next use by `distribute_links` (`combine.c:12060-12077`). Probes with a provably-zero second
  consumer (`|(int)v`, `& 0xFFFFFFFF`, duplicated-expression cse copies, `volatile` on `*p`) all
  still fold.

## Why it is parked and NOT matched

Byte-exact and full-ninja green, re-measured twice (`probes/05`):

```c
long long _sysbitNext(unsigned long long *p, int n)
{
    long long w; int k;
    if (n > 0) { k = 64 - n; w = (long long)(*p >> k) << 32; }
    else       { k = 64 - n; w = (long long)(*p >> k) << 32; }
    return w >> 32;
}
```

**Rejected as a crutch.** ROM is exactly 7 instructions, so there is no room for the arms to differ —
the branch is forced to have code-identical arms, emits nothing, and exists only to stop combine
folding. A redundant `& 0xFFFFFFFFu` in one arm is the same crutch renamed. A tree-wide scan found
**no precedent** for `if (c) X; else X;` anywhere in `src/`, `ios/` or `ito/`. The crutch is the
*branch*, not the shifts.

Load-bearing and legitimate when the real shape is found: the callers must be retyped. With
`long long ret = _sysbitNext(...)`, `_sysbitGet`/`_sysbitMarker` stay rc0 and the ELF matches;
without it each gains a `dsll32/dsra32` pair and the SHA breaks. Also measured: `k = 64 - n` must be
computed INSIDE the arm — hoisting it keeps the last four insns exact but reorders the head to
`li/subu/ld` where ROM is `ld/li/subu`.

## Control case that sharpens the residual

`dptoul` (`asm/nonmatchings/src/cod/vendor_25E1E8/`) is a genuine two-way join
(`dsllv` arm / `dsrlv` arm) whose narrowing at the join is the **adjacent** `dsll32;dsra32`. So a
join by itself is not the distinguishing feature: ROM's split pair specifically needs
`v = <expr> << 32` in the **predecessors** and `return v >> 32` at the join.

## Next levers, in the order I would run them

1. **Drive the sibling `ftoi` to rc0 first.** Its arms *genuinely differ*, so it can exhibit
   the honest form of this idiom without the identical-arm confound. `scratchpad/n450b/b/A3.c`
   already reproduces its ROM structure and split tail with the per-arm `<< 32` shape, and its
   natural `return (int)m;` spelling shows the same residual as here (`b/A1.c`). If it lands, either
   the real construct is named — and may supply a genuinely non-identical second block here — or the
   per-arm `<< 32` is proven to be dev source.
2. **Hunt `sound.o`'s other bitstream functions for a "park an int in the high half of a `long long`"
   data model** (likely a `#define`). That is the only thing that would make a per-arm `<< 32` read
   as intent rather than device.

Probes: `probes/` here, full corpus at `scratchpad/n450b/` (~90 compiled probes; `keep/` are the
named ones). Everything above was COMPILED unless it cites a compiler source line.
