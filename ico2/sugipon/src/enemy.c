typedef struct {
    int a;
    int b;
    float life;
    float c;
    float d;
    float dodge;
    int paraIndex : 8;
    unsigned int flyType : 2;
    unsigned int battleType : 2;
} EnemyDef;

extern EnemyDef D_00624880[];

#include "typedef.h"
#include "enemy.h"
#include "sugiCommon.h"
#include "charFileManager.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "gobj.h"
#include "GifPacket.h"
#include "enemy_act.h"
#include "EnemyInit.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "enemyParts.h"
#include "geometryManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "particleEffect.h"
#include "quaternion.h"
#include <libvu0.h>
#include <stdlib.h>
#include "ios.h"
#include "main.h"

/* kept local: int (float, float, float, int, int, char *, int) here, int (int, int, int, int) in Primitive.h */
extern int prim_InitParticle(float f12, float f13, float f14, int num, int a1, char *tag, int a3);
extern void __assert(char *file, int line, char *mes);

typedef struct {
    float x;
    float y;
    float z;
    float w;
} EnemyPosEntry;

/* static helper the listing places at enemy.c lines 99-100, expanded only into
 * setEnemyParticleObject; never emitted out of line, so it has no MAIN.MAP
 * symbol and this name is ours. */
static inline void clearEnemyParticleFlags(int *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
        p[i] = 0;
}

/* .data, the whole of enemy.o's run (MAIN.MAP sizes the member 0x40): a unit
   matrix with the translation (10, 0, 0).  No instruction in the retail ELF
   reaches it and MAIN.MAP names no symbol in the run, so the role is not
   recoverable; the object itself is, and this is where the member emits it. */
static float offsetMatrix[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {10.0f, 0.0f, 0.0f, 1.0f},
};

/* RECONSTRUCTION, read from the ROM.  The 84-byte work record InitEnemyGeo
   allocates into the object's work word: the variation kind and the counter
   setEnemyObject randomises it with, the enemy-table row, the particle and
   broken-part tables, the two eyes, the footprints, the per-node particle
   flags, the object-loaded flag, the wing and stone parameters and the
   scale. */
typedef struct {
    int kind;                 /* 0x00 */
    int ctr;                  /* 0x04, setEnemyObject's randomiser state */
    int def;                  /* 0x08, the D_00624880 row */
    int padC;                 /* 0x0C */
    int *particle;            /* 0x10 */
    int *broken;              /* 0x14 */
    EnemyEye *eye0;           /* 0x18 */
    int f_1C;                 /* 0x1C */
    EnemyEye *eye1;           /* 0x20 */
    int f_24;                 /* 0x24 */
    EnemyFootPrintHead *foot; /* 0x28 */
    int f_2C;                 /* 0x2C */
    int *flag;                /* 0x30 */
    int pad34;                /* 0x34 */
    int loaded;               /* 0x38 */
    float f_3C;               /* 0x3C */
    short f_40;               /* 0x40 */
    float wing;               /* 0x44 */
    float scale;              /* 0x48 */
    int timer;                /* 0x4C */
    float f_50;               /* 0x50 */
} EnemyWork;

