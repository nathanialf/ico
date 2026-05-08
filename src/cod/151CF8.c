typedef int (*func_00251CF8_FnPtr)(int *self, int *idx, int extra);

int func_00251CF8(int *self, int *idx)
{
    int ret = 0;
    if (self != 0) {
        int *t = (int *)self[0x40 / 4];
        if (t != 0) {
            int *entry = (int *)((char *)t + (*idx) * 8);
            func_00251CF8_FnPtr fn = (func_00251CF8_FnPtr)entry[0xC / 4];
            if (fn != 0) {
                ret = fn(self, idx, entry[0x10 / 4]);
            }
        }
    }
    return ret;
}
