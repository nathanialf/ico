
extern void func_0013EFD0(int *self, int a1, int a2);
void func_0013F1D0(int *self, int a1, int a2, int a3, unsigned char t0)
{
  char new_var;
  if (a1)
  {
    self[0x48 / 4] = a1;
    self[0x50 / 4] = t0;
    new_var = 0xFF;
    func_0013EFD0(self, a2 & new_var, a3);
  }
}
