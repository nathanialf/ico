#!/usr/bin/env python3
"""
progress.py — regenerate README.md / docs/PROGRESS.md status tables.

Reads config/ico.us.yaml + the current src/ tree, computes per-section
matched-bytes ratios from claimed `c` subsegments, and rewrites the
status tables in README.md and docs/PROGRESS.md.

A subsegment counted as "matched" iff:
  - its yaml entry has type `c` (claimed for matching), and
  - the corresponding src/<name>.c file actually exists.

Sizes are pulled from baserom/baseelf.elf section headers so the
ratios stay accurate even if subsegment boundaries shift.

Output format: two-decimal-place percentages (e.g. `0.42 %`).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("progress.py: missing PyYAML. Run `.venv/bin/pip install pyyaml`.")

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("progress.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
YAML = REPO_ROOT / "config" / "ico.us.yaml"
BASEELF = REPO_ROOT / "baserom" / "baseelf.elf"
README = REPO_ROOT / "README.md"
PROGRESS_DOC = REPO_ROOT / "docs" / "PROGRESS.md"

# Source roots that contribute to the "matched" tally. Phase 1
# flattened ios/, sound/, isys/ out of src/ to repo-root siblings;
# their compiled .o files live at build/<root>/ alongside build/src/.
SOURCE_ROOTS = ("src", "ios", "sound", "isys")
BUILD_OBJ_DIRS = tuple(REPO_ROOT / "build" / r for r in SOURCE_ROOTS)

# Yaml subsegment types that correspond to each ELF section. Splat lumps
# .vutext under `textbin` because it's hand-written VU code rather than
# auto-disassembled MIPS — we account for it as its own row.
SECTION_TO_TYPES = {
    ".text":   {"asm", "c", "hasm"},
    ".vutext": {"textbin"},
    ".data":   {"data"},
    ".rodata": {"rodata"},
    ".lit4":   {"lit4"},
    ".sdata":  {"sdata"},
}
MATCHABLE_TYPES = {"c", "hasm"}

# Non-text sections we credit from compiled object emissions. With
# `migrate_rodata_to_functions: True` in the splat config, rodata/lit4/
# sdata bytes referenced from a matched function disappear from the YAML
# entirely and reappear inside the function's `.o`. Walking the YAML
# alone therefore under-counts non-text matches; we walk built objects to
# recover those bytes. .text stays YAML-driven so progress works without
# a build.
OBJECT_SECTION_PREFIXES = (".rodata", ".data", ".lit4", ".sdata")


def _human_bytes(n: int) -> str:
    if n >= 1 << 20:
        return f"{n / (1 << 20):.2f} MB"
    if n >= 1 << 10:
        return f"{n / (1 << 10):.2f} KB"
    return f"{n} B"


def _load_section_sizes() -> dict[str, int]:
    """Map ELF section name -> size in bytes, from baserom/baseelf.elf."""
    if not BASEELF.exists():
        sys.exit(f"progress: {BASEELF} not found - run tools/extract_elf.sh first.")
    sizes: dict[str, int] = {}
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            sizes[sec.name] = sec["sh_size"]
    return sizes


def _walk_subsegments(yaml_doc: dict) -> list[tuple[int, str, str]]:
    """Return [(file_offset, type, name)] from the cod segment."""
    out: list[tuple[int, str, str]] = []
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list):
            continue  # closing sentinel like [0x533BC6]
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list):
                if len(sub) < 2:
                    continue
                offset = sub[0]
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                offset = sub.get("vram", 0)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            out.append((offset, stype, name))
    return out


def _claim_size(subs: list[tuple[int, str, str]], idx: int, default_end: int) -> int:
    """Distance from this subseg's offset to the next, in bytes."""
    cur_off = subs[idx][0]
    if idx + 1 < len(subs):
        return subs[idx + 1][0] - cur_off
    return max(0, default_end - cur_off)


_INCLUDE_ASM_RE = re.compile(
    r'\bINCLUDE_ASM\s*\(\s*"[^"]+"\s*,\s*(\w+)\s*\)'
)


