
extern unsigned int D_00633CA4;
extern char *D_00633CA0;
int func_0013E488(void)
{
  unsigned int count = D_00633CA4;
  int found = 0;
  unsigned int new_var2;
  char *new_var3;
  int new_var;
  new_var3 = D_00633CA0;
  new_var = 0;
  if (count != new_var)
  {
    char *base = new_var3;
    unsigned int i = new_var;
    do
    {
      int *p = (int *) (base + (new_var2 * 0x174));
      int next = found + 1;
      i++;
      if ((*p) != 0)
      {
        found = next;
      }
    }
    while ((new_var2 = i) < count);
  }
  return found;
}
