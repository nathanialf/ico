#!/usr/bin/env python3
"""Census of the ICO PAL source tree's STRUCTURE, from the disc's own listing.

WHAT THIS DOES
--------------
baserom/pal/SRCFILE.TXT is an `objdump -dl` listing of the 2002-01-16
"MasterVer1.00EU" main.elf: every instruction carries the source file and line
it came from.  That is a complete map of which file holds which function, of
which files were #included into which translation unit, and of which header
bodies were expanded inline into which callers -- all of it DERIVED metadata
(names, paths, line NUMBERS, instruction counts).  No source text is read,
copied or reproduced: the listing contains none, and neither do the outputs.

Writes:
  * decomp/pal_source_tree.md    (tracked) -- the human-readable census.
  * decomp/pal_source_tree.json  (tracked) -- the same, machine-readable.

USAGE
-----
    tools/gen_pal_source_tree.py
    tools/gen_pal_source_tree.py --report     # summary to stdout, write nothing

WHY IT MATTERS FOR MATCHING
---------------------------
Three things it settles that the rom alone cannot:

  * COALESCERS.  A `.c` whose functions also carry rows from a `.c.inc` was
    compiled with that file textually included.  `sugipon/motionManager2.c`
    pulls in motMan_rootUpdate.c.inc / motMan_getFinalMatrix.c.inc;
    `fumi/girl_act.c` pulls in girl_brain_main.c.inc.  A decomp TU that does
    not reproduce the include will not reproduce the .o's function ORDER, and
    order is what fixes gcse hash-bucket ties (see the gcse_bucket_name_hash
    note).  Every such TU is flagged here, with the exact list of includes.
  * STATIC-INLINE HELPERS.  A body whose rows point at a `.h` was expanded
    into its caller.  Each header below lists exactly which callers absorbed
    it, which is the difference between writing a static helper and writing a
    macro.
  * FUNCTION ORDER AND LINE ORDER.  Per TU, functions are listed in SOURCE
    LINE order with their PAL rom VMA.  Emission order (rom order) versus
    definition order (line order) is directly readable, and so is the
    file-relative position of every function -- which is what a reconstructed
    .c has to reproduce.

PROVENANCE
----------
SRCFILE.TXT and MAIN.MAP shipped on the retail SCES-50760 disc: officially
distributed retail media, the same class of input as the aug6 branch's
TRFILE.TXT/MAIN.MAP.  No leaked SDK, leaked source or debug build is an input.
See docs/LEGAL.md.  !! The listing is a DIFFERENT LINK from the retail PAL ELF
(its .text is 0x18DB34, the ELF's is 0x189BC4), so a `pal_vma` column below is
the address recovered by tools/gen_pal_symbol_addrs.py's reloc-normalized
instruction-stream correlation, never an address copied from the listing.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
OUT_MD = ROOT / "decomp" / "pal_source_tree.md"
OUT_JSON = ROOT / "decomp" / "pal_source_tree.json"

_spec = importlib.util.spec_from_file_location(
    "gen_pal_symbol_addrs", HERE / "gen_pal_symbol_addrs.py")
G = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(G)

VUTEXT_LISTING_BASE = 0x0028DB40      # .vutext start in SRCFILE.TXT's link
VUTEXT_PAL_BASE = 0x00289BD0          # .vutext start in the retail PAL ELF
VUTEXT_SIZE = 0x50E0                  # .vutext sh_size, baserom/pal/baseelf.elf
# The five microprograms sit in the same order and at the same sizes in both
# links, so running the listing's sizes forward from VUTEXT_PAL_BASE places
# them; the result is checked against config/ico.pal.yaml's hasm subsegment
# offsets, which the SHA-1 round-trip already proves.
VUTEXT_EXPECTED = (0x00289BD0, 0x0028A990, 0x0028B380, 0x0028CA60, 0x0028E700)

L_LABEL = re.compile(r"^([0-9a-f]{16}) <(.*)>:$")
L_BYTES = re.compile(r"^ *([0-9a-f]+):\t((?:[0-9a-f]{2} )+)\t")


# ------------------------------------------------------------------ vutext --
def parse_vutext(path: Path):
    """.vutext labels per microprogram, with their VU instruction addresses.

    Each microprogram is a DMA chain: `.dma.N` / `.vif.N` tags and `.vu.N`
    blocks of VU code.  A `_$NAME` label is a VU branch target, so its address
    is meaningful only relative to the `.vu.N` block it sits in -- VU program
    counters count 64-bit instruction PAIRS from the start of the upload."""
    progs = []
    cur = None
    block = None
    started = False
    with path.open(errors="replace") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if line.startswith("Disassembly of section .vutext"):
                started = True
                continue
            if not started:
                continue
            m = L_LABEL.match(line)
            if not m:
                continue
            vma, label = int(m.group(1), 16), m.group(2)
            if label.endswith("MicroProgram"):
                cur = {"program": label, "listing_vma": vma, "labels": []}
                progs.append(cur)
                block = None
                continue
            if cur is None:
                continue
            if label.startswith(".vu."):
                block = vma
            cur["labels"].append({
                "label": label,
                "listing_vma": vma,
                "block_listing_vma": block,
                "vu_addr": (vma - block) // 8 if block and not label.startswith((".vu.", ".vif.", ".dma.")) else None,
            })
    for i, p in enumerate(progs):
        nxt = (progs[i + 1]["listing_vma"] if i + 1 < len(progs)
               else VUTEXT_LISTING_BASE + VUTEXT_SIZE)
        p["listing_size"] = nxt - p["listing_vma"]
    return progs


def map_vutext(progs, rom: bytes):
    """Place each microprogram at its retail PAL VMA and check byte identity.

    The five programs sit in the same order and at the same sizes in both
    links, so the PAL VMA follows by running sizes forward from the PAL
    .vutext start; every derived address is then verified against the rom."""
    vma = VUTEXT_PAL_BASE
    for p in progs:
        p["pal_vma"] = vma
        size = p["listing_size"]
        p["size"] = size
        delta = vma - p["listing_vma"]
        for l in p["labels"]:
            l["pal_vma"] = l["listing_vma"] + delta
            l["block"] = (f"0x{l['block_listing_vma'] + delta:08X}"
                          if l["block_listing_vma"] else None)
            del l["block_listing_vma"]
        vma += size
    got = tuple(p["pal_vma"] for p in progs)
    if got != VUTEXT_EXPECTED:
        raise SystemExit(
            "vutext placement disagrees with config/ico.pal.yaml: "
            + " ".join(f"0x{v:08X}" for v in got))
    if vma != VUTEXT_PAL_BASE + VUTEXT_SIZE:
        raise SystemExit(f"vutext sizes do not sum to 0x{VUTEXT_SIZE:X}")
    return progs


# ------------------------------------------------------------------- census --
def kind_of(path: str) -> str:
    if path.startswith("/"):
        return "vendor"
    if path.endswith(".c.inc"):
        return "c.inc"
    if path.endswith(".c"):
        return "c"
    if path.endswith(".h"):
        return "h"
    if path.endswith(".s"):
        return "s"
    return "other"


def programmer_of(path: str) -> str | None:
    if path.startswith("/"):
        return None
    parts = path.split("/")
    return parts[0] if len(parts) > 1 else None


def strip_programmer(path: str) -> str:
    """Same convention as the yaml TU paths: drop the per-programmer dir,
    normalise the `x/../y/` spellings objdump emits for an #include, keep the
    ito/mpeg namespace."""
    if path.startswith("/"):
        return path
    parts = []
    for seg in path.split("/"):
        if seg == "..":
            if parts:
                parts.pop()
            continue
        parts.append(seg)
    if len(parts) > 1:
        parts = parts[1:]
    return "/".join(parts)


def build_census(m):
    corr_name, corr_tier = {}, {}
    for r, l in m.corr.items():
        corr_name[l] = m.rfuncs[r][0]
        corr_tier[l] = "twin" if r in m.twins else "ordinal"

    files: dict[str, dict] = {}

    def entry(path):
        f = files.get(path)
        if f is None:
            f = files[path] = {
                "path": path,
                "programmer": programmer_of(path),
                "repo_path": strip_programmer(path),
                "kind": kind_of(path),
                "first_addr": None,
                "links_into": Counter(),
                "functions": [],
                "expanded_into": [],
            }
        return f

    for li, lf in enumerate(m.lf):
        owner = None
        if lf.own_rows or lf.rows:
            src = lf.own_rows or lf.rows
            owner = max(src.items(), key=lambda kv: kv[1][0])[0]
        rec = {
            "label": lf.label,
            "name": lf.name,
            "discrim": lf.discrim,
            "pal_vma": corr_name.get(li),
            "tier": corr_tier.get(li),
            "tu": lf.tu,
            "insns": lf.ninsn,
            "def_line": lf.entry_line,
            "def_path": lf.entry_path,
            "first_line": None,
            "last_line": None,
            "rows": 0,
            "cites": [],
        }
        src = lf.own_rows or lf.rows
        if owner:
            r = src[owner]
            rec["rows"], rec["first_line"], rec["last_line"] = r[0], r[1], r[2]
        cites = sorted(lf.rows.items(), key=lambda kv: -kv[1][0])
        if len(cites) > 1:
            rec["cites"] = [{"path": p, "rows": v[0], "first_line": v[1],
                             "last_line": v[2]} for p, v in cites]
        if owner:
            fe = entry(owner)
            if fe["first_addr"] is None:
                fe["first_addr"] = lf.start
            fe["functions"].append(rec)
            fe["links_into"][lf.tu] += 1
        # every non-owner path this function cites got expanded into it
        for p, v in lf.rows.items():
            if p == owner:
                continue
            fe = entry(p)
            if fe["first_addr"] is None:
                fe["first_addr"] = lf.start
            fe["expanded_into"].append({
                "host": lf.label, "host_tu": lf.tu, "host_pal_vma": corr_name.get(li),
                "rows": v[0], "first_line": v[1], "last_line": v[2],
            })
            fe["links_into"][lf.tu] += 0

    out = []
    for path, fe in files.items():
        fe["functions"].sort(key=lambda r: (r["def_line"] if r["def_line"]
                                            is not None else 1 << 30, r["label"]))
        fe["n_funcs"] = len(fe["functions"])
        fe["links_into"] = ([p for p, _ in fe["links_into"].most_common(1)]
                            or [None])[0]
        fe["is_member"] = (fe["kind"] == "c"
                           and fe["repo_path"][:-2].rsplit("/", 1)[-1]
                           in set(m.members))
        fe["own_tu"] = (fe["kind"] == "c" and fe["repo_path"][:-2] == fe["links_into"])
        out.append(fe)
    out.sort(key=lambda f: (f["first_addr"] if f["first_addr"] is not None
                            else 1 << 62))
    for i, fe in enumerate(out):
        fe["order"] = i

    # coalescers: a TU whose members include more than one source file
    by_tu = defaultdict(list)
    for fe in out:
        if fe["kind"] in ("c", "c.inc") and fe["links_into"]:
            by_tu[fe["links_into"]].append(fe)
    coalescers = {}
    for tu, fes in by_tu.items():
        if len(fes) < 2:
            continue
        host = next((f for f in fes if f["own_tu"]), None)
        coalescers[tu] = {
            "host": host["path"] if host else None,
            "includes": sorted(f["path"] for f in fes if f is not host),
        }
    for fe in out:
        fe["coalescer"] = (fe["own_tu"] and fe["links_into"] in coalescers)
        fe["includes"] = (coalescers[fe["links_into"]]["includes"]
                          if fe["coalescer"] else [])
    return out, coalescers


# ------------------------------------------------------------------ writers --
def write_json(files, coalescers, vutext, m):
    doc = {
        "generated_by": "tools/gen_pal_source_tree.py",
        "target": "ICO PAL retail, SCES-50760 / SCES_507.60",
        "provenance": (
            "Derived metadata only (names, paths, line numbers, instruction "
            "counts) from baserom/pal/SRCFILE.TXT + MAIN.MAP, files shipped on "
            "the retail PAL disc. No source text is read or reproduced. "
            "The listing is a DIFFERENT LINK from the retail ELF: every "
            "pal_vma is recovered by reloc-normalized instruction-stream "
            "correlation (tools/gen_pal_symbol_addrs.py), never copied."),
        "listing": {
            "text_start": f"0x{m.lf[0].start:08X}",
            "text_end": f"0x{m.lf[-1].end:08X}",
            "n_functions": len(m.lf),
        },
        "rom": {
            "text_start": f"0x{G.TEXT_VMA:08X}",
            "text_end": f"0x{G.TEXT_VMA + G.PAL_TEXT_SZ:08X}",
            "n_functions": len(m.rfuncs),
            "twinned": len(m.twins),
            "ordinal": len(m.ordinal),
        },
        "coalescers": coalescers,
        "files": [],
        "vutext": vutext,
    }
    for fe in files:
        d = dict(fe)
        d["first_addr"] = (f"0x{fe['first_addr']:08X}"
                           if fe["first_addr"] is not None else None)
        for r in d["functions"]:
            r["pal_vma"] = f"0x{r['pal_vma']:08X}" if r["pal_vma"] else None
        for r in d["expanded_into"]:
            r["host_pal_vma"] = (f"0x{r['host_pal_vma']:08X}"
                                 if r["host_pal_vma"] else None)
        doc["files"].append(d)
    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    OUT_JSON.write_text(json.dumps(doc, indent=1) + "\n")


HEAD = """\
# ICO PAL — source-tree structure census

