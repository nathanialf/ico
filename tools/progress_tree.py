#!/usr/bin/env python3
"""progress_tree.py — emit docs/progress.json for the GitHub Pages site.

Builds a programmer -> TU -> function tree of decompilation progress,
mirroring (and extending to function granularity) the section numbers
`tools/progress.py` already computes. The output is IP-clean by
construction: it contains only address-derived function names, byte
sizes, and matched/unmatched booleans — no ROM bytes, no disassembly.

Sources (all git-tracked, no base ELF required):
  - config/symbol_addrs.<ver>.txt : every `type:func` symbol, its
    address, and the owning TU (from the trailing `// <path>.c` note).
    Function sizes are next-symbol-address deltas.
  - <TU>.c INCLUDE_ASM(...) directives : the still-asm (unmatched)
    functions inside a started TU. A function is "matched" iff its TU
    `.c` exists and the function is NOT INCLUDE_ASM'd there.

Run via `tools/build.sh progress` (which also runs progress.py) so the
JSON stays in lockstep with the README badges and PROGRESS.md table.
"""

from __future__ import annotations

import json
import os
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

VERSION = os.environ.get("VERSION")
if not VERSION:
    if (REPO_ROOT / "config" / "ico.aug6.yaml").exists():
        VERSION = "aug6"
    else:
        VERSION = "us"

SYMBOLS = REPO_ROOT / "config" / f"symbol_addrs.{VERSION}.txt"
OUT_JSON = REPO_ROOT / "docs" / "progress.json"

# A gap larger than this between consecutive function symbols is treated
# as interleaved non-code (data/padding) rather than one giant function,
# so a single trailing symbol before a data blob can't inflate the tree.
MAX_FUNC_SIZE = 0x4000

# `Name = 0xADDR; // type:func  // path/to/tu.c`
_SYM_RE = re.compile(
    r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*type:func\b(.*)$"
)
_TU_NOTE_RE = re.compile(r"//\s*([\w./-]+)\.c\b")
_INCLUDE_ASM_RE = re.compile(
    r'\bINCLUDE_ASM(?:_NOAT)?\s*\(\s*"[^"]+"\s*,\s*(\w+)\s*\)'
)


def _parse_symbols() -> list[dict]:
    """[{name, addr, tu}] for every type:func symbol, address-sorted."""
    if not SYMBOLS.exists():
        sys.exit(f"progress_tree: {SYMBOLS} not found")
    out: list[dict] = []
    for line in SYMBOLS.read_text().splitlines():
        m = _SYM_RE.match(line)
        if not m:
            continue
        name, addr_hex, rest = m.group(1), m.group(2), m.group(3)
        tu_m = _TU_NOTE_RE.search(rest)
        tu = tu_m.group(1) if tu_m else None
        out.append({"name": name, "addr": int(addr_hex, 16), "tu": tu})
    out.sort(key=lambda s: s["addr"])
    # Size = distance to the next function start, clamped.
    for i, sym in enumerate(out):
        if i + 1 < len(out):
            sym["size"] = min(out[i + 1]["addr"] - sym["addr"], MAX_FUNC_SIZE)
        else:
            sym["size"] = 0
        sym["size"] = max(0, sym["size"])
    return out


def _unmatched_funcs_for_tu(tu: str) -> set[str] | None:
    """Set of still-INCLUDE_ASM'd function names in <tu>.c, or None if
    the TU hasn't been started (no .c yet -> every func unmatched)."""
    csrc = REPO_ROOT / f"{tu}.c"
    if not csrc.exists():
        return None
    try:
        text = csrc.read_text()
    except Exception:
        return None
    return set(_INCLUDE_ASM_RE.findall(text))


def _programmer_of(tu: str | None) -> str:
    if not tu:
        return "vendor"
    head = tu.split("/", 1)[0]
    # src/cod/* is crt0 + vendored libkernl, not a programmer dir.
    return "vendor" if head == "src" else head


def build_tree() -> dict:
    syms = _parse_symbols()

    # Cache per-TU unmatched sets so we read each .c once.
    tu_unmatched: dict[str, set[str] | None] = {}
    programmers: dict[str, dict] = {}

    for sym in syms:
        tu = sym["tu"]
        prog = _programmer_of(tu)
        tu_key = tu if tu else "(unassigned)"
        if tu and tu not in tu_unmatched:
            tu_unmatched[tu] = _unmatched_funcs_for_tu(tu)

        unmatched = tu_unmatched.get(tu) if tu else None
        if unmatched is None:
            matched = False          # TU not started, or vendor
        else:
            matched = sym["name"] not in unmatched

        p = programmers.setdefault(prog, {"name": prog, "tus": {}})
        t = p["tus"].setdefault(
            tu_key,
            {"name": tu_key.split("/", 1)[-1] if tu else tu_key,
             "path": tu_key, "funcs": []},
        )
        t["funcs"].append({
            "name": sym["name"],
            "addr": f"0x{sym['addr']:08X}",
            "size": sym["size"],
            "matched": matched,
        })

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
        prog_list.append({
            "name": prog["name"],
            "matched_funcs": p_m_funcs, "total_funcs": p_funcs,
            "matched_bytes": p_m_bytes, "total_bytes": p_bytes,
            "tus": tu_list,
        })
        tot_m_funcs += p_m_funcs; tot_funcs += p_funcs
        tot_m_bytes += p_m_bytes; tot_bytes += p_bytes

    return {
        "version": VERSION,
        "totals": {
            "matched_funcs": tot_m_funcs, "total_funcs": tot_funcs,
            "matched_bytes": tot_m_bytes, "total_bytes": tot_bytes,
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
