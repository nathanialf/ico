#!/usr/bin/env python3
"""tools/check_targets.py: the source tree against the configured targets.

One tree, ico2/ and sce/, is every configured target's source; where the
targets differ, a file holds each one's lines in #ifdef VERSION_<SLUG>
blocks, which tools/compile_c.sh defines for the target it builds. A target
is configured when config/link_order.<slug>.txt exists. Five rules:

  1. Every source (.c, .s, .S, .dsm) is a row of at least one configured
     target's link order, and every VU program text (.vsm) is the mate of a
     listed .dsm (the same stem).
  2. Every source row of every configured link order is a file.
  3. No targets/ directory: a target's differences live in the shared file.
  4. A VERSION_<SLUG> name appears only in C sources and headers (.c, .h,
     .c.inc) and in the VU program text (.vsm), which the period cpp reads
     with VERSION_<SLUG> defined (tools/gen_ninja.py's vucpp rule); nothing
     preprocesses the .s and .dsm sources. Only a configured slug is named.
  5. A VERSION_<SLUG> name appears only in a version condition of one of
     these forms (version_condition below), each arm of a block covering the
     targets its condition names:

         #ifdef VERSION_A                     #ifndef VERSION_A
         #if defined(VERSION_A) || defined(VERSION_B)
         #if !defined(VERSION_A) && !defined(VERSION_B)
         #elif defined(VERSION_A) [|| defined(VERSION_B)]
         #else                                #endif

     An #elif or #else of a version block follows its #if, and an #elif
     names no target an earlier arm of the block already took.

The files are the ones git tracks or would track (untracked, not ignored),
so a file not yet staged is checked too.

    python3 tools/check_targets.py              exit 0 when every rule holds
    python3 tools/check_targets.py --self-test  the condition forms on fixed cases

tools/gen_ninja.py runs the same check before it writes build.ninja, and
the pre-commit hook runs this script. Plain python3, no venv.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from ico_version import configured_versions, config_path, layer_files  # noqa: E402

SOURCES = (".c", ".s", ".S", ".dsm")
PREPROCESSED = (".c", ".h", ".inc", ".vsm")
VERSION_NAME = re.compile(rb"\bVERSION_([A-Z0-9_]+)\b")

_DIRECTIVE = re.compile(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)$")
_DEFINED = r"defined\(VERSION_([A-Z0-9_]+)\)"
_ANY_OF = re.compile(rf"{_DEFINED}(?:\s+\|\|\s+{_DEFINED})*")
_NONE_OF = re.compile(rf"!{_DEFINED}(?:\s+&&\s+!{_DEFINED})*")


def version_condition(line: str):
    """A preprocessor line read as a version block's directive.

    Returns (kw, slugs, positive) for a version condition: kw "if" or "elif",
    slugs the lower-case target names it tests, positive False when the arm
    is taken for the targets it does not name (#ifndef, the !defined form).
    Returns (kw, None, None) for #else and #endif and for a conditional that
    names no VERSION_ (its block is not a version block), and None for a
    line that is no conditional directive. Raises ValueError for a
    conditional naming a VERSION_ in any other form."""
    m = _DIRECTIVE.match(line)
    if not m:
        return None
    kw, rest = m.group(1), m.group(2).split("/*", 1)[0].strip()
    if "VERSION_" not in rest:
        return (kw, None, None)
    names = re.findall(r"VERSION_([A-Z0-9_]+)", rest)
    if kw in ("ifdef", "ifndef") and re.fullmatch(r"VERSION_[A-Z0-9_]+", rest):
        return ("if", frozenset(n.lower() for n in names), kw == "ifdef")
    if kw in ("if", "elif") and _ANY_OF.fullmatch(rest):
        return (kw, frozenset(n.lower() for n in names), True)
    if kw == "if" and _NONE_OF.fullmatch(rest):
        return (kw, frozenset(n.lower() for n in names), False)
    raise ValueError(f"#{kw} {rest}: not a version condition form")


def condition_holds(slugs, positive, slug: str) -> bool:
    """Whether a version condition's arm is the one target `slug` compiles."""
    return (slug in slugs) == positive


def version_block_problems(text: str) -> list[str]:
    """Rule 5 on one file's text: every VERSION_ in an accepted directive,
    and each version block's arms in order. (line, message) strings."""
    bad = []
    stack = []  # per open conditional: None, or the targets its arms took so far
    for n, line in enumerate(text.splitlines(), 1):
        try:
            v = version_condition(line)
        except ValueError as e:
            bad.append(f"{n}: {e}")
            # read on as a block that is not a version block
            v = (_DIRECTIVE.match(line).group(1), None, None)
        if v is None:
            if VERSION_NAME.search(line.encode()):
                bad.append(f"{n}: VERSION_ outside a version condition")
            continue
        kw, slugs, positive = v
        if kw in ("if", "ifdef", "ifndef"):
            stack.append(None if slugs is None else (set(slugs) if positive else {"*"}))
        elif kw == "elif":
            if not stack:
                bad.append(f"{n}: #elif with no #if")
            elif stack[-1] is None:
                if slugs is not None:
                    bad.append(f"{n}: a version #elif in a block whose #if names no VERSION_")
            elif slugs is None:
                bad.append(f"{n}: an #elif of a version block names no VERSION_")
            elif "*" in stack[-1]:
                bad.append(f"{n}: #elif after a negative (#ifndef/!defined) arm")
            elif stack[-1] & slugs:
                bad.append(f"{n}: #elif names {', '.join(sorted(stack[-1] & slugs))}, taken by an earlier arm")
            else:
                stack[-1] |= slugs
        elif kw == "else":
            if not stack:
                bad.append(f"{n}: #else with no #if")
        elif kw == "endif":
            if not stack:
                bad.append(f"{n}: #endif with no #if")
            else:
                stack.pop()
    if stack:
        bad.append(f"{len(text.splitlines())}: {len(stack)} conditional(s) left open")
    return bad


def link_rows(root: Path, slug: str) -> list[tuple[int, str]]:
    """(line, path) of each source row of config/link_order.<slug>.txt (a
    `data:` row names a member, not a file, and is left out)."""
    out = []
    for n, line in enumerate(config_path(root, slug, "link_order", "txt").read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        kind, _, name = f[0].rpartition(":")
        if (kind or "src") == "src":
            out.append((n, name))
    return out


def problems(root: Path = ROOT) -> list[str]:
    slugs = configured_versions(root)
    rows = {s: link_rows(root, s) for s in slugs}
    listed = {name for r in rows.values() for _, name in r}
    names = {s.upper() for s in slugs}
    bad = []
    files = layer_files(root)
    for p in files:
        # 1
        if p.endswith(SOURCES) and p not in listed:
            bad.append(f"{p}: in no configured target's link order"
                       f" (configured: {', '.join(slugs) or 'none'})")
        if p.endswith(".vsm") and p[:-4] + ".dsm" not in listed:
            bad.append(f"{p}: not the program text of a listed .dsm (the same stem)")
        # 4
        used = set(VERSION_NAME.findall((root / p).read_bytes()))
        if used and not p.endswith(PREPROCESSED):
            bad.append(f"{p}: VERSION_ blocks work only in C sources and headers and the VU program text")
        for u in sorted(used):
            if u.decode() not in names:
                bad.append(f"{p}: VERSION_{u.decode()} names no configured target"
                           f" (configured: {', '.join(slugs) or 'none'})")
        # 5
        if used and p.endswith(PREPROCESSED):
            text = (root / p).read_text(encoding="latin-1")
            bad.extend(f"{p}:{b}" for b in version_block_problems(text))
    # 2
    for s in slugs:
        for n, name in rows[s]:
            if not (root / name).is_file():
                bad.append(f"config/link_order.{s}.txt:{n}: {name} is not a file")
    # 3
    if (root / "targets").exists():
        bad.append("targets/: a target's differences go inline in the shared file"
                   " as VERSION_<SLUG> blocks, not in a per-target tree")
    return bad


SELF_TEST = (
    # (lines, expected problem count)
    ("#ifdef VERSION_JPN\n#else\n#endif", 0),
    ("#ifndef VERSION_JPN\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR)\n#else\n#endif", 0),
    ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR)\n#endif", 0),
    ("#ifdef VERSION_KOR\n#elif defined(VERSION_JPN)\n#else\n#endif", 0),
    ("#if defined(VERSION_KOR)\n#elif defined(VERSION_JPN) || defined(VERSION_NTSC)\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC)\n#else\n#endif", 0),
    ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR)\n#else\n#ifdef VERSION_NTSC\n#else\n#endif\n#endif", 0),
    # a fifth target: named beside the fourth, nested inside its arm, or inside the PAL arm of both
    ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6)\n#else\n#endif", 0),
    ("#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)\n#else\n#endif", 0),
    ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6)\n#ifdef VERSION_AUG6\n#else\n#endif\n#else\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR)\n#else\n#ifdef VERSION_NTSC\n#else\n#ifdef VERSION_AUG6\n#else\n#endif\n#endif\n#endif", 0),
    # a sixth target: named beside the fifth, nested inside its arm (the fourth's arm around
    # both), excluded inside a three-name PAL-only block, or on its own at the fourth level
    ("#if defined(VERSION_AUG6) || defined(VERSION_JUN26)\n#else\n#endif", 0),
    ("#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)\n#endif", 0),
    ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)\n#ifdef VERSION_JUN26\n#else\n#endif\n#else\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_JUN26)\n#else\n#endif", 0),
    ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)\n#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)\n#endif\n#endif", 0),
    ("#if defined(VERSION_JPN) || defined(VERSION_KOR)\n#else\n#ifdef VERSION_NTSC\n#else\n#ifdef VERSION_AUG6\n#else\n#ifdef VERSION_JUN26\n#else\n#endif\n#endif\n#endif\n#endif", 0),
    ("#if 0\n#ifdef VERSION_JPN\n#endif\n#elif 1\n#endif", 0),
    ("#if defined(VERSION_JPN) && defined(VERSION_KOR)\n#endif", 1),
    ("#if defined(VERSION_JPN) || !defined(VERSION_KOR)\n#endif", 1),
    ("#if VERSION_JPN\n#endif", 1),
    ("#if X && defined(VERSION_JPN)\n#endif", 1),
    ("#elif defined(VERSION_JPN)", 1),
    ("#ifdef VERSION_JPN\n#elif defined(VERSION_JPN)\n#endif", 1),
    ("#ifndef VERSION_JPN\n#elif defined(VERSION_KOR)\n#endif", 1),
    ("#ifdef VERSION_JPN\n#elif FOO\n#endif", 1),
    ("#if FOO\n#elif defined(VERSION_JPN)\n#endif", 1),
    ("#ifdef VERSION_JPN", 1),
    ("int VERSION_JPN;", 1),
    ("extern const _LIB_VERSION_TYPE _LIB_VERSION;", 0),
)


