# func_00118B18 — parked

VRAM: 0x00118B18 (file_off 0x018B18)
Asm source: asm/nonmatchings/src/Packet/func_00118B18.s

## Attempt at 2026-05-22

**Reason parked:** Iter 29 best: 85 vs 84 lines (1 insn off). MATERIALIZE(cp) in case 2 breaks ee-gcc 2.9 tail-merge of byte-identical case 0/1+2 bodies (target has distinct labels for same bytes) at cost of +1 insn for the materialization move. Remaining diff: prologue scheduling (D[4]=p+8 emitted early in build vs in beqz delay slot in target). Tried: -fno-cse-follow-jumps, -fno-thread-jumps, -fno-gcse, -fno-optimize-sibling-calls (all no effect), volatile cast on D[4], memory barriers, REG pins. No 2.9-era flag found to disable switch-body tail-merge.

**TU:** `src/Packet.c`

**Seed:** `tough_nuts/func_00118B18/func_00118B18.c`

Disassembly:

```
.align 3
nonmatching func_00118B18, 0x150

glabel func_00118B18
    /* 18B18 00118B18 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 18B1C 00118B1C FFFF8724 */  addiu      $7, $4, -0x1
    /* 18B20 00118B20 0000B0FF */  sd         $16, 0x0($29)
    /* 18B24 00118B24 0010063C */  lui        $6, (0x10000000 >> 16)
    /* 18B28 00118B28 1000BFFF */  sd         $31, 0x10($29)
    /* 18B2C 00118B2C 4C00103C */  lui        $16, %hi(D_004C7710)
    /* 18B30 00118B30 10770226 */  addiu      $2, $16, %lo(D_004C7710)
    /* 18B34 00118B34 2D40A000 */  daddu      $8, $5, $0
    /* 18B38 00118B38 1000438C */  lw         $3, 0x10($2)
    /* 18B3C 00118B3C 0500E52C */  sltiu      $5, $7, 0x5
    /* 18B40 00118B40 180040AC */  sw         $0, 0x18($2)
    /* 18B44 00118B44 0C0043AC */  sw         $3, 0xC($2)
    /* 18B48 00118B48 08006424 */  addiu      $4, $3, 0x8
    /* 18B4C 00118B4C 1C0040AC */  sw         $0, 0x1C($2)
    /* 18B50 00118B50 140043AC */  sw         $3, 0x14($2)
    /* 18B54 00118B54 000066FC */  sd         $6, 0x0($3)
    /* 18B58 00118B58 2C00A010 */  beqz       $5, .L00118C0C
    /* 18B5C 00118B5C 100044AC */   sw        $4, 0x10($2)
    /* 18B60 00118B60 5500023C */  lui        $2, %hi(jtbl_00554DB0)
    /* 18B64 00118B64 80180700 */  sll        $3, $7, 2
    /* 18B68 00118B68 B04D4224 */  addiu      $2, $2, %lo(jtbl_00554DB0)
    /* 18B6C 00118B6C 21186200 */  addu       $3, $3, $2
    /* 18B70 00118B70 0000648C */  lw         $4, 0x0($3)
    /* 18B74 00118B74 08008000 */  jr         $4
    /* 18B78 00118B78 00000000 */   nop
.align 2
  jlabel .L00118B7C
    /* 18B7C 00118B7C 10770526 */  addiu      $5, $16, %lo(D_004C7710)
    /* 18B80 00118B80 0003023C */  lui        $2, (0x3000100 >> 16)
    /* 18B84 00118B84 1000A38C */  lw         $3, 0x10($5)
    /* 18B88 00118B88 00014234 */  ori        $2, $2, (0x3000100 & 0xFFFF)
    /* 18B8C 00118B8C 0002043C */  lui        $4, (0x2000180 >> 16)
    /* 18B90 00118B90 000062AC */  sw         $2, 0x0($3)
    /* 18B94 00118B94 18000010 */  b          .L00118BF8
    /* 18B98 00118B98 80018434 */   ori       $4, $4, (0x2000180 & 0xFFFF)
.align 2
  jlabel .L00118B9C
    /* 18B9C 00118B9C 10770526 */  addiu      $5, $16, 0x7710
    /* 18BA0 00118BA0 0003023C */  lui        $2, (0x3000100 >> 16)
    /* 18BA4 00118BA4 1000A38C */  lw         $3, 0x10($5)
    /* 18BA8 00118BA8 00014234 */  ori        $2, $2, (0x3000100 & 0xFFFF)
    /* 18BAC 00118BAC 0002043C */  lui        $4, (0x2000180 >> 16)
    /* 18BB0 00118BB0 000062AC */  sw         $2, 0x0($3)
    /* 18BB4 00118BB4 10000010 */  b          .L00118BF8
    /* 18BB8 00118BB8 80018434 */   ori       $4, $4, (0x2000180 & 0xFFFF)
.align 2
  jlabel .L00118BBC
    /* 18BBC 00118BBC 10770526 */  addiu      $5, $16, 0x7710
    /* 18BC0 00118BC0 0003023C */  lui        $2, (0x3000010 >> 16)
    /* 18BC4 00118BC4 1000A38C */  lw         $3, 0x10($5)
    /* 18BC8 00118BC8 10004234 */  ori        $2, $2, (0x3000010 & 0xFFFF)
    /* 18BCC 00118BCC 0002043C */  lui        $4, (0x20001F8 >> 16)
    /* 18BD0 00118BD0 000062AC */  sw         $2, 0x0($3)
    /* 18BD4 00118BD4 08000010 */  b          .L00118BF8
    /* 18BD8 00118BD8 F8018434 */   ori       $4, $4, (0x20001F8 & 0xFFFF)
.align 2
  jlabel .L00118BDC
    /* 18BDC 00118BDC 10770526 */  addiu      $5, $16, 0x7710
    /* 18BE0 00118BE0 0003023C */  lui        $2, (0x3000010 >> 16)
    /* 18BE4 00118BE4 1000A38C */  lw         $3, 0x10($5)
    /* 18BE8 00118BE8 10004234 */  ori        $2, $2, (0x3000010 & 0xFFFF)
    /* 18BEC 00118BEC 0002043C */  lui        $4, (0x200016A >> 16)
    /* 18BF0 00118BF0 000062AC */  sw         $2, 0x0($3)
    /* 18BF4 00118BF4 6A018434 */  ori        $4, $4, (0x200016A & 0xFFFF)
.align 2
  .L00118BF8:
    /* 18BF8 00118BF8 04006324 */  addiu      $3, $3, 0x4
    /* 18BFC 00118BFC 1000A3AC */  sw         $3, 0x10($5)
    /* 18C00 00118C00 04006224 */  addiu      $2, $3, 0x4
    /* 18C04 00118C04 000064AC */  sw         $4, 0x0($3)
    /* 18C08 00118C08 1000A2AC */  sw         $2, 0x10($5)
.align 2
  .L00118C0C:
    /* 18C0C 00118C0C 10771026 */  addiu      $16, $16, %lo(D_004C7710)
    /* 18C10 00118C10 0060063C */  lui        $6, (0x60000000 >> 16)
    /* 18C14 00118C14 1000028E */  lw         $2, 0x10($16)
    /* 18C18 00118C18 2D200001 */  daddu      $4, $8, $0
    /* 18C1C 00118C1C 140002AE */  sw         $2, 0x14($16)
    /* 18C20 00118C20 08004324 */  addiu      $3, $2, 0x8
    /* 18C24 00118C24 000046FC */  sd         $6, 0x0($2)
    /* 18C28 00118C28 0C004524 */  addiu      $5, $2, 0xC
    /* 18C2C 00118C2C 100003AE */  sw         $3, 0x10($16)
    /* 18C30 00118C30 10004624 */  addiu      $6, $2, 0x10
    /* 18C34 00118C34 080040AC */  sw         $0, 0x8($2)
    /* 18C38 00118C38 100005AE */  sw         $5, 0x10($16)
    /* 18C3C 00118C3C 0C0040AC */  sw         $0, 0xC($2)
    /* 18C40 00118C40 A0EE070C */  jal        func_001FBA80
    /* 18C44 00118C44 100006AE */   sw        $6, 0x10($16)
    /* 18C48 00118C48 0C00058E */  lw         $5, 0xC($16)
    /* 18C4C 00118C4C 2D300000 */  daddu      $6, $0, $0
    /* 18C50 00118C50 AAEE070C */  jal        func_001FBAA8
    /* 18C54 00118C54 05000424 */   addiu     $4, $0, 0x5
    /* 18C58 00118C58 1000BFDF */  ld         $31, 0x10($29)
    /* 18C5C 00118C5C 0000B0DF */  ld         $16, 0x0($29)
    /* 18C60 00118C60 2EEE0708 */  j          func_001FB8B8
    /* 18C64 00118C64 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00118B18
```
