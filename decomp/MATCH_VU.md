# VU0 microcode matching prompt — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude
Code session) to launch a VU0 microcode hand-rewrite session on the
ICO decomp at `/primary/dev/ico`. **Sprint C** in the project plan;
**do not start until data sections are >90% repo-wide.**

---

Continue the **ICO** clean-room decomp. Working directive: **hand-write
`src/cod/16F5E0.S` from understanding** of the VU0 microcode blob,
chunk by chunk, until `make setup && ninja` produces SHA-1-identical
ELF with `.vutext` typed-and-tracked. Same clean-room rules as
everywhere else — no disc data, no extracted assets, no
leaked-source-derived code, no AI co-author trailer on commits.

## What this matching loop is

The `.vutext` section (`0x0026F5E0 - 0x00274EBF`, 20,704 bytes, ~2,588
bundles) currently lives in `config/ico.us.yaml` as:

```yaml
- [0x16F5E0, textbin, src/cod/16F5E0]
```

`textbin` is "opaque binary blob, pulled via `.incbin`." Splat
references `assets/cod/16F5E0.textbin.bin` (gitignored, IP-sensitive).
`tools/progress.py` reports `.vutext` 0% under the IP-aware filter
because the bytes are not in tracked source.

**The match:** replace the yaml entry with:

```yaml
- [0x16F5E0, hasm, src/cod/16F5E0]
```

backed by `src/cod/16F5E0.S` — a hand-typed VU0 assembly file. Splat
already supports `hasm` for the rest of the binary (see Pattern A in
`decomp/MATCH.md`). `tools/postprocess_asm.py:patch_vu0_special_regs_per_function()`
already handles `$ACC`/`$Q`/`$R`/`$I` rewrites for splat-emitted asm;
it's a no-op for hand-typed `.S`.

## IP-safety boundary — HARD RULE

Mechanical byte→mnemonic disassembly is **itself extraction** and is
**NOT IP-safe** to commit to this repo. The clean-room path is:

1. Run `tools/disasm_vu0.py --range <lo>-<hi>` to get a reference
   listing for the chunk.
2. **Read** the reference. Understand the loop structure, register
   usage, lane-broadcast pattern (`.x`/`.y`/`.z`/`.w`), branch
   targets, accumulator chains.
3. **Re-write** the chunk into `src/cod/16F5E0.S` from understanding
   — with hand-chosen labels (not `L_<addr>`), pseudocode comments
   describing intent, and idiomatic VU formatting.
4. The disassembler output itself **NEVER ENTERS GIT.** Treat it
   like the gitignored `_data.c` sidecars — a regenerable reference,
   not source.

This is the same boundary as `MATCH_DATA.md`'s "typed reconstruction":
the developer must assign meaning. For VU code that means loop
annotation, label naming, and comment-as-pseudocode.

## Do not stop matching

**Run until the Claude usage cap stops you, or until the user
explicitly tells you to stop. Do not stop early, ever.** Same
discipline as `decomp/MATCH.md` and `decomp/MATCH_DATA.md`.

### Cron-driven /loop is NOT a heartbeat to wait on

If this prompt is firing from `/loop 30m decomp/MATCH_VU.md
unsupervised`, the 30-minute cadence is a **failsafe re-entry
mechanism** — not a per-iteration work cap. Each fire of the loop
should burn many minutes of work (many chunks, full rebuilds, SHA-1
checks) before terminating at the cap or a user prompt.

### Forbidden closing-summary phrasing

- "Yielding."
- "**This firing: N chunks done.**"
- "Cron continues."
- "Cumulative session totals: …"
- Any bold-summary block reading like a per-firing recap.

