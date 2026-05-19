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

# Second patch: make get_global_asm_funcs follow #include "X.c.inc"
# directives so INCLUDE_ASM declarations inside .c.inc fragments
# are visible to splat. Without this, funcs declared INCLUDE_ASM
# inside a `.c.inc` end up in `asm/matchings/` instead of
# `asm/nonmatchings/` and the macro path fails at link time.
INC_MARKER = "# ICO_PATCH: scan .c.inc includes"
INC_ANCHOR = '        text = CommonSegC.strip_c_comments(c_file.read_text(encoding="utf-8"))'
INC_PATCH = """
        # ICO_PATCH: scan .c.inc includes
        # Expand any `#include "X.c.inc"` (and `.h` for completeness)
        # so INCLUDE_ASM directives inside those fragments are visible.
        import re as _ico_inc_re
        _ico_seen = set()
        def _ico_expand(c_path, depth=0):
            if depth > 4: return ""
            try:
                t = c_path.read_text(encoding="utf-8")
            except Exception:
                return ""
            out_parts = [t]
            for _m in _ico_inc_re.finditer(r'^\\s*#\\s*include\\s+"([^"]+\\.c\\.inc)"', t, _ico_inc_re.MULTILINE):
                _inc_name = _m.group(1)
                _inc_path = c_path.parent / _inc_name
                if not _inc_path.exists() or str(_inc_path) in _ico_seen:
                    continue
                _ico_seen.add(str(_inc_path))
                out_parts.append(_ico_expand(_inc_path, depth+1))
            return "\\n".join(out_parts)
        text = CommonSegC.strip_c_comments(_ico_expand(c_file))
"""


def main() -> int:
    c_py = find_splat_c_py()
    if c_py is None:
        print("patch_splat: splat not importable; nothing to patch.")
        return 0

    text = c_py.read_text()
    changed = False

    if MARKER not in text:
        if PATCH_INSERT_AFTER not in text:
            print(
                f"patch_splat: anchor line not found in {c_py}; splat may have "
                "changed upstream. Skipping ACC/Q patch.",
                file=sys.stderr,
            )
        else:
            text = text.replace(
                PATCH_INSERT_AFTER,
                PATCH_INSERT_AFTER + PATCH.rstrip(),
                1,
            )
            changed = True
            print(f"patch_splat: ACC/Q fix applied to {c_py}")

    if INC_MARKER not in text:
        if INC_ANCHOR not in text:
            print(
                f"patch_splat: .c.inc anchor not found in {c_py}; splat may "
                "have changed upstream. Skipping .c.inc-scan patch.",
                file=sys.stderr,
            )
        else:
            # Replace ALL occurrences — the anchor pattern appears in
            # both get_funcs_defined_in_c and get_global_asm_funcs (and
            # get_global_asm_rodata_syms). All three need .c.inc visibility.
            n_subs = text.count(INC_ANCHOR)
            text = text.replace(INC_ANCHOR, INC_PATCH.rstrip())
            changed = True
            print(f"patch_splat: .c.inc-scan applied to {c_py} ({n_subs} sites)")

    if changed:
        c_py.write_text(text)
    else:
        print(f"patch_splat: {c_py} already patched.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
