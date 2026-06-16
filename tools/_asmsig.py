#!/usr/bin/env python3
"""tools/_asmsig.py — shared signature + symbol-resolution library.

NOT a CLI of its own. Imported by:
  * tools/classify_asm.py   (--bundle context dump)
  * tools/match_loop.py     (clone subcommand: clone-banking + propagation)
  * tools/templatize.py     (immediate-generalised family propagation)

It centralises three things those tools would otherwise each reinvent:

  1. RELOC-NORMALISED FUNCTION SIGNATURES, read straight from the per-function
     splat `.s` (`asm/aug6/{matchings,nonmatchings}/<tu>/<func>.s`). Every line
     carries the raw word AND the resolved operand, so we normalise away exactly
     the fields the linker fixes up — `%hi(S)`/`%lo(S)`/`%gp_rel(S)` symbols,
     `.L` branch labels (PC-relative; identical bytes, different absolute name),
     and absolute `j`/`jal` targets — and KEEP every real register/immediate.
     Two funcs with an equal signature are byte-identical *modulo relocations*:
     clone candidates. This mirrors tools/match_diff.py's normalisation, but on
     a target `.s` (no compile) so it works for matched AND unmatched funcs.

  2. ORDERED SYMBOL SLOTS for retargeting — the list of symbols that were masked
     (in `.s` order). For a clone pair the masked signatures are equal, so the
     slot lists are positionally aligned: slot i of A maps to slot i of B. That
     is the rename map that turns A's matched C into B's candidate.

  3. VMA / NAME / TU / STRUCT RESOLUTION over the existing data files
     (config/symbol_addrs.aug6.txt, decomp/{tu_map,callgraph,struct_shapes}.json)
     plus a best-effort callee C-signature, for the context bundle.

The oracle (tools/sweep_try.sh) is always the final authority — signatures and
retargeting are a *filter*, never a proof. A wrong guess just MISSes.
"""
from __future__ import annotations

import json
import re
import subprocess
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm" / "aug6"

# ---------------------------------------------------------------------------
# .s parsing
# ---------------------------------------------------------------------------

# `    /* 9EFB8 0019EFB8 80FFBD27 */  addiu      $29, $29, -0x80`
_LINE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*)$"
)
_WS = re.compile(r"\s+")

# operand-masking: collapse exactly the fields a relocation fixes up.
_HILO = re.compile(r"%(hi|lo|gp_rel)\(([^)]*)\)")
_LABEL = re.compile(r"\.L[0-9A-Fa-f]+")
_JUMP_MNEM = {"j", "jal", "b", "bal"}


class Insn:
    __slots__ = ("vma", "word", "mnem", "ops", "norm", "syms")

    def __init__(self, vma: int, word: str, mnem: str, ops: str):
        self.vma = vma
        self.word = word
        self.mnem = mnem
        self.ops = ops
        self.syms: list[tuple[str, str]] = []   # (kind, symbol) in operand order
        self.norm = self._normalise()

    def _normalise(self) -> str:
        ops = self.ops
        # %hi/%lo/%gp_rel(SYM) -> %hi etc.; record the symbol slot
        def _hl(m):
            self.syms.append((m.group(1), m.group(2)))
            return f"%{m.group(1)}"
        ops = _HILO.sub(_hl, ops)
        # branch labels: PC-relative, same bytes, different absolute name
        ops = _LABEL.sub(".L", ops)
        # absolute jump/call target symbol -> T (and record it)
        if self.mnem in _JUMP_MNEM and ops and not ops.startswith("$"):
            self.syms.append(("call", ops.strip()))
            ops = "T"
        return f"{self.mnem} {ops}".strip()


def parse_s(s_path: Path) -> list[Insn]:
    out: list[Insn] = []
    for line in s_path.read_text(errors="replace").splitlines():
        m = _LINE.match(line)
        if not m:
            continue
        vma = int(m.group(1), 16)
        word = m.group(2)
        body = _WS.sub(" ", m.group(3).strip())
        if not body:
            continue
        parts = body.split(" ", 1)
        mnem = parts[0]
        ops = parts[1] if len(parts) > 1 else ""
        out.append(Insn(vma, word, mnem, ops))
    return out


