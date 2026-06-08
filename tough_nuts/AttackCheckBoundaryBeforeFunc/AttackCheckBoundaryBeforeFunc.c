extern int D_0062D388;
extern void *D_004BA260[];

void *AttackCheckBoundaryBeforeFunc(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    if (p != 0) {
        unsigned int idx = *(unsigned int *)((char *)p + 0x30);
        if (idx < 6) {
            return D_004BA260[idx];
        }
    }
    return &D_0062D388;
}
