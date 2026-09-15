# Developer headers reconstructed into the include tree

The 2002-01-16 PAL listing (`baserom/pal/SRCFILE.TXT`, an `objdump -dl` of
the disc's `main.elf`; provenance and reading rules in
`docs/pal_source_tree.md`) attributes instructions inside 104 distinct functions (106 expansions) to
four developer **headers**, and whole functions to six more.  Instructions
attributed to a `.h` are a header body expanded into its caller, so each
distinct `first_line..last_line` range inside one header is a distinct
`static` helper.  This file records what was pulled out of those hosts into
real headers, what was written from the ROM without a matched host, and what
is still a TODO.

The census is local-only metadata: line ranges, host names, instruction
counts.  No source text exists in the listing and none is reproduced here.

## Naming rule applied

A helper's name is the developer's **only when the listing shows the helper
emitted out of line somewhere**, because that is the only case where the
binary carries a label for it.  Everything else gets a plain descriptive name
of ours, and every such name is marked as ours at its definition.

Two names in the census turned out to be traps:

* **`checkOverThePlane`** is listed as an out-of-line copy from
  `sugiCommon.h`, but it is not.  Its *first* instruction row is the inlined
  line-71 helper, which is what the census keys on; its own body rows are at
  `sugipon/src/clothAnimation.c:1086`.  It is a `clothAnimation.c` static
  that *calls* the header helper, and the line-69/71 helper itself has no
  name at all.
* **`Free`** (`mv_defs.h`) is genuine: *both* its rows are in the header
  (line 31 for the inlined mask, line 83 for `iosFree`), and it is emitted
  out of line once per including TU.  It is absent from
  `baserom/pal/MAIN.MAP`, so it is a file-static whose label comes from the
  binary's local symbol table.

## The `include/ico/types.h` split rule

`ico/types.h` keeps everything **cross-programmer**: the engine object shapes
(`GObj`, `Sub15C`, `Obj7F0`, `GeoNode`, `GeoSub`) recovered mechanically from
load offsets and used by every programmer's TUs.

A per-programmer header may claim a declaration out of `ico/types.h` or out
of a TU's file-top block **only when the census shows that programmer's
header is where the code using it lived**: i.e. there are census rows
pointing at that header from the TUs in question.

Under that rule **nothing moved out of `ico/types.h` in this pass, and no
file-top extern block was emptied.**  The reason is measurable: of the 89
census host functions, only 6 are matched in this tree
(`GetProjectionPosOfPlane`, `GetProjectionOfPlane`,
`GetProjectionOfPlaneWithKeepAway`, `GetOutOutsideOfWall`,
`vector_angle_degree`, `loadImage`) plus `checkOverThePlane` and the three
`Free` copies.  Every other host is still `INCLUDE_ASM`, so there is no
repeated file-top declaration to hoist: the declarations these headers own
are the ones their *own* helpers need, and those were written into the
headers directly.  The externs each TU declares today
(`AddVectorXYZ`, `iosFree`, ...) belong to whatever TU defines them, not to
these headers, and the census gives no evidence to reassign them.

## Headers created

Each header now sits at the path the listing records for it, under the
programmer directory that owns it.

| header | helpers written | TODO |
| --- | --- | --- |
| `ico2/sugipon/include/sugiCommon.h` | 9 | none |
| `ico2/ito/include/itou_common.h` | 2 | none |
| `ico2/common/include/typedef.h` | 0 | line 74 |
| `ico2/ito/include/mv_defs.h` | 3 | line 83 (`Free`) |
| `ico2/omori/include/b50climb.h` | 0 | 3 functions |
| `ico2/omori/include/b100climb.h` | 0 | 3 functions |
| `ico2/omori/include/b200climb.h` | 0 | 3 functions |
| `ico2/omori/include/g50climb.h` | 0 | 3 functions |
| `ico2/omori/include/g100climb.h` | 0 | 3 functions |
| `ico2/omori/include/g200climb.h` | 0 | 3 functions |
| `ico2/common/include/charFileName.h` | n/a | none |