def find_s(func: str, tu: str | None = None) -> Path | None:
    """Locate the per-function `.s`, preferring matchings/ (matched) then
    nonmatchings/ (unmatched). `tu` (yaml stem, e.g. fumi/src/main) narrows it."""
    for sub in ("matchings", "nonmatchings"):
        base = ASM / sub
        if tu:
            cand = base / f"{tu}" / f"{func}.s"
            if cand.exists():
                return cand
        hits = list(base.rglob(f"{func}.s"))
        if hits:
            return hits[0]
    return None


def is_matched(s_path: Path) -> bool:
    return "matchings" in s_path.parts and "nonmatchings" not in s_path.parts


# ---------------------------------------------------------------------------
# signatures
# ---------------------------------------------------------------------------

def signature(s_path: Path) -> tuple[str, ...]:
    """Reloc-normalised instruction stream — the clone-equality key."""
    return tuple(i.norm for i in parse_s(s_path))


def imm_masked_signature(s_path: Path) -> tuple[str, ...]:
    """Signature with NUMERIC immediates also wildcarded — the templatize key
    (siblings that differ only in offsets/shifts/constants)."""
    return tuple(re.sub(r"-?0x[0-9A-Fa-f]+", "#", i.norm) for i in parse_s(s_path))


def symbol_slots(s_path: Path) -> list[tuple[str, str]]:
    """Ordered (kind, symbol) slots that were masked — the retarget map source.
    kind in {hi, lo, gp_rel, call}."""
    slots: list[tuple[str, str]] = []
    for i in parse_s(s_path):
        slots.extend(i.syms)
    return slots


def tu_stem_of(s_path: Path) -> str | None:
    """nonmatchings/script/src/st08a/foo.s -> script/src/st08a (repo-rel sweep
    stem; `<stem>.c` is the owning TU source)."""
    for anchor in ("nonmatchings", "matchings"):
        if anchor in s_path.parts:
            i = s_path.parts.index(anchor)
            return str(Path(*s_path.parts[i + 1:-1]))
    return None


def iter_funcs(base: str = "nonmatchings"):
    """Yield (func_name, s_path, tu_stem) over every per-function .s. The
    nonmatchings/ tree carries one .s per in-scope func (matched OR not), so it
    is the canonical corpus for clone/templatize signature indexing."""
    root = ASM / base
    seen: set[str] = set()
    for s in root.rglob("*.s"):
        name = s.stem
        if name in seen:
            continue
        seen.add(name)
        yield name, s, tu_stem_of(s)


@lru_cache(maxsize=4)
def signature_index(imm_masked: bool = False) -> dict:
    """{signature -> [(func, s_path, tu_stem), ...]} over the whole corpus.
    imm_masked=True wildcards numeric immediates too (templatize near-clones).
    Funcs shorter than 4 insns are skipped (trampolines/stubs are noise)."""
    idx: dict[tuple, list] = {}
    sig_fn = imm_masked_signature if imm_masked else signature
    for name, s, tu in iter_funcs():
        try:
            insns = parse_s(s)
        except Exception:
            continue
        if len(insns) < 4:
            continue
        sig = (tuple(re.sub(r"-?0x[0-9A-Fa-f]+", "#", i.norm) for i in insns)
               if imm_masked else tuple(i.norm for i in insns))
        idx.setdefault(sig, []).append((name, s, tu))
    return idx


# ---------------------------------------------------------------------------
# data-file resolution
# ---------------------------------------------------------------------------

@lru_cache(maxsize=1)
def _symbol_addrs() -> dict:
    """name -> {vma, type, tu};  also reverse vma -> name."""
    by_name: dict[str, dict] = {}
    by_vma: dict[int, str] = {}
    f = ROOT / "config" / "symbol_addrs.aug6.txt"
    pat = re.compile(
        r"^(\w+)\s*=\s*0x([0-9A-Fa-f]+);\s*//\s*type:(\w+)(?:\s*//\s*(.*))?")
    for line in f.read_text().splitlines():
        m = pat.match(line.strip())
        if not m:
            continue
        name, vma_s, typ, tu = m.group(1), m.group(2), m.group(3), m.group(4)
        vma = int(vma_s, 16)
        by_name[name] = {"vma": vma, "type": typ, "tu": (tu or "").strip() or None}
        by_vma.setdefault(vma, name)
    return {"by_name": by_name, "by_vma": by_vma}