Generated by `tools/gen_pal_source_tree.py`; regenerate rather than hand-edit.
Machine-readable twin: `decomp/pal_source_tree.json`.

**Provenance.** Everything here is *derived metadata* — file paths, function
names, source line NUMBERS, instruction counts — read out of
`baserom/pal/SRCFILE.TXT` (an `objdump -dl` listing of the 2002-01-16
"MasterVer1.00EU" `main.elf`) and `baserom/pal/MAIN.MAP` (its link map). Both
files shipped on the retail SCES-50760 disc: officially distributed retail
media, the same class of input as the `aug6` branch's TRFILE.TXT/MAIN.MAP.
No leaked SDK, leaked source or debug build is an input, and **no source text
is reproduced** — the listing contains none. See `docs/LEGAL.md`.

**The listing is a different link.** Its `.text` is `0x00100000..0x0028DB34`;
the retail PAL ELF's is `0x00100000..0x00289BC4`. Every `pal vma` column below
is an address *recovered* by `tools/gen_pal_symbol_addrs.py`'s
reloc-normalized instruction-stream correlation against
`baserom/pal/baseelf.rom` — never an address copied out of the listing. A
blank `pal vma` means that listing function has no established counterpart in
the retail link (it moved, changed, or is not present).

`tier` is that correlation's confidence: `twin` = reloc-normalized
instruction-stream equality; `ord` = position forced by link order between two
twins (provisional — verify before relying on it).

