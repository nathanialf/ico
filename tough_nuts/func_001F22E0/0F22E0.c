/* src/cod/0F22E0.c — func_001F22E0 */

extern void func_001F2320(void);
extern void *func_00203B40(void *handler, int priority);

void func_001F22E0(int *self)
{
    int *h = (int *)func_00203B40((void *)func_001F2320, 0x15);
    self[0] = 0;
    h[0x20 / 4] = (int)self;
}
