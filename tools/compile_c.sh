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

if command -v mips64r5900el-ps2-elf-as >/dev/null 2>&1; then
    MIPS_PREFIX="mips64r5900el-ps2-elf-"
else
    MIPS_PREFIX="mips-linux-gnu-"
fi
OBJCOPY="${MIPS_PREFIX}objcopy"

# NOTE: neither modern gas (${MIPS_PREFIX}as) nor the 2.10-ee-001003-1 assembler
# under tools/cc/ee-gcc2.96/bin/as is reachable from this script any more, and
# neither is bound to a variable — a spare handle on another assembler is the
# first thing a stuck matching run reaches for. THE assembler is EE_AS_OLD below:
# the one bundled with the compiler this build uses. See decomp/NOTES.md.
# Period assembler whose delay-slot reorder is LESS aggressive than 2.96: it
# does not hoist a preceding unaligned store (sdl/sdr/...) into a `j <func>`
# tail-call delay slot, matching the original ICO toolchain (verified universal:
# 0 of 783 ROM tail-calls carry an unaligned store in the delay). It is THE
# assembler for every C TU — there is no per-TU selection and no fallback.
EE_AS_OLD="${ROOT}/tools/cc/ee-gcc2.9-991111/bin/as"

INCLUDE_DIR="${ROOT}/include"
CFLAGS="-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I${INCLUDE_DIR}"
ASFLAGS="-EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -I${INCLUDE_DIR}"
EE_ASFLAGS="-EL -mcpu=5900 -G 8"

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
if listed "${INCLUDE_ITO_TXT}"; then
    SRC_ABS="${SRC}"; case "${SRC_ABS}" in /*) ;; *) SRC_ABS="${ROOT}/${SRC_ABS}";; esac
    S_ABS="${S}";    case "${S_ABS}"   in /*) ;; *) S_ABS="${ROOT}/${S_ABS}";; esac
    # shellcheck disable=SC2086
    ( cd "${ROOT}/ito" && "${CC}" -B "${EEGCC_LIB}" ${CFLAGS} -I../ito/include -o "${S_ABS}" "${SRC_ABS}" )
else
    # shellcheck disable=SC2086
    "${CC}" -B "${EEGCC_LIB}" ${CFLAGS} -o "${S}" "${SRC}"
fi

# Split each gcc-emitted switch jtbl onto its own .rodata.0x<VMA>
# section so the linker can place multi-jtbl TUs correctly. No-op on
# single-jtbl TUs and on .s files with no `.rdata`/jtbl blocks.
"${PYTHON}" "${ROOT}/tools/postprocess_split_jtbls.py" "${S}"

# Each runs whole-TU unless its config line carries `@func_<hex>` tokens, in
# (the per-function scoped variant was retired with the allowlists) — so a
# postprocess added for one func in a coalesced TU can't rewrite its siblings.
# Promote gcc's `#nop` hazard-hint comment after an FCC compare to a real `nop`
# when the following branch sits in a `.set noreorder` block — ee-as 2.96 ignores
# the comment, so the R5900 FCC-update hazard slot would otherwise be unfilled.
# Universal assembler-adaptation (retired postprocess_fcc_nop.py + its allowlist),
# same category as the move→daddu / break sed rewrites below.
awk '
{ ln[NR]=$0 }
END { i=1; while (i<=NR) { print ln[i];
  if (ln[i] ~ /^[ \t]*c\.(lt|le|eq)\.[sd]([ \t]|$)/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] ~ /^[ \t]*\.set[ \t]+noreorder([ \t]|$)/) { print "\tnop"; i+=2; continue } }
  i++ } }' "${S}" > "${S}.fcc" && mv "${S}.fcc" "${S}"

# COP1-move (mfc1 / mtc1) hazard, opposite of the FCC case above. gcc emits an
# `mfc1 $r,$f` (move-out) OR `mtc1 $r,$f` (move-in) immediately followed by a
# `#nop` COMMENT and then the DEPENDENT instruction it scheduled into that hazard
# slot. The period assembler (ee-as 2.9-991111) and the ROM leave the dependent
# insn directly after the move (the R5900 interlocks the COP1 move — verified: the
# ROM has `mfc1;daddu` and `mtc1;c.lt.s` adjacent), but ee-as 2.96 / modern gas in
# `.set reorder` mode FILL that slot with a real nop. The `#nop` comment is gcc's
# marker that the slot is already filled — distinct from the cases where gcc emits
# a REAL `nop` it couldn't fill (those stay, e.g. the 71 ROM `mfc1;nop` sites).
# Wrap the move + its dependent use in `.set noreorder` so modern gas does NOT
# insert the spurious nop; under the period assembler the wrap is a byte no-op.
# Universal assembler-adaptation (same category as the FCC / jr-fp / move→daddu
# rewrites). Fixes coalesced TUs (e.g. PObj) whose VU0 siblings force the modern-as
# fallback so the period assembler can't be used wholesale, and FP compares whose
# 0.0 operand is materialized via `mtc1 $0,$fN` (e.g. stage_DispAnimation).
awk '
{ ln[NR]=$0 }
END { nr=0; seen=0; i=1; while (i<=NR) {
  # Track gcc-emitted .set state + whether a real insn has appeared in the
  # current reorder region (gas resets its pipeline model at region entry and
  # at every label/branch target).
  if (ln[i] ~ /\.set[ \t]+noreorder/) { nr=1; print ln[i]; i++; continue }
  if (ln[i] ~ /\.set[ \t]+reorder/)   { nr=0; seen=0; print ln[i]; i++; continue }
  if (ln[i] ~ /:[ \t]*$/)             { seen=0; print ln[i]; i++; continue }

  # Case 1 (existing): m[ft]c1 + `#nop` marker + the dependent insn gcc
  # scheduled into the COP1-move hazard slot.
  if (ln[i] ~ /^[ \t]*m[ft]c1[ \t]/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] !~ /^[ \t]*\./ && ln[j] !~ /:[ \t]*$/ && ln[j] !~ /^[ \t]*[bj][a-z0-9]*[ \t]/) {
      print "\t.set noreorder"; print ln[i]; print ln[j]; print "\t.set reorder";
      nr=0; seen=0; i=j+1; continue } }

  # Case 2 (new): a marker-less `mtc1` that is the FIRST real insn of a reorder
  # region (or first after a label/branch-target), immediately followed by a
  # dependent `cvt.*` OR FCC compare `c.{eq,lt,le}.s`. gas-2.96 has no pipeline
  # state there and inserts a spurious COP1-move hazard nop; the period assembler
  # / ROM leave the pair adjacent (verified universal: 840 ROM `mtc1;cvt` pairs
  # + 342 `mtc1;c.{eq,lt,le}.s` pairs, 0 carry a nop — the c.X.s case is a 0.0
  # operand `mtc1 $0,$fN` feeding a float compare, e.g. func_0025A968).
  # In-pipeline (seen==1) pairs are left alone — wrapping them would be a no-op
  # but the guard keeps the rewrite minimal. Byte no-op under the period as.
  if (nr==0 && ln[i] ~ /^[ \t]*mtc1[ \t]/) {
    j=i+1; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] ~ /^[ \t]*(cvt\.[swd]\.[swd]|c\.(eq|lt|le)\.[sd])[ \t]/) {
      m=j+1; while (m<=NR && ln[m] ~ /^[ \t]*(#|$)/) m++;
      if (m>NR || ln[m] !~ /^[ \t]*(b|j|beq|bne|beql|bnel|bgez|bgtz|blez|bltz|bc1)/) {
      print "\t.set noreorder"; print ln[i];
      for (k=i+1; k<j; k++) print ln[k];
      print ln[j]; print "\t.set reorder";
      nr=0; seen=0; i=j+1; continue }
      else if (ln[m] ~ /^[ \t]*b[ \t]/) {
        tgt=ln[m]; sub(/^[ \t]*b[ \t]+/,"",tgt); sub(/[ \t].*$/,"",tgt);
        slack=0;
        for (t=1; t<=NR; t++) { st=ln[t]; gsub(/[ \t]/,"",st);
          if (st==(tgt ":")) {
            u=t+1; while (u<=NR && (ln[u] ~ /^[ \t]*(#|\.|$)/ || ln[u] ~ /:[ \t]*$/)) u++;
            if (u<=NR && ln[u] ~ /^[ \t]*nop[ \t]*$/) slack=1;
            break } }
        if (slack) {
        print "\t.set noreorder"; print ln[i];
        for (k=i+1; k<j; k++) print ln[k];
        print ln[m]; print ln[j]; print "\t.set reorder";
        nr=0; seen=0; i=m+1; continue } } } }

  if (ln[i] !~ /^[ \t]*(#|\.|$)/) seen=1;
  print ln[i]; i++ } }' "${S}" > "${S}.mfc1nop" && mv "${S}.mfc1nop" "${S}"

# ee-as 2.96 fills a jr/j $31 delay slot with a preceding FP store (s.s/swc1),
# FP convert (cvt.*), or a quad/COP2 memory op (sq/sqc2/lqc2 — 0 of 48 such ROM
# returns are filled), and any return that directly follows an inline-asm block
# (past #NO_APP: 0 of 66 such ROM returns hold a COP2/quad op; the block's own
# trailing nop, if any, already fills it), but the R5900 FP→return hazard means the original
# assembler left a nop there (verified universal: 0 ROM funcs have cvt in a jr
# delay). Wrap such a return in .set noreorder + explicit nop. Universal
# assembler-adaptation.
# Compiled-code rule only: the SCE library objects under src/cod/vendor_* were not
# produced by ee-gcc, and libvu0 (vendor_25D410) carries sqc2 IN its return slots
# (26 sites); they keep the pre-2026-09-05 rule (FP store/convert on the literal previous line).
case "${SRC}" in *vendor_*) JRPAD_WIDE=0 ;; *) JRPAD_WIDE=1 ;; esac
awk -v wide="${JRPAD_WIDE}" '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*jr?[ \t]+\$31[ \t]*$/) && i>1 && ((ln[i-1] ~ /^[ \t]*(s\.s|swc1|cvt\.[swd]\.[swd])[ \t]/) || (wide==1 && ((ln[i-1] ~ /^[ \t]*(sqc2|lqc2|sq)[ \t]/) || (ln[i-1] ~ /^[ \t]*#NO_APP/ && i>2 && ln[i-2] !~ /^[ \t]*nop[ \t]*$/))))) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "${S}" > "${S}.jrfp" && mv "${S}.jrfp" "${S}"

# A `j <func>` TAIL CALL with a preceding unaligned store (sdl/sdr/swl/swr): ee-as
# 2.96 and modern-as both hoist that store into the j delay slot, but the original
# assembler left it nop (verified universal: 0 of 783 ROM tail-calls carry an
# unaligned store in the delay — see the assembler note above). Wrap the tail call in
# .set noreorder + explicit nop so the store stays BEFORE the j and the delay is
# nop — universally and per-FUNCTION (the `.set` pair is local), so it does NOT
# require switching the whole TU to ee-as (which regresses modern-as-matched
# siblings, e.g. fieldCollision). Assembler-parity, byte-correct everywhere.
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*j[ \t]+[A-Za-z_.]/) && i>1 && ln[i-1] ~ /^[ \t]*(sdl|sdr|swl|swr)[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "${S}" > "${S}.jtc" && mv "${S}.jtc" "${S}"


# ee-gcc emits `move $r,$s` for parameter-passing moves. ee-as 2.10
# encodes `move` as `daddu $r,$s,$0` (function code 0x2D); modern gas
# encodes `move` as `or $r,$s,$0` (function code 0x25). Original ELF
# uses daddu encoding. Force daddu explicitly so both assemblers agree.
sed -i -E 's/\bmove[[:space:]]+(\$[0-9a-zA-Z]+),[[:space:]]*(\$[0-9a-zA-Z]+)\b/daddu \1,\2,$0/g' "${S}"

# ee-gcc emits a single-operand `break 7` for its integer divide-by-zero
# trap. ee-as 2.10 puts that code in the LOW field (break 0,7 → 0x000001cd,
# the original ELF's encoding); modern gas puts a single operand in the HIGH
# field (0x0007000d). Rewrite to the explicit two-operand `break 0,N` so both
# assemblers emit the low-field encoding the ROM uses. (Already-explicit
# `break a,b` from INCLUDE_ASM'd .s has a comma and is left untouched.)
sed -i -E 's/\bbreak[[:space:]]+(0x[0-9a-fA-F]+|[0-9]+)[[:space:]]*$/break 0,\1/' "${S}"

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

# Assembler. There is exactly ONE, for every C TU: the period ee-as 2.9-991111.
# It is the ROM's contemporary assembler and leaves a jal/jr delay as `nop`
# where 2.96 / modern-as over-fill it with a preceding store. It rejects splat's
# `%gp_rel(SYM)($28)` spelling, so a MIXED TU (C + INCLUDE_ASM siblings) is first
# flattened + gp_rel-translated by preprocess_old_as.py (byte-identical GPREL16).
ASM_INPUT="${S}"
# ASSEMBLER DEFAULT = the period assembler EE_AS_OLD (ee-gcc 2.9-991111's `as`).
# This is the ROM's CONTEMPORARY assembler: it pairs with the 2.9-991111 COMPILER
# (EEGCC_DIR above) and leaves the jal/jr delay-slot NOPs that the later 2.96 and
# modern gas wrongly OVER-FILL with a preceding store. The whole aug6 ELF verifies
# byte-identical under it (proven 2026-06-04 — a full rebuild kept sha1 2b4d7de4).
# Do NOT reintroduce the 2.96/2.10 assembler as a default OR as a per-TU opt-in
# (config/use_as296.txt, tried and reverted 2026-08-05): it was a stale mismatch that
# forced per-func assembler bandaids and faked phantom jr-delay fills. The per-TU
# opt-in config/use_old_as.txt was retired 2026-09-04 — it selected the assembler
# that was already the default, so every entry was a no-op. There is NO modern-gas
# escape hatch: a TU that "genuinely needs modern gas" is a TU whose .s needs
# fixing, or a match that is really the assembler's delay-slot scheduling wearing
# a source's clothes. See decomp/NOTES.md "Assembler" section.
SELECTED_EE_AS="${EE_AS_OLD}"
# ONE ASSEMBLER, NO EXCEPTIONS. ee-as 2.9-991111 is the assembler BUNDLED WITH
# the compiler this build uses (EEGCC_DIR above is ee-gcc 2.9-991111), and that
# pairing is the whole argument for it. config/use_as296.txt — a per-TU opt-in to
# the 2.10-ee-001003-1 assembler bundled with the "2.96" toolchain — was tried on
# 2026-08-05 and REVERTED the same day: feeding one compiler's output to a
# different toolchain's assembler is a mismatched pairing, and "this TU used a
# different assembler than its own compiler" is far too weak a claim to hang a
# match on. Modern gas is likewise gone (see below). If a delay slot will not
# fill, that is a SOURCE-SHAPE problem to solve in C.
# Flatten INCLUDE_ASM siblings + translate splat's gp_rel spellings to the bare
# gp-addressable form the PERIOD assembler accepts, so the ROM's contemporary
# assembler (ee-as 2.9-991111) assembles mixed C+asm TUs
# directly instead of silently falling back to modern gas (which mis-encodes
# `la sdata` as daddiu where the ROM has addiu). See decomp/NOTES.md.
# stderr is NOT swallowed: preprocess_old_as.py is silent on success, and its
# `.lit4_slot` diagnostics (stale slot, non-FP reference) name the actual defect
# — hiding them leaves only the assembler's downstream "REJECTED" to go on.
if "${PYTHON}" "${ROOT}/tools/preprocess_old_as.py" "${S}" "${S}.pp"; then
    ASM_INPUT="${S}.pp"
fi

# THE PERIOD ASSEMBLER IS THE ONLY ASSEMBLER FOR C TUs. There is no modern-gas
# path here any more — no allowlist, no failure fallback. Retired 2026-08-05.
#
# WHY (do not reinstate either one):
#   Modern gas fills delay slots that ee-as 2.9-991111 leaves bare, so a TU that
#   reached it could "match" on the ASSEMBLER's scheduling rather than on source
#   shape. That produced 8 false matches (1 enemy, 2 Packet, 5 vendor_2418A0),
#   every one of which had to be reverted to INCLUDE_ASM on 2026-08-01 and
#   re-derived in C. A matching source shape provably exists for every ROM
#   function — the ROM was built by this toolchain — so an assembler swap is
#   never the answer, and having the path available at all makes it the first
#   thing a stuck matching run reaches for.
#
# If the period assembler rejects this TU, that is a REAL defect in the .s to be
# fixed at the source (past causes: splat's `enddlabel` leaving an `.ent`
# unclosed — fixed in include/labels.inc; the $ACC/$Q/$R sigil dialect, which
# preprocess_old_as.py now translates to the bare spelling). Hard-fail so ninja
# stops on it instead of silently producing an object from a different assembler.
# shellcheck disable=SC2086
if "${SELECTED_EE_AS}" ${EE_ASFLAGS} -I"${INCLUDE_DIR}" -o "${OUT}" "${ASM_INPUT}" 2>"${OUT}.aserr"; then
    rm -f "${OUT}.aserr"
    "${OBJCOPY}" "${OUT}" "${OUT}"
else
    echo "compile_c.sh: period assembler (ee-as 2.9-991111) REJECTED ${ASM_INPUT}" >&2
    grep -iE 'error' "${OUT}.aserr" | head -20 >&2 || head -20 "${OUT}.aserr" >&2
    rm -f "${OUT}.aserr" "${OUT}"
    echo "  This is a source defect to FIX, not an assembler to swap: there is no" >&2
    echo "  modern-gas fallback (retired 2026-08-05 — it manufactured 8 false" >&2
    echo "  delay-slot matches). See decomp/NOTES.md \"Assembler\"." >&2
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
# ROM's inter-TU function padding. See decomp/carve_ledger.md "Root cause".
"${OBJCOPY}" --set-section-alignment ".data=1" \
             --set-section-alignment ".bss=1" "${OUT}"

