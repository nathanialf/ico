
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 31 insns; original 32 (1 missing — likely store-order or trailing nop)

Seed: `tough_nuts/func_001F4250/0F4250.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F4250; check asm/matchings/cod/0F4250/)
```

---

## Attempt at 2026-05-13

**Reason parked:** expected moves flag a2→a1; gcc uses a2 directly

Seed: `tough_nuts/func_001F4250/0F4250.c.new`

Disassembly excerpt:

```
glabel func_001F4250
    /* F4250 001F4250 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* F4254 001F4254 2000B2FF */  sd         $s2, 0x20($sp)
    /* F4258 001F4258 1000B1FF */  sd         $s1, 0x10($sp)
    /* F425C 001F425C 2D90A000 */  daddu      $s2, $a1, $zero
    /* F4260 001F4260 3000BFFF */  sd         $ra, 0x30($sp)
    /* F4264 001F4264 2D28C000 */  daddu      $a1, $a2, $zero
    /* F4268 001F4268 0000B0FF */  sd         $s0, 0x0($sp)
    /* F426C 001F426C 5C01908C */  lw         $s0, 0x15C($a0)
    /* F4270 001F4270 0008048E */  lw         $a0, 0x800($s0)
    /* F4274 001F4274 0800828C */  lw         $v0, 0x8($a0)
    /* F4278 001F4278 03004010 */  beqz       $v0, .L001F4288
    /* F427C 001F427C A0001126 */   addiu     $s1, $s0, 0xA0
    /* F4280 001F4280 5C01428C */  lw         $v0, 0x15C($v0)
    /* F4284 001F4284 300640AC */  sw         $zero, 0x630($v0)
.align 2
  .L001F4288:
    /* F4288 001F4288 FFFF0324 */  addiu      $v1, $zero, -0x1
    /* F428C 001F428C 01000224 */  addiu      $v0, $zero, 0x1
    /* F4290 001F4290 040082AC */  sw         $v0, 0x4($a0)
    /* F4294 001F4294 0C0083AC */  sw         $v1, 0xC($a0)
    /* F4298 001F4298 0300A010 */  beqz       $a1, .L001F42A8
    /* F429C 001F429C 080080AC */   sw        $zero, 0x8($a0)
    /* F42A0 001F42A0 0C36040C */  jal        func_0010D830
    /* F42A4 001F42A4 50010426 */   addiu     $a0, $s0, 0x150
.align 2
  .L001F42A8:
    /* F42A8 001F42A8 30010426 */  addiu      $a0, $s0, 0x130
    /* F42AC 001F42AC C017040C */  jal        func_00105F00
    /* F42B0 001F42B0 2D284002 */   daddu     $a1, $s2, $zero
    /* F42B4 001F42B4 9C0020AE */  sw         $zero, 0x9C($s1)
    /* F42B8 001F42B8 3000BFDF */  ld         $ra, 0x30($sp)
    /* F42BC 001F42BC 2000B2DF */  ld         $s2, 0x20($sp)
    /* F42C0 001F42C0 1000B1DF */  ld         $s1, 0x10($sp)
    /* F42C4 001F42C4 0000B0DF */  ld         $s0, 0x0($sp)
    /* F42C8 001F42C8 0800E003 */  jr         $ra
    /* F42CC 001F42CC 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_001F4250
```
