#!/usr/bin/env python3
"""Find matchable leaf-ish functions in splat-emitted PS2 EE asm.

Walks asm/cod/*.s, parses each `glabel func_... endlabel func_...` block,
and filters by size / instruction count / mnemonic shape / regex.

Example:
    tools/find_leaves.py --size 0x10 --no-vu --shape 'lw,sw,jr,sw'
    tools/find_leaves.py --size 0x10..0x40 --jal 0 --insns 4..10
    tools/find_leaves.py --contains 'gp_rel\\(D_' --brief
    tools/find_leaves.py --no-vu --jal 0 --insns 4 --size 0x10 --exclude-parked
"""
from __future__ import annotations

import argparse
import glob
import os
import pickle
import re
import sys
from dataclasses import dataclass
from pathlib import Path

CACHE_PATH = Path(__file__).resolve().parent.parent / ".cache" / "find_leaves.pkl"
CACHE_VERSION = 1
PARKED_PATH = Path(__file__).resolve().parent / "parked.txt"

# /* hex hex HEX */ <whitespace> -- spimdisasm address/vram/rawbytes prefix
ADDR_PREFIX_RE = re.compile(r"^\s*/\*\s+[0-9a-fA-F]+\s+[0-9a-fA-F]+\s+[0-9A-Fa-f]+\s+\*/[ \t]*")
NONMATCHING_RE = re.compile(r"^\s*nonmatching\s+(\S+)\s*,\s*(0x[0-9A-Fa-f]+)")
GLABEL_RE = re.compile(r"^\s*glabel\s+(\S+)")
ENDLABEL_RE = re.compile(r"^\s*endlabel\s+(\S+)")
# VU regs ($vf0..$vf31) and common VU mnemonics
VU_REG_RE = re.compile(r"\$vf\d+\b")
VU_MNEMONICS = {
    "lq", "sq", "lqc2", "sqc2", "qmtc2", "qmfc2", "cfc2", "ctc2",
    "vabs", "vadd", "vaddi", "vaddq", "vaddx", "vaddy", "vaddz", "vaddw",
    "vsub", "vsubi", "vsubq", "vsubx", "vsuby", "vsubz", "vsubw",
    "vmul", "vmuli", "vmulq", "vmulx", "vmuly", "vmulz", "vmulw",
    "vmadd", "vmaddi", "vmaddq", "vmaddx", "vmaddy", "vmaddz", "vmaddw",
    "vmsub", "vmsubi", "vmsubq", "vmsubx", "vmsuby", "vmsubz", "vmsubw",
    "vmax", "vmaxi", "vmaxx", "vmaxy", "vmaxz", "vmaxw",
    "vmini", "vminix", "vminiy", "vminiz", "vminiw",
    "vdiv", "vsqrt", "vrsqrt", "viadd", "visub", "viaddi",
    "vmove", "vmr32", "vmfir", "vmtir", "viand", "vior",
    "vftoi0", "vftoi4", "vftoi12", "vftoi15",
    "vitof0", "vitof4", "vitof12", "vitof15",
    "vopmula", "vopmsub", "vnop", "vwaitq", "vcallms", "vcallmsr",
    "vrnext", "vrget", "vrinit", "vrxor", "vlqi", "vsqi", "vlqd", "vsqd",
    "vclipw", "vmaddax", "vmadday", "vmaddaz", "vmaddaw", "vmaddabc",
    "vmsubax", "vmsubay", "vmsubaz", "vmsubaw", "vmsubabc",
    "vmulax", "vmulay", "vmulaz", "vmulaw", "vmulabc",
    "vaddax", "vadday", "vaddaz", "vaddaw",
    "vsubax", "vsubay", "vsubaz", "vsubaw",
}


@dataclass
class Func:
    name: str
    size: int  # declared size in bytes
    insns: list[str]  # full "mnemonic operands" strings
    mnemonics: list[str]  # first-token only (e.g. "vmul.xyz")
    path: str
    line: int  # 1-based line of glabel

    def jal_count(self) -> int:
        return sum(1 for m in self.mnemonics if m == "jal" or m == "jalr")

    def has_vu(self) -> bool:
        for s, m in zip(self.insns, self.mnemonics):
            if VU_REG_RE.search(s):
                return True
            base = m.split(".", 1)[0]
            if base in VU_MNEMONICS or m in VU_MNEMONICS:
                return True
        return False


