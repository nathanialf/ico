extern int func_001FBAA8(int a0, int v, int n);
extern void func_001FB8B8(void);

void func_0011FCD8(short *self, int *p)
{
    short idx = self[0x80/2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
        func_001FBAA8(2, v, 6);
        func_001FB8B8();
    }
}
