# func_00247A00 — parked

VRAM: 0x00247A00 (file_off 0x147A00)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00247A00.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00247A00/func_00247A00.c`

Disassembly:

```
.align 3
/* Handwritten function */
nonmatching func_00247A00, 0x37C

glabel func_00247A00
    /* 147A00 00247A00 71001A3C */  lui        $26, %hi(D_00710AC0) /* handwritten instruction */
    /* 147A04 00247A04 C00A5A27 */  addiu      $26, $26, %lo(D_00710AC0) /* handwritten instruction */
    /* 147A08 00247A08 1000417F */  sq         $1, 0x10($26) /* handwritten instruction */
    /* 147A0C 00247A0C 2000427F */  sq         $2, 0x20($26) /* handwritten instruction */
    /* 147A10 00247A10 3000437F */  sq         $3, 0x30($26) /* handwritten instruction */
    /* 147A14 00247A14 4000447F */  sq         $4, 0x40($26) /* handwritten instruction */
    /* 147A18 00247A18 5000457F */  sq         $5, 0x50($26) /* handwritten instruction */
    /* 147A1C 00247A1C 6000467F */  sq         $6, 0x60($26) /* handwritten instruction */
    /* 147A20 00247A20 7000477F */  sq         $7, 0x70($26) /* handwritten instruction */
    /* 147A24 00247A24 8000487F */  sq         $8, 0x80($26) /* handwritten instruction */
    /* 147A28 00247A28 9000497F */  sq         $9, 0x90($26) /* handwritten instruction */
    /* 147A2C 00247A2C A0004A7F */  sq         $10, 0xA0($26) /* handwritten instruction */
    /* 147A30 00247A30 B0004B7F */  sq         $11, 0xB0($26) /* handwritten instruction */
    /* 147A34 00247A34 C0004C7F */  sq         $12, 0xC0($26) /* handwritten instruction */
    /* 147A38 00247A38 D0004D7F */  sq         $13, 0xD0($26) /* handwritten instruction */
    /* 147A3C 00247A3C E0004E7F */  sq         $14, 0xE0($26) /* handwritten instruction */
    /* 147A40 00247A40 F0004F7F */  sq         $15, 0xF0($26) /* handwritten instruction */
    /* 147A44 00247A44 0001507F */  sq         $16, 0x100($26) /* handwritten instruction */
    /* 147A48 00247A48 1001517F */  sq         $17, 0x110($26) /* handwritten instruction */
    /* 147A4C 00247A4C 2001527F */  sq         $18, 0x120($26) /* handwritten instruction */
    /* 147A50 00247A50 3001537F */  sq         $19, 0x130($26) /* handwritten instruction */
    /* 147A54 00247A54 4001547F */  sq         $20, 0x140($26) /* handwritten instruction */
    /* 147A58 00247A58 5001557F */  sq         $21, 0x150($26) /* handwritten instruction */
    /* 147A5C 00247A5C 6001567F */  sq         $22, 0x160($26) /* handwritten instruction */
    /* 147A60 00247A60 7001577F */  sq         $23, 0x170($26) /* handwritten instruction */
    /* 147A64 00247A64 8001587F */  sq         $24, 0x180($26) /* handwritten instruction */
    /* 147A68 00247A68 9001597F */  sq         $25, 0x190($26) /* handwritten instruction */
    /* 147A6C 00247A6C C0015C7F */  sq         $28, 0x1C0($26) /* handwritten instruction */
    /* 147A70 00247A70 D0015D7F */  sq         $29, 0x1D0($26) /* handwritten instruction */
    /* 147A74 00247A74 E0015E7F */  sq         $30, 0x1E0($26) /* handwritten instruction */
    /* 147A78 00247A78 F0015F7F */  sq         $31, 0x1F0($26) /* handwritten instruction */
    /* 147A7C 00247A7C 10100000 */  mfhi       $2
    /* 147A80 00247A80 7100013C */  lui        $1, %hi(D_00710CC0)
    /* 147A84 00247A84 C00C22FC */  sd         $2, %lo(D_00710CC0)($1)
    /* 147A88 00247A88 10100070 */  mfhi1      $2
    /* 147A8C 00247A8C 7100013C */  lui        $1, %hi(D_00710CC8)
    /* 147A90 00247A90 C80C22FC */  sd         $2, %lo(D_00710CC8)($1)
    /* 147A94 00247A94 12100000 */  mflo       $2
    /* 147A98 00247A98 7100013C */  lui        $1, %hi(D_00710CD0)
    /* 147A9C 00247A9C D00C22FC */  sd         $2, %lo(D_00710CD0)($1)
    /* 147AA0 00247AA0 12100070 */  mflo1      $2
    /* 147AA4 00247AA4 7100013C */  lui        $1, %hi(D_00710CD8)
    /* 147AA8 00247AA8 D80C22FC */  sd         $2, %lo(D_00710CD8)($1)
    /* 147AAC 00247AAC 28100000 */  mfsa       $2
    /* 147AB0 00247AB0 7100013C */  lui        $1, %hi(D_00710CE0)
    /* 147AB4 00247AB4 E00C22FC */  sd         $2, %lo(D_00710CE0)($1)
    /* 147AB8 00247AB8 00600440 */  mfc0       $4, $12 /* handwritten instruction */
    /* 147ABC 00247ABC 00680540 */  mfc0       $5, $13 /* handwritten instruction */
    /* 147AC0 00247AC0 00700640 */  mfc0       $6, $14 /* handwritten instruction */
    /* 147AC4 00247AC4 00400740 */  mfc0       $7, $8 /* handwritten instruction */
    /* 147AC8 00247AC8 7100083C */  lui        $8, %hi(D_00710AC0)
    /* 147ACC 00247ACC C00A0825 */  addiu      $8, $8, %lo(D_00710AC0)
    /* 147AD0 00247AD0 7100013C */  lui        $1, %hi(D_00710CE8)
    /* 147AD4 00247AD4 E80C26AC */  sw         $6, %lo(D_00710CE8)($1)
    /* 147AD8 00247AD8 2400013C */  lui        $1, %hi(D_00247B00)
    /* 147ADC 00247ADC 007B2124 */  addiu      $1, $1, %lo(D_00247B00)
    /* 147AE0 00247AE0 00708140 */  mtc0       $1, $14 /* handwritten instruction */
    /* 147AE4 00247AE4 0F040000 */  sync.p
    /* 147AE8 00247AE8 00600140 */  mfc0       $1, $12 /* handwritten instruction */
    /* 147AEC 00247AEC FEFF0224 */  addiu      $2, $0, -0x2
    /* 147AF0 00247AF0 24082200 */  and        $1, $1, $2
    /* 147AF4 00247AF4 00608140 */  mtc0       $1, $12 /* handwritten instruction */
    /* 147AF8 00247AF8 0F040000 */  sync.p
    /* 147AFC 00247AFC 18000042 */  eret /* handwritten instruction */
