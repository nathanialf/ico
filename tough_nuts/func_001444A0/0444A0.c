
extern void func_00140138(int *p);
extern unsigned char D_006A95B0[];
void func_001444A0(void)
{
  unsigned char *end;
  unsigned char *new_var;
  unsigned char *p = D_006A95B0;
  new_var = D_006A95B0 + 0x300;
  while (p < end)
  {
    end = p + 2;
    end = new_var;
    if ((*((unsigned short *) end)) == 0x11)
    {
      func_00140138((int *) p);
    }
    p += 0x30;
  }

}
