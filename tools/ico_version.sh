# tools/ico_version.sh: shell twin of tools/ico_version.py.
#
# Source it and call `ico_version_init [repo_root]`; it exports:
#   ICO_VERSION      version slug (pal | us | aug6)
#   ICO_BASEROM_DIR  baserom/ (us) or baserom/<ver>/
#   ICO_BASEELF      <baserom dir>/baseelf.elf
#   ICO_ROM          <baserom dir>/baseelf.rom   (objcopy -O binary view)
# All paths are repo-root-relative. An explicit VERSION environment variable
# wins; otherwise the slug is the first one whose config/link_order.<ver>.txt
# exists. No python and no .venv dependency, so the shell tools can source it
# before the venv exists. Keep in sync with tools/ico_version.py.

ico_version_detect() {
    local root="${1:-.}" v
    if [ -n "${VERSION:-}" ]; then printf '%s\n' "$VERSION"; return 0; fi
    for v in pal us aug6; do
        if [ -f "$root/config/link_order.$v.txt" ]; then printf '%s\n' "$v"; return 0; fi
    done
    printf 'us\n'
}

ico_version_baserom_dir() {  # <version>
    case "$1" in
        us) printf 'baserom\n' ;;
        *)  printf 'baserom/%s\n' "$1" ;;
    esac
}

ico_version_init() {
    local root="${1:-$PWD}"
    ICO_VERSION="$(ico_version_detect "$root")"
    ICO_BASEROM_DIR="$(ico_version_baserom_dir "$ICO_VERSION")"
    ICO_BASEELF="${ICO_BASEROM_DIR}/baseelf.elf"
    ICO_ROM="${ICO_BASEROM_DIR}/baseelf.rom"
    export ICO_VERSION ICO_BASEROM_DIR ICO_BASEELF ICO_ROM
}
