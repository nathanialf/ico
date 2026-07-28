
extern int D_00632008;
extern char D_00557A10[];
extern int D_00633CA0;
extern int D_00633CA4;
extern int *func_0013A0F8(volatile unsigned long a0, int a1, char *p, int line);
void func_0013E4D0(unsigned int count)
{
  int *p;
  unsigned int i;
  p = func_0013A0F8(D_00632008, count * 0x174, D_00557A10, 0xAE);
  D_00633CA4 = count;
  if (count != 0)
  {
    D_00633CA0 = (int) p;
    i = 0;
    do
    {
      p[0] = 0;
      i++;
      p[0x15C / 4] = 0;
      p[0x8 / 4] = -1;
      p[0x4 / 4] = -1;
      p = (int *) (((char *) p) + 0x174);
    }
    while (i < count);
  }
}
