#include "common.h"

typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoInit);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoSave);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoLoad);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoEmptyAreaSearch);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoBaseSet);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysBackStageProcess);
extern char D_0061D328[];
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void memcpy();

void func_001B6CA0(int *self, int n, int a2)
{
    if (n != 0) {
        memcpy(self[0] + self[1], n);
    }
    self[1] += a2;
    debug_StdPrintfDummy(D_0061D328, self[1]);
}
INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001B6CF8);
extern int *GetbufpGeneratorPacket(void);
extern int GetsizeGeneratorPacket(void);
extern int ReadGeneratorPacket();

void func_001B6D40(int *a0)
{
    int s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadGeneratorPacket();
}
INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001B6DA8);
extern int *GetBuffHintSaveInfo(void);
extern int GetSizeHintSaveInfo(void);
extern int ReadHintSaveInfo();

void func_001B6DF0(int *a0)
{
    int s1 = GetBuffHintSaveInfo();
    int s2 = GetSizeHintSaveInfo();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadHintSaveInfo();
}
INCLUDE_ASM("asm/nonmatchings/src/gamesys", func_001B6E58);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysCharacterInfoLoad);
extern char D_004DA980[];

void gamesysNObjInfoInit(void)
{
    int mask = 0xFFFF;
    char *p = D_004DA980;
    int i = 0x8B;
    p += 0xA80;
    do {
        *(short *)(p + 2) = 0;
        *(short *)(p + 4) = (short)mask;
        p += 0x40;
        i--;
    } while (i >= 0);
}
void gamesysObjInfoStageInitFlagCls(void)
{
    long long mask = -2LL;
    long long *p = (long long *)D_004DA980;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}
void gamesysObjInfoStageInitPosSaveUnlock(void)
{
    long long mask = -3LL;
    long long *p = (long long *)D_004DA980;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}
extern int *gamesysObjInfoBaseSet(int *self, int a1);

int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3)
{
    int *p = gamesysObjInfoBaseSet(self, a3);
    p[0xC] = a1;
    p[0xD] = a2;
    return p;
}
extern char D_002C1270[];
extern int stage_no;
extern int *gamesysObjInfoBaseSet__pn(int a0, int a3) __asm__("gamesysObjInfoBaseSet");

int *gamesysObjInfoUniqDataSet(int a0) {
    int *p;
    void (*fn)(int *, int);
    char *elem;
    int idx;

    p = gamesysObjInfoBaseSet__pn(a0, stage_no);
    idx = *(int *)((char *)a0 + 0xC);
    elem = D_002C1270 + idx * 0x64;
    fn = *(void (**)(int *, int))(elem + 0x3C);
    if (fn != 0) {
        fn(p + 12, a0);
    }
    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoPosNewStageSet);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoGet);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoCls);
extern unsigned short D_004DA9C0[];

int gamesysGirlStageGet(void)
{
    if (D_004DA9C0[1]) return D_004DA9C0[2];
    return 4;
}
extern void CopyVector(void *dst, void *src);
extern int D_0028FF00[4];

int gamesysGetGirlStageIDAndPosition(int a0)
{
    if (D_004DA9C0[1] != 0) {
        CopyVector(a0, (int *)((char *)D_004DA9C0 + 0x10));
        return D_004DA9C0[2];
    }
    CopyVector(a0, (int *)D_0028FF00);
    return 4;
}
extern int D_004DA7D0[];
extern int gamesysTimeCount;

void gamesysStageExitTimeSet(int a0) {
    D_004DA7D0[a0] = gamesysTimeCount;
}
void gamesysMemoryHandlerRead(int *self, int a1, int a2)
{
    if (a1 != 0) {
        memcpy(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
}
void gamesysMemorySave(int *self, int a1, int a2)
{
  func_001AE8F0_FnPtr new_var;
  int buf[2];
  int new_var2;
  func_001AE8F0_FnPtr fn;
  buf[0] = a1;
  buf[1] = 0;
  fn = (func_001AE8F0_FnPtr) self[1];
  new_var2 = fn != 0;
  if (new_var2)
  {
    do
    {
      fn(buf, a2);
      self += 2;
      new_var2 = self[1];
      new_var = (func_001AE8F0_FnPtr) new_var2;
      fn = new_var;
    }
    while (new_var2);
  }
}
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysMemoryLoad);
extern int D_004DA770[];
extern int gamesysVersionDiff;
extern int gamesysMemoryHandlerRead__pn(void *, void *, int) __asm__("gamesysMemoryHandlerRead");
extern int strcmp(int *p, int *buf);

void gamesysVersionLoad(int *self)
{
    int buf[8];
    gamesysMemoryHandlerRead__pn(self, buf, 0x12);
    if (strcmp(D_004DA770, buf) != 0) {
        gamesysVersionDiff = 1;
    } else {
        gamesysVersionDiff = 0;
    }
}
extern void func_001B6CA0__pn(int a, char *p, int n) __asm__("func_001B6CA0");
extern void memset(char *p, int a, int n);

void gamesysVersionSave(int a0)
{
    if (gamesysVersionDiff == 0) {
        func_001B6CA0__pn(a0, D_004DA770, 0x12);
        return;
    }
    {
        char buf[0x20];
        memset(buf, 0, 0x12);
        func_001B6CA0__pn(a0, buf, 0x12);
    }
}
