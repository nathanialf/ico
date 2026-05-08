
---

## Attempt at 2026-05-08

**Reason parked:** sw a0 in delay slot vs target sw before jr ra (nop in delay); volatile not enough

Seed: `tough_nuts/func_001A9D90/0A9D90.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001A9D90; check asm/matchings/cod/0A9D90/)
```

---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 fills jr ra delay slot with sw a0,0(v1); original keeps nop in delay slot. Size 0x20 vs expected 0x24

Seed: `tough_nuts/func_001A9D90/0A9D90.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001A9D90; check asm/matchings/cod/0A9D90/)
```
