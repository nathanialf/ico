
extern void func_00163EB8(int *self, int a1, int a2, int a3, int t0);
extern void func_00163B40(int *self, int a1, int a2, int a3, int t0);
void func_00165FB8(int *self, int a1, int a2, int a3, int t0)
{
  int *p = (int *) ((int *) self[0x164 / 4])[0x670 / 4];
  int masked = t0 & 0xFF;
  if (p[0x1DC / 4] == 3)
  {
    if (1)
    {
      func_00163B40(self, a1, a2, a3, masked);
    }
  }
  else
  {
    p = &a3;
    func_00163EB8(self, a1, a2, *p, masked);
  }
}
