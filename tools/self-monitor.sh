#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, and the last commit. Refreshes every 10 seconds.

INTERVAL=10

dashboard() {
    local cols=${COLUMNS:-$(tput cols)}
    local rule
    rule=$(printf '%*s\n' "$cols" '' | tr ' ' -)

    echo "$rule"
    sed -n '8,13p' docs/PROGRESS.md
    echo "$rule"
    git status
    echo "$rule"
    git log -1
    echo "$rule"
}

export -f dashboard
watch -t -n "$INTERVAL" "bash -c dashboard"
