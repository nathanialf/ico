# Reconstructed header: `ito/include/mv_defs.h`

Status: **DONE — the header is a real file at `ito/include/mv_defs.h`.**
This document is the recovery record: how the header's existence was proved
from the binary, and the levers that made its inline match. Read the real
file and `decomp/HEADERS.md` for the current form; read this for the *why*.

IP-clean: derived entirely from our own disassembly + the `__FILE__`/`__LINE__`
literals baked into the shipped ELF, no leaked source. The PAL disc listing
later confirmed the header independently (`mv_defs.h`, 16 host functions —
`decomp/pal_source_tree.md`).

> **Names below are aug6-era.** The recovery ran on the Aug-6-2001 prototype
> in 2026-06 (the quoted SHA-1 `2b4d7de4` is aug6's ROM). Every
> `func_00XXXXXX` in this file is an **aug6 VMA** and names nothing on PAL;
> the same callees are `iosMallocAlignDebug`, `func_001B6250` and `__assert`
> in the header as it stands today, and the assert entry point is
> `debug_Assert` on PAL. Read the code sample for its *shape* — the
> `fp = __FILE__` lever and the line-42/43 placement — not for its symbols.

## Why we know it exists

The shipped `.rodata` contains 8 copies of the C-string
`"../ito/include/mv_defs.h"` (the build ran from `ito/mpeg/`, so the
header lives at `ito/include/mv_defs.h`). It is the **only** `ito/include/*.h`
that emits any `__FILE__` literal. Each copy is referenced by exactly one
function (no cross-`.o` string dedup in ee-gcc 2.9), which both proves the
header is real and makes its rodata **per-TU attributable**.

## The single load-bearing artifact: one inline accessor at lines 42–43

Every consumer shows the identical instruction signature:

```
jal     deq_mes_th
 addiu  $8, $0, 0x2A        # 5th arg = __LINE__ = 42   (deq call is on line 42)
...
addiu   $5, $0, 0x2B        # __LINE__ = 43  -> func_001AAD00(file, 43)
addiu   $5, $0, 0x2B        # __LINE__ = 43  -> func_00260380(file, 43, "p != NULL")
```

A constant `__LINE__` (42 for the deq, 43 for the assert) across four
different `.c` files can only mean the code physically lives in the header
and is **inlined** into each consumer. The single file-string register
(`$18 = &"../ito/include/mv_defs.h"`) is CSE-reused across the `deq_mes_th`
call *and* both assert-handler calls — confirming the deq and the assert
share one `__FILE__`, i.e. one inline body.

Reconstructed body (offsets pinned by the `__LINE__` immediates):

```c
/* ito/include/mv_defs.h  (line numbers pinned to the binary) */
...
static inline void *mvDeqMes(<queue> q) {                      /* ~41 */
    void *p = deq_mes_th(q, 0x50000, 0x40, __FILE__, __LINE__); /* 42  -> line 42 = 0x2A */
    assert(p != NULL);                                          /* 43  -> line 43 = 0x2B */
    return p;
}
...
```

- `deq_mes_th` (`fumi/ios/message.c`) is the debug-instrumented IOS message
  dequeue; its last two params are `(__FILE__, __LINE__)`. Fixed call args:
  `(queue, 0x50000, 0x40, file, line)` — `0x50000`/`0x40` constant, the
  queue is the inline's parameter (e.g. `termAll` passes the global at
  `D_0062A340`, whose first word `0x0026347C` is the movie message queue).
- `assert(cond)` is a **custom 2-call handler**, not libc:
  `func_001AAD00(__FILE__, __LINE__)` then
  `func_00260380(__FILE__, __LINE__, #cond)` (`func_00260380` ∈
  `common/src/PObj.c`). It fires on the false branch (`p == 0`).

## Consumers (string copy → owning function)

| `__FILE__` copy | owner | TU | inlined |
|---|---|---|---|
| `D_00557060` | `termAll` | `ito/mpeg/mv_main` | ×1 |
| `D_005570C0` | `readBufBeginGet` | `ito/mpeg/mv_readbuf` | ×1 |
| `D_00557158` | `voBufDelete` | `ito/mpeg/mv_vobuf` | ×2 |
| `D_00614F10` | `func_00239E18` | `ito/mpeg/mv_sub` | ×1 |
| `D_00615190` | `func_0023BE80` | `common/src/GobjProc` | ×2 |
| `D_00557090`, `D_00615120`, `D_00615150` | (unreferenced dup copies) | — | — |

