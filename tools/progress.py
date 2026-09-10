#!/usr/bin/env python3
"""
progress.py — regenerate README.md progress badges and docs/PROGRESS.md.

Reads the active splat yaml + the current src/ tree, computes per-section
matched-bytes ratios from claimed `c` subsegments, and rewrites the
status tables in README.md and docs/PROGRESS.md.

A subsegment counted as "matched" iff:
  - its yaml entry has type `c` (claimed for matching), and
  - the corresponding src/<name>.c file actually exists.

Sizes are pulled from this target's baseelf.elf section headers (baserom/
for us, baserom/<ver>/ for pal and aug6) so the ratios stay accurate even if
subsegment boundaries shift. Every section the reference ELF declares gets a
row: .text, .vutext, .data, .vudata, .rodata, .lit4, .sdata, .sbss, .bss.

The two NOBITS sections (.sbss, .bss) hold no ROM bytes, so their column is
OWNERSHIP, not reproduction: the bytes of the section that a compiled C
object defines for itself and the link places at the ROM's VMAs. See
NOBITS_SECTIONS.

Output format: two-decimal-place percentages (e.g. `0.42 %`).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path
from urllib.parse import quote

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
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import (  # noqa: E402
    detect_version, yaml_path, baseelf_path, source_roots,
)

# Version-aware: `main` = PAL retail (config/ico.pal.yaml +
# baserom/pal/baseelf.elf), `ntsc` = USA retail, `aug6` = the prototype.
# Explicit VERSION env wins; else auto-detect from which config exists.
VERSION = detect_version(REPO_ROOT)
YAML = yaml_path(REPO_ROOT, VERSION)
BASEELF = baseelf_path(REPO_ROOT, VERSION)
README = REPO_ROOT / "README.md"
PROGRESS_DOC = REPO_ROOT / "docs" / "PROGRESS.md"

# Source roots that contribute to the "matched" tally. The retail targets
# (us, pal) flattened ios/, sound/, isys/ out of src/ to repo-root siblings;
# their compiled .o files live at build/<root>/ alongside build/src/. The aug6
# prototype adds the dev's per-developer module tree. The union is walked on
# every target — a root that doesn't exist contributes nothing.
SOURCE_ROOTS = tuple(dict.fromkeys(source_roots("us") + source_roots("aug6")))
BUILD_OBJ_DIRS = tuple(REPO_ROOT / "build" / r for r in SOURCE_ROOTS)

# Yaml subsegment types that correspond to each ELF section. Splat lumps
# .vutext under `textbin` because it's hand-written VU code rather than
# auto-disassembled MIPS — we account for it as its own row.  Hand-typed
# VU0 chunks land as `hasm` subsegs in the .vutext VRAM range; the
# address check in `_section_for_subseg` keeps them out of the .text
# tally and credits them to .vutext.
# Both spellings are listed per section: splat's raw blob subsegments use
# the bare type (`data`, `sbss`), the per-TU carve rows use the dot form
# (`.data`, `.sbss`) that tells the linker to place THAT TU's own section
# there. Only MATCHABLE_TYPES ever adds to the matched tally straight from
# the yaml; the data/bss rows are here so every ELF section this target has
# is a key of `compute_progress()`.
SECTION_TO_TYPES = {
    ".text":   {"asm", "c", "hasm"},
    ".vutext": {"textbin", "hasm"},
    ".data":   {"data", ".data"},
    ".vudata": {"vudata", ".vudata"},
    ".rodata": {"rodata", ".rodata"},
    ".lit4":   {"lit4", ".lit4"},
    ".sdata":  {"sdata", ".sdata"},
    ".sbss":   {"sbss", ".sbss"},
    ".bss":    {"bss", ".bss"},
}
MATCHABLE_TYPES = {"c", "hasm"}

# The two NOBITS sections. They occupy no ROM bytes, so "matched" cannot mean
# "these bytes are reproduced"; it means OWNERSHIP — the run of the section a
# compiled C object defines for itself (its own `.sbss`/`.bss`, or its COMMON
# symbols, which `ld_bss_contains_common: True` folds into .bss) and which the
# link places at the ROM's VMAs. Reported under the same badge/table as the
# PROGBITS sections, labelled as ownership wherever the metric is shown.
NOBITS_SECTIONS = (".sbss", ".bss")

# VRAM range that the .vutext ELF section covers. Subsegs landing here
# count toward .vutext even if their yaml type is also valid for .text
# (e.g. hasm). Filled in from baseelf.elf on first use; cached in
# _VUTEXT_RANGE.
_VUTEXT_RANGE: tuple[int, int] | None = None

# Non-text sections we credit from compiled object emissions. With
# `migrate_rodata_to_functions: True` in the splat config, rodata/lit4/
# sdata bytes referenced from a matched function disappear from the YAML
# entirely and reappear inside the function's `.o`. Walking the YAML
# alone therefore under-counts non-text matches; we walk built objects to
# recover those bytes. .text stays YAML-driven so progress works without
# a build.
OBJECT_SECTION_PREFIXES = (".rodata", ".data", ".vudata", ".lit4", ".sdata")

# Sections credited from built objects at all: the PROGBITS ones above plus
# the NOBITS pair, whose object-side bytes are the ownership metric.
CREDITED_SECTION_PREFIXES = OBJECT_SECTION_PREFIXES + NOBITS_SECTIONS

# A COMMON symbol has no section of its own in the object; the link allocates
# it. `ld_bss_contains_common: True` sends the ordinary ones to .bss, and the
# small ones (<= the -G threshold, MIPS' own SHN_MIPS_SCOMMON) to .sbss. Both
# are bytes the defining object owns, so both are credited. pyelftools hands
# back the name for the generic index and the raw number for the MIPS one.
SHN_MIPS_SCOMMON = 0xFF03
COMMON_SHNDX_SECTION = {
    "SHN_COMMON": ".bss",
    SHN_MIPS_SCOMMON: ".sbss",
}


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


def segment_vram_base(yaml_doc: dict) -> int:
    """VRAM minus file offset for the code segment (0x100000 on every ICO
    target so far).

    List-form subsegment rows carry a ROM FILE OFFSET; dict-form rows carry
    `vram:` — and the NOBITS rows have to be dict-form because a NOBITS
    section has no file offset at all. Mixing the two spaces in one list
    makes every span across the boundary wrong, so `_walk_subsegments`
    normalises everything to VRAM with this base."""
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, dict) and "vram" in seg:
            return int(seg["vram"]) - int(seg.get("start") or 0)
    return 0x100000


def _walk_subsegments(yaml_doc: dict) -> list[tuple[int, str, str]]:
    """Return [(vram, type, name)] from the cod segment, in yaml order."""
    base = segment_vram_base(yaml_doc)
    out: list[tuple[int, str, str]] = []
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list):
            continue  # closing sentinel like [0x533BC6]
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list):
                if len(sub) < 2:
                    continue
                vram = sub[0] + base
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                vram = (int(sub["vram"]) if "vram" in sub
                        else int(sub.get("start") or 0) + base)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            out.append((vram, stype, name))
    return out


def _claim_size(subs: list[tuple[int, str, str]], idx: int, default_end: int) -> int:
    """Distance from this subseg's VRAM to the next, in bytes."""
    cur = subs[idx][0]
    if idx + 1 < len(subs):
        return subs[idx + 1][0] - cur
    return max(0, default_end - cur)


