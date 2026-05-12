
---

## Attempt at 2026-05-12

**Reason parked:** init+clear loop: final 4 stores reordered by gcc (1C/24/8/14 vs 8/24/14/1C)

Seed: `tough_nuts/func_00181F58/081F58.c`

Disassembly excerpt:

```
glabel func_00181F58
    /* 81F58 00181F58 2900023C */  lui        $v0, %hi(D_0028A890)
    /* 81F5C 00181F5C 13000424 */  addiu      $a0, $zero, 0x13
    /* 81F60 00181F60 90A84324 */  addiu      $v1, $v0, %lo(D_0028A890)
    /* 81F64 00181F64 90A840AC */  sw         $zero, %lo(D_0028A890)($v0)
    /* 81F68 00181F68 040060AC */  sw         $zero, 0x4($v1)
    /* 81F6C 00181F6C 3C026224 */  addiu      $v0, $v1, 0x23C
    /* 81F70 00181F70 0C0060AC */  sw         $zero, 0xC($v1)
    /* 81F74 00181F74 100060AC */  sw         $zero, 0x10($v1)
.align 2
  .L00181F78:
    /* 81F78 00181F78 000040AC */  sw         $zero, 0x0($v0)
    /* 81F7C 00181F7C FFFF8424 */  addiu      $a0, $a0, -0x1
    /* 81F80 00181F80 E4FF4224 */  addiu      $v0, $v0, -0x1C
    /* 81F84 00181F84 00000000 */  nop
    /* 81F88 00181F88 00000000 */  nop
    /* 81F8C 00181F8C FAFF8104 */  bgez       $a0, .L00181F78
    /* 81F90 00181F90 00000000 */   nop
    /* 81F94 00181F94 FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 81F98 00181F98 080060AC */  sw         $zero, 0x8($v1)
    /* 81F9C 00181F9C 240062A4 */  sh         $v0, 0x24($v1)
    /* 81FA0 00181FA0 140060AC */  sw         $zero, 0x14($v1)
    /* 81FA4 00181FA4 2A460608 */  j          func_001918A8
    /* 81FA8 00181FA8 1C0060A4 */   sh        $zero, 0x1C($v1)
endlabel func_00181F58
```
