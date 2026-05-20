
extern void func_00100560(int x);
extern void func_00100540(int x);
void func_00240600(int *self)
{
  int v;
  unsigned long new_var;
  int rounded;
  func_00100560(self[0x40 / 4]);
  v = self[0x14 / 4];
  if ((v + 0x7FF) >= 0)
  {
    new_var = v;
    rounded = ((new_var + 0x7FF) >> 11) << 11;
  }
  else
  {
    ;
  }
  self[0x14 / 4] = ((v + 0xFFE) >> 11) << 11;
  func_00100540(self[0x40 / 4]);
}