.align 2
  alabel D_00247B00
    /* 147B00 00247B00 5500013C */  lui        $1, %hi(D_0054AB40)
    /* 147B04 00247B04 40AB218C */  lw         $1, %lo(D_0054AB40)($1)
    /* 147B08 00247B08 71001D3C */  lui        $29, %hi(D_00710AC0)
    /* 147B0C 00247B0C 09F82000 */  jalr       $1
    /* 147B10 00247B10 C00ABD27 */   addiu     $29, $29, %lo(D_00710AC0)
    /* 147B14 00247B14 ACFF0324 */  addiu      $3, $0, -0x54
    /* 147B18 00247B18 0C000000 */  syscall    0 /* handwritten instruction */
    /* 147B1C 00247B1C 00000000 */  nop
    /* 147B20 00247B20 00000000 */  nop
    /* 147B24 00247B24 00000000 */  nop
    /* 147B28 00247B28 00000000 */  nop
    /* 147B2C 00247B2C 00000000 */  nop
    /* 147B30 00247B30 00000000 */  nop
    /* 147B34 00247B34 00000000 */  nop
    /* 147B38 00247B38 00000000 */  nop
    /* 147B3C 00247B3C 00000000 */  nop
    /* 147B40 00247B40 00600140 */  mfc0       $1, $12 /* handwritten instruction */
    /* 147B44 00247B44 E4FF1A24 */  addiu      $26, $0, -0x1C /* handwritten instruction */
    /* 147B48 00247B48 24083A00 */  and        $1, $1, $26
    /* 147B4C 00247B4C 00608140 */  mtc0       $1, $12 /* handwritten instruction */
    /* 147B50 00247B50 0F040000 */  sync.p
    /* 147B54 00247B54 7100023C */  lui        $2, %hi(D_00710CE8)
    /* 147B58 00247B58 E80C428C */  lw         $2, %lo(D_00710CE8)($2)
    /* 147B5C 00247B5C 00708240 */  mtc0       $2, $14 /* handwritten instruction */
    /* 147B60 00247B60 0F040000 */  sync.p
    /* 147B64 00247B64 7100023C */  lui        $2, %hi(D_00710CC0)
    /* 147B68 00247B68 C00C42DC */  ld         $2, %lo(D_00710CC0)($2)
    /* 147B6C 00247B6C 11004000 */  mthi       $2
    /* 147B70 00247B70 7100023C */  lui        $2, %hi(D_00710CC8)
    /* 147B74 00247B74 C80C42DC */  ld         $2, %lo(D_00710CC8)($2)
    /* 147B78 00247B78 11004070 */  mthi1      $2
    /* 147B7C 00247B7C 7100023C */  lui        $2, %hi(D_00710CD0)
    /* 147B80 00247B80 D00C42DC */  ld         $2, %lo(D_00710CD0)($2)
    /* 147B84 00247B84 13004000 */  mtlo       $2
    /* 147B88 00247B88 7100023C */  lui        $2, %hi(D_00710CD8)
    /* 147B8C 00247B8C D80C42DC */  ld         $2, %lo(D_00710CD8)($2)
    /* 147B90 00247B90 13004070 */  mtlo1      $2
    /* 147B94 00247B94 7100023C */  lui        $2, %hi(D_00710CE0)
    /* 147B98 00247B98 E00C42DC */  ld         $2, %lo(D_00710CE0)($2)
    /* 147B9C 00247B9C 29004000 */  mtsa       $2
    /* 147BA0 00247BA0 0F040000 */  sync.p
    /* 147BA4 00247BA4 71001A3C */  lui        $26, %hi(D_00710AC0) /* handwritten instruction */
    /* 147BA8 00247BA8 C00A5A27 */  addiu      $26, $26, %lo(D_00710AC0) /* handwritten instruction */
    /* 147BAC 00247BAC 1000417B */  lq         $1, 0x10($26) /* handwritten instruction */
    /* 147BB0 00247BB0 2000427B */  lq         $2, 0x20($26) /* handwritten instruction */
    /* 147BB4 00247BB4 3000437B */  lq         $3, 0x30($26) /* handwritten instruction */
    /* 147BB8 00247BB8 4000447B */  lq         $4, 0x40($26) /* handwritten instruction */
    /* 147BBC 00247BBC 5000457B */  lq         $5, 0x50($26) /* handwritten instruction */
    /* 147BC0 00247BC0 6000467B */  lq         $6, 0x60($26) /* handwritten instruction */
    /* 147BC4 00247BC4 7000477B */  lq         $7, 0x70($26) /* handwritten instruction */
    /* 147BC8 00247BC8 8000487B */  lq         $8, 0x80($26) /* handwritten instruction */
    /* 147BCC 00247BCC 9000497B */  lq         $9, 0x90($26) /* handwritten instruction */
    /* 147BD0 00247BD0 A0004A7B */  lq         $10, 0xA0($26) /* handwritten instruction */
    /* 147BD4 00247BD4 B0004B7B */  lq         $11, 0xB0($26) /* handwritten instruction */
    /* 147BD8 00247BD8 C0004C7B */  lq         $12, 0xC0($26) /* handwritten instruction */
    /* 147BDC 00247BDC D0004D7B */  lq         $13, 0xD0($26) /* handwritten instruction */
    /* 147BE0 00247BE0 E0004E7B */  lq         $14, 0xE0($26) /* handwritten instruction */
    /* 147BE4 00247BE4 F0004F7B */  lq         $15, 0xF0($26) /* handwritten instruction */
    /* 147BE8 00247BE8 0001507B */  lq         $16, 0x100($26) /* handwritten instruction */
    /* 147BEC 00247BEC 1001517B */  lq         $17, 0x110($26) /* handwritten instruction */
    /* 147BF0 00247BF0 2001527B */  lq         $18, 0x120($26) /* handwritten instruction */
    /* 147BF4 00247BF4 3001537B */  lq         $19, 0x130($26) /* handwritten instruction */
    /* 147BF8 00247BF8 4001547B */  lq         $20, 0x140($26) /* handwritten instruction */
    /* 147BFC 00247BFC 5001557B */  lq         $21, 0x150($26) /* handwritten instruction */
    /* 147C00 00247C00 6001567B */  lq         $22, 0x160($26) /* handwritten instruction */
    /* 147C04 00247C04 7001577B */  lq         $23, 0x170($26) /* handwritten instruction */
    /* 147C08 00247C08 8001587B */  lq         $24, 0x180($26) /* handwritten instruction */
    /* 147C0C 00247C0C 9001597B */  lq         $25, 0x190($26) /* handwritten instruction */
    /* 147C10 00247C10 C0015C7B */  lq         $28, 0x1C0($26) /* handwritten instruction */
    /* 147C14 00247C14 D0015D7B */  lq         $29, 0x1D0($26) /* handwritten instruction */
    /* 147C18 00247C18 E0015E7B */  lq         $30, 0x1E0($26) /* handwritten instruction */
    /* 147C1C 00247C1C F0015F7B */  lq         $31, 0x1F0($26) /* handwritten instruction */
    /* 147C20 00247C20 00601A40 */  mfc0       $26, $12 /* handwritten instruction */
    /* 147C24 00247C24 13005A37 */  ori        $26, $26, 0x13 /* handwritten instruction */
    /* 147C28 00247C28 00609A40 */  mtc0       $26, $12 /* handwritten instruction */
    /* 147C2C 00247C2C 0F040000 */  sync.p
    /* 147C30 00247C30 18000042 */  eret /* handwritten instruction */
    /* 147C34 00247C34 00000000 */  nop
    /* 147C38 00247C38 00000000 */  nop
    /* 147C3C 00247C3C 00000000 */  nop
