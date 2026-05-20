#!/usr/bin/env bash
# tools/park.sh — move a failed match attempt into tough_nuts/<func>/.
#
# Usage:
#   tools/park.sh <vram> <reason...>
#
# Example:
#   tools/park.sh 0x14BB00 "mtc1->lw nop hazard inserted by gas reorder"
#
# Effect:
#   - Computes file_off = vram - 0x100000.
#   - Looks up the function name from asm/cod/*.s (glabel func_<vram>).
#   - Moves src/cod/<file_off>.c into tough_nuts/func_<vram>/<file_off>.c.
#   - Writes a tough_nuts/func_<vram>/notes.md with the reason and a
#     quick excerpt of the disassembly for permuter context.
#   - Reverts the yaml entry: flips c → asm and removes any size-fill
#     filler this attempt added.
#
# After parking, run `tools/build.sh setup && ninja` to confirm the
# build still round-trips (asm fallback). The permuter wrapper
# (tools/auto_permute*) will pick up the new tough_nuts seed on its
# next pass.

set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

if [[ $# -lt 2 ]]; then
    echo "usage: $0 <vram> <reason...>" >&2
    exit 2
fi

vram_in="$1"; shift
reason="$*"

# Normalize vram (allow 0x prefix, lowercase hex).
vram_dec=$(( vram_in ))
vram_hex=$(printf "%08X" "$vram_dec")
file_off=$(printf "%06X" $(( vram_dec - 0x100000 )))
fn_name="func_${vram_hex}"

src_file="src/cod/${file_off}.c"
nuts_dir="tough_nuts/${fn_name}"

if [[ ! -f "$src_file" ]]; then
    echo "park: $src_file not found (already reverted? try a different vram)" >&2
    exit 3
fi

# Size-match guard: a parked seed whose function compiles to a different
# .text size than the expected asm has zero permuter yield — permuter
# only mutates source, it can't shrink/grow the function body. Either
# the C structure is fundamentally wrong (e.g., wrong arg count, missing
# branch) or the wrong gcc emit path is being taken. Refuse to park.
# Bypass with FORCE_PARK=1 if you're sure (e.g., parking a strict subset
# of a larger function for later analysis).
if [[ "${FORCE_PARK:-0}" != "1" ]]; then
    expected_size=$(grep -E "^[ \t]*nonmatching ${fn_name}, 0x" "asm/matchings/cod/${file_off}/${fn_name}.s" 2>/dev/null \
                     | sed -E 's|.*, 0x([0-9A-Fa-f]+).*|\1|' | head -1)
    if [[ -z "$expected_size" ]]; then
        # Try segment .s file (some non-promoted subsegs)
        expected_size=$(grep -E "^[ \t]*nonmatching ${fn_name}, 0x" asm/cod/*.s 2>/dev/null \
                         | sed -E 's|.*, 0x([0-9A-Fa-f]+).*|\1|' | head -1)
    fi
    built_obj="build/src/cod/${file_off}.o"
    if [[ -f "$built_obj" && -n "$expected_size" ]]; then
        # Read .text size from the .o file (objdump -h gives hex 8-char size in col 3)
        built_size=$(mips-linux-gnu-objdump -h "$built_obj" 2>/dev/null \
                       | awk '/^ *[0-9]+ \.text /{print $3; exit}')
        if [[ -n "$built_size" ]]; then
            built_dec=$(( 16#$built_size ))
            expected_dec=$(( 16#$expected_size ))
            if [[ "$built_dec" -ne "$expected_dec" ]]; then
                echo "park: REFUSING — size mismatch (built=0x${built_size}, expected=0x${expected_size})" >&2
                echo "      permuter only mutates source, not .text size; fix the structure first." >&2
                echo "      Override with FORCE_PARK=1 if you're sure." >&2
                exit 4
            fi
        fi
    fi
fi

# Find the asm source for this function, for the notes.md excerpt.
asm_path=$(grep -l "glabel ${fn_name}\b" asm/cod/*.s 2>/dev/null | head -1 || true)
if [[ -z "$asm_path" ]]; then
    asm_excerpt="(no asm/cod/*.s found for ${fn_name}; check asm/matchings/cod/${file_off}/)"
else
    asm_excerpt=$(awk "/glabel ${fn_name}\$/,/endlabel/" "$asm_path")
fi

mkdir -p "$nuts_dir"

# Move seed (don't clobber an existing one without warning).
seed_dst="${nuts_dir}/${file_off}.c"
if [[ -f "$seed_dst" ]]; then
    echo "park: $seed_dst already exists; appending .new" >&2
    seed_dst="${seed_dst}.new"
fi
mv "$src_file" "$seed_dst"
echo "park: moved $src_file -> $seed_dst"

notes="${nuts_dir}/notes.md"
{
    if [[ ! -f "$notes" ]]; then
        echo "# ${fn_name} — parked"
        echo
        echo "VRAM: 0x${vram_hex} (file offset 0x${file_off})"
        echo "Asm source: ${asm_path:-(unknown)}"
        echo
    else
        echo
        echo "---"
        echo
    fi
    echo "## Attempt at $(date -u +%Y-%m-%d)"
    echo
    echo "**Reason parked:** ${reason}"
    echo
    echo "Seed: \`${seed_dst}\`"
    echo
    echo "Disassembly excerpt:"
    echo
    echo '```'
    echo "${asm_excerpt}"
    echo '```'
} >> "$notes"
echo "park: wrote notes -> $notes"

# Revert yaml: flip c -> asm and drop fill filler at file_off + size if
# present. We don't know the size precisely, but we can scan the yaml
# for the c entry and the immediately-following filler at the next
# 4-byte-aligned offset that we likely added.
yaml="config/ico.us.yaml"
if grep -q "      - \[0x${file_off}, c," "$yaml"; then
    sed -i -E "s|^      - \[0x${file_off}, c,.*$|      - [0x${file_off}, asm, cod/${file_off}]|" "$yaml"
    echo "park: flipped yaml entry 0x${file_off} c -> asm"
else
    echo "park: no yaml c entry for 0x${file_off}; leaving config alone"
fi

echo
echo "park: done. Next steps:"
echo "  tools/build.sh setup && ninja    # confirm asm fallback round-trips"
echo "  git add -A && git commit -m 'Park ${fn_name} — ${reason}'"
