extern void func_0026AC40(int a0, int *self);

int func_00266870(int a0, int *self)
{
    if (self[2] == 0) {
        self[1] = 0;
        goto end;
    }
    func_0026AC40(a0, self);
    self[2] = 0;
    self[1] = 0;
end:
    return 0;
}
