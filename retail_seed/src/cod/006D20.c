#include "ico/types.h"

extern void func_00105F00(int a, int b);
extern void func_00105F90(int a, int b, int c);
void func_00106D20(int a0, int *a1)
{
  int *p = (int *)((GObj *)(a1))->p_15C;
  char *new_var;
  new_var = ((char *) p) + 0xA0;
  func_00105F00(a0, (int) (((char *) p) + 0x130));
  func_00105F90(a0, a0, (int) new_var);
}
