#!/usr/bin/env bash
# =============================================================================
# build_pages_site.sh — assemble the three-version progress dashboard into _site/
#
# Run by .github/workflows/pages.yml on `main`, `ntsc` and `aug6`. This file is
# byte-identical on all three branches on purpose: it works out what to do from
# the branch it is running on, so there are no per-branch conditionals to keep
# in sync and any drift between the copies is a bug (and is warned about below).
#
# Why it has to publish every version: a GitHub Pages deploy replaces the ENTIRE
# site. If each branch only published its own JSON, whichever branch deployed
# last would 404 the other versions' data until those branches happened to push
# again. Every branch therefore assembles the same complete site, which makes
# last-push-wins harmless.
#
# Branch -> version:
#   main -> pal    PAL retail  (SCES-50760)
#   ntsc -> us     USA retail  (SLUS-20218)
#   aug6 -> aug6   Aug-6-2001 prototype
#
# Layout produced:
#   _site/index.html        version-toggle dashboard (the running branch's copy;
#                           the branches keep this file identical)
#   _site/pal/              `main`'s docs/  — PAL retail target
#   _site/us/               `ntsc`'s docs/  — USA retail target
#   _site/aug6/             `aug6`'s docs/  — Aug-6-2001 prototype target
#   _site/progress.json     COMPAT COPY — holds the *aug6* data. A browser
#                           holding a cached pre-toggle index.html fetches bare
#                           `progress.json`; back when those pages were served,
#                           the branch publishing them carried the prototype, so
#                           aug6 stays what that stale cache keeps showing. This
#                           is frozen for cache compatibility and deliberately
#                           did NOT follow the aug6/main branch rename, nor the
#                           2026-09-04 retarget of `main` to PAL.
#   _site/PROGRESS.md        the aug6 copy too, so the URLs the old
#   (+ any other docs/*.md)   `path: docs` upload already serves keep working.
#
# Usage: build_pages_site.sh [branch]   (defaults to the current branch)
# =============================================================================
set -euo pipefail

BRANCH="${1:-$(git rev-parse --abbrev-ref HEAD)}"

# The complete branch<->version table. Every publishing branch is listed here,
# so adding a target means editing this one line (plus docs/index.html's own
# picker) rather than hunting per-branch conditionals.
VERSION_OF_main=pal
VERSION_OF_ntsc=us
VERSION_OF_aug6=aug6
BRANCHES="main ntsc aug6"

version_of() { eval "printf '%s\n' \"\${VERSION_OF_$1-}\""; }

SELF="$(version_of "$BRANCH")"
if [ -z "$SELF" ]; then
    echo "build_pages_site: no version mapping for branch '$BRANCH'" >&2
    echo "  expected 'main' (-> pal), 'ntsc' (-> us) or 'aug6' (-> aug6)." >&2
    exit 1
fi

# Every branch OTHER than the running one — fetched below.
OTHER_BRANCHES=""
for b in $BRANCHES; do
    [ "$b" = "$BRANCH" ] || OTHER_BRANCHES="$OTHER_BRANCHES $b"
done

# The root compat copies always come from aug6, whichever branch is running,
# so the assembled site is the same either way.
ROOT_VERSION=aug6

echo "build_pages_site: branch=$BRANCH self=$SELF others=${OTHER_BRANCHES# }"

rm -rf _site
mkdir -p "_site/$SELF"

# --- this branch's own version -------------------------------------------
# Deliberately the checked-out working tree rather than a remote ref: a run
# triggered by a push must publish the numbers that push just landed, without
# waiting for anything else to observe the new ref.
cp -R docs/. "_site/$SELF/"

# --- the other branches' versions ----------------------------------------
# actions/checkout only configures a remote-tracking refspec for the branch it
# checked out, so a bare `git fetch origin <other>` updates FETCH_HEAD but
# leaves refs/remotes/origin/<other> unresolvable. Fetch an explicit refspec.
FETCHED_BRANCHES=""
for ob in $OTHER_BRANCHES; do
    ov="$(version_of "$ob")"
    mkdir -p "_site/$ov"
    oref="refs/remotes/origin/$ob"
    if git fetch --no-tags --depth=1 origin "+refs/heads/$ob:$oref" &&
       git archive "$oref:docs" | tar -x -C "_site/$ov"; then
        FETCHED_BRANCHES="$FETCHED_BRANCHES $ob"
    else
        # Explicit, loud fallback: drop the empty version directory so the
        # page's own per-version fetch misses and visibly falls back to the
        # root copy (it labels which version it actually rendered) instead of
        # silently showing one version's numbers under another version's tab.
        rm -rf "_site/$ov"
        echo "::warning title=Pages::could not read '$ob:docs' — the '$ov' tab" \
             "will fall back to the root copy and say so."
    fi
done

# --- root compat copies ---------------------------------------------------
ROOT_SRC="$ROOT_VERSION"
if [ ! -d "_site/$ROOT_SRC" ]; then
    ROOT_SRC="$SELF"
    echo "::warning title=Pages::root compat progress.json holds '$SELF' data" \
         "this run, not the usual '$ROOT_VERSION'."
fi
cp -R "_site/$ROOT_SRC/." _site/
# ...but the landing page is always this branch's own copy of the dashboard.
cp docs/index.html _site/index.html

# --- drift guard ----------------------------------------------------------
# The three files below must be identical on every publishing branch, or the
# branches stop producing the same site and last-push-wins starts to matter
# again. Warn rather than fail so a half-landed change still deploys. Only
# branches whose refs were actually fetched can be compared.
for ob in $FETCHED_BRANCHES; do
    for f in docs/index.html \
             .github/workflows/pages.yml \
             .github/scripts/build_pages_site.sh; do
        if ! git show "refs/remotes/origin/$ob:$f" 2>/dev/null | cmp -s - "$f"; then
            echo "::warning title=Pages drift::$f differs between '$BRANCH'" \
                 "and '$ob'; every publishing branch must publish the same site."
        fi
    done
done

echo "build_pages_site: assembled site:"
find _site -type f | LC_ALL=C sort | while read -r f; do
    printf '  %s (%s bytes)\n' "$f" "$(wc -c < "$f")"
done
