#!/usr/bin/env bash
# Install the IP-safety scan + byte-identical-build gate as git hooks
# (opt-in). Installs:
#   - pre-commit  — catches local commits that break the build
#   - pre-push    — catches commits authored with --no-verify before
#                   they reach a shared ref. This is the real gate;
#                   30 commits got pushed in May 2026 that broke the
#                   global SHA because pre-commit was --no-verify'd
#                   and there was no pre-push backstop.
# Re-run any time either hook body changes.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
HOOK="$ROOT/.git/hooks/pre-commit"
PUSH_HOOK="$ROOT/.git/hooks/pre-push"

if [[ ! -d "$ROOT/.git" ]]; then
    echo "install_hooks: $ROOT is not a git repo (no .git dir)" >&2
    exit 1
fi

cat > "$HOOK" <<'EOF'
#!/usr/bin/env bash
# Auto-installed by tools/install_hooks.sh. Runs:
#   1. tools/check_no_rom.sh    — IP-safety scan on staged files
#   2. tools/build.sh setup     — splat + migrator + ninja regen
#   3. ninja                    — byte-identical-build gate (SHA-1 verify)
#
# The full-setup step matters: incremental ninja can be misleadingly
# green if the per-TU data sidecars on disk happen to match a prior
# state. Running setup forces the migrator/aligner/rewriter pipeline
# to regenerate from current asm + linker map, so a commit can only
# land if a clean-room rebuild also passes SHA-1.
#
# Bypass with --no-verify only when you're committing changes that
# don't touch the build graph (docs-only edits, etc.) and you're
# certain the build is still green.
#
# Notes:
# * Setup + ninja is invoked only when the staged changes can plausibly
#   affect the build (src/, asm/, config/, tools/, include/, baserom/).
#   Pure docs/notes commits skip it.
# * If `build.ninja` is absent (fresh checkout), the hook prints a hint
#   and skips the gate rather than spending minutes mid-commit.
set -e
ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/tools/check_no_rom.sh"

# Decide whether staged changes can affect the build. Pure-docs commits
# (only docs/, README.md, .gitignore, etc.) bypass the build gate.
BUILD_SENSITIVE=$(git diff --cached --name-only -z |
    tr '\0' '\n' |
    grep -E '^(src/|asm/|config/|tools/|include/|baserom/|Makefile|build\.ninja$)' ||
    true)
if [[ -z "$BUILD_SENSITIVE" ]]; then
    exit 0
fi

if [[ ! -f "$ROOT/build.ninja" ]]; then
    echo "pre-commit: build.ninja not found — run \`tools/build.sh setup\` once," >&2
    echo "  then this hook will be able to enforce the SHA-1 gate." >&2
    exit 0
fi

NINJA="$ROOT/.venv/bin/ninja"
if [[ ! -x "$NINJA" ]]; then
    NINJA="$(command -v ninja || true)"
fi
if [[ -z "$NINJA" ]]; then
    echo "pre-commit: ninja not on PATH and .venv/bin/ninja missing — skip" >&2
    exit 0
fi

echo "pre-commit: tools/build.sh setup (full regen) ..."
if ! "$ROOT/tools/build.sh" setup >/dev/null; then
    echo "" >&2
    echo "pre-commit: SETUP FAILED — splat/migrator pipeline errored." >&2
    echo "  Run \`tools/build.sh setup\` manually to see the error." >&2
    exit 1
fi

echo "pre-commit: ninja (SHA-1 gate) ..."
if ! "$NINJA" -C "$ROOT"; then
    echo "" >&2
    echo "pre-commit: BUILD FAILED — the staged changes break the byte-identical" >&2
    echo "  round-trip. Fix the build (or rebase) before committing." >&2
    echo "  Bypass with \`git commit --no-verify\` only if you understand why" >&2
    echo "  ninja is failing and have a follow-up commit ready that fixes it." >&2
    exit 1
fi
EOF
chmod +x "$HOOK"
echo "Installed pre-commit hook at $HOOK"

# pre-push: re-run the SHA gate against the tip of each ref being
# pushed. Catches commits that bypassed pre-commit via --no-verify.
# Cannot itself be bypassed (--no-verify only affects pre-commit and
# commit-msg; for push, use `git push --no-verify`, but reviewers can
# at least see push history in the reflog).
cat > "$PUSH_HOOK" <<'EOF'
#!/usr/bin/env bash
# Auto-installed by tools/install_hooks.sh. Per-push SHA gate.
#
# For each ref being pushed, checks out its tip in a worktree, runs
# tools/build.sh setup + ninja, and refuses the push if SHA-1 doesn't
# match. This is the backstop against commits authored with
# `git commit --no-verify` that broke the byte-identical round-trip.
#
# Bypass with `git push --no-verify` ONLY when pushing a known-broken
# commit that has a follow-up fix queued.
set -e
ROOT="$(git rev-parse --show-toplevel)"

remote="$1"
url="$2"

NINJA="$ROOT/.venv/bin/ninja"
if [[ ! -x "$NINJA" ]]; then
    NINJA="$(command -v ninja || true)"
fi
if [[ -z "$NINJA" ]]; then
    echo "pre-push: ninja not on PATH and .venv/bin/ninja missing — skip" >&2
    exit 0
fi

# Read refs from stdin (git push protocol): "<local-ref> <local-sha> <remote-ref> <remote-sha>"
push_failed=0
while read local_ref local_sha remote_ref remote_sha; do
    # Skip ref deletion (local_sha is all zeros)
    if [[ "$local_sha" =~ ^0+$ ]]; then
        continue
    fi
    # Check if any commits being pushed touch build-sensitive paths
    if [[ "$remote_sha" =~ ^0+$ ]]; then
        # New branch: check all commits in local_sha
        range="$local_sha"
    else
        range="$remote_sha..$local_sha"
    fi
    BUILD_SENSITIVE=$(git diff --name-only "$range" 2>/dev/null |
        grep -E '^(src/|asm/|config/|tools/|include/|baserom/|Makefile|build\.ninja$)' ||
        true)
    if [[ -z "$BUILD_SENSITIVE" ]]; then
        continue
    fi

    echo "pre-push: build-sensitive changes in $local_ref → re-verifying SHA gate ..."
    # Verify the tip being pushed builds clean. Use the current working
    # tree (which should match local_sha if the user hasn't done weird
    # things). If working tree differs, refuse.
    head_sha=$(git rev-parse HEAD)
    if [[ "$head_sha" != "$local_sha" ]]; then
        echo "pre-push: working tree HEAD ($head_sha) doesn't match pushed ref tip ($local_sha)." >&2
        echo "  Check out the pushed commit and re-run \`tools/build.sh setup && ninja\` manually first." >&2
        push_failed=1
        continue
    fi
    if ! "$ROOT/tools/build.sh" setup >/dev/null 2>&1; then
        echo "pre-push: SETUP FAILED on $local_ref — refusing push." >&2
        push_failed=1
        continue
    fi
    if ! "$NINJA" -C "$ROOT" >/dev/null 2>&1; then
        echo "pre-push: SHA-1 GATE FAILED on $local_ref — refusing push." >&2
        echo "  This is the byte-identical round-trip check. The commit being pushed" >&2
        echo "  was likely authored with \`git commit --no-verify\`. Fix the build" >&2
        echo "  (or rebase to drop the bad commit) before pushing." >&2
        push_failed=1
        continue
    fi
    echo "pre-push: SHA-1 gate OK on $local_ref"
done

exit $push_failed
EOF
chmod +x "$PUSH_HOOK"
echo "Installed pre-push hook at $PUSH_HOOK"
