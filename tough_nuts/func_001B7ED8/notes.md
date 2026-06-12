# func_001B7ED8 — parked

VRAM: 0x001B7ED8 (file_off 0x0B7ED8)
Asm source: asm/aug6/nonmatchings/sugipon/src/actressLight/func_001B7ED8.s

## Attempt at 2026-06-12

**Reason parked:** best rc34 (multi-return + single shared epilogue + typed ALState + inline clamps). ROOT: clamp lower-bound emits movn (cond-move) vs ROM bnel (branch-likely cond-assign); also bc1t-vs-bc1f on 50.0 check + 0x800 clamp not sharing. Single-epilogue (ret var) FIXED the original self/st s0/s1 swap; multi-return keeps ret in v0. Levers to try next: force bnel on 'if(r3<-N) r3=-N' (int-index/do-while form per int_index_loop_forces_bnel), fix 50.0 bc1t sense, share L8028 0x800 clamp tail.

**TU:** `sugipon/src/actressLight.c`

**Seed:** `tough_nuts/func_001B7ED8/func_001B7ED8.c`

Disassembly:

```
.align 3
nonmatching func_001B7ED8, 0x1B8

glabel func_001B7ED8
    /* B7ED8 001B7ED8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* B7EDC 001B7EDC 0000B0FF */  sd         $16, 0x0($29)
    /* B7EE0 001B7EE0 2000BFFF */  sd         $31, 0x20($29)
    /* B7EE4 001B7EE4 2D808000 */  daddu      $16, $4, $0
    /* B7EE8 001B7EE8 1000B1FF */  sd         $17, 0x10($29)
    /* B7EEC 001B7EEC 6401118E */  lw         $17, 0x164($16)
    /* B7EF0 001B7EF0 200022DE */  ld         $2, 0x20($17)
    /* B7EF4 001B7EF4 78160200 */  dsll       $2, $2, 25
    /* B7EF8 001B7EF8 3F100200 */  dsra32     $2, $2, 0
    /* B7EFC 001B7EFC 01004230 */  andi       $2, $2, 0x1
    /* B7F00 001B7F00 49004014 */  bnez       $2, .L001B8028
    /* B7F04 001B7F04 F6B58387 */   lh        $3, %gp_rel(D_0062C1E6)($28)
    /* B7F08 001B7F08 F0B581C7 */  lwc1       $f1, %gp_rel(D_0062C1E0)($28)
    /* B7F0C 001B7F0C FA43013C */  lui        $1, (0x43FA0000 >> 16)
    /* B7F10 001B7F10 00008144 */  mtc1       $1, $f0
    /* B7F14 001B7F14 34080046 */  c.lt.s     $f1, $f0
    /* B7F18 001B7F18 00000000 */  nop
    /* B7F1C 001B7F1C 2E000045 */  bc1f       .L001B7FD8
    /* B7F20 001B7F20 8C00228E */   lw        $2, 0x8C($17)
    /* B7F24 001B7F24 05004010 */  beqz       $2, .L001B7F3C
    /* B7F28 001B7F28 2D200002 */   daddu     $4, $16, $0
    /* B7F2C 001B7F2C F6DE060C */  jal        AP1BeforeFunc
    /* B7F30 001B7F30 01000524 */   addiu     $5, $0, 0x1
    /* B7F34 001B7F34 51004014 */  bnez       $2, .L001B807C
    /* B7F38 001B7F38 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001B7F3C:
    /* B7F3C 001B7F3C FCB581C7 */  lwc1       $f1, %gp_rel(D_0062C1EC)($28)
    /* B7F40 001B7F40 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* B7F44 001B7F44 00008144 */  mtc1       $1, $f0
    /* B7F48 001B7F48 34000146 */  c.lt.s     $f0, $f1
    /* B7F4C 001B7F4C 00000000 */  nop
    /* B7F50 001B7F50 07000045 */  bc1f       .L001B7F70
    /* B7F54 001B7F54 2D200002 */   daddu     $4, $16, $0
    /* B7F58 001B7F58 F6DE060C */  jal        AP1BeforeFunc
    /* B7F5C 001B7F5C 01000524 */   addiu     $5, $0, 0x1
    /* B7F60 001B7F60 04004010 */  beqz       $2, .L001B7F74
    /* B7F64 001B7F64 F4B58287 */   lh        $2, %gp_rel(D_0062C1E4)($28)
    /* B7F68 001B7F68 44000010 */  b          .L001B807C
    /* B7F6C 001B7F6C 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001B7F70:
    /* B7F70 001B7F70 F4B58287 */  lh         $2, %gp_rel(D_0062C1E4)($28)
.align 2
  .L001B7F74:
    /* B7F74 001B7F74 00404228 */  slti       $2, $2, 0x4000
    /* B7F78 001B7F78 11004010 */  beqz       $2, .L001B7FC0
    /* B7F7C 001B7F7C F0B581C7 */   lwc1      $f1, %gp_rel(D_0062C1E0)($28)
    /* B7F80 001B7F80 9643013C */  lui        $1, (0x43960000 >> 16)
    /* B7F84 001B7F84 00008144 */  mtc1       $1, $f0
    /* B7F88 001B7F88 34000146 */  c.lt.s     $f0, $f1
    /* B7F8C 001B7F8C 00000000 */  nop
    /* B7F90 001B7F90 0B000045 */  bc1f       .L001B7FC0
    /* B7F94 001B7F94 F6B58387 */   lh        $3, %gp_rel(D_0062C1E6)($28)
    /* B7F98 001B7F98 01106228 */  slti       $2, $3, 0x1001
    /* B7F9C 001B7F9C 06004010 */  beqz       $2, .L001B7FB8
    /* B7FA0 001B7FA0 2D106000 */   daddu     $2, $3, $0
    /* B7FA4 001B7FA4 00F04228 */  slti       $2, $2, -0x1000
    /* B7FA8 001B7FA8 25004054 */  bnel       $2, $0, .L001B8040
    /* B7FAC 001B7FAC 00F00324 */   addiu     $3, $0, -0x1000
    /* B7FB0 001B7FB0 24000010 */  b          .L001B8044
    /* B7FB4 001B7FB4 00140300 */   sll       $2, $3, 16
.align 2
  .L001B7FB8:
    /* B7FB8 001B7FB8 25000010 */  b          .L001B8050
    /* B7FBC 001B7FBC 00100524 */   addiu     $5, $0, 0x1000
.align 2
  .L001B7FC0:
    /* B7FC0 001B7FC0 2D200002 */  daddu      $4, $16, $0
    /* B7FC4 001B7FC4 F6DE060C */  jal        AP1BeforeFunc
    /* B7FC8 001B7FC8 01000524 */   addiu     $5, $0, 0x1
    /* B7FCC 001B7FCC 2B004014 */  bnez       $2, .L001B807C
    /* B7FD0 001B7FD0 01000224 */   addiu     $2, $0, 0x1
    /* B7FD4 001B7FD4 8C00228E */  lw         $2, 0x8C($17)
.align 2
  .L001B7FD8:
    /* B7FD8 001B7FD8 0C004010 */  beqz       $2, .L001B800C
    /* B7FDC 001B7FDC FCB581C7 */   lwc1      $f1, %gp_rel(D_0062C1EC)($28)
    /* B7FE0 001B7FE0 4842013C */  lui        $1, (0x42480000 >> 16)
    /* B7FE4 001B7FE4 00008144 */  mtc1       $1, $f0
    /* B7FE8 001B7FE8 34080046 */  c.lt.s     $f1, $f0
    /* B7FEC 001B7FEC 00000000 */  nop
    /* B7FF0 001B7FF0 0D000145 */  bc1t       .L001B8028
    /* B7FF4 001B7FF4 00B68387 */   lh        $3, %gp_rel(D_0062C1F0)($28)
    /* B7FF8 001B7FF8 2D200002 */  daddu      $4, $16, $0
    /* B7FFC 001B7FFC F6DE060C */  jal        AP1BeforeFunc
    /* B8000 001B8000 01000524 */   addiu     $5, $0, 0x1
    /* B8004 001B8004 1D004014 */  bnez       $2, .L001B807C
    /* B8008 001B8008 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001B800C:
    /* B800C 001B800C FCB581C7 */  lwc1       $f1, %gp_rel(D_0062C1EC)($28)
    /* B8010 001B8010 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* B8014 001B8014 00008144 */  mtc1       $1, $f0
    /* B8018 001B8018 34080046 */  c.lt.s     $f1, $f0
    /* B801C 001B801C 00000000 */  nop
    /* B8020 001B8020 0F000045 */  bc1f       .L001B8060
    /* B8024 001B8024 F6B58387 */   lh        $3, %gp_rel(D_0062C1E6)($28)
.align 2
  .L001B8028:
    /* B8028 001B8028 01086228 */  slti       $2, $3, 0x801
    /* B802C 001B802C 07004010 */  beqz       $2, .L001B804C
    /* B8030 001B8030 2D106000 */   daddu     $2, $3, $0
    /* B8034 001B8034 00F84228 */  slti       $2, $2, -0x800
    /* B8038 001B8038 01004054 */  bnel       $2, $0, .L001B8040
    /* B803C 001B803C 00F80324 */   addiu     $3, $0, -0x800
.align 2
  .L001B8040:
    /* B8040 001B8040 00140300 */  sll        $2, $3, 16
.align 2
  .L001B8044:
    /* B8044 001B8044 02000010 */  b          .L001B8050
    /* B8048 001B8048 032C0200 */   sra       $5, $2, 16
.align 2
  .L001B804C:
    /* B804C 001B804C 00080524 */  addiu      $5, $0, 0x800
.align 2
  .L001B8050:
    /* B8050 001B8050 C2DE060C */  jal        hitProc
    /* B8054 001B8054 2D200002 */   daddu     $4, $16, $0
    /* B8058 001B8058 08000010 */  b          .L001B807C
    /* B805C 001B805C FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L001B8060:
    /* B8060 001B8060 2D200002 */  daddu      $4, $16, $0
    /* B8064 001B8064 F6DE060C */  jal        AP1BeforeFunc
    /* B8068 001B8068 01000524 */   addiu     $5, $0, 0x1
    /* B806C 001B806C FFFF0424 */  addiu      $4, $0, -0x1
    /* B8070 001B8070 01000324 */  addiu      $3, $0, 0x1
    /* B8074 001B8074 0A188200 */  movz       $3, $4, $2
    /* B8078 001B8078 2D106000 */  daddu      $2, $3, $0
.align 2
  .L001B807C:
    /* B807C 001B807C 2000BFDF */  ld         $31, 0x20($29)
    /* B8080 001B8080 1000B1DF */  ld         $17, 0x10($29)
    /* B8084 001B8084 0000B0DF */  ld         $16, 0x0($29)
    /* B8088 001B8088 0800E003 */  jr         $31
    /* B808C 001B808C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001B7ED8
```
