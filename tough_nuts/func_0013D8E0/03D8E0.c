extern int D_006A6F30[];
extern char D_00557958[];
extern void func_001A6E28(char *p);

int func_0013D8E0(unsigned int a0)
{
    if (a0 < 0x101) {
        return D_006A6F30[a0];
    }
    func_001A6E28(D_00557958);
    return 0;
}
