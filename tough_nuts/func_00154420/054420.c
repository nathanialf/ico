extern int *D_00631AE4;

int func_00154420(void)
{
    int *v1 = D_00631AE4;
    unsigned int x = ((unsigned int *)v1[0x164 / 4])[0x30 / 4];
    if (x >= 0x5D) {
        return 1;
    }
    return x < 0x5B;
}
