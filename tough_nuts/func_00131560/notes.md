# func_00131560 — parked

VRAM: 0x00131560 (file_off 0x031560)
Asm source: asm/nonmatchings/ios/cdvd/func_00131560.s

## Attempt at 2026-05-31

**Reason parked:** rc1 near-miss: single .p2align-style merge nop before jal func_0024A1E0 (the bnez-target L0013158C). do-while-0 first-store idiom is CORRECT (matches sibling func_001331D8 which uses the identical idiom + return func_0024A1E0 tail). Merge nop appears ONLY because func_0024A1E0 is a REGULAR call at the merge (func_001354B8 is the tail), unlike the sibling's tail-call merge. sched_diff shows prologue correct + NO nop in dbr stream -> nop is post-dbr branch-target alignment. 9 forms tried (temp-var/inline/goto/plain-store/a0-direct/conditional-do-while0/func_0024A1E0-do-while0): do-while0 gives rc1, removing it gives rc2 (prologue daddu). Needs an alignment/demote_p2align lever, not a source shape. stall 8, NOT a floor.

**TU:** `ios/cdvd.c`

**Seed:** `tough_nuts/func_00131560/func_00131560.c`

Disassembly:

```
.align 3
nonmatching func_00131560, 0x48

glabel func_00131560
    /* 31560 00131560 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 31564 00131564 0000B0FF */  sd         $16, 0x0($29)
    /* 31568 00131568 1000BFFF */  sd         $31, 0x10($29)
    /* 3156C 0013156C 2D808000 */  daddu      $16, $4, $0
    /* 31570 00131570 A036090C */  jal        func_0024DA80
    /* 31574 00131574 0C0000AE */   sw        $0, 0xC($16)
    /* 31578 00131578 04004014 */  bnez       $2, .L0013158C
    /* 3157C 0013157C 00000000 */   nop
    /* 31580 00131580 EC35090C */  jal        func_0024D7B0
    /* 31584 00131584 00000000 */   nop
    /* 31588 00131588 0C0002AE */  sw         $2, 0xC($16)
.align 2
  .L0013158C:
    /* 3158C 0013158C 7828090C */  jal        func_0024A1E0
    /* 31590 00131590 6001048E */   lw        $4, 0x160($16)
    /* 31594 00131594 5C01048E */  lw         $4, 0x15C($16)
    /* 31598 00131598 1000BFDF */  ld         $31, 0x10($29)
    /* 3159C 0013159C 0000B0DF */  ld         $16, 0x0($29)
    /* 315A0 001315A0 2ED50408 */  j          func_001354B8
    /* 315A4 001315A4 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00131560
```
