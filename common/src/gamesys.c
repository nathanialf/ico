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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysBackStageProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGeneratorInfoLoad);

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoPosSetStage);

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoCls);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGirlStageGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGetGirlStageIDAndPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysStageExitTimeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemorySave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryLoad);

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", func_001A99D0);


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
