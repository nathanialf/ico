
---

## Attempt at 2026-05-12

**Reason parked:** toggle wrapper: register choice diff (v0/v1 swap) + store offset order (28,16,20,24 vs 24,16,28,20)

Seed: `tough_nuts/func_001FBBE0/0FBBE0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001FBBE0; check asm/matchings/cod/0FBBE0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** toggle+copy: addu+lw 4 pattern matched but ee-gcc reorders sw [6] before sw [4] to fill lw latency

Seed: `tough_nuts/func_001FBBE0/0FBBE0.c.new`

Disassembly excerpt:

```
glabel func_001FBBE0
    /* FBBE0 001FBBE0 4C00043C */  lui        $a0, %hi(D_004C7710)
    /* FBBE4 001FBBE4 1077838C */  lw         $v1, %lo(D_004C7710)($a0)
    /* FBBE8 001FBBE8 10778524 */  addiu      $a1, $a0, %lo(D_004C7710)
    /* FBBEC 001FBBEC 01006338 */  xori       $v1, $v1, 0x1
    /* FBBF0 001FBBF0 80100300 */  sll        $v0, $v1, 2
    /* FBBF4 001FBBF4 107783AC */  sw         $v1, %lo(D_004C7710)($a0)
    /* FBBF8 001FBBF8 2110A200 */  addu       $v0, $a1, $v0
    /* FBBFC 001FBBFC 0400438C */  lw         $v1, 0x4($v0)
    /* FBC00 001FBC00 1C00A0AC */  sw         $zero, 0x1C($a1)
    /* FBC04 001FBC04 1000A3AC */  sw         $v1, 0x10($a1)
    /* FBC08 001FBC08 1400A0AC */  sw         $zero, 0x14($a1)
    /* FBC0C 001FBC0C 0800E003 */  jr         $ra
    /* FBC10 001FBC10 1800A0AC */   sw        $zero, 0x18($a1)
endlabel func_001FBBE0
```

---

## Attempt at 2026-05-13

**Reason parked:** v+1 computation order: expected addiu+sll+addu vs mine sll+addu+lw at offset 4

Seed: `tough_nuts/func_001FBBE0/0FBBE0.c.new`

Disassembly excerpt:

```
glabel func_001FBBE0
    /* FBBE0 001FBBE0 4C00043C */  lui        $a0, %hi(D_004C7710)
    /* FBBE4 001FBBE4 1077838C */  lw         $v1, %lo(D_004C7710)($a0)
    /* FBBE8 001FBBE8 10778524 */  addiu      $a1, $a0, %lo(D_004C7710)
    /* FBBEC 001FBBEC 01006338 */  xori       $v1, $v1, 0x1
    /* FBBF0 001FBBF0 80100300 */  sll        $v0, $v1, 2
    /* FBBF4 001FBBF4 107783AC */  sw         $v1, %lo(D_004C7710)($a0)
    /* FBBF8 001FBBF8 2110A200 */  addu       $v0, $a1, $v0
    /* FBBFC 001FBBFC 0400438C */  lw         $v1, 0x4($v0)
    /* FBC00 001FBC00 1C00A0AC */  sw         $zero, 0x1C($a1)
    /* FBC04 001FBC04 1000A3AC */  sw         $v1, 0x10($a1)
    /* FBC08 001FBC08 1400A0AC */  sw         $zero, 0x14($a1)
    /* FBC0C 001FBC0C 0800E003 */  jr         $ra
    /* FBC10 001FBC10 1800A0AC */   sw        $zero, 0x18($a1)
endlabel func_001FBBE0
```
