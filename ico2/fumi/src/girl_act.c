#include "common.h"
#include "girl_act.h"
#include "debug.h"
#include "pad.h"
#include "obj_manager.h"
#include "act-way.h"
#include "way_sys.h"
#include "brain.h"
#include "gflag.h"
#include "Primitive.h"
#include "box.h"
#include "matrixDrive.h"
#include "motionOrientManager.h"
#include "quaternion.h"
#include <stdlib.h>
#include "geometryManager.h"
#include "typedef.h"

typedef struct {
    char _0[0x20];
    float f_20; /* 0x20 */
    char _24[0x0C];
    float sub30[4];     /* 0x30 */
    float sub40[4];     /* 0x40 */
    float f_50;         /* 0x50 */
    float f_54;         /* 0x54 */
    unsigned char f_58; /* 0x58 */
    unsigned char f_59;
    unsigned char f_5A;
    unsigned char f_5B;
    unsigned char f_5C;
    unsigned char f_5D;
    unsigned char f_5E;
} GirlStand;

union GAIF {
    int i;
    float f;
};

/* kept local: this TU's uses of GetSkeltonFocusNode do not fit the prototype in motionManager2.h */
extern int GetSkeltonFocusNode(void *obj, int kind);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);

void GetEyeDirection(char *dir, char *obj)
{
    int node = GetSkeltonFocusNode(obj, 0x23);
    if (*(int *)(obj + 0xC) == 4) {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = -1.0f;
        *(int *)(dir + 0x8) = 0;
    } else {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = 1.0f;
        *(int *)(dir + 0x8) = 0;
    }
    *(int *)(dir + 0xC) = 0;
    sceVu0ApplyMatrix(dir, (char *)(GOBJ_SUB(obj)->f_C + (node << 6)), dir);
}

/* kept local: this TU's uses of ACTGame_DisconnectHand do not fit the prototype in act-game.h */
extern void ACTGame_DisconnectHand(void);
extern char D_00553990[];

void funcGirlHandDisconnect(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy(D_00553990);
}

extern char D_005539E8[];
extern int *D_00639EA4;
extern char *D_0063A61C;
/* kept local: this TU's uses of ACTSendMailCorrect do not fit the prototype in commonact.h */
extern void ACTSendMailCorrect(void *a0, int mail);
/* kept local: this TU's uses of _ACTWait do not fit the prototype in act.h */
extern void _ACTWait(int n);

