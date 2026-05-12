
---

## Attempt at 2026-05-08

**Reason parked:** v0/v1 swap and final-sw-as-delay-slot scheduling differs

Seed: `tough_nuts/func_00111918/011918.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00111918; check asm/matchings/cod/011918/)
```

---

## Attempt at 2026-05-08

**Reason parked:** long-long ring buffer: ee-gcc fuses 7 insns; original has 9 (kept dead p++ and earlier head update)

Seed: `tough_nuts/func_00111918/011918.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00111918; check asm/matchings/cod/011918/)
```

---

## Attempt at 2026-05-12

**Reason parked:** ee-gcc optimizes away dead addiu a1,v1,8 + reorders sw to delay; can't reproduce target's redundant instruction

Seed: `tough_nuts/func_00111918/011918.c.new`

Disassembly excerpt:

```
glabel func_00111918
    /* 11918 00111918 4C00023C */  lui        $v0, %hi(D_004C7710)
    /* 1191C 0011191C 10774224 */  addiu      $v0, $v0, %lo(D_004C7710)
    /* 11920 00111920 1000438C */  lw         $v1, 0x10($v0)
    /* 11924 00111924 000065FC */  sd         $a1, 0x0($v1)
    /* 11928 00111928 08006324 */  addiu      $v1, $v1, 0x8
    /* 1192C 0011192C 100043AC */  sw         $v1, 0x10($v0)
    /* 11930 00111930 08006524 */  addiu      $a1, $v1, 0x8
    /* 11934 00111934 000064FC */  sd         $a0, 0x0($v1)
    /* 11938 00111938 0800E003 */  jr         $ra
endlabel func_00111918
```
