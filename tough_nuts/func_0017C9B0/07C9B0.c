
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
  short s;
  new_var = ((idx - 1) * 2) + (D_00631990 * 0x194);
  p = &D_005F2FB8[new_var];
  s = *((short *) (p + 0xA0));
  new_var = s * 0x28;
  q = &D_00561928[new_var];
  func_001A0010(*((int *) ((&D_00561928[new_var]) + 0x24)));
  func_001A0038(1);
}
