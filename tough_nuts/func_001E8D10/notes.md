# func_001E8D10 — parked

VRAM: 0x001E8D10 (file_off 0x0E8D10)
Asm source: asm/aug6/nonmatchings/sugipon/src/spiderGroupManager/func_001E8D10.s

## Attempt at 2026-06-04

**Reason parked:** rc5 scheduler near-miss (same class as func_0011F1C8): independent 'addiu a2,a2,1' (idx+1 for count store D_0062B8E4) fills the sll->addu address-latency gap, so the count store lands before jr and the array store fills the jr-delay; ROM has it reversed (array store before jr, count store in jr-delay). 4 distinct forms (array/count order, slot-ptr, post-inc) all rc5+. Permuter target.

**TU:** `sugipon/src/spiderGroupManager.c`

**Seed:** `tough_nuts/func_001E8D10/func_001E8D10.c`

Disassembly:

```
.align 3
nonmatching func_001E8D10, 0x28

glabel func_001E8D10
    /* E8D10 001E8D10 F4AC868F */  lw         $6, %gp_rel(D_0062B8E4)($28)
    /* E8D14 001E8D14 7000033C */  lui        $3, %hi(D_00706298)
    /* E8D18 001E8D18 98626324 */  addiu      $3, $3, %lo(D_00706298)
    /* E8D1C 001E8D1C FCAC85AF */  sw         $5, %gp_rel(D_0062B8EC)($28)
    /* E8D20 001E8D20 80100600 */  sll        $2, $6, 2
    /* E8D24 001E8D24 21104300 */  addu       $2, $2, $3
    /* E8D28 001E8D28 0100C624 */  addiu      $6, $6, 0x1
    /* E8D2C 001E8D2C 000044AC */  sw         $4, 0x0($2)
    /* E8D30 001E8D30 0800E003 */  jr         $31
    /* E8D34 001E8D34 F4AC86AF */   sw        $6, %gp_rel(D_0062B8E4)($28)
endlabel func_001E8D10
```
