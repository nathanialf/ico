extern float D_006333F0;
extern void func_001D0FA8(int a0);
extern void func_001D1158(int a0);

void func_001D1288(int a0, int a1)
{
    D_006333F0 = 1.0f;
    if (a0) {
        func_001D0FA8(a0);
    } else {
        func_001D1158(a1);
    }
}
