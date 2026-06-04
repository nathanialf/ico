# GetRealModelId — parked

VRAM: 0x001B4778 (file_off 0x0B4778)
Asm source: asm/aug6/nonmatchings/common/src/sceneManager/GetRealModelId.s

## Attempt at 2026-06-04

**Reason parked:** rc3 floor (compound-update lever): RealModel *m=D_002E34F0; m+=a0; return m->f_68=(m->f_68&~1)|(a1&1). The compound m+=a0 FIXED the stride/base v0/v1 swap (rc7->rc3). RESIDUAL=1-register tie-break: addu dest is base-reg v1 (mine) vs index-reg a0 (ROM). base->v1 REQUIRES the read-write compound (forces element=v1); element->a0 REQUIRES non-compound/index (forces base=v0 swap, rc7) -- mutually exclusive by hand (~65 shapes, 4 fires). Permuter-class (cf func_001FB768 v0->a1 copy). next-verdict park 30/30 for offline auto_permute.

**TU:** `common/src/sceneManager.c`

**Seed:** `tough_nuts/GetRealModelId/GetRealModelId.c`

Disassembly:

```
.align 3
nonmatching GetRealModelId, 0x30

glabel GetRealModelId
    /* B4778 001B4778 6C000224 */  addiu      $2, $0, 0x6C
    /* B477C 001B477C 2E00033C */  lui        $3, %hi(D_002E34F0)
    /* B4780 001B4780 18208200 */  mult       $4, $4, $2
    /* B4784 001B4784 F0346324 */  addiu      $3, $3, %lo(D_002E34F0)
    /* B4788 001B4788 FEFF0624 */  addiu      $6, $0, -0x2
    /* B478C 001B478C 0100A530 */  andi       $5, $5, 0x1
    /* B4790 001B4790 21208300 */  addu       $4, $4, $3
    /* B4794 001B4794 6800828C */  lw         $2, 0x68($4)
    /* B4798 001B4798 24104600 */  and        $2, $2, $6
    /* B479C 001B479C 25104500 */  or         $2, $2, $5
    /* B47A0 001B47A0 0800E003 */  jr         $31
    /* B47A4 001B47A4 680082AC */   sw        $2, 0x68($4)
endlabel GetRealModelId
```
