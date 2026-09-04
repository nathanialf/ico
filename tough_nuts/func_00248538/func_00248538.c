extern int sceCdSync(int a0);
extern void DIntr(int *self);
extern void EIntr(void);
extern int D_00710F80[];

int sceCdCallback(int a0) {
    int old;
    if (sceCdSync(1) != 0) {
        return 0;
    }
    ((void (*)(void))DIntr)();
    old = D_00710F80[0];
    D_00710F80[0] = a0;
    EIntr();
    return old;
}
