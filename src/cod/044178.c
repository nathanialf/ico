extern int func_00142C60(int a0, int a1, int a2, int a3, int t0, int t1);
extern void func_00142890(int *p);
extern unsigned char D_006A98B0[];

int func_00144178(int a0, int a1, int a2, int a3)
{
    int idx = func_00142C60(a0, a1, a2, a3, 0, 0);
    if (idx >= 0) {
        func_00142890((int *)((char *)D_006A98B0 + (idx & 0xFF) * 64));
    }
    return idx;
}
