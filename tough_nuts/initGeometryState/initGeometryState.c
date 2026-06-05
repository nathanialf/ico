/* common/src/DObj.c — initGeometryState parked seed (rc5, after 1 permuter pass).
   value-before-if (int count) + long long result temp fixed const->v0; residual is
   value->a1/base->v1/product->a0 vs ROM value->v1/base->a0/product->v1 (coalescing
   coupling, same class as func_001F8848). Apply + match_loop.py reset. */
int initGeometryState(int *a0) {
    int count = a0[2];
    if (a0[3] != a0[4]) {
        long long r = a0[0] + count * 0x151800;
        return r;
    }
    return 0;
}
