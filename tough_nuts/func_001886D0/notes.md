# func_001886D0 — parked

VRAM: 0x001886D0 (file_off 0x0886D0)
Asm source: asm/matchings/camera-ico2/func_001886D0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/camera-ico2.c`

**Seed:** `tough_nuts/func_001886D0/func_001886D0.c`

Disassembly:

```
.align 3
nonmatching func_001886D0, 0x24

glabel func_001886D0
    /* 886D0 001886D0 6D00023C */  lui        $2, %hi(D_006D04B4)
    /* 886D4 001886D4 01000324 */  addiu      $3, $0, 0x1
    /* 886D8 001886D8 FF008430 */  andi       $4, $4, 0xFF
    /* 886DC 001886DC 03008010 */  beqz       $4, .L001886EC
    /* 886E0 001886E0 B40443A0 */   sb        $3, %lo(D_006D04B4)($2)
    /* 886E4 001886E4 F8330608 */  j          func_0018CFE0
    /* 886E8 001886E8 00000000 */   nop
.align 2
  .L001886EC:
    /* 886EC 001886EC 0800E003 */  jr         $31
    /* 886F0 001886F0 00000000 */   nop
endlabel func_001886D0
    /* 886F4 001886F4 00000000 */  nop
```

## 2026-05-31 near-miss (rc3, NOT a floor — stall well under 30)
Clean shape MATCHES structure: `void f(unsigned char a0){ D_006D04B4[0]=1; if(a0) func_0018CFE0(a0); }`
→ correct `j func_0018CFE0` tail-call + andi + beq. ONLY diff: addr/const v0<->v1 swap
(expected addr→v0, const→v1; built reversed). gcc expands store RHS(const) first → const gets v0.
Tried: pointer-var (`char*flag=D;*flag=1`) no change; scalar global -> WORSE (gp_rel collapse, far global needs []).
NEXT levers: make address pseudo created first (compute &D into var used before const exists);
try value-from-reused-reg; try func returning int to free/reserve v0; permuter only after 30-stall.

## 2026-05-31 (turn 2) — 4th hypothesis, swap persists (4/30 stall)
Tried condition-temp + int-return: `int f(unsigned char a0){int t=a0; D_006D04B4[0]=1; if(t)func_0018CFE0(t);}`
→ STILL addr->v1, const->v0 (want addr->v0, const->v1). The j tail-call stays correct throughout.
Root: gcc expands store RHS(const 1) pseudo before LHS(%hi addr) pseudo → const gets lower reg v0.
4 distinct hyps failed (baseline/pointer-var/scalar-worse/cond-temp). NOT a floor (4/30).
NEXT untried: force %hi addr pseudo to be created first (read the global before storing?); store value derived
from a longer-lived expr; or permuter after 30-stall (this is the classic 1-reg store addr/const swap REG() pin solved).

## 2026-05-31 (turn 4) — seed reveals REG("$3") need; decl-order does NOT substitute
The PARKED SEED's matching solution used `register int one REG("$3")=1` to pin the const to $3(=v1),
letting the addr take v0. REG is retired (no-op). Clean decl-order equivalent FAILS:
  `char *p=D; int one=1; int masked=a0&0xFF; *p=(char)one; if(!masked)return; func_0018CFE0(masked);`
→ STILL addr->v1, const->v0 (5th distinct form). gcc allocates const->v0 regardless of decl order /
named-var / pointer-first. This genuinely needs the $3 pin; clean source-shape NOT found in 5 forms.
→ Firing permuter (target: force const into $3). Tree reverted to INCLUDE_ASM.

## Update 2026-05-31 (clean-C resume)
rc3 confirmed: instruction order IDENTICAL to ROM (lui,addiu,andi,beq,sb,j,jr),
ONLY v0/v1 coloring swapped — ROM: addr(lui)->v0, const(1)->v1, `sb v1,0(v0)`;
gcc: addr->v1, const->v0, `sb v0,0(v1)`. Root: gcc expands the store RHS (const 1)
before the LHS address, so the const pseudo is born first -> gets v0. The ROM
compiler created the address pseudo first. 5 clean forms all rc3: array store,
char*p pointer-first, int-param-masked, separate `char v=1`, assignment-in-lvalue
`*(p=D)=1`. This is the v0/v1 birth-order tie-break the removed REG("$3") pinned;
no clean source shape found to make gcc evaluate the address pseudo first. Same
class as [[multireturn_reserves_v0]] but NO return value to leverage. Leave for
offline auto_permute.
