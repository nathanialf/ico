extern int D_00633F64;
extern int D_006337B0;
extern int D_006337B8;
extern int D_00710BE0[];
extern void func_001185A8(void *dst, void *src);

int func_001FA598(void *p)
{
    int v = D_00633F64;
    if (v != 0) {
        func_001185A8(p, D_00710BE0);
        v = D_00633F64;
    } else {
        D_006337B0 = 0;
    }
    return v != 0 && D_006337B8 == 0;
}
