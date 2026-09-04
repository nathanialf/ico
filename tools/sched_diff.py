#!/usr/bin/env python3
"""
sched_diff.py — show ee-gcc 2.9's scheduling decisions for one function.

Scheduling diffs (same instructions, different order / different delay-slot
occupant) are the hardest matching residual to fix BLIND. ee-gcc 2.9 produces
the final instruction order across four RTL passes, each with its own lever:

    sched   (-dS)  first scheduler, PRE register-alloc  -> source order / live ranges
    sched2  (-dR)  second scheduler, POST register-alloc -> -fno-schedule-insns2
    dbr     (-dd)  delayed-branch reorg, fills delay slots -> readiness at the branch

This tool compiles the function with the EXACT quick_diff CFLAGS plus the
dump flags, slices the function out of each
dump, and shows:

  * the final (dbr) instruction stream as readable pseudo-ops, with each
    branch's DELAY-SLOT occupant marked `└delay→` (the motionOrientManager
    `daddu s2,a2`-in-the-beqz-delay case is visible directly), and
  * a MOVE MAP: for every insn, its position in sched / sched2 / dbr, flagging
    the pass at which it changed rank — so you target the lever for THAT pass
    instead of guessing with barriers.

Usage:
    tools/sched_diff.py <TU> <func>          # dbr stream + move map
    tools/sched_diff.py <TU> <func> --pass sched|sched2|dbr   # one pass stream
    tools/sched_diff.py <TU> <func> --raw <pass>             # dump path (full RTL)

`<TU>` is the same arg quick_diff/match_diff take (e.g. `cod/05F228`,
`motionOrientManager`). `<func>` selects the function inside a coalesced TU.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EEGCC = ROOT / "tools" / "cc" / "ee-gcc2.9-991111" / "ee-gcc"
EEGCC_LIB = ROOT / "tools" / "cc" / "ee-gcc2.9-991111" / "gcc-lib" / "ee" / "2.9-ee-991111-01"
BASE_CFLAGS = ["-S", "-G", "8", "-O2", "-mips3", "-EL", "-fno-builtin",
               "-nostdinc", "-fdata-sections", "-I" + str(ROOT / "include")]
PASS_SUFFIX = {"sched": "sched", "sched2": "sched2", "dbr": "dbr"}
DUMP_FLAG = {"sched": "-dS", "sched2": "-dR", "dbr": "-dd"}


# aug6 is the `main` layout: TUs live under per-programmer roots and are
# addressed by their full subseg path (e.g. `ito/mpeg/mv_disp`). Retail (us)
# addressed them by bare basename under src/. Resolve both.
SRC_ROOTS = ("", "src", "common", "fumi", "sugipon", "seki", "omori",
             "script", "ito", "ios", "sound", "isys")


def resolve_src(tu: str) -> Path:
    # 1. Full subseg path (aug6): `ito/mpeg/mv_disp` -> `ito/mpeg/mv_disp.c`.
    #    Also covers any root-relative path the caller already qualified.
    direct = ROOT / f"{tu}.c"
    if direct.is_file():
        return direct
    # 2. Bare-name forms under each known root (+ the parked-seed layout).
    cands = [f"tough_nuts/{tu}/{tu}.c"]
    cands += [f"{root}/{tu}.c" if root else f"{tu}.c" for root in SRC_ROOTS]
    for cand in cands:
        p = ROOT / cand
        if p.is_file():
            return p
    # 3. Recursive fallback: a bare basename anywhere under a known root
    #    (handles nested subsegs like `ito/mpeg/<name>` given just `<name>`).
    base = tu.split("/")[-1]
    for root in SRC_ROOTS:
        rdir = ROOT / root if root else ROOT
        if not rdir.is_dir():
            continue
        for hit in rdir.rglob(f"{base}.c"):
            if "/build/" not in str(hit) and "/asm/" not in str(hit):
                return hit
    sys.exit(f"sched_diff: no source for TU '{tu}' "
             f"(tried <tu>.c, src/, tough_nuts/, and aug6 roots "
             f"{', '.join(r for r in SRC_ROOTS if r)})")


def compile_dumps(src: Path, outdir: Path) -> Path:
    """Compile src into outdir with all three pass dumps; return dump base."""
    cc = EEGCC if EEGCC.exists() else Path("mips64r5900el-ps2-elf-gcc")
    cflags = list(BASE_CFLAGS)
    if EEGCC.exists():
        cflags = ["-B", str(EEGCC_LIB) + "/"] + cflags
    # gcc 2.9 writes pass dumps to the CWD, named <input_basename>.<pass>.
    # Copy the source into outdir and compile with cwd=outdir so the dumps
    # land there (and not in the repo root).
    local = outdir / src.name
    local.write_text(src.read_text())
    cmd = [str(cc), *cflags, "-dS", "-dR", "-dd", src.name, "-o", "out.s"]
    proc = subprocess.run(cmd, capture_output=True, text=True, cwd=str(outdir))
    if proc.returncode != 0:
        sys.exit("sched_diff: compile failed:\n" + proc.stderr.strip())
    return outdir / (src.name + ".")  # dumps are <name>.c.<pass>


def slice_function(dump: Path, func: str) -> str | None:
    """Return the RTL text for one `;; Function <func>` block."""
    if not dump.exists():
        return None
    text = dump.read_text(errors="replace")
    marker = f";; Function {func}\n"
    i = text.find(marker)
    if i < 0:
        # single-function file: gcc still emits `;; Function NAME`; if the
        # requested func isn't found, fall back to the whole dump.
        return text if text.strip() else None
    j = text.find("\n;; Function ", i + len(marker))
    return text[i:j if j >= 0 else len(text)]


# ---------------------------------------------------------------------------
# Minimal RTL reader: split a function dump into top-level insn forms, pull the
# UID + a readable reduction of the (set dst src) pattern.  Best-effort: any
# form it can't reduce degrades to a whitespace-collapsed truncation, so the
# UID/position machinery never depends on the pretty-printer.
# ---------------------------------------------------------------------------
_CMP = {"ne": "!=", "eq": "==", "lt": "<", "ge": ">=", "le": "<=", "gt": ">",
        "ltu": "<u", "geu": ">=u", "leu": "<=u", "gtu": ">u"}


def _split(s: str) -> tuple[str, list[str]]:
    """Split a balanced `(op a b c)` (brackets [] treated like ()) into
    (op, [arg_text...]).  op is the first token; args are balanced children
    or atoms."""
    s = s.strip()
    if not (s.startswith("(") or s.startswith("[")):
        return s, []
    inner = s[1:-1].strip()
    # op = leading token up to whitespace or an opening bracket
    m = re.match(r"[^\s()\[\]]+", inner)
    op = m.group(0) if m else ""
    rest = inner[len(op):].strip()
    args, depth, cur = [], 0, ""
    for ch in rest:
        if ch in "([":
            depth += 1
            cur += ch
        elif ch in ")]":
            depth -= 1
            cur += ch
        elif ch.isspace() and depth == 0:
            if cur:
                args.append(cur)
                cur = ""
        else:
            cur += ch
    if cur:
        args.append(cur)
    return op, args


def _base(op: str) -> str:
    return op.split(":", 1)[0].split("/", 1)[0]


def _vector_children(s: str) -> list[str]:
    """Split a `[ (a) (b) ... ]` RTL vector into its top-level `(...)` forms."""
    s = s.strip().lstrip("[").rstrip("]")
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1; cur += ch
        elif ch in ")]":
            depth -= 1; cur += ch
            if depth == 0 and cur.strip():
                out.append(cur.strip()); cur = ""
        elif depth > 0:
            cur += ch
    return out


def reduce_rtl(s: str) -> str:
    s = s.strip()
    if s.startswith('"'):
        return s.strip('"')
    if not s.startswith("(") and not s.startswith("["):
        return s.strip('"')
    op, args = _split(s)
    if op.startswith('"'):
        return op.strip('"')
    b = _base(op)
    try:
        if b == "reg":
            return args[-1] if len(args) >= 2 else "r" + args[0]
        if b == "const_int":
            return "#" + args[0]
        if b == "symbol_ref":
            return reduce_rtl(args[0])
        if b == "label_ref":
            return "L" + args[-1]
        if b == "pc":
            return "pc"
        if b == "high":
            return "%hi(" + reduce_rtl(args[0]) + ")"
        if b == "lo_sum":
            return "%lo(" + reduce_rtl(args[1]) + ")+" + reduce_rtl(args[0])
        if b in ("plus", "minus", "mult", "and", "ior", "xor", "ashift",
                 "ashiftrt", "lshiftrt", "div", "udiv", "mod"):
            sym = {"plus": "+", "minus": "-", "mult": "*", "and": "&",
                   "ior": "|", "xor": "^", "ashift": "<<", "ashiftrt": ">>",
                   "lshiftrt": ">>u", "div": "/", "udiv": "/u", "mod": "%"}[b]
            return f"{reduce_rtl(args[0])} {sym} {reduce_rtl(args[1])}"
        if b in _CMP:
            return f"{reduce_rtl(args[0])} {_CMP[b]} {reduce_rtl(args[1])}"
        if b == "mem":
            return "mem[" + reduce_rtl(args[0]) + "]"
        if b == "set":
            return f"{reduce_rtl(args[0])} = {reduce_rtl(args[1])}"
        if b == "if_then_else":
            cond = reduce_rtl(args[0])
            tgt = args[2] if reduce_rtl(args[1]) == "pc" else args[1]
            return f"if {cond} goto {reduce_rtl(tgt)}"
        if b == "parallel":
            # first (set ...) child of the vector carries the operation
            children = _vector_children(args[0]) if args else []
            for a in children:
                if _base(_split(a)[0]) == "set":
                    return reduce_rtl(a)
        if b == "asm_operands":
            return "asm(" + reduce_rtl(args[0]) + ")" if args else "asm(...)"
        if b in ("zero_extend", "sign_extend", "truncate", "neg", "not",
                 "abs", "float_extend"):
            return f"{b}({reduce_rtl(args[0])})"
    except (IndexError, RecursionError):
        pass
    return re.sub(r"\s+", " ", s)[:48]


def _form_uid(form: str) -> int | None:
    m = re.match(r"\([A-Za-z_]+[A-Za-z0-9_/:]*\s+(\d+)", form.strip())
    return int(m.group(1)) if m else None


def _pattern_of(form: str) -> str:
    """Extract the readable op for an insn form (whatever follows UID/links)."""
    _, args = _split(form)
    # insn layout: UID PREV NEXT PATTERN CODE {name} ...
    if len(args) >= 4:
        return reduce_rtl(args[3])
    return re.sub(r"\s+", " ", form)[:48]


def parse_insns(block: str):
    """Yield (uid, kind, text, delay_uids) for each real insn in source order.
    kind in {insn, jump, call}.  Delay-slot insns are attached to their branch
    and NOT yielded separately."""
    # split into top-level forms: a new form starts at a line beginning with '('
    forms, cur = [], ""
    for line in block.splitlines():
        if line.startswith("(") and cur:
            forms.append(cur)
            cur = line + "\n"
        else:
            cur += line + "\n"
    if cur.strip():
        forms.append(cur)

    out = []
    for form in forms:
        head = form.lstrip("(").split(None, 1)[0]
        base = head.split("/", 1)[0].split(":", 1)[0]
        if base not in ("insn", "jump_insn", "call_insn"):
            continue
        uid = _form_uid(form)
        if "(sequence[" in form:
            # branch + delay slot(s): pull the inner forms
            inner = form[form.index("(sequence[") + len("(sequence["):]
            sub, d, cu = [], 0, ""
            for ch in inner:
                if ch in "([":
                    d += 1; cu += ch
                elif ch in ")]":
                    d -= 1; cu += ch
                    if d <= 0 and cu.strip().startswith("("):
                        sub.append(cu.strip()); cu = ""
                        if d < 0:
                            break
                else:
                    cu += ch
            if not sub:
                out.append((uid, "jump", _pattern_of(form), []))
                continue
            jump = sub[0]
            juid = _form_uid(jump)
            delays = [(_form_uid(x), _pattern_of(x)) for x in sub[1:]]
            out.append((juid, "jump", _pattern_of(jump),
                        [(u, p) for (u, p) in delays]))
        else:
            kind = {"insn": "insn", "jump_insn": "jump",
                    "call_insn": "call"}[base]
            out.append((uid, kind, _pattern_of(form), []))
    return out


def order_uids(block: str) -> list[int]:
    """Linear UID order of real insns (delay-slot insns inline after branch)."""
    order = []
    for uid, kind, _pat, delays in parse_insns(block):
        if uid is not None:
            order.append(uid)
        for du, _ in delays:
            if du is not None:
                order.append(du)
    return order


def render_stream(block: str) -> str:
    def uid_s(u):
        return f"{u:>4}" if u is not None else "   ?"
    lines = []
    for uid, kind, pat, delays in parse_insns(block):
        mark = {"insn": "   ", "jump": ">> ", "call": "() "}[kind]
        lines.append(f"  {mark}{uid_s(uid)}  {pat}")
        for du, dp in delays:
            lines.append(f"      └delay→ {uid_s(du)}  {dp}")
    return "\n".join(lines)


def move_map(streams: dict[str, str]) -> str:
    """Report which insns were REORDERED, and by which pass — robust to the
    global UID renumbering that happens when insn count changes.  An insn
    "moved at pass P" when its immediate predecessor in the linear order
    differs from the previous pass (local adjacency change), which ignores the
    bulk shift that absolute ranks suffer.  Delay-slot occupants are starred —
    those are dbr's doing and the most common matching residual."""
    orders = {p: order_uids(b) for p, b in streams.items() if b}
    passes = [p for p in ("sched", "sched2", "dbr") if p in orders]
    if not passes:
        return "  (no insns parsed)"
    pred = {}
    for p in passes:
        o = orders[p]
        pred[p] = {u: (o[i - 1] if i else None) for i, u in enumerate(o)}
    delay = {p: _delay_uids(streams[p]) for p in passes}
    final = orders.get("dbr") or orders[passes[-1]]
    rows, any_move = [], False
    for u in final:
        moved = ""
        for k in range(1, len(passes)):
            pp, cp = passes[k - 1], passes[k]
            if u in pred[pp] and u in pred[cp] and pred[pp][u] != pred[cp][u]:
                moved = cp
                break
        star = " *delay" if u in delay.get("dbr", set()) else ""
        if moved or star:
            any_move = True
            tag = (f"moved@{moved}" if moved else "") + star
            rows.append(f"  {u:>4}  {tag.strip()}")
    if not any_move:
        return "  (no reorder between passes — order is stable from sched1)"
    return ("  insns reordered across passes (cmp this build's own passes; "
            "* = filled a delay slot):\n" + "\n".join(rows))


