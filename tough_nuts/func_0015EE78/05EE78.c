extern void func_001A6E28(char *p);
extern void func_001902C8(int x, int y);
extern char D_00558848[];

void func_0015EE78(volatile unsigned int self)
{
    volatile int local;
    int *s = (int *)((int *)self)[0x164 / 4];
    func_001A6E28(D_00558848);
    func_001902C8(s[0x180 / 4], (int)self);
    s[0x184 / 4] = s[0x180 / 4];
    ((int *)((int *)self)[0x15C / 4])[0x420 / 4] = 0;
}
