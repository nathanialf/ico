# Delay-slot re-match queue (created 2026-08-01)

Eight functions were "matched" only because MODERN gas filled a delay slot
that ee-gcc 2.9's reorder-mode output left bare; the period assembler
(ee-as 2.9-991111, `tools/cc/ee-gcc2.9-991111/bin/as`) does no delay-slot
filling at all, so under it these functions get `nop` where the ROM carries
the hoisted instruction. They were reverted to `INCLUDE_ASM` on `main` and
their C stashed here (one `.c` per function, same-named). The re-match goal
for each: a source shape where gcc's OWN reorg pass fills the slot.

Evidence method: per-TU object rebuilt on the period assembler with the TU
removed from `config/use_modern_as.txt`, then reloc-canonicalized
per-function disassembly diff against the modern-gas object (which is
ROM-byte-equivalent — full-image SHA-1 gate green). Everything not listed
below was byte-identical under both assemblers.

Ordered smallest/simplest first:

| # | TU | function | ROM addr | insns | offending branch | ROM delay-slot occupant | status |
|---|----|----------|----------|-------|------------------|--------------------------|--------|
| 1 | src/cod/vendor_2418A0.c | func_00243B60 | 0x00243B60 | 4 | `jr ra` | `sq a2,0(a0)` | MATCHED (hand asm, jr-slot sq) |
| 2 | src/cod/vendor_2418A0.c | func_00243B70 | 0x00243B70 | 10 | `jr ra` | `sq t1,48(a0)` | MATCHED (hand asm, jr-slot sq) |
| 3 | src/cod/vendor_2418A0.c | func_00244958 | 0x00244958 | 10 | `beq a0,v1,<+0x24>` | `lw v0,0(v0)` (also: period pads a 2nd trailing nop) | OPEN — parked C is CORRECT but needs a filled slot; source shape still unknown |
| 4 | src/enemy.c | EnemySetfDisappearAll | 0x001CE6F0 | 10 | `j InitMotionOrient` (tail call) | `sw zero,0x3BC(v0)` | MATCHED (plain C, `int`-typed 0x15C load) — see HANDOFF_enemy.md |
| 5 | src/Packet.c | pac_makeMaterialTable | 0x0011A2A8 | 18 | `j debug_assertMessage` (tail call) | `lw a2,4(v0)` | MATCHED (plain C, EABI 5th arg in `$8`) — see HANDOFF_Packet.md |
| 6 | src/Packet.c | pac_makeMaterialTableLine | 0x0011A2F0 | 18 | `j debug_assertMessage` (tail call) | `sw a1,44(v1)` | MATCHED (plain C, `int`-typed cursor store defeats DSE) — see HANDOFF_Packet.md |
| 7 | src/cod/vendor_2418A0.c | func_002439B0 | 0x002439B0 | 18 | `jr ra` | `sq t3,48(a0)` | MATCHED (hand asm, MMI transpose) |
| 8 | src/cod/vendor_2418A0.c | func_00244598 | 0x00244598 | 24 | `jr ra` | `sq v1,0(a1)` | MATCHED (real C, volatile-first/plain-second store pair) |

Notes:
- #1, #2, #7, #8 are VU0/MMI-macro bodies (`QCOPY16_NO_NOP`,
  `QCOPY64_PARALLEL_NO_NOP`, `VU0_LSGP`, mode(TI) u128 copy): the trailing
  128-bit store must land in the `jr ra` slot. Likely fix direction: emit the
  jr + slot explicitly inside the noreorder inline-asm block (per the repo's
  vu0_delay conventions), NOT a C-shape change.
- #3 (`func_00244958`): read-modify-write of 0x1000E060; ROM hoists the
  first `lw` into the `beq` slot AND the function is padded differently
  (base 10 vs period 12 insns).
- #4-#6 are plain-C void tail calls (`j <extern>`). MEASURED (2026-08-04, see
  HANDOFF_enemy.md): gcc 2.9-991111's own reorg pass DOES fill a `j <extern>`
  tail-call slot — `void f(int*p){p[3]=0;g(p);}` compiles to `j g / sw` with
  no assembler help. What suppressed it in #4 was `volatile` in the parked C
  (reorg rejects any trial insn touching a volatile MEM). #4 re-matched by
  dropping `volatile` and using the repo's `*(int *)`-typed sub-object load,
  whose alias set equals the stores' so CSE/sched keep the ROM's `lw`/`sw`
  pairing. Check #5/#6's parked C for the same disqualifier.
