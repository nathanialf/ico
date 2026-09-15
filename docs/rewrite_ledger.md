# Rewrite ledger: retiring the pre- and post-processing of toolchain output

2026-09-15. One pass over every pre- and post-processing rewrite of ee-gcc's or
ee-as's output in `tools/compile_c.sh`, `tools/quick_diff.sh` and
`tools/preprocess_old_as.py`, measured rule by rule.

Method per rule: remove the rule, `rm -rf asm/nonmatchings .cache build`,
`tools/build.sh setup && .venv/bin/ninja`, then compare every one of the 474
objects against the objects built with the rule in place. The comparison is
`objdump -dzr` plus `objdump -s` over the allocated sections, with `.mdebug`,
`.comment` and `.reginfo` excluded: a removed `nop` line shifts the line map in
`.mdebug` without changing a byte of code, and counting that as a difference
hides the rules that are genuinely dead. The gate is the ROM SHA-1
`a401d1e5a20b1659189a8b1026a8eb35811dc9ca`.

Baseline for every row: the tree at a4bad1de7, ROM SHA-1 above, 474 objects.

## Table

| rule | pattern sites in the tree | objects changed when removed | outcome |
|---|---|---|---|
| FCC `#nop` promotion | 1100 | 0 | dead, deleted |
| COP1-move wrap, case 1 (`m[ft]c1` + `#nop` + dependent) | 256 | 0 | dead, deleted |
| COP1-move wrap, case 2 (`mtc1` + `cvt`/`c.X.s`) | 488 | 0 | dead, deleted |
| COP1-move wrap, case 2 `mtc1;cvt;b` slack sub-rule | 1 | 1 (`sce/libsndn2/sg.o`) | (c) `_SgContPolta` reverted to INCLUDE_ASM |
| jr/j return wrap, FP store or convert clause (`s.s`/`swc1`/`cvt`) | 4 | 0 | dead, deleted |
| jr/j return wrap, quad/COP2 clause (`sqc2`/`lqc2`/`sq`) | 0 | 0 | fires nowhere, deleted |
| jr/j return wrap, post-inline-asm clause (`#NO_APP`) | 69 | 6 | kept, see below |
| `j <func>` tail-call unaligned-store wrap | 2 | 0 | dead, deleted |
| `move` to `daddu` | 24057 | 0 | dead, deleted |
| `break N` to `break 0,N` | 349 | 0 | dead, deleted |

`tools/preprocess_old_as.py` needed no change: `.include` flattening, the
`%gp_rel` to bare-symbol translation with its `.extern` header, and the
`.lit4_slot` to `li.s` restoration are scaffolding that lets the period
assembler read a mixed C plus INCLUDE_ASM TU at all. None of them rewrites an
instruction the compiler emitted.

## What the probes established about ee-as 2.9-991111

- It never swaps an instruction into a BRANCH delay slot. Probed with a bare
  `addu; b L` pair under no flags, `-O`, `-O0`, `-O1`, `-O2`, `-g`, `.set bopt`,
  `.set reorder`, `-mips1`, `-mips3`, `-mcpu=4000`, `-mcpu=5900` and
  `-no-m5900`: the delay slot stays `nop` in every one.
- It does swap into a JUMP-REGISTER delay slot, which is where the return-wrap
  rules came from.
- It fills the R5900 FCC-update hazard slot itself, which is why the `#nop`
  promotion was dead: 1100 sites, not one byte.
- It already encodes `move $r,$s` as `daddu $r,$s,$0` and puts a single-operand
  `break N` code in the low field, the ROM's encodings for both.
- `-g` is the only option that stops the jump-register swap, and it also stops
  nop removal: a whole-tree build with `-g` and no rules changes 323 objects.
  It is not the ROM's setting.

## The one rewrite still standing

`jr $31` directly after a gcc inline-asm block (`#NO_APP`), in the ico2 tree
only. 69 sites, 6 objects, about 80 functions: `ico2/ito/src/itou_sub.c`,
`ico2/ito/src/lightning.c`, `ico2/seki/src/Matrix.c`,
`ico2/sugipon/src/matrixDrive.c`, `ico2/sugipon/src/quaternion.c`,
`ico2/sugipon/src/clothAnimation.c`. Raw, the assembler swaps the block's last
instruction (always a `sqc2`) into the return delay slot; the ROM keeps the
`sqc2` before the `jr` and leaves the slot `nop`.

The source shape that reproduces the ROM was found and measured, but it lives
in `include/vu0.h`, outside this pass's scope. Either spelling of the VU0 asm
template works, byte-exact on a hand probe: a `.set noreorder` / `.set reorder`
pair around the template body, or a trailing `nop` in the template. The wrap's
existing guard on a preceding `nop` is the same fact seen from the tool side.

ROM proves the shape is per-TU rather than global. `sce/libvu0` carries `sqc2`
in its return delay slots at 26 sites, exactly what the raw toolchain produces,
while the game's ico2 TUs never do. The 2001 build therefore used two
differently spelled VU0 templates, and a single `include/vu0.h` can only spell
one of them. That is why the rule keeps the `sce/` exclusion it inherited: with
the exclusion dropped, `sce/libvu0/libvu0.o` is the one object that breaks.

Next step for whoever owns `include/`: give the game-side VU0 macros the
`.set noreorder` pair (or the trailing `nop`), leave the sce-side spelling
alone, and delete this last rule.

## Reverted function

`sce/libsndn2/sg.c` `_SgContPolta`, now INCLUDE_ASM.

Seed: `tails/seeds/sg.rewrite_cop1_mtc1cvtb_SgContPolta_TU.c` (the whole TU as
it stood while the rule carried it).

Rule that carried it: the `mtc1;cvt;b` slack sub-rule of the COP1-move wrap in
`tools/compile_c.sh`, which reordered the instructions gcc emitted.

The exact bytes. ee-gcc emits, for the float divide that joins the two arms of
the `*(s+3) & 0x80` test:

    mtc1     $3,$f1
    cvt.s.w  $f1,$f1
    b        $L70

ROM has the `cvt` in the branch delay slot, at object offset 0x280c:

    2808: 44830800  mtc1     v1,$f1
    280c: 10000008  b        2830
    2810: 46800860  cvt.s.w  $f1,$f1

The raw toolchain gets 0x280c and 0x2810 wrong, emitting `46800860` then
`10000008` and an extra `00000000` in the slot, which makes the function 8
bytes longer and shifts every later function in the object. ee-gcc does not
fill a `b` slot and ee-as 2.9-991111 does not swap into one (probe list above),
so neither half of the toolchain produces those two words from this source.
A source shape that makes ee-gcc fill the slot itself is the open axis; the
arms as written reproduce the ROM everywhere else in the function.
