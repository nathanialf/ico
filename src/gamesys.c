#include "common.h"









extern void gsb_antiAlias();
extern int D_00274EF0[];
extern void func_00244598();
extern int func_00244630(unsigned a0);
extern void func_00244980();
extern void func_00242640();
extern void func_00245228();
extern void func_002450C8();
extern void func_00245270();
extern void func_00245178();
extern int D_00275254[];
extern void func_0018CC00(int x);
extern void InitCharFileManager(void);
extern void init_debug_menu(void);
extern unsigned short D_002E7710[];
extern char D_005D49E0[];
extern void iosMcManager(void);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoInit);

int gamesysObjInfoSave(void) {
    iosMcManager();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoLoad);

int gamesysObjInfoEmptyAreaSearch(int idx)
{
  char *entry = D_005D49E0 - (-(idx * 0x3C));
  int new_var;
  int v3 = *((int *) (entry + 0x20));
  unsigned short a4 = *((unsigned short *) (((char *) D_002E7710) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoBaseSet);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysBackStageProcess);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysGeneratorInfoLoad);

int gamesysCharacterInfoLoad(void) {
    init_debug_menu();
    return -1;
}

int gamesysNObjInfoInit(void) {
    init_debug_menu();
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoStageInitFlagCls);

int gamesysObjInfoStageInitPosSaveUnlock(void) {
    InitCharFileManager();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoPosSetStage);

int gamesysObjInfoUniqDataSet(int a0)
{
    if (a0 != 0) {
        func_0018CC00(1);
    }
    func_0018CC00(1);
    return (D_00275254[0] & 0x100) ? -1 : 0;
}

void gamesysObjInfoPosNewStageSet(int a0)
{
    func_00245270(a0);
    func_00245228(a0);
    func_00245178(a0, 0);
    func_002450C8(a0);
}

void gamesysObjInfoGet(int *self)
{
    int *p;
    func_00242640(0, 0);
    p = func_00244630(1);
    *p |= 0x40;
    func_00244980(p, (self[0x4/4] & 0x3FF0) | 0x80000000);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoCls);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysGirlStageGet);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysGetGirlStageIDAndPosition);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysStageExitTimeSet);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysMemoryHandlerWrite);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysMemoryHandlerRead);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysMemorySave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysMemoryLoad);

void gamesysVersionLoad(int a0)
{
    func_00244598(a0);
    gsb_antiAlias(D_00274EF0);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysCharacterInfoSave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysGeneratorInfoSave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001AC348);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001AC438);

