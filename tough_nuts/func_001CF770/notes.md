
---

## Attempt at 2026-05-07

**Reason parked:** scheduling near-miss: ee-gcc places li $v0=1 BEFORE ld $ra; original places it AFTER. Both independent; compiler scheduler decision. Common to many 0x20 wrappers (also AA660, AB190, 144E30 etc)

Seed: `tough_nuts/func_001CF770/0CF770.c`

Disassembly excerpt:

```
glabel func_001CF770
    /* CF770 001CF770 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* CF774 001CF774 0000BFFF */  sd         $ra, 0x0($sp)
    /* CF778 001CF778 263B040C */  jal        func_0010EC98
    /* CF77C 001CF77C 0400848C */   lw        $a0, 0x4($a0)
    /* CF780 001CF780 0000BFDF */  ld         $ra, 0x0($sp)
    /* CF784 001CF784 01000224 */  addiu      $v0, $zero, 0x1
    /* CF788 001CF788 0800E003 */  jr         $ra
    /* CF78C 001CF78C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001CF770
```
