#!/usr/bin/env python3
"""
extract_elf.py — pull the EE-side boot ELF (SLUS_202.18) out of the user's
ICO disc image (.bin/.cue), record its SHA-1, and dump a hint about the
compiler fingerprint.

Handles MODE1/2352 and MODE2/2352 raw .bin sectors by extracting the 2048-
byte user data and feeding the resulting ISO9660 image to pycdlib.

Idempotent — re-runs are cheap once baseelf.elf exists.
"""

from __future__ import annotations

import hashlib
import io
import re
import sys
from pathlib import Path

import pycdlib

REPO_ROOT = Path(__file__).resolve().parent.parent
BASEROM_DIR = REPO_ROOT / "baserom"
BIN = BASEROM_DIR / "Ico_USA.bin"
CUE = BASEROM_DIR / "Ico_USA.cue"
ELF = BASEROM_DIR / "baseelf.elf"
ROM = BASEROM_DIR / "baseelf.rom"      # objcopy -O binary view, splat's input
ISO = BASEROM_DIR / "Ico_USA.iso"  # cached cooked ISO (gitignored)
SHA1SUMS = REPO_ROOT / "config" / "sha1sums.txt"

OBJCOPY_CANDIDATES = (
    "mips64r5900el-ps2-elf-objcopy",
    "mips-linux-gnu-objcopy",
    "objcopy",
)

SYSTEM_CNF = "SYSTEM.CNF"

LOGICAL_SECTOR_SIZE = 2048
RAW_SECTOR_SIZE = 2352


def parse_cue_mode(cue_path: Path) -> str:
    """Return e.g. 'MODE1/2352' or 'MODE2/2352' from the cue file."""
    text = cue_path.read_text(errors="replace")
    m = re.search(r"TRACK\s+\d+\s+(MODE\d/\d+)", text)
    if m is None:
        raise SystemExit(f"extract_elf: can't parse mode from {cue_path}")
    return m.group(1).upper()


def cook_iso(bin_path: Path, mode: str, out_path: Path) -> None:
    """Convert a raw .bin to a cooked .iso (one 2048-byte sector per logical sector)."""
    if mode == "MODE1/2352":
        data_offset = 16  # 12 sync + 4 header
    elif mode == "MODE2/2352":
        # Mode 2 Form 1: 12 sync + 4 header + 8 subheader = 24
        data_offset = 24
    elif mode == "MODE1/2048":
        # already cooked — just copy / symlink
        out_path.write_bytes(bin_path.read_bytes())
        return
    else:
        raise SystemExit(f"extract_elf: unsupported mode {mode}")

    size = bin_path.stat().st_size
    if size % RAW_SECTOR_SIZE != 0:
        print(f"extract_elf: warning — bin size {size} is not a multiple of "
              f"{RAW_SECTOR_SIZE}; truncating", file=sys.stderr)
    n_sectors = size // RAW_SECTOR_SIZE
    print(f"extract_elf: cooking {bin_path.name} "
          f"({mode}, {n_sectors} sectors → {n_sectors * LOGICAL_SECTOR_SIZE} bytes)")

    with bin_path.open("rb") as src, out_path.open("wb") as dst:
        # Iterate in chunks of 256 sectors for I/O efficiency.
        chunk_sectors = 256
        chunk_size = chunk_sectors * RAW_SECTOR_SIZE
        for _ in range(0, n_sectors, chunk_sectors):
            buf = src.read(chunk_size)
            if not buf:
                break
            for i in range(0, len(buf), RAW_SECTOR_SIZE):
                dst.write(buf[i + data_offset : i + data_offset + LOGICAL_SECTOR_SIZE])


def extract_iso_file(iso_path: Path, iso_member: str, out_path: Path) -> None:
    """Use pycdlib to extract a named file from an ISO9660 image."""
    iso = pycdlib.PyCdlib()
    iso.open(str(iso_path))
    try:
        # ISO9660 stores filenames with version suffix, e.g. ;1.
        candidate_paths = [f"/{iso_member};1", f"/{iso_member}"]
        last_err: Exception | None = None
        for p in candidate_paths:
            try:
                buf = io.BytesIO()
                iso.get_file_from_iso_fp(buf, iso_path=p)
                out_path.write_bytes(buf.getvalue())
                return
            except pycdlib.pycdlibexception.PyCdlibException as exc:
                last_err = exc
                continue
        raise SystemExit(
            f"extract_elf: '{iso_member}' not found at any of {candidate_paths} "
            f"({last_err})"
        )
    finally:
        iso.close()


def boot_path_from_system_cnf(iso_path: Path) -> str:
    """Read SYSTEM.CNF and return the boot ELF filename it points at.

    SYSTEM.CNF format:
        BOOT2 = cdrom0:\\SCUS_971.13;1
        VER = 1.00
        VMODE = NTSC
    """
    iso = pycdlib.PyCdlib()
    iso.open(str(iso_path))
    try:
        buf = io.BytesIO()
        iso.get_file_from_iso_fp(buf, iso_path=f"/{SYSTEM_CNF};1")
        text = buf.getvalue().decode("ascii", errors="replace")
    finally:
        iso.close()

    for line in text.splitlines():
        line = line.strip()
        if not line.upper().startswith("BOOT2"):
            continue
        # everything after '=', strip 'cdrom0:\' and ';1'
        _, _, rhs = line.partition("=")
        rhs = rhs.strip()
        rhs = re.sub(r"^cdrom0:\\?", "", rhs, flags=re.IGNORECASE)
        rhs = rhs.lstrip("\\/")
        rhs = rhs.split(";")[0]
        return rhs
    raise SystemExit(f"extract_elf: no BOOT2 line in {SYSTEM_CNF}")


