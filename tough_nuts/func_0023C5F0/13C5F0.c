extern int func_0018CF60(int *p);
extern int func_0023B728(int *p);

int func_0023C5F0(int *self)
{
    float *p = (float *)func_0018CF60(self);
    int v = 0;
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            v = func_0023B728(self);
        }
    }
    return v;
}
