# commonact near-misses — parked bodies

Incomplete matches, parked so they survive the session that produced them.
These were recovered from session-local scratchpad, where they would have been
lost. Sites-first; mechanisms and refuted axes live in
`decomp/convpass_ledger_3.md`.

| seed | sites | state |
|---|--:|---|
| `commonact_func_0015ADF0_s4_novolatile.c` | 4 | **canonical** — crutch-free. The `int *volatile` alias carried since the conv-9 seed proved unnecessary: removing it leaves the divergence map byte-for-byte identical, and the function now names `D_00631AE4` through one declaration instead of two. |
| `commonact_func_0015ADF0_regsnap_s4.c` | 4 | pointer-alias base — two registers snap, but the deref floats ahead of the store. |
| `commonact_func_0015ADF0_orderexact_s5.c` | 5 | order-exact base — order right, no register snap. ROM has both, so the snap does not require the float. |
| `commonact_func_00156BA0_CF0_s6.c` | 6/7 | twins; one shape lands both. gcc never generates the SF copy at any pass, so ROM's `mov.s` pair needs a construct that forces two pseudos, not a reordering of one. |
| `commonact_func_0015D6D0_s3.c` | 3 | head exact. Residual is the position of the third loop reload. |

`func_0015ADF0`'s requirement, corrected across three passes: `len(readA) = 3`
is the whole requirement (`len(s164) > 4` was wrong and misdirected two
passes). The `%hi`/`%lo` pair is TWO quantities; `block_alloc` sorts by
`1/live_length` with birth-order tie-breaks, and on both bases a different
competitor wins `$2`. Seventeen shapes measured — every one that moved the
schedule moved it the wrong way, consistent with the data model being what
differs.

**Not parked:** `func_00260BA0` (vendor, 2 sites, 8 refutations) has no saved
body — it is diagnosed as a loop-rotation difference (gcc peels the
callee-pointer load into the preheader; ROM's loop head IS that load) but the
next worker will need to rebuild the body from that diagnosis.
