#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, and the last commit. Refreshes every 10 seconds.

INTERVAL=10

if [[ "$1" == "--once" ]]; then
    cols=${COLUMNS:-$(tput cols)}
    rule=$(printf '%*s\n' "$cols" '' | tr ' ' -)

    echo "$rule"
    sed -n '8,13p' docs/PROGRESS.md
    echo "$rule"
    git status
    echo "$rule"
    git log -1
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
