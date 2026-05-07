extern int D_006D0D20[];
extern void func_00141E00(int a0);

void func_00192050(void)
{
    if (D_006D0D20[0] != 0) {
        func_00141E00(D_006D0D20[0]);
        D_006D0D20[0] = 0;
    }
}
