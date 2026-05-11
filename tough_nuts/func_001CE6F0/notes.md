
---

## Attempt at 2026-05-08

**Reason parked:** volatile pointer-pointer forces 4 reloads but regalloc differs (target alternates v1/v0; gcc uses v0/v1/a1/a2)

Seed: `tough_nuts/func_001CE6F0/0CE6F0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001CE6F0; check asm/matchings/cod/0CE6F0/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 4-store + tail-call: ee-gcc saves self via move v0,a0; original uses daddu a1,a0,zero

Seed: `tough_nuts/func_001CE6F0/0CE6F0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001CE6F0; check asm/matchings/cod/0CE6F0/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss: regalloc — built uses v0 as self-copy and v1 throughout; original uses a1 as self-copy with alternating v0/v1 for reloads. Tried regpin REG("$5") — gcc 2.9 ignored.

Seed: `tough_nuts/func_001CE6F0/0CE6F0.c.new`

Disassembly excerpt:

```
glabel func_001CE6F0
    /* CE6F0 001CE6F0 2D288000 */  daddu      $a1, $a0, $zero
    /* CE6F4 001CE6F4 5C01A38C */  lw         $v1, 0x15C($a1)
    /* CE6F8 001CE6F8 B00260AC */  sw         $zero, 0x2B0($v1)
    /* CE6FC 001CE6FC 5C01A28C */  lw         $v0, 0x15C($a1)
    /* CE700 001CE700 100340AC */  sw         $zero, 0x310($v0)
    /* CE704 001CE704 5C01A38C */  lw         $v1, 0x15C($a1)
    /* CE708 001CE708 B80360AC */  sw         $zero, 0x3B8($v1)
    /* CE70C 001CE70C 5C01A28C */  lw         $v0, 0x15C($a1)
    /* CE710 001CE710 F28F0708 */  j          func_001E3FC8
    /* CE714 001CE714 BC0340AC */   sw        $zero, 0x3BC($v0)
endlabel func_001CE6F0
```
