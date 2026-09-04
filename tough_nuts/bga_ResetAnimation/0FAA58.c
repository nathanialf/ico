
extern int D_00274ED4[];
extern int D_00633F64;
extern int D_006337BC;
extern void func_001F6D90(void *p);
void bga_ResetAnimation(void)
{
  int *p;
  D_00633F64 = 0;
  if (D_00274ED4[0] != 0)
  {
    return;
  }
  p = (int *) D_006337BC;
  if (p == 0)
  {
    return;
  }
  do
  {
    D_006337BC = 0;
    func_001F6D90(p);
    if (1)
    {
    }
    p = *((int **) (((char *) p) + 0x154));
  }
  while (p != 0);
}
