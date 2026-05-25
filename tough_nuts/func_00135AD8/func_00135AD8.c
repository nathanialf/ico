int func_00135AD8(int *a0)
{
    register int *self __asm__("$16") = a0;
    int *w = (int *)((char *) self + 0x18000);
    w[0x4C / 4] = 0;
    for (;;)
    {
        int offset = w[0x4C / 4];
        long long ret = (*(int (**)(char *, unsigned int, int))((char *) self + 4))(
            (char *) self + offset + 0x10008,
            (unsigned int)(0x8000 - offset),
            self[0]);
        if ((unsigned int)(ret + 1) < 2)
        {
            break;
        }
        offset = w[0x4C / 4] + ret;
        if ((unsigned int) offset > 0x7FFF)
        {
            break;
        }
        w[0x4C / 4] = offset;
    }
    if (((int *)((char *) self + 0x18000))[0x4C / 4] == 0)
    {
        return -1;
    }
    ((int *)((char *) self + 0x18000))[0x50 / 4] = 1;
    return *(unsigned char *)((char *) self + 0x10008);
}
