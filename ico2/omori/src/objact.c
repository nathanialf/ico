#include "gobj.h"
#include "obj_manager.h"
#include "objact.h"
#include "typedef.h"
#include "act2.h"
#include "gamesys.h"

/* the data-only member obj-action.o, read as typedef.h's OaRecB rows; no
   header declares it */
extern OaRecB objAction[];

/* the object's action record, or none */
static inline OaRecB *objActionRecord(int label) /* derived name */
{
    int e = objLayout[label].action;
    if (e != 0) {
        return &objAction[e];
    }
    return 0;
}

inline void ObjAction_Init(void)
{
    GObj *p = isysGObjGetExist_begin();
    while (p != 0) {
        ObjAction_CorrectGeo(p->labelId, 0);
        p = isysGObjGetExist_next(p);
    }
}

static inline void objActionCorrectFlag(OaRecB *p) /* derived name */
{
    if ((p->flags & 1) == 1u) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        p->mode = 949;
#else
#ifdef VERSION_NTSC
        p->mode = 815;
#else
#ifdef VERSION_AUG6
        p->mode = 814;
#else
#ifdef VERSION_JUN26
        p->mode = 763;
#else
        p->mode = 972;
#endif
#endif
#endif
#endif
    }
}

#ifdef VERSION_NTSC
static inline void objActionCorrectMode(OaRecB *p) /* derived name */
{
    if (p->mode == 815) {
        p->mode = p->baseMode;
    }
}
#else
static inline void objActionCorrectMode(OaRecB *p) /* derived name */
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    if (p->mode == 949) {
#else
#ifdef VERSION_AUG6
    if (p->mode == 814) {
#else
#ifdef VERSION_JUN26
    if (p->mode == 763) {
#else
    if (p->mode == 972) {
#endif
#endif
#endif
        p->mode = p->baseMode;
    }
}
#endif

inline void ObjAction_CorrectGeo(int label, int unused)
{
    OaRecB *p;
    if (label < 0)
        return;
    p = objActionRecord(label);
    if (p == 0)
        return;
    objActionCorrectFlag(p);
    objActionCorrectMode(p);
}

inline void ObjAction_Mail(void *data, int mail)
{
    void *p = isysGObjGetExist_begin();
    while (p != 0) {
        iosOmSendMail(p, mail, data);
        p = isysGObjGetExist_next(p);
    }
}

#ifdef VERSION_NTSC
inline void ObjAction_MailCenter(GObj *gobj, int step)
{
    int i;
    const ObjActMailEnt *e;
    int n;

    for (i = 0; i < 31; i++) {
        e = &objTrigger[i];
        if (gobj->labelId != e->labelId)
            continue;
        n = e->triggerNo;
        if (step > 0) {
            if (n < 5)
                continue;
            n += step;
        }
        ObjAction_Mail(gobj, objTriggerDef[n]);
    }
}
#else
inline void ObjAction_MailCenter(GObj *gobj, int step)
{
    int i;
    const ObjActMailEnt *e;
    int n;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    for (i = 0; i < 31; i++) {
#else
    for (i = 0; i < 33; i++) {
#endif
        e = &objTrigger[i];
        if (gobj->labelId != e->labelId)
            continue;
        n = e->triggerNo;
        if (step > 0) {
            if (n < 5)
                continue;
            n += step;
        }
        ObjAction_Mail(gobj, objTriggerDef[n]);
    }
}
#endif

void ObjectBeforeFunc(GObj *self)
{
    BeforeFunc2(self);
}
