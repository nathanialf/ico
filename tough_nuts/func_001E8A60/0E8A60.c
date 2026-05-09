
extern void func_001E80D8(int x);
extern int D_007097F0[];
void func_001E8A60(void)
{
  int *p = D_007097F0;
  int *end = (int *) (((char *) D_007097F0) + 0xC00);
  int *new_var;
  while (p < new_var)
  {
    if ((*p) != 0)
    {
      func_001E80D8(p[0x14 / 4]);
    }
    new_var = end;
    p = (int *) (((char *) p) + 0x18);
  }

}
