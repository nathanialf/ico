
---

## Attempt at 2026-05-07

**Reason parked:** bnel form OK; lui+addiu vs daddiu+sll scheduling differs (extra nop in  delay slot vs original addiu in delay slot)

Seed: `tough_nuts/func_001F4C00/0F4C00.c`

Disassembly excerpt:

```
glabel func_001F4C00
    /* F4C00 001F4C00 01008054 */  bnel       $a0, $zero, .L001F4C08
    /* F4C04 001F4C04 000080AC */   sw        $zero, 0x0($a0)
.align 2
  .L001F4C08:
    /* F4C08 001F4C08 2700023C */  lui        $v0, %hi(D_00275850)
    /* F4C0C 001F4C0C 0800E003 */  jr         $ra
    /* F4C10 001F4C10 50584224 */   addiu     $v0, $v0, %lo(D_00275850)
endlabel func_001F4C00
```
