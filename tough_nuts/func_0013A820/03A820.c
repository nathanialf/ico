
extern int D_00632108;
extern int D_00631950;
extern void func_00100F18(int a, int *b);
int func_0013A820(int a0)
{
  unsigned int new_var;
  new_var = 1;
  if (a0 == 2)
  {
    long long v = *((long long *) 0x12001000);
    int *p = (int *) D_00632108;
    D_00631950 = !((v >> 13) & new_var);
    func_00100F18(p[0x30 / 4], p);
  }
  return 0;
}
