typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);

void func_001AE8F0(int *self, int a1, int a2)
{
    int buf[2];
    func_001AE8F0_FnPtr fn;

    buf[0] = a1;
    buf[1] = 0;
    fn = (func_001AE8F0_FnPtr)self[1];
    if (fn != 0) {
        do {
            fn(buf, a2);
            self += 2;
            fn = (func_001AE8F0_FnPtr)self[1];
        } while (fn != 0);
    }
}