def self_test() -> int:
    failed = 0
    for text, want in SELF_TEST:
        got = version_block_problems(text)
        ok = len(got) == want
        failed += not ok
        print(f"check_targets: self-test {'ok  ' if ok else 'FAIL'} {text.splitlines()[0]!r}"
              f" ({len(got)} problems, want {want})", file=sys.stderr)
    for line, slug, want in (("#ifdef VERSION_JPN", "kor", False),
                             ("#ifndef VERSION_JPN", "pal", True),
                             ("#if defined(VERSION_JPN) || defined(VERSION_KOR)", "kor", True),
                             ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR)", "kor", False),
                             ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR)", "pal", True),
                             ("#elif defined(VERSION_JPN)", "jpn", True),
                             ("#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC)", "ntsc", True),
                             ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)", "ntsc", False),
                             ("#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)", "pal", True),
                             ("#ifdef VERSION_NTSC", "pal", False),
                             ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6)", "aug6", True),
                             ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6)", "ntsc", True),
                             ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6)", "pal", False),
                             ("#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)", "aug6", False),
                             ("#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)", "jpn", True),
                             ("#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_AUG6)", "aug6", True),
                             ("#ifdef VERSION_AUG6", "ntsc", False),
                             ("#if defined(VERSION_AUG6) || defined(VERSION_JUN26)", "jun26", True),
                             ("#if defined(VERSION_AUG6) || defined(VERSION_JUN26)", "aug6", True),
                             ("#if defined(VERSION_AUG6) || defined(VERSION_JUN26)", "ntsc", False),
                             ("#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)", "jun26", False),
                             ("#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)", "pal", True),
                             ("#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)", "jun26", True),
                             ("#ifdef VERSION_JUN26", "aug6", False)):
        _, slugs, positive = version_condition(line)
        ok = condition_holds(slugs, positive, slug) == want
        failed += not ok
        print(f"check_targets: self-test {'ok  ' if ok else 'FAIL'} {line!r} for {slug}", file=sys.stderr)
    print(f"check_targets: self-test {'FAIL' if failed else 'OK'} ({failed} failed)", file=sys.stderr)
    return 1 if failed else 0


def main() -> int:
    if "--self-test" in sys.argv[1:]:
        return self_test()
    bad = problems(ROOT)
    for b in bad:
        print(f"check_targets: {b}", file=sys.stderr)
    slugs = configured_versions(ROOT)
    print(f"check_targets: {'FAIL' if bad else 'OK'} (targets {', '.join(slugs) or 'none'};"
          f" {len(bad)} problems)", file=sys.stderr)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
