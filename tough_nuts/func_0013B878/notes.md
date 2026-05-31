# func_0013B878 (ios/pad.c)

**Status:** 1-instruction near-miss — permuter candidate.

The C body is functionally complete and produces a byte-identical match
**except** the prologue emission order of two independent instructions:

```
expected:                 built:
sd  s1,16(sp)             sd  s1,16(sp)
daddu a1,zero,zero        sd  s0,0(sp)
sd  s0,0(sp)              daddu a1,zero,zero
```

`daddu a1,zero,zero` is func_002641D8's 2nd arg (`0`); gcc schedules it
*after* the `sd s0` callee-save instead of *between* the two saves.

Tried (no effect): `-fno-schedule-insns`, `-fno-schedule-insns2`,
`-fno-delayed-branch`, `-fno-peephole`, `do/while(0)` wrap of the call,
pinning `a1` to `$5` + `KEEP_LIVE` (made it worse — loaded a1 from gp).
The `$3` (v1) pin + `KEEP_LIVE` on the D_002811C0 base, and splitting the
`+0x1B8` off the symbol address (eager materialize), are both load-bearing
and correct.

This is a pure instruction-emission-order swap — exactly what the permuter
closes. Seed above is the best human attempt.

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013B878/func_0013B878.1.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632194, 1

.align 3
nonmatching func_0013B878, 0x78

glabel func_0013B878
    /* 3B878 0013B878 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 3B87C 0013B87C 6A00043C */  lui        $4, %hi(D_006A6DB0)
    /* 3B880 0013B880 1000B1FF */  sd         $17, 0x10($29)
    /* 3B884 0013B884 2D280000 */  daddu      $5, $0, $0
    /* 3B888 0013B888 0000B0FF */  sd         $16, 0x0($29)
    /* 3B88C 0013B88C B06D8424 */  addiu      $4, $4, %lo(D_006A6DB0)
    /* 3B890 0013B890 2000BFFF */  sd         $31, 0x20($29)
    /* 3B894 0013B894 7690090C */  jal        func_002641D8
    /* 3B898 0013B898 80010624 */   addiu     $6, $0, 0x180
    /* 3B89C 0013B89C 92F3040C */  jal        func_0013CE48
    /* 3B8A0 0013B8A0 01001124 */   addiu     $17, $0, 0x1
    /* 3B8A4 0013B8A4 A498858F */  lw         $5, (D_00632194) /* gp_rel: (D_00632194) */
    /* 3B8A8 0013B8A8 C2F3040C */  jal        func_0013CF08
    /* 3B8AC 0013B8AC 2D200000 */   daddu     $4, $0, $0
    /* 3B8B0 0013B8B0 2800033C */  lui        $3, %hi(D_002811C0)
    /* 3B8B4 0013B8B4 C0116324 */  addiu      $3, $3, %lo(D_002811C0)
    /* 3B8B8 0013B8B8 B8017024 */  addiu      $16, $3, 0x1B8
    /* 3B8BC 0013B8BC 00000000 */  nop
.align 2
  .L0013B8C0:
    /* 3B8C0 0013B8C0 2D200002 */  daddu      $4, $16, $0
    /* 3B8C4 0013B8C4 DCF3040C */  jal        func_0013CF70
    /* 3B8C8 0013B8C8 FFFF3126 */   addiu     $17, $17, -0x1
    /* 3B8CC 0013B8CC CEF3040C */  jal        func_0013CF38
    /* 3B8D0 0013B8D0 ECFF0426 */   addiu     $4, $16, -0x14
    /* 3B8D4 0013B8D4 FAFF2106 */  bgez       $17, .L0013B8C0
    /* 3B8D8 0013B8D8 00021026 */   addiu     $16, $16, 0x200
    /* 3B8DC 0013B8DC 2000BFDF */  ld         $31, 0x20($29)
    /* 3B8E0 0013B8E0 1000B1DF */  ld         $17, 0x10($29)
    /* 3B8E4 0013B8E4 0000B0DF */  ld         $16, 0x0($29)
    /* 3B8E8 0013B8E8 0800E003 */  jr         $31
    /* 3B8EC 0013B8EC 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0013B878
```
