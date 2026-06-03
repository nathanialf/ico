# func_0025CC70 — parked

VRAM: 0x0025CC70 (file_off 0x15CC70)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025CC70.s

## Attempt at 2026-06-03

**Reason parked:** rc2 fabsf bit-twiddle (mfc1+lui 0x7fff+ori+and+mtc1 $f0). Pure-C plateau at 30/30: gcc emits 'mfc1 a0; move v1,a0' where ROM has 'mfc1 v1' directly — a coalescing miss between the mfc1-result pseudo and the and-chain pseudo. INVARIANT to source shape: tried 30 distinct forms incl __builtin_fabsf (itself rc2), static-inline helper, every union member/order, two-union, pointer-union, struct-cast, address-of-param, CFG wrappers (do-while/if/comma), mask lowerings (~0x80000000, >>1, named-var, static-const), 64-bit width, writeback. Cookbook 7.3 fingerprint — historically FABSF_BIT_TWIDDLE (retired). No FP reg pin per fp-licm playbook. Left for offline auto_permute.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025CC70/func_0025CC70.c`

Disassembly:

```
.align 3
nonmatching func_0025CC70, 0x1C

glabel func_0025CC70
    /* 15CC70 0025CC70 00600344 */  mfc1       $3, $f12
    /* 15CC74 0025CC74 FF7F023C */  lui        $2, (0x7FFFFFFF >> 16)
    /* 15CC78 0025CC78 FFFF4234 */  ori        $2, $2, (0x7FFFFFFF & 0xFFFF)
    /* 15CC7C 0025CC7C 24186200 */  and        $3, $3, $2
    /* 15CC80 0025CC80 00008344 */  mtc1       $3, $f0
    /* 15CC84 0025CC84 0800E003 */  jr         $31
    /* 15CC88 0025CC88 00000000 */   nop
endlabel func_0025CC70
    /* 15CC8C 0025CC8C 00000000 */  nop
```

## In-loop permuter shot (full park procedure) — FAILED to run
Fired the Step-4 10-min permuter shot at park (CFLAGS = exact quick_diff flags).
It could not even compile the base: `Error: unrecognized opcode 'endlabel
func_002484A4'` — the permuter's standalone assembler doesn't define the repo's
`endlabel` asm-macro present in the extracted PObj TU context. Exited "no
permutation matched (permuter exit=0)". This is a permuter-infra limitation for
this coalesced TU, NOT a matching result. offline auto_permute will likely hit
the same import error. Hand 30-stall stands (mfc1 reg-pick invariant; even
__builtin_fabsf is rc2). §7.3 fabsf — needs the retired FABSF_BIT_TWIDDLE idiom.
