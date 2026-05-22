#!/usr/bin/env bash
# =============================================================================
# tools/extract_assets.sh
#
# Dump the ISO-level files from the user's ICO disc image to assets/disc/
# (gitignored), recording each file's SHA-1 in config/sha1sums.txt.
#
# Wrapper that delegates to tools/extract_assets.py — pure-Python
# implementation via pycdlib. Requires baserom/Ico_USA.iso, which is
# produced by tools/extract_elf.sh on first run.
#
# Reads no copyrighted material into the repository — assets/ is gitignored.
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

VENV_PY="$ROOT/.venv/bin/python"
if [[ ! -x "$VENV_PY" ]]; then
    echo "extract_assets: $VENV_PY not found — run tools/setup.sh first" >&2
    exit 1
fi

exec "$VENV_PY" "$ROOT/tools/extract_assets.py" "$@"