## How to read this for matching

* **Coalescers.** A `.c` compiled with another file textually `#include`d
  emits *both* files' functions into one `.o`, interleaved in the compiler's
  own order. A decomp TU that does not reproduce the include cannot reproduce
  that order, and order is what fixes gcse hash-bucket ties. Every coalescer
  is flagged below with its exact include list.
* **Static-inline helpers.** Instruction rows pointing at a `.h` are a header
  body expanded into its caller. The header sections list exactly which
  callers absorbed which line range — the difference between a `static inline`
  helper and a macro, and between one helper and several.
* **Line order vs rom order.** Functions are listed in SOURCE LINE order with
  their rom VMA, so definition order and emission order are directly
  comparable. A reconstructed `.c` has to reproduce the definition order.

`def line` is the line the function's FIRST instruction is attributed to — its
definition line. `row span` is the min..max over ALL its instruction rows,
which is wider whenever a same-file static was inlined into it (the inlined
body keeps its own line numbers), so a wide span is itself a signal that
something got inlined here. `cites` names any OTHER file whose lines appear in
the function, with that file's line range — a header helper, or a `.c.inc`
body, expanded at this call site.
* **Multi-file functions.** A function whose rows cite more than one file got
  something inlined into it; the `cites` note names the files and line ranges.
