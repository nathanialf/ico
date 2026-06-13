# func_0024E088 — PARKED near-miss rc9 (not permuter-run)

VRAM 0x0024E088, common/src/PObj.c. vtable dispatch with fn-ptr call.
Caller-side decl is `void func_0024E088(void*,void*)` but it RETURNS the fn's
return value (callers ignore it) — I changed the in-TU extern to `void*`.

## Shape (rc9 seed)
`if(!a0) return 0; tbl=a0->[0x40]; if(!tbl) return 0; e=tbl+(*a1<<3);
fn=e[0xC]; if(!fn) return 0; return fn(a0,a1,e[0x10]);`  rv defaults 0.
Note: rv = fn's RETURN ($2 after jalr), NOT the entry e (jalr clobbers v0).
fn called with $4=a0,$5=a1 unchanged + $6=e[0x10] set in the jalr delay.

## Residual rc9 (3 coupled issues, 5 sites)
1. rv accumulator reg: ROM $7/a3, gcc $6/a2 (sites 1,15,17).
2. tbl reg: ROM lw a2,64(a0); gcc lw v1,64(a0).
3. ROM RECOMPUTES e twice (addu v1 for fn lookup, addu v0 for the call) and
   fills the `beq fn,0` delay slot with the 2nd addu → plain **beq**. gcc
   CSEs e (one addu) → nothing to fill → **beql** (annulled). Need to force
   the e-address recompute so the beq delay is filled.
Tried: inline-addr, basefold ((tbl+off)+idx*8), idx_var, e[3]/e[4] — all rc9.

## RESUME
Force gcc to (a) recompute e's address after the fn!=0 check (fills beq delay,
kills beql) and (b) allocate rv to a3 / tbl to a2. Likely the e-recompute is the
root that cascades the regs. Try giving the fn-lookup and the call-arg/data
DIFFERENT rooted address expressions (dual-root, see
feedback_dual_root_addr_ptr_defeats_gcse) so gcse doesn't merge e.
