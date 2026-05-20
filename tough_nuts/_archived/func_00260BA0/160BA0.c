
extern int D_00552F50[];
void func_00260BA0(void)
{
  int *p = (int *) D_00552F50[0];
  if ((*((int *) D_00552F50[0])) != 0)
  {
    do
    {
      void (*fn)(void) = (void (*)(void)) (*((int *) D_00552F50[0]));
      p++;
      D_00552F50[0] = (int) p;
      fn();
      p = (int *) D_00552F50[0];
    }
    while ((*p) != 0);
  }
}
