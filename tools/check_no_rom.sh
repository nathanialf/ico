#!/usr/bin/env bash
# =============================================================================
# check_no_rom.sh
#
# IP-safety scan. Refuses to let disc data, extracted assets, or other
# IP-tainted files slip into a commit. Run before pushing; the pre-commit
# hook runs it on staged files.
#
# Heuristics (intentionally conservative: false positives are fine, false
# negatives are not):
#
#   1. File extensions associated with PS2 disc dumps and extracted assets.
#   2. PS2 boot-ELF naming patterns (SLUS-/SLES-/SLPS-/SLPM-/SCUS-/...), the
#      discs' reference files (MAIN.MAP, SRCFILE.TXT, TRFILE.TXT,
#      TRTABLE.BIN, SYSTEM.CNF), which docs/LEGAL.md keeps out of the tree,
#      and the names the tools give the user's disc images (Ico_PAL.*,
#      Ico_JPN.*, Ico_USA.*, Ico_AUG6.*, Ico_JUN26.*) whatever their extension.
#   3. Any tracked file > 256 KiB (C sources under ico2/ and sce/: 8 MiB),
#      except the named text files below.
#   4. ELF magic (\x7fELF) sniff regardless of extension.
#   5. Raw byte-array initializers in tracked C and in a stub list.
#   6. Any file whose path matches our gitignore patterns but is somehow
#      tracked anyway.
#   7. A stub tools/gen_stub_s.py writes from the base ELF (build/<slug>/stubs/,
#      caught by 6 where it lies) copied into a tracked source or a stub
#      list: its header line, or a run of four or more hex .word/.half/.byte
#      lines.
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
disc_file_re='(^|/)(MAIN\.MAP|SRCFILE\.TXT|TRFILE\.TXT|TRTABLE\.BIN|SYSTEM\.CNF)$'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    if [[ "${f^^}" =~ $disc_file_re ]]; then
        note "disc reference file: $f"
    fi
done
# The extension rule above already refuses .iso, .bin and .cue; this one
# also refuses a renamed copy or a cooked cache under another extension.
disc_image_re='(^|/)ICO_(PAL|JPN|USA|AUG6|JUN26)\.[^/]*$'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    if [[ "${f^^}" =~ $disc_image_re ]]; then
        note "disc image name: $f"
    fi
done

