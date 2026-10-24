# Targets

What differs between the targets of this tree. One tree (`ico2/`, `sce/`)
builds every target: its base text is the PAL revision, and where another
target differs the file holds that target's lines inline in
`VERSION_<SLUG>` blocks (`docs/BUILDING.md`, "Targets and version
blocks"); `grep -rn VERSION_JPN ico2`, `grep -rn VERSION_KOR ico2` and
`grep -rn VERSION_NTSC ico2` list every place. This file
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
(frozen at `8c99cc75a`, `ntsc-v1.0.0`) is the single-target tree this was
joined from, and its `docs/README.md` lists the same differences.

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
  PAL's.
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
