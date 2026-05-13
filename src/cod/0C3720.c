extern void func_001C34C0(void);
extern void *func_00203B40(void *fp, int prio);

void func_001C3720(int *self)
{
    void *r = func_00203B40((void *)func_001C34C0, 0x15);
    do {
        *self = 0;
        *(int **)((char *)r + 0x20) = self;
    } while (0);
}
