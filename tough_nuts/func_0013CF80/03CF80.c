typedef void (*func_0013CF80_FnPtr)(int *p, int x);

void func_0013CF80(int *self)
{
    func_0013CF80_FnPtr fn = (func_0013CF80_FnPtr)self[0x8 / 4];
    if (fn != 0) {
        int *p = (int *)self[0];
        while (p != 0) {
            fn(p, self[0xC / 4]);
            p = (int *)p[0x34 / 4];
        }
    }
    self[0] = 0;
}
