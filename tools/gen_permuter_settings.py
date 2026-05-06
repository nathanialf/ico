#!/usr/bin/env python3
"""Generate `permuter_settings.toml` at the project root for ICO.

decomp-permuter (vendored at `lib/decomp-permuter/`) reads
`permuter_settings.toml` from the repo root or `tools/`. The settings
file controls:

  - `compiler_type`        — codegen backend the permuter targets. We
                              use `gcc` (the closest entry in
                              `default_weights.toml` for ee-gcc 2.96).
  - `[preserve_macros]`    — regex -> C-type-string. Macros whose name
                              matches a regex are left un-expanded by
                              the permuter's `cpp` pass and treated as
                              opaque expressions of the given type. The
                              ICO project has only a small handful of
                              helper macros today; this list will grow
                              as `include/` evolves.
  - `[decompme.compilers]` — map our local ee-gcc 2.96 binary path to a
                              decomp.me compiler ID, so `import.py
                              --decompme` can post scratches for this
                              project.

Why a generator instead of a hand-written file:

  - The ee-gcc path is environment-dependent (`EEGCC` env, default
    `tools/cc/ee-gcc2.96/bin/gcc`). We resolve it the same way
    `tools/quick_diff.sh` and `tools/permute_run.sh` do.
  - Re-running this script after adding a new family of helper macros
    in `include/` keeps the list honest.

Schema reference: `lib/decomp-permuter/permuter_settings_example.toml`.
Keys in `[preserve_macros]` are anchored regex patterns; values are
the C type the permuter should pretend the macro expands to.

Usage:
    tools/gen_permuter_settings.py            # idempotent rewrite
    EEGCC=/path/to/cc tools/gen_permuter_settings.py
"""

from __future__ import annotations

import os
import sys
from pathlib import Path
from typing import List, Tuple

PROJECT_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_EEGCC = PROJECT_ROOT / "tools" / "cc" / "ee-gcc2.96" / "bin" / "gcc"
HEADER_COMMENT = (
    "# permuter_settings.toml — managed by tools/gen_permuter_settings.py.\n"
    "# Re-run that script to regenerate (e.g. after `EEGCC=` changes or new\n"
    "# project macros land in `include/`). Do not hand-edit; edits are lost.\n"
)


# (regex_pattern, expansion_type)
#
# Patterns are matched anchored (the permuter wraps them in `^(?:...)$`).
# Keep the list curated — every entry is something we expect to see in
# matchable ICO C. The ICO codebase is early-stage so this is short.
# Add new entries as helper macros land in `include/`.
_PRESERVE_PATTERNS: List[Tuple[str, str]] = [
    # NULL is a constant pointer; the permuter treats it as `void *`-ish.
    ("NULL", "void *"),
    # Generic helper macros — drop in patterns even if not yet present.
    ("ARRAY_COUNT", "u32"),
    ("ARRAY_COUNTU", "u32"),
    ("ABS", "s32"),
    ("CLAMP", "s32"),
    ("CLAMP_MAX", "s32"),
    ("CLAMP_MIN", "s32"),
    ("SQ", "s32"),
    ("MIN", "s32"),
    ("MAX", "s32"),
    # PS2 / SCE prefixed APIs — when these eventually appear in headers,
    # we want the permuter to leave them intact rather than try to expand
    # SDK macros into raw bytes.
    ("sce[A-Z][A-Za-z0-9_]*", "s32"),
    ("SCE_[A-Z0-9_]+", "s32"),
]


def resolve_eegcc() -> str:
    """Mirror EEGCC resolution from tools/quick_diff.sh and
    tools/permute_run.sh: `EEGCC` env override, else
    `tools/cc/ee-gcc2.96/bin/gcc` under the project root."""
    eegcc = os.environ.get("EEGCC")
    if eegcc:
        return eegcc
    return str(DEFAULT_EEGCC)


def _toml_quote(s: str) -> str:
    # Basic TOML basic-string quoting — enough for our paths/types which
    # never contain quotes, backslashes, or control chars. Bail loudly
    # if that assumption breaks so we don't silently emit invalid TOML.
    if any(c in s for c in ('"', "\\", "\n", "\t")):
        raise ValueError(f"value needs richer TOML escaping: {s!r}")
    return f'"{s}"'


def render_toml(eegcc: str) -> str:
    out = [HEADER_COMMENT]
    out.append("\n")
    # ee-gcc 2.96 is closer to the `gcc` weight set than `ido` / `mwcc`.
    # If we ever wire a custom weight family for ee-gcc, switch this and
    # add an entry to lib/decomp-permuter/default_weights.toml.
    out.append('compiler_type = "gcc"\n')
    out.append("\n")

    out.append("[preserve_macros]\n")
    out.append("# Regex pattern -> C type the permuter pretends the macro returns.\n")
    out.append("# Patterns are anchored by the permuter (`^(?:...)$`).\n")
    for pattern, type_str in _PRESERVE_PATTERNS:
        out.append(f"{_toml_quote(pattern)} = {_toml_quote(type_str)}\n")
    out.append("\n")

    out.append("[decompme.compilers]\n")
    out.append("# Local ee-gcc binary path -> decomp.me compiler ID. fnmatch on\n")
    out.append("# the full compiler[0] path. There is no canonical decomp.me ID\n")
    out.append("# for ee-gcc 2.96 yet — `ee-gcc-2.96` is a placeholder; update\n")
    out.append("# once decomp.me adds a matching preset.\n")
    out.append(f"{_toml_quote(eegcc)} = \"ee-gcc-2.96\"\n")
    out.append('"*/ee-gcc2.96/bin/gcc" = "ee-gcc-2.96"\n')

    return "".join(out)


def main() -> int:
    eegcc = resolve_eegcc()
    body = render_toml(eegcc)

    out_path = PROJECT_ROOT / "permuter_settings.toml"
    # Idempotent write: only touch the file if contents actually changed.
    if out_path.exists():
        old = out_path.read_text(encoding="utf-8")
        if old == body:
            print(f"permuter_settings.toml unchanged ({out_path})")
            return 0

    out_path.write_text(body, encoding="utf-8")
    print(f"wrote {out_path}")
    print("  compiler_type = gcc")
    print(f"  ee-gcc       = {eegcc}")
    print(f"  preserve_macros patterns: {len(_PRESERVE_PATTERNS)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
