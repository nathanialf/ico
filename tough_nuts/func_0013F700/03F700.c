
extern int D_00632008;
extern char D_00557AD0[];
extern int D_00633CA8;
extern int D_00633CAC;
extern int *func_0013A0F8(int a0, int a1, char *p, int line);
void func_0013F700(unsigned int count)
{
  unsigned int *new_var;
  int *p;
  unsigned int i;
  p = func_0013A0F8(D_00632008, count * 0x94, D_00557AD0, 0x49);
  D_00633CAC = count;
  D_00633CA8 = (int) p;
  if (count != 0)
  {
    i = 0;
    do
    {
      *((int *) (((char *) p) + ((*(new_var = &i)) * 0x94))) = 0;
      i++;
    }
    while (i < count);
  }
}
