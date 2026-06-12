# PObj bulk-matching campaign — session handoff prompt

Paste everything below this line into a fresh Claude Code session in /primary/dev/ico.

---

Continue the bulk byte-matching campaign for `common/src/PObj.c` (ICO PS2 decomp,
aug6 prototype = main branch, compiler ee-gcc 2.9-991111 -O2). Ignore the
decomp-match skill and the 30-stall/parking methodology for this campaign: the goal
is throughput — bounded attempts per function via parallel worker agents, not
per-function ceremony. You are the ORCHESTRATOR; do not hand-match functions
yourself except to spot-check.

## Infrastructure that already exists (verify, don't recreate blindly)

- `common/src/PObj.c` — the real TU. ~519 functions started as
  `INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", <func>);` lines.
  NEVER let a worker touch this file; only you merge into it.
- `scratch/wN/PObj.c` (N=1..8) — private worker copies of the TU.
  `asm/aug6/nonmatchings/scratch/wN/PObj` is a relative symlink to
  `../../../nonmatchings/common/src/PObj` so quick_diff resolves baselines.
  `scratch/` is in `.git/info/exclude`. To refresh for a new wave:
  `cp common/src/PObj.c scratch/wN/PObj.c` (AFTER merging the previous wave).
- `build/pobj_bulk/matched/<func>.md` — one file per matched function (decls +
  code + notes). `build/pobj_bulk/failed/<func>.md` — best attempt + residual
  diff count. These are the campaign's persistent state; they survive worker
  death and session limits.
- `build/pobj_bulk/assign_wN.txt` / `assign_wN_r2.txt` — wave-1 assignment lists
  (`<func>  (<insns> insns)` per line, smallest first).
- `decomp/bulk_campaign/merge_generic.py` (run as `python3 decomp/bulk_campaign/merge_generic.py common/src/PObj build/pobj_bulk`) — merges matched/*.md into the real
  PObj.c (replaces the INCLUDE_ASM line, dedupes decls already in the TU).
  Dry-run by default; `--apply` to write. Its decl dedupe is crude — expect to
  fix a few duplicate/conflicting externs by hand after merging.

## First: assess state

1. `ls build/pobj_bulk/matched | wc -l` and `ls build/pobj_bulk/failed | wc -l`.
2. `grep -c INCLUDE_ASM common/src/PObj.c` — how many remain unmerged.
3. Rebuild the remaining-function list with sizes:
   `grep -oP 'INCLUDE_ASM\("asm/aug6/nonmatchings/common/src/PObj", \K[A-Za-z0-9_]+' common/src/PObj.c`
   then for each, insn count = `grep -c '^\s*/\* ' asm/aug6/nonmatchings/common/src/PObj/<f>.s`.
   Exclude funcs that already have a matched/ or failed/ file.
4. `git log --oneline -3` and `git status` — make sure you start clean; baseline
   `ninja` must pass (sha1 2b4d7de4...) before you merge anything.

## The cycle (repeat until done)

### 1. Launch a wave of 8 background workers
Partition the current tier's functions round-robin into
`build/pobj_bulk/assign_wN_r<K>.txt`. Tiers, in order:
- Tier A: ≤60 insns — model **sonnet**, ~30 funcs/worker, 10 attempts/func.
- Tier B: 61–150 insns — model **opus**, ~12 funcs/worker, 10 attempts/func.
- Tier C: >150 insns — model **opus** (or inherit if you are Opus), 4–6
  funcs/worker, 12 attempts/func, tell workers to start from
  `.venv/bin/python tools/m2c_scaffold.py <func>`.
- Escalation tier: every failed/<func>.md from earlier waves — strongest model
  available, seed the worker with the best-attempt C from the failed file
  (tell it to read the file first), 12 fresh attempts.

Launch all 8 in ONE message (parallel), `run_in_background: true`. Worker prompt
template (fill in N and the list filename):

```
You are worker wN in a bulk byte-matching campaign for the ICO PS2 decompilation.
Repo root: /primary/dev/ico (run all commands from there). Target compiler:
ee-gcc 2.9-991111, -O2, MIPS r5900 (PS2 EE).

Your private scratch TU is scratch/wN/PObj.c (a copy of common/src/PObj.c; it may
already contain C for functions a previous run matched — keep those). Your assigned
function list (smallest first): build/pobj_bulk/<ASSIGN_FILE>.

For each function F in your list, in order:
1. Read its target asm: asm/aug6/nonmatchings/common/src/PObj/F.s
2. In scratch/wN/PObj.c, replace the line
   `INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", F);` with your C
   implementation. (If a previous run left a partial C attempt for F instead of
   the INCLUDE_ASM line, continue from it.) Add extern decls you need near the
   function. First grep the scratch file for the symbols involved — many
   globals/callees/structs are already declared by matched sibling functions;
   reuse them (a duplicate conflicting decl is a compile error).
3. Iterate with: VERSION=aug6 tools/quick_diff.sh scratch/wN/PObj F
   On success the output ends with `MATCH (canonical instruction stream
   identical)`. Otherwise it prints a side-by-side diff (expected | built) —
   expected is the ROM, built is yours.
4. Budget: up to 10 genuinely different attempts per function (different
   semantics/structure, not respellings). When MATCHED: write
   build/pobj_bulk/matched/F.md (format below) and continue, keeping the matched
   C in your scratch file. If still unmatched after the budget: write
   build/pobj_bulk/failed/F.md with your best C and its residual diff-line
   count, restore the exact INCLUDE_ASM line for F in the scratch file, move on.

