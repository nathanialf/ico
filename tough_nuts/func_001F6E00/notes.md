# func_001F6E00 — TU-combination scheduler interaction

## Status

**Matches standalone.** Per-subsegment build with `[0x0F6E00, c, cod/0F6E00]`
and `src/cod/0F6E00.c` containing the seed below produces byte-identical
output. SHA-1 round-trip passes.

**Does NOT match combined.** When this function body is moved into a
multi-function `src/Basic.c` alongside `func_001F6CB0` (INCLUDE_ASM),
`func_001F6D90`, `func_001F6DB0`, `func_001F6DB8`, the ee-gcc 2.9-991111
output reorders two prologue instructions for *this function only* — the
other 4 entities still match perfectly.

## The diff (8 bytes inside func_001F6E00 only)

Original (matching, file_off 0xF6E00):

```
+0x00: 27bdfff0  addiu sp, sp, -0x10
+0x04: 3c060062  lui   a2, 0x62             # %hi(D_0061A8A8)
+0x08: ffbf0000  sd    ra, 0x0(sp)          ← sd ra FIRST
+0x0c: 24c6a8a8  addiu a2, a2, -0x5758      ← addiu SECOND  %lo(D_0061A8A8)
+0x10: 0c04e75e  jal   func_00139D78
+0x14: 240701a8  addiu a3, zero, 0x1a8      # delay slot
```

Combined-into-Basic.c build:

```
+0x08: 24c6a8a8  addiu a2, a2, -0x5758      ← addiu FIRST
+0x0c: ffbf0000  sd    ra, 0x0(sp)          ← sd ra SECOND
```

## Investigation summary

- Source code is identical (same `func_00139D78(a0, a1, D_0061A8A8, 0x1A8); DEFEAT_TCO();`).
- ee-gcc 2.9-991111 `-S` output for func_001F6E00 is identical in both
  cases except `$sp`/`$29` register-name aliasing — confirmed equivalent.
- ee-as 2.10 (`tools/cc/ee-gcc2.96/bin/as`) produces the *same byte
  order* (addiu, sd ra) when assembling either .s — also confirmed by
  hand-patching `$29 → $sp`.
- The original baseelf was therefore produced from a .s that had `sd ra`
  *before* `addiu`, which neither ee-gcc form (standalone or combined)
  emits today. Yet the standalone-matching path passes SHA-1.
- One unverified hypothesis: the standalone build hits a different
  ee-as code path due to some environmental factor (per-file cflags,
  symbol table state, or a tool in the post-process chain). Worth
  checking `build/src/cod/0F6E00.s` vs `build/src/Basic.s` byte-level
  during a clean build before drawing conclusions.

## Permuter target

Find a C body for `func_001F6E00` that matches when compiled inside
`src/Basic.c` (alongside the 4 sibling entities listed above). Possible
permutations:
- Reorder the call args.
- Introduce a temporary local for the literal address.
- Use `register` or asm-pin to bias regalloc.
- Use `__attribute__` directives that nudge the prologue layout.

## Current state in repo

- Held out as its own subsegment `[0x0F6E00, c, cod/0F6E00]` in
  `config/ico.us.yaml`.
- `src/cod/0F6E00.c` retains the matching standalone seed.
- `src/Basic.c` is the TU-promoted file for the other 4 functions
  (+ INCLUDE_ASM for `func_001F6CB0`).

When the permuter finds a TU-context-compatible body, fold it into
`src/Basic.c` and remove the held-out subsegment line in the YAML.

---

## Attempt at 2026-05-08

**Reason parked:** TU-context schedule reorder when combined into src/Basic.c — addiu/sd-ra prologue swap

Seed: `tough_nuts/func_001F6E00/0F6E00.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F6E00; check asm/matchings/cod/0F6E00/)
```
