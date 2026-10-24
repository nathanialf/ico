#!/usr/bin/env bash
# =============================================================================
# tools/check_shared_layer.sh
#
# The shared layer (tools/ except tools/dev_native_allow.txt, build.sh,
# .github/ and docs/index.html) is the same file for file on every branch
# that builds a target (main, which carries every one but cn; the frozen pal,
# jpn, kor, ntsc, aug6 and jun26 branches take only hotfixes and these
# copies; cn, the Asian retail campaign branch, until it joins main): the
# target is chosen only by tools/ico_version.py's slug detection, never by
# a branch's own copy of a tool. A change to the shared layer lands on main
# first and is then copied to the other branches as it is.
# tools/dev_native_allow.txt is left out: it
# holds the allowed sites in the branch's own sources, so each branch keeps
# its own.
#
# On main this passes. On any other branch it runs `git fetch origin main`
# and requires `git diff --stat origin/main -- tools
# ':(exclude)tools/dev_native_allow.txt' build.sh .github docs/index.html` to
# be empty; otherwise it names the files that differ and exits 1. A failed
# fetch also exits non-zero.
#
#   tools/check_shared_layer.sh                  the checked-out branch and
#                                                the working tree
#   tools/check_shared_layer.sh BRANCH [COMMIT]  BRANCH's name and COMMIT's
#                                                tree (the pre-push hook
#                                                passes each pushed ref)
#
# A detached HEAD counts as main when it is at main's tip (local or
# origin/main).
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

SHARED=(tools ':(exclude)tools/dev_native_allow.txt' build.sh .github docs/index.html)

branch="${1:-$(git symbolic-ref --short -q HEAD || true)}"
commit="${2:-}"

if [[ -z "$branch" ]]; then
    head="$(git rev-parse HEAD)"
    for ref in refs/heads/main refs/remotes/origin/main; do
        if [[ "$(git rev-parse -q --verify "$ref^{commit}" || true)" == "$head" ]]; then
            branch=main
            break
        fi
    done
fi

if [[ "$branch" == "main" ]]; then
    echo "check_shared_layer: OK (on main, the shared layer's home)"
    exit 0
fi

if ! git fetch --quiet origin main; then
    echo "check_shared_layer: git fetch origin main failed; cannot compare" >&2
    echo "  ${branch:-HEAD}'s shared layer with main's." >&2
    exit 2
fi

# shellcheck disable=SC2086
stat="$(git diff --stat origin/main $commit -- "${SHARED[@]}")"
if [[ -n "$stat" ]]; then
    echo "check_shared_layer: ${branch:-HEAD} differs from origin/main in the shared layer" >&2
    echo "  (tools/ except tools/dev_native_allow.txt, build.sh, .github/, docs/index.html):" >&2
    printf '%s\n' "$stat" | sed 's/^/  /' >&2
    echo "  Land the change on main first, then copy main's files here:" >&2
    echo "    git checkout origin/main -- ${SHARED[*]@Q}" >&2
    exit 1
fi

echo "check_shared_layer: OK (${branch:-HEAD} matches origin/main in tools/ except tools/dev_native_allow.txt, build.sh, .github/, docs/index.html)"
