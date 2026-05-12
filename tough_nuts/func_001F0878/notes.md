
---

## Attempt at 2026-05-09

**Reason parked:** permuter score-0 was false positive: stack frame size differs (-0x30 vs -0x40)

Seed: `tough_nuts/func_001F0878/0F0878.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F0878; check asm/matchings/cod/0F0878/)
```

---

## Attempt at 2026-05-12

**Reason parked:** permuter score-0 file mismatch: -64 vs -48 frame; s0/s1 offsets shifted by 16 (extra padding)

Seed: `tough_nuts/func_001F0878/0F0878.c.new`

Disassembly excerpt:

```
glabel func_001F0878
    /* F0878 001F0878 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* F087C 001F087C FFFF0324 */  addiu      $v1, $zero, -0x1
    /* F0880 001F0880 2000B1FF */  sd         $s1, 0x20($sp)
    /* F0884 001F0884 2700053C */  lui        $a1, %hi(D_00275850)
    /* F0888 001F0888 1000B0FF */  sd         $s0, 0x10($sp)
    /* F088C 001F088C 01001124 */  addiu      $s1, $zero, 0x1
    /* F0890 001F0890 3000BFFF */  sd         $ra, 0x30($sp)
    /* F0894 001F0894 2D808000 */  daddu      $s0, $a0, $zero
    /* F0898 001F0898 5058A524 */  addiu      $a1, $a1, %lo(D_00275850)
    /* F089C 001F089C 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A0 001F08A0 700443AC */  sw         $v1, 0x470($v0)
    /* F08A4 001F08A4 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A8 001F08A8 600651AC */  sw         $s1, 0x660($v0)
    /* F08AC 001F08AC 5C01048E */  lw         $a0, 0x15C($s0)
    /* F08B0 001F08B0 C017040C */  jal        func_00105F00
    /* F08B4 001F08B4 70068424 */   addiu     $a0, $a0, 0x670
    /* F08B8 001F08B8 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08BC 001F08BC 3000BFDF */  ld         $ra, 0x30($sp)
    /* F08C0 001F08C0 500551AC */  sw         $s1, 0x550($v0)
    /* F08C4 001F08C4 2000B1DF */  ld         $s1, 0x20($sp)
    /* F08C8 001F08C8 1000B0DF */  ld         $s0, 0x10($sp)
    /* F08CC 001F08CC 0800E003 */  jr         $ra
    /* F08D0 001F08D0 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_001F0878
```

---

## Attempt at 2026-05-12

**Reason parked:** score-0 promotion fails: frame size diff (-48 vs -64); pipeline difference

Seed: `tough_nuts/func_001F0878/0F0878.c.new`

Disassembly excerpt:

```
glabel func_001F0878
    /* F0878 001F0878 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* F087C 001F087C FFFF0324 */  addiu      $v1, $zero, -0x1
    /* F0880 001F0880 2000B1FF */  sd         $s1, 0x20($sp)
    /* F0884 001F0884 2700053C */  lui        $a1, %hi(D_00275850)
    /* F0888 001F0888 1000B0FF */  sd         $s0, 0x10($sp)
    /* F088C 001F088C 01001124 */  addiu      $s1, $zero, 0x1
    /* F0890 001F0890 3000BFFF */  sd         $ra, 0x30($sp)
    /* F0894 001F0894 2D808000 */  daddu      $s0, $a0, $zero
    /* F0898 001F0898 5058A524 */  addiu      $a1, $a1, %lo(D_00275850)
    /* F089C 001F089C 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A0 001F08A0 700443AC */  sw         $v1, 0x470($v0)
    /* F08A4 001F08A4 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A8 001F08A8 600651AC */  sw         $s1, 0x660($v0)
    /* F08AC 001F08AC 5C01048E */  lw         $a0, 0x15C($s0)
    /* F08B0 001F08B0 C017040C */  jal        func_00105F00
    /* F08B4 001F08B4 70068424 */   addiu     $a0, $a0, 0x670
    /* F08B8 001F08B8 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08BC 001F08BC 3000BFDF */  ld         $ra, 0x30($sp)
    /* F08C0 001F08C0 500551AC */  sw         $s1, 0x550($v0)
    /* F08C4 001F08C4 2000B1DF */  ld         $s1, 0x20($sp)
    /* F08C8 001F08C8 1000B0DF */  ld         $s0, 0x10($sp)
    /* F08CC 001F08CC 0800E003 */  jr         $ra
    /* F08D0 001F08D0 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_001F0878
```

