
---

## Attempt at 2026-05-07

**Reason parked:** scheduling near-miss: ee-gcc emits 'lw $a3,gp_rel' BEFORE 'addiu $sp,-0x10'; original emits stack-alloc first then load. Independent ops, scheduler decision

Seed: `tough_nuts/func_001E8B48/0E8B48.c`

Disassembly excerpt:

```
glabel func_001E8B48
    /* E8B48 001E8B48 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* E8B4C 001E8B4C 3897878F */  lw         $a3, %gp_rel(D_00632028)($gp)
    /* E8B50 001E8B50 0000BFFF */  sd         $ra, 0x0($sp)
    /* E8B54 001E8B54 FEA0070C */  jal        func_001E83F8
    /* E8B58 001E8B58 00000000 */   nop
    /* E8B5C 001E8B5C 0000BFDF */  ld         $ra, 0x0($sp)
    /* E8B60 001E8B60 0800E003 */  jr         $ra
    /* E8B64 001E8B64 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001E8B48
```
