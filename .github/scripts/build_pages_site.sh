#!/usr/bin/env bash
# =============================================================================
# build_pages_site.sh: assemble the four-version progress dashboard into _site/
#
# Run by .github/workflows/pages.yml on `main`, `ntsc` and `aug6`. It works out
# what to do from the branch it is running on, so there are no per-branch
# conditionals to keep in sync.
#
# Why it has to publish every version: a GitHub Pages deploy replaces the ENTIRE
# site. If each branch only published its own JSON, whichever branch deployed
# last would 404 the other versions' data until those branches happened to push
# again. Every branch therefore assembles the same complete site, which makes
# last-push-wins harmless.
#
# Where each file comes from:
#   - The dashboard page (docs/index.html, which carries its own styles and
#     scripts) comes from `main` only. On `main` it is the checked-out file;
#     on any other branch it is read from origin/main. A page change lands on
#     `main` and the next deploy from any branch publishes it; the other
#     branches' copies of docs/index.html (identical to main's once the
#     change is copied over, tools/check_shared_layer.sh) are never read.
#   - `main` carries several targets in one tree and contributes every
#     docs/<slug>/ it has (docs/pal/, and docs/jpn/ once the Japanese target
#     joins). Each other branch carries one target and contributes its
#     docs/<slug>/; a branch that still keeps its files at docs/ is read
#     there. Only the files in DATA_FILES are served.
#
# Branch -> version(s):
#   main -> every docs/<slug>/ it has (pal PAL retail SCES-50760, jpn
#           Japanese retail SCPS-11003)
#   ntsc -> us     USA retail       (SLUS-20218)
#   aug6 -> aug6   Aug-6-2001 prototype
#
# Layout produced:
#   _site/index.html        version-toggle dashboard, `main`'s copy
#   _site/pal/              `main`'s docs/pal/progress.json and PROGRESS.md
#   _site/jpn/              `main`'s docs/jpn/ (when main has it)
#   _site/us/               `ntsc`'s progress.json and PROGRESS.md
#   _site/aug6/             `aug6`'s progress.json and PROGRESS.md
#
# Only the files named in DATA_FILES are published from each branch, not all
# of docs/. docs/ also holds the project's documentation (docs/README.md
# indexes it), which the dashboard does not serve; a Pages deploy is public,
# so the served set is named rather than taken as a directory. Add a file
# there to serve it.
#   _site/progress.json     COMPAT COPY: holds the *aug6* data. A browser
#                           holding a cached pre-toggle index.html fetches bare
#                           `progress.json`; back when those pages were served,
#                           the branch publishing them carried the prototype, so
#                           aug6 stays what that stale cache keeps showing. This
#                           is frozen for cache compatibility and deliberately
#                           did NOT follow the aug6/main branch rename, nor the
#                           2026-09-04 retarget of `main` to PAL.
#   _site/PROGRESS.md       the aug6 copy too, so the URLs the old `path: docs`
#                           upload already serves keep working.
#
# Usage: build_pages_site.sh [branch]   (defaults to the current branch)
# =============================================================================
set -euo pipefail

BRANCH="${1:-$(git rev-parse --abbrev-ref HEAD)}"

# The complete branch<->version table. Every publishing branch is listed here,
# so adding a target branch means editing this one table (plus docs/index.html's
# own picker) rather than hunting per-branch conditionals. `main` has no fixed
# version: it publishes every docs/<slug>/ it carries (MAIN_BRANCH below).
VERSION_OF_ntsc=us
VERSION_OF_aug6=aug6
BRANCHES="main ntsc aug6"
MAIN_BRANCH=main

# The branch whose docs/index.html is the dashboard page.
PAGE_BRANCH=main

# Each target's served data. Everything else in docs/ stays unpublished.
DATA_FILES="progress.json PROGRESS.md"

version_of() { eval "printf '%s\n' \"\${VERSION_OF_$1-}\""; }

case " $BRANCHES " in
    *" $BRANCH "*) ;;
    *)
        echo "build_pages_site: no version mapping for branch '$BRANCH'" >&2
        echo "  expected one of: $BRANCHES ('main' -> every docs/<slug>/, 'ntsc' -> us, 'aug6' -> aug6)." >&2
        exit 1
        ;;
esac

# Every branch OTHER than the running one, fetched below.
OTHER_BRANCHES=""
for b in $BRANCHES; do
    [ "$b" = "$BRANCH" ] || OTHER_BRANCHES="$OTHER_BRANCHES $b"
done

# The root compat copies always come from aug6, whichever branch is running,
# so the assembled site is the same either way.
ROOT_VERSION=aug6

echo "build_pages_site: branch=$BRANCH others=${OTHER_BRANCHES# }"

rm -rf _site
mkdir -p _site

