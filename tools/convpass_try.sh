#!/usr/bin/env bash
# convpass wave-2 helper (worker 3)
#   convpass_try.sh <tu.c> <func>
# Mechanical port attempt.  Clean -> "PORTED".  Codegen diff -> splices the
# aug6 body into the TU anyway (from the debug dump) and leaves it there for
# hand convergence; prints the port driver's first-diff reason.
set -uo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
TU="$1"; FUNC="$2"
DUMP="${CONVPASS_DUMP:-/tmp/convpass_dump_w3}"
mkdir -p "$DUMP"; rm -f "$DUMP/$FUNC.c"
before=$(md5sum "$TU" | cut -d' ' -f1)
out=$(PORT_DEBUG_DUMP="$DUMP" .venv/bin/python tools/port_from_aug6.py port "$TU" --only "$FUNC" --waves 0,1,2,3 --apply 2>&1)
echo "$out" | tail -3
after=$(md5sum "$TU" | cut -d' ' -f1)
if [ "$before" != "$after" ]; then echo "PORTED $FUNC"; exit 0; fi
grep -F "\`$FUNC\`" decomp/port_ledger.md | tail -1
if [ -f "$DUMP/$FUNC.c" ]; then
  cp "$DUMP/$FUNC.c" "$TU"
  echo "SPLICED $FUNC into $TU (hand-converge)"
else
  echo "NO-DUMP $FUNC (not a codegen revert)"
fi
