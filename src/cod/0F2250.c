extern void func_00104508(int *buf, int *p);
extern void func_00243AE8(int *p, int *buf, int *q);
extern void func_00105F00(int *dst, int *src);

void func_001F2250(int *self)
{
    int buf[4];
    int *p;
    func_00104508(buf, self);
    p = (int *)self[0x15C/4];
    func_00243AE8((int *)((char *)p + 0x130), buf, (int *)((char *)p + 0x1F0));
    p = (int *)self[0x15C/4];
    func_00105F00((int *)((char *)p + 0x1F0), buf);
}
