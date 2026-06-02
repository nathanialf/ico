extern int func_001E8D30(int a0);
extern void func_00243B60(int a, int b);

void func_001973A8(int a0, int a1)
{
    if (a0 >= 0) {
        int v;
        v = func_001E8D30(a0);
        func_00243B60(v + 0x40, a1);
    }
}
