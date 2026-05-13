
---

## Attempt at 2026-05-12

**Reason parked:** dual-write +1 trick: gcc computes simple idx*4 base, expected uses idx*2 + idx*2+1 separate index manipulation

Seed: `tough_nuts/func_00140B30/040B30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00140B30; check asm/matchings/cod/040B30/)
```

---

## Attempt at 2026-05-12

**Reason parked:** double base ptr computation differs; expected uses 2 separate addrs for 0x3C and 0x42 stores

Seed: `tough_nuts/func_00140B30/040B30.c.new`

Disassembly excerpt:

```
glabel func_00140B30
    /* 40B30 00140B30 2D18A000 */  daddu      $v1, $a1, $zero
    /* 40B34 00140B34 2C00848C */  lw         $a0, 0x2C($a0)
    /* 40B38 00140B38 40280300 */  sll        $a1, $v1, 1
    /* 40B3C 00140B3C 0100A224 */  addiu      $v0, $a1, 0x1
    /* 40B40 00140B40 80180300 */  sll        $v1, $v1, 2
    /* 40B44 00140B44 40100200 */  sll        $v0, $v0, 1
    /* 40B48 00140B48 21188300 */  addu       $v1, $a0, $v1
    /* 40B4C 00140B4C 21108200 */  addu       $v0, $a0, $v0
    /* 40B50 00140B50 400046A4 */  sh         $a2, 0x40($v0)
    /* 40B54 00140B54 88020508 */  j          func_00140A20
    /* 40B58 00140B58 3C0066A4 */   sh        $a2, 0x3C($v1)
endlabel func_00140B30
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc CSEs base+a1*4 into single reg; expected splits into v1=base+a1*4 and v0=base+a1*4+2 separately

Seed: `tough_nuts/func_00140B30/040B30.c.new`

Disassembly excerpt:

```
glabel func_00140B30
    /* 40B30 00140B30 2D18A000 */  daddu      $v1, $a1, $zero
    /* 40B34 00140B34 2C00848C */  lw         $a0, 0x2C($a0)
    /* 40B38 00140B38 40280300 */  sll        $a1, $v1, 1
    /* 40B3C 00140B3C 0100A224 */  addiu      $v0, $a1, 0x1
    /* 40B40 00140B40 80180300 */  sll        $v1, $v1, 2
    /* 40B44 00140B44 40100200 */  sll        $v0, $v0, 1
    /* 40B48 00140B48 21188300 */  addu       $v1, $a0, $v1
    /* 40B4C 00140B4C 21108200 */  addu       $v0, $a0, $v0
    /* 40B50 00140B50 400046A4 */  sh         $a2, 0x40($v0)
    /* 40B54 00140B54 88020508 */  j          func_00140A20
    /* 40B58 00140B58 3C0066A4 */   sh        $a2, 0x3C($v1)
endlabel func_00140B30
```

---

## Attempt at 2026-05-13

**Reason parked:** gcc folds idx*4 + const offset into single addr; expected uses two pointer-arith chains

Seed: `tough_nuts/func_00140B30/040B30.c.new`

Disassembly excerpt:

```
glabel func_00140B30
    /* 40B30 00140B30 2D18A000 */  daddu      $v1, $a1, $zero
    /* 40B34 00140B34 2C00848C */  lw         $a0, 0x2C($a0)
    /* 40B38 00140B38 40280300 */  sll        $a1, $v1, 1
    /* 40B3C 00140B3C 0100A224 */  addiu      $v0, $a1, 0x1
    /* 40B40 00140B40 80180300 */  sll        $v1, $v1, 2
    /* 40B44 00140B44 40100200 */  sll        $v0, $v0, 1
    /* 40B48 00140B48 21188300 */  addu       $v1, $a0, $v1
    /* 40B4C 00140B4C 21108200 */  addu       $v0, $a0, $v0
    /* 40B50 00140B50 400046A4 */  sh         $a2, 0x40($v0)
    /* 40B54 00140B54 88020508 */  j          func_00140A20
    /* 40B58 00140B58 3C0066A4 */   sh        $a2, 0x3C($v1)
endlabel func_00140B30
```
