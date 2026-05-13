extern float D_00630F8C;

unsigned char func_00190440(char *a0, int *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / D_00630F8C);
    return *(unsigned char *)(p + 0x6C);
}
