
---

## Attempt at 2026-05-12

**Reason parked:** bne vs beql branch-likely; structurally close but loop body emits differently

Seed: `tough_nuts/func_001D4E30/0D4E30.c`

Disassembly excerpt:

```
glabel func_001D4E30
    /* D4E30 001D4E30 5600023C */  lui        $v0, %hi(D_00565060)
    /* D4E34 001D4E34 4C00033C */  lui        $v1, %hi(D_004C49A8)
    /* D4E38 001D4E38 60504224 */  addiu      $v0, $v0, %lo(D_00565060)
    /* D4E3C 001D4E3C A8496324 */  addiu      $v1, $v1, %lo(D_004C49A8)
    /* D4E40 001D4E40 34014624 */  addiu      $a2, $v0, 0x134
    /* D4E44 001D4E44 3D040524 */  addiu      $a1, $zero, 0x43D
.align 2
  .L001D4E48:
    /* D4E48 001D4E48 0000C28C */  lw         $v0, 0x0($a2)
    /* D4E4C 001D4E4C 01004450 */  beql       $v0, $a0, .L001D4E54
    /* D4E50 001D4E50 000060AC */   sw        $zero, 0x0($v1)
.align 2
  .L001D4E54:
    /* D4E54 001D4E54 04006324 */  addiu      $v1, $v1, 0x4
    /* D4E58 001D4E58 FFFFA524 */  addiu      $a1, $a1, -0x1
    /* D4E5C 001D4E5C FAFFA104 */  bgez       $a1, .L001D4E48
    /* D4E60 001D4E60 9001C624 */   addiu     $a2, $a2, 0x190
    /* D4E64 001D4E64 0800E003 */  jr         $ra
    /* D4E68 001D4E68 00000000 */   nop
endlabel func_001D4E30
```
