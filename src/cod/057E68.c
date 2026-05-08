extern void func_00157DC8(int a0);
extern void func_00157DA0(int a, int b);

void func_00157E68(int *self)
{
    func_00157DC8((int)self);
    if (self[0xC / 4] == 1) {
        func_00157DA0(((int *)self[0x164 / 4])[0x1A0 / 4], 6);
    }
}
