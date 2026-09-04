#include "common.h"









extern void gsb_antiAlias();
extern int D_00274EF0[];
extern void sceVpu0Reset();
extern int sceDmaGetChan(unsigned a0);
extern void sceDmaSend();
extern void sceGsSyncPath();
extern void sceVif1PkCloseDirectCode();
extern void sceVif1PkTerminate();
extern void sceVif1PkCloseGifTag();
extern void func_00245178();
extern int D_00275254[];
extern void CameraSetMode(int x);
extern void InitCharFileManager(void);
extern void init_debug_menu(void);
extern unsigned short D_002E7710[];
/* object-info table, stride 0x3C */
typedef struct { char _0[0x20]; int f_20; char _24[0x18]; } GsysObjInfo;
extern GsysObjInfo D_005D49E0[];
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

int debug_STAFFROLLTest(void) {
    staffRollMain(0x80, 1.0f);
    return 1;
}

int debug_SETest_color(int idx)
{
  int new_var;
  int v3 = D_005D49E0[idx].f_20;
  unsigned short a4 = *((unsigned short *) (((char *) D_002E7710) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", debug_reverbTest);

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
extern int debug_SelectCsvWindowVal(void *a0, int a1, int a2, int a3, int a4, void *a5, void *a6, int a7);
extern void func_001A8D40();

int debugCdvdLoadInfoSegDisp(void) {
    long buf[3];
    int r;
    __builtin_memcpy((char *)buf, D_00615790, 0x14);
    if (D_00632BF8 != 0) {
        *(long *)((char *)buf + 0) = *(long *)(D_006157A8 + 0);
        *(long *)((char *)buf + 8) = *(long *)(D_006157A8 + 8);
        *(short *)((char *)buf + 0x10) = *(short *)(D_006157A8 + 0x10);
        *(char *)((char *)buf + 0x12) = *(char *)(D_006157A8 + 0x12);
    }
    r = debug_SelectCsvWindowVal(buf, 0x50, 0x46, 0xA, 0x1A, &D_00632BFC, (void *)func_001A8D40, D_00632BF8);
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

extern void backStageProcessInit(float a0);

int debug_BackStageTest(void) {
    backStageProcessInit(10000000.0f);
    return 1;
}

int gamesysObjInfoStageInitPosSaveUnlock(void) {
    InitCharFileManager();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", debug_SelectPad2ControlGobj);

int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_00275254[0] & 0x100) ? -1 : 0;
}

void CloseVif1DirectPacket(int a0)
{
    sceVif1PkCloseGifTag(a0);
    sceVif1PkCloseDirectCode(a0);
    func_00245178(a0, 0);
    sceVif1PkTerminate(a0);
}

void SendVif1DirectPacket(int *self)
{
    int *p;
    sceGsSyncPath(0, 0);
    p = sceDmaGetChan(1);
    *p |= 0x40;
    sceDmaSend(p, (self[0x4/4] & 0x3FF0) | 0x80000000);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", RestoreNormalDrawEnvironment);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", SetTextureWithFrameBuffer);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", SetTexDrawEnvironment);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", SetDrawnTextureEnvironment);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", SetDrawEnvironment);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", drawSprite);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", PutFont);

extern void sceGsResetPath(void);
extern void sceDmaReset(int a0);
extern void sceDmaSync(int *a0, int a1, int a2);

void resetPath(void) {
    sceDmaReset(1);
    sceDmaSync((int *)sceDmaGetChan(0), 0, 0x64);
    sceDmaSync((int *)sceDmaGetChan(1), 0, 0x64);
    sceDmaSync((int *)sceDmaGetChan(2), 0, 0x64);
    *(int *)sceDmaGetChan(0) |= 0x40;
    *(int *)sceDmaGetChan(1) |= 0x40;
    *(int *)sceDmaGetChan(2) |= 0x40;
    sceGsResetPath();
}

void gamesysVersionLoad(int a0)
{
    sceVpu0Reset(a0);
    gsb_antiAlias(D_00274EF0);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", drawWin);
ASM_LIT4_SLOT(D_006310F8, 0.8f);

extern void drawSprite(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern void SetDrawEnvironment(int a0);

void saveBack(void)
{
    SetDrawEnvironment(1);
    drawSprite(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    SetDrawEnvironment(1);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", baseFunc);

INCLUDE_ASM("asm/nonmatchings/src/gamesys", syncGS);

