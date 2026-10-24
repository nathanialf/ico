# Headers

Which headers under `ico2/` the disc attests, which source files are compiled
as part of another, and where every other declaration lives.

The evidence is the PAL disc's listing (`SRCFILE.TXT`, an
`objdump -dl` of the game with a source path and line on every instruction)
and its `MAIN.MAP`; both are copied into `baserom/pal/` by
`tools/extract_elf.sh` and are never committed (`docs/LEGAL.md`). The
Japanese, Korean and USA discs ship neither: the headers are the PAL tree's,
with the other builds' declarations inline where they differ (per-target
declarations, below). The listing
contains no source text. A header shows up in it only when code from the
header was compiled into a caller: a header that only declares leaves no
rows at all.

## Headers the disc attests

Eleven headers under `ico2/` are known from the disc. Each sits at the path
the listing records for it, under the programmer directory that owns it.

| header | evidence | what it holds |
| --- | --- | --- |
| `ico2/sugipon/include/sugiCommon.h` | listing rows in 84 caller functions in six directories (`sugipon` 63, `fumi` 11, `ito` 5, `common` 3, `omori` 1, `script` 1) | nine `static` inline helpers: random numbers, plane distance, squared distances, a byte checksum |
| `ico2/ito/include/itou_common.h` | listing rows in five `ito` functions (`DrawLightning2`, `GatherEffect_Proc`, `QueenBarrierGeo`, `subBirdBrainMain`, `vector_angle_degree`) | degree and radian conversion |
| `ico2/ito/include/mv_defs.h` | inlined expansions in the movie player, and three out-of-line copies of `Free` | address masks and a zeroing allocator; `Free`, its release, is defined in each of `mv_vibuf.c`, `mv_videodec.c` and `mv_vobuf.c` |
| `ico2/common/include/typedef.h` | one helper at line 74, inlined twice into `avoid_obstacle2` | the engine's shared object records (`GObj`, `Sub15C`, `Act`, ...) and the game's VU0 asm templates |
| `ico2/omori/include/{b50,b100,b200}climb.h` | whole functions, emitted into `fumi/src/boyact.c`'s object | the boy's climb handlers |
| `ico2/omori/include/{g50,g100,g200}climb.h` | whole functions, emitted into `fumi/src/girl_act.c`'s object | the girl's climb handlers |
| `ico2/common/include/charFileName.h` | no listing rows; the ROM's message at `0x00619370` (Japanese build `0x00612710`, Korean `0x00612520`, USA `0x00612A30`) names `commmon/include/charFileName.h` (the typo is the message's) | `MAX_CHARS` (1637; 1621 in the Japanese and Korean builds, 1582 in the USA one), the size of `charFileManager.c`'s character-file table and the bound its four id checks compare against |

Things a reader of these files should know:

- **Helper names.** An inlined helper leaves no symbol, so its name is the
  developer's only when the listing shows it emitted out of line somewhere.
  That holds for `Free` and for the eighteen climb functions
  (`after*Hand*`, `act*Hand*`, `mot*Hand*`). Every other helper name is a
  descriptive one, marked as described under "Derived names" below.
- **Two pairs of identical helpers.** The listing cites line 55 and line 65
  of the developer's `sugiCommon.h` for the same instructions (the
  `* 2.0f - 1.0f` of a -1..+1 random number), and lines 85 and 87 and line 97
  for the same VU0 squared distance. Both of each pair are written out:
  `random_signed` (line 55) and `random_signed_b` (line 65), and
  `distance_squared` (lines 85 and 87) and `distance_squared_b` (line 97).
  The tracked file's line numbers are not the listing's.
- **Line numbers that are part of the bytes.** `mv_defs.h`'s allocator bakes
  `__FILE__` and `__LINE__` into the ROM (`"../ito/include/mv_defs.h"`, lines
  43 and 44; 42 and 43 in the Japanese, Korean and USA builds), and `typedef.h`'s helper must
  stay on line 74. Neither file may be reflowed.
