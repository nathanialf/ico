
---

## Attempt at 2026-05-12

**Reason parked:** lui+mtc1 for -133.0 moves after gp_rel loads instead of before; store offset reordered

Seed: `tough_nuts/func_0023CCB8/13CCB8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023CCB8; check asm/matchings/cod/13CCB8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** init 3 floats; scheduler picks different fp reg + store order; close but not byte-equal

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
glabel func_0023CCB8
    /* 13CCB8 0023CCB8 3400838C */  lw         $v1, 0x34($a0)
    /* 13CCBC 0023CCBC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CCC0 0023CCC0 05C3013C */  lui        $at, (0xC3050000 >> 16)
    /* 13CCC4 0023CCC4 00088144 */  mtc1       $at, $f1
    /* 13CCC8 0023CCC8 5C8F82C7 */  lwc1       $f2, %gp_rel(D_0063184C)($gp)
    /* 13CCCC 0023CCCC 608F80C7 */  lwc1       $f0, %gp_rel(D_00631850)($gp)
    /* 13CCD0 0023CCD0 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13CCD4 0023CCD4 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CCD8 0023CCD8 0800E003 */  jr         $ra
    /* 13CCDC 0023CCDC 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023CCB8
```

---

## Attempt at 2026-05-12

**Reason parked:** lui+mtc1 (literal -133) scheduled after gp_rel loads; expected has literal first

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
glabel func_0023CCB8
    /* 13CCB8 0023CCB8 3400838C */  lw         $v1, 0x34($a0)
    /* 13CCBC 0023CCBC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CCC0 0023CCC0 05C3013C */  lui        $at, (0xC3050000 >> 16)
    /* 13CCC4 0023CCC4 00088144 */  mtc1       $at, $f1
    /* 13CCC8 0023CCC8 5C8F82C7 */  lwc1       $f2, %gp_rel(D_0063184C)($gp)
    /* 13CCCC 0023CCCC 608F80C7 */  lwc1       $f0, %gp_rel(D_00631850)($gp)
    /* 13CCD0 0023CCD0 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13CCD4 0023CCD4 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CCD8 0023CCD8 0800E003 */  jr         $ra
    /* 13CCDC 0023CCDC 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023CCB8
```

---

## Attempt at 2026-05-13

**Reason parked:** scheduler interleaves compute+store; expected holds 3 FP regs live before any store

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
glabel func_0023CCB8
    /* 13CCB8 0023CCB8 3400838C */  lw         $v1, 0x34($a0)
    /* 13CCBC 0023CCBC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CCC0 0023CCC0 05C3013C */  lui        $at, (0xC3050000 >> 16)
    /* 13CCC4 0023CCC4 00088144 */  mtc1       $at, $f1
    /* 13CCC8 0023CCC8 5C8F82C7 */  lwc1       $f2, %gp_rel(D_0063184C)($gp)
    /* 13CCCC 0023CCCC 608F80C7 */  lwc1       $f0, %gp_rel(D_00631850)($gp)
    /* 13CCD0 0023CCD0 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13CCD4 0023CCD4 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CCD8 0023CCD8 0800E003 */  jr         $ra
    /* 13CCDC 0023CCDC 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023CCB8
```

---

## Attempt at 2026-05-13

**Reason parked:** retry: improvement on load order but still scheduler reorders stores

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
glabel func_0023CCB8
    /* 13CCB8 0023CCB8 3400838C */  lw         $v1, 0x34($a0)
    /* 13CCBC 0023CCBC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CCC0 0023CCC0 05C3013C */  lui        $at, (0xC3050000 >> 16)
    /* 13CCC4 0023CCC4 00088144 */  mtc1       $at, $f1
    /* 13CCC8 0023CCC8 5C8F82C7 */  lwc1       $f2, %gp_rel(D_0063184C)($gp)
    /* 13CCCC 0023CCCC 608F80C7 */  lwc1       $f0, %gp_rel(D_00631850)($gp)
    /* 13CCD0 0023CCD0 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13CCD4 0023CCD4 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CCD8 0023CCD8 0800E003 */  jr         $ra
    /* 13CCDC 0023CCDC 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023CCB8
```

---

## Attempt at 2026-05-13

**Reason parked:** lui/mtc1 for -133.0 placed after lwc1; expected has it first

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
glabel func_0023CCB8
    /* 13CCB8 0023CCB8 3400838C */  lw         $v1, 0x34($a0)
    /* 13CCBC 0023CCBC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CCC0 0023CCC0 05C3013C */  lui        $at, (0xC3050000 >> 16)
    /* 13CCC4 0023CCC4 00088144 */  mtc1       $at, $f1
    /* 13CCC8 0023CCC8 5C8F82C7 */  lwc1       $f2, %gp_rel(D_0063184C)($gp)
    /* 13CCCC 0023CCCC 608F80C7 */  lwc1       $f0, %gp_rel(D_00631850)($gp)
    /* 13CCD0 0023CCD0 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13CCD4 0023CCD4 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CCD8 0023CCD8 0800E003 */  jr         $ra
    /* 13CCDC 0023CCDC 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023CCB8
```

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B macros (KEEP_LIVE)

Seed: `tough_nuts/func_0023CCB8/13CCB8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023CCB8; check asm/matchings/cod/13CCB8/)
```
