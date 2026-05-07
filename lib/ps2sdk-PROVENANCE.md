# lib/ps2sdk — provenance

`lib/ps2sdk/` is a git submodule pointing at the open-source PS2 SDK.
This file lives outside the submodule tree because submodules carry
their own `.git` and we do not modify upstream files in-tree
(per `docs/LEGAL.md`).

| field            | value                                              |
| ---------------- | -------------------------------------------------- |
| upstream         | <https://github.com/ps2dev/ps2sdk>                 |
| pinned commit    | `586784c0900b9fdec4dd820ef46c2155d2fae94f`         |
| pinned date      | 2026-05-04                                         |
| date pulled      | 2026-05-07                                         |
| license          | Academic Free License v. 2.0 (`lib/ps2sdk/LICENSE`)|
| spdx identifier  | `AFL-2.0`                                          |
| project license  | MIT (top-level `LICENSE`); AFL-2.0 governs only    |
|                  | the contents of `lib/ps2sdk/`.                     |

## Why it's here

`docs/LEGAL.md` ("Vendoring (open-source PS2 SDK headers)") explicitly
permits vendoring the `ps2dev` family because those projects are
themselves clean-room community work. We use it as:

- A **reference for EE kernel calling conventions and syscall macros**
  — `ee/kernel/src/kernel.S` defines `SYSCALL_SPECIAL`, whose body
  (`li $3, NUM; syscall; jr $31; nop`) is the same shape that several
  small handwritten leaves in the original ICO ELF take.
- A **reference for sdata / sbss / scommon layout** when interpreting
  splat-emitted symbol tables.
- A **future runtime source** if/when we begin linking decompiled C
  against open-source EE kernel stubs (not currently wired into the
  build).

## What is NOT changed in-tree

Per `docs/LEGAL.md`: we do **not** modify upstream files inside
`lib/ps2sdk/`. If a change is needed, fork upstream and re-point the
submodule URL in `.gitmodules`.

## License compatibility

AFL-2.0 is OSI-approved and FSF-recognised as a free-software licence.
It is permissive (similar in spirit to BSD/MIT) but adds:

- A patent-retaliation termination clause (§10).
- An attribution requirement (§5): the original copyright notice and
  licence text must be retained — preserved via the upstream
  `lib/ps2sdk/LICENSE` file.

Combining AFL-2.0 vendored material with this project's MIT licence is
compatible: AFL-2.0 governs only the contents of `lib/ps2sdk/`; our
own first-party source remains MIT.
