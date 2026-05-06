#!/usr/bin/env bash
# =============================================================================
# tools/setup.sh
#
# One-shot host setup. Idempotent — running it twice is fine.
#
#   1. Create a Python venv at .venv and install tools/requirements.txt.
#   2. Initialize / update git submodules (splat, asm-differ, decomp-permuter,
#      m2c).
#   3. Install m2c into the venv (editable).
#   4. Set up the EE toolchain (system binary detection → Docker → source).
#   5. Fetch a pinned Ghidra release into tools/ghidra/.
#   6. Best-effort install pcsx2.
#   7. Install the IP-safety pre-commit hook.
#
# This script downloads no disc data, no assets, and no ICO-specific files.
# Everything pulled is from open-source projects (ps2dev, ghidra, etc.) used
# across many PS2 reverse-engineering projects.
#
# Skip flags:
#   SKIP_TOOLCHAIN=1   skip step 4
#   SKIP_GHIDRA=1      skip step 5
#   SKIP_PCSX2=1       skip step 6
# =============================================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

PYTHON="${PYTHON:-python3}"
VENV="${VENV:-.venv}"

echo "==> ico setup at $ROOT"

# --- 1. Python venv ----------------------------------------------------------

if [[ ! -d "$VENV" ]]; then
    echo "==> creating venv at $VENV"
    "$PYTHON" -m venv "$VENV"
fi
# shellcheck disable=SC1091
source "$VENV/bin/activate"
python -m pip install --upgrade pip >/dev/null
python -m pip install -r tools/requirements.txt

# --- 2. Submodules -----------------------------------------------------------

if [[ -d .git ]] && [[ -f .gitmodules ]]; then
    echo "==> updating submodules"
    git submodule update --init --recursive
elif [[ -d .git ]]; then
    echo "==> no .gitmodules yet (skipping submodule init)"
else
    echo "==> not a git repo yet; run 'git init' first (skipping submodules)"
fi

# --- 3. m2c (editable install) -----------------------------------------------

if [[ -d lib/m2c ]] && [[ -f lib/m2c/setup.py || -f lib/m2c/pyproject.toml ]]; then
    echo "==> installing m2c (editable)"
    python -m pip install -e lib/m2c
elif [[ -d lib/m2c ]]; then
    echo "==> lib/m2c present but no setup.py/pyproject.toml; skipping pip install"
else
    echo "==> lib/m2c missing; add as submodule then re-run"
fi

# --- 4. EE GCC 2.96 (matching compiler — same source as SOTC and other PS2 decomps) ----

EEGCC_DIR="$ROOT/tools/cc/ee-gcc2.96"
EEGCC_BIN="$EEGCC_DIR/bin/gcc"
EEGCC_TARBALL_URL="${EEGCC_TARBALL_URL:-https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.96.tar.xz}"

if [[ "${SKIP_TOOLCHAIN:-0}" == "1" ]]; then
    echo "==> SKIP_TOOLCHAIN=1; not fetching ee-gcc2.96"
elif [[ -f "$EEGCC_BIN" ]]; then
    echo "==> ee-gcc2.96 already at $EEGCC_DIR"
elif command -v curl >/dev/null 2>&1; then
    echo "==> fetching ee-gcc2.96 from decompme/compilers (~18 MB)"
    mkdir -p "$EEGCC_DIR"
    if curl -fsSL "$EEGCC_TARBALL_URL" | tar -xJ -C "$EEGCC_DIR" --strip-components=1; then
        echo "==> ee-gcc2.96 extracted to $EEGCC_DIR"
    else
        echo "==> ee-gcc2.96 fetch failed; install manually" >&2
        rm -rf "$EEGCC_DIR"
    fi
else
    echo "==> curl not available; skipping ee-gcc2.96 (install manually)"
fi

# ee-gcc2.96 is a 32-bit i386 ELF (matches the toolchain SOTC and other PS2
# decomp projects use). On a 64-bit Linux host it requires multilib /
# 32-bit libc; check and warn so failures are obvious.
if [[ -f "$EEGCC_BIN" ]] && ! "$EEGCC_BIN" --version >/dev/null 2>&1; then
    cat >&2 <<EOF
