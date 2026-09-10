#include "common.h"

extern char D_0061EEC8[];
extern int D_0063A438;
extern int iosMallocDebug(int handle, int size, char *file, int line);

/* .data — carved VMA 0x4E5A90..0x4E5AA0; bytes verified against baserom/pal/baseelf.rom */
unsigned int D_004E5A90[4] = {
    0x00000000,
    0x00000080,
    0x000000FF,
    0x00000080,
};

extern int D_0063B148;
extern void CopyVector(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_StartPacketPri(int a0);
extern void prim_DispWireSphere(void *a0, int a1, int a2, float a3);
extern void _ACTWait();
extern int actInitialize();
extern void actInitialize_ext_charcter();

typedef union {
    float f[4];
    long long ll[2];
} AcbVec;

typedef struct {
    AcbVec pos;   /* 0x00 */
    AcbVec rot;   /* 0x10 */
    AcbVec scale; /* 0x20 */
    int *obj;     /* 0x30 */
    int unk34[3]; /* 0x34 */
} AcbLayout;

extern AcbLayout D_004E45C0;
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
/* prototypes: their order is the inline tail's emission order */
int InitAttackCheckBoundaryGeo(int unused, void *obj);
void AttackCheckBoundaryGeo(void *a0);
void AttackCheckBoundaryDL(char *obj);
void actAttackCheckBoundaryStart(int *self);
float GetAttackCheckBoundaryRadius(char *a0);
char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r);
int GetAttackCheckBoundaryManagerStatus(char *a0);
void SetAttackCheckBoundaryAttribute(char *a0, int a1);

static inline char *createAttackCheckBoundaryGObj(AcbLayout *lay)
{
    return CreateLayoutedGObj(0x3F, 0x4B, -1, 0, lay, -1, 7, 1);
}

inline int InitAttackCheckBoundaryGeo(int unused, void *obj)
{
    int buf = iosMallocDebug(D_0063A438, 0xC, D_0061EEC8, 0x1B);
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
    prim_DispWireSphere(D_004E5A90, 4, 4, r);
    do {
        gif_EndPacket();
    } while (0);
}

inline void SetAttackCheckBoundaryAttribute(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) = a1;
}

inline float GetAttackCheckBoundaryRadius(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x870) + 0x20);
}

inline char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r)
{
    AcbLayout lay = D_004E45C0;

    lay.pos.f[0] = x;
    lay.pos.f[1] = y;
    lay.pos.f[2] = z;
    lay.scale.f[0] = r;
    lay.obj = obj;
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
extern char D_0061EEE8[];
extern char D_0061EF00[];
extern void *GetBoyWeaponGObj(void);
extern int CheckWeaponKind(void *w);
extern void ExecuteSEPackage(void *a0, int a1);
/* mail-add-data.c defines this returning int; declaring it void costs the
   $v1 allocation of the reloaded state pointer in the mail block below. */
extern int ActSendMail_WithAdditionalData(char *to, int mail, char *from, void *data);
extern void debug_StdPrintfDummy(char *fmt, ...);

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
                            debug_StdPrintfDummy(D_0061EEE8);
                        }
                        goto done;
                    }
                }
                if (*(int *)b[0] <= 0) {
                    ActSendMail_WithAdditionalData(D_00639EA4, 209, self, &b[2]);
                    b[1] = 1;
                    *(int *)b[0] = 1;
                    debug_StdPrintfDummy(D_0061EF00);
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

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", InitAttackCheckBoundaryManagerGeo);

/* the manager's 8-byte roster entries and its work block at sub+0x830 */
typedef struct AcbEntry {
    char *obj; /* 0x00 */
    int hit;   /* 0x04 */
} AcbEntry;

typedef struct AcbMgr {
    int count;      /* 0x00 */
    int cur;        /* 0x04 */
    int prev;       /* 0x08 */
    AcbEntry *list; /* 0x0C */
} AcbMgr;

void AttackCheckBoundaryManagerGeo(char *self)
{
    AcbMgr *m = *(AcbMgr **)(*(char **)(self + 0x15C) + 0x830);
    int i;

    for (i = 0; i < m->count; i++) {
        char *e = m->list[i].obj;

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
