"""Shared version-slug detection and per-version paths for ICO tooling.

One branch per target:

    branch   slug   disc                                 boot ELF
    ------   ----   ----------------------------------   -----------
    main     pal    PAL retail, SCES-50760               SCES_507.60
    jpn      jpn    Japanese retail, SCPS-11003 (1.02)   SCPS_110.03
    ntsc     us     USA retail, SLUS-20218               SCUS_971.13
    aug6     aug6   Aug-6-2001 prototype                 SCUS_971.13

Each slug's link order is config/link_order.<slug>.txt on its own branch, and
its extracted base files are baserom/<slug>/baseelf.{elf,rom}. `baserom/` is
gitignored and can hold every target's files side by side.

An explicit `VERSION` environment variable wins; otherwise the slug is the
first one whose `config/link_order.<slug>.txt` exists. A working tree only
carries its own target's link order.

DISCS is the one table of what each target's disc image is called and how
tools name it in messages: the file the user copies under baserom/ (a plain
2048-byte-sector ISO for pal, a raw .bin with its .cue for the others), the
product code, the region description, and the disc's reference files that
tools/extract_elf.py copies beside the ELF.

tools/ico_version.sh is the shell twin of this module (same detection order,
same paths, same disc table). Keep the two in sync.
"""
from __future__ import annotations
import os
from pathlib import Path

# Detection order.
VERSIONS = ("pal", "jpn", "us", "aug6")

# Per-target disc image.
#   region  : how messages describe the disc
#   product : the product code printed on it ("" when it carries none)
#   where   : the region in the name a dump of it usually goes by,
#             as in `Ico (Europe).iso`
#   image   : the file the user copies under baserom/
#   cue     : the raw image's cue sheet, or "" when `image` is already a
#             cooked ISO9660 image
#   extras  : disc files copied beside the ELF as reference material (the
#             build reads none of them)
DISCS = {
    "pal": {
        "region": "PAL retail",
        "product": "SCES-50760",
        "where": "Europe",
        "image": "Ico_PAL.iso",
        "cue": "",
        # The 2002-01-16 EU master's linker map and source listings.
        "extras": ("MAIN.MAP", "SRCFILE.TXT", "TRFILE.TXT", "SYSTEM.CNF"),
    },
    "jpn": {
        "region": "Japanese retail",
        "product": "SCPS-11003",
        "where": "Japan",
        "image": "Ico_JPN.bin",
        "cue": "Ico_JPN.cue",
        # The JPN disc ships no map or listing.
        "extras": ("SYSTEM.CNF",),
    },
    "us": {
        "region": "USA retail",
        "product": "SLUS-20218",
        "where": "USA",
        "image": "Ico_USA.bin",
        "cue": "Ico_USA.cue",
        "extras": ("SYSTEM.CNF",),
    },
    "aug6": {
        "region": "Aug-6-2001 prototype",
        "product": "",
        "where": "prototype",
        "image": "Ico_AUG6.bin",
        "cue": "Ico_AUG6.cue",
        # A linker map and the trace listing; this disc has no SRCFILE.TXT.
        "extras": ("MAIN.MAP", "TRFILE.TXT", "SYSTEM.CNF"),
    },
}


def detect_version(repo_root: Path) -> str:
    v = os.environ.get("VERSION")
    if v:
        return v
    for ver in VERSIONS:
        if (repo_root / "config" / f"link_order.{ver}.txt").exists():
            return ver
    return "us"


def baserom_dir(repo_root: Path, version: str) -> Path:
    """Directory holding this target's extracted base files."""
    return repo_root / "baserom" / version


def baseelf_path(repo_root: Path, version: str) -> Path:
    return baserom_dir(repo_root, version) / "baseelf.elf"


def rom_path(repo_root: Path, version: str) -> Path:
    """The `objcopy -O binary` view of the base ELF, the ROM SHA-1's subject."""
    return baserom_dir(repo_root, version) / "baseelf.rom"


def config_path(repo_root: Path, version: str, stem: str, ext: str) -> Path:
    """config/<stem>.<version>.<ext>, e.g. config/link_order.pal.txt."""
    return repo_root / "config" / f"{stem}.{version}.{ext}"


def link_map_path(repo_root: Path, version: str) -> Path:
    """The link map the build writes, build/ico.<version>.map."""
    return repo_root / "build" / f"ico.{version}.map"


def disc_name(version: str) -> str:
    """The disc as messages name it, e.g. `PAL retail disc (SCES-50760)`
    ("" for a slug with no DISCS row)."""
    d = DISCS.get(version)
    if d is None:
        return ""
    return f"{d['region']} disc" + (f" ({d['product']})" if d["product"] else "")


def disc_image(repo_root: Path, version: str) -> Path | None:
    """The disc image file the user copies under baserom/ for this target."""
    d = DISCS.get(version)
    return repo_root / "baserom" / d["image"] if d else None


def disc_cue(repo_root: Path, version: str) -> Path | None:
    """The raw image's cue sheet, or None for a cooked ISO (or no recipe)."""
    d = DISCS.get(version)
    return repo_root / "baserom" / d["cue"] if d and d["cue"] else None


def _rel(p, root):
    return "" if p is None else p.relative_to(root)


_KEYS = {
    "version": lambda root, v: v,
    "baserom_dir": lambda root, v: baserom_dir(root, v).relative_to(root),
    "baseelf": lambda root, v: baseelf_path(root, v).relative_to(root),
    "rom": lambda root, v: rom_path(root, v).relative_to(root),
    "disc": lambda root, v: _rel(disc_image(root, v), root),
    "disc_cue": lambda root, v: _rel(disc_cue(root, v), root),
    "disc_name": lambda root, v: disc_name(v),
    "disc_where": lambda root, v: DISCS[v]["where"] if v in DISCS else "",
}


def main(argv: list[str] | None = None) -> int:
    import sys
    argv = list(sys.argv[1:] if argv is None else argv)
    root = Path(__file__).resolve().parent.parent
    ver = detect_version(root)
    if not argv:
        for k, fn in _KEYS.items():
            print(f"ICO_{k.upper()}={fn(root, ver)}")
        return 0
    for key in argv:
        if key not in _KEYS:
            print(f"ico_version: unknown key '{key}' (have: {', '.join(_KEYS)})",
                  file=sys.stderr)
            return 2
        print(_KEYS[key](root, ver))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
