
extern int D_00633E58;
extern int D_00632D54;
extern unsigned char D_006F1EE0[];
extern char D_00632AB0[];
extern void func_00264DF8(int *entry, char *p, int x, int y);
void func_001A9FE0(int a0, unsigned int a1, int a2, int a3)
{
  int idx = D_00633E58;
  int *entry = (int *) (((char *) D_006F1EE0) + (14 * (2 * idx)));
  if ((D_00632D54 != 0) && (idx != 0x400))
  {
    unsigned int mmio;
    func_00264DF8(entry, D_00632AB0, a0, a3);
    mmio = *((volatile unsigned int *) 0x10000000);
    idx = 24;
    D_00633E58 = idx + 1;
    ((unsigned char *) entry)[0xC] = a1 >> idx;
    ((unsigned char *) entry)[0xE] = a1 >> 8;
    do
    {
      ((unsigned char *) entry)[0xD] = a1 >> 16;
      ((unsigned char *) entry)[0xF] = a1;
      *((unsigned short *) (((char *) entry) + 0x14)) = (unsigned short) mmio;
    }
    while (0);
    entry[0x10 / 4] = a2;
    entry[0x18 / 4] = a3;
  }
}
