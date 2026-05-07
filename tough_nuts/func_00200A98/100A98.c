extern int D_00631990;
extern int func_0010A088(int a0, int a1);
extern int func_0010A068(int a0, int a1);

int func_00200A98(int a0)
{
    int v0;
    if (D_00631990 == 4) {
        v0 = func_0010A088(a0, 0x1000);
    } else {
        v0 = func_0010A068(a0, 0x1000);
    }
    return v0 & 0xFF;
}
