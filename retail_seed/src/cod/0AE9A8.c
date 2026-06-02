extern void func_001AE8A0(int *self, int *buf, int x);
extern int func_00265024(int *p, int *buf);
extern int D_00632F80;
extern int D_004B3B10[];

void func_001AE9A8(int *self)
{
    int buf[8];
    func_001AE8A0(self, buf, 0x12);
    if (func_00265024(D_004B3B10, buf) != 0) {
        D_00632F80 = 1;
    } else {
        D_00632F80 = 0;
    }
}
