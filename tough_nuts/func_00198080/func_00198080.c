extern void GetClothAnimation(int a0, int a1, int a2);
extern void func_0010F068(void);
extern void func_0010F048(int a0);

void func_00198080(char *a0) {
    char *cloth;
    int x;
    func_0010F068();
    func_0010F048((int)a0);
    cloth = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    if (*(int *)(cloth + 0xC) != 0) {
        GetClothAnimation(*(int *)(cloth + 0x10), x + 0x40, x);
    }
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x14), x + 0x40, x);
}
