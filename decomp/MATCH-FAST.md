# Matching prompt (fast pass) — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude Code
session) to launch a **shape-batched, park-early** matching session.

---

Continue the **ICO** clean-room decomp at `/primary/dev/ico`. Working
directive: match as many ELF functions as possible by **plowing buckets
of similar shapes**, parking near-misses early, and trusting the
auto-permuter to recoup parked seeds in the background. Same clean-room
rules as before — no disc data, no extracted assets, no
leaked-source-derived code, no AI co-author trailer on commits.

## The doctrine: park early, batch by shape, trust the permuter

The matching loop has two timescales:

1. **Foreground (this session):** plow buckets fast. Land the easy
   wins. The 1–2% you leave on the table from parked near-misses today
   gets harvested later for free by `tools/auto_permute.sh` running on
   the parked seeds.
2. **Background (between sessions):** the auto-permuter mutates parked
   `tough_nuts/<func>/` seeds against `target.s` until it lands a
   score-0 hit. Future sessions just promote those.

So the right move on a near-miss is **park it now, move on**. Do not
spend 30 minutes chasing a regalloc swap or a delay-slot reorder when
that same minute could clear three other entries in the same shape
bucket. The permuter will do the chasing while you sleep.

**Specific banned anti-patterns** (these waste foreground time):

- Iterating on a single near-miss for more than ~3 attempts. Park.
- Reading `decomp/NOTES.md` for "the right idiom" on a function that
  ee-gcc emits in 9 instructions when expected has 12. Park — let the
  permuter find the missing 3-insn shape.
- Writing increasingly elaborate `volatile` / `do {…} while (0)` /
  `&x` tricks past attempt 2. Park.
- Solo-targeting a single function from `docs/candidates.md`. Always
  pull a **batch** (the bucket the function belongs to plus its
  shape-siblings).

## Do not stop matching

**Run until the Claude usage cap stops you, or until the user explicitly
tells you to stop.** Same rule as `decomp/MATCH.md`. The fast-pass
doctrine *is* the way to keep moving — every park frees you to start the
next batch.

When in doubt, the answer is always: re-scan `docs/candidates.md` for
the next-largest bucket, write template C bodies for every entry in it,
batch-claim them all, run `rm asm/cod/*.s && make setup && make`,
park the failures, commit the matches, repeat.

### Cron firings are heartbeats, not session boundaries

If you are reading this prompt because a `/loop 30m decomp/MATCH-FAST.md
unsupervised` cron just fired, **do not treat it as a fresh session**.
Do not write a "session summary," do not list what you matched last
round, do not yield. Just continue from current state: scan
`docs/candidates.md`, pick the next bucket, batch-claim, build, commit,
repeat. The cron is a heartbeat that keeps the conversation alive — not
a checkpoint that demands a recap.

The only signals that mean *stop*:
- The user types something explicitly ending the loop ("stop", "pause",
  "that's enough", a different task).
- You hit the usage cap (the harness will surface it).
- `docs/candidates.md` has zero non-empty buckets AND no unbucketed
  functions worth surfacing — even then, edit `tools/gen_candidates.py`
  to add a new sub-shape bucket before yielding.

Between batches, do not summarize. Just go.

### Forbidden closing-summary phrasing

The cron-firing handoff has a recurring bug pattern: a closing line that
*reads* as a stop signal even when the agent intends to keep going. Do
not write any of these at the end of a turn:

- "Yielding."
- "**This firing: N matches, M parks.**"
- "Cron continues." / "Cron will fire next."
- "Cumulative session totals: …" / "Direct matches in this session: N"
- "1.X% .text. Continuing to wait for next cron fire."
- Any bold-summary block that reads like a per-firing recap.

