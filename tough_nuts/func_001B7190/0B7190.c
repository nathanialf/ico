
extern int D_0063314C;
extern int D_00633EC0;
extern int D_00633158;
extern int D_0063315C;
extern unsigned char D_005F2FB8[];
extern void func_001B5C38(int a, int b);
int func_001B7190(int idx)
{
  int *p = (int *) (((char *) D_005F2FB8) + (idx * 0x194));
  int new_a = D_0063314C + 1;
  if (new_a >= p[0x134 / 4])
  {
    new_a = p[0x130 / 4];
  }
  D_0063314C = new_a;
  if (new_a == 0x3A)
  {
    D_00633EC0 = 0x3A;
    func_001B5C38(0x3A, 0x3A);
    D_00633158 = (D_0063315C == 1) ? (5) : (3);
    return new_a;
  }
}
