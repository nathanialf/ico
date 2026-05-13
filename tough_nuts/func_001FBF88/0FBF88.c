
extern int D_00633828;
extern char D_00710FA0[];
int func_001FBF88(int a0, int a1)
{
  if (a0 < 0)
  {
    return 0;
  }
  if (a0 >= D_00633828)
  {
    return 0;
  }
  return *((int *) ((&D_00710FA0[(short) (a0 * 0x6C)]) + (a1 * 4)));
}
