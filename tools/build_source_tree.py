#!/usr/bin/env python3
"""
build_source_tree.py — generate the skeleton of the *original* ICO source
tree under `decomp/source_tree/`, populated from `__FILE__` paths the SCE
assert macro left in `.rodata`.

The skeleton is a planning / reference artifact. The build does not touch
it. Each placeholder file records:

  - the verbatim original path (e.g. `src/boy.c`)
  - the `.rodata` vma where its `__FILE__` literal anchors

Tooling that wants to map functions to TUs reads the anchor vma here and
matches it against the `lui+addiu` (or `gp_rel`) reference in each
function's disassembly.

Idempotent: re-running rewrites the tree from scratch. Any handwritten
placeholder content will be lost, by design — these files exist to be
empty.

Run: `.venv/bin/python tools/build_source_tree.py`
"""

from __future__ import annotations

import re
import shutil
import sys
from collections import defaultdict
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("build_source_tree: missing pyelftools. "
             "Run `.venv/bin/pip install -r tools/requirements.txt`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
BASEELF = REPO_ROOT / "baserom" / "baseelf.elf"
TREE_ROOT = REPO_ROOT / "decomp" / "source_tree"

# Directories we expect to find under the recovered tree, with a one-line
# description for each. New directories that surface get a TODO marker.
DIR_BLURBS = {
    "src":     "Game code — actor logic, render pipeline, scene/file management.",
    "ios":     "I/O system — wrappers around SCE SDK libs (cdvd, pad, mc, sif).",
    "isys":    "Interactive system — GObj per-frame game-object framework.",
    "sound":   "EE-side sound init / ADPCM. IOP-side audio lives in another ELF.",
    "include": "Public headers shared across the tree.",
}

# Subsystem groupings within src/. Keyed by file *stem* (without extension)
# or by hyphen-prefix for grouped names. Values are short hooks for the
# README. None / not-listed files fall under "(unsorted)".
SRC_SUBSYSTEMS = {
    "Player AI": [
        "boy", "boyact",
        "girl", "girlForceField", "girl_act",
        "girl_brain_main", "girl_brain_attract",
        "warpGirl",
    ],
    "Enemy AI": [
        "enemy", "enemyParts", "enemy_act", "EnemyInit",
        "ebrain",
        "itou_boss", "queen",
        "spider", "spiderGroupManager",
        "worm",
    ],
    "World objects": [
        "box", "cage", "candle", "chain", "flag", "item", "kanban",
        "rope", "rotObject", "switch", "sugiTree", "torch", "weapon",
    ],
    "Combat": [
        "attackhit", "attackCheckBoundary", "fightSound",
        "fieldCollision", "moveColTest",
    ],
    "Animation": [
        "BgAnimation", "StageAnimation",
        "motionManager", "motionManager2", "motionOrientManager",
        "motionViewer", "streamMotionManager", "multiBgaManager",
        "clothAnimation", "clothTest",
        "particleEffect", "particleLayout",
    ],
    "Render pipeline (PS2-specific)": [
        "DObj", "PObj",
        "DisplayList", "DmaPacket", "Packet", "RegistPacket",
        "Light", "Texture", "Primitive", "Basic", "layout_texture",
        "geometryManager", "lodManager",
    ],
    "Core / system": [
        "FileManager", "delayFreeManager", "pool",
        "sceneManager", "debug", "jimaku", "staffroll",
        "icoMisc", "commonact",
        "charFileManager",
    ],
    "Generators / scripting": [
        "generator", "act", "act-env", "act-game", "act-parallel-control",
        "mail-add-data",
    ],
    "Camera": [
        "camera-editor", "camera-ico2",
    ],
    "Misc / unsorted": [
        "a_p_1", "act_bird", "way_tool", "way_util", "stormTest",
    ],
}


def scan_rodata() -> dict[str, int]:
    """Return {original_path: rodata_vma} for every `<dir>/<file>.[ch]`
    pattern in `.rodata`. The vma is the address of the *first* occurrence
    (TUs emit one literal per file, so this is the anchor)."""
    if not BASEELF.exists():
        sys.exit(f"build_source_tree: {BASEELF} missing — run "
                 "tools/extract_elf.sh first.")
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        sec = elf.get_section_by_name(".rodata")
        if sec is None:
            sys.exit("build_source_tree: .rodata not found in baseelf")
        rod_vma = sec["sh_addr"]
        rod = sec.data()

    anchors: dict[str, int] = {}
    pat = re.compile(rb"\b([a-z][a-zA-Z0-9_]{1,12})/([A-Za-z0-9_-]+\."
                     rb"(?:c|h|cpp|cxx|inc))\b")
    for m in pat.finditer(rod):
        try:
            path = m.group(0).decode("ascii")
        except UnicodeDecodeError:
            continue
        # First occurrence wins (the TU's emitted literal).
        anchors.setdefault(path, rod_vma + m.start())
    return anchors


def placeholder_body(path: str, anchor_vma: int) -> str:
    """One-line C placeholder. Just enough to be searchable."""
    return (f"/* placeholder: {path} — __FILE__ anchor at "
            f".rodata 0x{anchor_vma:08x} */\n")


def render_dir_readme(dirname: str, files: list[tuple[str, int]]) -> str:
    """README for a top-level directory under the skeleton tree."""
    blurb = DIR_BLURBS.get(dirname, "TODO: describe this directory.")
    lines = [
        f"# `{dirname}/` — recovered ICO source",
        "",
        blurb,
        "",
        f"**{len(files)} file(s)** recovered from `__FILE__` literals in "
        "`baserom/baseelf.elf` `.rodata`. Each placeholder records its "
        "anchor vma — the address of the literal that lets us tie a "
        "`.text` function back to this TU.",
        "",
        "See `../source_tree.md` for the full recovery method.",
        "",
    ]
    if dirname == "src":
        # Group src/ by subsystem. Build a stem→(path, vma) lookup.
        by_stem: dict[str, tuple[str, int]] = {}
        for path, vma in files:
            stem = Path(path).stem  # 'src/boy.c' → 'boy'
            by_stem[stem] = (path, vma)

        used: set[str] = set()
        for subsys, stems in SRC_SUBSYSTEMS.items():
            present = [(s, by_stem[s]) for s in stems if s in by_stem]
            if not present:
                continue
            lines.append(f"## {subsys}")
            lines.append("")
            for stem, (path, vma) in present:
                lines.append(f"- `{Path(path).name}` — anchor 0x{vma:08x}")
                used.add(stem)
            lines.append("")
        leftover = [(p, v) for p, v in files if Path(p).stem not in used]
        if leftover:
            lines.append("## (Uncategorized)")
            lines.append("")
            for path, vma in leftover:
                lines.append(f"- `{Path(path).name}` — anchor 0x{vma:08x}")
            lines.append("")
    else:
        lines.append("## Files")
        lines.append("")
        for path, vma in files:
            lines.append(f"- `{Path(path).name}` — anchor 0x{vma:08x}")
        lines.append("")
    return "\n".join(lines)


def render_root_readme(by_dir: dict[str, list[tuple[str, int]]]) -> str:
    total = sum(len(v) for v in by_dir.values())
    lines = [
        "# `decomp/source_tree/` — original ICO source-tree skeleton",
        "",
        "Empty placeholders mirroring the *original* directory layout of",
        "ICO's source as recovered from `__FILE__` strings in",
        "`baserom/baseelf.elf` `.rodata`. **Build does not touch this**;",
        "it is a planning / reference artifact.",
        "",
        f"**{total} file(s) across {len(by_dir)} director(ies):**",
        "",
    ]
    for d in sorted(by_dir):
        lines.append(f"- `{d}/` — {len(by_dir[d])} file(s) — "
                     + DIR_BLURBS.get(d, "TODO"))
    lines.extend([
        "",
        "## Why this exists",
        "",
        "Each `.c`/`.h` here is a one-line placeholder recording the rodata",
        "vma of its `__FILE__` literal. That vma is the *anchor* for",
        "tying matched `.text` functions back to their original TU: any",
        "function that loads the anchor address (via `lui+addiu` or",
        "`%gp_rel`) belongs to this TU.",
        "",
        "When we begin grouping `cod/<offset>` subsegments into per-TU",
        "buckets, this directory is the target layout. Until then, it",
        "serves as a checklist of TUs and a record of recovery state.",
        "",
        "## Regenerating",
        "",
        "```sh",
        ".venv/bin/python tools/build_source_tree.py",
        "```",
        "",
        "Idempotent. New paths that surface in `.rodata` (e.g. after a",
        "future SDK change or additional inspection) will appear as new",
        "placeholders. Hand-edits to placeholders or READMEs are",
        "overwritten — extend `tools/build_source_tree.py` itself to",
        "change blurbs or subsystem groupings.",
        "",
        "## Caveats",
        "",
        "- TUs without any `assert()` produce no `__FILE__` literal and",
        "  do not appear here. Such TUs surface only as gaps between",
        "  identified TUs in `.text` ordering.",
        "- Inlined functions assert with the *inliner's* `__FILE__`, so",
        "  helpers that got inlined into a different TU will be tagged",
        "  to the inliner. Usually fine.",
        "- A few `<file>.c.inc` entries are inline-included fragments",
        "  rather than standalone TUs — see `../source_tree.md`.",
        "",
    ])
    return "\n".join(lines)


def main() -> int:
    anchors = scan_rodata()
    if not anchors:
        sys.exit("build_source_tree: no `__FILE__`-shaped paths found in "
                 ".rodata — has the ELF been stripped further?")

    # Group by top-level directory.
    by_dir: dict[str, list[tuple[str, int]]] = defaultdict(list)
    for path, vma in anchors.items():
        d = path.split("/", 1)[0]
        by_dir[d].append((path, vma))
    for d in by_dir:
        by_dir[d].sort()

    # Wipe and recreate the skeleton.
    if TREE_ROOT.exists():
        shutil.rmtree(TREE_ROOT)
    TREE_ROOT.mkdir(parents=True)

    # Top-level README.
    (TREE_ROOT / "README.md").write_text(render_root_readme(by_dir))

    file_count = 0
    for d, files in by_dir.items():
        ddir = TREE_ROOT / d
        ddir.mkdir(parents=True, exist_ok=True)
        (ddir / "README.md").write_text(render_dir_readme(d, files))
        for path, vma in files:
            fname = Path(path).name
            (ddir / fname).write_text(placeholder_body(path, vma))
            file_count += 1

    print(f"build_source_tree: {file_count} placeholder(s) across "
          f"{len(by_dir)} dir(s) under {TREE_ROOT.relative_to(REPO_ROOT)}/")
    for d in sorted(by_dir):
        print(f"  {d}/  {len(by_dir[d])} file(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
