
extern void func_001E80D8(int x);
extern int D_007097F0[];
void func_001E8A60(void)
{
  int *p = D_007097F0;
  int new_var2;
  int *end = (int *) (((char *) D_007097F0) + 0xC00);
  int *new_var;
 do { new_var2 = 0x18; } while (0);
  while (p < new_var)
  {
    if ((*p) != 0)
    {
      func_001E80D8(p[0x14 / 4]);
    }
    new_var = end;
    p = (int *) (((char *) p) + new_var2);
  }

}
