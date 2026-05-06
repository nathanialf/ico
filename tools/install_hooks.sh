#!/usr/bin/env bash
# Install the IP-safety scan as a git pre-commit hook (opt-in).
# Re-run any time tools/check_no_rom.sh changes.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
HOOK="$ROOT/.git/hooks/pre-commit"

if [[ ! -d "$ROOT/.git" ]]; then
    echo "install_hooks: $ROOT is not a git repo (no .git dir)" >&2
    exit 1
fi

cat > "$HOOK" <<'EOF'
#!/usr/bin/env bash
# Auto-installed by tools/install_hooks.sh — runs:
#   1. tools/check_no_rom.sh (IP-safety scan on staged files)
# Bypass with --no-verify only after convincing yourself a hit is a real
# false positive.
set -e
ROOT="$(git rev-parse --show-toplevel)"
"$ROOT/tools/check_no_rom.sh"
EOF
chmod +x "$HOOK"
echo "Installed pre-commit hook at $HOOK"
