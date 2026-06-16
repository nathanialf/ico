#!/usr/bin/env bash
# tools/sweep_park.sh <tu_stem> <func> <rc> [note...]
#
# Record a sweep MISS you are moving on from, so the NEXT sweep does not
# re-tread it. Appends "<func>   # rc<rc> <note>" to config/sweep_parked.txt
# (idempotent: a func already present is left as-is). sweep_targets.sh then
# drops it from the default fresh-only list.
#
# Call this whenever you abandon a func after its one allowed refinement (or a
# >=10 first miss). It is the mechanical counterpart to the "move on" step.
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; cd "$ROOT"
PARKED_FILE="config/sweep_parked.txt"

if [ $# -lt 3 ]; then
    echo "usage: sweep_park.sh <tu_stem> <func> <rc> [note...]" >&2
    exit 2
fi
TU="$1"; FN="$2"; RC="$3"; shift 3; NOTE="$*"

# No rc ceiling on parking. A high real_count after an HONEST attempt is a fine
# reason to move on — the sweep is single-pass and hard funcs are left for the
# deep pass. What is NOT ok is parking a func you never genuinely tried, or
# batch-parking a family on one shared template without giving each member its
# own real hypothesis. Those are BEHAVIORAL rules enforced by actually running
# sweep_try on every row (see SKILL.md), not by a number gate here.
if grep -qE "^[[:space:]]*${FN}([[:space:]]|#|$)" "$PARKED_FILE" 2>/dev/null; then
    echo "already parked: $FN"
    exit 0
fi

printf '%-20s# rc%s %s\n' "$FN" "$RC" "$NOTE" >> "$PARKED_FILE"
echo "parked: $FN (rc$RC) [$TU]"
