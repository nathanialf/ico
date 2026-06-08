# func_00138100 (fumi/ios/mcdata) — parked

VRAM: 0x00138100
Asm source: asm/aug6/nonmatchings/fumi/ios/mcdata/func_00138100.s
TU: fumi/ios/mcdata.c
Retail twin: func_001383F8 (ios/memory.c)

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

Retail-port candidate with a real regalloc/codegen diff in its packed-struct
copy. The body indexes `Elem_001383F8` (stride 0x18C: `char pad[0x140]; int
f140; int f144; int f148; Blk40_001383F8 f14C` where `Blk40` is a packed
`long long x[8]`) and copies the 0x40-byte `Blk40` via
`*(Blk40 *)D_X = *(Blk40 *)(base + 0x14C + i*0x18C)`. The ported body compiled
~0x80 bytes short of the ROM — gcc's index/copy regalloc differs from the
original. Needs real matching: rework the index arithmetic / copy shape so the
`i*0x18C` stride and the packed copy match. (The sibling func_00138098 in this
TU ported fine and is matched; only func_00138100 is parked.)

## Seed

`tough_nuts/func_00138100/func_00138100.c` — retail body rebound to aug6
symbols (does NOT match yet). The `Blk40_001383F8` / `Elem_001383F8` typedefs
are already in `fumi/ios/mcdata.c`.