- #5/#6 CONFIRMED that reading (2026-08-04, HANDOFF_Packet.md): with the
  parked C's `volatile` dropped, gcc filled BOTH `j debug_assertMessage`
  slots on the first attempt. Neither residual was a delay slot — #5 was a
  missing 5th call argument (the build is `-mabi=eabi`, so args 5-8 are in
  `$8-$11`; the ROM's `daddu $8,$4,$0` is arg5, not a param copy), #6 was
  dead-store elimination deleting three cursor write-backs because an
  `int *`-typed store does not share an alias set with the `int` data
  stores around it. Both are now real C; row status updated above.
- One-round caveat: the "delay-slot" attribution for each function is this
  round's conclusion from the object diff shown above; if a re-match finds
  another mechanism (e.g. #3's extra pad nop), trust the bytes.

## Revert bookkeeping

- Packet: on revert, splat migrated `D_005551A0` ("VIFUNPACK ...") into
  `pac_makeMaterialTable.s`; the C definition was removed from Packet.c and
  `D_005551C0` moved after the `pac_makeMaterialTableLine` INCLUDE_ASM
  (section order must equal VMA order under the `(.rodata*)` glob). Reverse
  both moves when re-matching #5 — details in Packet_pac_makeMaterialTable.c.
  DONE 2026-08-04: `D_005551A0`'s C definition is restored after `D_00555190`;
  `D_005551C0` needed no move (it already followed the removed INCLUDE_ASMs,
  which is still after `D_005551A0`, so section order == VMA order).
- vendor_2418A0: `func_002439B0` / `func_00243B60` keep C prototypes in the
  TU (in-TU C callers at the former lines ~759/764-767).
- enemy: nothing extra; `extern void InitMotionOrient();` decl left in place.

## 2026-08-05 — assembler swapping was tried and REVERTED (read this)

`func_00244958` and `func_00258450` were briefly landed by assembling their TUs
with a DIFFERENT assembler, then reverted the same day on the user's ruling.
Recording it so nobody re-derives the dead end — and because the measurements
underneath it are real and useful.

ee-as 2.9-991111 performs NO delay-slot filling at all (probed with three
hand-written bodies before a `j $31` — a dsll/dsra macro pair, the native
dsll32/dsra32 form, and a plain non-macro daddu: all three came out
`jr ra; nop`). ee-as **2.96** (2.10-ee-001003-1, Oct 2000, already in
`tools/cc/`) does fill. Both are period assemblers; modern gas is retired and
irrelevant here.

So the whole premise of this queue needs re-reading. These functions were
reverted in 2026-08-01 because their matches depended on MODERN gas — that
part stands, and modern gas is now impossible. But "the ROM's assembler fills
this slot" was true all along; the error was concluding that the only filler
was modern gas, when the repo already shipped a period one.

**WHY IT WAS REVERTED — the decisive argument.** The build COMPILES with ee-gcc
2.9-991111, and `tools/cc/ee-gcc2.9-991111/bin/as` is the assembler bundled with
that very compiler. The 2.10 assembler is bundled with a DIFFERENT toolchain.
Feeding one compiler's output to another toolchain's assembler is a mismatched
pairing, and "this one TU used a different assembler than its own compiler" is
far too weak a claim to hang a match on — the SHA gate merely fails to disprove
it, which is not the same as evidence for it. `config/use_as296.txt` is deleted
and there is ONE period assembler. Do not reintroduce it.

So both functions are OPEN, and the residual is a SOURCE-SHAPE problem: find the
C that makes gcc's own reorg fill the slot (gcc 2.9-991111 demonstrably does fill
`jr`/`j <extern>` slots when the candidate's `length` attribute is 1 — rows #4-#6
are exactly that). For `func_00258450` the known obstruction is that a DI->SI
narrowing is length 2 and therefore ineligible; the open question is what C
returns that value WITHOUT a length-2 narrowing in the tail.

**Worth revisiting under 2.96:** rows #1/#2/#7 (`func_00243B60`,
`func_00243B70`, `func_002439B0`) were landed as whole-function HAND ASM on the
reasoning that gcc "never schedules an inline-asm insn into a delay slot". That
reasoning was about gcc; the slot is filled by the assembler. They may be
expressible as real C now, which would retire three hand-asm transcriptions.

## 2026-08-05 — CORRECTION to row #8's recorded mechanism (func_00244598)

Commit `4b302110`'s message explains `func_00244598`'s delay-slot `sq` as a
"volatile-first/plain-second store pair": the volatile first store supposedly
materialises the address register and the plain second store is then hoistable.
**That explanation is wrong.** The function's bytes are correct and it still matches;
only the recorded reason is bad, and it cost this session two rounds of building on it.

