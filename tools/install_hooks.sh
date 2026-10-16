#!/usr/bin/env bash
# Install the IP-safety scan and the byte gate as git hooks (opt-in):
#   - pre-commit: refuses a local commit that breaks the build
#   - pre-push:   refuses to push a ref whose tip does not rebuild every
#                 configured target's base,
#                 the backstop for commits made with --no-verify, or a branch
#                 other than main whose shared layer (tools/, build.sh,
#                 .github/, docs/index.html) differs from origin/main's
# Re-run any time either hook body changes.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
# In a linked worktree `$ROOT/.git` is a FILE pointing at the main repo, and
# the hooks live in the main repo's shared hook dir. Ask git for that dir so
# running this from a worktree refreshes the hooks every checkout uses.
GITDIR="$(cd "$ROOT" && git rev-parse --git-common-dir 2>/dev/null || true)"
case "$GITDIR" in "") GITDIR="$ROOT/.git" ;; /*) ;; *) GITDIR="$ROOT/$GITDIR" ;; esac
HOOK="$GITDIR/hooks/pre-commit"
PUSH_HOOK="$GITDIR/hooks/pre-push"

if [[ ! -d "$GITDIR" ]]; then
    echo "install_hooks: $ROOT is not a git repo (no git dir)" >&2
    exit 1
fi

cat > "$HOOK" <<'EOF'
#!/usr/bin/env bash
# Auto-installed by tools/install_hooks.sh. Runs, in order:
#   1. tools/check_no_rom.sh        IP-safety scan of the staged files
#   2. tools/check_dev_native.py    refuses codegen-steering constructs in staged C
#   3. tools/check_targets.py       the source tree (ico2/, sce/) against every
#                                   configured target's link order
#   4. tools/format.sh --check      staged C must be clang-formatted
#   5. tools/build.sh gate-all      for EVERY configured target (a
#                                   config/link_order.<slug>.txt exists): its base
#                                   files are required, then build.sh setup
#                                   (verify the base ELF and ROM SHA-1s, write
#                                   build.ninja) and ninja
#                                   (build every object from source, link, and run
#                                   tools/check_elf.py --gate --require-elf-sha:
#                                   the byte gate and the whole ELF's SHA-1)
#   6. tools/build.sh progress-all  refresh docs/<slug>/PROGRESS.md,
#                                   docs/<slug>/progress.json and README.md's
#                                   progress block for every target, then
#                                   `git add` them into this commit
#
# Steps 5 and 6 run only when a staged path can affect the build (ico2/, sce/,
# config/, tools/, baserom/). `build.sh setup` deletes build/<slug>/
# first, so each gate is a from-scratch build of the staged tree, and a
# missing baserom/<slug>/ of any configured target fails the commit.
#
# Bypass with --no-verify only for a commit that cannot touch the build and
# when the build is known green.
set -e
ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/tools/check_no_rom.sh"

# Staged C must be developer-native: no K&R definitions, no empty do-while
# loop notes, no empty asm, no symbol aliases, no register pins or asm blocks
# in functions the January listing proves were compiled C. tools/dev_native_allow.txt holds the
# ROM-proven exceptions with their reasons.
python3 "$ROOT/tools/check_dev_native.py"

# The source tree: every source is compiled by some configured target, every
# link-order row is a file, no per-target tree, and VERSION_ blocks name
# configured targets.
python3 "$ROOT/tools/check_targets.py"

# Staged C must be clang-formatted. Formatting can move bytes under -g, which
# the byte gate below catches. Fix with: tools/format.sh FILE
STAGED_C=$(git diff --cached --name-only --diff-filter=ACMR -z | tr '\0' '\n' |
    grep -E '^(ico2/[^/]+/[^/]+|sce(/[^/]+){0,3})/[^/]+\.c(\.inc)?$' || true)
if [[ -n "$STAGED_C" ]]; then
    # shellcheck disable=SC2086
    "$ROOT/tools/format.sh" --check $STAGED_C
fi

# Pure-docs commits (docs/, README.md, .gitignore, ...) skip the build gate.
BUILD_SENSITIVE=$(git diff --cached --name-only -z |
    tr '\0' '\n' |
    grep -E '^(ico2/|sce/|config/|tools/|baserom/)' ||
    true)
if [[ -z "$BUILD_SENSITIVE" ]]; then
    exit 0
fi

# Every configured target's gate. gate-all refuses before building anything
# when a configured target's baserom/<slug>/ files are missing; the build
# output goes to the terminal so the gate table of each target is seen.
echo "pre-commit: tools/build.sh gate-all ..."
if ! "$ROOT/tools/build.sh" gate-all; then
    echo "" >&2
    echo "pre-commit: GATE FAILED: a configured target's base files are missing," >&2
    echo "  or the staged tree does not rebuild a target's base ELF byte for byte." >&2
    echo "  Fix the build (or rebase) before committing; every configured target" >&2
    echo "  must pass. Bypass with \`git commit --no-verify\` only if you understand" >&2
    echo "  why and have a follow-up commit ready that fixes it." >&2
    exit 1
fi

# Every gate is green: refresh the progress tables and the dashboard's JSON of
# every target and stage them into THIS commit. They are derived files, so a
# failure here warns and never blocks the commit (the byte gates above already
# passed). For a path-scoped `git commit <file>` the re-staged files do not
# ride along.
echo "pre-commit: tools/build.sh progress-all (refresh + stage progress) ..."
if "$ROOT/tools/build.sh" progress-all >/dev/null 2>&1; then
    (cd "$ROOT" && git add README.md docs/*/PROGRESS.md docs/*/progress.json) 2>/dev/null || true
else
    echo "pre-commit: progress regen failed (non-fatal): commit proceeds" >&2
    echo "  without refreshed progress; run \`tools/build.sh progress-all\` manually." >&2
fi
EOF
chmod +x "$HOOK"
echo "Installed pre-commit hook at $HOOK"

# pre-push: re-run the byte gate against the tip of each ref being
# pushed. Catches commits that bypassed pre-commit via --no-verify.
# `git push --no-verify` skips it in turn.
cat > "$PUSH_HOOK" <<'EOF'
#!/usr/bin/env bash
# Auto-installed by tools/install_hooks.sh. Per-push shared-layer check and
# byte gate.
#
# For each branch being pushed other than main, tools/check_shared_layer.sh
# requires its tip's tools/, build.sh, .github/ and docs/index.html to equal
# origin/main's: every branch that builds a target carries the same shared layer, and a
# change to it lands on main first.
#
# For each ref being pushed whose commits touch the build, requires the
# working tree to be at that ref's tip with no uncommitted change to a
# build path, runs tools/build.sh gate-all (setup + ninja for every configured
# target, each ending in tools/check_elf.py --gate --require-elf-sha; a
# configured target without its baserom/<slug>/ files fails), and refuses the
# push if a rebuilt ELF differs from its base. This is the backstop against
# commits authored with `git commit --no-verify` that broke the
# byte-identical round-trip.
#
# Bypass with `git push --no-verify` ONLY when pushing a known-broken
# commit that has a follow-up fix queued.
set -e
ROOT="$(git rev-parse --show-toplevel)"

remote="$1"
url="$2"

# Read refs from stdin (git push protocol): "<local-ref> <local-sha> <remote-ref> <remote-sha>"
push_failed=0
while read local_ref local_sha remote_ref remote_sha; do
    # Skip ref deletion (local_sha is all zeros)
    if [[ "$local_sha" =~ ^0+$ ]]; then
        continue
    fi
    # The shared layer must equal main's on every other branch.
    case "$remote_ref" in
        refs/heads/*)
            if ! "$ROOT/tools/check_shared_layer.sh" "${remote_ref#refs/heads/}" "$local_sha"; then
                echo "pre-push: SHARED LAYER differs from origin/main on $remote_ref: refusing push." >&2
                push_failed=1
                continue
            fi
            ;;
    esac
    # Check if any commits being pushed touch build-sensitive paths
    if [[ "$remote_sha" =~ ^0+$ ]]; then
        # New branch: check all commits in local_sha
        range="$local_sha"
    else
        range="$remote_sha..$local_sha"
    fi
    BUILD_SENSITIVE=$(git diff --name-only "$range" 2>/dev/null |
        grep -E '^(ico2/|sce/|config/|tools/|baserom/)' ||
        true)
    if [[ -z "$BUILD_SENSITIVE" ]]; then
        continue
    fi

    echo "pre-push: build-sensitive changes in $local_ref: re-running the byte gate ..."
    # The gate builds the working tree, so it must be the tip being pushed:
    # HEAD at that commit and no uncommitted change under a build path.
    head_sha=$(git rev-parse HEAD)
    if [[ "$head_sha" != "$local_sha" ]]; then
        echo "pre-push: working tree HEAD ($head_sha) doesn't match pushed ref tip ($local_sha)." >&2
        echo "  Check out the pushed commit and re-run \`tools/build.sh setup && ninja\` manually first." >&2
        push_failed=1
        continue
    fi
    if ! git diff --quiet HEAD -- ico2 sce config tools; then
        echo "pre-push: uncommitted changes under ico2/, sce/, config/ or tools/;" >&2
        echo "  the gate would build them instead of $local_sha. Commit or set them aside first." >&2
        push_failed=1
        continue
    fi
    if ! "$ROOT/tools/build.sh" gate-all >/dev/null 2>&1; then
        echo "pre-push: GATE FAILED on $local_ref: refusing push." >&2
        echo "  A configured target's base files are missing, or a rebuilt ELF" >&2
        echo "  differs from its base (run \`tools/build.sh gate-all\` to see which)." >&2
        echo "  A commit being pushed was likely authored with \`git commit --no-verify\`." >&2
        echo "  Fix the build (or rebase to drop the bad commit) before pushing." >&2
        push_failed=1
        continue
    fi
    echo "pre-push: byte gate OK on $local_ref"
done

exit $push_failed
EOF
chmod +x "$PUSH_HOOK"
echo "Installed pre-push hook at $PUSH_HOOK"
