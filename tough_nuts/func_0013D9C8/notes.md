# func_0013D9C8 — parked

VRAM: 0x0013D9C8 (file offset 0x03D9C8)
Asm source: asm/cod/03D944.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sibcall on both branches — TCO defeats fail

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0013D9C8
    /* 3D9C8 0013D9C8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 3D9CC 0013D9CC 05008014 */  bnez       $a0, .L0013D9E4
    /* 3D9D0 0013D9D0 0000BFFF */   sd        $ra, 0x0($sp)
    /* 3D9D4 0013D9D4 0401040C */  jal        func_00100410
    /* 3D9D8 0013D9D8 00000000 */   nop
    /* 3D9DC 0013D9DC 02000010 */  b          .L0013D9E8
    /* 3D9E0 0013D9E0 00000000 */   nop
.align 2
  .L0013D9E4:
    /* 3D9E4 0013D9E4 3000828C */  lw         $v0, 0x30($a0)
.align 2
  .L0013D9E8:
    /* 3D9E8 0013D9E8 1C01040C */  jal        func_00100470
    /* 3D9EC 0013D9EC 2D204000 */   daddu     $a0, $v0, $zero
    /* 3D9F0 0013D9F0 0000BFDF */  ld         $ra, 0x0($sp)
    /* 3D9F4 0013D9F4 0800E003 */  jr         $ra
    /* 3D9F8 0013D9F8 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0013D9C8
```
