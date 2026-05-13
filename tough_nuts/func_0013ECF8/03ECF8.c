
extern int D_00633CA0;
extern int D_00633CA4;
void *func_0013ECF8(char *a0)
{
  char *end = (((char *) D_00633CA0) + (D_00633CA4 * 0x174)) - 0x174;
  if (end == a0)
  {
    return 0;
  }
  a0 += 0x174;
  do
  {
    if ((*((int *) a0)) != 0)
    {
      return a0;
    }
    if (a0 == end)
    {
      return 0;
    }
    a0 += 0x174;
  }
  while (1);
}
