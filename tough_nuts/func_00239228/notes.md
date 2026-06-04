# func_00239228 — parked

VRAM: 0x00239228 (file_off 0x139228)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_audiodec/func_00239228.s

## Attempt at 2026-06-04

**Reason parked:** rc5 scheduler near-miss: FP const -133.0f (lui+mtc1, 2-insn chain) is deprioritized vs the two single-insn %gp_rel lwc1 loads — gcc hoists the loads before the const (ROM has const first), cascading the swc1 store order. Structure/regalloc otherwise matches sendDispEnv idiom. 3 forms (temp/direct/store-order) rc5-8. Permuter target.

**TU:** `ito/mpeg/mv_audiodec.c`

**Seed:** `tough_nuts/func_00239228/func_00239228.c`

Disassembly:

```
.align 3
nonmatching func_00239228, 0x28

glabel func_00239228
    /* 139228 00239228 3400838C */  lw         $3, 0x34($4)
    /* 13922C 0023922C 01000224 */  addiu      $2, $0, 0x1
    /* 139230 00239230 05C3013C */  lui        $1, (0xC3050000 >> 16)
    /* 139234 00239234 00088144 */  mtc1       $1, $f1
    /* 139238 00239238 448F82C7 */  lwc1       $f2, %gp_rel(D_00629B34)($28)
    /* 13923C 0023923C 488F80C7 */  lwc1       $f0, %gp_rel(D_00629B38)($28)
    /* 139240 00239240 000061E4 */  swc1       $f1, 0x0($3)
    /* 139244 00239244 080060E4 */  swc1       $f0, 0x8($3)
    /* 139248 00239248 0800E003 */  jr         $31
    /* 13924C 0023924C 040062E4 */   swc1      $f2, 0x4($3)
endlabel func_00239228
```
