
---

## Attempt at 2026-05-12

**Reason parked:** gcc reuses a1 as loop counter; expected uses v0 separate. just register names differ

Seed: `tough_nuts/func_002445F8/1445F8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_002445F8; check asm/matchings/cod/1445F8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** loop body has 2 internal nops + trailing align nop; gcc scheduler doesn't insert; needs branch alignment flag

Seed: `tough_nuts/func_002445F8/1445F8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_002445F8; check asm/matchings/cod/1445F8/)
```
