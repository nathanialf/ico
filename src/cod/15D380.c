extern int func_00258C50(int a0);

int func_0025D380(unsigned int a0)
{
    int v = -1;
    if (a0 < 0x30) {
        v = *(unsigned short *)(func_00258C50(a0) + 0x1E);
    }
    return v;
}
