/* common/src/DObj.c — initGeometryState parked seed (rc6 regalloc coalescing tie).
   ROM keeps value/product in v1 + const in v0; built coalesces value->v0 (return reg)
   and fills the beq delay with the const lui. if(!=)compute gives the correct beq;
   ~20 distinct shapes all rc6. Permuter-class. Apply + match_loop.py reset. */
int initGeometryState(int *a0) {
    if (a0[3] != a0[4]) {
        return a0[0] + a0[2] * 0x151800;
    }
    return 0;
}
