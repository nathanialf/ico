# func_00258450 — parked 2026-08-06

**Status: ONE divergent instruction.** Not a floor, and not an assembler question.
Parked by user decision at a natural pause, with the mechanism further along than
any narrative in the git history — several of which were wrong and are corrected
below.

VMA 0x00258450 · 7 insns · 0x1C bytes · `src/cod/vendor_2575C0.c`
Sibling with the IDENTICAL residual: `func_001011E8` (`src/cod/vendor_100C90.c`).
Anything that explains one explains both — they are the only two sites in the
whole 379k-instruction ROM that end `dsll32 / jr / dsra32`.

## The residual

ROM ends `dsll32 v0 / jr ra / dsra32 v0` — the second half of a 64→32 narrowing
sits IN the `jr` delay slot. The seed C produces all seven instructions in ROM's
exact registers and order; only that one instruction is wrong (we emit
`extendsidi2`'s self-move there instead).

## Established, with the wrong turns marked

1. **The assembler is settled and is NOT the answer.** ee-as 2.9-991111 fills no
   delay slot ever (probed with three hand-written bodies before a `j $31`:
   a dsll/dsra macro pair, native dsll32/dsra32, and a plain non-macro daddu —
   all came out `jr ra; nop`). Only gcc's dbr pass fills. A per-TU opt-in to the
   other period assembler was tried, landed this function, and was REVERTED by
   user ruling (the assembler ships bundled with the compiler we build with).
   Do not reopen it.

2. **The return type is NOT pinned to 32 bits.** Retyping this function and both
   callers to `long long` leaves the callers byte-identical. Earlier rounds
   asserted the opposite from the callers' bare `daddu`, never measured it, and
   the false constraint bounded the search for three rounds.

3. **~~The pair can only survive cross-BB~~ — FALSE, and this is the big one.**
   Probe K got `dsll32`/`dsra32` to survive as two separate length-1 DImode
   shifts inside ONE basic block, no branch anywhere:

       ld $3,0($4) / li $2,64 / subu $2,$2,$5 / dsrl $3,$3,$2 /
       dsll $3,$3,32 / dsra $2,$3,32 / j $31 / sd $3,D_probe

   from `long long w = (long long)(*p >> (64-n)) << 32; D_probe = w; return w >> 32;`

   Mechanism (`flow.c:3376-3390`): flow builds exactly ONE log link per def, to
   the FIRST forward use. Give `w` an earlier use combine cannot absorb and
   `try_combine(ashiftrt, ashift)` is never attempted — the fold that would
   collapse the pair into one length-2 insn never gets a chance. The intra-BB
   fold everyone was fighting is `make_compound_operation`'s ASHIFTRT case
   (combine.c:6183 → make_extraction, pos 0 / len 32 →
   `(sign_extend:DI (subreg:SI v))` → `extendsidi2`, which prints as a move).

   So the ten-round hunt for "the author's vanishing branch" was chasing the
   wrong mechanism. A diamond DOES work (two identical multi-insn arms collapse
   to exactly 7 insns with `dsra` in the slot, arms cross-jumped, `beq`/`b`
   deleted as jumps-to-next) but it is not required.

4. **The colouring rule, corrected.** Not `combine_regs`' block-local tie (the
   r10 account, which does not explain the data). It is `local-alloc.c`'s
   HARD-REGISTER SUGGESTION pass, which runs BEFORE the priority pass: when an
   insn's SET_DEST is a hard reg and one of its dying inputs is a local pseudo,
   `combine_regs` records `qty_phys_sugg |= $2` for that quantity.
   - The straight-line seed wins `$2` for the accumulator because its chain ends
     in `(set (reg:DI 2) (sign_extend t))`.
   - Every probe whose chain ends in a pseudo gets no suggestion, falls back to
     `QTY_CMP_PRI = floor_log2(refs)*refs*size/(death-birth)`, and in a 5-insn
     block the shift amount (32/3 = 10.67) always beats the accumulator
     (64/7 = 9.14). Six probes, no exception.
   - Therefore ROM's colours require the `ld`/`dsrlv` block to ALSO contain the
     insn that writes hard `$2` off that chain — i.e. the `dsra32`. That
     independently corroborates the one-block reading in (3).

   NOTE: this is the same pass that landed `initGeometryState` this session
   (commit 55c0aa47) — there, routing a value through a join variable REMOVED an
   unwanted `$2` suggestion. Here we need one to FIRE. Same lever, opposite sign.

## What is left: three conditions on one use

The source must give `w` a use U such that
  U1 — U sits between the `dsll` and the `dsra` in the insn chain, taking flow's
       single log link and blocking the fold;
  U2 — `w` still DIES at the `dsra`, so the `$2` suggestion fires and the
       accumulator gets ROM's register;
  U3 — U costs ZERO BYTES.
U1 and U2 are compatible and both demonstrated. **U3 is the whole open question.**
`jump_optimize(NOOP_MOVES)` runs before `dbr_schedule`, so a coalescing copy is
gone before reorg picks a slot filler — but for that copy to survive combine, `w`
must be live past it, and for flow not to delete it, its destination must be live.

**Worth trying first on resume, from the sibling that cracked the same shape of
problem:** `func_001010C8` (committed 56df1a4e, mechanism corrected in 8356f2dc)
had the identical "find a free intervening use" question, and it was NOT solved
by finding a free use. It was solved by writing the operand in a form the target
CANNOT FOLD — there, `(mem (ior reg const))` is not a legitimate address, so no
pass could absorb it, and the load-bearing extra ingredient was OPACITY (cse
collapses such a form the moment it knows the pseudo's value in the same extended
basic block). Ask whether the shift pair can be made UNFOLDABLE rather than
merely unlinked.

## Rejected — do not resubmit, all three reached rc0 with a green gate

- A whole-function `__asm__` transcription of the ROM instruction stream. That is
  a restatement of the INCLUDE_ASM, not a decompilation.
- `return (int)(p - (unsigned char *)0x1000F180) + c;`-style tails, i.e. any term
  that is identically zero and exists only to hold a value live.
- A diamond whose arms differ ONLY to stop cse unifying them (`v << 32` vs
  `(v & 0xFFFFFFFF) << 32` — the mask is redundant before a 32-bit left shift).
The bar for any term: state in one sentence what it MEANS as a quantity the
author wanted. An allocator-motivated term is a crutch.

## Where the evidence lives

Round notes and probe dumps under `scratchpad/func_00258450_R4..r11_notes.md` and
`scratchpad/r5,r6,r8,r9,r10,r11/` (local, not committed). `src/cod/vendor_25E1E8.c`
is full of this compiled idiom in branch delay slots — the author's habits are
visible there in already-matched code.