@lru_cache(maxsize=1)
def _tu_map() -> dict[int, dict]:
    f = ROOT / "decomp" / "tu_map.json"
    if not f.exists():
        return {}
    data = json.loads(f.read_text())
    rows = data if isinstance(data, list) else data.get("functions", [])
    return {int(r["vram"]): r for r in rows if "vram" in r}


@lru_cache(maxsize=1)
def _callgraph() -> dict[int, list[int]]:
    f = ROOT / "decomp" / "callgraph.json"
    if not f.exists():
        return {}
    data = json.loads(f.read_text())
    rows = data if isinstance(data, list) else data.get("edges", [])
    return {int(r["caller"]): [int(c) for c in r.get("callees", [])] for r in rows}


@lru_cache(maxsize=1)
def _struct_shapes() -> dict:
    f = ROOT / "decomp" / "struct_shapes.json"
    if not f.exists():
        return {}
    return json.loads(f.read_text()).get("globals", {})


def resolve(vma: int) -> dict:
    """vma -> {name, tu, source_file}; falls back to symbol_addrs then nearest."""
    tm = _tu_map().get(vma)
    if tm:
        return {"name": tm.get("name"), "tu": tm.get("tu"),
                "source_file": tm.get("source_file")}
    sa = _symbol_addrs()
    if vma in sa["by_vma"]:
        name = sa["by_vma"][vma]
        return {"name": name, "tu": sa["by_name"][name]["tu"], "source_file": None}
    return {"name": None, "tu": None, "source_file": None}


def name_to_vma(name: str) -> int | None:
    sa = _symbol_addrs()["by_name"].get(name)
    if sa:
        return sa["vma"]
    m = re.fullmatch(r"(?:func|D)_([0-9A-Fa-f]{8})", name)
    return int(m.group(1), 16) if m else None


def struct_shape(name: str) -> dict | None:
    return _struct_shapes().get(name)


# ---------------------------------------------------------------------------
# best-effort callee C-signature (for the bundle's reasoning aid)
# ---------------------------------------------------------------------------

_ARG_INT = ["$4", "$5", "$6", "$7", "$8", "$9"]      # a0..a3 then $8/$9 (n32-ish)
_ARG_FLT = ["$f12", "$f13", "$f14", "$f15", "$f16", "$f17"]


def callee_sig(name: str) -> str:
    """Best-effort signature hint for `name`. If the callee is matched, lift its
    declared C prototype from its TU .c; else infer arg/return registers from the
    first basic block of its `.s`. Heuristic — labelled as such in the bundle."""
    s = find_s(name)
    if s is None:
        return f"{name}(?)"
    # matched -> try the real C declaration
    if is_matched(s):
        proto = _c_prototype(name)
        if proto:
            return proto
    insns = parse_s(s)
    seen_int, seen_flt = set(), set()
    rets = set()
    for ins in insns[:24]:
        toks = re.findall(r"\$(?:f?\d+)", ins.ops)
        # a read of an arg reg before any obvious def => incoming arg
        for r in _ARG_INT:
            if r in toks:
                seen_int.add(r)
        for r in _ARG_FLT:
            if r in toks:
                seen_flt.add(r)
        if ins.mnem.startswith(("jr",)) and "$31" in ins.ops:
            pass
    n_int = sum(1 for r in _ARG_INT if r in seen_int)
    n_flt = sum(1 for r in _ARG_FLT if r in seen_flt)
    args = []
    if n_int:
        args.append(f"{n_int} int/ptr")
    if n_flt:
        args.append(f"{n_flt} float")
    return f"{name}(~{' + '.join(args) or 'void'}) [inferred from .s]"


def _c_prototype(name: str) -> str | None:
    """Grep the owning TU .c for `<ret> name(<params>) {` and return that line."""
    info = _symbol_addrs()["by_name"].get(name)
    tu = info.get("tu") if info else None
    if not tu:
        tm = _tu_map().get(name_to_vma(name) or -1)
        tu = tm.get("tu") if tm else None
    if not tu:
        return None
    c = ROOT / f"{tu}.c" if not str(tu).endswith(".c") else ROOT / str(tu)
    if not c.exists():
        return None
    pat = re.compile(r"^[\w \t\*]+\b" + re.escape(name) + r"\s*\([^;{]*\)\s*\{")
    for line in c.read_text(errors="replace").splitlines():
        if pat.match(line.strip()):
            return line.strip().rstrip("{").strip()
    return None
