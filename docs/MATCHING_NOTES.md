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
