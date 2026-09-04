# Phase 5 — per-TU data carve ledger (retail-v2)

Tracks noncontiguous-data carves landed under the aug6 carved-subsegment
convention (`decomp/NOTES.md` §"Noncontiguous data"). One entry per TU:
sections carved, symbol count, source of types, and any SHARED symbols
left in the blob for a future pass. Kept small by design — this is an
index, not a diff dump; `git log` has the byte-level detail per commit.

Tooling: `tools/find_carves.py <tu>` (version-aware via `tools/ico_version.py`
— auto-detects `us` vs `aug6`, same CARVE/SHARED/BLOCKED classification on
both) is the source of truth for what's safe to carve. `--emit` groups the
CARVE rows into CONTIGUOUS runs and prints, per run, the dot-form yaml pair
(carve + blob resume) plus byte-verified C definitions — or marks the run
`[BLOCKED]` with the mechanical reason it cannot be carved as-is (see
"Root cause of Blocker 2").

## Batch 1 — jtbl queue (Phase 4 deferral, reason `jtbl`)

Four TUs, one contiguous `.rodata` carve each, landed together with the
`tools/port_from_aug6.py` body ports (`decomp/port_ledger.md` has the
per-function port detail / hand-fixes). `tools/build.sh setup && ninja`
green from a clean rebuild; `tools/check_no_rom.sh` clean.

| TU | carve (ROM off, VMA range) | symbol(s) | body port |
|---|---|---|---|
| `src/Packet` | `[0x454E00, .rodata]`, VMA 0x554E00..0x554E44 | `jtbl_00554E00` (17 entries, 0x44) — `pac_setVifEndCode`'s switch | PORTED, clean rebind |
| `src/debug_exception` | `[0x515090, .rodata]`, VMA 0x615090..0x6150D4 | `jtbl_00615090` (17 entries, 0x44) — `initLineTraceTable`'s switch | PORTED, clean rebind |
| `src/girl_act` | `[0x459950, .rodata]`, VMA 0x559950..0x559A5C | `jtbl_00559950` (67 entries, 0x10C) — `actGirlHang`'s switch | PORTED, hand-fixed (see below) |
| `src/motionOrientManager` | `[0x5196C8, .rodata]`, VMA 0x6196C8..0x619734 | `D_006196C8` (0x18, debug fmt string) + `jtbl_006196E0` (21 entries, 0x54) — `shiftMotionOrientEndFunc`'s switch | carve landed, function LEFT ASM (see below) |
| `src/StageAnimation` | `[0x455990, .rodata]`, VMA 0x555990..0x5559B8 | `jtbl_00555990` (10 entries, 0x28) — `stage_Init`'s switch | carve landed 2026-07-31, function LEFT ASM |