void setEnemyParticleObject(GObj *self, int pid)
{
    Sub15C *sub = GOBJ_SUB(self);
    EnemyWork *w = sub->work;
    int n = sub->skelNodeNum;
    char *tbl = *(char **)((char *)sub + 0x8C);
    char *p = *(char **)((char *)sub + 0x870);
    int *parts;
    int *fl;
    float size;
    int i;
    int cnt;
    int num;
    int n4;
    int type;
    EnemyPosEntry *v;
    EnemyPosEntry *q;

    size = (*(float *)(p + 0x20) + *(float *)(p + 0x24) + *(float *)(p + 0x28)) * 32.0f * 0.33333f *
           0.5f * 10.0f;
    parts = (int *)iosMallocDebug(ios_partition_sugipon, n * 4, "src/enemy.c", 130);
    w->particle = parts;
    fl = (int *)iosMallocDebug(ios_partition_sugipon, n * 4, "src/enemy.c", 132);
    w->flag = fl;
    clearEnemyParticleFlags(fl, n);
    for (i = 0; i < n; i++) {
        q = (EnemyPosEntry *)enemy_GetPositionTable(pid, i);
        v = q;
        if (q == 0) {
            (w->flag)[i] = 0;
            continue;
        }
        (w->flag)[i] = 1;
        for (cnt = 0; q->w > -1.0f; cnt++)
            q++;
        q = v;
        parts[i] = 0;
        if (cnt <= 0)
            continue;
        if (cnt >= 80)
            num = 80;
        else
            num = cnt;
        parts[i] = prim_InitParticle(size, 0.5f, 0.5f, num, 1, "enemy_sprite", 0);
        if (parts[i] == 0) {
            /* EUC-JP: "cannot reserve the memory for the enemy soldier particles" */
            debug_StdPrintfDummy("敵兵のパーティクルのメモリを確保できません\n");
            debug_assertMessage("src/enemy.c", 177, "CAN'T ALLOCATE ENEMY'S PARTICLE MEMORY\n");
            __assert("src/enemy.c", 177, "e");
        }
        for (cnt = 0; q->w > -1.0f && cnt < 80; cnt++, q++) {
            n4 = rand() % 4;
            _CopyVector(*(char **)(parts[i] + 0x190) + cnt * 32, q);
            _CopyVector(*(char **)(parts[i] + 0x194) + cnt * 32, q);
            type = *(int *)(tbl + i * 0x40 + 4);
            if (type >= 38)
                goto spread;
            if (type < 36)
                goto spread;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x10) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x10) = 0.5f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x14) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x14) = 0.0f;
            goto done;
        spread:
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x10) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x10) = (n4 / 2) * 0.5f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x14) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x14) = (n4 % 2) * 0.5f;
        done:
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x18) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x18) = 128.0f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x1C) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x1C) = 64.0f;
        }
    }
}

/* static helper the listing places at enemy.c lines 223-233, expanded only into
 * setEnemyObject; never emitted out of line, so it has no MAIN.MAP symbol and
 * this name is ours. */
static inline int enemyRandomizeID(int kind, int *ctr)
{
    int lo = randomEnemyKind[kind - 0x10000].first;
    int n = randomEnemyKind[kind - 0x10000].last - lo;
    int id = lo + *ctr;

    debug_StdPrintfDummy("\x1b[36mRANDOMIZE COUNT: %d > RID: %d\x1b[m\n", *ctr, id);
    *ctr = *ctr + 1;
    if (*ctr >= n) {
        *ctr = 0;
    }
    return randomEnemyVariationKind[id];
}

int setEnemyObject(GObj *self, int kind, int *ctr)
{
    struct DObjNode *p;
    Sub15C *sub;
    EnemyWork *w;
    float sc;
    int obj;
    int pid;

retry:
    sub = GOBJ_SUB(self);
    w = sub->work;
    if (kind > 0xFFFF) {
        kind = enemyRandomizeID(kind, ctr);
        goto retry;
    }
    p = sub->nodes;
    sc = D_00624880[kind].d;
    p->scale[2] = sc;
    p->scale[1] = sc;
    p->scale[0] = sc;
    w->scale = sc;
    obj = D_00624880[kind].a;
    if (obj != 0x610) {
        *(int *)&GOBJ_SUB(self)->model = GetPObjAddress(obj);
        GOBJ_SUB(self)->modelId = obj;
        debug_StdPrintfDummy("%p\n", GOBJ_SUB(self)->model);
        w->loaded = 1;
    }
    pid = D_00624880[kind].b;
    if (pid != -1) {
        setEnemyParticleObject(self, pid);
    }
    debug_StdPrintfDummy("\x1b[36mENEMY DESIGN ID: %d\x1b[m\n", kind);
    return kind;
}

typedef struct {
    int idx;
    int _4;
    int z;
    int _C;
} EnemyDispEntry;

/* dispEnemyObject sits on the January listing's lines (SRCFILE.TXT 295 to 373):
 * every row of code is at the listing's offset from the opening brace, and the
 * lines the listing shows without code hold declarations, braces and comments.
 * WHAT THE BYTES PIN: the first loop's condition reads the sub-object handle
 * through a volatile int view. The ROM keeps the body's own read of the handle
 * at the loop top (line 314, `lw $3,348($20)`, run on entry only because reorg
 * skips it on the back edge), which happens only when neither cse1 nor gcse
 * records the condition's read: cse's HASH and gcse's hash_expr_1 both refuse
 * a volatile MEM, so cse_around_loop finds nothing to copy into the top and PRE
 * finds no available computation to delete it with. The plain int view gives
 * the copy and a strict count of 12 (measured). The int view itself is the
 * file's own (GOBJ_SUB): it shares the idx store's alias set, which holds the
 * latch's read behind that store, so i++ issues first as in the ROM.
 * WHAT THEY CANNOT PIN: why the developer's accessor was volatile there, and
 * the text of the lines without code. */
