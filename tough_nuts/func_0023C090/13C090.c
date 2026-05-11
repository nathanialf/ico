extern int func_0017B230(int x);
extern float D_006317E0;

typedef struct {
    float a0;
    float a4;
    float a8;
} S;

int func_0023C090(int *self)
{
    S *p;
    p = (S *) self[0x34 / 4];
    p->a8 = 482.0f;
    p->a0 = D_006317E0;
    *(float *) ((char *) self + 0x1C) = 0.5f;
    if (func_0017B230(0x5F)) {
        *(int *) ((char *) self + 0x18) = 0;
    }
    return 1;
}
