# func_00220918 (st08a) + clones func_002209A8, func_00220A38

Sub-actor registration. Shape (int-cast, gp-first = dev's true store order):
    int s = *(int*)(a0 + 0x164);
    int arg = a0;                       // hoist 2nd volatile read early (deref split)
    D_0062A894 = 1;
    *(int*)(s + 0xB4) = (int)D_004CCAA0;
    D_004CCAA0[1] = (int)actSt05eSolar;
    *(int*)(s + 0xB0) = 0;
    BoxBarSoundOn(arg, 0x189);
    _ACTWait(0);

best real_count: gp-first=10 (CORRECT store order, all stores+loads+liveness match;
ONLY the 6 setup insns [2 lui, 2 addiu, addiu a3=1, addiu a1=393] are ordered
differently: expected breadth-first [lui v0,lui v1,addiu v0,addiu v1,a3,a1] vs built
depth-first with addiu a3=1 grabbing slot2). gp-after-B4=6 (lower count but WRONG
store order: gp store lands 3rd). Tried ~16 distinct shapes: arg/base temp positions,
gp-store position (aliasing-coupled to const-1 placement), struct-typed s (12),
data-local (13), B0/D[1] reorders, split decl. The const-1 (D_0062A894=1) materialize
slot is a pure sched2 tie-break unreachable by clean source: gp-first => const early;
gp-after-B4 => const correct but gp store late. PERMUTER-CLASS once 30-stall reached.
Seed permuter with the gp-first (count-10) version (correct store order).

---

## Attempt at 2026-06-13

**Reason parked:** scheduler filler tie best rc6: D_0062A894=1 const-materialize slot vs gp-store-position mutually exclusive in clean source (gp-first=>const@slot2; gp-late=>store floats). ~30 distinct hand shapes. seed=int-cast arg-temp, all stores/loads/liveness match, only 6 setup insns mis-ordered. clones: func_002209A8, func_00220A38

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220918/func_00220918.1.c`

Disassembly:

```
.align 3
nonmatching func_00220918, 0x58

glabel func_00220918
    /* 120918 00220918 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 12091C 0022091C 4D00023C */  lui        $2, %hi(D_004CCAA0)
    /* 120920 00220920 0000A4AF */  sw         $4, 0x0($29)
    /* 120924 00220924 2200033C */  lui        $3, %hi(actSt05eSolar)
    /* 120928 00220928 1000BFFF */  sd         $31, 0x10($29)
    /* 12092C 0022092C A0CA4224 */  addiu      $2, $2, %lo(D_004CCAA0)
    /* 120930 00220930 0000A58F */  lw         $5, 0x0($29)
    /* 120934 00220934 B0CD6324 */  addiu      $3, $3, %lo(actSt05eSolar)
    /* 120938 00220938 0000A48F */  lw         $4, 0x0($29)
    /* 12093C 0022093C 01000724 */  addiu      $7, $0, 0x1
    /* 120940 00220940 6401A68C */  lw         $6, 0x164($5)
    /* 120944 00220944 89010524 */  addiu      $5, $0, 0x189
    /* 120948 00220948 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 12094C 0022094C B400C2AC */  sw         $2, 0xB4($6)
    /* 120950 00220950 040043AC */  sw         $3, 0x4($2)
    /* 120954 00220954 F867050C */  jal        BoxBarSoundOn
    /* 120958 00220958 B000C0AC */   sw        $0, 0xB0($6)
    /* 12095C 0022095C 6004080C */  jal        _ACTWait
    /* 120960 00220960 2D200000 */   daddu     $4, $0, $0
    /* 120964 00220964 1000BFDF */  ld         $31, 0x10($29)
    /* 120968 00220968 0800E003 */  jr         $31
    /* 12096C 0022096C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00220918
```
