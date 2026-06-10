# func_001F21B0 — parked

VRAM: 0x001F21B0 (file_off 0x0F21B0)
Asm source: asm/aug6/nonmatchings/sugipon/src/windManager/func_001F21B0.s

## Attempt at 2026-06-10

**Reason parked:** rc15 q-first on-path seed. IDENTICAL base+idx*0x190 remat wall as GetRegularizedWindSpeed (3 regs: copy daddu v0,a1,zero + remat addu v1,a3,v1); my source keeps 1-2. Only prologue differs (idx=a0, D_0062BA38=idx writeback). Same permuter-class residual; same fix transfers from Get.

**TU:** `sugipon/src/windManager.c`

**Seed:** `tough_nuts/func_001F21B0/func_001F21B0.c`

Disassembly:

```
.align 3
nonmatching func_001F21B0, 0xD4

glabel func_001F21B0
    /* F21B0 001F21B0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F21B4 001F21B4 90010724 */  addiu      $7, $0, 0x190
    /* F21B8 001F21B8 2000B0FF */  sd         $16, 0x20($29)
    /* F21BC 001F21BC 5F00033C */  lui        $3, %hi(D_005EBD14)
    /* F21C0 001F21C0 2D808000 */  daddu      $16, $4, $0
    /* F21C4 001F21C4 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* F21C8 001F21C8 00188144 */  mtc1       $1, $f3
    /* F21CC 001F21CC 18380702 */  mult       $7, $16, $7
    /* F21D0 001F21D0 14BD6324 */  addiu      $3, $3, %lo(D_005EBD14)
    /* F21D4 001F21D4 0C00A3E7 */  swc1       $f3, 0xC($29)
    /* F21D8 001F21D8 F4FF6624 */  addiu      $6, $3, -0xC
    /* F21DC 001F21DC 3000BFFF */  sd         $31, 0x30($29)
    /* F21E0 001F21E0 01000424 */  addiu      $4, $0, 0x1
    /* F21E4 001F21E4 21286700 */  addu       $5, $3, $7
    /* F21E8 001F21E8 2D10A000 */  daddu      $2, $5, $0
    /* F21EC 001F21EC 8C00A6C4 */  lwc1       $f6, 0x8C($5)
    /* F21F0 001F21F0 B40042C4 */  lwc1       $f2, 0xB4($2)
    /* F21F4 001F21F4 2118E300 */  addu       $3, $7, $3
    /* F21F8 001F21F8 000060C4 */  lwc1       $f0, 0x0($3)
    /* F21FC 001F21FC 2138E600 */  addu       $7, $7, $6
    /* F2200 001F2200 00000000 */  nop
    /* F2204 001F2204 00000000 */  nop
    /* F2208 001F2208 C3190246 */  div.s      $f7, $f3, $f2
    /* F220C 001F220C 040061C4 */  lwc1       $f1, 0x4($3)
    /* F2210 001F2210 080064C4 */  lwc1       $f4, 0x8($3)
    /* F2214 001F2214 00000000 */  nop
    /* F2218 001F2218 00000000 */  nop
    /* F221C 001F221C C3180646 */  div.s      $f3, $f3, $f6
    /* F2220 001F2220 0800E5C4 */  lwc1       $f5, 0x8($7)
    /* F2224 001F2224 06130046 */  mov.s      $f12, $f2
    /* F2228 001F2228 0000A0E7 */  swc1       $f0, 0x0($29)
    /* F222C 001F222C 2D28A003 */  daddu      $5, $29, $0
    /* F2230 001F2230 0400A1E7 */  swc1       $f1, 0x4($29)
    /* F2234 001F2234 1000A627 */  addiu      $6, $29, 0x10
    /* F2238 001F2238 0800A4E7 */  swc1       $f4, 0x8($29)
    /* F223C 001F223C 0000E1C4 */  lwc1       $f1, 0x0($7)
    /* F2240 001F2240 0400E0C4 */  lwc1       $f0, 0x4($7)
    /* F2244 001F2244 1000A1E7 */  swc1       $f1, 0x10($29)
    /* F2248 001F2248 1400A0E7 */  swc1       $f0, 0x14($29)
    /* F224C 001F224C 1800A5E7 */  swc1       $f5, 0x18($29)
    /* F2250 001F2250 50AE87E7 */  swc1       $f7, %gp_rel(D_0062BA40)($28)
    /* F2254 001F2254 58AE83E7 */  swc1       $f3, %gp_rel(D_0062BA48)($28)
    /* F2258 001F2258 1C00A0AF */  sw         $0, 0x1C($29)
    /* F225C 001F225C 4CAE82E7 */  swc1       $f2, %gp_rel(D_0062BA3C)($28)
    /* F2260 001F2260 54AE86E7 */  swc1       $f6, %gp_rel(D_0062BA44)($28)
    /* F2264 001F2264 5CAE82E7 */  swc1       $f2, %gp_rel(D_0062BA4C)($28)
    /* F2268 001F2268 34C5070C */  jal        LightTorchOnOfWeaponWithNoSE
    /* F226C 001F226C 60AE82E7 */   swc1      $f2, %gp_rel(D_0062BA50)($28)
    /* F2270 001F2270 48AE90AF */  sw         $16, %gp_rel(D_0062BA38)($28)
    /* F2274 001F2274 3000BFDF */  ld         $31, 0x30($29)
    /* F2278 001F2278 2000B0DF */  ld         $16, 0x20($29)
    /* F227C 001F227C 0800E003 */  jr         $31
    /* F2280 001F2280 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001F21B0
    /* F2284 001F2284 00000000 */  nop
```

## Detailed findings — IDENTICAL to GetRegularizedWindSpeed
func_001F21B0 is the same body as GetRegularizedWindSpeed sourced from arg `a0`
instead of `D_0062BA38` (both end with `D_0062BA38 = idx`). See
`tough_nuts/GetRegularizedWindSpeed/notes.md` for the full semantic model
(wind-frame table, position/direction Vec4, scale reciprocals) and the wall.

**Hand floor: rc15** via **q-first declaration order** (declare
`float *q = &D_005EBD14[idx*100-3]` BEFORE `p`). The `a0` prologue shifts
register pressure vs Get (whose floor was rc17), but the SAME residual remains:
ROM materializes `base + idx*0x190` in 3 registers
(`addu a1,v1,a3` + `daddu v0,a1,zero` copy + `addu v1,a3,v1` remat) for the
scales/position split; my source keeps it in 1-2. Not source-coercible (CSE
merges value-equal addr exprs; no branch to force a non-coalesced copy).

31 distinct hand hypotheses folded (same set as Get + q-first/2D/fresh-base
variants); none triggered the 3-reg split. Permuter-class. **Whatever cracks
GetRegularizedWindSpeed's remat transfers here directly** — re-apply the same
clean shape with `idx = a0`.
