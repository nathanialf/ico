# DispCollisionPC — parked

VRAM: 0x00163DE8 (file_off 0x063DE8)
Asm source: asm/aug6/nonmatchings/fumi/src/fieldCollision/DispCollisionPC.s

## Attempt at 2026-06-13

**Reason parked:** best rc4: pure 2-temp coloring tie - const-3 grabs freed param reg a0, obj wants a0 (ROM const v1/obj a0; built const a0/obj v1). 30 distinct forms (if/else/ternary/switch/goto, inline/typed/int*/param-reuse/ptr-to-array x3/do-while0 x3/decl-order/yoda/compound/register/static-helper/void*-return) ALL rc4. Semantically perfect. Deterministic gcc reload/coloring tie - needs interference-graph change to flip coloring order (const colored before obj).

**TU:** `fumi/src/fieldCollision.c`

**Seed:** `tough_nuts/DispCollisionPC/DispCollisionPC.c`

Disassembly:

```
.align 3
nonmatching DispCollisionPC, 0x48

glabel DispCollisionPC
    /* 63DE8 00163DE8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 63DEC 00163DEC 2D488000 */  daddu      $9, $4, $0
    /* 63DF0 00163DF0 0000BFFF */  sd         $31, 0x0($29)
    /* 63DF4 00163DF4 03000324 */  addiu      $3, $0, 0x3
    /* 63DF8 00163DF8 6401228D */  lw         $2, 0x164($9)
    /* 63DFC 00163DFC 7006448C */  lw         $4, 0x670($2)
    /* 63E00 00163E00 DC01828C */  lw         $2, 0x1DC($4)
    /* 63E04 00163E04 05004310 */  beq        $2, $3, .L00163E1C
    /* 63E08 00163E08 FF000831 */   andi      $8, $8, 0xFF
    /* 63E0C 00163E0C 4487050C */  jal        ChangeBrain_ToKidnap
    /* 63E10 00163E10 2D202001 */   daddu     $4, $9, $0
    /* 63E14 00163E14 04000010 */  b          .L00163E28
    /* 63E18 00163E18 0000BFDF */   ld        $31, 0x0($29)
.align 2
  .L00163E1C:
    /* 63E1C 00163E1C 6686050C */  jal        func_00161998
    /* 63E20 00163E20 2D202001 */   daddu     $4, $9, $0
    /* 63E24 00163E24 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L00163E28:
    /* 63E28 00163E28 0800E003 */  jr         $31
    /* 63E2C 00163E2C 1000BD27 */   addiu     $29, $29, 0x10
endlabel DispCollisionPC
```
