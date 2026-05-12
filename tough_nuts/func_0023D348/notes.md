
---

## Attempt at 2026-05-11

**Reason parked:** near-miss: float regalloc order differs; expected D_006318A4 in f2 and D_006318A8 in f0, built reverses

Seed: `tough_nuts/func_0023D348/13D348.c`

Disassembly excerpt:

```
glabel func_0023D348
    /* 13D348 0023D348 3400838C */  lw         $v1, 0x34($a0)
    /* 13D34C 0023D34C 01000224 */  addiu      $v0, $zero, 0x1
    /* 13D350 0023D350 B48F82C7 */  lwc1       $f2, %gp_rel(D_006318A4)($gp)
    /* 13D354 0023D354 B88F80C7 */  lwc1       $f0, %gp_rel(D_006318A8)($gp)
    /* 13D358 0023D358 003F013C */  lui        $at, (0x3F000000 >> 16)
    /* 13D35C 0023D35C 00088144 */  mtc1       $at, $f1
    /* 13D360 0023D360 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13D364 0023D364 000062E4 */  swc1       $f2, 0x0($v1)
    /* 13D368 0023D368 0800E003 */  jr         $ra
    /* 13D36C 0023D36C 1C0081E4 */   swc1      $f1, 0x1C($a0)
endlabel func_0023D348
```

---

## Attempt at 2026-05-12

**Reason parked:** swc1 order: built emits v[0] before v[2]; expected v[2] before v[0]; also float regs swapped

Seed: `tough_nuts/func_0023D348/13D348.c.new`

Disassembly excerpt:

```
glabel func_0023D348
    /* 13D348 0023D348 3400838C */  lw         $v1, 0x34($a0)
    /* 13D34C 0023D34C 01000224 */  addiu      $v0, $zero, 0x1
    /* 13D350 0023D350 B48F82C7 */  lwc1       $f2, %gp_rel(D_006318A4)($gp)
    /* 13D354 0023D354 B88F80C7 */  lwc1       $f0, %gp_rel(D_006318A8)($gp)
    /* 13D358 0023D358 003F013C */  lui        $at, (0x3F000000 >> 16)
    /* 13D35C 0023D35C 00088144 */  mtc1       $at, $f1
    /* 13D360 0023D360 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13D364 0023D364 000062E4 */  swc1       $f2, 0x0($v1)
    /* 13D368 0023D368 0800E003 */  jr         $ra
    /* 13D36C 0023D36C 1C0081E4 */   swc1      $f1, 0x1C($a0)
endlabel func_0023D348
```
