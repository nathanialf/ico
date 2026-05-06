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
        echo "Permuter scores (tough_nuts):"
        {
            printf "func\tbest_score\tcand_count\n"
            while IFS= read -r func; do
                [[ -z "$func" ]] && continue
                runs_dir="lib/decomp-permuter/runs/$func"
                if [[ -d "$runs_dir" ]]; then
                    best=$(find "$runs_dir" -maxdepth 1 -type d -name 'output-*' \
                                -printf '%f\n' 2>/dev/null \
                            | sed -nE 's/^output-(-?[0-9]+).*$/\1/p' \
                            | sort -n | head -1)
                    count=$(find "$runs_dir" -maxdepth 1 -type d -name 'output-*' \
                                2>/dev/null | wc -l)
                    [[ -z "$best" ]] && best="-"
                    printf "%s\t%s\t%s\n" "$func" "$best" "$count"
                else
                    printf "%s\t-\t0\n" "$func"
                fi
            done < <(find tough_nuts -mindepth 1 -maxdepth 1 -type d \
                          -name 'func_*' -printf '%f\n' 2>/dev/null | sort)
        } | column -t -s "$(printf '\t')"
        echo "$rule"
    fi

    git status
    echo "$rule"
    git log -1
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
