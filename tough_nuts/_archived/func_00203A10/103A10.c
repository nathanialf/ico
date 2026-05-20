
extern void func_0013FF88(int self, int a, int b);
int func_00203A10(int *self, volatile unsigned int a1, int a2)
{
  int *p = (int *) self[0x164 / 4];
  if (p[0x12C / 4] != 0)
  {
    return 0;
  }
  p[0x130 / 4] = a2;
  p[0x12C / 4] = (int) self;
  func_0013FF88((int) self, a2, a1);
  return 1;
}
