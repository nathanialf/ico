#include "common.h"
#include "DObj.h"
#include "GobjProc.h"
#include "debug.h"
#include "gamesys.h"
#include "obj_manager.h"
#include "act-game.h"
#include "fieldCollision.h"
#include "way_tool.h"
#include "brain.h"
#include "camera-root.h"
#include "fightSound.h"
#include "GsBase.h"
#include "Light.h"
#include "clipCollisionManager.h"
#include "waySystemManager.h"

extern ObjKindEnt D_002C1270[];
/* kept local: this TU's uses of isysGObjGetExist_begin do not fit the prototype in gobj.h */
extern int *isysGObjGetExist_begin(int a0);
/* kept local: this TU's uses of isysGObjGetExist_next do not fit the prototype in gobj.h */
extern int *isysGObjGetExist_next(int *a0);

/* .sbss, owned by sceneManager.o and reached only from this file (MAIN.MAP
   names no symbol in the run), in the ROM's run order: the three frame counts
   GetStageStartInfo hands back, which boyact's stage-entry action waits out in
   turn (before the motion, during it, after it). */
static int stageStartWait1;

static int stageStartWait2;

static int stageStartWait3;

extern char D_0063B640;
extern int D_0063B644;
extern float D_0071D960[];
extern float D_0071D970[];
extern int exit_no;

#include "sceneManager.h"
#include "backStage.h"
#include "typedef.h"

inline void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5)
{
    D_0071D960[0] = a0[0];
    D_0071D960[1] = a0[1];
    D_0071D960[2] = a0[2];
    stageStartWait1 = a2;
    stageStartWait2 = a3;
    stageStartWait3 = a4;
    D_0063B644 = a5;
    D_0071D970[0] = a1[0];
    D_0071D970[1] = a1[1];
    D_0071D970[2] = a1[2];
    D_0063B640 = 1;
}

inline void test_nextstage_firstwalk_set(int unused, int a, int b, int c)
{
    stageStartWait1 = a;
    stageStartWait2 = b;
    stageStartWait3 = c;
}

inline int GetStageStartInfo(int a0, int a1, int a2, int *p, int *q, int *r)
{
    int ret = 1;
    if (exit_no == 0) {
        *r = 1;
        *q = 1;
        *p = 1;
    } else {
        *p = stageStartWait1;
        *q = stageStartWait2;
        *r = stageStartWait3;
        if (*q == 0)
            ret = 0;
        if (*p == 0)
            *p = 1;
        if (*q == 0)
            *q = 1;
        if (*r == 0)
            *r = 1;
    }
    *q = 0x32;
    return ret;
}

inline void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0)
{
    if (a2 >= 0) {
        stageStartWait1 = a2;
    }
    if (a3 >= 0) {
        stageStartWait2 = a3;
    }
    if (t0 >= 0) {
        stageStartWait3 = t0;
    }
}

inline void MoveNextStage_Clear(void)
{
    D_0063B640 = 0;
    D_0063B644 = -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/sceneManager", GetRealModelId);

extern const StgPre D_005F5D50[];

/* sceneManager.c:213-313.  D_0028F720 is the StageSettingScenemanager record ico2/seki/src/GsBase.c
   already names; the fields this TU touches beyond that file's four are spelled by
   offset.  The stage-preset record is read through the D_005F5D50[stage] subscript on
   every line, which is what the listing's per-line pointer copies show. */
/* kept local: this TU's bytes only come out with its own view of StageSettingScenemanager. */
/* kept local: this TU's bytes only come out with its own view of StageSetting, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct StageSettingScenemanager {
    float flatLightDir[3][4]; /* 0x000 */
    float flatLightCol[3][4]; /* 0x030 */
    float ambientCol[4];      /* 0x060 */
    float bgCol[4];           /* 0x070 */
    int f080;                 /* 0x080 */
    int _084[3];              /* 0x084 */
    int f090[4];              /* 0x090 */
    int f0A0[3];              /* 0x0A0 */
    int f0AC;                 /* 0x0AC */
    int f0B0;                 /* 0x0B0 */
    int f0B4;                 /* 0x0B4 */
    int f0B8;                 /* 0x0B8 */
    int f0BC;                 /* 0x0BC */
    int f0C0;                 /* 0x0C0 */
    int f0C4;                 /* 0x0C4 */
    int f0C8;                 /* 0x0C8 */
    int _0CC;                 /* 0x0CC */
    int f0D0;                 /* 0x0D0 */
    int f0D4;                 /* 0x0D4 */
    int f0D8;                 /* 0x0D8 */
    int _0DC;                 /* 0x0DC */
    int f0E0;                 /* 0x0E0 */
    int _0E4;                 /* 0x0E4 */
    int f0E8;                 /* 0x0E8 */
    int f0EC;                 /* 0x0EC */
    int f0F0;                 /* 0x0F0 */
    int motionBlur;           /* 0x0F4 */
    int _0F8;                 /* 0x0F8 */
    int f0FC;                 /* 0x0FC */
    int f100;                 /* 0x100 */
    int f104;                 /* 0x104 */
    int _108[2];              /* 0x108 */
    int f110;                 /* 0x110 */
    int f114;                 /* 0x114 */
    int f118;                 /* 0x118 */
    int f11C;                 /* 0x11C */
    int f120;                 /* 0x120 */
    int _124[3];              /* 0x124 */

    struct {
        int x;
        int y;
        int z;
        int w;
    } f130[4]; /* 0x130 */

    float f170;  /* 0x170 */
    int _174[3]; /* 0x174 */
    int f180;    /* 0x180 */
    int f184;    /* 0x184 */
    int _188[2]; /* 0x188 */
    int f190;    /* 0x190 */
    int _194[2]; /* 0x194 */

    struct {
        int a;
        int b;
    } f19C[4]; /* 0x19C */

    int subMotionBlur[4]; /* 0x1BC */
} StageSettingScenemanager;