Mid-stream status notes ("matched func_X", "parking func_Y, regalloc
swap", "moving to bucket Z") are fine — they describe what *just*
happened. What's not fine is the closing-line pattern that signals
"this firing is done" — there is no "this firing." There is one
continuous matching session, and you keep going until cap or user stop.

## Read first (in this order)

1. `CLAUDE.md` — IP rules, toolchain, build commands, conventions.
2. `decomp/NOTES.md` — PS2 EE / compiler / splat / linker quirks
   catalogued so far. **Skim, don't memorize.** The fast-pass loop
   doesn't need every quirk; it parks anything subtle.
3. `docs/candidates.md` — the bucketed unmatched-function shortlist.
   Every section has a header like `_N total in this bucket; showing
   top N._`. **Pick the largest non-empty bucket** and pull the whole
   thing. (The buckets are auto-derived; you can also tweak the bucket
   definitions in `tools/gen_candidates.py` to surface more shapes if
   the existing ones are exhausted.)
4. `docs/MATCHING_NOTES.md` — per-function tough-nuts and deferred
   targets.
5. `docs/LEGAL.md` — clean-room boundary; what's allowed as a reference,
   what's forbidden as an input.

## The fast-pass loop

Five steps. Repeat until cap or user stop.

### 1. Pick a bucket

Open `docs/candidates.md`. Pick the largest bucket with ≥4 entries
that share a tight first-mnemonics prefix. Good targets, in order:

- `wrap-1jal-0x28-0x30` / `wrap-1jal-0x34-0x40` — sub-cluster by
  callee (`grep "jal func_X" inside the bucket`).
- `cond-deref-leaf` — leaf branch shapes; very cheap to template.
- `wrap-2jal-0x18-0x24` / `wrap-2jal-0x28-0x40` — small 2-call
  wrappers.
- `wrap-gp-1jal` (122+ entries) — wide and heterogeneous; sub-cluster
  by mnemonic prefix (e.g. `addiu lw sd sd`, `addiu sd jal nop`,
  `lui addiu addiu sw`).

If every bucket is empty or down to single-entry shapes, **edit
`tools/gen_candidates.py`** to add a new bucket definition (different
size band, different jal count, different mnemonic prefix) and
regenerate. There are always more sub-shapes worth surfacing.

### 2. Inspect the cluster's asm in one shot

Don't single-step through functions. Dump them all to `/tmp/cluster.txt`
and read once:

```sh
for fn in func_AAAA func_BBBB func_CCCC ...; do
  loc=$(grep -l "glabel $fn\$" asm/cod/*.s | head -1)
  echo "=== $fn ==="
  awk -v fn="$fn" '$0 ~ "^glabel " fn "$" {f=1} f; f && /^endlabel/{exit}' "$loc"
done > /tmp/cluster.txt
```

You're looking for **one templated C shape per arity**. If the cluster
has 8 entries but 5 distinct shapes, that's not really a cluster —
keep just the 4–5 entries that share an arity and shape.

### 3. Write a templated TOML manifest

Per the `match_batching` memory, batch-claim via
`tools/claim.py batch --manifest <path>.toml`. Include:

- `#include "matching.h"` if you need `DEFEAT_TCO()` (almost always
  for 1-jal wrappers — ee-gcc 2.9 hardcodes sibling-call opt at -O2).
- Declare the callee with the **right return type** even if other
  files declare it differently. The linker resolves by name, not type.
- C89 only: ee-gcc 2.9 rejects mid-block declarations. Declare all
  locals at the top of each block.

### 4. Build, classify, park

```sh
rm asm/cod/*.s && make setup && make
```

If SHA-1 OK on first try, commit the whole batch with one message
("Match N <shape> wrappers for func_X").

If MISMATCH:

1. **Check sizes first.** A `.c` that compiles smaller than the splat
   slot causes a cascading shift that fails everything downstream.
   Disassemble each new `.o` and confirm size against `candidates.md`.
   Any size mismatch → revert that one entry to `asm` in yaml, **park
   it via `tools/park.sh <vram> <reason>`**, rebuild.
2. **Locate the function-level diffs.** Use the python snippet:
   ```py
   diffs = [i for i in range(len(base)) if base[i] != built[i]]
   # group by 0x40 windows; print vram of each range
   ```
   then `mips-linux-gnu-objdump -d` both ELFs at each range.
3. **For each diffing function:** try at most ONE quick fix (typical
   cheap fixes: `&&` instead of two `if`s, branch-direction inversion,
   reordered local declarations). If still diff after one attempt,
   **park it.** Do not iterate further.

### 5. Commit and loop

Three commit shapes:

- `Match N <shape> wrappers — <one-line description>` for clean
  bucket-batch matches.
- `Match func_X — <description>` for individual one-off matches.
- `Park func_X — <reason>` for parked near-misses (one per commit;
  the reason is structured "<shape>: <ee-gcc behavior> vs <expected
  behavior>" so the auto-permuter's seed has context).

Then immediately scan `docs/candidates.md` again and pick the next
bucket. **No "iteration results" / "session summary" text.** No
trailing `grep '\.text' docs/PROGRESS.md` ritual. Just keep going.

## Score-0 promotion sweep (every ~5 buckets)

The auto-permuter writes solutions to
`lib/decomp-permuter/runs/<func>/output-0-N/source.c` (N >= 1). When
score is 0, that's a real match the auto-promotion path may have
missed.

Every few buckets, sweep:

```sh
for fn in $(ls tough_nuts/ | grep '^func_'); do
  for s in lib/decomp-permuter/runs/$fn/output-0-*/score.txt; do
    [ -f "$s" ] && [ "$(cat "$s")" = "0" ] && \
      [[ "$s" != *output-0-base* ]] && echo "PROMOTABLE: $fn"
  done
done | sort -u
```

Promote promotable hits (copy `output-0-N/source.c` to `src/cod/<off>.c`,
flip yaml entry from `asm` to `c`, `rm -rf tough_nuts/<func>`,
`rm asm/cod/*.s && make setup && make`, commit).

**Caveat:** `output-0-base` score 0 does NOT mean the seed matches
(see `feedback_score0_promotion.md`). Only `output-0-N` (N >= 1).

## Toolkit reference

**Inner loop:**
- `tools/claim.py batch --manifest <toml>` — batch-claim functions.
  Manifest is `[[claim]] vram = ... size = ... comment = "..." body
  = """..."""`.
- `tools/quick_diff.sh <name>` — fast single-function diff before full
  make. Note: `daddu | or` diffs are a **false positive** (NOTES.md:549);
  always confirm with `make` before parking on that alone.
- `rm asm/cod/*.s && make setup` — nuclear orphan-asm clean (per
  `match_batching` memory). Required after every batch claim.
- `tools/park.sh <vram> "<reason>"` — park a near-miss. **Always use
  this** instead of revert+delete (per `park_failed_matches` memory).

**Triage / first-diff:**
- `cmp -l baserom/baseelf.rom build/ico.rom | wc -l` — diff byte
  count.
- `tools/first_diff.py` — symbolic per-instruction first-diff (note:
  ee-gcc 2.9-991111 currently builds `.cod` not `.text`; pass
  `--built build/ico.elf` and it may report "no .text in built". When
  that happens, fall back to objdump on both ELFs at the diff range).

**Permuter:**
- `tools/auto_permute.sh` / `tools/auto_permute_parked.sh` — kick off
  permuter runs against parked tough_nuts. Run these in the background
  and let them harvest matches between sessions.

## Don't

Same as `decomp/MATCH.md` — IP rules, no AI co-author trailer, no
bypassing SHA-1 by editing `config/sha1sums.txt`.

Plus the fast-pass-specific don'ts:

- Don't manually inspect 20+ candidates one at a time. Batch the dump,
  read once.
- Don't write `__asm__ __volatile__("")` / `volatile` tricks past one
  attempt. Park.
- Don't spend foreground time on functions where the parked seed will
  match cleanly under permuter. The permuter is faster at this than
  you are.
- Don't skip the `rm asm/cod/*.s` step after a batch claim. The
  orphan-asm multiple-definition link error wastes 30s every time and
  hides real problems.
