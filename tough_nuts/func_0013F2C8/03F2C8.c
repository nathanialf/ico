extern int D_00281AB0[];
extern int D_00281AD0[];

void func_0013F2C8(void)
{
    int *p1 = D_00281AB0;
    int *p2 = D_00281AD0;
    int i = 7;
    do {
        *p1 = 0;
        i--;
        *p2 = 0;
        p1++;
        p2++;
    } while (i >= 0);
}
