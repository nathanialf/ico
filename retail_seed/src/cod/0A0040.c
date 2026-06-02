extern int D_00274EC0[];
extern int D_004B3B28[];
extern int D_004B6A90[];
extern void func_001AE8F0(int *a0, int *a1, int a2);

void func_001A0040(void)
{
    if (D_00274EC0[2]) {
        func_001AE8F0(D_004B3B28, D_004B6A90, 0);
        D_00274EC0[3] = 1;
    }
}
