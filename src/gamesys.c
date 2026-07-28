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
extern char D_00632B48[];
extern char D_00632B50[];

void *gamesysObjInfoInit(int a0, void *a1) {
    if ((1 << a0) & *(long long *)((char *)a1 + 0x9C0)) {
        return D_00632B48;
    }
    return D_00632B50;
}

int gamesysObjInfoSave(void) {
    iosMcManager();
    return 1;
}

extern void staffRollMain(int a0, float a1);

int gamesysObjInfoLoad(void) {
    staffRollMain(0x80, 1.0f);
    return 1;
}

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

extern char D_0055F468[];
extern char D_00615770[];
extern int D_00632BDC;
extern int D_00632BE0;
extern int func_001A7848(void *, int, int, int, void *, int, int, int, int, int *);
extern void scpPlayStart(int, int, int, int, int);

int gamesysBackStageProcess(int a0) {
    int ret;
    if (a0 != 0) {
        D_00632BE0 = -1;
    }
    ret = func_001A7848(D_00615770, 0xA, 0x3C, 0xA, D_0055F468, 0x40, 0, 0, 0x60, &D_00632BDC);
    if (ret > 0 && D_00632BDC != 0) {
        scpPlayStart(D_00632BDC, 0, 1, 1, 1);
    }
    return ret;
}

extern char D_00615790[];
extern char D_006157A8[];
extern int D_00632BF8;
extern int D_00632BFC;
extern char D_006F8EE0[];
extern int func_001A76B8(void *a0, int a1, int a2, int a3, int a4, void *a5, void *a6, int a7);
extern void func_001A8D40();

int gamesysGeneratorInfoLoad(void) {
    long buf[3];
    int r;
    __builtin_memcpy((char *)buf, D_00615790, 0x14);
    if (D_00632BF8 != 0) {
        *(long *)((char *)buf + 0) = *(long *)(D_006157A8 + 0);
        *(long *)((char *)buf + 8) = *(long *)(D_006157A8 + 8);
        *(short *)((char *)buf + 0x10) = *(short *)(D_006157A8 + 0x10);
        *(char *)((char *)buf + 0x12) = *(char *)(D_006157A8 + 0x12);
    }
    r = func_001A76B8(buf, 0x50, 0x46, 0xA, 0x1A, &D_00632BFC, (void *)func_001A8D40, D_00632BF8);
    if (D_00275254[0] & 0x10) {
        int *row = (int *)(D_006F8EE0 + D_00632BF8 * 0xD0);
        int i;
        for (i = 0x19; i >= 0; i--) {
            row[1] = row[0];
            row += 2;
        }
    }
    return r;
}

int gamesysCharacterInfoLoad(void) {
    init_debug_menu();
    return -1;
}

int gamesysNObjInfoInit(void) {
    init_debug_menu();
    return -1;
}

extern float D_006310F4;
extern void backStageProcessInit(float a0);

int gamesysObjInfoStageInitFlagCls(void) {
    backStageProcessInit(D_006310F4);
    return 1;
}

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

extern void func_00241C48(void);
extern void func_00244658(int a0);
extern void func_00244ED0(int *a0, int a1, int a2);

void gamesysMemoryLoad(void) {
    func_00244658(1);
    func_00244ED0((int *)func_00244630(0), 0, 0x64);
    func_00244ED0((int *)func_00244630(1), 0, 0x64);
    func_00244ED0((int *)func_00244630(2), 0, 0x64);
    *(int *)func_00244630(0) |= 0x40;
    *(int *)func_00244630(1) |= 0x40;
    *(int *)func_00244630(2) |= 0x40;
    func_00241C48();
}

void gamesysVersionLoad(int a0)
{
    func_00244598(a0);
    gsb_antiAlias(D_00274EF0);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysCharacterInfoSave);

extern void gamesysMemoryHandlerRead(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern void gamesysMemoryHandlerWrite(int a0);

void gamesysGeneratorInfoSave(void)
{
    gamesysMemoryHandlerWrite(1);
    gamesysMemoryHandlerRead(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    gamesysMemoryHandlerWrite(1);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001AC348);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001AC438);

