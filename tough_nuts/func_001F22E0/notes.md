
---

## Attempt at 2026-05-08

**Reason parked:** func_00203B40 wrapper: ee-gcc emits sw s0,0x20(v0) before sw zero,0(s0); expected order is reversed with daddu v1,v0,0 intermediate (v0->v1 move)

Seed: `tough_nuts/func_001F22E0/0F22E0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F22E0; check asm/matchings/cod/0F22E0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** same shape as func_001C3720: missing daddu v1,v0,zero (register-move-after-jal)

Seed: `tough_nuts/func_001F22E0/0F22E0.c.new`

Disassembly excerpt:

```
glabel func_001F22E0
    /* F22E0 001F22E0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* F22E4 001F22E4 15000524 */  addiu      $a1, $zero, 0x15
    /* F22E8 001F22E8 0000B0FF */  sd         $s0, 0x0($sp)
    /* F22EC 001F22EC 2D808000 */  daddu      $s0, $a0, $zero
    /* F22F0 001F22F0 1000BFFF */  sd         $ra, 0x10($sp)
    /* F22F4 001F22F4 1F00043C */  lui        $a0, %hi(func_001F2320)
    /* F22F8 001F22F8 D00E080C */  jal        func_00203B40
    /* F22FC 001F22FC 20238424 */   addiu     $a0, $a0, %lo(func_001F2320)
    /* F2300 001F2300 2D184000 */  daddu      $v1, $v0, $zero
    /* F2304 001F2304 000000AE */  sw         $zero, 0x0($s0)
    /* F2308 001F2308 200070AC */  sw         $s0, 0x20($v1)
    /* F230C 001F230C 1000BFDF */  ld         $ra, 0x10($sp)
    /* F2310 001F2310 0000B0DF */  ld         $s0, 0x0($sp)
    /* F2314 001F2314 0800E003 */  jr         $ra
    /* F2318 001F2318 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_001F22E0
```

---

## Attempt at 2026-05-13

**Reason parked:** gcc emits daddu v1,v0; expected uses v0 directly for sw s0,32(v0)

Seed: `tough_nuts/func_001F22E0/0F22E0.c.new`

Disassembly excerpt:

```
glabel func_001F22E0
    /* F22E0 001F22E0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* F22E4 001F22E4 15000524 */  addiu      $a1, $zero, 0x15
    /* F22E8 001F22E8 0000B0FF */  sd         $s0, 0x0($sp)
    /* F22EC 001F22EC 2D808000 */  daddu      $s0, $a0, $zero
    /* F22F0 001F22F0 1000BFFF */  sd         $ra, 0x10($sp)
    /* F22F4 001F22F4 1F00043C */  lui        $a0, %hi(func_001F2320)
    /* F22F8 001F22F8 D00E080C */  jal        func_00203B40
    /* F22FC 001F22FC 20238424 */   addiu     $a0, $a0, %lo(func_001F2320)
    /* F2300 001F2300 2D184000 */  daddu      $v1, $v0, $zero
    /* F2304 001F2304 000000AE */  sw         $zero, 0x0($s0)
    /* F2308 001F2308 200070AC */  sw         $s0, 0x20($v1)
    /* F230C 001F230C 1000BFDF */  ld         $ra, 0x10($sp)
    /* F2310 001F2310 0000B0DF */  ld         $s0, 0x0($sp)
    /* F2314 001F2314 0800E003 */  jr         $ra
    /* F2318 001F2318 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_001F22E0
```
