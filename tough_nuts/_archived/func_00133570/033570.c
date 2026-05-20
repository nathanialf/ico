
extern int func_00131C90(int *p, int *self, int n);
int func_00133570(int *self, int max, int *p)
{
  unsigned int v = ((unsigned int) p[0x138 / 4]) - ((unsigned int) p[0x24 / 4]);
  int new_var3;
  int n;
  int **new_var2;
  int *new_var;
  unsigned long new_var4;
  new_var3 = (int) v;
  if (new_var3 < max)
  {
    n = v;
  }
  else
  {
    n = max;
  }
  new_var2 = &p;
  if (n != 0)
  {
    new_var4 = n;
    new_var = self;
    func_00131C90(*new_var2, new_var, new_var4);
  }
  return n;
}
