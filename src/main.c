#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/main", Emergency_DestroyAllThread);
extern int D_0028F8F4[];
extern int D_00639C80;
extern int D_00639C94;
extern void ExecKeyInput();

int movie_abort_check(void)
{
  int ret = 0;
  if (D_00639C94 != D_00639C80)
  {
    D_00639C94 = D_00639C80;
    ExecKeyInput();
    ret = 0;
    ret = (D_0028F8F4[0] & 0x800) != ret;
  }
  return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/main", demoEnd);
INCLUDE_ASM("asm/nonmatchings/src/main", main);
