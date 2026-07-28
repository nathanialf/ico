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

## SHARED-symbol hotlist (seen so far, not carved — owner ambiguous)

None yet logged from a genuine multi-TU CARVE-candidate sweep — the four
TUs above only needed their jtbl region. The broader per-TU ranking pass
(`find_carves.py <tu>` across the ~200 already-ported TUs) is the next
piece of this phase and will populate this section; see the recommended
next TUs below.

## Recommended next TUs (successor should start here)

Not yet attempted this session — ranked by `find_carves.py`'s CARVE count
once run per-TU; a fast way to generate the candidate list:
`for tu in <ported TUs>; do python3 tools/find_carves.py "$tu" 2>/dev/null | tail -1; done`
and sort by the `CARVE=N` count. Prioritize TUs whose report shows
`SHARED=0 BLOCKED=0` (or blocked-only-in-.bss, which is expected and fine)
so every referenced symbol lands cleanly without a cross-TU ownership
question. `src/Packet`, `src/girl_act`, and `src/motionOrientManager`
(seen in this session, tails above) all have substantial CARVE counts
(67, and more) beyond just their jtbl — worth full carve passes next since
their `find_carves.py` output is already captured/warm.
