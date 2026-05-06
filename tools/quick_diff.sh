#!/usr/bin/env bash
# =============================================================================
# tools/quick_diff.sh <func_name>
#
# Fast inner-loop diff: compile a single src/<name>.c (or
# tough_nuts/<name>/<name>.c), disassemble the result, and side-by-side it
# against asm/nonmatchings/<name>/<func>.s.
#
# Skips splat and full ELF linking — runs in ~100 ms vs ~30–60 s for a full
# `make setup && make`. This is the iteration loop for tough nuts.
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

if [[ $# -lt 1 ]]; then
    echo "usage: $0 <func_name_or_filename>" >&2
    exit 2
fi

NAME="$1"
shift || true

# Resolve C source: prefer src/, fall back to tough_nuts/
if [[ -f "src/$NAME.c" ]]; then
    CSRC="src/$NAME.c"
elif [[ -f "tough_nuts/$NAME/$NAME.c" ]]; then
    CSRC="tough_nuts/$NAME/$NAME.c"
else
    echo "quick_diff: no src/$NAME.c or tough_nuts/$NAME/$NAME.c" >&2
    exit 3
fi

# Resolve target asm: asm/nonmatchings/$NAME/<func>.s. If multiple .s files
# exist (multi-function source file), allow narrowing via second arg.
ASM_DIR="asm/nonmatchings/$NAME"
if [[ ! -d "$ASM_DIR" ]]; then
    echo "quick_diff: no $ASM_DIR (did you run 'make setup' after editing the yaml?)" >&2
    exit 4
fi

if [[ -n "${1:-}" ]]; then
    TARGET_ASM="$ASM_DIR/$1.s"
else
    # Default: pick the only .s, error if there are several.
    mapfile -t asms < <(find "$ASM_DIR" -maxdepth 1 -name '*.s' | sort)
    if [[ ${#asms[@]} -eq 0 ]]; then
        echo "quick_diff: no .s files in $ASM_DIR" >&2
        exit 5
    elif [[ ${#asms[@]} -gt 1 ]]; then
        echo "quick_diff: multiple .s files in $ASM_DIR; pass the function name as 2nd arg:" >&2
        printf "  %s\n" "${asms[@]##*/}" | sed 's/\.s$//' >&2
        exit 6
    fi
    TARGET_ASM="${asms[0]}"
fi

# Compile.
MIPS_PREFIX="${MIPS_PREFIX:-mips64r5900el-ps2-elf-}"
CC="${CC:-${MIPS_PREFIX}gcc}"
OBJDUMP="${OBJDUMP:-${MIPS_PREFIX}objdump}"
CFLAGS="${CFLAGS:--c -G 0 -O2 -mips3 -EL -fno-builtin -nostdinc -Iinclude}"

OBJ="build/quick_diff/$NAME.o"
mkdir -p "$(dirname "$OBJ")"
$CC $CFLAGS -o "$OBJ" "$CSRC"

# Disassemble compiled object and target asm side-by-side.
LEFT=$(mktemp)
RIGHT=$(mktemp)
trap 'rm -f "$LEFT" "$RIGHT"' EXIT

"$OBJDUMP" -d -M no-aliases "$OBJ" \
    | awk '/^[[:xdigit:]]+\s+<[a-zA-Z_]/{p=1} p{print}' \
    > "$LEFT"

# Strip splat-emitted directives / labels noise from the target asm so the
# diff focuses on instructions.
grep -E '^\s+[a-z]' "$TARGET_ASM" > "$RIGHT" || true

if command -v diff >/dev/null 2>&1; then
    diff -y --suppress-common-lines -W 200 "$RIGHT" "$LEFT" || true
else
    echo "(no diff binary; printing both)"
    echo "=== expected ($TARGET_ASM) ==="
    cat "$RIGHT"
    echo "=== built ($OBJ) ==="
    cat "$LEFT"
fi
