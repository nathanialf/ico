
extern int D_00631990;
extern char D_005F2FB8[];
extern char D_00561928[];
extern void func_001A0010(int val);
extern void func_001A0038(int val);
void func_0017C9B0(int idx)
{
  int new_var;
  char *p;
  char *q;
  int new_var2;
  short s;
  new_var = 0xA0;
  p = &D_005F2FB8[new_var];
  new_var = ((idx - 1) * 2) + (D_00631990 * 0x194);
  s = *((short *) (p + new_var));
  new_var2 = 0x28;
  ;
  q = &D_00561928[new_var];
  func_001A0010(*((int *) ((&D_00561928[s * new_var2]) + 0x24)));
  func_001A0038(1);
}
