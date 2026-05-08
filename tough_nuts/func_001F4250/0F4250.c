extern void func_0010D830(int *p);
extern void func_00105F00(int *dst, int *src);

void func_001F4250(int *self, int *src, int flag)
{
    int *p = (int *)self[0x15C/4];
    int *q = (int *)p[0x800/4];
    int *base_A0 = (int *)((char *)p + 0xA0);
    if (q[0x8/4] != 0) {
        ((int *)((int *)q[0x8/4])[0x15C/4])[0x630/4] = 0;
    }
    q[0x4/4] = 1;
    q[0xC/4] = -1;
    if (flag != 0) {
        q[0x8/4] = 0;
        func_0010D830((int *)((char *)p + 0x150));
    }
    func_00105F00((int *)((char *)p + 0x130), src);
    base_A0[0x9C/4] = 0;
}
