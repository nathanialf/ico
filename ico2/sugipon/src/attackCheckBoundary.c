#include "debug.h"
#include "sceneManager.h"
#include "memory.h"
#include "act.h"
#include "boyact.h"
#include "mail-add-data.h"
#include "Matrix.h"
#include "Primitive.h"
#include "frameDependSequence.h"
#include "matrixDrive.h"
#include "weapon.h"
#include <libvu0.h>

/* the TU's whole .data (MAIN.MAP attackCheckBoundary.o .data 0x10, no symbol):
   the colour the debug display draws a boundary sphere in */
static unsigned int acbSphereColor[4] = {0, 128, 255, 128}; /* derived name */

#include "attackCheckBoundary.h"
#include "ios.h"
#include "main.h"
#include "GifPacket.h"

static inline char *createAttackCheckBoundaryGObj(SObjSimpleSetting *lay)
{
    return CreateLayoutedGObj(63, 0x4B, -1, 0, lay, -1, 7, 1);
}

/* The 12-byte work record this function allocates and the other members
   reach through the sub-object's 0x830: 0x4 is the hit flag AttackCheckBoundaryDL
   tests and the manager reads back and clears, 0x8 the attribute SetAttackCheckBoundaryAttribute stores, and 0x0
   the caller's int that CreateAttackCheckBoundary passed in the layout's
   handle, cleared again through it here. */
typedef struct {
    int *handle; /* 0x0 */
    int hit;     /* 0x4 */
    int attr;    /* 0x8 */
} AcbWork;

inline int InitAttackCheckBoundaryGeo(int unused, void *obj)
{
    AcbWork *w = (AcbWork *)iosMallocDebug(ios_partition_sugipon, 0xC, __FILE__, 27);

    w->handle = (int *)((SObjSimpleSetting *)obj)->obj;
    w->hit = 0;
    *w->handle = 0;
    w->attr = 0;
    return (int)w;
}

inline void AttackCheckBoundaryGeo(void *a0)
{
    int *a = *(int **)((char *)a0 + 0x15C);
    int *b = *(int **)a;
    if (b == 0)
        return;
    if (*(int *)((char *)b + 0x16C) == 0) {
        *(int *)((char *)a0 + 0x16C) = 0;
    }
}

inline void AttackCheckBoundaryDL(GObj *obj)
{
    AcbWork *m = GOBJ_SUB(obj)->work;
    float r;

    if (debug_skel_flag == 0) {
        return;
    }
    /* The drawing is the body of this if (listing line 57 is its brace), so the
       if's join label and the early return's label both follow gif_EndPacket:
       its block does not fall straight into the exit block, and sibcall.c keeps
       the jal and the frame the ROM has. */
    if (m->hit == 0) {
        gif_StartPacketPri(0xB);

        gif_SetZTest(1);
        gif_SetAlpha(1, 5, 0x80);
        _UnitMatrix(MatrixDrive_GetMatrix());
        CopyVector(MatrixDrive_GetMatrix()[3], (char *)GOBJ_SUB(obj)->nodeMtx + 0x30);
        r = GetAttackCheckBoundaryRadius(obj);
        prim_DispWireSphere(r, acbSphereColor, 4, 4);
        gif_EndPacket();
    }
}

inline void SetAttackCheckBoundaryAttribute(char *a0, int a1)
{
    /* listing lines 62 and 63: the work pointer is its own statement, and
       the sub-object chase is int-typed (the engine's int handle), so the
       attribute store kills it and the manager's owner store at line 218
       reloads 0x15C */
    AcbWork *w = GOBJ_SUB(a0)->work;
    w->attr = a1;
}

inline float GetAttackCheckBoundaryRadius(GObj *a0)
{
    return *(float *)((char *)GOBJ_SUB(a0)->nodes + 0x20);
}

inline char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r)
{
    SObjSimpleSetting lay = InitialSObjSimpleSetting;

    lay.pos[0] = x;
    lay.pos[1] = y;
    lay.pos[2] = z;
    lay.scale[0] = r;
    lay.obj = (int)obj;
    *obj = 0;
    return createAttackCheckBoundaryGObj(&lay);
}

inline void actAttackCheckBoundaryStart(GObj *self)
{
    Act *p = actInitialize(self);

    actInitialize_ext_charcter(self);
    _ACTWait(1);
    p->flags18.ll |= 1LL << 32;
}

/* mail-add-data.c defines this returning int; declaring it void costs the
   $v1 allocation of the reloaded state pointer in the mail block below. */

