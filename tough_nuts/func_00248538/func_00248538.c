extern int func_002490C0(int a0);
extern void func_00101A40(int *self);
extern void func_00101A88(void);
extern int D_00710F80[];

int func_00248538(int a0) {
    int old;
    if (func_002490C0(1) != 0) {
        return 0;
    }
    ((void (*)(void))func_00101A40)();
    old = D_00710F80[0];
    D_00710F80[0] = a0;
    func_00101A88();
    return old;
}
