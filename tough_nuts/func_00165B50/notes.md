
---

## Attempt at 2026-05-09

**Reason parked:** byte-diffs:31

Seed: `tough_nuts/func_00165B50/065B50.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00165B50; check asm/matchings/cod/065B50/)
```

---

## Attempt at 2026-05-12

**Reason parked:** two-store w/ reload: shape matches, reg alloc differs (target reloads to v0, builds to a0); val in a0 vs a2

Seed: `tough_nuts/func_00165B50/065B50.c.new`

Disassembly excerpt:

```
glabel func_00165B50
    /* 65B50 00165B50 6401828C */  lw         $v0, 0x164($a0)
    /* 65B54 00165B54 7006438C */  lw         $v1, 0x670($v0)
    /* 65B58 00165B58 0400C010 */  beqz       $a2, .L00165B6C
    /* 65B5C 00165B5C 000265AC */   sw        $a1, 0x200($v1)
    /* 65B60 00165B60 6401828C */  lw         $v0, 0x164($a0)
    /* 65B64 00165B64 03000010 */  b          .L00165B74
    /* 65B68 00165B68 0000C48C */   lw        $a0, 0x0($a2)
.align 2
  .L00165B6C:
    /* 65B6C 00165B6C 6401828C */  lw         $v0, 0x164($a0)
    /* 65B70 00165B70 A09A848F */  lw         $a0, %gp_rel(D_00632390)($gp)
.align 2
  .L00165B74:
    /* 65B74 00165B74 7006438C */  lw         $v1, 0x670($v0)
    /* 65B78 00165B78 0800E003 */  jr         $ra
    /* 65B7C 00165B7C 0C0264AC */   sw        $a0, 0x20C($v1)
endlabel func_00165B50
```
