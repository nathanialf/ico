extern unsigned int D_0028A640[];
extern void func_00203AA0(int);
extern void func_0017BB98(int);

void func_0017D1D0(volatile int a0)
{
    unsigned int i;
    short *p;

    func_00203AA0(10);
    p = (short *)D_0028A640;
    for (i = 0; i < 7; i++) {
        if ((int)*p == ((int *)a0)[2]) goto found;
        p = (short *)((char *)p + 0x30);
    }
    return;
found:
    func_0017BB98(a0);
}
