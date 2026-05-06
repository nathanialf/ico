# Matching notes

Per-function deferred targets and tough nuts. Empty at init; populated as
matching work proceeds.

Each entry should record:

- The function (VRAM address, name if known).
- The failure mode (regalloc divergence, scheduling, missing opcode in
  m2c, …).
- The best diff state achieved (permuter plateau score if applicable).
- Structural hints learned from the asm.
- Where the current best attempt is parked (`tough_nuts/<name>/`).

## Parked

- **func_00105278** / **func_00105290** — array-base + index-shifted
  address pattern. ee-gcc emits 64-bit `la` macro expansion (daddiu/
  daddu); original uses 32-bit addiu/addu with different instruction
  order. Likely needs a non-ee-gcc compiler (Pro-DG/wcc or CodeWarrior)
  or a gas option to force 32-bit `la`. See
  `tough_nuts/func_00105278/notes.md`.
