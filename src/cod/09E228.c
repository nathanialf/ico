/* src/cod/09E228.c — func_0019E228 */

extern void func_0023FB20(int a0);
extern void func_0019E4F8(int a0);
extern void func_0019DF38(int a0, int a1, int a2);

void func_0019E228(int *self)
{
    func_0023FB20(self[0] + 0x50);
    func_0019E4F8(self[2]);
    func_0019DF38(self[0], self[1], self[2]);
    *(int *)(self[0] + 0xB8) = 3;
}
