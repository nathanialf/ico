extern void func_001BC0A8(void);

void func_001C0870(int *self, int x)
{
    int *q = (int *)((int *)self[0x15C/4])[0x800/4];
    if (q[0x4/4] != x) {
        func_001BC0A8();
    }
    q[0x4/4] = x;
}
