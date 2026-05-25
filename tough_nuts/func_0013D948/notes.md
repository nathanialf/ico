# func_0013D948 (ios/thread.c) — semaphore lazy-init + join-wait

**Status:** 1-instruction scheduling near-miss — permuter candidate.
Same root cause as [[func_0013D498]] (sibling).

Correct C: lazily init the queue (func_0013A0F8 alloc/log + func_0013A250)
when self[0x48]==0, then func_0013A6C0 recv into a stack local, log
"th:thread joined", return the received value.

Only diff: the `self[0x48]=1` store splits gcc's &D_005578D0 (a2)
materialisation. expected `lui a2; lw a0; addiu a2; sw v0`; built
`lw a0; lui a2; sw v0; addiu a2`. Tried fmt-local, volatile-store
(worse), -fno-schedule-insns (worse). gcc-owned instruction ordering.
