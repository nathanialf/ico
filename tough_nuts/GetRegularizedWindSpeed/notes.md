# GetRegularizedWindSpeed — parked

VRAM: 0x001F2058 (file_off 0x0F2058)
Asm source: asm/aug6/nonmatchings/sugipon/src/windManager/GetRegularizedWindSpeed.s

## Attempt at 2026-06-10

**Reason parked:** rc17 on-path (best-by-count rc11 is a dead-end: h on q-base). Residual = gcc-2.9 rematerializes base+idx*0x190 into 3 regs (copy daddu v0,t0,zero + remat addu v1,a3,v1) for scales/position split; my source keeps it in 1-2 regs. Not source-coercible (CSE merges value-equal addr exprs; no branch to force non-coalesced copy). Permuter-class.

**TU:** `sugipon/src/windManager.c`

**Seed:** `tough_nuts/GetRegularizedWindSpeed/GetRegularizedWindSpeed.c`

Disassembly:

```
.align 3
nonmatching GetRegularizedWindSpeed, 0xD4

glabel GetRegularizedWindSpeed
    /* F2058 001F2058 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F205C 001F205C 90010724 */  addiu      $7, $0, 0x190
    /* F2060 001F2060 2000B0FF */  sd         $16, 0x20($29)
    /* F2064 001F2064 5F00033C */  lui        $3, %hi(D_005EBD14)
    /* F2068 001F2068 48AE908F */  lw         $16, %gp_rel(D_0062BA38)($28)
    /* F206C 001F206C 14BD6324 */  addiu      $3, $3, %lo(D_005EBD14)
    /* F2070 001F2070 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* F2074 001F2074 00188144 */  mtc1       $1, $f3
    /* F2078 001F2078 F4FF6924 */  addiu      $9, $3, -0xC
    /* F207C 001F207C 18380702 */  mult       $7, $16, $7
    /* F2080 001F2080 3000BFFF */  sd         $31, 0x30($29)
    /* F2084 001F2084 0C00A3E7 */  swc1       $f3, 0xC($29)
    /* F2088 001F2088 01000424 */  addiu      $4, $0, 0x1
    /* F208C 001F208C 2D28A003 */  daddu      $5, $29, $0
    /* F2090 001F2090 1000A627 */  addiu      $6, $29, 0x10
    /* F2094 001F2094 21406700 */  addu       $8, $3, $7
    /* F2098 001F2098 2D100001 */  daddu      $2, $8, $0
    /* F209C 001F209C 8C0006C5 */  lwc1       $f6, 0x8C($8)
    /* F20A0 001F20A0 B40042C4 */  lwc1       $f2, 0xB4($2)
    /* F20A4 001F20A4 2118E300 */  addu       $3, $7, $3
    /* F20A8 001F20A8 000060C4 */  lwc1       $f0, 0x0($3)
    /* F20AC 001F20AC 2138E900 */  addu       $7, $7, $9
    /* F20B0 001F20B0 00000000 */  nop
    /* F20B4 001F20B4 00000000 */  nop
    /* F20B8 001F20B8 C3190246 */  div.s      $f7, $f3, $f2
    /* F20BC 001F20BC 040061C4 */  lwc1       $f1, 0x4($3)
    /* F20C0 001F20C0 080064C4 */  lwc1       $f4, 0x8($3)
    /* F20C4 001F20C4 00000000 */  nop
    /* F20C8 001F20C8 00000000 */  nop
    /* F20CC 001F20CC C3180646 */  div.s      $f3, $f3, $f6
    /* F20D0 001F20D0 0800E5C4 */  lwc1       $f5, 0x8($7)
    /* F20D4 001F20D4 06130046 */  mov.s      $f12, $f2
    /* F20D8 001F20D8 0000A0E7 */  swc1       $f0, 0x0($29)
    /* F20DC 001F20DC 0400A1E7 */  swc1       $f1, 0x4($29)
    /* F20E0 001F20E0 0800A4E7 */  swc1       $f4, 0x8($29)
    /* F20E4 001F20E4 0000E1C4 */  lwc1       $f1, 0x0($7)
    /* F20E8 001F20E8 0400E0C4 */  lwc1       $f0, 0x4($7)
    /* F20EC 001F20EC 1000A1E7 */  swc1       $f1, 0x10($29)
    /* F20F0 001F20F0 1400A0E7 */  swc1       $f0, 0x14($29)
    /* F20F4 001F20F4 1800A5E7 */  swc1       $f5, 0x18($29)
    /* F20F8 001F20F8 50AE87E7 */  swc1       $f7, %gp_rel(D_0062BA40)($28)
    /* F20FC 001F20FC 58AE83E7 */  swc1       $f3, %gp_rel(D_0062BA48)($28)
    /* F2100 001F2100 1C00A0AF */  sw         $0, 0x1C($29)
    /* F2104 001F2104 4CAE82E7 */  swc1       $f2, %gp_rel(D_0062BA3C)($28)
    /* F2108 001F2108 54AE86E7 */  swc1       $f6, %gp_rel(D_0062BA44)($28)
    /* F210C 001F210C 5CAE82E7 */  swc1       $f2, %gp_rel(D_0062BA4C)($28)
    /* F2110 001F2110 34C5070C */  jal        LightTorchOnOfWeaponWithNoSE
    /* F2114 001F2114 60AE82E7 */   swc1      $f2, %gp_rel(D_0062BA50)($28)
    /* F2118 001F2118 48AE90AF */  sw         $16, %gp_rel(D_0062BA38)($28)
    /* F211C 001F211C 3000BFDF */  ld         $31, 0x30($29)
    /* F2120 001F2120 2000B0DF */  ld         $16, 0x20($29)
    /* F2124 001F2124 0800E003 */  jr         $31
    /* F2128 001F2128 4000BD27 */   addiu     $29, $29, 0x40
endlabel GetRegularizedWindSpeed
    /* F212C 001F212C 00000000 */  nop
```

