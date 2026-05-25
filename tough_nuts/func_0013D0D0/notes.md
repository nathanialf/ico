# func_0013D0D0 (ios/thread.c) — doubly-linked-list unlink + callback

**Status:** 5 diffs after 6 attempts. Structure correct. Permuter candidate.

Unlink a1 from its list: if a1[0x30] (prev) != 0, prev[0x34] = a1[0x34]
(next); else *a0 = a1[0x34]. If next != 0, next[0x30] = a1[0x30] (then
reload next = a1[0x34], an aliasing reload). Then if a0[0x8] (fn) != 0,
fn(a1, a0[0xC]) via jalr (beql guards). Return next.

Remaining: gcc copies a1 to a working reg at function entry
(`daddu v0/v1,a1`) and reads a1[...] through the copy; the original keeps
a1 in $5 directly as the load base and only moves it to $4 at the fn call.
Allocation-order quirk: gcc assigns the first load result (prev) to $5
(reusing the param reg) and evicts a1, OR (with `register int *node
__asm__("$5")`) keeps $5 reserved and copies to v0. Neither reproduces the
"a1 stays $5, prev->v1" allocation.

Tried (best = node pin $5, 5 diffs): no pins (13), self pin $6 only (10,
fixes a0->$6 = a2), node pin $5 (5), node+self pins (5), inline prev. The
seed (node pin $5) is closest. Hand to permuter.
