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

# Resolve target asm. Splat 0.40.0 emits per-function baselines under
# asm/matchings/<name>/<func>.s when a subsegment is `[addr, c, name]`.
# Older splat versions (and hand-written stubs) live under asm/nonmatchings/.
# Try matchings first, then nonmatchings.
if [[ -d "asm/matchings/$NAME" ]]; then
    ASM_DIR="asm/matchings/$NAME"
elif [[ -d "asm/nonmatchings/$NAME" ]]; then
    ASM_DIR="asm/nonmatchings/$NAME"
else
    echo "quick_diff: no asm/matchings/$NAME or asm/nonmatchings/$NAME" >&2
    echo "  did you flip the yaml entry to 'c' and run 'make setup'?" >&2
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

# Compile with the project's matching compiler. ee-gcc 2.96 from
# tools/cc/ee-gcc2.96 if present (fetched by tools/setup.sh), else fall back
# to ee-prefix on PATH, else mips-linux-gnu-gcc (only useful for asm sanity
# checks — it won't match game C since the codegen differs).
EEGCC="$ROOT/tools/cc/ee-gcc2.96/bin/gcc"
if [[ -z "${CC:-}" ]]; then
    if [[ -x "$EEGCC" ]] && "$EEGCC" --version >/dev/null 2>&1; then
        CC="$EEGCC"
    elif command -v mips64r5900el-ps2-elf-gcc >/dev/null 2>&1; then
        CC="mips64r5900el-ps2-elf-gcc"
    else
        CC="mips-linux-gnu-gcc"
    fi
fi
# objdump for disassembly: prefer EE-aware, fall back to system mips
if [[ -z "${OBJDUMP:-}" ]]; then
    if command -v mips64r5900el-ps2-elf-objdump >/dev/null 2>&1; then
        OBJDUMP="mips64r5900el-ps2-elf-objdump"
    else
        OBJDUMP="mips-linux-gnu-objdump"
    fi
fi
# ee-gcc 2.96 is r5900-LE by default; -EL / -mips3 / -march=r5900 are either
# unsupported or redundant. Match SOTC's flag shape (mostly): -O2 -g2 -G 0
# -nostdinc -Iinclude. We use -S (emit asm, don't assemble) because the
# bundled `as` is from the 1990s and chokes on flags modern as accepts —
# we then run modern mips-linux-gnu-as on the .s output.
CFLAGS="${CFLAGS:--S -G 8 -O2 -g2 -fno-builtin -fno-optimize-sibling-calls -nostdinc -Iinclude}"

# Per-file overrides from config/extra_cflags.txt (same lookup as the
# Makefile src/.o rule), so quick_diff stays in sync with the full build.
EXTRA_CFLAGS_LOOKUP="$ROOT/tools/extra_cflags.sh"
if [[ -x "$EXTRA_CFLAGS_LOOKUP" ]]; then
    EXTRA_CFLAGS="$("$EXTRA_CFLAGS_LOOKUP" "$CSRC" 2>/dev/null || true)"
    if [[ -n "$EXTRA_CFLAGS" ]]; then
        CFLAGS="$CFLAGS $EXTRA_CFLAGS"
    fi
fi

# ee-gcc looks for cc1 at the path it was built against (typically
# ${PS2DEV}/ee/gcc-lib/...). Pass -B so it finds the bundled cc1 in our tree.
if [[ "$CC" == *"ee-gcc2.96"* ]]; then
    EEGCC_LIB="$ROOT/tools/cc/ee-gcc2.96/gcc-lib/ee/2.96-ee-001003-1/"
    CFLAGS="-B $EEGCC_LIB $CFLAGS"
fi

OBJ="build/quick_diff/$NAME.o"
ASM_OUT="build/quick_diff/$NAME.s"
mkdir -p "$(dirname "$OBJ")"

# Stage 1: ee-gcc → assembly
$CC $CFLAGS -o "$ASM_OUT" "$CSRC"

# Stage 2: assemble with modern binutils
ASFLAGS_QD="${ASFLAGS_QD:--EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -Iinclude}"
AS_FOR_QD="${AS_FOR_QD:-mips-linux-gnu-as}"
$AS_FOR_QD $ASFLAGS_QD -o "$OBJ" "$ASM_OUT"

# Canonicalize both sides via the same objdump so the diff is meaningful.
# We assemble the target .s with the same modern as, then objdump both .o's.
# splat's per-function .s files don't .include "macro.inc" themselves, so we
# prepend it to a temp copy.
TARGET_OBJ="build/quick_diff/$NAME.target.o"
TARGET_ASM_WRAPPED="build/quick_diff/$NAME.target.s"
{
    echo '.include "macro.inc"'
    echo '.set noreorder'
    echo '.set noat'
    cat "$TARGET_ASM"
} > "$TARGET_ASM_WRAPPED"
$AS_FOR_QD $ASFLAGS_QD -o "$TARGET_OBJ" "$TARGET_ASM_WRAPPED"

LEFT=$(mktemp); RIGHT=$(mktemp)
trap 'rm -f "$LEFT" "$RIGHT"' EXIT

# Pipe each through objdump → strip leading addr / opcode columns → keep
# only the mnemonic + operand columns. Tabs delimit; columns 3+ are the
# instruction text.
canon() {
    # objdump lines have shape:  "  ADDR:\tHEXBYTES\tMNEMONIC\tOPERANDS"
    # Strip leading whitespace + addr+colon + hex bytes; keep the rest.
    "$OBJDUMP" -d -M no-aliases "$1" 2>/dev/null \
        | sed -nE 's/^[[:space:]]*[0-9a-f]+:[[:space:]]+[0-9a-f]+[[:space:]]+//p'
}
canon "$TARGET_OBJ" > "$RIGHT"
canon "$OBJ"        > "$LEFT"

echo "=== expected: $TARGET_ASM ==="
cat -n "$RIGHT"
echo
echo "=== built: $CSRC -> $OBJ ==="
cat -n "$LEFT"
echo
echo "=== diff (expected | built) ==="
if diff -q "$RIGHT" "$LEFT" >/dev/null; then
    echo "MATCH (canonical instruction stream identical)"
else
    diff -y -W 200 "$RIGHT" "$LEFT" || true
fi