extern StageSettingScenemanager D_0028F720;
extern int D_0028F4F0[];
extern char D_0061DDD8[];
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(float *dst, float *src);
/* kept local: this TU's uses of tex_RemakeRegistersSampleMin do not fit the prototype in Texture.h */
extern void tex_RemakeRegistersSampleMin(int a);

void InitStageLight(int stage)
{
    int i;

    debug_StdPrintfDummy(D_0061DDD8);

    for (i = 0; i < 3; i++) {
        D_0028F720.flatLightDir[0][i] = -D_005F5D50[stage].flatLightDir[i];

        D_0028F720.flatLightCol[0][i] = D_005F5D50[stage].flatLightCol[i] * 0.0078125f;
    }

    _NormalizeVector(D_0028F720.flatLightDir[0], D_0028F720.flatLightDir[0]);

    for (i = 0; i < 3; i++) {
        D_0028F720.flatLightDir[1][i] = D_0028F720.flatLightDir[2][i] =
            D_005F5D50[stage].flatLightDir[i];

        D_0028F720.flatLightCol[1][i] = D_0028F720.flatLightCol[2][i] =
            D_005F5D50[stage].flatLightCol[i] * 0.0078125f * 0.25f;
    }

    _NormalizeVector(D_0028F720.flatLightDir[1], D_0028F720.flatLightDir[1]);

    _NormalizeVector(D_0028F720.flatLightDir[2], D_0028F720.flatLightDir[2]);

    for (i = 0; i < 3; i++) {
        D_0028F720.ambientCol[i] = D_005F5D50[stage].ambientCol[i] * 0.0078125f;

        D_0028F720.bgCol[i] = D_005F5D50[stage].bgCol[i];
    }
    D_0028F720.ambientCol[3] = D_0028F720.bgCol[3] = 1.0f;

    light_AddLight(0, 0, 0);

    D_0028F720.f080 = (int)D_005F5D50[stage].f60[0];
    D_0028F720.f090[0] = (int)D_005F5D50[stage].f60[1];
    D_0028F720.f090[1] = (int)D_005F5D50[stage].f60[2];
    D_0028F720.f090[2] = (int)D_005F5D50[stage].f60[3];
    D_0028F720.f090[3] = (int)D_005F5D50[stage].f60[4];
    D_0028F720.f0A0[0] = (int)D_005F5D50[stage].f60[5];
    D_0028F720.f0A0[1] = (int)D_005F5D50[stage].f60[6];
    D_0028F720.f0A0[2] = (int)D_005F5D50[stage].f60[7];
    D_0028F720.f120 = 128;

    gsb_SetBGColor(D_0028F4F0, (int)D_0028F720.bgCol[0], (int)D_0028F720.bgCol[1],
                   (int)D_0028F720.bgCol[2]);

    D_0028F720.f0AC = D_005F5D50[stage].f188;
    D_0028F720.f0B0 = 0;
    D_0028F720.f0B4 = 40;
    D_0028F720.f0B8 = 80;
    D_0028F720.f0BC = 120;
    D_0028F720.f0C0 = 0;
    D_0028F720.f0C4 = 0;
    D_0028F720.f0C8 = 0;

    D_0028F720.f0D0 = 128;
    D_0028F720.f0D4 = 128;
    D_0028F720.f0D8 = 128;

    D_0028F720.f0E0 = 100;

    D_0028F720.f0E8 = 0;
    D_0028F720.f104 = 2;
    D_0028F720.f0EC = 100;
    D_0028F720.f0F0 = 500;
    D_0028F720.motionBlur = 32;

    D_0028F720.f110 = 64;
    D_0028F720.f114 = 64;
    D_0028F720.f118 = 64;
    D_0028F720.f11C = 128;

    D_0028F720.f0FC = 24;
    D_0028F720.f100 = 24;

    for (i = 0; i < 4; i++) {
        int *row = (int *)&D_0028F720 + i * 4;

        row[0x130 / 4] = 128;
        row[0x134 / 4] = 128;
        row[0x138 / 4] = 128;
        row[0x13C / 4] = (i + 1) * 8;
        D_0028F720.subMotionBlur[i] = 32;
        D_0028F720.f19C[i].a = 0;
        D_0028F720.f19C[i].b = 0;
    }

    D_0028F720.f170 = 3.0f;

    D_0028F720.f180 = 120;
    D_0028F720.f184 = 80;
    D_0028F720.f190 = 200;

    tex_RemakeRegistersSampleMin(0);
}

