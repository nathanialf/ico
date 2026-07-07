# dispSquare2 — parked

VRAM: 0x001D5E48 (file_off 0x0D5E48)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionManager/dispSquare2.s

## Attempt at 2026-07-07

**Reason parked:** rc13 near-miss. int dispSquare2(int type, float thresh). STRUCTURE FULLY RECOVERED: if(D_0062C230->0x220!=0){if(type==6||0xB)ret -1;} st=->0x280; if(st){if(type==0x16||0x1B)ret -1;} for(i=0;i<D_0062C22C;i++){ if(*(int*)(D_0062B758+i*64+4)==type){ if(*(int*)(D_0062C218+i*32)>=0xF9)ret -1; f0=*(float*)(D_0062C224+i*16+4)+D_00703094[0]; if(f0<0){f0=-f0; if(f0<thresh)ret type; ret -1;} if(!(f0<thresh))ret -1; ret type; } } ret -1. LEVERS THAT WORKED: goto-CFG for return sharing (rc16), asymmetric abs-compare polarity if(!(f0<thresh)) blocks cross-jump into bc1tl -> two explicit c.lt.s (rc13), bare for-loop=single blez guard sharing count<=0 with loop-exit L5F34. RESIDUAL (~13, mostly ONE cascade): ROM places shared error-return block L5E6C EARLY at 0x24 (enabling bnel type!=0xB with st-load in delay + type==0xB fall-through) + duplicates st-load into bnel delay; my ee-gcc places ret_neg1 at end (0xec) -> ~8 target-addr diffs + beq-not-bnel. gcc block-placement/delay-fill artifact; inline-returns(rc15) and explicit-CFG-dup-st(rc15) both regressed. RESUME: permuter on rc13 seed, or find lever to place error-return block early.

**TU:** `sugipon/src/motionManager.c`

**Seed:** `tough_nuts/dispSquare2/dispSquare2.c`

Disassembly:

