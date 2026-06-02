#include "ico/types.h"

extern void func_00243978(int x);
extern void func_0015B780(int *self, int y, float t);
extern int D_00565060[];
void func_0017B398(int *self, int y)
{
  unsigned long long new_var2;
  int *p;
  int *q;
  unsigned long long new_var;
  int *new_var4;
  int new_var3;
  int idx;
  new_var3 = y;
  y++;
  y--;
  func_00243978(new_var3);
  new_var4 = (int *)((GObj *)(self))->p_15C;
  p = new_var4;
  idx = p[0x4A0 / 4];
  new_var2 = (new_var = 0x138);
  p = (int *) (new_var2 + (((char *) D_00565060) + (idx * 0x190)));
  q = p;
  func_0015B780(self, y, (float) (*q));
}