void dispEnemyObject(void *self)
{
    float m[16];
    EnemyDispEntry *tmp;
    int i, j;
    int n = GOBJ_SUB(self)->skelNodeNum;
    char *tbl = *(char **)(*(char **)(self + 0x15C) + 0x8C);
    EnemyWork *w = GOBJ_SUB(self)->work;
    int *pl = w->particle;
    EnemyDispEntry buf[n];
    EnemyDispEntry *ptr[n];
    _SetCurrentMatrix((char *)GOBJ_SUB(self)->nodeMtx);
    _MulCurrentMatrixL(matrixptr + 0x100);

    _InitCurrentMatrix();

    /* clang-format off */
    for (i = 0; i < *(int *)(*(volatile int *)(self + 0x15C) + 0x88); i++) {
        /* project each part's origin: z goes into buf[i].z for the sort */
        ptr[i] = &buf[i];
        _SetCurrentMatrix((char *)GOBJ_SUB(self)->nodeMtx + i * 0x40);
        _MulCurrentMatrixL(matrixptr + 0x100);
        __asm__ __volatile__("lqc2 $vf8, 0x0(%0)\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                             "vdiv Q, $vf0w, $vf10w\n\t"
                             "vwaitq\n\t"
                             "vmulq.xyz $vf10, $vf10, Q\n\t"
                             "vftoi0.z $vf13, $vf10\n\t"
                             "sqc2 $vf13, 0x0(%1)"
                             :
                             : "r"(ZeroPoint), "r"(&buf[i])
                             : "memory");
        buf[i].idx = i;
    }

    /* sort far to near */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                if (ptr[j]->z > ptr[i]->z) {
                    tmp = ptr[j];
                    ptr[j] = ptr[i];
                    ptr[i] = tmp;
                }
            }
        }
    }
    sceVu0UnitMatrix(m);

    for (j = 0; j < n; j++) {
        /* draw the parts still alive, far to near */
        i = ptr[j]->idx;
        if ((w->broken)[i] != 0) continue;
        if ((w->flag)[i] == 0) continue;

        switch (*(int *)(tbl + i * 0x40 + 4)) {
        case 37:
            if (*(float *)((char *)GOBJ_SUB(self)->nodes + 0x30) == 0.0f)
                DispEnemyEye(w->eye0);
            break;
        case 36:
            if (*(float *)((char *)GOBJ_SUB(self)->nodes + 0x30) == 0.0f)
                DispEnemyEye(w->eye1);
            break;
        default:
            /* every other part is a particle */
            gif_StartPacketPri(6);
            gif_SetAlpha(1, 4, 128);
            gif_EndPacket();

            /* The particle is drawn in view space: m is the view matrix
               times the part's own matrix, the same product the first loop
               made on the current-matrix stack, rebuilt here because the
               stack no longer holds it. */

            sceVu0MulMatrix(m, matrixptr + 0x100, (char *)GOBJ_SUB(self)->nodeMtx + i * 0x40);
            prim_DispParticle(pl[i], m);
            break;
        }
    }
    /* clang-format on */
}

/* static helper the listing places at enemy.c lines 382-392, expanded into
 * EnemyCheckHit, enemySetParticleDie, EnemySetfDisappear and EnemyDeleteParticle;
 * never emitted out of line, so it has no MAIN.MAP symbol and this name is ours.
 * It returns SetParticleEffect's result: the discarded value register is what
 * EnemyCheckHit's allocation after the call shows (chain 2 pass 8). */