def parse_file(path: str) -> list[Func]:
    funcs: list[Func] = []
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        lines = f.readlines()

    pending_size: int | None = None
    cur: Func | None = None

    for idx, raw in enumerate(lines, start=1):
        m = NONMATCHING_RE.match(raw)
        if m:
            pending_size = int(m.group(2), 16)
            continue
        m = GLABEL_RE.match(raw)
        if m:
            cur = Func(
                name=m.group(1),
                size=pending_size if pending_size is not None else 0,
                insns=[],
                mnemonics=[],
                path=path,
                line=idx,
            )
            pending_size = None
            continue
        if cur is not None:
            m = ENDLABEL_RE.match(raw)
            if m:
                funcs.append(cur)
                cur = None
                continue
            stripped = ADDR_PREFIX_RE.sub("", raw)
            if stripped is raw or not stripped.strip():
                continue
            if stripped == raw:  # no prefix matched
                continue
            # strip trailing comment ('# ...' or '/* ... */') and rstrip
            body = stripped.rstrip("\n")
            # remove trailing /* ... */ comment if present
            body = re.sub(r"\s*/\*.*?\*/\s*$", "", body)
            # remove trailing '# ...' comment
            body = re.sub(r"\s+#.*$", "", body)
            body = body.strip()
            if not body:
                continue
            tok = body.split(None, 1)[0]
            cur.insns.append(body)
            cur.mnemonics.append(tok)
    return funcs


def parse_size_spec(s: str) -> tuple[int, int]:
    if ".." in s:
        a, b = s.split("..", 1)
        return int(a, 0), int(b, 0)
    v = int(s, 0)
    return v, v


def parse_count_spec(s: str) -> tuple[int, int]:
    if s.endswith("+"):
        return int(s[:-1]), sys.maxsize
    if ".." in s:
        a, b = s.split("..", 1)
        return int(a), int(b)
    v = int(s)
    return v, v


def shape_match(mnemonics: list[str], shape: list[str]) -> bool:
    """Ordered subsequence: each shape token must appear in order. '*' is wildcard."""
    i = 0
    for tok in shape:
        while i < len(mnemonics):
            if tok == "*" or mnemonics[i] == tok:
                i += 1
                break
            i += 1
        else:
            return False
    return True


def load_parked(path: Path) -> set[str]:
    """Read newline-delimited parked function names. '#' starts a comment.

    Blank lines and lines that are only comments are ignored. Inline
    comments after the function name are stripped. Returns an empty set
    if the file is missing (parked filtering is opt-in).
    """
    parked: set[str] = set()
    if not path.exists():
        return parked
    with path.open("r", encoding="utf-8") as f:
        for raw in f:
            # strip trailing comment, if any
            line = raw.split("#", 1)[0].strip()
            if not line:
                continue
            parked.add(line)
    return parked


