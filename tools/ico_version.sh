# tools/ico_version.sh — pure-bash twin of tools/ico_version.py.
#
# Source it and call `ico_version_init [repo_root]`; it exports:
#   ICO_VERSION      version slug (pal | us | aug6)
#   ICO_YAML         config/ico.<ver>.yaml
#   ICO_ASM_ROOT     splat asm tree root, read from the yaml's `asm_path`
#   ICO_BASEROM_DIR  baserom/ (us) or baserom/<ver>/
#   ICO_BASEELF      <baserom dir>/baseelf.elf
#   ICO_ROM          <baserom dir>/baseelf.rom   (splat input + build oracle)
#   ICO_LAYOUT       flat (retail us/pal) | devtree (aug6 per-programmer tree)
# All paths are repo-root-relative. Explicit VERSION env wins over detection.
#
# No python and no .venv dependency on purpose: this runs in the inner loop
# (quick_diff) hundreds of times per matching round. Keep in sync with
# tools/ico_version.py, which is the same table for the python tools.

ico_version_detect() {
    local root="${1:-.}" v
    if [ -n "${VERSION:-}" ]; then printf '%s\n' "$VERSION"; return 0; fi
    for v in pal us aug6; do
        if [ -f "$root/config/ico.$v.yaml" ]; then printf '%s\n' "$v"; return 0; fi
    done
    printf 'us\n'
}

ico_version_asm_root() {  # <repo_root> <version>
    local p
    p=$(sed -n 's/^[[:space:]]*asm_path:[[:space:]]*\([^[:space:]#]*\).*/\1/p' \
            "$1/config/ico.$2.yaml" 2>/dev/null | head -1)
    printf '%s\n' "${p:-asm}"
}

ico_version_baserom_dir() {  # <version>
    case "$1" in
        us) printf 'baserom\n' ;;
        *)  printf 'baserom/%s\n' "$1" ;;
    esac
}

ico_version_layout() {  # <version>
    case "$1" in
        aug6) printf 'devtree\n' ;;
        *)    printf 'flat\n' ;;
    esac
}

ico_version_init() {
    local root="${1:-$PWD}"
    ICO_VERSION="$(ico_version_detect "$root")"
    ICO_YAML="config/ico.${ICO_VERSION}.yaml"
    ICO_ASM_ROOT="$(ico_version_asm_root "$root" "$ICO_VERSION")"
    ICO_BASEROM_DIR="$(ico_version_baserom_dir "$ICO_VERSION")"
    ICO_BASEELF="${ICO_BASEROM_DIR}/baseelf.elf"
    ICO_ROM="${ICO_BASEROM_DIR}/baseelf.rom"
    ICO_LAYOUT="$(ico_version_layout "$ICO_VERSION")"
    export ICO_VERSION ICO_YAML ICO_ASM_ROOT ICO_BASEROM_DIR ICO_BASEELF ICO_ROM ICO_LAYOUT
}