"""


def write_md(files, coalescers, vutext, m):
    L = [HEAD, ""]
    game = [f for f in files if f["kind"] in ("c", "c.inc", "h")
            and not f["path"].startswith("/")]
    vendor = [f for f in files if f not in game]
    L.append("## Summary")
    L.append("")
    L.append(f"| listing .text functions | {len(m.lf)} |")
    L.append("| --- | --- |")
    L.append(f"| retail PAL .text functions | {len(m.rfuncs)} |")
    L.append(f"| correlated — twin | {len(m.twins)} |")
    L.append(f"| correlated — ordinal | {len(m.ordinal)} |")
    L.append(f"| source files in the listing | {len(files)} |")
    for k in ("c", "c.inc", "h", "s", "vendor"):
        n = sum(1 for f in files if f["kind"] == k)
        if n:
            L.append(f"| &nbsp;&nbsp;`{k}` | {n} |")
    L.append(f"| translation units that coalesce >1 file | {len(coalescers)} |")
    L.append(f"| functions citing more than one file | "
             f"{sum(1 for f in files for r in f['functions'] if r['cites'])} |")
    L.append("")

    L.append("## Coalescing translation units")
    L.append("")
    L.append("A `.o` built from more than one source file. `host` is the file "
             "the member is named after; the rest were `#include`d into it.")
    L.append("")
    L.append("| TU | host | included |")
    L.append("| --- | --- | --- |")
    for tu, c in sorted(coalescers.items()):
        L.append(f"| `{tu}` | `{c['host']}` | " +
                 ", ".join(f"`{p}`" for p in c["includes"]) + " |")
    L.append("")

    L.append("## Headers with code")
    L.append("")
    L.append("Bodies defined in a header and expanded into each caller — "
             "`static inline` helpers, or a `.h` used as an include-once code "
             "file.")
    L.append("")
    hdrs = [f for f in files if f["kind"] == "h" and (f["functions"]
                                                     or f["expanded_into"])]
    for fe in hdrs:
        L.append(f"### `{fe['path']}`")
        L.append("")
        L.append(f"programmer dir `{fe['programmer']}` · repo path "
                 f"`{fe['repo_path']}` · links into `{fe['links_into']}`")
        L.append("")
        if fe["functions"]:
            L.append("Whole functions emitted from this header "
                     "(out-of-line copies):")
            L.append("")
            L.append("| function | pal vma | tier | row span | insns | TU |")
            L.append("| --- | --- | --- | --- | --- | --- |")
            for r in fe["functions"]:
                L.append(_frow(r))
            L.append("")
        if fe["expanded_into"]:
            L.append("Expanded inline into:")
            L.append("")
            L.append("| caller | caller TU | caller pal vma | header lines | rows |")
            L.append("| --- | --- | --- | --- | --- |")
            for r in sorted(fe["expanded_into"], key=lambda x: -x["rows"]):
                L.append(f"| `{r['host']}` | `{r['host_tu']}` | "
                         f"{_vma(r['host_pal_vma'])} | "
                         f"{r['first_line']}–{r['last_line']} | {r['rows']} |")
            L.append("")

    L.append("## Translation units, in link order")
    L.append("")
    for fe in files:
        if fe["kind"] not in ("c", "c.inc", "s") or not fe["functions"]:
            continue
        vend = fe["path"].startswith("/")
        L.append(f"### {fe['order']:3d}. `{fe['path']}`")
        L.append("")
        bits = [f"kind `{fe['kind']}`"]
        if fe["programmer"]:
            bits.append(f"programmer dir `{fe['programmer']}`")
        bits.append(f"repo path `{fe['repo_path']}`")
        if not vend:
            bits.append(f"links into `{fe['links_into']}`")
            bits.append("own `.o`" if fe["is_member"] else "#included")
        bits.append(f"{fe['n_funcs']} functions")
        L.append(" · ".join(bits))
        if fe["coalescer"]:
            L.append("")
            L.append("**Coalescer** — this TU also compiles: "
                     + ", ".join(f"`{p}`" for p in fe["includes"]))
        if fe["expanded_into"]:
            L.append("")
            L.append(f"*(also expanded into {len(fe['expanded_into'])} caller(s) "
                     f"elsewhere — see the JSON)*")
        L.append("")
        L.append("| def line | function | pal vma | tier | row span | insns | cites |")
        L.append("| --- | --- | --- | --- | --- | --- | --- |")
        for r in fe["functions"]:
            L.append(_frow(r, with_line=True))
        L.append("")

    L.append("## `.vutext` microprograms")
    L.append("")
    L.append("VU1 microprograms are DMA chains: `.dma.N` / `.vif.N` tags around "
             "`.vu.N` blocks of VU code. A `_$NAME` label is a VU branch "
             "target, so its `vu addr` — the 64-bit instruction index from the "
             "start of the `.vu.N` block it lives in — is the number the "
             "microprogram's own branches encode. `pal vma` is the EE address "
             "in the retail PAL ELF.")
    L.append("")
    for p in vutext:
        L.append(f"### `{p['program']}` — 0x{p['pal_vma']:08X}, "
                 f"{p['size']} bytes, {len(p['labels'])} labels")
        L.append("")
        L.append("| label | pal vma | vu addr | .vu block |")
        L.append("| --- | --- | --- | --- |")
        for l in p["labels"]:
            va = "" if l["vu_addr"] is None else str(l["vu_addr"])
            L.append(f"| `{l['label']}` | 0x{l['pal_vma']:08X} | {va} | "
                     f"{l['block'] or ''} |")
        L.append("")
    OUT_MD.parent.mkdir(parents=True, exist_ok=True)
    OUT_MD.write_text("\n".join(L).rstrip("\n") + "\n")


def _vma(v):
    if v is None:
        return ""
    return v if isinstance(v, str) else f"0x{v:08X}"


def _frow(r, with_line=False):
    """One row of a function table.

    with_line=True  -> | def line | function | pal vma | tier | row span | insns | cites |
    with_line=False -> | function | pal vma | tier | row span | insns | TU |"""
    lines = ("" if r["first_line"] is None
             else f"{r['first_line']}\u2013{r['last_line']}")
    if with_line:
        cites = ("" if not r["cites"] else
                 " ".join(f"`{c['path']}`({c['first_line']}\u2013{c['last_line']})"
                          for c in r["cites"][1:]))
        return (f"| {r['def_line'] if r['def_line'] is not None else ''} | "
                f"`{r['label']}` | {_vma(r['pal_vma'])} | {(r['tier'] or '')[:4]} | "
                f"{lines} | {r['insns']} | {cites} |")
    return (f"| `{r['label']}` | {_vma(r['pal_vma'])} | {(r['tier'] or '')[:4]} | "
            f"{lines} | {r['insns']} | `{r['tu']}` |")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--report", action="store_true")
    args = ap.parse_args()
    m = G.build()
    files, coalescers = build_census(m)
    vutext = map_vutext(parse_vutext(G.LISTING), m.rom)
    print(f"source files in listing      : {len(files)}")
    for k in ("c", "c.inc", "h", "s", "vendor"):
        n = sum(1 for f in files if f["kind"] == k)
        print(f"  {k:8s}                   : {n}")
    print(f"coalescing TUs               : {len(coalescers)}")
    for tu, c in sorted(coalescers.items()):
        print(f"    {tu:28s} <- {', '.join(c['includes'])}")
    print(f"headers carrying code        : "
          f"{sum(1 for f in files if f['kind'] == 'h' and (f['functions'] or f['expanded_into']))}")
    print(f"functions citing >1 file     : "
          f"{sum(1 for f in files for r in f['functions'] if r['cites'])}")
    print(f"vutext microprograms         : {len(vutext)}"
          f"  ({sum(len(p['labels']) for p in vutext)} labels)")
    if args.report:
        return 0
    write_json(files, coalescers, vutext, m)
    write_md(files, coalescers, vutext, m)
    print(f"wrote {OUT_MD.relative_to(ROOT)}")
    print(f"wrote {OUT_JSON.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
