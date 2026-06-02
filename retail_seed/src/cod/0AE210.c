/* src/cod/0AE210.c — func_001AE210 */

extern void func_00192E08(int a0);
extern int func_001939C8(void);
extern int func_001939D8(void);
extern void func_001AE1B8(int a0, int a1, int a2);

void func_001AE210(int a0)
{
    func_00192E08(a0);
    {
        int s0 = func_001939C8();
        int s1 = func_001939D8();
        return func_001AE1B8(a0, s0, s1);
    }
}
