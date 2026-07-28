# conv-2 pass ledger (worker 2)

Convergence pass over the ≤81-insn retail-vs-aug6 near-miss queue
(`convpass_worker2.json`, 60 TU sets). Method: mechanically splice the aug6
twin body (`port_from_aug6.py` + `PORT_DEBUG_DUMP`), then edit the SOURCE to
express whatever the retail dev changed after Aug 6.

## Systematic retail-vs-aug6 edits found so far

| pattern | detail |
|---|---|
| **Sub15C geometry slot +0x10** | the shared `Sub15C` model/geometry pointer the aug6 tree calls `p_7F0` sits at **0x800** in retail (`include/ico/types.h` already has it as `p_800`; the `p_7F0` field there is a stale aug6 leftover with no retail consumer). Same +0x10 shift shows up as 0x110→0x120 (fieldCollision) and 0x120→0x130 (act_a_p_1). |
| **act/BoxBar wrapper object 0xB4 → 0xC4** | the `actStXX` BoxBar wrapper family's `ActB4Obj` member moved from 0xB4 to 0xC4. Bump the `pad[]` in the TU-local typedef. |
| **BoxBarSoundOn id 0x189 → 0x18D** | the sound/bar id constant the script TUs pass shifted by +4. |
| **assert `__LINE__` args drift** | retail source files gained lines: debug.c 0x4F4/0x4F5 → 0x503/0x504. |
| **table sizes / layout ids drift** | charFileManager model table 1576 → 1582 entries; gather_effect layout id 0x3F → 0x40 and 0x1E0 → 0x1E1. |
| **extra call argument** | `file_Init(x)` (aug6) became a 2-arg call `func_001227C8(x, 0xA)` in retail (src/flag.c InitFlagGeo). |
| **32-bit flag word widened to 64-bit** | `*(int *)(p+0x20) & 1` (aug6) → `(int)(*(long long *)(p+0x20) >> 1) & 1` in retail (fieldCollision clip_wall_1): `ld`+`dsll 31`+`dsra32 0`+`andi 1`. |
| **`provisional-ordinal` name skew** | in src/st19a.c the retail ordinal names are shifted one slot vs aug6: retail `actSt19aOriDown` carries aug6 `actSt19aPipeChk`'s body, retail `actSt19aHaguruma` carries aug6 `actSt19aOriDown`'s. Always read the retail `.s` before trusting the name. |

## Batch 1 — TU sets 0-7 (24 matched, 0 deferred)

| TU | matched | deferred |
|---|---|---|
| src/fieldCollision.c | MakeCollisionDependGObjList, clip_wall_1 | — |
| src/charFileManager.c | ReadModelFile, ReadVolumeModelFile | — |
| src/flag.c | InitFlagGeo | — |
| src/act_a_p_1.c | WakeUpAP1, subAP1BrainMain, SetAP1HostGObj, AP1BeforeFunc, GetAP1AIMode, SetAP1PriorLevel, walkAI, actAP1Start, hitProc, SleepAP1 | — |
| src/cageFix.c | InitCageFixGeo, CageFixGeo, CageFixDL | — |
| src/debug.c | debug_openLog | — |
| src/gather_effect.c | GatherEffect_InqEnd | — |
| src/st19a.c | actSt19aHagurumaChk, actSt19aPipeChk, actSt19aOriDown, actSt19aHaguruma | — |

## Batch 2 — TU sets 8-17 (36 matched, 0 deferred)

