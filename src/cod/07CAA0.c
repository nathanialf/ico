extern int *func_0013EB50(void);
extern int *func_0013EBE0(int *a0);

void func_0017CAA0(void)
{
    int *p = func_0013EB50();
    while (p != 0) {
        p[0x16C / 4] = 1;
        p = func_0013EBE0(p);
    }
}
