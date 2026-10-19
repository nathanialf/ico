# Targets

What differs between the Korean build this branch rebuilds and the builds
it was seeded from. The tree is the `jpn` branch's (the Japanese retail
build, SCPS-11003, which is `main`'s PAL tree with the Japanese
differences), with the Korean build's differences written into the same
files: this branch carries one target and no `VERSION_` blocks, as the
`jpn` branch did before it joined `main`. Each line names where the
difference lives; the comment at that place has the detail.

## Korean retail (`kor`): how the build differs

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
build, including every difference `main`'s `docs/TARGETS.md` lists for it
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
