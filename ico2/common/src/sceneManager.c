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
#include "generator.h"
#include "ebrain.h"
#include "act.h"
#include "debug_exception.h"
#include "Texture.h"

/* .sbss: the three frame counts
   GetStageStartInfo hands back, which boyact's stage-entry action waits out in
   turn (before the motion, during it, after it). */
static int stageStartWait1; /* derived name */

static int stageStartWait2; /* derived name */

static int stageStartWait3; /* derived name */

/* .sdata: set while MoveNextStage_Set's request stands, and the stage it is for. */
static char nextStageSet = 0; /* derived name */

static int nextStageNo = -1; /* derived name */

/* .bss: the position and rotation MoveNextStage_Set keeps for the next
   stage and MoveNextStage_Get restores, as VU0 vectors. */
static sceVu0FVECTOR nextStagePos; /* derived name */

static sceVu0FVECTOR nextStageRot; /* derived name */

#include "sceneManager.h"
#include "backStage.h"
#include "typedef.h"
#include "include_asm.h"

/* .data, owned by sceneManager.o: the default layout a scene object is
   created with, at the origin, unrotated, at unit scale. */
SObjSimpleSetting InitialSObjSimpleSetting = {
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    0,
};

inline void MoveNextStage_Set(float *pos, float *rot, int wait1, int wait2, int wait3, int stage)
{
    nextStagePos[0] = pos[0];
    nextStagePos[1] = pos[1];
    nextStagePos[2] = pos[2];
    stageStartWait1 = wait1;
    stageStartWait2 = wait2;
    stageStartWait3 = wait3;
    nextStageNo = stage;
    nextStageRot[0] = rot[0];
    nextStageRot[1] = rot[1];
    nextStageRot[2] = rot[2];
    nextStageSet = 1;
}

inline void test_nextstage_firstwalk_set(int unused, int wait1, int wait2, int wait3)
{
    stageStartWait1 = wait1;
    stageStartWait2 = wait2;
    stageStartWait3 = wait3;
}

inline int GetStageStartInfo(GObj *self, int a1, int a2, int *wait1, int *wait2, int *wait3)
{
    int ret = 1;
    if (exit_no == 0) {
        *wait3 = 1;
        *wait2 = 1;
        *wait1 = 1;
    } else {
        *wait1 = stageStartWait1;
        *wait2 = stageStartWait2;
        *wait3 = stageStartWait3;
        if (*wait2 == 0)
            ret = 0;
        if (*wait1 == 0)
            *wait1 = 1;
        if (*wait2 == 0)
            *wait2 = 1;
        if (*wait3 == 0)
            *wait3 = 1;
    }
    *wait2 = 0x32;
    return ret;
}

inline void MoveNextStage_Clear(void)
{
    nextStageSet = 0;
    nextStageNo = -1;
}

static int GetRealModelId(int stageNo, char *gen)
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

/* GlobalStageSetting is the system's StageSetting record (typedef.h).  The
   stage-preset record is read through the stageData[stage] subscript on every
   line. */
INCLUDE_ASM(InitStageLight);

typedef union { /* field names derived */
    long long flag;
    GamesysObjInfo info;
} GamesysObjInfoFlag; /* derived name */

/* restores the position the previous stage stored through MoveNextStage_Set;
   named after its siblings MoveNextStage_Set and MoveNextStage_Clear */
static inline void MoveNextStage_Get(SObjSimpleSetting *a, int kind) /* derived name */
{
    if (stage_no == nextStageNo && kind == 1) {
        a->pos[0] = nextStagePos[0];
        a->pos[1] = nextStagePos[1];
        a->pos[2] = nextStagePos[2];
        a->rot[1] = nextStageRot[1] * 3.1415927f / 180.0f;
    }
}

static void initSceneGObj(int stage, int no);

INCLUDE_ASM(initSceneGObj);

static void initParentLink(int id);

INCLUDE_ASM(initParentLink);

/* three static helpers inlined into InitSceneObjects */

static inline void initSceneGObjRange(int stage, int first, int last) /* derived name */
{
    int i;

    for (i = first; i < last; i++) {
        initSceneGObj(stage, i);
    }

    for (i = first; i < last; i++) {
        initParentLink(i);
    }
}

static inline void setEnemyGeneratorDispFlag(void) /* derived name */
{
    GObj *gobj;

    for (gobj = isysGObjSearchFromObjKindID_begin(4); gobj != 0;
         gobj = isysGObjSearchFromObjKindID_next(gobj)) {
        GenGeo *gen = &objLayout[gobj->labelId];

        gen->flags |= 0x200000;
    }
}

static inline void initGamesysSceneGObjs(int stage) /* derived name */
{
    GamesysObjInfoFlag *p = (GamesysObjInfoFlag *)gameSysObjInfo;
    int i;

    for (i = 0; i <= 181; i++, p++) {
        if (p->info.no != 0 && (p->flag & 1) == 0 && p->info.stage == stage) {
            initSceneGObj(stage, p->info.no);
        }
    }
}

static void initWayData(int stage)
{
    ExtractWayData(stage);
}

void InitSceneObjects(int stage)
{
    GObj *cam;

    ResetGObjProc();
    boyGObj = girlGObj = 0;
    boyPad = 0;
    gameover_flag = 0;
    gameover_layout_flag = 0;

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
                void (*fn)(GObj *);
                if (e->before != 0) {
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

INCLUDE_ASM(ChangeStageStartInfo);

INCLUDE_ASM(CreateLayoutedGObj);
