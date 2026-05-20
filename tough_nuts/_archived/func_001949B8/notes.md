
---

## Attempt at 2026-05-12

**Reason parked:** clamp/dispatch: built uses bne early return vs expected beq+branch+b sequence

Seed: `tough_nuts/func_001949B8/0949B8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001949B8; check asm/matchings/cod/0949B8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc v0/v1 swap throughout (slti, slt, movz)

Seed: `tough_nuts/func_001949B8/0949B8.c.new`

Disassembly excerpt:

```
glabel func_001949B8
    /* 949B8 001949B8 79FF8228 */  slti       $v0, $a0, -0x87
    /* 949BC 001949BC 03004010 */  beqz       $v0, .L001949CC
    /* 949C0 001949C0 D3FF8228 */   slti      $v0, $a0, -0x2D
    /* 949C4 001949C4 0E000010 */  b          .L00194A00
    /* 949C8 001949C8 B4000424 */   addiu     $a0, $zero, 0xB4
.align 2
  .L001949CC:
    /* 949CC 001949CC 03004010 */  beqz       $v0, .L001949DC
    /* 949D0 001949D0 2D008228 */   slti      $v0, $a0, 0x2D
    /* 949D4 001949D4 0A000010 */  b          .L00194A00
    /* 949D8 001949D8 A6FF0424 */   addiu     $a0, $zero, -0x5A
.align 2
  .L001949DC:
    /* 949DC 001949DC 03004010 */  beqz       $v0, .L001949EC
    /* 949E0 001949E0 2D108000 */   daddu     $v0, $a0, $zero
    /* 949E4 001949E4 06000010 */  b          .L00194A00
    /* 949E8 001949E8 2D200000 */   daddu     $a0, $zero, $zero
.align 2
  .L001949EC:
    /* 949EC 001949EC 86000324 */  addiu      $v1, $zero, 0x86
    /* 949F0 001949F0 2A186200 */  slt        $v1, $v1, $v0
    /* 949F4 001949F4 B4000424 */  addiu      $a0, $zero, 0xB4
    /* 949F8 001949F8 5A000224 */  addiu      $v0, $zero, 0x5A
    /* 949FC 001949FC 0A204300 */  movz       $a0, $v0, $v1
.align 2
  .L00194A00:
    /* 94A00 00194A00 0800E003 */  jr         $ra
    /* 94A04 00194A04 2D108000 */   daddu     $v0, $a0, $zero
endlabel func_001949B8
```
