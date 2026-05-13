
---

## Attempt at 2026-05-13

**Reason parked:** 32-byte copy + float div; ee-as schedules ld+sd pairs differently

Seed: `tough_nuts/func_0018CF80/08CF80.c`

Disassembly excerpt:

```
glabel func_0018CF80
    /* 8CF80 0018CF80 6D00063C */  lui        $a2, %hi(D_006D0680)
    /* 8CF84 0018CF84 40A480C7 */  lwc1       $f0, %gp_rel(D_00632D30)($gp)
    /* 8CF88 0018CF88 20008046 */  cvt.s.w    $f0, $f0
    /* 8CF8C 0018CF8C 8006C2DC */  ld         $v0, %lo(D_006D0680)($a2)
    /* 8CF90 0018CF90 8006C624 */  addiu      $a2, $a2, %lo(D_006D0680)
    /* 8CF94 0018CF94 C842013C */  lui        $at, (0x42C80000 >> 16)
    /* 8CF98 0018CF98 00088144 */  mtc1       $at, $f1
    /* 8CF9C 0018CF9C 000082FC */  sd         $v0, 0x0($a0)
    /* 8CFA0 0018CFA0 00000000 */  nop
    /* 8CFA4 0018CFA4 00000000 */  nop
    /* 8CFA8 0018CFA8 03000146 */  div.s      $f0, $f0, $f1
    /* 8CFAC 0018CFAC 0800C3DC */  ld         $v1, 0x8($a2)
    /* 8CFB0 0018CFB0 080083FC */  sd         $v1, 0x8($a0)
    /* 8CFB4 0018CFB4 1000C2DC */  ld         $v0, 0x10($a2)
    /* 8CFB8 0018CFB8 100082FC */  sd         $v0, 0x10($a0)
    /* 8CFBC 0018CFBC 1800C3DC */  ld         $v1, 0x18($a2)
    /* 8CFC0 0018CFC0 180083FC */  sd         $v1, 0x18($a0)
    /* 8CFC4 0018CFC4 0800E003 */  jr         $ra
    /* 8CFC8 0018CFC8 0000A0E4 */   swc1      $f0, 0x0($a1)
endlabel func_0018CF80
```
