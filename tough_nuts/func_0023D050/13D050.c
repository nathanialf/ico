extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;
extern float D_00631880;

int func_0023D050(int *self)
{
    float f;
    int *p = (int *)self[0x34 / 4];
    int v;
    *(float *)((char *)p + 8) = -3300.0f;
    *(float *)((char *)p + 0) = D_00631880;
    if (D_00633B4C != D_00631960) {
        D_00633B4C = D_00631960;
        v = func_0018CF60((int)self);
        f = func_001F5298(v);
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    } else {
        f = D_00633B48;
    }
    *(float *)((char *)self + 0x18) = f;
    return 1;
}
