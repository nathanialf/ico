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
#include "Matrix.h"
#include "gobj.h"
#include "enemy_act.h"
#include "gobj_process.h"
#include <assert.h>
#include "main.h"

/* .sbss, owned by sceneManager.o and reached only from this file (MAIN.MAP
   names no symbol in the run), in the ROM's run order: the three frame counts
   GetStageStartInfo hands back, which boyact's stage-entry action waits out in
   turn (before the motion, during it, after it). */
static int stageStartWait1;

static int stageStartWait2;

static int stageStartWait3;

/* .sdata, owned by sceneManager.o (MAIN.MAP names no symbol in the run):
   set while MoveNextStage_Set's request stands, and the stage it is for. */
static char nextStageSet = 0; /* derived name */

static int nextStageNo = -1; /* derived name */

/* .bss, owned by sceneManager.o (MAIN.MAP line 7741, 0x20 bytes, no symbol
   named): the position and rotation MoveNextStage_Set keeps for the next
   stage and MoveNextStage_Get restores, in the ROM's run order.  Both are
   16-byte vectors: the object's .bss is 16-aligned in the ROM and in
   MAIN.MAP, which a plain float[4] (8-aligned) does not give. */
static sceVu0FVECTOR nextStagePos;

static sceVu0FVECTOR nextStageRot;

#include "sceneManager.h"
#include "backStage.h"
#include "typedef.h"

/* .data, owned by sceneManager.o: the default layout a scene object is
   created with, at the origin, unrotated, at unit scale. */
SObjSimpleSetting InitialSObjSimpleSetting = {
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    0,
};

inline void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5)
{
    nextStagePos[0] = a0[0];
    nextStagePos[1] = a0[1];
    nextStagePos[2] = a0[2];
    stageStartWait1 = a2;
    stageStartWait2 = a3;
    stageStartWait3 = a4;
    nextStageNo = a5;
    nextStageRot[0] = a1[0];
    nextStageRot[1] = a1[1];
    nextStageRot[2] = a1[2];
    nextStageSet = 1;
}

inline void test_nextstage_firstwalk_set(int unused, int a, int b, int c)
{
    stageStartWait1 = a;
    stageStartWait2 = b;
    stageStartWait3 = c;
}

inline int GetStageStartInfo(GObj *a0, int a1, int a2, int *p, int *q, int *r)
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
    nextStageSet = 0;
    nextStageNo = -1;
}

extern const StgPre stageData[];

int GetRealModelId(int stageNo, char *gen)
{
    int mdl;
    int first;
    int count;
    int r;

    if (*(unsigned char *)(gen + 0x46) == 4) {
        switch (GetEnemyType(*(float *)gen, *(float *)(gen + 4), *(float *)(gen + 8))) {
        case 0:
            mdl = stageData[stageNo].mdl[2];
            break;
        case 1:
            mdl = stageData[stageNo].mdl[3];
            break;
        case 2:
            mdl = stageData[stageNo].mdl[1];
            break;
        case 3:
            mdl = stageData[stageNo].mdl[0];
            break;
        default:
            goto plain;
        }
        count = enemymodelGroup[mdl].last - enemymodelGroup[mdl].first;
        first = enemymodelGroup[mdl].first;
        if (count != 0) {
            r = (int)(_GetRandom() * 10.0f);
            return enemymodelTable[first + r % count];
        }
    }
plain:
    return *(int *)(gen + 0x2C);
}

/* sceneManager.c:213-313.  GlobalStageSetting is the system's StageSetting
   record (typedef.h).  The stage-preset record is read through the stageData[stage] subscript on
   every line, which is what the listing's per-line pointer copies show. */
extern StageSetting GlobalStageSetting;
/* kept local: Texture.h declares it (void); the callers here pass 0 */
extern int tex_RemakeRegistersSampleMin(int a);

