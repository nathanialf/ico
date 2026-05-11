
extern int D_0063314C;
extern int D_00633EC0;
extern int D_00633158;
extern int D_0063315C;
extern unsigned char D_005F2FB8[];
extern void func_001B5C38(int a, int b);
void func_001B7190(unsigned char idx)
{
  unsigned short new_var3;
  int *p = (int *) (((char *) D_005F2FB8) - (-(idx * 0x194)));
  unsigned int new_var2;
  int new_var6;
  int new_var;
  int new_a = D_0063314C - (-1);
  int new_var7;
  int new_var4;
  int *new_var5;
  new_var4 = p[0x134 / 4];
  new_var = new_var6;
  if (new_a >= new_var4)
  {
    new_var6 = p[0x130 / 4];
    new_a = new_var6;
    D_0063314C = new_a;
  }
  ;
  new_var4 = new_var;
  if (new_var4 == 0x3A)
  {
    {
      ;
      D_00633EC0 = new_var;
      func_001B5C38(0x3A, 0x3A);
    }
    new_var4 = (new_var7 = (unsigned long long) 1);
    D_00633158 = (new_var3 = (D_0063315C == new_var4) ? (5) : (3));
    new_var5 = &new_a;
    new_var7 = *new_var5;
    new_var2 = new_var7;
    return new_var2;
  }
}
