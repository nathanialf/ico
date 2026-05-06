#!/usr/bin/env bash
# =============================================================================
# tools/extract_elf.sh
#
# Extracts the EE-side boot ELF (SLUS_202.18) from the user's ICO disc image
# at baserom/Ico_USA.bin / .cue, writes it to baserom/baseelf.elf, and
# records its SHA-1 to config/sha1sums.txt (creating the entry on first run,
# verifying against existing entry on subsequent runs).
#
# Reads no copyrighted material into the repository — the ELF lives under
# baserom/, which is gitignored.
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

BIN="baserom/Ico_USA.bin"
CUE="baserom/Ico_USA.cue"
ELF="baserom/baseelf.elf"
ISO="baserom/Ico_USA.iso"
SHA1SUMS="config/sha1sums.txt"
EXPECTED_BOOT="SLUS_202.18"

if [[ ! -f "$BIN" ]]; then
    echo "extract_elf: missing $BIN" >&2
    echo "  Copy your disc image:" >&2
    echo "    cp '/path/to/Ico (USA).bin'  $BIN" >&2
    echo "    cp '/path/to/Ico (USA).cue'  $CUE" >&2
    exit 1
fi
if [[ ! -f "$CUE" ]]; then
    echo "extract_elf: missing $CUE" >&2
    exit 1
fi

# --- 1. .bin/.cue -> .iso (data track only) ----------------------------------

if [[ ! -f "$ISO" ]]; then
    if command -v bchunk >/dev/null 2>&1; then
        echo "==> bchunk: extracting data track to $ISO"
        ( cd baserom && bchunk -v "Ico_USA.bin" "Ico_USA.cue" "Ico_USA_track" )
        # bchunk writes Ico_USA_track01.iso for the first track on a single-track
        # data disc.
        if [[ -f baserom/Ico_USA_track01.iso ]]; then
            mv baserom/Ico_USA_track01.iso "$ISO"
        fi
    else
        echo "==> bchunk not installed; treating .bin as raw ISO9660"
        ln -sf "$(basename "$BIN")" "$ISO"
    fi
fi

# --- 2. Pull SLUS_202.18 from the ISO9660 filesystem -------------------------

if [[ ! -f "$ELF" ]]; then
    echo "==> extracting $EXPECTED_BOOT from $ISO"
    if command -v isoinfo >/dev/null 2>&1; then
        isoinfo -i "$ISO" -x "/${EXPECTED_BOOT};1" > "$ELF"
    elif command -v 7z >/dev/null 2>&1; then
        ( cd baserom && 7z e -y "$(basename "$ISO")" "$EXPECTED_BOOT" >/dev/null )
        if [[ -f "baserom/$EXPECTED_BOOT" ]]; then
            mv "baserom/$EXPECTED_BOOT" "$ELF"
        fi
    else
        echo "extract_elf: neither isoinfo nor 7z available — install one of:" >&2
        echo "  apt-get install genisoimage  (provides isoinfo)" >&2
        echo "  apt-get install p7zip-full   (provides 7z)" >&2
        exit 2
    fi
fi

if [[ ! -s "$ELF" ]]; then
    echo "extract_elf: extraction produced empty $ELF" >&2
    exit 3
fi

# --- 3. SHA-1 record / verify ------------------------------------------------

CURRENT_SHA1=$(sha1sum "$ELF" | awk '{print $1}')
echo "==> ELF SHA-1: $CURRENT_SHA1"

EXISTING=$(grep -E "^[0-9a-f]{40}\s+baseelf\.elf$" "$SHA1SUMS" 2>/dev/null | awk '{print $1}' || true)

if [[ -z "$EXISTING" ]]; then
    echo "==> recording SHA-1 in $SHA1SUMS"
    {
        grep -v "baseelf.elf" "$SHA1SUMS" 2>/dev/null || true
        echo "$CURRENT_SHA1  baseelf.elf"
    } > "$SHA1SUMS.tmp"
    mv "$SHA1SUMS.tmp" "$SHA1SUMS"
elif [[ "$EXISTING" != "$CURRENT_SHA1" ]]; then
    echo "extract_elf: SHA-1 mismatch!" >&2
    echo "  recorded: $EXISTING" >&2
    echo "  actual:   $CURRENT_SHA1" >&2
    echo "" >&2
    echo "Either your disc image is a different revision, or the recorded" >&2
    echo "hash is wrong. Do not blindly update $SHA1SUMS — consult the" >&2
    echo "maintainer first." >&2
    exit 4
else
    echo "==> SHA-1 matches recorded value"
fi

# --- 4. Inspect .comment for compiler fingerprint hint -----------------------

if command -v mips64r5900el-ps2-elf-objdump >/dev/null 2>&1; then
    OBJDUMP=mips64r5900el-ps2-elf-objdump
elif command -v mips-linux-gnu-objdump >/dev/null 2>&1; then
    OBJDUMP=mips-linux-gnu-objdump
else
    OBJDUMP=
fi

if [[ -n "$OBJDUMP" ]]; then
    echo
    echo "==> .comment section (compiler fingerprint hint):"
    "$OBJDUMP" -s -j .comment "$ELF" 2>/dev/null | head -20 || \
        echo "  (no .comment section or objdump can't parse the ELF)"
    echo
fi

echo "extract_elf: done. ELF at $ELF"
