
---

## Attempt at 2026-05-12

**Reason parked:** gcc emits bnel instead of beql; structure differs

Seed: `tough_nuts/func_00154CE8/054CE8.c`

Disassembly excerpt:

```
glabel func_00154CE8
    /* 54CE8 00154CE8 05008050 */  beql       $a0, $zero, .L00154D00
    /* 54CEC 00154CEC 6B00043C */   lui       $a0, %hi(D_006AAAE0)
    /* 54CF0 00154CF0 0800828C */  lw         $v0, 0x8($a0)
    /* 54CF4 00154CF4 6B00043C */  lui        $a0, %hi(D_006AAAE0)
    /* 54CF8 00154CF8 02000010 */  b          .L00154D04
    /* 54CFC 00154CFC E0AA82AC */   sw        $v0, %lo(D_006AAAE0)($a0)
.align 2
  .L00154D00:
    /* 54D00 00154D00 E0AA80AC */  sw         $zero, %lo(D_006AAAE0)($a0)
.align 2
  .L00154D04:
    /* 54D04 00154D04 0400A010 */  beqz       $a1, .L00154D18
    /* 54D08 00154D08 E0AA8224 */   addiu     $v0, $a0, %lo(D_006AAAE0)
    /* 54D0C 00154D0C 0800A38C */  lw         $v1, 0x8($a1)
    /* 54D10 00154D10 0800E003 */  jr         $ra
    /* 54D14 00154D14 040043AC */   sw        $v1, 0x4($v0)
.align 2
  .L00154D18:
    /* 54D18 00154D18 0800E003 */  jr         $ra
    /* 54D1C 00154D1C 040040AC */   sw        $zero, 0x4($v0)
endlabel func_00154CE8
```
