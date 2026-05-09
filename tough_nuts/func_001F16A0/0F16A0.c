
extern int func_0013A0F8(int a0, int a1, char *p, int line);
extern int func_00264D60(void);
extern int D_00632010;
extern char D_0061A6D8[];
short *func_001F16A0(void)
{
  short *p;
  int v;
  p = (short *) func_0013A0F8(D_00632010, 2, D_0061A6D8, 0xC);
  v = func_00264D60();
  if (v < 0)
  {
    v = v + 0xFFFF;
    *p = v;
  }
  return p;
}
