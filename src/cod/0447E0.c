
extern void func_00144500(int x);
extern void func_00140B70(int x);
extern void func_001412C8(int x);
extern unsigned char D_005F2FB8[];
void func_001447E0(int idx)
{
  short new_var;
  func_00144500(idx);
  func_00140B70(0);
  new_var = 0x18C;
  func_001412C8(*((unsigned short *) ((((char *) D_005F2FB8) + (idx * 0x194)) + new_var)));
}