# --- 3. size cap ---
# Non-source files keep the tight 256 KiB cap (catches stray binary/asset
# dumps). Tracked C source (ico2/ and sce/ *.c/*.h/*.c.inc) gets a
# higher 8 MiB ceiling: some TUs hold their data as typed C (word arrays,
# strings, structs), which pushes them past 256 KiB. Their CONTENT is still
# gated by rule #5 below (raw byte-array dumps banned), so a large .c is
# typed source, not laundered ROM. The 8 MiB ceiling stays as a backstop.
src_large_re='^(ico2|sce)/.*\.(c|h|c\.inc|inc)$'
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    # Symbol-address files (config/symbol_addrs.<ver>.txt) are
    # `Name = 0xADDR; // type:func` declarations, no byte data. The aug6 and
    # PAL ones are large (>256 KiB) only because those builds are fully named
    # from a disc-shipped MAIN.MAP (5k+ functions), unlike a target whose
    # disc ships no map. Format-verified text, not laundered ROM; exempt the
    # size cap (content is still subject to the byte-array rules below).
    case "$f" in config/symbol_addrs.*.txt) continue ;; esac
    # A stub list (config/stubs.<ver>.txt) is rows of a section, a name, two
    # addresses, a TU and tokens, with comments: no byte data, since
    # tools/gen_stub_s.py writes the bytes from the user's own base ELF at
    # build time. A target campaign seeded from correlate_elf.py lists every
    # function its tree does not yet build (1300 to 2900 rows with their
    # literal rows), which passes 256 KiB. Format-verified text; exempt the
    # size cap (rules 5 and 7 still read it: a stub list never carries a
    # byte array or a .word run).
    case "$f" in config/stubs.*.txt) continue ;; esac
    # config/ico.<ver>.yaml is a posterity record read by nothing: address
    # rows and their per-row reasoning comments, no byte data (the comments
    # pushed it past 256 KiB).
    case "$f" in config/ico.*.yaml) continue ;; esac
    # docs/<slug>/progress.json is the GitHub Pages dashboard's data, generated by
    # tools/check_elf.py --progress from the built ELF and the link map. It
    # holds only function names, addresses and integer byte counts, no ROM
    # bytes. Large (>256 KiB)
    # only because a fully-named build has 5k+ functions. Content is still
    # subject to the byte-array rules below; exempt the size cap.
    case "$f" in docs/*/progress.json) continue ;; esac
    size=$(wc -c < "$f")
    if [[ "$f" =~ $src_large_re ]]; then
        if (( size > 8388608 )); then
            note "tracked source >8MiB (suspicious): $f ($size bytes)"
        fi
    elif (( size > 262144 )); then
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

# --- 5. raw byte-array initializers in tracked C ---
# An `unsigned char D_<VMA>[N] = { 0x..., ... }` initializer is raw bytes
# from the original ELF, not a developer reconstruction. Tracked C under
# ico2/ and sce/ uses TYPED forms (string literals, ints, floats, named
# pointer arrays, struct literals); a byte-array initializer fails the
# commit, so the bytes are never laundered into the tracked tree. (The
# data-only members are generated at build time instead, from the user's own
# disc: tools/gen_data_c.py.)
#
# The match is on the byte-array SHAPE itself, with an
# `__attribute__((section(...)))` prefix OPTIONAL: a plain
# `unsigned char D_X[N] = { 0xAB, 0xCD, ... }` is just as much a raw dump.
# The shape requires the first brace element to be a hex byte AND at least
# one comma (>=2 elements), so the legitimate typed forms all pass:
#   - all-zero `{ 0 };`        (no comma, never matches)
#   - strings `= "...";`       (no brace, never matches)
#   - word/short `unsigned int D_X[N] = { 0x.., .. }`  (non-byte type)
#   - struct/typedef arrays    (non-byte type)
byte_type_re='(unsigned[[:space:]]+char|signed[[:space:]]+char|char|uint8_t|int8_t|u8|s8)'
attr_opt_re='(__attribute__[[:space:]]*\(\([[:space:]]*section[[:space:]]*\([[:space:]]*"\.\w+\.0x[0-9A-Fa-f]+"[[:space:]]*\)[[:space:]]*\)\)[[:space:]]+)?'
raw_byte_re="^[[:space:]]*${attr_opt_re}(const[[:space:]]+)?${byte_type_re}[[:space:]]+D_[0-9A-Fa-f]{8}[[:space:]]*\[[0-9]+\][[:space:]]*=[[:space:]]*\{[[:space:]]*0x[0-9A-Fa-f]{1,2}[[:space:]]*,[^}]*\}"
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    # Only tracked C under ico2/ and sce/, and the stub lists.
    case "$f" in
        ico2/*.c|ico2/*.c.inc|sce/*.c|config/stubs.*.txt) ;;
        *) continue ;;
    esac
    if grep -nE "${raw_byte_re}" "$f" >/dev/null 2>&1; then
        note "raw byte-array initializer in tracked source: $f"
        note "  ICO data sections must be typed (string literal / int / float /"
        note "  named pointer array / struct), not raw bytes. See docs/LEGAL.md."
        grep -nE "${raw_byte_re}" "$f" 2>&1 | head -3 >&2
    fi
done

# --- 6. gitignore-tracked anomalies ---
while IFS= read -r f; do
    [[ -z "$f" ]] && continue
    if git check-ignore -q "$f" 2>/dev/null; then
        note "tracked file matches .gitignore: $f"
    fi
done < <(printf "%s\n" "${files[@]}")

# --- 7. generated stubs in tracked sources ---
# build/<slug>/stubs/<name>.s holds base-ELF bytes as hex directives; no tracked
# source carries even one such line, so a run of four is a copied stub.
for f in "${files[@]}"; do
    [[ -z "$f" ]] && continue
    [[ ! -f "$f" ]] && continue
    case "$f" in *.s|*.S|*.c|*.h|*.inc|*.dsm|*.vsm|config/stubs.*.txt) ;; *) continue ;; esac
    if grep -q 'generated by tools/gen_stub_s\.py' "$f"; then
        note "generated stub in a tracked file: $f"
    elif awk '/^[[:space:]]*\.(word|half|byte)[[:space:]]+0x/{if(++c>=4)hit=1;next}{c=0}END{exit !hit}' "$f"; then
        note "run of hex .word/.half/.byte lines (a stub from the base ELF?): $f"
    fi
done

if (( bad )); then
    echo "" >&2
    echo "IP-safety scan FAILED. See messages above." >&2
    echo "If a hit is a false positive, document why and consider tightening" >&2
    echo "allowlists in tools/check_no_rom.sh rather than removing the check." >&2
    exit 1
fi

echo "check_no_rom: OK (${#files[@]} files scanned)"
