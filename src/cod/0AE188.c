
extern unsigned short D_004B3D10[];
extern int D_00632F74;
extern short D_00632F78;
extern void func_001A05D0(void);
void func_001AE188(void)
{
  char *new_var2;
  unsigned short *new_var;
  new_var2 = (char *) D_004B3D10;
  new_var = (unsigned short *) (new_var2 + 0x42);
  if ((*new_var) == 0x83)
  {
    D_00632F78 = (short) (*((unsigned short *) (new_var2 + 0x44)));
  }
  D_00632F74 += 1;
  func_001A05D0();
}
