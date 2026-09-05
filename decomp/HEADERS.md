# Developer headers reconstructed into the include tree

The 2002-01-16 PAL listing (`baserom/pal/SRCFILE.TXT` — an `objdump -dl` of
the disc's `main.elf`; provenance and reading rules in
`decomp/pal_source_tree.md`) attributes instructions inside 104 distinct functions (106 expansions) to
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
header is where the code using it lived** — i.e. there are census rows
pointing at that header from the TUs in question.

Under that rule **nothing moved out of `ico/types.h` in this pass, and no
file-top extern block was emptied.**  The reason is measurable: of the 89
census host functions, only 6 are matched in this tree
(`GetProjectionPosOfPlane`, `GetProjectionOfPlane`,
`GetProjectionOfPlaneWithKeepAway`, `GetOutOutsideOfWall`,
`vector_angle_degree`, `loadImage`) plus `checkOverThePlane` and the three
`Free` copies.  Every other host is still `INCLUDE_ASM`, so there is no
repeated file-top declaration to hoist — the declarations these headers own
are the ones their *own* helpers need, and those were written into the
headers directly.  The externs each TU declares today
(`AddVectorXYZ`, `iosFree`, ...) belong to whatever TU defines them, not to
these headers, and the census gives no evidence to reassign them.

## Headers created

| header | dev path | helpers written | TODO |
| --- | --- | --- | --- |
| `include/sugiCommon.h` | `sugipon/include/sugiCommon.h` | 9 | — |
| `include/itou_common.h` | `ito/include/itou_common.h` | 2 | — |
| `include/typedef.h` | `common/include/typedef.h` | 0 | line 74 |
| `ito/include/mv_defs.h` | `ito/include/mv_defs.h` | 3 | line 83 (`Free`) |
| `include/b50climb.h` | `omori/include/b50climb.h` | 0 | 3 functions |
| `include/b100climb.h` | `omori/include/b100climb.h` | 0 | 3 functions |
| `include/b200climb.h` | `omori/include/b200climb.h` | 0 | 3 functions |
| `include/g50climb.h` | `omori/include/g50climb.h` | 0 | 3 functions |
| `include/g100climb.h` | `omori/include/g100climb.h` | 0 | 3 functions |
| `include/g200climb.h` | `omori/include/g200climb.h` | 0 | 3 functions |

`mv_defs.h` is the one header that is **not** under `include/`.  Its line-42
helper bakes `__FILE__` into `.rodata` as the literal
`"../ito/include/mv_defs.h"` (`D_005576A8` in the ROM), which only comes out
right if the consuming TU is compiled from CWD `${ROOT}/ito` with a relative
`-I../ito/include`.  That mechanism already exists in `tools/compile_c.sh`
and `tools/quick_diff.sh`, opt-in through `config/include_ito.txt`; putting
the header anywhere else would break it.

---

## `include/sugiCommon.h`

Census sections: `{sugipon,fumi,script,omori,ito,common}/../sugipon/include/sugiCommon.h`
— 62 + 11 + 1 + 1 + 6 + 3 = 84 expansions.  Nine distinct line ranges, so
nine helpers.  Every one is inline-only, so **all nine names are ours**.

| header lines | what the ROM does | census hosts | status |
| --- | --- | --- | --- |
| 45-48 `random_unit` | `jal _GetRandom` | 39 hosts (line 47) | reconstruction |
| 53-56 `random_signed` | `2*x - 1.0f` over `random_unit` | 13 hosts (47+55) | reconstruction |
| 58-61 `crt_random_unit` | `((rand()>>4)&0xFFFF) * 1/65535` | 3 hosts (line 60) | reconstruction |
| 63-66 `random_signed_b` | identical body to lines 53-56 | 5 hosts (47+65) | reconstruction |
| 69-72 `plane_distance` | `dot(plane.xyz,pos.xyz)+plane.w` on VU0 | 28 expansions | **PROVEN** |
| 85-88 `distance_squared` | `\|a-b\|^2` (xyz) on VU0 | 22 hosts (85/87) | reconstruction |
| 95-98 `distance_squared_b` | identical body to lines 85-88 | 1 host (87+97) | reconstruction |
| 100-103 `distance_squared_xz` | `dx^2+dz^2` (`vmul.xz`) | 1 host (line 102) | reconstruction |
| 115-120 `byte_checksum` | byte sum over n bytes | 2 hosts (115/118/119) | reconstruction |

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
one-host helper in `typedef.h` is *not* written — see below — because its
shape has no proven sibling to key off.)

### `plane_distance` — factored and re-gated

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

### `GetOutOutsideOfWall` — the one host that refused

`src/motionManager2`'s `GetOutOutsideOfWall` is a fifth matched host of the
same helper, and calling `plane_distance(buf0, buf1)` there costs **+2**:
ee-gcc inserts a `daddu v0,s0,zero` before the pair of `lqc2`s and then loads
`lqc2 $vf2,0(v0)` where the ROM has `0(s0)`.

