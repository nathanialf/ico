#!/usr/bin/env bash
# =============================================================================
# tools/quick_diff.sh <func_name>
#
# Fast inner-loop diff: compile a single src/<name>.c (or
# tough_nuts/<name>/<name>.c), disassemble the result, and side-by-side it
# against asm/nonmatchings/<name>/<func>.s.
#
# Skips splat and full ELF linking — runs in ~100 ms vs several minutes
# for a full `tools/build.sh setup && ninja`. This is the iteration loop
# for tough nuts.
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

# Resolve target asm. Splat emits per-function baselines under
# asm/matchings/<yaml-subseg-name>/<func>.s when a subsegment is
# `[addr, c, name]`. Since the repo flattened src/ios/sound/isys to
# repo-root paths (yaml subsegs like `src/DmaPacket`), splat puts the
# asm at `asm/matchings/src/<TU>/`. We try a few shapes so the user
# can pass either the bare TU name (`layout_texture`) or the path
# (`src/layout_texture`).
for candidate in \
    "asm/matchings/$NAME" \
    "asm/matchings/src/$NAME" \
    "asm/nonmatchings/$NAME" \
    "asm/nonmatchings/src/$NAME"; do
    if [[ -d "$candidate" ]]; then
        ASM_DIR="$candidate"
        break
    fi
done
if [[ -z "${ASM_DIR:-}" ]]; then
    echo "quick_diff: no asm/matchings/$NAME (or src/$NAME) and no asm/nonmatchings/$NAME" >&2
    echo "  did you flip the yaml entry to 'c' and run 'tools/build.sh setup'?" >&2
    exit 4
fi

