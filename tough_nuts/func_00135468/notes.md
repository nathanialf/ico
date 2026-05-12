
---

## Attempt at 2026-05-12

**Reason parked:** init loop with many stores: gcc emits extra sw, ordering differs

Seed: `tough_nuts/func_00135468/035468.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00135468; check asm/matchings/cod/035468/)
```

---

## Attempt at 2026-05-12

**Reason parked:** 12 zero stores: ee-gcc moves sw 0x84 from late to right after addu a0; target keeps it just before j

Seed: `tough_nuts/func_00135468/035468.c.new`

Disassembly excerpt:

```
glabel func_00135468
    /* 35468 00135468 0100023C */  lui        $v0, (0x18000 >> 16)
    /* 3546C 0013546C 0100033C */  lui        $v1, (0x18098 >> 16)
    /* 35470 00135470 00804234 */  ori        $v0, $v0, (0x18000 & 0xFFFF)
    /* 35474 00135474 FFFF0524 */  addiu      $a1, $zero, -0x1
    /* 35478 00135478 21108200 */  addu       $v0, $a0, $v0
    /* 3547C 0013547C 98806334 */  ori        $v1, $v1, (0x18098 & 0xFFFF)
    /* 35480 00135480 780045AC */  sw         $a1, 0x78($v0)
    /* 35484 00135484 21208300 */  addu       $a0, $a0, $v1
    /* 35488 00135488 880040AC */  sw         $zero, 0x88($v0)
    /* 3548C 0013548C 480040AC */  sw         $zero, 0x48($v0)
    /* 35490 00135490 680040FC */  sd         $zero, 0x68($v0)
    /* 35494 00135494 700040FC */  sd         $zero, 0x70($v0)
    /* 35498 00135498 500040AC */  sw         $zero, 0x50($v0)
    /* 3549C 0013549C 4C0040AC */  sw         $zero, 0x4C($v0)
    /* 354A0 001354A0 540040AC */  sw         $zero, 0x54($v0)
    /* 354A4 001354A4 580040AC */  sw         $zero, 0x58($v0)
    /* 354A8 001354A8 7C0040AC */  sw         $zero, 0x7C($v0)
    /* 354AC 001354AC 840040AC */  sw         $zero, 0x84($v0)
    /* 354B0 001354B0 22D80408 */  j          func_00136088
    /* 354B4 001354B4 800040AC */   sw        $zero, 0x80($v0)
endlabel func_00135468
```
