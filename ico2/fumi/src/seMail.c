#include "debug.h"
#include "gobj.h"
#include "act-game.h"
#include "geometryManager.h"
#include <libvu0.h>
#include "main.h"

void setMailTarget(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_StdPrintfDummy("seMail: gobj buff over\n");
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}

/* One 60-byte sound-mail record: the mail id, an optional per-target filter,
   and a flag word whose low nibble selects the target set. */
typedef struct SeRec {
    char pad0[40];
    int mail;                                              /* 0x28 */
    int (*check)(int target, int self, struct SeRec *rec); /* 0x2C */
    char pad30[4];
    unsigned short x34; /* 0x34 */
    char pad36[2];
    unsigned int flags; /* 0x38 */
} SeRec;

extern SeRec seDef[];
void setMailTarget(int a0, int *a1, int *a2);

void seMail(int self, int id)
{
    SeRec *rec = &seDef[id];
    int flags = rec->flags & 0xF;
    int targets[16];
    int n = 0;
    int i;
    int o;
    int r;

    if (flags != 0) {
        if (rec->flags & 8) {
            if (self != boyGObj) {
                flags |= 1;
            }
            if (self != girlGObj) {
                flags |= 2;
            }
            flags |= ~3;
        }
        if (flags & 1) {
            setMailTarget(boyGObj, targets, &n);
        }
        if (flags & 2) {
            setMailTarget(girlGObj, targets, &n);
        }
        if (flags & 4) {
            o = isysGObjSearchFromObjKindID_begin(4);
            while (o != 0) {
                if ((flags & 8) == 0 || o != self) {
                    setMailTarget(o, targets, &n);
                }
                o = isysGObjSearchFromObjKindID_next(o);
            }
        }
        for (i = 0; i < n; i++) {
            if (rec->check != 0) {
                r = rec->check(targets[i], self, rec);
            } else {
                r = 1;
            }
            if (r != 0) {
                ACTGame_SendSoundMail((char *)targets[i], rec->mail, self, rec->x34,
                                      (rec->flags >> 9) & 1);
            }
        }
    }
}

int seMailTargetDistCheck(void *a0, void *a1, void *a2)
{
    float buf0[4];
    float buf1[4];
    float buf2[4];
    float threshold;
    threshold = (float)(*(int *)((char *)a2 + 0x30) * *(int *)((char *)a2 + 0x30));
    if (a0 == 0 || a1 == 0) {
        return 0;
    }
    GetRootPosition(buf0, a0);
    GetRootPosition(buf1, a1);
    sceVu0SubVector(buf2, buf0, buf1);
    if (sceVu0InnerProduct(buf2, buf2) < threshold) {
        return 1;
    }
    return 0;
}
