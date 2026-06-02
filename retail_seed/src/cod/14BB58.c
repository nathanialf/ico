extern int D_005508F8[];
extern int D_00717754[];
extern long func_00100AD8(int a0);
extern int func_00100250(int a0, int a1);
void func_0024BB58(void)
{
    func_00100AD8(5);
    {
        register int *v1 asm("$3") = D_00717754;
        register int a1_val asm("$5") = *v1;
        func_00100250(5, a1_val);
    }
    D_005508F8[0] = 0;
}