static inline int enemySetParticle(int kind, void *obj, float *dir)
{
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, dir[0], dir[1], -dir[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    return SetParticleEffect(kind, obj, buf);
}

int EnemyCheckHit(GObj *self, float *pos, float *dir)
{
    int eff = 0;
    Sub15C *sub;
    EnemyWork *w;
    int n;
    int i;
    int cnt;
    int flags;

    sub = self->dobj;
    w = sub->work;
    n = sub->skelNodeNum;
    cnt = 0;
    flags = 0;
    for (i = 0; i < n; i++) {
        if ((w->broken)[i] == 0) {
            if (distance_squared((char *)sub->nodeMtx + i * 64 + 0x30, pos) < 10000.0f) {
                enemySetParticle(8, (char *)sub->nodeMtx + i * 64 + 0x30, dir);
                /* The hand-written form the helper call replaced, the way
                   CheckEnemyHit still spells it, switched off by a local effect
                   switch, CheckEnemyHit's own `eff` with the other value.
                   WHAT THE BYTES PIN: a 4-byte stack object at sp+0x20 that
                   nothing reads, above the helper's freed 0x20 block and below
                   the pos/n/cnt spills; only promoted locals whose address is
                   taken after the call give it (put_var_into_stack runs when
                   the `&` is parsed, and q reuses the helper's block), and the
                   listing's lines 497-512 emit nothing.  WHAT THEY CANNOT PIN:
                   this text. */
                if (eff) {
                    float q[4];
                    short rx;
                    short ry;

                    MatrixDrive_GetTurnZAngleXY(&rx, &ry, dir[0], dir[1], -dir[2]);
                    SetIdentityQuaternion(q);
                    RotQuaternionX(q, -rx);
                    RotQuaternionY(q, -ry);
                    SetParticleEffect(8, (char *)sub->nodeMtx + i * 64 + 0x30, q);
                }
                flags |= 1;
                (w->broken)[i] = 1;
                cnt++;
                GetSkeltonFocusNode(self, 34);
                if (i == GetSkeltonFocusNode(self, 35)) {
                    (w->broken)[GetSkeltonFocusNode(self, 36)] = 1;
                    (w->broken)[GetSkeltonFocusNode(self, 37)] = 1;
                }
                if (cnt >= 4) {
                    break;
                }
            }
        }
    }
    return flags;
}

/* CheckEnemyHit sits on the January listing's lines (SRCFILE.TXT 531 to 572):
 * every row of code is at the listing's offset from the opening brace, and the
 * lines the listing shows without code hold declarations, braces and comments.
 * WHAT THE BYTES PIN: the counter starts at 0 in a statement of its own ahead of
 * a test on n alone, and the for has no initialiser. The ROM's blez is that
 * test and `move $9,$0` fills its delay slot; i is coloured after pos, the list
 * pointer and the entity pointer ($9), which only a first set of i that keeps
 * cse1's REG_EQUAL 0 through combine gives (update_equiv_regs doubles its live
 * length), and it keeps it only when nothing in its block reads i: gcse folds
 * the for's copied entry test from the `i = 0` and cse2 drops it under the
 * `n > 0` test. The listing prints the blez, its slot, the list load and the
 * latch on one line (548), so the test and the for share it. The particle
 * calls sit under a test of a local constant only gcse resolves: the store's
 * list reload after them is a PRE insertion at the end of the call block (line
 * 563), which needs the store's block to be a join when PRE runs.
 * WHAT THEY CANNOT PIN: how the test on n and the flag were spelled, and the
 * text of the lines without code. */
int CheckEnemyHit(GObj *self, float *pos, float *a, float *b)
{
    int eff = 1;
    Sub15C *sub = self->dobj;
    EnemyWork *w = sub->work;
    int i;
    int n = sub->skelNodeNum;

    if (2500.0f < distance_squared(pos, a)) {
        /* Walk the parts still alive and take the first one within reach
           of all three points: mark it hit, spawn the hit effect facing
           along a - pos, and report the hit.  The counter is cleared
           before the test on n, which shares its line with the for (see
           the comment above the function); the fence keeps that line, the
           braceless for and the condition below as the listing has them,
           one row of code per line. */
        /* clang-format off */
        i = 0;
        if (n > 0) for (; i < n; i++)
            if ((w->broken)[i] == 0) {
                if (distance_squared((char *)sub->nodeMtx + i * 64 + 0x30, pos) < 10000.0f &&
                    distance_squared((char *)sub->nodeMtx + i * 64 + 0x30, a) < 10000.0f &&
                    distance_squared((char *)sub->nodeMtx + i * 64 + 0x30, b) < 10000.0f) {
                    float q[4];
                    unsigned short ax, ay;
                    if (eff) {
                        MatrixDrive_GetTurnZAngleXY(&ax, &ay,
                                                    -(pos[0] - a[0]),
                                                    -(pos[1] - a[1]),
                                                    -(pos[2] - a[2]));
                        SetIdentityQuaternion(q);
                        RotQuaternionX(q, (short)-ax);
                        RotQuaternionY(q, (short)-ay);
                        SetParticleEffect(8, (char *)sub->nodeMtx + i * 64 + 0x30, q);
                    }

                    (w->broken)[i] = 1;

                    return 1;
                }
            }
    }
    return 0;
    /* clang-format on */
}

/* The 0x15C slot is the engine's sub-object HANDLE: the code stores an int and
 * reads it back as a pointer, so every read of it is a union view, the same
 * spelling ico2/sugipon/src/geometryManager.c uses for the same slot. */

#define SUBOF(o) (((SubHandle *)&((GObj *)(o))->dobj)->p)

/* the TU's one named .sdata object (after the two literals): the variation
   number the next enemy takes, stepped by two modulo ten */
static int enemyVariation = 0; /* derived name */

/* static helper the listing places at enemy.c lines 281-290, expanded only into
 * InitEnemyGeo; never emitted out of line, so it has no MAIN.MAP symbol and this
 * name is ours.  Its own body inlines the lines 99-100 clear loop. */
static inline int enemyInitPartsList(GObj *self, char *param)
{
    int kind = *(int *)(param + 0x30);
    EnemyWork *w;
    int n;
    int *parts;

    n = *(int *)(SUBOF(self) + 0x88);
    /* The work-record entry is chased as an int and cast: the ROM orders every
     * store of InitEnemyGeo's setup group ahead of this load, which only an int
     * view of the slot produces (evidence rung: ROM bytes). */
    w = (EnemyWork *)*(int *)(SUBOF(self) + 0x830);

    parts = (int *)iosMallocDebug(ios_partition_sugipon, n * 4, "src/enemy.c", 285);
    w->broken = parts;
    clearEnemyParticleFlags(parts, n);
    w->kind = kind;
    w->ctr = 0;
    return setEnemyObject(self, kind, &w->ctr);
}

void *InitEnemyGeo(GObj *self, char *param)
{
    EnemyWork *w;
    int kind;
    int no;

    w = iosMallocDebug(ios_partition_sugipon, 0x54, "src/enemy.c", 641);
    *(EnemyWork **)(SUBOF(self) + 0x830) = w;
    w->f_1C = 0;
    w->eye0 = InitEnemyEye(10, 0, 10);
    w->f_24 = 0;
    w->eye1 = InitEnemyEye(10, 0, 10);
    w->foot = InitEnemyFootPrint(6);
    w->f_2C = 1;
    w->particle = 0;
    w->loaded = 0;
    w->f_3C = 0.0f;
    w->f_40 = 0;
    w->wing = 0.0f;
    w->timer = 0;
    w->f_50 = 1.0f;
    kind = enemyInitPartsList(self, param);
    w->def = kind;
    w->f_50 = D_00624880[kind].c;
    InitMotionOrient(self, 0x84A, 0x967, 0x18, 0x24, 0x342);
    no = enemyVariation;
    *(int *)(SUBOF(self) + 0x558) = no;
    enemyVariation = (no + 2) % 10;
    *(int *)(SUBOF(self) + 0x550) = 0;
    SetLodLevel(self, 2);
    return w;
}

void EnemyGeo(GObj *self)
{
    int sub = (int)GOBJ_SUB(self);
    Act *node = GOBJ_ACT(self);
    unsigned long long flag = *(unsigned long long *)((char *)node + 0x18);
    EnemyWork *w = *(EnemyWork **)(sub + 0x830);
    float ratio;
    float buf[4];

    if ((int)(flag >> 33) & 1) {
        w->timer = 0;
    } else {
        if (w->timer >= 0xB)
            return;
        w->timer = w->timer + 1;
    }

    GOBJ_SUB(self)->catchBoy = 0;
    GOBJ_SUB(self)->word54C = 2;
    GOBJ_SUB(self)->word548 = 0;
    if (GetEnemyTypeFromGObj(self) == 3)
        GOBJ_SUB(self)->catchBoy = 1;

    ExecMotionOrient(self);

    CylinderCollisionWithControlDynamics(self, 4, 0, w->scale * 70.0f, w->scale * 50.0f, 0.5f);

    if (isEnemyActive((int *)self) != 0) {
        Sub15C *s = GOBJ_SUB(self);
        if (*(int *)((char *)s + 0x63C) != 0) {
            if (w->f_2C != 0) {
                if (!(s->motion == 0x3A1 || s->motion == 0x3A2)) {
                    GetProjectionOfPlane(buf, (float *)((char *)s + 0x1D0),
                                         (float *)(*(char **)((char *)s + 0xC) +
                                                   *(int *)((char *)s + 0x220) * 0x40 + 0x30));
                    EntryEnemyFootPrint(w->foot, buf);
                }
            }
        }
    }
    ExecEnemyFootPrints(w->foot);

    GOBJ_SUB(self)->word558 = (GOBJ_SUB(self)->word558 + 1) % 10;

    ratio = (*(float *)((char *)GOBJ_SUB(self)->nodes + 0x20) +
             *(float *)((char *)GOBJ_SUB(self)->nodes + 0x24) +
             *(float *)((char *)GOBJ_SUB(self)->nodes + 0x28)) /
            3.0f;

    _MulMatrix(MatrixDrive_GetMatrix(),
               (char *)GOBJ_SUB(self)->nodeMtx + GetSkeltonFocusNode(self, 0x24) * 0x40,
               (char *)offsetMatrix);
    UpdateEnemyEye(w->eye0, MatrixDrive_GetMatrix(), ratio);
    _MulMatrix(MatrixDrive_GetMatrix(),
               (char *)GOBJ_SUB(self)->nodeMtx + GetSkeltonFocusNode(self, 0x25) * 0x40,
               (char *)offsetMatrix);
    UpdateEnemyEye(w->eye1, MatrixDrive_GetMatrix(), ratio);
}

void DisplayEnemy(GObj *self)
{
    EnemyWork *w = GOBJ_SUB(self)->work;

    if (w->loaded != 0) {
        reg_DispEnemy((char *)GOBJ_SUB(self));
        if (*(float *)((char *)GOBJ_SUB(self)->nodes + 0x30) == 0.0f) {
            DispEnemyEye(w->eye0);
            DispEnemyEye(w->eye1);
        }
    }
    DispEnemyFootPrints(w->foot);
    if (w->particle != 0) {
        dispEnemyObject(self);
    }
}

/* kept local: act_a_p_1.h does not compile in this TU (too few arguments to function `IsActCharDead') */
extern int IsActCharDead();

void EnemyDL(int *self)
{
    Act *sub = GOBJ_ACT(self);
    unsigned long long flag = *(unsigned long long *)((char *)sub + 0x18);
    if (((flag >> 33) & 1) == 0)
        return;
    IsActCharDead();
    if (isEnemyHyde(self) != 0)
        return;
    DisplayEnemy((char *)self);
}

void DemoMotionGeo(GObj *self)
{
    GOBJ_SUB(self)->hand1Mode = 0;
    GOBJ_SUB(self)->hand0Mode = 0;
    GOBJ_SUB(self)->word3B8 = 0;
    GOBJ_SUB(self)->word3BC = 0;
    ExecMotionOrient(self);
}

void SetEnemyDissolve(GObj *self, float ratio)
{
    Sub15C *sub = GOBJ_SUB(self);

    sub->nodes->fade = ratio;
    if (sub->nodes->fade < 0.0f)
        sub->nodes->fade = 0.0f;
    if (sub->nodes->fade > 1.0f)
        sub->nodes->fade = 1.0f;
}

void SetEnemyFlyXZAccel(GObj *a0, float f)
{
    *(float *)((char *)GOBJ_SUB(a0)->work + 0x50) = f;
}

void SetEnemyFlyXZAccelAll(float accel)
{
    GObj *g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        *(float *)((char *)GOBJ_SUB(g)->work + 0x50) = accel;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}

float GetEnemyFlyXZAccel(GObj *a0)
{
    return *(float *)((char *)GOBJ_SUB(a0)->work + 0x50);
}

void EnemyAI(void) {}

void SetEnemyFootPrintSwitch(GObj *a0, int a1)
{
    *(int *)((char *)GOBJ_SUB(a0)->work + 0x2C) = a1;
}

void EnemySetfAppearAll(GObj *self)
{
    int n = GOBJ_SUB(self)->skelNodeNum;
    int i;

    for (i = 0; i < n; i++)
        ((int *)*(int *)(GOBJ_SUB(self)->work + 0x14))[i] = 0;
}

void EnemySetfDisappearAll(GObj *self)
{
    int n = GOBJ_SUB(self)->skelNodeNum;
    int i;

    for (i = 0; i < n; i++)
        ((int *)*(int *)(GOBJ_SUB(self)->work + 0x14))[i] = 1;
}

void EnemySetfDisappear(GObj *self, float *dir)
{
    Sub15C *sub = GOBJ_SUB(self);
    int n = sub->skelNodeNum;
    EnemyWork *w = sub->work;
    int i;

    for (i = 0; i < n; i++) {
        if ((w->broken)[i] == 0) {
            (w->broken)[i] = 1;
            enemySetParticle(8, *(char **)((char *)sub + 0xC) + i * 0x40 + 0x30, dir);
            return;
        }
    }
}

void enemySetParticleDie(void *a0, float *a1)
{
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    SetParticleEffect(0xC, a0, buf);
}

void ReviveEnemyParticle(GObj *a0, int a1)
{
    (*(int **)((char *)GOBJ_SUB(a0)->work + 0x14))[a1] = 0;
}

int isExistEnemyParticle(GObj *a0, int a1)
{
    return (*(int **)((char *)GOBJ_SUB(a0)->work + 0x14))[a1] == 0;
}

int EnemyGetNSafeParts(GObj *self)
{
    int n = GOBJ_SUB(self)->skelNodeNum;
    int *p;
    int i;
    int cnt = 0;

    for (i = 0; i < n; i++) {
        p = *(int **)((char *)GOBJ_SUB(self)->work + 0x14);
        if (p[i] == 0)
            cnt++;
    }
    return cnt;
}

void EnemyDeleteParticle(GObj *self, float *dir, short *list)
{
    Sub15C *sub = self->dobj;
    int i;
    int n;

    n = 2;
    for (i = 0; list[i] >= 0 && n > 0; i++, n--) {
        enemySetParticle(8, *(char **)((char *)sub + 0xC) + list[i] * 0x40 + 0x30, dir);
    }
}

void SetEnemyHitGeometryAction(GObj *a0, int a1)
{
    *(int *)((char *)GOBJ_SUB(a0)->work + 0x38) = a1;
}

int InitDemoMotionGeo(GObj *self)
{
    InitMotionOrient(self, 0x84A, 0x967, -1, -1, 0x3D7);
    SetLodLevel(self, 0);
    *(int *)(((char *)self) + 0x16C) = 0;
    return 0;
}

void HotInitDemoMotionGeo(GObj *self)
{
    InitMotionOrient(self, 0x84A, 0x967, -1, -1, 0x3D7);
    SetLodLevel(self, 0);
    *(int *)(((char *)self) + 0x16C) = 0;
}

int GetEnemyHitNodeFlag(GObj *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work + 0x14);
}

