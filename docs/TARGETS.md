# Targets

What differs between the targets of this tree. One tree (`ico2/`, `sce/`)
builds every target: its base text is the PAL revision, and where another
target differs the file holds that target's lines inline in
`VERSION_<SLUG>` blocks (`docs/BUILDING.md`, "Targets and version
blocks"); `grep -rn VERSION_JPN ico2`, `grep -rn VERSION_KOR ico2`,
`grep -rn VERSION_CN ico2`, `grep -rn VERSION_NTSC ico2`, `grep -rn
VERSION_AUG6 ico2` and `grep -rn VERSION_JUN26 ico2` list every place. This file
records, per target, where its build differs from PAL's and why; the file or
function named at each line is where to read the detail. A target that joins
later gets its own section here.

## Japanese retail (`jpn`): how the build differs from PAL's

The `VERSION_JPN` blocks hold the Japanese build's differences from the PAL
text. The debug menu's `DISC VER.` line (`debug.c`) dates the Japanese build
`Nov  2 2001 17:26:01` and PAL's `Jan 17 2002 15:37:26`; comments in the
sources call the Japanese one the November build. Each line names
where the difference lives; the comment at that place has the detail.

Ids and numbers:

- Stage animation ids are mostly 4 lower (`stage_SetAnimation` in the stage
  scripts, e.g. `actSt20aInit` 144 for PAL's 148).
- Stage numbers are 2 lower and the game has 104 stages, not 106 (`Main`'s
  start-stage clamp, `debug_SelectStage`, `InitWindMillGeo` 99 for 101).
- Layout ids are 3 lower and layout property ids 23 lower
  (`exec_layout_texture`, `ExecIcoMisc`, `actSt20aBridgeDown`).
- The "no animation" sentinel is 949, not 972 (`item.c`'s
  `entryBreakBgAnimation` and `BreakItemFromOutside`, `objact.c`).
- The boot signs' kanban ids are 2 lower (`kanbanBootMcCheck`).

Timing and video mode. The build is NTSC (`systemStatus` starts at 0 in
`main.c`):

- Where PAL scales by the frame rate, these functions use fixed 30 Hz
  values: `staffRollStart`, `ThrowItem`, `GetChainSlope`, `rootUpdateXZ`,
  six terms of `_getFinalMatrix`, `debug_DrawBar`, `debug_DispBar`,
  `monitorMonitorCamera`. The other frame-rate terms,
  `(60 - systemStatus[0] * 10) / systemStatus[1]`, are as on PAL.
- The reverse in one place: `stage_PlayBgAnimation` and
  `stage_PlayBgAnimationDissolve` use the general frame-rate term where PAL
  multiplies by the constant 1.2075409 in 50 Hz mode.
- PAL's 50 Hz branches are absent here: the movie is 720 x 480 (`Main`,
  `mv_vobuf.h`), `setDispEnv` sizes the display from the picture, and
  `actSt13bConte02` has no extra wait.
- The pad convention is circle to confirm and cross to cancel, where PAL
  uses cross and triangle (`default_item_select`; `actE3TitleChk` waits on
  start or circle).

Records and memory (`docs/HEADERS.md` has the layouts):

- `MotionDef` is 400 bytes with other word and bit orders
  (`motionOrientManager.h`).
- `TexRec` is `char path[48]` (`charFileManager.h`).
- `ActWork` has no `boxDir` and is 16 bytes shorter from 0x530
  (`act-game.h`); `act.c`'s `ActExt` follows it.
- `McProductFile` is 488 bytes (`typedef.h`).
- The heap's root partition starts at 0x780000 (PAL 0x760000) and the stage
  partition is 15695872 bytes (`iosInitialize`).

Code only this build has, or names differently:

- `debug_SnapShot` stores numbered shots and writes one, two-by-two or
  four-by-four joined images; PAL's `gsb_ResetSnap` and `gsb_TakeSnap` are
  absent.
- `kanbanBootMcCheck` checks the memory card and shows the no-card sign
  only: no language, camera or video-mode steps.
- `dispSetTags` draws the decoded picture in two sprite passes.
- The ending's save step is `actEndLogoChk`, its name in the August 6, 2001
  prototype's `TRFILE.TXT`; the step before it, which PAL calls
  `actEndLogoChk`, is `actEndLogoFade` (derived name) (`end.c`).
- `DummyIcoMisc` (derived name) is an empty function after `ExitIcoMisc`
  (`icoMisc.c`).
- `actCommonBox`, `actGirlHand` and `_getFinalMatrix` each have a block
  under a local debug switch that is off, where the PAL listing or the
  August `TRFILE.TXT` has code-less lines; the compiler drops the blocks,
  and their text is derived.
- `gsb_SetVSMatrix` has the field-of-view print of PAL's listing under
  `#ifdef DEBUG`; its format text is derived.
- Absent from this build: Sony's `libscf`, `NonLinearCameraMove`,
  `demoEnd`, `bgaStreamSync` and `bgaFrame`, and `BgAnimation.c`'s
  `bga_GetMotionParticle` and `bga_GetMotionLightning`.

## Korean retail (`kor`): how the build differs from the Japanese one

The Korean build's text is the Japanese one with 24 files changed, so the
Japanese blocks serve it too: `#if defined(VERSION_JPN) ||
defined(VERSION_KOR)` holds the lines both have and `#if !defined(VERSION_JPN)
&& !defined(VERSION_KOR)` PAL's alone. Where the Korean build has PAL's lines
(`cdvd.c`'s media and disc type and background waits, `pad.c`) the block
stays `#ifdef VERSION_JPN`, and where it has lines of its own an
`#ifdef VERSION_KOR` block sits inside the Japanese arm, or beside PAL's
text where the Japanese build has PAL's.

The debug menu's `DISC VER.` line (`debug.c`) dates the Korean build
`Jan  9 2002 19:03:40`, between the Japanese build's `Nov  2 2001 17:26:01`
and PAL's `Jan 17 2002 15:37:26`; the version string in `gamesys.c` reads
`10/23/01 17:47:13` (Japanese `10/23/01 02:02:43`); the game was released
in Korea in February 2002. The Korean build is the
Japanese program in nearly every function: of the 5727 functions the census
(`tools/correlate_elf.py`) pairs with the Japanese build's, 5679 have equal
bodies; the others are the functions named below, and a few SDK functions
the census pairs by position across `tlbtrap.s` and `crt0.s`, whose objects
are the Japanese ones. Everything not named here is as in the Japanese
build, including every difference the section above lists for it
against PAL (stage and animation ids, NTSC timing, the records, the memory
map).

Ids and numbers:

- The disc is `SCPS_560.01` (`cdvd.c`) and the memory card directory
  `BISCPS-56001ico` (`mcard.c`); the staff roll's copyright line reads 2002
  (the generated `staffroll_dat`).
- The layout property table, `tex-property`, has 406 rows for the Japanese
  412 and PAL's 436: six of the Japanese rows 2 to 12 are absent, so the
  property ids the code names are 3 to 6 lower than the Japanese ones, 6
  lower from the Japanese 13 on (`layout_action.c` throughout,
  `default_item_select`'s range test, `kanbanBootMcCheck`'s item 5 for 11,
  `jimakuDisp`'s 404 and 405 for 410 and 411). `texture-layout` keeps 76
  rows with its property ranges and default items moved the same way.
- `jimakuMgrNext`'s assertion line is 658 (Japanese 655, PAL 688).
- `cdvd.c` and `pad.c` carry PAL's assertion and allocation line numbers.

Timing and video mode. The build is NTSC like the Japanese one
(`SYSTEM.CNF` reads `VER = 1.00`, `VMODE = NTSC`; `main.c` is the
Japanese file). The five constant-address VU overlays are zero-filled, as
on PAL, where the Japanese disc has 0x6E (`config/link_order.kor.txt`
carries no `overlay-fill` token).

Media and records:

- The disc is a DVD, and `cdvd.c` is PAL's: media mode 2 and disc type 20,
  `SCECdPS2DVD` (the Japanese CD build has 1 and 18, `SCECdPS2CD`), and
  the background reads wait on `sceCdStatus` only for CD media.
- `iosCdvdMgrSearchFile` moves the start of `\DFDATAS\DATA.DF;1` 153600
  sectors (300 MB) on: on the Korean disc the archive's header lies that
  far into the file. Neither the Japanese nor the PAL build has this code,
  but PAL's listing has seven code-less lines at that place (`cdvd.c`
  789-795), and its assertion and allocation lines after it carry the
  numbers they have here, so the block is in PAL's source too, compiled out
  there.
- `iosPadDevReadFunc` prints the pad state on a failed read and drops the
  pad only when the state is 0, as PAL's does.
- The records are the Japanese ones (`docs/HEADERS.md`).

Code only this build has:

- `actBossCtrlStart` and `InitBossCtrlGeo` (`itou_boss.c`) print the
  generator count and the capsule count with `printf`, where the Japanese
  and PAL builds call `debug_StdPrintfDummy`.
- `actE3Warning` (`e3.c`) does not set `GlobalStageSetting.viewScale` to
  150 before its fade-in, as the Japanese build's does (PAL's function
  changes stage instead).

Link order. `puddle.c`, `waterDot.c` and `windmill.c` link in PAL's places
(the Japanese link puts them after `mv_vibuf.c`), and the unmapped
`hintTable` run lies between `game-param` and `motion-orient` as in PAL
(the Japanese link has it first in its `.data` run);
`config/link_order.kor.txt` and `config/data_members.kor.txt` say how each
place was measured. As in the Japanese link, `libscf` is absent and
`texture-path` is in `.rodata`.

## Asian retail (`cn`): how the build differs from the Korean and Japanese ones

The debug menu's `DISC VER.` line (`debug.c`) dates the Asian build
`Nov  2 2001 19:35:51`, about two hours after the Japanese build's
`Nov  2 2001 17:26:01` and before the Korean build's `Jan  9 2002
19:03:40`; the version string in `gamesys.c` reads `10/23/01 17:47:13`, the
Korean build's (Japanese `10/23/01 02:02:43`). The Asian build is the Korean
program in nearly every function: of the 5727 functions the census
(`tools/correlate_elf.py`) pairs with the Korean build's, 5693 have equal
bodies, and of the 34 others 33 equal the Japanese build's twin (named
below); the last is the census's pairing across `tlbtrap.s`, whose 64-byte
alignment fill is 16 bytes shorter here, and its object is the Korean one.
Against the Japanese build 5712 of 5727 are equal; the 15 others are the
Korean functions named below and the same `tlbtrap.s` pairing. No function
equals only a PAL, USA or prototype twin. Everything not named here is as
in the Korean build, including every difference the Korean section above
lists against the Japanese build that is not undone below. In the shared
files the Asian build is named beside the Korean one in each version
condition, takes the Japanese arm where it has the Japanese lines and the
Korean build its own, and keeps its own lines in `#ifdef VERSION_CN` blocks
inside the Korean arm (`docs/BUILDING.md`).

Ids and numbers:

- The disc is `SCPS_550.01` (`cdvd.c`) and the memory card directory
  `BISCPS-55001ico` (`mcard.c`); the staff roll's copyright line reads 2001,
  as in the Japanese build (the generated `staffroll_dat`).
- The layout property table, `tex-property`, has the Japanese build's 412
  rows (Korean 406, PAL 436), so the property ids the code names are the
  Japanese ones (`layout_action.c` throughout, `default_item_select`'s range
  test, `kanbanBootMcCheck`'s item 11, `jimakuDisp`'s 410 and 411,
  `lt_property_visible` in `layout_texture.c`). `texture-layout` is the
  Japanese member.
- `jimakuMgrNext`'s assertion line is 658, the Korean one (Japanese 655).
- `pad.c` has the Japanese lines: its assertion lines are 465, 550 and 566
  (Korean and PAL 468, 553, 569), and `iosPadDevReadFunc` drops the pad on
  any failed read without printing its state.

Timing and video mode. The build is NTSC like the Japanese and Korean ones
(`SYSTEM.CNF` reads `VER = 1.02`, `VMODE = NTSC`). The five
constant-address VU overlays are zero-filled, as on the Korean disc and
PAL's, where the Japanese disc has 0x6E (`config/link_order.cn.txt` carries
no `overlay-fill` token).

