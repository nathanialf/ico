#!/usr/bin/env bash
# build.sh: build a target's boot ELF from a clean clone in one command.
#
# The target is the one tools/ico_version.sh detects: VERSION=<slug>, or the
# first configured one (a config/link_order.<slug>.txt exists; pal on main),
# and so are the paths below. Its outputs are under build/<slug>/.
#
#   1. tools/setup.sh, when the toolchain under tools/cc/ or the venv is
#      missing. Then a check for mips-linux-gnu-objcopy, a host package.
#   2. tools/extract_elf.sh, when baserom/<slug>/baseelf.elf is missing. It
#      reads the user's own image of the target's disc: baserom/Ico_PAL.iso
#      on PAL, baserom/Ico_KOR.iso on the Korean disc and
#      baserom/Ico_JUN26.iso on the demo, a .bin and its .cue
#      (baserom/Ico_JPN.bin, Ico_USA.bin, Ico_AUG6.bin) on the others.
#   3. tools/build.sh setup when build.ninja is missing (delete build/<slug>/,
#      verify the base ELF and ROM SHA-1s, write build.ninja); otherwise
#      tools/build.sh verify, the SHA-1s alone, which also writes build.ninja
#      again when its first line names another target. build.ninja rewrites
#      itself when gen_ninja.py or its config inputs change.
#   4. ninja: compile, assemble, link, and run tools/check_elf.py --gate.
#      On a tree that is already built this does nothing but the gate.
#      ninja does not track header or .c.inc dependencies: after editing one,
#      run tools/build.sh clean (or setup) before ./build.sh. tools/build.sh
#      gate-all builds and gates every configured target.
#   5. Print check_elf's gate table once more, as the last thing on screen.
#
# Exits non-zero when any step fails. tools/build.sh keeps the individual
# subcommands (setup, regen, clean, distclean, progress).
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"

# shellcheck source=tools/ico_version.sh
. tools/ico_version.sh
ico_version_init "$ROOT"
DISC="$ICO_DISC"
CUE="$ICO_DISC_CUE"
BASEELF="$ICO_BASEELF"
NINJA=".venv/bin/ninja"

toolchain_ok() {
    [[ -x .venv/bin/python && -x "$NINJA" ]] &&
    [[ -x tools/cc/ee-gcc2.9-991111/ee-gcc ]] &&
    [[ -x tools/cc/ee-gcc2.96/bin/as ]] &&
    [[ -x tools/cc/binutils-2.10-ee/bin/ld ]] &&
    [[ -x tools/cc/dvp-as/bin/dvp-as ]]
}

if ! toolchain_ok; then
    echo "==> build.sh: toolchain incomplete, running tools/setup.sh"
    ICO_FROM_BUILD_SH=1 tools/setup.sh
    if ! toolchain_ok; then
        echo "build.sh: tools/setup.sh finished but the toolchain is still incomplete;" >&2
        echo "  see its output above (32-bit host libraries, network access)." >&2
        exit 1
    fi
fi

# The ROM view (build.ninja's rom rule) needs a host package setup.sh cannot
# install; say so before ninja fails on it.
if ! command -v mips-linux-gnu-objcopy >/dev/null 2>&1; then
    echo "build.sh: mips-linux-gnu-objcopy is not on PATH;" >&2
    echo "  install it (Debian/Ubuntu: sudo apt-get install binutils-mips-linux-gnu)." >&2
    exit 1
fi

if [[ ! -f "$BASEELF" ]]; then
    if [[ -z "$DISC" ]]; then
        echo "build.sh: $BASEELF is missing and target '$ICO_VERSION' has no disc recipe" >&2
        echo "  in tools/ico_version.sh; place the extracted files under $ICO_BASEROM_DIR/ by hand." >&2
        exit 1
    fi
    if [[ ! -f "$DISC" || ( -n "$CUE" && ! -f "$CUE" ) ]]; then
        if [[ -n "$CUE" ]]; then
            cat >&2 <<EOF
build.sh: $BASEELF is missing and there is no disc image to extract it from.
  Copy your own image of the $ICO_DISC_NAME, the .bin and its .cue,
  to $DISC and $CUE:
    mkdir -p baserom
    cp "/path/to/Ico ($ICO_DISC_WHERE).bin" $DISC
    cp "/path/to/Ico ($ICO_DISC_WHERE).cue" $CUE
  then run ./build.sh again. Nothing under baserom/ is ever committed.
EOF
        else
            cat >&2 <<EOF
build.sh: $BASEELF is missing and there is no disc image to extract it from.
  Copy your own image of the $ICO_DISC_NAME to $DISC:
    mkdir -p baserom
    cp "/path/to/Ico ($ICO_DISC_WHERE).iso" $DISC
  then run ./build.sh again. Nothing under baserom/ is ever committed.
EOF
        fi
        exit 1
    fi
    echo "==> build.sh: extracting the base ELF from $DISC"
    tools/extract_elf.sh
fi

if [[ -f build.ninja ]]; then
    tools/build.sh verify
else
    tools/build.sh setup
fi
"$NINJA"

echo
echo "==> build.sh: gate"
VERSION="$ICO_VERSION" .venv/bin/python tools/check_elf.py --gate --require-elf-sha
