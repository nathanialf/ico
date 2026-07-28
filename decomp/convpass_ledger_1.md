# Convergence pass — worker 1 ledger

Scope: the 60 TU sets of `convpass_worker1.json` (149 candidate funcs, all
<= 33 insns).  Step 0 (skip anything already matched) leaves **52 funcs in
20 TU sets** actually needing work; the other 97 were already `PORTED` /
`PRE-MATCHED` by Phase 4.

Method per function: read the retail `.s`, read the aug6 twin's C, work out
*what the retail dev changed after Aug 6*, and write that C.  No crutches,
no per-func flags, no yaml/carve edits.

## Systematic retail-vs-aug6 edit patterns

These recur across many TUs — later workers should assume them first.

1. **`gobj+0x15C` sub-object: the `0x7F0` slot moved to `0x800`.**  By far
   the biggest class.  Any aug6 body spelling
   `*(T **)((char *)p + 0x7F0)` becomes `+ 0x800` in retail.  Same +0x10
   shift shows up at other offsets in the same struct:
   `0x60C -> 0x61C`, `0x634 -> 0x644`, `0x544 -> 0x554`, `0x4A0 -> 0x4B0`,
   `0x100 -> 0x110`, `0x830 -> 0x840`.  Read as: 16 bytes inserted into the
   motion/sub struct somewhere below 0x100.
2. **Camera set stride 0x190 (400) -> 0x194 (404).**  `D_005EBC48_arr[][0x64]`
   -> `D_005F2FB8_arr[][0x65]`; element indices are unchanged.
3. **`ito/mpeg` display constants bumped by one** (`400->404`, `59->60`,
   `814->815`) — the movie viewport/TEX0 params were retuned.
4. **`__LINE__` immediates drift** (e.g. `1087 -> 1085`) — asserts in a
   header/TU moved a couple of lines.  Not a code change.
5. `mv_defs.h` does not exist in the retail tree, so every aug6 `ito/mpeg`
   body that includes it must be re-spelled with plain casts.

## Log

Legend: `MATCHED` (byte-identical, committed) · `pass-deferred` (budget
spent, reverted to `INCLUDE_ASM`, re-enters the standing queue).

### batch 1

| TU | func | result | note |
|---|---|---|---|
| ito/mpeg/mv_main | proceedAudio | MATCHED | `initAll(*a0)`; retail `initAll` takes `int`, no `mv_defs.h` needed |
| ito/mpeg/mv_main | readMpeg | MATCHED | void tail call to `proceedAudio` |
| src/worm | WormDL | MATCHED | pattern 1 (`0x7F0 -> 0x800`) |
| src/frameDependSequence | execEff | MATCHED | `p[0x183] -> p[0x187]` (pattern 1) |
| src/frameDependSequence | ExecuteSEPackageWithGroupVariation | MATCHED | `0x634 -> 0x644` (pattern 1) |
| src/camera-ico2 | InitPluralCameraSet | MATCHED | pattern 2, stride 404 |
| src/ebrain | eBrainGetTarget | MATCHED | pattern 1 |
| src/ebrain | eBrainInit | MATCHED | pattern 1 |
| src/ebrain | eBrainStatusSet | MATCHED | pattern 1 |
| src/ebrain | eBrainSendMes | MATCHED | pattern 1 |
| src/ebrain | GetStageFromLabel | MATCHED | pattern 1 |
| src/ebrain | eBrainGetTargetGeneratorFromLabelStage | MATCHED | pattern 1 |
| src/gamesys | gamesysObjInfoInit | MATCHED | `long long` bit test; globals must be `char D_x[]` (array => `%hi/%lo`, not `$gp`) |

### batch 2