_INCLUDE_ASM_RE = re.compile(
    r'\bINCLUDE_ASM(?:_NOAT)?\s*\(\s*"([^"]+)"\s*,\s*(\w+)\s*\)'
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
        text = csrc.read_text(encoding="utf-8", errors="replace")
    except Exception:
        return 0
    total = 0
    # Use the asm dir from the INCLUDE_ASM directive itself (e.g.
    # "asm/aug6/nonmatchings/sugipon/src/pool") so it works for any version's
    # asm_path, not just retail's asm/nonmatchings/.
    for asmdir, func in _INCLUDE_ASM_RE.findall(text):
        s = REPO_ROOT / asmdir / f"{func}.s"
        if not s.exists():
            s = REPO_ROOT / "asm" / "nonmatchings" / name / f"{func}.s"  # legacy fallback
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


def _vutext_range() -> tuple[int, int]:
    """Lazy-load the .vutext VRAM range from baseelf.elf.

    `_walk_subsegments` normalises every subsegment address to VRAM, so
    the section's own `sh_addr` bounds are used as-is."""
    global _VUTEXT_RANGE
    if _VUTEXT_RANGE is not None:
        return _VUTEXT_RANGE
    if not BASEELF.exists():
        _VUTEXT_RANGE = (0, 0)
        return _VUTEXT_RANGE
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            if sec.name == ".vutext":
                _VUTEXT_RANGE = (sec["sh_addr"],
                                 sec["sh_addr"] + sec["sh_size"])
                return _VUTEXT_RANGE
    _VUTEXT_RANGE = (0, 0)
    return _VUTEXT_RANGE


def _section_for_subseg(vram: int, stype: str) -> str | None:
    """Address-aware mapping. A subseg in the .vutext VRAM range counts
    as .vutext regardless of yaml type (textbin or hasm — both are
    valid forms for VU code); everything else falls back to the
    type-only mapping."""
    lo, hi = _vutext_range()
    if lo <= vram < hi:
        if stype in {"textbin", "hasm"}:
            return ".vutext"
    return _section_for_type(stype)


def _src_exists(name: str, stype: str) -> bool:
    # After the Phase 1 flatten, yaml subseg names are repo-root-
    # relative (e.g. `src/DmaPacket`, `ios/cdvd`, `src/cod/0FBB48`).
    # The earlier convention prepended `src/` here; that doubles the
    # prefix and silently makes every check fail. Resolve directly
    # against the repo root instead.
    if stype == "hasm":
        # VU0 hand-typed sources commit as `<name>.S` (uppercase);
        # `tools/assemble_vu0.py` regenerates `<name>.s` from it as a
        # build artifact. Either form is a real, tracked match.
        if (REPO_ROOT / f"{name}.S").exists():
            return True
        return (REPO_ROOT / f"{name}.s").exists()
    return (REPO_ROOT / f"{name}.c").exists()


def _section_for_object_section(name: str) -> str | None:
    """Map a section name from a built .o (e.g. '.rodata.func_001234' or
    '.bss.gGameStatus') to one of the credited rollup buckets."""
    for prefix in CREDITED_SECTION_PREFIXES:
        if name == prefix or name.startswith(prefix + "."):
            return prefix
    return None


def _tracked_source_files() -> set[Path]:
    """Set of repo-rooted .c/.s files tracked by git across every
    source root (src/, ios/, sound/, isys/). Used by
    `object_section_credits` to exclude .o files built from gitignored
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


def _is_attr_form(sec_name: str, base: str) -> bool:
    """True for attr-tagged-form section names like `.rodata.0x00553700`.
    False for plain-form sections (`.rodata`, `.rodata.str1.4`)."""
    if not sec_name.startswith(base + "."):
        return False
    rest = sec_name[len(base) + 1:]
    return rest.startswith("0x") or rest.startswith("0X")


def _tu_key_for_object(build_root: Path, obj: Path) -> str:
    """`build/src/foo/bar.o` -> `src/foo/bar`: the repo-root-relative TU stem.

    That stem is exactly the key the yaml subsegment rows and the
    `// <path>` TU notes in config/symbol_addrs use, so per-object figures
    join straight onto the TU tree progress_tree.py builds."""
    return str(Path(build_root.name) / obj.relative_to(build_root).with_suffix(""))


def _object_section_bytes(obj: Path) -> tuple[dict[str, int], dict[str, int]]:
    """(attr_form, plain_form) credited section bytes for ONE built object.

    PROGBITS sections contribute their `sh_size` — those bytes land in the
    ROM and the SHA-1 gate proves them. The NOBITS sections (.sbss, .bss)
    contribute `sh_size` as well, but as OWNERSHIP: no bytes exist to
    reproduce, so what is being counted is how much of the section this
    object defines and the link seats at the ROM's VMAs. COMMON symbols get
    no section of their own in the object, so they are read off the symbol
    table and added to the section the link would put them in.
    """
    attr: dict[str, int] = {}
    plain: dict[str, int] = {}
    with obj.open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            bucket = _section_for_object_section(sec.name)
            if bucket is None:
                continue
            if sec["sh_type"] == "SHT_NOBITS" and bucket not in NOBITS_SECTIONS:
                continue     # a PROGBITS bucket's NOBITS namesake is not it
            sz = sec["sh_size"]
            if not sz:
                continue     # every object carries empty .data/.bss shells
            if _is_attr_form(sec.name, bucket):
                attr[bucket] = attr.get(bucket, 0) + sz
            else:
                plain[bucket] = plain.get(bucket, 0) + sz
        symtab = elf.get_section_by_name(".symtab")
        if symtab is not None:
            for sym in symtab.iter_symbols():
                bucket = COMMON_SHNDX_SECTION.get(sym["st_shndx"])
                if bucket is None or not sym["st_size"]:
                    continue
                plain[bucket] = plain.get(bucket, 0) + sym["st_size"]
    return attr, plain


_OBJ_CREDITS: dict | None = None


def object_section_credits() -> dict:
    """Credited non-.text bytes from every built object, walked ONCE.

    Shared by progress.py (the badges / PROGRESS.md table) and
    progress_tree.py (docs/progress.json) so the two can never disagree
    about what a section is worth.

    Returns::

        {"attr":  {section: bytes},     # `.X.0x<VMA>` splat-carved sections
         "plain": {section: bytes},     # bare `.X`, gcc's `.X.<sym>`, COMMON
         "by_tu": {tu_stem: {section: bytes}}}

    Objects under build/{src,ios,sound,isys,...}/ whose source file is not
    tracked by git are excluded: the auto-generated per-TU `_data.c`
    sidecars take their byte content straight from the original ELF, so
    counting them would inflate "matched" with bytes nobody decompiled.

    All zeros if the build tree is missing — running progress before a
    build is supported (fresh clone, post-`tools/build.sh split`)."""
    global _OBJ_CREDITS
    if _OBJ_CREDITS is not None:
        return _OBJ_CREDITS

    attr: dict[str, int] = {p: 0 for p in CREDITED_SECTION_PREFIXES}
    plain: dict[str, int] = {p: 0 for p in CREDITED_SECTION_PREFIXES}
    by_tu: dict[str, dict[str, int]] = {}

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
                o_attr, o_plain = _object_section_bytes(obj)
            except Exception as e:
                print(f"progress: skipping {obj.name}: {e}", file=sys.stderr)
                continue
            tu = _tu_key_for_object(build_root, obj)
            per_tu = by_tu.setdefault(tu, {})
            for src, dst in ((o_attr, attr), (o_plain, plain)):
                for sec, sz in src.items():
                    dst[sec] = dst.get(sec, 0) + sz
                    per_tu[sec] = per_tu.get(sec, 0) + sz
            if not per_tu:
                by_tu.pop(tu, None)

    _OBJ_CREDITS = {"attr": attr, "plain": plain, "by_tu": by_tu}
    return _OBJ_CREDITS


def compute_progress() -> dict[str, tuple[int, int]]:
    """Return {section_name: (matched_bytes, total_bytes)} for every section
    the reference ELF declares.

    For .sbss and .bss the first number is owned bytes, not reproduced ones
    — see NOBITS_SECTIONS. Totals always come from the ELF section headers,
    never from the yaml, so a section the yaml does not mention at all (an
    empty .vudata, say) still reports its real size."""
    yaml_doc = yaml.safe_load(YAML.read_text())
    sizes = _load_section_sizes()
    subs = _walk_subsegments(yaml_doc)
    base = segment_vram_base(yaml_doc)

    # The cod segment runs to the closing sentinel address (the last
    # top-level item). Splat seeds it as e.g. `[0x533BC6]` — a file offset,
    # normalised to VRAM like every other address here.
    final_vram = 0
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list) and len(seg) >= 1:
            final_vram = max(final_vram, seg[0] + base)

    matched: dict[str, int] = {sec: 0 for sec in SECTION_TO_TYPES}
    # {section: {tu: bytes}} for explicit per-TU NOBITS carve rows —
    # `[addr, .sbss, src/<tu>]` / `{type: .bss, vram: ..., name: src/<tu>}`.
    # Those rows are a LINKER PLACEMENT for the TU's own bss, so they claim
    # the same bytes the object already accounts for; they are unioned
    # per-TU with the object figures below rather than added to them.
    yaml_nobits: dict[str, dict[str, int]] = {s: {} for s in NOBITS_SECTIONS}

    for i, (vram, stype, name) in enumerate(subs):
        sec = _section_for_subseg(vram, stype)
        if sec is None:
            continue
        size = _claim_size(subs, i, final_vram)
        if stype in MATCHABLE_TYPES and name and _src_exists(name, stype):
            # Honest count: a coalesced TU's `c` subseg covers its
            # whole range, but any function still INCLUDE_ASM'd inside
            # that .c isn't actually a match — it's the original asm
            # being passed through. Subtract those bytes so .text %
            # reflects real decompilation progress, not yaml shape.
            if sec == ".text":
                size -= _include_asm_bytes(name)
            matched[sec] += max(0, size)
        elif (sec in NOBITS_SECTIONS and stype.startswith(".")
                and name and _src_exists(name, "c")):
            yaml_nobits[sec][name] = yaml_nobits[sec].get(name, 0) + max(0, size)

    # Add migrated rodata / lit4 / sdata bytes emitted from compiled
    # objects. Object emissions take precedence over YAML accounting for
    # non-text sections — explicit YAML rodata subsegments (when added)
    # will reach the same bytes via the same .o, so we drop the YAML
    # contribution there to avoid double counting.
    credits = object_section_credits()
    attr_form, plain_form, by_tu = (
        credits["attr"], credits["plain"], credits["by_tu"])
    # Cache the split for callers that need to distinguish explicit
    # VMA-pinned sections from normal compiler-emitted sections, and the
    # per-TU breakdown for the dashboard tree.
    compute_progress.attr_form = dict(attr_form)
    compute_progress.plain_form = dict(plain_form)
    compute_progress.by_tu = {tu: dict(s) for tu, s in by_tu.items()}
    for sec in OBJECT_SECTION_PREFIXES:
        matched[sec] = attr_form.get(sec, 0) + plain_form.get(sec, 0)
    # NOBITS ownership, per TU: whichever of the two views claims more for a
    # given TU wins, so a carve row still reports when the build tree is
    # absent and an object's bss still reports when no carve row exists —
    # without a TU ever being counted twice.
    for sec in NOBITS_SECTIONS:
        obj_tu = {tu: s[sec] for tu, s in by_tu.items() if s.get(sec)}
        yml_tu = yaml_nobits[sec]
        matched[sec] = sum(max(obj_tu.get(tu, 0), yml_tu.get(tu, 0))
                           for tu in set(obj_tu) | set(yml_tu))

    totals = {sec: sizes.get(sec, 0) for sec in SECTION_TO_TYPES}
    # Clamp matched against section total: subsegment spans (from yaml
    # subseg-to-next-subseg distance) include any trailing alignment
    # padding the linker absorbs between sections, but only the bytes
    # inside the section header's `sh_size` are real section content.
    # Without clamping, a hasm subseg that emits its own alignment pad
    # (e.g. VU0's 64-byte trailing zeros) can credit slightly over 100%.
    for sec in matched:
        matched[sec] = min(matched[sec], totals[sec])
    return {sec: (matched[sec], totals[sec]) for sec in SECTION_TO_TYPES}


def _fmt_pct(matched: int, total: int) -> str:
    if total == 0:
        return "-"
    return f"{(100.0 * matched / total):.2f} %"


# ----- README badges --------------------------------------------------

README_BEGIN = "<!-- progress:begin -->"
README_END = "<!-- progress:end -->"

# Code and data are separate progress axes (MM-decomp style). The data
# rows (.data/.vudata/.rodata/.lit4/.sdata) count only bytes emitted from
# compiled *git-tracked* sources — i.e. hand-typed defs and
# matched functions' embedded constants — so they start at 0% and move
# as the aug6 per-TU data carving / dot-form migration lands. (The old
# retail `_data.c` sidecar pattern that made these numbers misleading
# is gone; sidecars were never tracked and are excluded anyway.)
#
# The .sbss / .bss rows are the OWNERSHIP metric (NOBITS_SECTIONS), not a
# reproduced-bytes one. They are badged alongside the rest because the
# question they answer — how much of the section belongs to a TU we have
# written — is the same question, and the label says which metric it is.
#
# Order is ELF link order, so the badge strip reads like `readelf -S`. A
# section the ELF sizes at zero (.vudata on PAL) badges as "-"/lightgrey
# rather than dividing by zero.
README_SECTIONS = [".text", ".vutext", ".data", ".vudata", ".rodata",
                   ".lit4", ".sdata", ".sbss", ".bss"]


def _badge_color(matched: int, total: int) -> str:
    if total == 0:
        return "lightgrey"
    pct = 100.0 * matched / total
    if pct >= 100.0:
        return "brightgreen"
    if pct >= 75.0:
        return "green"
    if pct >= 50.0:
        return "yellowgreen"
    if pct >= 25.0:
        return "yellow"
    if pct > 0.0:
        return "orange"
    return "red"


def _badge_url(label: str, matched: int, total: int) -> str:
    # shields.io reads the path as `label-message-color`, so a literal dash
    # inside a field has to be escaped or the parse shifts. `_fmt_pct` returns
    # "-" for a zero-sized section (.vudata here), which unescaped would give
    # `vudata---lightgrey` and an ambiguous split; %2D is a dash under any
    # reading of the path. urllib's quote() leaves "-" alone (it is unreserved),
    # hence the explicit replace.
    pct = quote(_fmt_pct(matched, total), safe="").replace("-", "%2D")
    return (
        "https://img.shields.io/badge/"
        f"{label}-{pct}-{_badge_color(matched, total)}.svg"
    )


def _render_readme_badges(progress: dict[str, tuple[int, int]]) -> str:
    lines = []
    for sec in README_SECTIONS:
        matched, total = progress.get(sec, (0, 0))
        if total == 0:
            # The ELF has no bytes in this section (.vudata on every ICO
            # target); nothing to be a fraction of, so no badge.
            continue
        label = sec.lstrip(".")
        lines.append(f"![{sec} progress]({_badge_url(label, matched, total)})")
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
    badges = _render_readme_badges(progress)

    if README_BEGIN in text:
        new = _splice_block(text, README_BEGIN, README_END, badges)
    else:
        # First-time: replace the seed table block and insert markers.
        # Match the table whose header row matches the README seed.
        seed = re.compile(
            r"\| Section\s+\| Matched \| Total \|\n"
            r"\|[-: ]+\|[-: ]+\|[-: ]+\|\n"
            r"(?:\|[^\n]*\|\n)+",
            re.MULTILINE,
        )
        replacement = README_BEGIN + "\n" + badges + "\n" + README_END + "\n"
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
    # Totals are the reference ELF's own section sizes, so every section it
    # declares gets a row even when the yaml never mentions it.
    # Data rows reflect bytes emitted from compiled tracked sources
    # (typed defs in tracked TUs and matched function bodies' embedded
    # constants). Untracked sources are excluded from the matched tally
    # (see object_section_credits).
    for sec in README_SECTIONS:
        matched, total = progress.get(sec, (0, 0))
        if total == 0:
            continue                      # zero-sized in this ELF: no row
        metric = " (owned)" if sec in NOBITS_SECTIONS else ""
        lines.append(
            f"| `{sec}`{metric} | {matched} | {total} | "
            f"{_fmt_pct(matched, total)} |"
        )
    lines.append("")
    lines.append(
        "`.sbss` and `.bss` are NOBITS: they hold no ROM bytes, so their "
        "figure is **ownership**, how much of the section a compiled C "
        "object defines and the link seats at the ROM's VMAs, not "
        "reproduced bytes. A section the ELF sizes at zero (`.vudata` on "
        "this target) is omitted."
    )

    return "\n".join(lines)


def _progress_tail() -> str:
    return (
        "\n\nPer-overlay or per-file breakdown will appear here once "
        f"`config/ico.{VERSION}.yaml`\ndeclares boundaries.\n"
    )


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

    tail = re.compile(
        r"\n\nPer-overlay or per-file breakdown will appear here once "
        r"`config/ico\.[^.]+\.yaml`\ndeclares boundaries\.\n?$"
    )
    new = tail.sub(_progress_tail(), new)
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
