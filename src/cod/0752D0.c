extern int D_006ABDE0[100];

void func_001752D0(int *self)
{
    int *p;
    p = (int *)self[0x59];
    D_006ABDE0[0] = 0;
    D_006ABDE0[1] = 0;
    if (p[0xC] != 0x45) {
        *(long long *)((char *)p + 0x20) &= ~0x200LL;
    }
}
