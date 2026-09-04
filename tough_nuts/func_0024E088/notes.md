# _dispatchMpegCallback — PARKED near-miss rc9 (not permuter-run)

VRAM 0x0024E088, common/src/PObj.c. vtable dispatch with fn-ptr call.
Caller-side decl is `void _dispatchMpegCallback(void*,void*)` but it RETURNS the fn's
return value (callers ignore it) — I changed the in-TU extern to `void*`.

## Shape (rc9 seed)
`if(!a0) return 0; tbl=a0->[0x40]; if(!tbl) return 0; e=tbl+(*a1<<3);
fn=e[0xC]; if(!fn) return 0; return fn(a0,a1,e[0x10]);`  rv defaults 0.
Note: rv = fn's RETURN ($2 after jalr), NOT the entry e (jalr clobbers v0).
fn called with $4=a0,$5=a1 unchanged + $6=e[0x10] set in the jalr delay.

## Residual rc9 (3 coupled issues, 5 sites)
1. rv accumulator reg: ROM $7/a3, gcc $6/a2 (sites 1,15,17).
2. tbl reg: ROM lw a2,64(a0); gcc lw v1,64(a0).
3. ROM RECOMPUTES e twice (addu v1 for fn lookup, addu v0 for the call) and
   fills the `beq fn,0` delay slot with the 2nd addu → plain **beq**. gcc
   CSEs e (one addu) → nothing to fill → **beql** (annulled). Need to force
   the e-address recompute so the beq delay is filled.
Tried: inline-addr, basefold ((tbl+off)+idx*8), idx_var, e[3]/e[4] — all rc9.

## RESUME
Force gcc to (a) recompute e's address after the fn!=0 check (fills beq delay,
kills beql) and (b) allocate rv to a3 / tbl to a2. Likely the e-recompute is the
root that cascades the regs. Try giving the fn-lookup and the call-arg/data
DIFFERENT rooted address expressions (dual-root, see
feedback_dual_root_addr_ptr_defeats_gcse) so gcse doesn't merge e.

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispatchMpegCallback/_dispatchMpegCallback.1.c`

Disassembly:

```
.align 3
nonmatching _dispatchMpegCallback, 0x50

glabel _dispatchMpegCallback
    /* 14E088 0024E088 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E08C 0024E08C 2D380000 */  daddu      $7, $0, $0
    /* 14E090 0024E090 0D008010 */  beqz       $4, .L0024E0C8
    /* 14E094 0024E094 0000BFFF */   sd        $31, 0x0($29)
    /* 14E098 0024E098 4000868C */  lw         $6, 0x40($4)
    /* 14E09C 0024E09C 0B00C010 */  beqz       $6, .L0024E0CC
    /* 14E0A0 0024E0A0 0000BFDF */   ld        $31, 0x0($29)
    /* 14E0A4 0024E0A4 0000A28C */  lw         $2, 0x0($5)
    /* 14E0A8 0024E0A8 C0100200 */  sll        $2, $2, 3
    /* 14E0AC 0024E0AC 2118C200 */  addu       $3, $6, $2
    /* 14E0B0 0024E0B0 0C00638C */  lw         $3, 0xC($3)
    /* 14E0B4 0024E0B4 05006010 */  beqz       $3, .L0024E0CC
    /* 14E0B8 0024E0B8 2110C200 */   addu      $2, $6, $2
    /* 14E0BC 0024E0BC 09F86000 */  jalr       $3
    /* 14E0C0 0024E0C0 1000468C */   lw        $6, 0x10($2)
    /* 14E0C4 0024E0C4 2D384000 */  daddu      $7, $2, $0
.align 2
  .L0024E0C8:
    /* 14E0C8 0024E0C8 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E0CC:
    /* 14E0CC 0024E0CC 2D10E000 */  daddu      $2, $7, $0
    /* 14E0D0 0024E0D0 0800E003 */  jr         $31
    /* 14E0D4 0024E0D4 1000BD27 */   addiu     $29, $29, 0x10