def _delay_uids(block: str) -> set:
    out = set()
    for _uid, _kind, _pat, delays in parse_insns(block):
        for du, _ in delays:
            if du is not None:
                out.add(du)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("tu")
    ap.add_argument("func")
    ap.add_argument("--pass", dest="which", choices=("sched", "sched2", "dbr"),
                    help="print just this pass's instruction stream")
    ap.add_argument("--raw", choices=("sched", "sched2", "dbr"),
                    help="print the path to the raw RTL dump and exit")
    args = ap.parse_args()

    src = resolve_src(args.tu)
    with tempfile.TemporaryDirectory() as td:
        outdir = Path(td)
        base = compile_dumps(src, outdir)
        dumps = {p: Path(str(base) + suf) for p, suf in PASS_SUFFIX.items()}
        blocks = {p: (slice_function(d, args.func) or "") for p, d in dumps.items()}

        if args.raw:
            # persist the requested raw dump so the path survives the tempdir
            keep = ROOT / "build" / "sched_diff"
            keep.mkdir(parents=True, exist_ok=True)
            dst = keep / f"{args.func}.{args.raw}"
            dst.write_text(blocks[args.raw] or "(function not found)")
            print(dst)
            return 0

        if not any(blocks.values()):
            sys.exit(f"sched_diff: function '{args.func}' not found in dumps "
                     f"(is it still INCLUDE_ASM?)")

        if args.which:
            print(f"== {args.func}: {args.which} ==")
            print(render_stream(blocks[args.which]))
            return 0

        print(f"== {args.func}: final (dbr) instruction stream "
              f"[>> branch, └delay→ delay-slot] ==")
        print(render_stream(blocks["dbr"]))
        print(f"\n== move map: which pass reordered each insn ==")
        print(move_map(blocks))
        return 0


if __name__ == "__main__":
    sys.exit(main())
