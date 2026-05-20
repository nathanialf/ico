
extern int *D_00633C30;
extern void func_00114FC8(int *p);
void func_00117768(void)
{
  int *s0 = D_00633C30;
  int *new_var2;
  int new_var;
  if (s0 == 0)
  {
    return;
  }
  do
  {
    short v1 = *((short *) (((char *) s0) + 0x44));
    new_var = v1 < 4;
    if ((v1 >= 2) && new_var)
    {
      func_00114FC8(new_var2);
      new_var2 = s0;
      do
      {
      }
      while (0);
    }
    s0 = (int *) s0[0x4C / 4];
  }
  while (s0 != 0);
}
