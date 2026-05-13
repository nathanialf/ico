
---

## Attempt at 2026-05-08

**Reason parked:** init self[0..3] from func addrs: ee-gcc 13 insns; original has 14 (trailing nop padding)

Seed: `tough_nuts/func_0013CF38/03CF38.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CF38; check asm/matchings/cod/03CF38/)
```

---

## Attempt at 2026-05-13

**Reason parked:** regalloc: fn allocated to a1 not v1, &D computed early

Seed: `tough_nuts/func_0013CF38/03CF38.c.new`

Disassembly excerpt:

```
glabel func_0013CF38
    /* 3CF38 0013CF38 1400023C */  lui        $v0, %hi(func_0013CD30)
    /* 3CF3C 0013CF3C 1400033C */  lui        $v1, %hi(func_0013CD70)
    /* 3CF40 0013CF40 30CD4224 */  addiu      $v0, $v0, %lo(func_0013CD30)
    /* 3CF44 0013CF44 70CD6324 */  addiu      $v1, $v1, %lo(func_0013CD70)
    /* 3CF48 0013CF48 03004014 */  bnez       $v0, .L0013CF58
    /* 3CF4C 0013CF4C 000080AC */   sw        $zero, 0x0($a0)
    /* 3CF50 0013CF50 1400023C */  lui        $v0, %hi(func_0013D098)
    /* 3CF54 0013CF54 98D04224 */  addiu      $v0, $v0, %lo(func_0013D098)
.align 2
  .L0013CF58:
    /* 3CF58 0013CF58 040082AC */  sw         $v0, 0x4($a0)
    /* 3CF5C 0013CF5C B8988227 */  addiu      $v0, $gp, %gp_rel(D_006321A8)
    /* 3CF60 0013CF60 080083AC */  sw         $v1, 0x8($a0)
    /* 3CF64 0013CF64 0800E003 */  jr         $ra
    /* 3CF68 0013CF68 0C0082AC */   sw        $v0, 0xC($a0)
endlabel func_0013CF38
```
