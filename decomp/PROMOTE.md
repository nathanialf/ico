# TU promotion prompt — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude Code
session) to launch a TU-promotion session — consolidating per-function
`src/cod/<offset>.c` files into per-TU files at the original ICO
source-tree paths (`src/Basic.c`, `src/ios/cdvd.c`, etc.) while keeping
`build/ico.rom` byte-identical to `baserom/baseelf.rom`.

This is structural / refactor work, not new matching. The matching loop
(`decomp/MATCH.md`) drives function bytes to match; this loop folds those
matched functions into TU-named files mirroring the recovered original
tree under `decomp/source_tree/`.

---

Continue the **ICO** clean-room decomp at `/primary/dev/ico`. Working
directive: **promote fully-matched per-function `src/cod/<offset>.c`
files into per-TU files at `src/<tu_path>.c`**, mirroring the original
ICO source tree recovered under `decomp/source_tree/`. Same clean-room
rules — no disc data, no extracted assets, no leaked-source-derived code,
no AI co-author trailer on commits.

## Do not stop promoting

**Run until the Claude usage cap stops you, or until the user explicitly
tells you to stop.** The only acceptable end-of-stream is the cap, an
exhaustion of viable TUs, or a direct user instruction. Routine failures
(scheduler diffs, type collisions, etc.) get held out + parked, not
escalated to "stop".

## The hard contract (never violate)