inline char *CreateLayoutedGObj(int id, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    ObjKindEnt *layout = (ObjKindEnt *)((char *)D_002C1270 + id * 0x64);
    char *gobj = CreateGObj(layout, id, a5, a6, a7);
    int dobj = CSVSYSTEM_InitDObj(a1, a4);
    int (*fn)(char *, int);

    *(int *)(gobj + 0x15C) = dobj;
    *(int *)(dobj + 0x844) = a2;

    light_AddLight(gobj, a3, 1);

    fn = layout->create;
    if (fn != 0) {
        *(int *)(*(int *)(gobj + 0x15C) + 0x830) = fn(gobj, a4);
    }
    return gobj;
}

typedef union {
    long long flag;
    GamesysObjInfo info;
} GamesysObjInfoFlag;

extern GenGeo D_002C2DC8[];
extern void *D_0063ACF0;

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/sceneManager", initSceneGObj);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/sceneManager", initParentLink);

/* sceneManager.c:519-536, 553-570, 606-617: three static helpers the listing
   inlines into InitSceneObjects; they have no symbol of their own in the ROM
   and no census row, so the names below are descriptive. */

extern GamesysObjInfoFlag D_004DA980[];
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_begin do not fit the prototype in gobj.h */
extern int *isysGObjSearchFromObjKindID_begin(int kind);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_next do not fit the prototype in gobj.h */
extern int *isysGObjSearchFromObjKindID_next(int *gobj);

static inline void initSceneGObjRange(int stage, int first, int last)
{
    int i;

    for (i = first; i < last; i++) {
        initSceneGObj(stage, i);
    }

    for (i = first; i < last; i++) {
        initParentLink(i);
    }
}

static inline void setEnemyGeneratorDispFlag(void)
{
    int *gobj;

    for (gobj = isysGObjSearchFromObjKindID_begin(4); gobj != 0;
         gobj = isysGObjSearchFromObjKindID_next(gobj)) {
        GenGeo *gen = &D_002C2DC8[gobj[2]];

        gen->f48 |= 0x200000;
    }
}

static inline void initGamesysSceneGObjs(int stage)
{
    GamesysObjInfoFlag *p = D_004DA980;
    int i;

    for (i = 0; i <= 181; i++, p++) {
        if (p->info.no != 0 && (p->flag & 1) == 0 && p->info.stage == stage) {
            initSceneGObj(stage, p->info.no);
        }
    }
}

void initWayData(int stage)
{
    ExtractWayData(stage);
}

extern void *D_00639EA4;
extern void *D_00639EA8;
extern void *D_00639EAC;
extern void *D_00639EB0;
extern void *D_00639EB4;
extern void *D_00639EB8;
extern void *D_00639EBC;
extern char D_0061DEF0[];
/* kept local: this TU's uses of isysGObjMoveAfterGObj do not fit the prototype in gobj.h */
extern void isysGObjMoveAfterGObj(void *gobj, int *after);

void InitSceneObjects(int stage)
{
    int *cam;

    ResetGObjProc();
    D_00639EA4 = D_00639EA8 = 0;
    D_00639EAC = 0;
    D_00639EB0 = 0;
    D_00639EB4 = 0;
    D_00639EB8 = 0;
    D_00639EBC = 0;

    debug_StdPrintfDummy(D_0061DEF0, stage);

    gsb_SetZoom(1.0f, 1000.0f);
    brainInit();
    ACTGameView_Init();

    gamesysObjInfoStageInitFlagCls();

    D_0063ACF0 = 0;
    fightSoundProcessRequestStart();

    CreateClipCollisionManagerGObj();

    CreateWaySystemManagerGObj();

    cam = InitCameraGObjs(stage, 0, 1);

    initSceneGObjRange(stage, 2, 6);
    initSceneGObjRange(stage, D_005F5D50[stage].labelTop, D_005F5D50[stage].labelEnd);
    initGamesysSceneGObjs(stage);

    if (D_00639EA8 != 0) {
        isysGObjMoveAfterGObj(D_00639EA8, cam);
    }
    if (D_00639EA4 != 0) {
        isysGObjMoveAfterGObj(D_00639EA4, cam);
    }

    setEnemyGeneratorDispFlag();

    InitCamera();

    initWayData(stage);

    MakeExitAttributeIndex();
}

int HotInitSceneObjects(int a0)
{
    int *node = isysGObjGetExist_begin(a0);
    if (node != 0) {
        do {
            int idx = ((PObjGObj *)node)->kind;
            if (idx >= 0) {
                ObjKindEnt *e = (ObjKindEnt *)((char *)D_002C1270 + idx * 0x64);
                void (*fn)(int *);
                if (e->f60 != 0) {
                    iosOmSendMail(node, 0x2F, node);
                }
                fn = e->hotInit;
                if (fn != 0) {
                    fn(node);
                }
            }
            node = isysGObjGetExist_next(node);
        } while (node != 0);
    }
    return 1;
}
