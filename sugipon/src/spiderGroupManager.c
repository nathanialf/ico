#include "common.h"

int EntrySpiderGroupManager(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", tryToRevive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", ExecSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", InitSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", EntryRevivedSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", DispAllSpiderGroups);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", EntryToSpiderGroupManagerForReviveMaster);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", getReviveEnemyGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8638);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E86B0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E87F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E89E8);

extern int D_0062B8D8, D_0062B8DC, D_0062B8E0, D_0062B8E4;
extern int D_0062B8E8, D_0062B8EC, D_0062B8F0, D_0062B8F4;

void func_001E8C18(void) {
    D_0062B8DC = 0;
    D_0062B8E4 = 0;
    D_0062B8E0 = 0;
    D_0062B8EC = 0;
    D_0062B8D8 = 0;
    D_0062B8E8 = 0;
    D_0062B8F0 = 0;
    D_0062B8F4 = 0;
}

extern int D_00705F98[];

void func_001E8C40(int a0) {
    int i = D_0062B8DC;
    D_0062B8DC = i + 1;
    D_00705F98[i] = a0;
}

extern int D_002715D4[];
extern int D_0062B8D4;
extern int D_0062B8BC;
extern unsigned char D_004C21B0[];
extern void GetNearestOfLayoutSpiders(int p, unsigned char *q);

void func_001E8C68(void)
{
  int v = D_002715D4[0];
  D_0062B8D4 = 0;
  if (v & 0x1000)
  {
    D_0062B8BC = D_0062B8BC - 1;
  }
  if (v & 0x4000)
  {
    D_0062B8BC = D_0062B8BC + 1;
  }
  {
    int i;
    for (i = 0; i < D_0062B8DC; i++)
    {
      GetNearestOfLayoutSpiders(D_00705F98[i], &D_004C21B0[i * 0x10]);
    }

  }
}

extern int D_00706298[];

void func_001E8D10(int a0, int a1) {
    D_0062B8EC = a1;
    D_00706298[D_0062B8E4++] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8D38);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8D98);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8E38);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00706D00;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00705F98;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
} S_00706098;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00706298;  /* stride 0x4 */

/* end struct shapes */
