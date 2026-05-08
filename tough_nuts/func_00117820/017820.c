extern int D_00632024;
extern char D_00554CA8[];
extern void *D_00633C34;
extern void *func_0013A0F8(int x, int n, void *t, int line);

void *func_00117820(void *self)
{
    void *d;
    void *old;
    d = func_0013A0F8(D_00632024, 0xA0, D_00554CA8, 0x2D3);
    *(void **)((char *)d + 0x90) = self;
    old = D_00633C34;
    if (old != 0) {
        *(void **)((char *)old + 0x94) = d;
    }
    *(float *)((char *)d + 0x80) = 1.0f;
    *(void **)((char *)d + 0x98) = old;
    *(void **)((char *)d + 0x94) = 0;
    D_00633C34 = d;
    return d;
}
