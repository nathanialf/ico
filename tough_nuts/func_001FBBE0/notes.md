# func_001FBBE0 (cod/0FBBE0)

Part of DmaPacket TU but cannot match alongside func_001FBB48 in
src/DmaPacket.c due to regalloc difference:
- Expected emits `lui $a0,hi; lw $v1,lo($a0); addiu $a1,$a0,lo`
- All naive C forms emit `lui $v1,hi; lw $v0,lo($v1); addiu $a0,$v1,lo`

Tried: register pin REG("$4"), unused int param, -fno-schedule-insns,
intermediate ptr var, struct typedef cast — none shifted gcc 2.9's
first-pick from $v1+$a0 to $a0+$a1 for the address-load pair.

This may need permuter to find a regalloc-shifting C form, or may need
to absorb into DmaPacket.c while accepting the regalloc miss.

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B macros (ADDU_RT,KEEP_LIVE,REG)

Seed: `tough_nuts/func_001FBBE0/0FBBE0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001FBBE0; check asm/matchings/cod/0FBBE0/)
```
