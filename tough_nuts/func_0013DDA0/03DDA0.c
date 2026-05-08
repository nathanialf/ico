extern int D_00281A70[];
extern int D_00281A90[];
extern int D_006321CC;
extern int D_006321D0;
extern void func_0013E4D0(void);
extern void func_0013DD88(void);

void func_0013DDA0(void)
{
    int *q = D_00281A90;
    int *p = D_00281A70;
    int i;
    for (i = 7; i >= 0; i--) {
        *p = 0;
        *q = 0;
        p++;
        q++;
    }
    func_0013E4D0();
    D_006321CC = 0;
    D_006321D0 = 0;
    func_0013DD88();
}
