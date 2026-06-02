extern void func_00242640(int x, int y);
extern int *func_00244630(int x);
extern void func_00244980(int *p, int q);

void func_001AB378(int *self)
{
    int *p;
    func_00242640(0, 0);
    p = func_00244630(1);
    *p |= 0x40;
    func_00244980(p, (self[0x4/4] & 0x3FF0) | 0x80000000);
}
