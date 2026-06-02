extern void func_0013F638(int a0);
extern int func_0013D3F8(int a0);

void func_0013F6B8(int *a0)
{
    int v0;
    func_0013F638((int)a0);
    v0 = a0[4];
    a0[0] = 0;
    if (v0 != 0) {
        return;
    }
    return func_0013D3F8((int)a0 + 0x24);
}