==> ee-gcc2.96 is installed but won't run on this host.
    It's a 32-bit i386 binary; you need 32-bit libc support, e.g.:

      sudo dpkg --add-architecture i386
      sudo apt-get update
      sudo apt-get install libc6:i386 libstdc++6:i386 zlib1g:i386

    Then re-run tools/setup.sh to verify.
EOF
fi

# --- 4b. EE binutils (assembler/linker) -------------------------------------

if [[ "${SKIP_TOOLCHAIN:-0}" == "1" ]]; then
    :
elif command -v mips64r5900el-ps2-elf-as >/dev/null 2>&1; then
    echo "==> system EE binutils detected"
elif command -v mips-linux-gnu-as >/dev/null 2>&1; then
    echo "==> using mips-linux-gnu-as in r5900 mode (system fallback — fine for splat asm)"
else
    cat <<'EOF' >&2

==> No MIPS assembler/linker on PATH.

Quickest fix on Debian/Ubuntu:

    sudo apt-get install binutils-mips-linux-gnu

That gives you mips-linux-gnu-as / -ld / -objcopy, which assemble splat's
r5900 output cleanly and round-trip the ICO ELF. The PS2-specific
'mips64r5900el-ps2-elf-' prefix is only needed if you want EE-specific
binutils features; for matching work the generic binutils is sufficient.

EOF
fi

# --- 5. Ghidra ---------------------------------------------------------------

GHIDRA_VER="${GHIDRA_VER:-11.2.1}"
GHIDRA_REL="${GHIDRA_REL:-PUBLIC_20241105}"
GHIDRA_URL="https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_${GHIDRA_VER}_build/ghidra_${GHIDRA_VER}_${GHIDRA_REL}.zip"

if [[ "${SKIP_GHIDRA:-0}" == "1" ]]; then
    echo "==> SKIP_GHIDRA=1; not fetching Ghidra"
elif [[ -d "tools/ghidra/ghidra_${GHIDRA_VER}_PUBLIC" ]]; then
    echo "==> Ghidra ${GHIDRA_VER} already present"
elif command -v curl >/dev/null 2>&1; then
    echo "==> fetching Ghidra ${GHIDRA_VER}"
    mkdir -p tools/ghidra
    if curl -fsSL --output "tools/ghidra/ghidra.zip" "$GHIDRA_URL"; then
        ( cd tools/ghidra && python -c "import zipfile; zipfile.ZipFile('ghidra.zip').extractall('.')" && rm -f ghidra.zip )
        echo "==> Ghidra extracted to tools/ghidra/ghidra_${GHIDRA_VER}_PUBLIC/"
    else
        echo "==> Ghidra download failed; install manually if needed" >&2
        rm -f tools/ghidra/ghidra.zip
    fi
else
    echo "==> curl not available; skipping Ghidra"
fi

# --- 6. pcsx2 (optional) -----------------------------------------------------

if [[ "${SKIP_PCSX2:-0}" == "1" ]]; then
    echo "==> SKIP_PCSX2=1; not installing pcsx2"
elif command -v pcsx2 >/dev/null 2>&1 || command -v pcsx2-qt >/dev/null 2>&1; then
    echo "==> pcsx2 already on PATH"
elif command -v apt-get >/dev/null 2>&1; then
    echo "==> attempting apt-get install pcsx2 (may fail on non-Debian hosts)"
    sudo apt-get update -qq || true
    sudo apt-get install -y pcsx2 || echo "==> pcsx2 install failed; grab the AppImage from https://pcsx2.net" >&2
else
    echo "==> non-apt host; install pcsx2 manually from https://pcsx2.net"
fi

# --- 7. pre-commit hook ------------------------------------------------------

if [[ -d .git ]]; then
    bash tools/install_hooks.sh
else
    echo "==> not a git repo yet; skipping hook install"
fi

echo
echo "Setup complete. Next steps:"
echo "  1. Place your disc image at baserom/Ico_USA.bin (+ .cue)"
echo "  2. Run 'tools/extract_elf.sh' to extract baseelf.elf and record SHA-1"
echo "  3. Run 'make setup && make' to verify and build"
