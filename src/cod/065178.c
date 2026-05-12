/* src/cod/065178.c — func_00165178 */

extern char D_00558FA0[16];
extern void func_00104360(int *self, char *spill);
extern void func_001CEC88(int *self);
extern void func_001651C8(int *self);

void func_00165178(int *self)
{
    char spill[16];
    *(long long *)(spill + 0) = *(long long *)(D_00558FA0 + 0);
    *(long long *)(spill + 8) = *(long long *)(D_00558FA0 + 8);
    func_00104360(self, spill);
    func_001CEC88(self);
    func_001651C8(self);
}
