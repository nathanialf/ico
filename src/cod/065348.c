extern int func_00160AF8(int *self);
extern void func_00165B50(int *self, int a, int b);
extern void func_0015BCC8(int *self, int a);

int func_00165348(int *self)
{
    int r = func_00160AF8(self);
    if (r != 0) {
        func_00165B50(self, 0, 0);
    }
    func_0015BCC8(self, 0xF4);
    return r;
}