Media and records:

- The disc is a DVD, and `cdvd.c` has the Korean lines, PAL's media mode 2
  and disc type 20, `SCECdPS2DVD`, with the boot file name changed.
- `iosCdvdMgrSearchFile` moves the start of `\DFDATAS\DATA.DF;1` 153600
  sectors on, as the Korean build's does; the census pairs it with the
  Korean function, equal. On the Asian disc, as on the Korean one, the
  archive header that opens `DATA.DF` on the Japanese disc lies 153600
  sectors into the file.
- The records are the Japanese ones (`docs/HEADERS.md`); the data members
  are the Korean ones but for `tex-property`, `texture-layout` and the
  `.rodata` pool of `staffroll_dat`, which hold the Japanese bytes
  (`config/data_members.cn.txt`).

Code only this build has: none. Against the Japanese build it keeps two
Korean functions: `actBossCtrlStart` and `InitBossCtrlGeo` (`itou_boss.c`)
print with `printf`, and `actE3Warning` (`e3.c`) does not set
`GlobalStageSetting.viewScale`.

Link order. The Korean link's: `puddle.c`, `waterDot.c` and `windmill.c`
in PAL's places, the unmapped `hintTable` run between `game-param` and
`motion-orient`, no `libscf`, `texture-path` in `.rodata`
(`config/link_order.cn.txt`, `config/data_members.cn.txt`). The objects
move by the sizes alone: `.text` is 64 bytes shorter than the Korean
build's (48 in `pad.c`, 16 of `tlbtrap.s`'s alignment fill), and `.data`
is 0x2C0 bytes longer, the size of the Japanese `.data`.