if [[ -n "${1:-}" ]]; then
    TARGET_ASM="$ASM_DIR/$1.s"
    # In coalesced TUs, the matched funcs live under asm/matchings/src/<TU>/
    # while the still-INCLUDE_ASM'd funcs live under asm/nonmatchings/src/<TU>/.
    # When the caller asks for a specific func name, fall through to the
    # nonmatchings sibling dir if the file isn't in the chosen ASM_DIR.
    if [[ ! -f "$TARGET_ASM" ]]; then
        case "$ASM_DIR" in
            asm/matchings/src/*) ALT_DIR="asm/nonmatchings/src/${ASM_DIR#asm/matchings/src/}" ;;
            asm/matchings/*)     ALT_DIR="asm/nonmatchings/${ASM_DIR#asm/matchings/}" ;;
            *)                   ALT_DIR="" ;;
        esac
        if [[ -n "$ALT_DIR" && -f "$ALT_DIR/$1.s" ]]; then
            TARGET_ASM="$ALT_DIR/$1.s"
        fi
    fi
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

# Compile with the project's matching compiler. ee-gcc 2.9-991111 from
# tools/cc/ee-gcc2.9-991111 if present (fetched by tools/setup.sh), else
# fall back to ee-prefix on PATH, else mips-linux-gnu-gcc (only useful
# for asm sanity checks — it won't match game C since the codegen differs).
EEGCC="$ROOT/tools/cc/ee-gcc2.9-991111/ee-gcc"
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
# Must agree with Makefile CFLAGS exactly so quick_diff and full build
# reach the same regalloc / scheduling decisions. ee-gcc 2.9-991111 doesn't
# accept -fno-optimize-sibling-calls (sibling-call defeat is per-function
# via __asm__ volatile("") barriers in src/cod/). -S because the bundled
# 2.9-era `as` chokes on modern flags — we re-assemble with ee-as 2.10.
CFLAGS="${CFLAGS:--S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -Iinclude}"

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
if [[ "$CC" == *"ee-gcc2.9-991111"* ]]; then
    EEGCC_LIB="$ROOT/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/"
    CFLAGS="-B $EEGCC_LIB $CFLAGS"
fi

OBJ="build/quick_diff/$NAME.o"
ASM_OUT="build/quick_diff/$NAME.s"
mkdir -p "$(dirname "$OBJ")"

# Stage 1: ee-gcc → assembly
$CC $CFLAGS -o "$ASM_OUT" "$CSRC"

# Stage 1b: run postprocesses listed in their gate files (match
# compile_c.sh pipeline). Only the per-file postprocesses; the always-on
# sw_pair + `move`→`daddu` translations are applied unconditionally.
qd_listed() {
    local txt="$ROOT/config/$1"
    [ -r "$txt" ] || return 1
    local base="$(basename "$NAME")"
    grep -qE "^[[:space:]]*(${NAME}|${base})([[:space:]]|\$|#)" "$txt"
}
qd_listed no_trailing_nop.txt    && python3 "$ROOT/tools/postprocess_no_trailing_nop.py" "$ASM_OUT" || true
qd_listed shared_sp_restore.txt  && python3 "$ROOT/tools/postprocess_shared_sp_restore.py" --sp-only "$ASM_OUT" || true
qd_listed shared_jr_restore.txt  && python3 "$ROOT/tools/postprocess_shared_sp_restore.py" --jr-and-sp "$ASM_OUT" || true
qd_listed la_sd_interleave.txt   && python3 "$ROOT/tools/postprocess_la_sd_interleave.py" "$ASM_OUT" || true
qd_listed fcc_nop.txt            && python3 "$ROOT/tools/postprocess_fcc_nop.py" "$ASM_OUT" || true
qd_listed early_body_swap.txt    && python3 "$ROOT/tools/postprocess_early_body_swap.py" "$ASM_OUT" || true
qd_listed unfold_ra_delay.txt    && python3 "$ROOT/tools/postprocess_unfold_ra_delay.py" "$ASM_OUT" || true
qd_listed early_epilogue_restore.txt && python3 "$ROOT/tools/postprocess_early_epilogue_restore.py" "$ASM_OUT" || true
qd_listed fill_blez_delay.txt        && python3 "$ROOT/tools/postprocess_fill_blez_delay.py" "$ASM_OUT" || true
qd_listed swap_zero_ret_ld_ra.txt    && python3 "$ROOT/tools/postprocess_swap_zero_ret_ld_ra.py" "$ASM_OUT" || true
qd_listed v0_zero_in_bne_delay.txt   && python3 "$ROOT/tools/postprocess_v0_zero_in_bne_delay.py" "$ASM_OUT" || true
qd_listed jal_daddu_lw_loop.txt      && python3 "$ROOT/tools/postprocess_jal_daddu_lw_loop.py" "$ASM_OUT" || true
qd_listed lui_const_swap.txt        && python3 "$ROOT/tools/postprocess_lui_const_swap.py" "$ASM_OUT" || true
qd_listed swap_addu_operands.txt && sed -i -E 's/(addu[[:space:]]+\$([0-9]+),)\$([0-9]+),\$\2\b/\1$\2,$\3/g' "$ASM_OUT" || true
qd_listed coalesce_v1_v0.txt     && sed -i -E -e '/^[[:space:]]*move[[:space:]]+\$2,\$3[[:space:]]*$/d' -e 's/\$3\b/$2/g' "$ASM_OUT" || true
python3 "$ROOT/tools/postprocess_sw_pair.py" "$ASM_OUT" || true
sed -i -E 's/\bmove[[:space:]]+(\$[0-9a-zA-Z]+),[[:space:]]*(\$[0-9a-zA-Z]+)\b/daddu \1,\2,$0/g' "$ASM_OUT"

# Stage 2: assemble. Prefer the project's ee-as 2.10 (matches the full
# build's src/.o pipeline so `move` pseudos expand consistently — modern
# mips-linux-gnu-as expands `move rd,rs` to `or`, ee-as expands to
# `daddu`, which would otherwise show up as spurious diffs). Fall back
# to mips-linux-gnu-as if ee-as rejects the input (typically on VU0/MMI
# ops it doesn't know).
EE_AS="$ROOT/tools/cc/ee-gcc2.96/bin/as"
EE_ASFLAGS="-EL -mcpu=5900 -G 8 -I$ROOT/include"
AS_MODERN="${AS_FOR_QD:-mips-linux-gnu-as}"
ASFLAGS_MODERN="${ASFLAGS_QD:--EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -Iinclude}"

# ee-as 2.10 doesn't accept register-name aliases ($zero, $sp, $ra, ...).
# Translate any to numbered. ee-gcc-emitted output uses $N already, but
# splat-generated target .s often has $sp/$ra/etc.
canon_regnames() {
    sed -i -E -e 's/\$zero\b/$0/g'  -e 's/\$at\b/$1/g' \
               -e 's/\$v0\b/$2/g'    -e 's/\$v1\b/$3/g' \
               -e 's/\$a0\b/$4/g'    -e 's/\$a1\b/$5/g' \
               -e 's/\$a2\b/$6/g'    -e 's/\$a3\b/$7/g' \
               -e 's/\$t0\b/$8/g'    -e 's/\$t1\b/$9/g' \
               -e 's/\$t2\b/$10/g'   -e 's/\$t3\b/$11/g' \
               -e 's/\$t4\b/$12/g'   -e 's/\$t5\b/$13/g' \
               -e 's/\$t6\b/$14/g'   -e 's/\$t7\b/$15/g' \
               -e 's/\$s0\b/$16/g'   -e 's/\$s1\b/$17/g' \
               -e 's/\$s2\b/$18/g'   -e 's/\$s3\b/$19/g' \
               -e 's/\$s4\b/$20/g'   -e 's/\$s5\b/$21/g' \
               -e 's/\$s6\b/$22/g'   -e 's/\$s7\b/$23/g' \
               -e 's/\$t8\b/$24/g'   -e 's/\$t9\b/$25/g' \
               -e 's/\$k0\b/$26/g'   -e 's/\$k1\b/$27/g' \
               -e 's/\$gp\b/$28/g'   -e 's/\$sp\b/$29/g' \
               -e 's/\$fp\b/$30/g'   -e 's/\$ra\b/$31/g' \
               "$1"
}

assemble() {
    local out="$1" in="$2"
    if [[ -x "$EE_AS" ]] && "$EE_AS" $EE_ASFLAGS -o "$out" "$in" 2>/dev/null; then
        return 0
    fi
    $AS_MODERN $ASFLAGS_MODERN -o "$out" "$in"
}

canon_regnames "$ASM_OUT"
assemble "$OBJ" "$ASM_OUT"

# Canonicalize both sides via the same objdump so the diff is meaningful.
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
canon_regnames "$TARGET_ASM_WRAPPED"
assemble "$TARGET_OBJ" "$TARGET_ASM_WRAPPED"

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

# Mask the gp-rel cosmetic: unlinked quick_diff .o shows `,0(gp)`
# while the linked baseline shows the resolved offset like
# `,-16384(gp)`. Only the narrow "built=0, target=non-zero"
# signature is masked — see tools/mask_gp_rel.py for why looser
# normalization would hide real divergences.
"$ROOT/.venv/bin/python" "$ROOT/tools/mask_gp_rel.py" "$RIGHT" "$LEFT"

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