| TU | matched | note |
|---|---|---|
| src/st08a.c | actSt08aDoorUp, actSt08aEnd, actSt08aEne1Chk, actSt08aEne2Chk, actSt08aDoor, actSt08aEne1, actSt08aEne2, **func_00223BF0, func_00223C78, func_00223D00** | the three `divergent` entries were **splat-merged**: retail `symbol_addrs` was missing the boundary after each infinite-loop `actSt08aXxx`, so splat glued the following (unnamed) function onto it. Added `func_00223BF0/C78/D00` as `provisional-ordinal` symbols → both halves match. 3 bonus functions. |
| src/Light.c | light_DrawCursor, light_Tool | table stride 0x190 → 0x194 |
| src/layout_texture.c | lt_analog2Pad | retail added a `Vibration_WaveDecode()` call in the `a0 != 0` arm |
| src/boy.c | dispClothes, execClothes | 0x7F0→0x800, 0x124→0x134, 0x834→0x844 |
| src/rope.c | ReleaseRope, HoldRope, RopeDL | |
| src/sceneManager.c | test_nextstage_firstwalk_set | `iosOmBeforeFuncStandard` kind 0x2E → 0x2F |
| src/op.c | actOpDemo03Chk, actOpDemo01, actOpDemo01_2Chk, actSt24aConte01_2, actTitleCamera2, actSt13aConte01_3, actSubMpegReturnPreload, actTitleReadTimeDemo0, actOpDemo01_2, actOpDemo02, actTitleShortCut, actSt26aConte01_1_newgame | |
| src/keyInput.c | InitKeyInput | 0xB0 → 0xC0 |
| src/actressLight.c | SetActressLight | |
| src/stageMultiBgaManager.c | EntryStageMultiBgaManager | retail added an `else if (D_00274EC0[5] == 0)` guard around the `_ApplyCurrentMatrix` call |

### More systematic edits

- **script/`actStXX` id spaces shifted +1**: the bg-animation / way-flag ids
  passed to `stage_KillPlayBgAnimation`, `func_0017B258`, `func_0017B230`,
  `func_0012AA80` in the **0x133–0x143** and **0x2F6–0x2F9** ranges are all
  one higher in retail. Ids below that (0xE, 0x10, 0x28, 0xFD–0xFF) are
  unchanged, so this is one inserted entry near the top of those tables, not
  a global renumber.
- **`BoxBarSoundOn` second arg 0x189 → 0x18D** holds everywhere so far.
- **splat-merged pairs** are a recurring shape in the script TUs: an
  `actStXX` that ends in `while(1) _ACTWait(1);` is followed by an unnamed
  function retail's ordinal name list never got. Look for `b .L…` + a second
  `addiu $29,$29,-0x20` prologue inside one `.s`.

## Batch 3 — TU sets 18-27 (48 matched, 3 deferred)

| TU | matched | deferred |
|---|---|---|
| src/attackCheckBoundary.c | AttackCheckBoundaryBeforeFunc, actAttackCheckBoundaryStart, switchOnSE | — |
| src/st05d.c | actSt05dDoor2 | actSt05dDoor2UpChk |
| src/motionManager2.c | GetCollisionOfLastActiveField, _GetMotionDirection, CopyMotionWithNodeHrc, dispPlane | CheckPureCliffAttribute |
| src/generator.c | Generator_MaskOff, Generator_ResetCount, Generator_Mask, Generator_Call, Generator_QuickCall, MakeGeneratorPacket, SetMotherGenerator | — |
| src/jimaku.c | jimakuUndisp | jimakuHandler |
| src/st07a.c | all 21 | — |
| src/st05b.c | all 9 | — |
| src/script.c | scpDispOnAllWithKind, scpActivateAllWithKind | — |
| src/girl.c | InitGirlGeo | — |

### Deferred

- `actSt05dDoor2UpChk` (src/st05d.c) — **rc4**, crutch-free. Residual is a pure
  two-allocno tie: ROM puts `%hi(D_004D1BB0)` in `s0` and `%hi(actSt04lRope2Chk)`
  in `s1`; our build swaps them. The aug6 twin compiles to the ROM order from the
  *same* C, so this is not a source-order effect I could find — 9 distinct
  spellings tried (statement swap, `int *tbl` temp before/after the loop,
  `&D_x[0]`, extern reorder, pad size). Same family as the standing
  `two_allocno_tie_nearmisses` parks.
- `CheckPureCliffAttribute` (src/motionManager2.c) — divergent (dc 47), no aug6
  twin body to splice; genuine retail rewrite, not started.
- `jimakuHandler` (src/jimaku.c) — divergent (dc 30), same.

### Tooling fix landed: `tools/preprocess_old_as.py`