```
.align 3
nonmatching dispSquare2, 0xF4

glabel dispSquare2
    /* D5E48 001D5E48 40B6838F */  lw         $3, %gp_rel(D_0062C230)($28)
    /* D5E4C 001D5E4C 2002628C */  lw         $2, 0x220($3)
    /* D5E50 001D5E50 08004010 */  beqz       $2, .L001D5E74
    /* D5E54 001D5E54 2D388000 */   daddu     $7, $4, $0
    /* D5E58 001D5E58 06000224 */  addiu      $2, $0, 0x6
    /* D5E5C 001D5E5C 0300E210 */  beq        $7, $2, .L001D5E6C
    /* D5E60 001D5E60 0B000224 */   addiu     $2, $0, 0xB
    /* D5E64 001D5E64 0400E254 */  bnel       $7, $2, .L001D5E78
    /* D5E68 001D5E68 8002628C */   lw        $2, 0x280($3)
.align 2
  .L001D5E6C:
    /* D5E6C 001D5E6C 0800E003 */  jr         $31
    /* D5E70 001D5E70 FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L001D5E74:
    /* D5E74 001D5E74 8002628C */  lw         $2, 0x280($3)
.align 2
  .L001D5E78:
    /* D5E78 001D5E78 05004010 */  beqz       $2, .L001D5E90
    /* D5E7C 001D5E7C 16000224 */   addiu     $2, $0, 0x16
    /* D5E80 001D5E80 FAFFE210 */  beq        $7, $2, .L001D5E6C
    /* D5E84 001D5E84 1B000224 */   addiu     $2, $0, 0x1B
    /* D5E88 001D5E88 F8FFE210 */  beq        $7, $2, .L001D5E6C
    /* D5E8C 001D5E8C 00000000 */   nop
.align 2
  .L001D5E90:
    /* D5E90 001D5E90 3CB6868F */  lw         $6, %gp_rel(D_0062C22C)($28)
    /* D5E94 001D5E94 2700C018 */  blez       $6, .L001D5F34
    /* D5E98 001D5E98 2D280000 */   daddu     $5, $0, $0
    /* D5E9C 001D5E9C 68AB848F */  lw         $4, %gp_rel(D_0062B758)($28)
    /* D5EA0 001D5EA0 80110500 */  sll        $2, $5, 6
    /* D5EA4 001D5EA4 00000000 */  nop
.align 2
  .L001D5EA8:
    /* D5EA8 001D5EA8 21104400 */  addu       $2, $2, $4
    /* D5EAC 001D5EAC 0400438C */  lw         $3, 0x4($2)
    /* D5EB0 001D5EB0 1D006754 */  bnel       $3, $7, .L001D5F28
    /* D5EB4 001D5EB4 0100A524 */   addiu     $5, $5, 0x1
    /* D5EB8 001D5EB8 28B6828F */  lw         $2, %gp_rel(D_0062C218)($28)
    /* D5EBC 001D5EBC 40190500 */  sll        $3, $5, 5
    /* D5EC0 001D5EC0 21186200 */  addu       $3, $3, $2
    /* D5EC4 001D5EC4 0000648C */  lw         $4, 0x0($3)
    /* D5EC8 001D5EC8 F9008428 */  slti       $4, $4, 0xF9
    /* D5ECC 001D5ECC E7FF8010 */  beqz       $4, .L001D5E6C
    /* D5ED0 001D5ED0 34B6848F */   lw        $4, %gp_rel(D_0062C224)($28)
    /* D5ED4 001D5ED4 00110500 */  sll        $2, $5, 4
    /* D5ED8 001D5ED8 7000033C */  lui        $3, %hi(D_00703094)
    /* D5EDC 001D5EDC 00108044 */  mtc1       $0, $f2
    /* D5EE0 001D5EE0 21104400 */  addu       $2, $2, $4
    /* D5EE4 001D5EE4 943061C4 */  lwc1       $f1, %lo(D_00703094)($3)
    /* D5EE8 001D5EE8 040040C4 */  lwc1       $f0, 0x4($2)
    /* D5EEC 001D5EEC 00000146 */  add.s      $f0, $f0, $f1
    /* D5EF0 001D5EF0 34000246 */  c.lt.s     $f0, $f2
    /* D5EF4 001D5EF4 07000045 */  bc1f       .L001D5F14
    /* D5EF8 001D5EF8 00000000 */   nop
    /* D5EFC 001D5EFC 07000046 */  neg.s      $f0, $f0
    /* D5F00 001D5F00 34000C46 */  c.lt.s     $f0, $f12
    /* D5F04 001D5F04 06000145 */  bc1t       .L001D5F20
    /* D5F08 001D5F08 00000000 */   nop
    /* D5F0C 001D5F0C D7FF0010 */  b          .L001D5E6C
    /* D5F10 001D5F10 00000000 */   nop
.align 2
  .L001D5F14:
    /* D5F14 001D5F14 34000C46 */  c.lt.s     $f0, $f12
    /* D5F18 001D5F18 D4FF0045 */  bc1f       .L001D5E6C
    /* D5F1C 001D5F1C 00000000 */   nop
.align 2
  .L001D5F20:
    /* D5F20 001D5F20 0800E003 */  jr         $31
    /* D5F24 001D5F24 2D10E000 */   daddu     $2, $7, $0
.align 2
  .L001D5F28:
    /* D5F28 001D5F28 2A10A600 */  slt        $2, $5, $6
    /* D5F2C 001D5F2C DEFF4014 */  bnez       $2, .L001D5EA8
    /* D5F30 001D5F30 80110500 */   sll       $2, $5, 6
.align 2
  .L001D5F34:
    /* D5F34 001D5F34 0800E003 */  jr         $31
    /* D5F38 001D5F38 FFFF0224 */   addiu     $2, $0, -0x1
endlabel dispSquare2
    /* D5F3C 001D5F3C 00000000 */  nop
```
