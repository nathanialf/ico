#!/usr/bin/env python3
"""
progress.py — regenerate README.md / docs/PROGRESS.md status tables.

Reads config/ico.us.yaml + the current src/ tree, computes matched-bytes
ratios per section, and rewrites the tables in README.md and
docs/PROGRESS.md.

Empty at init — the table-regeneration logic depends on the splat yaml
having declared file-boundary subsegments, which doesn't happen until
matching work begins. Stub here so the Makefile target is not a hanging
reference.
"""

from __future__ import annotations

import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
YAML = REPO_ROOT / "config" / "ico.us.yaml"


def main() -> int:
    if not YAML.exists():
        print(f"progress: {YAML} not found", file=sys.stderr)
        return 1
    print("progress: not yet implemented — splat yaml needs file-boundary "
          "subsegments before matched-byte ratios are meaningful")
    return 0


if __name__ == "__main__":
    sys.exit(main())
