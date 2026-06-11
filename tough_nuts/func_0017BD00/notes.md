# func_0017BD00 — parked

VRAM: 0x0017BD00 (file_off 0x07BD00)
Asm source: asm/aug6/nonmatchings/script/src/st25a/func_0017BD00.s

## Attempt at 2026-06-11

**Reason parked:** rc3 fresh: p=ACTGameCollisionOn(); return p ? p->0x8==a1 : 0. Coalescing+branch tie: ROM copies call-result p->$3 + plain beq, ret in $2 (return reg); gcc keeps p in $2 and either beql-annuls (ternary, rc3) or puts ret in $5 + moves (if-form, rc6). ~25 forms (ternary/if/goto/both-arms/vol-load/typed/operand-swap) all rc3-13. permuter-class (return-value coalescing, cf actWaySystemCore-inverse).

**TU:** `script/src/st25a.c`

**Seed:** `tough_nuts/func_0017BD00/func_0017BD00.c`

Disassembly:

```
.align 3
nonmatching func_0017BD00, 0x3C

glabel func_0017BD00
    /* 7BD00 0017BD00 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 7BD04 0017BD04 0000B0FF */  sd         $16, 0x0($29)
    /* 7BD08 0017BD08 1000BFFF */  sd         $31, 0x10($29)
    /* 7BD0C 0017BD0C 1A24050C */  jal        ACTGameCollisionOn
    /* 7BD10 0017BD10 2D80A000 */   daddu     $16, $5, $0
    /* 7BD14 0017BD14 2D184000 */  daddu      $3, $2, $0
    /* 7BD18 0017BD18 04006010 */  beqz       $3, .L0017BD2C
    /* 7BD1C 0017BD1C 2D100000 */   daddu     $2, $0, $0
    /* 7BD20 0017BD20 0800628C */  lw         $2, 0x8($3)
    /* 7BD24 0017BD24 26105000 */  xor        $2, $2, $16
    /* 7BD28 0017BD28 0100422C */  sltiu      $2, $2, 0x1
.align 2
  .L0017BD2C:
    /* 7BD2C 0017BD2C 1000BFDF */  ld         $31, 0x10($29)
    /* 7BD30 0017BD30 0000B0DF */  ld         $16, 0x0($29)
    /* 7BD34 0017BD34 0800E003 */  jr         $31
    /* 7BD38 0017BD38 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0017BD00
    /* 7BD3C 0017BD3C 00000000 */  nop
```

## Fresh attempt 2026-06-11: rc6 -> rc3, stall=30 -> permute
p=ACTGameCollisionOn(); ret = p ? (p->0x8==a1) : 0; a1 saved in s0 across the call.
ROM: daddu $3,$2 (copy call-result p) + plain beq $3; ret stays in $2 (return reg), default 0 in
the beqz delay; comparison = xor+sltiu in $2. gcc instead keeps p in $2 and either (ternary) emits
beql annulling the p->0x8 load [rc3, residual=copy+beq vs beql], or (if-form) puts ret in $5 and
moves $2,$5 at the end [rc6]. ~25 distinct hand forms all rc3-13; the copy of the call-result into
$3 (freeing $2 for ret) never appears. Same return-value-coalescing class as actWaySystemCore
(there store-first forced the copy; no store here). Permuter pass 1.

## Permuter harvest 2026-06-11: nothing below rc3 -> (b)
"no permutation matched". Lowest scores 260-280 (base 305) but diff --dry: output-260-1=rc9,
270-1/280-1=rc8 — all WORSE than parked rc3 (score/real_count anti-correlation; outputs are
new_var pointer-indirection mutations). Nothing beats rc3. RESOLUTION (b). Re-attack future resume
with a fresh idea to force the call-result copy into $3 (freeing $2 for ret) without the beql annul.
