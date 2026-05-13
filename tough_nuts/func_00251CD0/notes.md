
---

## Attempt at 2026-05-12

**Reason parked:** indexed slot read-then-write: regalloc differs for slot pointers (v0/v1 vs v0/a1)

Seed: `tough_nuts/func_00251CD0/151CD0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00251CD0; check asm/matchings/cod/151CD0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** target keeps base and base+0xC as separate ptrs both biased by idx*8; built coalesces into single base+idx*8

Seed: `tough_nuts/func_00251CD0/151CD0.c.new`

Disassembly excerpt:

```
glabel func_00251CD0
    /* 151CD0 00251CD0 4000828C */  lw         $v0, 0x40($a0)
    /* 151CD4 00251CD4 C0280500 */  sll        $a1, $a1, 3
    /* 151CD8 00251CD8 0C004324 */  addiu      $v1, $v0, 0xC
    /* 151CDC 00251CDC 21104500 */  addu       $v0, $v0, $a1
    /* 151CE0 00251CE0 21186500 */  addu       $v1, $v1, $a1
    /* 151CE4 00251CE4 100047AC */  sw         $a3, 0x10($v0)
    /* 151CE8 00251CE8 0000628C */  lw         $v0, 0x0($v1)
    /* 151CEC 00251CEC 0800E003 */  jr         $ra
    /* 151CF0 00251CF0 000066AC */   sw        $a2, 0x0($v1)
endlabel func_00251CD0
```

---

## Attempt at 2026-05-12

**Reason parked:** expected has dead lw v0,0(v1) read between stores; built lacks it

Seed: `tough_nuts/func_00251CD0/151CD0.c.new`

Disassembly excerpt:

```
glabel func_00251CD0
    /* 151CD0 00251CD0 4000828C */  lw         $v0, 0x40($a0)
    /* 151CD4 00251CD4 C0280500 */  sll        $a1, $a1, 3
    /* 151CD8 00251CD8 0C004324 */  addiu      $v1, $v0, 0xC
    /* 151CDC 00251CDC 21104500 */  addu       $v0, $v0, $a1
    /* 151CE0 00251CE0 21186500 */  addu       $v1, $v1, $a1
    /* 151CE4 00251CE4 100047AC */  sw         $a3, 0x10($v0)
    /* 151CE8 00251CE8 0000628C */  lw         $v0, 0x0($v1)
    /* 151CEC 00251CEC 0800E003 */  jr         $ra
    /* 151CF0 00251CF0 000066AC */   sw        $a2, 0x0($v1)
endlabel func_00251CD0
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: 1 insn schedule order on sw a3 + reg alloc t0 vs v0

Seed: `tough_nuts/func_00251CD0/151CD0.c.new`

Disassembly excerpt:

```
glabel func_00251CD0
    /* 151CD0 00251CD0 4000828C */  lw         $v0, 0x40($a0)
    /* 151CD4 00251CD4 C0280500 */  sll        $a1, $a1, 3
    /* 151CD8 00251CD8 0C004324 */  addiu      $v1, $v0, 0xC
    /* 151CDC 00251CDC 21104500 */  addu       $v0, $v0, $a1
    /* 151CE0 00251CE0 21186500 */  addu       $v1, $v1, $a1
    /* 151CE4 00251CE4 100047AC */  sw         $a3, 0x10($v0)
    /* 151CE8 00251CE8 0000628C */  lw         $v0, 0x0($v1)
    /* 151CEC 00251CEC 0800E003 */  jr         $ra
    /* 151CF0 00251CF0 000066AC */   sw        $a2, 0x0($v1)
endlabel func_00251CD0
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss retry: gcc CSEs base+idx*8 into single base; expected has 2 separate

Seed: `tough_nuts/func_00251CD0/151CD0.c.new`

Disassembly excerpt:

```
glabel func_00251CD0
    /* 151CD0 00251CD0 4000828C */  lw         $v0, 0x40($a0)
    /* 151CD4 00251CD4 C0280500 */  sll        $a1, $a1, 3
    /* 151CD8 00251CD8 0C004324 */  addiu      $v1, $v0, 0xC
    /* 151CDC 00251CDC 21104500 */  addu       $v0, $v0, $a1
    /* 151CE0 00251CE0 21186500 */  addu       $v1, $v1, $a1
    /* 151CE4 00251CE4 100047AC */  sw         $a3, 0x10($v0)
    /* 151CE8 00251CE8 0000628C */  lw         $v0, 0x0($v1)
    /* 151CEC 00251CEC 0800E003 */  jr         $ra
    /* 151CF0 00251CF0 000066AC */   sw        $a2, 0x0($v1)
endlabel func_00251CD0
```
