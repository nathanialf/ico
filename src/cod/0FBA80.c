extern int D_00633F70;

void func_001FBA80(int a0)
{
    if (a0 < 0) {
        D_00633F70 = 0;
    } else if (a0 >= 0xD) {
        D_00633F70 = 0xC;
    } else {
        D_00633F70 = a0;
    }
}
