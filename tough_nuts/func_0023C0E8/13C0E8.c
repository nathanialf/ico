extern int func_0017B230(int x);
extern float D_006317E4;
extern float D_006317E8;

int func_0023C0E8(int *self)
{
    float *p;
    p = (float *) self[0x34 / 4];
    p[2] = 482.0f;
    p[0] = D_006317E4;
    p[1] = D_006317E8;
    *(float *) ((char *) self + 0x1C) = 0.5f;
    if (func_0017B230(0x5F)) {
        *(int *) ((char *) self + 0x18) = 0;
    }
    return 1;
}