def _include_asm_bytes(name: str) -> int:
    """Sum bytes of every INCLUDE_ASM'd function referenced from the
    matched src file `name` (yaml subseg name, repo-root-relative).
    Function sizes are read from the `nonmatching <func>, 0x<size>`
    directive splat emits at the top of each per-function .s file.

    Returns 0 if the .c file is absent or has no INCLUDE_ASMs."""
    csrc = REPO_ROOT / f"{name}.c"
    if not csrc.exists():
        return 0
    try:
        text = csrc.read_text()
    except Exception:
        return 0
    total = 0
    for func in _INCLUDE_ASM_RE.findall(text):
        s = REPO_ROOT / "asm" / "nonmatchings" / name / f"{func}.s"
        if not s.exists():
            continue
        try:
            head = s.read_text()
        except Exception:
            continue
        # `nonmatching <func>, 0x<size>` lives in the .s preamble.
        m = re.search(r"\bnonmatching\s+" + re.escape(func) + r"\s*,\s*0x([0-9A-Fa-f]+)", head)
        if m:
            total += int(m.group(1), 16)
    return total


def _section_for_type(stype: str) -> str | None:
    for sec, types in SECTION_TO_TYPES.items():
        if stype in types:
            return sec
    return None


def _src_exists(name: str, stype: str) -> bool:
    # After the Phase 1 flatten, yaml subseg names are repo-root-
    # relative (e.g. `src/DmaPacket`, `ios/cdvd`, `src/cod/0FBB48`).
    # The earlier convention prepended `src/` here; that doubles the
    # prefix and silently makes every check fail. Resolve directly
    # against the repo root instead.
    ext = "s" if stype == "hasm" else "c"
    return (REPO_ROOT / f"{name}.{ext}").exists()


def _section_for_object_section(name: str) -> str | None:
    """Map a section name from a built .o (e.g. '.rodata.func_001234') to
    one of the rollup buckets in SECTION_TO_TYPES."""
    for prefix in OBJECT_SECTION_PREFIXES:
        if name == prefix or name.startswith(prefix + "."):
            return prefix
    return None


def _tracked_source_files() -> set[Path]:
    """Set of repo-rooted .c/.s files tracked by git across every
    source root (src/, ios/, sound/, isys/). Used by
    `_walk_built_objects` to exclude .o files built from gitignored
    sources — the auto-generated per-TU `_data.c` sidecars contain
    raw bytes from the original ELF (IP-sensitive) and shouldn't
    count toward the "matched" progress. Only hand-typed sources,
    which are tracked, contribute.

    Falls back to "track everything" if `git ls-files` isn't available
    (e.g. running outside a git checkout)."""
    import subprocess
    try:
        out = subprocess.check_output(
            ["git", "-C", str(REPO_ROOT), "ls-files",
             *[f"{r}/" for r in SOURCE_ROOTS], "--", "*.c", "*.s"],
            text=True, stderr=subprocess.DEVNULL,
        )
    except (subprocess.CalledProcessError, FileNotFoundError):
        return set()  # signal: don't filter
    return {REPO_ROOT / line.strip() for line in out.splitlines() if line.strip()}


