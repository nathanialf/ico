# func_0014B000 (act-parallel-control) — near-miss rc1, swap_addu (commutative operand order)

WORKING C (everything EXACT except 1 addu operand order):
  struct E36ap { char pad[0x1C]; int f1C; char pad2[4]; };  // stride 0x24
  int func_0014B000(int a0) {
      int ret;
      if (a0 != 0) {
          struct E36ap *base = (struct E36ap *)D_006124F8;  // base in s0 BEFORE call (kept across)
          base += func_001F40C8(a0);
          ret = base->f1C;
      } else { ret = 0; }
      return ret;
  }
→ base kept in $s0 across the call (if/else gives beq+body-inline+b-to-end), lw v0,28(s0) EXACT.
ONLY diff: `addu s0,v0,s0` (built, rd==rt) vs `addu s0,s0,v0` (expected, rd==rs). swap_addu.
The usual fix "declare prod-mult BEFORE base ptr" is BLOCKED: the func_001F40C8 call sits between
base-materialization and the add, so base must precede the call (for s0) — can't put prod first.
ADDU_RS macro retired. Tried: base[idx], base+=idx, char* byte off — all give rd==rt.
NEXT: permuter, or a source form that makes base the rs of the commutative add despite call-ordering.

## 2026-05-31 (unsupervised) — rc1 swap_addu floor, clean seed (no MATERIALIZE)
Confirmed rc1 = the single commutative `addu` operand order: gcc `addu s0,v0,s0`
(rd==rt, prod=v0 lower-regno canonicalized as rs); ROM `addu s0,s0,v0` (rd==rs,
base first). base must be callee-saved (s0) across the func_001F40C8 call, so the
"declare prod before base" lever is blocked (prod is computed after the call).
3 forms (struct-array rc15, base+prod explicit rc1, base-off-first rc3). ADDU_RS
macro + swap_addu postprocess both retired; this TU (ap1) was excluded from the
clean retirement. Genuine swap_addu floor — offline permuter. Seed = clean rc1.
