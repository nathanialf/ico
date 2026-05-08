
extern int D_006321D8;
extern void func_001FBFC8(int *s1, int *s0);
void func_001FC460(int *s1, int *s0)
{
  int new_var;
  func_001FBFC8(s1, s0);
  *(((unsigned char *) s1) + 0x40) = *(((unsigned char *) s0) + 0x40);
  s1[0x38 / 4] = (int) s0;
  new_var = s0[0x44 / 4];
  s1[0x34 / 4] = s0[0x34 / 4];
  s0[0x34 / 4] = (int) s1;
  s1[0x44 / 4] = new_var;
  if (s1[0x34 / 4] == 0)
  {
    D_006321D8 = (int) s1;
  }
}
