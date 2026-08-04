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

### func_00243B60 (4 insns) — MATCHED
Whole-function `__asm__` block at file scope with `.set noreorder` and an
explicit `jr $31` + `sq $6,0x0($4)` in the slot, plus the trailing pad `nop`
after `.size` — the same form already used by `func_002439F8` in this TU.
The C prototype stays for the in-TU callers in `func_00244058`.

### func_00243B70 (10 insns) — MATCHED
Same form. `lq $6/$7/$8/$9` from `0/0x10/0x20/0x30($5)`, then
`sq $6/$7/$8`, `jr $31`, `sq $9,0x30($4)` in the slot, trailing `nop`.

### func_002439B0 (18 insns) — MATCHED
Same form. MMI 4x4 transpose (`pextlw`/`pextuw`/`pcpyld`/`pcpyud` on
`$8..$15`), `jr $31` with `sq $11,0x30($4)` in the slot, trailing `nop`.

`ninja` after these three: `verify_elf: OK (build/ico.rom
sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.

### func_00244598 (24 insns) — MATCHED
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

### func_00244958 (10 insns) — STALLED, restored to INCLUDE_ASM

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
SImode constant address in a register (the TImode accesses in func_00244598
get this for free because TImode has no constant-address form). Writing the
function as a whole-function `__asm__` block would reproduce the bytes but it
is not a VU0/MMI body, so it was left as INCLUDE_ASM.

## Final state

`ninja`: `verify_elf: OK (build/ico.rom
sha1=fbf50c75cd5911273511c4f9af90503ff8423582)` — whole image byte-identical
with func_00243B60, func_00243B70, func_002439B0 and func_00244598 landed in
`src/cod/vendor_2418A0.c` and func_00244958 still INCLUDE_ASM.

`QUEUE.md` rows 1, 2, 7, 8 are resolved; row 3 (func_00244958) remains, with
the residual above. Rows 4–6 (enemy.c, Packet.c) were out of scope here.
