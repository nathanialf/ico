#!/usr/bin/env bash
# convpass wave-2 helper (worker 3)
#   convpass_batch.sh <tu.c> <func> [func...]
# Mechanical-port each named func in order (no splice-on-fail).  Prints
# PORTED / FAILED plus the ledger reason for each failure.
set -uo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
TU="$1"; shift
for F in "$@"; do
  before=$(md5sum "$TU" | cut -d' ' -f1)
  .venv/bin/python tools/port_from_aug6.py port "$TU" --only "$F" --waves 0,1,2,3 --apply >/dev/null 2>&1
  after=$(md5sum "$TU" | cut -d' ' -f1)
  if [ "$before" != "$after" ]; then
    echo "PORTED  $F"
  else
    echo "FAILED  $F :: $(grep -F "\`$F\`" decomp/port_ledger.md | tail -1 | sed 's/^- REVERTED //')"
  fi
done
