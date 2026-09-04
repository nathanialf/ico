# fill_inbuf (ios/inflate.c) — window-fill read loop

**Status:** structurally correct, ~29 diffs of gcc-owned scheduling/regalloc.
Permuter candidate.

Reads a decompression source into the 0x10008 window in 0x8000-byte chunks
via the callback at `self[1]` (jalr), accumulating the offset at
`self[0x1804C]` until it overflows 0x7FFF or the callback returns -1/0.
Then sets `self[0x18050]=1` and returns the first window byte (or -1 if
nothing was read).

Seed (`fill_inbuf.c`) has the structure **right**:
- `register int *self __asm__("$16")` pins a0 to s0 so the window base
  `self+0x18000` takes s1 (without the pin gcc swaps s0/s1).
- `long long ret` reproduces the redundant sign-extension (dsll32/dsra32)
  of the callback return — needed for `offset += ret`.
- `(unsigned)(ret+1) < 2` gives the **correct beql** (the `(int)ret+1`
  variant drops the sign-ext and flips it to bne).

Remaining diffs are all in the "intractable" set:
1. **sign-ext order** — expected sign-extends ret *then* `addiu +1`
   (32-bit); gcc does `daddiu +1` (64-bit) *then* sign-extends.
2. **offset regalloc** — expected loads offset into $4 (the a0-arg reg)
   and reuses it for `subu avail` then the dst pointer; gcc uses v1/a1.
   Pinning offset to $4 did not help.
3. **prologue scheduling** — expected emits `w[0x4C]=0` (sw to v0) before
   saving the base into s1; gcc saves s1 first.

Tried (no improvement): w-var vs inline base, `(int)ret+1`, pin offset $4.
The sign-ext order + branch-likely + prologue scheduling are exactly the
postprocess_intractables_30x patterns. Hand off to permuter.
