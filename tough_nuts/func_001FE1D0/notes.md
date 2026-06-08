# func_001FE1D0 (fumi/src/act-env) — parked

VRAM: 0x001FE1D0
Asm source: asm/aug6/nonmatchings/fumi/src/act-env/func_001FE1D0.s
TU: fumi/src/act-env.c
Retail twin: func_00200970 (src/act-env.c)

## Parked 2026-06-08 (deferred from retail-port; NOT a 30-stall floor)

Retail-port candidate that fails odiff-vs-baseline at the first load: the ROM
does `ld $7, 0x8($3)` but the ported retail body emits `ld a3, 2(v1)` — an
**unaligned 64-bit load at a different struct offset** (plus a `jalr` indirect
call where the retail body has a direct call). Almost certainly a
packed-struct / field-offset shape mismatch (the retail struct typing doesn't
reproduce the ROM's `ld 0x8` access). Needs real matching: recover the correct
(packed?) struct shape so the `ld` lands at offset 8.

## Seed

`tough_nuts/func_001FE1D0/func_001FE1D0.c` — retail body rebound to aug6
symbols (does NOT match yet; fix the struct/offset shape).
