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
