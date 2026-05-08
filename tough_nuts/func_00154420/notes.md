
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc emits two jr ra (size 0x28) but expected single merged jr ra (size 0x24)

Seed: `tough_nuts/func_00154420/054420.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00154420; check asm/matchings/cod/054420/)
```

---

## Attempt at 2026-05-08

**Reason parked:** early-exit chain: ee-gcc converts to movn idiom; original uses beqz+single jr ra fall-through

Seed: `tough_nuts/func_00154420/054420.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00154420; check asm/matchings/cod/054420/)
```
