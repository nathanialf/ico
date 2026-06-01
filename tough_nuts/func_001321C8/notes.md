# func_001321C8 — near-miss rc54 (iosCdvdMgrReadDir)

VRAM 0x001321C8  TU ios/cdvd.c  (111 insns, frame 0x1d0, 8 jal)
Seed: func_001321C8.c (full TU at rc54).

## Status: ALGORITHM + FRAME correct, rc54, ~6 regalloc/order diffs

Reads dir-entry count via func_001320E8, then per entry: read 32B record,
sprintf "DFDATAS/%s" into self+0x34, sprintf again into a stack namebuf,
normalise the path (D_0062FC79 ctype idiom, same as func_00133218), register
the name in D_0027E528[n*0x30] (func_00265168) and the rounded size/id at
D_0027E528[n*0x30]-8/-4 (= D_0027E520[n]), bump D_00631F54. Returns 1.

Fixed so far: frame 0x1d0 (matches); moved `name = self+0x34` AFTER the count
check (cleared block-0 diffs, rc57->54).

## Remaining diffs (2 clusters)

1. **count copy (blk1):** ROM loads count, copies to $3, computes count-1 in
   $2, `blez $3`, stores count-1 (delay). Built tests count in $v0 directly.
   Tried `int c=count; count=c-1; if(c<=0)` → rc55 (v0/v1 reload shifts). Open.
2. **namebuf/sizebuf register swap (blk2):** ROM hoists namebuf(sp+0x20)=$21,
   sizebuf(sp+0x124)=$20; built has them swapped ($20/$21). Can't reorder decls
   (stack layout 0x20/0x124 is fixed). gcc LICM/alloc-order detail.

## NOT yet tried
- Single D_0027E528 base + neg offsets gave rc80 (worse than D_tbl_0027E520 form
  — the address-arith order regressed); revisit with the right `e-8`/`e-4`
  computation order (ROM computes `base-4` BEFORE adding n*0x30).
- The int-return v0/v1 lever ([[int_return_pushes_v0_to_v1]]) if any swap is a
  post-call reload.
- NOT a floor — algorithm is correct; the tail is hoist-order/regalloc.
