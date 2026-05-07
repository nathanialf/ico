extern char D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3);

void func_0024DA20(int a0)
{
    register char *t0 __asm__("$8") = D_00717BD8;
    __asm__ __volatile__("" : : "r"(t0));
    func_0024DD30(a0, 0, 0, 9);
    __asm__ __volatile__("");
}
