extern int D_005525DC[];
extern int D_0055266C;
extern int D_005524D0[];
extern int D_005524DC[];
extern int D_005524C4[];
extern char D_0062ECE8[];
extern void func_00252590(char *p, int x);
extern void func_00257A20(int a, int b);
extern void func_00257B38(int a, int b, int c);

void func_002523B0(int a0)
{
    if (D_005525DC[0] != 0) {
        func_00252590(D_0062ECE8, a0);
    } else if (D_0055266C == 3) {
        func_00257A20(D_005524C4[0], a0 - 1);
    } else {
        func_00257B38(D_005524D0[0], D_005524DC[0], a0 - 1);
    }
    D_005525DC[0] = 0;
}
