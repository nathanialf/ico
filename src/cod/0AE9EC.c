extern int D_00632F80;
extern char D_004B3B10[];
extern void func_001AE1B8(int a, char *p, int n);
extern void func_002641D8(char *p, int a, int n);

void func_001AE9F0(int a0)
{
    if (D_00632F80 == 0) {
        func_001AE1B8(a0, D_004B3B10, 0x12);
        return;
    }
    {
        char buf[0x20];
        func_002641D8(buf, 0, 0x12);
        func_001AE1B8(a0, buf, 0x12);
    }
}
