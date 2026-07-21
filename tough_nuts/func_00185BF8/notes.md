# func_00185BF8 (omori/src/camera-ico2.c) — PARKED WIP

In-progress decomp (CamG struct + M48 saved-quat block + orient math) parked 2026-07-21 to free main for landing.
Not matching when parked. The recovered CamG struct layout (f44 gate, saved.q at 0x50, f80..fA4) + M48 { long long q[6] } are the seed. Resume: splice func_00185BF8 back into omori/src/camera-ico2.c (replace its INCLUDE_ASM) and converge.
