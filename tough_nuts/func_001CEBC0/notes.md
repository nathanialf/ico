# func_001CEBC0 — parked

VRAM: 0x001CEBC0 (file offset 0x0CEBC0)
Asm source: asm/cod/0CEBC0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sw before vs in delay slot

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001CEBC0
    /* CEBC0 001CEBC0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* CEBC4 001CEBC4 0000BFFF */  sd         $ra, 0x0($sp)
    /* CEBC8 001CEBC8 5C01828C */  lw         $v0, 0x15C($a0)
    /* CEBCC 001CEBCC 0008468C */  lw         $a2, 0x800($v0)
    /* CEBD0 001CEBD0 4008438C */  lw         $v1, 0x840($v0)
    /* CEBD4 001CEBD4 0000C58C */  lw         $a1, 0x0($a2)
    /* CEBD8 001CEBD8 0400C624 */  addiu      $a2, $a2, 0x4
    /* CEBDC 001CEBDC 6C36070C */  jal        func_001CD9B0
    /* CEBE0 001CEBE0 300060AC */   sw        $zero, 0x30($v1)
    /* CEBE4 001CEBE4 0000BFDF */  ld         $ra, 0x0($sp)
    /* CEBE8 001CEBE8 0800E003 */  jr         $ra
    /* CEBEC 001CEBEC 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001CEBC0
```
