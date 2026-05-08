
extern volatile int func_0010F5B8(int a0, int a1, int a2);
void func_00168690(int *self, int a1)
{
  int new_var;
  int *p;
  func_0010F5B8((int) self, a1, 0);
  p = (int *) self[0];
  new_var = 0x14 / 4;
  p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
  p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}
