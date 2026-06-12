# func_00251F98 — parked

VRAM: 0x00251F98 (file_off 0x151F98)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00251F98.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00251F98/func_00251F98.c`

Disassembly:

```
.align 3
nonmatching func_00251F98, 0x88

glabel func_00251F98
    /* 151F98 00251F98 2D508000 */  daddu      $10, $4, $0
    /* 151F9C 00251F9C 10000224 */  addiu      $2, $0, 0x10
    /* 151FA0 00251FA0 0000448D */  lw         $4, 0x0($10)
    /* 151FA4 00251FA4 0448A200 */  sllv       $9, $2, $5
    /* 151FA8 00251FA8 43180400 */  sra        $3, $4, 1
    /* 151FAC 00251FAC 0C00C018 */  blez       $6, .L00251FE0
    /* 151FB0 00251FB0 0B206800 */   movn      $4, $3, $8
    /* 151FB4 00251FB4 FFFFC224 */  addiu      $2, $6, -0x1
    /* 151FB8 00251FB8 01008424 */  addiu      $4, $4, 0x1
    /* 151FBC 00251FBC 0410A200 */  sllv       $2, $2, $5
    /* 151FC0 00251FC0 21104700 */  addu       $2, $2, $7
    /* 151FC4 00251FC4 21208200 */  addu       $4, $4, $2
    /* 151FC8 00251FC8 2A188900 */  slt        $3, $4, $9
    /* 151FCC 00251FCC 11006014 */  bnez       $3, .L00252014
    /* 151FD0 00251FD0 40100400 */   sll       $2, $4, 1
    /* 151FD4 00251FD4 40100900 */  sll        $2, $9, 1
    /* 151FD8 00251FD8 0D000010 */  b          .L00252010
    /* 151FDC 00251FDC 23208200 */   subu      $4, $4, $2
.align 2
  .L00251FE0:
    /* 151FE0 00251FE0 0C00C104 */  bgez       $6, .L00252014
    /* 151FE4 00251FE4 40100400 */   sll       $2, $4, 1
    /* 151FE8 00251FE8 27100600 */  nor        $2, $0, $6
    /* 151FEC 00251FEC FFFF8424 */  addiu      $4, $4, -0x1
    /* 151FF0 00251FF0 0410A200 */  sllv       $2, $2, $5
    /* 151FF4 00251FF4 23180900 */  negu       $3, $9
    /* 151FF8 00251FF8 21104700 */  addu       $2, $2, $7
    /* 151FFC 00251FFC 23208200 */  subu       $4, $4, $2
    /* 152000 00252000 2A188300 */  slt        $3, $4, $3
    /* 152004 00252004 02006010 */  beqz       $3, .L00252010
    /* 152008 00252008 40100900 */   sll       $2, $9, 1
    /* 15200C 0025200C 21208200 */  addu       $4, $4, $2
.align 2
  .L00252010:
    /* 152010 00252010 40100400 */  sll        $2, $4, 1
.align 2
  .L00252014:
    /* 152014 00252014 0A108800 */  movz       $2, $4, $8
    /* 152018 00252018 0800E003 */  jr         $31
    /* 15201C 0025201C 000042AD */   sw        $2, 0x0($10)
endlabel func_00251F98
```
