extern void func_001297A0(int a, int b, int c);
extern int func_0012AA80(int x);
extern void func_00203AA0(int x);
extern void func_001C3270(void);
extern void func_0017B2B8(int x);

void func_00229CB0(volatile unsigned int self)
{
    volatile int local;
    func_001297A0(0x142, 1, 0);
    while (func_0012AA80(0x142) == 0) {
        func_00203AA0(1);
    }
    func_00203AA0(1);
    func_001C3270();
    func_00203AA0(0x78);
    func_0017B2B8(0x18A);
    func_0017B2B8(0x18B);
    func_00203AA0(0);
}