- `make` must end with
  `verify_elf: OK (build/ico.rom sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.
- **Never edit `config/sha1sums.txt`.** A SHA-1 mismatch means the bytes
  diverged — fix the bytes.
- **Never disrupt active matching.** If `find asm/cod -name '*.s' | wc -l`
  returns 0, the matching loop is mid-cycle and is about to repopulate
  `asm/cod/*.s` via `rm + make setup`. Wait, then retry. Don't run
  `make setup` while the matching loop is running unless the user has
  explicitly paused it.
- Don't commit anything under `asm/`, `assets/`, `build/`, `baserom/`,
  or anything from leaked SDKs / leaked source / pirated debug builds.
- Don't add an AI co-author trailer to commits.
- **Don't coalesce the giant TUs yet.** `decomp/tu_map.json`'s largest
  original TUs by function count are off-limits for whole-TU promotion
  until matching tooling can handle the iteration cost: every match
  attempt against a typed `src/<TU>.c` recompiles the whole TU, and a
  558-func TU would dominate the matching loop. Treat these as
  per-func asm subsegs only:

  | funcs | TU |
  | ---: | --- |
  | 558 | `src/way_tool.c` |
  | 410 | `src/PObj.c` |
  | 217 | `src/commonact.c` (partial promotion already at `[0x0683A8, c, src/commonact]` — don't expand) |
  | 121 | `src/motionManager.c` |

  Promote *named slices* (tight shape-buckets of adjacent functions) into
  the typed TU while leaving the rest as `INCLUDE_ASM` neighbours, the
  way `src/commonact` does. Don't lift a giant whole. See
  `decomp/NOTES.md` § "`main` location and the don't-coalesce-the-giants-yet rule"
  for the full rationale.

## Read these first (in order)

1. `CLAUDE.md` — project preamble.
2. `decomp/NOTES.md` — every PS2/EE/splat/linker quirk that has bitten
   matching work. The "Build-environment fingerprint" and "Compiler
   fingerprint (resolved)" sections matter. This file is authoritative
   for "why doesn't X match".
3. `decomp/source_tree.md` — the original-tree recovery method, the
   TU-mapping pipeline, and the workflow for analyzers + snapshot.
4. `decomp/source_tree/` — 96 placeholders representing the original
   ICO source-tree files we want to populate.
5. `decomp/tu_map.json` — sidecar listing every function with its
   inferred TU. **Authoritative input.**
6. `decomp/unnamed_tus.md` — slice-by-slice TU classification.
7. `config/ico.us.yaml` — splat config; this is what you'll edit.
8. **The worked example.** Re-read these three before starting:
   - `src/Basic.c` — the canonical pattern (4 funcs C + 1 INCLUDE_ASM).
   - `tough_nuts/func_001F6E00/notes.md` — the held-out function and
     why combining it broke the schedule.
   - YAML lines around offset `0x0F6CB0` (`grep -n "0F6CB0\|0F6E00"
     config/ico.us.yaml`) — the before/after subseg shape.
   Every promotion should look like this.

## Definitions

- **TU** — a translation unit; one original `.c` file in the recovered
  source tree (`src/Basic.c`, `ios/cdvd.c`, `sound/s_init.c`, etc.).
  Listed in `decomp/source_tree/`.
- **TU member** — a function tagged with that TU in
  `decomp/tu_map.json`.
- **Fully-matched TU** — every member has a `src/cod/<offset>.c` and
  `asm/matchings/cod/<offset>/func_*.s`. Cleanest to promote — no
  `INCLUDE_ASM` needed.
- **Mixed TU** — some matched, some not. Use `INCLUDE_ASM` for the
  unmatched.
- **Promotion target path** — literal `src/<rest_of_tu_path>`:
  `src/Basic.c`, `src/ios/cdvd.c`, `src/sound/s_init.c`. The
  `decomp/source_tree/` skeleton just shows the layout; the actual file
  lives at `src/<...>` because splat's `src_path: src`.

## Procedure

### Step 0 — refresh the TU map (only if stale)

If recent matching activity has substantially changed `asm/matchings/`
or `asm/nonmatchings/` since `decomp/tu_map.json` was last written,
refresh — iterate `build_data_tu_map` ↔ `identify_tus` to fixpoint
(typically 2–3 rounds):

```sh
.venv/bin/python tools/snapshot_asm.py
.venv/bin/python tools/find_callgraph.py
.venv/bin/python tools/find_vtables.py
.venv/bin/python tools/find_boundaries.py
.venv/bin/python tools/build_data_tu_map.py
.venv/bin/python tools/identify_tus.py
.venv/bin/python tools/build_data_tu_map.py
.venv/bin/python tools/identify_tus.py
.venv/bin/python tools/find_unnamed_tus.py
```

`snapshot_asm.py` mirrors `asm/src/cod/`, `asm/matchings/` (whole tree),
and `asm/nonmatchings/` (whole tree) into `decomp/asm_snapshot/`. If
`asm/src/cod/` is empty the matching loop is mid-cycle — the script
keeps the previous cod snapshot but still refreshes matchings +
nonmatchings.

The strongest signal in the refreshed map is **`path`** — when a
function's `.s` file lives in a per-TU subdir (e.g.
`asm/nonmatchings/src/way_tool/`), splat's YAML explicitly assigned
it. See `decomp/NOTES.md` §"TU identification pipeline" for the
full source precedence (path > anchor > bracket > vtable > callgraph
> data > revcg > slice_vote > bracket_inferred).

Tag-source breakdown for a TU: `tools/tu_status.py --tag-sources`.

If artifacts look fresh enough, skip this step.

### Step 1 — pick a target TU

Prefer in this order:

1. Fully-matched TUs (no INCLUDE_ASM) — cleanest.
2. Mixed TUs with high match% — most leverage with manageable risk.
3. Smaller TUs (≤10 functions) before larger ones.

Skip:

- TUs with `span > ~0x10000` — likely non-contiguous (multiple TUs
  sharing a name due to inlining); needs manual review.
- TUs flagged in `decomp/unnamed_tus.md` "Multi-TU slices (review)" —
  `.c.inc` inlining requires bespoke handling.

Enumerate candidates (`matchings/` is now the whole tree, not just
`matchings/cod/` — recursive glob picks up per-TU subdirs like
`matchings/Basic/`, `matchings/src/Texture/`):

```python
.venv/bin/python << 'PY'
import json, re
from pathlib import Path
from collections import defaultdict
tu_map = json.load(open("decomp/tu_map.json"))
matched = set()
for p in Path("decomp/asm_snapshot/matchings").rglob("func_*.s"):
    m = re.match(r"func_([0-9A-Fa-f]+)\.s", p.name)
    if m: matched.add(int(m.group(1), 16))
by_tu = defaultdict(list)
for f in tu_map:
    if f.get("tu"): by_tu[f["tu"]].append(f)
for tu, fs in sorted(by_tu.items(), key=lambda kv: len(kv[1])):
    fs.sort(key=lambda f: f["vram"])
    n_matched = sum(1 for f in fs if f["vram"] in matched)
    span = fs[-1]["vram"] - fs[0]["vram"]
    print(f"{tu:<35} funcs={len(fs):>3} matched={n_matched:>3}/{len(fs):>3} span=0x{span:x}")
PY
```

### Step 2 — gather the TU's scope

For each member function, record:

- vram, file_off (`vram - 0x100000`), name.
- Is `src/cod/<file_off>.c` present (matched) or `asm/cod/<file_off>.s`
  (unmatched)?
- The YAML subseg line: `grep -n "0x<file_off>" config/ico.us.yaml`.
- Any entry in `config/extra_cflags.txt` for that file_off.

If any function has a per-file CFLAG override, **hold that function out**
as a separate subseg (Failure mode A pattern). Combining loses the
per-function flag and won't match.

### Step 3 — write the consolidated TU file

Path: `src/<rest_of_tu_path>` — e.g. `src/Basic.c`, `src/ios/cdvd.c`.

Order functions by vram (matches the original `.text` link order). For
each member:

- **Matched**: copy the body verbatim from `src/cod/<file_off>.c`,
  stripping its top-of-file `#include "matching.h"` if duplicated.
- **Unmatched**: emit
  `INCLUDE_ASM("asm/nonmatchings/<TU_SUBSEG_NAME>", func_<VRAM>);`.
  **Note the path:** splat drops the `cod/` segment prefix in the
  nonmatchings tree, so for subseg `Basic` the path is
  `asm/nonmatchings/Basic`, not `asm/nonmatchings/cod/Basic`.
- **Synthetic single-`nop` "functions"** (size 0x4, body is one `nop`):
  do *not* include them. They are linker alignment padding; the
  assembler regenerates them from `.p2align 3` between functions.

`INCLUDE_ASM` lines must appear at the **vram position** of the
unmatched function relative to its siblings — declared in source order.
Putting `INCLUDE_ASM` in the wrong place breaks the function layout.

Top of the file (in order):

1. **Anchor provenance comment** — copy the one-line comment from the
   matching skeleton placeholder at `decomp/source_tree/<tu_path>`.
   Format: `/* <tu_path> — __FILE__ anchor at .rodata 0x<vma> */`.
   This records where the original `__FILE__` literal sits in `.rodata`,
   so future readers can verify the TU identity. Read the placeholder:
   `cat decomp/source_tree/<tu_path>` — it's a one-liner.
2. `#include "matching.h"`
3. `#include "include_asm.h"` (only if any `INCLUDE_ASM` is used)
4. `#include "regpin.h"` (only if any function body uses the `REG()`
   macro for register pinning)