## USA retail (`ntsc`): how the build differs from PAL's

The `VERSION_NTSC` blocks hold the USA build's differences from the PAL
text. The USA build is the earliest of the four retail links: the debug
menu's `DISC VER.` line (`debug.c`) dates it `Aug 20 2001 22:01:44`, the
Japanese build `Nov  2 2001`, the Korean `Jan  9 2002` and PAL's
`Jan 17 2002`, and the version string in `gamesys.c` reads `08/18/01
22:22:20`. Its text is PAL's with 189 files changed, many of them in whole
functions: 1888 blocks name it, 1476 `#ifdef VERSION_NTSC` and 321 `#ifndef
VERSION_NTSC` against PAL's lines (132 of them nested in the PAL arm of a
Japanese block), 65 Japanese conditions it shares (`#if defined(VERSION_JPN)
|| defined(VERSION_KOR) || defined(VERSION_NTSC)`) and 26 PAL-only
conditions it also lacks (`#if !defined(VERSION_JPN) &&
!defined(VERSION_KOR) && !defined(VERSION_NTSC)`). Where a comment names
PAL's value only, the USA build's is the one in its arm. The branch `ntsc`
is the single-target tree this was joined from (at `8c99cc75a`,
`ntsc-v1.0.0`; current release `ntsc-v1.0.1`, `67c876a25`), and its
`docs/README.md` lists the same differences.

Disc and video mode:

- `SYSTEM.CNF` reads `VER = 1.00`, `VMODE = NTSC`. The build is NTSC like
  the Japanese and Korean ones: `systemStatus` starts at 0 (`main.c`), the
  movie is 720 x 480 (`Main`, `mv_vobuf.h`) and `setDispEnv` sizes the
  display from the picture (`mv_disp.c` shares the Japanese conditions
  there).
- The disc is `SCUS_971.13` (`cdvd.c`) and the memory card directory
  `BASCUS-97113ico` (`mcard.c`); the product file has no `controlType`,
  `cameraMove` or `palMode`, and the game block is one 25596-byte write
  with no `optionScreenMode` and `girlControlMode` words after it
  (`gameblock_write`, `gameblock_read`). `IosMcPreviewInfo` has 4 words
  (PAL 6).
- The five VU1 programs' constant-address overlays hold the byte 0x6E, as
  on the Japanese disc: `overlay-fill=110` on each `.dsm` line of
  `config/link_order.ntsc.txt`. The `.dsm` headers name the programs' USA
  addresses.

Ids and numbers:

