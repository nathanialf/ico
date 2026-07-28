extern void func_001CF998(int a0);
extern int func_001CF770(int a0);
extern void func_001CDB28(int *self);

void func_001CE5F8(int *self)
{
    char *p = *(char **)((char *)self + 0x15C);
    char *s0 = *(char **)(p + 0x800);
    if (*(int *)(s0 + 0x38) != 0) {
        func_001224E0(p);
        if (*(float *)(*(char **)(*(char **)((char *)self + 0x15C) + 0x840) + 0x30) == 0.0f) {
            func_001CF998(*(volatile int *)(s0 + 0x18));
            func_001CF998(*(int *)(s0 + 0x20));
        }
    }
    func_001CF770(*(int *)(s0 + 0x28));
    if (*(int *)(s0 + 0x10) != 0) {
        func_001CDB28(self);
    }
}
extern int func_00165F88(int *self);
extern void func_001BB7E0(void);
extern void func_001CE5F8(int *self);

void func_001CE690(int *self)
