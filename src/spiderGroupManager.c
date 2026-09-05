#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int *getReviveEnemyGObj(int count);
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int *getReviveEnemyGObj(int count);
extern int D_0063BAE0;
extern int D_0063BAE4;
extern int D_0063BAE8;
extern int D_0063BAEC;
extern int D_0063BAF0;
extern int D_0063BAF4;
extern int D_0063BAF8;
extern int D_0063BAFC;
extern int D_00723C98[];
extern int D_0028F8F4[];
extern unsigned char D_004ECFB0[];
extern int D_0063BAC4;
extern int D_0063BADC;
extern void DispAllMemberOfSpider();
extern int D_00723F98[];
extern int isysGObjSearchFromObjKindID_begin();
extern int isysGObjSearchFromObjKindID_next();
inline void InitSpiderGroupManager(void) {
    D_0063BAE4 = 0;
    D_0063BAEC = 0;

    D_0063BAE8 = 0;

    D_0063BAF4 = 0;

    D_0063BAE0 = 0;

    D_0063BAF0 = 0;

    D_0063BAF8 = 0;
    D_0063BAFC = 0;
}
inline int *getReviveEnemyGObj(int count)
{
  int *p = isysGObjSearchFromObjKindID_begin(4);
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
inline void EntryRevivedSpiderGroupManager(int a0)
{
    int idx = D_0063BAE4;
    D_0063BAE4 = idx + 1;
    D_00723C98[idx] = a0;
}
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", EntrySpiderGroupManager);
inline void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1)
{
  int idx = D_0063BAEC;
  int *p;
  int new_var;
  int *new_var2;
  new_var2 = &a1;
  D_0063BAF4 = *new_var2;
  p = D_00723F98 + idx;
  new_var = idx;
  idx = new_var + 1;
  *p = a0;
  D_0063BAEC = idx;
}
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", tryToRevive);
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", ExecSpiderGroupManager);
inline void DispAllSpiderGroups(void)
{
  int v = D_0028F8F4[0];
  D_0063BADC = 0;
  if (v & 0x1000)
  {
    D_0063BAC4 = D_0063BAC4 - 1;
  }
  if (v & 0x4000)
  {
    D_0063BAC4 = D_0063BAC4 + 1;
  }
  {
    int i;
    for (i = 0; i < D_0063BAE4; i++)
    {
      DispAllMemberOfSpider(D_00723C98[i], &D_004ECFB0[i * 0x10]);
    }

  }
}
