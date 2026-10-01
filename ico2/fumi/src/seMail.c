#include "debug.h"
#include "gobj.h"
#include "act-game.h"
#include "geometryManager.h"
#include <libvu0.h>
#include "main.h"
#include "s_init.h"

void setMailTarget(GObj *a0, GObj **a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_StdPrintfDummy("seMail: gobj buff over\n");
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}

/* kept local: s_init.c reads the table as bytes */
extern SeDef seDef[];

void seMail(GObj *self, int id)
{
    SeDef *rec = &seDef[id];
    int flags = rec->flags & 0xF;
    GObj *targets[16];
    int n = 0;
    int i;
    void *o;
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
                ACTGame_SendSoundMail(targets[i], rec->mail, self, rec->mailArg,
                                      (rec->flags >> 9) & 1);
            }
        }
    }
}

int seMailTargetDistCheck(void *a0, void *a1, SeDef *rec)
{
    float buf0[4];
    float buf1[4];
    float buf2[4];
    float threshold;
    threshold = (float)(rec->range * rec->range);
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
