
---

## Attempt at 2026-05-12

**Reason parked:** regalloc differs: a1/a0/a3 swap for the 3 mask constants

Seed: `tough_nuts/func_0015F5F8/05F5F8.c`

Disassembly excerpt:

```
glabel func_0015F5F8
    /* 5F5F8 0015F5F8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 5F5FC 0015F5FC FFFD053C */  lui        $a1, (0xFDFFFFFF >> 16)
    /* 5F600 0015F600 FFFFA534 */  ori        $a1, $a1, (0xFDFFFFFF & 0xFFFF)
    /* 5F604 0015F604 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5F608 0015F608 FEFF063C */  lui        $a2, (0xFFFEFFFF >> 16)
    /* 5F60C 0015F60C FFFFC634 */  ori        $a2, $a2, (0xFFFEFFFF & 0xFFFF)
    /* 5F610 0015F610 38340600 */  dsll       $a2, $a2, 16
    /* 5F614 0015F614 FFFFC634 */  ori        $a2, $a2, 0xFFFF
    /* 5F618 0015F618 38340600 */  dsll       $a2, $a2, 16
    /* 5F61C 0015F61C FFFFC634 */  ori        $a2, $a2, 0xFFFF
    /* 5F620 0015F620 0400073C */  lui        $a3, (0x40000 >> 16)
    /* 5F624 0015F624 0000A38F */  lw         $v1, 0x0($sp)
    /* 5F628 0015F628 6401648C */  lw         $a0, 0x164($v1)
    /* 5F62C 0015F62C 200082DC */  ld         $v0, 0x20($a0)
    /* 5F630 0015F630 180083DC */  ld         $v1, 0x18($a0)
    /* 5F634 0015F634 24104500 */  and        $v0, $v0, $a1
    /* 5F638 0015F638 24186600 */  and        $v1, $v1, $a2
    /* 5F63C 0015F63C 25104700 */  or         $v0, $v0, $a3
    /* 5F640 0015F640 200082FC */  sd         $v0, 0x20($a0)
    /* 5F644 0015F644 180083FC */  sd         $v1, 0x18($a0)
    /* 5F648 0015F648 0800E003 */  jr         $ra
    /* 5F64C 0015F64C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0015F5F8
```

---

## Attempt at 2026-05-12

**Reason parked:** shape matches, regs v0/v1 swapped between target and built; first-load goes to v1 (built) vs v0 (target)

Seed: `tough_nuts/func_0015F5F8/05F5F8.c.new`

Disassembly excerpt:

```
glabel func_0015F5F8
    /* 5F5F8 0015F5F8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 5F5FC 0015F5FC FFFD053C */  lui        $a1, (0xFDFFFFFF >> 16)
    /* 5F600 0015F600 FFFFA534 */  ori        $a1, $a1, (0xFDFFFFFF & 0xFFFF)
    /* 5F604 0015F604 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5F608 0015F608 FEFF063C */  lui        $a2, (0xFFFEFFFF >> 16)
    /* 5F60C 0015F60C FFFFC634 */  ori        $a2, $a2, (0xFFFEFFFF & 0xFFFF)
    /* 5F610 0015F610 38340600 */  dsll       $a2, $a2, 16
    /* 5F614 0015F614 FFFFC634 */  ori        $a2, $a2, 0xFFFF
    /* 5F618 0015F618 38340600 */  dsll       $a2, $a2, 16
    /* 5F61C 0015F61C FFFFC634 */  ori        $a2, $a2, 0xFFFF
    /* 5F620 0015F620 0400073C */  lui        $a3, (0x40000 >> 16)
    /* 5F624 0015F624 0000A38F */  lw         $v1, 0x0($sp)
    /* 5F628 0015F628 6401648C */  lw         $a0, 0x164($v1)
    /* 5F62C 0015F62C 200082DC */  ld         $v0, 0x20($a0)
    /* 5F630 0015F630 180083DC */  ld         $v1, 0x18($a0)
    /* 5F634 0015F634 24104500 */  and        $v0, $v0, $a1
    /* 5F638 0015F638 24186600 */  and        $v1, $v1, $a2
    /* 5F63C 0015F63C 25104700 */  or         $v0, $v0, $a3
    /* 5F640 0015F640 200082FC */  sd         $v0, 0x20($a0)
    /* 5F644 0015F644 180083FC */  sd         $v1, 0x18($a0)
    /* 5F648 0015F648 0800E003 */  jr         $ra
    /* 5F64C 0015F64C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0015F5F8
```
