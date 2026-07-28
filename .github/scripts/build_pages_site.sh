#!/usr/bin/env bash
# =============================================================================
# build_pages_site.sh — assemble the two-version progress dashboard into _site/
#
# Run by .github/workflows/pages.yml on BOTH `main` and `retail-v2`. This file
# is byte-identical on both branches on purpose: it works out what to do from
# the branch it is running on, so there are no per-branch conditionals to keep
# in sync and any drift between the two copies is a bug (and is warned about
# below).
#
# Why it has to publish both versions: a GitHub Pages deploy replaces the
# ENTIRE site. If each branch only published its own JSON, whichever branch
# deployed last would 404 the other version's data until that branch happened
# to push again. Both branches therefore assemble the same complete site, which
# makes last-push-wins harmless.
#
# Layout produced:
#   _site/index.html        version-toggle dashboard (the running branch's copy;
#                           the two branches keep this file identical)
#   _site/aug6/             `main`'s      docs/  — Aug-6-2001 prototype target
#   _site/us/               `retail-v2`'s docs/  — USA retail target
#   _site/progress.json     COMPAT COPY — holds the *aug6* data. A browser
#                           holding a cached pre-toggle index.html fetches bare
#                           `progress.json`; that cached page came from main,
#                           so aug6 is what it should keep showing.
#   _site/PROGRESS.md, dup_funcs.md, tu_candidates.md, tu_coalesce.md
#                           the aug6 copies too, so the URLs main's old
#                           `path: docs` upload already serves keep working.
#
# Usage: build_pages_site.sh [branch]   (defaults to the current branch)
# =============================================================================
set -euo pipefail

BRANCH="${1:-$(git rev-parse --abbrev-ref HEAD)}"

case "$BRANCH" in
    main)      SELF=aug6 ; OTHER=us   ; OTHER_BRANCH=retail-v2 ;;
    retail-v2) SELF=us   ; OTHER=aug6 ; OTHER_BRANCH=main      ;;
    *)
        echo "build_pages_site: no version mapping for branch '$BRANCH'" >&2
        echo "  expected 'main' (-> aug6) or 'retail-v2' (-> us)." >&2
        exit 1
        ;;
esac

# The root compat copies always come from aug6, whichever branch is running,
# so the assembled site is the same either way.
ROOT_VERSION=aug6

echo "build_pages_site: branch=$BRANCH self=$SELF other=$OTHER ($OTHER_BRANCH)"

rm -rf _site
mkdir -p "_site/$SELF" "_site/$OTHER"

# --- this branch's own version -------------------------------------------
# Deliberately the checked-out working tree rather than a remote ref: a run
# triggered by a push must publish the numbers that push just landed, without
# waiting for anything else to observe the new ref.
cp -R docs/. "_site/$SELF/"

# --- the other branch's version ------------------------------------------
# actions/checkout only configures a remote-tracking refspec for the branch it
# checked out, so a bare `git fetch origin <other>` updates FETCH_HEAD but
# leaves refs/remotes/origin/<other> unresolvable. Fetch an explicit refspec.
OTHER_REF="refs/remotes/origin/$OTHER_BRANCH"
other_ok=0
if git fetch --no-tags --depth=1 origin \
        "+refs/heads/$OTHER_BRANCH:$OTHER_REF" &&
   git archive "$OTHER_REF:docs" | tar -x -C "_site/$OTHER"; then
    other_ok=1
else
    # Explicit, loud fallback: drop the empty version directory so the page's
    # own per-version fetch misses and visibly falls back to the root copy
    # (it labels which version it actually rendered) instead of silently
    # showing one version's numbers under the other version's tab.
    rm -rf "_site/$OTHER"
    echo "::warning title=Pages::could not read '$OTHER_BRANCH:docs' —" \
         "publishing '$SELF' only; the '$OTHER' tab will fall back to the" \
         "root copy and say so."
fi

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
# The three files below must be identical on both branches, or the two
# branches stop producing the same site and last-push-wins starts to matter
# again. Warn rather than fail so a half-landed change still deploys.
if [ "$other_ok" -eq 1 ]; then
    for f in docs/index.html \
             .github/workflows/pages.yml \
             .github/scripts/build_pages_site.sh; do
        if ! git show "$OTHER_REF:$f" 2>/dev/null | cmp -s - "$f"; then
            echo "::warning title=Pages drift::$f differs between '$BRANCH'" \
                 "and '$OTHER_BRANCH'; both branches must publish the same site."
        fi
    done
fi

echo "build_pages_site: assembled site:"
find _site -type f | LC_ALL=C sort | while read -r f; do
    printf '  %s (%s bytes)\n' "$f" "$(wc -c < "$f")"
done
