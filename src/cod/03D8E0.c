extern int D_006A6F30[];
extern char D_00557958[];
extern void func_001A6E28(char *p);

int func_0013D8E0(unsigned int a0)
{
    int ret;
    if (a0 < 0x101) goto valid;
    func_001A6E28(D_00557958);
    ret = 0;
    goto out;
valid:
    ret = D_006A6F30[a0];
out:
    return ret;
}
