#include "gobj.h"
#include "obj_manager.h"
#include "objact.h"
#include "typedef.h"
#include "act2.h"

extern OaRecA objLayout[];
extern OaRecB D_002BC6E0[];

/* the object's action record, or none */
static inline OaRecB *objActionRecord(int a0) /* derived name */
{
    int e = objLayout[a0].x34;
    if (e != 0) {
        return &D_002BC6E0[e];
    }
    return 0;
}

inline void ObjAction_Init(void)
{
    GObj *p = isysGObjGetExist_begin();
    while (p != 0) {
        ObjAction_CorrectGeo(p->f_8, 0);
        p = isysGObjGetExist_next(p);
    }
}

static inline void objActionCorrectFlag(OaRecB *p) /* derived name */
{
    if ((p->x10 & 1) == 1u) {
        p->xC = 972;
    }
}

static inline void objActionCorrectMode(OaRecB *p)
{
    if (p->xC == 972) {
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

inline void ObjAction_MailCenter(void *a0, int a1)
{
    int i;
    ObjActMailEnt *e;
    int n;

    for (i = 0; i < 33; i++) {
        e = &objTrigger[i];
        if (((int *)a0)[2] != e->id)
            continue;
        n = e->idx;
        if (a1 > 0) {
            if (n < 5)
                continue;
            n += a1;
        }
        ObjAction_Mail(a0, objTriggerDef[n]);
    }
}

void ObjectBeforeFunc(char *self)
{
    BeforeFunc2(self);
}