A `%gp_rel()` operand can carry an addend (`%gp_rel(D_00633C00 + 0xC)`, emitted
by splat for a mid-struct gp-relative access). The script copied the whole
expression into its `.extern` header, producing `.extern D_00633C00 + 0xC, 4`,
which the **period assembler rejects** — so `compile_c.sh` silently fell back to
modern gas for that whole TU, and modern gas **over-fills `jr $31` delay slots**
with the preceding store. That is why `CopyMotionWithNodeHrc` came out as
`jr ra; sw …` where the ROM has `sw …; jr ra; nop`, even though the identical C
matches in the aug6 tree. Header now names the symbol only. Full clean rebuild
still verifies `fbf50c75`. **Any TU whose `.s` contains `%gp_rel(SYM + N)` was
being assembled with the wrong assembler — expect more jr/jal-delay near-misses
to fall out for free.**

### More systematic edits

- `stage_KillPlayBgAnimation` / `func_0017B230` / `func_0017B258` id **+1** holds
  across st07a, st05b, st05d, op (0xC8→0xC9, 199→200, 205→211, 280→286, 303→307,
  310→311). The **1300–1460** id band moves **+4 or +6**, per id — never assume,
  read it off the diff.
- `tools/autofix.py`-style mechanical immediate rewriting (scratchpad) resolves
  nearly all script-TU near-misses: only *identical* constants used for two
  different parameters need hand-splitting (`actSt07aEnd`: a0 0xC8→0xC9 but a2
  stays 0xC8).

## Batch 4 — TU sets 28-41 (53 matched, 8 deferred)

| TU | matched | deferred |
|---|---|---|
| src/Packet.c | — | pac_continueTag |
| src/st22a.c | actSt22aLightningVolime, actSt22aIntroSub | — |
| src/motionViewer.c | setMotionSpeed, setRootUpdateMode | — |
| src/st04b.c | actSt04bEnd | — |
| src/torch.c | TorchGeo, TorchDL, IsTorchLightOn, torchOffSE, InitTorchGeo | — |
| src/windManager.c | GetRegularizedWindSpeed | — |
| src/st05c.c | actSt04rDoorChk, actSt04rDoor2Chk, actSt05cSolarXL, actSt05cDoorDownChk, actSt05cWaterXL, actSt05cEne, actSt05cEnemy1, actSt05cEnemy2, **func_0021F060, func_0021F0E8, func_0021F170** | actSt05cDoorDown, actSt05cDoorDownEvent |
| src/gflag.c | gflagInit, gflagOff | — |
| src/st03t.c | actSt03tSwitchRChk, actSt03tInit, actSt03tSekizo, actSt03tSwitchLUpChk, actSt03tSwitchRUpChk, actSt03tWay, actSt03tGirlCam, actSt03tSwitchLChk, actSt03tGirlCamEndChk, actSt03tSwitchL | actSt03tGirlCamStartChk, actSt03tSwitchR, actSt03tWayOffChk |
| src/st04a.c | actSt04aConte06Jimaku, actSt04aGateRChk, actSt04aTorchAllFlagfChk, actSt04aTorch1Chk, actSt04aGateL, actSt04aGateOpen3Chk, actConte09_3, actSt04aTorchXL, actSt04aGateOpen, actConte09Jimaku | actSt04aGateLChk |
| src/st04c.c | all 8 | — |

`src/st05c.c` needed the same **splat-merge symbol carve** as st08a: added
`func_0021F060 / func_0021F0E8 / func_0021F170` to `config/symbol_addrs.us.txt`.
3 bonus functions.

Still splat-merged and NOT yet carved (next worker: add the second prologue's
address to `symbol_addrs.us.txt`, then both halves port):
`actSt03tGirlCamStartChk` (2nd prologue 0x00212AF8), `actSt10rEne` (0x002276F8).

Single-prologue wave-0 rewrites still deferred: `pac_continueTag`,
`actSt03tSwitchR`, `actSt03tWayOffChk`, `actSt04aGateLChk`,
`actSt05cDoorDown`, `actSt05cDoorDownEvent`.

### Notes
- `src/windManager.c`: the spliced `static inline windApply` helper had to move
  **below** the TU's extern block (it referenced `D_006337xx` before their
  declarations). Retail also re-shaped the table: stride 100 floats → **101**,
  and the `g` element index **45 → 36** (`h` stayed 35).
- `src/st22a.c actSt22aIntroSub` shows a residual `lui s1,0x62 | lui s1,0x0`.
  That is a splat artifact — the baseline `.s` renders the *second* copy of
  `%hi(D_0061C100)` as the literal `(0x620000 >> 16)` instead of a reloc.
  Identical after linking; `ninja` verifies.
