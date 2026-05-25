
extern void func_00243B70(int *p, int q, float t);
extern void func_00243B18(int *p, int *q, float t);
void func_001999A8(int *self, int a1, float t)
{
  int new_var3;
  float new_var2;
  int *new_var;
 do { new_var2 = t; new_var3 = 0x20; } while (0);
  new_var = self;
  func_00243B70(self, a1, t);
  new_var2 = t;
  func_00243B18(new_var, new_var, new_var2);
  func_00243B18(new_var + (0x10 / 4), new_var + (0x10 / 4), t);
  func_00243B18(new_var + (new_var3 / 4), new_var + (0x20 / 4), new_var2);
}
