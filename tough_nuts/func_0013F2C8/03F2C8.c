
extern int D_00281AB0[];
extern int D_00281AD0[];
void func_0013F2C8(void)
{
  int *p1 = D_00281AB0;
  int **new_var2;
  int *p2;
  int **new_var;
  int i = 7;
  do
  {
    new_var2 = &p2;
    *p1 = (*(*(new_var = new_var2)) = 0);
    i--;
    p1++;
    p2 = D_00281AD0;
    do
    {
    }
    while (0);
    p2++;
  }
  while (i >= 0);
}
