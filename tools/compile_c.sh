#!/usr/bin/env bash
# tools/compile_c.sh <src.c> <out.o>
#
# Compile one C source for the ICO decomp: ee-gcc → .s →
# postprocessors → regname sed → ee-as (or mips-as fallback) → objcopy.
# Replaces the per-recipe body of the Makefile's $(BUILD_DIR)/src/%.o
# rule so the same path is callable from both Make (Phase 1) and Ninja
# (Phase 2). Running all the steps inside one shell invocation avoids
# the per-line fork overhead that Make imposed on every `.c` file.

set -eu

[ $# -eq 2 ] || { echo "usage: $0 <src.c> <out.o>" >&2; exit 2; }
SRC="$1"
OUT="$2"

ROOT="$(cd "$(dirname "$0")/.." && pwd)"

EEGCC_DIR="${EEGCC_DIR:-${ROOT}/tools/cc/ee-gcc2.9-991111}"
EEGCC_LIB="${EEGCC_DIR}/gcc-lib/ee/2.9-ee-991111-01/"
CC="${EEGCC_DIR}/ee-gcc"

if command -v mips64r5900el-ps2-elf-objcopy >/dev/null 2>&1; then
    MIPS_PREFIX="mips64r5900el-ps2-elf-"
else
    MIPS_PREFIX="mips-linux-gnu-"
fi
OBJCOPY="${MIPS_PREFIX}objcopy"

# TWO ASSEMBLERS, SELECTED PER ARCHIVE BY THE DISC'S LINK (user ruling 2026-09-27,
# docs/NOTES.md "Assembler per archive"). MAIN.MAP takes libc.a, libm.a and
# libgcc.a from the studio's ee-gcc 2.9-991111-01 install and every other archive
# from Sony's SDK install (/usr/local/sce/ee/lib, version strings PsIIlib* 2200
# and 2240 in the ELF). The game and the compiler-install libraries were
# assembled by the assembler bundled with that compiler, EE_AS_OLD: 142 game TUs
# and 12 libc/libm TUs only match under it. The SDK-install archives were
# compiled by a compiler code-identical to it (SCE's later 2.96 is ruled out by
# size) but assembled by a later gas that fills reorder-mode branch delay slots:
# sceGsSyncPath, sceScfSetT10kConfig and cmd_sem_init are the compiler's own
# output plus that swap, and all 58 matched archive TUs are byte-identical under
# both. EE_AS_SDK is SCE's own 2.10-ee-001003-1 assembler (tools/setup.sh
# fetches it), which reproduces all three; the bytes prove the behaviour, not
# which gas binary Sony's library build ran. The selection is by ARCHIVE only:
# never per TU, never per function, never a config opt-in (config/use_as296.txt,
# a per-TU opt-in, was tried and reverted 2026-08-05 for exactly that reason).
# Compiler-install assembler, whose delay-slot reorder is LESS aggressive than 2.10: it
# does not hoist a preceding unaligned store (sdl/sdr/...) into a `j <func>`
# tail-call delay slot, matching the original ICO toolchain (verified universal:
# 0 of 783 ROM tail-calls carry an unaligned store in the delay). It is THE
# assembler for every C TU — there is no per-TU selection and no fallback.
EE_AS_OLD="${ROOT}/tools/cc/ee-gcc2.9-991111/bin/as"
# SDK-install archive assembler (see the paragraph above).
EE_AS_SDK="${ROOT}/tools/cc/ee-gcc2.96/bin/as"

INCLUDE_DIR="${ROOT}/include"
# include/ holds stub scaffolding only (the fdlibm two-word idiom now lives in the libm members that use it): the libm
# members and the game TUs that use the GET_FLOAT_WORD macros reach it by name.
# Small-data threshold. The game (ico2/) was built at -G 8. Every SDK archive
# under sce/ was built at -G 0: no SDK function in the ROM makes a gp-relative
# access (0 of 208 stubs across twelve archives), the libm and libscf members
# only match at -G 0 (li.s expands to lui/ori/mtc1, short strings and NaNs land
# in .rodata rather than .sdata), and the whole tree is byte-identical with
# every sce/ member at -G 0 (measured 2026-09-16). A library's own build
# setting is a fact of that archive, not a per-function lever.
# The same split decides -fno-builtin. MAIN.MAP's LOAD list shows the game
# linked against Sony's prebuilt archives (libc.a, libm.a, libgcc.a and the
# /usr/local/sce/ee/lib archives), never compiling them: the archives carry
# newlib's own build flag, which keeps libm calling fabsf where a builtin
# would inline it, while the game compiled plain, which is what expands the
# aligned six-byte memcpy in layout_action (measured 2026-09-18).
# The same split decides -g (user ruling 2026-09-27, docs/NOTES.md "-g for the
# game"): the studio compiled the game with line information and Sony's
# archives were built without it. Measured: Info-ZIP's plain huft_build text,
# the shape the listing's line map shows, gives the ROM's 498 words only with
# -g (a line note left after the deleted break keeps cse_around_loop off the
# body's load); every other matched game TU is byte-identical with or without
# it; the January listing, a build with line information for certain, agrees
# with the retail words on that region where the no-g build does not; and with
# -g the SDK archives lose the delay-slot fills their assembler gave them, so
# they were built without it. Per origin only, never per TU.
case "${1:-}" in
    sce/*|*/sce/*) GNUM=0; BUILTIN="-fno-builtin"; DBG="" ;;
    *) GNUM=8; BUILTIN=""; DBG="-g" ;;
esac
# The SDK's and newlib's own public headers, reconstructed under sce/<archive>/
# by public naming (the members and the game TUs include them as <libdma.h>).
SCE_INCS=""
for _a in libc libm libvu0 libkernl libpkt libgraph libdma libpad libscf libmpeg libmc libipu libcdvd; do
    SCE_INCS="${SCE_INCS} -I${ROOT}/sce/${_a}"
done
CFLAGS="-S ${DBG} -G ${GNUM} -O2 -mips3 -EL ${BUILTIN} -nostdinc -fdata-sections -I${INCLUDE_DIR}${SCE_INCS}"
ASFLAGS="-EL -march=r5900 -mabi=eabi -G ${GNUM} -no-pad-sections -I${INCLUDE_DIR}"
EE_ASFLAGS="-EL -mcpu=5900 -G ${GNUM}"

PYTHON="${ROOT}/.venv/bin/python"

BASE="$(basename "${SRC}" .c)"
# Relative TU path without the .c (e.g. fumi/src/jimaku), with any leading
# ROOT/ prefix stripped — the alternate config key form quick_diff.sh accepts.
REL="${SRC%.c}"; REL="${REL#"${ROOT}/"}"
S="${OUT%.o}.s"

# Match the Makefile's `^[[:space:]]*<KEY>(<space>|<eol>|#)` pattern. KEY may be
# the TU BASENAME (canonical) or the full TU path — both forms are honored here
# and in quick_diff.sh so a single config line agrees across diff and build.
listed() {
    local txt="$1"
    [ -r "$txt" ] || return 1
    grep -qE "^[[:space:]]*(${BASE}|${REL})([[:space:]]|\$|#)" "$txt"
}

# Replicates Makefile:162 ALIGN_FOR in pure shell — picks the largest
# power-of-two ≤ 8 dividing the hex offset encoded in the .o basename.
# Non-hex basenames (and offset 0) fall through to 8.
align_for() {
    local b="$1" n=0 a=8
    if [[ "$b" =~ ^[0-9A-Fa-f]+$ ]]; then
        n=$((16#$b))
    fi
    while [ "$a" -gt 1 ] && [ "$n" -ne 0 ] && [ $((n % a)) -ne 0 ]; do
        a=$((a / 2))
    done
    printf '%s' "$a"
}
ALIGN="$(align_for "$(basename "${OUT%.o}")")"

mkdir -p "$(dirname "${OUT}")"

# TUs that include a header under `ito/include/` (e.g. mv_defs.h) must be
# compiled so the `__FILE__` literal resolves to "../ito/include/<h>" exactly
# as the original build did: a *relative* `-I../ito/include` evaluated from a
# CWD one level below ROOT (so `../ito/include` == `${ROOT}/ito/include`).
# ee-gcc records the -I spelling verbatim into __FILE__, so an absolute -I (or
# a different CWD) would change the baked rodata string. Opt-in per TU via
# config/include_ito.txt; all paths are made absolute since CWD changes.
INCLUDE_ITO_TXT="${ROOT}/config/include_ito.txt"
# ico2/<programmer>/<kind>/<file>.c : compile it the way the original build
# did, from inside the programmer's own directory with RELATIVE -I entries to
# the sibling programmers' include dirs. ee-gcc bakes the spelling it is given
# into __FILE__, so both the source argument (`src/main.c`, not
# `ico2/common/src/main.c`) and the header spelling (`../ito/include/mv_defs.h`)
# have to match what the 2002 link recorded. The project's own headers stay at
# the repo-root include/ and are reached by an absolute -I.
ICO2_PROG=""
case "${SRC}" in
    ico2/*/*) ICO2_PROG="${SRC#ico2/}"; ICO2_PROG="${ICO2_PROG%%/*}" ;;
