extern int D_00631AE4;
extern void func_001F3388(int *sub);

void func_00156488(int *self)
{
    int *p;
    int *sub;
    int *base;
    int a1;
    p = (int *)self[0x59];
    if (p[0xB] == 0) {
        a1 = p[0x174];
    } else {
        a1 = *(int *)p[0xB];
    }
    if (self != (int *)D_00631AE4) return;
    sub = (int *)p[0x50];
    if (sub == 0) return;
    base = (int *)sub[0x57];
    *(int *)((char *)base + 0x5F4) = a1;
    func_001F3388(sub);
}
