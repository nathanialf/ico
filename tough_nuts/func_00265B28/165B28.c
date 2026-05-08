
extern int func_0026AC40(int a0, int *a1);
int func_00265B28(int a0, int *a1)
{
  int new_var;
  int ret;
  if (a1[0x8 / 4] != 0)
  {
    new_var = 0x8 / 4;
    ret = func_0026AC40(a0, a1);
    a1[0x4 / 4] = 0;
    a1[new_var] = 0;
  }
  else
  {
    ret = 0;
    a1[0x4 / 4] = 0;
  }
  return ret;
}
