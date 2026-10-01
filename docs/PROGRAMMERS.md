# Programmers and subsystems

Who wrote which part of the game, as far as public information shows, and
how that maps onto the `ico2/` directories.

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

The mapping comes from public information: the game's published staff roll
(its ending credits), cross-checked against what each directory contains and
against per-developer asset paths in the ELF (`camdata/<name>.gcm`,
`object/sdf/<name>_test/`). No credit text or other disc data is committed,
only this reading of it.

| dir | programmer (credit) | credited role | corroboration | confidence |
| --- | --- | --- | --- | --- |
| `seki` | Takuya Seki | Tools / Visual Program | GS and drawing code | high |
| `sugipon` | Hajime Sugiyama ("Sugipon") | Draw Engine / YORDA A.I. Program | matrix, motion, geometry and Yorda code | high |
| `omori` | Shotaro Omori | Motion System Program | camera, brains, attack hits | high |
| `ito` | Toshihiro Ito | Scripting | the `itou_*` files carry his name | high |
| `fumi` | Fumiaki Hara (candidate) | System Program | I/O and object system fit the role; the action files less so | low |

Caveats:

- The candidate for `fumi` is Fumiaki Hara, whom MobyGames lists under System
  Program in the PlayStation 2 credits
  (<https://www.mobygames.com/game/5158/ico/credits/ps2/>). It is a plausible
  name match, not proof.
- Raw `strings` hits for "seki" are mostly the Japanese word *seki*, stone
  (`sekizo`, stone statue; `sekika`, petrification), not the name. The
  credit block is the reliable source.

## Shared records

The engine's object records are defined once, in
`ico2/common/include/typedef.h`, and read from every programmer directory:
the game object (`GObj`), its display object (`Sub15C`, reached through
`GOBJ_SUB`) and its action state (`Act`, reached through `GOBJ_ACT`). They
belong to the engine rather than to any one programmer. A few files declare
their own view of one of them, under a comment saying so (`script/src/st04a.c`
for `Act` and `GObj`).
