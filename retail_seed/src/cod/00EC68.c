extern int D_00632CE0;
extern int D_00631B84;
extern char D_00553E90[];
extern void func_001A6B10(int a0, char *a1, int a2);

void func_0010EC68(int a0)
{
    D_00631B84 = a0;
    if (D_00632CE0 != 0) {
        func_001A6B10(0xCCCCCC00, D_00553E90, a0);
    }
}
