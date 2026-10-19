"""Shared version-slug detection and per-version paths for ICO tooling.

The targets:

    slug   disc                                 boot ELF
    ----   ----------------------------------   -----------
    pal    PAL retail, SCES-50760               SCES_507.60
    jpn    Japanese retail, SCPS-11003 (1.02)   SCPS_110.03
    kor    Korean retail, SCPS-56001            SCPS_560.01
    us     USA retail, SLUS-20218               SCUS_971.13
    aug6   Aug-6-2001 prototype                 SCUS_971.13
    jun26  Jun-26-2001 demo, on the US          CUS97113/SCPS_000.00
           PlayStation Magazine's disc
           SCUS-97158

One tree may carry several targets. A target is configured in a tree when
config/link_order.<slug>.txt exists (configured_versions()). Its other
per-target files are config/<stem>.<slug>.<ext> and
config/sha1sums.<slug>.txt; its extracted base files are
baserom/<slug>/baseelf.{elf,rom} (`baserom/` is gitignored and holds every
target's files side by side); its build is under build/<slug>/; its progress
files are under docs/<slug>/.

The sources, ico2/ and sce/, are one tree for every configured target:
where the targets differ, a file holds each one's lines inline in
VERSION_<SLUG> blocks (tools/check_targets.py's forms), which
tools/compile_c.sh defines.

An explicit `VERSION` environment variable wins; otherwise the slug is the
first configured one in VERSIONS order.

DISCS is the one table of what each target's disc image is called and how
tools name it in messages: the file the user copies under baserom/ (a plain
2048-byte-sector ISO for pal, kor and jun26, a raw .bin with its .cue for the
others), the product code, the region description, the boot file when it is
not the one SYSTEM.CNF names, and the disc's reference files that
tools/extract_elf.py copies beside the ELF.

tools/ico_version.sh is the shell twin of this module (same detection order,
same paths, same disc table). Keep the two in sync.
"""
from __future__ import annotations
import os
from pathlib import Path

# Detection order.
VERSIONS = ("pal", "jpn", "kor", "us", "aug6", "jun26")

# Per-target disc image.
#   region  : how messages describe the disc
#   product : the product code printed on it ("" when it carries none)
#   where   : the region in the name a dump of it usually goes by,
#             as in `Ico (Europe).iso`
#   image   : the file the user copies under baserom/
#   cue     : the raw image's cue sheet, or "" when `image` is already a
#             cooked ISO9660 image
#   boot    : the ELF's path on the disc, when it is not the file the disc's
#             SYSTEM.CNF BOOT2 line names (absent: SYSTEM.CNF's)
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
    "kor": {
        "region": "Korean retail",
        "product": "SCPS-56001",
        "where": "Korea",
        "image": "Ico_KOR.iso",
        "cue": "",
        # The Korean disc ships no map or listing either.
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
    "jun26": {
        "region": "Jun-26-2001 demo",
        "product": "SCUS-97158",
        "where": "demo",
        "image": "Ico_JUN26.iso",
        "cue": "",
        # A demo among other games on the Official U.S. PlayStation
        # Magazine's disc (issue 49, a DVD); its SYSTEM.CNF boots the disc's
        # menu, SCUS_971.58, which starts the ICO demo from its own
        # directory. The build's stamp is "Jun 26 2001" "20:01:21". The
        # directory has no SYSTEM.CNF, map or listing.
        "boot": "CUS97113/SCPS_000.00",
        "extras": ("SYSTEM.CNF",),
    },
}


def configured_versions(repo_root: Path) -> list[str]:
    """The slugs this tree carries a link order for, in VERSIONS order."""
    return [v for v in VERSIONS
            if (repo_root / "config" / f"link_order.{v}.txt").exists()]


def detect_version(repo_root: Path) -> str:
    v = os.environ.get("VERSION")
    if v:
        return v
    have = configured_versions(repo_root)
    return have[0] if have else "us"


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


def build_dir(repo_root: Path, version: str) -> Path:
    """This target's build directory, build/<version>."""
    return repo_root / "build" / version


def link_map_path(repo_root: Path, version: str) -> Path:
    """The link map the build writes, build/<version>/ico.<version>.map."""
    return build_dir(repo_root, version) / f"ico.{version}.map"


def sha1sums_path(repo_root: Path, version: str) -> Path:
    """The recorded SHA-1s of this target's base files,
    config/sha1sums.<version>.txt (keyed by basename)."""
    return repo_root / "config" / f"sha1sums.{version}.txt"


def docs_dir(repo_root: Path, version: str) -> Path:
    """This target's progress files, docs/<version>/ (PROGRESS.md,
    progress.json)."""
    return repo_root / "docs" / version


def layer_files(repo_root: Path) -> list[str]:
    """The repo-relative paths of the source files (ico2/, sce/): every file
    git tracks there or would track (untracked files not ignored), so a file
    added and not yet staged is counted."""
    import subprocess
    out = subprocess.run(["git", "ls-files", "-co", "--exclude-standard", "--", "ico2", "sce"],
                         cwd=repo_root, capture_output=True, text=True, check=True).stdout
    return [p for p in dict.fromkeys(out.splitlines()) if p and (repo_root / p).is_file()]


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
    "build_dir": lambda root, v: build_dir(root, v).relative_to(root),
    "sha1sums": lambda root, v: sha1sums_path(root, v).relative_to(root),
    "docs_dir": lambda root, v: docs_dir(root, v).relative_to(root),
    "versions": lambda root, v: " ".join(configured_versions(root)),
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
