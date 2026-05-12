
unsigned char *func_0013CD30(int *a0)
{
  int new_var;
  int count = a0[0];
  int i = 0;
  if (count > 0)
  {
    unsigned char *p = (unsigned char *) a0[1];
    new_var = 0;
    do
    {
      if ((*p) != new_var)
      {
        return p;
      }
      i++;
      p += 0x40;
    }
    while (i < count);
  }
  return 0;
}
