# func_0013A250 (ios/message.c) — semaphore-table register

**Status:** 1-store-scheduling near-miss — permuter candidate.

Logic is fully correct (verified against the disassembly). The only diff is
which of the two `*(self) = a2` stores (offset 0x18 vs 0xC) gcc places in
the `jal func_00100520` delay slot:

```
expected:  ... sw a2,0x18 ; sw 1,0x24 ; jal ; sw a2,0xC  (delay)
built:     ... sw 1,0x24  ; sw a2,0xC ; jal ; sw a2,0x18 (delay)
```

Both stores write a2, so ee-gcc's first-pass scheduler freely reorders
them. Tried (all shift something else): `-fno-schedule-insns` (fixes the
store but flips func_00263FF0's delay from `addiu a1` to `addiu a2`),
`volatile` on 0xC / 0x18 / both, `__asm__ memory` barrier, arg-as-local.

func_001A6E28 is varargs (`"sema[%d] = %p"`): the tail call passes
(D_00557550, idx, self). Declared 2-arg in message.c; the seed uses the
varargs form. The error path (func_001AD768 + func_00263FF0) matches the
shape of the already-matched func_0013DA00 family.

A store-swap is squarely in the permuter's wheelhouse.
