
extern int D_00631990;
extern char D_005F2FB8[];
extern char D_00561928[];
extern void func_001A0010(int val);
extern void func_001A0038(int val);
void func_0017C9B0(int idx)
{
  char *p;
  char *q;
  short s;
  p = &D_005F2FB8[((idx - 1) * 2) + (D_00631990 * 0x194)];
  s = *((short *) (p + 0xA0));
  q = &D_00561928[s * 0x28];
  func_001A0010(*((int *) (q + 0x24)));
  func_001A0038(1);
}
