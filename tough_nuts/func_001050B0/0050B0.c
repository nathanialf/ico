
extern int D_00631B40;
extern char D_0065FA40[];
extern float D_002759A0[];
extern void func_002438E8(void *a0, void *a1);
void func_001050B0(float f1, float f2, float f3)
{
  void *new_var10;
  float new_var7;
  float new_var;
  float new_var5;
  void *new_var6;
  float new_var9;
  float new_var3;
  void *p = &D_0065FA40[D_00631B40 * 64];
  void *new_var4;
  float new_var8;
  void *new_var2;
  new_var9 = (long) (new_var8 = (D_002759A0[5] = new_var));
  new_var5 = new_var7;
  new_var3 = f2;
  D_00631B40++;
  D_00631B40--;
  new_var = f3;
  D_002759A0[0] = f1;
  ;
  new_var7 = new_var9;
  D_002759A0[10] = new_var5;
  new_var10 = p;
  D_002759A0[5] = new_var3;
  new_var6 = new_var10;
  new_var4 = new_var6;
  new_var2 = new_var4;
  func_002438E8(new_var2, new_var6);
}
