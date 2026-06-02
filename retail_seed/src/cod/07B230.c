extern unsigned char D_0028A520[];

int func_0017B230(int a0)
{
    return (D_0028A520[a0 >> 3] >> (a0 & 7)) & 1;
}
