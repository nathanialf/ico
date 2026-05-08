
extern char D_00557AB0[];
extern char D_00557AC0[];
extern void func_001A6E28(char *p);
extern void func_0013EE60(int *self, int x, int y);
void func_0013F130(int *self, int *p, int q, int r, int t0)
{
  int new_var;
  new_var = q & 0xFF;
  func_001A6E28(D_00557AB0);
  if (p != 0)
  {
    self[0x48 / 4] = (int) p;
    self[0x50 / 4] = t0;
    func_0013EE60(self, new_var, r);
    func_001A6E28(D_00557AC0);
  }
}