endlabel _dispatchMpegCallback
```

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 31 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispatchMpegCallback/_dispatchMpegCallback.2.c`

Disassembly:

```
.align 3
nonmatching _dispatchMpegCallback, 0x50

glabel _dispatchMpegCallback
    /* 14E088 0024E088 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E08C 0024E08C 2D380000 */  daddu      $7, $0, $0
    /* 14E090 0024E090 0D008010 */  beqz       $4, .L0024E0C8
    /* 14E094 0024E094 0000BFFF */   sd        $31, 0x0($29)
    /* 14E098 0024E098 4000868C */  lw         $6, 0x40($4)
    /* 14E09C 0024E09C 0B00C010 */  beqz       $6, .L0024E0CC
    /* 14E0A0 0024E0A0 0000BFDF */   ld        $31, 0x0($29)
    /* 14E0A4 0024E0A4 0000A28C */  lw         $2, 0x0($5)
    /* 14E0A8 0024E0A8 C0100200 */  sll        $2, $2, 3
    /* 14E0AC 0024E0AC 2118C200 */  addu       $3, $6, $2
    /* 14E0B0 0024E0B0 0C00638C */  lw         $3, 0xC($3)
    /* 14E0B4 0024E0B4 05006010 */  beqz       $3, .L0024E0CC
    /* 14E0B8 0024E0B8 2110C200 */   addu      $2, $6, $2
    /* 14E0BC 0024E0BC 09F86000 */  jalr       $3
    /* 14E0C0 0024E0C0 1000468C */   lw        $6, 0x10($2)
    /* 14E0C4 0024E0C4 2D384000 */  daddu      $7, $2, $0
.align 2
  .L0024E0C8:
    /* 14E0C8 0024E0C8 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E0CC:
    /* 14E0CC 0024E0CC 2D10E000 */  daddu      $2, $7, $0
    /* 14E0D0 0024E0D0 0800E003 */  jr         $31
    /* 14E0D4 0024E0D4 1000BD27 */   addiu     $29, $29, 0x10
endlabel _dispatchMpegCallback
```

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispatchMpegCallback/_dispatchMpegCallback.3.c`

Disassembly:

```
.align 3
nonmatching _dispatchMpegCallback, 0x50

glabel _dispatchMpegCallback
    /* 14E088 0024E088 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E08C 0024E08C 2D380000 */  daddu      $7, $0, $0
    /* 14E090 0024E090 0D008010 */  beqz       $4, .L0024E0C8
    /* 14E094 0024E094 0000BFFF */   sd        $31, 0x0($29)
    /* 14E098 0024E098 4000868C */  lw         $6, 0x40($4)
    /* 14E09C 0024E09C 0B00C010 */  beqz       $6, .L0024E0CC
    /* 14E0A0 0024E0A0 0000BFDF */   ld        $31, 0x0($29)
    /* 14E0A4 0024E0A4 0000A28C */  lw         $2, 0x0($5)
    /* 14E0A8 0024E0A8 C0100200 */  sll        $2, $2, 3
    /* 14E0AC 0024E0AC 2118C200 */  addu       $3, $6, $2
    /* 14E0B0 0024E0B0 0C00638C */  lw         $3, 0xC($3)
    /* 14E0B4 0024E0B4 05006010 */  beqz       $3, .L0024E0CC
    /* 14E0B8 0024E0B8 2110C200 */   addu      $2, $6, $2
    /* 14E0BC 0024E0BC 09F86000 */  jalr       $3
    /* 14E0C0 0024E0C0 1000468C */   lw        $6, 0x10($2)
    /* 14E0C4 0024E0C4 2D384000 */  daddu      $7, $2, $0
.align 2
  .L0024E0C8:
    /* 14E0C8 0024E0C8 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E0CC:
    /* 14E0CC 0024E0CC 2D10E000 */  daddu      $2, $7, $0
    /* 14E0D0 0024E0D0 0800E003 */  jr         $31
    /* 14E0D4 0024E0D4 1000BD27 */   addiu     $29, $29, 0x10
