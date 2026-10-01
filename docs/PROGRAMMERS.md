# Programmers and subsystems

Who wrote which part of the game, as far as the game's own staff roll and
its per-developer strings show, and how that maps onto the `ico2/`
directories.

## The directories

The game's source tree is the one the PAL disc's listing (`SRCFILE.TXT`)
records, file by file: `ico2/<dir>/<kind>/<file>`. Five of the eight
top-level directories are named after a programmer; `common` and `script`
are shared, and `vusrc` holds the VU1 microprograms.

| dir | contents |
| --- | --- |
| `seki` | the GS drawing layer: `GsBase`, `GifPacket`, `DmaPacket`, `Packet`, `Primitive`, `Texture`, `Light`, `Shadow`, `ZFog`, `Matrix`, the display lists and fonts |
| `sugipon` | the draw engine and object behaviour: `matrixDrive`, `motionManager`, `geometryManager`, `quaternion`, cloth, rope, wind, particles, Yorda (`girl`), the enemies and the stage objects (box, cage, torch, switch, ...) |
| `omori` | the cameras, the brains (`brain`, `ebrain`), attack hits, enemy control, the chain, the object action mail (`objact`) and the climb headers (`*climb.h`, whose handlers are written in fumi's `boyact.c` and `girl_act.c`) |
| `ito` | the queen and boss scenes (`itou_boss`, `itou_sub`, `itou_gflag`), effects, and the movie player (`mpeg/`, the IPU layer) |
| `fumi` | the action layer (`boyact`, `girl_act`, `commonact`, `enemy_act`, the `act-*` files, the way-point system), the I/O layer (`ios/`: CD, memory card, pad, threads, memory), the object system (`isys/`) and sound (`sound/`) |
| `common` | the main loop, the game system, stage and scene management, debug menus, the staff roll |
| `script` | the per-stage scripts (`st00a` to `st99a`, `op`, `end`, `e3`, `deja`) and the script interpreter |

`ico2/vusrc/` holds the five VU1 microprograms. MAIN.MAP takes their objects
from `ico2000.a`, but the listing has no source rows for them, so the
directory they lived in is not recorded.

## Who the programmer directories belong to

The source for the names is the game's own staff roll: the ending credits'
text in the user's boot ELF (a table of string pointers at `0x004E4610`, read
in table order, each role line followed by its names). Its programmers
section reads:

| credited role | names, in the roll's order |
| --- | --- |
| System Program | Jinji Horagai, Fumiaki Hara |
| Characters&Objects Program | Shotaro Omori, Hajime Sugiyama, Toshihiro Ito |
| Motion System Program | Hajime Sugiyama |
| YORDA A.I. Program | Shotaro Omori, Jinji Horagai |
| Draw Engine Program | Takuya Seki |
| Visual Program | Hajime Sugiyama, Takuya Seki |
| Tools Program | Toshihiro Ito |
| Scripting | Junichi Hosono |

The roll does not say who wrote which directory. Each directory is matched to
a name by the per-developer strings in the same ELF: the camera files
`camdata/seki.gcm`, `camdata/sugiyama.gcm`, `camdata/omori.gcm` and
`camdata/itoh.gcm`, the test directory `object/sdf/sekitest/`, and the
memory-area messages printed by `seki/src/FileManager.c` and
`common/src/debug.c` (`seki area`, `sugi area`, `hara-area`, `oomori area`,
`horagai-area`). No credit text or other disc data is committed, only this
reading of it.

| dir | programmer | evidence in the ELF besides the roll |
| --- | --- | --- |
| `seki` | Takuya Seki | `camdata/seki.gcm`, `object/sdf/sekitest/`, `seki area` |
| `sugipon` | Hajime Sugiyama | `camdata/sugiyama.gcm`, `sugi area` |
| `omori` | Shotaro Omori | `camdata/omori.gcm`, `oomori area` |
| `ito` | Toshihiro Ito | `camdata/itoh.gcm`, the `itou_*` file and stage names |
| `fumi` | Fumiaki Hara (candidate) | `hara-area`; the directory name matches his given name only |

Caveats:

- `fumi` to Fumiaki Hara is a name match, not proof. Jinji Horagai, credited
  beside him under System Program, has a memory area (`horagai-area`) but no
  directory in the listing.
- The roll names two other Sekis (Yoshiyuki and Masamichi), and most `seki`
  strings in the ELF are the Japanese word *seki*, stone (`sekizo`, stone
  statue; `sekika`, petrification), not the name.

## Shared records

The engine's object records are defined once, in
`ico2/common/include/typedef.h`, and read from every programmer directory:
the game object (`GObj`), its display object (`Sub15C`, reached through
`GOBJ_SUB`) and its action state (`Act`, reached through `GOBJ_ACT`). They
belong to the engine rather than to any one programmer. A few files declare
their own view of one of them, under a comment saying so (`script/src/st04a.c`
for `Act` and `GObj`).
