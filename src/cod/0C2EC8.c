extern int *func_0013EB50(int x);
extern void func_001C2760(int *p);
extern int *func_0013EBE0(int *p);

void func_001C2EC8(void)
{
    int *p = func_0013EB50(0x2B);
    if (p != 0) {
        do {
            func_001C2760(p);
            p = func_0013EBE0(p);
        } while (p != 0);
    }
}
