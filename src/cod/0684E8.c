extern void (*D_006323F0)(int a0, int a1);
extern int D_00633D34;

void func_001684E8(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F0(a0, 8);
    __asm__ __volatile__("");
}
