#!/usr/bin/env bash
# tools/build.sh — top-level orchestration for the ICO decomp.
#
# Inner-loop build is `ninja` (or `.venv/bin/ninja` if not on PATH).
# This script only handles one-shots that don't belong in the build
# graph: baserom verification, splat, progress regeneration.
#
# Subcommands:
#   setup       Verify baserom SHA-1 + run splat + regen build.ninja.
#   split       Just re-run splat (no baserom check, no build.ninja regen).
#   clean       rm -rf build/.
#   distclean   clean + remove splat-emitted asm and config artifacts.
#   progress    Regenerate progress tables (README + docs/PROGRESS.md).

set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "${ROOT}"

VENV_PY="${ROOT}/.venv/bin/python"
SPLAT="${ROOT}/.venv/bin/splat"

# `main` is us-only; the aug6 prototype pipeline lives on the `aug6` branch.
# (This branch is the former `retail-v2`, renamed to `main` on 2026-07-29;
# the old `retail` and `retail-v2` branches are gone.) VERSION stays
# overridable via env for ad-hoc targets. Exported so child tools
# (gen_ninja.py) see it.
VERSION="${VERSION:-us}"
export VERSION
# The retail baseelf lives at baserom/baseelf.rom; the aug6 prototype's lives
# under baserom/aug6/ in the same (gitignored, branch-shared) working tree.
# Overridable via env for ad-hoc targets.
BASEROM="${BASEROM:-baserom/baseelf.rom}"
SPLAT_YAML="config/ico.${VERSION}.yaml"
LDSCRIPT="config/ico.${VERSION}.ld"
DEPS_FILE="config/ico.${VERSION}.d"
AUTO_FUNCS="config/undefined_funcs_auto.${VERSION}.txt"
AUTO_SYMS="config/undefined_syms_auto.${VERSION}.txt"

regen_ninja() {
    echo "==> regenerating build.ninja"
    "${VENV_PY}" tools/gen_ninja.py
}

split() {
    # ICO patches the installed splat (.c.inc scanning, aug6 layout,
    # sub-word data tails) and UNAPPLIES the retired $ACC/$Q sigil
    # rewrite if present. The patches die on every `pip install`, so
    # re-apply (idempotent) here.
    "${VENV_PY}" tools/patch_splat.py
    echo "==> running splat against ${SPLAT_YAML}"
    "${SPLAT}" split "${SPLAT_YAML}"
    # This target is a clean, raw round-trip: splat reproduces the original layout
    # byte-for-byte via config (align: 0x80, .reginfo subseg) + the
    # patch_splat.py aug6 layout/sub-word-tail patches. There is deliberately
    # NO linker-script post-processing and NO data->typed-C migration — data is
    # placed by per-TU yaml carving + dot-form subsegments, and noncontiguous
    # data blocks land via the carved selectors splat emits in a single pass.
    # The old postprocess/slinky machinery lived on the retired `retail`
    # branch (deleted 2026-07-29); this rebuild deliberately has none.
    #
    # box.o: functions written in shipped-VMA order across box.c + the
    # block-#included src/switch.c (BOX_SWBLK guards), so the default single
    # .text glob lays them out correctly — no -ffunction-sections, no
    # trace-reorder postprocess.
    echo "==> ${VERSION}: raw pipeline (no postprocess, no data-migration)"
}

setup() {
    echo "==> clean build/ (full rebuild — incremental ninja silently retains stale .o files when only .h/.s deps change, masking yaml-flip / coalesce regressions)"
    rm -rf build .ninja_log .ninja_deps
    echo "==> verifying base ROM SHA-1"
    "${VENV_PY}" tools/verify_elf.py --target "${BASEROM}"
    echo "==> assembling hand-written VU1 microprogram .S sources (src)"
    for vs in src/*.S; do
        [ -f "$vs" ] || continue
        out="${vs%.S}.s"
        stem=$(basename "${vs%.S}")
        # VU microprogram global symbol: TitleCase(stem, split on '_') + MicroProgram
        # e.g. cluster→ClusterMicroProgram, normal_c→NormalCMicroProgram
        sym=$("${VENV_PY}" -c "import sys;print(''.join(w.title() for w in sys.argv[1].split('_'))+'MicroProgram')" "$stem")
        "${VENV_PY}" tools/assemble_vu0.py "$vs" --label "$sym" --out "$out"
    done
    split
    regen_ninja
}

do_clean() {
    rm -rf build
}

do_distclean() {
    do_clean
    find asm -type f -name '*.s' ! -path 'asm/nonmatchings/*' -delete
    find asm -type d -empty ! -path asm ! -path 'asm/nonmatchings*' -delete 2>/dev/null || true
    rm -f "${LDSCRIPT}" "${AUTO_FUNCS}" "${AUTO_SYMS}" "${DEPS_FILE}"
    rm -f build.ninja .ninja_log .ninja_deps
}

do_progress() {
    "${VENV_PY}" tools/progress.py
    # Function-level tree JSON for the GitHub Pages site (docs/index.html).
    "${VENV_PY}" tools/progress_tree.py
}

cmd="${1:-help}"
case "$cmd" in
    setup)      setup ;;
    split)      split ;;
    regen)      regen_ninja ;;
    clean)      do_clean ;;
    distclean)  do_distclean ;;
    progress)   do_progress ;;
    help|*)
        cat <<EOF
usage: $0 <subcommand>

  setup       verify base ROM, run splat, regenerate build.ninja
  split       re-run splat only (no baserom verify, no build.ninja regen)
  regen       regenerate build.ninja from config/ico.${VERSION}.d
  clean       rm -rf build/
  distclean   clean + delete splat-emitted asm and config artifacts
  progress    regenerate README + docs/PROGRESS.md tables

Build with: ninja
EOF
        ;;
esac
