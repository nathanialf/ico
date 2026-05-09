
extern void func_00105F00(int p, int q);
extern void func_001D12A8(int p, int q);
extern int D_00631AE8;
extern int D_0063330C;
extern int D_00633310;
extern int D_00633314;
extern int D_00633318;
extern float D_0063331C;
extern char D_004C09A0[];
void func_001CBD88(int a0, float t)
{
  int new_var;
  if (D_00631AE8 != 0)
  {
    func_001D12A8(D_00631AE8, 0x75);
    func_001D12A8(D_00631AE8, 0x76);
    func_001D12A8(D_00631AE8, 0x77);
    func_001D12A8(D_00631AE8, 0x78);
    func_001D12A8(D_00631AE8, 0x79);
  }
  new_var = 1;
  D_0063330C = (D_00633314 = new_var);
  D_00633318 = (D_00633310 = 0);
  func_00105F00((int) D_004C09A0, a0);
  D_0063331C = t;
}
