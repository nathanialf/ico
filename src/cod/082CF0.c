extern int func_0014AF70(int a0, int a1);

int func_00182CF0(int *a0, int *a1)
{
    if (((unsigned char *)a1)[0x19] != 0) {
        return 1;
    }
    return func_0014AF70(*a0, a1[0]) != 0;
}