---

## Attempt at 2026-05-12

**Reason parked:** permuter score-0 false positive; stack frame differs sp=64 vs 48

Seed: `tough_nuts/func_001F0878/0F0878.c.new`

Disassembly excerpt:

```
glabel func_001F0878
    /* F0878 001F0878 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* F087C 001F087C FFFF0324 */  addiu      $v1, $zero, -0x1
    /* F0880 001F0880 2000B1FF */  sd         $s1, 0x20($sp)
    /* F0884 001F0884 2700053C */  lui        $a1, %hi(D_00275850)
    /* F0888 001F0888 1000B0FF */  sd         $s0, 0x10($sp)
    /* F088C 001F088C 01001124 */  addiu      $s1, $zero, 0x1
    /* F0890 001F0890 3000BFFF */  sd         $ra, 0x30($sp)
    /* F0894 001F0894 2D808000 */  daddu      $s0, $a0, $zero
    /* F0898 001F0898 5058A524 */  addiu      $a1, $a1, %lo(D_00275850)
    /* F089C 001F089C 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A0 001F08A0 700443AC */  sw         $v1, 0x470($v0)
    /* F08A4 001F08A4 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A8 001F08A8 600651AC */  sw         $s1, 0x660($v0)
    /* F08AC 001F08AC 5C01048E */  lw         $a0, 0x15C($s0)
    /* F08B0 001F08B0 C017040C */  jal        func_00105F00
    /* F08B4 001F08B4 70068424 */   addiu     $a0, $a0, 0x670
    /* F08B8 001F08B8 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08BC 001F08BC 3000BFDF */  ld         $ra, 0x30($sp)
    /* F08C0 001F08C0 500551AC */  sw         $s1, 0x550($v0)
    /* F08C4 001F08C4 2000B1DF */  ld         $s1, 0x20($sp)
    /* F08C8 001F08C8 1000B0DF */  ld         $s0, 0x10($sp)
    /* F08CC 001F08CC 0800E003 */  jr         $ra
    /* F08D0 001F08D0 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_001F0878
```

---

## Attempt at 2026-05-12

**Reason parked:** stack frame size mismatch -0x30 vs expected -0x40; saves shifted by 0x10; combined 0x1F0878+0x1F08B8 into one C func, body matches

Seed: `tough_nuts/func_001F0878/0F0878.c.new`

Disassembly excerpt:

```
glabel func_001F0878
    /* F0878 001F0878 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* F087C 001F087C FFFF0324 */  addiu      $v1, $zero, -0x1
    /* F0880 001F0880 2000B1FF */  sd         $s1, 0x20($sp)
    /* F0884 001F0884 2700053C */  lui        $a1, %hi(D_00275850)
    /* F0888 001F0888 1000B0FF */  sd         $s0, 0x10($sp)
    /* F088C 001F088C 01001124 */  addiu      $s1, $zero, 0x1
    /* F0890 001F0890 3000BFFF */  sd         $ra, 0x30($sp)
    /* F0894 001F0894 2D808000 */  daddu      $s0, $a0, $zero
    /* F0898 001F0898 5058A524 */  addiu      $a1, $a1, %lo(D_00275850)
    /* F089C 001F089C 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A0 001F08A0 700443AC */  sw         $v1, 0x470($v0)
    /* F08A4 001F08A4 5C01028E */  lw         $v0, 0x15C($s0)
    /* F08A8 001F08A8 600651AC */  sw         $s1, 0x660($v0)
    /* F08AC 001F08AC 5C01048E */  lw         $a0, 0x15C($s0)
    /* F08B0 001F08B0 C017040C */  jal        func_00105F00
    /* F08B4 001F08B4 70068424 */   addiu     $a0, $a0, 0x670
endlabel func_001F0878
```
