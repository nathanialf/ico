
extern int func_002450C8(int *self, int a1);
void func_00245120(int *self, int a1)
{
  int v0;
  int *new_var;
  int *p;
  int *q;
  int new_var2;
  v0 = func_002450C8(self, a1);
  q = (int *) self[0];
  p = q;
  new_var = &v0;
  self[2] = *new_var;
  p[0] = (new_var2 = a1 | 0x10000000);
  q = p + 1;
  self[3] = 0;
  self[0] = (int) (q + 1);
  *q = 0;
}
