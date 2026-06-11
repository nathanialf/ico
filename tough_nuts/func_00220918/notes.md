# func_00220918 — parked

VRAM: 0x00220918 (file_off 0x120918)
Asm source: asm/aug6/nonmatchings/script/src/st08a/func_00220918.s

## Attempt at 2026-06-11

**Reason parked:** rc9: struct s + void*[] D. CORRECT: const placement, v0/v1, store order, reads, frame. RESIDUAL: a2/a3 swap (const->a2 vs a3, deref s->a3 vs a2) coupled with v0/v1 via D_004CCAA0 typing (int[] flips a2/a3 correct but reorders [1] store + swaps v0/v1; void*[] keeps v0/v1+order but swaps a2/a3). Ruled out: 3/4-arg BoxBarSoundOn (copies s), hoisted addr locals (rematerialized), ptr-to-array pseudos (folded). Coupled regalloc/sched tie.

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220918/func_00220918.c`

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
