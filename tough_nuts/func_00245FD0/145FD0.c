
extern int *func_00245EA8(int x);
extern void func_0024BD90(int magic, int *p, int sz, int v3, int v4, int v5);
void func_00245FD0(int *self, int a1)
{
  int *p;
  int new_var;
  p = func_00245EA8(a1);
  new_var = self[0x24 / 4];
  p[0x14 / 4] = self[0x14 / 4];
  p[0x1C / 4] = self[0x1C / 4];
  p[0x20 / 4] = 0x8000000C;
  func_0024BD90(0x80000008, p, 0x40, self[0x20 / 4], new_var, self[0x28 / 4]);
}