void motGirlHand50(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_005539E8);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x5C, D_0063A61C);
        if (sub->f_E0 & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(a0)->f_4A0 < 0x214 || !(GOBJ_SUB(a0)->f_4A0 < 0x21B)) {
        *(void **)((char *)sub + 0x130) =
            SetMotionRequest((void *)a0, 1, *(MotOriReq *)((char *)sub + 0x620));
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x5D, D_0063A61C);
        if (sub->f_E0 & 2)
            break;
        _ACTWait(1);
    }
    if ((((int)(*(unsigned long long *)((char *)sub + 0x18) >> 44)) & 1) == 0) {
        iosOmSendMail(D_00639EA4, 0x10, D_0063A61C);
        ACTSendMailCorrect((void *)a0, 7);
    }
    iosOmSendMail(D_00639EA4, 0x5E, D_0063A61C);
    *(void **)((char *)sub + 0x130) =
        SetMotionRequest((void *)a0, 0x5E, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)(*(char **)((char *)sub + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->f_14 = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern char D_00553A18[];

void motGirlHand100(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00553A18);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x61, D_0063A61C);
        if (sub->f_E0 & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(a0)->f_4A0 < 0x214 || !(GOBJ_SUB(a0)->f_4A0 < 0x21B)) {
        *(void **)((char *)sub + 0x130) =
            SetMotionRequest((void *)a0, 1, *(MotOriReq *)((char *)sub + 0x620));
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x62, D_0063A61C);
        if (sub->f_E0 & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(D_00639EA4, 0x63, D_0063A61C);
    *(void **)((char *)sub + 0x130) =
        SetMotionRequest((void *)a0, 0x65, *(MotOriReq *)((char *)sub + 0x620));
    while (GOBJ_SUB(a0)->f_4A0 < 0x214 || !(GOBJ_SUB(a0)->f_4A0 < 0x21B)) {
        *(void **)((char *)sub + 0x130) =
            SetMotionRequest((void *)a0, 1, *(MotOriReq *)((char *)sub + 0x620));
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x64, D_0063A61C);
        if (sub->f_E0 & 8)
            break;
        _ACTWait(1);
    }
    sub->f_14 = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern char D_00553A48[];
extern char D_00553A60[];
extern char D_0063A880[];
extern char D_0063A888[];
extern int D_0028F4C0[];

void motGirlHand200(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int n;

    debug_StdPrintfDummy(D_00553A48);
    n = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2;
    while (1) {
        if (n <= 0)
            goto expired;
        n--;
        iosOmSendMail(D_00639EA4, 0x66, D_0063A61C);
        if (sub->f_E0 & 1)
            break;
        _ACTWait(1);
    }
    goto held;
expired:
    ACTSendMailCorrect((void *)a0, 0x6A);
    debug_StdPrintfDummy(D_00553A60, (void *)a0 == (void *)D_00639EA4 ? D_0063A880 : D_0063A888);
held:
    while (GOBJ_SUB(a0)->f_4A0 < 0x214 || !(GOBJ_SUB(a0)->f_4A0 < 0x21B)) {
        *(void **)((char *)sub + 0x130) =
            SetMotionRequest((void *)a0, 1, *(MotOriReq *)((char *)sub + 0x620));
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x67, D_0063A61C);
        if (sub->f_E0 & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(D_00639EA4, 0x68, D_0063A61C);
    *(void **)((char *)sub + 0x130) =
        SetMotionRequest((void *)a0, 0x66, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)(*(char **)((char *)sub + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        iosOmSendMail(D_00639EA4, 0x69, D_0063A61C);
        if (sub->f_E0 & 8)
            break;
        _ACTWait(1);
    }
    sub->f_14 = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern Brain D_002A5580[];

void GirlBrainClearTarget(void)
{
    brainClsTargetLevel(D_002A5580);
}

/* kept local: this TU's uses of ACTGame_SetMotionPlaySpeedRatio_Reserve do not fit the prototype in act-game.h */
extern void ACTGame_SetMotionPlaySpeedRatio_Reserve(void *a0, float f, int a1);

void SetTurnSpeedInEscape(char *a0)
{
    if (GOBJ_ACT(a0)->unk34 == 10) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve(a0, 1.5f, 5);
    }
}

/* The hide/others/listB/listD object lists.  Layout derived from the ROM:
   0x30 per entry, 100 entries per list, and the four lists sit exactly 0x12D0
   apart inside GirlBrainWork (others 0xC90, listB 0x1F60, hide 0x3230,
   listD 0x4500).  The `long long` at 0x08 is the alignment carrier that makes
   the record copy come out as six ld/sd pairs rather than ldl/ldr. */
typedef struct {
    void *obj; /* 0x00 */
    int _04;
    long long _08;
    float pos[4]; /* 0x10 */
    float dist;   /* 0x20 */
    int flags;    /* 0x24 */
    int _28[2];
} GirlListEnt;

typedef struct {
    int num; /* 0x00 */
    char _04[0x0C];
    GirlListEnt ent[100]; /* 0x10 */
} GirlList;

typedef struct {
    unsigned char f_0; /* 0x00 */
    unsigned char f_1; /* 0x01 */
    char _2[0xC8E];
    GirlList others;  /* 0x0C90 */
    GirlList listB;   /* 0x1F60 */
    GirlList hide;    /* 0x3230 */
    GirlList listD;   /* 0x4500 */
    void *target;     /* 0x57D0 the brain's current target gobj             */
    void *lastTarget; /* 0x57D4 the target the last DecideMode pass saw      */
    char _57D8[0x08];
    int targetFlag; /* 0x57E0 bit 16 of the winning BrainTarget's b18 word */
    char _57E4[0x0C];
    float f_57F0[4]; /* 0x57F0 the runaway goal            */
    float f_5800[4]; /* 0x5800 last accepted hide point    */
    float f_5810[4]; /* 0x5810 */
    float f_5820[4]; /* 0x5820 */
    float f_5830[4]; /* 0x5830 the girl's own position     */
    float f_5840[4]; /* 0x5840 */
    float f_5850[4]; /* 0x5850 */
    int f_5860;      /* 0x5860 */
    char _5864[0x8C];
    unsigned char f_58F0; /* 0x58F0 */
    char _58F1[0x03];
    int f_58F4;  /* 0x58F4 */
    int runMode; /* 0x58F8 */
    int wait;
    int timer;
    int limit;
    int f_5908; /* 0x5908 */
    char _590C[0x04];
    int f_5910; /* 0x5910 */
    int f_5914; /* 0x5914 */
} GirlBrainWork;

extern char D_0029D650[];

/* The head of the TU's .data, in ROM run order (VMA 0x29D420..0x29D64C; the
   brain work record at 0x29D650 and the hand manager follow and stay in the
   blob while the TU spells them through casts): the danger-environment
   initial value, the
   brain mode table (the mode's routine and its flag byte), the object kinds
   the others list gathers (-1 ends it) and their debug names, the run-mode
   rows ChangeRunMode indexes, the three attract parameter sets, the
   debug names of the move states, the three escape angles and the debug
   names of the attract states.  Every array and record is placed on an
   8-byte boundary, which is where the zero words between them come from. */
typedef struct {
    int kind;
    void *obj;
    void *save;
    int count;
} GirlDangerEnv;

typedef struct {
    void (*proc)(int a0);
    unsigned char flag;
} GirlBrainMode;

typedef struct {
    float _00[4];
    float _10[4];
    int kind; /* 0x20 */
    int mail; /* 0x24 */
    float f_28;
    float f_2C;
    unsigned char f_30;
    char _31[0x0F];
    float pos[4]; /* 0x40 */
    unsigned char f_50;
    char _51[3];
    float f_54;
    char _58[8];
} GirlAttractParam;

void subGirlBrain_Idle(volatile int a0);
void subGirlBrain_Attract(volatile int a0);
void subGirlBrain_Escape(volatile int a0);
void subGirlBrain_Hide(volatile int a0);
void subGirlBrain_Hesitate(volatile int a0);
void subGirlBrain_Becarry(volatile int a0);
void subGirlBrain_Busy(volatile int a0);
void subGirlBrain_Pulledup(volatile int a0);
void subGirlBrain_DangerEnv(volatile int a0);
void subGirlBrain_HideAdvance(volatile int a0);
extern char D_0063A8B0[];
extern char D_0063A8B8[];
extern char D_0063A8C8[];
extern char D_0063A8D0[];
extern char D_0063A8D8[];
extern char D_0063A8F0[];
extern char D_0063A8F8[];
extern char D_0063A900[];
extern char D_00553AA8[];
extern char D_00553AB8[];
extern char D_00553C10[];
extern char D_00553C20[];
extern char D_00553C88[];
extern char D_00553C98[];
extern char D_00553CA8[];
extern char D_00553CB8[];
extern char D_00553CC8[];

GirlDangerEnv D_0029D420 = {0};

GirlBrainMode D_0029D430[10] = {
    {subGirlBrain_Idle, 0},        {subGirlBrain_Attract, 0},  {subGirlBrain_Escape, 1},
    {subGirlBrain_Hide, 1},        {subGirlBrain_Hesitate, 1}, {subGirlBrain_Becarry, 0},
    {subGirlBrain_Busy, 0},        {subGirlBrain_Pulledup, 0}, {subGirlBrain_DangerEnv, 0},
    {subGirlBrain_HideAdvance, 1},
};

int D_0029D480[3] = {4, 62, -1};

static char *D_0029D490[4] = {D_0063A8B8, D_00553AB8, D_00553AA8, D_0063A8B0};

static int D_0029D4A0[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {2, 1, 1, 0},
    {3, 2, 1, 1},
};

GirlAttractParam D_0029D4E0 = {{0}, {0}, 0, 338, 100.0f, 100.0f};

GirlAttractParam D_0029D540 = {{0}, {0}, 68, 267, 50.0f, 100.0f, 1, {0}, {0}, 0, {0}, 200.0f};

GirlAttractParam D_0029D5A0 = {{0}, {0}, 0, 338, 100.0f, 70.0f};

char *D_0029D600[5] = {D_0063A8D8, D_00553C20, D_00553C10, D_0063A8D0, D_0063A8C8};

static int D_0029D618[3] = {0, -90, 90};

static char *D_0029D628[9] = {D_0063A8D8, D_00553CC8, D_00553CB8, D_00553CA8, D_0063A900,
                              D_0063A8F8, D_00553C98, D_00553C88, D_0063A8F0};

/* The TU's .bss, in ROM run order (VMA 0x6C1180..0x6C1E50): sort_list's
   index/distance pairs and its copy of the sorted positions, CorrectList's
   compaction scratch and the runaway candidate list (ten positions each),
   subGirlBrain_Escape's debug string buffer, subGirlCollision's direction
   request (priority, direction, the vector at +0x10) and the current danger
   environment (VMA 0x6C1E40..0x6C1E50; subGirlBrainMain copies D_0029D420
   into it and the Danger_* routines read its object). */
typedef struct {
    int idx;
    float dist;
} GirlSortEnt;

static GirlSortEnt D_006C1180[100];

static float D_006C14A0[100][4];

static float D_006C1AE0[10][4];

static float D_006C1B80[10][4];

static char D_006C1C20[512];

static int D_006C1E20[8];

static GirlDangerEnv D_006C1E40;

extern void *D_00639EA8;
extern char D_002A2E70[];
/* kept local: this TU's uses of ACTGameView_Check do not fit the prototype in act-game.h */
extern int ACTGameView_Check(void *self, void *target);
/* kept local: this TU's uses of _DistSqGV do not fit the prototype in gv.h */
extern float _DistSqGV(void *a, void *b);
/* kept local: this TU's uses of _DistGV do not fit the prototype in gv.h */
extern float _DistGV(void *a, void *b);
/* kept local: this TU's uses of GetRootProjectionPosOfGObj do not fit the prototype in motionManager2.h */
extern void GetRootProjectionPosOfGObj(void *out, void *obj);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_begin do not fit the prototype in gobj.h */
extern void *isysGObjSearchFromObjKindID_begin(int kind);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_next do not fit the prototype in gobj.h */
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern int EnemyBrainStatus_Boy(void *gobj);
int enemy_list_compare(int a0, int a1);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern char D_00553A70[];
extern char D_00553A88[];
extern char D_0063A8A0[];
/* the marker text "III", the anonymous literal after the assert's "0" */
extern char D_0063A8A8[];

/* girl_brain_main.c.inc:279-293: the wire-string marker (colour, a
   MatrixDrive transform of the position, DispWireString, colour reset),
   compiled out in this build: an empty debug inline.  The name is ours.
   WHAT THE BYTES PIN: the ROM keeps the loop at 559 with no body and the
   "III" literal at 0x63A8A8 that only this chain loads, and its register
   allocation needs the chain at cse1/gcse: the switch in
   girlDispHidePoint keeps a label in that loop's body through cse1, jump2
   then merges the emptied body into the loop test's block, and gcse finds
   two (high D_0029D650) there; the copy it inserts after the second
   re-sets its reaching register inside the loop, which gives the ROM's
   `daddu $30,$22,$0` before the countdown, the $30/$22 pair from the
   prologue on and the base copy before the last loop.  With the loop
   empty, or with the colour code alone (jump1 turns it into conditional
   moves), those words are lost.
   WHAT THEY CANNOT PIN: the switch and colour text beyond the listing's
   lines, the helpers' parameter order, their names. */
static inline void girlDispWire(int r, int g, int b, float *pos, char *str) {}

/* girl_brain_main.c.inc:297-304: the marker colour for a hide point. */
static inline void girlDispHidePoint(float *pos, int c)
{
    int r = 0;
    int g = 0;
    int b = 0;

    switch (c) {
    case 'R':
        r = 255;
        break;
    case 'B':
        b = 255;
        break;
    case 'W':
        r = 255;
        g = 255;
        b = 255;
        break;
    case 'Y':
        g = 255;
        b = 255;
        break;
    }
    girlDispWire(r, g, b, pos, D_0063A8A8);
}

/* girl_brain_main.c.inc:366-369 */
static inline int girlListIsOnBoy(void *gobj)
{
    if (*(int *)((char *)gobj + 0xC) != 4) {
        return 1;
    }
    return EnemyBrainStatus_Boy(gobj);
}

/* girl_brain_main.c.inc:375-378 */
static inline int girlListIsAlive(void *gobj)
{
    return (int)(*(unsigned long long *)((char *)GOBJ_ACT(gobj) + 0x18) >> 32) & 1;
}

/* girl_brain_main.c.inc:408-420: the flag-masked record copy the three
   sub-lists share */
static inline int girlListPick(GirlListEnt *src, GirlListEnt *dst, int n, int mask)
{
    int cnt = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (src[i].flags & mask) {
            dst[cnt] = src[i];
            cnt++;
        }
    }
    return cnt;
}

void girlBrainMain_MakeOthersList(void)
{
    /* girl_brain_main.c.inc:428-456, a GNU nested function: the ROM homes the
       incoming static chain with `sw $2,0($sp)` and both call sites load it
       with `daddu $2,$29,$0`. */
    void sort_list(float *list, int n)
    {
        GirlSortEnt t;
        int i;
        int j;

        for (i = 0; i < n; i++) {
            D_006C1180[i].idx = i;
            D_006C1180[i].dist = _DistSqGV(list + i * 4, D_002A2E70);
        }
        for (i = 0; i < n; i++) {
            for (j = n - 1; i < j; j--) {
                if (D_006C1180[j].dist < D_006C1180[j - 1].dist) {
                    t = D_006C1180[j];
                    D_006C1180[j] = D_006C1180[j - 1];
                    D_006C1180[j - 1] = t;
                }
            }
        }
        for (i = 0; i < n; i++) {
            float *d = D_006C14A0[i];

            d[0] = list[i * 4 + 0];
            d[1] = list[i * 4 + 1];
            d[2] = list[i * 4 + 2];
        }
        for (i = 0; i < n; i++) {
            float *e = D_006C14A0[D_006C1180[i].idx];

            list[i * 4 + 0] = e[0];
            list[i * 4 + 1] = e[1];
            list[i * 4 + 2] = e[2];
        }
    }
    float d;
    int seen;
    int i;
    int j;
    int k;

    ((GirlBrainWork *)D_0029D650)->hide.num = ((GirlBrainWork *)D_0029D650)->listB.num = 0;
    for (i = 0; D_0029D480[i] != -1; i++) {
        void *o;

        for (o = isysGObjSearchFromObjKindID_begin(D_0029D480[i]); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (girlListIsAlive(o) && girlListIsOnBoy(o)) {
                if (!(((GirlBrainWork *)D_0029D650)->hide.num < 100)) {
                    debug_StdPrintfDummy(D_00553A70);
                    debug_assert(D_00553A88, 485);
                    __assert(D_00553A88, 485, D_0063A8A0);
                }
                GetRootPosition(((GirlBrainWork *)D_0029D650)
                                    ->hide.ent[((GirlBrainWork *)D_0029D650)->hide.num]
                                    .pos,
                                o);
                ((GirlBrainWork *)D_0029D650)->hide.num++;
            }
        }
    }
    sort_list(((GirlBrainWork *)D_0029D650)->listB.ent[0].pos,
              ((GirlBrainWork *)D_0029D650)->listB.num);
    sort_list(((GirlBrainWork *)D_0029D650)->hide.ent[0].pos,
              ((GirlBrainWork *)D_0029D650)->hide.num);
    ((GirlBrainWork *)D_0029D650)->others.num = 0;
    for (i = 0; D_0029D480[i] != -1; i++) {
        void *o;

        for (o = isysGObjSearchFromObjKindID_begin(D_0029D480[i]); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (girlListIsAlive(o)) {
                int n = ((GirlBrainWork *)D_0029D650)->others.num;

                ((GirlBrainWork *)D_0029D650)->others.ent[n].obj = o;
                GetRootProjectionPosOfGObj(((GirlBrainWork *)D_0029D650)->others.ent[n].pos, o);
                ((GirlBrainWork *)D_0029D650)->others.ent[n].dist =
                    _DistGV(((GirlBrainWork *)D_0029D650)->others.ent[n].pos,
                            ((GirlBrainWork *)D_0029D650)->f_5830);
                ((GirlBrainWork *)D_0029D650)->others.ent[n].flags = 1;
                if (girlListIsOnBoy(o)) {
                    ((GirlBrainWork *)D_0029D650)->others.ent[n].flags |= 2;
                }
                ((GirlBrainWork *)D_0029D650)->others.num++;
            }
        }
    }
    qsort(((GirlBrainWork *)D_0029D650)->others.ent, ((GirlBrainWork *)D_0029D650)->others.num,
          sizeof(GirlListEnt), enemy_list_compare);
    ((GirlBrainWork *)D_0029D650)->listB.num = girlListPick(
        ((GirlBrainWork *)D_0029D650)->others.ent, ((GirlBrainWork *)D_0029D650)->listB.ent,
        ((GirlBrainWork *)D_0029D650)->others.num, 0xC);
    ((GirlBrainWork *)D_0029D650)->hide.num = girlListPick(
        ((GirlBrainWork *)D_0029D650)->others.ent, ((GirlBrainWork *)D_0029D650)->hide.ent,
        ((GirlBrainWork *)D_0029D650)->others.num, 0xF);
    ((GirlBrainWork *)D_0029D650)->listD.num = girlListPick(
        ((GirlBrainWork *)D_0029D650)->others.ent, ((GirlBrainWork *)D_0029D650)->listD.ent,
        ((GirlBrainWork *)D_0029D650)->others.num, 0xE);
    ((GirlBrainWork *)D_0029D650)->f_0 = 0;
    if (((GirlBrainWork *)D_0029D650)->listB.num != 0 &&
        ((GirlBrainWork *)D_0029D650)->listB.ent[0].dist < 300.0f) {
        ((GirlBrainWork *)D_0029D650)->f_0 = 1;
    }
    ((GirlBrainWork *)D_0029D650)->f_1 = 0;
    if (((GirlBrainWork *)D_0029D650)->listD.num != 0) {
        ((GirlBrainWork *)D_0029D650)->f_1 = 1;
    }
    /* girl_brain_main.c.inc:559-568: a marker at each hide point, coloured
       by the others entry's flags; only its drawing is compiled out (see
       girlDispWire), so the loop stays and counts down empty. */
    for (k = 0; k < ((GirlBrainWork *)D_0029D650)->hide.num; k++) {
        int c = ((GirlBrainWork *)D_0029D650)->others.ent[k].flags & 2 ? 'B' : 'W';

        if (((GirlBrainWork *)D_0029D650)->others.ent[k].flags & 4) {
            c = 'Y';
        }
        if (((GirlBrainWork *)D_0029D650)->others.ent[k].flags & 8) {
            c = 'R';
        }
        girlDispHidePoint(((GirlBrainWork *)D_0029D650)->hide.ent[k].pos, c);
    }
    seen = 0;
    for (i = 0; i < ((GirlBrainWork *)D_0029D650)->hide.num; i++) {
        if (ACTGameView_Check(D_00639EA8, ((GirlBrainWork *)D_0029D650)->hide.ent[i].obj) != 0) {
            seen = 1;
            break;
        }
    }
    if (seen != 0) {
        ((GirlBrainWork *)D_0029D650)->f_5910 = 0;
    } else {
        ((GirlBrainWork *)D_0029D650)->f_5910++;
    }
    if (((GirlBrainWork *)D_0029D650)->others.num != 0 &&
        ((GirlBrainWork *)D_0029D650)->others.ent[0].dist < 600.0f) {
        GOBJ_ACT(D_00639EA8)->flags20.ll |= 0x1000;
    }
    GOBJ_ACT(D_00639EA8)->flags20.ll &= ~0x2000;
    if (((GirlBrainWork *)D_0029D650)->others.num != 0 &&
        ((GirlBrainWork *)D_0029D650)->others.ent[0].dist < 1000.0f) {
        GOBJ_ACT(D_00639EA8)->flags20.ll |= 0x2000;
    }
    GOBJ_ACT(D_00639EA8)->flags20.ll |= 0x400000000000;
    if (((GirlBrainWork *)D_0029D650)->others.num != 0) {
        if (((GirlBrainWork *)D_0029D650)->others.ent[0].dist < 200.0f) {
            GOBJ_ACT(D_00639EA8)->flags20.ll &= ~0x400000000000;
            return;
        }
        d = _DistGV(((GirlBrainWork *)D_0029D650)->f_5830, ((GirlBrainWork *)D_0029D650)->f_5850);
        for (j = 0; j < ((GirlBrainWork *)D_0029D650)->others.num; j++) {
            if (_DistSqGV(((GirlBrainWork *)D_0029D650)->others.ent[j].pos,
                          ((GirlBrainWork *)D_0029D650)->f_5850) < d * d) {
                GOBJ_ACT(D_00639EA8)->flags20.ll &= ~0x400000000000;
                break;
            }
        }
    }
}

/* kept local: this TU's uses of GetMatrixDirectionToZ do not fit the prototype in gv.h */
extern void GetMatrixDirectionToZ(void *m, void *dir);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);

int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n)
{
    float d[4];
    float m[16];
    float v[4];
    int i;
    float dist;
    float flag;
    float dy;

    sceVu0SubVector(d, from, to);
    d[1] = 0.0f;
    GetMatrixDirectionToZ(m, d);
    dist = FSqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    for (i = 0; i < n; i++) {
        flag = *(int *)(*(char **)(*(char **)(list + i * 0x30) + 0x164) + 0x34) == 6 ? 1.0f : 0.0f;
        dy = *(float *)(list + i * 0x30 + 0x14) - from[1] < 0.0f
                 ? -(*(float *)(list + i * 0x30 + 0x14) - from[1])
                 : *(float *)(list + i * 0x30 + 0x14) - from[1];

        if (flag != 0.0f) {
            if (80.0f < dy) {
                continue;
            }
        } else {
            if (200.0f < dy) {
                continue;
            }
        }
        sceVu0SubVector(v, list + i * 0x30 + 0x10, to);
        v[1] = 0.0f;
        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, m, v);

        if (0.0f < v[2]) {
            if (v[2] < dist) {
                if (v[0] * v[0] + v[1] * v[1] < 10000.0f) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

extern int stage_no;
/* kept local: this TU's uses of ACTCheckCollis_WAY do not fit the prototype in act-game.h */
extern int ACTCheckCollis_WAY(void *a0, void *a1, float a2, void *a3, void *a4);
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
/* kept local: this TU's uses of debug_Marker do not fit the prototype in camera-editor.h */
extern void debug_Marker(void *buf, int a1, int a2, int a3, float f12, float f13);

/* girl_brain_main.c.inc:313-317 (rows outside WayTest's span => static inline) */
static inline void dispWayMarker(float *p)
{
    float buf[4];
    sceVu0ScaleVector(buf, p, -1.0f);
    debug_Marker(buf, 0xFF, 0, 0, 70.0f, 0.0f);
}

/* girl_brain_main.c.inc:325-338 (rows outside every caller's span => static
   inline; the listing inlines it at two sites).  True when the candidate hide
   point sits above the girl's floor by more than 100 units. */
static inline unsigned char isHidePointTooHigh(float *p)
{
    GirlBrainWork *b;
    float y;

    if (stage_no == 8 || stage_no == 22) {
        b = (GirlBrainWork *)D_0029D650;
        y = b->f_5830[1] + 100.0f;
        if (y < p[1] || y < b->f_5850[1]) {
            return 1;
        }
    }
    return 0;
}

/* The 0x80-byte way-parameter block the boy's sub-object carries at +0x360; ROM
   copies it with gcc's 4x ld/sd block-move loop, i.e. a struct assignment whose
   member type is 8 bytes wide. */
typedef struct {
    long long d[16];
} GirlWayParam;

/* girl_brain_main.c.inc:620-656, one call site.  `r = 0;` is a STATEMENT after the
   struct copy, not an initialiser. */
static inline int girlBrainHide_TryWay(float *pt, char *way, float *goal, float *hit)
{
    float start[4];
    int r = 0;
    void *girl = D_00639EA4;
    void *self = D_00639EA8;
    Act *sub = GOBJ_ACT(self);

    *(GirlWayParam *)way = *(GirlWayParam *)((char *)sub + 0x360);
    if (GetWay_begin(pt, way, goal)) {
        r = 1;
        start[0] = pt[0];
        start[1] = pt[1];
        start[2] = pt[2];
        start[1] -= 50.0f;
        goal[1] = goal[1] - 30.0f;
        *(int *)(way + 0x44) = 0;
        if (ACTCheckCollis_WAY(goal, start, 10.0f, girl, hit) == 0) {
            *(int *)(way + 0x44) = 1;
            DeleteGuideWay(way);
            r = 3;
        } else if (*(int *)(way + 0x3C) == 0) {
            r = 2;
        }
    }
    return r;
}

int girlBrainMain_CheckWarningMode(unsigned char check)
{
    float hit[4];
    int mode;
    char *w = D_0029D650;

    w[0x58F1] = 1;
    if (((unsigned char *)w)[0] != 0) {
        mode = 2;
    } else {
        mode = ((unsigned char *)w)[1] != 0 ? 4 : 0;
    }
    {
        char *g = D_0029D650;

        if (*(int *)(g + 0x3230) == 0 ||
            (check != 0 && ACTGameView_Check(D_00639EA8, D_00639EA4) == 0)) {
            goto out;
        }
        _girlBrainHide_MakeHidePoint((float *)(g + 0x5800), 200.0f);
        dispWayMarker((float *)(g + 0x5800));
        if (girlBrainHide_TryWay((float *)(g + 0x5800), g + 0x5870, (float *)(g + 0x5830), hit) !=
            3) {
            goto out;
        }
    }
    if (!isHidePointTooHigh((float *)(D_0029D650 + 0x5800)) &&
        !girlBrainHideCheckIntercept((float *)(D_0029D650 + 0x5830), (float *)(D_0029D650 + 0x5800),
                                     D_0029D650 + 0x3240, *(int *)(D_0029D650 + 0x3230))) {
        mode = 3;
    } else {
        char *v = D_0029D650;

        if (*(int *)(v + 0x1F60) != 0 && _DistSqGV(v + 0x5820, v + 0x1F80) < 90000.0f) {
            goto out;
        }
        mode = 4;
    }
out:
    return mode;
}

/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
extern void *test_CURRENTROOT(void *a0);
extern void *D_00639EA0;
extern void _ACTCharStatus_Set(void *obj, int id, float v, int flag);
/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *a, void *b);
/* kept local: this TU's uses of ACTCheckView do not fit the prototype in act-game.h */
extern int ACTCheckView(void *self, void *obj, float *pos, float margin, int range);
/* kept local: this TU's uses of PAIR_IsStatus_BOY_WAIT do not fit the prototype in act-game.h */
extern int PAIR_IsStatus_BOY_WAIT(void);
extern void brainGetTarget(Brain *b);
extern int isEnterHideadv(void);
/* the pad record: the button word at +0 */
extern int D_0028F8F0[];

/* girl_act.c:558-573 in the listing: the brain target pass, inlined into
   girlBrainMain_DecideMode and into subGirlBrainMain. */
static inline void *girlBrainGetTarget(void)
{
    int *flag = &((GirlBrainWork *)D_0029D650)->targetFlag;
    Brain *b = D_002A5580;
    void *obj = 0;

    brainGetTarget(b);
    *flag = 0;
    if (b->idx != -1) {
        obj = (void *)b->tgt[b->idx].gobj;
        *flag = *(unsigned short *)&b->tgt[b->idx].b1A & 1;
    }
    return obj;
}

/* The TU's compiled-out debug print, in cdvd.c's stDebugPrint form: each
   inlined call of the empty body emits no instruction but leaves one
   (use (const_int 0)) insn that gcse and the live-length counts see.  The
   name is ours: an inlined empty body leaves no symbol and no listing row.
   subGirlBrain_Escape's four calls are commented at that function.
   WHAT THE BYTES PIN in girlBrainMain_DecideMode: one zero-code insn inside
   the live range of `near`, the boy-proximity flag the ROM spills to 0x30.
   Without it sched1 leaves the three flags at lengths 315/325/319, which
   local-alloc doubles, and global's priorities (warned 47, changed 46,
   near 47) give $30 to near and spill changed, where the ROM keeps changed
   in $30 and spills near; with it near reaches 640 and ties changed, which
   wins on its lower allocno.  Measured necessary at this site; a second
   print at either sibling flag set (`changed = 1`, `warned = 1`), or one
   at every mode change inside setNext, moves changed below near again,
   which the ROM rules out.
   WHAT THEY CANNOT PIN: the text of the print, or its exact statement
   inside near's range. */
static __inline__ void girlBrainDebugPrint(void) {}

/* girl_act.c:577-585 in the listing. */
static inline float girlBrainGetTargetLevel(void)
{
    if (D_002A5580->idx == -1) {
        return 0.0f;
    }
    return D_002A5580->f20;
}

int girlBrainMain_DecideMode(int mode, int *next)
{
    /* girl_brain_main.c.inc:848-856: two nested helpers; their reference to
       `next` is what homes the parameter at 0($sp) and reloads it per use. */
    __inline void setNext(int m)
    {
        if (D_00639EA0 != 0 && D_0029D430[m].flag != 0) {
            return;
        }
        *next = m;
    }
    __inline void checkWarning(unsigned char c)
    {
        int m = girlBrainMain_CheckWarningMode(c);

        if (0 <= m) {
            setNext(m);
        }
    }
    float gpos[4];
    float opos[4];
    void *o;
    float lv;
    int seen;
    int i;
    void *self = D_00639EA8;
    Act *sub = GOBJ_ACT(self);
    int warned = 0;
    int changed = 0;
    int near = 0;

    gpos[0] = ((float *)test_CURRENTROOT(self))[0];
    gpos[1] = ((float *)test_CURRENTROOT(self))[1];
    gpos[2] = ((float *)test_CURRENTROOT(self))[2];

    if (sub->unk34 == 0x6F) {
        setNext(5);
        return 0;
    }
    ((GirlBrainWork *)D_0029D650)->target = girlBrainGetTarget();

    lv = girlBrainGetTargetLevel() * 10.0f;
    if (3.0f <= lv) {
        sub->flags20.ll |= 0x100000000000;
    }
    if (2.0f <= lv) {
        sub->flags20.ll |= 0x200000000000;
    }
    if (((GirlBrainWork *)D_0029D650)->target != ((GirlBrainWork *)D_0029D650)->lastTarget) {
        ((GirlBrainWork *)D_0029D650)->lastTarget = ((GirlBrainWork *)D_0029D650)->target;
        changed = 1;
    }
    if (((GirlBrainWork *)D_0029D650)->target != 0) {
        _ACTCharStatus_Set(self, 10, -1.0f, (int)((GirlBrainWork *)D_0029D650)->target);
    }
    switch (mode) {
    case 0:
    case 1:
    case 7:
        if (((GirlBrainWork *)D_0029D650)->lastTarget != 0) {
            setNext(1);
        } else {
            setNext(0);
        }
        if (((GirlBrainWork *)D_0029D650)->hide.num == 0) {
            break;
        }
        for (i = 0; D_0029D480[i] != -1; i++) {
            for (o = isysGObjSearchFromObjKindID_begin(D_0029D480[i]); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                seen = 0;
                opos[0] = ((float *)test_CURRENTROOT(o))[0];
                opos[1] = ((float *)test_CURRENTROOT(o))[1];
                opos[2] = ((float *)test_CURRENTROOT(o))[2];
                if (ACTCheckView(self, o, opos, 0.0f, 160) != 0 &&
                    _DistSqGV(gpos, opos) < 160000.0f) {
                    seen = 1;
                }
                if (ACTGameView_Check(self, o) != 0 || seen != 0) {
                    checkWarning(0);
                    break;
                }
            }
        }
        break;

    case 2:
        if (((GirlBrainWork *)D_0029D650)->f_58F0 != 0) {
            checkWarning(1);
            ((GirlBrainWork *)D_0029D650)->f_58F0 = 0;
        }
        if (D_0028F8F0[0] & 8) {
            ACTSendMailCorrect(self, 251);
        }
        break;

    case 3:
        if (((GirlBrainWork *)D_0029D650)->f_5914 == 0 && isEnterHideadv() != 0) {
            setNext(9);
            break;
        }
        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10 <
                ((GirlBrainWork *)D_0029D650)->f_5910 &&
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10 <
                ((GirlBrainWork *)D_0029D650)->f_5908) {
            setNext(0);
            break;
        }
        /* fall through */

    case 4:
        if (((GirlBrainWork *)D_0029D650)->f_58F0 != 0) {
            checkWarning(0);

            warned = 1;
            ((GirlBrainWork *)D_0029D650)->f_58F0 = 0;
        }
        break;

    case 5:
        setNext(6);
        break;

    case 6:
        if (((GirlBrainWork *)D_0029D650)->f_58F0 == 0) {
            break;
        }
        /* fall through */

    case 8:
        setNext(0);
        ((GirlBrainWork *)D_0029D650)->f_58F0 = 0;
        break;

    case 9:
        if (isEnterHideadv() != 0) {
            break;
        }
        setNext(3);
        break;
    }
    if (PAIR_IsStatus_BOY_WAIT() != 0 &&
        _DistxzSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) < 40000.0f) {
        near = 1;
        girlBrainDebugPrint();
    }
    if (*next != 2 && PAIR_IsStatus_BOY_WAIT() != 0) {
        if (*next != 4 || near != 0) {
            setNext(7);
            return 0;
        }
    }
    return *next == 1 ? changed : warned;
}

