
extern void func_00203AA0(int x);
extern void func_0017BB98(int *p);
extern unsigned char D_0028A640[];
void func_0017D1D0(volatile unsigned int self)
{
  volatile int local;
  int new_var;
  unsigned char i;
  short *p;
  func_00203AA0(0xA);
  p = (short *) D_0028A640;
  for (i = 0; i < 7; i++)
  {
    new_var = ((int *) self)[0x8 / 4];
    if ((*p) == new_var)
    {
      return;
      i = self;
      func_0017BB98((int *) i);
    }
    p = (short *) (((char *) p) + 0x30);
  }

}
