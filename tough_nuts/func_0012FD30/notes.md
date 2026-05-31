# func_0012FD30 — parked

VRAM: 0x0012FD30 (file_off 0x02FD30)
Asm source: asm/matchings/cod/02FD30/func_0012FD30.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO)

**TU:** `src/Texture.c`

**Seed:** `tough_nuts/func_0012FD30/func_0012FD30.c`

Disassembly:

```
.align 3
nonmatching func_0012FD30, 0x1C

glabel func_0012FD30
    /* 2FD30 0012FD30 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 2FD34 0012FD34 0000BFFF */  sd         $31, 0x0($29)
    /* 2FD38 0012FD38 BEB3040C */  jal        func_0012CEF8
    /* 2FD3C 0012FD3C 00000000 */   nop
    /* 2FD40 0012FD40 0000BFDF */  ld         $31, 0x0($29)
    /* 2FD44 0012FD44 0800E003 */  jr         $31
    /* 2FD48 0012FD48 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0012FD30
```

## Re-attempt 2026-05-31 (loop) — BLOCKED by toolchain, not a near-miss

Confirmed via plain-C `void func_0012FD30(void){ func_0012CEF8(); }`:
ee-gcc 2.9 emits `j func_0012CEF8` (sibling call, no frame), real_count=6.
Original keeps the full frame (`addiu sp,-0x10; sd ra; jal; ld ra; jr; addiu sp,+0x10`).

ee-gcc 2.9-991111 hardcodes sibling-call opt ON at -O2 and REJECTS
`-fno-optimize-sibling-calls`. There is NO zero-instruction pure-C defeat
(a volatile read/store adds an insn the asm doesn't have; an empty stmt
doesn't block sibcall). The ONLY mechanism is the empty `__asm__ __volatile__("")`
barrier == the deleted DEFEAT_TCO crutch (133 funcs parked for its removal).

Per current skill (no inline-asm matching nudges) this stays PARKED until
the real ICO compiler is identified (which presumably does not sibcall this
shape, making the plain wrapper match) or a sanctioned ROM-parity postprocess
is added. Do NOT re-introduce the barrier for a single func.
