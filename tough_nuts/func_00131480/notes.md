# func_00131480 — parked (isolated v0↔v1 regalloc swap)

VRAM: 0x00131480  TU: `ios/cdvd.c`
Asm: asm/nonmatchings/ios/cdvd/func_00131480.s

## Status: rc5, diff_sites=1 — one v0↔v1 swap on the capacity check

Algorithm fully recovered and CLEAN (de-crutched, no REG/ANCHOR). The only
diff is a register swap in the `a0[0x138/4] > (D_00633C78 << 11)` capacity
check:

```
expected:                 built:
  lw   v1, D_00633C78        lw   v0, D_00633C78
  lw   v0, 312(s0)  ; limit  lw   v1, 312(s0)  ; limit
  sll  v1, v1, 0xb           sll  v0, v0, 0xb
  sltu v1, v1, v0            sltu v0, v0, v1
  beq  v1, zero, T           beq  v0, zero, T
```

Originally matched ONLY with `register unsigned int limit REG("$2")` (retired).

## Mechanism (precise)

- `limit` is ALWAYS the sltu **rt**; thresh (`D_00633C78<<11`) is ALWAYS **rs**;
  the sltu result reuses **rs**'s register. So limit→$2 requires the thresh
  chain to land in $3.
- gcc sched1 hoists the gp-relative `D_00633C78` load FIRST (it starts the
  longer critical chain load→sll→sltu), and local-alloc gives the first-
  scheduled value $2 → thresh in $2, limit in $3 (built). Expected is reversed:
  limit must load first / out-prioritise thresh for $2.
- Operand order can't help: "limit > thresh" / "thresh < limit" / "thresh >=
  limit" all emit the SAME `sltu(thresh, limit)` (limit = rt).

## 12 hand shapes tried, ALL rc5 (none moved the swap)

swap cmp operands; named thresh after limit; thresh before limit; flatten
block + inline unsigned cmp; pages-local cache; limit-named-first inline
threshold; reuse `limit` var for the func_0024D9E8 result (ranges split, no
coalesce); explicit bool `over` temp; int return type + return-store; comma to
sequence limit's load before D_00633C78 (sched still hoists D_00633C78);
goto-inverted out-of-line body.

## Permuter: USELESS here — scorer MISFIRES

5-min shot ran 52 iters and EXITED on a **spurious score-0** (output is
whitespace-identical to the rc5 seed; true rc still 5). `--stop-on-zero` makes
it quit on the false 0. Do NOT trust its score for this func.

## Next levers (fresh eyes)

- Force limit's load to be scheduled FIRST without adding an instruction (the
  whole game): shorten thresh's chain off the critical path, or give limit a
  non-folding extra use that extends its live range past the D_00633C78 load.
- This is NOT a floor — a shape exists. Deferred at hand-stall ~12 (NOT a
  30-stall) to keep throughput on the rest of ios/cdvd; return with fresh ideas.
