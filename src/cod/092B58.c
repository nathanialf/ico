extern void func_001AE460(int *self);
extern void func_0013FF88(int a0, int a1, int a2);

void func_00192B58(int *self) {
    int *p = (int *)((int *)self[0x15C/4])[0x800/4];
    p[0x50/4] = 1;
    func_001AE460(self);
    func_0013FF88((int)self, 1, (int)self);
}
