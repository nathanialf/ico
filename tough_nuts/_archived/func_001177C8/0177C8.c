
extern int *D_00633C34;
extern void func_00115068(int *p);
void func_001177C8(void)
{
  int new_var;
  int *s0 = D_00633C34;
  if (s0 == 0)
  {
    return;
  }
  do
  {
    int v1 = s0[0x90 / 4];
    new_var = v1;
    if ((new_var >= 0) && (v1 < 3))
    {
      func_00115068(D_00633C34);
    }
    s0 = (int *) s0[0x98 / 4];
  }
  while (s0 != 0);
}
