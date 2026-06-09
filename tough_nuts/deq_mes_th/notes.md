# deq_mes_th — parked

VRAM: 0x00139C50 (file_off 0x039C50)
Asm source: asm/aug6/nonmatchings/fumi/ios/message/deq_mes_th.s

## Attempt at 2026-06-09

**Reason parked:** best=2: register-coloring tie. Subu temp (aligned-rem) colors v0; ROM uses dead arg reg $6 with rem in v0 (decoupled). 30 hand hyps: a2-reuse fixes frame, a1-=16 fixes a1 caching, unsigned fixes divu; all assoc/type/decl-order/param-reassign/CFG variants either keep subu->v0 or regress. Two literal ret%a2 (two div-traps, one divu) required.

**TU:** `fumi/ios/message.c`

**Seed:** `tough_nuts/deq_mes_th/deq_mes_th.c`

Disassembly:

```
.align 3
nonmatching deq_mes_th, 0xB4

glabel deq_mes_th
    /* 39C50 00139C50 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 39C54 00139C54 2D488000 */  daddu      $9, $4, $0
    /* 39C58 00139C58 0000B0FF */  sd         $16, 0x0($29)
    /* 39C5C 00139C5C 2D80C000 */  daddu      $16, $6, $0
    /* 39C60 00139C60 2000BFFF */  sd         $31, 0x20($29)
    /* 39C64 00139C64 2D30E000 */  daddu      $6, $7, $0
    /* 39C68 00139C68 1000B1FF */  sd         $17, 0x10($29)
    /* 39C6C 00139C6C 1100022A */  slti       $2, $16, 0x11
    /* 39C70 00139C70 05004010 */  beqz       $2, .L00139C88
    /* 39C74 00139C74 2D380001 */   daddu     $7, $8, $0
    /* 39C78 00139C78 CEE2040C */  jal        iosFree
    /* 39C7C 00139C7C 00000000 */   nop
    /* 39C80 00139C80 1C000010 */  b          .L00139CF4
    /* 39C84 00139C84 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L00139C88:
    /* 39C88 00139C88 0F000426 */  addiu      $4, $16, 0xF
    /* 39C8C 00139C8C FFFF0224 */  addiu      $2, $0, -0x1
    /* 39C90 00139C90 2A104400 */  slt        $2, $2, $4
    /* 39C94 00139C94 1E000326 */  addiu      $3, $16, 0x1E
    /* 39C98 00139C98 0B188200 */  movn       $3, $4, $2
    /* 39C9C 00139C9C F0FFA524 */  addiu      $5, $5, -0x10
    /* 39CA0 00139CA0 03190300 */  sra        $3, $3, 4
    /* 39CA4 00139CA4 2D202001 */  daddu      $4, $9, $0
    /* 39CA8 00139CA8 00810300 */  sll        $16, $3, 4
    /* 39CAC 00139CAC CEE2040C */  jal        iosFree
    /* 39CB0 00139CB0 2128B000 */   addu      $5, $5, $16
    /* 39CB4 00139CB4 2D884000 */  daddu      $17, $2, $0
    /* 39CB8 00139CB8 01000052 */  beql       $16, $0, .L00139CC0
    /* 39CBC 00139CBC CD010000 */   break     0, 7
.align 2
  .L00139CC0:
    /* 39CC0 00139CC0 1B003002 */  divu       $0, $17, $16
    /* 39CC4 00139CC4 10100000 */  mfhi       $2
    /* 39CC8 00139CC8 08004010 */  beqz       $2, .L00139CEC
    /* 39CCC 00139CCC 23300202 */   subu      $6, $16, $2
    /* 39CD0 00139CD0 5500053C */  lui        $5, %hi(D_00551678)
    /* 39CD4 00139CD4 21882602 */  addu       $17, $17, $6
    /* 39CD8 00139CD8 01000052 */  beql       $16, $0, .L00139CE0
    /* 39CDC 00139CDC CD010000 */   break     0, 7
.align 2
  .L00139CE0:
    /* 39CE0 00139CE0 7816A524 */  addiu      $5, $5, %lo(D_00551678)
    /* 39CE4 00139CE4 6284090C */  jal        func_00261188
    /* 39CE8 00139CE8 F0FF2426 */   addiu     $4, $17, -0x10
.align 2
  .L00139CEC:
    /* 39CEC 00139CEC 2D102002 */  daddu      $2, $17, $0
    /* 39CF0 00139CF0 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L00139CF4:
    /* 39CF4 00139CF4 1000B1DF */  ld         $17, 0x10($29)
    /* 39CF8 00139CF8 0000B0DF */  ld         $16, 0x0($29)
    /* 39CFC 00139CFC 0800E003 */  jr         $31
    /* 39D00 00139D00 3000BD27 */   addiu     $29, $29, 0x30
endlabel deq_mes_th
    /* 39D04 00139D04 00000000 */  nop
```
