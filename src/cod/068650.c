extern int D_006323F0;
extern int D_006323F4;
extern void func_00167230(int *a0);
extern void func_00167258(int *a0);
extern void func_00169F80(int *a0);
extern void func_0016A058(int *a0);

int func_00168650(int a0)
{
    D_006323F0 = (int)&func_00167230;
    D_006323F4 = (int)&func_00167258;
    if (a0 != 0) {
        D_006323F0 = (int)&func_00169F80;
        D_006323F4 = (int)&func_0016A058;
    }
    return 0;
}