# copy_tree <slug> <git-ref or ""> <dir>: DATA_FILES of <dir> (in the working
# tree when ref is "", else in ref's tree) to _site/<slug>/.
copy_tree() {
    local slug="$1" ref="$2" dir="$3" f
    mkdir -p "_site/$slug"
    for f in $DATA_FILES; do
        if [ -z "$ref" ]; then
            [ -f "$dir/$f" ] && cp "$dir/$f" "_site/$slug/$f"
        else
            git show "$ref:$dir/$f" > "_site/$slug/$f" 2>/dev/null ||
                rm -f "_site/$slug/$f"
        fi
    done
    if [ ! -f "_site/$slug/progress.json" ]; then
        # Explicit, loud fallback: drop the version directory so the page's own
        # per-version fetch misses and visibly falls back to the root copy (it
        # labels which version it actually rendered) instead of silently
        # showing one version's numbers under another version's tab.
        rm -rf "_site/$slug"
        echo "::warning title=Pages::could not read '${ref:-working tree}:$dir/progress.json';" \
             "the '$slug' tab will fall back to the root copy and say so."
    fi
}

# --- this branch's own data ------------------------------------------------
# Deliberately the checked-out working tree rather than a remote ref: a run
# triggered by a push must publish the numbers that push just landed, without
# waiting for anything else to observe the new ref.
if [ "$BRANCH" = "$MAIN_BRANCH" ]; then
    for d in docs/*/; do
        d="${d%/}"
        [ -f "$d/progress.json" ] && copy_tree "${d#docs/}" "" "$d"
    done
else
    SELF="$(version_of "$BRANCH")"
    if [ -f "docs/$SELF/progress.json" ]; then
        copy_tree "$SELF" "" "docs/$SELF"
    else
        copy_tree "$SELF" "" docs
    fi
fi

# --- the other branches' data -----------------------------------------------
# actions/checkout only configures a remote-tracking refspec for the branch it
# checked out, so a bare `git fetch origin <other>` updates FETCH_HEAD but
# leaves refs/remotes/origin/<other> unresolvable. Fetch an explicit refspec.
# The runner's checkout is shallow and one commit of each branch is enough;
# a full local clone is fetched into without --depth, which would make it
# shallow.
DEPTH=""
[ "$(git rev-parse --is-shallow-repository)" = true ] && DEPTH="--depth=1"
FETCHED_BRANCHES=""
for ob in $OTHER_BRANCHES; do
    oref="refs/remotes/origin/$ob"
    # shellcheck disable=SC2086
    if ! git fetch --no-tags $DEPTH origin "+refs/heads/$ob:$oref"; then
        echo "::warning title=Pages::could not fetch '$ob'; its versions are not published this run."
        continue
    fi
    FETCHED_BRANCHES="$FETCHED_BRANCHES $ob"
    if [ "$ob" = "$MAIN_BRANCH" ]; then
        # every docs/<slug>/ main carries
        for slug in $(git ls-tree -d --name-only "$oref:docs" 2>/dev/null); do
            git cat-file -e "$oref:docs/$slug/progress.json" 2>/dev/null &&
                copy_tree "$slug" "$oref" "docs/$slug"
        done
    else
        ov="$(version_of "$ob")"
        if git cat-file -e "$oref:docs/$ov/progress.json" 2>/dev/null; then
            copy_tree "$ov" "$oref" "docs/$ov"
        else
            copy_tree "$ov" "$oref" docs
        fi
    fi
done

# --- root compat copies -----------------------------------------------------
ROOT_SRC="$ROOT_VERSION"
if [ ! -d "_site/$ROOT_SRC" ]; then
    ROOT_SRC="$(find _site -mindepth 2 -maxdepth 2 -name progress.json | LC_ALL=C sort | head -n 1 | cut -d/ -f2)"
    echo "::warning title=Pages::root compat progress.json holds '${ROOT_SRC:-no}' data" \
         "this run, not the usual '$ROOT_VERSION'."
fi
if [ -n "$ROOT_SRC" ]; then
    cp -R "_site/$ROOT_SRC/." _site/
fi

# --- the dashboard page, from main --------------------------------------------
if [ "$BRANCH" = "$PAGE_BRANCH" ]; then
    cp docs/index.html _site/index.html
elif ! git show "refs/remotes/origin/$PAGE_BRANCH:docs/index.html" \
        > _site/index.html 2>/dev/null; then
    # main was unreadable: publish this branch's own copy rather than no page,
    # and say so.
    cp docs/index.html _site/index.html
    echo "::warning title=Pages::could not read '$PAGE_BRANCH:docs/index.html';" \
         "published '$BRANCH''s own copy of the dashboard page this run."
fi

# --- drift guard ------------------------------------------------------------
# The workflow and this script must be identical on every publishing branch,
# or the branches stop producing the same site and last-push-wins starts to
# matter again. docs/index.html is not compared: only main's copy is served.
# Warn rather than fail so a half-landed change still deploys. Only branches
# whose refs were actually fetched can be compared.
for ob in $FETCHED_BRANCHES; do
    for f in .github/workflows/pages.yml \
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
