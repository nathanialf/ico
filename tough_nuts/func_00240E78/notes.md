# sceDmaPutStallAddr — parked

VRAM: 0x00240E78 (file_off 0x140E78)
Asm source: asm/aug6/nonmatchings/common/src/PObj/sceDmaPutStallAddr.s

## Attempt at 2026-06-04

**Reason parked:** rc5 regalloc near-miss: discarded volatile HW-read *(volatile int*)0x1000E060 — gcc loads it into a0 (with a0->a1 copy) and a nop in the beq-delay, but the ROM reads into the address reg (v0) IN the beq-delay slot. Found the 0xFFFFFFFF (lui+ori, not li -1) lever; remaining is the read dest/delay-slot regalloc. 4 forms (discard/ptr-var/void-cast/reassign). Permuter target.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/sceDmaPutStallAddr/sceDmaPutStallAddr.c`

Disassembly:

```
.align 3
nonmatching sceDmaPutStallAddr, 0x28

glabel sceDmaPutStallAddr
    /* 140E78 00240E78 0010023C */  lui        $2, (0x1000E060 >> 16)
    /* 140E7C 00240E7C FFFF033C */  lui        $3, (0xFFFFFFFF >> 16)
    /* 140E80 00240E80 60E04234 */  ori        $2, $2, (0x1000E060 & 0xFFFF)
    /* 140E84 00240E84 FFFF6334 */  ori        $3, $3, (0xFFFFFFFF & 0xFFFF)
    /* 140E88 00240E88 03008310 */  beq        $4, $3, .L00240E98
    /* 140E8C 00240E8C 0000428C */   lw        $2, 0x0($2)
    /* 140E90 00240E90 0110013C */  lui        $1, (0x10010000 >> 16)
    /* 140E94 00240E94 60E024AC */  sw         $4, -0x1FA0($1)
.align 2
  .L00240E98:
    /* 140E98 00240E98 0800E003 */  jr         $31
    /* 140E9C 00240E9C 00000000 */   nop
endlabel sceDmaPutStallAddr
```
