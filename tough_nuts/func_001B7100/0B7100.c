
extern int D_0063314C;
extern int D_00633EC0;
extern int D_00633158;
extern int D_0063315C;
extern unsigned char D_005F2FB8[];
extern void func_001B5C38(int a, int b);
int func_001B7100(int idx)
{
  volatile int new_var3;
  int *new_var;
  int *p = (int *) (((char *) D_005F2FB8) + (101 * (2 * (idx * 2))));
  short new_var2;
  int new_a;
  if (new_a < ((int *) (((char *) D_005F2FB8) + (101 * (2 * (idx * 2)))))[0x130 / 4])
  {
    new_var = p;
    new_a = D_0063314C - 1;
    if (1)
    {
    }
    new_a = new_var[0x134 / 4] - 1;
    D_0063314C = new_var3;
  }
  new_var3 = new_a;
  if ((p[0x134 / 4] - 1) == 0x3A)
  {
    D_00633EC0 = 0x3A;
    func_001B5C38(0x3A, 0x3A);
    D_00633158 = (new_var2 = (D_0063315C == 1) ? (5) : (3));
    return new_var3;
  }
}