- `p_7F0`→`p_800` retyping keeps showing up in `include/ico/types.h` consumers
  (`src/torch.c`, `src/rope.c`, `src/cageFix.c`, `src/actressLight.c`). The
  mechanical fix is `((Obj7F0 *)GOBJ_SUB(x)->p_800)`; do **not** edit the
  `p_7F0` field offset in the header, it has no retail consumer.

## Batch 5 — TU sets 42-59 (60 matched, 11 deferred)

| TU | matched | deferred |
|---|---|---|
| src/act_bird.c | interp_vector_sa | subBirdBrainMain, Debug_WireString_Bird |
| src/weapon.c | all 12 | — |
| src/box.c | ExecBoxMoveEndReaction, BoxGeoRestore, BoxExtGeoRestore, initLanding, inertiaMove | — |
| src/GsBase.c | — | gsb_StageSettingTool |
| src/item.c | ReleaseItem, avoidInsideOfWall, execBombGeo, bombExplodeSE | — |
| src/st08b.c | all 12 | — |
| src/StageAnimation.c | stage_CalcAnimationParent, stage_DispBgAnimation | stage_SetScale |
| src/st04d.c | all 8 | — |
| src/switch.c | SetWallLeverWithNodePoint, InitWallLeverGeo, initParentize | IsWallLeverStatus, GetWallLeverAngle |
| src/st00a.c | all 6 | — |
| src/itou_boss.c | — | BossEnemyFunc, gene_enemy |
| src/st13b2.c | — | actSt13b2Generator |
| src/st13b.c | all 4 | — |
| src/way_util.c | — | GetWgAll |
| src/st13c.c | actSt13cCageFallEffect, actSt13cGirlCarryChk, actSt13cConte05Jimaku, actSt13cCageFallChk, actSt13cConte05 | actSt13cBmg1, actSt13cHandChk |
| src/candle.c | InitCandleGeo, _deleteLayoutedCandleParticleEffect, CandleGeo | — |
| src/st10l.c | actSt10lChain, actSt10lInit, actSt10lGondolaUp | actSt10lChainMove |
| src/girlForceField.c | InitGirlForceFieldGeo, GirlForceFieldDL | — |

### Splice pitfalls found (fix these when a port "reverts with parse/undeclared")

1. **`src/box.c` — bogus unity `#include "switch.c.inc"` ×6.** aug6 builds
   box.o as a unity TU that `#include`s `sugipon/src/switch.c.inc`. Retail
   links `src/switch.c` as its own TU, so the driver's "headers the aug6 TU
   pulled in" step injects six includes of a file that does not exist here.
   Delete them.
2. **Plain `struct` definitions are not carried.** The driver moves `typedef`
   blocks but not bare `struct X { … };` — `struct vec4_iner` (box.c
   `inertiaMove`) and `struct gff_vec` (girlForceField.c `GirlForceFieldDL`)
   had to be re-added by hand above their user.
3. **`static inline` helpers land at the top of the file** and can reference
   externs declared further down (`src/windManager.c windApply`). Move the
   helper down to just above its caller.
4. **`extern int D_xxx;` vs `extern char D_xxx[];` decides gp-rel vs `lui/%lo`**
   (-G8). `src/candle.c CandleGeo` came out with `lw a2,0(gp)` where the ROM
   has `lui/addiu` purely because two assert-string symbols were declared
   `int`. Retyping them `char[]` took it from rc77 → 0 (with `i*0x50 → i*0x40`).
5. **`switch.c` functions are not port candidates** — their aug6 twins live in
   `sugipon/src/box.c` (unity), so the name-join puts them in the wrong TU.
   Hand-splice from `sugipon/src/switch.c.inc`.

### Still splat-merged (2+ prologues in one `.s`) — carve then port, 2 funcs each
`subBirdBrainMain` (0x00197198, 0x001971C0 — **3** functions merged),
`actSt13cBmg1` (0x0022B5E8), `actSt13cHandChk` (0x0022BD58),
`actSt10lChainMove` (0x00225DD0), `actSt03tGirlCamStartChk` (0x00212AF8),
`actSt10rEne` (0x002276F8).

