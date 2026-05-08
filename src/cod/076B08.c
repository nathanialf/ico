extern int D_00274EE8[];
extern int D_0028A4A0[];
extern void func_0013A5B8(int *a0, int *a1, int a2);

void func_00176B08(int *p) {
    if (D_00274EE8[0] != 0) {
        *p = 1;
        func_0013A5B8(D_0028A4A0, p, 0);
    }
}
