#!/usr/bin/env python3
"""progress_tree.py — emit docs/progress.json for the GitHub Pages site.

Builds a programmer -> TU -> function tree of decompilation progress,
mirroring (and extending to function granularity) the section numbers
`tools/progress.py` already computes. The output is IP-clean by
construction: it contains only address-derived function names, byte
sizes, and matched/unmatched booleans — no ROM bytes, no disassembly.

Sources (all git-tracked, no base ELF required):
  - config/symbol_addrs.<ver>.txt : every `type:func` symbol, its
    address, and the owning TU (from the trailing `// <path>.c` or
    `// <path>.S` note). Function sizes are next-symbol-address deltas.
  - <TU>.c INCLUDE_ASM(...) directives : the still-asm (unmatched)
    functions inside a started TU. A function is "matched" iff its TU
    `.c` exists and the function is NOT INCLUDE_ASM'd there.
  - <TU>.S sources : hand-written assembly TUs (the VU1 microprograms
    in src/). These are `hasm` subsegments — assembled and linked
    byte-identically, with no INCLUDE_ASM left to retire — so every
    function in one counts as matched once the `.S` exists. This
    mirrors progress.py, which already folds `hasm` into the matched
    tally for `.vutext`.
  - `// (vendor)` notes : library-archive functions, emitted under the
    `// ---- (vendor)` section headers by tools/gen_us_symbol_addrs.py.
    These are NOT ICO translation units — see decomp/VENDOR.md.

Bucketing rules (see decomp/VENDOR.md for the policy behind them):
  - a `// <path>.c` / `// <path>.S` note  -> that TU, grouped by the
    leading path component (retail's flat `src/` collapses to "src").
  - a `// (vendor)` note                  -> the "vendor" group, split
    into one node per contiguous address run (the crt0 + libkernl head
    and the libc / libgcc / SDK tail bracket the game code).
  - no note at all                        -> the "(unassigned)" group.
    This is a DATA BUG, not a category: every function belongs to a TU
    or to a vendor archive. The node exists so an unnoted symbol is
    visible instead of being silently miscounted as vendor (which is
    what this script did before 2026-07-28).

Section accounting: the headline `totals.matched_bytes/total_bytes` is
the ELF `.text` section only, exactly as progress.py measures it and as
the README badge reports it. The five VU1 microprograms live in a
different ELF section (`.vutext`), so they are grouped separately and
counted in `totals.sections` — never folded into a `.text` roll-up.

Run via `tools/build.sh progress` (which also runs progress.py) so the
JSON stays in lockstep with the README badges and PROGRESS.md table.
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

# Authoritative .text byte totals come from progress.py (same tools/ dir),
# which measures against the real baseelf.elf `.text` section size and counts
# `c`+`hasm` subsegs as matched — the accurate metric that reaches exactly
# 100% at full match. We reuse it for the dashboard's headline "code bytes"
# figure so it agrees with the README badge to the byte. It needs the base
# ELF; when that's absent (CI / fresh checkout) we fall back to the ELF-free
# per-function symbol-delta sum below.
try:
    import progress as _progress  # tools/progress.py (script dir is on sys.path)
except BaseException:
    # BaseException, not Exception: progress.py sys.exit()s at import when
    # PyYAML / pyelftools / the base ELF are missing, and SystemExit does not
    # derive from Exception — so the ELF-free fallback documented above never
    # actually engaged, it just killed this script.
    _progress = None

# `main` = PAL retail (pal), `ntsc` = USA retail (us), `aug6` = the prototype.
# Explicit VERSION env wins; else detected from which config/ico.<ver>.yaml
# this tree carries. (Imported after progress.py above so both agree.)
from ico_version import detect_version  # noqa: E402

VERSION = detect_version(REPO_ROOT)

SYMBOLS = REPO_ROOT / "config" / f"symbol_addrs.{VERSION}.txt"
OUT_JSON = REPO_ROOT / "docs" / "progress.json"

# Base VMA of the `cod` code segment == start of `.text`.
TEXT_START = 0x00100000

# A gap larger than this between consecutive function symbols is treated
# as interleaved non-code (data/padding) rather than one giant function,
# so a single trailing symbol before a data blob can't inflate the tree.
MAX_FUNC_SIZE = 0x4000

# `Name = 0xADDR; // type:func  // path/to/tu.c`
_SYM_RE = re.compile(
    r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*type:func\b(.*)$"
)
# `.c` for decompiled TUs, `.S` for hand-written assembly TUs. Anything
# else leaves the symbol unassigned.
_TU_NOTE_RE = re.compile(r"//\s*([\w./-]+)\.([cS])\b")
# `// (vendor)` — a library-archive member, not an ICO TU.
_VENDOR_NOTE_RE = re.compile(r"//\s*\(vendor\)")
_INCLUDE_ASM_RE = re.compile(
    r'\bINCLUDE_ASM(?:_NOAT)?\s*\(\s*"[^"]+"\s*,\s*(\w+)\s*\)'
)

VENDOR_GROUP = "vendor"
VUTEXT_GROUP = ".vutext"
UNASSIGNED_GROUP = "(unassigned)"

VENDOR_NOTE = (
    "Library archive members linked from pre-built .a files (crt0, SCE SDK, "
    "newlib/libgcc) — not ICO source. These bytes are already inside the "
    "SHA-1 gate, satisfied by assembled ROM asm. See decomp/VENDOR.md."
)
VUTEXT_NOTE = (
    "VU1 microprograms in the .vutext ELF section — hand-typed src/*.S, "
    "assembled byte-identically. Counted separately from .text so the "
    "headline .text figure is not inflated."
)
UNASSIGNED_NOTE = (
    "Symbols in config/symbol_addrs with neither a `// <path>.c` TU note nor "
    "a `// (vendor)` note. This bucket should be empty — anything here is a "
    "missing note in symbol_addrs, not a real category."
)

# In link order, the vendor archives bracket the game code: crt0 + libkernl
# in front, the libc / libgcc / SDK tail behind. Same split the symbol
# generator documents at tools/gen_us_symbol_addrs.py (VENDOR label comment).
VENDOR_RUN_LABELS = [
    "crt0 + libkernl prologue",
    "libc / libgcc / SCE SDK tail",
]


def _parse_symbols() -> list[dict]:
    """[{name, addr, tu, ext, vendor}] for every type:func symbol, sorted."""
    if not SYMBOLS.exists():
        sys.exit(f"progress_tree: {SYMBOLS} not found")
    out: list[dict] = []
    for line in SYMBOLS.read_text().splitlines():
        m = _SYM_RE.match(line)
        if not m:
            continue
        name, addr_hex, rest = m.group(1), m.group(2), m.group(3)
        tu_m = _TU_NOTE_RE.search(rest)
        out.append({
            "name": name,
            "addr": int(addr_hex, 16),
            "tu": tu_m.group(1) if tu_m else None,
            "ext": tu_m.group(2) if tu_m else None,
            "vendor": tu_m is None and bool(_VENDOR_NOTE_RE.search(rest)),
        })
    out.sort(key=lambda s: s["addr"])
    return out


def _section_bounds(syms: list[dict]) -> dict[str, tuple[int, int]]:
    """{section: (start_vma, end_vma)} for the code sections we tally.

    `.vutext` starts at the first `.S` (hand-assembly) symbol — the VU1
    microprograms are the only thing in it. Section END addresses come
    from progress.py's ELF measurement; without the ELF we leave them
    open-ended and fall back to plain next-symbol deltas.
    """
    vu_starts = [s["addr"] for s in syms if s["ext"] == "S"]
    vutext_start = min(vu_starts) if vu_starts else None

    sizes: dict[str, int] = {}
    if _progress is not None:
        try:
            sizes = {k: v[1] for k, v in _progress.compute_progress().items()}
        except Exception:
            sizes = {}

    bounds: dict[str, tuple[int, int]] = {}
    text_end = TEXT_START + sizes[".text"] if ".text" in sizes else vutext_start
    bounds[".text"] = (TEXT_START, text_end if text_end else 1 << 62)
    if vutext_start is not None:
        vu_end = (vutext_start + sizes[".vutext"]) if ".vutext" in sizes \
            else 1 << 62
        bounds[".vutext"] = (vutext_start, vu_end)
    return bounds


def _assign_sizes(syms: list[dict], bounds: dict[str, tuple[int, int]]) -> None:
    """Set sym['section'] and sym['size'] in place.

    A function's size is the distance to the next symbol, clamped to the
    END OF ITS OWN SECTION. Without the section clamp the last `.text`
    function absorbed the 12 bytes of inter-section pad before `.vutext`,
    and the last `.vutext` function (having no successor) got size 0 —
    together the exact reason the per-group byte sums used to overshoot
    the `.text` headline by 19,260.
    """
    for i, sym in enumerate(syms):
        sec = ".text"
        for name, (lo, hi) in bounds.items():
            if lo <= sym["addr"] < hi:
                sec = name
                break
        sym["section"] = sec
        end = bounds.get(sec, (0, 1 << 62))[1]
        if i + 1 < len(syms):
            end = min(end, syms[i + 1]["addr"])
        if end >= 1 << 61:          # open-ended (no ELF) and no successor
            end = sym["addr"]
        sym["size"] = max(0, min(end - sym["addr"], MAX_FUNC_SIZE))


def _unmatched_funcs_for_tu(tu: str, ext: str) -> set[str] | None:
    """Set of still-unmatched function names in the TU source, or None if
    the TU hasn't been started (no source yet -> every func unmatched).

    For a `.S` TU the answer is always the empty set once the file
    exists: a hand-written assembly subsegment is `hasm` in the yaml and
    links byte-identically, so there is nothing left to retire.
    """
    src = REPO_ROOT / f"{tu}.{ext}"
    if not src.exists():
        return None
    if ext == "S":
        return set()
    try:
        text = src.read_text(encoding="utf-8", errors="replace")
    except Exception:
        return None
    return set(_INCLUDE_ASM_RE.findall(text))


def _programmer_of(tu: str | None) -> str:
    if not tu:
        return UNASSIGNED_GROUP
    head = tu.split("/", 1)[0]
    # src/cod/* is crt0 + vendored libkernl, not a game dir. On the retail
    # trees (us, pal) the game TUs themselves live under a flat src/ (the
    # release build collapsed the per-programmer dirs), so plain src/<tu>
    # groups as "src"; only the src/cod/ blob remains vendor.
    if head == "src":
        return VENDOR_GROUP if tu.startswith("src/cod/") else "src"
    return head


def _vendor_runs(syms: list[dict]) -> dict[int, str]:
    """Map symbol index -> vendor node key, one node per contiguous run.

    The vendor archives bracket the game code, so `// (vendor)` symbols
    form exactly two address runs in a normal build. Splitting on runs
    (rather than lumping all 944 into one node) keeps the head and tail
    distinguishable without inventing a per-function archive attribution
    that this repo does not track.
    """
    keys: dict[int, str] = {}
    run = 0
    i = 0
    while i < len(syms):
        if not syms[i]["vendor"]:
            i += 1
            continue
        j = i
        while j + 1 < len(syms) and syms[j + 1]["vendor"]:
            j += 1
        lo = syms[i]["addr"]
        hi = syms[j]["addr"] + syms[j]["size"]
        label = VENDOR_RUN_LABELS[run] if run < len(VENDOR_RUN_LABELS) else None
        name = f"(vendor) 0x{lo:08X}–0x{hi:08X}"
        if label:
            name = f"(vendor) {label} — 0x{lo:08X}–0x{hi:08X}"
        for k in range(i, j + 1):
            keys[k] = name
        run += 1
        i = j + 1
    return keys


def build_tree() -> dict:
    syms = _parse_symbols()
    bounds = _section_bounds(syms)
    _assign_sizes(syms, bounds)
    vendor_keys = _vendor_runs(syms)

    # Cache per-TU unmatched sets so we read each source once.
    tu_unmatched: dict[str, set[str] | None] = {}
    programmers: dict[str, dict] = {}

    for idx, sym in enumerate(syms):
        tu = sym["tu"]
        if sym["vendor"]:
            prog = VENDOR_GROUP
            tu_key = vendor_keys[idx]
            tu_name = tu_key
        elif tu is None:
            prog = UNASSIGNED_GROUP
            tu_key = tu_name = UNASSIGNED_GROUP
        else:
            prog = (VUTEXT_GROUP if sym["section"] == ".vutext"
                    else _programmer_of(tu))
            tu_key = tu
            tu_name = tu.split("/", 1)[-1]

        if tu and tu not in tu_unmatched:
            tu_unmatched[tu] = _unmatched_funcs_for_tu(tu, sym["ext"])

        unmatched = tu_unmatched.get(tu) if tu else None
        if unmatched is None:
            # TU not started, or a vendor / unassigned symbol: vendor bytes
            # are passthrough asm in the link, so they are honestly "not
            # decompiled" even though the ELF already reproduces them.
            matched = False
        else:
            matched = sym["name"] not in unmatched

        p = programmers.setdefault(prog, {"name": prog, "tus": {}})
        t = p["tus"].setdefault(
            tu_key, {"name": tu_name, "path": tu_key, "funcs": []})
        t["funcs"].append({
            "name": sym["name"],
            "addr": f"0x{sym['addr']:08X}",
            "size": sym["size"],
            "section": sym["section"],
            "matched": matched,
        })

    group_notes = {
        VENDOR_GROUP: VENDOR_NOTE,
        VUTEXT_GROUP: VUTEXT_NOTE,
        UNASSIGNED_GROUP: UNASSIGNED_NOTE,
    }

    # Roll up byte/func counts bottom-up and flatten dicts to lists.
    prog_list = []
    tot_m_funcs = tot_funcs = tot_m_bytes = tot_bytes = 0
    for prog in sorted(programmers.values(), key=lambda p: p["name"]):
        tu_list = []
        p_m_funcs = p_funcs = p_m_bytes = p_bytes = 0
        for t in sorted(prog["tus"].values(), key=lambda t: t["path"]):
            funcs = sorted(t["funcs"], key=lambda f: f["addr"])
            m_funcs = sum(1 for f in funcs if f["matched"])
            m_bytes = sum(f["size"] for f in funcs if f["matched"])
            b = sum(f["size"] for f in funcs)
            tu_list.append({
                "name": t["name"], "path": t["path"],
                "matched_funcs": m_funcs, "total_funcs": len(funcs),
                "matched_bytes": m_bytes, "total_bytes": b,
                "funcs": funcs,
            })
            p_m_funcs += m_funcs; p_funcs += len(funcs)
            p_m_bytes += m_bytes; p_bytes += b
        entry = {
            "name": prog["name"],
            "matched_funcs": p_m_funcs, "total_funcs": p_funcs,
            "matched_bytes": p_m_bytes, "total_bytes": p_bytes,
            "tus": tu_list,
        }
        if prog["name"] in group_notes:
            entry["note"] = group_notes[prog["name"]]
        prog_list.append(entry)
        tot_m_funcs += p_m_funcs; tot_funcs += p_funcs
        tot_m_bytes += p_m_bytes; tot_bytes += p_bytes

    # Per-section roll-up straight off the function list, so the tree's own
    # arithmetic is checkable against progress.py rather than assumed equal.
    sym_sections: dict[str, list[int]] = {}
    for s in syms:
        sym_sections.setdefault(s["section"], [0, 0])[1] += s["size"]
    for p in prog_list:
        for t in p["tus"]:
            for f in t["funcs"]:
                if f["matched"]:
                    sym_sections.setdefault(f["section"], [0, 0])[0] += f["size"]

    # Authoritative per-section numbers, same source as the README badge.
    # These differ slightly on the MATCHED side from the symbol-derived sums
    # above: progress.py credits (subseg span - splat's `nonmatching ..., 0xN`
    # sizes), and those .s sizes exclude the inter-function alignment padding
    # that a next-symbol delta absorbs — so progress.py's matched .text runs a
    # few KB ahead of the tree's. Both denominators agree exactly. The
    # symbol-derived figures are kept as `sections_from_symbols` so the gap is
    # inspectable rather than silently reconciled.
    sections = {k: list(v) for k, v in sorted(sym_sections.items())}
    if _progress is not None:
        try:
            authoritative = _progress.compute_progress()
            for sec in sections:
                if sec in authoritative:
                    sections[sec] = list(authoritative[sec])
        except Exception:
            pass

    # Headline "code bytes" total: prefer progress.py's authoritative .text
    # section measurement (matches the README badge, hits 100% at full match).
    # Fall back to the .text slice of the symbol-delta sum when the base ELF
    # isn't available, so this stays runnable without it. Note this is `.text`
    # ONLY — .vutext is reported separately in `sections` and grouped under
    # its own tree node, so it can never inflate the headline.
    text = sections.get(".text", [tot_m_bytes, tot_bytes])
    text_matched, text_total = text[0], text[1]

    return {
        "version": VERSION,
        "totals": {
            "matched_funcs": tot_m_funcs, "total_funcs": tot_funcs,
            "matched_bytes": text_matched, "total_bytes": text_total,
            "sections": sections,
            "sections_from_symbols": {
                k: list(v) for k, v in sorted(sym_sections.items())},
        },
        "programmers": prog_list,
    }


def main() -> int:
    tree = build_tree()
    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    OUT_JSON.write_text(json.dumps(tree, separators=(",", ":")) + "\n")
    t = tree["totals"]
    print(f"progress_tree: {OUT_JSON.relative_to(REPO_ROOT)} "
          f"({t['matched_funcs']}/{t['total_funcs']} funcs, "
          f"{len(tree['programmers'])} programmers)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
