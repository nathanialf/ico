extern int func_0013EB50(void);
extern int func_0013EBE0(int a0);

void func_0017CAE0(void)
{
    int v0 = func_0013EB50();
    while (v0 != 0) {
        *(int *)(v0 + 0x16C) = 0;
        v0 = func_0013EBE0(v0);
    }
}