.align 2
  alabel D_00247C40
    /* 147C40 00247C40 71001A3C */  lui        $26, %hi(D_00710AC0) /* handwritten instruction */
    /* 147C44 00247C44 C00A5A27 */  addiu      $26, $26, %lo(D_00710AC0) /* handwritten instruction */
    /* 147C48 00247C48 1000417F */  sq         $1, 0x10($26) /* handwritten instruction */
    /* 147C4C 00247C4C 2000427F */  sq         $2, 0x20($26) /* handwritten instruction */
    /* 147C50 00247C50 3000437F */  sq         $3, 0x30($26) /* handwritten instruction */
    /* 147C54 00247C54 4000447F */  sq         $4, 0x40($26) /* handwritten instruction */
    /* 147C58 00247C58 5000457F */  sq         $5, 0x50($26) /* handwritten instruction */
    /* 147C5C 00247C5C 6000467F */  sq         $6, 0x60($26) /* handwritten instruction */
    /* 147C60 00247C60 7000477F */  sq         $7, 0x70($26) /* handwritten instruction */
    /* 147C64 00247C64 8000487F */  sq         $8, 0x80($26) /* handwritten instruction */
    /* 147C68 00247C68 9000497F */  sq         $9, 0x90($26) /* handwritten instruction */
    /* 147C6C 00247C6C A0004A7F */  sq         $10, 0xA0($26) /* handwritten instruction */
    /* 147C70 00247C70 B0004B7F */  sq         $11, 0xB0($26) /* handwritten instruction */
    /* 147C74 00247C74 C0004C7F */  sq         $12, 0xC0($26) /* handwritten instruction */
    /* 147C78 00247C78 D0004D7F */  sq         $13, 0xD0($26) /* handwritten instruction */
    /* 147C7C 00247C7C E0004E7F */  sq         $14, 0xE0($26) /* handwritten instruction */
    /* 147C80 00247C80 F0004F7F */  sq         $15, 0xF0($26) /* handwritten instruction */
    /* 147C84 00247C84 0001507F */  sq         $16, 0x100($26) /* handwritten instruction */
    /* 147C88 00247C88 1001517F */  sq         $17, 0x110($26) /* handwritten instruction */
    /* 147C8C 00247C8C 2001527F */  sq         $18, 0x120($26) /* handwritten instruction */
    /* 147C90 00247C90 3001537F */  sq         $19, 0x130($26) /* handwritten instruction */
    /* 147C94 00247C94 4001547F */  sq         $20, 0x140($26) /* handwritten instruction */
    /* 147C98 00247C98 5001557F */  sq         $21, 0x150($26) /* handwritten instruction */
    /* 147C9C 00247C9C 6001567F */  sq         $22, 0x160($26) /* handwritten instruction */
    /* 147CA0 00247CA0 7001577F */  sq         $23, 0x170($26) /* handwritten instruction */
    /* 147CA4 00247CA4 8001587F */  sq         $24, 0x180($26) /* handwritten instruction */
    /* 147CA8 00247CA8 9001597F */  sq         $25, 0x190($26) /* handwritten instruction */
    /* 147CAC 00247CAC C0015C7F */  sq         $28, 0x1C0($26) /* handwritten instruction */
    /* 147CB0 00247CB0 D0015D7F */  sq         $29, 0x1D0($26) /* handwritten instruction */
    /* 147CB4 00247CB4 E0015E7F */  sq         $30, 0x1E0($26) /* handwritten instruction */
    /* 147CB8 00247CB8 F0015F7F */  sq         $31, 0x1F0($26) /* handwritten instruction */
    /* 147CBC 00247CBC 10100000 */  mfhi       $2
    /* 147CC0 00247CC0 7100013C */  lui        $1, %hi(D_00710CC0)
    /* 147CC4 00247CC4 C00C22FC */  sd         $2, %lo(D_00710CC0)($1)
    /* 147CC8 00247CC8 10100070 */  mfhi1      $2
    /* 147CCC 00247CCC 7100013C */  lui        $1, %hi(D_00710CC8)
    /* 147CD0 00247CD0 C80C22FC */  sd         $2, %lo(D_00710CC8)($1)
    /* 147CD4 00247CD4 12100000 */  mflo       $2
    /* 147CD8 00247CD8 7100013C */  lui        $1, %hi(D_00710CD0)
    /* 147CDC 00247CDC D00C22FC */  sd         $2, %lo(D_00710CD0)($1)
    /* 147CE0 00247CE0 12100070 */  mflo1      $2
    /* 147CE4 00247CE4 7100013C */  lui        $1, %hi(D_00710CD8)
    /* 147CE8 00247CE8 D80C22FC */  sd         $2, %lo(D_00710CD8)($1)
    /* 147CEC 00247CEC 28100000 */  mfsa       $2
    /* 147CF0 00247CF0 7100013C */  lui        $1, %hi(D_00710CE0)
    /* 147CF4 00247CF4 E00C22FC */  sd         $2, %lo(D_00710CE0)($1)
    /* 147CF8 00247CF8 00600440 */  mfc0       $4, $12 /* handwritten instruction */
    /* 147CFC 00247CFC 00680540 */  mfc0       $5, $13 /* handwritten instruction */
    /* 147D00 00247D00 00700640 */  mfc0       $6, $14 /* handwritten instruction */
    /* 147D04 00247D04 00400740 */  mfc0       $7, $8 /* handwritten instruction */
    /* 147D08 00247D08 00B80840 */  mfc0       $8, $23 /* handwritten instruction */
    /* 147D0C 00247D0C 7100093C */  lui        $9, %hi(D_00710AC0)
    /* 147D10 00247D10 C00A2925 */  addiu      $9, $9, %lo(D_00710AC0)
    /* 147D14 00247D14 2400013C */  lui        $1, %hi(D_00247D3C)
    /* 147D18 00247D18 3C7D2124 */  addiu      $1, $1, %lo(D_00247D3C)
    /* 147D1C 00247D1C 00708140 */  mtc0       $1, $14 /* handwritten instruction */
    /* 147D20 00247D20 0F040000 */  sync.p
    /* 147D24 00247D24 00600140 */  mfc0       $1, $12 /* handwritten instruction */
    /* 147D28 00247D28 FEFF0224 */  addiu      $2, $0, -0x2
    /* 147D2C 00247D2C 24082200 */  and        $1, $1, $2
    /* 147D30 00247D30 00608140 */  mtc0       $1, $12 /* handwritten instruction */
    /* 147D34 00247D34 0F040000 */  sync.p
    /* 147D38 00247D38 18000042 */  eret /* handwritten instruction */
