#include "common.h"
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

extern int D_0063A438;

/* .data, carved VMA 0x4E5A90..0x4E5AA0; bytes verified against baserom/pal/baseelf.rom */
unsigned int D_004E5A90[4] = {
    0x00000000,
    0x00000080,
    0x000000FF,
    0x00000080,
};

extern int D_0063B148;
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int a0);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);

/* What the bytes pin (InitAttackCheckBoundaryManagerGeo's copy of the
   template, listing lines 85 to 91): an 8-aligned record, since the 0x40-byte
   copy is eight ld/sd pairs; position members that are plain float arrays,
   since a union member's stores alias the int store `*obj = 0` and keep it
   behind them where the ROM issues it first; and an int handle at 0x30,
   whose store must conflict with `*obj = 0` so that sched1 keeps the two in
   source order, which is what issues the 0x30 chunk of the copy first. What
   they cannot pin: the vector type's name (sceVu0FVECTOR is the SDK's). */
typedef struct {
    sceVu0FVECTOR pos;   /* 0x00 */
    sceVu0FVECTOR rot;   /* 0x10 */
    sceVu0FVECTOR scale; /* 0x20 */
    int obj;             /* 0x30 */
    int unk34[3];        /* 0x34 */
} AcbLayout;

extern AcbLayout D_004E45C0;

#include "attackCheckBoundary.h"

static inline char *createAttackCheckBoundaryGObj(AcbLayout *lay)
{
    return CreateLayoutedGObj(63, 0x4B, -1, 0, lay, -1, 7, 1);
}

inline int InitAttackCheckBoundaryGeo(int unused, void *obj)
{
    int buf = iosMallocDebug(D_0063A438, 0xC, __FILE__, 27);
    int *p = *((int **)(((char *)obj) + 0x30));
    int new_var4;
    int *new_var2;
    int *new_var3;
    int new_var;
    new_var2 = p;
    do {
        new_var4 = (int)p;
        ;
    } while (0);
    *((int *)(buf + 4)) = 0;
    new_var3 = (int *)buf;
    *new_var2 = 0;
    *new_var3 = new_var4;
    *((int *)(buf + 8)) = 0;
    return buf;
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

inline void AttackCheckBoundaryDL(char *obj)
{
    char *m = *(char **)(*(char **)(obj + 0x15C) + 0x830);
    float r;

    if (D_0063B148 == 0) {
        return;
    }
    if (*(int *)(m + 4) != 0) {
        return;
    }
    gif_StartPacketPri(0xB);

    gif_SetZTest(1);
    gif_SetAlpha(1, 5, 0x80);
    _UnitMatrix(MatrixDrive_GetMatrix());
    CopyVector((char *)MatrixDrive_GetMatrix() + 0x30,
               *(char **)(*(char **)(obj + 0x15C) + 0xC) + 0x30);
    r = GetAttackCheckBoundaryRadius(obj);
    prim_DispWireSphere(r, D_004E5A90, 4, 4);
    do {
        gif_EndPacket();
    } while (0);
}

inline void SetAttackCheckBoundaryAttribute(char *a0, int a1)
{
    /* listing lines 62 and 63: the work pointer is its own statement, and
       the sub-object chase is int-typed (the engine's int handle), so the
       attribute store kills it and the manager's owner store at line 218
       reloads 0x15C */
    char *w = (char *)*(int *)(*(int *)(a0 + 0x15C) + 0x830);
    *(int *)(w + 8) = a1;
}

inline float GetAttackCheckBoundaryRadius(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x870) + 0x20);
}

inline char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r)
{
    AcbLayout lay = D_004E45C0;

    lay.pos[0] = x;
    lay.pos[1] = y;
    lay.pos[2] = z;
    lay.scale[0] = r;
    lay.obj = (int)obj;
    *obj = 0;
    return createAttackCheckBoundaryGObj(&lay);
}

