extern int func_00168BD0(void *a0, void *a1);

int func_0010A120(int *a0, int a1)
{
    int *v0 = (int *)a0[0x15C / 4];
    signed char *v1 = (signed char *)v0[0x810 / 4];
    char *a2 = (char *)v0[0xC / 4];
    return func_00168BD0((char *)v0 + 0x3F0, a2 + (v1[a1] << 6) + 0x30);
}
