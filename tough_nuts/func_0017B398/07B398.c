
extern void func_00243978(int x);
extern void func_0015B780(int *self, int y, float t);
extern int D_00565060[];
void func_0017B398(int *self, int y)
{
  int *p;
  unsigned long long new_var;
  int idx;
  int *q;
  func_00243978(y);
  p = (int *) self[0x15C / 4];
  idx = p[0x4A0 / 4];
  new_var = 0x138;
  q = (int *) ((((char *) D_00565060) + (idx * 0x190)) + new_var);
  func_0015B780(self, y, (float) (*q));
}
