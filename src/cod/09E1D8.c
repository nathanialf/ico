extern int func_00240A20(int x);
extern int func_00251C18(int *self);

int func_0019E1D8(int *self)
{
    int ret = 0;
    if (func_00240A20((int)((char *)self + 0x50)) == 0) {
        ret = func_00251C18(self) != 0;
    }
    return ret;
}