int RandomizeEnemy(GObj *self)
{
    Sub15C *sub = GOBJ_SUB(self);
    EnemyWork *w = sub->work;
    int kind = w->kind;

    *(int *)(*(char **)((char *)sub + 0x870) + 0x30) = 0;
    return setEnemyObject(self, kind, &w->ctr);
}

void SetEnemyWingRatio(GObj *a0, float f)
{
    ((EnemyWork *)GOBJ_SUB(a0)->work)->wing = f;
}

int CanThisEnemyFly(GObj *a0)
{
    return D_00624880[((EnemyWork *)GOBJ_SUB(a0)->work)->def].flyType;
}

int GetEnemyBattleType(GObj *a0)
{
    return D_00624880[((EnemyWork *)GOBJ_SUB(a0)->work)->def].battleType;
}

float GetEnemyDefLife(GObj *a0)
{
    return D_00624880[((EnemyWork *)GOBJ_SUB(a0)->work)->def].life;
}

float GetEnemyDefDodgeRange(GObj *a0)
{
    return D_00624880[((EnemyWork *)GOBJ_SUB(a0)->work)->def].dodge;
}

float GetEnemyDefParaIndex(GObj *a0)
{
    return D_00624880[((EnemyWork *)GOBJ_SUB(a0)->work)->def].paraIndex;
}

void ResetEnemyPositionInfo(GObj *self)
{
    EnemyWork *w = GOBJ_SUB(self)->work;

    ResetEnemyEye(w->eye0);
    ResetEnemyEye(w->eye1);
    GOBJ_SUB(self)->word514 =
        (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 0.0f);
}

void SetEnemyStonizedVisual(GObj *self)
{
    int local[8];
    GetRootPosition(local, self);
    GetRootQuaternion(&local[4], self);
    SetParticleEffect(0x31, local, &local[4]);
    self->active = 0;
}
