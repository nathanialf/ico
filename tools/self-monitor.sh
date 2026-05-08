#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, last commit, and best permuter scores for parked funcs.
# Refreshes every 10 seconds.

INTERVAL=10

if [[ "$1" == "--once" ]]; then
    cols=${COLUMNS:-$(tput cols)}
    rule=$(printf '%*s\n' "$cols" '' | tr ' ' -)

    echo "$rule"
    # Render the markdown table (header + 6 data rows) as a fixed-width
    # table: strip the leading/trailing pipes, drop the markdown
    # separator row (---|---|...), then column-align on `|`.
    sed -n '6,13p' docs/PROGRESS.md \
        | sed -E 's/^\| //; s/ \|$//; /^[- |:]+$/d' \
        | column -t -s '|'
    echo "$rule"

    # Lowest permuter score per parked function. Decomp-permuter writes
    # candidates to lib/decomp-permuter/runs/<func>/output-<score>-<n>/.
    # Lower score = better; 0 = matched. Source of truth for parked
    # functions is tough_nuts/<func>/ (one subdir per parked function).
    if [[ -d tough_nuts && -d lib/decomp-permuter/runs ]]; then
        # Skip-marked targets (tough_nuts/<func>/.skip) are excluded from
        # the auto-permuter rotation, so don't list them here either —
        # this dashboard exists to show what the permuter is working on.
        skipped=$(find tough_nuts -mindepth 2 -maxdepth 2 -name '.skip' -printf '%h\n' 2>/dev/null | wc -l)
        echo "Permuter scores (tough_nuts; ${skipped} .skip-marked hidden):"
        # Build "func:best" cells, then pack as many columns as fit the
        # terminal width.
        cells=()
        while IFS= read -r func; do
            [[ -z "$func" ]] && continue
            [[ -f "tough_nuts/$func/.skip" ]] && continue
            runs_dir="lib/decomp-permuter/runs/$func"
            best="-"
            if [[ -d "$runs_dir" ]]; then
                b=$(find "$runs_dir" -maxdepth 1 -type d -name 'output-*' \
                            -printf '%f\n' 2>/dev/null \
                        | sed -nE 's/^output-(-?[0-9]+).*$/\1/p' \
                        | sort -n | head -1)
                [[ -n "$b" ]] && best="$b"
            fi
            cells+=("${func}:${best}")
        done < <(find tough_nuts -mindepth 1 -maxdepth 1 -type d \
                      -name 'func_*' -printf '%f\n' 2>/dev/null | sort)
        if (( ${#cells[@]} > 0 )); then
            cellw=0
            for c in "${cells[@]}"; do (( ${#c} > cellw )) && cellw=${#c}; done
            cellw=$((cellw + 2))            # gutter
            ncols=$(( cols / cellw ))
            (( ncols < 1 )) && ncols=1
            i=0
            for c in "${cells[@]}"; do
                printf "%-${cellw}s" "$c"
                i=$((i + 1))
                (( i % ncols == 0 )) && echo
            done
            (( i % ncols != 0 )) && echo
        fi
        echo "$rule"
    fi

    git log -1
    echo "$rule"
    git status
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