`charFileName.h` is the eleventh and the only one the listing does not name.
It has no SRCFILE.TXT rows at all; the retail ELF names it, in the message at
`D_00619370` (.rodata, VMA 0x00619370, rom offset 0x519370), which spells
`commmon/include/charFileName.h` with the developers' typo and asks the reader
to raise `MAX_CHARS`. The path is hand typed into that message rather than
expanded from `__FILE__`, so it fixes the header's name and directory but says
nothing about the `-I` spelling gcc saw, and no include search order had to
change: `tools/compile_c.sh` already puts `-I../common/include` in every ico2
TU's order. The three sites in `ico2/common/src/charFileManager.c` that print
the message all compare against 1637, so the bound is the one recoverable
contents, and the message's bytes still come from the uncarved blob
`asm/data/cod/4577D0.rodata.s`.

## The `.c.inc` code-includes

The census records four coalescing TUs. `ico2/fumi/src/girl_act.c` pulls in
three members, of which two are split out as of 2026-09-14,
`girl_act_hand.c.inc` (five `HandMgr_*` bodies) and `girl_brain_attract.c.inc`
(three), both contiguous runs of the emission order that moved verbatim. The
third, `girl_brain_main.c.inc`, is blocked: its functions occupy three disjoint
blocks of the emission order, 0x0016FC30 to 0x00177898, then
`FindGirlPullupFloorBoxGObj` alone at 0x0017B858, then 0x0017C3A8 to
0x0017C6D0, because the end-of-file inline tail splits them. The same blocker
holds the six `*climb.h` bodies, below.

`mv_defs.h`'s line-42 helper bakes `__FILE__` into `.rodata` as the literal
`"../ito/include/mv_defs.h"` (`D_005576A8` in the ROM), which only comes out
right if the consuming TU is compiled from CWD `${ROOT}/ico2/ito` with a
relative `-I../ito/include`.  That is now how every game TU is compiled:
`tools/compile_c.sh` runs each one from inside its own programmer directory
with relative `-I../<other>/include` entries, so the spelling the ROM
recorded is the spelling gcc is given.  The earlier opt-in list
`config/include_ito.txt` is superseded by that rule.

---

## `ico2/sugipon/include/sugiCommon.h`

Census sections: `{sugipon,fumi,script,omori,ito,common}/../sugipon/include/sugiCommon.h`
adds up to 62 + 11 + 1 + 1 + 6 + 3 = 84 expansions.  Nine distinct line ranges, so
nine helpers.  Every one is inline-only, so **all nine names are ours**.

| header lines | what the ROM does | census hosts | status |
| --- | --- | --- | --- |
| 45-48 `random_unit` | `jal _GetRandom` | 39 hosts (line 47) | reconstruction |
| 53-56 `random_signed` | `2*x - 1.0f` over `random_unit` | 13 hosts (47+55) | reconstruction |
| 58-61 `crt_random_unit` | `((rand()>>4)&0xFFFF) * 1/65535` | 3 hosts (line 60) | MATCHED 2026-09-11 (hosts playSERandomID, execEff in src/frameDependSequence) |
| 63-66 `random_signed_b` | identical body to lines 53-56 | 5 hosts (47+65) | reconstruction |
| 69-72 `plane_distance` | `dot(plane.xyz,pos.xyz)+plane.w` on VU0 | 28 expansions | **PROVEN** |
| 85-88 `distance_squared` | `\|a-b\|^2` (xyz) on VU0 | 22 hosts (85/87) | MATCHED 2026-09-07 (host GetChainCollision): one clobber-free asm block like plane_distance; the macro form's "memory" clobber killed gcse's MEM expressions in every host |
| 95-98 `distance_squared_b` | identical body to lines 85-88 | 1 host (87+97) | reconstruction; see the note below |
| 100-103 `distance_squared_xz` | `dx^2+dz^2` (`vmul.xz`) | 1 host (line 102) | reconstruction |
| 115-120 `byte_checksum` | byte sum over n bytes | 2 hosts (115/118/119) | reconstruction |

