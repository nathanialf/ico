
---

## Attempt at 2026-05-11

**Reason parked:** near-miss: float regalloc order f0/f1/f2 differs from original (which uses f1=D_00631884, f2=D_00631888, f0=D_0063188C)

Seed: `tough_nuts/func_0023D0C8/13D0C8.c`

Disassembly excerpt:

```
glabel func_0023D0C8
    /* 13D0C8 0023D0C8 3400838C */  lw         $v1, 0x34($a0)
    /* 13D0CC 0023D0CC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13D0D0 0023D0D0 948F81C7 */  lwc1       $f1, %gp_rel(D_00631884)($gp)
    /* 13D0D4 0023D0D4 988F82C7 */  lwc1       $f2, %gp_rel(D_00631888)($gp)
    /* 13D0D8 0023D0D8 9C8F80C7 */  lwc1       $f0, %gp_rel(D_0063188C)($gp)
    /* 13D0DC 0023D0DC 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13D0E0 0023D0E0 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13D0E4 0023D0E4 0800E003 */  jr         $ra
    /* 13D0E8 0023D0E8 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023D0C8
```

---

## Attempt at 2026-05-13

**Reason parked:** retry: REG pin + fno-sched gave matching loads but stores still v0 not v1 + ret in delay

Seed: `tough_nuts/func_0023D0C8/13D0C8.c.new`

Disassembly excerpt:

```
glabel func_0023D0C8
    /* 13D0C8 0023D0C8 3400838C */  lw         $v1, 0x34($a0)
    /* 13D0CC 0023D0CC 01000224 */  addiu      $v0, $zero, 0x1
    /* 13D0D0 0023D0D0 948F81C7 */  lwc1       $f1, %gp_rel(D_00631884)($gp)
    /* 13D0D4 0023D0D4 988F82C7 */  lwc1       $f2, %gp_rel(D_00631888)($gp)
    /* 13D0D8 0023D0D8 9C8F80C7 */  lwc1       $f0, %gp_rel(D_0063188C)($gp)
    /* 13D0DC 0023D0DC 000061E4 */  swc1       $f1, 0x0($v1)
    /* 13D0E0 0023D0E0 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13D0E4 0023D0E4 0800E003 */  jr         $ra
    /* 13D0E8 0023D0E8 040062E4 */   swc1      $f2, 0x4($v1)
endlabel func_0023D0C8
```
