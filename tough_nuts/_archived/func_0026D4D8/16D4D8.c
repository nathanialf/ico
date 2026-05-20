
extern int D_00633FF0;
extern int func_00245680(int *p, int *q);
int func_0026D4D8(int *self, int *x, int *y)
{
  int *new_var2;
  int new_var3;
  long long new_var;
  int ret;
  do
  {
    new_var = -1;
    ret = func_00245680(x, y);
    if (ret == ((short) new_var))
    {
      if ((*new_var2) != 0)
      {
        new_var3 = *new_var2;
        *self = new_var3;
      }
    }
    new_var2 = &D_00633FF0;
    return ret;
  }
  while (0);
  D_00633FF0 = 0;
}
