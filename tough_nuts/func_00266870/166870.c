
extern int func_0026AC40(int a0, int *a1);
int func_00266870(int a0, int *a1)
{
  int ret = 0;
  if (a1[0x8 / 4] != 0)
  {
    ret = func_0026AC40(a0, a1);
    a1[0x4 / 4] = 0;
    a1[0x8 / 4] = 0;
  }
  else
  {
    a1[0x4 / 4] = 0;
    return ret;
  }
}
