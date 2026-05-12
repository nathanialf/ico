/* src/cod/038138.c — func_00138138 */

extern char D_00280F88[];
extern void func_0013A5B8(char *base, char *self, int z, int neg_two);

void func_00138138(char *self, int a1)
{
    *(int *)(self + 4) = 10;
    *(int *)(self + 0x48) = a1;
    *(long long *)self &= ~1LL;
    func_0013A5B8(D_00280F88, self, 0, ~1);
}
