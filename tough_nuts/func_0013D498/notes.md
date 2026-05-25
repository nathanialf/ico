# func_0013D498 (ios/thread.c) — message-queue lazy-init + send

**Status:** permuter-improved to score 60 (one-instruction miss).

Sibling of the matched func_0013D140. Lazily init the queue (func_0013A0F8
alloc/log + func_0013A250) when obj[0x48]==0, then func_0013A5B8 send, tail
func_001A6E28("th:msg %d").

The permuter found the `do { } while (0)` scheduling barrier (between the
`obj[0x48]=1` store and func_0013A0F8), halving the score 120 -> 60. The
seed above is that 60-base. Remaining single diff: the `obj[0x48]=1` store
is emitted right after `v0=1` instead of *after* the &D_005578D0 (a2)
materialisation. Tried (no further improvement): do/while before the
store, args-as-locals, 25 min permuter @ -j3 from the 60-base. gcc-owned
store-vs-address scheduling.

func_0013A5B8 must be declared returning int (harmless to func_0013D3F8).
Same root issue as [[func_0013D948]].
