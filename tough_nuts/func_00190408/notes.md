
---

## Attempt at 2026-05-12

**Reason parked:** reg alloc differs: target reuses v0 for q->ll, builds use a1 for ll; load/store ordering correct but regs swapped

Seed: `tough_nuts/func_00190408/090408.c`

Disassembly excerpt:

```
glabel func_00190408
    /* 90408 00190408 5C01A28C */  lw         $v0, 0x15C($a1)
    /* 9040C 0019040C 0008438C */  lw         $v1, 0x800($v0)
    /* 90410 00190410 AB006268 */  ldl        $v0, 0xAB($v1)
    /* 90414 00190414 A400626C */  ldr        $v0, 0xA4($v1)
    /* 90418 00190418 AC00658C */  lw         $a1, 0xAC($v1)
    /* 9041C 0019041C 070082B0 */  sdl        $v0, 0x7($a0)
    /* 90420 00190420 000082B4 */  sdr        $v0, 0x0($a0)
    /* 90424 00190424 080085AC */  sw         $a1, 0x8($a0)
    /* 90428 00190428 0800E003 */  jr         $ra
    /* 9042C 0019042C 00000000 */   nop
endlabel func_00190408
```

---

## Attempt at 2026-05-12

**Reason parked:** scheduler doesn't interleave int load between unaligned 8B load/store; expected has lw between ldr and sdl, built has lw before sw

Seed: `tough_nuts/func_00190408/090408.c.new`

Disassembly excerpt:

```
glabel func_00190408
    /* 90408 00190408 5C01A28C */  lw         $v0, 0x15C($a1)
    /* 9040C 0019040C 0008438C */  lw         $v1, 0x800($v0)
    /* 90410 00190410 AB006268 */  ldl        $v0, 0xAB($v1)
    /* 90414 00190414 A400626C */  ldr        $v0, 0xA4($v1)
    /* 90418 00190418 AC00658C */  lw         $a1, 0xAC($v1)
    /* 9041C 0019041C 070082B0 */  sdl        $v0, 0x7($a0)
    /* 90420 00190420 000082B4 */  sdr        $v0, 0x0($a0)
    /* 90424 00190424 080085AC */  sw         $a1, 0x8($a0)
    /* 90428 00190428 0800E003 */  jr         $ra
    /* 9042C 0019042C 00000000 */   nop
endlabel func_00190408
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: 1 insn schedule offset on tail int load (between ldl/ldr and sdl/sdr in expected)

Seed: `tough_nuts/func_00190408/090408.c.new`

Disassembly excerpt:

```
glabel func_00190408
    /* 90408 00190408 5C01A28C */  lw         $v0, 0x15C($a1)
    /* 9040C 0019040C 0008438C */  lw         $v1, 0x800($v0)
    /* 90410 00190410 AB006268 */  ldl        $v0, 0xAB($v1)
    /* 90414 00190414 A400626C */  ldr        $v0, 0xA4($v1)
    /* 90418 00190418 AC00658C */  lw         $a1, 0xAC($v1)
    /* 9041C 0019041C 070082B0 */  sdl        $v0, 0x7($a0)
    /* 90420 00190420 000082B4 */  sdr        $v0, 0x0($a0)
    /* 90424 00190424 080085AC */  sw         $a1, 0x8($a0)
    /* 90428 00190428 0800E003 */  jr         $ra
    /* 9042C 0019042C 00000000 */   nop
endlabel func_00190408
```
