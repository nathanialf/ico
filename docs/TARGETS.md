# Targets

What differs between the Asian build this branch rebuilds and the builds
it was seeded from. The tree is the `kor` branch's (the Korean retail
build, SCPS-56001, itself seeded from the `jpn` branch), with the Asian
build's differences written into the same files: this branch carries one
target and no `VERSION_` blocks, as the `kor` branch did before it joined
`main`. Each line names where the difference lives; the comment at that
place has the detail.

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
in the Korean build, including every difference the `kor` branch's
`docs/TARGETS.md` lists against the Japanese build that is not undone
below.

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
- `pad.c` is the Japanese file: its assertion lines are 465, 550 and 566
  (Korean and PAL 468, 553, 569), and `iosPadDevReadFunc` drops the pad on
  any failed read without printing its state.

Timing and video mode. The build is NTSC like the Japanese and Korean ones
(`SYSTEM.CNF` reads `VER = 1.02`, `VMODE = NTSC`). The five
constant-address VU overlays are zero-filled, as on the Korean disc and
PAL's, where the Japanese disc has 0x6E (`config/link_order.cn.txt` carries
no `overlay-fill` token).

Media and records:

- The disc is a DVD, and `cdvd.c` is the Korean file, PAL's media mode 2
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
