#!/usr/bin/env bash
# =============================================================================
# check_no_rom.sh
#
# IP-safety scan. Refuses to let disc data, extracted assets, or other
# IP-tainted files slip into a commit. Run before pushing; the pre-commit
# hook runs it on staged files.
#
# Heuristics (intentionally conservative — false positives are fine, false
# negatives are not):
#
#   1. File extensions associated with PS2 disc dumps and extracted assets.
#   2. PS2 boot-ELF naming patterns (SLUS-/SLES-/SLPS-/SLPM-/SCUS-/...).
#   3. Any tracked file > 256 KiB that is not in an allowlisted directory.
#   4. ELF magic (\x7fELF) sniff regardless of extension.
#   5. Any file whose path matches our gitignore patterns but is somehow
#      tracked anyway.
#
# Exit non-zero on any hit.
# =============================================================================
set -euo pipefail

# Files to inspect: staged ones if running pre-commit, otherwise everything
# tracked by git. Override with FILES env var for ad-hoc scans.
if [[ -n "${FILES:-}" ]]; then
    mapfile -t files < <(printf "%s\n" "$FILES" | tr ' ' '\n')
elif git diff --cached --name-only --quiet 2>/dev/null; then
    mapfile -t files < <(git ls-files)
else
    mapfile -t files < <(git diff --cached --name-only --diff-filter=ACMR)
fi

bad=0
note() { echo "check_no_rom: $*" >&2; bad=1; }

# --- 1. extension blocklist ---
ext_block_re='\.(bin|iso|cue|chd|mdf|mds|nrg|elf|irx|aifc|aiff|wav|adp|vag|vab|mid|seq|tm2|rgba16|rgba32|sym\.bak)$'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    if [[ "$f" =~ $ext_block_re ]]; then
        note "blocked extension: $f"
    fi
done

# --- 2. PS2 boot-ELF naming patterns ---
ps2_boot_re='(^|/)(SLUS|SLES|SLPS|SLPM|SCUS|SCES|SCPS|PBPX)[-_][0-9A-Za-z._]+'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    if [[ "$f" =~ $ps2_boot_re ]]; then
        note "PS2 boot-ELF naming: $f"
    fi
done

# --- 3. size cap outside allowlisted dirs ---
allow_large_re='^(tools/toolchain/|tools/ghidra/|\.git/|lib/)'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    if [[ "$f" =~ $allow_large_re ]]; then continue; fi
    size=$(wc -c < "$f")
    if (( size > 262144 )); then
        note "tracked file >256KiB (suspicious): $f ($size bytes)"
    fi
done

# --- 4. ELF magic sniff ---
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    head4=$(head -c 4 "$f" 2>/dev/null | od -An -tx1 -N4 | tr -d ' \n' || true)
    if [[ "$head4" == "7f454c46" ]]; then
        note "file starts with ELF magic: $f"
    fi
done

# --- 5. raw byte-array initializers in tracked src/ ---
# The auto-generated `src/<TU>_data.c` sidecars (gitignored) emit
# `__attribute__((section(".X.0xVMA"))) unsigned char D_<VMA>[N] = { 0x..., ... }`
# — that's raw bytes from the original ELF, not a developer reconstruction.
# Tracked `src/**/*.c` must use TYPED forms (string literals, ints, floats,
# named pointer arrays, struct literals). If a hand-promoted file slips in
# a byte-array initializer, fail the commit — the bytes shouldn't be
# laundered into the tracked tree by changing only the filename.
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    # Only check tracked src/ .c files; skip gitignored *_data.c sidecars
    # (those are expected to be raw bytes) and anything outside src/.
    case "$f" in
        src/*.c) ;;
        *) continue ;;
    esac
    case "$f" in
        */[!/]*_data.c|*_data.c) continue ;;
    esac
    # Detect `(unsigned char|char|uint8_t|u8|s8|int8_t) D_<8hex>[<N>] = { ... , ... }`
    # in a per-VMA section. Word-typed initializers (`int D_X[2] = { 0x80, 0 }`)
    # are fine — they're typed reconstructions. Byte arrays with multiple
    # brace-init elements are the migrator's raw-bytes shape.
    byte_type_re='(unsigned[[:space:]]+char|signed[[:space:]]+char|char|uint8_t|int8_t|u8|s8)'
    if grep -nE "__attribute__[[:space:]]*\(\([[:space:]]*section[[:space:]]*\([[:space:]]*\"\.\w+\.0x[0-9A-Fa-f]+\"[[:space:]]*\)[[:space:]]*\)\)[[:space:]]+(const[[:space:]]+)?${byte_type_re}[[:space:]]+D_[0-9A-Fa-f]{8}[[:space:]]*\[[0-9]+\][[:space:]]*=[[:space:]]*\{[^}]*,[^}]*\}" "$f" >/dev/null 2>&1; then
        note "raw byte-array initializer in tracked source: $f"
        note "  ICO data sections must be typed (string literal / int / float /"
        note "  named pointer array / struct), not raw bytes. See decomp/MATCH_DATA.md."
        grep -nE "__attribute__[[:space:]]*\(\([[:space:]]*section[[:space:]]*\([[:space:]]*\"\.\w+\.0x[0-9A-Fa-f]+\"[[:space:]]*\)[[:space:]]*\)\)[[:space:]]+(const[[:space:]]+)?${byte_type_re}[[:space:]]+D_[0-9A-Fa-f]{8}[[:space:]]*\[[0-9]+\][[:space:]]*=[[:space:]]*\{[^}]*,[^}]*\}" "$f" 2>&1 | head -3 >&2
    fi
done

# --- 6. gitignore-tracked anomalies ---
while IFS= read -r f; do
    [[ -z "$f" ]] && continue
    if git check-ignore -q "$f" 2>/dev/null; then
        note "tracked file matches .gitignore: $f"
    fi
done < <(printf "%s\n" "${files[@]}")

if (( bad )); then
    echo "" >&2
    echo "IP-safety scan FAILED. See messages above." >&2
    echo "If a hit is a false positive, document why and consider tightening" >&2
    echo "allowlists in tools/check_no_rom.sh rather than removing the check." >&2
    exit 1
fi

echo "check_no_rom: OK (${#files[@]} files scanned)"
