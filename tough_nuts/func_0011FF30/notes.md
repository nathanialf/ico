
---

## Attempt at 2026-05-08

**Reason parked:** scheduling: target emits a2/a1/a1-lo before jal with a0=2 in delay slot; gcc emits a0/a2 before jal with a1-lo in delay slot

Seed: `tough_nuts/func_0011FF30/01FF30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0011FF30; check asm/matchings/cod/01FF30/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 3-call wrapper: ee-gcc emits args a0,a2,a1 (in delay); original a2,a1,a0 (a0 in delay)

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0011FF30; check asm/matchings/cod/01FF30/)
```

---

## Attempt at 2026-05-12

**Reason parked:** tail-call args reused; gcc spills D_00555830 to s0; expected loads once + assumes args survive across call

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-12

**Reason parked:** scheduler delay-slot choice: built places addiu a1+=lo in delay; target has addiu a0=2 there

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-12

**Reason parked:** jal delay slot picks addiu a2,4 vs expected addiu a0,2; otherwise matches

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss with fno-schedule-insns: a0 vs a2 in jal delay slot

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss retry: a0 vs a1 setup in delay slot — gcc fills with a1 not a0

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-13

**Reason parked:** ee-as picks addiu a2 for jal delay; expected picks addiu a0

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-13

**Reason parked:** ee-as picks addiu a0 for jal delay; expected has addiu a2

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```

---

## Attempt at 2026-05-13

**Reason parked:** permuter score-10 has wrong arg order; expected (2,D,4) but emits (4,D,2)

Seed: `tough_nuts/func_0011FF30/01FF30.c.new`

Disassembly excerpt:

```
glabel func_0011FF30
    /* 1FF30 0011FF30 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 1FF34 0011FF34 0000BFFF */  sd         $ra, 0x0($sp)
    /* 1FF38 0011FF38 A0EE070C */  jal        func_001FBA80
    /* 1FF3C 0011FF3C 00000000 */   nop
    /* 1FF40 0011FF40 5500053C */  lui        $a1, %hi(D_00555830)
    /* 1FF44 0011FF44 04000624 */  addiu      $a2, $zero, 0x4
    /* 1FF48 0011FF48 3058A524 */  addiu      $a1, $a1, %lo(D_00555830)
    /* 1FF4C 0011FF4C AAEE070C */  jal        func_001FBAA8
    /* 1FF50 0011FF50 02000424 */   addiu     $a0, $zero, 0x2
    /* 1FF54 0011FF54 0000BFDF */  ld         $ra, 0x0($sp)
    /* 1FF58 0011FF58 2EEE0708 */  j          func_001FB8B8
    /* 1FF5C 0011FF5C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0011FF30
```
