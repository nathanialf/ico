
extern int *func_0014A6B8(int a0);
int func_0017E620(int a0, int b)
{
  int new_var;
  int *p = func_0014A6B8(a0);
  if (p == 0)
  {
    return 0;
  }
  new_var = 4;
  return p[0x8 / new_var] == b;
}
