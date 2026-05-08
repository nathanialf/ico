extern int func_0014B090(void);
extern int func_001F4228(int *self);

int func_0014A700(int *self)
{
    int ret = 0;
    if (func_0014B090() != 0) {
        ret = func_001F4228(self);
    }
    return ret;
}
