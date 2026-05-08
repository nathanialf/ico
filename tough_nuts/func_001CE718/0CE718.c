void func_001CE718(int *self, float val)
{
    int *p = (int *)self[0x15C/4];
    int *q = (int *)p[0x840/4];
    if (val < 0.0f) {
        *(float *)((char *)q + 0x30) = 0.0f;
    } else {
        *(float *)((char *)q + 0x30) = val;
    }
    if (1.0f < *(float *)((char *)q + 0x30)) {
        *(float *)((char *)q + 0x30) = 1.0f;
    }
}
