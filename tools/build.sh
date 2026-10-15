#!/usr/bin/env bash
# tools/build.sh: top-level orchestration for the ICO decomp.
#
# One tree may carry several targets: a target is configured when
# config/link_order.<slug>.txt exists. The target slug and its paths come from
# tools/ico_version.sh: VERSION=<slug> picks one, and without it the first
# configured target (pal) is used.
#
# Inner-loop build is `ninja` (or `.venv/bin/ninja` if not on PATH): every
# object from its own source, linked by config/link.<slug>.ld in the order of
# config/link_order.<slug>.txt (tools/gen_ninja.py writes build.ninja, whose
# first line names the slug it was written for). Every output is under
# build/<slug>/. This script only handles the one-shots that do not belong in
# the build graph.
#
# Subcommands:
#   setup         Delete build/<slug>/, verify the base ELF and ROM SHA-1s,
#                 write build/<slug>/tree/ and build.ninja.
#   verify        Just verify the base ELF and ROM SHA-1s (and regen when
#                 build.ninja was written for another target).
#   regen         Just rewrite build/<slug>/tree/ and build.ninja (after adding
#                 a source file or a header).
#   clean         rm -rf build/<slug>/.
#   distclean     rm -rf build/ and build.ninja (every target).
#   progress      Regenerate the progress files (docs/<slug>/PROGRESS.md,
#                 docs/<slug>/progress.json, README's progress block).
#   gate-all      For every configured target: require its base files, then
#                 setup and ninja (the byte gate). Every target's base files
#                 are required before anything is built.
#   progress-all  progress for every configured target.

set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "${ROOT}"

VENV_PY="${ROOT}/.venv/bin/python"

# shellcheck source=tools/ico_version.sh
. "${ROOT}/tools/ico_version.sh"
ico_version_init "${ROOT}"
VERSION="${ICO_VERSION}"
export VERSION
BASEELF="${BASEELF:-${ICO_BASEELF}}"
BASEROM="${BASEROM:-${ICO_ROM}}"

regen_ninja() {
    echo "==> writing ${ICO_TREE}/ and build.ninja (VERSION=${VERSION})"
    "${VENV_PY}" tools/gen_ninja.py --tree
    "${VENV_PY}" tools/gen_ninja.py
}

# The slug build.ninja was written for (its first line), or "" without one.
manifest_slug() {
    [ -f build.ninja ] || return 0
    head -n 1 build.ninja | sed -n 's/^# ico build.ninja for VERSION=\([^:]*\):.*/\1/p'
}

verify_base() {
    echo "==> verifying the base ELF and ROM SHA-1s (${ICO_SHA1SUMS})"
    "${VENV_PY}" tools/verify_elf.py --target "${BASEELF}"
    "${VENV_PY}" tools/verify_elf.py --target "${BASEROM}"
}

setup() {
    echo "==> clean ${ICO_BUILD_DIR}/ (full rebuild)"
    rm -rf "${ICO_BUILD_DIR}"
    verify_base
    regen_ninja
}

do_clean() {
    rm -rf "${ICO_BUILD_DIR}"
}

do_distclean() {
    rm -rf build
    rm -f build.ninja .ninja_log .ninja_deps
}

do_progress() {
    # docs/<slug>/PROGRESS.md, the dashboard's docs/<slug>/progress.json
    # (docs/index.html) and README's progress block, from the built ELF and
    # its link map.
    "${VENV_PY}" tools/check_elf.py --progress
}

ninja_bin() {
    if [ -x "${ROOT}/.venv/bin/ninja" ]; then
        printf '%s\n' "${ROOT}/.venv/bin/ninja"
    else
        command -v ninja || { echo "build.sh: ninja not on PATH and .venv/bin/ninja missing: run tools/setup.sh" >&2; exit 1; }
    fi
}

gate_all() {
    # Every configured target's base files first: a missing one fails the
    # whole run before anything is built, never a skip.
    local v missing=0 n
    if [ -z "${ICO_VERSIONS}" ]; then
        echo "build.sh gate-all: no configured target (no config/link_order.<slug>.txt)" >&2
        exit 1
    fi
    for v in ${ICO_VERSIONS}; do
        for f in "baserom/${v}/baseelf.elf" "baserom/${v}/baseelf.rom"; do
            if [ ! -f "${f}" ]; then
                echo "build.sh gate-all: ${f} is missing; every configured target (${ICO_VERSIONS}) needs its base files (VERSION=${v} tools/extract_elf.sh)" >&2
                missing=1
            fi
        done
    done
    [ "${missing}" -eq 0 ] || exit 1
    n="$(ninja_bin)"
    for v in ${ICO_VERSIONS}; do
        echo "==> gate-all: ${v}"
        VERSION="${v}" "${ROOT}/tools/build.sh" setup
        VERSION="${v}" "${n}" -C "${ROOT}"
    done
    echo "==> gate-all: every configured target passed (${ICO_VERSIONS})"
}

progress_all() {
    local v
    for v in ${ICO_VERSIONS}; do
        echo "==> progress-all: ${v}"
        VERSION="${v}" "${VENV_PY}" tools/check_elf.py --progress
    done
}

cmd="${1:-help}"
case "$cmd" in
    setup)        setup ;;
    verify)       verify_base
                  if [ -f build.ninja ] && [ "$(manifest_slug)" != "${VERSION}" ]; then regen_ninja; fi ;;
    regen)        regen_ninja ;;
    clean)        do_clean ;;
    distclean)    do_distclean ;;
    progress)     do_progress ;;
    gate-all)     gate_all ;;
    progress-all) progress_all ;;
    help|*)
        cat <<USAGE
usage: [VERSION=<slug>] $0 <subcommand>      (configured: ${ICO_VERSIONS:-none}; now ${VERSION})

  setup         delete ${ICO_BUILD_DIR}/, verify the base ELF and ROM, write ${ICO_TREE}/ and build.ninja
  verify        verify the base ELF and ROM SHA-1s only
  regen         rewrite ${ICO_TREE}/ and build.ninja from config/link_order.${VERSION}.txt
  clean         rm -rf ${ICO_BUILD_DIR}/
  distclean     rm -rf build/ and delete build.ninja
  progress      regenerate ${ICO_DOCS_DIR}/PROGRESS.md, ${ICO_DOCS_DIR}/progress.json and README's block
  gate-all      every configured target: its base files required, then setup and ninja
  progress-all  progress for every configured target

Build with: ninja
USAGE
        ;;
esac