## Detailed findings (31 hand hypotheses, 39 → 17 → parked)

**Semantic model (verified):** wind-frame table `D_005EBD14`, 0x190-byte stride
(=100 floats) per index `D_0062BA38`. Each frame: position Vec3 @0 (w=1 → buf1),
direction Vec3 @-0xC (w=0 → buf2), scaleA @0xB4, scaleB @0x8C. "Regularized" =
the `1/scale` reciprocals stored to wind-state globals. func_001F2130 =
SetWind(pos3, dir3, sA, sB); Get/21B0 = load frame + apply, `D_0062BA38 = idx`
is the shared write-back. Vec3-by-value RULED OUT (rc66: emits ldl/ldr/sdl/sdr
struct copies; ROM has none → dev passed scalars).

**The seed (`GetRegularizedWindSpeed.c`) is rc17, the ON-PATH form** — NOT the
lowest count. The lowest hand count was rc11 (`h = q[38]`) but it is a DEAD END:
it loads h from `152(q-base)` whereas ROM loads `140(base+stride)` — different
base reg + offset, can never reach rc0. Seed/permute from rc17, not rc11.

**THE residual wall:** ROM materializes `base + idx*0x190` in **three** regs:
```
addu  t0,v1,a3   ; base+stride
daddu v0,t0,zero ; redundant COPY of base+stride  -> g loaded from v0
lwc1  $f6,140(t0); h from t0
addu  v1,a3,v1   ; REMAT base+stride             -> pos[0..2] from v1
addu  a3,a3,t1   ; dir base = stride+(base-12)
```
My source keeps base+stride in ONE reg (g,h,pos all share it). This is a gcc-2.9
register-allocation rematerialization under div-induced pressure (scales stay
live across the two `div.s` until the position loads). NOT source-coercible:
gcc CSE merges value-equal address expressions, and there is no branch in this
function to force a non-coalesced copy (cf. permuter's `if((new_var2=new_var)>=7)`
crack of func_001FB768). The `daddu v0,t0,zero` + `addu v1,a3,v1` pair is what
the permuter must reproduce.

**Tried & ruled out (none triggered the 3-reg split; all ≥ rc15):** hoist g/h
(rc17) vs no-hoist (rc23); 2D `float[][100]` → stride lands in `$a3` (matches
ROM!) but adds separate `%hi` for dir base (rc15); 2D + `[0][idx*100-3]` for dir
(rc17); q as `p-3` / `(D-3)+idx*100` / `row-3` (32768 split or CSE); r =
`&[idx*100-6]` for buf1 (rc24, wrong offsets 24/28/32); direct-index scales
(rc27, extra mult); pointer-by-ref helper (rc56, struct copies); recips-first
(rc19); one-array buf (rc43); buf2-first (rc29); store-order perms (rc19-21);
index-taking inline helper (rc17); `off=idx*100` temp (forces mult-100+sll2,
avoid it).

**Permuter target lever:** a construct forcing gcc to rematerialize/copy
`base+idx*0x190` for the position load separately from the scales. Re-apply by
hand once found. **func_001F21B0 is the IDENTICAL body** sourced from arg `a0`
instead of `D_0062BA38` — the same fix transfers directly.

## Permuter pass #1 (2026-06-10) — EXHAUSTED (resolution b)
Bounded run (600s, -j4, ~22.7k iters) from the rc17 seed. Harvested the 20
lowest-score outputs by TRUE real_count: best was **rc15** (output-3515-3),
none reached rc0, none beat the parked count. The rc15 form accesses position
& scales via FRESH `(&D_005EBD14[idx*100])[k]` expressions (not cached `p`) to
remat the base — BUT it depends on UNDEFINED BEHAVIOR (`new_var3` passed to
windApply before its `= p[0]` assignment, which reorders the load). Re-applied
CLEANLY (valid C, fresh-base per element) → rc26 (WORSE) — the UB was load-
bearing, so not re-applicable. The 3-reg base remat still not reproduced.
NEXT permuter pass: seed with a longer run or feed the rc15 UB form to study
the exact load-reorder it exploits, then find a valid-C equivalent.