void InitStageLight(int stage)
{
    int i;

    /* using the Excel data for the stage information */
    debug_StdPrintfDummy("ステージ情報にエクセルのデータを使用します.\n");

    for (i = 0; i < 3; i++) {
        GlobalStageSetting.flatLightDir[0][i] = -stageData[stage].flatLightDir[i];

        GlobalStageSetting.flatLightCol[0][i] = stageData[stage].flatLightCol[i] * 0.0078125f;
    }

    _NormalizeVector(GlobalStageSetting.flatLightDir[0], GlobalStageSetting.flatLightDir[0]);

    for (i = 0; i < 3; i++) {
        GlobalStageSetting.flatLightDir[1][i] = GlobalStageSetting.flatLightDir[2][i] =
            stageData[stage].flatLightDir[i];

        GlobalStageSetting.flatLightCol[1][i] = GlobalStageSetting.flatLightCol[2][i] =
            stageData[stage].flatLightCol[i] * 0.0078125f * 0.25f;
    }

    _NormalizeVector(GlobalStageSetting.flatLightDir[1], GlobalStageSetting.flatLightDir[1]);

    _NormalizeVector(GlobalStageSetting.flatLightDir[2], GlobalStageSetting.flatLightDir[2]);

    for (i = 0; i < 3; i++) {
        GlobalStageSetting.ambientCol[i] = stageData[stage].ambientCol[i] * 0.0078125f;

        GlobalStageSetting.bgCol[i] = stageData[stage].bgCol[i];
    }
    GlobalStageSetting.ambientCol[3] = GlobalStageSetting.bgCol[3] = 1.0f;

    light_AddLight(0, 0, 0);

    GlobalStageSetting.fogOn = (int)stageData[stage].fog[0];
    GlobalStageSetting.fogColR = (int)stageData[stage].fog[1];
    GlobalStageSetting.fogColG = (int)stageData[stage].fog[2];
    GlobalStageSetting.fogColB = (int)stageData[stage].fog[3];
    GlobalStageSetting.fogColA = (int)stageData[stage].fog[4];
    GlobalStageSetting.fogOffsetA = (int)stageData[stage].fog[5];
    GlobalStageSetting.fogNear = (int)stageData[stage].fog[6];
    GlobalStageSetting.fogFar = (int)stageData[stage].fog[7];
    GlobalStageSetting.fogStrength = 128;

    gsb_SetBGColor(db, (int)GlobalStageSetting.bgCol[0], (int)GlobalStageSetting.bgCol[1],
                   (int)GlobalStageSetting.bgCol[2]);

    GlobalStageSetting.shadowDepth = stageData[stage].shadowDepth;
    GlobalStageSetting.shadowBlend[0] = 0;
    GlobalStageSetting.shadowBlend[1] = 40;
    GlobalStageSetting.shadowBlend[2] = 80;
    GlobalStageSetting.shadowBlend[3] = 120;
    GlobalStageSetting.shadowColR = 0;
    GlobalStageSetting.shadowColG = 0;
    GlobalStageSetting.shadowColB = 0;

    GlobalStageSetting.reductionCol[0] = 128;
    GlobalStageSetting.reductionCol[1] = 128;
    GlobalStageSetting.reductionCol[2] = 128;

    GlobalStageSetting.viewScale = 100;

    GlobalStageSetting.postEffect = 0;
    GlobalStageSetting.feedbackEffect = 2;
    GlobalStageSetting.depthFieldStart = 100;
    GlobalStageSetting.depthFieldWidth = 500;
    GlobalStageSetting.motionBlur = 32;

    GlobalStageSetting.feedbackCol[0] = 64;
    GlobalStageSetting.feedbackCol[1] = 64;
    GlobalStageSetting.feedbackCol[2] = 64;
    GlobalStageSetting.feedbackCol[3] = 128;

    GlobalStageSetting.antiLevel0 = 24;
    GlobalStageSetting.antiLevel1 = 24;

    for (i = 0; i < 4; i++) {
        int *row = (int *)&GlobalStageSetting + i * 4;

        row[0x130 / 4] = 128;
        row[0x134 / 4] = 128;
        row[0x138 / 4] = 128;
        row[0x13C / 4] = (i + 1) * 8;
        GlobalStageSetting.subMotionBlur[i] = 32;
        GlobalStageSetting.antiLevel[i].a = 0;
        GlobalStageSetting.antiLevel[i].b = 0;
    }

    GlobalStageSetting.grainScale = 3.0f;

    GlobalStageSetting.handCameraLimitP = 120;
    GlobalStageSetting.handCameraLimitV = 80;
    GlobalStageSetting.zoomMaxInDemo = 200;

    tex_RemakeRegistersSampleMin(0);
}

inline char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *lay, int a5, int a6, int a7)
{
    ObjKindEnt *layout = &objKindData[id];
    char *gobj = CreateGObj(layout, id, a5, a6, a7);
    int dobj = CSVSYSTEM_InitDObj(a1, lay);
    int (*fn)(char *, int);

    *(int *)&((GObj *)gobj)->dobj = dobj;
    ((Sub15C *)dobj)->accessary = a2;

    light_AddLight(gobj, a3, 1);

    fn = layout->create;
    if (fn != 0) {
        GOBJ_SUB(gobj)->work = fn(gobj, lay);
    }
    return gobj;
}

typedef union {
    long long flag;
    GamesysObjInfo info;
} GamesysObjInfoFlag;

