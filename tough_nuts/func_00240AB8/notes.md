# func_00240AB8 — parked

VRAM: 0x00240AB8 (file_off 0x140AB8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00240AB8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00240AB8/func_00240AB8.c`

Disassembly:

```
.align 3
nonmatching func_00240AB8, 0x5C

glabel func_00240AB8
    /* 140AB8 00240AB8 0010023C */  lui        $2, (0x10003830 >> 16)
    /* 140ABC 00240ABC 0010043C */  lui        $4, (0x10003820 >> 16)
    /* 140AC0 00240AC0 30384234 */  ori        $2, $2, (0x10003830 & 0xFFFF)
    /* 140AC4 00240AC4 20388434 */  ori        $4, $4, (0x10003820 & 0xFFFF)
    /* 140AC8 00240AC8 000040AC */  sw         $0, 0x0($2)
    /* 140ACC 00240ACC 0010033C */  lui        $3, (0x10003810 >> 16)
    /* 140AD0 00240AD0 000080AC */  sw         $0, 0x0($4)
    /* 140AD4 00240AD4 10386334 */  ori        $3, $3, (0x10003810 & 0xFFFF)
    /* 140AD8 00240AD8 01000224 */  addiu      $2, $0, 0x1
    /* 140ADC 00240ADC 000062AC */  sw         $2, 0x0($3)
    /* 140AE0 00240AE0 00E04848 */  cfc2.ni    $8, $vi28
    /* 140AE4 00240AE4 02000835 */  ori        $8, $8, 0x2
    /* 140AE8 00240AE8 00E0C848 */  ctc2.ni    $8, $vi28
    /* 140AEC 00240AEC 0F040000 */  sync.p
    /* 140AF0 00240AF0 5500043C */  lui        $4, %hi(D_0054A9B0)
    /* 140AF4 00240AF4 0010053C */  lui        $5, (0x10004000 >> 16)
    /* 140AF8 00240AF8 B0A98424 */  addiu      $4, $4, %lo(D_0054A9B0)
    /* 140AFC 00240AFC 0040A534 */  ori        $5, $5, (0x10004000 & 0xFFFF)
    /* 140B00 00240B00 00008278 */  lq         $2, 0x0($4)
    /* 140B04 00240B04 0000A27C */  sq         $2, 0x0($5)
    /* 140B08 00240B08 10008378 */  lq         $3, 0x10($4)
    /* 140B0C 00240B0C 0800E003 */  jr         $31
    /* 140B10 00240B10 0000A37C */   sq        $3, 0x0($5)
endlabel func_00240AB8
    /* 140B14 00240B14 00000000 */  nop
```