| TU | func | result | note |
|---|---|---|---|
| src/lineManager | Draw2DLine | MATCHED | pattern 1 |
| src/lineManager | Draw2DLineSeg_Start | MATCHED | pattern 1 |
| src/lineManager | Draw2DLineSeg_Loop | MATCHED | pattern 1 |
| src/lineManager | Draw2DLineG | MATCHED | pattern 1 |
| src/motionFileManager | pursueNodeList | MATCHED | node table shrank: `i <= 0x43F` -> `i <= 0x43D` |
| src/st25a | actConte12Jimaku | MATCHED | `St25State` +0x10 below 0x110, unchanged at 0x328 |
| src/enemy | EnemySetfDisappear | MATCHED | `0x830 -> 0x840` |
| src/enemy | ReviveEnemyParticle | MATCHED | pattern 1 |
| src/enemy | isExistEnemyParticle | MATCHED | pattern 1 |
| src/enemy | EnemyGetNSafeParts | MATCHED | pattern 1 |
| src/enemy | InitDemoMotionGeo | MATCHED | pattern 1 |
| src/enemy | HotInitDemoMotionGeo | MATCHED | pattern 1 |
| src/enemy | GetEnemyHitNodeFlag | MATCHED | pattern 1 |
| src/enemyParts | InitEnemyEye | MATCHED | pattern 1 |
| src/enemyParts | EntryEnemyFootPrint | MATCHED | pattern 1 |
| src/enemyParts | DispEnemyFootPrints | MATCHED | pattern 1 + `0x830 -> 0x840` |
| src/enemyParts | InitPointBlur | MATCHED | pattern 1 |
| src/enemyParts | UpdateEnemyEye | MATCHED | pattern 1, eye table `D_00617828 -> D_0061D560` |
| src/enemyParts | DispEnemyEye | MATCHED | pattern 1 |
| src/way_llf | InitWayPointSystem | MATCHED | way-point table grew 64 -> 94 records (stride 0x34) |
| src/way_llf | CreateTempWayGroup | MATCHED | temp-group table grew 215 -> 275 records (stride 0x40) |
| src/waySystemManager | CreateWaySystemManagerGObj | MATCHED | `0x120/0x1E0 -> 0x130/0x1F0` |

### batch 3

