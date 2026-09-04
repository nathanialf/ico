#!/usr/bin/env bash
# =============================================================================
# tools/quick_diff.sh <func_name>
#
# Version-generic: the target slug and the splat asm root come from
# tools/ico_version.sh — `main` = PAL retail (pal), `ntsc` = USA retail (us),
# `aug6` = the Aug-6-2001 prototype. Override with VERSION=<slug>.
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
FUNC="${1:-}"   # target func (coalesced TU); used for @func postprocess scoping

# Version-aware asm root, straight from the target yaml's `asm_path` option:
# the retail targets (us, pal) emit baselines to asm/, the aug6 prototype to
# asm/aug6/. Explicit VERSION env wins; else detected from which
# config/ico.<ver>.yaml this tree carries. See tools/ico_version.sh.
# shellcheck source=tools/ico_version.sh
. "$ROOT/tools/ico_version.sh"
ico_version_init "$ROOT"
VERSION="$ICO_VERSION"
ASM_ROOT="$ICO_ASM_ROOT"

# Resolve C source. Accept a full path/TU stem (e.g. sugipon/src/pool) directly,
# or a bare basename searched across the union of every target's source roots
# (retail us/pal: src ios sound isys; aug6: the per-programmer dev tree). The
# union is searched on every version — a bare name resolves to whatever exists.
CSRC=""
if [[ -f "$NAME.c" ]]; then
    CSRC="$NAME.c"                       # full dev-tree path: sugipon/src/pool
elif [[ -f "tough_nuts/$NAME/$NAME.c" ]]; then
    CSRC="tough_nuts/$NAME/$NAME.c"
else
    for _root in src ios sound isys \
                 common/src fumi/src fumi/ios fumi/sound fumi/isys \
                 sugipon/src seki/src omori/src script/src ito/src ito/mpeg; do
        if [[ -f "$_root/$NAME.c" ]]; then CSRC="$_root/$NAME.c"; break; fi
    done
fi
if [[ -z "$CSRC" ]]; then
    echo "quick_diff: no C source for '$NAME' (tried $NAME.c, tough_nuts/, and src/dev-tree roots)" >&2
    exit 3
fi

# Resolve target asm. Splat emits per-function baselines under
# asm/matchings/<yaml-subseg-name>/<func>.s when a subsegment is
# `[addr, c, name]`. Since the repo flattened src/ios/sound/isys to
# repo-root paths (yaml subsegs like `src/DmaPacket`), splat puts the
# asm at `asm/matchings/src/<TU>/`. We try a few shapes so the user
# can pass either the bare TU name (`layout_texture`) or the path
# (`src/layout_texture`).
CANDIDATES=(
    "$ASM_ROOT/matchings/$NAME"
    "$ASM_ROOT/matchings/src/$NAME"
    "$ASM_ROOT/matchings/sound/$NAME"
    "$ASM_ROOT/matchings/ios/$NAME"
    "$ASM_ROOT/matchings/isys/$NAME"
    "$ASM_ROOT/nonmatchings/$NAME"
    "$ASM_ROOT/nonmatchings/src/$NAME"
    "$ASM_ROOT/nonmatchings/sound/$NAME"
    "$ASM_ROOT/nonmatchings/ios/$NAME"
    "$ASM_ROOT/nonmatchings/isys/$NAME"
)
# When a specific func is requested, prefer the candidate dir that actually
# CONTAINS it — a stale gitignored layout dir (e.g. asm/matchings/<TU>/ left
# behind when the TU moved under asm/matchings/src/<TU>/) otherwise shadows the
# correct dir by sorting first, and the func is never found.
if [[ -n "${1:-}" ]]; then
    for candidate in "${CANDIDATES[@]}"; do
        if [[ -f "$candidate/$1.s" ]]; then
            ASM_DIR="$candidate"
            break
        fi
    done
fi
if [[ -z "${ASM_DIR:-}" ]]; then
    for candidate in "${CANDIDATES[@]}"; do
        if [[ -d "$candidate" ]]; then
            ASM_DIR="$candidate"
            break
        fi
    done
