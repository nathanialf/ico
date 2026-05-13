
---

## Attempt at 2026-05-12

**Reason parked:** gcc emits slti+movz instead of slt+movn; equivalent semantics but different MIPS instrs

Seed: `tough_nuts/func_00251AB8/151AB8.c`

Disassembly excerpt:

```
glabel func_00251AB8
    /* 151AB8 00251AB8 1300C324 */  addiu      $v1, $a2, 0x13
    /* 151ABC 00251ABC FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 151AC0 00251AC0 2A104300 */  slt        $v0, $v0, $v1
    /* 151AC4 00251AC4 2200C624 */  addiu      $a2, $a2, 0x22
    /* 151AC8 00251AC8 2D20A000 */  daddu      $a0, $a1, $zero
    /* 151ACC 00251ACC 0B306200 */  movn       $a2, $v1, $v0
    /* 151AD0 00251AD0 5500053C */  lui        $a1, %hi(D_005524A8)
    /* 151AD4 00251AD4 03310600 */  sra        $a2, $a2, 4
    /* 151AD8 00251AD8 00310600 */  sll        $a2, $a2, 4
    /* 151ADC 00251ADC 5500023C */  lui        $v0, %hi(D_005525C0)
    /* 151AE0 00251AE0 A824A4AC */  sw         $a0, %lo(D_005524A8)($a1)
    /* 151AE4 00251AE4 C02546AC */  sw         $a2, %lo(D_005525C0)($v0)
    /* 151AE8 00251AE8 7A490908 */  j          func_002525E8
    /* 151AEC 00251AEC 2D28C000 */   daddu     $a1, $a2, $zero
endlabel func_00251AB8
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc emits movz+slti vs expected movn+slt (a2_orig >= -0x13 condition)

Seed: `tough_nuts/func_00251AB8/151AB8.c.new`

Disassembly excerpt:

```
glabel func_00251AB8
    /* 151AB8 00251AB8 1300C324 */  addiu      $v1, $a2, 0x13
    /* 151ABC 00251ABC FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 151AC0 00251AC0 2A104300 */  slt        $v0, $v0, $v1
    /* 151AC4 00251AC4 2200C624 */  addiu      $a2, $a2, 0x22
    /* 151AC8 00251AC8 2D20A000 */  daddu      $a0, $a1, $zero
    /* 151ACC 00251ACC 0B306200 */  movn       $a2, $v1, $v0
    /* 151AD0 00251AD0 5500053C */  lui        $a1, %hi(D_005524A8)
    /* 151AD4 00251AD4 03310600 */  sra        $a2, $a2, 4
    /* 151AD8 00251AD8 00310600 */  sll        $a2, $a2, 4
    /* 151ADC 00251ADC 5500023C */  lui        $v0, %hi(D_005525C0)
    /* 151AE0 00251AE0 A824A4AC */  sw         $a0, %lo(D_005524A8)($a1)
    /* 151AE4 00251AE4 C02546AC */  sw         $a2, %lo(D_005525C0)($v0)
    /* 151AE8 00251AE8 7A490908 */  j          func_002525E8
    /* 151AEC 00251AEC 2D28C000 */   daddu     $a1, $a2, $zero
endlabel func_00251AB8
```

---

## Attempt at 2026-05-13

**Reason parked:** movz+slti instead of movn+slt; gcc 2.9 prefers slti over slt for >=0 compare

Seed: `tough_nuts/func_00251AB8/151AB8.c.new`

Disassembly excerpt:

```
glabel func_00251AB8
    /* 151AB8 00251AB8 1300C324 */  addiu      $v1, $a2, 0x13
    /* 151ABC 00251ABC FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 151AC0 00251AC0 2A104300 */  slt        $v0, $v0, $v1
    /* 151AC4 00251AC4 2200C624 */  addiu      $a2, $a2, 0x22
    /* 151AC8 00251AC8 2D20A000 */  daddu      $a0, $a1, $zero
    /* 151ACC 00251ACC 0B306200 */  movn       $a2, $v1, $v0
    /* 151AD0 00251AD0 5500053C */  lui        $a1, %hi(D_005524A8)
    /* 151AD4 00251AD4 03310600 */  sra        $a2, $a2, 4
    /* 151AD8 00251AD8 00310600 */  sll        $a2, $a2, 4
    /* 151ADC 00251ADC 5500023C */  lui        $v0, %hi(D_005525C0)
    /* 151AE0 00251AE0 A824A4AC */  sw         $a0, %lo(D_005524A8)($a1)
    /* 151AE4 00251AE4 C02546AC */  sw         $a2, %lo(D_005525C0)($v0)
    /* 151AE8 00251AE8 7A490908 */  j          func_002525E8
    /* 151AEC 00251AEC 2D28C000 */   daddu     $a1, $a2, $zero
endlabel func_00251AB8
```
