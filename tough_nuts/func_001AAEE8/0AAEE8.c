
extern char D_005D49E0[];
extern unsigned short D_002E7710[];
int func_001AAEE8(int idx)
{
  char *entry = D_005D49E0 - (-(idx * 0x3C));
  int new_var;
  int v3 = *((int *) (entry + 0x20));
  unsigned short a4 = *((unsigned short *) (((char *) D_002E7710) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}
