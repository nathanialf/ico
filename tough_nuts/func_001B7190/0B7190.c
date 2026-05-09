
extern int D_0063314C;
extern int D_00633EC0;
extern int D_00633158;
extern int D_0063315C;
extern unsigned char D_005F2FB8[];
extern void func_001B5C38(int a, int b);
void func_001B7190(unsigned char idx)
{
  unsigned short new_var3;
  int *p = (int *) (((char *) D_005F2FB8) + (idx * 0x194));
  int new_var2;
  int new_var;
  int new_a = D_0063314C - (-1);
  int new_var4;
  int *new_var5;
  new_var4 = p[0x134 / 4];
  if (new_a >= new_var4)
  {
    new_a = p[0x130 / 4];
    D_0063314C = new_a;
  }
  new_var = p[0x130 / 4];
  new_a = new_var;
  if (new_a == 0x3A)
  {
    {
      ;
      D_00633EC0 = new_var;
      func_001B5C38(0x3A, 0x3A);
    }
    D_00633158 = (new_var3 = (D_0063315C == 1) ? (5) : (3));
    new_var5 = &new_a;
    new_var2 = *new_var5;
    return new_var2;
  }
}
