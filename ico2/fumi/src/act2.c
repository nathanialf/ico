#include "act.h"
#include "act2.h"
#include "isys.h"

/* One mail-table row: the message id the actor listens for and the three
   entry points it starts. 429 terminates a table. */
typedef struct MailRec { /* field names derived */
    unsigned short id;   /* 0x00 */
    char pad2[2];
    void *main;   /* 0x04 */
    void *motion; /* 0x08 */
    void *sub;    /* 0x0C */
} MailRec;        /* derived name */

typedef struct ActState { /* field names derived */
    char pad0[4];
    void *mainThread;   /* 0x04 */
    void *motionThread; /* 0x08 */
    char padC[196];
    MailRec *listB; /* 0xD0 */
    MailRec *listA; /* 0xD4 */
    int lastKey;    /* 0xD8 */
} ActState;         /* derived name */

void BeforeFunc2(GObj *self)
{
    ActState *act = (ActState *)self->act;

    if (act != 0) {
        /* the mail box and the three lists to walk, the last a -1 terminator */
        IosMailBox *mb = &self->mailBox;
        MailRec *lists[3] = {act->listA, act->listB, (MailRec *)-1};
        MailRec *p;
        int i;
        int j;

        for (i = 0; lists[i] != (MailRec *)-1; i++) {
            p = lists[i];
            if (p == 0) {
                continue;
            }
            while (p->id != 429) {
                for (j = 0; j < mb->num; j++) {
                    if (mb->mail[j].type == p->id) {
                        goto found;
                    }
                }
                p++;
            }
        }
        mb->num = 0;
        return;

    found:
        act->lastKey = mb->mail[j].type;
        mb->num = 0;
        if (p->main != 0) {
            actChangeActMain(isysCurrentGObj, p->main, &act->mainThread);
        }
        if (p->sub != 0) {
            actCreateSubThread(p->sub, 20);
        }
        if (p->motion != 0) {
            actCreateMotionThread(p->motion, 21, &act->motionThread);
        }
    }
}

void actDummy(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
}