endlabel _dispatchMpegCallback
```

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispatchMpegCallback/_dispatchMpegCallback.4.c`

Disassembly:

```
.align 3
nonmatching _dispatchMpegCallback, 0x50

glabel _dispatchMpegCallback
    /* 14E088 0024E088 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E08C 0024E08C 2D380000 */  daddu      $7, $0, $0
    /* 14E090 0024E090 0D008010 */  beqz       $4, .L0024E0C8
    /* 14E094 0024E094 0000BFFF */   sd        $31, 0x0($29)
    /* 14E098 0024E098 4000868C */  lw         $6, 0x40($4)
    /* 14E09C 0024E09C 0B00C010 */  beqz       $6, .L0024E0CC
    /* 14E0A0 0024E0A0 0000BFDF */   ld        $31, 0x0($29)
    /* 14E0A4 0024E0A4 0000A28C */  lw         $2, 0x0($5)
    /* 14E0A8 0024E0A8 C0100200 */  sll        $2, $2, 3
    /* 14E0AC 0024E0AC 2118C200 */  addu       $3, $6, $2
    /* 14E0B0 0024E0B0 0C00638C */  lw         $3, 0xC($3)
    /* 14E0B4 0024E0B4 05006010 */  beqz       $3, .L0024E0CC
    /* 14E0B8 0024E0B8 2110C200 */   addu      $2, $6, $2
    /* 14E0BC 0024E0BC 09F86000 */  jalr       $3
    /* 14E0C0 0024E0C0 1000468C */   lw        $6, 0x10($2)
    /* 14E0C4 0024E0C4 2D384000 */  daddu      $7, $2, $0
.align 2
  .L0024E0C8:
    /* 14E0C8 0024E0C8 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E0CC:
    /* 14E0CC 0024E0CC 2D10E000 */  daddu      $2, $7, $0
    /* 14E0D0 0024E0D0 0800E003 */  jr         $31
    /* 14E0D4 0024E0D4 1000BD27 */   addiu     $29, $29, 0x10
endlabel _dispatchMpegCallback
```

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_dispatchMpegCallback/_dispatchMpegCallback.5.c`

Disassembly:

```
.align 3
nonmatching _dispatchMpegCallback, 0x50

glabel _dispatchMpegCallback
    /* 14E088 0024E088 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E08C 0024E08C 2D380000 */  daddu      $7, $0, $0
    /* 14E090 0024E090 0D008010 */  beqz       $4, .L0024E0C8
    /* 14E094 0024E094 0000BFFF */   sd        $31, 0x0($29)
    /* 14E098 0024E098 4000868C */  lw         $6, 0x40($4)
    /* 14E09C 0024E09C 0B00C010 */  beqz       $6, .L0024E0CC
    /* 14E0A0 0024E0A0 0000BFDF */   ld        $31, 0x0($29)
    /* 14E0A4 0024E0A4 0000A28C */  lw         $2, 0x0($5)
    /* 14E0A8 0024E0A8 C0100200 */  sll        $2, $2, 3
    /* 14E0AC 0024E0AC 2118C200 */  addu       $3, $6, $2
    /* 14E0B0 0024E0B0 0C00638C */  lw         $3, 0xC($3)
    /* 14E0B4 0024E0B4 05006010 */  beqz       $3, .L0024E0CC
    /* 14E0B8 0024E0B8 2110C200 */   addu      $2, $6, $2
    /* 14E0BC 0024E0BC 09F86000 */  jalr       $3
    /* 14E0C0 0024E0C0 1000468C */   lw        $6, 0x10($2)
    /* 14E0C4 0024E0C4 2D384000 */  daddu      $7, $2, $0
.align 2
  .L0024E0C8:
    /* 14E0C8 0024E0C8 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E0CC:
    /* 14E0CC 0024E0CC 2D10E000 */  daddu      $2, $7, $0
    /* 14E0D0 0024E0D0 0800E003 */  jr         $31
    /* 14E0D4 0024E0D4 1000BD27 */   addiu     $29, $29, 0x10
endlabel _dispatchMpegCallback
```
