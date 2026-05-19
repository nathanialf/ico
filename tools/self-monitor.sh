#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, last commit, and best permuter scores for parked funcs.
# Refreshes every 10 seconds.

INTERVAL=10

if [[ "$1" == "--once" ]]; then
    cols=${COLUMNS:-$(tput cols)}
    rule=$(printf '%*s\n' "$cols" '' | tr ' ' -)

    # Refresh docs/PROGRESS.md from current src/ + yaml + built objects.
    # Done here (not in per-match commits) so the matching loop doesn't
    # carry the ~1s progress-regen cost. Output suppressed; progress.py
    # is a no-op write when content hasn't changed.
    if [[ -x .venv/bin/python ]]; then
        .venv/bin/python tools/progress.py >/dev/null 2>&1 || true
    fi

    echo "$rule"
    # Render the markdown table as a fixed-width table. Pull the rows
    # between the `progress:begin` / `progress:end` markers so adding
    # a new section row in tools/progress.py doesn't drift this range.
    # Strip the leading/trailing pipes, drop the markdown separator
    # row (---|---|...), then column-align on `|`.
    sed -n '/<!-- progress:begin -->/,/<!-- progress:end -->/p' docs/PROGRESS.md \
        | sed -E '/<!-- progress:(begin|end) -->/d; s/^\| //; s/ \|$//; /^[- |:]+$/d' \
        | column -t -s '|'
    echo "$rule"

    # Lowest permuter score per parked function. Decomp-permuter writes
    # candidates to lib/decomp-permuter/runs/<func>/output-<score>-<n>/.
    # Lower score = better; 0 = matched. Source of truth for parked
    # functions is tough_nuts/<func>/ (one subdir per parked function).
    #
    # Temporarily hidden during the coalesce sprint — the dashboard
    # focuses on TU coalesce progress, not per-function matching, until
    # the structural pass is done. Flip this guard to re-enable.
    if false && [[ -d tough_nuts && -d lib/decomp-permuter/runs ]]; then
        # Skip-marked targets (tough_nuts/<func>/.skip) are excluded from
        # the auto-permuter rotation, so don't list them here either —
        # this dashboard exists to show what the permuter is working on.
        skipped=$(find tough_nuts -mindepth 2 -maxdepth 2 -name '.skip' -printf '%h\n' 2>/dev/null | wc -l)
        echo "Permuter scores (tough_nuts; ${skipped} .skip-marked hidden; sorted lowest-score first):"
        # Build "score|func:best" rows, sort by score ascending, then drop
        # the score prefix. Functions with no permuter output sort last
        # (assigned a sentinel beyond any real score). Lower score = better;
        # 0 = matched, so promotable hits surface at the top of the table.
        rows=()
        while IFS= read -r func; do
            [[ -z "$func" ]] && continue
            [[ -f "tough_nuts/$func/.skip" ]] && continue
            runs_dir="lib/decomp-permuter/runs/$func"
            best="-"
            sort_key=999999999
            if [[ -d "$runs_dir" ]]; then
                b=$(find "$runs_dir" -maxdepth 1 -type d -name 'output-*' \
                            -printf '%f\n' 2>/dev/null \
                        | sed -nE 's/^output-(-?[0-9]+).*$/\1/p' \
                        | sort -n | head -1)
                if [[ -n "$b" ]]; then
                    best="$b"
                    sort_key="$b"
                fi
            fi
            rows+=("$(printf '%012d|%s:%s' "$sort_key" "$func" "$best")")
        done < <(find tough_nuts -mindepth 1 -maxdepth 1 -type d \
                      -name 'func_*' -printf '%f\n' 2>/dev/null | sort)
        # Sort rows by their numeric prefix, then strip it.
        cells=()
        while IFS= read -r row; do
            cells+=("${row#*|}")
        done < <(printf '%s\n' "${rows[@]}" | sort -n)
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