- Stage animation, layout, mail and global-flag ids are lower throughout the
  stage scripts (`st22a.c`: the lightning animations are 684 and 685 for
  PAL's 758 and 759 and the Japanese 754 and 755, the intro mail 397 and 396
  for 430 and 429, the layout 50 for 54, the flag 294 for 323).
- `charFileName.h`'s `MAX_CHARS` is 1582 (PAL 1637, JPN and KOR 1621).
- The debug-option table has 69 records (PAL 76) (`debug.c`).
- The heap's root partition starts at 0x780000, as in the Japanese build
  (PAL 0x760000) (`iosInitialize`).
- The assertion and allocation line numbers are the fourth argument of
  every `LN(...)`: the USA build's own at the 97 sites it compiles
  (`FileManager.c` 312 for PAL's 349 and the Japanese 331, `mv_defs.h` 42
  and 43 like JPN and KOR, `flag.c` 31, 39, 46, 65 and 77 for PAL's 87, 95,
  102, 132 and 145), PAL's at a site in an arm it does not compile.

Data and records (`docs/HEADERS.md` has the layouts):

- The link has 71 data-only runs (PAL and KOR 73): PAL's hint table and
  subtitle file names are not in it, and no code here reads either. Most
  tables hold fewer rows, and eight record types have another layout; each
  row of `config/data_members.ntsc.txt` says how its member compares with
  PAL's. One of the runs, `enemy-def` (`EnemyDef`, 0x14 bytes here), is
  committed source, `ico2/sugipon/src/enemyKind.c` (`docs/LEGAL.md`), so
  that file lists 70.
- `Act` has `actMode` at 0x30 and `env` at 0x4A0 (PAL 0x34 and 0x4B0);
  `Sub15C` has `motionBuf` at 0x78C (PAL 0x7B4) and its node records at
  0x840 (PAL 0x870); `ActWork` has no `boxDir` (`wayReq` 0x4B0,
  `viewState` 0x730, `intrReq` 0x7E0; PAL 0x580, 0x800, 0x8B0); `MotionDef`
  is 0x190 bytes (PAL 0x194); `TexRec` is `char path[32]`, 0x20 bytes;
  `PObjMdl` is 0x10C bytes with a model path and a shadow model path before
  the skeleton path (PAL 0x8C); `McProductFile` is 0x18C bytes (PAL 0x1F0);
  `StageSetting` ends at `pad124` (PAL's target colours, grain scale, camera
  limits and anti levels from 0x130 are not in it); `VoTag` and `VoData`
  are sized for the 720 x 480 picture.
- `typedef.h`'s `GOBJ_SUB` reads the 0x15C word through its `IntFloat`
  view in the USA arm and as `*(int *)` in the others. Both compile to
  their targets' bytes; the branch measured the union view as the same
  code for every reader of its tree (the comment at the macro), and the
  join keeps each target's spelling rather than re-measure the other
  three.

Code only this build has, or lacks:

- Absent: Sony's `libscf`; `sugipon`'s `puddle.c`, `waterDot.c` and
  `windmill.c`; the hint system (`Hint_Init`, `MakeHintSaveInfo`,
  `ReadHintSaveInfo`, `FinishHint`, `actGirlHintVoice`); `libcdvd`'s
  `sceCdReadClock` (`libcdvd_267388.c`); `SetFlag4PointFixID` and the
  fixed four-point flag, `InitFlagGeo`'s cloth type 4 (`flag.c`); and many
  smaller functions of the stage scripts and the action layer.
- Only here, among others: `actBoyItem`, `afterCommonItem`,
  `actSt17bIntro`, `actSt47aSekizo3` and `actSt47aSekizo4`, which the
  August 6, 2001 prototype's `TRFILE.TXT` and `MAIN.MAP` name and PAL's
  `TRFILE.TXT` does not, and `bga_updateMotionFrame` (`BgAnimation.c`, a
  derived name).
- `subGirlControl` (`girl_act.c`): the girl's slow-walk states ran a debug
  display that every retail build compiles out. The ROM fixes its strings,
  their order, the number of calls to body-less helpers and the size of its
  locals, but not the statements themselves; the USA arm's block is an
  educated guess, marked in the source as a draft with unverified ordering.

Link order. The USA disc ships no map, so `config/link_order.ntsc.txt` is
PAL's order carried over by the function census (`tools/correlate_elf.py`),
each departure explained on its line; the USA link has 539 objects (PAL
547). As in the Japanese and Korean links, `libscf` is absent.

## Aug-6-2001 prototype (`aug6`): how the build differs from PAL's

