extern int D_006AB100[];
extern void func_00105F00(int a0, int a1);

int func_00168C88(int a0, int a1)
{
    int v = D_006AB100[a1 & 0xF];
    if (v != 0) {
        func_00105F00(a0, v);
        return 0;
    }
    return 1;
}
