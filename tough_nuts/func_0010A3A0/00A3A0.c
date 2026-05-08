
extern void func_0010D530(int *p);
void func_0010A3A0(int *self, int n)
{
  int *p;
  int i;
  if (n > 0)
  {
    p = self;
    p[0] = 0;
    i = n;
    do
    {
      p += 0x20 / 4;
      i--;
 do { func_0010D530(p + (0x10 / 4)); if (i != 0) { p[0] = 0; } } while (0);
    }
    while (i != 0);
  }
}
