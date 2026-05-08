
extern int *D_006A6F30[];
extern int func_00100410(void);
int func_0013D8A0(int *a0)
{
  int **new_var;
  if (a0 == 0)
  {
    int idx = func_00100410();
    a0 = new_var[idx];
  }
  return a0[0x18 / 4];
  new_var = D_006A6F30;
}