5. **Rodata typed defs** — every `.rodata.0x...` symbol owned by this
   TU, with its `__attribute__((section(...)))` section attribute.
   These live directly in the TU's `.c` — **do not create a private
   `.h`**. Per-TU headers are not part of the original source layout;
   the only sanctioned `.h` files are those listed in
   `decomp/source_tree/include/`. See
   `decomp/header_candidates.md` for the migration history.
6. **Extern declarations** — union of externs from all source `.c`
   files, deduplicated. Match types exactly; don't introduce
   broader/narrower types than the originals had. Externs for:
   - `.sdata` / `.lit4` / `.data` / `.bss` / `.sbss` symbols owned
     by this TU (those definitions stay in the auto-generated
     `<TU>_data.c` sidecar — `feedback_lit4_gp_rel` requires they
     live outside the `INCLUDE_ASM`-containing TU)
   - Cross-TU rodata symbols (the *other* TU defines those)
   - Cross-TU function pointers

Example top-of-file (matches `src/Basic.c` style):

```c
/* src/Basic.c — __FILE__ anchor at .rodata 0x0061a8a8 */

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

__attribute__((section(".rodata.0x0061A890"))) char D_0061A890[24] = "set partition first!\n";
__attribute__((section(".rodata.0x0061A8A8"))) char D_0061A8A8[24] = "src/Basic.c";

extern int   D_00633780;          /* in <TU>_data.c sidecar — .sdata */
extern int   D_00633788[];        /* in <TU>_data.c sidecar — .sbss */
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_001A6E28(char *p);
// …
```

For TUs with `INCLUDE_ASM`, see `src/EnemyInit.c` and
`src/act-parallel-control.c` as references — same top-of-file
pattern, then `INCLUDE_ASM(...)` lines in vram order alongside
matched C bodies.

The skeleton placeholder under `decomp/source_tree/<tu_path>` stays
in place after promotion — it remains the master record of the
recovered tree layout and the anchor table. Status markers in the
placeholder (`complete` / `partial` / `partial+data-sidecar` /
`coalesced` / `unstarted`) are auto-updated by
`tools/build_source_tree.py`.

### Step 4 — update the YAML

Replace every per-function subseg line within the TU's vram range with
**one** TU-level line:

```yaml
- [0x<FILE_OFF_OF_TU_START>, c, <tu_subseg_name>]
```

`<tu_subseg_name>` mapping:

- `src/Basic.c` → `Basic`
- `src/ios/cdvd.c` → `ios/cdvd` (slash-separated; splat handles the path
  mapping)
- `src/sound/s_init.c` → `sound/s_init`

Preserve the YAML line for the *next* subseg after the TU — that's the
boundary marker. Don't extend the TU's subseg into the next TU's range.

### Step 5 — delete orphans

```sh
# Per-function matched .c files (now consolidated into the TU file):
rm src/cod/<file_off>.c

# Per-function asm files for unmatched funcs (will reappear under
# asm/nonmatchings/<TU>/):
rm asm/cod/<file_off>.s
```