/* RECONSTRUCTION: the 0x40-byte actor-init record CreateLayoutedGObj hands to the
   kind's constructor: position, angle and scale as VU0 vectors, then the
   generator's word at 0x38.  The vectors' 16-byte alignment is what makes gcc
   copy the record with eight ld/sd pairs, and the record has exactly the four
   members initSceneGObj's constructor names, so store_constructor fills the
   temporary without clearing it first (the ROM has no clear); 0x34..0x3F is
   the alignment tail, copied but never written. */
typedef struct {
    sceVu0FVECTOR pos;   /* 0x00 */
    sceVu0FVECTOR ang;   /* 0x10 */
    sceVu0FVECTOR scale; /* 0x20 */
    int f30;             /* 0x30 */
} ActInit;

/* sceneManager.c:118-127: the static helper that restores the position the
   previous stage stored through MoveNextStage_Set.  It is fully inlined in the
   ROM, so it has no symbol and no census row; the name follows its two siblings
   MoveNextStage_Set and MoveNextStage_Clear. */
static inline void MoveNextStage_Get(ActInit *a, int kind)
{
    if (stage_no == nextStageNo && kind == 1) {
        a->pos[0] = nextStagePos[0];
        a->pos[1] = nextStagePos[1];
        a->pos[2] = nextStagePos[2];
        a->ang[1] = nextStageRot[1] * 3.1415927f / 180.0f;
    }
}

/* kept local: this TU passes a 64-bit process priority where the prototype in
   gobj_process.h carries an int, and the ROM's `dsll $8, $2, 10` proves the
   fifth argument is 64 bits wide. */

void initSceneGObj(int stage, int no)
{
    ActInit a;
    GenGeo *gen = &objLayout[no];
    ObjKindEnt *lay = &objKindData[gen->kind];
    GamesysObjInfo *info = gamesysObjInfoGet(gen->kind, no);
    int mdl = gen->mdl;
    int st;
    GObj *gobj;
    float ry;
    int sno;
    long long pri;
    unsigned short fld;

    if (info != 0) {
        sno = info->stage;
        if (sno != stage) {
            return;
        }

        ((GamesysObjInfoFlag *)info)->flag |= 1;

        if (stageData[sno].flag1 == 1 && gamesysGirlStageGet() != sno) {
            switch (gen->kind) {
            case 4:
                ReturnEnemyToGenerator(no);
            case 15:
            case 33:
                gamesysObjInfoCls(gen->kind, no);
                info = 0;
                break;
            }
        }
    }

    debug_StdPrintfDummy("try layout index=[%d] model_id=[%d]------------\n", no, mdl);

    st = 0;

    if (lay->layouted != 0) {
        /* sceneManager.c:394 holds the whole fill and the copy into a: one
           statement, a constructor built in a temporary and assigned (the
           construct ico2/ito/src/lightning.c uses for its LightningVtx). */
        a = (ActInit){
            {-gen->pos[0], -gen->pos[1], -gen->pos[2], 1.0f},
            {gen->rot[0] * 3.1415927f / 180.0f, 0.0f, gen->rot[2] * 3.1415927f / 180.0f, 0.0f},
            {gen->scale[0], gen->scale[1], gen->scale[2], 1.0f},
            gen->initArg};

        ry = gen->rot[1];
        if (ry > 180.0f) {
            ry -= 360.0f;
        }
        if (gen->rot[1] < -180.0f) {
            ry += 360.0f;
        }
        a.ang[1] = ry * 3.1415927f / 180.0f;

        if (info != 0) {
            if (lay->infoInit != 0) {
                lay->infoInit(&a, info);
            } else {
                a.pos[0] = info->pos[0];
                a.pos[1] = info->pos[1];
                a.pos[2] = info->pos[2];
                a.ang[0] = info->rot[0];
                a.ang[1] = info->rot[1];
                a.ang[2] = info->rot[2];
                st = info->work[0];
            }
        }

        MoveNextStage_Get(&a, gen->kind);

        gobj = CreateLayoutedGObj(gen->kind, mdl, gen->accessary, gen->light & 0x1F, &a, no,
                                  (gen->flags >> 14) & 7, 0);

        fld = gen->procPri;
        pri = 0x1800;
        if (fld != 0) {
            pri = (long long)fld << 10;
        }

        if (gen->proc != 0) {
            isysGObjProcAddS(gobj, gen->proc, 0, 0x13, pri);
        } else if (lay->start != 0) {
            isysGObjProcAddS(gobj, lay->start, 0, 0x13, pri);
        }

        if (gen->kind == 1) {
            boyGObj = gobj;
        }
        if (gen->kind == 2) {
            girlGObj = gobj;
        }

        if (info != 0 && lay->infoLoad != 0) {
            lay->infoLoad(gobj, info);
        }

        if (st == 4) {
            backStageGirlTargetEnemyGop = gobj;
        }

        if (gen->outGObj != 0) {
            *gen->outGObj = (char *)gobj;
        }

        brainStatusDefaultSet(&brainGirl, (int)gobj, no);

        eBrainStatusSet(gobj, gen->kind);

        ActSetStartBrainStatus(gobj, st);
    }

    MakeCollisionDependGObjList();
}

