extern void func_00139598(void *p);
extern void func_00136140(void *p);
extern void func_00138A10(int a0);
extern int D_0063203C;

void func_001354B8(int *a0)
{
    int *s0;
    register int *prev __asm__("$4");
    if (((int *)((char *) a0 + 0x18000))[0x54 / 4] != 0)
    {
        s0 = (int *) ((int *)((char *) a0 + 0x18000))[0x58 / 4];
        if (s0 != 0)
        {
            s0 = (int *)((char *) s0 - 8);
            __asm__ __volatile__("");
        loop58:
            prev = s0;
            func_00139598(prev);
            s0 = *(int **)((char *) s0 + 4);
            if (s0 != 0)
            {
                s0 = (int *)((char *) s0 - 8);
                goto loop58;
            }
        }
        s0 = (int *) ((int *)((char *) a0 + 0x18000))[0x54 / 4];
        if (s0 != 0)
        {
            s0 = (int *)((char *) s0 - 8);
            __asm__ __volatile__("");
        loop54:
            prev = s0;
            func_00139598(prev);
            s0 = *(int **)((char *) s0 + 4);
            if (s0 != 0)
            {
                s0 = (int *)((char *) s0 - 8);
                goto loop54;
            }
        }
        ((int *)((char *) a0 + 0x18000))[0x54 / 4] = 0;
        ((int *)((char *) a0 + 0x18000))[0x58 / 4] = 0;
    }
    func_00136140((char *) a0 + 0x18098);
    func_00139598(a0);
    func_00138A10(D_0063203C);
}
