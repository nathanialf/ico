extern int D_004BEFA8[];
extern void func_001A6E28(int a0);

void func_001BAEE0(int a0)
{
    int idx = *(int *)(*(int *)(a0 + 0x164) + 0x30);
    func_001A6E28(D_004BEFA8[idx]);
}
