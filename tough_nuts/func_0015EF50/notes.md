# func_0015EF50 — parked

VRAM: 0x0015EF50 (file offset 0x05EF50)
Asm source: asm/cod/05EF50.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** lw v0/v1 swap

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0015EF50
    /* 5EF50 0015EF50 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 5EF54 0015EF54 1000BFFF */  sd         $ra, 0x10($sp)
    /* 5EF58 0015EF58 0000B0FF */  sd         $s0, 0x0($sp)
    /* 5EF5C 0015EF5C 6401908C */  lw         $s0, 0x164($a0)
    /* 5EF60 0015EF60 7A8A070C */  jal        func_001E29E8
    /* 5EF64 0015EF64 10060626 */   addiu     $a2, $s0, 0x610
    /* 5EF68 0015EF68 200102AE */  sw         $v0, 0x120($s0)
    /* 5EF6C 0015EF6C 0C00438C */  lw         $v1, 0xC($v0)
    /* 5EF70 0015EF70 1000BFDF */  ld         $ra, 0x10($sp)
    /* 5EF74 0015EF74 0000B0DF */  ld         $s0, 0x0($sp)
    /* 5EF78 0015EF78 2B100300 */  sltu       $v0, $zero, $v1
    /* 5EF7C 0015EF7C 0800E003 */  jr         $ra
    /* 5EF80 0015EF80 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0015EF50
```
