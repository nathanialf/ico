"""Shared version-slug detection for ICO tooling.

Retail `main` has config/ico.us.yaml (+ baserom/baseelf.elf); the aug6 prototype
branch has config/ico.aug6.yaml (+ baserom/aug6/baseelf.elf). Explicit VERSION
env wins; else auto-detect from which config exists.
"""
from __future__ import annotations
import os
from pathlib import Path

def detect_version(repo_root: Path) -> str:
    v = os.environ.get("VERSION")
    if v:
        return v
    if (repo_root / "config" / "ico.us.yaml").exists():
        return "us"
    if (repo_root / "config" / "ico.aug6.yaml").exists():
        return "aug6"
    return "us"

def baseelf_path(repo_root: Path, version: str) -> Path:
    return repo_root / "baserom" / ("baseelf.elf" if version == "us" else f"{version}/baseelf.elf")
