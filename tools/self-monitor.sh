#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, and the last commit. Refreshes every 10 seconds.

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
    git status
    echo "$rule"
    git log -1
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
