
---

## Attempt at 2026-05-07

**Reason parked:** scheduling near-miss: ee-gcc places 'addiu $a0,+0x10' BEFORE 'addiu $v0,-1'; original places 'addiu $v0,-1' BEFORE 'addiu $a0,+0x10'. Independent ops, scheduler decision

Seed: `tough_nuts/func_001D4E70/0D4E70.c`

Disassembly excerpt:

```
glabel func_001D4E70
    /* D4E70 001D4E70 0800838C */  lw         $v1, 0x8($a0)
    /* D4E74 001D4E74 FFFF0224 */  addiu      $v0, $zero, -0x1
    /* D4E78 001D4E78 10008424 */  addiu      $a0, $a0, 0x10
    /* D4E7C 001D4E7C 2B208300 */  sltu       $a0, $a0, $v1
    /* D4E80 001D4E80 0800E003 */  jr         $ra
    /* D4E84 001D4E84 0B100400 */   movn      $v0, $zero, $a0
endlabel func_001D4E70
```