void girlBrainMain_PositionUpdate(void)
{
    GetRootPosition(D_002A2E70 + 0x00, D_00639EA8);
    GetRootPosition(D_002A2E70 + 0x20, D_00639EA4);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x10, D_00639EA8);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x30, D_00639EA4);
}

extern void *memset(void *dst, int c, int n);

void girlBrainMain_Init(void)
{
    memset(D_0029D650, 0, 0x5920);
}

extern float D_002A5594[];
extern char D_005D3EF0[];

void ChangeRunMode(int mode)
{
    /* CRUTCH: the next three lines are a stand-in, not source.  The census
       labels this body ChangeRunMode.252 -- make_function_rtl's rename for a
       GNU NESTED FUNCTION -- and ROM's prologue homes the incoming static
       chain with `sw $2,0($sp)`.  The crutch-free form is a real nested
       definition inside its parent subGirlBrainMain (0x00171188), which is
       still INCLUDE_ASM, so the parent must land first.  Measured 2026-09-14:
       with the stand-in this function is rc0 (60/60 words); the stand-in's
       `uninit` pseudo has one reference, so QTY_CMP_PRI is 0 and it loses $2
       to any multi-ref pseudo -- that is why the stand-in closes this body but
       not HandMgr_Print's or sort_list's. */
    volatile int home;
    int uninit;
    int n;
    int t;
    int lo;
    int hi;

    home = uninit;
    ((GirlBrainWork *)D_0029D650)->runMode = mode;
    ((GirlBrainWork *)D_0029D650)->timer = 0;
    ((GirlBrainWork *)D_0029D650)->wait = rand() % 3;
    n = (int)D_002A5594[0];
    n = n / 3;
    n = (n < 0) ? 0 : ((n < 4) ? n : 3);
    t = D_0029D4A0[n][0];
    lo = *(int *)(t * 16 + mode * 8 + D_005D3EF0);
    hi = *(int *)(D_005D3EF0 + (t * 16 + mode * 8) + 4);
    ((GirlBrainWork *)D_0029D650)->limit = lo + rand() % (hi - lo);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", subGirlBrainMain);

/* kept local: this TU's uses of debug_NMarker do not fit the prototype in camera-editor.h */
extern void debug_NMarker(void *pos, int r, int g, int b, float size);
/* kept local: this TU's uses of test_CURRENTORIENT do not fit the prototype in commonact.h */
extern void *test_CURRENTORIENT(void *a0);
/* kept local: this TU's uses of _DistxzGV do not fit the prototype in gv.h */
extern float _DistxzGV(void *a, void *b);
/* kept local: this TU's uses of _OrientXZGV do not fit the prototype in gv.h */
extern void _OrientXZGV(void *out, void *a, void *b);
/* kept local: this TU's uses of _RotyGV do not fit the prototype in gv.h */
extern int _RotyGV(void *buf, void *vec);
/* kept local: this TU's uses of GetSkeltonOrient do not fit the prototype in act-game.h */
extern void GetSkeltonOrient(float *out, void *obj, int node);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f);
extern void *D_0063A6B0;

/* girl_brain_main.c.inc:2-8 -- a file-scope static helper with no out-of-line
 * ROM copy (no MAIN.MAP symbol); the listing attributes lines 3/4/5/7 of the
 * .inc inside subGirlBrain_HideAdvance's move arm and inside
 * subGirlBrain_Pulledup's. */
static inline void girlBrainSetWalkRatio(void *g)
{
    float run = 1.0f;
    Act *s = GOBJ_ACT(g);
    float walk = 0.5f;

    if (ACTWay_IsMustWalkFromWay(g)) {
        *(float *)((char *)s + 0x34C) = walk;
    } else {
        *(float *)((char *)s + 0x34C) = run;
    }
}

/* girl_act.c:692-698 in the listing, which is why it sits here and not in
   girl_brain_attract.c.inc: subGirlBrain_Pulledup (whose text the .inc
   follows) expands it too.  The first parameter is unused -- the listing
   emits the read anyway at every site whose actor is the volatile entry
   parameter, which is what pins the parameter's existence. */
static inline void ATGoalTurnSet(void *actor, int prio, int dir, float *v)
{
    if (prio >= D_006C1E20[0]) {
        D_006C1E20[0] = prio;
        D_006C1E20[1] = dir;
        *(float *)&D_006C1E20[4] = v[0];
        *(float *)&D_006C1E20[5] = v[1];
        *(float *)&D_006C1E20[6] = v[2];
    }
}

void subGirlBrain_Pulledup(volatile int a0)
{
    float self_pos[4];
    float boy_pos[4];
    float ofs[4];
    float base[4];
    float top[4];
    float well[4];
    float cur[4];
    float sk[4];
    float oz[4];
    Act *sub = GOBJ_ACT(a0);
    int hit;
    float d;
    float dy;
    float lim;
    int ry;

    GetRootProjectionPosOfGObj(self_pos, (void *)a0);
    GetRootProjectionPosOfGObj(boy_pos, D_00639EA4);
    *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x374) = 0;
    sceVu0ScaleVector(ofs, test_CURRENTORIENT(D_00639EA4), 60.0f);
    sceVu0AddVector(base, boy_pos, ofs);
    base[1] = base[1] - 50.0f;
    top[0] = base[0];
    top[2] = base[2];
    top[1] = base[1] + 1000.0f;
    if (ACTCheckCollis_WELL(base, top, D_00639EA4, well, 0.0f)) {
        boy_pos[0] = well[0];
        boy_pos[1] = well[1];
        boy_pos[2] = well[2];
        if (D_0063A6B0 != 0 && *(int *)((char *)D_0063A6B0 + 0xC) == 0x11) {
            *(void **)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x374) = D_0063A6B0;
        }
        boy_pos[1] = boy_pos[1] - 10.0f;
    }
    if (*(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x58) {
        boy_pos[0] = *(float *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x510);
        boy_pos[1] = *(float *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x514);
        boy_pos[2] = *(float *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x518);
    }
    if (!ACTWayMove_BeginDetail((void *)a0, self_pos, boy_pos, 0, 0, 0)) {
        while (1) {
            _ACTWait(1);
        }
    }
    for (;;) {
        cur[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
        cur[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
        cur[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
        hit = ACTWayMove_NextDetail((void *)a0, (char *)sub + 0x120, boy_pos, 0, 0);
        debug_NMarker(boy_pos, 0xFF, 0, 0, 100.0f);
        if (!hit) {
            sub->f_34C = 0;
        } else {
            sub->f_120 = *(float *)((char *)sub + 0x3E0);
            sub->f_124 = *(float *)((char *)sub + 0x3E4);
            sub->f_128 = *(float *)((char *)sub + 0x3E8);
            girlBrainSetWalkRatio((void *)a0);
        }
        d = _DistxzGV(boy_pos, cur);
        dy = boy_pos[1] - cur[1];
        dy = (dy < 0.0f) ? -dy : dy;
        lim = (*(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x58) ? 200.0f : 100.0f;
        if (d < 30.0f && dy < 200.0f) {
            sub->f_34C = 0;
            GetSkeltonOrient(sk, (void *)a0, 0x2C);
            _OrientXZGV(oz, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
            ry = _RotyGV(sk, oz);
            if (0x15 <= ((ry < 0) ? -ry : ry)) {
                if (D_00639EA0 == 0) {
                    if (0 < ry) {
                        ATGoalTurnSet((void *)a0, 3, 2, oz);
                    } else {
                        ATGoalTurnSet((void *)a0, 3, 1, oz);
                    }
                }
            } else {
                *(unsigned long long *)((char *)sub + 0x18) |= 0x40000000000000;
            }
        } else if (d < lim) {
            *(float *)((char *)sub + 0x34C) =
                (*(float *)((char *)sub + 0x34C) < 0.0f)
                    ? 0.0f
                    : ((0.5f < *(float *)((char *)sub + 0x34C)) ? 0.5f
                                                                : *(float *)((char *)sub + 0x34C));
        }
        _ACTCharStatus_Set((void *)a0, 0x1C, -1.0f, 0);
        *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x32C) =
            _DistGV(test_CURRENTROOT((void *)a0), boy_pos);
        _ACTWait(1);
    }
}

#include "girl_brain_attract.c.inc"

/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *w);
/* kept local: this TU's uses of ClipFloor do not fit the prototype in fieldCollision.h */
extern void ClipFloor(void *w);
extern void sceVu0Normalize(void *dst, void *src);
extern void sceVu0CopyVector(void *dst, void *src);

void _girlBrainHide_MakeHidePoint(float *p, float dist)
{
    float v[4];
    ClipWork work;
    int i;
    float total;
    float w;

    if (*(int *)(D_0029D650 + 0x3230) == 0) {
        return;
    }
    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;
    total = p[0];
    for (i = 0; i < *(int *)(D_0029D650 + 0x3230); i++) {
        sceVu0SubVector(v, ((GirlBrainWork *)D_0029D650)->f_5850,
                        ((GirlBrainWork *)D_0029D650)->hide.ent[i].pos);
        v[1] = 0.0f;
        sceVu0Normalize(v, v);
        w = ((GirlBrainWork *)D_0029D650)->hide.ent[i].dist;
        if (w < 1.0f) {
            w = 1.0f;
        }
        w = 1.0f / w;
        total += w;
        sceVu0ScaleVector(v, v, w);
        sceVu0AddVector(p, p, v);
    }
    if (total != 0.0f) {
        sceVu0ScaleVector(p, p, dist / total);
    } else {
        debug_assert(D_00553A88, 1981);
        __assert(D_00553A88, 1981, D_0063A8A0);
    }
    sceVu0Normalize(p, p);
    sceVu0ScaleVector(p, p, dist);
    sceVu0AddVector(p, ((GirlBrainWork *)D_0029D650)->f_5850, p);
    p[1] = ((GirlBrainWork *)D_0029D650)->f_5840[1];
    work.radius = 50.0f;
    sceVu0CopyVector(work.a, ((GirlBrainWork *)D_0029D650)->f_5820);
    sceVu0CopyVector(work.b, p);
    ClipWall(&work);
    work.a[0] = work.pos[0];
    work.a[2] = work.pos[2];
    work.b[0] = work.pos[0];
    work.b[2] = work.pos[2];
    work.a[1] = work.pos[1] - 200.0f;
    work.b[1] = work.pos[1] + 200.0f;
    ClipFloor(&work);
    p[0] = work.pos[0];
    p[2] = work.pos[2];
    p[1] = work.pos[1] - 10.0f;
}

extern char D_00553BF0[];
extern char D_00553C00[];

void girlBrainHide_GoalTurn(float *dir, unsigned char sendMail)
{
    float mo[4];
    float eye[4];
    char *girl;
    char *p;
    int r;

    girl = (char *)D_00639EA8;
    GetRootMotionOrient(mo, girl);
    r = _RotyGV(mo, dir);
    r = (r < 0) ? -r : r;
    if (r >= 0x2E) {
        p = *(char **)(*(char **)(girl + 0x164) + 0x688);
        *(float *)(p + 0x3F0) = dir[0];
        *(float *)(p + 0x3F4) = dir[1];
        *(float *)(p + 0x3F8) = dir[2];
        GetEyeDirection((char *)eye, girl);
        if (_RotyGV(eye, dir) > 0) {
            debug_StdPrintfDummy(D_00553BF0);
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xEC);
            } else {
                ACTSendMailCorrect(girl, 0xEE);
            }
        } else {
            debug_StdPrintfDummy(D_00553C00);
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xEB);
            } else {
                ACTSendMailCorrect(girl, 0xED);
            }
        }
    }
}

/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *a, void *b);
/* one object: [0] is the entry count, +0x20 the 0x30-byte hide-point records
   (ROM re-reads the count as -0x20 off the record base). */
extern int D_0029F5B0[];
/* the second entry of girlBrainMain_PositionUpdate's vector block, i.e.
   D_002A2E70 + 0x10: the girl's projected ground position, with her root
   position 0x20 further on. */
extern char D_002A2E80[];

/* girl_brain_main.c.inc:~381-387 (rows outside every caller's span => static
   inline; the listing tags the two loads 382/383, the ratio store 384 and the
   direction stores 386).  Hands the girl's sub a move direction at the full
   run ratio.  `run` is declared ahead of the two loads exactly as this TU's
   girlBrainSetWalkRatio (.inc:2-8) declares its own run/walk ratios -- ROM
   hoists the 1.0f out of subGirlBrain_Hide's loop into $f20, which gcc's
   loop.c only does once the constant's live range spans the two loads. */
static inline void girlBrainSetMoveDir(float *d)
{
    float run = 1.0f;
    char *s;

    s = *(char **)((char *)D_00639EA8 + 0x164);
    *(float *)(s + 0x34C) = run;
    *(float *)(s + 0x120) = d[0];
    *(float *)(s + 0x124) = d[1];
    *(float *)(s + 0x128) = d[2];
}

