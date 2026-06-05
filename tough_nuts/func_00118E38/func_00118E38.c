/* seki/src/MicroCode.c — func_00118E38 parked seed (rc12 regalloc-coloring tie)
   Apply this func into seki/src/MicroCode.c (hoist the typedef to file top if not
   already present), then: match_loop.py reset func_00118E38 --reason "resume". */
typedef int Qw128 __attribute__((mode(TI)));

void func_00118E38(Qw128 *a0, Qw128 *a1, Qw128 *a2, Qw128 *a3, Qw128 *a4) {
    Qw128 b0 = *a1, b1 = *a2, b2 = *a3, b3 = *a4;
    a0[0] = b0;
    a0[1] = b1;
    a0[2] = b2;
    a0[3] = b3;
}
