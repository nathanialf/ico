extern char D_006A98B0[];
extern long long D_00633CE0;
extern char D_005F2F00[];
extern void func_0025D7F0(int x);
extern void func_0013B8F0(void);
void func_00143138(int a0, int a1)
{
    int idx = a0 & 0xFF;
    char *e = D_006A98B0 + idx * 0x40;
    short h = *(short *)(e + 0x10);
    int *x;
    if (h < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)e) return;
    {
        int *node = *(int **)((char *)D_006A98B0 + 0x30 + idx * 0x40);
        if (node != 0) {
            unsigned long long bit = 1ULL << idx;
            long long m = *(long long *)((char *)node + 0x20);
            if (m & bit) {
                register long long nb asm("$5") = ~bit;
                unsigned int ev = *(unsigned short *)e;
                long long dv = D_00633CE0;
                *(long long *)((char *)node + 0x20) = m & nb;
                *(unsigned short *)e = ev + 1;
                D_00633CE0 = dv & nb;
                *(int *)((char *)D_006A98B0 + 0x30 + idx * 0x40) = 0;
            }
        }
    }
    if (a1 != 0) { func_0025D7F0(h | 0x8000); } else { func_0025D7F0(h); }
    x = *(int **)(e + 0x38);
    if ((((unsigned int)x[0xE] >> 6) & 1) != 1) {
        short *q = (short *)((char *)D_005F2F00 + *(unsigned short *)((char *)x + 0x36) * 8);
        if (*(short *)((char *)q + 6) != 0) return;
    }
    if (*(int *)(e + 0xC) == 0) return;
    func_0013B8F0();
}
