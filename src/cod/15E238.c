extern int *func_00258CE0(void);

int func_0025E238(unsigned int a0)
{
    int ret = 0;
    if (a0 < 0x10) {
        int *p = func_00258CE0();
        ret = *(int *)((char *)p + (a0 << 2) + 0x180);
    }
    return ret;
}
