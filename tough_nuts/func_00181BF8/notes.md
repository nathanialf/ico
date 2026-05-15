# func_00181BF8 — parked

VRAM: 0x00181BF8 (file offset 0x081BF8)
TU: src/attackhit.c (coalesced)
Anchor: line 0x2ED in original "src/attackhit.c"
Asm source: asm/nonmatchings/src/attackhit/func_00181BF8.s (size 0x190, 100 insns, 0xE0 frame)

## Attempt at 2026-05-15

**Reason parked:** structurally correct (100/100 insn count, same algorithm,
same calls, same FP reg allocation once pinned f2/f0/f1) but plateaued at
**67 byte-diffs**. All remaining gaps are gcc 2.9 caller-save allocator
choices for the D_0055A3F0 copy loop:

- Expected: src=$4(a0), end=$2(v0), buf_base=$16(s0), dst=$3(v1)
- Built:    src=$2(v0), end=$4(a0)/sometimes $3, buf_base=$16, dst=$2(v0)

`REG()` pins on src=$4 / dst=$3 partially work but get overridden after
`KEEP_LIVE` markers — gcc reallocates inside the loop body. Additionally,
gcc folds the `lui+addiu` pair for D_0055A3F0 into one register unless
the hi-part is kept live across an intervening use my C doesn't express
naturally.

Tried ~10 structural variants:
- long-long unrolled loop (4-at-a-time): wrong shape
- struct copy (current seed): closest, 67 byte-diff
- memcpy(): emitted out-of-line call to memcpy, worse
- `static __inline__ copy_template(dst, src)`: inlined identical to struct copy
- int-counter loop: extra scheduling differences
- `register const AttackBuf *src REG("$4")` + KEEP_LIVE: src lands in $4
  but introduces a `move $3, $4` to get loop iterator out, breaking shape
- `register AttackBuf *dst REG("$3")` + KEEP_LIVE: dst pin gets overridden
  inside the loop (gcc picks $2)
- FP reg pins (f2/f0/f1 for vx/vy/vz): **works** — confirmed the lwc1
  sequence matches expected after pinning

## Permuter pointers

Seed file: `081BF8.c` (this directory) — uses externs only, no project
header includes (per tough_nuts convention; cf. `tough_nuts/func_00101AA0/`).

The seed is the closest-byte-diff variant (struct copy + buf_base pin
to $16 + FP pins f2/f0/f1).

Initial permuter pass: **no match** (expected for first run; the gcc
allocator gap needs random-mutation search). The seed is structurally
correct so the search space is the gcc 2.9 caller-save reg-pick state
for the copy loop — narrow enough that a multi-hour permuter session
should land it.

`config/extra_cflags.txt` does NOT carry an ATTACKHIT override — the
attempt at `-fno-schedule-insns` broke the sha-1 of the matched stubs
(BB8/BC0/BC8) elsewhere in the TU, so the TU compiles with default
CFLAGS. Permuter inherits this.

## Sibling function

`func_00181D88` (line 0x300) is the same source pattern with different
`__LINE__`. A match for BF8 will inform D88 quickly (signature differs
in arg-to-callee-save mapping per gcc choice, but semantically identical).