The `VERSION_AUG6` blocks hold the August 6, 2001 prototype's differences
from the PAL text. The prototype is the oldest build in this tree, two weeks
before the USA retail link: the debug menu's `DISC VER.` line (`debug.c`)
dates it `Aug  7 2001 15:03:20` and the version string in `gamesys.c` reads
`08/07/01 14:51:53`. Its text is PAL's with 265 files changed, most of them
in whole functions and many in whole files (a file whose functions the
prototype has in another order holds each text whole): 4534 blocks name it,
in 254 files. 3196 `#ifdef VERSION_AUG6` and 327 `#ifndef VERSION_AUG6`
hold its own lines against PAL's (1441 at the top level, 2833 inside the arm
of a Japanese or USA block, 259 inside two, 1 inside three). Where the USA
build already differs from PAL and the prototype has the USA lines, the USA
condition names it: 626 `#if defined(VERSION_NTSC) || defined(VERSION_AUG6)`
and 260 `#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)`, the
prototype's remaining differences nested inside the shared arm. 59 `#if
defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) ||
defined(VERSION_AUG6)`, 58 `#if defined(VERSION_JPN) || defined(VERSION_KOR)
|| defined(VERSION_AUG6)` and one `#if defined(VERSION_KOR) ||
defined(VERSION_AUG6)` name it where it has the Japanese lines, 7 negative
Japanese conditions where it lacks them too. The 20 PAL-only blocks it also
lacks keep their three-name condition (`#if !defined(VERSION_JPN) &&
!defined(VERSION_KOR) && !defined(VERSION_NTSC)`) with `#ifndef
VERSION_AUG6` nested inside: the four-name line would pass the column limit,
and clang-format would break the directive, which `tools/check_targets.py`
does not read. Each block was placed by resolving its place for each earlier
target and comparing with the branch's text, never by assumption. Where a
comment names PAL's value only, the prototype's is the one in its arm. The
branch `aug6` is the single-target tree this was joined from (at
`c8e730628`, `aug6-v1.0.0`; current release `aug6-v1.0.1`, `ba93991ed`),
and its `docs/README.md` lists the same differences.

Disc and video mode:

- The disc carries no product code; `SYSTEM.CNF` reads `VER = 1.00`,
  `VMODE = NTSC`. The build is NTSC like the USA, Japanese and Korean ones:
  `systemStatus` starts at 0 (`main.c`) and the movie is 720 x 480 (`Main`,
  `mv_vobuf.h`).
- The boot file is `SCUS_971.13` (`cdvd.c`) and the memory card directory
  `BASCUS-97113ico` (`mcard.c`), as on the USA disc; the game block is one
  25596-byte write and `IosMcPreviewInfo` has 4 words, as there.
- The five VU1 programs' constant-address overlays hold the byte 0x6E, as
  on the Japanese and USA discs: `overlay-fill=110` on each `.dsm` line of
  `config/link_order.aug6.txt`. The `.dsm` headers name the programs'
  prototype addresses.
- The disc ships a `MAIN.MAP` that is the PAL disc's file byte for byte,
  describing a later link, and a `TRFILE.TXT` (`docs/LEGAL.md`); the
  function names of this build come from the PAL listing by the census, and
  from `TRFILE.TXT` for the functions only the prototype has.

Ids and numbers:

- Stage animation, mail and global-flag ids are lower than the USA build's
  throughout the stage scripts (`st22a.c`: the lightning animations are 683
  and 684 for the USA 684 and 685 and PAL's 758 and 759, the intro mail 393
  and 392 for 397 and 396 and 430 and 429, the flags 293 and 294 for the USA
  294 and PAL's 323).
- `charFileName.h`'s `MAX_CHARS` is 1576 (USA 1582, PAL 1637, JPN and KOR
  1621).
- The assertion and allocation line numbers are the fifth argument of every
  `LN(...)`: the prototype's own at the 491 sites where it differs from
  PAL's (`mv_defs.h` 42 and 43, `FileManager.c` 312 for PAL's 349, the
  Japanese 331 and the USA 312, `flag.c` 31, 39, 46, 65 and 77 as the USA
  build), PAL's at the 401 sites in arms it does not compile or where the
  lines agree. 456 sites where the four retail builds share one line, which
  main spelled as a literal (`debug_assert(__FILE__, 598)`,
  `iosMallocDebug(..., __FILE__, 844)`), spell `LN(n, n, n, n, m)` now that
  the prototype's line differs.

Data and records (`docs/HEADERS.md` has the layouts):

- The link has the 70 data-only members PAL's has and none of PAL's three
  unmapped runs (the hint table, `motSyncPairs` and the subtitle file names
  are not in it; USA 71 runs, PAL and KOR 73). Most tables hold fewer rows,
  and ten record types have another layout: eight are the USA build's
  (`ParallelMotionRow`, `LtProperty`, `ItemBreakRec`, `PObjMdl`,
  `MotionDef`, `EnemyDef`, `LayoutClothDef`, `TexRec`) and two the
  prototype's own (`StgPre`, 0x190 bytes with its fields after 0x15B in
  another order and no `ledgeRange`; `ActModeRec`, PAL's 0x50 bytes with
  the words at 0x44 and 0x48 exchanged and the flag bits at 0x4C
  renumbered). Each row of `config/data_members.aug6.txt` and the header of
  `config/data_schema.aug6.txt` say how its member compares with PAL's.
  `enemy-def` (`EnemyDef`) is committed source,
  `ico2/sugipon/src/enemyKind.c` (`docs/LEGAL.md`), so that file lists 69
  runs.
- The engine's records are 16 bytes shorter at the display object: `Act`
  has `actMode` at 0x30 (PAL 0x34; as the USA); `Sub15C` has `motionBuf` at
  0x77C and its node records at 0x830 (PAL 0x7B4 and 0x870, USA 0x78C and
  0x840); `MotRoot`'s motion-control block is at +0x460 (PAL 0x470), so its
  fields from `savePos` on sit 0x10 lower and `flag330` and `flag334` are
  read at 0x320 and 0x324; `ActWork` has `wayReq` at 0x490, `viewState` at
  0x710 and `intrReq` at 0x7C0 (USA 0x4B0, 0x730, 0x7E0; PAL 0x580, 0x800,
  0x8B0). The comment at each field gives its offset and the reader that
  pins it.

Code only this build has, or lacks:

- Absent, as in the USA build: Sony's `libscf`; `sugipon`'s `puddle.c`,
  `waterDot.c` and `windmill.c`; the hint system; `libcdvd`'s
  `sceCdReadClock` (`libcdvd_267388.c`); `SetFlag4PointFixID` and
  `InitFlagGeo`'s cloth type 4 (`flag.c`); and many smaller functions of
  the stage scripts and the action layer that were added after August 6.
- Only here: the functions the prototype's `TRFILE.TXT` names and no retail
  listing does; each carries its `TRFILE.TXT` name or a `/* derived name */`
  (`git grep -n 'derived name'` inside the `VERSION_AUG6` blocks lists the
  derived ones).
- `subGirlControl` (`girl_act.c`): the girl's slow-walk states ran a debug
  display that every retail build compiles out, and in this build the ROM
  fixes its strings, their order, 139 calls to body-less helpers and the
  size of its locals, not the statements themselves; the prototype arm's
  block is an educated guess, marked in the source as a draft with
  unverified ordering, as the USA arm's is.

Names. A function or object the branch named otherwise than `main` names
the same thing takes `main`'s name in the joined tree, since the bytes do
not care: `handoff_heroin` and `actE3St13cSekizoEvent` (the prototype's
`TRFILE.TXT` spells them `hand_heroin` and `actSt13cSekizoEvent`, noted at
the definitions), `IsNeedGeneratorHard` (`generator.c`), `logoIcoMiscLock`,
`continueIcoMiscLock` and `newGameIcoMiscLock` (`layout_action.c`, which the
prototype sets from `GlobalTimer`), `demoClothMeshF20`, `clothMeshF20` and
`clothHangF20` (`girl.c`; the prototype reads the record at 0x1C), the
`MotRoot` fields `flag330` and `flag334` (0x320 and 0x324 here), the
`ReviveSub` and `StoneSub` field `f14`, `st13c.c`'s `st13c_reserved`, and
the locals `dy` (`girl_act.c`) and `f8` (`camera-ico2.c`). `AttackCenter`,
`scpAdpcmFadeClose` and `scpAdpcmCloseChk`, which the branch's notes list
as `TRFILE.TXT` spellings of `_AttackCenter`, `scpAdpcmFadeCloseFunc` and
`scpAdpcmCloseChkFunc`, are the prototype calling the one function where PAL
has two, and keep their names. A name a target's bytes pin stays per arm:
`D_002E3508` (`kanban.c`, `layout_texture.c`), the label the build defines
at that address of `texProperty` (`D_0030D014` on PAL); `GirlForceFieldGeo`
and `GirlForceFieldDL`, since the body sits in the Geo slot of the
prototype's object-kind table and in the DL slot of PAL's; and
`bga_SetCameraMatrix` (`BgAnimation.c`), whose body is not
`bga_checkCameraDistance`'s. Two reconstruction differences in typing stay
per arm too (`motionOrientManager.c`'s `rotateNodes` taking `StreamElem *`,
`st13c.c` holding the demo thread as `GProc *`).

Link order. The prototype's `MAIN.MAP` describes PAL's link, so
`config/link_order.aug6.txt` is PAL's order carried over by the function
census (`tools/correlate_elf.py`) as the USA build's is, each departure
explained on its line; the prototype's link has 536 objects (USA 539, PAL
547). `libscf` is absent, as in every link but PAL's.

## Jun-26-2001 demo (`jun26`): how the build differs from PAL's

The `VERSION_JUN26` blocks hold the June 26, 2001 demo's differences from
the PAL text. The demo is the oldest build in this tree, six weeks before
the August 6 prototype: its ELF carries the build stamp `Jun 26 2001`
`20:01:21`, and the version string in `gamesys.c` reads `06/26/01
20:00:06` (the prototype's `08/07/01 14:51:53`). It is one game on the
Official U.S. PlayStation Magazine demo disc 49 (SCUS-97158, a DVD): the
disc's `SYSTEM.CNF` (`VER = 1.00`, `VMODE = NTSC`) boots the magazine's
menu, `SCUS_971.58`, which starts the demo from its own directory, and the
build reads the demo's own ELF, `CUS97113/SCPS_000.00` (the `boot` key of
`tools/ico_version.py`'s row). Its text is PAL's with 315 files changed, three
VU program texts and one source of its own, most of the changes in whole
functions and many in whole files; where the prototype or the USA build already differs from PAL
and the demo has their lines, their condition names it: 5187 blocks name it,
in 305 files. 2976 `#ifdef VERSION_JUN26` and 476 `#ifndef VERSION_JUN26`
hold its own lines (2096 blocks naming it at the top level, 1586 inside one
arm, 1416 inside two, 89 inside three); 909 `#if defined(VERSION_AUG6) ||
defined(VERSION_JUN26)`, 199 `#if !defined(VERSION_AUG6) &&
!defined(VERSION_JUN26)`, 368 `#if defined(VERSION_NTSC) ||
defined(VERSION_AUG6) || defined(VERSION_JUN26)` and 190 `#if
!defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)`
are prototype or USA blocks whose lines the demo has or lacks too, with its
remaining differences nested inside the shared arm; 16 `#if
defined(VERSION_NTSC) || defined(VERSION_JUN26)` and 12 `#if
!defined(VERSION_NTSC) && !defined(VERSION_JUN26)` name it beside the USA
build alone; 36 `#if defined(VERSION_JPN) || defined(VERSION_KOR) ||
defined(VERSION_AUG6) || defined(VERSION_JUN26)`, one `#if
defined(VERSION_KOR) || defined(VERSION_AUG6) || defined(VERSION_JUN26)`,
one `#if defined(VERSION_JPN) || defined(VERSION_KOR) ||
defined(VERSION_JUN26)`, one `#if defined(VERSION_JPN) ||
defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_JUN26)` and
2 `#if !defined(VERSION_JPN) && !defined(VERSION_KOR) &&
!defined(VERSION_JUN26)` name it where it has or lacks the Japanese lines.
Six PAL-only blocks the demo also lacks keep their three-name condition
(`#if !defined(VERSION_JPN) && !defined(VERSION_KOR) &&
!defined(VERSION_NTSC)`) with the demo's exclusion nested inside (`#if
!defined(VERSION_AUG6) && !defined(VERSION_JUN26)` where the prototype lacks
them too), and the one place where the demo has the lines all four later
builds share (`e3.c`) holds them in a block of its own beside the four-name
condition: a five-name line would pass the column limit, and clang-format
would break the directive, which `tools/check_targets.py` does not read.
Each block was placed by resolving its place for each earlier target and
comparing with the branch's text, never by assumption. Where a comment names
PAL's value only, the demo's is the one in its arm. The branch `jun26`
is the single-target tree this was joined from (at `230819536`,
`jun26-v1.0.0`; current release `jun26-v1.0.1`, `654630aa7`), and its
`docs/README.md` lists the same differences.

Disc and video mode:

- The build is NTSC like the prototype and the USA, Japanese and Korean
  ones: `systemStatus` starts at 0 (`main.c`) and the movie is 720 x 480
  (`Main`, `mv_vobuf.h`).
- The demo is started by the magazine's menu and hands control back to it.
  `main` (`main.c`) reads the menu's settings (language, aspect, play mode,
  the idle and total timeouts, the media type) through `demoDisc.c`'s
  `sceDemoStart`, runs the game, and after the boot thread is woken shuts
  the game down and calls `sceDemoEnd`, which reloads the menu's ELF with
  the arguments it was given (the prototype's map links the pair as
  `libscedemo.a(libscedemo.o)`). `ico2/common/src/demoDisc.c` is the one
  source only this target has; `config/link_order.jun26.txt` alone lists
  it, after `sce/libsndn2/sound.c`.
- The exits (`main.c`): an idle countdown of four minutes that any button or
  stick resets (`sampleModeNoContTimeOutMain`), `sampleModeDemoEnd` and
  `sampleModeDemoEndTimeOut` (to stages 101 and 102; `layout_action.c` and
  `script.c` call the second), and `demoEnd`, which wakes the boot thread
  (`e3.c` calls it; its static that PAL names `demoEnd` is `demoEndFlag` in
  the demo's arm, since the function's name is taken there).
- The five VU1 programs' constant-address overlays hold the byte 0x6E, as
  on the Japanese, USA and prototype discs: `overlay-fill=110` on each
  `.dsm` line of `config/link_order.jun26.txt`. Four programs (cluster,
  mesh, normal_c and normal_l) are this build's own instruction streams,
  held in `VERSION_JUN26` blocks of the shared `.vsm`, which cpp reads with
  the target and `LN` defined; particle is the same program in every build.
  dvp-as names each continuation overlay after the `.vsm` line where it
  starts, taken from cpp's line markers, and the base ELF carries the names,
  so those lines are a datum of the build: mesh's second overlay starts at
  line 327 of the demo's text and 323 of the later builds', normal_c's and
  normal_l's at 244 and 243 in both but at other instructions, and their
  include-side continuations at other lines of `scissorcommcut.h` (the
  include's own lines, by instruction count). A `#line LN(...) ""` before
  each such instruction gives each target its line (`#line 244 ""` inside a
  block's arm); cluster's difference lies after its boundary (line 359 in
  both) and needs none. The `.dsm` headers name the programs' demo
  addresses.

Ids and numbers:

- Stage animation, mail and global-flag ids are lower than the prototype's
  where the stage scripts differ (`st03t.c`'s `wayOnChk_mes` mails are 377
  and 376 for the prototype's 393 and 392); `charFileName.h`'s `MAX_CHARS` is 1500
  (prototype 1576, USA 1582, PAL 1637, JPN and KOR 1621), and
  `ModelDataID_NUMBER`, 1474, bounds the model table (`charFileManager.c`).
- The assertion and allocation line numbers are the sixth argument of every
  `LN(...)`: the demo's own at the 530 sites where it differs from PAL's
  (`mv_defs.h` 42 and 43, `FileManager.c` 306 for PAL's 349, the Japanese
  331 and the USA and prototype 312, `flag.c` 31, 39, 46, 65 and 77 as the
  USA build and the prototype), PAL's at the 747 sites in arms it does not
  compile or where the lines agree. 154 sites where main spelled one literal
  for the five earlier targets spell `LN(n, n, n, n, n, m)` now that the
  demo's line differs.

Data and records (`docs/HEADERS.md` has the layouts):

- The link has 120 data-only runs: the 70 archive members PAL's has, in the
  prototype's member order, none of PAL's three unmapped runs (the hint
  table, `motSyncPairs` and the subtitle file names, which no code here
  reads), `mcdata.o`'s save icon record (the `icon.sys` PAL reads from the
  disc) and `EnemyInit.o`'s 49 enemy-set tables of the stage models (PAL
  keeps only its first model's, as C). Many tables hold another number of
  rows (the model paths 1474 records of 0x14C bytes, PAL 1637 of 0x8C);
  each row of `config/data_members.jun26.txt` and the header of
  `config/data_schema.jun26.txt` say how its member compares with PAL's.
  `enemy-def` (`EnemyDef`, 18 rows here) is committed source,
  `ico2/sugipon/src/enemyKind.c` (`docs/LEGAL.md`), so that file lists 119
  runs.
- Records with another layout, each derived from the demo code that reads
  it: `ParallelMotionRow`, `EnemyDef`, `LayoutClothDef`, `TexRec` and
  `ActModeRec` as the prototype has them; `PObjMdl` (0x14C), `LtProperty`
  (0x58), `ItemBreakRec` (0x10), `SeBank` (0x54), `MotionDef` (0x184),
  `StgPre` (0x18C), `StageSetting` (0x130), `MotionStateInfo` (0x1E0), the
  texture slot (`Texture.c`, 0x330), and among the engine's records the
  display object `Sub15C` and its motion control `MotCtrl` (`typedef.h`),
  the packet records `PacHeader` (176 bytes) and `PacLine` (144,
  `Packet.h`), a part's group record `PObjGroup` (60, `DisplayP2O.h`) and
  the box work block (336, `box.c`). The motion-effect row (`EffEntry`,
  `frameDependSequence.h`) has its flags at 0x1C and its node at 0x20
  (PAL's node at 0x1C, flags at 0x20), so `icoMisc.c` reads it through the
  shared record where PAL's reads its own `EffEnt`.

Code only this build has, or lacks:

- Absent: Sony's `libscf` and `libcdvd`'s `sceCdReadClock`
  (`libcdvd_267388.c`), `sceCdBreak` and `sceCdStatus` (`libcdvd.h`
  declares neither for it); `sugipon`'s `puddle.c`, `waterDot.c` and
  `windmill.c`, as in the prototype; `ito`'s `itou_gflag.c` and `sugipon`'s
  `clipCollisionManager.c`, `flyManager.c` and `waySystemManager.c`, whose
  objects would be empty in this link (the prototype's `TRFILE.TXT` lists
  their functions and the census finds none of them in the demo), so
  `config/link_order.jun26.txt` does not list them and their headers stay
  for the other targets; and about 900 functions of PAL's that the census
  finds nowhere in the demo.
- Only here: `demoDisc.c` and the exits (above), and the functions the
  census finds in no other build, named after the prototype's functions
  where a table slot, a caller or a record ties them to one, else with
  names marked `/* derived name */`.
- `subGirlControl` (`girl_act.c`): the girl's slow-walk states ran a debug
  display that every retail build compiles out. The demo shares the
  prototype's arm of the function, its own statements in `VERSION_JUN26`
  blocks inside it; the ROM fixes the display's strings, their order, 143
  calls to body-less helpers (the prototype 139, the USA build 144) and the
  size of its locals, not the statements themselves, so the demo's block is
  an educated guess, marked in the source as a draft with unverified
  ordering, as the prototype's and the USA build's are.

Names. The demo disc ships no map or listing, so the branch's names are the
PAL listing's and the prototype's `TRFILE.TXT`'s carried over by the census,
and derived for the rest. A function or object the branch named otherwise
than `main` names the same thing takes `main`'s name in the joined tree,
since the bytes do not care: `handoff_heroin` and `actE3St13cSekizoEvent`
(the `TRFILE.TXT` spellings `hand_heroin` and `actSt13cSekizoEvent`, as
the prototype's branch had them), `IsNeedGeneratorHard` (`generator.c`),
the `MotRoot` fields `flag330` and `flag334` (`typedef.h`,
`motionOrientManager.h`, `motionManager2.c`, `motMan_getFinalMatrix.c.inc`;
the branch's `dropNode4Turn` and `dropNode6Turn`), `stageAnimObjCount`
(`StageAnimation.c`; `bgaDispNodeCount`), `seRandomPickCount` and
`seRandomPicks` (`frameDependSequence.c`; `randomSEHits` and
`randomSECallCount`; the demo's table has 52 entries, PAL's 50),
`carryOfsOther` (`item.c`; `carryOfs`), and `effectTool.c`'s two words of
`.sdata`: the branch bound the map's `targetMemo` to the saved camera
target (`GObj *`) and named the tool mode `toolMode`, where `main` binds
`targetMemo` to the mode word and names the pointer `savedTarget`; both are
zero-initialised 4-byte words of the member, so the demo takes `main`'s
binding, `effectTool.h` declaring one `int targetMemo` for every target. A
name a target's bytes pin stays per arm: `D_002CC054` (`kanban.c`,
`layout_texture.c`), the label the build defines at that address of
`texProperty` (`D_0030D014` on PAL, `D_002E3508` on the prototype), and
`e3.c`'s `demoEndFlag` (above). Everything else the join's rename check
flagged (`SetDirectRootPosition` for `SetDirectRootPositionNoFitting` and
`ACTSetPositionWithFitting`, `gif_SetGsReg` for `GifPacket.c`'s inline
`setGsReg`, `printf` for `debug_StdPrintfDummy` in `quaternion.c`,
`sceVu0ScaleVectorXYZ` and `sceVu0MulMatrix` for the local copies,
`GetSlerpQuaternion` for `GetSlerpQuaternionNoRegularize`, the record
fields `flags` for `flags2`, `flag0` for `flag1`, `word30` for `open`,
`clstNum` for `nloop` and `id`, `boyRoot` for `girlRoot`, `base` for
`capsule`, `lock_execIcoMisc` for `graphics_ready`, the `pad` fields named
by offset, and the declarations whose types differ) is a different entity
or a different layout on the two trees and stays in the demo's arm.

Link order. The demo's directory ships no map, so `config/link_order.jun26.txt`
is PAL's order carried over by the function census (`tools/correlate_elf.py`)
run against PAL, the prototype and the USA build, each departure explained on
its line; the demo's link has 393 source objects and 120 generated data
members (the prototype 396 and 70, PAL 401 and 73). `libscf` is absent, as
in every link but PAL's.