Mid-stream notes ("finishing chunk 0x0040-0x0080", "SHA-1 fail at
0x0118, investigating") are fine. The closing-line pattern is what's
banned.

## Read first (in this order)

1. `CLAUDE.md` — IP rules, toolchain, build commands, conventions.
2. `docs/LEGAL.md` — clean-room boundary; reinforce that VU
   disassembler output is reference-only.
3. `decomp/NOTES.md` — `.vutext` section + Stage 0/1 framing.
4. `include/vu0.h` — the EE-side VU0 inline-asm macros define the
   instruction vocabulary you'll be writing. Same mnemonics on the
   VU side; same idioms apply.
5. `decomp/MATCH_DATA.md` — companion data-matching prompt; the
   `.vutext` callout cross-references this file.

## Selection rule — pick a chunk

`.vutext` is 2,588 bundles. Work bottom-up by VMA in
**~64-byte chunks** (8 bundles per chunk) so each session has a
bounded unit of work. Per-session goal: 1-4 chunks fully matched.

```sh
# Determine the next unstarted chunk:
.venv/bin/python tools/disasm_vu0.py --bundles 16 --range 0x0-0x80
# Identify the boundary of work already committed in src/cod/16F5E0.S.
# Start at the next 0x40-aligned offset.
```

For early sessions, prefer obvious-shape chunks (long branch chains,
matrix-multiply loops, register clears) over dense FMAC accumulator
sequences. The disassembler's branch-collection makes loop bodies
visually obvious.

## Inner loop (per ~64-byte chunk)

For each picked chunk `[lo, hi]`:

1. **Get the reference:**
   ```sh
   .venv/bin/python tools/disasm_vu0.py --range 0xLO-0xHI > /tmp/vu0_ref.txt
   # /tmp/vu0_ref.txt is gitignored by virtue of /tmp/ — never copy
   # the body into the repo tree.
   ```

2. **Understand the chunk.** Read `/tmp/vu0_ref.txt`. Cross-reference
   any `.word 0x<hex>` lines with a VU0 reference manual (EE User's
   Manual chapter on VU programming, or any open-source VU
   disassembler's tests). The disassembler reliably identifies nop
   and branches; everything else needs your manual decoding.

3. **Identify the intent.** Look at:
   - Branch targets and loop structure (the `L_<addr>:` labels in
     the reference output).
   - Lane patterns (which `xyzw` mask is used) — common idioms:
     vector add (`.xyzw`), 4x4 matrix mul (`.x`/`.y`/`.z`/`.w`
     broadcast), w-only ops for perspective divide.
   - Accumulator chains (`mula` followed by `madda`*N then `madd`).
   - Memory-access patterns (`lq`/`sq` with offset register).

4. **Re-write the chunk** into `src/cod/16F5E0.S`. Use:
   - Hand-chosen labels (`matrix_mul_inner:`, `vertex_loop:`) — not
     `L_0040`.
   - Pseudocode comments (`; rotate vertex into world space`).
   - Standard VU0 mnemonics with `.bc` and `.xyzw` field suffixes.
   - Bundle-pair formatting: upper instruction on left, lower on
     right, separated by `;`.

5. **Build:**
   ```sh
   timeout 600 tools/build.sh setup && timeout 900 ninja
   ```
   No `quick_diff` for `.vutext` — `quick_diff.sh` only covers
   `.text`. SHA-1 round-trip via `verify_elf.py` is the only signal.

6. **Localize failures:**
   ```sh
   .venv/bin/python tools/first_diff.py
   ```
   First diff usually shows the exact bundle that diverges. Either:
   - Mnemonic wrong → re-read VU0 reference, fix instruction.
   - Bundle ordering wrong → check upper/lower placement.
   - Register field wrong → re-decode the bit pattern.

7. **Commit one chunk at a time** with descriptive messages:
   ```
   VU0: hand-write 0x0040-0x0080 (matrix_mul_inner)
   VU0: hand-write 0x0080-0x00C0 (vertex_normalize)
   ```

## VU0 idiom catalog (seed)

These are common patterns in VU0 microcode you'll recognize.
Expand this list as you learn more idioms.

### 4-component vector ops (xyzw)

Standard vector add/sub/mul/madd operating on all 4 lanes:
```asm
add.xyzw  vf03, vf01, vf02 ; nop
```

### Accumulator chain (4×4 matrix multiply)

Classic VU0 matrix-mul idiom — load matrix once, broadcast each
column lane to multiply:
```asm
mulax.xyzw   ACC, vf02, vf01x  ; nop          ; row 0 = m[0]*v.x
madday.xyzw  ACC, vf03, vf01y  ; nop          ; + m[1]*v.y
maddaz.xyzw  ACC, vf04, vf01z  ; nop          ; + m[2]*v.z
maddw.xyzw   vf05, vf05, vf01w ; nop          ; + m[3]*v.w → vf05
```

### Branch + delay slot

Lower-half branches are PC-relative with a delay slot. The bundle
*following* the branch executes regardless of branch outcome:
```asm
nop                       ; ibeq vi01, vi02, loop_end
nop                       ; nop                       ; ← delay slot
```

### Bundle ordering and hazards

Upper and lower instructions in the same bundle execute in parallel.
`Q`-register operations (divide/sqrt) have multi-bundle latency;
`vwaitq` in the lower half stalls until `Q` is ready:
```asm
nop                       ; vwaitq                    ; wait for prior vdiv
add.xyzw vf03, vf01, Q    ; nop                       ; now Q is safe
```

### Reference: `include/vu0.h`

The EE-side macros in `include/vu0.h` define the VU0 instruction
vocabulary used in ICO's matching C source. Same mnemonics, same
register names — when you're unsure about an instruction's syntax,
check how the EE side invokes it.

## Yaml flip procedure

Once `src/cod/16F5E0.S` is structurally complete (all 2,588 bundles
hand-written), flip the yaml subseg type:

```yaml
# before:
- [0x16F5E0, textbin, src/cod/16F5E0]
# after:
- [0x16F5E0, hasm, src/cod/16F5E0]
```

Then:

```sh
timeout 600 tools/build.sh setup && timeout 900 ninja
.venv/bin/python tools/verify_elf.py        # must report SHA-1 match
.venv/bin/python tools/progress.py          # .vutext now 100%
tools/check_no_rom.sh                       # must pass
```

The `hasm_in_src_path: True` splat option is already set in the yaml
header. `tools/postprocess_asm.py:patch_vu0_special_regs_per_function()`
applies idempotently to the hand-written `.S` — it's a no-op when the
file already uses `$ACC`/`$Q` form.

## Done criterion

- `src/cod/16F5E0.S` exists and contains hand-typed VU0 assembly
  (no copy-paste from `tools/disasm_vu0.py` output).
- Yaml subseg type is `hasm`.
- `make setup && ninja && .venv/bin/python tools/verify_elf.py`
  reports SHA-1 match.
- `tools/progress.py` reports `.vutext` 100%.
- `tools/check_no_rom.sh` passes.
- `tools/disasm_vu0.py` stdout was never committed to git
  (verify via `git log -p --all -- src/cod/16F5E0.S` and grep for
  the disassembler's "REFERENCE ONLY" banner — must show zero
  matches).

## Effort expectation

**Multi-week sub-project.** Reference: zeldaret RSP microcode (oot/mm
F3DEX2, aspMain, njpgdspMain) took multiple PRs and weeks of work
per microcode binary. ICO's VU0 blob is ~2,588 bundles ≈ ~5,000
instructions; expect comparable effort.

This is not a "one session" sprint. Plan for chunk-by-chunk
commits over many sessions, with the project's data-matching work
continuing in parallel.

## Tough-nut parking

If a chunk's SHA-1 fails persistently and you can't localize the
divergence, **revert that chunk's section of `src/cod/16F5E0.S`**
and commit a `tough_nuts/vu0/<offset>.md` note describing what you
tried. Move on to the next chunk. The reverted section returns to
the `textbin` form by virtue of the yaml subseg still being mostly
hasm-pointing-at-a-hand-written-file — but the gap is real. Track
gaps in `tough_nuts/vu0/` for a future re-attempt.

(Permuter does not apply to VU0 code; there's no equivalent of
ee-gcc regalloc to randomize.)

## Wrap-up — only when stopping for cap or user prompt

- ELF SHA-1 must match at session end. If it doesn't, revert the
  most recent chunk additions until it does.
- `git status` empty before the last commit lands.
- Confirm `tools/disasm_vu0.py` stdout never landed in git
  (the REFERENCE ONLY banner is the canary).
- Do **not** emit an "iteration results" or "session summary" —
  the commit log is the record.

## Cross-references

- `decomp/MATCH.md` — function matching workflow.
- `decomp/MATCH_DATA.md` — data section matching.
- `decomp/NOTES.md` — `.vutext` Stage 0/1 framing.
- `include/vu0.h` — EE-side VU macros (instruction vocabulary).
- `tools/disasm_vu0.py` — the disassembler used for chunk references.
