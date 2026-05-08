
extern void func_0013EFD0(int *self, int a1, int a2);
void func_0013F1D0(int *self, int a1, int a2, int a3, int t0)
{
  int new_var;
  int new_var2;
  new_var2 = a2 & 0xFF;
  if (a1)
  {
    self[0x48 / 4] = a1;
    self[0x50 / 4] = t0;
    func_0013EFD0(self, new_var = new_var2, a3);
  }
}
