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
