# func_00149D18 — parked

VRAM: 0x00149D18 (file_off 0x049D18)
Asm source: asm/aug6/nonmatchings/fumi/src/act-parallel-control/func_00149D18.s

## Attempt at 2026-06-10

**Reason parked:** rc9: switch(t) on f_184 bits19-21 + flag-check default. ROTATION SOLVED (ret=v0,d=v1 via 'int ret=2'+combined cond 'x<4 && x!=0'); residual=combined gives branchless (x-1)<3 tail vs ROM's split sltiu+movz with x in a0 (dead param). Pure regalloc: x->a0 in split tail. case order 1,2,3 + accumulator was key (43->16->9). Permuter: seed rc9, find split-tail x->a0.

**TU:** `fumi/src/act-parallel-control.c`

**Seed:** `tough_nuts/func_00149D18/func_00149D18.c`

Disassembly:

```
.align 3
nonmatching func_00149D18, 0xC0

glabel func_00149D18
    /* 49D18 00149D18 5C01838C */  lw         $3, 0x15C($4)
    /* 49D1C 00149D1C 90010624 */  addiu      $6, $0, 0x190
    /* 49D20 00149D20 5600053C */  lui        $5, %hi(D_0055DA10)
    /* 49D24 00149D24 6401878C */  lw         $7, 0x164($4)
    /* 49D28 00149D28 9004628C */  lw         $2, 0x490($3)
    /* 49D2C 00149D2C 10DAA524 */  addiu      $5, $5, %lo(D_0055DA10)
    /* 49D30 00149D30 02000424 */  addiu      $4, $0, 0x2
    /* 49D34 00149D34 18104600 */  mult       $2, $2, $6
    /* 49D38 00149D38 21104500 */  addu       $2, $2, $5
    /* 49D3C 00149D3C 8401438C */  lw         $3, 0x184($2)
    /* 49D40 00149D40 C21C0300 */  srl        $3, $3, 19
    /* 49D44 00149D44 07006330 */  andi       $3, $3, 0x7
    /* 49D48 00149D48 0E006410 */  beq        $3, $4, .L00149D84
    /* 49D4C 00149D4C 03006228 */   slti      $2, $3, 0x3
    /* 49D50 00149D50 05004010 */  beqz       $2, .L00149D68
    /* 49D54 00149D54 01000224 */   addiu     $2, $0, 0x1
    /* 49D58 00149D58 08006210 */  beq        $3, $2, .L00149D7C
    /* 49D5C 00149D5C 00000000 */   nop
    /* 49D60 00149D60 0C000010 */  b          .L00149D94
    /* 49D64 00149D64 6804E3DC */   ld        $3, 0x468($7)
.align 2
  .L00149D68:
    /* 49D68 00149D68 03000224 */  addiu      $2, $0, 0x3
    /* 49D6C 00149D6C 07006210 */  beq        $3, $2, .L00149D8C
    /* 49D70 00149D70 00000000 */   nop
    /* 49D74 00149D74 07000010 */  b          .L00149D94
    /* 49D78 00149D78 6804E3DC */   ld        $3, 0x468($7)
.align 2
  .L00149D7C:
    /* 49D7C 00149D7C 0800E003 */  jr         $31
    /* 49D80 00149D80 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L00149D84:
    /* 49D84 00149D84 0800E003 */  jr         $31
    /* 49D88 00149D88 02000224 */   addiu     $2, $0, 0x2
.align 2
  .L00149D8C:
    /* 49D8C 00149D8C 0800E003 */  jr         $31
    /* 49D90 00149D90 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00149D94:
    /* 49D94 00149D94 3E1B0300 */  dsrl32     $3, $3, 12
    /* 49D98 00149D98 01006330 */  andi       $3, $3, 0x1
    /* 49D9C 00149D9C 0C006010 */  beqz       $3, .L00149DD0
    /* 49DA0 00149DA0 2D100000 */   daddu     $2, $0, $0
    /* 49DA4 00149DA4 7804E3DC */  ld         $3, 0x478($7)
    /* 49DA8 00149DA8 3E1B0300 */  dsrl32     $3, $3, 12
    /* 49DAC 00149DAC 01006330 */  andi       $3, $3, 0x1
    /* 49DB0 00149DB0 07006010 */  beqz       $3, .L00149DD0
    /* 49DB4 00149DB4 00000000 */   nop
    /* 49DB8 00149DB8 3000E48C */  lw         $4, 0x30($7)
    /* 49DBC 00149DBC 0400832C */  sltiu      $3, $4, 0x4
    /* 49DC0 00149DC0 03006010 */  beqz       $3, .L00149DD0
    /* 49DC4 00149DC4 00000000 */   nop
    /* 49DC8 00149DC8 02000224 */  addiu      $2, $0, 0x2
    /* 49DCC 00149DCC 0A100400 */  movz       $2, $0, $4
.align 2
  .L00149DD0:
    /* 49DD0 00149DD0 0800E003 */  jr         $31
    /* 49DD4 00149DD4 00000000 */   nop
endlabel func_00149D18
```
