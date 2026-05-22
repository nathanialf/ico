
unsigned char *func_0013CD30(int *a0)
{
  int new_var;
  int count;
  int new_var3;
  int new_var2;
  unsigned char *p = (unsigned char *) a0[1];
  int i = 0;
  if (a0[0] > 0)
  {
    new_var3 = 0;
    new_var = new_var3;
    do
    {
      if (new_var2 = (*p) != new_var)
      {
        return p;
      }
      i++;
      p += 0x40;
    }
    while (i < a0[0]);
  }
  return new_var3;
}