Every jtbl VMA/entry-count was hand-verified against `baserom/baseelf.rom`
before landing: decoded every `.word` in the table, confirmed each target
address lands inside the owning function's own `.text` range (rules out
misattributing a neighboring function's data). `pac_makeNormalStrip`
(`src/Packet`'s OTHER jtbl skip, `jtbl_00554DB0`) is intentionally NOT
carved — it's `INCLUDE_ASM` on aug6 too (never matched upstream), so there
is no reference body to port and no payoff yet from carving just its table.

### `src/girl_act` / `actGirlHang` — hand-fix detail

Reference: PROTOTYPE-VS-RETAIL struct-layout drift, not a rebind bug.
`port_from_aug6.py`'s mechanical rebind isn't enough when the field being
accessed literally moved between the aug6 build and retail. Four literal
offsets changed (all re-derived from
`asm/nonmatchings/src/girl_act/actGirlHang.s`, not guessed):
`SUB(g)+0x134`->`+0x144`, `REF(g)+0x490`->`+0x4A0`, `SUB(g)+0x678` chain's
inner `+0x3E8`->`+0x408` (both occurrences), and the case-36 comparison
constant `0x54`->`0x55`. Also needed the aug6 body's function-local
`#define SUB(g)`/`#define REF(g)` macro pair re-added by hand — the port
splice doesn't carry sibling `#define`/`#undef` lines, so without them
`SUB(g)`/`REF(g)` silently compiled as implicit undeclared-function calls
(ee-gcc 2.9 K&R implicit int) instead of failing loudly.

### `src/motionOrientManager` / `shiftMotionOrientEndFunc` — NOT ported, resume note

The carve is landed (jtbl + its string neighbor own their bytes now,
function stays `INCLUDE_ASM`). The body port does not close cleanly:

- `REF(g)+0x490`->`+0x4A0`: same struct-offset drift as actGirlHang (same
  field, same delta) — confirmed correct in isolation.
- Remaining blocker is NOT a literal/offset issue: recompiling the
  (offset-corrected) aug6 body cross-jump-merges several of the switch's
  21 case bodies into a shared call trailer (gcc tail-merging structurally
  identical `func_00264DF8(buf, D_X); break;` arms), while the retail ROM
  keeps every case's `lui/daddu/jal/addiu` sequence fully inlined before
  branching to the shared `display()` tail. This is a whole-function
  codegen-shape difference, not a rebind/const-value fix — needs a proper
  `decomp-match`/`decomp-convergence` pass on the switch's case-body
  source shape (e.g. break the cross-jump candidacy per case), not another
  mechanical port attempt.
- `D_006196C8` (the format string immediately before the jtbl) needed a
  REAL typed definition (`const char D_006196C8[0x18] = "%s \207 %s (%s)\n";`,
  0x18 bytes = string + ROM's own null-pad to the jtbl's `.align 3`
  boundary) even with the function left unported: the RAW ROM disassembly
  itself carries a `%hi/%lo(D_006196C8)` reference (the still-asm function
  loads the string's address for its `display()` call), and once the byte
  range is carved out of the blob there is no other source for that symbol
  to resolve against.

## Root cause of Blocker 2 — FOUND AND FIXED (2026-07-28, branch `carve-fix`)

Blocker 2 below ("a 2nd plain named-data dot-form carve corrupts the whole
link") is **not one bug and not a splat/gen_ninja bookkeeping bug**. The
generated linker script was correct all along; the corruption came from
`ld`'s *input-section alignment* padding, plus three source-spelling traps.
All four are now either fixed in the build graph or gated mechanically, and
a 9-carve batch across 6 TUs and 2 sections round-trips SHA-green (below).

### (1) THE mechanism: gas's 2**4 floor on the STANDARD sections

GNU `as` for MIPS unconditionally does the equivalent of
`record_alignment (text_section, 4)` / `(data_section, 4)` / `(bss_section, 4)`
in `md_begin` — i.e. `.text`, `.data` and `.bss` get a **hard 16-byte minimum
section alignment regardless of their contents, and regardless of being
completely EMPTY**. Custom section names (`.rodata`, `.lit4`, `.sdata`, and
gcc's `-fdata-sections` `.data.<sym>`) escape it and get only the alignment
their directives imply.

Consequences, all confirmed on this branch by reading `build/ico.us.map`:

* every raw `.data` blob object (`build/asm/data/src/cod/<HEX>.data.o`) carried
  `.data` alignment 16;
* **34 compiled TU objects carried an EMPTY `.data` (and `.bss`) at alignment
  16** — the ones assembled on the modern-gas path;
* `ld` pads for a zero-size input section exactly as eagerly as for a real one.

So the whole build round-tripped only because every one of those over-aligned
sections happened to land on a 16-byte boundary. The instant a carve made the
`.data` output stream land at an address that is 8- but not 16-aligned (i.e.
**any carve whose run does not END on a 16-byte boundary**), the next
over-aligned section injected 8 bytes of `*fill*` and every following byte
shifted. The cascade then hit `. = ALIGN(., 128)` at `cod_DATA_END`, which
rounded the whole `.data` section up a full 128 bytes — producing the ledger's
"+0x80 shift", "+128 bytes file-size growth", "first diff at file offset 0x10"
(that first diff is crt0's `%lo` of the moved `.sbss` base, not a data byte)
and, once far enough, the `R_MIPS_GPREL16 relocation truncated to fit` errors
(`.lit4`/`.sdata` sliding out of `_gp ± 32 KB`).

This is also exactly why the four batch-1 jtbl `.rodata` carves were never
affected: `.rodata` is a custom section, so it only ever carried 2**2/2**3.

**Fix (one-pass, tracked, no ld postprocessing):** normalise the alignment of
sections that can never legitimately need one.
* `tools/gen_ninja.py` — `section_for()` derives the ONE section a splat blob
  object owns from its `<ROMHEX>.<section>.o` name; the assemble rule now
  emits `--set-section-alignment <owned>=<align_for(romhex)>` (a divisor of the
  blob's own ROM address, so never a source of padding) plus
  `--set-section-alignment {.text,.data,.bss}=1` for the empty leftovers.
* `tools/compile_c.sh` — every compiled TU object now gets
  `--set-section-alignment .data=1 --set-section-alignment .bss=1`. `.text`
  keeps its `align_for()` value: it is load-bearing, reproducing the ROM's
  4-byte inter-TU function padding in 34 TUs. The `-fdata-sections`
  `.data.<sym>` / `.rodata.<sym>` alignments are also left alone — gcc's
  alignment there reproduces intra-TU padding between carved objects.

Rejected alternative: `subalign: 1` in the yaml (splat emits `SUBALIGN(1)` on
the output section). It fixes the blobs but also flattens `.text` to 1, which
deletes those 34 legitimate 4-byte inter-TU pads — `cod_TEXT_END` came out
0x88 short. Do not use it.

### (2) One carved run per (TU, section) — a real, permanent constraint

splat emits a **whole-object** selector per dot-form carve subsegment —
`build/src/<tu>.o(.data*)`. Two disjoint `.data` carves for the same TU
therefore emit that identical glob twice, and GNU ld assigns each input
section to the **first** output statement that matches it: the 2nd+ run is
dead, and ALL of that TU's carved `.data.<sym>` sections collapse into the
1st run's address. That is the ledger's "charFileManager needs 2 disjoint
`.data` runs → `D_004D42B0` linked at 0x559A60" case.

Not fixable without per-symbol selectors, so it is now a **mechanical gate**:
`tools/gen_ninja.py::check_ld_carve_globs()` scans the generated linker script
and hard-errors on any duplicated `<object>(<glob>)` pair before the build
starts. aug6 has always (accidentally) respected this — every one of its 33+
carves is one run per TU per section.

### (3) Source-spelling traps that also present as "the link corrupted"

Each of these makes ee-gcc put the symbol somewhere other than where the carve
says, which shifts everything after it. All are now checked by
`tools/find_carves.py --emit`, which refuses to emit a run that trips one:

| trap | symptom | rule |
|---|---|---|
| all-zero initialiser | object lands in `.bss`/`.sbss`, carve region under-fills | carve only non-zero symbols |
| `.data` symbol ≤ 8 bytes | `-G8` puts it in `.sdata` | `.data` carve syms must be > 8 bytes |
| `.sdata` symbol > 8 bytes | `-G8` puts it in `.data` | `.sdata` carve syms must be ≤ 8 bytes |
| 4-byte symbol spelled `unsigned int X[1]` | ee-gcc aligns arrays to 8; a 4-aligned VMA then gets `*fill*` | spell 4-byte symbols as a **scalar** `unsigned int X = ...;` |
| carve start not 8-aligned (4 for a scalar) | `ld` pads to gcc's section alignment | check `VMA % 8 == 0` |
| `const` qualifier | object lands in `.rodata` | never `const` a `.data`/`.sdata` carve |

### (4) Unchanged, still true

Blocker 1 (`.rodata` carve vs. `migrate_rodata_to_functions`' local dlabel
copy) and Blocker 3 (named `.lit4` float compiles to `.sdata`) are real and
untouched. `find_carves.py --emit` now flags both up front instead of letting
them surface as an assembly/link error.

### Proof batch (this commit)

Nine plain named-data dot-form carves, 6 TUs, 2 sections, landed together —
`tools/build.sh setup` (clean `rm -rf build` rebuild) + `ninja` →
`verify_elf: OK (fbf50c75…)`, `check_no_rom.sh` clean:

| TU | section | VMA range | bytes | syms |
|---|---|---|---|---|
| `src/commonact` | `.data` | 0x282390..0x282400 | 112 | 5 |
| `src/chain` | `.data` | 0x28AFB0..0x28B100 | 336 | 3 |
| `src/debug` | `.data` | 0x4B30F8..0x4B3108 | 16 | 1 |
| `src/box` | `.data` | 0x4BF460..0x4BF7C0 | 864 | 10 |
| `src/staticBlur` | `.data` | 0x4C61A0..0x4C61F0 | 80 | 5 |
| `src/st47a` | `.data` | 0x4D3A30..0x4D3E50 | 1056 | 33 |
| `src/commonact` | `.sdata` | 0x6322F0..0x632310 | 32 | 5 |
| `src/chain` | `.sdata` | 0x632758..0x632770 | 24 | 4 |
| `src/debug` | `.sdata` | 0x632A18..0x632A30 | 24 | 4 |

(Plus the pre-existing `src/PObj` `.data` carve and the four batch-1 jtbl
`.rodata` carves: 14 carves coexisting.) Every run is symbols whose ONLY
consumers are that TU's own still-asm functions, so no existing `extern`
declaration or C body changed — the carves add data and nothing else. Every
byte was generated directly from the target ELF by `find_carves.py`.

### What aug6/`main` should adopt

aug6 uses the same `gen_ninja.py`/`compile_c.sh` (VERSION-keyed), so porting
these two commits gives it the same protection. aug6's 33 carves all happen to
end on 16-byte boundaries today, which is why it never hit this — that is luck,
not design, and the next aug6 carve at an 8-aligned end would have failed the
same way.

## Tooling notes for future carves

- `tools/port_from_aug6.py port <tu> --allow-jtbl <func> [--only <func>]`:
  Phase-5 additions. `--allow-jtbl` lifts the ordinary jtbl-skip and the
  "may add code, never data" growth-revert for named functions whose jtbl
  carve is already in the yaml. `--only` restricts the port to named
  function(s) — use it whenever a coalesced TU has OTHER candidates the
  driver would otherwise re-attempt (already-decided REVERTED siblings);
  without it, `port` iterates every wave-eligible candidate in the TU.
- `build_symbol_map`'s aug6->retail rebind had a real gap for jtbl bases:
  it named the retail counterpart of a `%hi/%lo(jtbl_...)` reference
  `D_<addr>` (the generic data-symbol template) instead of `jtbl_<addr>`
  (splat's actual auto-name for a carved switch jump table), so it always
  reported the rebind target as "undefined" even after the yaml carve
  existed. Fixed: prefer `jtbl_<addr>` when the aug6-side symbol itself is
  `jtbl_`-named and that name is present in the retail `defined` label set.
- `.port_cache/retail_labels.json` caches the retail label scan
  (`glabel`/`dlabel`/`jlabel` + symbol_addrs) and does NOT self-invalidate
  when a new yaml carve adds a fresh `dlabel` (e.g. a jtbl's auto-generated
  fallback). `rm .port_cache/retail_labels.json` after any yaml carve
  change, before the next `port` run.
- A carved region referenced ONLY from a still-`INCLUDE_ASM` function is
  NOT exempt from needing a real C definition — the raw ROM bytes'
  `%hi/%lo` relocations need SOME symbol to resolve against once the bytes
  leave the auto-generated blob fallback. Define it, leave the function
  itself asm, if the port doesn't close cleanly (see the
  motionOrientManager case above).
- Splitting a carve's start point one boundary EARLIER (to absorb a small
  neighbor like a format string) is safe as long as the new region is
  still ONE contiguous run for that TU/section, and every byte in the
  extended range is verified against `baserom/baseelf.rom` before landing
  — the SHA gate cannot tell you if you've swept in a neighbor's data.

## Batch 2 — `src/PObj` (VERY limited: 1 symbol) + a major tooling-bug finding

Ranked the ~192 non-excluded, non-batch-1 TUs by `find_carves.py`'s CARVE
count (script in this session's scratch; sort by `CARVE=N`). Top of the
list: `src/commonact` (124), `src/st47a` (121), `src/debug` (93),
`src/motionManager` (87), `src/Light` (81), `src/camera-editor` (80),
`src/chain` (76), `src/enemy_act` (74), `src/st04b` (69), `src/kanbanBoot`
(69), `src/charFileManager` (63), `src/PObj` (19, chosen first as the
smallest/cleanest — `SHARED=0 BLOCKED=1`).

**Only landed 1 symbol this batch**: `D_004D4230` (`.data`, 0x80 bytes,
`src/PObj`). Everything else attempted — PObj's own remaining 18 CARVE
symbols, plus a `src/charFileManager` pass — hit one of two blockers below
and was reverted. This is a MUCH smaller yield than planned; the second
blocker (multi-entry corruption) is a session-blocking discovery that
needs a real fix before this phase can scale.

### Blocker 1 — plain `.rodata` string carve collides with INCLUDE_ASM's local dlabel copy

Confirmed on `src/PObj`'s 8-string run (`D_0062DF08`..`D_0062DFF0` +
`D_0062E010`, VMA 0x62DF08..0x62E020): splat's per-function "nonmatching"
`.s` stub for a still-`INCLUDE_ASM` function embeds its OWN local
`dlabel`/`enddlabel` copy of any small `.rodata` it references (visible in
`asm/nonmatchings/src/PObj/func_002413F0.s` etc. — a `.section .rodata` /
`dlabel D_0062DF08` block ahead of the function body), so it can assemble
standalone. Add a C-level carve at the SAME address and `ee-as` errors
`symbol 'D_0062DF08' is already defined` (two definitions: the embedded
one and the carved global). The 4 batch-1 jtbl carves never hit this
because gcc-emitted switch jump tables go through a different splat path
that doesn't locally re-embed. **Rodata carving a plain string is only
safe once every INCLUDE_ASM function referencing it is ported to C**
(removing its `.s` stub) — not a yaml/C workaround, an actual match/port.
PObj's `func_002412D8`/`func_002413F0` still reference these strings, so
the carve stays reverted; symbols left in the `src/cod` rodata blob.

### Blocker 2 (THE BIG ONE) — a 2nd plain named-data dot-form carve corrupts the whole link

**RESOLVED 2026-07-28 — see "Root cause of Blocker 2" above. The section below
is the original symptom report, kept verbatim because every row in it maps to
one of the four mechanisms documented there.**
Exactly ONE plain (non-jtbl) named-data dot-form carve — in `.data`,
`.sdata`, whatever section, for whatever TU — round-trips fine (proven:
`src/PObj`'s lone `D_004D4230` `.data` carve, and in isolation a lone
`src/charFileManager` `D_004B2FD0` `.data` carve). The moment a SECOND
such carve exists ANYWHERE in the `cod` segment's data subsegments —
same TU different section, same TU a 2nd disjoint run, or a totally
different TU — `ninja`'s `verify_elf` mismatches. Confirmed across four
independent configurations, all bisected via `rm -rf build` clean
rebuilds (no stale-cache artifacts):

| config (2nd carve added) | symptom |
|---|---|
| PObj `.data` + PObj `.sdata` (`D_00633B98`..`D_00633BC0`) | whole link shifts +0x80 bytes from `D_00633000`-ish onward; `cod_TEXT_END` itself is 0x274780 instead of 0x274700 (the shift originates AT THE .text/.data BOUNDARY, before any of the touched symbols) |
| PObj `.data` + charFileManager `.data` (`D_004B2FD0` before it, `D_004D42B0` after it — i.e. charFileManager needs 2 disjoint `.data` runs) | `D_004D4230` shifts +8; `D_004D42B0` ends up linked at 0x559A60 (in `.rodata`'s address range, nowhere near its real 0x4D42B0) |
| charFileManager `.data` (`D_004B2FD0`) ALONE, PObj's carve reverted first | still mismatches (+128 bytes file-size growth, first diff at file offset 0x10 — i.e. even a SINGLE new carve for a DIFFERENT TU than the one already proven clean reproduces the corruption) |
| charFileManager `D_004D42B0`+`D_004D42E0` (a large, 382KB, symbol) added alongside PObj's `.data` carve | `ld` errors outright: `R_MIPS_GPREL16` relocation-truncated-to-fit across UNRELATED TUs (`matrixDrive` etc.) + `undefined reference to D_00531818` in the raw data blob |

The generated `config/ico.us.ld` linker-script GLOB for a working single
carve looks byte-for-byte structurally identical to a broken 2-carve one
(`build/src/<TU>.o(.data*)` threaded into the giant per-TU-declaration-order
list at the position matching the yaml address, raw blob pieces
(`build/asm/data/src/cod/<HEX>.data.o`) correctly bracketing it) — so this
is NOT a linker-script authoring mistake on my part; it's some
count/order-dependent bug in splat's or `gen_ninja.py`'s size/alignment
bookkeeping across MULTIPLE such carves. `D_00633BC0`'s `.sdata.*`
sub-sections all report `2**3` (8-byte) alignment in `objdump -h`, which is
a candidate lead (an `ALIGN(8)`-per-new-object emission that always adds a
full unit even when already aligned, rather than 0 when unneeded) but
NOT confirmed as the root cause — whoever picks this up should instrument
`tools/gen_ninja.py`'s data/sdata glob emission directly rather than
re-deriving this from `nm`/`objdump` output as this session did.

**Practical implication (SUPERSEDED)**: the one-carve-per-commit cap is
lifted — see the root-cause section above. What survives is the narrower
rule: ONE contiguous carved run per (TU, section), now enforced by
`gen_ninja.py::check_ld_carve_globs()`.

### Blocker 3 — `.lit4` carve default-placement mismatch

`float D_006318C0 = 16777215.0f;` as a plain named global compiles into
`.sdata` under this project's `-G8` flags, NOT `.lit4` (confirmed via link
error `multiple definition` + `.sdata.D_006318C0` in `objdump -h` when
tested without a yaml carve). The ORIGINAL binary's `.lit4` placement for
a NAMED (not anonymous-literal-pool) float needs `compile_c.sh`'s
`config/lit4_pool_slots.txt` rename mechanism, which is explicitly
**single-entry-only** per the tool's own error message; PObj needs 4
(`D_006318C0`/`C4`/`C8`/`CC`). Left uncarved, in the `src/cod` `.lit4`
blob. A multi-entry `.lit4` splitter would need to be built first.

### `src/charFileManager` cross-branch findings (informational, not landed)

Cross-referencing `git show retail:<file>` by SYMBOL NAME (not just
same-named `.c` file) is essential: `D_004D42B0`/`D_004D42E0` are defined
in retail's `src/PObj.c`, not `charFileManager.c` — TU boundaries differ
between the old `retail` branch and this `us` rebuild for this address
range (same underlying PObj model-path table, split differently by each
branch's own matching order). `find_carves.py`'s consumer scan is
authoritative for THIS branch regardless of what retail did, so carving
under charFileManager (this branch's actual sole referencer) would still
be correct IF the multi-entry bug didn't block it. Also re-confirmed the
"oversized CARVE symbol" trap from batch 1's `D_0062E010` case: retail
types `D_004D42E0[95566]` (0x5D5D8 = 382264 bytes); `find_carves.py`
guessed 423800 (0x67778) via its next-known-symbol heuristic overshoot.
Byte-verified the FULL trimmed 382264-byte array against
`baserom/baseelf.rom` (exact match) before deciding not to carve it (see
Blocker 2). **Standing rule reinforced: always cross-check a CARVE
symbol's size against retail before trusting `find_carves.py`'s own
number — prefer the smaller, retail-verified one whenever they disagree.**

## SHARED-symbol hotlist (seen so far, not carved — owner ambiguous)

None yet logged from a genuine multi-TU CARVE-candidate sweep beyond what's
in the two batches above.

## Recommended next TUs (successor should start here)

**Blocker 2 is fixed** — carve in batches. Workflow: `tools/find_carves.py
<tu> --emit` now prints, per CONTIGUOUS run, the dot-form yaml pair (carve +
blob resume) and byte-verified C definitions, and marks a run `[BLOCKED]`
with the reason when it would trip any of the mechanical gates. Take the
largest non-blocked run per (TU, section), paste the yaml in ascending ROM
order, append the C to the TU, then `tools/build.sh setup && ninja`.

Ranked list (CARVE count, this session's sweep, excludes batch-1/2 TUs and
the worker exclusion list): `src/commonact` (124), `src/st47a` (121),
`src/debug` (93), `src/motionManager` (87), `src/Light` (81),
`src/camera-editor` (80), `src/chain` (76), `src/enemy_act` (74),
`src/st04b` (69), `src/kanbanBoot` (69), `src/charFileManager` (63,
partially explored above), `src/staticBlur` (58), `src/haveParentSimpleObj`
(56), `ios/cdvd` (55), `sound/s_init` (52), `src/box` (52), `src/way_tool`
(44), `src/icoMisc` (44). Once Blocker 2 is fixed, re-run
`find_carves.py --emit` on each and apply the same retail-crossref +
byte-verify workflow this batch used for `src/PObj`/`src/charFileManager`.

## Batch 3 (carve-3, this session) — 6 TUs landed, 1 new blocker class found, no floors

Scope: `commonact`/`enemy_act`/`girl_act`/`boyact`/`e3`/`way_tool` were
EXCLUDED all session (conv-6 in-flight on those TUs per `git log conv-6
--oneline`: it touches exactly those six `.c` files). `src/act-env.c` and
`src/motionOrientManager.c` were excluded per the standing worker split.
Everything else ranked above was fair game.

**Landed** (6 TUs, 7 symbol runs, `tools/build.sh setup` clean rebuild +
`ninja` → `verify_elf: OK (…fbf50c75…)`, `check_no_rom.sh` clean):

| TU | section | VMA range | bytes | syms |
|---|---|---|---|---|
| `src/motionManager` | `.data` | 0x4C5AA0..0x4C5AE0 | 64 | 4 |
| `src/motionManager` | `.sdata` | 0x63345C..0x633478 | 28 | 5 |
| `src/Light` | `.rodata` | 0x554780..0x554790 | 16 | 1 |
| `src/charFileManager` | `.data` | 0x4B2FD0..0x4B2FE8 | 24 | 1 |
| `src/icoMisc` | `.data` | 0x4BCE90..0x4BCEB0 | 32 | 2 |
| `src/kanbanBoot` | `.data` | 0x4BCEC0..0x4BCED8 | 24 | 1 |
| `src/st04b` | `.data` | 0x4D1490..0x4D1510 | 128 | 4 |

**`src/charFileManager` — the 296-byte `find_carves.py` guess was wrong,
confirmed by an EXISTING typed extern.** The TU already has
`extern Blk24 D_004B2FD0;` (`Blk24` = `{ long long a,b,c; } __attribute__
((packed))`, 24 bytes) used as a per-element reset template
(`D_006E4890[j] = D_004B2FD0;`). `find_carves.py`'s next-symbol-address
heuristic reported 296 bytes/1 sym (guessing the whole gap to `debug`'s
carve belongs to this one name) — same class of overshoot as the
`D_004D42E0` case in batch 2. Carved only the byte-verified 24 bytes
(`Blk24 D_004B2FD0 = { 0, 0, 0x0000000100000000LL };`, values read
straight from `baserom/baseelf.rom` offset `0x3B2FD0`); the remaining
272 bytes (`0x4B2FE8..0x4B30F8`) stay unattributed in the blob. **Standing
rule reinforced again: an existing typed `extern` in the TU is a stronger
size oracle than `find_carves.py`'s heuristic — check for one before
trusting the tool's byte count.**

**`src/Light` — const-qualifier trap caught by the build, not by
`find_carves.py`.** First attempt defined the `.rodata` string as
`char D_00554780[16] = "reset gs\n";` (no `const`) — ee-gcc puts an
*initialized, non-const* array in `.data`, not `.rodata`, confirmed via
`ico.us.map` (`.data.D_00554780` instead of `.rodata.D_00554780`), which
silently shifted `cod_DATA_START` by the object's own text-order position
and produced a whole-link SHA mismatch (`+384` bytes, symptom identical
to Blocker 2's original signature — same alignment-cascade mechanism,
different trigger). Fix: `const char D_00554780[16] = "reset gs\n";`
(and its extern declaration also needed `const` to avoid a `conflicting
types` compile error). **This is the trap-table row "const → .rodata"
read in the CORRECT direction: a `.rodata` carve of a byte array MUST be
`const`, not just "don't const a `.data`/`.sdata` carve."**

### NEW blocker class found — carving a scalar/small-array symbol that a
### COMPILED (not just still-asm) sibling function already references by
### plain `extern` can flip that reference's addressing mode from
### gp-relative to far, growing `.text` and desyncing the whole link

Found on 3 of the original 9 candidate TUs this batch (**reverted, not
landed** — see below): `sound/s_init` (`D_00632200/04/08`, referenced by
the ALREADY-COMPILED `soundAllocIopFree`/`soundDataOpen`), `src/camera-editor`
(`D_00632640`, referenced by the STILL-ASM `menuGroupEdit.s` via an
explicit `%gp_rel(D_00632640)` pseudo-op), and `src/staticBlur`'s 2nd
`.sdata` run (`D_0063368C` run — some function elsewhere in the TU touches
one of those 5 symbols).

Mechanism, confirmed by isolating each TU with `tools/compile_c.sh
<file>.c /tmp/out.o` (bypassing the whole link) on the ORIGINAL vs the
EDITED source and diffing `.text` size/objdump: with **no local
definition anywhere in the TU**, ee-gcc/gas speculatively assumes an
`extern int`/`extern unsigned int` scalar (and `%gp_rel(SYM)` pseudo-ops
in raw `.s` text) is small and emits ONE instruction (`sw/lw ...,N(gp)` or
`addiu reg,gp,N`) with an `R_MIPS_GPREL16` relocation, deferred entirely to
the linker. The MOMENT a real local definition for that exact symbol name
exists anywhere in the same translation unit (even correctly placed in
`.sdata` by `-fdata-sections`, even well under the 8-byte `-G8`
threshold), every **earlier-compiled reference in the same TU** — whether
from a normal C function OR from raw `INCLUDE_ASM` text carrying a literal
`%gp_rel()` pseudo-op — silently recompiles to the 2-instruction far form
(`lui+sw` / `lui+addiu` with `R_MIPS_HI16`/`R_MIPS_LO16`), growing that
TU's `.text` by 4 bytes per flipped reference. This is invisible to
`tools/find_carves.py`'s BLOCKED classifier (which only detects the
Blocker-1 "duplicate local `dlabel`" assembler-error case for `.rodata`
strings) — it does not currently scan sibling functions/`.s` stubs in the
TU for a bare `%gp_rel(SYM)`/`extern SYM` reference at all, so a run it
reports clean can still desync the link this way. Symptom is identical in
shape to the alignment-cascade family (whole-file-size growth, first
mismatch far from the actual symbol, `cod_TEXT_END`/`cod_DATA_START`
shifted) but the ROOT CAUSE is upstream in `.text`, not `.data` layout —
diagnose it by binary-searching `cod_TEXT_END`'s address against a clean
rebuild's, not by staring at the data segment.

**Detection recipe added this session (not yet automated into
`find_carves.py` — flagged for a future pass):** for each candidate
symbol in a run, `git show HEAD:<tu>.c` vs the edited file through
`tools/compile_c.sh <file> /tmp/x.o` (no yaml/link needed) and compare
`.text` size (`objdump -h`) before/after adding the definition. Equal
size == safe; any growth == revert that run and ledger it as
`[gp-rel-flip]` blocked, pending either porting the referencing function
to C (removing the raw `%gp_rel`) or further study of ee-gcc's `-G8`
extern-vs-local addressing heuristic.

**Reverted, not landed this batch** (yaml + C additions both backed out
cleanly, confirmed via `git checkout -- <file>` since each was a pure
addition): `sound/s_init` `.sdata` run `0x632200..0x63220C` (12B, 3 syms),
`src/camera-editor` `.sdata` run `0x632618..0x6326D0` (184B, 23 syms),
`src/staticBlur` `.sdata` run `0x63368C..0x6336AC` (32B, 5 syms — note
this TU's `.data` run from batch-1/proof-batch is still landed and
unaffected). All three TUs' full `find_carves.py --emit` output is
otherwise unchanged and can be re-attempted once the `[gp-rel-flip]`
symbol(s) are identified and either excluded from the run or their
referencing function is ported to C first.

### Recommended next TUs (successor should start here)

Verified-safe six TUs above are landed. Continue down the ranked list
above with the SAME workflow, but add the `.text`-size-equality check
(via `tools/compile_c.sh`, before touching yaml) as a mandatory gate on
every run before landing it — not just for runs `find_carves.py` marks
clean. Next unexplored candidates: `src/enemy_act` (74, EXCLUDED this
session — conv-6 — reassess once that branch lands/merges),
`src/haveParentSimpleObj` (56, all BLOCKED this session — asm-consumer
gated, re-check after those functions port), `ios/cdvd` (55, all BLOCKED),
`src/box` (52, `.data` already carved; other sections all BLOCKED),
`src/way_tool` (44, EXCLUDED — conv-6). `sound/s_init`/`src/camera-editor`/
`src/staticBlur` have ONE more `.sdata`/`.rodata`/`.lit4` slot each already
used (or reverted) per the one-run-per-section rule — re-scan them fresh
with `find_carves.py --emit` after a `git pull` in case upstream state
changed, and gate any new candidate run through the `.text`-equality
check before landing.

## Batch 4 — jtbl carve sweep (30 TUs, `.rodata`, all functions left ASM)

Complete sweep of the 101 `jtbl_*` symbols. Every jtbl was mapped to its
owner function (the `%hi(jtbl_…)` referencer), owner TU, and the rodata
neighbourhood the TU exclusively owns; the ~49 jtbl-owning TUs were then
classified (a) SAFE-FINAL / (b) NOT-FINAL against the one-contiguous-run
per (TU, section) rule. 30 (a) TUs landed here, one at a time, each with
`tools/build.sh setup` + `ninja` → `verify_elf: OK (fbf50c75…)`. Final
`rm -rf build` clean rebuild green; `check_no_rom.sh` clean. **No `.c`
file changed** — the carves are yaml-only.

### The two mechanisms that decide what is carvable today

1. **splat migrates jump tables into the owner function's `INCLUDE_ASM`
   stub, but NOT plain `D_` rodata.** Confirmed both ways:
   `asm/nonmatchings/src/motionOrientManager/shiftMotionOrientEndFunc.s`
   carries `dlabel jtbl_006196E0` but *not* `dlabel D_006196C8` (which is
   why that string needed a hand-written C definition), while
   `asm/nonmatchings/isys/obj_manager/soundOutputModeSet.s` gained a
   `.section .rodata` + `dlabel jtbl_00557B60` block the moment the carve
   was added. **Consequence: a jtbl-only carve needs no C at all; a carve
   covering any plain rodata needs a real typed C definition for it.**
2. **The only things gcc auto-emits into a TU's `.rodata` are switch jump
   tables and 8-byte `.lit8` double literals.** Strings and const
   aggregates are held by the repo-wide `extern` convention (every matched
   TU declares `extern char D_00xxxxxx[]` and the bytes stay in the
   `src/cod` blob), so they never force a carve to be re-cut. 4-byte float
   literals go to the separate `.lit4` subsegment (own section, own slot).
   **Consequence: a jtbl-only region is FINAL iff the TU owns no `.lit8`
   double outside it.** `.lit8` doubles are identified mechanically: an
   exactly-8-byte rodata symbol loaded with `ld $r, %lo(SYM)($r)` and
   handed straight to a call (e.g. `src/boyact`'s 0x558620 pool,
   `src/gflag`'s `D_0055A198` = 916.0). A 16-/32-/64-byte symbol loaded
   the same way is a float *vector*, not a literal — `D_0055AA60`
   (0,-200,-500,0) and `src/motionManager2`'s `D_00553C40` family are
   vectors and do NOT disqualify their TU.

### Region END is the table's TRUE entry count, not splat's dlabel

Splat's dlabel runs to the next label, so it absorbs gcc's `.align` pad
belonging to the NEXT object. Each table's true entry count was derived
from `baserom/baseelf.rom`: count the leading run of words that are
addresses inside the owner function's own `.text` range, stop at the first
that is not. Every trailing word between the true end and splat's next
label was verified to be `0x00000000` and is left in the blob. This makes
several regions end 4-aligned rather than 8-aligned (e.g. `isys/obj_manager`
0x557B74, 5 entries) — that is fine: `gen_ninja.py::align_for()` gives the
resume blob object an alignment that divides its own ROM address, so no
padding is injected. All 30 verified byte-identical with such ends.

| TU | carve (ROM off) | VMA range | jtbl(s) — owner switch, entries |
|---|---|---|---|
| `src/motionManager2` | `[0x453DB0]` | 0x553DB0..0x553DC8 | `jtbl_00553DB0` (AdjustVerticalSidePlaneOfWall, 6) |
| `src/tableSin` | `[0x453E70]` | 0x553E70..0x553E8C | `jtbl_00553E70` (func_0010DFB8, 7) |
| `src/FileManager` | `[0x454330]` | 0x554330..0x554430 | `jtbl_00554330` (11) + pad + `jtbl_00554360` (52), both func_0010EE90 |
| `ios/mcard` | `[0x456F10]` | 0x556F10..0x556F4C | `jtbl_00556F10` (iosMcMgrGetBlockSaveInfo, 15) |
| `ios/pad` | `[0x4576D0]` | 0x5576D0..0x557804 | `jtbl_005576D0` (iosPadDevInit, 77) |
| `isys/obj_manager` | `[0x457B60]` | 0x557B60..0x557B74 | `jtbl_00557B60` (soundOutputModeSet, 5) |
| `src/act-parallel-control` | `[0x458150]` | 0x558150..0x55818C | `jtbl_00558150` (func_0014B270, 15) |
| `src/camera-root` | `[0x45AA70]` | 0x55AA70..0x55AA84 | `jtbl_0055AA70` (BackToGameCamera, 5) |
| `src/ebrain` | `[0x45AE40]` | 0x55AE40..0x55AE84 | `jtbl_0055AE40` (7) + pad + `jtbl_0055AE60` (9), both func_00190F30 |
| `src/poly-flat` | `[0x45AFB0]` | 0x55AFB0..0x55AFD4 | `jtbl_0055AFB0` (IsPointIsInScreen, 9) |
| `src/gather_effect` | `[0x45C090]` | 0x55C090..0x55C158 | `jtbl_0055C090` (func_00197A38, 50) |
| `src/lightning` | `[0x45C670]` | 0x55C670..0x55C690 | `jtbl_0055C670` (func_00199F80, 8) |
| `src/debug` | `[0x514F10]` | 0x614F10..0x614F3C | `jtbl_00614F10` (func_001A3398, 11) |
| `src/gamesys` | `[0x5164D0]` | 0x6164D0..0x6164E4 | `jtbl_006164D0` (gamesysMemoryHandlerWrite, 5) |
| `src/kanban` | `[0x516CC0]` | 0x616CC0..0x616CE0 | `jtbl_00616CC0` (func_001B08E0, 8) |
| `src/layout_action` | `[0x5171B0]` | 0x6171B0..0x6171C4 | `jtbl_006171B0` (la_load_processing, 5) |
| `src/layout_texture` | `[0x5171E0]` | 0x6171E0..0x6171FC | `jtbl_006171E0` (lt_current_property_item, 7) |
| `src/staffroll` | `[0x517390]` | 0x617390..0x6173AC | `jtbl_00617390` (func_001B84C8, 7) |
| `src/handManager` | `[0x518F20]` | 0x618F20..0x618F38 | `jtbl_00618F20` (connectToTarget, 6) |
| `src/item` | `[0x518FB0]` | 0x618FB0..0x618FC4 | `jtbl_00618FB0` (uncarriedItemGeo, 5) |
| `src/lodManager` | `[0x5190E0]` | 0x6190E0..0x6190F8 | `jtbl_006190E0` (func_001D4BD0, 6) |
| `src/motionFileManager` | `[0x519100]` | 0x619100..0x6191D0 | `jtbl_00619100` (ResetStatic2MotionManager, 52) |
| `src/moveColTest` | `[0x519D80]` | 0x619D80..0x619D94 | `jtbl_00619D80` (MoveColTestGeo, 5) |
| `src/spider` | `[0x51A170]` | 0x61A170..0x61A184 | `jtbl_0061A170` (func_001EA5E8, 5) |
| `src/DisplayList` | `[0x51AC40]` | 0x61AC40..0x61AC60 | `jtbl_0061AC40` (dl_GetPri, 8) |
| `src/st04b` | `[0x51BCE0]` | 0x61BCE0..0x61BD00 | `jtbl_0061BCE0` (func_00217658, 8) |
| `src/cod/vendor_2453C0` | `[0x52E5F0]` | 0x62E5F0..0x62E654 | `jtbl_0062E5F0` (func_00246CD0, 25) |
| `src/cod/vendor_2517D0` | `[0x52ECD0]` | 0x62ECD0..0x62ECE4 | `jtbl_0062ECD0` (func_00251ED0, 5) — was `vendor_24E9D8` until the 2026-08-01 member-boundary re-carve moved its owner function |
| `src/cod/vendor_258CC0` | `[0x52F0E0]` | 0x62F0E0..0x62F2C0 | `jtbl_0062F0E0` (func_00258D10, 99) + pad + `jtbl_0062F270` (func_0025BA58, 20) |
| `src/cod/vendor_25E1E8` | `[0x52FE10]` | 0x62FE10..0x62FF74 | `jtbl_0062FE10` (func_00265CA0, 89) |

Two-jtbl regions (`src/FileManager`, `src/ebrain`, `src/cod/vendor_258CC0`)
span the 4-byte `.align 3` pad between the tables; the pad is reproduced
today by the stubs' own `.align 3` and, once the functions land, by gcc's
section alignment. Same bytes either way — verified.

### (b) NOT-FINAL — 19 TUs deliberately NOT carved

**Already hold their one `.rodata` run; the remaining jtbls cannot get a
second, disjoint region.** Widening the existing run would sweep in
plain rodata that needs typed C definitions first.

| TU | existing run | left out |
|---|---|---|
| `src/Packet` | jtbl_00554E00 | `jtbl_00554DB0`, `jtbl_00554FE0` — 14 TU-owned strings interleaved |
| `src/StageAnimation` | jtbl_00555990 | `jtbl_005559C0` — collapses into one wider carve when stage_SetAnimation lands (known) |
| `src/boyact` | .lit8 pool 0x558620 | 3 jtbls at 0x558300..0x558620 + 2 owned strings interleaved; 4 more `.lit8` outside |
| `src/girl_act` | jtbl_00559950 | 7 jtbls at 0x559570..0x559888, 17 owned syms interleaved |
| `src/debug_exception` | jtbl_00615090 | 6 jtbls, 37 owned strings interleaved |
| `src/motionOrientManager` | D_006196C8 + jtbl_006196E0 | `jtbl_00619960` — 12 owned strings in between |

**jtbls split by the TU's OWN non-jtbl rodata** — a single region covering
them all would need C definitions for the interleaved data, so the correct
carve depends on which functions land first: `src/Texture` (4 jtbls, 3
owned word tables between), `sound/soundManager` (4, 3), `src/enemy_act`
(4, 24 — mostly `.lit8`), `src/kanbanBoot` (6, 19), `src/box` (2, 1 string
`D_00618708`), `src/motionManager` (2, 1 + 5 `.lit8` outside),
`src/staticBlur` (3, 1 `D_0061A418`), `src/BgAnimation` (4, 8),
`src/cod/vendor_2418A0` (2, 5), `src/cod/vendor_2668B8` (7, 15 + 4 `.lit8`
outside).

**jtbls contiguous, but the TU owns genuine `.lit8` doubles OUTSIDE the
region** — gcc will emit those into the TU's `.rodata` the moment their
functions land, so a jtbl-only carve is not final:
`src/cod/vendor_100C90` (`D_00553748/50/58` = 0.1/0.1/1e6, immediately
*before* its jtbl), `src/gflag` (`D_0055A198` = 916.0, `D_0055A1A0`,
immediately *after* its jtbl), `src/chain` (5 doubles at
0x55AB20..0x55AB88, far from the jtbls at 0x55AD50). All three become
one-run carveable the day their double-using functions land in C —
`vendor_100C90` and `gflag` only need the region extended by one
neighbour, so they are the cheapest follow-ups.

### Successor notes

- The jtbl queue is now DONE for everything that is carveable without
  touching C. The remaining 19 TUs all need at least one plain-rodata C
  definition (string / const aggregate / `.lit8` double) before their
  single run can cover their whole footprint. Do them the
  `src/motionOrientManager` way: byte-verify the range against
  `baserom/baseelf.rom`, add a real typed `const` definition, leave the
  function `INCLUDE_ASM` if the body port does not close.
- `rm .port_cache/retail_labels.json` before the next `port_from_aug6.py`
  run — 30 new `dlabel`s just appeared.

## Phase 6 — FULL-RUN per-TU rodata carves (the durable model, 2026-07-31)

The per-jtbl / per-symbol-run carve treadmill above is retired as the
primary mechanism. Its structural wall: ONE contiguous carved run per
(TU, section) means every narrow carve forecloses that TU's remaining
rodata (girl_act's actGirlHang carve blocked its other five switch
functions), and the linker script's trailing `/DISCARD/ *(*)` silently
hides any compiled rodata a partial carve doesn't cover, so failures
surface only at the SHA gate (the commonact lone-string pilot).

The durable form: a TU owns its COMPLETE contiguous `.rodata` extent,
carved once. Everything needed already exists:

- **Per-symbol stub sections** (`include/labels.inc`): `dlabel` switches
  each splat-migrated rodata block into its own `.rodata.<sym>` section
  (rodata analog of `-fdata-sections` / `INCLUDE_ASM_FS`), so
  .o section order == source order == VMA order and stub-emitted bytes
  interleave freely with C defs and compiled jtbls (ee-gcc emits switch
  jtbls inline at the function's position). `glabel`/`endlabel`/
  `enddlabel` maintain `__in_text` so in-.text embedded data (vendor
  constant pools) is never yanked out. Spelled ee-as 2.9-compatibly:
  `sym = value` (its `.set` is options-only), `.align` (no `.balign`) —
  a failed ee-as pass silently falls back to modern gas, which fills
  jal delay slots the period assembler leaves as nop and shifts .text.
- **Boundary evidence** (`tools/map_data_tus.py`): per-symbol ownership
  stream (TU anchor / SHARED / UNREF / CARVED) over the blob
  disassemblies + consumer scan. The rodata address space has three
  zones: 0x553700..0x55CFA8 strictly .text-link-ordered per-TU runs
  (TUs #1..#87), 0x560C68..0x612348 a ~700KB big-table zone that does
  NOT follow link order (boyact motion tables, s_init banks — per-symbol
  carves stay the right tool there), and 0x612620.. a second strictly
  ordered region resuming at text#88 (DObj). All switch jtbls live in
  the two ordered zones. Interior foreign anchors inside a run are
  cross-TU externs (one-pass link contiguity guarantees ownership);
  only EDGE ambiguity matters, and a conservative edge is fine because
  a run can be extended later without structural debt.
- **Def generation** (`tools/emit_run_defs.py <tu> <start> <end>`):
  after the yaml carve + `build.sh setup`, prints the VMA-ordered
  emitter plan: `[stub …]` markers (bytes come from the stub's migrated
  blocks via INCLUDE_ASM), byte-verified `const` C defs for everything
  else (multi-string extents as single literals with embedded NULs,
  round-trip-verified against the ELF; splits at every C-referenced
  interior symbol), and `INCLUDE_RODATA(...)` lines for ≤8-byte symbols
  (a C def ≤8 bytes lands in .sdata under -G8 — Blocker 3's family).
  Defs are inserted so source order == VMA order; pre-def externs of
  the symbol become `extern const`, post-def externs are deleted.
- EUC-JP strings are spelled with raw EUC-JP bytes inline (splice with
  a python rb/wb script — UTF-8 editors corrupt them; the SHA gate
  catches it as U+FFFD replacement bytes).

Landed: `src/girl_act` [0x559430,0x559B50) (unblocks WayTest,
actGirlHand, actGirlPulledGo, GirlAct_BoyAndMeCollisionMail,
actGirlHangG3M), `src/commonact` [0x558848,0x558DC0), `src/enemy_act`
[0x558E10,0x5591F0) (unblocks jtbl_00558E40/559000/559130/559150;
NakaBoss's two switch tables were standalone splat-migrated
`.rodata.<sym>` stub files with no owning function INCLUDE_ASM in the
.c — wired in via `INCLUDE_RODATA`, same as the sub-8-byte symbols,
since their `.word` entries reference `.L` labels local to NakaBoss's
own still-nonmatching asm and can't be spelled as C), `src/Packet`
[0x554DB0,0x555490) (extended the narrow jtbl_00554E00 carve; unblocks
jtbl_00554DB0/554E00/554FE0. New wrinkle: `tools/emit_run_defs.py`'s
stub-span heuristic has a blind spot — a symbol referenced ONLY from
already-matched C (never from any remaining asm) is invisible to
splat's migration too, so it neither gets its own nonmatchings stub
file NOR shows up as "standalone" in the tool's plan; it silently
vanishes from the blob once the carve boundary crosses it. Caught by
cross-checking every `D_*` extern in the TU's `.c` against the full
`dlabel` inventory of `asm/nonmatchings/<tu>/*.s` post-setup — 4 such
gaps here (D_00554DD0, D_00554DE8, D_00555190, D_005551A0), hand-defined
byte-verified against baseelf), `src/StageAnimation` [0x555938,0x555E70)
(extended the narrow jtbl_00555990 carve; unblocks jtbl_005559C0
stage_SetAnimation, collapsing the two-carve NOT-FINAL note above into
one run as predicted). New failure mode: `include/labels.inc`'s
`dlabel` macro (used by BOTH `INCLUDE_RODATA` and, via gcc
`-fdata-sections`, every hand-written `const` def) hard-codes
`.align 3` on every per-symbol `.rodata.<sym>` section — its own
comment admits "a block whose VMA is only 4-aligned would need special
handling — none exists in the current split." D_005559F4 (a 116-byte
array) sits at exactly such a VMA, 4 bytes after the 4-byte
D_005559F0 with zero gap in the real ROM. A plain `const unsigned int`
def or `INCLUDE_RODATA` both silently ate a 4-byte `*fill*` there,
growing the ELF by 128 bytes and shifting everything after it (caught
by comparing `build/ico.rom` size against `baserom/baseelf.rom`, not
by the first byte diff — that showed up misleadingly early). Fixed by
hand-assembling D_005559E8/F0/F4 as ONE contiguous raw `__asm__` block
(bypassing `dlabel` entirely, own `.section .rodata.D_005559E8`
manually, no `.align`) starting from the already-8-aligned D_005559E8 —
`include/labels.inc` itself was not touched. 5 EUC-JP debug strings in
this run spliced via python rb/wb per the standing rule, `src/Texture`
[0x555E70,0x5565E0) (new carve, no prior narrow jtbl carve existed;
unblocks jtbl_00555F20/5560D0/5561C0/5562B0 — the last two live inside
tex_convertClutCSM2ToCSM1's own two-switch body, same shape as
FileManager/ebrain's two-jtbl-one-function carves. All 12 standalone
extents are multiples of 8 landing on an already-8-aligned run head, so
none of the dlabel align-3 landmine from StageAnimation). Batch
conversion of the remaining jtbl-bearing TUs recorded below as they
land, `sound/soundManager` [0x557E78,0x558150) (worklist flagged this
run as ambiguous — src/act-game anchors D_00557EE0/557F00 sit interior
between two soundManager blocks; RESOLVED by byte-decoding them off
baseelf: "too many view check object" / "src/act-game.c", genuinely
act-game content, so rule (a) applies and the full contiguous run is
safe rather than falling back to the narrower [0x557F10,0x558150)
alternative. Also hit a second instance of the matched-C-blind-spot
class from Packet: D_00557ED0 ("with mail\n", referenced only from
matched func_00144E30) sits in what emit_run_defs.py's heuristic
assumed was func_00144828's migrated span; func_00144828.s's last
dlabel actually ends 0x10 short of that assumption. Hand-defined),
`src/chain` [0x55AA90,0x55ADE0) (new carve; unblocks jtbl_0055AD50/
AD90/ADC0; 2 EUC-JP debug strings). `src/boyact` REVERTED — see the
Blocked TUs section below; do not retry without a matching-level fix.
`src/motionManager` [0x619220,0x619620) (new carve; unblocks
jtbl_006194B0/619530; 8 EUC-JP debug strings), `src/motionOrientManager`
[0x619620,0x619BB0) (extends the narrow D_006196C8 carve; unblocks
jtbl_006196E0/619960. Its existing top-of-file `const char D_006196C8`
had to MOVE to its real VMA-ordered position — gcc compiles
`-fdata-sections` globals in C DECLARATION order into the `.o`'s
section table, so a global declared at the top of the file lands
ahead of everything else regardless of its true VMA, and once the
carve widened to include shiftMotionOrientEndFunc's own embedded
D_00619620..D_006196B8 content ahead of it, the stale top position
broke the layout — moved the declaration down next to jtbl_006196E0's
wiring. Also: an editing mistake mid-attempt mixed Edit-tool calls
into a EUC-JP-bearing file already touched by python — silently
re-encoded every raw EUC-JP byte to UTF-8 U+FFFD, caught immediately
by a byte-count sanity check before ninja even ran, reverted, redone
as one python-only pass), `src/box` [0x6186A0,0x618808) (new carve;
unblocks jtbl_006186E0/618720; box.c is trace-reordered for .text via
INCLUDE_ASM_FS but the 5 functions/defs in this run are already
VMA-ordered in source so plain interleaving held; 3 EUC-JP strings).
`src/staticBlur` REVERTED — see the Blocked TUs section below (a
splat disassembly bug, not a carve-recipe problem), `src/BgAnimation`
[0x61A8C0,0x61AB50) (new carve; unblocks jtbl_0061A8F0/A9C0/AA20/AAB0,
first two standalone-wired; blind-spot D_0061AAF0 "illegal lightning
data set"; 4 EUC-JP strings), `src/cod/vendor_100C90`
[0x553700,0x553888) (new carve at the very start of the .rodata
segment; unblocks jtbl_00553760/func_001013E0's switch; 3 sub-8-byte
symbols via INCLUDE_RODATA, no C defs otherwise), `src/cod/vendor_2418A0`
[0x62E020,0x62E578) (new carve; unblocks jtbl_0062E260/E470, both
embedded in-function; run between src/PObj and
src/cod/vendor_2453C0's own pre-carve anchors), `src/cod/vendor_2668B8`
[0x62FF80,0x6308A8) (new carve; unblocks all 7 jtbls
630020/6301C0/6303B0/6303D0/630510/630640/6307D0. Run ends at the
TRUE .rodata ELF section end, not the yaml-neighboring .lit4 start —
0x58 bytes of linker alignment gap sit between them, not PROGBITS
content. Two new landmine classes hit here: a const array ≤8 bytes
routes to .sdata under -G8 even when declared `const` — same fix as
INCLUDE_RODATA's purpose but for a genuine matched-C blind spot
(D_00630698) with no generated stub file at all, and for a second
gcc-compiled def (D_006308A0) that hit the same threshold; and
D_006306B0 is an array of 25 64-bit `long` (a pow10-as-double-bits
table) rather than unsigned int — spelling it as unsigned[50] silently
compiled a shift-by-2 index in its one matched caller where the ROM
has shift-by-3, an 8-byte regression only visible by diffing raw
instruction words, not by size), `src/gflag` [0x559E60,0x55A1B0)
(new carve; unblocks jtbl_0055A170, embedded in-function. This is
the worklist's flagged interleaved gflag/script/warpGirl zone —
SHARED and foreign anchor blocks scatter through 0x559F80..0x55A020,
but every one is strictly interior to clean gflag/st25a edge
boundaries, so the full contiguous run landed on the first attempt
with no need for the narrower jtbl-only fallback; 9 EUC-JP strings).
Batch conversion of the remaining jtbl-bearing TUs recorded below as
they land. Decided runs + evidence live in the yaml carve comments and the
per-TU sections below (`decomp/data_tu_boundaries.json` is gitignored —
regenerable local evidence, not the record).

### Interleave zones resolved + text audit clean (2026-08-01)

The two formerly-deferred interleave zones are landed: `src/kanbanBoot`
[0x616CE0,0x617170) + `src/layout_action` [0x617170,0x6171C4), and
`src/debug_exception` [0x615060,0x615900) + `src/debug_menu`
[0x615900,0x615B60). The contested spans were settled by their
referencing `.data` pointer tables (debug_exception's D_004B3110/20 vs
debug_menu's menu table D_004B3140), not position heuristics. The
.text side audits clean: 0 splat merges and 0 fall-through boundary
violations across 4987 functions (delay-slot-aware, coroutine-`b`
aware). Every switch-bearing TU in both ordered rodata zones now owns
its full run except the two reverted cases (boyact li.d pool,
staticBlur splat .asciz bug).

Tool hardening from this pass: `emit_run_defs.py` now verifies a
C-referenced symbol that falls inside a stub's span against the stub's
actual `dlabel`s before assuming the stub emits it (debug_exception's
D_006150F0, referenced only via a matched-C `__asm__` alias, had no
emitter -> silent 0x10-byte shortfall at the SHA gate). And
`patch_splat.py` gained the EUC-JP-tolerant C-scan read: raw EUC-JP
bytes in a TU source made splat's INCLUDE_ASM scan return an empty set,
misclassifying every function of that TU into `asm/matchings/` on a
truly clean re-split.

## Blocked: `src/staticBlur` full-run carve reverted (2026-07-31)

Attempted run [0x61A2C0,0x61A470) (jtbl_0061A3F0/A430/A450, all
embedded in-function so no standalone wiring needed). Landed defs and
build FAILED with a 6-byte mismatch inside `fillWork2`'s own
INCLUDE_ASM'd span, unrelated to anything this recipe writes:
splat's disassembly of `asm/nonmatchings/src/staticBlur/fillWork2.s`
renders `D_0061A350` as `.asciz "BLUR $R: %d"` — a stray `$` before
the `R` that is NOT in the ELF (baseelf bytes are `BLUR R: %d`,
confirmed both by direct byte extraction and by the file's own hex
comment `424C555220523A2025640000`, which decodes to `BLUR R: %d`
with no `$`). This is a pure splat transcription bug in the
`.asciz`-reconstruction path for per-function rodata migration —
never triggered before because this address always shipped as raw
hex in the shared blob (byte-accurate by construction there), and
only surfaces now that the address is asked to round-trip through
`.asciz`.

Hand-patching the generated `.s` file (verified to fix the byte and
survive an un-forced re-run of `tools/build.sh setup`, since splat
skips regenerating an already-present nonmatching stub) is NOT a
durable fix: `asm/**` is entirely gitignored on this branch
(`.gitignore:51`, "All of these are reproducible from the ELF, so
they stay gitignored") — nothing under `asm/nonmatchings/` is
tracked, confirmed via `git ls-files asm/`. Deleting and
regenerating the file reproduces the identical bug, proving it is
deterministic in splat, not a stale artifact. A hand-fix would vanish
on the next clean `asm/` regen (a fresh clone, or the pre-commit
hook's full setup from a wiped tree), silently reintroducing the
mismatch — so it was reverted rather than committed.

`config/ico.us.yaml` and `src/staticBlur.c` are back to the
pre-attempt state (verified green with the ORIGINAL narrow-blob
layout, i.e. this address range still lives in the shared
`src/cod` blob). Do not retry until the splat `.asciz` transcription
bug is fixed upstream, or a policy decision authorizes a tracked
override for this one symbol.

## Blocked: `src/boyact` full-run carve reverted (2026-07-31)

Attempted run [0x5581D8,0x558848) (jtbl_00558300/5584D0/558510). The
narrow existing carve `[0x458620, .rodata, src/boyact]` (the .lit8 pool,
doubles 0.2/0.9/0.2/0.7 used by matched func_00151868/func_001519D8's
literal float args) is NOT relocatable into a wider carve without a
genuine matching-level fix, for a reason distinct from every other
landmine in this ledger:

ee-gcc/gas expand the `li.d` pseudo-op (used whenever a C function
loads a `double` literal, e.g. `func_00262BE8(r1, 0.2)`) into a
POOLED LOAD from an assembler-internal literal pool that lands in the
**plain, unnamed `.rodata` section** — not a `-fdata-sections`-named
one. That section is a STANDARD section gas pre-allocates early in
every TU's object (same root cause as the `.data`/`.bss` alignment
floor `compile_c.sh` already patches via
`--set-section-alignment ".data=1" ".bss=1"` — see "Root cause of
Blocker 2" below); confirmed empirically (`objdump -h`) it sits at
section index 5 in `build/src/boyact.o`, AHEAD of every named
`.rodata.<sym>` section regardless of where in the C source the
literal is used. Verified via 4 independent hand fixes, none clean:

1. Plain `const unsigned int`/`INCLUDE_RODATA` defs for
   D_00558620/628/630/638 (the splat-disassembled names for this same
   address range): duplicates the pool (both a named section AND 32
   extra bytes in the generic section), +128B, MISMATCH.
2. Hand-assembled raw `__asm__` named sections (bypassing `dlabel`
   entirely, same lever that fixed StageAnimation's align-3 case):
   still duplicates — the generic section is gcc's OWN emission, not
   ours, so nothing on our side controls it.
3. Same as (2) but with ZERO explicit C definition for the 4 doubles at
   all (trusting gcc's own pool to supply them): pool still lands at
   the run's START VMA (0x5581D8) instead of its true 0x558620 — an
   ld single-glob `(.rodata*)` pulls sections in `.o` encounter order,
   and gas's standard `.rodata` slot is allocated before any of ours
   regardless of C source position.
4. Route func_00151868/func_001519D8's literal args through
   `extern double D_X __asm__("D_00558620")`-style aliases (matching
   the alias-of-last-resort pattern already used elsewhere in this TU)
   so the LOAD targets our named symbol instead of an anonymous pool
   entry: this DOES fix the carve (0 diffs in [0x5581D8,0x558848)) but
   REGRESSES the two already-matched functions by 8 bytes total (a
   `lui` register differs, `$1`/`$at` vs `$5` — gcc's `li.d` pseudo
   picks a different scratch register than its normal `%hi`/`%lo`
   global-symbol addressing). A follow-up (route through local `double`
   temporaries first) made it much worse (+128B, 583 diffs) and was
   also reverted.

Fixing (4)'s register choice is a genuine matching-lever problem (same
family as `dead_arg_reg`/regalloc levers elsewhere in this codebase),
not a data-carve mechanism — out of scope here. `config/ico.us.yaml`
and `src/boyact.c` were reverted to the pre-attempt state (verified
green). Do not retry the full-run carve without first re-matching
func_00151868/func_001519D8 against the aliased-symbol form.

## Batch 5 — vendor member-boundary re-carve of the 0x252D28 region (2026-08-01)

**What changed.** The `[0x152D28, c, vendor_252D28]` 96-function chunk carve
merged parts of SIX archive members, and its 0x252D28 start fell mid-member
inside `libmpeg.a(mpc.o)`. Replaced with true member-boundary TUs; the
`vendor_24E9D8` chunk now ends at the `mpc.o` start:

| TU | member | VMA span |
|---|---|---|
| `vendor_2517D0` | `libmpeg.a(mpc.o)` | 0x2517D0..0x2564E0 |
| `vendor_2564E0` | `libmpeg.a(csc.o)` | 0x2564E0..0x256BF8 |
| `vendor_256BF8` | `libmpeg.a(bit.o)` | 0x256BF8..0x256DF8 |
| `vendor_256DF8` | `libipu.a(libipu.o)` | 0x256DF8..0x257128 |
| `vendor_257128` | `libipu.a(ipuinit.o)` | 0x257128..0x2575C0 |
| `vendor_2575C0` | `libsndn2.a(sound.o)` head | 0x2575C0..0x258CC0 (member continues into `vendor_258CC0`) |

**Boundary evidence.** Per-function aug6-twin mapping (`.port_cache/
name_alias.json`, delta +0x3C70 throughout this region) binned against the
aug6 MAIN.MAP member spans (`baserom/aug6/text_tu_boundaries.txt` on the
aug6 worktree). Boundaries were then pinned to *retail function starts*
(all 8-aligned), NOT projected addresses — retail member sizes drift from
aug6 (e.g. aug6's projected csc.o start 0x256478 lands mid-way through
retail `func_002563C8`; the retail boundary is the next function start,
0x2564E0). Five retail-only functions with no aug6 twin (func_00252F90,
func_002532C8, func_00255410, func_00256C30, func_00257DE0) all sit
interior to member spans, so no boundary is ambiguous. The exact retail
`mpc.o` start is bracketed to (0x251248+sizeof(func_00251248), 0x2517D0];
0x2517D0 is the first function positively attributed to mpc.o (aug6 has
~0xC0 of unattributed mpc.o head before its first twin), so the split sits
there. `MAIN.MAP` addresses were never used to verify retail placement
(different link).

**Why (the assembler finding).** Under the period assembler the OLD merged
stream made the R5900 short-loop-erratum pass insert 10 spurious nops into
`func_00254328` (both backward branches padded 5 each), which a
forward-defined label alias had to suppress (commit b5788929). Empirics
recorded so far: the pass mis-measures the ~26-insn loop as 1 insn under
the old carve's exact 8573-line stream; the block is clean standalone,
clean behind >12KB of synthetic filler (plain insns, labelled backward
branches, `%hi` reloc insns, `.align`+label units — none trigger), clean
when almost ANY single preceding function is dropped from the real stream,
and clean in the TRUE `mpc.o` TU even though that puts MORE content before
the loop than the old carve did. I.e. the trigger is a whole-stream
configuration artifact, not stream position; delta-minimisation could not
reduce the triggering prefix below ~1450 real lines. With the re-carve the
direct `.L0025071C` labels assemble byte-identical and the alias is
retired. (This also explains the Batch-2 note on `func_00254C98`: the
"rewriting two `.word`s inserts 10 nops 0x1600 earlier" effect was the
same configuration sensitivity, and it is moot under the new carve.)

**Mechanics of the split.** All 96+96 functions redistributed by contiguous
line ranges; every moved *matched* C body was verified by compiling each new
TU with the production CFLAGS and diffing per-function `.s` bodies
(local-label-normalised) against the pre-split TUs — three extern decls had
to move with the sound part (`D_005524A4`, `func_00251CF8`, and signatures
for `func_00252590`/`func_00255F50`) to keep `func_00257CF8`'s $2/$3
register tie: an implicitly-declared callee (assumed `int` return) flips
it. The `jtbl_0062ECD0` `.rodata` carve moved with its owner function
(`func_00251ED0`) to `vendor_2517D0`; splat only inlines a jtbl into the
owner's `.s` when the jtbl subsegment names the owner's TU, otherwise the
link fails on an undefined `jtbl_*` — same rule Batch 4 stated, now
observed from the failing side. Gate: full distclean + setup + ninja →
`verify_elf: OK sha1=fbf50c75…`, zero assembler fallbacks,
`use_modern_as.txt` still empty.

## PAL phase 1 — `.lit4` constant-pool carves + one `.sdata` literal (2026-09-04)

Target: `main` = PAL retail SCES-507.60.  Scope: the 32 bodies in 12 TUs that
`tools/port_from_ntsc.py` reverted with reason `emits-data`
(`decomp/port_ledger_pal.md`).  All 13 carves below landed together and the
tree is SHA-green from a clean rebuild (`rm -rf build .ninja_log .ninja_deps`
+ `tools/build.sh setup` + `ninja` -> `verify_elf: OK
(a401d1e5a20b1659189a8b1026a8eb35811dc9ca)`), `check_no_rom.sh` clean.
All 32 bodies are ported.

### Landed

| TU | section | carve (ROM off) | VMA range | bytes | slots/syms | MAIN.MAP size |
|---|---|---|---|---|---|---|
| `src/matrixDrive` | `.lit4` | `[0x538B0C]` | 0x638B0C..0x638B3C | 48 | 12 (all 0.01f) | 0x30 — agrees |
| `src/motionManager2` | `.lit4` | `[0x538B3C]` | 0x638B3C..0x638B84 | 72 | 18 | 0x48 — agrees |
| `src/act-game` | `.lit4` | `[0x538CC8]` | 0x638CC8..0x638D10 | 72 | 18 | 0x40 — differs |
| `src/commonact` | `.lit4` | `[0x538E3C]` | 0x638E3C..0x638EF4 | 184 | 46 | 0xb4 — differs |
| `src/enemy_act` | `.lit4` | `[0x538EF4]` | 0x638EF4..0x638F5C | 104 | 26 | 0x68 — agrees |
| `src/way_util` | `.lit4` | `[0x539060]` | 0x639060..0x639090 | 48 | 12 (all 100000f) | 0x30 — agrees |
| `src/st25a` | `.lit4` | `[0x5390D4]` | 0x6390D4..0x639108 | 52 | 13 | 0x44 — differs |
| `src/act_bird` | `.lit4` | `[0x539230]` | 0x639230..0x639294 | 100 | 25 | 0x64 — agrees |
| `src/debug` | `.lit4` | `[0x539338]` | 0x639338..0x639358 | 32 | 8 | 0x18 — differs |
| `src/layout_action` | `.lit4` | `[0x539360]` | 0x639360..0x63936C | 12 | 3 | 0x8 — differs |
| `src/staticBlur` | `.lit4` | `[0x5396A8]` | 0x6396A8..0x6396B0 | 8 | 2 | 0x8 — agrees |
| `src/stageSEProc` | `.lit4` | `[0x539B18]` | 0x639B18..0x639C44 | 300 | 75 | 0x138 — differs |
| `src/commonact` | `.sdata` | `[0x53A738]` | 0x63A738..0x63A740 | 8 | 1 ("reset\n" + ROM pad byte) | 0x6d for the whole member — differs |

Every carve line in `config/ico.pal.yaml` carries the USA counterpart verbatim
(`USA: - [...]`) so the provenance travels, or says "no `.lit4` carve for this
TU" where USA had none (`st25a`, `debug`, `layout_action`, `stageSEProc`).

### How a `.lit4` carve is made to hold

`.lit4` is built by the ASSEMBLER, not the compiler: ee-gcc emits `li.s
$fN,<value>` for a float constant and ee-as interns each new literal into the
object's anonymous `.lit4` **in the order it meets them in the `.s` stream**,
with no de-duplication (`src/way_util` ships twelve identical `100000.0f`
words, one per waypoint-search function).  A TU's pool is therefore ONE output
section whose content is fixed by source order, and the carve is final only if
EVERY word of the shipped run is produced by that TU's own object.  Words whose
owner is still `INCLUDE_ASM` are supplied by `ASM_LIT4_SLOT(D_<VMA>, <value>)`
(`include/include_asm.h`), which emits a `.lit4_slot` directive that
`tools/preprocess_old_as.py` turns back into the sibling's original `li.s` —
ee-as cannot assemble a *named* symbol defined in `.lit4` at all
(`nopic_need_relax()` asserts on it).  Landing a body then deletes exactly one
`ASM_LIT4_SLOT` and the body's own literal produces that word, so the object's
data size is unchanged and `port_from_ntsc.py`'s "may add code, never data"
gate passes.  `preprocess_old_as.py` errors on a stale slot and on a slot
reached by a non-FP load, so the two halves can never drift apart silently.

Values are spelled as the shortest decimal that round-trips through binary32
(`0.01f`, `10430.378f`, `1.0000001e-06f`) — generated from
`baserom/pal/baseelf.rom`, not copied from splat's `.float` rendering.

### Evidence, and how the runs were cut

`tools/map_data_tus.py --sect lit4 --runs` plus a per-word owner scan over
`asm/{non,}matchings/**/*.s`: every `.lit4` word is loaded by exactly one
function, so per-TU ownership is exact and the PAL `.lit4` stream is strictly
link-ordered per TU (TU #0..#186 ascending, no interleaving).  Each of the 12
runs was checked to be **exclusively** owned by its TU with no foreign or
already-matched-C word inside it before the carve went in.  Two runs came out
different from `map_data_tus.py`'s collapsed view, which folds unattributed
neighbours into the preceding run: `src/act-game` really ends at 0x638D10
(0x638D10..0x638D30 is `src/act-wish`), and `src/staticBlur` really ends at
0x6396B0 (0x6396B0..0x6396C8 is `src/stormTest`).  The per-word owner scan is
the authority; the `--runs` view is a first cut.

**MAIN.MAP is a size cross-check, not an oracle — and it disagrees more often
than it agrees here.**  `baserom/pal/MAIN.MAP`'s `.lit4` output section is
0xfb0 bytes against the shipped ELF's 0x1154, i.e. it is a genuinely different
(earlier) link, and only 6 of the 13 member sizes match the PAL ELF's own
runs.  Where they disagree the reference stream wins; the disagreement is
recorded in each yaml comment rather than reconciled.

### New rule this batch established (write it down before the next carve)

**A carve that contains an ANONYMOUS constant must START at that constant's own
VMA.**  `-fdata-sections` gives a section only to a `VAR_DECL`; a string
literal, an `li.d` double or an interned `.lit4` word has no `.<sec>.<sym>` of
its own and lands in the object's plain `.sdata` / `.rodata` / `.lit4`, which
gas allocates ahead of every named per-symbol section.  An `ld` single-glob
`<tu>.o(.<sec>*)` pulls sections in `.o` encounter order, so the anonymous
blob is placed at the run's START no matter where the literal sits in the C.
This is the positive statement of the `src/boyact` `.lit8` blocker above, and
it decided this batch's only `.sdata` carve: `afterCommonBar`'s `"reset\n"`
is a `<=8`-byte string constant, which gcc routes to `.sdata`
(`mips_select_section`) and never gp-addresses (the ROM reaches it with a
`%hi/%lo` pair at 0x163D68/0x163D74).  `src/commonact`'s full `.sdata` run is
0x63A710..0x63A7E0 (208 B, ~17 more such literals from still-`INCLUDE_ASM`
siblings), and "reset\n" sits at 0x63A738 — six literals in.  Carving the
full run would have put the object's single anonymous constant at 0x63A710.
So the carve is the narrow 8 bytes at 0x63A738 exactly.

**Structural debt this creates (one item):** by the one-contiguous-run-per-(TU,
section) rule, `src/commonact` has now spent its `.sdata` slot on 8 of its 208
bytes.  Widening it to the full run needs the other ~17 literals' owners in C
first, in VMA order, and the widened carve must then start at 0x63A710 with
the FIRST of those literals.  Nothing else in this batch is foreclosed:
the 12 `.lit4` carves each cover their TU's complete pool run.

### One crutch rode in with a ported body and was retired

`src/way_util`'s ntsc bodies carried
`extern void sceVu0SubVector__pn(void*,void*,void*) __asm__("sceVu0SubVector");`
alongside the TU's existing K&R `extern void sceVu0SubVector();` — the
`<name>__<suffix>` second-alias-for-an-already-declared-symbol form CLAUDE.md
names as the gcse-bucket tell.  Deleted and every call routed through the
plain declaration: `ninja` still `verify_elf: OK`, so the alias emitted no
bytes and steered nothing that matters.  Nothing else in the 32 ported bodies
trips the ban.

### Tooling fixed on the way (both were `us`/`aug6`-only)

- `tools/find_carves.py` — `ASM_ROOT` resolved to `asm/pal` (the yaml says
  `asm`) and `SRC_ROOTS` fell through to the aug6 per-programmer tree, so it
  scanned nothing on this branch.  `pal` now shares the flat retail roots.
- `tools/map_data_tus.py` — hard-coded `config/ico.us.yaml`; now picks the
  yaml from `tools/ico_version.detect_version()`.

### Not attempted here

The other data the 12 TUs own (`.data` / `.rodata` runs, and `.sdata` beyond
the one literal) is untouched: none of the 32 reverted bodies needed it.  The
Phase-6 full-run `.rodata` model has not been started on PAL at all — every
`.rodata` byte is still in the `src/cod/44D380` blob.

