# func_001D4BD0 — parked

VRAM: 0x001D4BD0 (file_off 0x0D4BD0)
Asm source: asm/nonmatchings/src/lodManager/func_001D4BD0.s

## Attempt at 2026-05-21

**Reason parked:** 5-way switch on (ops[i]-1) for LOD encoding; algorithm semantically matches but gcc reg-allocation differs (s0/s1 save order, v param reg choice). jtbl_006190E0 is 24 bytes (6 entries); original ELF reserves 32 bytes — needs a typed pad section .rodata.0x006190F8 since the next section in 453700.rodata.o has only 4-byte alignment. Permuter should be able to finesse the regalloc; the typed pad needs to be re-added when promoting.

**TU:** `src/lodManager.c`

**Seed:** `tough_nuts/func_001D4BD0/func_001D4BD0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633430, 1

.align 3
nonmatching func_001D4BD0, 0xF4

glabel func_001D4BD0
    /* D4BD0 001D4BD0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* D4BD4 001D4BD4 2000B2FF */  sd         $18, 0x20($29)
    /* D4BD8 001D4BD8 1000B1FF */  sd         $17, 0x10($29)
    /* D4BDC 001D4BDC 2D90A000 */  daddu      $18, $5, $0
    /* D4BE0 001D4BE0 0000B0FF */  sd         $16, 0x0($29)
    /* D4BE4 001D4BE4 3000BFFF */  sd         $31, 0x30($29)
    /* D4BE8 001D4BE8 2D808000 */  daddu      $16, $4, $0
    /* D4BEC 001D4BEC 0000068E */  lw         $6, 0x0($16)
    /* D4BF0 001D4BF0 2E00C010 */  beqz       $6, .L001D4CAC
    /* D4BF4 001D4BF4 2D880000 */   daddu     $17, $0, $0
.align 2
  .L001D4BF8:
    /* D4BF8 001D4BF8 21105102 */  addu       $2, $18, $17
    /* D4BFC 001D4BFC 00004590 */  lbu        $5, 0x0($2)
    /* D4C00 001D4C00 FFFFA324 */  addiu      $3, $5, -0x1
    /* D4C04 001D4C04 0600622C */  sltiu      $2, $3, 0x6
    /* D4C08 001D4C08 07004010 */  beqz       $2, .L001D4C28
    /* D4C0C 001D4C0C 6200023C */   lui       $2, %hi(jtbl_006190E0)
    /* D4C10 001D4C10 80180300 */  sll        $3, $3, 2
    /* D4C14 001D4C14 E0904224 */  addiu      $2, $2, %lo(jtbl_006190E0)
    /* D4C18 001D4C18 21186200 */  addu       $3, $3, $2
    /* D4C1C 001D4C1C 0000648C */  lw         $4, 0x0($3)
    /* D4C20 001D4C20 08008000 */  jr         $4
    /* D4C24 001D4C24 00000000 */   nop
.align 2
  .L001D4C28:
    /* D4C28 001D4C28 6200043C */  lui        $4, %hi(D_00619080)
    /* D4C2C 001D4C2C 8A9B060C */  jal        func_001A6E28
    /* D4C30 001D4C30 80908424 */   addiu     $4, $4, %lo(D_00619080)
    /* D4C34 001D4C34 6200043C */  lui        $4, %hi(D_006190A0)
    /* D4C38 001D4C38 8A9B060C */  jal        func_001A6E28
    /* D4C3C 001D4C3C A0908424 */   addiu     $4, $4, %lo(D_006190A0)
    /* D4C40 001D4C40 16000010 */  b          .L001D4C9C
    /* D4C44 001D4C44 04001026 */   addiu     $16, $16, 0x4
.align 2
  jlabel .L001D4C48
    /* D4C48 001D4C48 40AB828F */  lw         $2, (D_00633430) /* gp_rel: (D_00633430) */
    /* D4C4C 001D4C4C 21104600 */  addu       $2, $2, $6
    /* D4C50 001D4C50 11000010 */  b          .L001D4C98
    /* D4C54 001D4C54 000002AE */   sw        $2, 0x0($16)
.align 2
  jlabel .L001D4C58
    /* D4C58 001D4C58 40AB828F */  lw         $2, (D_00633430) /* gp_rel: (D_00633430) */
    /* D4C5C 001D4C5C 21184600 */  addu       $3, $2, $6
    /* D4C60 001D4C60 0000648C */  lw         $4, 0x0($3)
    /* D4C64 001D4C64 000003AE */  sw         $3, 0x0($16)
    /* D4C68 001D4C68 21104400 */  addu       $2, $2, $4
    /* D4C6C 001D4C6C 0A000010 */  b          .L001D4C98
    /* D4C70 001D4C70 000062AC */   sw        $2, 0x0($3)
.align 2
  jlabel .L001D4C74
    /* D4C74 001D4C74 40AB848F */  lw         $4, (D_00633430) /* gp_rel: (D_00633430) */
    /* D4C78 001D4C78 21108600 */  addu       $2, $4, $6
    /* D4C7C 001D4C7C 0000438C */  lw         $3, 0x0($2)
    /* D4C80 001D4C80 0400458C */  lw         $5, 0x4($2)
    /* D4C84 001D4C84 21188300 */  addu       $3, $4, $3
    /* D4C88 001D4C88 000002AE */  sw         $2, 0x0($16)
    /* D4C8C 001D4C8C 21208500 */  addu       $4, $4, $5
    /* D4C90 001D4C90 000043AC */  sw         $3, 0x0($2)
    /* D4C94 001D4C94 040044AC */  sw         $4, 0x4($2)
.align 2
  .L001D4C98:
    /* D4C98 001D4C98 04001026 */  addiu      $16, $16, 0x4
.align 2
  .L001D4C9C:
    /* D4C9C 001D4C9C 01003126 */  addiu      $17, $17, 0x1
    /* D4CA0 001D4CA0 0000028E */  lw         $2, 0x0($16)
    /* D4CA4 001D4CA4 D4FF4014 */  bnez       $2, .L001D4BF8
    /* D4CA8 001D4CA8 2D304000 */   daddu     $6, $2, $0
.align 2
  .L001D4CAC:
    /* D4CAC 001D4CAC 3000BFDF */  ld         $31, 0x30($29)
    /* D4CB0 001D4CB0 2000B2DF */  ld         $18, 0x20($29)
    /* D4CB4 001D4CB4 1000B1DF */  ld         $17, 0x10($29)
    /* D4CB8 001D4CB8 0000B0DF */  ld         $16, 0x0($29)
    /* D4CBC 001D4CBC 0800E003 */  jr         $31
    /* D4CC0 001D4CC0 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001D4BD0
    /* D4CC4 001D4CC4 00000000 */  nop
```
