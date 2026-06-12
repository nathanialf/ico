# Generic TU bulk-matching campaign — session handoff prompt

Fill in the two parameters, then paste everything below the `---` into a fresh
Claude Code session in /primary/dev/ico.

- **TU** = dev-tree stem of the target, e.g. `common/src/GobjProc`,
  `seki/src/displaylist`, `ito/src/act_bird` (the .c lives at `<TU>.c`,
  the asm baselines at `asm/aug6/nonmatchings/<TU>/`).
- **BASE** = basename of TU (e.g. `GobjProc`) — used for scratch/result dirs so
  campaigns for different TUs don't collide.

---

Run a bulk byte-matching campaign for `<TU>.c` (ICO PS2 decomp, aug6 prototype =
main branch, compiler ee-gcc 2.9-991111 -O2). Ignore the decomp-match skill and
the 30-stall/parking methodology: the goal is throughput — bounded attempts per
function via parallel background worker agents. You are the ORCHESTRATOR; do not
hand-match functions yourself except to spot-check.

## Per-TU preflight (PObj needed none of these; other TUs may)

1. `grep -c INCLUDE_ASM <TU>.c` — confirm there's enough unmatched work.
2. Per-file build config — each hit changes the plan:
   - `grep -E '(^|/)<BASE>(\.|\b)' config/extra_cflags.txt` — if the TU has
     extra cflags keyed by FULL path, quick_diff on a scratch copy will miss
     them (its lookup uses the C source path). Basename-keyed entries are fine.
   - `grep <BASE> config/*.txt | grep -v symbol_addrs` — postprocess allowlists
     (swap_addu, fcc_nop, use_old_as, early_epilogue...) are dual-keyed and
     basename entries apply to scratch copies; full-path-only entries do not.
   - `grep -x <BASE> config/include_ito.txt` — ito-include TUs compile from a
     different CWD for `__FILE__` literals; quick_diff handles this by basename,
     so scratch copies named `scratch/<BASE>-wN/<BASE>.c` keep working.
3. Encoding: some TUs are EUC-JP — use `grep -a` when grepping them.
4. `/* Handwritten function */` markers in the asm: match via include/r5900.h
   intrinsics (SYNC(), EI(), DI(), VU0 macros), never skip, never raw .word
   first.
5. Author idioms: check decomp/PROGRAMMERS.md for the directory's programmer
   and skim 2-3 already-matched functions in the same TU for house style.

## Infrastructure setup (idempotent)

```sh
echo 'scratch/' >> .git/info/exclude   # if not already there
mkdir -p build/bulk/<BASE>/{matched,failed}
for i in 1 2 3 4 5 6 7 8; do
  mkdir -p scratch/<BASE>-w$i asm/aug6/nonmatchings/scratch/<BASE>-w$i
  cp <TU>.c scratch/<BASE>-w$i/<BASE>.c
  ln -sfn $(python3 -c "import os;print(os.path.relpath('asm/aug6/nonmatchings/<TU>','asm/aug6/nonmatchings/scratch/<BASE>-w$i'))") \
      asm/aug6/nonmatchings/scratch/<BASE>-w$i/<BASE>
done
```
Sanity-check one worker before launching the fleet:
`VERSION=aug6 tools/quick_diff.sh scratch/<BASE>-w1/<BASE> <some_unmatched_func>`
must print a diff (not an asm-resolution error). Also hand-match the single
smallest function yourself end-to-end once — it validates the whole pipeline
and calibrates difficulty.

## Function inventory

```sh
grep -oP 'INCLUDE_ASM\("asm/aug6/nonmatchings/<TU>", \K[A-Za-z0-9_]+' <TU>.c
```
Size each by `grep -c '^\s*/\* ' asm/aug6/nonmatchings/<TU>/<f>.s`. Exclude
funcs that already have a `build/bulk/<BASE>/matched/<f>.md` or `failed/<f>.md`.

## The cycle (repeat until done)

### 1. Launch a wave of 8 background workers
Partition the current tier round-robin into `build/bulk/<BASE>/assign_wN_r<K>.txt`
(lines: `<func>  (<insns> insns)`, smallest first). Tiers in order:
- Tier A: ≤60 insns — model **sonnet**, ~30 funcs/worker, 10 attempts/func.
- Tier B: 61–150 insns — model **opus**, ~12 funcs/worker, 10 attempts/func.
- Tier C: >150 insns — model **opus** or stronger, 4–6 funcs/worker, 12
  attempts/func, start from `.venv/bin/python tools/m2c_scaffold.py <func>`.
- Escalation: every failed/<func>.md — strongest model, worker reads the failed
  file first and continues from its best attempt, 12 fresh attempts.

Launch all 8 in ONE message, `run_in_background: true`. Worker prompt template
(substitute N, <ASSIGN_FILE>, and the TU/BASE strings):