def load_funcs(paths: list[str], rebuild: bool = False) -> list[Func]:
    """Parse all paths, with a pickle cache keyed on (path, mtime).

    Each .s file's funcs are stored under its path. On every call:
    - For each path, if the cache has an entry whose mtime matches the
      current file's mtime, reuse the parsed funcs.
    - Otherwise re-parse and update the cache entry.
    Stale entries (paths no longer in the glob) are dropped.
    """
    cache: dict[str, tuple[float, list[Func]]] = {}
    if not rebuild and CACHE_PATH.exists():
        try:
            with CACHE_PATH.open("rb") as f:
                version, cache = pickle.load(f)
            if version != CACHE_VERSION:
                cache = {}
        except Exception:
            cache = {}

    keep = set(paths)
    cache = {k: v for k, v in cache.items() if k in keep}

    all_funcs: list[Func] = []
    dirty = False
    for p in paths:
        try:
            mtime = os.path.getmtime(p)
        except OSError:
            continue
        entry = cache.get(p)
        if entry is None or entry[0] != mtime:
            funcs = parse_file(p)
            cache[p] = (mtime, funcs)
            dirty = True
        else:
            funcs = entry[1]
        all_funcs.extend(funcs)

    if dirty:
        CACHE_PATH.parent.mkdir(parents=True, exist_ok=True)
        tmp = CACHE_PATH.with_suffix(CACHE_PATH.suffix + ".tmp")
        with tmp.open("wb") as f:
            pickle.dump((CACHE_VERSION, cache), f, protocol=pickle.HIGHEST_PROTOCOL)
        tmp.replace(CACHE_PATH)

    return all_funcs


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(
        description="Find matchable leaf functions in splat asm.",
        epilog="Example: tools/find_leaves.py --size 0x10 --no-vu --shape 'lw,sw,jr,sw'",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument("--path", default="asm/cod/*.s", help="glob (default: asm/cod/*.s)")
    ap.add_argument("--size", help="exact (0x10) or range (0x10..0x20), inclusive")
    ap.add_argument("--insns", help="exact (4) or range (4..8)")
    ap.add_argument("--jal", help="exact count, or '1+' for >=N")
    ap.add_argument("--shape", help="comma list of mnemonics in order; '*' wildcard")
    ap.add_argument("--contains", help="regex that must match somewhere in body")
    ap.add_argument("--no-vu", action="store_true", help="exclude any VU reg/mnemonic")
    ap.add_argument("--has-vu", action="store_true", help="require a VU reg/mnemonic")
    ap.add_argument("--brief", action="store_true", help="print just function names")
    ap.add_argument("--list-files", action="store_true", help="include path:line")
    ap.add_argument("--rebuild-cache", action="store_true",
                    help="ignore cache and re-parse all .s files")
    ap.add_argument("--exclude-parked", action="store_true",
                    help="skip functions listed in tools/parked.txt "
                         "(known unmatchable; see decomp/NOTES.md). "
                         "Example: --no-vu --jal 0 --insns 4 --size 0x10 --exclude-parked")
    ap.add_argument("--parked-file", default=str(PARKED_PATH),
                    help=f"path to parked-function list (default: {PARKED_PATH})")
    args = ap.parse_args(argv)

    size_lo, size_hi = (0, sys.maxsize)
    if args.size:
        size_lo, size_hi = parse_size_spec(args.size)
    insn_lo, insn_hi = (0, sys.maxsize)
    if args.insns:
        insn_lo, insn_hi = parse_count_spec(args.insns)
    jal_lo, jal_hi = (0, sys.maxsize)
    if args.jal:
        jal_lo, jal_hi = parse_count_spec(args.jal)
    shape = [t.strip() for t in args.shape.split(",")] if args.shape else None
    contains_re = re.compile(args.contains) if args.contains else None

    paths = sorted(glob.glob(args.path))
    if not paths:
        print(f"no files matched: {args.path}", file=sys.stderr)
        return 1

    funcs = load_funcs(paths, rebuild=args.rebuild_cache)

    parked: set[str] = set()
    if args.exclude_parked:
        parked = load_parked(Path(args.parked_file))

    matched = 0
    for fn in funcs:
        if parked and fn.name in parked:
            continue
        if not (size_lo <= fn.size <= size_hi):
            continue
        if not (insn_lo <= len(fn.insns) <= insn_hi):
            continue
        if args.jal and not (jal_lo <= fn.jal_count() <= jal_hi):
            continue
        if args.no_vu and fn.has_vu():
            continue
        if args.has_vu and not fn.has_vu():
            continue
        if shape and not shape_match(fn.mnemonics, shape):
            continue
        if contains_re and not any(contains_re.search(s) for s in fn.insns):
            continue

        matched += 1
        if args.brief:
            print(fn.name)
            continue
        parts = [fn.name, f"0x{fn.size:X}"]
        if args.list_files:
            parts.append(f"{fn.path}:{fn.line}")
        for ins in fn.insns:
            parts.append(ins)
        print(" | ".join(parts))

    print(f"# {matched} match(es)", file=sys.stderr)
    return 0 if matched else 2


if __name__ == "__main__":
    sys.exit(main())
