"""Shared version-slug detection and per-version paths for ICO tooling.

One branch per target, one config namespace per target:

    branch   slug   splat yaml              base files
    ------   ----   ---------------------   -----------------------------
    main     pal    config/ico.pal.yaml     baserom/pal/baseelf.{elf,rom}
    ntsc     us     config/ico.us.yaml      baserom/baseelf.{elf,rom}
    aug6     aug6   config/ico.aug6.yaml    baserom/aug6/baseelf.{elf,rom}

`us` keeps its base files at the top of `baserom/` for historical reasons (it
was the original single-target layout); every other slug gets its own
`baserom/<slug>/` subdirectory. `baserom/` is gitignored wholesale and shared
across the branches' working trees, so all three targets coexist.

Explicit `VERSION` env wins; else auto-detect from which config exists.

tools/ico_version.sh is the pure-bash twin of this module (same detection
order, same paths) for the shell tools. Keep the two in sync.
"""
from __future__ import annotations
import os
import re
from pathlib import Path

# Detection order. The first config/ico.<ver>.yaml that exists wins; a branch's
# working tree only ever carries its own target's config.
VERSIONS = ("pal", "us", "aug6")

# Source-tree shape. The retail targets (us, pal) use a flat repo-root layout
# (src/ ios/ sound/ isys/); the aug6 prototype mirrors the dev's per-programmer
# module tree recovered from TRFILE.TXT.
FLAT_SOURCE_ROOTS = ("src", "ios", "sound", "isys", "ito")
DEVTREE_SOURCE_ROOTS = ("common", "fumi", "sugipon", "seki", "omori",
                        "script", "ito")
LAYOUTS = {"pal": "flat", "us": "flat", "aug6": "devtree"}

_ASM_PATH_RE = re.compile(r"^\s*asm_path:\s*([^\s#]+)", re.M)


def detect_version(repo_root: Path) -> str:
    v = os.environ.get("VERSION")
    if v:
        return v
    for ver in VERSIONS:
        if (repo_root / "config" / f"ico.{ver}.yaml").exists():
            return ver
    return "us"


def yaml_path(repo_root: Path, version: str) -> Path:
    return repo_root / "config" / f"ico.{version}.yaml"


def baserom_dir(repo_root: Path, version: str) -> Path:
    """Directory holding this target's extracted base files."""
    if version == "us":
        return repo_root / "baserom"
    return repo_root / "baserom" / version


def baseelf_path(repo_root: Path, version: str) -> Path:
    return baserom_dir(repo_root, version) / "baseelf.elf"


def rom_path(repo_root: Path, version: str) -> Path:
    """The `objcopy -O binary` view — splat's input and the build oracle."""
    return baserom_dir(repo_root, version) / "baseelf.rom"


def asm_root(repo_root: Path, version: str) -> str:
    """Repo-relative root of the splat-emitted asm tree (the yaml `asm_path`).

    Read straight out of the yaml with a plain regex (so this module stays
    importable without PyYAML) — the tools never second-guess splat's option.
    """
    yml = yaml_path(repo_root, version)
    try:
        m = _ASM_PATH_RE.search(yml.read_text(errors="replace"))
    except OSError:
        m = None
    return m.group(1).rstrip("/") if m else "asm"


def layout(version: str) -> str:
    """'flat' (retail: repo-root src/…) or 'devtree' (aug6 per-programmer)."""
    return LAYOUTS.get(version, "flat")


def source_roots(version: str) -> tuple[str, ...]:
    """Top-level dirs that may hold this target's C / hand-asm translation units."""
    if layout(version) == "devtree":
        return DEVTREE_SOURCE_ROOTS + FLAT_SOURCE_ROOTS
    return FLAT_SOURCE_ROOTS


_KEYS = {
    "version": lambda root, v: v,
    "yaml": lambda root, v: yaml_path(root, v).relative_to(root),
    "asm_root": lambda root, v: asm_root(root, v),
    "baserom_dir": lambda root, v: baserom_dir(root, v).relative_to(root),
    "baseelf": lambda root, v: baseelf_path(root, v).relative_to(root),
    "rom": lambda root, v: rom_path(root, v).relative_to(root),
    "layout": lambda root, v: layout(v),
    "source_roots": lambda root, v: " ".join(source_roots(v)),
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
