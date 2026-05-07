extern int D_00633F18;
extern int D_00633F1C;

int func_001D4DA8(int a0, int a1)
{
    int v0;
    if (a1 != 0) {
        v0 = D_00633F1C + a0;
        D_00633F1C = v0;
    } else {
        v0 = D_00633F18 + a0;
        D_00633F18 = v0;
    }
    return v0;
}
