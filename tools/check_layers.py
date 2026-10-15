#!/usr/bin/env python3
"""tools/check_layers.py: the source layers against the configured targets.

The shared tree (ico2/, sce/) is every configured target's source except
where the target's overlay, targets/<slug>/, holds a file at the same
relative path (tools/ico_version.py, resolve_source). A target is configured
when config/link_order.<slug>.txt exists. Five rules:

  1. An overlay file sits at a shared-tree path (targets/<slug>/ico2/... or
     targets/<slug>/sce/...), and it is not byte-equal to the shared file at
     that path: a file the target does not change stays shared.
  2. Every overlay source (.c, .s, .S, .dsm) is a row of its own target's
     link order.
  3. Every shared source (.c, .s, .S, .dsm) is a row of the link order of at
     least one configured target that compiles it, that is, one whose
     overlay does not replace it.
  4. targets/<slug> exists only for a configured slug.
  5. Every source row of every configured link order resolves to a file.

The files are the ones git tracks. With no targets/ directory rules 1, 2 and
4 hold trivially and 3 reads as "every tracked source is in a link order".

    python3 tools/check_layers.py      exit 0 when every rule holds

tools/gen_ninja.py runs the same check before it writes build.ninja, and
the pre-commit hook runs this script. Plain python3, no venv.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from ico_version import configured_versions, config_path, overlay_dir  # noqa: E402

SOURCES = (".c", ".s", ".S", ".dsm")


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


def tracked(root: Path, *paths: str) -> list[str]:
    return subprocess.run(["git", "ls-files", "--", *paths], cwd=root,
                          capture_output=True, text=True, check=True).stdout.splitlines()


def problems(root: Path = ROOT) -> list[str]:
    slugs = configured_versions(root)
    rows = {s: link_rows(root, s) for s in slugs}
    listed = {s: {name for _, name in r} for s, r in rows.items()}
    bad = []
    targets = root / "targets"
    present = sorted(p.name for p in targets.iterdir() if p.is_dir()) if targets.is_dir() else []
    # 4
    for s in present:
        if s not in slugs:
            bad.append(f"targets/{s}/: no config/link_order.{s}.txt, so {s} is not a configured target")
    overlay = {s: set() for s in slugs}
    for p in tracked(root, "targets"):
        parts = p.split("/", 2)
        if len(parts) < 3:
            bad.append(f"{p}: outside any targets/<slug>/ directory")
            continue
        s, rel = parts[1], parts[2]
        # 1
        if not rel.startswith(("ico2/", "sce/")):
            bad.append(f"{p}: an overlay file sits at a shared-tree path (ico2/... or sce/...)")
            continue
        shared = root / rel
        if shared.is_file() and (root / p).is_file() and shared.read_bytes() == (root / p).read_bytes():
            bad.append(f"{p}: byte-equal to {rel}; a file the target does not change stays shared")
        if s in overlay:
            overlay[s].add(rel)
        # 2
        if rel.endswith(SOURCES) and s in listed and rel not in listed[s]:
            bad.append(f"{p}: not a row of config/link_order.{s}.txt")
    # 3
    for p in tracked(root, "ico2", "sce"):
        if not p.endswith(SOURCES):
            continue
        if not any(p in listed[s] and p not in overlay[s] for s in slugs):
            bad.append(f"{p}: in no configured target's link order that compiles it"
                       f" (configured: {', '.join(slugs) or 'none'})")
    # 5
    for s in slugs:
        for n, name in rows[s]:
            if not ((overlay_dir(root, s) / name).is_file() or (root / name).is_file()):
                bad.append(f"config/link_order.{s}.txt:{n}: {name} resolves to no file"
                           f" (neither targets/{s}/{name} nor {name})")
    return bad


def main() -> int:
    bad = problems(ROOT)
    for b in bad:
        print(f"check_layers: {b}", file=sys.stderr)
    slugs = configured_versions(ROOT)
    print(f"check_layers: {'FAIL' if bad else 'OK'} (targets {', '.join(slugs) or 'none'};"
          f" {len(bad)} problems)", file=sys.stderr)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
