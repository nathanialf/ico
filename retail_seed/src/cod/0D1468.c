extern int D_006333EC;
extern int func_001F40C8(int *p);
extern void func_001F41C8(int *p);

int func_001D1468(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_006333EC)[0x15C/4];
    q = (int *)p[0x630/4];
    if (q != 0) {
        if (func_001F40C8(q) == 1) {
            int *r = (int *)((int *)D_006333EC)[0x15C/4];
            func_001F41C8((int *)r[0x630/4]);
        }
    }
    return 1;
}