def _walk_built_objects() -> dict[str, int]:
    """Sum non-text section bytes across every built object under
    build/{src,ios,sound,isys}/ whose corresponding source file is
    tracked by git. Untracked sources (the auto-generated per-TU
    `_data.c` files in particular) are *excluded* because their byte
    content comes directly from the original ELF and isn't a hand-
    typed clean-room reconstruction — counting them inflates the
    "matched" numbers with bytes we haven't actually decompiled.

    Returns zeros if the build tree is missing — running progress
    before a build is supported (e.g. fresh clone, post-`tools/build.sh split`)."""
    matched: dict[str, int] = {p: 0 for p in OBJECT_SECTION_PREFIXES}

    tracked = _tracked_source_files()
    # tracked == empty set with falsy bool => no filtering (git not
    # available). Distinguishing "git not available" from "no tracked
    # src files" is intentionally optimistic here: if git is missing
    # we'd rather show inflated progress than no progress.
    no_filter = not tracked

    for build_root in BUILD_OBJ_DIRS:
        if not build_root.exists():
            continue
        for obj in build_root.rglob("*.o"):
            if not no_filter:
                # Map the .o path back to its source .c/.s under the
                # mirroring source root (build/<root>/X.o → <root>/X.c).
                rel = obj.relative_to(build_root)
                root_name = build_root.name
                src_c = REPO_ROOT / root_name / rel.with_suffix(".c")
                src_s = REPO_ROOT / root_name / rel.with_suffix(".s")
                if src_c not in tracked and src_s not in tracked:
                    continue
            try:
                with obj.open("rb") as f:
                    elf = ELFFile(f)
                    for sec in elf.iter_sections():
                        if sec["sh_type"] == "SHT_NOBITS":
                            continue
                        bucket = _section_for_object_section(sec.name)
                        if bucket is None:
                            continue
                        matched[bucket] += sec["sh_size"]
            except Exception as e:
                print(f"progress: skipping {obj.name}: {e}", file=sys.stderr)
    return matched


def compute_progress() -> dict[str, tuple[int, int]]:
    """Return {section_name: (matched_bytes, total_bytes)}."""
    yaml_doc = yaml.safe_load(YAML.read_text())
    sizes = _load_section_sizes()
    subs = _walk_subsegments(yaml_doc)

    # The cod segment runs to the closing sentinel address (the last
    # top-level item). Splat seeds it as e.g. `[0x533BC6]`.
    final_off = 0
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list) and len(seg) >= 1:
            final_off = max(final_off, seg[0])

    matched: dict[str, int] = {sec: 0 for sec in SECTION_TO_TYPES}
    for i, (_off, stype, name) in enumerate(subs):
        sec = _section_for_type(stype)
        if sec is None:
            continue
        size = _claim_size(subs, i, final_off)
        if stype in MATCHABLE_TYPES and name and _src_exists(name, stype):
            # Honest count: a coalesced TU's `c` subseg covers its
            # whole range, but any function still INCLUDE_ASM'd inside
            # that .c isn't actually a match — it's the original asm
            # being passed through. Subtract those bytes so .text %
            # reflects real decompilation progress, not yaml shape.
            if sec == ".text":
                size -= _include_asm_bytes(name)
            matched[sec] += max(0, size)

    # Add migrated rodata / lit4 / sdata bytes emitted from compiled
    # objects. Object emissions take precedence over YAML accounting for
    # non-text sections — explicit YAML rodata subsegments (when added)
    # will reach the same bytes via the same .o, so we drop the YAML
    # contribution there to avoid double counting.
    obj_matched = _walk_built_objects()
    for sec, n in obj_matched.items():
        matched[sec] = n

    totals = {sec: sizes.get(sec, 0) for sec in SECTION_TO_TYPES}
    return {sec: (matched[sec], totals[sec]) for sec in SECTION_TO_TYPES}


def _fmt_pct(matched: int, total: int) -> str:
    if total == 0:
        return "-"
    return f"{(100.0 * matched / total):.2f} %"


# ----- README table ---------------------------------------------------

README_BEGIN = "<!-- progress:begin -->"
README_END = "<!-- progress:end -->"

# Only .text rolls up as decomp progress. Data sections (.data/.rodata/
# .lit4/.sdata) are tracked via the gitignored auto-gen `_data.c`
# sidecar pattern (raw bytes extracted from baserom at build time, not
# committed). Their "matched" percentage is misleading — it conflates
# auto-gen byte fidelity with hand-typed clean-room reconstruction.
# Drop the data rows; resurrect if we ever start tracking typed-data
# promotion as a metric.
README_SECTIONS = [".text"]


def _render_readme_table(progress: dict[str, tuple[int, int]]) -> str:
    lines = [
        "| Section          | Matched | Total |",
        "| ---------------- | ------: | ----: |",
    ]
    for sec in README_SECTIONS:
        matched, total = progress.get(sec, (0, 0))
        lines.append(
            f"| `{sec}` | {_fmt_pct(matched, total):>7} | {_human_bytes(total)} |"
        )
    return "\n".join(lines)


