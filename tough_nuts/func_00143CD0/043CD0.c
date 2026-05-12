
extern int D_006A95B0[];
int *func_00143CD0(int *target_ptr)
{
  int target = *target_ptr;
  int *new_var4;
  char *p;
  char *new_var2;
  char *q = (char *) D_006A95B0;
  int *new_var3;
  char *end = 0x300 + ((char *) D_006A95B0);
  int *new_var;
  new_var2 = p;
  while (new_var2 < (new_var4 = end))
  {
    new_var = (int *) p;
    if ((*new_var) == target)
    {
      new_var3 = new_var4;
      new_var4 = (int *) p;
      return new_var3;
    }
    p = p + 0x30;
    q += 0x30;
  }

  return 0;
}
