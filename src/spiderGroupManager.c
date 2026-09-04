#include "common.h"






extern int isysGObjSearchFromObjKindID_next();
extern int isysGObjSearchFromObjLayoutID();
extern int D_0070C9C8[];
extern void func_001EA9C8();
extern unsigned char D_004C60C0[];
extern int D_00275254[];
extern int D_006335DC;
extern int D_006335F4;
extern int D_0070C6C8[];
extern int D_00633614;
extern int D_006335F8;
extern int D_0063360C;
extern int D_00633600;
extern int D_00633608;
extern int D_006335FC;
extern int D_00633610;
extern int D_00633604;
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", EntrySpiderGroupManager);

INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EB5C8);

INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", ExecSpiderGroupManager);

void InitSpiderGroupManager(void) {
    D_006335FC = 0;
    D_00633604 = 0;

    D_00633600 = 0;

    D_0063360C = 0;

    D_006335F8 = 0;

    D_00633608 = 0;

    D_00633610 = 0;
    D_00633614 = 0;
}

void EntryRevivedSpiderGroupManager(int a0)
{
    int idx = D_006335FC;
    D_006335FC = idx + 1;
    D_0070C6C8[idx] = a0;
}

void DispAllSpiderGroups(void)
{
  int v = D_00275254[0];
  D_006335F4 = 0;
  if (v & 0x1000)
  {
    D_006335DC = D_006335DC - 1;
  }
  if (v & 0x4000)
  {
    D_006335DC = D_006335DC + 1;
  }
  {
    int i;
    for (i = 0; i < D_006335FC; i++)
    {
      func_001EA9C8(D_0070C6C8[i], &D_004C60C0[i * 0x10]);
    }

  }
}

void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1)
{
  int idx = D_00633604;
  int *p;
  int new_var;
  int *new_var2;
  new_var2 = &a1;
  D_0063360C = *new_var2;
  p = D_0070C9C8 + idx;
  new_var = idx;
  idx = new_var + 1;
  *p = a0;
  D_00633604 = idx;
}

int *getReviveEnemyGObj(int count)
{
  int *p = isysGObjSearchFromObjLayoutID(4);
  int i;
  {
    for (i = 0; i < count; i++)
    {
      if (p == 0)
      {
        return 0;
      }
      p = isysGObjSearchFromObjKindID_next(p);
    }

  }
  return p;
}

INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EBB70);

INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EBC10);

