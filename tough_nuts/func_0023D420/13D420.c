
extern void func_0023D468(int *p);
extern int D_00633B60;
extern int D_005F3038[];
void func_0023D420(int idx)
{
  int *new_var2;
  int new_var;
  int *p;
  new_var = idx;
  if (idx == (-1))
  {
    p = &D_00633B60;
  }
  else
  {
    new_var2 = &new_var;
    p = (int *) (((char *) D_005F3038) + ((*new_var2) * 0x194));
  }
  func_0023D468(p);
}
