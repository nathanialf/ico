
extern int D_006AA4B0[];
unsigned int func_0014AF70(int unused, int target)
{
  int *new_var;
  int count = D_006AA4B0[0x12C];
  char *new_var2;
  int i;
  int *cur;
  if (count <= 0)
  {
    i = 0;
    return 0;
  }
  cur = D_006AA4B0;
  do
  {
    new_var = &(*cur);
    if ((*new_var) == target)
    {
      do
      {
        i++;
        new_var2 = (char *) cur;
        new_var2 = new_var2 + 0x190;
        return *((unsigned char *) new_var2);
      }
      while (0);
    }
    i++;
    cur++;
  }
  while (i < count);
  return 0;
}
