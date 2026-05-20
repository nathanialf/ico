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
bundles) is split in `config/ico.us.yaml` between a `hasm` head
(bytes already hand-typed) and a `textbin` tail (rest still
incbin'd):

```yaml
- [0x16F5E0, hasm, src/cod/16F5E0]            # already hand-typed
- [0x16F<N+0x40>, textbin, src/cod/16F<N+0x40>]   # rest
```

The hasm head is backed by `src/cod/16F5E0.S` — a hand-typed VU0
assembly file. The textbin tail is `assets/src/cod/16F<N+0x40>.textbin.bin`
(gitignored, IP-sensitive). Each new chunk extends the hasm range
forward and shrinks the textbin head — see the
"Yaml split-extension procedure" section below.

`tools/progress.py` credits hasm subsegs landing in the .vutext VRAM
range to `.vutext`, so the percentage tracks real hand-typed bytes
(not yaml shape). `tools/postprocess_asm.py:patch_vu0_special_regs_per_function()`
already handles `$ACC`/`$Q`/`$R`/`$I` rewrites for splat-emitted asm;
it's a no-op for hand-typed `.S`.

## Toolchain — `tools/assemble_vu0.py`

The repo ships a clean-room VU0 micromode assembler. The hand-written
`src/cod/16F5E0.S` does NOT go straight to `mips-linux-gnu-as` (which
doesn't know VU0 micromode). Instead:

    src/cod/16F5E0.S
       → tools/assemble_vu0.py        ; symbolic → .word stream
       → src/cod/16F5E0.s             ; binutils-ingestable .s
       → mips-linux-gnu-as            ; existing `as_hasm` ninja rule

Symbolic mnemonics the assembler recognises today (parity with
`tools/disasm_vu0.py`):

  upper:  `nop` (true zero), `pad` (0x000002FF — the canonical NOP
          encoding, FD_11 sub-op 0x0B)
  lower:  `nop` (true zero), `nop_swap` (0x8000033C — PCSX2 names
          this the "BIOS-bug NOP"; bytes are common in PS2 microcode
          but PCSX2 special-cases them as a no-op), branches
          `b/bal/jr/jalr/ibeq/ibne/ibltz/ibgtz/iblez/ibgez`

Plus the escape directives `.word`, `.bundle <upper>, <lower>`,
`.raw <bytes>`, `.macro`, `.assert_pc`.

The lower-half opcode dispatches via **bits 25-31** (7-bit field —
cross-checked against PCSX2 `VU0_LOWER_OPCODE[VU->code >> 25]`, GPL-3.0).
An earlier version of `disasm_vu0.py` used a 6-bit dispatch, which
silently mislabeled four ICO bundles as branches in the very first
chunk (the bytes were the BIOS-NOP `0x8000033C` pattern). If you
spot historical commits that wrote `b L_<addr>` for a 0x8000033C
bundle, that's a known-fixed bug.

Everything else (FMAC families, LSU, I-type, T3 sub-tables) is
still written via `.word` until that family's encoder lands in
`assemble_vu0.py` (mirror `disasm_vu0.py`).

When you crack a new opcode family during hand-rewrite:

  1. Add the decode case to `tools/disasm_vu0.py:decode_upper` /
     `decode_lower` (so the reference listing is no longer `.word`).
  2. Add the matching encode case to `tools/assemble_vu0.py:_try_encode_*`
     (so the source no longer needs `.word` for that family).
  3. Add a round-trip test entry in `tools/test_assemble_vu0.py`.

`tools/assemble_vu0.py src/cod/16F5E0.S --check assets/cod/16F5E0.textbin.bin --allow-short`
does an end-to-end byte comparison: built vs the textbin's leading
bytes (length-permissive, prefix-only match). Use it after every
edit to the `.S` — it's a sub-second loop vs the multi-minute
`build.sh setup && ninja` cycle.

Build wiring is automatic. `tools/build.sh setup` runs `assemble_vu0`
on every `src/cod/*.S` before splat, generating the corresponding
gitignored `<stem>.s` that splat's `hasm` subseg picks up. No manual
pre-step needed; just edit the `.S` and re-run setup + ninja.

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
# 1. Find the boundary of work already committed:
grep -E '0x16F[5-9A-F][0-9A-F]+, (hasm|textbin)' config/ico.us.yaml
#   → output shows e.g.
#         - [0x16F5E0, hasm, src/cod/16F5E0]
#         - [0x16F620, textbin, src/cod/16F620]
#     The hasm subseg runs 0x16F5E0..0x16F620 (== textbin start).
#     Subtract 0x16F5E0 to translate to a .vutext-relative offset
#     (0..0x40 already hand-typed).

# 2. Disassemble the next 8 bundles (64 bytes) as reference:
.venv/bin/python tools/disasm_vu0.py --range 0x40-0x80 > /tmp/vu0_ref.txt
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

4. **Re-write the chunk** by appending to `src/cod/16F5E0.S`. Use:
   - Hand-chosen labels (`matrix_mul_inner:`, `vertex_loop:`) — not
     `L_0040` (the disasm uses `L_<addr>` because it knows nothing
     about intent; you do).
   - Pseudocode comments (`; rotate vertex into world space`).
   - Standard VU0 mnemonics with `.bc` and `.xyzw` field suffixes
     when symbolic in `tools/assemble_vu0.py` — otherwise `.word
     0x<hex>` (with intent comment on the same line).
   - Bundle-pair formatting: upper on left, lower on right,
     separated by `;`.

5. **Tight inner loop — verify before building.** Sub-second:
   ```sh
   .venv/bin/python tools/assemble_vu0.py src/cod/16F5E0.S \
     --check assets/cod/16F5E0.textbin.bin --allow-short
   ```
   Prints the first mismatched byte (with both `--check-offset` and
   in-built offset) or `OK (N bytes match — built is a N/20768 prefix)`.
   Iterate on the `.S` until OK, THEN promote the hasm/textbin split.

6. **Promote the chunk** in `config/ico.us.yaml`. The hasm subseg
   grows by 0x40, the textbin subseg shrinks by 0x40 from its head.
   See "Yaml split-extension procedure" below for the exact form.

7. **Build + SHA-1 verify:**
   ```sh
   tools/build.sh setup && ninja
   ```
   No `quick_diff` for `.vutext` — `quick_diff.sh` only covers
   `.text`. SHA-1 round-trip via `verify_elf.py` (last ninja step) is
   the only signal.

8. **Localize unexpected failures:**
   ```sh
   .venv/bin/python tools/first_diff.py
   ```
   If `--check` already passed and ninja fails, the divergence is in
   the yaml/build wiring, not the bytes. Common causes: textbin's
   bin offset didn't slice correctly (rare; splat handles this), or
   the gitignore for the generated `.s` isn't covering the new path.

9. **Commit one chunk at a time** with descriptive messages:
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

## Yaml split-extension procedure

The `.vutext` segment lives in the yaml as TWO subsegs in tandem:
a leading `hasm` covering the already-hand-typed bytes, and a
trailing `textbin` covering everything that's still incbin'd from
`assets/`. After each new chunk lands, advance the split point:

```yaml
# before (after the first 8 bundles landed):
- [0x16F5E0, hasm, src/cod/16F5E0]
- [0x16F620, textbin, src/cod/16F620]

# after the second chunk (next 8 bundles, 0x40 more bytes):
- [0x16F5E0, hasm, src/cod/16F5E0]
- [0x16F660, textbin, src/cod/16F660]
```

Splat re-derives `assets/src/cod/16F660.textbin.bin` from the rest
of the .vutext bytes on the next setup, so no manual asset
extraction is needed. The hasm side just grows its byte range; the
single `src/cod/16F5E0.S` file accumulates more bundles.

When the entire 20704 bytes are hand-typed, delete the textbin
subseg entirely:

```yaml
- [0x16F5E0, hasm, src/cod/16F5E0]
# (no following textbin entry)
```

Then run:

```sh
tools/build.sh setup && ninja           # SHA-1 verify last step
.venv/bin/python tools/progress.py      # .vutext now 100%
tools/check_no_rom.sh                   # must pass
```

The `hasm_in_src_path: True` splat option is already set in the
yaml header. `tools/postprocess_asm.py:patch_vu0_special_regs_per_function()`
applies idempotently to the generated `<stem>.s` — it's a no-op
when the file already uses `$ACC`/`$Q` form.

## Done criterion

- `src/cod/16F5E0.S` exists and contains hand-typed VU0 assembly
  (no copy-paste from `tools/disasm_vu0.py` output).
- Yaml entry for 0x16F5E0 is `hasm` and there is NO trailing
  `textbin` subseg in the .vutext range.
- `tools/build.sh setup && ninja` reports
  `verify_elf: OK (... sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.
- `tools/progress.py` reports `.vutext` 100% (20704 / 20704).
- `tools/check_no_rom.sh` passes.
- `tools/disasm_vu0.py` stdout was never committed to git
  (verify via `git log -p --all -- src/cod/16F5E0.S` and grep for
  the disassembler's "REFERENCE ONLY" banner — must show zero
  matches).
- `assets/src/cod/16F*.textbin.bin` left in `.gitignore`'d
  `assets/` tree only — no `assets/` files are tracked.

## Effort expectation

**Multi-week sub-project.** Reference: zeldaret RSP microcode (oot/mm
F3DEX2, aspMain, njpgdspMain) took multiple PRs and weeks of work
per microcode binary. ICO's VU0 blob is ~2,588 bundles ≈ ~5,000
instructions; expect comparable effort.

This is not a "one session" sprint. Plan for chunk-by-chunk
commits over many sessions, with the project's data-matching work
continuing in parallel.

## Tough-nut parking

If a chunk's `--check` fails and you can't decode the bytes, **revert
that chunk's lines from `src/cod/16F5E0.S`** and back out the yaml
split-extension (move the textbin start back to where it was). The
reverted bytes return to incbin from `assets/` via the now-larger
textbin subseg — the section round-trips trivially. Commit a
`tough_nuts/vu0/<offset>.md` note describing what you tried (which
upper opcode family was opaque, which bundle's encoding you couldn't
identify) so a future session has the breadcrumbs.

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
