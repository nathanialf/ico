/* func_0024E088 — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
void *func_0024E088(void *a0, void *a1) {
    void *rv = 0;
    if (a0 != 0) {
        int *tbl = *(int **)((char *)a0 + 0x40);
        if (tbl != 0) {
            int *e = (int *)((char *)tbl + (*(int *)a1 << 3));
            void *(*fn)() = (void *(*)())e[3];
            if (fn != 0) {
                rv = fn(a0, a1, e[4]);
            }
        }
    }
    return rv;
}
