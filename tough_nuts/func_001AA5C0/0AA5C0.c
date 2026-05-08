
extern int D_006F8EE0[];
void func_001AA5C0(int idx)
{
  int *p = (int *) ((((char *) D_006F8EE0) + (idx * 0xD0)) + 0xC8);
  int new_var;
  int i;
  for (i = 0x19; i >= 0; i--)
  {
    new_var = 0;
    p = (int *) (((char *) p) - 8);
    *p = new_var;
    p = (int *) (((char *) p) - 8);
  }

}
