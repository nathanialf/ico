#!/usr/bin/env bash
# tools/sweep_targets.sh [scope_dir]   (default: fumi)
#
# Regenerate the smallest-first UNMATCHED target list for the single-pass
# sweep. The source of truth is the .c files: a func is "unmatched" iff it
# still has an INCLUDE_ASM stub. So this is fully resumable across sessions —
# already-matched funcs simply drop out (no /tmp state to keep in sync).
#
# Output columns:  <s_bytes>  <tu_stem>  <func>  <SPILL|.>
#   SPILL = the .s spills param a0 to its stack home in the first 8 lines
#           (sw $4,0x0($29)) -> known one-pass MISS class; skip it.
# Sorted ascending by .s size (smallest/leaf-iest first).
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; cd "$ROOT"
SCOPE="${1:-fumi}"

find "$SCOPE" -name '*.c' -print | while read -r f; do
    tu="${f%.c}"
    grep -oP 'INCLUDE_ASM\("asm/aug6/nonmatchings/\K[^"]+", \K[A-Za-z0-9_]+' "$f" 2>/dev/null | \
    while read -r fn; do
        s="asm/aug6/nonmatchings/$tu/$fn.s"
        [ -f "$s" ] || continue
        # Parked funcs (deep-pass owned) live under tough_nuts/<func>/ — drop
        # them so neither the to-do list nor the stop-hook's remaining-count
        # traps the sweep on a func a human already declared a tough nut.
        [ -d "tough_nuts/$fn" ] && continue
        sz=$(stat -c%s "$s")
        if head -8 "$s" | grep -q 'sw .*\$4, 0x0(\$29)'; then sp="SPILL"; else sp="."; fi
        printf '%s %s %s %s\n' "$sz" "$tu" "$fn" "$sp"
    done
done | sort -n