void AttackCheckBoundaryBeforeFunc(char *self)
{
    int *mgr = (int *)(self + 0x54);
    int *e = (int *)(self + 0x5C);
    int i;

    for (i = 0; i < mgr[1]; i++, e += 2) {
        if (e[0] == 13) {
            if (*(char **)&e[1] == boyGObj) {
                AcbWork *b = GOBJ_SUB(self)->work;
                void *g = GetBoyWeaponGObj();

                if (g != 0) {
                    int k = CheckWeaponKind(g);

                    if (k == 4 || k == 5 || k == 6 || k == 9 || k == 8) {
                        if (*b->handle < 2) {
                            GOBJ_SUB(g)->ctrl.wallAttr = b->attr;
                            ExecuteSEPackage(g, 74);
                            b->hit = 2;
                            *b->handle = 2;
                            /* " - cut by the sword" */
                            debug_StdPrintfDummy(" - 剣で切られた\n");
                        }
                        goto done;
                    }
                }
                if (*b->handle <= 0) {
                    ActSendMail_WithAdditionalData(boyGObj, 209, self, &b->attr);
                    b->hit = 1;
                    *b->handle = 1;
                    /* " - cannot cut" */
                    debug_StdPrintfDummy(" - きれない\n");
                }
            }
        done:
            {
                Act *q = GOBJ_ACT(self);

                q->attacker = 0;
                q->hit = 0;
            }
        }
    }
    mgr[1] = 0;
}

/* the manager's 8-byte roster entries and its work block at sub+0x830 */
typedef struct AcbEntry {
    int obj; /* 0x00 */
    int hit; /* 0x04 */
} AcbEntry;

typedef struct AcbMgr {
    int count;      /* 0x00 */
    int cur;        /* 0x04 */
    int prev;       /* 0x08 */
    AcbEntry *list; /* 0x0C */
} AcbMgr;

/* attackCheckBoundary.o's own 8-byte .sdata (MAIN.MAP line 7305, unnamed
   there): the blank roster entry each slot starts from */
static AcbEntry acbBlankEntry = {0, 0}; /* derived name */

AcbMgr *InitAttackCheckBoundaryManagerGeo(int a0, SObjSimpleSetting *a1)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float p[4];
    AcbMgr *mgr;
    const LayoutClothDef *rec;
    float len;
    int i;
    char *g;

    rec = &layoutClothDef[a1->obj];
    mgr = (AcbMgr *)iosMallocDebug(ios_partition_sugipon, 0x10, __FILE__, 180);
    mgr->prev = mgr->cur;
    mgr->cur = 0;
    mgr->count = rec->count;
    mgr->list = (AcbEntry *)iosMallocDebug(ios_partition_sugipon, mgr->count * 8, __FILE__, 189);
    v0[0] = rec->pt[0][0];
    v0[1] = -rec->pt[0][1];
    v0[2] = rec->pt[0][2];
    v0[3] = 1.0f;
    v1[0] = rec->pt[1][0];
    v1[1] = -rec->pt[1][1];
    v1[2] = rec->pt[1][2];
    v1[3] = 1.0f;
    _SubVector(v2, v1, v0);
    _ScaleVector(v2, v2, 0.5f / (float)mgr->count);
    _AddVectorXYZ(v0, v0, v2);
    _SubVectorXYZ(v1, v1, v2);
    len = VectorLength(v2);
    for (i = 0; i < mgr->count; i++) {
        _InterVector(p, v1, v0, (float)i / (float)(mgr->count - 1));
        mgr->list[i] = acbBlankEntry;
        g = CreateAttackCheckBoundary(&mgr->cur, p[0], p[1], p[2], len);
        mgr->list[i].obj = (int)g;
        SetAttackCheckBoundaryAttribute(g, rec->attr);
        /* the sub-object's first word is its owner (AttackCheckBoundaryGeo
           reads it as an int pointer); an int-typed store would hold the
           loop test's count reload behind it and lose the delay slot */
        *(int **)*(int *)(g + 0x15C) = (int *)a0;
    }
    return mgr;
}

void AttackCheckBoundaryManagerGeo(GObj *self)
{
    AcbMgr *m = GOBJ_SUB(self)->work;
    int i;

    for (i = 0; i < m->count; i++) {
        char *e = (char *)m->list[i].obj;

        /* int-typed chase (types.h GOBJ_SUB): the int store below may-alias the
           chase, so ROM reloads 0x15C/0x830 for the second access */
        m->list[i].hit = *(int *)(*(int *)((char *)GOBJ_SUB(e) + 0x830) + 4);
        *(int *)(*(int *)((char *)GOBJ_SUB(e) + 0x830) + 4) = 0;
        *(int *)(e + 0x16C) = 1;
    }
    m->prev = m->cur;
    m->cur = 0;
}

void AttackCheckBoundaryManagerDL(void) {}

inline int GetAttackCheckBoundaryManagerStatus(GObj *a0)
{
    AcbMgr *m = GOBJ_SUB(a0)->work;

    return m->prev;
}
