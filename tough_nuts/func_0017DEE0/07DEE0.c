extern int *func_0013EAE8(void);
extern void func_0013FF88(int a, int b, int c);
extern unsigned char D_002A4C48[];

void func_0017DEE0(void)
{
    int *p = func_0013EAE8();
    if (p != 0) {
        func_0013FF88((int)p, 0x26, (int)p);
        *(unsigned short *)((char *)D_002A4C48 + p[0x8 / 4] * 0x4C + 0x42) = 0;
    }
}
