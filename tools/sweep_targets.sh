#!/usr/bin/env bash
# tools/sweep_targets.sh [scope_dir] [--all|--counts] [--include-parked]
#
# Regenerate the smallest-first UNMATCHED target list for the single-pass
# sweep. The source of truth is the .c files: a func is "unmatched" iff it
# still has an INCLUDE_ASM stub. So this is fully resumable across sessions —
# already-matched funcs simply drop out (no /tmp state to keep in sync).
#
# Output columns:  <s_bytes>  <tu_stem>  <func>  <SPILL|PARKED|.>
#   SPILL  = the .s spills param a0 to its stack home in the first 8 lines
#            (sw $4,0x0($29)) -> known one-pass MISS class; skip it.
#   PARKED = this func was ALREADY attempted+parked in a prior sweep (its name
#            appears in docs/MATCHING_NOTES.md or config/sweep_parked.txt).
#            Re-attempting it re-treads recorded ground and burns a shot.
#
# By DEFAULT, PARKED rows are EXCLUDED (the list is fresh-only) so a sweep can
# never accidentally re-tread a documented near-miss. SPILL rows are still shown
# (flagged) for visibility; the loop skips them. tough_nuts/<func>/ are dropped.
#
# Modes:
#   (default)         smallest-first fresh-only list (SPILL flagged, PARKED gone)
#   --all             show every stub, flagged (PARKED included)
#   --include-parked  include PARKED rows in the default list (to re-attempt one)
#   --counts          one-line breakdown: total / SPILL / PARKED / fresh
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; cd "$ROOT"

SCOPE="fumi"; MODE=""; INCLUDE_PARKED=0
for a in "$@"; do
    case "$a" in
        --all)            MODE="all" ;;
        --counts)         MODE="counts" ;;
        --include-parked) INCLUDE_PARKED=1 ;;
        -*)               echo "unknown flag: $a" >&2; exit 2 ;;
        *)                SCOPE="$a" ;;
    esac
done

NOTES="docs/MATCHING_NOTES.md"
PARKED_FILE="config/sweep_parked.txt"

# Preload the set of already-parked func names. Two sources, unioned:
#   1. every func_XXXXXXXX token in docs/MATCHING_NOTES.md (auto — covers the
#      bulk; a name there that is already MATCHED is harmless, it won't be a stub)
#   2. config/sweep_parked.txt (curated — for named-symbol funcs like
#      gamesysObjInfoCls and any func not yet written into the prose notes)
declare -A PARKED
if [ -f "$NOTES" ]; then
    while read -r t; do PARKED["$t"]=1; done < <(grep -oE 'func_[0-9A-Fa-f]{8}' "$NOTES" | sort -u)
fi
if [ -f "$PARKED_FILE" ]; then
    while read -r t; do
        t="${t%%#*}"; t="${t//[[:space:]]/}"   # strip "# note" + whitespace
        [ -n "$t" ] && PARKED["$t"]=1
    done < "$PARKED_FILE"
fi

emit() {
    find "$SCOPE" -name '*.c' -print | while read -r f; do
        tu="${f%.c}"
        grep -oP 'INCLUDE_ASM\("asm/aug6/nonmatchings/\K[^"]+", \K[A-Za-z0-9_]+' "$f" 2>/dev/null | \
        while read -r fn; do
            s="asm/aug6/nonmatchings/$tu/$fn.s"
            [ -f "$s" ] || continue
            # Parked funcs (deep-pass owned) live under tough_nuts/<func>/ — drop.
            [ -d "tough_nuts/$fn" ] && continue
            sz=$(stat -c%s "$s")
            if [ -n "${PARKED[$fn]:-}" ]; then
                flag="PARKED"
            elif head -8 "$s" | grep -q 'sw .*\$4, 0x0(\$29)'; then
                flag="SPILL"
            else
                flag="."
            fi
            printf '%s %s %s %s\n' "$sz" "$tu" "$fn" "$flag"
        done
    done | sort -n
}

ALL="$(emit)"

case "$MODE" in
    counts)
        total=$(printf '%s\n' "$ALL" | grep -c .)
        spill=$(printf '%s\n' "$ALL" | grep -cw SPILL)
        parked=$(printf '%s\n' "$ALL" | grep -cw PARKED)
        fresh=$((total - spill - parked))
        printf '%-14s total=%-5s SPILL=%-4s PARKED=%-4s fresh=%-5s\n' \
            "$SCOPE" "$total" "$spill" "$parked" "$fresh"
        ;;
    all)
        printf '%s\n' "$ALL"
        ;;
    *)
        if [ "$INCLUDE_PARKED" -eq 1 ]; then
            printf '%s\n' "$ALL"
        else
            printf '%s\n' "$ALL" | grep -vw PARKED
        fi
        ;;
esac