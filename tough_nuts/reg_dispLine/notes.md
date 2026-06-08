# reg_dispLine — parked

VRAM: 0x00120298 (file_off 0x020298)
Asm source: asm/aug6/nonmatchings/seki/src/RegistPacket/reg_dispLine.s

## Attempt at 2026-06-08

**Reason parked:** best=rc4 (void-return, TCO j dl_GetPri correct). Residual: dpk_Init(2,D,4) delay-slot tie — ROM defers a0=2 to the jal delay (a1hi,a2,a1lo,[a0]); ee-gcc emits args L-to-R so a1lo (pointer %lo, last-ready via RAW chain) always fills the delay (a1hi,a0,a2,[a1lo]). 30+ distinct forms (return type void/int/long/void*, proto void*/int*/char/short/array/const/register, global ref D/&D[0]/D+1/scalar&/struct, enum/unsigned/comma/bare-call/two-stmt) + flag sweep (O1/O2/no-sched1/no-sched2) ALL rc4. a0=2 is a pure no-WAR constant (func_002590A0 defers const only via $4 WAR from an incoming arg; reg_dispLine is void(void)) so it can never schedule last by source. Permuter-class scheduler tie.

**TU:** `seki/src/RegistPacket.c`

**Seed:** `tough_nuts/reg_dispLine/reg_dispLine.c`

Disassembly:

```
.align 3
nonmatching reg_dispLine, 0x30

glabel reg_dispLine
    /* 20298 00120298 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 2029C 0012029C 0000BFFF */  sd         $31, 0x0($29)
    /* 202A0 001202A0 BAE1070C */  jal        dpk_SwapBuffer
    /* 202A4 001202A4 00000000 */   nop
    /* 202A8 001202A8 5500053C */  lui        $5, %hi(D_0054FBE0)
    /* 202AC 001202AC 04000624 */  addiu      $6, $0, 0x4
    /* 202B0 001202B0 E0FBA524 */  addiu      $5, $5, %lo(D_0054FBE0)
    /* 202B4 001202B4 C4E1070C */  jal        dpk_Init
    /* 202B8 001202B8 02000424 */   addiu     $4, $0, 0x2
    /* 202BC 001202BC 0000BFDF */  ld         $31, 0x0($29)
    /* 202C0 001202C0 48E10708 */  j          dl_GetPri
    /* 202C4 001202C4 1000BD27 */   addiu     $29, $29, 0x10
endlabel reg_dispLine
```

## Permuter harvest 2026-06-08 (this pass)

Fired bounded permuter (8445 iters). Best = `output-20-1` (score 20 = **rc2**,
improving the clean-C rc4): the mutation is an empty `if (D_0054FBE0) {}` BEFORE
the calls, which materializes `%hi(D)` (lui a1) early so `a1lo` no longer falls
into the dpk_Init delay slot. Residual rc2 is then purely the `a0=2`/`a2=4`
transposition: ROM emits `a2=4` into the a1 hi/lo gap and defers `a0=2` to the
delay; ee-gcc 2.9 emits call args LEFT-TO-RIGHT so `a0` (arg0) fills the gap and
`a2` (arg2) is deferred. No clean source reorders two plain immediates across a
fixed-position call. arg0-const-in-delay needs a WAR hazard on $4 (cf.
func_002590A0 `f(0x18,a0,a1,0)` where an incoming param copied to a1 forces the
const write last) — reg_dispLine is `void(void)`, no incoming arg, so no WAR.
The `if(D){}` is a permuter artifact, NOT clean dev C, and still only rc2.
Permuter found NO rc0 (no output-0-*). RESUME idea: find the dev construct that
creates a $4 WAR (an arg/temp using $4 before dpk_Init) — that is the only known
lever that defers a const arg0.

## Pass 2 (2026-06-08): rc4->rc2 adopted, (b) re-confirmed
Fresh levers tried: do{}while(0)/empty-block anchor (no effect on arg-sched),
const-form variants (1<<2, 4>>1, 2+2, type changes — all fold, rc2). Adopted the
if(D){} rc2 form (best now rc2). Permuter seeded WITH the rc2 form (closer start):
~7400 iters, NO rc0. Best harvest = score-15 UB artifact `dpk_Init(nv, D, nv=(nv=4))`
which yields a0=4 (WRONG value) — real_count 2 but semantically broken, does NOT
beat rc2. Genuine floor stays rc2 (a0/a2 left-to-right gap-filler swap). (b).
