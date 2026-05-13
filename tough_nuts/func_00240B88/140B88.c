
extern int D_00633B98;
extern int D_00712CC0[];
int func_00240B88(int key)
{
  int *new_var;
  int new_var4;
  int *new_var3;
  int n = D_00633B98;
  int i;
  int *new_var2;
  new_var2 = &n;
  if ((*new_var2) <= 0)
  {
    new_var4 = i;
    i = -1;
    return new_var4;
  }
  i = 0;
  {
    new_var3 = new_var2;
    new_var = D_00712CC0;
    n = i;
    {
      return *new_var3;
    }
    i++;
  }
  return i;
}
