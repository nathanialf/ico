extern int D_00275254[];
extern int func_001B7040(void);

int func_001B5998(void)
{
    if (D_00275254[0] & 0x10) {
        return func_001B7040();
    }
    return -1;
}
