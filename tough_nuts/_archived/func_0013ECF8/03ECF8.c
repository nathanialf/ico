
extern int D_00633CA0;
extern int D_00633CA4;
void *func_0013ECF8(char *a0)
{
  int new_var;
  char *end = (((char *) D_00633CA0) + (D_00633CA4 * 0x174)) - 0x174;
  new_var = 0x174;
  if (a0 == end)
  {
    return 0;
  }
  a0 += new_var;
  new_var = *((int *) a0);
  {
    if (new_var != 0)
    {
      return a0;
    }
    if (a0 == end)
    {
      return 0;
    }
    a0 += new_var;
  }
}
