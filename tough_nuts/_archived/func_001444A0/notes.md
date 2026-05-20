
---

## Attempt at 2026-05-09

**Reason parked:** size mismatch: built=0x68 expected=0x60 diff=+8

Seed: `tough_nuts/func_001444A0/0444A0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001444A0; check asm/matchings/cod/0444A0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** scan+call: target uses bnel with s0+=0x30 in annul-delay; built uses bne with nop in jal delay

Seed: `tough_nuts/func_001444A0/0444A0.c.new`

Disassembly excerpt:

```
glabel func_001444A0
    /* 444A0 001444A0 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 444A4 001444A4 6B00023C */  lui        $v0, %hi(D_006A95B0)
    /* 444A8 001444A8 0000B0FF */  sd         $s0, 0x0($sp)
    /* 444AC 001444AC 2000B2FF */  sd         $s2, 0x20($sp)
    /* 444B0 001444B0 B0955024 */  addiu      $s0, $v0, %lo(D_006A95B0)
    /* 444B4 001444B4 1000B1FF */  sd         $s1, 0x10($sp)
    /* 444B8 001444B8 11001224 */  addiu      $s2, $zero, 0x11
    /* 444BC 001444BC 3000BFFF */  sd         $ra, 0x30($sp)
    /* 444C0 001444C0 00031126 */  addiu      $s1, $s0, 0x300
    /* 444C4 001444C4 02000296 */  lhu        $v0, 0x2($s0)
.align 2
  .L001444C8:
    /* 444C8 001444C8 04005254 */  bnel       $v0, $s2, .L001444DC
    /* 444CC 001444CC 30001026 */   addiu     $s0, $s0, 0x30
    /* 444D0 001444D0 4E00050C */  jal        func_00140138
    /* 444D4 001444D4 2D200002 */   daddu     $a0, $s0, $zero
    /* 444D8 001444D8 30001026 */  addiu      $s0, $s0, 0x30
.align 2
  .L001444DC:
    /* 444DC 001444DC 2A101102 */  slt        $v0, $s0, $s1
    /* 444E0 001444E0 F9FF4054 */  bnel       $v0, $zero, .L001444C8
    /* 444E4 001444E4 02000296 */   lhu       $v0, 0x2($s0)
    /* 444E8 001444E8 3000BFDF */  ld         $ra, 0x30($sp)
    /* 444EC 001444EC 2000B2DF */  ld         $s2, 0x20($sp)
    /* 444F0 001444F0 1000B1DF */  ld         $s1, 0x10($sp)
    /* 444F4 001444F4 0000B0DF */  ld         $s0, 0x0($sp)
    /* 444F8 001444F8 0800E003 */  jr         $ra
    /* 444FC 001444FC 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_001444A0
```
