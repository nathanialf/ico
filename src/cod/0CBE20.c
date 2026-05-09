extern void func_00105F00(int p, int q);
extern int D_0063330C;
extern int D_00633310;
extern int D_00633314;
extern int D_00633318;
extern float D_0063331C;
extern char D_004C09A0[];

void func_001CBE20(int a0, float t)
{
    D_0063330C = 1;
    D_00633314 = 1;
    D_00633310 = 0;
    D_00633318 = 0;
    func_00105F00((int) D_004C09A0, a0);
    D_0063331C = t;
    D_00633318 = 1;
    D_00633314 = 0;
}
