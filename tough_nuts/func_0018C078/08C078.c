extern int D_00632D30;
extern float D_006D0694[];
extern void func_0018CC18(int a0, int a1, int a2, float *a3, float *t0);

void func_0018C078(int a0, int a1, int a2, float *a3, float *t0)
{
    *a3 = D_006D0694[0];
    *t0 = (float)D_00632D30 / 100.0f;
    return func_0018CC18(a0, a1, a2, a3, t0);
}
