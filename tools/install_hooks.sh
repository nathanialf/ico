#!/usr/bin/env bash
# Install the IP-safety scan + byte-identical-build gate as a git
# pre-commit hook (opt-in). Re-run any time the hook body changes.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
HOOK="$ROOT/.git/hooks/pre-commit"

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
