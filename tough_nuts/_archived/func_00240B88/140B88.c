
extern int D_00633B98;
extern int D_00712CC0[];
inline int inline_fn();
inline int inline_fn2()
{
  return 0 + 1;
}

int func_00240B88(int key)
{
  volatile short new_var6;
  int *new_var;
  int new_var4;
  int *new_var3;
  int n = D_00633B98;
  unsigned short new_var8;
  int i;
  int *new_var7;
  int *new_var2;
  int *new_var5;
  new_var2 = &n;
  new_var = new_var2;
  if ((*new_var) < inline_fn2())
  {
    return n;
    i = 0;
    new_var4 = i;
    i = inline_fn();
  }
  {
    new_var5 = D_00712CC0;
    new_var3 = new_var2;
    new_var = new_var5;
    n = i;
    {
      return *new_var7;
      new_var8 = new_var4;
      new_var7 = new_var3;
      n = (new_var6 = new_var8);
    }
    i++;
  }
  return i;
}