inline void actAttackCheckBoundaryStart(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

extern char *D_00639EA4;

/* mail-add-data.c defines this returning int; declaring it void costs the
   $v1 allocation of the reloaded state pointer in the mail block below. */

void AttackCheckBoundaryBeforeFunc(char *self)
{
    int *mgr = (int *)(self + 0x54);
    int *e = (int *)(self + 0x5C);
    int i;

    for (i = 0; i < mgr[1]; i++, e += 2) {
        if (e[0] == 13) {
            if (*(char **)&e[1] == D_00639EA4) {
                int *b = *(int **)(*(char **)(self + 0x15C) + 0x830);
                void *g = GetBoyWeaponGObj();

                if (g != 0) {
                    int k = CheckWeaponKind(g);

                    if (k == 4 || k == 5 || k == 6 || k == 9 || k == 8) {
                        if (*(int *)b[0] < 2) {
                            *(int *)(*(char **)((char *)g + 0x15C) + 0x5F4) = b[2];
                            ExecuteSEPackage(g, 74);
                            b[1] = 2;
                            *(int *)b[0] = 2;
                            /* " - cut by the sword" */
                            debug_StdPrintfDummy(" - 剣で切られた\n");
                        }
                        goto done;
                    }
                }
                if (*(int *)b[0] <= 0) {
                    ActSendMail_WithAdditionalData(D_00639EA4, 209, self, &b[2]);
                    b[1] = 1;
                    *(int *)b[0] = 1;
                    /* " - cannot cut" */
                    debug_StdPrintfDummy(" - きれない\n");
                }
            }
        done:
            {
                char *q = *(char **)(self + 0x164);

                q[0x1DA] = *(int *)(q + 0x1B0) = 0;
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

/* RECONSTRUCTION: the attribute word of a cloth layout record has a type of
   its own. The ROM's schedule of InitAttackCheckBoundaryManagerGeo loads
   rec->attr (line 61) above the roster store `mgr->list[i].obj = g` (line
   214), while that store must still precede the first sub-object chase
   (line 62) and the attribute store must force the second chase (line 218)
   to reload; with the roster handle and both chases int (the engine's
   int-handle reading, GOBJ_SUB), only an attribute load outside int's alias
   set is free to rise (the compiler's sched2 dump gives int set 2 and this
   enum its own set). Only the type is attested: the table holds 96 and 128
   here and the developers' enumerator names are not recoverable. */
typedef enum { CLOTH_ATTR_NONE = 0 } ClothAttr;

/* RECONSTRUCTION: one record of layoutClothDef (MAIN.MAP line 6655, member
   layout-cloth-def.o, .rodata; the retail table is 36 records, 0xEA0 bytes).
   The name string and the four corner points are the table's own bytes; this
   TU reads the first two corners, the attribute and the boundary count, and
   InitFlagGeo reads the rest. */
typedef struct {
    char name[32];  /* 0x00 */
    float pt[4][3]; /* 0x20 */
    int f_50;       /* 0x50 */
    ClothAttr attr; /* 0x54 */
    int f_58;       /* 0x58 */
    int count;      /* 0x5C, the boundaries a manager lays out */
    float f_60;     /* 0x60 */
    float f_64;     /* 0x64 */
} LayoutClothDef;

extern const LayoutClothDef layoutClothDef[];
/* attackCheckBoundary.o's own 8-byte .sdata (MAIN.MAP line 7305, unnamed
   there): the blank roster entry each slot starts from */
extern AcbEntry D_0063B730;

AcbMgr *InitAttackCheckBoundaryManagerGeo(int a0, char *a1)
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

    rec = &layoutClothDef[*(int *)(a1 + 0x30)];
    mgr = (AcbMgr *)iosMallocDebug(D_0063A438, 0x10, __FILE__, 180);
    mgr->prev = mgr->cur;
    mgr->cur = 0;
    mgr->count = rec->count;
    mgr->list = (AcbEntry *)iosMallocDebug(D_0063A438, mgr->count * 8, __FILE__, 189);
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
        mgr->list[i] = D_0063B730;
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

void AttackCheckBoundaryManagerGeo(char *self)
{
    AcbMgr *m = *(AcbMgr **)(*(char **)(self + 0x15C) + 0x830);
    int i;

    for (i = 0; i < m->count; i++) {
        char *e = (char *)m->list[i].obj;

        /* int-typed chase (types.h GOBJ_SUB): the int store below may-alias the
           chase, so ROM reloads 0x15C/0x830 for the second access */
        m->list[i].hit = *(int *)(*(int *)(*(int *)(e + 0x15C) + 0x830) + 4);
        *(int *)(*(int *)(*(int *)(e + 0x15C) + 0x830) + 4) = 0;
        *(int *)(e + 0x16C) = 1;
    }
    m->prev = m->cur;
    m->cur = 0;
}

void AttackCheckBoundaryManagerDL(void) {}

inline int GetAttackCheckBoundaryManagerStatus(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
}
