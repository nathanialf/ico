extern int D_00631B7C;
extern int D_00553E48[];
extern void func_001A6E28(int *a0);

void func_0010DB28(void)
{
    D_00631B7C -= 1;
    if (D_00631B7C < 0) {
        func_001A6E28(D_00553E48);
        D_00631B7C = 0;
    }
}
