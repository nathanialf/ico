extern int func_00100410(void);
extern int func_00100470(int a0);

int func_0013D9C8(int *self)
{
    int v;
    if (self == 0) {
        v = func_00100410();
    } else {
        v = self[0x30/4];
    }
    return func_00100470(v);
}
