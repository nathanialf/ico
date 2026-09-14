#include "common.h"

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void *D_0063A61C;
extern void actChangeActMain(void *a0, void *a1, void **a2);
extern void actCreateSubThread(void *entry, int prio);
extern void actCreateMotionThread(void *a0, void *a1, void **a2);

/* One mail-table row: the message id the actor listens for and the three
   entry points it starts. 429 (0x1AD) terminates a table. */
typedef struct MailRec {
    unsigned short id; /* 0x00 */
    char _p2[0x2];
    void *main;   /* 0x04 */
    void *motion; /* 0x08 */
    void *sub;    /* 0x0C */
} MailRec;

/* The GObj's pending-mail box at +0x54: a count and a run of 8-byte slots. */
typedef struct MailEntry {
    int key; /* 0x00 */
    int val; /* 0x04 */
} MailEntry;

typedef struct MailBox {
    int _p0;           /* 0x54 */
    int count;         /* 0x58 */
    MailEntry list[1]; /* 0x5C */
} MailBox;

typedef struct ActState {
    char _p0[0x4];
    void *mainThread;   /* 0x04 */
    void *motionThread; /* 0x08 */
    char _pC[0xC4];
    MailRec *listB; /* 0xD0 */
    MailRec *listA; /* 0xD4 */
    int lastKey;    /* 0xD8 */
} ActState;

void BeforeFunc2(char *self)
{
    ActState *act = *(ActState **)(self + 0x164);

    if (act != 0) {
        /* declared HERE, not before the guard: ROM keeps `self` live across the
           list init (it copies the parameter to $v0 and reuses $a0 as a temp) */
        MailBox *mb = (MailBox *)(self + 0x54);
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
                for (j = 0; j < mb->count; j++) {
                    if (mb->list[j].key == p->id) {
                        goto found;
                    }
                }
                p++;
            }
        }
        mb->count = 0;
        return;

    found:
        act->lastKey = mb->list[j].key;
        mb->count = 0;
        if (p->main != 0) {
            actChangeActMain(D_0063A61C, p->main, &act->mainThread);
        }
        if (p->sub != 0) {
            actCreateSubThread(p->sub, 20);
        }
        if (p->motion != 0) {
            actCreateMotionThread(p->motion, (void *)21, &act->motionThread);
        }
    }
}

void actDummy(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}
