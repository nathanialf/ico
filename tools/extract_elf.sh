#!/usr/bin/env bash
# =============================================================================
# tools/extract_elf.sh
#
# Extracts the EE-side boot ELF (SLUS_202.18) from the user's ICO disc image
# at baserom/Ico_USA.bin / .cue, writes it to baserom/baseelf.elf, and
# records its SHA-1 to config/sha1sums.txt (creating the entry on first run,
# verifying against existing entry on subsequent runs).
#
# Wrapper that delegates to tools/extract_elf.py — pure-Python implementation
# that handles MODE1/2352 and MODE2/2352 .bin/.cue images without external
# CD tools (bchunk / isoinfo / 7z), via pycdlib.
#
# Reads no copyrighted material into the repository — the ELF lives under
# baserom/, which is gitignored.
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

VENV_PY="$ROOT/.venv/bin/python"
if [[ ! -x "$VENV_PY" ]]; then
    echo "extract_elf: $VENV_PY not found — run tools/setup.sh first" >&2
    exit 1
fi

exec "$VENV_PY" "$ROOT/tools/extract_elf.py" "$@"
