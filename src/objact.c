#include "common.h"

/* objact.h prototypes: their order is the inline tail's emission order */
void ObjAction_CorrectGeo(int a0, int a1);
void ObjAction_Mail(void *a0, int a1);
void ObjAction_MailCenter(void *a0, int a1);
void ObjAction_Init(void);

extern void BeforeFunc2();
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *a0);

typedef struct { char pad[0x34]; int x34; char pad2[0x4C - 0x38]; } OaRecA;
typedef struct { int x0; int x4; int x8; int xC; int x10; } OaRecB;
extern OaRecA D_002C2DC8[];
extern OaRecB D_002BC6E0[];

/* listing lines 30-34: the object's action record, or none */
static inline OaRecB *objActionRecord(int a0)
{
    int e = D_002C2DC8[a0].x34;
    if (e != 0) {
        return &D_002BC6E0[e];
    }
    return 0;
}

inline void ObjAction_Init(void) {
    int *p = (int *)isysGObjGetExist_begin();
    while (p != 0) {
        ObjAction_CorrectGeo(p[2], 0);
        p = (int *)isysGObjGetExist_next(p);
    }
}

/* listing lines 50-51 and 56-57 */
static inline void objActionCorrectFlag(OaRecB *p)
{
    if ((p->x10 & 1) == 1u) {
        p->xC = 0x3CC;
    }
}

static inline void objActionCorrectMode(OaRecB *p)
{
    if (p->xC == 0x3CC) {
        p->xC = p->x0;
    }
}

inline void ObjAction_CorrectGeo(int a0, int a1) {
    OaRecB *p;
    if (a0 < 0) return;
    p = objActionRecord(a0);
    if (p == 0) return;
    objActionCorrectFlag(p);
    objActionCorrectMode(p);
}

inline void ObjAction_Mail(void *a0, int a1) {
    void *p = isysGObjGetExist_begin();
    while (p != 0) {
        iosOmSendMail(p, a1, a0);
        p = isysGObjGetExist_next(p);
    }
}

typedef struct { int id; int idx; } ObjActMailEnt;
extern ObjActMailEnt D_00629D38[];
extern int D_00629D08[];

inline void ObjAction_MailCenter(void *a0, int a1)
{
    int i;
    ObjActMailEnt *e;
    int n;

    for (i = 0; i < 33; i++) {
        e = &D_00629D38[i];
        if (((int *)a0)[2] != e->id) continue;
        n = e->idx;
        if (a1 > 0) {
            if (n < 5) continue;
            n += a1;
        }
        ObjAction_Mail(a0, D_00629D08[n]);
    }
}

void ObjectBeforeFunc(int a0, int a1, int a2, int a3)
{
    BeforeFunc2(a0, a1, a2, a3);
}
