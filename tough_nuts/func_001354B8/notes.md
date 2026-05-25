# func_001354B8 (ios/inflate.c) — two free-list walks + cleanup

**Status:** 2 diffs after 12 attempts. STRUCTURE BYTE-CORRECT (the beql
guard, BOTH §8.14 walks, the tail func_00138A10 all match). Permuter seed.

Walks two free-lists at window+0x54 and window+0x58 (jal_daddu_lw / §8.14
pattern: per node func_00139598(node), advance s0=*(s0+4), s0-=8 in the
bne delay), guarded by `if (window[0x54] != 0)`, then zeroes both heads,
func_00136140(window+0x18098), func_00139598(a0), tail func_00138A10.

Keys already found (in the seed):
- INLINE the window base `((int*)((char*)a0+0x18000))[...]` (no `base`
  variable) → gcc recomputes a0+0x18000 in a caller-saved temp each use
  (matching), instead of caching it in a callee-saved reg (extra frame).
- reuse `s0` for the list head (no separate `H` var) → head loads into
  $16 directly, then s0-=8 in place.
- advance AFTER func in source (gcc puts it in the jal delay).
- swap the two zeroing stores (write 0x54 then 0x58; gcc reverses to 0x58
  then 0x54, matching).
- `__asm__ __volatile__("")` barrier before each loop label → stops gcc
  rotating the do-while into a `b`-loop (gives the correct `bne` back).

Remaining 2 diffs (scheduling TRADE-OFF): the original hoists the *next*
block's base-recompute `lui v0,0x1` into the preceding H-check beq delay
slot. The barrier needed to prevent loop rotation also blocks that
cross-block hoist. Without the barrier gcc hoists the lui but b-loops
(6 diffs). Empty vs memory-clobber barrier, barrier-at-loop-top, literal
nop, early-advance — none break the trade-off. Permuter should.
