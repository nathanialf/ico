# func_002667C8 — parked

VRAM: 0x002667C8 (file_off 0x1667C8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_002667C8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_002667C8/func_002667C8.c`

Disassembly:

```
.align 3
nonmatching func_002667C8, 0x58

glabel func_002667C8
    /* 1667C8 002667C8 2700023C */  lui        $2, %hi(func_002698E8)
    /* 1667CC 002667CC 2700033C */  lui        $3, %hi(func_00269950)
    /* 1667D0 002667D0 2700083C */  lui        $8, %hi(func_002699D0)
    /* 1667D4 002667D4 2700093C */  lui        $9, %hi(func_00269A38)
    /* 1667D8 002667D8 E8984224 */  addiu      $2, $2, %lo(func_002698E8)
    /* 1667DC 002667DC 50996324 */  addiu      $3, $3, %lo(func_00269950)
    /* 1667E0 002667E0 D0990825 */  addiu      $8, $8, %lo(func_002699D0)
    /* 1667E4 002667E4 389A2925 */  addiu      $9, $9, %lo(func_00269A38)
    /* 1667E8 002667E8 540087AC */  sw         $7, 0x54($4)
    /* 1667EC 002667EC 0C0085A4 */  sh         $5, 0xC($4)
    /* 1667F0 002667F0 0E0086A4 */  sh         $6, 0xE($4)
    /* 1667F4 002667F4 200082AC */  sw         $2, 0x20($4)
    /* 1667F8 002667F8 240083AC */  sw         $3, 0x24($4)
    /* 1667FC 002667FC 280088AC */  sw         $8, 0x28($4)
    /* 166800 00266800 2C0089AC */  sw         $9, 0x2C($4)
    /* 166804 00266804 000080AC */  sw         $0, 0x0($4)
    /* 166808 00266808 040080AC */  sw         $0, 0x4($4)
    /* 16680C 0026680C 080080AC */  sw         $0, 0x8($4)
    /* 166810 00266810 100080AC */  sw         $0, 0x10($4)
    /* 166814 00266814 180080AC */  sw         $0, 0x18($4)
    /* 166818 00266818 0800E003 */  jr         $31
    /* 16681C 0026681C 1C0084AC */   sw        $4, 0x1C($4)
endlabel func_002667C8
```
