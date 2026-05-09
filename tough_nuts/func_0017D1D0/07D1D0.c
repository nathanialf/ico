
extern void func_00203AA0(int x);
extern void func_0017BB98(int *p);
extern unsigned char D_0028A640[];
void func_0017D1D0(volatile unsigned int self)
{
  volatile int local;
  unsigned char i;
  short *p = (short *) D_0028A640;
  func_00203AA0(0xA);
  for (i = 0; i < 7; i++)
  {
    if ((*p) == ((int *) self)[0x8 / 4])
    {
      i = self;
      func_0017BB98((int *) i);
      return;
    }
    p = (short *) (((char *) p) + 0x30);
  }

}
