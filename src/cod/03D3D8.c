extern void func_00100350(void);
extern void func_00100370(int a0);

void func_0013D3D8(int a0)
{
    if (a0 == 0) {
        func_00100350();
    } else {
        func_00100370(*(int *)(a0 + 0x30));
    }
}
