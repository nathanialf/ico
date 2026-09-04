# vendor_2418A0 delay-slot re-match — running handoff

Base: whole-image byte-identical, `verify_elf: OK`,
sha1 `fbf50c75cd5911273511c4f9af90503ff8423582`.

## Mechanism findings that apply to the whole TU

Measured with the project CFLAGS
(`-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -Iinclude`,
`tools/cc/ee-gcc2.9-991111/ee-gcc -B .../2.9-ee-991111-01/`):

1. **gcc's reorg never schedules an inline-asm insn into a delay slot.**
   Probe: a function whose whole body is `__asm__ __volatile__("lq $6,0($5)")`
   + `__asm__ __volatile__("sq $6,0($4)")` compiles to
   `#APP / lq / sq / #NO_APP / j $31` — the `j $31` is emitted with *nothing*
   after it. Same for a single asm block containing both insns. So any
   function whose tail work is inline asm gets a bare `jr` slot, which
   ee-as 2.9-991111 leaves as `nop` (modern gas hoists, hence the old
   false matches).
2. **A quadword copy written as C *does* get its slot filled by gcc**, but
   the register is always `$2`. `typedef unsigned int u128 __attribute__((mode(TI)));
   void f(void*d,void*s){*(u128*)d=*(u128*)s;}` →
   `lq $2,0($5) / j $31 / sq $2,0($4)`. Adding dead trailing int params,
   routing through a named local, or wrapping the quad in a one-member
   struct all give the identical `$2`.
3. **gcc emits a 64-byte quad copy as interleaved lq/sq pairs**, alternating
   `$2`/`$3` (`lq $2,0 / sq $2,0 / lq $3,16 / sq $3,16 / ...`). Forcing all
   four values live at once (four named locals, then four stores) gives
   `$2,$3,$6,$7` *and* reorders the offsets (48,0,16,32). Neither is the
   ROM's `lq $6,$7,$8,$9` then `sq $6,$7,$8,$9` in offset order.

(2)+(3) are the proof that the quad-copy / MMI-transpose leaves in this TU
are hand-written assembly in the original: the register budget is an
author's, not an allocator's. Combined with (1), the trailing `sq` in the
`jr` slot can only have been written explicitly.

## Per-function state

### sceVu0CopyVector (4 insns) — MATCHED
Whole-function `__asm__` block at file scope with `.set noreorder` and an
explicit `jr $31` + `sq $6,0x0($4)` in the slot, plus the trailing pad `nop`
after `.size` — the same form already used by `sceVu0InversMatrix` in this TU.
The C prototype stays for the in-TU callers in `sceVu0LightColorMatrix`.

### sceVu0CopyMatrix (10 insns) — MATCHED
Same form. `lq $6/$7/$8/$9` from `0/0x10/0x20/0x30($5)`, then
`sq $6/$7/$8`, `jr $31`, `sq $9,0x30($4)` in the slot, trailing `nop`.

### sceVu0TransposeMatrix (18 insns) — MATCHED
Same form. MMI 4x4 transpose (`pextlw`/`pextuw`/`pcpyld`/`pcpyud` on
`$8..$15`), `jr $31` with `sq $11,0x30($4)` in the slot, trailing `nop`.

