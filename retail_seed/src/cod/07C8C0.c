extern int func_0013EAE8(void);
extern void func_0013FF88(int a0, int a1, int a2);

void func_0017C8C0(void)
{
    int rc = func_0013EAE8();
    if (rc) {
        func_0013FF88(rc, 0x1F, rc);
    }
}
