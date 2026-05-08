extern int func_00154770(void);
extern int func_0013EAE8(int a0);
extern int D_00631AE4;

int func_0018CAD8(void) {
    int v = func_00154770();
    if (v == 0) {
        return D_00631AE4;
    }
    v = func_0013EAE8(v);
    if (v != 0) {
        return v;
    }
    return D_00631AE4;
}
