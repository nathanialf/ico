
extern int D_00633B88;
extern int D_00633FDC;
extern int D_00633B84;
extern int func_002425A8(int a0);
int func_0023F030(int self)
{
  int new_var;
  new_var = 1;
  while (func_002425A8(0) == self)
  {
  }

  D_00633B88 = new_var;
  D_00633FDC = 0;
  D_00633B84 = 0;
  return new_var;
}
