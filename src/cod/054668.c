
extern int D_00631AE4;
extern int D_006AAAE0[];
extern void func_001F3F58(int *self, int *d, int r);
void func_00154668(int *self)
{
  int new_var;
  int *d;
  int *p;
  d = (int *) D_00631AE4;
  if (0 == d)
  {
    return;
  }
  if (self == 0)
  {
    return;
  }
  new_var = 0x164;
  p = (int *) d[new_var / 4];
  func_001F3F58(self, d, 0x16);
  new_var = self[0x8 / 4];
  p[0x140 / 4] = (int) self;
  D_006AAAE0[0] = new_var;
}
