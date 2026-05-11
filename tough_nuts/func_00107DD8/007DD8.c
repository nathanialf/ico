
extern void func_00168AE0(int a, int b, int c, int d, int t0);
extern void func_001182F0(int a, int b);
void func_00107DD8(int a0, int *a1, int *info)
{
  int *p;
  int v = ((int *) p[0x15C / 4])[0xC / 4];
  int *new_var;
  p = (int *) info[0];
  v = info[1] << 6;
  func_00168AE0(a0, (int) a1, info[2], ((int *) (*new_var))[0xC / 4] + v, (int) p);
  new_var = &p[0x15C / 4];
  a1[0x4 / 4] = 0;
  func_001182F0((int) a1, (int) a1);
}