`ninja` after these three: `verify_elf: OK (build/ico.rom
sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.

### sceVpu0Reset (24 insns) — MATCHED
Real C. Two mechanisms:
* **The FIFO store must be non-volatile so gcc can hoist it into the `jr` slot.**
  gcc's reorg refuses any trial insn that references a volatile MEM
  (`resource_conflicts_p` treats `volatil` on either side as a conflict —
  verified with a minimal pair: `int f(int*p,...)` puts the `lw` in the `beq`
  slot, `int f(volatile int*p,...)` does not). With `*(u128*)0x10004000` written
  plainly, gcc emits `jr ra / sq v1,0(a1)` by itself.
* **…but then gcc dead-store-eliminates the FIRST write to the same address.**
  Both writes are to VIF0_FIFO (0x10004000) and gcc 2.9's flow.c deletes the
  earlier non-volatile store. Marking only the FIRST store volatile
  (`*(volatile u128 *)fifo = pkt[0];`) keeps it AND leaves the second store
  hoistable. The non-volatile second store reuses the address register the
  volatile one materialised, so both `sq`s share `a1` exactly as the ROM does.
* TImode has no gas large-constant addressing macro, so both `0x10004000` and
  `%hi/%lo(D_005506F0)` get materialised into registers with no volatile needed
  — which is why the tail is dbr-eligible at all.
* The three VIF0 register writes stay `*(volatile int *)` and the
  `cfc2/ori/ctc2/sync.p` stays one `.set noreorder` asm block. Declaring `fifo`
  and `pkt` in a nested block AFTER the asm block is load-bearing: at function
  scope their address setup is scheduled above `sync.p`.

### sceDmaPutStallAddr (10 insns) — STALLED, restored to INCLUDE_ASM

Two measured gcc rules collide. Every hypothesis tried is excluded by one or
the other, so this is a characterised impasse rather than a random plateau.

**Rule A — the delay-slot insn must be non-volatile.** gcc's reorg rejects any
trial insn referencing a volatile MEM. Minimal pair, same body otherwise:

    int tn(int *p, int x, int *q){ int o=*p; if(x) *q=1; return o; }
      → beq $5,$0,$L3 / lw $4,0($4)        (lw IS in the slot)
    int tv(volatile int *p, int x, int *q){ ... }
      → lw $4,0($4) / beq $5,$0,$L5 / li $2,1   (lw is NOT)

**Rule B — the delay-slot insn must be one instruction, i.e. a register
address.** A *non-volatile* SImode load from a large constant address is always
folded back to the gas macro `lw $r,268492896` (length 2, so reorg-ineligible,
and it assembles to `lui $r,0x1001 / lw $r,-8096($r)`, not the ROM's
`lui/ori/lw 0($r)`). Only marking the load `volatile` keeps the address in a
register — `int lv(void){return *(volatile int*)0x1000E060;}` gives
`li $3,0x10000000 / ori $3,$3,0xe060 / lw $2,0($3)` — and that re-triggers
Rule A. Spellings measured and all folded to the macro form: plain cast,
`(R*)A->v`, `0x1000E000+0x60`, `(char*)+0x60`, `(unsigned long long)` cast,
`const int*`, a `int*` local used for both accesses, a `volatile int*` local
with the volatile cast away on the load, a union-punned pointer, and a second
redundant load.

**Best residual** (the volatile/volatile shape, i.e. the stashed C):
everything matches except the slot — 12 insns emitted vs the ROM's 10.

    ROM                          built
    lui v0,0x1000                lui v0,0x1000
    lui v1,0xffff                lui v1,0xffff
    ori v0,v0,0xe060             ori v0,v0,0xe060
    ori v1,v1,0xffff             ori v1,v1,0xffff
    beq a0,v1,+0x20              lw  v0,0(v0)
     lw v0,0(v0)                 beq a0,v1,+0x24
    lui at,0x1001                 nop
    sw  a0,-8096(at)             lui at,0x1001
    jr  ra                       sw  a0,-8096(at)
     nop                         jr  ra / nop / nop

Ruled out as an explanation: the assembler. `tools/cc/ee-gcc2.9-991111/bin/as`
performs NO branch-delay swapping at all — a hand `.s` with
`lw $2,0($5) / beq $4,$3,1f / sw $4,0($6)` assembles with a `nop` in the slot
at `-O0`, `-O` and `-O2` alike. So the fill has to come from gcc, not gas.

Not yet tried, if someone resumes: whatever makes gcc keep a NON-volatile
SImode constant address in a register (the TImode accesses in sceVpu0Reset
get this for free because TImode has no constant-address form). Writing the
function as a whole-function `__asm__` block would reproduce the bytes but it
is not a VU0/MMI body, so it was left as INCLUDE_ASM.

## Final state

`ninja`: `verify_elf: OK (build/ico.rom
sha1=fbf50c75cd5911273511c4f9af90503ff8423582)` — whole image byte-identical
with sceVu0CopyVector, sceVu0CopyMatrix, sceVu0TransposeMatrix and sceVpu0Reset landed in
`src/cod/vendor_2418A0.c` and sceDmaPutStallAddr still INCLUDE_ASM.

`QUEUE.md` rows 1, 2, 7, 8 are resolved; row 3 (sceDmaPutStallAddr) remains, with
the residual above. Rows 4–6 (enemy.c, Packet.c) were out of scope here.

## 2026-08-05 — round 2 on sceDmaPutStallAddr (7 probe compiles, dump forensics,
## gcse.c/combine.c/local-alloc.c source reads). Result: measured impossibility
## argument for plain C under the single non-filling assembler; and a
## CORRECTION to the recorded kputchar mechanism.

Full lab notes: scratchpad/func_00244958_r2_notes.md (probes 1-7 with
predictions and dumps under scratchpad/r958/).

### Measured pass model (ee-gcc 2.9-991111, project CFLAGS)

1. expand: a large-constant address NEVER folds into a MEM at birth (every
   access is born `(set x C); (mem x)`), but `(mem (const_int))` IS accepted
   by movsi/extendsidi recog once a pass builds it.
2. cse: rewrites EVERY const-valued src to the constant (even a cheap reg
   copy or a 1-insn ior becomes a 2-insn li) and unifies same-valued roots.
   Its table flows across the whole B0-chain (label-less fallthroughs AND
   single-pred branch targets — probe D folded iors in BOTH arms). Only a
   multi-pred label (loop top, join) forces a fresh table.
3. gcse cprop (blocks >= 1 only; never block 0): folds a recorded
   `(set x C)` (recorded iff dest unmodified to its block's end) into EVERY
   valid use — loads, stores, volatile included (volatile_ok is on).
   It CANNOT fold into an ior/plus-of-consts (validate_replace_rtx does not
   simplify IOR): probes sib/D show "0 const props" on ior operands.
4. combine: folds a const-set into any DYING same-block use — loads AND
   stores (probe s2: plain `*(u32*)C = a` folds to the macro sw). Blocked
   only by: volatile-MEM insn (probe sv), live-past/used-between (probe
   D-B1), cross-block (no LOG_LINK), or an unrecognizable result
   ((mem (ior ..))). dead_or_set_p counts a SET, so the self-overwrite
   `p = *(u32*)p` is NOT protected (probe sx folded).
5. update_equiv_regs (read, local-alloc.c): set-once + REG_EQUAL + used-once
   + multi-block: a substitution-VALID use gets macro-ized (init deleted); an
   INVALID one gets the init moved adjacent. No rescue for SImode loads
   ((mem:SI C) is always valid).

### Why sceDmaPutStallAddr's bytes are unreachable from plain C here

Bytes pin: address materialization (lui/ori) + non-volatile register-form
`lw $2,0($2)` in the ENTRY block (pre-beq; the slot fill must be gcc reorg's
simple fill), macro `sw` in the store arm, join = bare `jr`. In the entry
block cse is omniscient (no earlier label), so the pointer's def is always
`(set p C)`; its only other possible consumer (the store address) is eaten by
cse-unification + cprop; therefore p dies at the lw and combine folds the
load to the slot-ineligible `lw $r,<abs>` macro. Every alternative geometry
(load first-in-arm, two-arm loads + reorg redundancy, self-overwrite,
base|offset in B0, extendsidi2 long-long load, copies, post-increment) is
excluded by the measured facts above — see the notes file for each trace.

### CORRECTION to commit 56df1a4e's mechanism claim (kputchar)

Measured (probe7): cse does NOT rewrite that ior to a constant, loop.c does
NOT hoist it, and reload does NOT rematerialise. The real mechanism is:
(a) `base`'s def sits inside the do-while, and the multi-pred loop-top label
ends cse's EBB, so `base` is UNKNOWN at the post-loop ior — the ior survives
as a real `(ior reg imm)`; (b) cprop cannot substitute into an ior; (c)
combine's fold would produce `(mem (ior ..))` which fails recog, and the
3-way is cross-block. The register form is therefore structural. Do NOT
template "cse-rewrite + REG_EQUAL + reload remat" from that commit message.

### Evidence relevant to the standing assembler ruling (for the user, FYI)

- aug6's twin func_00240E78 is MATCHED with the all-volatile body because the
  aug6 build's DEFAULT assembler is ee-as 2.96, which fills delay slots.
- ROM 0x2526b8's exit block (three same-block const-set + register-form
  volatile-looking SI stores, one in the jr slot) is inexplicable under
  [gcc-reorg fills / 2.9-991111 assembles]: combine folds plain same-block
  stores (probe s2) and reorg refuses volatile — but is exactly what
  gcc-reorder-mode output + a filling assembler produces.
- The 783-tail-call sdl/sdr statistic does not discriminate: 2.96 could fill
  ordinary insns while (per its own behavior) skipping unaligned stores.
This function, 0x2526b8, and possibly others form one class. Under the
current one-assembler ruling they stay INCLUDE_ASM.