void subGirlBrain_Hide(volatile int a0)
{
    float hp[4];
    float cand[4];
    int cnt = 0;
    float rad = 80.0f;
    int near;
    /* the girl object handed in by the actor entry.  ROM reads the parameter
       home into $a0 BEFORE the ratio store of each arm (branch 1) and before
       girlBrainSetMoveDir's two loads (branch 2); spelling the argument
       `(void *)a0` inline cannot reach that order, because ee-gcc gives a
       volatile MEM read a dependence on every pending store in the block. */
    char *g;

    /* girl_brain_main.c.inc:2066-2096.  A gcc nested function (the PAL listing
       names it isHideRecheck.300 and its prologue homes the static chain with
       `sw $2,0($sp)`); it writes the enclosing `rad` through that chain. */
    int isHideRecheck(float *from, float *to, float *root)
    {
        float v0[4];
        float v1[4];
        float v2[4];
        int i;
        int r;

        sceVu0SubVector(v0, from, root);
        sceVu0SubVector(v1, to, root);
        for (i = 0; i < D_0029F5B0[0]; i++) {
            sceVu0SubVector(v2, i * 0x30 + ((char *)D_0029F5B0 + 0x20), root);
            r = _RotyGV(v0, v2);
            if ((r < 0 ? -r : r) < 45) {
                rad = 80.0f;
                return 1;
            }
        }
        r = _RotyGV(v0, v1);
        if (!((r < 0 ? -r : r) < 46)) {
            return 1;
        }
        if (_DistxzSqGV(from, root) < _DistxzSqGV(to, root) &&
            !(_DistxzSqGV(from, to) < 25600.0f)) {
            return 1;
        }
        return 0;
    }

    float dir[4];

    _ACTWait(1);
    hp[0] = ((GirlBrainWork *)D_0029D650)->f_5800[0];
    hp[1] = ((GirlBrainWork *)D_0029D650)->f_5800[1];
    hp[2] = ((GirlBrainWork *)D_0029D650)->f_5800[2];
    while (1) {
        if (cnt++ % ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2) == 0 &&
            girlBrainMain_CheckWarningMode(0) != 3) {
            ((GirlBrainWork *)D_0029D650)->f_58F0 = 1;
        }
        _girlBrainHide_MakeHidePoint(cand, rad);
        if (isHideRecheck(hp, cand, test_CURRENTROOT(D_00639EA4))) {
            rad = _DistxzGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
            rad = (rad < 200.0f) ? 200.0f : ((800.0f < rad) ? 800.0f : rad);
            _girlBrainHide_MakeHidePoint(hp, rad);
            cand[0] = hp[0];
            cand[1] = hp[1];
            cand[2] = hp[2];
        }
        if (isHidePointTooHigh(cand) ||
            girlBrainHideCheckIntercept(((GirlBrainWork *)D_0029D650)->f_5830, cand,
                                        (char *)((GirlBrainWork *)D_0029D650)->hide.ent,
                                        ((GirlBrainWork *)D_0029D650)->hide.num)) {
            ((GirlBrainWork *)D_0029D650)->f_58F0 = 1;
        }
        near = _DistxzSqGV(cand, D_002A2E80) < 3600.0f;
        if (near) {
            hp[0] = cand[0];
            hp[1] = cand[1];
            hp[2] = cand[2];
        }
        if (_DistxzSqGV(hp, D_002A2E80) < 10000.0f || near) {
            g = (char *)a0;
            GOBJ_ACT(D_00639EA8)->f_34C = 0;
            _ACTCharStatus_Set(g, 7, -1.0f, 0);
            if (_DistxzSqGV(hp, D_002A2E80) < 6400.0f || near) {
                _OrientXZGV(dir, D_002A2E80 + 0x20, D_002A2E80);
                girlBrainHide_GoalTurn(dir, 1);
            }
        } else {
            _OrientXZGV(dir, cand, D_002A2E80);
            g = (char *)a0;
            girlBrainSetMoveDir(dir);
            _ACTCharStatus_Set(g, 6, -1.0f, 0);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *);
/* kept local: this TU's uses of ClipWallField do not fit the prototype in fieldCollision.h */
extern void ClipWallField(void *);
/* kept local: this TU's uses of ClipFloor do not fit the prototype in fieldCollision.h */
extern void ClipFloor(void *);

/* girl_brain_main.c.inc:2276-2291 (rows outside every caller's span => static
   inline; the listing inlines it three times).  True when the straight segment
   from `from` to `to` clears both the wall and the wall-field collision. */
static inline int isNoWallBetween(float *from, float *to)
{
    ClipWork work;

    work.radius = 10.0f;
    sceVu0CopyVector(work.a, from);
    sceVu0CopyVector(work.b, to);
    ClipWall(&work);
    if (work.wallHit == 0) {
        ClipWallField(&work);
        if (work.wallHit == 0) {
            return 1;
        }
    }
    return 0;
}

/* girl_brain_main.c.inc:2221-2226 (rows outside its callers' span => static
   inline).  True when `b` is within 100 units vertically and 100 units in the
   plane of `a`. */
static inline unsigned char isNearPoint(float *a, float *b)
{
    if ((a[1] - b[1] < 0.0f ? -(a[1] - b[1]) : a[1] - b[1]) < 100.0f) {
        if (_DistSqGV(a, b) < 10000.0f) {
            return 1;
        }
    }
    return 0;
}

/* girl_brain_main.c.inc:2300-2327 (rows outside every caller's span => static
   inline; the listing inlines it twice inside girlBrainRunawaySearchPoint).
   True when no listB entry lies closer to `p` than the girl does, and no
   listB entry lies closer to `p` than it lies to the girl. */
static inline unsigned char isRunawayPointClear(float *p, float *girl)
{
    int i;
    float d;

    d = _DistSqGV(p, girl);
    for (i = 0; i < ((GirlBrainWork *)D_0029D650)->listB.num; i++) {
        if (_DistSqGV(p, ((GirlBrainWork *)D_0029D650)->listB.ent[i].pos) < d) {
            return 0;
        }
    }
    for (i = 0; i < ((GirlBrainWork *)D_0029D650)->listB.num; i++) {
        float dg = _DistSqGV(girl, ((GirlBrainWork *)D_0029D650)->listB.ent[i].pos);
        float dp = _DistSqGV(p, ((GirlBrainWork *)D_0029D650)->listB.ent[i].pos);

        if (dp < dg) {
            return 0;
        }
    }
    return 1;
}

int girlBrainRunawaySearchPoint(float *goal, float *out, float *p)
{
    /* girl_brain_main.c.inc:2429-2443, a GNU nested function: the listing
       places it inside its parent's body and names it CorrectList.331.  It
       reads nothing of the parent's frame (its scratch list is a file static),
       but gcc homes the static chain in every nested function's prologue,
       which is ROM's `sw $2,0($sp)`. */
    int CorrectList(float (*list)[4], float *p, int n)
    {
        int i;
        int num;

        num = 0;
        for (i = 0; i < n; i++) {
            if (!isNearPoint(p, list[i])) {
                float *d = D_006C1AE0[num];

                d[0] = list[i][0];
                d[1] = list[i][1];
                d[2] = list[i][2];
                num++;
            }
        }
        for (i = 0; i < num; i++) {
            float *s = D_006C1AE0[i];

            list[i][0] = s[0];
            list[i][1] = s[1];
            list[i][2] = s[2];
        }
        return num;
    }

    char *g;
    char *sub;
    int n;
    int i;
    int correct = 1;

    g = D_00639EA8;
    sub = *(char **)(g + 0x164);
    n = GetNearNigePointN(D_006C1B80, 10, sub + 0x360, p);
    for (i = n - 1; i >= 0; i--) {
        float (*list)[4] = D_006C1B80;

        if (isNearPoint(p, list[i])) {
            p[0] = list[i][0];
            p[1] = list[i][1];
            p[2] = list[i][2];
            n = GetNearNigePointN(list, 10, sub + 0x360, p);
            break;
        }
    }
    /* RECONSTRUCTION: what the bytes pin is a jump over this call to a label
       right after it, alive through the minimal jump pass of the sibcall
       stage (so a (use (const_int 0)) is left behind the call) and gone by
       gcse's constant propagation, which is what keeps `i = 0` below behind
       the call in the blez slot.  A test of a local holding a constant is the
       spelling that does that; its name and role are ours, not the disc's. */
    if (correct) {
        n = CorrectList(D_006C1B80, p, n);
    }
    for (i = 0; i < n; i++) {
        _DistGV(p, D_006C1B80[i]);
        _DistGV(((GirlBrainWork *)D_0029D650)->listB.ent[0].pos, D_006C1B80[i]);
        if (isNearPoint(p, D_006C1B80[i])) {}
    }
    for (i = 0; i < n; i++) {
        if (isRunawayPointClear(D_006C1B80[i], p)) {
            dispWayMarker(D_006C1B80[i]);
        }
    }
    for (i = 0; i < n; i++) {
        if (isRunawayPointClear(D_006C1B80[i], p)) {
            float pos[4];
            float *s;

            GetWay_begin(D_006C1B80[i], sub + 0x360, goal);
            *(int *)(sub + 0x3A4) = 0;
            pos[0] = goal[0];
            pos[1] = goal[1];
            pos[2] = goal[2];
            pos[1] -= 50.0f;
            if (isNoWallBetween(pos, D_006C1B80[i])) {
                *(int *)(sub + 0x3A4) = 1;
                DeleteGuideWay(sub + 0x360);
            }
            s = D_006C1B80[i];
            out[0] = s[0];
            out[1] = s[1];
            out[2] = s[2];
            ((GirlBrainWork *)D_0029D650)->f_5860 = 0;
            return 1;
        }
    }
    return 0;
}

int girlBrainRunawayMoveByWay(char *self, float *out, float *tgt)
{
    float d[4];
    float pos[4];
    char *sub;
    int way;
    int done;

    sub = *(char **)(self + 0x164);
    d[0] = tgt[0];
    d[1] = tgt[1];
    d[2] = tgt[2];
    switch (*(int *)(sub + 0x3A4)) {
    case 0:
        done = 0;
        GetRootProjectionPosOfGObj(pos, self);
        pos[1] = pos[1] - 0.0f;
        way = GetWay_next(sub + 0x360, pos);
        if (way == 0) {
            sceVu0CopyVector(out, sub + 0x3B0);
        } else {
            char *w;

            sceVu0CopyVector(out, sub + 0x3B0);
            w = D_0029D650;
            if (*(int *)(w + 0x5860) != way) {
                if (*(int *)(w + 0x5860) != 0) {
                    done = *(int *)(sub + 0x3C4) < 1;
                }
                *(int *)(w + 0x5860) = way;
            }
        }
        if (*(int *)(sub + 0x388) == 0) {
            if (isNoWallBetween(pos, d)) {
                *(int *)(sub + 0x3A4) = 1;
                DeleteGuideWay(sub + 0x360);
            }
        }
        if (done) {
            return 2;
        }
        break;
    case 1: {
        float cur[4];
        float dir[4];

        GetRootPosition(cur, self);
        if (isNoWallBetween(cur, d)) {
            float dx = d[0];
            float dz = d[2];

            dir[0] = dx - cur[0];
            dir[1] = 0.0f;
            dir[2] = dz - cur[2];
            sceVu0Normalize(out, dir);
            if (isNearPoint(d, cur)) {
                return 1;
            }
        }
    } break;
    }
    return 0;
}

/* kept local: this TU's uses of sceVu0TransposeMatrix do not fit the prototype in vu0.h */
extern void sceVu0TransposeMatrix(float *dst, float *src);
/* kept local: this TU's uses of sceVu0MulMatrix do not fit the prototype in vu0.h */
extern void sceVu0MulMatrix(void *dst, void *a, void *b);
extern void sceVu0UnitMatrix(void *m);
extern void DispWireString(char *s);
extern int sprintf(char *buf, const char *fmt, ...);
/* kept local: this TU's uses of _RotGV do not fit the prototype in gv.h */
extern int _RotGV(void *a, void *b);
extern float *matrixptr;

/* girl_brain_main.c.inc:2239-2249 (rows outside its caller's span => static
   inline).  Points `v` at the first listB entry within 300 units of `p` whose
   bearing from `dir` is under 45 degrees. */
static inline void girlBrainEscapeFaceCheck(float *p, float *dir, Vec4u *v)
{
    int i;

    memset(v, 0, 16);
    v->f[3] = 1.0f;
    for (i = 0; i < ((GirlBrainWork *)D_0029D650)->listB.num; i++) {
        if (_DistSqGV(p, ((GirlBrainWork *)D_0029D650)->listB.ent[i].pos) < 90000.0f) {
            sceVu0SubVector(v->f, ((GirlBrainWork *)D_0029D650)->listB.ent[i].pos, p);
            if ((_RotGV(dir, v) < 0 ? -_RotGV(dir, v) : _RotGV(dir, v)) < 45) {
                break;
            }
        }
    }
}

/* girlBrainDebugPrint in subGirlBrain_Escape: each call leaves one zero-code
   insn that gcse counts and sched2 issues.
   WHAT THE BYTES PIN, site by site (each measured
   necessary: the function differs from the ROM without it):
   - arm 1 after `mode = 2`: one more insn in gcse's table, which decides the
     frame-address homes at 0xA4..0xB4;
   - arm 1 after `mode = 3`: a second insn in the failed search's branch, so
     jump1 keeps it a branch (beql) instead of a conditional move;
   - cases 1 and 2 after girlBrainRunawayMoveByWay: the zero-code insn takes
     the issue slot ahead of each vector copy.
   And none at the other mode changes, which the ROM proves: `mode = 4` on
   the unk34 test and arm 4's `mode = 0` are movz/movn, which a second
   statement in the if would block; arm 0's `mode = 1` fills its jal slot
   with the li of mode*4, which a zero-code insn there reorders.
   WHAT THEY CANNOT PIN: the text of the prints, or whether they were one
   macro or several. */

/* girl_brain_main.c.inc:2621-2846 */
void subGirlBrain_Escape(volatile int a0)
{
    float pos[4];
    float ppos[4];
    float rp[4];
    Vec4u v;
    float mk[4];
    float mtx[16];
    Act *sub;
    int cnt;
    int mode;
    int i;
    int ret;

    cnt = 1;
    sub = GOBJ_ACT(a0);
    mode = 0;
    for (i = 0; i < (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2; i++) {
        sub->f_34C = 0;
        _ACTWait(1);
    }
    for (;;) {
        if (sub->unk34 == 0x6F) {
            mode = 4;
        }
        if (((GirlBrainWork *)D_0029D650)->listB.num == 0 ||
            cnt++ % ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2) == 0) {
            ((GirlBrainWork *)D_0029D650)->f_58F0 = 1;
        }
        GetRootPosition(pos, (void *)a0);
        GetRootProjectionPosOfGObj(ppos, (void *)a0);
        switch (mode) {
        case 0:
            mode = 1;
            GetRootProjectionPosOfGObj(rp, (void *)a0);
            ((GirlBrainWork *)D_0029D650)->f_5810[0] = rp[0];
            ((GirlBrainWork *)D_0029D650)->f_5810[1] = rp[1];
            ((GirlBrainWork *)D_0029D650)->f_5810[2] = rp[2];
            sub->f_34C = 0;
            break;
        case 1:
            mode = 2;
            girlBrainDebugPrint();
            GetRootProjectionPosOfGObj(rp, (void *)a0);
            if (girlBrainRunawaySearchPoint(rp, ((GirlBrainWork *)D_0029D650)->f_57F0,
                                            ((GirlBrainWork *)D_0029D650)->f_5810) == 0) {
                mode = 3;
                girlBrainDebugPrint();
            }
            sub->f_34C = 0;
            break;
        case 2:
            ret = girlBrainRunawayMoveByWay((char *)a0, (float *)&sub->f_120,
                                            ((GirlBrainWork *)D_0029D650)->f_57F0);
            switch (ret) {
            case 0:
                break;
            case 1:
                girlBrainDebugPrint();
                ((GirlBrainWork *)D_0029D650)->f_5810[0] = ((GirlBrainWork *)D_0029D650)->f_57F0[0];
                ((GirlBrainWork *)D_0029D650)->f_5810[1] = ((GirlBrainWork *)D_0029D650)->f_57F0[1];
                ((GirlBrainWork *)D_0029D650)->f_5810[2] = ((GirlBrainWork *)D_0029D650)->f_57F0[2];
                mode = 1;
                break;
            case 2:
                girlBrainDebugPrint();
                ((GirlBrainWork *)D_0029D650)->f_5810[0] = ppos[0];
                ((GirlBrainWork *)D_0029D650)->f_5810[1] = ppos[1];
                ((GirlBrainWork *)D_0029D650)->f_5810[2] = ppos[2];
                mode = 1;
                break;
            }
            girlBrainEscapeFaceCheck(pos, (float *)&sub->f_120, &v);
            switch (((GirlBrainWork *)D_0029D650)->runMode) {
            case 0:
                girlBrainSetWalkRatio((void *)a0);
                break;
            case 1:
                *(float *)&sub->f_34C = 0.5f;
                break;
            }
            if (*(float *)&sub->f_34C != 0.0f) {
                sceVu0ScaleVector(v.f, (float *)&sub->f_120, 300.0f);
                sceVu0AddVector(v.f, ((GirlBrainWork *)D_0029D650)->f_5830, v.f);
                if (girlBrainHideCheckIntercept(((GirlBrainWork *)D_0029D650)->f_5830, v.f,
                                                (char *)((GirlBrainWork *)D_0029D650)->hide.ent,
                                                ((GirlBrainWork *)D_0029D650)->hide.num)) {
                    *(float *)&sub->f_34C = 0.0f;
                    ((GirlBrainWork *)D_0029D650)->f_58F0 = 1;
                }
            }
            sceVu0ScaleVector(mk, ((GirlBrainWork *)D_0029D650)->f_57F0, -1.0f);
            debug_Marker(mk, 0xFF, 0, 0, 200.0f, (float)((GirlBrainWork *)D_0029D650)->f_58F4);
            ((GirlBrainWork *)D_0029D650)->f_58F4 = ((GirlBrainWork *)D_0029D650)->f_58F4 + 5;
            break;
        case 3:
            sub->f_34C = 0;
            ACTSendMailCorrect((void *)a0, 0xE5);
            D_002A5580[0].f18 = 9.0f;
            if ((((int)(((ActStatus *)((char *)sub + 0x18))->ll >> 63)) & 1) ||
                (sub->flags20.i[0] & 1)) {
                sub->flags20.ll = sub->flags20.ll | 4;
            }
            break;
        case 4:
            sub->f_34C = 0;
            if (sub->unk34 != 0x6F) {
                mode = 0;
            }
            break;
        }
        MatrixDrive_PushMatrix();
        sceVu0TransposeMatrix(mtx, matrixptr + 32);
        mtx[3] = mtx[7] = mtx[11] = 0.0f;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
        sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), mtx);
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
        sprintf(D_006C1C20, "%s", D_0029D600[mode]);
        DispWireString(D_006C1C20);
        MatrixDrive_PopMatrix();
        MatrixDrive_PopMatrix();
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(float *dst, float *a, float *b, float t0, float t1);

void ClipTwinVector(float *out, float *from, float *to, float max)
{
    float d;
    float t;

    d = _DistGV(from, to);
    if (max < d) {
        t = (d - max) / d;
        _InterGV(out, from, to, t, 1.0f - t);
    } else {
        out[0] = to[0];
        out[1] = to[1];
        out[2] = to[2];
    }
}

/* INTERIM: ACTCheckCollis_SAFE is `inline` in the 2001 source -- the PAL
 * listing attributes girl_brain_main.c.inc:2868-2909 both to its out-of-line
 * copy (this TU's deferred-inline tail, ROM 0x0017C6D0, still spelled as a
 * plain definition further down) and to the four Danger_* GetSafePosition
 * bodies that inline it.  Marking the real definition `inline` would move its
 * out-of-line copy past the tail members that are still INCLUDE_ASM, so the
 * callers above it use this identical static-inline stand-in.  Delete it and
 * mark the real definition `inline` once the tail is complete. */
static inline int ACTCheckCollis_SAFE_inl(float height, float *p0, float *p1, void *actor,
                                          float *posout, int radius)
{
    ClipWork work;
    float tmp[4];
    int flag;
    int rv;

    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->f_74 : 0;

    work.radius = (float)radius;
    work.a[0] = p0[0];
    work.a[1] = p0[1];
    work.a[2] = p0[2];
    work.b[0] = p1[0];
    work.b[2] = p1[2];
    work.b[1] = p0[1];

    tmp[0] = p1[0];
    tmp[1] = p0[1];
    tmp[2] = p1[2];

    if (flag != 0) {
        GOBJ_SUB(actor)->f_74 = 0;
    }
    ClipWall(&work);
    if (work.wallHit == 0) {
        ClipWallField(&work);
        if (work.wallHit == 0)
            goto no_wall;
    }
    tmp[0] = work.pos[0];
    tmp[1] = work.pos[1];
    tmp[2] = work.pos[2];
no_wall:
    work.a[0] = tmp[0];
    work.a[1] = tmp[1];
    work.a[2] = tmp[2];
    work.b[0] = tmp[0];
    work.b[2] = tmp[2];
    work.b[1] = tmp[1] + height;
    ClipFloor(&work);
    if (work.floorHit == 0) {
        rv = 0;
    } else {
        work.pos[1] -= 10.0f;
    }
    if (posout != 0) {
        posout[0] = work.pos[0];
        posout[1] = work.pos[1];
        posout[2] = work.pos[2];
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->f_74 = 1;
    }
    return rv;
}

/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(float *v, float ang);

static void Danger_Bomb(void *self)
{
    /* girl_brain_main.c.inc:2942 -- a GNU nested function: ROM sets the static
     * chain with `daddu $2,$29,$0` at the call and the callee homes it with
     * `sw $2,0($sp)`.  Each Danger_* parent carries its own copy (the listing
     * names them GetSafePosition.357/.364/.371/.379).  The float radius is the
     * FIRST parameter (ee-gcc still passes it in $f12 with the four pointers in
     * $a0-$a3), and the last parameter -- the boy position the callers hand in
     * and this copy never reads -- is reused as the collision flag. */
    int GetSafePosition(float rad, float *dst, float *center, float *cur, int ok)
    {
        float dir[4];
        float pos[4];
        float best;
        float d;
        int found;
        int i;

        best = 0.0f;
        found = 0;
        for (i = 0; i < 8; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            _ApplyRyGV(dir, (float)(i * 45 - 180) * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            ok = ACTCheckCollis_SAFE_inl(200.0f, center, pos, 0, pos, 40);
            if (ok) {
                d = _DistGV(center, pos);
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        if (found && _DistSqGV(dst, center) < _DistSqGV(cur, center)) {
            dst[0] = cur[0];
            dst[1] = cur[1];
            dst[2] = cur[2];
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float obj[4];
    float base[4];
    float tmp[4];
    float now[4];
    float dir[4];
    char *sub;
    void *bomb;
    long long f;
    unsigned char r;
    unsigned char r2;
    long long p;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    bomb = D_006C1E40.obj;
retry:
    {
        GetRootProjectionPosOfGObj(goal, bomb);
        GetRootProjectionPosOfGObj(girl, self);
        obj[0] = ((float *)test_CURRENTROOT(bomb))[0];
        obj[1] = ((float *)test_CURRENTROOT(bomb))[1];
        obj[2] = ((float *)test_CURRENTROOT(bomb))[2];
        GetRootProjectionPosOfGObj(base, bomb);
        _ACTWait(1);
        GetSafePosition(500.0f, goal, (float *)test_CURRENTROOT(bomb), girl,
                        (int)test_CURRENTROOT(D_00639EA4));
        _ACTWait(1);
        p = ACTWayMove_BeginDetail(self, girl, goal, 0, 0, 0);
        r = p;
        if (!r) {
            _ACTWait(0);
        }
        _ACTWait(1);
        turn = 0;
        while (1) {
            _ACTCharStatus_Set(self, 11, -1.0f, (int)bomb);
            GetRootProjectionPosOfGObj(tmp, bomb);
            GetRootProjectionPosOfGObj(girl, self);
            GetRootProjectionPosOfGObj(now, bomb);
            if (!(_DistxzSqGV(now, base) < 10000.0f)) {
                goto retry;
            }
            p = ACTWayMove_NextDetail(self, sub + 0x120, goal, 0, 0);
            r2 = p;
            f = *(long long *)(sub + 0x3F0);
            if (((int)(f >> 16) & 1)) {
                turn = 0;
            }
            if (!r2) {
                turn = 1;
            } else if (((int)(f >> 17) & 1)) {
                turn = 1;
            } else if (*(float *)(sub + 0x3F8) < 50.0f) {
                turn = 1;
            } else if (turn == 0) {
                *(float *)(sub + 0x120) = *(float *)(sub + 0x3E0);
                *(float *)(sub + 0x124) = *(float *)(sub + 0x3E4);
                *(float *)(sub + 0x128) = *(float *)(sub + 0x3E8);
                *(float *)(sub + 0x34C) = 1.0f;
            }
            if (turn) {
                *(float *)(sub + 0x34C) = 0.0f;
                _OrientXZGV(dir, obj, test_CURRENTROOT(self));
                girlBrainHide_GoalTurn(dir, 1);
            }
            _ACTWait(1);
        }
    }
}

/* census GetSafePosition.364, the GNU nested child of Danger_Gondola; it lands
   inside its parent (rc0 as a nested function in chain G pass 13). */
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", func_001762A0);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", Danger_Gondola);

/* girl_brain_main.c.inc:44-53 -- a file-scope static helper with no MAIN.MAP
 * symbol of its own; the listing attributes lines 45/50/52 to Danger_Box, to
 * its nested GetSafePosition and to subGirlBrainMain, i.e. it is inlined at
 * every site.  Name chosen here: it asks whether the boy is currently pushing
 * a truck-type box (his sub-object's status 0x34 == 0x31 and the object he
 * holds at 0x158 is box kind 7). */
static inline unsigned char isBoyPushBoxTruck(void)
{
    char *sub;
    char *box;

    if (D_00639EA4 != 0 &&
        *(int *)((sub = *(char **)((char *)D_00639EA4 + 0x164)) + 0x34) == 0x31 &&
        (box = *(char **)(sub + 0x158)) != 0 && IsThisBoxTruck(box) == 7) {
        return 1;
    }
    return 0;
}

/* kept local: this TU's uses of _GetDirection do not fit the prototype in gv.h */
extern float _GetDirection(void *orient);
extern char D_00553C58[];

static void Danger_Box(void *self)
{
    /* girl_brain_main.c.inc:3438 -- a GNU nested function (the listing's
     * GetSafePosition.371); see Danger_Bomb for the parameter-order note.
     * This copy takes six integer parameters; the fifth (the boy root the
     * callers hand in) is never read and is reused as the collision flag. */
    int GetSafePosition(float *dst, float *way, float *center, float rad, int ok, int mode,
                        float *girl)
    {
        float dir[4];
        float pos[4];
        float from[4];
        float best;
        float d;
        int found;
        int i;
        int ang;

        best = 0.0f;
        found = 0;
        for (i = 0; i < 3; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            if (i == 0 && !isBoyPushBoxTruck()) {
                continue;
            }
            ang = (int)(_GetDirection(test_CURRENTORIENT(D_00639EA4)) / 3.1415927f * 180.0f) +
                  D_0029D618[i];
            if (ang >= 181) {
                ang -= 360;
            }
            if (ang <= -181) {
                ang += 360;
            }
            _ApplyRyGV(dir, (float)ang * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            pos[1] = center[1];
            from[0] = center[0];
            from[2] = center[2];
            from[1] = center[1] - 70.0f;
            ok = ACTCheckCollis_SAFE_inl(200.0f, from, pos, 0, pos, 40);
            if (ok) {
                d = _DistxzSqGV(way, pos);
                if (mode != 1) {
                    if (_DistxzSqGV(pos, way) < _DistxzSqGV(way, center)) {
                        continue;
                    }
                }
                if (_DistxzSqGV(pos, girl) < 3600.0f) {
                    continue;
                }
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        if (found) {
            /* ROM evaluates both calls and drops the comparison: the body of
             * this test is empty in the shipped build. */
            if (_DistSqGV(dst, way) < _DistSqGV(center, way)) {}
        } else {
            dst[0] = center[0];
            dst[1] = center[1];
            dst[2] = center[2];
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float objp[4];
    float way[4];
    float cur[4];
    float boxp[4];
    float sideA[4];
    float sideB[4];
    float ofs[4];
    float orient[4];
    float tmp[4];
    float dir[4];
    char *sub;
    void *box;
    float rad;
    long long f;
    unsigned char r;
    unsigned char r2;
    long long p;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    rad = isBoyPushBoxTruck() ? 400.0f : 200.0f;
    box = D_006C1E40.obj;
    GetRootProjectionPosOfGObj(goal, box);
    GetRootProjectionPosOfGObj(girl, self);
    objp[0] = ((float *)test_CURRENTROOT(box))[0];
    objp[1] = ((float *)test_CURRENTROOT(box))[1];
    objp[2] = ((float *)test_CURRENTROOT(box))[2];
    GetRootProjectionPosOfGObj(way, box);
    orient[0] = ((float *)test_CURRENTORIENT(D_00639EA4))[0];
    orient[1] = ((float *)test_CURRENTORIENT(D_00639EA4))[1];
    orient[2] = ((float *)test_CURRENTORIENT(D_00639EA4))[2];
    boxp[0] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[0];
    boxp[1] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[1];
    boxp[2] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[2];
    cur[0] = ((float *)test_CURRENTROOT(self))[0];
    cur[1] = ((float *)test_CURRENTROOT(self))[1];
    cur[2] = ((float *)test_CURRENTROOT(self))[2];
    sceVu0ScaleVector(ofs, orient, 100.0f);
    sceVu0AddVector(sideA, boxp, ofs);
    sceVu0ScaleVector(ofs, orient, -100.0f);
    sceVu0AddVector(sideB, boxp, ofs);
    if (_DistSqGV(sideA, cur) < _DistSqGV(sideB, cur)) {
        way[0] = sideA[0];
        way[1] = sideA[1];
        way[2] = sideA[2];
    } else {
        way[0] = sideB[0];
        way[1] = sideB[1];
        way[2] = sideB[2];
    }
    _ACTWait(1);
    if (!GetSafePosition(goal, way, girl, rad, (int)test_CURRENTROOT(D_00639EA4), 0, girl)) {
        GetRootProjectionPosOfGObj(cur, box);
        if (!GetSafePosition(goal, way, cur, rad, (int)test_CURRENTROOT(D_00639EA4), 1, girl)) {
            debug_StdPrintfDummy(D_00553C58);
            goal[0] = girl[0];
            goal[1] = girl[1];
            goal[2] = girl[2];
        }
    }
    _ACTWait(1);
    p = ACTWayMove_BeginDetail(self, girl, goal, 0, 0, 0);
    r = p;
    if (!r) {
        _ACTWait(0);
    }
    *(long long *)(sub + 0x438) |= 0x10000;
    _ACTWait(1);
    turn = 0;
    while (1) {
        _ACTCharStatus_Set(self, 11, -1.0f, (int)box);
        GetRootProjectionPosOfGObj(cur, box);
        GetRootProjectionPosOfGObj(girl, self);
        GetRootProjectionPosOfGObj(tmp, box);
        p = ACTWayMove_NextDetail(self, sub + 0x120, goal, 0, 0);
        r2 = p;
        f = *(long long *)(sub + 0x3F0);
        if (((int)(f >> 16) & 1)) {
            turn = 0;
        }
        if (!r2) {
            turn = 1;
        } else if (((int)(f >> 17) & 1)) {
            turn = 1;
        } else if (*(float *)(sub + 0x3F8) < 50.0f) {
            turn = 1;
        } else if (turn == 0) {
            *(float *)(sub + 0x120) = *(float *)(sub + 0x3E0);
            *(float *)(sub + 0x124) = *(float *)(sub + 0x3E4);
            *(float *)(sub + 0x128) = *(float *)(sub + 0x3E8);
            *(float *)(sub + 0x34C) = 1.0f;
        }
        if (turn) {
            *(float *)(sub + 0x34C) = 0.0f;
            _OrientXZGV(dir, objp, test_CURRENTROOT(self));
            girlBrainHide_GoalTurn(dir, 0);
        }
        _ACTWait(1);
    }
}

static void Danger_Rotobject(void *self)
{
    /* girl_brain_main.c.inc -- a GNU nested function (the listing's
     * GetSafePosition.379); see Danger_Bomb for the parameter-order note. */
    int GetSafePosition(float rad, float *dst, float *center, float *girl, int ok)
    {
        float boy[4];
        float dir[4];
        float pos[4];
        float from[4];
        float best;
        float d;
        int found;
        int i;

        boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
        boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
        boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
        best = 0.0f;
        found = 0;
        for (i = 0; i < 4; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            _ApplyRyGV(dir, (float)(i * 90 - 135) * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            pos[1] = girl[1];
            from[0] = girl[0];
            from[1] = girl[1] - 70.0f;
            from[2] = girl[2];
            ok = ACTCheckCollis_SAFE_inl(200.0f, from, pos, 0, pos, 30);
            if (ok) {
                d = _DistxzSqGV(boy, pos);
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float objp[4];
    float base[4];
    float tmp1[4];
    float tmp2[4];
    float dir[4];
    char *sub;
    void *obj;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    obj = D_006C1E40.obj;
    GetRootProjectionPosOfGObj(goal, obj);
    GetRootProjectionPosOfGObj(girl, self);
    objp[0] = ((float *)test_CURRENTROOT(obj))[0];
    objp[1] = ((float *)test_CURRENTROOT(obj))[1];
    objp[2] = ((float *)test_CURRENTROOT(obj))[2];
    GetRootProjectionPosOfGObj(base, obj);
    _ACTWait(1);
    if (!GetSafePosition(300.0f, goal, (float *)test_CURRENTROOT(obj), girl,
                         (int)test_CURRENTROOT(D_00639EA4))) {
        while (1) {
            *(float *)(sub + 0x34C) = 0.0f;
            _ACTWait(1);
        }
    }
    turn = 0;
    _ACTWait(1);
    while (1) {
        _ACTCharStatus_Set(self, 11, -1.0f, (int)obj);
        GetRootProjectionPosOfGObj(tmp1, obj);
        GetRootProjectionPosOfGObj(girl, self);
        GetRootProjectionPosOfGObj(tmp2, obj);
        if (_DistxzSqGV(girl, goal) < 3600.0f) {
            turn = 1;
        } else {
            _OrientXZGV(sub + 0x120, goal, girl);
            *(float *)(sub + 0x34C) = 1.0f;
        }
        if (turn) {
            *(float *)(sub + 0x34C) = 0.0f;
            _OrientXZGV(dir, objp, test_CURRENTROOT(self));
            girlBrainHide_GoalTurn(dir, 0);
        }
        _ACTWait(1);
    }
}

void subGirlBrain_HideAdvance(volatile int a0)
{
    float self_pos[4];
    float boy_pos[4];
    Act *sub = GOBJ_ACT(a0);
    long long p;
    unsigned char hit;

    GetRootProjectionPosOfGObj(self_pos, (void *)a0);
    GetRootProjectionPosOfGObj(boy_pos, D_00639EA4);
    ACTWayMove_BeginDetail((void *)a0, self_pos, boy_pos, 0, 0, 0);
    for (;;) {
        ((GirlBrainWork *)D_0029D650)->f_5914 = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
        GetRootProjectionPosOfGObj(boy_pos, D_00639EA4);
        p = ACTWayMove_NextDetail((void *)a0, (char *)sub + 0x120, boy_pos, 0, 0);
        hit = p;
        debug_NMarker(boy_pos, 0xFF, 0, 0, 100.0f);
        if (!hit ||
            (*(float *)((char *)sub + 0x3F8) < 100.0f &&
             (*(float *)((char *)sub + 0x3FC) < 0.0f ? -*(float *)((char *)sub + 0x3FC)
                                                     : *(float *)((char *)sub + 0x3FC)) < 100.0f)) {
            sub->f_34C = 0;
            _ACTWait(1);
            continue;
        }
        {
            /* the actor-entry home is `volatile` (the scheduler rewrites the
             * GObj slot between waits), so the arm reads it once at its top
             * and works from the captured pointer -- ROM's `lw $v0,0($sp)`
             * followed by `move $a0,$v0`. */
            void *g = (void *)a0;

            sub->f_120 = *(float *)((char *)sub + 0x3E0);
            sub->f_124 = *(float *)((char *)sub + 0x3E4);
            sub->f_128 = *(float *)((char *)sub + 0x3E8);
            girlBrainSetWalkRatio(g);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of _AbsRotyGV do not fit the prototype in gv.h */
extern int _AbsRotyGV(void *a, void *b);

int isEnterHideadv_EnemyLocation(float *bpos, float *gpos)
{
    float o1[4];
    float o2[4];
    int i;
    float d;

    bpos[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    bpos[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    bpos[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    gpos[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
    gpos[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
    gpos[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    _OrientXZGV(o1, bpos, gpos);
    for (i = 0; i < ((GirlBrainWork *)D_0029D650)->hide.num; i++) {
        if (*(int *)((char *)((GirlBrainWork *)D_0029D650)->hide.ent[i].obj + 0xC) == 4) {
            d = _DistGV(gpos, ((GirlBrainWork *)D_0029D650)->hide.ent[i].pos);
            if (!(1500.0f < d)) {
                if (_DistSqGV(bpos, ((GirlBrainWork *)D_0029D650)->hide.ent[i].pos) <
                    (d + 100.0f) * (d + 100.0f)) {
                    return 0;
                }
                if (d < 150.0f) {
                    return 0;
                }
                _OrientXZGV(o2, ((GirlBrainWork *)D_0029D650)->hide.ent[i].pos, gpos);
                if (_AbsRotyGV(o1, o2) < 45) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

extern void *D_00629DE4;
/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *, void *);

int isEnterHideadv(void)
{
    char buf[0x20];
    int rv = 0;
    float diff;
    if (D_00639EA4 == 0) {
        goto ret0;
    }
    if (D_00639EA8 == 0) {
        return 0;
    }
    GetRootProjectionPosOfGObj(buf, D_00639EA4);
    GetRootProjectionPosOfGObj(buf + 0x10, D_00639EA8);
    diff = *(float *)(buf + 0x4) - *(float *)(buf + 0x14);
    if (diff < 0.0f) {
        if (-diff > 200.0f) {
            goto set;
        }
        goto test;
    }
    if (diff > 200.0f) {
    set:
        rv = 1;
    }
test:
    if (rv == 0) {
        goto ret0;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 22500.0f) {
        return 1;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 250000.0f) {
        if (isEnterHideadv_EnemyLocation(buf, buf + 0x10) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}

extern int D_0028F8F4[];
extern unsigned char D_0063A8E0[4];
extern unsigned char D_0063A8E4;
extern char D_0063A8E8[];
extern char D_00553C78[];

/* .sbss, girl_act.o's first word (MAIN.MAP line 7594 names no symbol, so the
   name is ours): how many frames in a row WayTest has seen the girl's heading
   swing by more than 90 units. The second word, 0x63C248, stays in the blob
   while subGirlBrain_Attract's stub names it. */
static int wayTurnFrames;

void WayTest(void)
{
    float a[4];
    float b[4];
    char *s;
    void *g;
    int r;

    g = D_00639EA8;
    s = *(char **)((char *)g + 0x164);
    GetRootProjectionPosOfGObj(b, g);
    GetRootProjectionPosOfGObj(a, D_00639EA4);
    if ((D_0028F8F4[0] & 8) || D_0063A8E0[3]) {
        debug_StdPrintfDummy(D_0063A8E8);
        D_0063A8E4 = ACTWayMove_BeginDetail(g, b, a, D_00639EA4, 0, 0);
        D_0063A8E0[3] = 0;
    }
    if (D_0063A8E4) {
        if (!ACTWayMove_NextDetail(g, s + 0x120, a, 0, 0)) {
            debug_StdPrintfDummy(D_00553C78);
        }
        dispWayMarker((float *)(s + 0x410));
    }
    if (*(float *)(s + 0x3F8) < 100.0f) {
        *(float *)(s + 0x34C) = 0.0f;
    } else {
        *(float *)(s + 0x34C) = 1.0f;
    }
    r = _RotyGV(s + 0x3E0, s + 0x120);
    r = (r < 0) ? -r : r;
    if (r >= 0x5B) {
        wayTurnFrames = wayTurnFrames + 1;
        *(float *)(s + 0x120) = *(float *)(s + 0x3E0);
        *(float *)(s + 0x124) = *(float *)(s + 0x3E4);
        *(float *)(s + 0x128) = *(float *)(s + 0x3E8);
    } else {
        *(float *)(s + 0x120) = *(float *)(s + 0x3E0);
        *(float *)(s + 0x124) = *(float *)(s + 0x3E4);
        *(float *)(s + 0x128) = *(float *)(s + 0x3E8);
        wayTurnFrames = 0;
    }
    dispWayMarker((float *)(*(char **)(s + 0x380) + 0x10));
    dispWayMarker((float *)(*(char **)(s + 0x384) + 0x10));
}

/* kept local: this TU's uses of CorrectStickInfo do not fit the prototype in boyact.h */
extern int CorrectStickInfo(void *dir, void *stick);
extern float GetDifferenceFromLowerField(void *obj, int node);
/* kept local: this TU's uses of _GetMotionDirection do not fit the prototype in motionManager2.h */
extern void _GetMotionDirection(float *dir, void *g);
/* kept local: this TU's uses of SetMotionDirectionSmooze do not fit the prototype in commonact.h */
extern void SetMotionDirectionSmooze(void *self, float *dir, float t);
extern void _ACTCommonMailTest(void *self, int a1, int a2, int a3);
extern char D_00553CD8[];
extern char D_0055FE58[];
extern void *D_00639EB0;
extern void *D_00639EC0;
extern void *D_00639ED0;
extern int D_0063AA08;
extern int D_0063B20C;
extern int padtimer_stand;
extern int padtimer_walk;
extern int padtimer_run;

/* one 0x194-byte motion row per motion id: 0x182 and 0x186 are the turn
   rates handed to SetMotionDirectionSmooze (boyact.c reads the same row
   through its CHAINROW macro) */
typedef struct {
    char _000[0x182];
    short f_182;
    char _184[0x2];
    short f_186;
    char _188[0xC];
} MotDirRow;

#define MOTDIRROW(self)                                                                            \
    ((MotDirRow *)(*(int *)(*(char **)((char *)(self) + 0x15C) + 0x4A0) * sizeof(MotDirRow) +      \
                   D_0055FE58))

/* girl_act.c:1533-2539 in the listing.  Lines 1654-2362 carry no instruction
   in the January link or in retail: that block is compiled-out debug code,
   and the strings it printed ("src/girl_act.c", "NOTARGET",
   "[%s] %4d %4d %4d", "delete wg 2\n") still sit in .rodata between this
   function's "girl no!!\n" and its jump table. */
void subGirlControl(volatile int a0)
{
    float dir[4];
    /* Unused here: a vector of the compiled-out block.  What the bytes pin:
       a 16-byte local between dir (0x10) and target (0x30).  What they
       cannot: its name or type. */
    float vec[4];

    /* The target and the actor pointer as one frame record: its members
       take their slots in declaration order (target 0x30, p 0x34), which
       keeps target's zero store and reloads p after every call, as the ROM
       does. */
    struct {
        void *target;
        char *p;
    } w;

    float mdir[4];
    /* Unused here: the locals of the compiled-out block.  What the bytes
       pin: 496 bytes after mdir that set the 0x2E0 frame.  What they cannot:
       how the block declared them. */
    float work[124];
    int hold;
    int push;
    int lim;

    w.p = (char *)GOBJ_ACT(a0);
    w.target = 0;
    while (*(int *)(w.p + 0x130) == 0) {
        debug_StdPrintfDummy(D_00553CD8);
        _ACTWait(1);
    }
    iosPadConnect(w.p + 0x2D8, 0, 1, w.p + 0x1E8);
    D_00639EB0 = w.p + 0x2D8;
    /* The listing gives the back branch its own line 2539: a goto, not a
       for or while, whose end carries no line note.  Without the loop notes
       the in-loop references weigh 1, which is what orders the allocation of
       mdir, dir and D_0028F4C0's high part ($20, $21, $22). */
loop:
    if ((int)(*(unsigned long long *)(w.p + 0x18) >> 48) & 1) {
        if (D_0063AA08 == 0 && ((void *)a0 == D_00639EC0 || D_00639EA0 != 0)) {
            /* The listing gives the jump out of this arm its own line
                   1639 after the last store (1637): the do-while's closing
                   line.  What the bytes pin: the arm's loop notes, which
                   weigh mdir's two uses and dir's first so that mdir is
                   allocated first ($20) and dir second ($21); the
                   declaration-block reading of 1639 leaves them swapped.
                   What they cannot: what the January code broke out of. */
            do {
                iosPadConnect(w.p + 0x2D8, 0, D_00639EA0 != 0, w.p + 0x1E8);
                iosPadRead(w.p + 0x2D8);
                iosPadGetStick(w.p + 0x2D8, w.p + 0x338, 0, 2, 2, D_0063B20C);
                _GetMotionDirection(mdir, (void *)a0);
                *(int *)(w.p + 0x340) = CorrectStickInfo(mdir, w.p + 0x338);
                if (*(float *)(w.p + 0x34C) > 0.001f) {
                    ConvertStickToAbsCoord(dir, w.p + 0x338);
                    *(float *)(w.p + 0x120) = dir[0];
                    *(float *)(w.p + 0x124) = dir[1];
                    *(float *)(w.p + 0x128) = dir[2];
                }
            } while (0);
        } else if ((void *)a0 == D_00639ED0) {
            iosPadConnect(w.p + 0x2D8, 0, 1, w.p + 0x1E8);
        } else {
            iosPadConnect(w.p + 0x2D8, 0, 1, w.p + 0x1E8);
        }
        if (D_00639EA0 == 0 && ((*(unsigned long long *)(w.p + 0x18) & 0x3000000000000000) != 0 ||
                                ((int)(*(unsigned long long *)(w.p + 0x20) >> 7) & 1))) {
            if (*(float *)(w.p + 0x34C) != 0.0f) {
                *(float *)(w.p + 0x34C) = 0.5f;
            }
        }
    }
    if (!(*(float *)(w.p + 0x34C) > 0.1f)) {
        padtimer_stand = padtimer_stand + 1;
    } else {
        padtimer_stand = 0;
    }
    if (*(float *)(w.p + 0x34C) > 0.1f &&
        (*(float *)(w.p + 0x34C) < 0.99f || (*(int *)(w.p + 0x2E0) & 0x20))) {
        padtimer_walk = padtimer_walk + 1;
    } else {
        padtimer_walk = 0;
    }
    if (0.1f < *(float *)(w.p + 0x34C) &&
        !(0.1f < *(float *)(w.p + 0x34C) &&
          (*(float *)(w.p + 0x34C) < 0.99f || (*(int *)(w.p + 0x2E0) & 0x20)))) {
        padtimer_run = padtimer_run + 1;
    } else {
        padtimer_run = 0;
    }
    dir[0] = *(float *)(w.p + 0x120);
    dir[1] = *(float *)(w.p + 0x124);
    dir[2] = *(float *)(w.p + 0x128);
    switch (*(unsigned int *)(w.p + 0x34)) {
    case 0x45:
    case 0x50:
    case 0x73:
        break;
    default:
        if (*(float *)(w.p + 0x34C) > 0.1f && *(int *)(w.p + 0x34) != 0x73) {
            SetMotionDirectionSmooze((void *)a0, dir,
                                     (float)(((void *)a0 == D_00639EA8 && D_00639EA0 != 0)
                                                 ? MOTDIRROW(a0)->f_182
                                                 : MOTDIRROW(a0)->f_186));
        }
        break;
    }
    _ACTCommonMailTest((void *)a0, padtimer_stand, padtimer_walk, padtimer_run);
    switch (*(int *)(w.p + 0x34)) {
    case 1:
        ACTSendMailCorrect((char *)a0, 0xC7);
        break;
    case 2:
        ACTSendMailCorrect((char *)a0, 0xB5);
        break;
    case 3:
        ACTSendMailCorrect((char *)a0, 0xBA);
        break;
    case 29:
        if (!(D_00639EA0 != 0 &&
              *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4 &&
              ((int)(*(unsigned long long *)(w.p + 0x18) >> 56) & 1))) {
            if ((*(float *)(w.p + 0x34C) > 0.1f &&
                 (*(int *)(w.p + 0x340) < -134 || 134 < *(int *)(w.p + 0x340))) ||
                (*(int *)(w.p + 0x2E4) & 0x40)) {
                if (100.0f < GetDifferenceFromLowerField((void *)a0, 0x2C)) {
                    ACTSendMailCorrect((char *)a0, 0x127);
                } else {
                    ACTSendMailCorrect((char *)a0, 0xE2);
                }
            }
        }
        if ((*(float *)(w.p + 0x34C) > 0.1f &&
             (*(int *)(w.p + 0x340) >= -45 && *(int *)(w.p + 0x340) <= 45)) ||
            (*(int *)(w.p + 0x2E4) & 0x10)) {
            ACTSendMailCorrect((char *)a0, 0xC7);
        }
        if (*(float *)(w.p + 0x34C) > 0.1f &&
            (*(int *)(w.p + 0x340) >= 46 && *(int *)(w.p + 0x340) <= 134)) {
            ACTSendMailCorrect((char *)a0, 0x14E);
        }
        if (*(float *)(w.p + 0x34C) > 0.1f) {
            if (-134 <= *(int *)(w.p + 0x340)) {
                if (*(int *)(w.p + 0x340) < -45) {
                    ACTSendMailCorrect((char *)a0, 0x14F);
                }
            }
        }
        break;
    case 28:
        if (!(D_00639EA0 != 0 &&
              *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4 &&
              ((int)(*(unsigned long long *)(w.p + 0x18) >> 56) & 1)) &&
            ((*(float *)(w.p + 0x34C) > 0.1f &&
              (*(int *)(w.p + 0x340) < -134 || 134 < *(int *)(w.p + 0x340))) ||
             (*(int *)(w.p + 0x2E4) & 0x40))) {
            ACTSendMailCorrect((char *)a0, 0xE2);
        } else {
            if (D_00639EA0 != 0 ||
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < *(int *)(w.p + 0x4C)) {
                if (*(float *)(w.p + 0x34C) > 0.1f &&
                    (*(int *)(w.p + 0x340) >= -45 && *(int *)(w.p + 0x340) <= 45)) {
                    ACTSendMailCorrect((char *)a0, 0xC7);
                }
            }
        }
        ACTSendMailCorrect((char *)a0, 0x150);
        break;
    case 15:
        if (*(int *)(w.p + 0x2E4) & 0x20) {
            ACTSendMailCorrect((char *)a0, 0xC7);
        }
        break;
    case 38:
        if (D_00639EA4 != 0) {
            if (((int *)((int *)D_00639EA4[0x59])[0x1A2])[0xEE] >
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 3) {
                ACTSendMailCorrect((char *)a0, 0x14A);
            }
            if (((int *)((int *)D_00639EA4[0x59])[0x1A2])[0xEF] >
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 3) {
                ACTSendMailCorrect((char *)a0, 0x14B);
            }
        }
        lim = *(int *)(w.p + 0x33C) - 128;
        if (100 < lim) {
            ACTSendMailCorrect((char *)a0, 0x14B);
        } else if (lim < -100) {
            ACTSendMailCorrect((char *)a0, 0x14A);
        } else {
            ACTSendMailCorrect((char *)a0, 0x150);
        }
        break;
    case 45:
        if ((D_00639EA0 != 0 ? (*(float *)(w.p + 0x34C) > 0.1f &&
                                (*(int *)(w.p + 0x340) >= -45 && *(int *)(w.p + 0x340) <= 45))
                             : (*(float *)(w.p + 0x34C) > 0.1f)) ||
            ((int)(*(unsigned long long *)(w.p + 0x20) >> 12) & 1)) {
            ACTSendMailCorrect((char *)a0, 0x75);
            ACTSendMailCorrect((char *)a0, 0x74);
        }
        hold = 0;
        push = 0;
        if (D_00639EA4 != 0 && D_00639EA0 == 0) {
            if (*(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x2D) {
                push = *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x3C) != 0x45;
            } else {
                hold = 1;
            }
        }
        if (hold) {
            (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x258))++;
        } else {
            *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x258) = 0;
        }
        if (push) {
            (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x25C))++;
        } else {
            *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x25C) = 0;
        }
        if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x258) >
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2) {
            ACTSendMailCorrect((char *)a0, 0x75);
            ACTSendMailCorrect((char *)a0, 0x74);
        }
        if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x25C) >
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2) {
            ACTSendMailCorrect((char *)a0, 0x74);
        }
        break;
    }
    *(unsigned long long *)(w.p + 0x20) = *(unsigned long long *)(w.p + 0x20) & ~0x4000000ULL;
    if (D_00639EA0 != 0 && (*(int *)(w.p + 0x2E0) & 8)) {
        *(unsigned long long *)(w.p + 0x20) = *(unsigned long long *)(w.p + 0x20) | 0x4000000ULL;
    }
    _ACTWait(1);
    goto loop;
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", subGirlCollision);

#include "girl_act_hand.c.inc"

void GetBoyMode(int *mode, int *p1, int *p2, int *p3)
{
    /* CRUTCH: the `home = uninit` pair below is a stand-in, not source.
       The census labels this body GetBoyMode.453 (a GNU NESTED FUNCTION of
       actGirlHand, girl_act.c:2956 against actGirlHand's 2953) and ROM homes
       the incoming static chain with `sw $2,0($sp)`.  Measured 2026-09-14:
       written as a real nested function inside actGirlHand, with the five
       HandMgr_* bodies of girl_act_hand.c.inc nested alongside it, this body
       is byte-identical (92/92 words) with no stand-in at all -- see the seed
       seeds/girl_act.pass12_actGirlHandUnit.5of7_rc0.TU.c.  The unit is
       indivisible and the parent does not yet match, so the stand-in stays. */
    volatile int home;
    int uninit;
    char *rec;
    home = uninit;
    *mode = ((int *)D_00639EA4[0x59])[0xD];
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    switch (*mode) {
    case 14:
        *mode = 1;
        break;
    case 15:
        *mode = 1;
        break;
    case 8:
        *mode = 1;
        break;
    case 2:
    case 3:
        if (((int *)D_00639EA4[0x59])[0x55] != 0) {
            *mode = 2;
        }
        rec = D_0055FE58 + ((int *)D_00639EA4[0x57])[0x128] * 0x194;
        switch ((*(unsigned int *)(rec + 0x188) >> 22) & 3) {
        case 1:
            *mode = 2;
            break;
        case 2:
            *mode = 3;
            break;
        }
        if (*mode == 3) {
            unsigned long long f =
                *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            } else if ((int)(f >> 32) & 1) {
                *mode = 2;
            }
        }
        if (*mode == 2) {
            unsigned long long f =
                *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            }
        }
        break;
    case 36:
        if (((int *)D_00639EA4[0x59])[0xF] == 0x5E) {
            *p2 = 1;
        } else {
            *mode = 1;
        }
        break;
    case 5:
    case 13:
    case 17:
    case 18:
    case 68:
        *mode = 3;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", actGirlHand);

/* kept local: this TU's uses of PAIR_GetPosition_BOY do not fit the prototype in act-game.h */
extern void PAIR_GetPosition_BOY(float *boy, float *dir);
/* kept local: this TU's uses of StartCorrectPosition do not fit the prototype in commonact.h */
extern void StartCorrectPosition(void *obj, float *dst, float *cur, float dist, int flag);
/* kept local: this TU's uses of IsCorrectPosition do not fit the prototype in commonact.h */
extern int IsCorrectPosition(void *obj);
/* kept local: this TU's uses of ContinueCorrectPosition do not fit the prototype in commonact.h */
extern void ContinueCorrectPosition(void *obj);
/* kept local: this TU's uses of PAIR_IsStatus_BOY_PULL do not fit the prototype in act-game.h */
extern int PAIR_IsStatus_BOY_PULL(void);

void actGirlPulledReady(volatile int a0)
{
    float boy[4];
    float dir[4];
    float pos[4];
    float dst[4];
    float d;
    float v;

    GetRootPosition(pos, (void *)a0);
    PAIR_GetPosition_BOY(boy, dir);
    sceVu0ScaleVector(dst, dir, 30.0f);
    sceVu0AddVector(dst, boy, dst);
    dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    sceVu0ScaleVector(dir, dir, -1.0f);
    d = _DistxzGV(pos, dst) * 0.5f;
    v = (d < 1.0f) ? 1.0f : ((d > 20.0f) ? 20.0f : d);
    StartCorrectPosition((void *)a0, dst, dir, v, 1);
    while (IsCorrectPosition((void *)a0)) {
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)a0, 0x50);
        }
        _ACTWait(1);
    }
}

typedef struct {
    int w[8];
} GirlPullBlk;

/* kept local: this TU's uses of ACTGame_ConnectHand do not fit the prototype in act-game.h */
extern void ACTGame_ConnectHand(void);
/* kept local: this TU's uses of SetMotionNodeFixModeParameter do not fit the prototype in motionManager2.h */
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);

void actGirlPulledGo(volatile int a0)
{
    float q[4];
    char *s;
    int m;

    s = *(char **)((char *)a0 + 0x164);
    *(void **)(s + 0x14) = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    *(GirlPullBlk *)((char *)GOBJ_SUB(a0) + 0x180) = *(GirlPullBlk *)(s + 0x620);
    *(int *)(*(char **)((char *)a0 + 0x15C) + 0x634) = 1;
    *(char **)(s + 0x18) = (char *)afterGirlPulledGo;
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)a0, 0x53);
            ACTSendMailCorrect((void *)a0, 0x54);
        } else {
            m = GOBJ_ACT(D_00639EA4)->unk34;
            if (m == 2 || m == 3) {
                ACTSendMailCorrect((void *)a0, 0x55);
                ACTSendMailCorrect((void *)a0, 0x56);
            }
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < *(int *)(s + 0x4C)) {
                ACTSendMailCorrect((void *)a0, 0x57);
            }
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of PAIR_GetPosition_BOY_DITCH do not fit the prototype in act-game.h */
extern void PAIR_GetPosition_BOY_DITCH(float *bpos, float *gpos);
/* kept local: this TU's uses of PAIR_IsStatus_BOY_DITCH do not fit the prototype in act-game.h */
extern int PAIR_IsStatus_BOY_DITCH(void);

void actGirlDitch3mReady(volatile int a0)
{
    float gpos[4];
    float now[4];
    float bpos[4];

    GetRootPosition(now, (void *)a0);
    PAIR_GetPosition_BOY_DITCH(bpos, gpos);
    bpos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    StartCorrectPosition((void *)a0, bpos, gpos, 20.0f, 1);
    while (IsCorrectPosition((void *)a0)) {
        debug_NMarker(bpos, 0, 0, 0xFF, 100.0f);
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)a0, 0x18E);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of debug_Arrow do not fit the prototype in camera-editor.h */
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);

void actGirlReadyMove(volatile int a0)
{
    float dst[4];
    float dir[4];
    char *p;
    int n;

    n = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 80.0f / 60.0f);
    dst[0] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x230);
    dst[1] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x234);
    dst[2] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x238);
    dir[0] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x240);
    dir[1] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x244);
    dir[2] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x248);
    dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    StartCorrectPosition((void *)a0, dst, dir, (float)n, 1);
    while (IsCorrectPosition((void *)a0)) {
        debug_Arrow(100.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        ACTSendMailCorrect((void *)a0, 0x10C);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of ACTGameCollisionOn do not fit the prototype in act-game.h */
extern void ACTGameCollisionOn(void *a0);
/* kept local: this TU's uses of ACTSetPositionWithFitting do not fit the prototype in commonact.h */
extern void ACTSetPositionWithFitting(void *a0, float *pos);
/* kept local: this TU's uses of SetMotionDirection do not fit the prototype in motionManager2.h */
extern void SetMotionDirection(void *a0, float *dir);
/* kept local: this TU's uses of ACTGame_CheckHandMotion do not fit the prototype in act-game.h */
extern int ACTGame_CheckHandMotion(void *a0, void *a1);
/* kept local: this TU's uses of GetSkeltonPosition do not fit the prototype in act-game.h */
extern void GetSkeltonPosition(float *out, void *obj, int node);
extern void sceVu0SubVector(void *out, void *a, void *b);

void actGirlRescueDst(volatile int a0)
{
    float dir[4];
    float q[4];
    float pos[4];
    float p1[4];
    float p2[4];
    float dst[4];
    char *s;
    char *w;
    int n;
    int done;

    s = *(char **)((char *)a0 + 0x164);
    memset(q, 0, 16);
    n = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 3;
    done = 0;
    *(void **)(s + 0x14) = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    ACTGameCollisionOn((void *)a0);
    gflagOff(393);
    pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
    pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
    pos[1] = *(float *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) + 0x304);
    ACTSetPositionWithFitting((void *)a0, pos);
    w = *(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680);
    _OrientXZGV(q, w + 0x2F0, w + 0x300);
    sceVu0SubVector(dir, *(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) + 0x300,
                    test_CURRENTROOT((void *)a0));
    sceVu0ScaleVector(dir, dir, 1.0f / (float)n);
    SetMotionDirection((void *)a0, q);
    while (1) {
        if (!ACTGame_CheckHandMotion(D_00639EA4, D_00639EA8)) {
            ACTGame_DisconnectHand();
            done = 1;
        }
        if (!done && ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2 < *(int *)(s + 0x4C)) {
            GetSkeltonPosition(p1, D_00639EA4, 6);
            GetSkeltonPosition(p2, D_00639EA8, 22);
            if (!(_DistSqGV(p1, p2) < 400.0f)) {
                iosOmSendMail(D_00639EA4, 248, D_0063A61C);
            }
            ACTSendMailCorrect((void *)a0, 198);
        }
        if (n > 0) {
            sceVu0AddVector(dst, test_CURRENTROOT((void *)a0), dir);
            dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            ACTSetPositionWithFitting((void *)a0, dst);
        }
        iosOmSendMail(D_00639EA4, 350, D_0063A61C);
        n--;
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of SetMotionNodeFixModeParameter do not fit the prototype in motionManager2.h */
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);

void actGirlSupportBGBegin(volatile int a0)
{
    float v1[4];
    float v2[4];
    float dst[4];
    float q[4];
    char *s;
    int i;

    i = 0;
    s = *(char **)((char *)a0 + 0x164);
    v1[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    v1[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    v1[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    v2[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
    v2[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
    v2[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    *(void **)(s + 0x14) = (void *)afterGirlSupportBGBegin;
    ACTGame_ConnectHand();
    while (1) {
        if (i++ < 6) {
            _InterGV(dst, v1, v2, (float)i, (float)(5 - i));
        }
        ACTSendMailCorrect((void *)a0, 0x184);
        _ACTWait(1);
    }
}

extern int girlcalled;
extern int GirlInfo;
extern int D_0063A954;
extern int D_0063B180;
extern char D_00554078[];
extern char D_002A84F8[];
/* kept local: this TU's uses of subCommonIdle do not fit the prototype in commonact.h */
extern void subCommonIdle(void);
/* kept local: this TU's uses of actCreateSubThread do not fit the prototype in act.h */
extern void actCreateSubThread(void *entry, int prio);
/* kept local: this TU's uses of actInitialize do not fit the prototype in act.h */
extern char *actInitialize(void *self);
/* kept local: this TU's uses of actInitialize_ext_charcter do not fit the prototype in act.h */
extern void actInitialize_ext_charcter(void *self);
/* kept local: this TU's uses of actInitialize_only_charcter do not fit the prototype in act.h */
extern void actInitialize_only_charcter(void *self);
/* kept local: this TU's uses of actInitialize_geo do not fit the prototype in act.h */
extern void actInitialize_geo(void *self);
/* kept local: this TU's uses of _ACTGame_GetParamF do not fit the prototype in act-game.h */
extern float _ACTGame_GetParamF(int idx);
/* kept local: this TU's uses of ACTGame_LwsEffectInit do not fit the prototype in act-game.h */
extern void ACTGame_LwsEffectInit(void *self);
/* kept local: this TU's uses of ACTLookTarget_Init do not fit the prototype in act-game.h */
extern void ACTLookTarget_Init(void *self);
/* kept local: this TU's uses of ACTParaStatus_Init do not fit the prototype in act-game.h */
extern void ACTParaStatus_Init(void *self);
/* kept local: this TU's uses of _ACTCharStatus_Init do not fit the prototype in act-game.h */
extern void _ACTCharStatus_Init(void *self);
/* kept local: this TU's uses of ACTGameView_FirstSet do not fit the prototype in act-game.h */
extern void ACTGameView_FirstSet(void *self);

void actGirlStart(void *self)
{
    char *p;

    girlcalled = 0;
    D_0063A954 = 0;
    GirlInfo = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 30;
    debug_StdPrintfDummy(D_00554078, self);
    p = actInitialize(self);
    actInitialize_ext_charcter(self);
    actInitialize_only_charcter(self);
    actInitialize_geo(self);
    *(int *)(*(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x254) =
        (int)(_ACTGame_GetParamF(0x22) * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) /
              60.0f);
    ACTGame_LwsEffectInit(self);
    ACTLookTarget_Init(self);
    *(int *)(p + 0x180) = 0;
    *(int *)(p + 0x184) = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init(self);
    _ACTWait(1);
    ACTGameView_FirstSet(self);
    brainInitGirlSet(self, D_00639EA4);
    if (D_0063B180 != 0) {
        actCreateSubThread(subGirlBrainMain, 20);
    }
    *(char **)(p + 0xD0) = D_002A84F8;
    actCreateSubThread(subGirlControl, 21);
    actCreateSubThread(subGirlCollision, 21);
    actCreateSubThread(subCommonIdle, 21);
    *(char **)(p + 0xD4) = D_002A84F8 + 0x78;
    *(int *)(p + 0x350) = 0;
    *(float *)(p + 0x1E0) = 100.0f;
    *(int *)(p + 0x48) = 1;
    ACTSendMailCorrect(self, 0xC7);
    _ACTWait(0);
}

extern void sceVu0Normalize(void *out, void *in);

void GirlAct_BoyAndMeCollisionMail(void *a0)
{
    float vec[4];
    float boyPos[4];
    float myPos[4];
    float ang;

    ACTSendMailCorrect(a0, 0x10D);

    if (((int *)D_00639EA4[0x59])[0xD] == 1) {
        return;
    }
    GetRootPosition(boyPos, D_00639EA4);
    GetRootPosition(myPos, a0);

    sceVu0SubVector(vec, boyPos, myPos);
    sceVu0Normalize(vec, vec);

    ang = _RotyGV(vec, test_CURRENTORIENT(a0));

    if ((ang < 0.0f ? -ang : ang) < 45.0f) {
        ACTSendMailCorrect(a0, 0x10E);
        return;
    } else if ((ang < 0.0f ? -ang : ang) > 135.0f) {
        ACTSendMailCorrect(a0, 0x10F);
        return;
    } else if (ang > 45.0f) {
        ACTSendMailCorrect(a0, 0x110);
        return;
    } else {
        ACTSendMailCorrect(a0, 0x111);
    }
}

extern char D_005577D0[];

typedef struct {
    float x;    /* 0x00 */
    float y;    /* 0x04 */
    float z;    /* 0x08 */
    int f_0C;   /* 0x0C */
    int f_10;   /* 0x10 */
    float f_14; /* 0x14 */
    float f_18; /* 0x18 */
} EscortPoint;  /* 0x1C */

extern EscortPoint D_0055BA60[98];

static inline unsigned char isGirlEscortStatus(void)
{
    Act *s = GOBJ_ACT(D_00639EA8);
    int mode = s->unk34;
    char *attr = D_005577D0 + mode * 0x50;
    if (((*(unsigned int *)(attr + 0x4C) >> 13) & 1) && mode != 0x6F &&
        ((int)(*(unsigned long long *)((char *)s + 0x20) >> 46) & 1)) {
        return 1;
    }
    return 0;
}

static inline EscortPoint *searchEscortPoint(int a0, int a1)
{
    EscortPoint *p;
    int i;
    for (i = 0; i < 98; i++) {
        p = &D_0055BA60[i];
        if (p->f_0C == a0 && p->f_10 == a1) {
            return p;
        }
    }
    return 0;
}

int IsGirlStatusEscortEnable(int a0, int a1)
{
    float v[4];
    EscortPoint *p;
    float d;

    if (D_00639EA4 != 0 && D_00639EA8 != 0 && isGirlEscortStatus()) {
        p = searchEscortPoint(a0, a1);
        if (p != 0) {
            v[0] = -p->x;
            v[1] = -p->y;
            v[2] = -p->z;
            d = _DistGV(v, test_CURRENTROOT(D_00639EA8));
            if (d < p->f_14) {
                *(float *)(GOBJ_ACT(D_00639EA8)->f_688 + 0x330) = d * p->f_18;
                return 1;
            }
        } else {
            if (_DistSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) <
                _ACTGame_GetParamF(5) * _ACTGame_GetParamF(5)) {
                return 1;
            }
        }
    }
    return 0;
}

extern Vec4 D_005540A0; /* { FLT_MAX, 0, 0, 1 } : "no girl" position */
extern Col4 D_00554090; /* { 0, 0x10, 0x20, 0x80 } : wire sphere colour */
extern int D_0063B228;  /* debug display switch */
extern void sceVu0UnitMatrix(void *a0);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int a0);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);

static inline void dispEscortSphere(void *pos, float r, unsigned char in)
{
    Col4 col;

    if (D_0063B228) {
        MatrixDrive_PushMatrix();
        col = D_00554090;
        if (in) {
            col.c[0] = 0xFF;
        }
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

void DebugDispAutoEscort(void)
{
    Vec4 pos = D_005540A0;
    Vec4 v;
    EscortPoint *p;
    int i;
    int in;

    if (D_0063B228 == 0) {
        return;
    }
    if (D_00639EA8 != 0 && isGirlEscortStatus()) {
        pos.f[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
        pos.f[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
        pos.f[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    }
    for (i = 1; i < 16; i++) {
        p = searchEscortPoint(stage_no, i);
        if (p != 0) {
            v.f[0] = -p->x;
            v.f[1] = -p->y;
            v.f[2] = -p->z;
            in = _DistSqGV(&v, &pos) < p->f_14 * p->f_14;
            dispEscortSphere(&v, p->f_14, in);
        }
    }
}

/* the *(sub+0x688) ACT parameter block, viewed as a struct.  Stores through it
   must be COMPONENT_REFs (MEM_IN_STRUCT_P) and not plain scalar indirections:
   alias.c can then tell them apart from the fixed-address parameter home, which
   is what lets ROM's reloads of `a0` move ahead of them. */
typedef struct {
    char _0[0x3B0];
    int f_3B0; /* 0x3B0 : frames left before the "cannot reach" retry */
    char _3B4[0x16C];
    float f_520; /* 0x520 : hint-point target position */
    float f_524;
    float f_528;
} ActPara;

/* kept local: this TU's uses of RequestChangeHandMode do not fit the prototype in act-game.h */
extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, void *a6);

void actGirlHintPoint(volatile int a0)
{
    float d[4];
    float p[4];
    float q[4];
    float r[4];
    float u[4];
    float o1[4];
    float o2[4];
    void *tgt;
    char *s;

    tgt = (void *)*(int *)(GOBJ_ACT(a0)->f_30);
    s = *(char **)((char *)a0 + 0x164);
    *(void **)(s + 0x18) = (void *)afterGirlHintPoint;
    sceVu0SubVector(d, test_CURRENTROOT(tgt), test_CURRENTROOT((void *)a0));
    while (1) {
        sceVu0AddVector(p, test_CURRENTROOT((void *)a0), d);
        sceVu0SubVector(p, p, test_CURRENTROOT(tgt));
        RequestChangeHandMode((void *)a0, 1, 4, 3, tgt, 0, p);
        if (D_00639EA4) {
            q[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
            q[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            q[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
            r[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
            r[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
            r[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            sceVu0AddVector(u, q, d);
            _OrientXZGV(o1, r, q);
            _OrientXZGV(o2, u, q);
            if (_AbsRotyGV(o1, o2) >= 121) {
                _ACTCharStatus_Set((void *)a0, 13, -1.0f, 0);
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_520 = u[0];
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_524 = u[1];
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_528 = u[2];
            }
        }
        _ACTCharStatus_Set((void *)a0, 14, -1.0f, 0);
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of ACTGame_FLAG_TETSUNAGI do not fit the prototype in act-game.h */
extern int ACTGame_FLAG_TETSUNAGI(void);

void ACTGame_GirlBeforeFunc(void *self)
{
    float boyPos[4];
    float girlPos[4];
    char *s;

    s = (char *)*(int *)((char *)self + 0x164);
    D_006C1E20[0] = 0;
    D_006C1E20[1] = 0;
    if (*(int *)(s + 0x34) != 69) {
        *(unsigned long long *)(s + 0x20) &= ~0x100000ULL;
    }
    *(unsigned long long *)(s + 0x18) &= ~0x40000000000ULL;
    if (ACTGame_FLAG_TETSUNAGI()) {
        if (*(int *)(s + 0x34) == 5 || *(int *)(s + 0x34) == 69) {
            *(unsigned long long *)(s + 0x18) |= 0x40000000000ULL;
        } else {
            GetSkeltonPosition(boyPos, D_00639EA4, 6);
            GetSkeltonPosition(girlPos, D_00639EA8, 22);
            if (_DistSqGV(boyPos, girlPos) < 900.0f) {
                *(unsigned long long *)(s + 0x18) |= 0x40000000000ULL;
            }
        }
    }
}

extern int D_002A2E2C[];

void *FindGirlPullupFloorBoxGObj(void)
{
    void *g = D_00639EA8;
    if (D_002A2E2C[0] == 7 && GOBJ_ACT(D_00639EA4)->unk34 == 0x4E) {
        return *(void **)(*(char **)(*(char **)((char *)g + 0x164) + 0x688) + 0x374);
    }
    return 0;
}

/* kept local: this TU's uses of _MoveGV do not fit the prototype in gv.h */
extern float _MoveGV(float *dst, float *from, float *to, float t);

void actGirlSupportGBBegin(volatile int a0)
{
    float girl[4];
    float boy[4];
    float dst[4];

    for (;;) {
        girl[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
        girl[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
        girl[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
        boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
        boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
        boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
        boy[1] = girl[1];
        _MoveGV(dst, girl, boy, 20.0f);
        SetDirectRootPositionNoFitting((void *)a0, dst);
        ACTSendMailCorrect((void *)a0, 0x17E);
        _ACTWait(1);
    }
}

/* girl_act.c:3933, the status-range test the listing attributes to its own
   line inside actGirlSupportGBLoop's loop. */
static inline unsigned char isGirlSupportGBStatus(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);

    if (st < 0x6B) {
        if (0x68 <= st) {
            return 1;
        }
    }
    return 0;
}

void actGirlSupportGBLoop(volatile int a0)
{
    for (;;) {
        if (!isGirlSupportGBStatus()) {
            ACTSendMailCorrect((void *)a0, 0x180);
        }
        _ACTWait(1);
    }
}

void actGirlSupportGBEnd(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

void actGirlHangG3M(volatile int a0)
{
    ACTWay_SetBeginPositionIllegal((char *)a0);
    for (;;) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)a0, 0x194);
        }
        _ACTWait(1);
    }
}

extern char D_00553FD0[];

void actGirlDitch3mExec(volatile int a0)
{
    float boy[4];
    float girl[4];
    float dst[4];
    int i = 0;
    int go = 1;

    ACTGame_ConnectHand();
    debug_StdPrintfDummy(D_00553FD0);
    for (;;) {
        if (go) {
            boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
            boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
            boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            girl[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
            girl[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
            girl[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
            _InterGV(dst, boy, girl, 1.0f, 1.0f);
            SetRootPosition((void *)a0, dst);
            i++;
            go = i < 3;
        }
        ACTSendMailCorrect((void *)a0, 0x193);
        _ACTWait(1);
    }
}

extern char D_00554000[];

void actGirlStand(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00554000);
    sub->unk34 = 1;
    _ACTWait(0);
}

extern char D_00554018[];

void actGirlWalk(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00554018);
    sub->unk34 = 2;
    _ACTWait(0);
}

extern char D_00554030[];

void actGirlRun(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00554030);
    sub->unk34 = 3;
    _ACTWait(0);
}

/* kept local: this TU's uses of ACTAdjustPlane do not fit the prototype in commonact.h */
extern void ACTAdjustPlane(void *self, void *plane);

void actGirlHang(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int rope;
    /* rope-hang detected from the ACT parameter block */
    int hang = 0;

    if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x904) == 0x5A) {
        hang = *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4;
    }
    /* the debug/free camera forces the pull mail on regardless */
    rope = hang;
    if (D_00639EA0 != 0) {
        if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4) {
            rope = 1;
            ACTAdjustPlane((void *)a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
        }
    }
    for (;;) {
        if (rope && (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < *(int *)((char *)s + 0x4C)) {
            ACTSendMailCorrect((void *)a0, 0xC7);
        }
        _ACTWait(1);
    }
}

void actGirlBHang(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int rope = 0;

    if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x904) == 0x5A) {
        rope = *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4;
    }
    ACTAdjustPlane((void *)a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
    for (;;) {
        if (rope && (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < *(int *)((char *)s + 0x4C)) {
            ACTSendMailCorrect((void *)a0, 0xC7);
        }
        ACTSendMailCorrect((void *)a0, 0x150);
        _ACTWait(1);
    }
}

extern char D_00554060[];

void actGirlAttack(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00554060);
    sub->unk34 = 15;
    _ACTWait(0);
}

/* kept local: this TU's uses of _ACTLookTarget_Set do not fit the prototype in act-game.h */
extern void _ACTLookTarget_Set(void *self, void *target, float *pos, int kind, int flag);

void actGirlBecall(volatile int a0)
{
    int i;

    for (i = 0; i < (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2; i++) {
        _ACTLookTarget_Set((void *)a0, D_00639EA4, 0, 5, 1);
        _ACTWait(1);
    }
    ACTSendMailCorrect((void *)a0, 252);
    _ACTWait(0);
}

void actGirlBehanged(volatile int a0)
{
    float q[4];

    for (;;) {
        memset(q, 0, 0x10);
        q[3] = 1.0f;
        RotQuaternionY(q, 0);
        SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
        _ACTWait(1);
    }
}

void actGirlAttractAction(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((void *)a0, 340);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of _ACTCharStatus_Set do not fit the prototype in act-game.h */
extern void _ACTCharStatus_Set(void *self, int status, float time, int flag);

void actGirlHintVoice(volatile int a0)
{
    for (;;) {
        _ACTCharStatus_Set((void *)a0, 14, -1.0f, 0);
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

void actGirlCannotReach(volatile int a0)
{
    for (;;) {
        ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_3B0 =
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10;
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

extern char D_005539D0[];
extern char D_005539B8[];

void actGirlHand50(volatile int a0)
{
    float dir[4];
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_005539B8);
    sceVu0ScaleVector(dir, (float *)((char *)sub + 0x4B0), -1.0f);
    SetMotionDirection((void *)a0, dir);
    SetDirectRootPositionNoFitting((void *)a0, (float *)((char *)sub + 0x590));
    sub->f_E0 = 0;
    *(void **)((char *)sub + 0x14) = (void *)afterGirlHand50;
    do {
        _ACTWait(1);
    } while ((sub->f_E0 & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x60);
        _ACTWait(1);
    }
}

extern char D_005539A0[];

void afterGirlHand50(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x60, D_0063A61C);
    ACTGame_DisconnectHand();
}

extern char D_00553A00[];

void actGirlHand100(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00553A00);
    sub->unk34 = 0x53;
    *(void **)((char *)sub + 0x14) = (void *)afterGirlHand100;
    sub->f_E0 = 0;
    do {
        _ACTWait(1);
    } while ((sub->f_E0 & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x65);
        _ACTWait(1);
    }
}

void afterGirlHand100(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x65, D_0063A61C);
    ACTGame_DisconnectHand();
}

extern char D_00553A30[];

void actGirlHand200(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00553A30);
    sub->unk34 = 0x54;
    *(void **)((char *)sub + 0x14) = (void *)afterGirlHand200;
    sub->f_E0 = 0;
    do {
        _ACTWait(1);
    } while ((sub->f_E0 & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x6A);
        _ACTWait(1);
    }
}

void afterGirlHand200(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x6A, D_0063A61C);
    ACTGame_DisconnectHand();
}

int NotNeedBackHand(void)
{
    char *g = D_00639EA8;
    Act *w = GOBJ_ACT(g);

    if ((((int)(*(unsigned long long *)((char *)w + 0x18) >> 40)) & 1) == 0) {
        return 1;
    }
    if (w->unk34 == 0x45 && D_002A2F70.f_5D != 0 && D_002A2F70.f_58 == 0) {
        return 1;
    }
    return 0;
}

void SetGirlDangerGObj(int a0)
{
    char *g = D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = a0;
    }
}

void ClearGirlDangerGObj(void)
{
    char *g = (char *)D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = 0;
    }
}

void subGirlBrain_Idle(volatile int a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->f_34C = 0;
    _ACTWait(0);
}

void subGirlBrain_Hesitate(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int i = 1;

    for (;;) {
        *(void **)((char *)s + 0x34C) = 0;
        if (i % ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2) == 0) {
            D_0029D650[0x58F0] = 1;
        }
        i++;
        _ACTWait(1);
    }
}

void subGirlBrain_Becarry(volatile int a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->f_34C = 0;
    _ACTWait(0);
}

void subGirlBrain_Busy(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    GirlBrainWork *w = (GirlBrainWork *)D_0029D650;
    int i = 0;

    sub->f_34C = 0;
    while (1) {
        if (w->others.num) {
            _ACTCharStatus_Set((void *)a0, 2, -1.0f, w->others.ent[0].obj);
        }
        if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] < i &&
             ACTGameView_Check((void *)a0, D_00639EA4)) ||
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < i) {
            w->f_58F0 = 1;
        }
        i++;
        _ACTWait(1);
    }
}

extern void Danger_Bomb(void *self);
extern void Danger_Box(void *self);
extern void Danger_Rotobject(void *self);

void subGirlBrain_DangerEnv(volatile int a0)
{
    switch (D_006C1E40.kind) {
    case 1:
        Danger_Bomb((void *)a0);
        break;
    case 2:
        Danger_Gondola((void *)a0);
        break;
    case 3:
        Danger_Box((void *)a0);
        break;
    case 4:
        Danger_Rotobject((void *)a0);
        break;
    }
    _ACTWait(0);
}

int enemy_list_compare(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}

int ACTCheckCollis_SAFE(float height, float *p0, float *p1, void *actor, float *posout, int radius)
{
    ClipWork work;
    float tmp[4];
    int flag;
    int rv;

    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->f_74 : 0;

    work.radius = (float)radius;
    work.a[0] = p0[0];
    work.a[1] = p0[1];
    work.a[2] = p0[2];
    work.b[0] = p1[0];
    work.b[2] = p1[2];
    work.b[1] = p0[1];

    tmp[0] = p1[0];
    tmp[1] = p0[1];
    tmp[2] = p1[2];

    if (flag != 0) {
        GOBJ_SUB(actor)->f_74 = 0;
    }
    ClipWall(&work);
    if (work.wallHit == 0) {
        ClipWallField(&work);
        if (work.wallHit == 0)
            goto no_wall;
    }
    tmp[0] = work.pos[0];
    tmp[1] = work.pos[1];
    tmp[2] = work.pos[2];
no_wall:
    work.a[0] = tmp[0];
    work.a[1] = tmp[1];
    work.a[2] = tmp[2];
    work.b[0] = tmp[0];
    work.b[2] = tmp[2];
    work.b[1] = tmp[1] + height;
    ClipFloor(&work);
    if (work.floorHit == 0) {
        rv = 0;
    } else {
        work.pos[1] -= 10.0f;
    }
    if (posout != 0) {
        posout[0] = work.pos[0];
        posout[1] = work.pos[1];
        posout[2] = work.pos[2];
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->f_74 = 1;
    }
    return rv;
}

extern char D_00553E50[];

void afterGirlHand(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy(D_00553E50);
    iosPadActStop(7);
    ACTWay_SetBeginPositionIllegal(local);
}

void afterGirlPulledGo(void *a0)
{
    void *volatile q = a0;
    int *p = (int *)GOBJ_SUB(q);
    *(int *)((char *)p + 0x634) = 0;
}

extern char D_00554048[];

void actGirlJump(volatile int a0)
{
    char *g = (char *)a0;
    Act *s = GOBJ_ACT(g);
    debug_StdPrintfDummy(D_00554048);
    s->unk34 = 4;
    _ACTWait(0);
}

void afterGirlSupportBGBegin(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTGame_DisconnectHand();
}

int isMustCheckCylinder(void *a, void *b)
{
    if ((a == (void *)D_00639EA4 && b == D_00639EA8) ||
        (a == D_00639EA8 && b == (void *)D_00639EA4)) {
        if (GOBJ_ACT(D_00639EA8)->unk34 == 0x51) {
            return 1;
        }
    }
    return 0;
}

void afterGirlHintPoint(volatile int a0)
{
    RequestChangeHandMode((void *)a0, 1, 4, 0, 0, 0, 0);
}
