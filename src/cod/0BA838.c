#include "ico/types.h"

extern int func_001B9638(int *a0);
int func_001BA838(int *a0)
{
  int *p = (int *)((GObj *)(a0))->p_15C;
  int *s = (int *) p[0x800 / 4];
  int ret;
  ret = func_001B9638(a0);
  if (ret == (-1))
  {
    s[0x1C0 / 4] = 0;
    s[0x1C8 / 4] = (s[0x1C4 / 4] = 0);
    return 2;
  }
  return ret;
}
