# func_00191F50 — parked

VRAM: 0x00191F50 (file_off 0x091F50)
Asm source: asm/nonmatchings/src/fightSound/func_00191F50.s

## Attempt at 2026-05-31

**Reason parked:** rc=3 floor after 30-stall (33 stalls, 32+ distinct pure-C shapes). ONLY diff = reorg b-delay fill: dbr steals insn164 (addiu %lo of D_0055AE88, standalone because insn163 lui pre-hoisted to cond-delays) into both goto-b delays + deletes from body; ROM copies insn178 (a1=#255 line const) instead, keeping addiu in body. Root: in ROM the file %hi (insn163) is placed by SCHED2 early; in our build it's hoisted by DBR. Need sched2 to raise file-%hi priority WITHOUT widening live range — every early-ref form (file-at-top/fmt-temp) widens live range -> rc23-31. reg-pins disallowed by user; no asm goto in gcc2.9; b-delays in gcc-generated dispatch unreachable by source asm. Ruled out: switch(=3), all dispatch-sense swaps(8-16), inline-both-arms(35), MEM_BARRIER/ANCHOR/KEEP_LIVE(3), line-local/volatile(3/21), access-forms(3), upstream case rewrites(3).

**TU:** `src/fightSound.c`

**Seed:** `tough_nuts/func_00191F50/func_00191F50.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632784, 1

.align 3
nonmatching func_00191F50, 0xF0

glabel func_00191F50
    /* 91F50 00191F50 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 91F54 00191F54 949E838F */  lw         $3, (D_00632784) /* gp_rel: (D_00632784) */
    /* 91F58 00191F58 1000BFFF */  sd         $31, 0x10($29)
    /* 91F5C 00191F5C 01000224 */  addiu      $2, $0, 0x1
    /* 91F60 00191F60 10006210 */  beq        $3, $2, .L00191FA4
    /* 91F64 00191F64 0000B0FF */   sd        $16, 0x0($29)
    /* 91F68 00191F68 02006228 */  slti       $2, $3, 0x2
    /* 91F6C 00191F6C 05004010 */  beqz       $2, .L00191F84
    /* 91F70 00191F70 02000224 */   addiu     $2, $0, 0x2
    /* 91F74 00191F74 07006010 */  beqz       $3, .L00191F94
    /* 91F78 00191F78 5600103C */   lui       $16, %hi(D_0055AE88)
    /* 91F7C 00191F7C 21000010 */  b          .L00192004
    /* 91F80 00191F80 FF000524 */   addiu     $5, $0, 0xFF
.align 2
  .L00191F84:
    /* 91F84 00191F84 16006210 */  beq        $3, $2, .L00191FE0
    /* 91F88 00191F88 5600103C */   lui       $16, %hi(D_0055AE88)
    /* 91F8C 00191F8C 1D000010 */  b          .L00192004
    /* 91F90 00191F90 FF000524 */   addiu     $5, $0, 0xFF
.align 2
  .L00191F94:
    /* 91F94 00191F94 1000BFDF */  ld         $31, 0x10($29)
    /* 91F98 00191F98 0000B0DF */  ld         $16, 0x0($29)
    /* 91F9C 00191F9C 5C470608 */  j          func_00191D70
    /* 91FA0 00191FA0 2000BD27 */   addiu     $29, $29, 0x20
.align 2
  .L00191FA4:
    /* 91FA4 00191FA4 6D00103C */  lui        $16, %hi(D_006D0D28)
    /* 91FA8 00191FA8 280D1026 */  addiu      $16, $16, %lo(D_006D0D28)
    /* 91FAC 00191FAC 4607050C */  jal        func_00141D18
    /* 91FB0 00191FB0 2D200002 */   daddu     $4, $16, $0
    /* 91FB4 00191FB4 2D184000 */  daddu      $3, $2, $0
    /* 91FB8 00191FB8 FFFF023C */  lui        $2, (0xFFFFFFFF >> 16)
    /* 91FBC 00191FBC FFFF4234 */  ori        $2, $2, (0xFFFFFFFF & 0xFFFF)
    /* 91FC0 00191FC0 1B006210 */  beq        $3, $2, .L00192030
    /* 91FC4 00191FC4 F8FF03AE */   sw        $3, -0x8($16)
    /* 91FC8 00191FC8 19006050 */  beql       $3, $0, .L00192030
    /* 91FCC 00191FCC 949E80AF */   sw        $0, (D_00632784) /* gp_rel: (D_00632784) */
    /* 91FD0 00191FD0 C401050C */  jal        func_00140710
    /* 91FD4 00191FD4 2C00648C */   lw        $4, 0x2C($3)
    /* 91FD8 00191FD8 15000010 */  b          .L00192030
    /* 91FDC 00191FDC 949E80AF */   sw        $0, (D_00632784) /* gp_rel: (D_00632784) */
.align 2
  .L00191FE0:
    /* 91FE0 00191FE0 6D00103C */  lui        $16, %hi(D_006D0D20)
    /* 91FE4 00191FE4 200D048E */  lw         $4, %lo(D_006D0D20)($16)
    /* 91FE8 00191FE8 04008050 */  beql       $4, $0, .L00191FFC
    /* 91FEC 00191FEC 200D00AE */   sw        $0, %lo(D_006D0D20)($16)
    /* 91FF0 00191FF0 8007050C */  jal        func_00141E00
    /* 91FF4 00191FF4 00000000 */   nop
    /* 91FF8 00191FF8 200D00AE */  sw         $0, %lo(D_006D0D20)($16)
.align 2
  .L00191FFC:
    /* 91FFC 00191FFC 0C000010 */  b          .L00192030
    /* 92000 00192000 949E80AF */   sw        $0, (D_00632784) /* gp_rel: (D_00632784) */
.align 2
  .L00192004:
    /* 92004 00192004 88AE1026 */  addiu      $16, $16, %lo(D_0055AE88)
    /* 92008 00192008 DAB5060C */  jal        func_001AD768
    /* 9200C 0019200C 2D200002 */   daddu     $4, $16, $0
    /* 92010 00192010 2D200002 */  daddu      $4, $16, $0
    /* 92014 00192014 6300063C */  lui        $6, %hi(D_00632790)
    /* 92018 00192018 1000BFDF */  ld         $31, 0x10($29)
    /* 9201C 0019201C 9027C624 */  addiu      $6, $6, %lo(D_00632790)
    /* 92020 00192020 0000B0DF */  ld         $16, 0x0($29)
    /* 92024 00192024 FF000524 */  addiu      $5, $0, 0xFF
    /* 92028 00192028 FC8F0908 */  j          func_00263FF0
    /* 9202C 0019202C 2000BD27 */   addiu     $29, $29, 0x20
.align 2
  .L00192030:
    /* 92030 00192030 1000BFDF */  ld         $31, 0x10($29)
    /* 92034 00192034 0000B0DF */  ld         $16, 0x0($29)
    /* 92038 00192038 0800E003 */  jr         $31
    /* 9203C 0019203C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00191F50
```
