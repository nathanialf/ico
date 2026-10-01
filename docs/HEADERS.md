# Headers

Which headers in the tree the disc attests, and how the others were placed
and named.

The evidence is the PAL disc's January 2002 listing (`SRCFILE.TXT`, an
`objdump -dl` of the game with a source path and line on every instruction)
and its `MAIN.MAP`; both are copied into `baserom/pal/` by
`tools/extract_elf.sh` and are never committed (`docs/LEGAL.md`). The listing
contains no source text. A header shows up in it only when code from the
header was compiled into a caller: a header that only declares leaves no
rows at all.

## Headers the disc attests

Eleven headers under `ico2/` are known from the disc. Each sits at the path
the listing records for it, under the programmer directory that owns it.

| header | evidence | what it holds |
| --- | --- | --- |
| `ico2/sugipon/include/sugiCommon.h` | 84 inlined expansions in callers across six programmer directories | nine `static` inline helpers: random numbers, plane distance, squared distances, a byte checksum |
| `ico2/ito/include/itou_common.h` | inlined expansions in five `ito` functions | degree and radian conversion |
| `ico2/ito/include/mv_defs.h` | inlined expansions in the movie player, and three out-of-line copies of `Free` | address masks, a zeroing allocator, `Free` |
| `ico2/common/include/typedef.h` | one helper at line 74, inlined twice into `avoid_obstacle2` | the engine's shared object records (`GObj`, `Sub15C`, `Obj7F0`, ...) and the game's VU0 asm templates |
| `ico2/omori/include/{b50,b100,b200}climb.h` | whole functions, emitted into `fumi/src/boyact.c`'s object | the boy's climb handlers |
| `ico2/omori/include/{g50,g100,g200}climb.h` | whole functions, emitted into `fumi/src/girl_act.c`'s object | the girl's climb handlers |
| `ico2/common/include/charFileName.h` | no listing rows; the ROM's message at `0x00619370` names `commmon/include/charFileName.h` (the typo is the message's) | `MAX_CHARS`, the bound three call sites compare against (1637) |

Things a reader of these files should know:

- **Helper names.** An inlined helper leaves no symbol, so its name is the
  developer's only when the listing shows it emitted out of line somewhere.
  That holds for `Free` and for the eighteen climb functions
  (`after*Hand*`, `act*Hand*`, `mot*Hand*`). Every other helper name is a
  descriptive one chosen here and is marked so at its definition.
- **Two pairs of identical helpers.** `sugiCommon.h` lines 53-56 and 63-66,
  and lines 85-88 and 95-98, compile to the same instructions. The listing
  cites the lines separately, so both of each pair are written out.
- **Line numbers that are part of the bytes.** `mv_defs.h`'s allocator bakes
  `__FILE__` and `__LINE__` into the ROM (`"../ito/include/mv_defs.h"`, lines
  43 and 44), and `typedef.h`'s helper must stay on line 74. Neither file may
  be reflowed.
- **The climb headers hold no bodies.** ee-gcc 2.9 emits ordinary functions
  in parse order and `inline` ones at the end of the file. In each includer
  the `mot*` function lands in the parse-order run and the `act*` and
  `after*` functions in the end-of-file run, which one `#include` cannot
  produce. The eighteen functions are therefore defined in `boyact.c` and
  `girl_act.c`, with a comment naming the header lines, and the headers keep
  the listing's line ranges and instruction counts.

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

**One header per game file.** The other 216 headers under
`ico2/<programmer>/include/` are named after the file whose definitions they
declare (`gobj.h` for `isys/gobj.c`). The disc records no such file, and
each one says so in its opening comment. They hold one prototype per
function and one `extern` per object, typed from the calling convention at
the call sites and from the definitions; the byte gate decides between
conflicting spellings, since an argument's declared type can move registers.
Shared records are defined in the owner's header or, for the engine's
records, in `typedef.h`; some files still define a local, partial view of a
shared record (several `CamWork` and `ClothCfg` definitions, for example).
Records only one file uses stay in that file. A file that keeps a local declaration instead of
including the owner's header says why in a `kept local` comment.

**Sony's and newlib's headers.** The headers under `sce/<archive>/` carry the
SDK's public header names (`eekernel.h`, `libgraph.h`, `libdma.h`, ...) and
newlib's (`stdio.h`, `math.h`, ...). The declarations follow the signatures
the open-source ps2sdk headers and newlib's own headers give; where a header
follows one, its opening comment names the file. Files named `*_internal.h` hold
declarations that are not public API, and their names are this project's.
The listing attributes no rows to `/usr/local/sce/ee/include`, so no SDK
header compiled code into the game.

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