def _splice_block(text: str, begin: str, end: str, body: str) -> str:
    """Replace the content between `begin` and `end` markers (inclusive)
    with `body`. Inserts the markers if missing.
    """
    if begin in text and end in text:
        pat = re.compile(re.escape(begin) + r".*?" + re.escape(end), re.DOTALL)
        return pat.sub(begin + "\n" + body + "\n" + end, text)
    return text + ("\n" if not text.endswith("\n") else "") + begin + "\n" + body + "\n" + end + "\n"


def _update_readme(progress: dict[str, tuple[int, int]]) -> bool:
    if not README.exists():
        return False
    text = README.read_text()
    table = _render_readme_table(progress)

    if README_BEGIN in text:
        new = _splice_block(text, README_BEGIN, README_END, table)
    else:
        # First-time: replace the seed table block and insert markers.
        # Match the table whose header row matches the README seed.
        seed = re.compile(
            r"\| Section\s+\| Matched \| Total \|\n"
            r"\|[-: ]+\|[-: ]+\|[-: ]+\|\n"
            r"(?:\|[^\n]*\|\n)+",
            re.MULTILINE,
        )
        replacement = README_BEGIN + "\n" + table + "\n" + README_END + "\n"
        if seed.search(text):
            new = seed.sub(replacement, text, count=1)
        else:
            return False  # no anchor - refuse to scribble blindly

    if new == text:
        return False
    README.write_text(new)
    return True


# ----- docs/PROGRESS.md table -----------------------------------------

PROGRESS_BEGIN = "<!-- progress:begin -->"
PROGRESS_END = "<!-- progress:end -->"


def _render_progress_table(progress: dict[str, tuple[int, int]]) -> str:
    lines = [
        "| Section | Matched bytes | Total bytes | % |",
        "| --- | ---: | ---: | ---: |",
    ]
    for sec in [".text", ".vutext"]:
        matched, total = progress.get(sec, (0, 0))
        lines.append(
            f"| `{sec}` | {matched} | {total} | {_fmt_pct(matched, total)} |"
        )
    return "\n".join(lines)


def _update_progress_doc(progress: dict[str, tuple[int, int]]) -> bool:
    if not PROGRESS_DOC.exists():
        return False
    text = PROGRESS_DOC.read_text()
    table = _render_progress_table(progress)

    if PROGRESS_BEGIN in text:
        new = _splice_block(text, PROGRESS_BEGIN, PROGRESS_END, table)
    else:
        seed = re.compile(
            r"\| Section \| Matched bytes \| Total bytes \| % \|\n"
            r"\|[-: ]+\|[-: ]+\|[-: ]+\|[-: ]+\|\n"
            r"(?:\|[^\n]*\|\n)+",
            re.MULTILINE,
        )
        replacement = PROGRESS_BEGIN + "\n" + table + "\n" + PROGRESS_END + "\n"
        if seed.search(text):
            new = seed.sub(replacement, text, count=1)
        else:
            return False

    if new == text:
        return False
    PROGRESS_DOC.write_text(new)
    return True


def main() -> int:
    if not YAML.exists():
        print(f"progress: {YAML} not found", file=sys.stderr)
        return 1
    progress = compute_progress()

    print("progress (matched / total):")
    for sec, (m, t) in progress.items():
        print(f"  {sec:<10} {m:>10} / {t:<10} {_fmt_pct(m, t):>8}")

    changed_readme = _update_readme(progress)
    changed_doc = _update_progress_doc(progress)
    if changed_readme:
        print(f"progress: rewrote {README.relative_to(REPO_ROOT)}")
    if changed_doc:
        print(f"progress: rewrote {PROGRESS_DOC.relative_to(REPO_ROOT)}")
    if not (changed_readme or changed_doc):
        print("progress: tables already up-to-date")
    return 0


if __name__ == "__main__":
    sys.exit(main())
