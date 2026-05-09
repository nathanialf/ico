extern int *func_0013EB50(int x);
extern int *func_0013EBE0(int *p);

void func_0017CA58(int x)
{
    int *p = func_0013EB50(x);
    while (p != 0) {
        p[0x50 / 4] = (int)0xFFFFFFFFU;
        p = func_0013EBE0(p);
    }
}
