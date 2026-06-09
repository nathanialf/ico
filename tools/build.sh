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

# Version slug: explicit env wins; else auto-detect from which config exists
# (retail main has config/ico.us.yaml; the aug6 prototype branch has
# config/ico.aug6.yaml). Exported so child tools (gen_ninja.py) see it.
if [ -z "${VERSION:-}" ]; then
    if [ -f config/ico.us.yaml ]; then VERSION=us
    elif [ -f config/ico.aug6.yaml ]; then VERSION=aug6
    else VERSION=us; fi
fi
export VERSION
# aug6 branch: the prototype baseelf lives under baserom/aug6/ so it does not
# collide with retail's baserom/baseelf.rom in the (gitignored, branch-shared)
# working tree. Overridable via env for ad-hoc targets.
BASEROM="${BASEROM:-baserom/aug6/baseelf.rom}"
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
    # ICO patches the installed splat to add `$` to r5900 special VU0
    # operands ($ACC, $Q) in per-func nonmatching .s files. The patch
    # dies on every `pip install`, so re-apply (idempotent) here.
    "${VENV_PY}" tools/patch_splat.py
    echo "==> running splat against ${SPLAT_YAML}"
    "${SPLAT}" split "${SPLAT_YAML}"
    if [ "${VERSION}" = "aug6" ]; then
        # aug6 is a clean, raw round-trip: splat reproduces the original layout
        # byte-for-byte via config (align: 0x80, .reginfo subseg) + the
        # patch_splat.py aug6 layout/sub-word-tail patches. NO output
        # postprocessing and NO data->typed-C migration (both deliberately
        # deferred — see the aug6 design notes). Stop here.
        #
        # box.o: functions written in shipped-VMA order across box.c + the
        # block-#included src/switch.c (BOX_SWBLK guards), so the default single
        # .text glob lays them out correctly — no -ffunction-sections, no
        # trace-reorder postprocess.
        echo "==> aug6: raw pipeline (skipping postprocess + data-migration)"
        return 0
    fi
    echo "==> postprocessing linker script (sbss/bss alignment fix)"
    "${VENV_PY}" tools/postprocess_ld.py
    echo "==> postprocessing asm (R5900 mnemonic fixups)"
    "${VENV_PY}" tools/postprocess_asm.py
    # The retail per-TU data-migration pipeline (sidecars + per-VMA named
    # sections) lived here; it was removed from main 2026-06-08 — the aug6
    # data phase uses per-TU yaml carving + dot-form subsegments instead
    # (see the retail branch for the old machinery).
}

setup() {
    echo "==> clean build/ (full rebuild — incremental ninja silently retains stale .o files when only .h/.s deps change, masking yaml-flip / coalesce regressions)"
    rm -rf build .ninja_log .ninja_deps
    echo "==> verifying base ROM SHA-1"
    "${VENV_PY}" tools/verify_elf.py --target "${BASEROM}"
    echo "==> assembling hand-written VU0 .S sources"
    for vs in src/cod/*.S; do
        [ -f "$vs" ] || continue
        out="${vs%.S}.s"
        stem=$(basename "${vs%.S}")
        "${VENV_PY}" tools/assemble_vu0.py "$vs" \
            --label "__src_cod_${stem}_textbin" --out "$out"
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
}

do_slinky() {
    # Regenerate config/ico.us.slinky.yaml from the current build state,
    # run slinky-cli to emit config/ico.us.slinky.ld, then post-process
    # the ld to inject SORT_BY_NAME for the typed-section catch-alls.
    # The patched slinky.ld builds a SHA-1-identical ELF alongside the
    # current postprocess_ld.py-patched ico.us.ld. Requires `ninja` to
    # have run at least once — gen_slinky.py reads .o section tables
    # via objdump. See decomp/NOTES.md "Per-TU section linking" block.
    "${VENV_PY}" tools/gen_slinky.py
    if ! command -v slinky-cli >/dev/null 2>&1; then
        echo "do_slinky: slinky-cli not on PATH — install via tools/setup.sh step 7"
        return 1
    fi
    slinky-cli --omit-version-comment \
        -o "config/ico.${VERSION}.slinky.ld" \
        "config/ico.${VERSION}.slinky.yaml"
    "${VENV_PY}" tools/postprocess_slinky_ld.py
    echo "do_slinky: wrote config/ico.${VERSION}.slinky.ld"
}

cmd="${1:-help}"
case "$cmd" in
    setup)      setup ;;
    split)      split ;;
    regen)      regen_ninja ;;
    clean)      do_clean ;;
    distclean)  do_distclean ;;
    progress)   do_progress ;;
    slinky)     do_slinky ;;
    help|*)
        cat <<EOF
usage: $0 <subcommand>

  setup       verify base ROM, run splat, regenerate build.ninja
  split       re-run splat only (no baserom verify, no build.ninja regen)
  regen       regenerate build.ninja from config/ico.${VERSION}.d
  clean       rm -rf build/
  distclean   clean + delete splat-emitted asm and config artifacts
  progress    regenerate README + docs/PROGRESS.md tables
  slinky      regenerate config/ico.${VERSION}.slinky.{yaml,ld} (parallel artifact)

Build with: ninja
EOF
        ;;
esac
