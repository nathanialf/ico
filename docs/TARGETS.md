# Targets

What differs between the targets of this tree. The shared tree (`ico2/`,
`sce/`) is the PAL revision; each other target is built from it with the files
of its overlay, `targets/<slug>/`, in place of the ones they replace
(`docs/BUILDING.md`, "Targets, overlays and the merged view"). This file
records, per target, where its build differs from PAL's and why; the file or
function named at each line is where to read the detail. A target that joins
later gets its own section here.

## Japanese retail (`jpn`): how the build differs from PAL's

`targets/jpn/` holds the Japanese build's differences from the shared (PAL) tree. The
debug menu's `DISC VER.` line (`debug.c`) dates the Japanese build
`Nov  2 2001 17:26:01` and PAL's `Jan 17 2002 15:37:26`; comments in the
sources call them the November and the January build. Each line names
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
