
---

## Attempt at 2026-05-12

**Reason parked:** scratchpad-or pattern: dst |= 0x20000000 elided by ee-gcc because QCOPY64_SERIAL macro inline-asm doesn't declare  dependency; would need explicit asm

Seed: `tough_nuts/func_00105F48/005F48.c`

Disassembly excerpt:

```
glabel func_00105F48
    /* 5F48 00105F48 0020073C */  lui        $a3, (0x20000030 >> 16)
    /* 5F4C 00105F4C 25208700 */  or         $a0, $a0, $a3
    /* 5F50 00105F50 0000A678 */  lq         $a2, 0x0($a1)
    /* 5F54 00105F54 0000867C */  sq         $a2, (0x20000000 & 0xFFFF)($a0)
    /* 5F58 00105F58 1000A678 */  lq         $a2, 0x10($a1)
    /* 5F5C 00105F5C 1000867C */  sq         $a2, (0x20000010 & 0xFFFF)($a0)
    /* 5F60 00105F60 2000A678 */  lq         $a2, 0x20($a1)
    /* 5F64 00105F64 2000867C */  sq         $a2, (0x20000020 & 0xFFFF)($a0)
    /* 5F68 00105F68 3000A678 */  lq         $a2, 0x30($a1)
    /* 5F6C 00105F6C 3000867C */  sq         $a2, (0x20000030 & 0xFFFF)($a0)
    /* 5F70 00105F70 0800E003 */  jr         $ra
    /* 5F74 00105F74 00000000 */   nop
endlabel func_00105F48
```