Result file format for build/pobj_bulk/matched/F.md:

## F — MATCHED
### decls
```c
<only the decls you ADDED (not ones already in common/src/PObj.c)>
```
### code
```c
<the function definition exactly as matched>
```
### notes
<1-2 lines on what mattered>

For failed/F.md use the same shape titled `## F — FAILED (best: N diff lines)`.

Toolchain facts you need:
- C89 compiler: declarations at top of block.
- `extern int D_X;` (object ≤8 bytes) gets gp_rel addressing
  (`lw $r, %gp_rel(D_X)($28)`). If the ROM instead uses `lui %hi / %lo`,
  declare `extern int D_X[];` and access `D_X[0]`, or use a typed struct/array.
- A void function whose last action is a call gets sibcalled (`j f`). If the
  ROM shows `jal` + a stack frame instead, try int return type with
  `return f();`, or non-tail placement.
- `jal 0 <somename>` / `lui v0,0x0` symbol names in the diff are
  unresolved-reloc display noise — judge by mnemonics/registers/immediates
  only. The diff does NOT check relocations, so make sure you call/reference
  the symbols the ROM asm names.
- Branch-likely ops (beql/bnel) execute the delay slot only when taken.
- A `daddu $r,$src,$0` copy before a compare often means a short/char variable
  promoted to int across a basic-block boundary; `sll 16/sra 16` pairs mean a
  short variable converted to int at a join. Use short-typed locals there.
- A clamp written as a statement-if (`if (v < -LIM) v = -LIM;`) if-converts to
  movz/movn. If the ROM shows a branchy clamp (daddu copy + slti + bnel with
  the assignment in the delay slot + sll/sra), write it as a TERNARY with a
  (short) cast: `(short)(v < -LIM ? -LIM : v)`.
- ee-gcc emits blocks in source order: mirror the ROM's block layout with
  gotos when the structure diffs are layout-shaped.
- float constants: plain literals (1.0f) compile to lwc1 from .lit4.
- VU0 macro idioms (lqc2/sqc2/etc.): grep already-matched siblings in the
  scratch file for `VU0_` macro usage and include/vu0.h.
- For functions >80 insns, scaffold the control flow with:
  `.venv/bin/python tools/m2c_scaffold.py F` then refine.
- If quick_diff prints a compile error (e.g. from cc1), the diff/MATCH output
  may be stale — fix the error and rerun before trusting it.

Hard rules:
- NEVER edit any file outside scratch/wN/ and build/pobj_bulk/. Especially
  never touch common/src/PObj.c.
- Never run ninja, git, match_loop.py, the permuter, or build.sh.
- Work the list in order; do not skip ahead except past functions you've
  finished or recorded as failed.

Final message: one line per function you got to, `F: MATCHED` or
`F: failed (best=N)`, plus nothing else.
```

### 2. While workers run
Don't poll their transcripts. Track progress with
`ls build/pobj_bulk/matched | wc -l`. Prepare the next tier's lists. If a worker
dies (session limit, crash), its per-func results are already on disk — just
regenerate its remaining list (assigned minus matched/ minus failed/) and
relaunch it. Worker death loses nothing.

### 3. Merge after each wave
1. `python3 decomp/bulk_campaign/merge_generic.py common/src/PObj build/pobj_bulk` (dry run), then `--apply`.
2. Fix compile errors from decl conflicts (duplicate externs, a worker's
   `extern int f();` colliding with another's real definition — keep the
   definition, delete the extern).
3. Verify every merged func against the REAL TU:
   `VERSION=aug6 .venv/bin/python tools/match_diff.py common/src/PObj <func> `
   (or quick_diff) — expect real_count 0. A func that matched in scratch but
   not in the master usually has a decl-type conflict; fix or back it out to
   INCLUDE_ASM (don't block the wave on one func).
4. `ninja` — the ONLY authoritative gate (sha1 must stay 2b4d7de4...). The .o
   differ false-negatives on in-TU symbol relocs, and coalesced-TU p2align/
   trailing-nop padding can pass quick_diff but break the ELF SHA (±4/8 byte
   shifts). If ninja fails: `readelf -S` the .o, bisect by backing out merged
   funcs in halves; known fixes are explicit `__asm__("nop")` tails or
   `-malign-functions=2` per-TU flags — but try backing out the offender first
   and queue it for the escalation tier.
5. `./tools/check_no_rom.sh`, then commit the TU
   (`git add common/src/PObj.c && git commit`). Message style:
   `PObj: merge wave N — <K> functions matched`. NO AI co-author trailer (repo
   rule). Do not commit scratch/ or build/.
6. Refresh all scratch copies from the merged master before the next wave.

### 4. Stop condition
All functions have either matched (merged + ninja-verified) or have a
failed/<func>.md from the escalation tier. Then write a final summary:
counts per tier, list of unmatched stragglers with their best residual counts.

## Hazards learned the hard way
- VERSION=aug6 must be set explicitly for quick_diff/match_diff (auto-detect
  can pick retail).
- quick_diff with a still-INCLUDE_ASM func can look near-identical (the macro
  embeds ROM bytes) — a "match" for a func you haven't written C for is fake.
- A sudden marks→0 after a cc1 error is stale output; rerun.
- Session usage limits kill workers mid-run; this is routine — relaunch with
  regenerated remaining-lists. Use sonnet for Tier A to stretch the budget;
  don't use sonnet above Tier A (it burns attempts on respellings).
- merge_generic.py addresses the INCLUDE_ASM line by exact string — if a func's
  line is already replaced, it reports "already merged" and skips; that's fine.
