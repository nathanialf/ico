
---

## Attempt at 2026-05-08

**Reason parked:** bound-checked array store: ee-gcc emits unsigned -1 via lui+ori (2 insns) instead of addiu -1 (1 insn); also bnel vs beq direction

Seed: `tough_nuts/func_0013CF08/03CF08.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CF08; check asm/matchings/cod/03CF08/)
```

---

## Attempt at 2026-05-08

**Reason parked:** bounded array store: ee-gcc emits beqz+regular shape; original uses bnel branch-likely

Seed: `tough_nuts/func_0013CF08/03CF08.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CF08; check asm/matchings/cod/03CF08/)
```
