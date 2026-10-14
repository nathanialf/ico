# tools/ico_version.sh: shell twin of tools/ico_version.py.
#
# Source it and call `ico_version_init [repo_root]`; it exports:
#   ICO_VERSION      version slug (pal | jpn | us | aug6)
#   ICO_BASEROM_DIR  baserom/<ver>
#   ICO_BASEELF      <baserom dir>/baseelf.elf
#   ICO_ROM          <baserom dir>/baseelf.rom   (objcopy -O binary view)
#   ICO_DISC         the disc image the user copies under baserom/
#                    (baserom/Ico_PAL.iso, baserom/Ico_JPN.bin, ...)
#   ICO_DISC_CUE     its cue sheet, empty when ICO_DISC is a cooked ISO
#   ICO_DISC_NAME    the disc as messages name it, e.g.
#                    "PAL retail disc (SCES-50760)"
#   ICO_DISC_WHERE   the region in the name a dump usually goes by, as in
#                    "Ico (Europe).iso"
# All paths are repo-root-relative. An explicit VERSION environment variable
# wins; otherwise the slug is the first one whose config/link_order.<ver>.txt
# exists. No python and no .venv dependency, so the shell tools can source it
# before the venv exists. Keep in sync with tools/ico_version.py, whose DISCS
# table ico_version_disc mirrors.

ico_version_detect() {
    local root="${1:-.}" v
    if [ -n "${VERSION:-}" ]; then printf '%s\n' "$VERSION"; return 0; fi
    for v in pal jpn us aug6; do
        if [ -f "$root/config/link_order.$v.txt" ]; then printf '%s\n' "$v"; return 0; fi
    done
    printf 'us\n'
}

ico_version_baserom_dir() {  # <version>
    printf 'baserom/%s\n' "$1"
}

# ico_version_disc <version>: sets ICO_DISC, ICO_DISC_CUE, ICO_DISC_NAME and
# ICO_DISC_WHERE (all empty for a slug with no disc recipe).
ico_version_disc() {
    local region="" product="" image="" cue=""
    ICO_DISC_WHERE=""
    case "$1" in
        pal)  region="PAL retail";           product="SCES-50760"; ICO_DISC_WHERE="Europe"
              image="Ico_PAL.iso" ;;
        jpn)  region="Japanese retail";      product="SCPS-11003"; ICO_DISC_WHERE="Japan"
              image="Ico_JPN.bin";  cue="Ico_JPN.cue" ;;
        us)   region="USA retail";           product="SLUS-20218"; ICO_DISC_WHERE="USA"
              image="Ico_USA.bin";  cue="Ico_USA.cue" ;;
        aug6) region="Aug-6-2001 prototype"; product="";           ICO_DISC_WHERE="prototype"
              image="Ico_AUG6.bin"; cue="Ico_AUG6.cue" ;;
    esac
    ICO_DISC="${image:+baserom/$image}"
    ICO_DISC_CUE="${cue:+baserom/$cue}"
    ICO_DISC_NAME="${region:+$region disc}${product:+ ($product)}"
}

ico_version_init() {
    local root="${1:-$PWD}"
    ICO_VERSION="$(ico_version_detect "$root")"
    ICO_BASEROM_DIR="$(ico_version_baserom_dir "$ICO_VERSION")"
    ICO_BASEELF="${ICO_BASEROM_DIR}/baseelf.elf"
    ICO_ROM="${ICO_BASEROM_DIR}/baseelf.rom"
    ico_version_disc "$ICO_VERSION"
    export ICO_VERSION ICO_BASEROM_DIR ICO_BASEELF ICO_ROM
    export ICO_DISC ICO_DISC_CUE ICO_DISC_NAME ICO_DISC_WHERE
}
