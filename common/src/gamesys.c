#include "common.h"

extern char D_0062CC90[];
extern char D_0062CC98[];

void *gamesysObjInfoInit(int a0, void *a1) {
    if ((1 << a0) & *(long long *)((char *)a1 + 0x9C0)) {
        return D_0062CC90;
    }
    return D_0062CC98;
}

extern int iosMcManager(void);

int gamesysObjInfoSave(void)
{
    iosMcManager();
    return 1;
}

extern void staffRollMain(int a0, float a1);

int debug_STAFFROLLTest(void) {
    staffRollMain(0x80, 1.0f);
    return 1;
}

typedef struct { char pad[0x20]; int f20; char pad2[0x18]; } GsObjInfo;
extern GsObjInfo D_005CD670[];
extern unsigned short D_002E2A10[];

int debug_SETest_color(int a0) {
    int ret = 0x80808000;
    if (D_002E2A10[D_005CD670[a0].f20] != 0) {
        ret = -0x100;
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", debug_reverbTest);

extern int D_0062AEA8;
extern int D_0062AEA4;
extern char D_0060E170[];
extern char D_006151D8[];
extern int func_001A4DE8(void *, int, int, int, void *, int, int, int, int, int *);
extern void scpPlayStart(int, int, int, int, int);

int gamesysBackStageProcess(int a0) {
    int ret;
    if (a0 != 0) {
        D_0062AEA8 = -1;
    }
    ret = func_001A4DE8(D_0060E170, 0xA, 0x3C, 0xA, D_006151D8, 0x40, 0, 0, 0x60, &D_0062AEA4);
    if (ret > 0 && D_0062AEA4 != 0) {
        scpPlayStart(D_0062AEA4, 0, 1, 1, 1);
    }
    return ret;
}

extern int debug_SelectCsvWindowVal(void *a0, int a1, int a2, int a3, int a4, void *a5, void *a6, int a7);
extern void func_001A62D8();
extern int D_0062AEC0;
extern int D_0062AEC4;
extern char D_0060E190[];
extern char D_0060E1A8[];
extern char D_006F26D0[];
extern int D_002715D4[];

int debugCdvdLoadInfoSegDisp(void) {
    long buf[3];
    int r;
    __builtin_memcpy((char *)buf, D_0060E190, 0x14);
    if (D_0062AEC0 != 0) {
        *(long *)((char *)buf + 0) = *(long *)(D_0060E1A8 + 0);
        *(long *)((char *)buf + 8) = *(long *)(D_0060E1A8 + 8);
        *(short *)((char *)buf + 0x10) = *(short *)(D_0060E1A8 + 0x10);
        *(char *)((char *)buf + 0x12) = *(char *)(D_0060E1A8 + 0x12);
    }
    r = debug_SelectCsvWindowVal(buf, 0x50, 0x46, 0xA, 0x1A, &D_0062AEC4, (void *)func_001A62D8, D_0062AEC0);
    if (D_002715D4[0] & 0x10) {
        int *row = (int *)(D_006F26D0 + D_0062AEC0 * 0xD0);
        int i;
        for (i = 0x19; i >= 0; i--) {
            row[1] = row[0];
            row += 2;
        }
    }
    return r;
}

extern int init_debug_menu(void);

int gamesysCharacterInfoLoad(void)
{
    init_debug_menu();
    return -1;
}

int gamesysNObjInfoInit(void)
{
    init_debug_menu();
    return -1;
}

extern float D_006293EC;
extern void backStageProcessInit(float a0);

int debug_BackStageTest(void) {
    backStageProcessInit(D_006293EC);
    return 1;
}

extern int InitCharFileManager(void);

int gamesysObjInfoStageInitPosSaveUnlock(void)
{
    InitCharFileManager();
    return 1;
}

/* debug_SelectPad2ControlGobj */
typedef struct { char _0[0xC]; int f0C; } PSObj;
typedef struct { char _0[0x64]; } StageInfo;
typedef struct { StageInfo *f0; PSObj *f4; } PosEntry;

extern PSObj *isysGObjGetExist_begin(int a0);
extern PSObj *isysGObjGetExist_next(PSObj *g);
extern StageInfo D_0029F060[];
extern char D_0060E1D8[];
extern int D_00629E10;
extern int D_0062AECC;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", debug_SelectPad2ControlGobj);


extern int D_002715D4[];
extern void CameraSetMode(int a0);

int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_002715D4[0] & 0x100) ? -1 : 0;
}

extern void sceVif1PkCloseGifTag(int a0);
extern void sceVif1PkCloseDirectCode(int a0);
extern void func_00241698(int a0, int a1);
extern void sceVif1PkTerminate(int a0);

void CloseVif1DirectPacket(int a0)
{
    sceVif1PkCloseGifTag(a0);
    sceVif1PkCloseDirectCode(a0);
    func_00241698(a0, 0);
    sceVif1PkTerminate(a0);
}

extern void sceGsSyncPath(int a0, int a1);
extern int sceDmaGetChan(unsigned int a0);
extern int sceDmaSend(int *a0, int a1);

void SendVif1DirectPacket(int *a0) {
    int *p;
    sceGsSyncPath(0, 0);
    p = (int *)sceDmaGetChan(1);
    *p |= 0x40;
    sceDmaSend(p, (a0[1] & 0x3FF0) | 0x80000000);
}

extern void sceGsSetHalfOffset(void *a0, int a1, int a2, short a3);
extern void sceGsPutDrawEnv(void *a0);

void RestoreNormalDrawEnvironment(void *a0, int a1, int a2) {
    char *p = (char *)((int)a0 | 0x20000000);
    if (a1 != 0) {
        sceGsSetHalfOffset(p + 0x150, 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv(p + 0x140);
    } else {
        sceGsSetHalfOffset(p + 0x60, 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv(p + 0x50);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", SetTextureWithFrameBuffer);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", SetTexDrawEnvironment);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", SetDrawnTextureEnvironment);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", SetDrawEnvironment);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", drawSprite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", PutFont);

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

extern void sceVpu0Reset(void);
extern void gsb_antiAlias(void *a0);
extern int D_00271270[];

void gamesysVersionLoad(void) {
    sceVpu0Reset();
    gsb_antiAlias(D_00271270);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", drawWin);

extern void SetDrawEnvironment(int a0);
extern void drawSprite(int a0, int a1, int a2, int a3, int a4,
                                     int a5, int a6, int a7, int a8);

void saveBack(void)
{
    SetDrawEnvironment(1);
    drawSprite(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    SetDrawEnvironment(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", baseFunc);

extern void FlushCache(int a0);
extern int sceGsSyncV(int a0);
extern void gsb_setNormalReg(void);
extern void sceGsSwapDBuff(void *a0, int a1);
extern void RestoreNormalDrawEnvironment(void *a0, int a1, int a2);
extern int D_00629C40;
extern int D_00629C50;
extern int D_00629C60;

void syncGS(void) {
    FlushCache(0);
    sceGsSyncPath(1, 0);
    D_00629C50 = sceGsSyncV(0);
    D_00629C60++;
    D_00629C40 = D_00629C60 & 1;
    gsb_setNormalReg();
    sceGsSwapDBuff(D_00271270, D_00629C40);
    RestoreNormalDrawEnvironment(D_00271270, D_00629C40, D_00629C50);
    SetDrawEnvironment(1);
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned short     f_10;  /* 0x10 */
    unsigned char      f_12;  /* 0x12 */
} S_0060E1A8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_4;  /* 0x04 */
} S_006F2890;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060EED0;  /* stride 0x4 */

/* end struct shapes */
