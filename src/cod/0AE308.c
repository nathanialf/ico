/* src/cod/0AE308.c — func_001AE308 */

extern int func_001547A0(void);
extern int func_001547B0(void);
extern void func_00264128(int a0, int a1, int a2);
extern void func_001548F0(void);

void func_001AE308(int *a0)
{
    int s1 = func_001547A0();
    int s2 = func_001547B0();
    if (s1 != 0) {
        func_00264128(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return func_001548F0();
}
