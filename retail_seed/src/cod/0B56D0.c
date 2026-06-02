extern int func_001B7288(int x);
extern int D_0063304C;

int func_001B56D0(int a0, int a1)
{
    int ret;
    if (a1 == 0xB7) goto path_b7;
    if (a1 == 0xB8) goto path_b8;
    return -1;
path_b7:
    func_001B7288(0);
    D_0063304C = 0;
    ret = 0x2E;
    goto out;
path_b8:
    func_001B7288(0);
    D_0063304C = 0;
    ret = 0x1A;
out:
    return ret;
}