The real reason is `mips.h`'s `GO_IF_LEGITIMATE_ADDRESS`:

    if (CONSTANT_ADDRESS_P (xinsn)
        && ! (mips_split_addresses && mips_check_split (xinsn, MODE))
        && ! (TARGET_MIPS5900 && mode == TImode)

A bare constant address is NOT a legitimate address for a 128-bit (TImode) access on
the R5900, so **no pass can fold the address into the MEM** — the register form is
guaranteed by the target, with no second reference needed. Measured: a *single* plain
`u128` store to a constant address is register-form and lands in the `jr` slot on its
own. The `volatile` on the first store does something much duller — it stops dead-store
elimination of the `pkt[0]` write.

Consequences for anyone reading this queue for leverage:
- There is no "volatile-first store pair" lever. Do not reach for it.
- The TImode exemption is mode-specific, so it does NOT help byte/half/word stores
  (`func_001010C8`'s store is QImode, `func_00244958`'s load is SImode).

Two further model corrections measured the same day, both from the shipped sources:
- **`volatile_insn_p` returns 0 for MEMs** (`rtlanal.c:1561`, `case MEM: return 0;`) —
  only volatile ASM and `UNSPEC_VOLATILE` qualify. A volatile memory reference between a
  const-set and a store does NOT block combine from pairing them; that was measured
  folding anyway.
- **`update_equiv_regs` cannot sink a const-set** (`local-alloc.c:838` only fills
  `reg_equiv_replacement` from a `REG_EQUIV` note, which a plain `(set p (const_int))`
  never gets). So there is no late move-to-the-use: the const-set sits where expand put
  it, which is the point of use.

The four ROM sites with a register-form store-at-`0(reg)` in a `jr` slot are FOUR
DIFFERENT mechanisms, not one family — worth knowing before treating any of them as a
template:
- `0x254d1c` (`func_00254CF8`): a genuine two-use pointer (read-modify-write).
- `0x2445f0` (`func_00244598`): the TImode address rule above.
- `0x241cac` (`func_00241C48`): the function is ONE basic block, so gcse returns early
  (`gcse.c:738`, `n_basic_blocks <= 1`), and its `__asm__ __volatile__` block is a real
  `volatile_insn_p`, so combine refuses to pair across it.
- `0x2526b8`: still unexplained, in unmatched code.

## 2026-08-05 — CORRECTION to func_001010C8's recorded mechanism (commit 56df1a4e)

`56df1a4e` landed func_001010C8 and explained it as: cse rewrites the `base | offset`
ior to a constant AND attaches a REG_EQUAL note, loop.c hoists it out of combine's
reach, and reload rematerialises the constant at its single use. **That is wrong.** The
match is real and the bytes are right; the mechanism is not.

Verified from the committed code's own `-da` dumps:

    insn 54: (set (reg:SI 86) (const_int 268497200))     ; 0x1000F130 — folded
    insn 34: (set (reg:SI 89) (ior:SI (reg/v:SI 85)
                                      (const_int 61824))); 0x1000F180 — NOT folded

The loop's ISR address does get constant-folded. The STORE's address does not: it
survives to combine as `(ior (reg) (const))`. **`(mem (ior ...))` is not a legitimate
address form, so no pass CAN fold it into the MEM** — the address is necessarily
computed into a register, which is what makes it delay-slot eligible, and the store
being non-volatile lets reorg take it. The ior is not rewritten, and that is exactly
why it works — the opposite of what the commit message said.

This is the same KIND of mechanism as func_00244598's: an address form the target
cannot fold. Stated generally: **make the address an IOR of an OPAQUE pseudo and a
constant.** The opacity is the load-bearing part — cse constant-folds the ior whenever
it knows the pseudo's value in the same extended basic block. In func_001010C8 the
do-while's multi-predecessor loop label ends cse's EBB, so `base` is opaque at the
store's ior. That is why latching the base inside the loop is load-bearing, and it is a
better reason than the one in the commit message.

### It does NOT transfer to func_00244958, and here is the specific reason

ROM pins func_00244958's non-volatile register-form `lw` into the ENTRY block, where
cse is omniscient — there is no multi-predecessor label before it to end the EBB, so a
`base | 0xE060` spelling is constant-folded straight back to `0x1000E060` and the load
folds into the slot-ineligible 2-insn macro. Creating an EBB boundary before the load
costs control flow the ROM does not have. Seven predicted probe compiles, full pass
model (cse unification, cprop from block 1, combine's fold conditions and
`dead_or_set_p`, `update_equiv_regs` macro-isation), all recorded in
HANDOFF_vendor_2418A0.md's round-2 section and scratchpad/func_00244958_r2_notes.md.

### Evidence for the user's standing assembler ruling to weigh (NOT a recommendation)

The aug6 prototype's twin of this function (`func_00240E78`) matches with the plain
all-volatile dev body, because aug6's default assembler is ee-as 2.96, which fills
delay slots. ROM 0x2526b8 is in the same class. Recorded as data; the retail ruling is
one period assembler (the one bundled with the compiler we build with) and it stands.
