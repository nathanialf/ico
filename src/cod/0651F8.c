
extern int *D_00631AE8;
extern void func_0013FF88(int *p, int a, int b);
extern void func_00149EA8(int *p);
extern void func_0017B288(int a);
extern void func_001919A0(int *self, int a);
void func_001651F8(volatile int self_arg)
{
  register int *D asm("$3") = D_00631AE8;
  int new_var2;
  int *sub = (int *) ((int *) self_arg)[0x59];
  int *new_var;
  sub[0x4E] = (int) D;
  new_var2 = 0x4E;
  new_var = &sub[new_var2];
  func_0013FF88(D_00631AE8, 0x30, self_arg);
  new_var2 = *new_var;
  ((int *) ((int *) sub[0x4E])[0x57])[0x1D] = 1;
  func_00149EA8((int *) new_var2);
  func_0017B288(0x168);
  sub[0x4E] = 0;
  if (sub[0xC] == 5)
  {
    func_001919A0((int *) self_arg, 4);
  }
  asm __volatile__("" : : : "memory");
}
