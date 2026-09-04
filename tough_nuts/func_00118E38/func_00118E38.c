/* seki/src/MicroCode.c — _MakeLightColorMatrix parked seed (rc9 regalloc-coloring tie).
   IMPROVED rc12 -> rc9 (2026-06-08): reverse decl order (b3=*a4..b0=*a1) + store
   order a0[1],a0[0],a0[3],a0[2] colors the high pair b2,b3 into t0,t1 ($8,$9)
   correctly. Residual rc9 = the low pair b0,b1 wanting a2,a3 ($6,$7) via src-ptr
   pre-saves (daddu) which gcc avoids by reusing dying arg regs.
   Apply into seki/src/MicroCode.c (after func_00118D68, BEFORE the _InitRandom
   VU0-asm sibling — do NOT delete _InitRandom!), then:
     match_loop.py reset _MakeLightColorMatrix --reason "resume". */
typedef int Qw128 __attribute__((mode(TI)));

void _MakeLightColorMatrix(Qw128 *a0, Qw128 *a1, Qw128 *a2, Qw128 *a3, Qw128 *a4) {
    Qw128 b3 = *a4, b2 = *a3, b1 = *a2, b0 = *a1;
    a0[1] = b1;
    a0[0] = b0;
    a0[3] = b3;
    a0[2] = b2;
}