Mechanism, measured rather than guessed.  Hand-expanding the identical helper
body at the call site gives 0 diffs, so the extra instruction is not the
constraint form (`"r"` + `"memory"`), the operand order, `const`-ness, or the
result's `float` temp — all four were tried and all four still give 2.  It is
the **inliner's parameter copy**: `&buf1` is a frame address (`sp+16`), not a
bare register, so `expand_inline_function` forces it into a fresh pseudo for
the `plane` parameter, and copy-propagation then fails to coalesce that pseudo
with the `s0` the preceding `GetGlobalWallPlane` call already put the same
address in.  The three `geometryManager` hosts do not hit it because their
actuals are incoming *parameters*, already in hard registers.  Two other
constraint spellings were tried and are worse, not better: an `"m"` memory
operand gives 16 diffs there and 0/0/0 in `geometryManager`; an `"r"`+`"m"`
pair gives 15 there and 11/13/13 in `geometryManager`.

So `GetOutOutsideOfWall` keeps the helper body hand-expanded, with a comment
at the site naming the mechanism.  It was still worth touching: the rewrite
dropped its two bare register pins (`register float thr __asm__("$f20")`,
`register float dot __asm__("$f0")`) and still gates at 0.

`src/motionManager2.c` keeps `#include "sugiCommon.h"` even though it does not
currently call the helper: the census shows two of its functions
(`AdjustVerticalSidePlaneOfWall`, `GetOutOutsideOfWall`) consuming the
line-71 helper, so the file is a genuine consumer and the include is
byte-neutral.  No other census-consumer TU was given the include, because an
include that nothing uses buys nothing and every one of them is a chance to
perturb a matched TU.

---

## `include/itou_common.h`

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

## `ito/include/mv_defs.h`

Census section `ito/../ito/include/mv_defs.h`: 16 inline expansions plus three
out-of-line `Free` copies.  Four line ranges.

| header lines | what the ROM does | census hosts | status |
| --- | --- | --- | --- |
| 30-31 `phys_addr` | `p & 0x0FFFFFFF` | 4 matched + 7 census | **PROVEN** |
| 35-36 `uncached_accel_addr` | `(p & 0x0FFFFFFF) \| 0x20000000` | 7 hosts | reconstruction |
| 42-45 `alloc_zeroed` | alloc + assert + `memset` | 5 hosts | reconstruction (codegen-verified), `#ifdef`-guarded |
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
(`D_005576A8`) and `"p != NULL"` (`D_005576C8`) — both read back out of
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
objects and shifted the `.data` region — the first full-build gate caught it
as a data divergence over a long list of symbols (`tools/data_diff.py`).  Define the macro
before the include in whichever TU first calls the helper.

`Free` stays a TODO even though its name and body are known.  It is a header
file-static: any including TU that does not call it in C would drop it as an
unused static and break the relocs of its still-`INCLUDE_ASM` callers, and it
would collide with the copy `mv_videodec.c` already defines.  Write it into
the header when its callers are C; until then the three TUs keep their own
copies, all of which now call `phys_addr()`.

Note that `decomp/mv_defs_h.md` describes the *Aug-2001 prototype's* version
of this header, whose helper at these lines dequeued a message
(`deq_mes_th`).  In the 2002 PAL build the helper at lines 42-45 allocates.
Same header, different revision — the earlier document is not wrong, it is
about a different target.

---

## `include/typedef.h`

One census row: `avoid_obstacle2` (`src/way_sys`, 0x0017DA50) absorbs
`typedef.h:74` twice.  The sequence is
`mtc1 $zero,$fN; c.lt.s $f1,$fN; bc1tl; neg.s $f1,$f1` — a float absolute
value, `x < 0.0f ? -x : x`.  It is left as a **TODO** rather than written:
the bar for writing a census-only helper is >= 2 *hosts*, and this is one host
expanding it twice.  Its host is still `INCLUDE_ASM`, and the helper is never
emitted out of line, so it has no name either.

## The six `*climb.h` code-includes

`b50climb.h`, `b100climb.h`, `b200climb.h` are `#include`d as code into
`fumi/src/boyact.c`; `g50climb.h`, `g100climb.h`, `g200climb.h` into
`fumi/src/girl_act.c`.  Each defines three whole functions
(`after*Hand*`, `act*Hand*`, `mot*Hand*`) — 18 in total — and those names are
the developer's, from the listing's symbol table.

All 18 are **TODO with no body**, and deliberately so.  `SRCFILE.TXT`
disassembles a different link from the retail ELF we build (its `.text` runs
to 0x0028DB34 against retail's 0x00289BC4) and these functions are
instrumented in it: every `act*Hand*` entry point opens with a `printf` gated
on a debug global.  None of the 18 correlates to a retail VMA — every
`pal vma` cell in those census sections is blank — so a body derived from the
listing could not be gated against the ROM we build.  Each header records its
functions' header line ranges and instruction counts so the matcher can pick
them up once their retail counterparts are identified in `boyact`/`girl_act`.

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
`.ent` (the probe itself) — no out-of-line copy of any helper, which is what
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