- **The climb headers hold no bodies.** ee-gcc 2.9 emits ordinary functions
  in parse order and `inline` ones at the end of the file. In each includer
  the `mot*` function sits in the parse-order run and the `act*` and
  `after*` functions in the end-of-file run, an order one `#include` cannot
  give. The eighteen functions are written in `boyact.c` and `girl_act.c`
  at the point the headers would be included, under a comment naming the
  three headers, and each header names the functions written in its place.

## Code includes (`.c.inc`)

The listing also records source files compiled as part of another file.
Each is a `.c.inc` beside its includer:

| file | included by |
| --- | --- |
| `ico2/common/src/debug_exception_screen.c.inc` | `debug_exception.c` |
| `ico2/fumi/src/girl_act_hand.c.inc` | `girl_act.c` (inside `actGirlHand`) |
| `ico2/fumi/src/girl_brain_attract.c.inc` | `girl_act.c` |
| `ico2/sugipon/src/motMan_getFinalMatrix.c.inc` | `motionManager.c` |
| `ico2/sugipon/src/motMan_rootUpdate.c.inc` | `motionManager.c` |
| `ico2/sugipon/src/switch.c.inc` | `box.c` |

The listing names one more, `girl_brain_main.c.inc`, which includes
`girl_brain_attract.c.inc`. Its functions fall into three separate stretches
of `girl_act.o`'s emission order, so its text stays inside `girl_act.c` at
the point the listing puts it, and its assert strings still name it
(`"src/girl_brain_main.c.inc"`).

## Headers placed by this project