### Single-prologue wave-0 rewrites deferred
`gsb_StageSettingTool`, `Debug_WireString_Bird`, `BossEnemyFunc`, `gene_enemy`
(rc52 — retail hoists a `$gp` base the aug6 body materializes with `lui`),
`actSt13b2Generator`, `GetWgAll`, `stage_SetScale`, `IsWallLeverStatus`,
`GetWallLeverAngle` (the last two have **no aug6 body either** — INCLUDE_ASM on
both sides, so they are fresh work, not ports).

## Batch 6 — splat-merge carves (11 matched, 2 deferred)

Added the missing second-prologue symbols to `config/symbol_addrs.us.txt`
(`provisional-ordinal`) so splat splits the merged `.s`, then ported both
halves:

| carved symbol | pairs with | result |
|---|---|---|
| `func_0022B5E8` | actSt13cBmg1 | both matched |
| `func_0022BD58` | actSt13cHandChk | first half matched, second **deferred at rc6** |
| `func_00225DD0` | actSt10lChainMove | both matched |
| `func_002276F8` | actSt10rEne | both matched |
| `func_00212AF8` | actSt03tGirlCamStartChk | second half matched; **first half still deferred** |
| `func_00197198`, `func_001971C0` | subBirdBrainMain | carved only (3-way merge); all three still INCLUDE_ASM |

### Two hard-won gotchas for whoever does the next carve

1. **splat only emits a `nonmatchings/*.s` for a symbol the `.c` already
   references.** After adding the symbol you must add an `INCLUDE_ASM(...)`
   line for it and re-run `build.sh setup`, otherwise the `.s` never appears
   and the linked TU is silently short those bytes.
2. **The `INCLUDE_ASM` order in the `.c` IS the `.text` order.** Inserting the
   two act_bird halves in the wrong order still passed every `quick_diff` and
   only showed up as a full-ELF SHA mismatch at ROM offset 0x97198. Order the
   inserted lines by ascending VMA.

`func_0022BD58` residual (rc6): ROM schedules `sw $3,%gp_rel(D_006325B4)`
*after* the `lw $16,0x164($2)` sub-object load, immediately before the
`jal func_0017B230`; our build sinks it up into the prologue. Statement order
(`field_B0 = 0` vs `D_006325B4 = 1` first) does not move it — a sched2 tie.

---

## Final tally

**329 of 349 queued functions matched (94%)**, plus **12 bonus functions** that
did not exist as separate symbols before this pass (the splat-merge carves).
All 60 TU sets worked. Every commit ends `verify_elf: OK (…fbf50c75…)`.

### The 20 still open (all re-enter the standing queue — none is a floor)

| function | TU | state |
|---|---|---|
| actSt05dDoor2UpChk | st05d | **rc4** two-allocno `%hi` tie (s0/s1) |
| func_0022BD58 | st13c | **rc6** sched2 tie on a `%gp_rel` store |
| actSt03tGirlCamStartChk | st03t | carved, not started (partner matched) |
| subBirdBrainMain | act_bird | carved 3-way, not started |
| CheckPureCliffAttribute, jimakuHandler, pac_continueTag, actSt05cDoorDown, actSt05cDoorDownEvent, actSt03tSwitchR, actSt03tWayOffChk, actSt04aGateLChk, Debug_WireString_Bird, gsb_StageSettingTool, stage_SetScale, BossEnemyFunc, gene_enemy, actSt13b2Generator, GetWgAll | — | wave-0 retail rewrites; aug6 twin exists but diverges |
| IsWallLeverStatus, GetWallLeverAngle | switch | **no aug6 body either** — fresh decomp, not a port |

### Method that worked, in one paragraph

`PORT_DEBUG_DUMP=<dir> tools/port_from_aug6.py port <tu> --apply --only <func>`
leaves the rebound-but-rejected candidate TU in the dump directory; copy it over
the real TU and you have the aug6 body already symbol-rebound. From there almost
every retail delta is a *constant*: read the immediate pairs straight off
`quick_diff` and rewrite them inside that one function's body. The scratchpad
tools that automate it (`spl.sh`, `qd.py` with coalesced-TU normalization,
`autofix.py`, `dotu.sh`, `revert.py`) are worth rebuilding for the next pass —
`dotu.sh <tu> <func>...` took most script TUs from "12 near-misses" to
"12 matched" in one command.
