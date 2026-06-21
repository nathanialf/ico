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

int gamesysObjInfoLoad(void) {
    staffRollMain(0x80, 1.0f);
    return 1;
}

typedef struct { char pad[0x20]; int f20; char pad2[0x18]; } GsObjInfo;
extern GsObjInfo D_005CD670[];
extern unsigned short D_002E2A10[];

int gamesysObjInfoEmptyAreaSearch(int a0) {
    int ret = 0x80808000;
    if (D_002E2A10[D_005CD670[a0].f20] != 0) {
        ret = -0x100;
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoBaseSet);

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

extern int func_001A4C58(void *a0, int a1, int a2, int a3, int a4, void *a5, void *a6, int a7);
extern void func_001A62D8();
extern int D_0062AEC0;
extern int D_0062AEC4;
extern char D_0060E190[];
extern char D_0060E1A8[];
extern char D_006F26D0[];
extern int D_002715D4[];

int gamesysGeneratorInfoLoad(void) {
    long buf[3];
    int r;
    __builtin_memcpy((char *)buf, D_0060E190, 0x14);
    if (D_0062AEC0 != 0) {
        *(long *)((char *)buf + 0) = *(long *)(D_0060E1A8 + 0);
        *(long *)((char *)buf + 8) = *(long *)(D_0060E1A8 + 8);
        *(short *)((char *)buf + 0x10) = *(short *)(D_0060E1A8 + 0x10);
        *(char *)((char *)buf + 0x12) = *(char *)(D_0060E1A8 + 0x12);
    }
    r = func_001A4C58(buf, 0x50, 0x46, 0xA, 0x1A, &D_0062AEC4, (void *)func_001A62D8, D_0062AEC0);
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

int gamesysObjInfoStageInitFlagCls(void) {
    backStageProcessInit(D_006293EC);
    return 1;
}

extern int InitCharFileManager(void);

int gamesysObjInfoStageInitPosSaveUnlock(void)
{
    InitCharFileManager();
    return 1;
}

/* gamesysObjInfoPosSetStage */
typedef struct { char _0[0xC]; int f0C; } PSObj;
typedef struct { char _0[0x64]; } StageInfo;
typedef struct { StageInfo *f0; PSObj *f4; } PosEntry;

extern PSObj *isysGObjRemoveObjDL(int a0);
extern PSObj *func_0013E7E0(PSObj *g);
extern StageInfo D_0029F060[];
extern char D_0060E1D8[];
extern int D_00629E10;
extern int D_0062AECC;

int gamesysObjInfoPosSetStage(int a0) {
    PosEntry local[10];
    PosEntry *lp = local;
    int count = 0;
    int r;
    PSObj *g = isysGObjRemoveObjDL(a0);
    if (g != 0) {
        do {
            int type = g->f0C;
            if (type == 2 || type == 4) {
                lp[count].f0 = &D_0029F060[type];
                lp[count].f4 = g;
                count++;
            }
            g = func_0013E7E0(g);
        } while (g != 0);
    }
    if (a0 == 0) {
        D_0062AECC = 0;
    }
    r = func_001A4DE8(D_0060E1D8, 10, 50, 11, lp, 8, 0, 1, count, &D_0062AECC);
    if (r > 0) {
        D_00629E10 = (int) lp[D_0062AECC].f4;
        return 1;
    }
    return (r == -1) ? -1 : 0;
}


extern int D_002715D4[];
extern void func_0018A0D8(int a0);

int gamesysObjInfoUniqDataSet(int a0)
{
    if (a0 != 0) {
        func_0018A0D8(1);
    }
    func_0018A0D8(1);
    return (D_002715D4[0] & 0x100) ? -1 : 0;
}

extern void func_00241790(int a0);
extern void func_00241748(int a0);
extern void func_00241698(int a0, int a1);
extern void func_002415E8(int a0);

void gamesysObjInfoPosNewStageSet(int a0)
{
    func_00241790(a0);
    func_00241748(a0);
    func_00241698(a0, 0);
    func_002415E8(a0);
}

extern void func_0023EB60(int a0, int a1);
extern int func_00240B50(unsigned int a0);
extern int func_00240EA0(int *a0, int a1);

void gamesysObjInfoGet(int *a0) {
    int *p;
    func_0023EB60(0, 0);
    p = (int *)func_00240B50(1);
    *p |= 0x40;
    func_00240EA0(p, (a0[1] & 0x3FF0) | 0x80000000);
}

extern void func_0023FB60(void *a0, int a1, int a2, short a3);
extern void func_0023E6E8(void *a0);

void gamesysObjInfoCls(void *a0, int a1, int a2) {
    char *p = (char *)((int)a0 | 0x20000000);
    if (a1 != 0) {
        func_0023FB60(p + 0x150, 0x800, 0x800, (short)a2);
        func_0023E6E8(p + 0x140);
    } else {
        func_0023FB60(p + 0x60, 0x800, 0x800, (short)a2);
        func_0023E6E8(p + 0x50);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGirlStageGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGetGirlStageIDAndPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysStageExitTimeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemorySave);

extern void func_00240B78(int a0);
extern void func_002413F0(int *a0, int a1, int a2);
extern void func_0023E168(void);

void gamesysMemoryLoad(void) {
    func_00240B78(1);
    func_002413F0((int *)func_00240B50(0), 0, 0x64);
    func_002413F0((int *)func_00240B50(1), 0, 0x64);
    func_002413F0((int *)func_00240B50(2), 0, 0x64);
    *(int *)func_00240B50(0) |= 0x40;
    *(int *)func_00240B50(1) |= 0x40;
    *(int *)func_00240B50(2) |= 0x40;
    func_0023E168();
}

extern void func_00240AB8(void);
extern void gsb_antiAlias(void *a0);
extern int D_00271270[];

void gamesysVersionLoad(void) {
    func_00240AB8();
    gsb_antiAlias(D_00271270);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysCharacterInfoSave);

extern void gamesysMemoryHandlerWrite(int a0);
extern void gamesysMemoryHandlerRead(int a0, int a1, int a2, int a3, int a4,
                                     int a5, int a6, int a7, int a8);

void gamesysGeneratorInfoSave(void)
{
    gamesysMemoryHandlerWrite(1);
    gamesysMemoryHandlerRead(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    gamesysMemoryHandlerWrite(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", func_001A98E0);

extern void func_001007A0(int a0);
extern int func_0023EAC8(int a0);
extern void gsb_setNormalReg(void);
extern void func_0023EA68(void *a0, int a1);
extern void gamesysObjInfoCls(void *a0, int a1, int a2);
extern int D_00629C40;
extern int D_00629C50;
extern int D_00629C60;

void func_001A99D0(void) {
    func_001007A0(0);
    func_0023EB60(1, 0);
    D_00629C50 = func_0023EAC8(0);
    D_00629C60++;
    D_00629C40 = D_00629C60 & 1;
    gsb_setNormalReg();
    func_0023EA68(D_00271270, D_00629C40);
    gamesysObjInfoCls(D_00271270, D_00629C40, D_00629C50);
    gamesysMemoryHandlerWrite(1);
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