def sha1_of(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def update_sha1sums(name: str, sha1: str) -> str | None:
    """Record (or verify) sha1 for `name` in config/sha1sums.txt.
    Returns the existing hash if there was a mismatch, else None.
    """
    lines: list[str] = []
    if SHA1SUMS.exists():
        for line in SHA1SUMS.read_text().splitlines():
            stripped = line.strip()
            if not stripped or stripped.startswith("#"):
                lines.append(line)
                continue
            parts = stripped.split()
            if len(parts) >= 2 and parts[1] == name:
                if parts[0] != sha1:
                    return parts[0]
                # already recorded and matching
                return None
            lines.append(line)
    lines.append(f"{sha1}  {name}")
    SHA1SUMS.write_text("\n".join(lines) + "\n")
    return None


def dump_comment_section(elf_path: Path) -> None:
    """Best-effort .comment dump for compiler fingerprint hint."""
    try:
        from elftools.elf.elffile import ELFFile
    except ImportError:
        return
    try:
        with elf_path.open("rb") as f:
            elf = ELFFile(f)
            sec = elf.get_section_by_name(".comment")
            if sec is None:
                return
            data = sec.data()
            # .comment is a series of NUL-terminated strings.
            strings = [s.decode("utf-8", errors="replace") for s in data.split(b"\x00") if s]
            print()
            print("==> .comment section (compiler fingerprint hint):")
            for s in strings:
                print(f"     {s!r}")
    except Exception as exc:
        print(f"extract_elf: .comment dump failed ({exc})", file=sys.stderr)


def main() -> int:
    if not BIN.exists():
        print(f"extract_elf: missing {BIN}", file=sys.stderr)
        print(f"  Copy your disc image:", file=sys.stderr)
        print(f"    cp '/path/to/Ico (USA).bin'  {BIN}", file=sys.stderr)
        print(f"    cp '/path/to/Ico (USA).cue'  {CUE}", file=sys.stderr)
        return 1
    if not CUE.exists():
        print(f"extract_elf: missing {CUE}", file=sys.stderr)
        return 1

    # 1. cook .bin → .iso (idempotent)
    if not ISO.exists():
        mode = parse_cue_mode(CUE)
        cook_iso(BIN, mode, ISO)
        print(f"==> wrote {ISO}")

    # 2. pull the boot ELF (name comes from SYSTEM.CNF — varies by region/title)
    if not ELF.exists():
        boot_name = boot_path_from_system_cnf(ISO)
        print(f"==> SYSTEM.CNF BOOT2: {boot_name}")
        print(f"==> extracting {boot_name} → {ELF}")
        extract_iso_file(ISO, boot_name, ELF)
    else:
        print(f"==> {ELF} already present")

    if not ELF.exists() or ELF.stat().st_size == 0:
        print("extract_elf: extraction produced empty ELF", file=sys.stderr)
        return 2

    # 3. SHA-1 record / verify
    sha1 = sha1_of(ELF)
    print(f"==> {ELF.name} SHA-1: {sha1}")
    mismatch = update_sha1sums("baseelf.elf", sha1)
    if mismatch is not None:
        print(f"extract_elf: SHA-1 mismatch with recorded value!", file=sys.stderr)
        print(f"  recorded: {mismatch}", file=sys.stderr)
        print(f"  actual:   {sha1}", file=sys.stderr)
        print("Either your disc image is a different revision, or the recorded",
              file=sys.stderr)
        print(f"hash is wrong. Do not blindly update {SHA1SUMS} — consult the",
              file=sys.stderr)
        print("maintainer first.", file=sys.stderr)
        return 4
    print(f"==> SHA-1 recorded/verified in {SHA1SUMS.relative_to(REPO_ROOT)}")

    # 4. produce baseelf.rom (objcopy -O binary view) — splat's input
    if not ROM.exists() or ROM.stat().st_mtime < ELF.stat().st_mtime:
        import shutil as _sh
        import subprocess as _sp
        objcopy = next((c for c in OBJCOPY_CANDIDATES if _sh.which(c)), None)
        if objcopy is None:
            print(
                "extract_elf: no objcopy on PATH; install binutils-mips-linux-gnu",
                file=sys.stderr,
            )
            return 5
        print(f"==> {objcopy} -O binary --gap-fill=0x00 {ELF.name} {ROM.name}")
        _sp.run(
            [objcopy, "-O", "binary", "--gap-fill=0x00", str(ELF), str(ROM)],
            check=True,
        )
    rom_sha1 = sha1_of(ROM)
    print(f"==> {ROM.name} SHA-1: {rom_sha1}")
    rom_mismatch = update_sha1sums("baseelf.rom", rom_sha1)
    if rom_mismatch is not None:
        print(f"extract_elf: .rom SHA-1 mismatch! recorded={rom_mismatch} actual={rom_sha1}",
              file=sys.stderr)
        return 6

    # 5. compiler fingerprint hint
    dump_comment_section(ELF)

    print()
    print(f"extract_elf: done. ELF at {ELF}, ROM at {ROM}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
