# func_0013D498 (ios/thread.c) — message-queue lazy-init + send

**Status:** 1-instruction scheduling near-miss — permuter candidate.

Sibling of the matched func_0013D140: obj = D_006A6F30[func_00100410()],
lazily init the queue (func_0013A0F8 alloc/log → func_0013A250 init) when
obj[0x48]==0, then func_0013A5B8 send, then tail func_001A6E28("th:msg %d").

The only diff is scheduling of the `obj[0x48]=1` store within the
func_0013A0F8 arg setup: expected `lui a2; lw a0; addiu a2; sw v0`
(store last), built `lw a0; lui a2; sw v0; addiu a2` (store splits the a2
= &D_005578D0 materialization). Tried: fmt-as-local, -fno-schedule-insns
(14 diffs, worse). gcc-owned instruction ordering.

NOTE: requires func_0013A5B8 declared returning `int` (it does; the
tracked thread.c decl was bumped void→int, harmless to func_0013D3F8).
Seed #includes nothing project-specific beyond externs.
