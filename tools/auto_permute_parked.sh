#!/usr/bin/env bash
# DEPRECATED: forwarding shim — the orchestrator now lives at
# tools/auto_permute.sh and iterates tough_nuts/<func>/ instead of
# tools/parked.txt. See tough_nuts/README.md.

echo "[auto_permute_parked.sh] deprecated — invoking tools/auto_permute.sh" >&2
exec "$(dirname "$0")/auto_permute.sh" "$@"