| TU | func | result | note |
|---|---|---|---|
| src/gv | GetMatrixDirectionToZ | MATCHED | pattern 1 |
| src/gv | _InterRotGV | MATCHED | pattern 1 |
| src/act-game | ACTParaStatus_Exec | MATCHED | `Sub15C` 0x534/0x538/0x53C -> 0x544/0x548/0x54C; reused the matched sibling `ACTParaStatus_Clear`'s `volatile int *self` shape |
| src/act-game | GetSkeltonOrient | MATCHED | char-status index 0x490 -> 0x4A0; table `D_0055DA10 -> D_00565060` |
| src/act-game | updateHMC | MATCHED | same index shift; `D_00629DE4 -> D_00631AE4` |
| src/act-game | ACTGameCollisionOn | MATCHED | **semantic edit**: attr bit `>> 6` -> `>> 9` (a flag was inserted in the per-state attribute word) |
| src/act-parallel-control | ActPara_DebugOut | MATCHED | fields widened: two `sw` at 0x54/0x58 became two `sd` at 0x58/0x60. Source order must be 0x58 then 0x60 (gcc emits the pair reversed) |
| src/chain | UpdateRootPosition | MATCHED | pure symbol rebind |
| src/chain | pendulum_Process | MATCHED | pattern 1 |
| src/way_kidnap | add_wp_pos | MATCHED | node pool grew `0xD7 -> 0x113` entries (stride 0x40); needed a TU-local struct name (retail's `Nd` has different members) |
| src/way_kidnap | NumOfWpPos | MATCHED | way-point table 64 -> 94 records |
| src/way_kidnap | WayLengthOfGObj_Pos | MATCHED | same |
| src/way_kidnap | WayPointWithRangeFromGObj | MATCHED | same |

### batch 4

| TU | func | result | note |
|---|---|---|---|
| src/ropeFix | RopeFixDL | MATCHED | pattern 1 + `f_608 -> 0x618`; the Phase-4 revert was only a sibling redeclaration clash (`isysGObjSearchFromObjLayoutID`) |
| ito/mpeg/mv_disp | endDisplay | MATCHED | pattern 2 (display-buffer stride 0x190 -> 0x194) |
| ito/mpeg/mv_disp | setGIFad | MATCHED | **semantic edit**: `MoveNextStage_Clear(0x3B, 0x44, …)` -> `(0x3C, 0x45, …)` |
| ito/mpeg/mv_disp | setTEX0_1 | MATCHED | **semantic edit**: sentinel `0x32E -> 0x32F` |

## Result

**52 attempted, 52 MATCHED, 0 pass-deferred.**  Every one of the 20 TU sets
that still had work was a *mechanical* retail-vs-aug6 source edit, not a
codegen problem: no function needed more than 2 hypotheses, none needed a
crutch, none needed a carve.

### Note for the harness, not for the source

`tools/quick_diff.sh <tu-stem> <func>` does **not** apply the three
coalesced-TU disassembly tolerances that `port_from_aug6.py` grants, so a
byte-identical body still prints a diff for any of:

* a same-function relative branch (`bne …,20 <f+0x20>` vs `bne …,1a08 <f+0x20>`)
  — identical `+0xNN`, different absolute;
* a call unresolved on **both** sides (`jal 0 <f>` vs `jal 0 <first_func_in_TU>`);
* a call the built object resolves in-TU while the isolated baseline leaves at 0;
* one trailing `sll zero,zero,0x0` — the real `.p2align 3` pad that lives in ROM
  just past `endlabel`.

All four were gated for real by the full `ninja` SHA-1
(`fbf50c75cd5911273511c4f9af90503ff8423582`) on every batch.

## Step 5 — unnamed-counterpart identification (`provisional-ordinal`)

Method: for each of my TUs, take the retail function list in address order and
the aug6 twin TU's list in address order, align them with `difflib` on the
*named* anchors, then sub-align each mismatched block on **function size**.
A retail `func_00XXXXXX` that lands opposite a named aug6 function of exactly
the same size, between the same two anchors, is taken as its counterpart.

**32 identifications**, no name collisions, all tagged `provisional-ordinal`
in `config/symbol_addrs.us.txt`.  The `src/chain.c` run (12 consecutive small
functions at 0x190298-0x190430) is independently corroborated: retail
`src/ropeFix.c`'s already-matched `InitRopeFixGeo` calls `func_00190430`
exactly where the aug6 twin calls `UnLockChainGeo`.

Named-only (aug6 side is still `INCLUDE_ASM`, nothing to port):
`iosCdvdChgFileName`, `reg_transMicroCode`, `ACTNotNeedCameraOffset`,
`GetPositionOnTheChain`, `TestChainUpDown`, `ReleaseChain`, `GetChainPendulum`,
`IncreasePdlChain`, `DecreasePdlChain`, `SetRootMatrixWithTransOffsetByDObj`,
`SetDirectRootPositionNoFittingWithNodePoint`.
Already-matched retail bodies, renamed only: `AdpcmFadeCloseAll`,
`GetStreamMotionData`, `_ACTCharStatus_Clear`, `ACTGame_CommonLoop`,
`ACTItemWatchMotion`.

### batch 5 — ports unlocked by the new names

| TU | func | result | note |
|---|---|---|---|
| src/geometryManager | SetRootQuaternion | MATCHED | clean mechanical port |
| src/chain | PlumbOrientUpdateChain | MATCHED | pattern 1 |
| src/chain | isBottomOfChain | MATCHED | pattern 1 |
| src/chain | isStopChain | MATCHED | pattern 1 |
| src/chain | GetChainClimbOrient | MATCHED | pattern 1 |
| src/chain | CheckChainClimbablePos | MATCHED | pattern 1 |
| src/chain | GetChainClimbCollision | MATCHED | pattern 1 |
| src/chain | SetChainParentGObj | MATCHED | pattern 1 |
| src/chain | GetChainDirCorrectVal | MATCHED | pattern 1 |
| src/chain | GetRootPositionHandExtra | MATCHED | pattern 1 |
| src/chain | InitPendulum | MATCHED | pattern 1 |
| src/chain | LockChainGeo | MATCHED | pattern 1 |
| src/chain | UnLockChainGeo | MATCHED | pattern 1 |
| src/gv | _AbsRotyGV | MATCHED | pattern 1 |
| src/gv | _ApplyRyGV | MATCHED | pattern 1 |
| ios/cdvd | iosCdvdHandlerRead | MATCHED | `__LINE__` arg `0x322 -> 0x33C` (pattern 4) |

**Step-5 total: 32 named, 16 additionally MATCHED.**
