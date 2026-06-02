/* src/cod/0AE258.c — func_001AE258 */

extern int func_001939C8(void);
extern int func_001939D8(void);
extern void func_00264128(int a0, int a1, int a2);
extern void func_00192D20(void);

void func_001AE258(int *a0)
{
    int s1 = func_001939C8();
    int s2 = func_001939D8();
    if (s1 != 0) {
        func_00264128(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return func_00192D20();
}
