
---

## Attempt at 2026-05-08

**Reason parked:** 2-call+sw_global: ee-gcc emits li a2,-128 (1 insn); original lui+ori for 0xFFFFFF80 (2 insns)

Seed: `tough_nuts/func_001EF9E0/0EF9E0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001EF9E0; check asm/matchings/cod/0EF9E0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** mov.s f12,f20 placement: expected before daddu a1, mine after

Seed: `tough_nuts/func_001EF9E0/0EF9E0.c.new`

Disassembly excerpt:

```
glabel func_001EF9E0
    /* EF9E0 001EF9E0 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* EF9E4 001EF9E4 FFFF063C */  lui        $a2, (0xFFFFFF80 >> 16)
    /* EF9E8 001EF9E8 0000B0FF */  sd         $s0, 0x0($sp)
    /* EF9EC 001EF9EC 10000424 */  addiu      $a0, $zero, 0x10
    /* EF9F0 001EF9F0 2000B4E7 */  swc1       $f20, 0x20($sp)
    /* EF9F4 001EF9F4 2700103C */  lui        $s0, %hi(D_00275860)
    /* EF9F8 001EF9F8 A042013C */  lui        $at, (0x42A00000 >> 16)
    /* EF9FC 001EF9FC 00A08144 */  mtc1       $at, $f20
    /* EFA00 001EFA00 60581026 */  addiu      $s0, $s0, %lo(D_00275860)
    /* EFA04 001EFA04 2D280002 */  daddu      $a1, $s0, $zero
    /* EFA08 001EFA08 1000BFFF */  sd         $ra, 0x10($sp)
    /* EFA0C 001EFA0C 06A30046 */  mov.s      $f12, $f20
    /* EFA10 001EFA10 80FFC634 */  ori        $a2, $a2, (0xFFFFFF80 & 0xFFFF)
    /* EFA14 001EFA14 0A70040C */  jal        func_0011C028
    /* EFA18 001EFA18 2D380000 */   daddu     $a3, $zero, $zero
    /* EFA1C 001EFA1C FFFF063C */  lui        $a2, (0xFFFFFF80 >> 16)
    /* EFA20 001EFA20 06A30046 */  mov.s      $f12, $f20
    /* EFA24 001EFA24 2D280002 */  daddu      $a1, $s0, $zero
    /* EFA28 001EFA28 44AD82AF */  sw         $v0, %gp_rel(D_00633634)($gp)
    /* EFA2C 001EFA2C 10000424 */  addiu      $a0, $zero, 0x10
    /* EFA30 001EFA30 80FFC634 */  ori        $a2, $a2, (0xFFFFFF80 & 0xFFFF)
    /* EFA34 001EFA34 0A70040C */  jal        func_0011C028
    /* EFA38 001EFA38 2D380000 */   daddu     $a3, $zero, $zero
    /* EFA3C 001EFA3C 1000BFDF */  ld         $ra, 0x10($sp)
    /* EFA40 001EFA40 0000B0DF */  ld         $s0, 0x0($sp)
    /* EFA44 001EFA44 2000B4C7 */  lwc1       $f20, 0x20($sp)
    /* EFA48 001EFA48 48AD82AF */  sw         $v0, %gp_rel(D_00633638)($gp)
    /* EFA4C 001EFA4C 0800E003 */  jr         $ra
    /* EFA50 001EFA50 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001EF9E0
```
