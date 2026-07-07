# correctJumpOrientByChain — parked

VRAM: 0x0015B560 (file_off 0x05B560)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/correctJumpOrientByChain.s

## Attempt at 2026-07-07

**Reason parked:** rc34; STRUCTURE RECOVERED (two table lookups D_00288FD0[s164->0x44] stride0x14 + D_0028E680 SlowrunRec stores w[2]/w[0] + guarded fill loop c..d). Residual COUPLED: (1) ROM emits 3x base-copy 'daddu copy,entry; lw dst,off(copy)' before field loads a/b/c while built folds offset into lw off(entry) directly; (2) field-load/delay-slot order (ROM: a,b,c pre-beq, d in delay; built: d,a,b pre-beq, c in delay); (3) register-rename cascade s164 v1-vs-a1. 3 distinct spellings (named locals, inlined derefs, reordered index-before-val) ALL FOLD to rc34. permuter-class basefold/dual_addr.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/correctJumpOrientByChain/correctJumpOrientByChain.c`

Disassembly:

```
.align 3
nonmatching correctJumpOrientByChain, 0xAC

glabel correctJumpOrientByChain
    /* 5B560 0015B560 6401838C */  lw         $3, 0x164($4)
    /* 5B564 0015B564 14000724 */  addiu      $7, $0, 0x14
    /* 5B568 0015B568 5C01868C */  lw         $6, 0x15C($4)
    /* 5B56C 0015B56C 2900023C */  lui        $2, %hi(D_00288FD0)
    /* 5B570 0015B570 4400658C */  lw         $5, 0x44($3)
    /* 5B574 0015B574 D08F4224 */  addiu      $2, $2, %lo(D_00288FD0)
    /* 5B578 0015B578 9004C98C */  lw         $9, 0x490($6)
    /* 5B57C 0015B57C 40040824 */  addiu      $8, $0, 0x440
    /* 5B580 0015B580 1828A700 */  mult       $5, $5, $7
    /* 5B584 0015B584 21304500 */  addu       $6, $2, $5
    /* 5B588 0015B588 2D18C000 */  daddu      $3, $6, $0
    /* 5B58C 0015B58C 2D20C000 */  daddu      $4, $6, $0
    /* 5B590 0015B590 2D10C000 */  daddu      $2, $6, $0
    /* 5B594 0015B594 0400638C */  lw         $3, 0x4($3)
    /* 5B598 0015B598 0800848C */  lw         $4, 0x8($4)
    /* 5B59C 0015B59C 0C00458C */  lw         $5, 0xC($2)
    /* 5B5A0 0015B5A0 18002811 */  beq        $9, $8, .L0015B604
    /* 5B5A4 0015B5A4 1000CA8C */   lw        $10, 0x10($6)
    /* 5B5A8 0015B5A8 18000724 */  addiu      $7, $0, 0x18
    /* 5B5AC 0015B5AC 2D30A000 */  daddu      $6, $5, $0
    /* 5B5B0 0015B5B0 18186700 */  mult       $3, $3, $7
    /* 5B5B4 0015B5B4 2900023C */  lui        $2, %hi(D_0028E680)
    /* 5B5B8 0015B5B8 18288700 */  mult       $5, $4, $7
    /* 5B5BC 0015B5BC 80E64824 */  addiu      $8, $2, %lo(D_0028E680)
    /* 5B5C0 0015B5C0 08000225 */  addiu      $2, $8, 0x8
    /* 5B5C4 0015B5C4 21186200 */  addu       $3, $3, $2
    /* 5B5C8 0015B5C8 2120A200 */  addu       $4, $5, $2
    /* 5B5CC 0015B5CC 000069AC */  sw         $9, 0x0($3)
    /* 5B5D0 0015B5D0 2A28CA00 */  slt        $5, $6, $10
    /* 5B5D4 0015B5D4 0B00A010 */  beqz       $5, .L0015B604
    /* 5B5D8 0015B5D8 000089AC */   sw        $9, 0x0($4)
    /* 5B5DC 0015B5DC 1818C700 */  mult       $3, $6, $7
    /* 5B5E0 0015B5E0 23304601 */  subu       $6, $10, $6
    /* 5B5E4 0015B5E4 21106800 */  addu       $2, $3, $8
.align 2
  .L0015B5E8:
    /* 5B5E8 0015B5E8 000049AC */  sw         $9, 0x0($2)
    /* 5B5EC 0015B5EC FFFFC624 */  addiu      $6, $6, -0x1
    /* 5B5F0 0015B5F0 18004224 */  addiu      $2, $2, 0x18
    /* 5B5F4 0015B5F4 00000000 */  nop
    /* 5B5F8 0015B5F8 00000000 */  nop
    /* 5B5FC 0015B5FC FAFFC014 */  bnez       $6, .L0015B5E8
    /* 5B600 0015B600 00000000 */   nop
.align 2
  .L0015B604:
    /* 5B604 0015B604 0800E003 */  jr         $31
    /* 5B608 0015B608 00000000 */   nop
endlabel correctJumpOrientByChain
    /* 5B60C 0015B60C 00000000 */  nop
```
