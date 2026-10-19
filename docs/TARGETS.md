# Targets

What differs between the targets of this tree. One tree (`ico2/`, `sce/`)
builds every target: its base text is the PAL revision, and where another
target differs the file holds that target's lines inline in
`VERSION_<SLUG>` blocks (`docs/BUILDING.md`, "Targets and version
blocks"); `grep -rn VERSION_JPN ico2` and `grep -rn VERSION_KOR ico2` list
every place. This file
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
