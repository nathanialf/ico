#include "common.h"

typedef struct { int x, y, w, h; } FR;

typedef struct { char _0[0x20]; int f_20; char _24[0x18]; } GsysObjInfo;

INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Assert);
extern int D_0063AE84;

void debug_openLog(void) {
    volatile char buf[256];
    D_0063AE84 = -1;

}
extern void sceWrite();
extern int strlen();
extern void vsprintf();

void debug_LogPrintf(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = strlen(buf);
    sceWrite(D_0063AE84, buf, info);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SaveDebugOptionFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_GetDebugOption);
extern int AddDmacHandler();
extern unsigned int D_0063AE8C;
extern void EnableDmac();
extern void RemoveDmacHandler();
extern int debug_CallbackGsFinish();

void debug_SetDmaCallback(void)
{
    if ((int)D_0063AE8C != -1) {
        RemoveDmacHandler(1, D_0063AE8C);
    }
    D_0063AE8C = AddDmacHandler(1, (int)debug_CallbackGsFinish, -1);
    EnableDmac(1);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_VariableInit);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Init);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Load);
ASM_LIT4_SLOT(D_00639338, 10059776.0f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeFont);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_makeBackImage);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintCharacter);
extern int D_0063AEB0;
extern int D_0063B13C;
extern void debug_PrintCharacter(char *str, int x, int y, int r, int g, int b, int sz);
extern int gif_CheckOpen(void);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_Sprite(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_StartPacketPri(int a0);

void debug_PrintFont(int a0, int a1, int a2, char *a3) {
    FR buf[2];
    int r;

    buf[1].x = a0 - 0x142;
    buf[1].y = a1 - 0x71;
    r = strlen(a3);
    buf[1].h = 9;
    buf[1].w = r * 0xC + 4;
    buf[0] = buf[1];

    if (gif_CheckOpen() != 0) {
        return;
    }
    if (D_0063B13C & 2) {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_Sprite(&buf[0], 0xFFFFFFFDU, 0, &D_0063AEB0, 1);
        gif_EndPacket();
    } else {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_EndPacket();
    }
    debug_PrintCharacter(a3, a0, a1, (unsigned) a2 >> 24, ((unsigned) a2 >> 16) & 0xFF, ((unsigned) a2 >> 8) & 0xFF, 0x70);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFontWindow);
extern void debug_FlushFontWindow(void);

void debug_FlushFont(void) {
    debug_FlushFontWindow();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_batsu);
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_shikaku);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_brainBar);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeBarString);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DrawBar);
ASM_LIT4_SLOT(D_0063933C, 270000.0f);
ASM_LIT4_SLOT(D_00639340, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBar);
ASM_LIT4_SLOT(D_00639344, 270000.0f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_ResizeSnapShot);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_WriteBMP);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SnapShot);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispQW);
extern void debug_PrintFont();

void debug_Printf(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
void debug_Printf2(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontWindow);
void debug_PrintfDummy(int a0, int a1, int a2, int a3, ...) {
}
void debug_PrintFontWindowDummy(int a0, int a1, ...) {
}
void debug_StdPrintfDummy(char *fmt, ...)
{
    (void)fmt;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontf);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintMatrix);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispVu1FReg);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Mode);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowVal);
extern int D_0063AF90[];
extern void sprintf();

void getLineBuffer(int a0, int a1, int a2)
{
    sprintf(a0, D_0063AF90, a1, a2);
}
extern int D_0063AF80[];

void getBuffer(int a0)
{
    sprintf(a0, D_0063AF80);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindow);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectStageMain);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectStage);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcRetErrCheck);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_selectFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcSaveMainBlock);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcLoadMainBlock);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcDeleteFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MemoryCard);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SETest);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SESlotDisp);
INCLUDE_ASM("asm/nonmatchings/src/debug", debugCdvdLoadInfoSegDispFunc);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectActGobj);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBox);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBall);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_CollisionTest);
ASM_LIT4_SLOT(D_00639348, 0.001f);
ASM_LIT4_SLOT(D_0063934C, 0.001f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Menu);
extern int D_0063B0F4;

void debug_Menu_off(void) {
    D_0063B0F4 = 0;
}
void debug_BeginTimer(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_GetTimerSec);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_GetTimerCount);
extern int D_0063AE64;
extern char D_007082D0[];

void debug_ClearFontWindow(void)
{
    char *p = D_007082D0;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_0063AE64 = 0;
}
extern int D_0063AEB4;

void debug_ResizeFontWindowHeight(int val) {
    D_0063AEB4 = val;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SetBar);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SetBar2);
extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063C384;

void debug_ResetBar(void)
{
    D_0063B120 = 0;
    *(volatile int *)0x10000000 = 0;
    D_0063B11C = 0;
    D_0063B118 = 0;
    D_0063B114 = 0;
    D_0063B110 = 0;
    D_0063B124 = 0;
    D_0063C384 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispVu1IReg);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispVu1SReg);
extern void debug_DispQW();

void debug_DispMatrix(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        debug_DispQW(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}
void debug_SetBarDummy(void) {}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLine);
int debug_TryToGetStartStage(void) {
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debugSceOpen);
extern int D_0063B100;
extern int sceClose();