```
You are worker wN in a bulk byte-matching campaign for the ICO PS2
decompilation. Repo root: /primary/dev/ico (run all commands from there).
Target compiler: ee-gcc 2.9-991111, -O2, MIPS r5900 (PS2 EE).

Your private scratch TU is scratch/<BASE>-wN/<BASE>.c (a copy of <TU>.c; it may
already contain C for functions a previous run matched — keep those). Your
assigned function list (smallest first): build/bulk/<BASE>/<ASSIGN_FILE>.

For each function F in your list, in order:
1. Read its target asm: asm/aug6/nonmatchings/<TU>/F.s
2. In scratch/<BASE>-wN/<BASE>.c, replace the line
   `INCLUDE_ASM("asm/aug6/nonmatchings/<TU>", F);` with your C implementation.
   (If a previous run left a partial C attempt for F instead of the INCLUDE_ASM
   line, continue from it.) Add extern decls you need near the function. First
   grep the scratch file for the symbols involved — many globals/callees/
   structs are already declared by matched sibling functions; reuse them (a
   duplicate conflicting decl is a compile error).
3. Iterate with: VERSION=aug6 tools/quick_diff.sh scratch/<BASE>-wN/<BASE> F
   On success the output ends with `MATCH (canonical instruction stream
   identical)`. Otherwise it prints a side-by-side diff (expected | built) —
   expected is the ROM, built is yours.
4. Budget: up to 10 genuinely different attempts per function (different
   semantics/structure, not respellings). When MATCHED: write
   build/bulk/<BASE>/matched/F.md (format below) and continue, keeping the
   matched C in your scratch file. If still unmatched after the budget: write
   build/bulk/<BASE>/failed/F.md with your best C and its residual diff-line
   count, restore the exact INCLUDE_ASM line for F in the scratch file, move on.

Result file format for build/bulk/<BASE>/matched/F.md:

## F — MATCHED
### decls
```c
<only the decls you ADDED (not ones already in <TU>.c)>
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
- VU0 macro idioms (lqc2/sqc2/etc.): grep already-matched siblings for `VU0_`
  macro usage and include/vu0.h. `/* Handwritten function */` markers: use
  include/r5900.h intrinsics (SYNC(), EI(), DI()).
- For functions >80 insns, scaffold the control flow with:
  `.venv/bin/python tools/m2c_scaffold.py F` then refine.
- If quick_diff prints a compile error (e.g. from cc1), the diff/MATCH output
  may be stale — fix the error and rerun before trusting it.

Hard rules:
- NEVER edit any file outside scratch/<BASE>-wN/ and build/bulk/<BASE>/.
  Especially never touch <TU>.c.
- Never run ninja, git, match_loop.py, the permuter, or build.sh.
- Work the list in order; do not skip ahead except past functions you've
  finished or recorded as failed.

Final message: one line per function you got to, `F: MATCHED` or
`F: failed (best=N)`, plus nothing else.
```

### 2. While workers run
Don't poll transcripts; track `ls build/bulk/<BASE>/matched | wc -l`. Prepare
the next tier. A dead worker (usage limit, crash) loses nothing — regenerate
its remaining list (assigned − matched − failed) and relaunch.

### 3. Merge after each wave
1. `python3 decomp/bulk_campaign/merge_generic.py <TU> build/bulk/<BASE>` (dry run),
   then with `--apply`.
2. Fix decl conflicts (duplicate externs; an extern colliding with another
   worker's real definition — keep the definition).
3. Verify every merged func against the REAL TU:
   `VERSION=aug6 .venv/bin/python tools/match_diff.py <TU> <func>` → real_count
   0. A scratch-matched func that fails in master usually has a decl-type
   conflict; fix or back out to INCLUDE_ASM — don't block the wave.
4. `ninja` — the ONLY authoritative gate (sha1 must stay
   2b4d7de41966ff38d061b4c985de45fc212e2fb2). The .o differ false-negatives on
   in-TU symbol relocs; coalesced-TU p2align/trailing-nop padding can pass
   quick_diff but shift the ELF by ±4/8. If ninja fails: bisect by backing out
   merged funcs in halves; known fixes are an explicit `__asm__("nop")` tail or
   `-malign-functions=2` per-TU — but back out the offender first and queue it
   for escalation.
5. `./tools/check_no_rom.sh`, commit ONLY `<TU>.c`:
   `<BASE>: merge wave N — <K> functions matched`. NO AI co-author trailer
   (repo rule). Never commit scratch/ or build/.
6. Refresh all scratch copies from the merged master before the next wave.

### 4. Stop condition
Every function either merged+ninja-verified or has an escalation-tier
failed/<func>.md. Write a final summary: counts per tier, stragglers with
residual counts.

## Hazards (learned on the PObj campaign)
- VERSION=aug6 must be explicit for quick_diff/match_diff (auto-detect can pick
  retail).
- quick_diff against a still-INCLUDE_ASM func looks near-identical (the macro
  embeds ROM bytes) — a "match" for a func with no C yet is fake.
- A sudden 0-diff right after a cc1 error is stale output; rerun.
- Session usage limits kill workers mid-run; routine — relaunch on regenerated
  lists. Sonnet only for Tier A.
- Don't run two campaigns against the SAME TU concurrently; different TUs are
  fine (dirs are namespaced by BASE).
