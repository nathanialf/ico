extern float D_006318A4;
extern float D_006318A8;

int func_0023D348(int *self)
{
    float *p = (float *)self[0x34 / 4];
    float lo = D_006318A4;
    float hi = D_006318A8;
    p[2] = hi;
    p[0] = lo;
    *(float *)((char *)self + 0x1C) = 0.5f;
    return 1;
}
