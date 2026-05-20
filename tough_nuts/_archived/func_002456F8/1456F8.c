
extern int D_00713000[];
int *func_002456F8(int a0)
{
  int *base = D_00713000;
  int *p = &base[4];
  base[1] = 0;
  base[0] = a0;
  base[2] = (base[3] = (int) p);
  if (1)
  {
    return base;
  }
}
