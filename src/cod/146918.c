extern void func_00101A40(int *self);
extern void func_00101A88(void);

int *func_00246918(int *self)
{
    int *p;
    int v;
    func_00101A40(self);
    p = (int *)self[0xC/4];
    if (p == 0) {
        self[0x4/4] = 0;
        goto after;
    }
    v = p[0x3C/4];
    self[0x4/4] = 1;
    self[0xC/4] = v;
after:
    func_00101A88();
    return p;
}
