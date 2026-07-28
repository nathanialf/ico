#!/usr/bin/env bash
# convpass wave-2 helper (worker 3)
#   convpass_tu.sh <tu.c> <stem> <func>...
# Splice every named func (mechanical port where it is clean, aug6 body
# otherwise) and print each one's real diff.  The whole-TU inner loop.
set -uo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
TU="$1"; STEM="$2"; shift 2
for F in "$@"; do ./tools/convpass_try.sh "$TU" "$F" >/dev/null 2>&1; done
for F in "$@"; do
  echo "== $F"
  ./tools/convpass_rd.sh "$STEM" "$F"
done
