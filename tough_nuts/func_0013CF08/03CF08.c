
extern unsigned int *D_00632190;
int func_0013CF08(unsigned int idx, int val)
{
  int new_var;
  int *base = (int *) D_00632190;
  if (idx <= (((unsigned) base[0]) - 1))
  {
    ((int *) base[1])[idx] = val;
  }
  else
  {
    new_var = -1;
    idx = new_var;
  }
  return idx;
}
