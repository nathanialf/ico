#include "common.h"
#include "gobj.h"
#include "obj_manager.h"

/* objact.h prototypes: their order is the inline tail's emission order */
void ObjAction_CorrectGeo(int a0, int a1);
void ObjAction_Mail(void *a0, int a1);
void ObjAction_MailCenter(void *a0, int a1);
void ObjAction_Init(void);
/* kept local: this TU's uses of BeforeFunc2 do not fit the prototype in act2.h */
extern void BeforeFunc2();

typedef struct {
    char pad[0x34];
    int x34;
    char pad2[0x4C - 0x38];
} OaRecA;

typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
} OaRecB;

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

inline void ObjAction_Init(void)
{
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

inline void ObjAction_CorrectGeo(int a0, int a1)
{
    OaRecB *p;
    if (a0 < 0)
        return;
    p = objActionRecord(a0);
    if (p == 0)
        return;
    objActionCorrectFlag(p);
    objActionCorrectMode(p);
}

inline void ObjAction_Mail(void *a0, int a1)
{
    void *p = isysGObjGetExist_begin();
    while (p != 0) {
        iosOmSendMail(p, a1, a0);
        p = isysGObjGetExist_next(p);
    }
}

typedef struct {
    int id;
    int idx;
} ObjActMailEnt;

/* objact.o's whole .rodata run, in definition order: the mail ids
   ObjAction_MailCenter sends, and the object-id to index table it walks. */
static const int objActMailId[12] = {-1, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 0};

static const ObjActMailEnt objActMailTable[33] = {
    {2074, 1}, {2482, 1}, {117, 2},  {145, 1},  {1711, 1}, {1712, 2}, {1797, 1},
    {1798, 2}, {366, 1},  {367, 2},  {368, 3},  {937, 2},  {3347, 2}, {3634, 2},
    {1979, 1}, {1980, 2}, {2037, 1}, {2038, 2}, {524, 1},  {525, 2},  {981, 1},
    {982, 2},  {983, 3},  {1625, 3}, {1292, 1}, {1571, 1}, {1126, 1}, {1207, 1},
    {1208, 2}, {1410, 1}, {1491, 1}, {1492, 2}, {3173, 1}};

inline void ObjAction_MailCenter(void *a0, int a1)
{
    int i;
    ObjActMailEnt *e;
    int n;

    for (i = 0; i < 33; i++) {
        e = &objActMailTable[i];
        if (((int *)a0)[2] != e->id)
            continue;
        n = e->idx;
        if (a1 > 0) {
            if (n < 5)
                continue;
            n += a1;
        }
        ObjAction_Mail(a0, objActMailId[n]);
    }
}

void ObjectBeforeFunc(int a0, int a1, int a2, int a3)
{
    BeforeFunc2(a0, a1, a2, a3);
}
