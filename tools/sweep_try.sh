#!/usr/bin/env bash
# tools/sweep_try.sh <tu_stem> <func> <c_snippet_file>
# Single-pass attempt: splice candidate, count reloc-normalized diffs.
#   count==0  -> leave applied (sentinels in place), print "CANDIDATE"
#   count!=0  -> surgical revert, print "MISS <count>"
#   compile   -> surgical revert, print "COMPILE-FAIL"
set -uo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; cd "$ROOT"
TU="$1"; FUNC="$2"; CF="$3"

python3 tools/sweep.py apply "$TU" "$FUNC" "$CF" || { echo "APPLY-FAIL"; exit 1; }

OUT="$(VERSION=aug6 python3 tools/match_diff.py "$TU" "$FUNC" 2>/dev/null)"
STATUS="$(printf '%s' "$OUT" | python3 -c 'import sys,json;
try: d=json.load(sys.stdin); print(d.get("status"), d.get("real_count"))
except Exception: print("parse-fail -1")')"
st="${STATUS%% *}"; cnt="${STATUS##* }"

if [[ "$st" == "match" ]]; then
    echo "CANDIDATE"
elif [[ "$st" == "compile-fail" ]]; then
    python3 tools/sweep.py revert "$TU" "$FUNC"; echo "COMPILE-FAIL"
else
    python3 tools/sweep.py revert "$TU" "$FUNC"; echo "MISS $cnt"
fi
