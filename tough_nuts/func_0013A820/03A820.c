
extern int D_00632108;
extern int D_00631950;
extern void func_00100F18(int a, int *b);
int func_0013A820(int a0)
{
  unsigned int new_var;
  int new_var2;
  new_var = 1;
  if (a0 == 2)
  {
    long long v = *((long long *) (new_var2 = 0x12001000));
    int *p = (int *) D_00632108;
    if (1)
    {
      D_00631950 = !((v >> 13) & new_var);
    }
    func_00100F18(p[new_var2 / 4], p);
  }
  new_var2 = 0x30;
  return 0;
}