fi
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
            "$ASM_ROOT"/matchings/src/*) ALT_DIR="$ASM_ROOT/nonmatchings/src/${ASM_DIR#$ASM_ROOT/matchings/src/}" ;;
            "$ASM_ROOT"/matchings/*)     ALT_DIR="$ASM_ROOT/nonmatchings/${ASM_DIR#$ASM_ROOT/matchings/}" ;;
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
CFLAGS="${CFLAGS:--S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -Iinclude}"

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
# TUs that include a header under ito/include/ (e.g. mv_defs.h) must be compiled
# from a CWD one level below ROOT with a *relative* -I../ito/include so the
# baked __FILE__ literal reads "../ito/include/<h>" — exactly as compile_c.sh
# does (opt-in per TU via config/include_ito.txt). Keeps quick_diff in sync.
if grep -qxF "$NAME" "$ROOT/config/include_ito.txt" 2>/dev/null; then
    CSRC_ABS="$CSRC"; case "$CSRC_ABS" in /*) ;; *) CSRC_ABS="$ROOT/$CSRC_ABS";; esac
    ASM_ABS="$ASM_OUT"; case "$ASM_ABS" in /*) ;; *) ASM_ABS="$ROOT/$ASM_ABS";; esac
    ( cd "$ROOT/ito" && $CC $CFLAGS -I"$ROOT/include" -I../ito/include -o "$ASM_ABS" "$CSRC_ABS" )
else
    $CC $CFLAGS -o "$ASM_OUT" "$CSRC"
fi

# Stage 1b: run postprocesses listed in their gate files (match
# compile_c.sh pipeline). Only the per-file postprocesses; the always-on
# `move`→`daddu` translation is applied unconditionally.
qd_listed() {
    local txt="$ROOT/config/$1"
    [ -r "$txt" ] || return 1
    local base; base="$(basename "$NAME")"
    local line
    line="$(awk -v a="$NAME" -v b="$base" '($1==a||$1==b){print; exit}' "$txt")"
    [ -n "$line" ] || return 1
    # If the matched line carries `@func_<hex>` scoping tokens, it only counts
    # as "listed" when the func being diffed ($FUNC) is one of them — mirrors
    # tools/compile_c.sh's funcs_for so quick_diff and the build agree on which
    # funcs a postprocess touches. A line with no @func token = whole-TU.
    case "$line" in
        *@func_*) echo "$line" | grep -qE "@${FUNC}([[:space:]]|\$|#)" ;;
        *)        return 0 ;;
    esac
}
python3 "$ROOT/tools/postprocess_split_jtbls.py" "$ASM_OUT" || true
awk '
{ ln[NR]=$0 }
END { i=1; while (i<=NR) { print ln[i];
  if (ln[i] ~ /^[ \t]*c\.(lt|le|eq)\.[sd]([ \t]|$)/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] ~ /^[ \t]*\.set[ \t]+noreorder([ \t]|$)/) { print "\tnop"; i+=2; continue } }
  i++ } }' "$ASM_OUT" > "$ASM_OUT.fcc" && mv "$ASM_OUT.fcc" "$ASM_OUT"

# mfc1 COP1-move-out hazard: gcc emits `mfc1 $r,$f` + `#nop` comment + the
# dependent insn it scheduled into the slot. modern gas (the fallback for TUs
# whose VU0 siblings the period assembler can't parse, e.g. PObj) FILLS that slot
# with a spurious nop; the period assembler and the ROM leave mfc1+dependent
# adjacent. The `#nop` COMMENT marks the slot as filled (vs gcc's REAL nops which
# stay). Wrap in .set noreorder so modern gas does not insert the nop. Mirrors
# compile_c.sh; universal assembler-adaptation.
awk '
{ ln[NR]=$0 }
END { i=1; while (i<=NR) {
  if (ln[i] ~ /^[ \t]*mfc1[ \t]/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] !~ /^[ \t]*\./ && ln[j] !~ /:[ \t]*$/) {
      print "\t.set noreorder"; print ln[i]; print ln[j]; print "\t.set reorder";
      i=j+1; continue } }
  print ln[i]; i++ } }' "$ASM_OUT" > "$ASM_OUT.mfc1nop" && mv "$ASM_OUT.mfc1nop" "$ASM_OUT"

# mtc1 COP1-move-in hazard, marker-less variant: gcc emits `mtc1 $r,$f` directly
# followed by a dependent `cvt.*` OR FCC compare `c.{eq,lt,le}.s` with NO `#nop`
# marker (its machine model has no latency between the two). When that mtc1 is the
# FIRST real insn of a reorder region (or first after a label/branch target),
# gas-2.96 has no pipeline state and inserts a spurious COP1-move hazard nop; the
# period assembler / ROM leave the pair adjacent (verified universal: 840 ROM
# `mtc1;cvt` + 342 `mtc1;c.{eq,lt,le}.s` pairs, 0 carry a nop).
# In-pipeline (seen==1) pairs are untouched. Mirrors compile_c.sh.
awk '
{ ln[NR]=$0 }
END { nr=0; seen=0; i=1; while (i<=NR) {
  if (ln[i] ~ /\.set[ \t]+noreorder/) { nr=1; print ln[i]; i++; continue }
  if (ln[i] ~ /\.set[ \t]+reorder/)   { nr=0; seen=0; print ln[i]; i++; continue }
  if (ln[i] ~ /:[ \t]*$/)             { seen=0; print ln[i]; i++; continue }
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
  print ln[i]; i++ } }' "$ASM_OUT" > "$ASM_OUT.mtc1cvt" && mv "$ASM_OUT.mtc1cvt" "$ASM_OUT"

# ee-as 2.96 fills a jr/j $31 delay slot with a preceding FP store (s.s/swc1)
# or FP convert (cvt.*), but the R5900 FP→return hazard means the original
# assembler left a nop there (verified universal: 0 ROM funcs have cvt in a jr
# delay). Wrap such a return in .set noreorder + explicit nop. Universal
# assembler-adaptation.
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*jr?[ \t]+\$31[ \t]*$/) && i>1 && ln[i-1] ~ /^[ \t]*(s\.s|swc1|cvt\.[swd]\.[swd])[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "$ASM_OUT" > "$ASM_OUT.jrfp" && mv "$ASM_OUT.jrfp" "$ASM_OUT"

# `j <func>` tail-call with a preceding unaligned store (sdl/sdr/swl/swr): wrap in
# .set noreorder + nop so the store stays before the j and the delay is nop (ROM
# never carries the store in a tail-call delay). Mirrors compile_c.sh.
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*j[ \t]+[A-Za-z_.]/) && i>1 && ln[i-1] ~ /^[ \t]*(sdl|sdr|swl|swr)[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "$ASM_OUT" > "$ASM_OUT.jtc" && mv "$ASM_OUT.jtc" "$ASM_OUT"

# qd_listed is @func-aware, so this fires only for the func(s) the TU line scopes to.
sed -i -E 's/\bmove[[:space:]]+(\$[0-9a-zA-Z]+),[[:space:]]*(\$[0-9a-zA-Z]+)\b/daddu \1,\2,$0/g' "$ASM_OUT"
# ee-gcc's single-operand `break 7` (integer divide-by-zero trap) → explicit
# two-operand `break 0,7` so both ee-as and modern gas emit the ROM's
# low-field encoding (0x000001cd, not 0x0007000d). Matches compile_c.sh.
sed -i -E 's/\bbreak[[:space:]]+(0x[0-9a-fA-F]+|[0-9]+)[[:space:]]*$/break 0,\1/' "$ASM_OUT"
# COP1 cvt.w.s → identical .word: gas's r5900 (mips3) modern-as fallback rejects
# the mnemonic though the EE FPU implements it (ROM holds the raw COP1 encoding;
# splat emits the target side as .word too). Assembler parity, matches compile_c.sh.
python3 - "$ASM_OUT" <<'PYEOF'
import re, sys
p = sys.argv[1]; s = open(p).read()
def _repl(m):
    fd, fs = int(m.group(1)), int(m.group(2))
    return "\t.word 0x%08X" % (0x46000000 | (fs << 11) | (fd << 6) | 0x24)
s2 = re.sub(r"\tcvt\.w\.s\s+\$f(\d+)\s*,\s*\$f(\d+)\b", _repl, s)
if s2 != s:
    open(p, "w").write(s2)
PYEOF

# Stage 2: assemble. Prefer the project's ee-as 2.10 (matches the full
# build's src/.o pipeline so `move` pseudos expand consistently — modern
# mips-linux-gnu-as expands `move rd,rs` to `or`, ee-as expands to
# `daddu`, which would otherwise show up as spurious diffs). Fall back
# to mips-linux-gnu-as if ee-as rejects the input (typically on VU0/MMI
# ops it doesn't know).
EE_AS="$ROOT/tools/cc/ee-gcc2.9-991111/bin/as"
EE_ASFLAGS="-EL -mcpu=5900 -G 8 -I$ROOT/include"
# Honor config/use_old_as.txt (same as compile_c.sh): the rare TU whose ROM
# left a jr/j-delay nop that 2.96 over-fills is assembled with the less
# aggressive 2.9-991111. Without this, quick_diff/match_diff would show a
# PHANTOM delay-fill the real ninja build doesn't have. The canonical key is
# the TU BASENAME (what compile_c.sh's `listed` matches), but a full-path entry
# (`fumi/src/jimaku`) is accepted too — same dual-key rule as qd_listed above,
# so a single config line agrees across quick_diff AND the ninja build.
USE_OLD_AS_TXT="$ROOT/config/use_old_as.txt"
OLD_AS_SELECTED=0
if [[ -r "$USE_OLD_AS_TXT" ]] && \
   awk -v a="$NAME" -v b="$(basename "$NAME")" '($1==a||$1==b){f=1} END{exit !f}' "$USE_OLD_AS_TXT"; then
    EE_AS="$ROOT/tools/cc/ee-gcc2.9-991111/bin/as"
    OLD_AS_SELECTED=1
fi
# NO MODERN-GAS PATH. config/use_modern_as.txt and the silent failure fallback
# were both retired 2026-08-05 (see compile_c.sh for the full rationale): modern
# gas fills delay slots ee-as 2.9-991111 leaves bare, so anything reaching it can
# read as MATCHED on the assembler's scheduling instead of on source shape. That
# is how 8 functions were falsely matched and later reverted. This inner loop is
# run hundreds of times per matching round, so a fallback here is the most
# dangerous of all — it silently disagrees with the ninja build.

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
    # THE ONLY assembler = the period assembler (ee-gcc 2.9-991111's `as`), the ROM's
    # contemporary assembler — it matches the 2.9-991111 COMPILER and leaves the
    # jal/jr delay-slot NOPs that 2.96 / modern-as wrongly over-fill (e.g.
    # debug_TargetGObj_Func). It rejects splat's %gp_rel spelling + reg aliases,
    # so flatten+translate the .s first (byte-identical GPREL16) — UNCONDITIONALLY,
    # exactly as compile_c.sh does, so quick_diff and the ninja build agree.
    # Do NOT reinstate a bare-2.96 default path: that silently fell back to modern
    # gas and faked phantom delay-fills the real build never had. (use_old_as.txt
    # is now redundant — the period assembler IS the default.)
    #
    # HARD-FAIL, never fall back. The old `2>/dev/null` + trailing modern-gas call
    # meant a period-assembler rejection (e.g. an untranslated $ACC/$Q/$R) silently
    # produced an object from a DIFFERENT assembler, and the diff shown was then
    # not the diff ninja would see. Errors are surfaced, not swallowed.
    if [[ ! -x "$EE_AS" ]]; then
        echo "quick_diff: period assembler missing at $EE_AS" >&2
        echo "  run ./tools/setup.sh — there is no modern-gas fallback" >&2
        return 1
    fi
    python3 "$ROOT/tools/preprocess_old_as.py" "$in" "$in.oldas" \
        && canon_regnames "$in.oldas" \
        && "$EE_AS" $EE_ASFLAGS -o "$out" "$in.oldas" && return 0
    echo "quick_diff: period assembler (ee-as 2.9-991111) REJECTED $in.oldas" >&2
    echo "  Fix the source/.s — there is no modern-gas fallback (retired" >&2
    echo "  2026-08-05; it manufactured 8 false delay-slot matches)." >&2
    return 1
}

# Canonicalize C-side inline-asm VU0 special registers ($ACC/$Q/$R from
# include/vu0.h) to the period assembler's BARE spelling — UNCONDITIONALLY, as
# compile_c.sh does. This is what keeps a VU0-using candidate assembling at all:
# untranslated, it fails the period assembler, which now hard-errors instead of
# silently falling back to modern gas and disagreeing with the ninja build.
sed -i -E -e 's/\$ACC\b/ACC/g' -e 's/\$Q\b/Q/g' -e 's/\$R\b/R/g' "$ASM_OUT"
canon_regnames "$ASM_OUT"
assemble "$OBJ" "$ASM_OUT"

# Canonicalize both sides via the same objdump so the diff is meaningful.
# splat's per-function .s files don't .include the label macros themselves, so
# we prepend them to a temp copy.
#
# labels.inc, NOT macro.inc: macro.inc is the MODERN-gas spelling (`.internal`,
# and `"\label"` argument substitution inside quotes) which ee-as 2.9-991111
# cannot parse. Prepending it made the TARGET side fail the period assembler on
# every macro-using .s and silently fall through to the old modern-gas fallback
# — so the reference bytes quick_diff diffed against came from an assembler the
# real build never uses. labels.inc is the period-assembler twin of the same
# macros (the real build's flattened INCLUDE_ASM path uses it). Fixed 2026-08-05
# alongside retiring the fallback that was hiding this.
TARGET_OBJ="build/quick_diff/$NAME.target.o"
TARGET_ASM_WRAPPED="build/quick_diff/$NAME.target.s"
{
    echo '.include "labels.inc"'
    echo '.set noreorder'
    echo '.set noat'
    cat "$TARGET_ASM"
} > "$TARGET_ASM_WRAPPED"
canon_regnames "$TARGET_ASM_WRAPPED"
# Rewrite splat's la-pseudo gp_rel form `(D_X)` (no base reg) into the
# explicit `%gp_rel(D_X)($gp)` form so modern-as doesn't try $at under
# .set noat. The trailing `/* gp_rel: (D_X) */` marker tells us splat
# already verified this symbol is gp-addressable.
sed -i -E 's|,[[:space:]]*\((D_[0-9A-Fa-f]+)\)[[:space:]]*/\*[[:space:]]*gp_rel:|, %gp_rel(\1)($28) /* gp_rel:|g' "$TARGET_ASM_WRAPPED"
assemble "$TARGET_OBJ" "$TARGET_ASM_WRAPPED"

LEFT=$(mktemp); RIGHT=$(mktemp)
trap 'rm -f "$LEFT" "$RIGHT"' EXIT

# Pipe each through objdump → strip leading addr / opcode columns → keep
# only the mnemonic + operand columns. Tabs delimit; columns 3+ are the
# instruction text.
# -z (--disassemble-zeroes): WITHOUT it, objdump collapses any run of >=3
# identical instructions (e.g. padding nops) to a single '...' line, which the
# sed below drops (no addr/hex prefix) -> the collapsed instructions VANISH from
# the compared stream, FALSE-PASSING a function whose built/expected sizes differ
# only by such a run (e.g. for(;;) padding -> phantom rc0, ninja MISMATCH). -z
# emits every instruction so the diff is faithful. (Investigated via func_001AACF4, 2026-06-04.)
canon() {
    # objdump lines have shape:  "  ADDR:\tHEXBYTES\tMNEMONIC\tOPERANDS"
    # Strip leading whitespace + addr+colon + hex bytes; keep the rest.
    "$OBJDUMP" -dz -M no-aliases "$1" 2>/dev/null \
        | sed -nE 's/^[[:space:]]*[0-9a-f]+:[[:space:]]+[0-9a-f]+[[:space:]]+//p'
}
# For multi-function .o files (coalesced TUs), --disassemble=<func> limits
# the dump to just the requested function. Use the 2nd arg as the symbol
# name when present; fall back to whole-file dump (single-function .c).
canon_func() {
    local obj="$1" fn="${2:-}"
    if [[ -n "$fn" ]]; then
        "$OBJDUMP" -dz -M no-aliases --disassemble="$fn" "$obj" 2>/dev/null \
            | sed -nE 's/^[[:space:]]*[0-9a-f]+:[[:space:]]+[0-9a-f]+[[:space:]]+//p'
    else
        canon "$obj"
    fi
}
# Isolate the requested function in the (coalesced) built .o. Retail (us, pal)
# funcs not yet named carry splat's func_<hex>; the aug6 prototype tree uses the
# dev's REAL symbol names (from MAIN.MAP), and named retail funcs exist too, so
# gating isolation on `func_*` would dump the whole TU object
# against a single-func expected .s (thousands of phantom diffs). Whenever a
# specific func is requested (match_diff/match_loop always pass it, and so does
# the agent for coalesced TUs), isolate to THAT symbol regardless of its name.
TGT_FN=""
if [[ -n "${1:-}" ]]; then
    TGT_FN="$1"
else
    case "$TARGET_ASM" in
        */func_*.s) TGT_FN="$(basename "$TARGET_ASM" .s)" ;;
    esac
fi
canon_func "$TARGET_OBJ" "$TGT_FN" > "$RIGHT"
canon_func "$OBJ"        "$TGT_FN" > "$LEFT"

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
    # Tag the diff against known cookbook anti-patterns and surface
    # which postprocess / C reformulation likely applies. See
    # tools/tag_diff.py RULES list. Quiet when no rule fires.
    HINTS=$("$ROOT/.venv/bin/python" "$ROOT/tools/tag_diff.py" "$RIGHT" "$LEFT" 2>/dev/null || true)
    if [[ -n "$HINTS" ]]; then
        echo
        echo "=== tag_diff hints ==="
        echo "$HINTS"
    fi
fi
