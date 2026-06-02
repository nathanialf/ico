extern int D_00275254[];
extern int D_0063304C;
extern void func_001B7288(int a0);

int func_001B5728(void)
{
    int ret;
    if ((D_00275254[0] & 0x10) == 0) goto fail;
    func_001B7288(0);
    D_0063304C = 0;
    ret = 0x1A;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}
