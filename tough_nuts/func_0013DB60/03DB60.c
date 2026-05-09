
extern int func_00100540(int x);
extern void func_001A6E28(char *p, int a);
extern char D_005579E0[];
int func_0013DB60(int *self)
{
  int v;
  int rv;
  v = func_00100540(self[0x30 / 4]);
  rv = 0;
  if (v < 0)
  {
    func_001A6E28(D_005579E0, self[0x30 / 4]);
    rv = v;
  }
  return rv;
}