Splat regenerates `asm/nonmatchings/<TU_SUBSEG>/func_<vram>.s` on the
next `make setup`.

### Step 6 — build and verify

```sh
make setup
make
```

Expected:
`verify_elf: OK (build/ico.rom sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.

### Step 7 — handle failure modes

If `make` fails the SHA-1 check, locate the diff:

```sh
.venv/bin/python -c "
with open('baserom/baseelf.rom','rb') as f: base=f.read()
with open('build/ico.rom','rb') as f: built=f.read()
diffs = [i for i in range(min(len(base),len(built))) if base[i] != built[i]]
print('first 10 diff offsets:', [hex(d) for d in diffs[:10]])
print('total bytes differ:', len(diffs))
"
```

Map diff offsets to functions; then apply the appropriate fix.

**Failure mode A — scheduler interaction (sibling-fn context shift).**

Symptom: a previously-matching function now reorders 2 instructions when
compiled with siblings. Same compiler `.s` output, different bytes after
`as`. Saw this with `func_001F6E00` in the Basic.c PoC — see
`tough_nuts/func_001F6E00/notes.md`.

Fix:

1. Hold the function out as its own subseg. Update the TU YAML to a
   smaller range and add a held-out line:
   ```yaml
   - [0x<TU_START>, c, <tu_name>]                       # TU minus the holdout
   - [0x<HELDOUT_FILE_OFF>, c, cod/<HELDOUT_FILE_OFF>]   # held out: schedule sensitive
   ```
2. Recreate `src/cod/<heldout_file_off>.c` from the original
   (`git show HEAD:src/cod/<file_off>.c > src/cod/<file_off>.c`).
3. Park the held-out function in `tough_nuts/func_<vram>/` with
   `notes.md` documenting:
   - what fails (the diff from the verify step),
   - which TU the function belongs to,
   - the seed C body (the matching standalone version).

   `tools/auto_permute.sh` will pick up the parked seed and try to find
   a TU-context-compatible body.

**Failure mode B — extern type collision.**

Symptom: `error: conflicting types for 'D_xxxx'` when compiling.

Fix: dedupe extern declarations in the consolidated file. If the same
symbol was declared with different types in different `src/cod/*.c`,
pick the type that produces matching codegen for the largest number of
call-sites, and adjust the others to match.

**Failure mode C — INCLUDE_ASM path wrong.**

Symptom: `as: ... cannot open` or assembler errors during compilation.

Fix: confirm path is `asm/nonmatchings/<tu_subseg_name>`, NOT
`asm/nonmatchings/cod/<tu_subseg_name>`. Splat drops the `cod/` segment
prefix.

**Failure mode D — rodata/jumptable disagreement.**

Symptom: SHA-1 mismatch in `.rodata` (file_off > ~0x453000).

Fix: rodata migration is automatic per `migrate_rodata_to_functions:
True`, but if a function's jumptable was emitted differently after
consolidation, you'll see it here. Hold the offending function out
(Failure mode A pattern).

**If 3–4 attempts fail to fix the same TU**: revert the entire
promotion (restore YAML, restore `src/cod/*.c` and `asm/cod/*.s` from
git, delete the new TU file). Document the obstacle in
`tough_nuts/tu_promotion_<tu_name>/notes.md`. Move to the next TU.

### Step 8 — record progress and continue

After each successful promotion:

- Re-run `tools/identify_tus.py` and `tools/find_unnamed_tus.py` to
  refresh the TU map (cheap; no snapshot needed).
- Move to the next TU. **Do not stop.**

## Stop conditions

- Claude usage cap reached.
- User explicitly says stop.
- All viable TUs have been promoted (i.e., remaining candidates are all
  span > 0x10000 multi-TU regions, or already-promoted, or every
  remaining TU has fewer than 2 matched members so consolidation has
  no leverage).
- Three consecutive promotion attempts on different TUs failed in the
  same way (likely a systemic issue worth pausing for).

## Reporting

When you stop, output a short summary:

```
Promoted N TUs:
  - src/Basic.c (4 funcs C + 1 INCLUDE_ASM, 1 held out)
  - src/ios/cdvd.c (12 funcs C, 7 unmatched INCLUDE_ASM)
  - ...
Held out / parked:
  - func_001F6E00 (TU=src/Basic.c, scheduler interaction)
  - ...
Failed / reverted:
  - src/<tu_name> — <reason>
SHA-1 final: fbf50c75... ✓
```

## Final reminder

Re-read `src/Basic.c`, `tough_nuts/func_001F6E00/notes.md`, and the
relevant YAML lines before you start. That file pair is the canonical
worked example — every promotion should look like it.
