# CheckFloorAttribute (sugipon/src/motionManager2) — RESUME

Best: **rc4** (nested-if while form, the seed `CheckFloorAttribute.c`).

## What it is (recovered)
```c
int CheckFloorAttribute(float *dst, void *a1) {
    unsigned char *src = a1;
    if (src[1] (signed lb) != 0) return 0;        // bnez -> ret0
    int count = src[3] (lbu);
    if (count == 0) return 0;                      // beqz -> ret0   (check #1)
    float *sp = (float*)(src + (src[2]*8 + 0x10)); // lbu*8, +0x10, addu(base) in beq delay
    // redundant loop ENTRY guard kept by ROM:
    while (count != 0) { *dst++ = *sp++; count--; }// beqz -> ret1   (check #2, redundant)
    return 1;                                       // L0EC ret1
    // ret0  L0F4 (placed LAST in ROM)
}
```
ROM layout: loop, then **ret1 (L0010A0EC)** then **ret0 (L0010A0F4)**.

## The residual (THE blocker)
ROM emits **TWO** `beqz $3` count guards on the same unmodified `count`:
- A0B8 `beqz $3,ret0` (explicit `if(count==0)return 0`)
- A0C8 `beqz $3,ret1` (the `while` **entry guard**, redundant, with `addu $2,$5,$2`
  = `sp=src+off` in its delay slot).

gcc **eliminates the second guard** in the nested form (it proves `count!=0`
inside the `if(count!=0)` scope) -> only one guard, check#1 delay = nop, offset
`addu` folds before the loop. That's the rc4 gap (≈3 insns: missing guard +
nop-fill + addu placement).

## Tried
- nested `if(count!=0){while(count!=0){}}` -> **rc4** (best) but second guard ELIMINATED.
- linear `if(count==0)return 0; while(...)` -> rc8: KEEPS the guard but as **bnel**
  (branch-likely) not beq, and ret0/ret1 layout SWAPPED (ret0 placed early).
- linear + `goto ret0;` tail (force ret0 last) -> rc5: STILL drops the 2nd guard +
  walking ptr reuses a1 (addu a1,a1,v0).
- offset parenthesized `src+(src[2]*8+0x10)` (to get sll;addiu;addu order) — folded.

## Next hypotheses
1. Force gcc to RETAIN the redundant entry guard: the linear form keeps it (rc8) but
   as bnel+wrong layout. Combine: linear `if(count==0)return 0;` + a `while` whose
   guard gcc emits as plain beqz to a SEPARATE `return 1` block placed after the loop,
   with ret0 forced last. The rc8 had it as bnel — investigate why branch-likely vs
   plain (maybe the loop body fills the guard delay -> annul). Try a `for(;count;count--)`
   or hoisting the `addu` so the guard delay takes it (plain beq).
2. The `addu` belongs in the 2nd-guard delay (ROM A0CC). Once the guard survives,
   express `sp = src + (src[2]*8+0x10)` so the base-`addu` is the last independent op
   at the guard point (it then slots into the beqz delay, plain not likely).
3. check#1 (A0B8) delay wants `lbu src[2]` — the offset's first load. Compute `src[2]`
   between the two checks so it's schedulable into check#1's delay.

Differ note: this TU's asm-differ misaligns on delay-slot fills; ALWAYS confirm with
`ninja` (build/.../motionManager2.o), not the differ's real_count, and beware the
match_loop scratch `.o` is NOT build/ (objdump build/ only AFTER a ninja).
