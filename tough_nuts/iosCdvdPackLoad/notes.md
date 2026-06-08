# iosCdvdPackLoad (fumi/ios/cdvd) — parked

VRAM: 0x001321C8
Asm source: asm/aug6/nonmatchings/fumi/ios/cdvd/iosCdvdPackLoad.s
TU: fumi/ios/cdvd.c
Retail twin: func_001321C8 (ios/cdvd.c) — **retail "match" is a SILENT REGRESSION**

## Parked 2026-06-08 (NO usable seed — needs from-scratch matching)

The normalized-asm correlator paired this with retail func_001321C8, which has
a C body on the retail branch (commit 97cdaa3b "Match func_001321C8"). BUT that
retail C does **not** compile to its own binary — the actual ROM (hash-equal on
both versions) has a 0x1D0 stack frame, **two** `func_00261188`/sprintf calls
(`D_00550D98` + `D_0062C0F8`), and an inline `D_00629E39`-table normpath loop,
none of which the retail source contains. So the retail "match" is wrong; there
is no trustworthy seed.

Needs real matching from scratch against `iosCdvdPackLoad.s`: a dir-entry read
loop that builds "DFDATAS/<name>", normalises the path, and registers id/size
in the `D_0027A8A8` table (stride 0x30). The other ios/cdvd funcs ported fine
(commit 0a31b15b); only this one is parked.

## Seed

`tough_nuts/iosCdvdPackLoad/iosCdvdPackLoad.c` — the retail body for reference
ONLY. **It is the known-bad regression form; do not apply it expecting a
match.** Match against the .s directly.

See `feedback_retail_port_workflow` memory ("RETAIL BODIES CAN BE SILENT
REGRESSIONS").
