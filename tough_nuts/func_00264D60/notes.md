
---

## Attempt at 2026-05-12

**Reason parked:** LCG random: D_00553244 emitted as gp_rel vs expected absolute lui+lo

Seed: `tough_nuts/func_00264D60/164D60.c`

Disassembly excerpt:

```
glabel func_00264D60
    /* 164D60 00264D60 5500023C */  lui        $v0, %hi(D_00553244)
    /* 164D64 00264D64 C641043C */  lui        $a0, (0x41C64E6D >> 16)
    /* 164D68 00264D68 4432458C */  lw         $a1, %lo(D_00553244)($v0)
    /* 164D6C 00264D6C 6D4E8434 */  ori        $a0, $a0, (0x41C64E6D & 0xFFFF)
    /* 164D70 00264D70 FF7F023C */  lui        $v0, (0x7FFFFFFF >> 16)
    /* 164D74 00264D74 5800A38C */  lw         $v1, 0x58($a1)
    /* 164D78 00264D78 FFFF4234 */  ori        $v0, $v0, (0x7FFFFFFF & 0xFFFF)
    /* 164D7C 00264D7C 18186400 */  mult       $v1, $v1, $a0
    /* 164D80 00264D80 39306324 */  addiu      $v1, $v1, 0x3039
    /* 164D84 00264D84 24106200 */  and        $v0, $v1, $v0
    /* 164D88 00264D88 0800E003 */  jr         $ra
    /* 164D8C 00264D8C 5800A3AC */   sw        $v1, 0x58($a1)
endlabel func_00264D60
```
