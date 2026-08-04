# enemy.c `EnemySetfDisappearAll` delay-slot re-match — MATCHED

Base: HEAD 4b302110, whole-image byte-identical,
`verify_elf: OK (build/ico.rom sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.
Same sha1 after the match — the ROM bytes are unchanged, the function is now
real C instead of `INCLUDE_ASM`.

ROM (0x001CE6F0, 10 insns):

```
daddu $5,$4,$0        lw $3,0x15C($5)   sw $0,0x2B0($3)
lw $2,0x15C($5)       sw $0,0x310($2)
lw $3,0x15C($5)       sw $0,0x3B8($3)
lw $2,0x15C($5)       j InitMotionOrient / sw $0,0x3BC($2)   <- slot
```

## Mechanism (one paragraph)

The blocker was never the assembler: **gcc 2.9-991111 runs its own dbr
(reorg) pass and emits `j <extern>` with the tail store already in the slot**
— verified with a two-line probe (`void f(int*p){p[3]=0;g(p);}` →
`j g / sw $0,12($2)` straight out of the compiler, and the period assembler
leaves that untouched). What suppressed it was the parked C's `volatile`:
reorg's `resource_conflicts_p` rejects any trial insn referencing a volatile
MEM, so a `*(int volatile *)` store can never enter a delay slot (the same
rule the vendor_2418A0 round measured for `func_00244598`). The `volatile`
was only there to stop CSE folding the four `0x15C` reloads into one. The
real dev shape needs no `volatile` at all: **load the sub-object pointer as
`int`, not as `int *`** — the repo's prevailing idiom
(`*(int *)((char *)*(int *)((char *)self + 0x15C) + OFF) = 0`, cf.
`src/box.c:48,80-81`). Because the load and the four stores are then both
`int`-typed accesses, gcc's alias analysis lets the stores clobber the load,
which (a) defeats CSE — four fresh `lw 0x15C` — and (b) stops the scheduler
hoisting load N+1 above store N, giving the ROM's strict `lw/sw` pairing.
Spelling the load as `int *` (or as a real `struct W *` field) makes the sets
disjoint and gcc collapses it to a single `lw` plus four stores. The
`daddu $5,$4,$0` copy falls out for free: `self` must stay in `$4` for the
tail call, so the base pseudo is coloured `$5` — no `register` hint, no
temp local, no pins needed.

Landed source (`src/enemy.c`):

```c
void EnemySetfDisappearAll(int *self)
{
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x2B0) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x310) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3B8) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3BC) = 0;
    InitMotionOrient(self);
}
```

## Probes measured (all against the project CFLAGS + period as)

| # | source shape | result |
|---|--------------|--------|
| 1 | parked C: `*(int volatile *)` store through `*(int * volatile *)` load | ROM's exact 9 insns, **slot `nop`** — reorg refuses volatile |
| 2 | `void f(int*p){p[3]=0;g(p);}` | `j g` + `sw` in slot — **gcc itself fills**, period as preserves |
| 3 | plain `int` stores through `int **` load | CSE → 1 `lw` + 4 `sw`, slot filled, wrong shape |
| 4 | real structs, `struct W *` field load + 4 pointer-field stores | identical to #3 — pointer stores do not clobber a pointer load |
| 5 | `int * volatile *` load + **plain** `int` store | slot FILLED, 4 reloads kept, but sched software-pipelines the loads (`lw $3/$5/$6` ahead of the stores) — wrong pairing |
| 6 | `*(int *)` load + `int` store (landed) | **byte-identical**, `ninja` sha1 unchanged |

Notes for the two remaining plain-C tail-call rows (#5/#6, `Packet.c`
`pac_makeMaterialTable*`, `j debug_assertMessage` with `lw a2,4(v0)` /
`sw a1,44(v1)` in the slot): probe #2 says the compiler fills those slots
by itself, so look for a `volatile` (or an inline-asm / addressable-memory
operand) in the parked C that is disqualifying the last insn, not for an
assembler lever.

## Status

`config/use_modern_as.txt` untouched (still empty). Queue row #4 → MATCHED.
