extern int D_00275254[];
extern int func_001B7048(int a0);

int func_001B4F20(void)
{
    if (D_00275254[0] & 0x40) {
        return func_001B7048(0);
    }
    return -1;
}
