# Reconstructed header: `ito/include/mv_defs.h`

Status: **reconstructed from binary, not yet a real file in the tree.**
Recovered 2026-06-08 while matching `ito/mpeg/mv_main`. IP-clean: derived
entirely from our own disassembly + `__FILE__`/`__LINE__` literals baked
into the shipped ELF, no leaked source.

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
