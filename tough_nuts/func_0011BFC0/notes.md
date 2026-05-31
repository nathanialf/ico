# func_0011BFC0 — parked

VRAM: 0x0011BFC0 (file_off 0x01BFC0)
Asm source: asm/nonmatchings/src/Primitive/func_0011BFC0.s

## Attempt at 2026-05-31

**Reason parked:** rc1 count-down loop near-miss + ALIGNMENT BLOCKER. Clean C: p=(u8*)(a0*16+0x1100C000); if(count<=0)return; i=count; loop:{arg=p;p+=16;func_00118FD8(arg,a2);} if(--i)goto loop;  -> rc1, the loop body matches (p+=16 in jal delay, a0 carried in bnez delay via the goto_loop_jal_delay_choice arg/advance shape). SOLE residual: gcc emits .p2align 3 before the loop which over-pads vs the ROM's exact layout (ROM loop .L0011BFF8 at 0x11BFF8, one nop pad). quick_diff rc1 (missing/misplaced loop nop); ninja SHA FAILS + breaks a sibling (4-byte shift). This is the coalesced_tu_c_func_alignment situation; the clean fix (-malign-loops=2 / demote_p2align.txt) is RETIRED machinery. do-while(rc4), while(rc9) worse. Needs a loop-align lever or the retired demote. NOT a codegen floor, stall 4.

**TU:** `src/Primitive.c`

**Seed:** `tough_nuts/func_0011BFC0/func_0011BFC0.c`

Disassembly:

```
.align 3
nonmatching func_0011BFC0, 0x68

glabel func_0011BFC0
    /* 1BFC0 0011BFC0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 1BFC4 0011BFC4 0011023C */  lui        $2, (0x1100C000 >> 16)
    /* 1BFC8 0011BFC8 2000B2FF */  sd         $18, 0x20($29)
    /* 1BFCC 0011BFCC 00210400 */  sll        $4, $4, 4
    /* 1BFD0 0011BFD0 1000B1FF */  sd         $17, 0x10($29)
    /* 1BFD4 0011BFD4 00C04234 */  ori        $2, $2, (0x1100C000 & 0xFFFF)
    /* 1BFD8 0011BFD8 3000BFFF */  sd         $31, 0x30($29)
    /* 1BFDC 0011BFDC 21888200 */  addu       $17, $4, $2
    /* 1BFE0 0011BFE0 0000B0FF */  sd         $16, 0x0($29)
    /* 1BFE4 0011BFE4 0A00A018 */  blez       $5, .L0011C010
    /* 1BFE8 0011BFE8 2D90C000 */   daddu     $18, $6, $0
    /* 1BFEC 0011BFEC 2D80A000 */  daddu      $16, $5, $0
    /* 1BFF0 0011BFF0 2D202002 */  daddu      $4, $17, $0
    /* 1BFF4 0011BFF4 00000000 */  nop
.align 2
  .L0011BFF8:
    /* 1BFF8 0011BFF8 2D284002 */  daddu      $5, $18, $0
    /* 1BFFC 0011BFFC F663040C */  jal        func_00118FD8
    /* 1C000 0011C000 10003126 */   addiu     $17, $17, 0x10
    /* 1C004 0011C004 FFFF1026 */  addiu      $16, $16, -0x1
    /* 1C008 0011C008 FBFF0016 */  bnez       $16, .L0011BFF8
    /* 1C00C 0011C00C 2D202002 */   daddu     $4, $17, $0
.align 2
  .L0011C010:
    /* 1C010 0011C010 3000BFDF */  ld         $31, 0x30($29)
    /* 1C014 0011C014 2000B2DF */  ld         $18, 0x20($29)
    /* 1C018 0011C018 1000B1DF */  ld         $17, 0x10($29)
    /* 1C01C 0011C01C 0000B0DF */  ld         $16, 0x0($29)
    /* 1C020 0011C020 0800E003 */  jr         $31
    /* 1C024 0011C024 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_0011BFC0
```