The unreferenced copies are duplicate string emissions whose code refs were
CSE'd/DCE'd away but whose rodata bytes remain (ee-gcc keeps unreferenced
string literals).

## Implications

1. **Source-fidelity check.** `__FILE__="../ito/include/mv_defs.h"` + line
   42/43 is a hard codegen fact in the ELF. Any dev-intended rewrite of
   these consumers that `#include "mv_defs.h"` and calls the `mvDeqMes`
   inline (deq on line 42, assert on line 43) will regenerate these exact
   strings — that's how we'll *prove* the reconstruction, not just match
   the text. Today `termAll` hand-expands the inline against the existing
   `D_005570xx` rodata symbols (byte-correct, structurally not dev-form).
2. **Data migration.** Because each TU owns its own string copies, the
   `mv_defs.h` rodata is cleanly carvable per-TU once the consumers are
   rewritten to emit the literals (literal-rewrite-at-TU-completion model,
   `[[project_aug6_data_model]]`).
3. To make `__FILE__` come out as `../ito/include/mv_defs.h`, the header
   must sit at `ito/include/mv_defs.h` and be `#include`d such that the
   opened path is `../ito/include/mv_defs.h` (build CWD = `ito/mpeg/`).
   That include-path plumbing is the open task before this can be the
   real source form.

## Update — header materialized (func_ naming) + build mechanism + open match

- The header now exists at `ito/include/mv_defs.h`. The inline is named
  `deq_movie_mes` (placeholder — inlined everywhere, no MAIN.MAP symbol; per
  user, `func_`-style not an invented API name).
- **Build mechanism** (in `tools/compile_c.sh`, opt-in via `config/include_ito.txt`):
  to bake `__FILE__` as exactly `"../ito/include/mv_defs.h"`, the listed TU is
  compiled from CWD `${ROOT}/ito` with a *relative* `-I../ito/include` (ee-gcc
  records the `-I` spelling verbatim into `__FILE__`; an absolute `-I` gives an
  absolute string). Proven: emits the exact string + deq@L42/assert@L43.
- **Rodata carve** `[0x457060, 0x457090)` (mv_main's file + "p != NULL") is
  proven byte-neutral as a plain blob split; with the header the strings come
  from `mv_main.o` and the blob is carved.
- **OPEN — permuter-class regalloc swap.** A consumer (`termAll`) rewritten to
  call `deq_movie_mes` does NOT byte-match: ee-gcc's inliner gives the `__FILE__`
  pointer `$s1` and the struct param `$s2`, the reverse of the ROM (struct `$s1`,
  file `$s2`), costing one `move`. The swap is invariant across ~15 reshapes
  (store order ×6, caller CFG ×5, inline keyword ×3, queue-as-param). The
  hand-written `termAll` (extern `D_005570xx`) matches and is what's committed;
  the inline form is parked pending a permuter/structural crack.

## RESOLVED — the inline matches (the `fp = __FILE__` lever)

The $s1/$s2 regalloc swap is cracked. Root cause: when ee-gcc inlines the
accessor, an inline-body `__FILE__` used directly at the deq + asserts gets a
live range that out-prioritises the struct param for $s1. **Materialising the
file pointer into a local once, before the deq, fixes it:**

```c
static __inline int deq_movie_mes(int size)
{
    int p; const char *fp = __FILE__;
    p = deq_mes_th(D_0062A340, size, 0x40, fp, __LINE__);   /* line 42 */
    if (p == NULL) { func_001AAD00(fp, __LINE__);           /* line 43 */
                     func_00260380(fp, __LINE__, "p != NULL"); }
    func_00260568(p, 0, size);
    return p;
}
```

With this, `termAll` rewritten as `int rv = deq_movie_mes(0x50000); ...` and the
`[0x457060,0x457090)` rodata carve, the whole ELF is byte-identical (sha1
2b4d7de4). The line numbers (deq=42, assert=43) are the dev's own __LINE__
instrumentation -- the header must keep those statements on those physical
lines. This is the template for the other four consumers (readBufBeginGet,
voBufDelete, func_00239E18, func_0023BE80) when they're matched.