/* sceneManager.c:486-514 in the listing.  The parent id is read before the
   kind, so the kind load carries the record pointer's death: sched1 raises
   both loads to one priority and then prefers the lighter register weight,
   issues the kind load first and keeps the record live past it, which is
   what gives the ROM its registers and lets reorg put the parent load in the
   first branch's slot.  The listing's rows cannot say where the read stood (the
   load sits in that slot, under row 490; rows 487 and 488 hold the record
   and the layout row, 489 is code-free), so the declaration here is ours.
   The three tests share row 490, one condition; each assert pair shares its
   row, 502 and 511, the line numbers it passes. */
void initParentLink(int id)
{
    GenGeo *gen = &objLayout[id];
    int parentId = gen->parent;
    ObjKindEnt *lay = &objKindData[gen->kind];
    int self;
    int parent;

    if (lay->layouted != 0 && parentId != 0 && gen->kind != 4) {
        self = (int)isysGObjSearchFromObjLayoutID(id);
        parent = (int)isysGObjSearchFromObjLayoutID(parentId);
        if (parent != 0) {
            if (parent == self) {
                /* tried to make "%s" a parent-child link, but it is trying to be its own
                   parent */
                debug_StdPrintfDummy(
                    "\"%s\"の親子関係づけをしようとしましたが、自分を親にしようとしています。\n",
                    lay);
                debug_assert(__FILE__, 502);
                __assert(__FILE__, 502, "0");
            }
            debug_StdPrintfDummy("Parentize \"%s\"\n", lay);
            *(int *)((int)GOBJ_SUB(self)) = parent;
            *(int *)((int)GOBJ_SUB(self) + 4) = 0;
        } else {
            /* tried to make "%s" a parent-child link, but the parent cannot be found */
            debug_StdPrintfDummy("\"%s\"の親子関係づけをしようとしましたが、親が見つかりません。\n",
                                 lay);
            debug_assert(__FILE__, 511);
            __assert(__FILE__, 511, "0");
        }
    }
}

/* sceneManager.c:519-536, 553-570, 606-617: three static helpers the listing
   inlines into InitSceneObjects; they have no symbol of their own in the ROM
   and no census row, so the names below are descriptive. */

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
        GenGeo *gen = &objLayout[gobj[2]];

        gen->flags |= 0x200000;
    }
}

static inline void initGamesysSceneGObjs(int stage)
{
    GamesysObjInfoFlag *p = (GamesysObjInfoFlag *)gameSysObjInfo;
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

void InitSceneObjects(int stage)
{
    GObj *cam;

    ResetGObjProc();
    boyGObj = girlGObj = 0;
    boyPad = 0;
    girlPad = 0;
    gameover_flag = 0;
    gameover_layout_flag = 0;
    itemWatchOff = 0;

    debug_StdPrintfDummy("[\033[42m scene %d \033[m ]\n", stage);

    gsb_SetZoom(1.0f, 1000.0f);
    brainInit();
    ACTGameView_Init();

    gamesysObjInfoStageInitFlagCls();

    backStageGirlTargetEnemyGop = 0;
    fightSoundProcessRequestStart();

    CreateClipCollisionManagerGObj();

    CreateWaySystemManagerGObj();

    cam = InitCameraGObjs(stage, 0, 1);

    initSceneGObjRange(stage, 2, 6);
    initSceneGObjRange(stage, stageData[stage].labelTop, stageData[stage].labelEnd);
    initGamesysSceneGObjs(stage);

    if (girlGObj != 0) {
        isysGObjMoveAfterGObj(girlGObj, cam);
    }
    if (boyGObj != 0) {
        isysGObjMoveAfterGObj(boyGObj, cam);
    }

    setEnemyGeneratorDispFlag();

    InitCamera();

    initWayData(stage);

    MakeExitAttributeIndex();
}

int HotInitSceneObjects(int a0)
{
    GObj *node = isysGObjGetExist_begin();
    if (node != 0) {
        do {
            int idx = ((GObj *)node)->kind;
            if (idx >= 0) {
                ObjKindEnt *e = &objKindData[idx];
                void (*fn)(int *);
                if (e->before != 0) {
                    iosOmSendMail(node, 0x2F, (int)node);
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
