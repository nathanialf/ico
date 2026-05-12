/* src/cod/066000.c — func_00166000 */

unsigned int func_00166000(unsigned int a0)
{
    volatile unsigned int local = a0;
    unsigned int v = local;
    *(int *)(*(int *)(v + 0x15C) + 0x550) = 0;
    *(int *)(*(int *)(v + 0x15C) + 0x380) = 0;
    return v;
}
