
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_00190440/090440.c`

Disassembly excerpt:

```
glabel func_00190440
    /* 90440 00190440 5C01828C */  lw         $v0, 0x15C($a0)
    /* 90444 00190444 3443013C */  lui        $at, (0x43340000 >> 16)
    /* 90448 00190448 00108144 */  mtc1       $at, $f2
    /* 9044C 0019044C 0008438C */  lw         $v1, 0x800($v0)
    /* 90450 00190450 9C8681C7 */  lwc1       $f1, %gp_rel(D_00630F8C)($gp)
    /* 90454 00190454 700060C4 */  lwc1       $f0, 0x70($v1)
    /* 90458 00190458 02000246 */  mul.s      $f0, $f0, $f2
    /* 9045C 0019045C 00000000 */  nop
    /* 90460 00190460 00000000 */  nop
    /* 90464 00190464 03000146 */  div.s      $f0, $f0, $f1
    /* 90468 00190468 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 9046C 0019046C 0000A1E4 */  swc1       $f1, 0x0($a1)
    /* 90470 00190470 0800E003 */  jr         $ra
    /* 90474 00190474 6C006290 */   lbu       $v0, 0x6C($v1)
endlabel func_00190440
```
