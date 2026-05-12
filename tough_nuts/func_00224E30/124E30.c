/* src/cod/124E30.c — func_00224E30 */

extern void func_00202208(unsigned int a0);
extern void func_00203AA0(int a0);
extern int func_0017B230(int a0);
extern int *func_0017E188(int a0);

void func_00224E30(volatile unsigned int a0)
{
    volatile int local;
    unsigned int copy = a0;
    func_00202208(copy);
    func_00203AA0(1);
    if (func_0017B230(0xCE) != 0) {
        *(int *)((char *)func_0017E188(0x4FC) + 0x16C) = 0;
    }
}
