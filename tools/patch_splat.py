#!/usr/bin/env python3
"""
patch_splat.py — apply local fixes to the pip-installed splat64 package.

ICO needs splat to emit `$ACC` / `$Q` (the r5900 special VU0 registers)
with the `$` prefix in per-function .s files inside a c subseg's
nonmatchings directory. Upstream splat only applies this fix for the
make_full_disasm_for_code path; per-function emits leave `ACC` / `Q`
bare, which mips-as rejects.

Idempotent: skips files that already contain the patch marker.
Re-run via `tools/build.sh setup` after every pip install / venv
rebuild — the patch only sticks until the package is reinstalled.
"""
from __future__ import annotations

import os
import re
import sys
from pathlib import Path

MARKER = "# ICO_PATCH: r5900 $ACC/$Q dollar-prefix fix"

def find_splat_c_py() -> Path | None:
    """Find the installed splat's c.py."""
    try:
        import splat
    except ImportError:
        return None
    splat_dir = Path(splat.__file__).parent
    candidate = splat_dir / "segtypes" / "common" / "c.py"
    return candidate if candidate.exists() else None


PATCH_INSERT_AFTER = (
    "            rabbitizer.config.regNames_namedRegisters = named_registers_opt"
)

PATCH = """
        # ICO_PATCH: r5900 $ACC/$Q dollar-prefix fix
        # Splat's per-func emit path leaves `ACC` / `Q` bare; mips-as
        # / ee-as require `$ACC` / `$Q`. Post-process the .s file to
        # add the prefix in operand positions.
        if options.opts.platform == "ps2":
            import re as _ico_re
            _ico_text = outpath.read_text()
            _ico_text = _ico_re.sub(r'([\\t ,])(ACC|Q)\\b', r'\\1$\\2', _ico_text)
            outpath.write_text(_ico_text)
"""


def main() -> int:
    c_py = find_splat_c_py()
    if c_py is None:
        print("patch_splat: splat not importable; nothing to patch.")
        return 0

    text = c_py.read_text()
    if MARKER in text:
        print(f"patch_splat: {c_py} already patched.")
        return 0

    if PATCH_INSERT_AFTER not in text:
        print(
            f"patch_splat: anchor line not found in {c_py}; splat may have "
            "changed upstream. Skipping patch.",
            file=sys.stderr,
        )
        return 1

    # Insert PATCH right after the anchor line.
    text = text.replace(
        PATCH_INSERT_AFTER,
        PATCH_INSERT_AFTER + PATCH.rstrip(),
        1,
    )
    c_py.write_text(text)
    print(f"patch_splat: applied to {c_py}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