**One header per game file.** The other 217 headers under
`ico2/<programmer>/include/` are each named after the source file whose
definitions they declare (`gobj.h` for `isys/gobj.c`, `switch.h` for
`switch.c.inc`); the disc records none of them. They hold one prototype
per function and one `extern` per object, with the types the definitions
and their callers use. Shared records are
defined in the owner's header or, for the engine's records (`GObj`,
`Sub15C`, `Act`, ...), in `typedef.h`. A few files declare their own view of
a shared record under a comment saying so (`st04a.c`'s `Act` and `GObj`,
`item.c`'s `ClipWork`). Records only one file uses stay in that file.

**Sony's and newlib's headers.** The headers under `sce/<archive>/` carry the
SDK's public header names (`eekernel.h`, `libgraph.h`, `libdma.h`, ...) and
newlib's (`stdio.h`, `math.h`, ...). Each declaration is the signature of the
member under `sce/` that defines the symbol; `eekernel.h`, whose calls the
kernel defines, gives the public signatures of ps2sdk's
`ee/kernel/include/kernel.h`. Each header's opening comment says which.
Files named `*_internal.h` hold declarations that are not public API, and their names
are this project's, as is `sce/libsndn2/sound.h`, named after its member
`sound.o`; the movie player's audio decoder takes the stream PCM calls from
it. The listing attributes no rows to `/usr/local/sce/ee/include`, so no SDK
header compiled code into the game. The Japanese, Korean and USA links have
no `libscf` member, so `sce/libscf/` is listed only in PAL's link order.

## Per-target declarations

The headers are PAL's. Where the Japanese build lays out a record or
declares something differently, the owner's header holds the Japanese
declaration in a `VERSION_JPN` block beside PAL's, which the Korean build
shares (`#if defined(VERSION_JPN) || defined(VERSION_KOR)`): it lays out
every record as the Japanese one does, and its data tables differ only in
content and in `tex-property`'s row count (`docs/TARGETS.md`)
(`ico2/common/include/{charFileManager,charFileName,typedef,icoMisc,main}.h`,
`fumi/include/act-game.h`, `ito/include/{mv_defs,mv_vobuf}.h`, `script/include/end.h`,
`seki/include/{BgAnimation,GsBase}.h`, `sugipon/include/motionOrientManager.h`),
and every reader of the Japanese and Korean builds compiles that block. The records:

| record | header | the Japanese layout |
| --- | --- | --- |
| `MotionDef` (motion-def) | `sugipon/include/motionOrientManager.h` | 0x190 bytes (PAL 0x194, with `palSpeedRatio`); the words from 0x144 and the four shorts in another order, and the bit fields of `MotionModeBits`, `MotionFlags` and `MotionFlags2` in another order |
| `TexRec` (texture-path) | `common/include/charFileManager.h` | `char path[48]`, 0x30 bytes in .rodata (PAL adds `cameraMove`, 0x34 bytes) |
| `ActWork` | `fumi/include/act-game.h` | no `boxDir` (PAL 0x530): every later field sits 16 bytes lower (`wayReq` 0x570, `viewState` 0x7F0, `intrReq` 0x8A0) |
| `McProductFile` | `common/include/typedef.h` | 488 bytes (PAL adds `cameraMove` and `palMode` and aligns to 0x1F0) |
| `VoTag`, `VoData` | `ito/include/mv_vobuf.h` | sized for a 720 x 480 picture (PAL 720 x 576) |

`act.c`'s own `ActExt`, the extended work block, has its three histories
16 bytes lower than PAL's (0x8F0, 0x918, 0x940).

Where the USA build lays out a record differently, the owner's header holds
its layout in a `VERSION_NTSC` block (nested in the PAL arm where a Japanese
block stands), and every reader of the USA build compiles it
(`docs/TARGETS.md`). The records:

| record | header | the USA layout |
| --- | --- | --- |
| `Act` | `common/include/typedef.h` | `actMode` at 0x30 (PAL 0x34), `env` at 0x4A0 (PAL 0x4B0) |
| `Sub15C` | `common/include/typedef.h` | `motionBuf` at 0x78C (PAL 0x7B4), the node records at 0x840 (PAL 0x870) |
| `StageSetting` | `common/include/typedef.h` | ends at `pad124`: the target colours, grain scale, camera limits and anti levels PAL has from 0x130 are not in it |
| `ActWork` | `fumi/include/act-game.h` | no `boxDir`: `wayReq` 0x4B0, `viewState` 0x730, `intrReq` 0x7E0 (PAL 0x580, 0x800, 0x8B0) |
| `MotionDef` (motion-def) | `sugipon/include/motionOrientManager.h` | 0x190 bytes (PAL 0x194) |
| `TexRec` (texture-path) | `common/include/charFileManager.h` | `char path[32]`, 0x20 bytes (PAL `char path[48]` and `cameraMove`, 0x34 bytes) |
| `PObjMdl` (model-path) | `common/include/charFileManager.h` | 0x10C bytes: a model path and a shadow model path before the skeleton path (PAL 0x8C, without the two) |
| `McProductFile` | `common/include/typedef.h` | 0x18C bytes (PAL 0x1F0) |
| `VoTag`, `VoData` | `ito/include/mv_vobuf.h` | sized for a 720 x 480 picture (PAL 720 x 576) |

`flag.h`'s `FLAG_ALLOC_NODES` takes the caller's source line as a third
argument, which `flag.c` spells with `LN` (the original passed
`__LINE__`).

## Derived names

The disc records no field names and no names for inlined helpers. A name
derived from context instead of read from the disc's maps is marked with a
`/* derived name */` token on its definition line. A record of the game
whose field names are derived carries one `/* field names derived */` token
on its opening line rather than one per field. Sony's public types keep
their public names. Besides PAL's derived names, the Japanese and Korean
builds derive
`actEndLogoFade` (`script/src/end.c`, the ending step PAL's map calls
`actEndLogoChk`; the Japanese and Korean builds give that name to the save
step, as the August 6, 2001 prototype's `TRFILE.TXT` does), `DummyIcoMisc`
(`common/src/icoMisc.c`, an empty function only those builds have),
`bga_updateMotionFrame` and `bgaRotDeg` (`seki/src/BgAnimation.c`) and
`warning_mes` (`script/src/e3.c`). The USA build derives names for the
objects and functions only it has or splits differently (`git grep -n
'derived name'` inside the `VERSION_NTSC` blocks lists them).

## Search order

`tools/compile_c.sh` compiles each game file from inside its programmer
directory, with the programmer's own `include/` first and then
`-I../sugipon/include -I../omori/include -I../common/include
-I../ito/include -I../fumi/include -I../seki/include -I../script/include`,
then the `sce/` archive directories. The relative spellings are the ones the
ROM's `__FILE__` strings record. Sony's members compile from inside their
own directory by bare file name, for the same reason.

ninja does not track header dependencies: after editing a header, run
`tools/build.sh clean` before `ninja`.