.align 2
  alabel D_00247D3C
    /* 147D3C 00247D3C 7C00A230 */  andi       $2, $5, 0x7C
    /* 147D40 00247D40 5500013C */  lui        $1, %hi(D_0054AB48)
    /* 147D44 00247D44 21082200 */  addu       $1, $1, $2
    /* 147D48 00247D48 48AB218C */  lw         $1, %lo(D_0054AB48)($1)
    /* 147D4C 00247D4C 71001D3C */  lui        $29, %hi(D_00710AC0)
    /* 147D50 00247D50 09F82000 */  jalr       $1
    /* 147D54 00247D54 C00ABD27 */   addiu     $29, $29, %lo(D_00710AC0)
    /* 147D58 00247D58 CDFFFF03 */  break      1023, 1023
    /* 147D5C 00247D5C 00000000 */  nop
.align 2
  alabel D_00247D60
    /* 147D60 00247D60 1000828C */  lw         $2, 0x10($4)
    /* 147D64 00247D64 1C00A68C */  lw         $6, 0x1C($5)
    /* 147D68 00247D68 1400838C */  lw         $3, 0x14($4)
    /* 147D6C 00247D6C 80100200 */  sll        $2, $2, 2
    /* 147D70 00247D70 21104600 */  addu       $2, $2, $6
    /* 147D74 00247D74 0800E003 */  jr         $31
    /* 147D78 00247D78 000043AC */   sw        $3, 0x0($2)
endlabel func_00247A00
    /* 147D7C 00247D7C 00000000 */  nop
```