int debugSceClose(int a0) {
    if (a0 == D_0063B100) {
        D_0063B100 = -1;
    }
    return sceClose();
}
int debugSceCloseFdNew(void)
{
    int r = 0;
    int h = D_0063B100;
    if (h != -1) {
        D_0063B100 = -1;
        r = sceClose(h);
        D_0063B100 = -1;
    }
    return r;
}
void debug_closeLog(void) {}
extern int D_0070F880[];

void debugCdvdLoadInfoSegInit(int idx)
{
  int *p;
  char *new_var2;
  int new_var;
  int i;
  new_var2 = (char *) D_0070F880;
  p = (int *) ((new_var2 + (idx * 0xD0)) + 0xC8);
  if (1)
  {
    for (i = 0x19; i >= 0; i--)
    {
      new_var = (*p = 0);
      p = (p = (int *) (((char *) p) - 8));
    }

  }
}
void debugCdvdLoadInfoSegAdd(int page, int idx, int delta)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) += delta;
}
void debugCdvdLoadInfoSegCls(int page, int idx)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) = 0;
}
extern int D_0028F4F0[];
extern void gsb_Init();

int gsResetFunc(void)
{
    gsb_Init(D_0028F4F0);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", ChangeGirlControlMode);
extern int D_0063AE68;

int debug_CallbackGsFinish(void)
{
    D_0063AE68 = *(volatile int *)0x10000000;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SaveStartStageFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", _debug_SelectCsvWindow);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLineColor);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcFormat);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcUnformat);
extern char D_0063AFC8[];
extern char D_0063AFD0[];

void *debug_saveNumFunc(int a0, void *a1) {
    if ((1 << a0) & *(long long *)((char *)a1 + 0x9C0)) {
        return D_0063AFC8;
    }
    return D_0063AFD0;
}
extern void iosMcTest(void);

int debug_mcTest(void) {
    iosMcTest();
    return 1;
}
extern void staffRollStart(int a0, float a1);

int debug_STAFFROLLTest(void) {
    staffRollStart(0x80, 1.0f);
    return 1;
}
extern unsigned short D_0030C4E0[];
extern GsysObjInfo D_005D6DB0[];

int debug_SETest_color(int idx)
{
  int new_var;
  int v3 = D_005D6DB0[idx].f_20;
  unsigned short a4 = *((unsigned short *) (((char *) D_0030C4E0) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_reverbTest);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_AdpcmTest);
INCLUDE_ASM("asm/nonmatchings/src/debug", debugCdvdLoadInfoSegDisp);
int debug_GameOver(void) {
    debug_Menu_off();
    return -1;
}
int debug_EndingDemo(void) {
    debug_Menu_off();
    return -1;
}
extern void backStageProcessInStage(float a0);

int debug_BackStageTest(void) {
    backStageProcessInStage(10000000.0f);
    return 1;
}
extern void backStageDebugTimeZero(void);

int debug_tsuresariTimeZero(void) {
    backStageDebugTimeZero();
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_hintStart);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectPad2ControlGobj);
extern void CameraSetMode(int x);
extern int D_0028F8F4[];

int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_0028F8F4[0] & 0x100) ? -1 : 0;
}
extern void sceVif1PkCloseDirectCode();
extern void sceVif1PkCloseGifTag();
extern void sceVif1PkEnd();
extern void sceVif1PkTerminate();

void CloseVif1DirectPacket(int a0)
{
    sceVif1PkCloseGifTag(a0);
    sceVif1PkCloseDirectCode(a0);
    sceVif1PkEnd(a0, 0);
    sceVif1PkTerminate(a0);
}
extern int sceDmaGetChan(unsigned a0);
extern void sceDmaSend();
extern void sceGsSyncPath();

void SendVif1DirectPacket(int *self)
{
    int *p;
    sceGsSyncPath(0, 0);
    p = sceDmaGetChan(1);
    *p |= 0x40;
    sceDmaSend(p, (self[0x4/4] & 0x3FF0) | 0x80000000);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", RestoreNormalDrawEnvironment);
INCLUDE_ASM("asm/nonmatchings/src/debug", SetTextureWithFrameBuffer);
INCLUDE_ASM("asm/nonmatchings/src/debug", SetTexDrawEnvironment);
INCLUDE_ASM("asm/nonmatchings/src/debug", SetDrawnTextureEnvironment);
INCLUDE_ASM("asm/nonmatchings/src/debug", SetDrawEnvironment);
INCLUDE_ASM("asm/nonmatchings/src/debug", drawSprite);
INCLUDE_ASM("asm/nonmatchings/src/debug", PutFont);
extern void sceDmaReset(int a0);
extern void sceDmaSync(int *a0, int a1, int a2);
extern void sceGsResetPath(void);

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
extern void sceVpu0Reset();

void resetGS(int a0)
{
    sceVpu0Reset(a0);
    gsb_Init(D_0028F4F0);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", putString);
INCLUDE_ASM("asm/nonmatchings/src/debug", drawWin);
ASM_LIT4_SLOT(D_00639354, 0.8f);
extern void SetDrawEnvironment(int a0);
extern void drawSprite(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);

void saveBack(void)
{
    SetDrawEnvironment(1);
    drawSprite(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    SetDrawEnvironment(1);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", baseFunc);
INCLUDE_ASM("asm/nonmatchings/src/debug", syncGS);
