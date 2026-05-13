
extern int D_006325B4;
int func_0014B800(int *self)
{
  int *q;
  int new_var;
  int *p;
  p = (int *) self[0x59];
  new_var = p[0xC];
  if (new_var == 0x35)
  {
    return 1;
  }
  q = (int *) p[0x19E];
  if (q[0xE5] == 0)
  {
    return 0;
  }
  if (D_006325B4 == 0)
  {
    return 0;
  }
  new_var = 1;
  return new_var;
}
