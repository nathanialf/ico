#!/usr/bin/env bash
# Format (or check) the repo's C with clang-format and the tracked .clang-format.
#   tools/format.sh            # rewrite every tracked .c under the source roots
#   tools/format.sh --check    # exit 1 if any tracked .c is not formatted (pre-commit)
#   tools/format.sh FILE...    # format just these files
# Whitespace and line breaks only: the SHA-1 gate proves formatting never
# changes the ROM. The binary is the `clang-format` wheel in the venv
# (tools/setup.sh installs it); without it the check is skipped with a note.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CF="$ROOT/.venv/bin/clang-format"
if [[ ! -x "$CF" ]]; then
    echo "format: $CF not found (pip install clang-format into the venv); skipping" >&2
    exit 0
fi
mode=format
if [[ "${1:-}" == "--check" ]]; then mode=check; shift; fi
if [[ $# -gt 0 ]]; then
    files=("$@")
else
    mapfile -t files < <(cd "$ROOT" && git ls-files 'src/*.c' 'ios/*.c' 'sound/*.c' 'isys/*.c' 'ito/mpeg/*.c')
fi
cd "$ROOT"
if [[ "$mode" == check ]]; then
    bad=0
    for f in "${files[@]}"; do
        [[ -f "$f" ]] || continue
        if ! "$CF" --dry-run -Werror "$f" >/dev/null 2>&1; then
            echo "format: $f is not clang-formatted (run tools/format.sh $f)" >&2
            bad=1
        fi
    done
    exit $bad
fi
"$CF" -i "${files[@]}"
