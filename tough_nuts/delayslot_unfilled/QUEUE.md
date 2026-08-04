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
| 3 | src/cod/vendor_2418A0.c | func_00244958 | 0x00244958 | 10 | `beq a0,v1,<+0x24>` | `lw v0,0(v0)` (also: period pads a 2nd trailing nop) | STALLED, restored — see HANDOFF_vendor_2418A0.md |
| 4 | src/enemy.c | EnemySetfDisappearAll | 0x001CE6F0 | 10 | `j InitMotionOrient` (tail call) | `sw zero,0x3BC(v0)` | MATCHED (plain C, `int`-typed 0x15C load) — see HANDOFF_enemy.md |
| 5 | src/Packet.c | pac_makeMaterialTable | 0x0011A2A8 | 18 | `j debug_assertMessage` (tail call) | `lw a2,4(v0)` | |
| 6 | src/Packet.c | pac_makeMaterialTableLine | 0x0011A2F0 | 18 | `j debug_assertMessage` (tail call) | `sw a1,44(v1)` | |
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
- One-round caveat: the "delay-slot" attribution for each function is this
  round's conclusion from the object diff shown above; if a re-match finds
  another mechanism (e.g. #3's extra pad nop), trust the bytes.

## Revert bookkeeping

- Packet: on revert, splat migrated `D_005551A0` ("VIFUNPACK ...") into
  `pac_makeMaterialTable.s`; the C definition was removed from Packet.c and
  `D_005551C0` moved after the `pac_makeMaterialTableLine` INCLUDE_ASM
  (section order must equal VMA order under the `(.rodata*)` glob). Reverse
  both moves when re-matching #5 — details in Packet_pac_makeMaterialTable.c.
- vendor_2418A0: `func_002439B0` / `func_00243B60` keep C prototypes in the
  TU (in-TU C callers at the former lines ~759/764-767).
- enemy: nothing extra; `extern void InitMotionOrient();` decl left in place.