### `distance_squared`: the listing settles which helper each host absorbed
(2026-09-14)

The open item of 2026-09-11 was whether `subAP1BrainMain` and
`GetChainCollision` absorb the same helper, since each reaches rc0 only under a
spelling the other rejects (the macro-split form and the single-block
`$2`-clobber form respectively, about 70 words moving under the wrong one).
The census decides it: both hosts cite the range `sugiCommon.h(87-87)` and
nothing else, so both absorbed the line 85-88 helper, and there is one dev body
to find, not two.

The line 95-98 helper is a different question and the listing keeps it separate.
Its only host is `GetBoxHoldPoint` (`src/box`, 0x001C9448), which cites
`sugiCommon.h(87-97)`: it absorbs BOTH helpers, which is why the two line ranges
cannot be collapsed. Nothing else in the listing cites line 95 or 97. The line
100-103 helper likewise has exactly one host, `clip_wall_1` (`src/way_llf`,
0x0016B268), citing `sugiCommon.h(102-102)`.

So the divergence between `subAP1BrainMain` and `GetChainCollision` is a
source-shape problem inside one of the two hosts, not evidence of a second
helper.

**Measured 2026-09-15, both hosts now matched C.** `subAP1BrainMain` landed, so
the question can be put to both objects at once. It cannot be answered yet, and
the axis is now known: it is the NUMBER of `__asm__` blocks the helper is spelt
in, not the clobber list and not where the `qmfc2`/`mtc1` hop is pinned. Seven
spellings were compiled against both TUs, each gated on the object's `.text`
bytes:

| spelling | `act_a_p_1.o` | `clothAnimation.o` |
| --- | --- | --- |
| one block, `$2` hard-wired and clobbered (the header's current body) | diff | 0 |
| one block, same plus a `"memory"` clobber | diff | diff |
| one block through `qmfc2`, allocated `"=r"` temp, separate `mtc1` | diff | 0 |
| one block through `vaddz`, separate pinned `qmfc2`/`mtc1` pair | diff | diff |
| per-instruction blocks, `VU0_LSV_R` loads, allocated hop (the `_b` body) | 0 | diff |
| per-instruction blocks, loads without the `"memory"` clobber | 0 | diff |
| per-instruction blocks, pinned `qmfc2`/`mtc1` pair | 0 | diff |

Every multi-block form reaches rc0 in `subAP1BrainMain` and every single-block
form reaches rc0 in `GetChainCollision`, with no overlap. Until a spelling is
found that does both, `subAP1BrainMain` calls `distance_squared_b`, whose body
is the multi-block form: that call is a PLACEHOLDER for the line 85-88 helper,
not a claim that the host absorbed the line 95-98 one. The census says line 87
and only line 87.

Two pairs (53-56 vs 63-66, and 85-88 vs 95-98) emit the *same* instruction
sequence at *different* header lines.  The line ranges are the only evidence
that there are two of each; we do not know how the developer's two spellings
differed, and both are written out rather than collapsed, because collapsing
them would throw away that evidence.

The `1/65535` constant in `crt_random_unit` is not a guess: `playSERandomID`
(retail 0x001DBF18) multiplies by `D_006394E4`, whose word in
`baserom/pal/baseelf.elf` is `0x37800080` = 1.5259022e-05 = 1.0f/65535.0f.

The line-100 and line-95 helpers have a single census host each, below the
"define it from >= 2 hosts" bar.  They are written anyway because their
instruction sequences are unambiguous and identical in shape to their proven
siblings; both are labelled RECONSTRUCTION at the definition.  (The
one-host helper in `typedef.h` is *not* written (see below) because its
shape has no proven sibling to key off.)

### `plane_distance`: factored and re-gated

Four matched hosts now call it and each still assembles byte-identically
(`tools/match_diff.py --count` = 0):

| host | TU | was |
| --- | --- | --- |
| `GetProjectionPosOfPlane` | `src/geometryManager` | open-coded VU0 block |
| `GetProjectionOfPlane` | `src/geometryManager` | open-coded VU0 block |
| `GetProjectionOfPlaneWithKeepAway` | `src/geometryManager` | open-coded VU0 block |
| `checkOverThePlane` | `src/clothAnimation` | open-coded + 2 register pins |

`checkOverThePlane` collapsed from 20 lines to two, and the factoring
**retired three crutches** in it: the bare register pins
`register float f1 __asm__("$f1")` / `register float f0 __asm__("$f0")` and
the dead store `bits = v0;`.  All three are in the class CLAUDE.md bans.

### `GetOutOutsideOfWall`: the host that refused, and no longer does

`src/motionManager2`'s `GetOutOutsideOfWall` is a fifth matched host of the
line 69-72 helper. The listing is unambiguous about it: its eight rows
`lqc2 vf1,0($sp)` through `mtc1 $v0,$f0` are attributed to
`sugipon/../sugipon/include/sugiCommon.h:71`, with `motionManager2.c:2119` on
the `GetGlobalWallPlane` call before them and `motionManager2.c:2120` on the
compare after, so the developer's source called the helper here.

The host used to keep the body hand-expanded, because calling
`plane_distance(buf0, buf1)` cost one extra `daddu v0,s0,zero`: `&buf1` is a
frame address, not a bare register, so `expand_inline_function` forced it into
a fresh pseudo for the `plane` parameter and copy-propagation failed to
coalesce that pseudo with the `s0` the preceding `GetGlobalWallPlane` call had
already put the same address in.

**That is stale as of 2026-09-15.** Commit 25683f1fd reshaped the helper into
one `asm volatile` block with the `qmfc2`/`mtc1` hop hard-wired to `$v0` and
declared as a clobber, and the extra copy went with it. The site now calls
`plane_distance(buf0, buf1)` like the other four hosts and
`motionManager2.o` is byte-identical to what the hand-expanded body produced:
same `.text` bytes, same relocations, same `nm -n` order. The only change in
the object file is eight bytes of `.mdebug`, the local `int t` the expansion
needed, and `.mdebug` is not allocated and never reaches the ROM.

The rewrite that first landed the hand-expansion is still worth its note: it
dropped two bare register pins (`register float thr __asm__("$f20")`,
`register float dot __asm__("$f0")`), both in the class CLAUDE.md bans.

`src/motionManager2.c` keeps `#include "sugiCommon.h"` even though it does not
currently call the helper: the census shows two of its functions
(`AdjustVerticalSidePlaneOfWall`, `GetOutOutsideOfWall`) consuming the
line-71 helper, so the file is a genuine consumer and the include is
byte-neutral.  No other census-consumer TU was given the include, because an
include that nothing uses buys nothing and every one of them is a chance to
perturb a matched TU.

---

## `ico2/ito/include/itou_common.h`

Census section `ito/../ito/include/itou_common.h`, 5 hosts, two line ranges.
Both helpers are inline-only, so **both names are ours**.

| header lines | what the ROM does | census hosts | status |
| --- | --- | --- | --- |
| ~24-27 `degrees_to_radians` | `x * 2pi / 360.0f` | 4 hosts (line 26) | reconstruction |
| ~29-32 `radians_to_degrees` | `x * 360.0f / 2pi` | 2 hosts (line 31) | **PROVEN** (1 matched host) |

`src/act_bird.c`'s `vector_angle_degree` is matched and the census puts its
tail on `itou_common.h:31`; it now calls `radians_to_degrees()` and re-gates
at 0.  `degrees_to_radians` has four census hosts, all still `INCLUDE_ASM`.

---

## `ico2/ito/include/mv_defs.h`

Census section `ito/../ito/include/mv_defs.h`: 16 inline expansions plus three
out-of-line `Free` copies.  Four line ranges.

| header lines | what the ROM does | census hosts | status |
| --- | --- | --- | --- |
| 30-31 `phys_addr` | `p & 0x0FFFFFFF` | 4 matched + 7 census | **PROVEN** |
| 35-36 `uncached_accel_addr` | `(p & 0x0FFFFFFF) \| 0x20000000` | 7 hosts | reconstruction |
| 42-45 `alloc_zeroed(size, align)` | alloc + assert + `memset` | 5 hosts (voBufCreate matched; viBufCreate's three sites pass 0x40, 0x40, 4) | reconstruction, `#ifdef`-guarded; alignment is a parameter since 2026-09-06 |
| 82-84 `Free` | `iosFree(phys_addr(p))` | 3 out-of-line copies | **TODO** |

`phys_addr` is factored into four matched hosts, each re-gated at 0:
`Free` (`ito/mpeg/mv_videodec`), `func_001A7318` (`mv_vobuf`),
`func_0025A4A8` (`mv_vibuf`), `loadImage` (`mv_disp`).  Those four TUs are
now listed in `config/include_ito.txt` and spell the include as the developer
did, `#include "mv_defs.h"`.

**This file's line numbers are load-bearing; it must not be reflowed.**  The
line-42 helper's `__LINE__` values are baked into the ROM as immediates
`0x2B` (43, the `iosMallocAlignDebug` call) and `0x2C` (44, the assert), and
its two `__FILE__`/expression literals are `"../ito/include/mv_defs.h"`
(`D_005576A8`) and `"p != NULL"` (`D_005576C8`), both read back out of
`baserom/pal/baseelf.elf` to confirm the reconstruction.

`alloc_zeroed` was checked against the ROM without a matched host, by
compiling a throwaway TU that calls it with `MV_DEFS_WANT_ALLOC` defined:
ee-gcc emits both literals, `li $8,43` in the `iosMallocAlignDebug` delay
slot, `li $5,44` in both assert calls, and the same argument order and
branch shape as retail `readBufCreate` (0x001A6810).  That is as far as the
reconstruction can be verified while all five of its hosts are `INCLUDE_ASM`.

`alloc_zeroed` sits behind `#ifdef MV_DEFS_WANT_ALLOC`.  It has to: ee-gcc
2.9 drops the unused `static` but **keeps its string literals**, so an
unguarded definition emitted both literals into each of the four consuming
objects and shifted the `.data` region. Thethe first full-build gate caught it
as a data divergence over a long list of symbols.  Define the macro
before the include in whichever TU first calls the helper.

`Free` stays a TODO even though its name and body are known.  It is a header
file-static: any including TU that does not call it in C would drop it as an
unused static and break the relocs of its still-`INCLUDE_ASM` callers, and it
would collide with the copy `mv_videodec.c` already defines.  Write it into
the header when its callers are C; until then the three TUs keep their own
copies, all of which now call `phys_addr()`.

Note that `docs/mv_defs_h.md` describes the *Aug-2001 prototype's* version
of this header, whose helper at these lines dequeued a message
(`deq_mes_th`).  In the 2002 PAL build the helper at lines 42-45 allocates.
Same header, different revision: the earlier document describes
a different target.

---

## `ico2/common/include/typedef.h`

One census row: `avoid_obstacle2` (`src/way_sys`, 0x0017DA50) absorbs
`typedef.h:74` twice.  The sequence is
`mtc1 $zero,$fN; c.lt.s $f1,$fN; bc1tl; neg.s $f1,$f1`: a float absolute
value, `x < 0.0f ? -x : x`.  It is left as a **TODO** rather than written:
the bar for writing a census-only helper is >= 2 *hosts*, and this is one host
expanding it twice.  Its host is still `INCLUDE_ASM`, and the helper is never
emitted out of line, so it has no name either.

## The six `*climb.h` code-includes

`b50climb.h`, `b100climb.h`, `b200climb.h` are `#include`d as code into
`fumi/src/boyact.c`; `g50climb.h`, `g100climb.h`, `g200climb.h` into
`fumi/src/girl_act.c`.  Each defines three whole functions
(`after*Hand*`, `act*Hand*`, `mot*Hand*`), 18 in total, and those names are
the developer's, from the listing's symbol table.

Each defines three whole functions (`after*Hand*`, `act*Hand*`, `mot*Hand*`),
18 in total, and those names are the developer's, from the listing's symbol
table. The census gives each one its header line range and instruction count.

**Correction 2026-09-14.** This section used to say that none of the 18
correlates to a retail VMA and that a body derived from the listing could not
be gated. Both halves are now false. Every one of the 18 has an address in
`config/symbol_addrs.pal.txt`, and 16 of the 18 are matched C today: all nine
girl functions inside `ico2/fumi/src/girl_act.c` and seven of the nine boy
functions inside `ico2/fumi/src/boyact.c`, with only `motBoyHand100`
(0x001507F8) and `motBoyHand200` (0x00150AA8) still `INCLUDE_ASM`. What is
true is the narrower statement the correction started from: the census's own
`pal vma` cells for these six sections are blank, because the listing
instruments every `act*Hand*` entry point with a `printf` on a debug global and
the generator's instruction-stream hashing cannot correlate an instrumented
body. The addresses came from the positional recovery instead.

The instruction counts show the instrumentation directly. `motGirlHand50` is 98
instructions in the listing and 98 in the ROM (0x0016F6B0 to 0x0016F838), an
uninstrumented function that matches exactly; `actGirlHand50` is 46 in the
listing against 42 in the ROM (0x0017C0E8 to 0x0017C190) and `afterGirlHand50`
17 against 16, the difference being the debug call the January 2002 link
carried.

**Why the bodies are still not in the headers.** Moving them is the same
blocker that holds `girl_brain_main.c.inc`: ee-gcc 2.9 emits non-inline
functions in parse order and inline functions at end of file in prototype
order, and in `girl_act.o` the `mot*` third of each header lands in the parse
run (0x0016F6B0 onward) while the `act*` and `after*` thirds land in the
end-of-file tail (0x0017C0E8 onward). A single `#include` of `g50climb.h`
cannot put one of its three functions in the parse run and two in the tail
until the tail is rebuilt as `inline` definitions with a prototype order
recovered from the ROM's tail order. `boyact.o` has the same split.

Each header keeps its functions' header line ranges and instruction counts
until then.

## Drift audit (2026-09-05)

Matched hosts must CALL the header helper, not open-code its body: an
open-coded body is the same defect as a TU laid out in the wrong order.
Measured from the census against the tree: of the census hosts that are
matched C, four open-coded a helper and were converted, each re-gated at 0
and the whole ROM byte-identical: `ExecWindManager` (windManager),
`scpBornSpider` (script) and `EnemyCtrlBeforeFunc` (enemy-control) now call
`random_unit()`; `sendDispEnv` (mv_disp) calls `phys_addr()`.  Newly landed
hosts call the helper from the start (`InitBirdGeo` in act_bird,
`getParallelWindVector` in windField).

`plane_distance` changed form in the same pass (commit 25683f1fd): it is one
`asm volatile` block with the `qmfc2`/`mtc1` hop hard-wired to `$v0` and
declared as a clobber, only the float result allocated.  The listing shows
that hop as `$v0` in all 28 expansions while the `mtc1` destination varies
over seven FP registers, so a gcc-allocated temp cannot be the developer's
spelling; in `getParallelWindVector` the allocated temp shared `$v0` with the
plane address and cost six instructions.  The four earlier hosts re-gate at 0.

## Inlining check

Every helper written into these headers really is inlined by ee-gcc 2.9 with
the project's flags: a probe TU that includes all nine new `include/` headers
and calls all eleven helpers compiles with `-Wall` clean and emits exactly one
`.ent` (the probe itself): no out-of-line copy of any helper, which is what
an INCLUDE_ASM host's reloc would collide with.

## Gate

`tools/build.sh setup && .venv/bin/ninja` →
`verify_elf: OK (build/ico.rom sha1=a401d1e5a20b1659189a8b1026a8eb35811dc9ca)`,
the same SHA-1 as before this pass.

One operational note learned here: **ninja does not track header
dependencies** in this tree.  Editing a header does not rebuild the objects
that include it; the stale objects link and the gate reports the *old* SHA-1.
Delete the affected `.o`/`.s` (or do a clean rebuild) after any header edit,
or a header change will silently go ungated.


## Open prototype questions

The listing carries no source text and no types, so it cannot settle a
signature on its own. What it does settle is where each function lives and
whether its definition exists as C yet, which is what each item below is
gated on.

- `WayLengthOfGObj_GObj` (`fumi/src/way_kidnap.c:215`, 0x00215BC8): **closed
  2026-09-15.** The definition is matched C in `ico2/fumi/src/way_kidnap.c` and
  takes two pointers, `float WayLengthOfGObj_GObj(void *obj0, void *obj1)`.
  `common/src/backStage.c` used to declare it locally as `(int, int)`; that
  declaration now matches the definition and `routeSetPos` casts its two `int`
  parameters at the call. `backStage.o` is byte-identical across the change.
- `WayPointWithRangeFromPos2` (`fumi/src/way_kidnap.c:385`, 0x00215400): still
  open, and nothing landed since that could close it.
  `backStageProcessOutStage` reaches rc0 only with `void *` as the second
  parameter, and the definition is still `INCLUDE_ASM` in `way_kidnap.c`. Only
  a matched body fixes the type.
- `gamesysObjInfoPosSetStage` (`common/src/gamesys.c:564`, 0x001B6FB8):
  **closed 2026-09-15.** The definition is matched,
  `int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3)`, and the
  six local declarations that disagreed with it and with each other
  (`fumi/src/enemy_act.c` twice, `fumi/src/boyact.c` twice,
  `fumi/src/act-game.c`, `script/src/e3.c`, `script/src/script.c`,
  `common/src/backStage.c`) now all spell the definition's signature, with a
  cast at each call site. All six objects are byte-identical across the change.
- `LockForceGroundParent` / `UnlockForceGroundParent`: empty retail bodies, now
  declared with the GObj parameter every call site passes (commit 009da5cd1).

Per-TU prototypes stay declared in the TU: the owning header is unrecoverable
for every one of them, since a header that only declares emits no instructions
and therefore leaves no row the listing could attribute.

## The scaffolding-header migration (2026-09-15)

`include/` no longer holds `r5900.h`, `vu0.h`, `ico/types.h`, `syscall.h` or
`math_private.h`. What each held, where it went, and on what evidence is in
`include/README.md`. Two facts belong here as well:

* The listing attributes zero rows to `/usr/local/sce/ee/include`, so no SDK
  header inlined code into the January 2002 link and every SDK call in our C
  is a call in the ROM too.
* Every expansion of every `VU0_*` and R5900 macro in the tree is attributed
  by `SRCFILE.TXT` to the `.c` line that invokes it. That is what a macro
  expansion looks like from `objdump -dl` and it rules nothing in or out about
  the header the macro came from; it does rule out the macros having been
  `static` helpers in one of the ten attested headers, since those would have
  shown their own header line the way `plane_distance` does. The only
  macro-bearing function in the tree whose rows the listing puts in a header
  is `GetOutOutsideOfWall`, and that is the `plane_distance` call above.

