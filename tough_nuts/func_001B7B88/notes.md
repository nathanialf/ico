# func_001B7B88 (sceneManager "Parentize") — parked near-match (17 diffs)

VRAM 0x001B7B88. Asm: asm/nonmatchings/src/sceneManager/func_001B7B88.s

## State after this session (2026-05-27): 67 -> 17 diffs, 20+ iters + permuter

REGALLOC ROTATION **SOLVED**. The 9-insn index computation
(entry=&D_002A4C48[a0*0x4C]; pid=entry[0x46]; parent=&D_002A31B8[pid*0x64])
near-missed with a 3-way temp ROTATION (v1<->a1<->a0; identical values &
order, only register NAMES rotated). Cracked by TWO pins:
  - `register unsigned char *pbase REG("$4") = D_002A31B8;` (dead arg-reg
    reuse; the original reuses $4/a0 after a0 is saved to $7) -> fixed the
    a0 slot (31->29).
  - `register int off REG("$5") = pid * 0x64;` -> pin the MULTIPLY
    INTERMEDIATE (NOT the final pointer) to $5; fixed the v1<->a1 swap
    (29->17). Pinning the final `entry`/`parent` pointer does NOT work.

Structure also correct: error path out-of-line, beql/bne dispatch, the
`j func_00263FF0` tail-call (void fn, last stmt is the call), the
double-deref store `*(int*)(*(int*)(ra0+0x15C))`. D_00633190 declared
`extern const char []` (incomplete) to keep %hi/%lo not gp_rel.

## THE WALL (17 diffs): gcc epilogue STRUCTURE differs

Original: 2-level shared epilogue
  L7CBC: ld $31           L7CC0: ld $19,$18,$17,$16; jr
  parent==0 / hw==0  -> L7CBC, delays filled with USEFUL work (lhu hw, addiu v0=4)
  pid==4             -> L7CC0, delay = ld $31

Built (ee-gcc): 3-level split, SKIPS the redundant $31 restore on pid==4
  $L2: ld $31   $L8: ld $19   $L9: ld $18,$17,$16; j $31
  parent==0 -> $L8 (skip $L2), delay = ld $31
  pid==4    -> $L9 (skip $L8), delay = ld $19 ($31 left valid, not restored)
  -> the lhu/addiu get pushed OUT of the beq delays.

gcc is "smarter" here (recognizes $31 valid pre-call, skips its restore on
the pid==4 path). The original restores $31 conservatively. Same compiler
(2.9-991111) so it is a source/structure trigger we have not found.
~12 guard structures (early-returns/nested/&&/goto/combined), volatile &
ANCHOR on hw, -fno-delayed-branch (worse, 21), and a permuter run (14k
iters, PLATEAUED at base score 105 — never improved) all failed.
Seed below is the 17-diff form. Needs a fresh epilogue-structure insight
or a custom postprocess (the built->original transform is a non-trivial
epilogue re-merge + delay re-fill, NOT the unfold_ra_delay daddu pattern).
