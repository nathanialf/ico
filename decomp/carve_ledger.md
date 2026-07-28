# Phase 5 — per-TU data carve ledger (retail-v2)

Tracks noncontiguous-data carves landed under the aug6 carved-subsegment
convention (`decomp/NOTES.md` §"Noncontiguous data"). One entry per TU:
sections carved, symbol count, source of types, and any SHARED symbols
left in the blob for a future pass. Kept small by design — this is an
index, not a diff dump; `git log` has the byte-level detail per commit.

Tooling: `tools/find_carves.py <tu>` (version-aware via `tools/ico_version.py`
— auto-detects `us` vs `aug6`, same CARVE/SHARED/BLOCKED classification on
both) is the source of truth for what's safe to carve. `--emit` prints the
yaml dot-form lines + a raw-byte C scaffold for every CARVE-verdict symbol.

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

**Reproducible, isolated via bisection, NOT yet root-caused or fixed.**
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

**Practical implication**: until this is root-caused and fixed, ONE plain
named-data carve can be landed per commit/session at most (verify with a
`rm -rf build` clean rebuild before trusting `ninja`'s cache — several
false "it still fails" / "it works now" readings this session turned out
to be stale `build/` state, not real signal). jtbl-associated `.rodata`
carves (the batch-1 pattern) are UNAFFECTED — 4 of them already coexist
cleanly on `main`/`HEAD` — so that pattern scales fine; it's specifically
non-jtbl named data (`.data`/`.sdata`/`.lit4`, any TU) that's capped at 1.

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

**Before picking a new TU: root-cause Blocker 2 above.** It's the actual
bottleneck — every TU on the ranked-by-CARVE-count list below has 15-124
CARVE symbols, and landing only one at a time makes this phase impractical.
Instrument `tools/gen_ninja.py` / splat's linker-script generation for the
`.data`/`.sdata`/`.lit4`/`.rodata` glob-building code path and compare its
behavior for 1 vs 2 dot-form carve entries directly (not via post-hoc
`nm`/`objdump` archaeology).

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
