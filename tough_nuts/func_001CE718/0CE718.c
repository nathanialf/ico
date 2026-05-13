/* src/cod/0CE718.c — func_001CE718 */

void func_001CE718(int *self, float val)
{
    char *p = (char *)((int *)self[0x57])[0x210];
    *(float *)(p + 0x30) = val;
    if (val < 0.0f) {
        *(float *)(p + 0x30) = 0.0f;
    }
    if (1.0f < *(float *)(p + 0x30)) {
        *(float *)(p + 0x30) = 1.0f;
    }
}