esac
if [ -n "${ICO2_PROG}" ]; then
    SRC_REL="${SRC#ico2/${ICO2_PROG}/}"
    S_ABS="${S}"; case "${S_ABS}" in /*) ;; *) S_ABS="${ROOT}/${S_ABS}";; esac
    # Search order: the programmer's own include dir first, then the
    # cross-programmer dirs the listing shows their TUs reaching into, then
    # (from CFLAGS) the repo's own include/ last.
    ICO2_INCS=""
    for _p in "${ICO2_PROG}" sugipon omori common ito fumi seki script; do
        [ -d "${ROOT}/ico2/${_p}/include" ] || continue
        case " ${ICO2_INCS} " in *" -I../${_p}/include "*) continue ;; esac
        ICO2_INCS="${ICO2_INCS} -I../${_p}/include"
    done
    # shellcheck disable=SC2086
    ( cd "${ROOT}/ico2/${ICO2_PROG}" \
      && "${CC}" -B "${EEGCC_LIB}" ${ICO2_INCS} ${CFLAGS} -o "${S_ABS}" "${SRC_REL}" )
elif listed "${INCLUDE_ITO_TXT}"; then
    SRC_ABS="${SRC}"; case "${SRC_ABS}" in /*) ;; *) SRC_ABS="${ROOT}/${SRC_ABS}";; esac
    S_ABS="${S}";    case "${S_ABS}"   in /*) ;; *) S_ABS="${ROOT}/${S_ABS}";; esac
    # shellcheck disable=SC2086
    ( cd "${ROOT}/ito" && "${CC}" -B "${EEGCC_LIB}" ${CFLAGS} -I../ito/include -o "${S_ABS}" "${SRC_ABS}" )
else
    # sce/<archive>/<member>.c : the vendor archives were built member by member
    # from inside the member's own directory, so __FILE__ is the bare name
    # (measured 2026-09-16: libscf.o's assert strings carry "libscf.c").
    SRC_ABS="${SRC}"; case "${SRC_ABS}" in /*) ;; *) SRC_ABS="${ROOT}/${SRC_ABS}";; esac
    S_ABS="${S}";    case "${S_ABS}"   in /*) ;; *) S_ABS="${ROOT}/${S_ABS}";; esac
    # shellcheck disable=SC2086
    ( cd "$(dirname "${SRC_ABS}")" && "${CC}" -B "${EEGCC_LIB}" ${CFLAGS} -o "${S_ABS}" "$(basename "${SRC_ABS}")" )
fi

# Split each gcc-emitted switch jtbl onto its own .rodata.0x<VMA>
# section so the linker can place multi-jtbl TUs correctly. No-op on
# single-jtbl TUs and on .s files with no `.rdata`/jtbl blocks.
"${PYTHON}" "${ROOT}/tools/postprocess_split_jtbls.py" "${S}"

# No rewrite of compiler output is left. The last one was the inline-asm return
# wrap: ee-as 2.9-991111 swaps the final instruction of a gcc inline-asm block
# into the following `jr $31` delay slot, and the ROM has a `nop` there in all
# 69 ico2 sites. That is a source fact, not an assembler fact, and the ROM says
# so: sce/libvu0 carries `sqc2` in 26 of its own return slots, the raw
# toolchain's output, so the SDK and the game were built from differently
# spelled VU0 asm templates. The game side's template now spells `.set
# noreorder` / `.set reorder` around its body, in ico2/common/include/typedef.h
# and in the four hand-written blocks of ico2/seki/src/Matrix.c, which
# reproduces all six objects byte-identical with no rewrite at all. libvu0's
# own copy of the macros stays raw.

# `move` and `break N` need no rewrite: ee-as 2.9-991111 already encodes `move`
# as `daddu $r,$s,$0` and puts a single-operand `break N` code in the LOW field,
# both the ROM's encodings. The two sed rewrites that forced them (24057 and 349
# sites) were measured byte-dead on the whole tree and dropped 2026-09-15.

# `cvt.w.s` is assembled by the period assembler itself: ee-as 2.9-991111 emits the
# ROM's COP1 word (function 0x24, which modern objdump prints as trunc.w.s). The
# former `.word` rewrite (a modern-gas parity shim, retired with that fallback)
# made gas flush pending hazards at the data directive and emitted nops the ROM
# does not have (after mfc1, and after a store two insns past a c.lt.s); dropped
# 2026-09-05, whole ROM re-verified byte-identical.

# NOTE: the r5900 special VU0 registers ACC / Q / R need no translation here.
# Both sources now speak the period assembler's dialect natively: splat emits
# them bare (patch_splat.py's sigil rewrite is retired) and our own inline asm
# — include/vu0.h plus the literal VU0_REG strings — was converted to the bare
# spelling at source on 2026-08-01. The modern-gas path adds the `$` back via
# preprocess_old_as.py --modern below, which also covers the .include'd files.

# ee-as 2.10 only accepts numbered MIPS registers; translate all aliases
# (float regs $f0-$f31 and VU regs $vfN are already accepted as-is).
sed -i -E \
    -e 's/\$zero\b/$0/g'  -e 's/\$at\b/$1/g' \
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
    "${S}"

# Assembler, selected per ARCHIVE by the disc's link (the paragraph at EE_AS_OLD
# and docs/NOTES.md "Assembler per archive"): the game and the compiler-install
# libraries (libc, libm, libgcc) on the assembler bundled with the compiler, the
# SDK-install archives on SCE's 2.10-ee assembler that fills reorder-mode delay
# slots as Sony's library build did. Both reject splat's `%gp_rel(SYM)($28)`
# spelling, so a MIXED TU (C + INCLUDE_ASM siblings) is first flattened +
# gp_rel-translated by preprocess_old_as.py (byte-identical GPREL16).
# There is no per-TU and no per-function selection and no config opt-in
# (config/use_as296.txt was tried and reverted 2026-08-05; config/use_old_as.txt
# retired 2026-09-04), and no modern-gas path at all (retired 2026-08-05: it
# manufactured 8 false delay-slot matches in GAME code, where the ROM proves the
# slots bare).
ASM_INPUT="${S}"
case "${SRC}" in
    sce/libc/*|*/sce/libc/*|sce/libm/*|*/sce/libm/*|sce/libgcc/*|*/sce/libgcc/*)
        SELECTED_EE_AS="${EE_AS_OLD}" ;;   # compiler-install archives (MAIN.MAP)
    sce/*|*/sce/*)
        SELECTED_EE_AS="${EE_AS_SDK}" ;;   # SDK-install archives (/usr/local/sce/ee/lib)
    *)
        SELECTED_EE_AS="${EE_AS_OLD}" ;;   # the game
esac
# Flatten INCLUDE_ASM siblings + translate splat's gp_rel spellings to the bare
# gp-addressable form the PERIOD assembler accepts, so the ROM's contemporary
# assembler (ee-as 2.9-991111) assembles mixed C+asm TUs
# directly instead of silently falling back to modern gas (which mis-encodes
# `la sdata` as daddiu where the ROM has addiu). See docs/NOTES.md.
# stderr is NOT swallowed: preprocess_old_as.py is silent on success, so
# anything it prints names a real defect. Hiding it would leave only the
# assembler's downstream "REJECTED" to go on.
if "${PYTHON}" "${ROOT}/tools/preprocess_old_as.py" "${S}" "${S}.pp"; then
    ASM_INPUT="${S}.pp"
fi

# THE SELECTED ASSEMBLER IS THE ONLY ASSEMBLER FOR THIS TU. There is no modern-gas
# path here any more — no allowlist, no failure fallback. Retired 2026-08-05.
#
# WHY (do not reinstate either one):
#   Modern gas fills delay slots that ee-as 2.9-991111 leaves bare, so a GAME TU
#   that reached it could "match" on the ASSEMBLER's scheduling rather than on
#   source shape. That produced 8 false matches (1 enemy, 2 Packet, 5
#   vendor_2418A0), every one of which had to be reverted to INCLUDE_ASM on
#   2026-08-01 and re-derived in C. The game's slots are bare in the ROM; only the
#   SDK-install archives carry the fill, and those get it by the archive rule
#   above, never by a fallback.
#
# If the selected assembler rejects this TU, that is a REAL defect in the .s to be
# fixed at the source (past causes: splat's `enddlabel` leaving an `.ent`
# unclosed — fixed in include/labels.inc; the $ACC/$Q/$R sigil dialect, which
# preprocess_old_as.py now translates to the bare spelling). Hard-fail so ninja
# stops on it instead of silently producing an object from a different assembler.
# shellcheck disable=SC2086
if "${SELECTED_EE_AS}" ${EE_ASFLAGS} -I"${INCLUDE_DIR}" -o "${OUT}" "${ASM_INPUT}" 2>"${OUT}.aserr"; then
    rm -f "${OUT}.aserr"
    "${OBJCOPY}" "${OUT}" "${OUT}"
else
    echo "compile_c.sh: assembler ${SELECTED_EE_AS} REJECTED ${ASM_INPUT}" >&2
    grep -iE 'error' "${OUT}.aserr" | head -20 >&2 || head -20 "${OUT}.aserr" >&2
    rm -f "${OUT}.aserr" "${OUT}"
    echo "  This is a source defect to FIX, not an assembler to swap: there is no" >&2
    echo "  modern-gas fallback (retired 2026-08-05 — it manufactured 8 false" >&2
    echo "  delay-slot matches). See docs/NOTES.md \"Assembler\"." >&2
    exit 1
fi

# Carve safety: modern gas applies `record_alignment (data_section, 4)` — a hard
# 2**4 floor — to the STANDARD sections `.text`/`.data`/`.bss` no matter what the
# assembly contains, so a C TU assembled on the gas path carries an EMPTY `.data`
# (and `.bss`) demanding 16-byte alignment. `ld` pads for a zero-size input
# section exactly as it does for a real one, so as soon as a data carve makes the
# `.data` output land at an address that is 8- but not 16-aligned, the first such
# empty section injects 8 bytes of `*fill*` and every following byte shifts —
# the classic "2nd carve corrupts the link" failure. `-fdata-sections` puts all
# real TU data in `.data.<sym>` / `.rodata.<sym>` (whose gcc-assigned alignment
# IS load-bearing: it reproduces intra-TU padding), so forcing the leftover
# standard sections to 1 is free. `.text` keeps ${ALIGN} — it reproduces the
# ROM's inter-TU function padding. See docs/NOTES.md "Data carves" (the section-alignment floor).
"${OBJCOPY}" --set-section-alignment ".data=1" \
             --set-section-alignment ".bss=1" "${OUT}"

