#include "gobj.h"
#include "obj_manager.h"
#include "objact.h"
#include "typedef.h"
#include "act2.h"
#include "gamesys.h"
#include "include_asm.h"

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

static inline void objActionCorrectFlag(OaRecB *p) /* derived name */
{
    if ((p->flags & 1) == 1u) {
        p->mode = 972;
    }
}

static inline void objActionCorrectMode(OaRecB *p) /* derived name */
{
    if (p->mode == 972) {
        p->mode = p->baseMode;
    }
}

void ObjectBeforeFunc(GObj *self)
{
    BeforeFunc2(self);
}

INCLUDE_ASM(ObjAction_CorrectGeo);

INCLUDE_ASM(ObjAction_Mail);

INCLUDE_ASM(ObjAction_MailCenter);

INCLUDE_ASM(ObjAction_Init);

INCLUDE_ASM(func_0023D8A0);
