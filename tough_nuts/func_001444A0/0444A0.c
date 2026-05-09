
extern void func_00140138(int *p);
extern unsigned char D_006A95B0[];
void func_001444A0(void)
{
  unsigned char *end = D_006A95B0 + 0x300;
  unsigned char *p = D_006A95B0;
  while (p < end)
  {
    if ((*((unsigned short *) (p + 2))) == 0x11)
    {
      func_00140138((int *) p);
    }
    p += 0x30;
  }

}
