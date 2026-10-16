#!/usr/bin/env python3
"""tools/check_targets.py: the source tree against the configured targets.

One tree, ico2/ and sce/, is every configured target's source; where the
targets differ, a file holds each one's lines in #ifdef VERSION_<SLUG>
blocks, which tools/compile_c.sh defines for the target it builds. A target
is configured when config/link_order.<slug>.txt exists. Four rules:

  1. Every source (.c, .s, .S, .dsm) is a row of at least one configured
     target's link order.
  2. Every source row of every configured link order is a file.
  3. No targets/ directory: a target's differences live in the shared file.
  4. A VERSION_<SLUG> name appears only in C sources and headers (.c, .h,
     .c.inc; nothing preprocesses the assembly and VU sources), and only for
     a configured slug.

The files are the ones git tracks or would track (untracked, not ignored),
so a file not yet staged is checked too.

    python3 tools/check_targets.py      exit 0 when every rule holds

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
PREPROCESSED = (".c", ".h", ".inc")
VERSION_NAME = re.compile(rb"\bVERSION_([A-Z0-9_]+)\b")


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
        # 4
        used = set(VERSION_NAME.findall((root / p).read_bytes()))
        if used and not p.endswith(PREPROCESSED):
            bad.append(f"{p}: VERSION_ blocks work only in C sources and headers")
        for u in sorted(used):
            if u.decode() not in names:
                bad.append(f"{p}: VERSION_{u.decode()} names no configured target"
                           f" (configured: {', '.join(slugs) or 'none'})")
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


def main() -> int:
    bad = problems(ROOT)
    for b in bad:
        print(f"check_targets: {b}", file=sys.stderr)
    slugs = configured_versions(ROOT)
    print(f"check_targets: {'FAIL' if bad else 'OK'} (targets {', '.join(slugs) or 'none'};"
          f" {len(bad)} problems)", file=sys.stderr)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
