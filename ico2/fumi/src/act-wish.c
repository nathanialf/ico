#include "typedef.h"
#include "debug.h"
#include "commonact.h"
#include "gv.h"
#include "item.h"
#include <libvu0.h>
#include "act-wish.h"
#include "act-game.h"
#include "boyact.h"
#include "main.h"

static inline unsigned char chkOrient(char *s, float *dir, float deg) /* derived name */
{
    float *q = (float *)(s + 0x4A0);
    float w[4];

    if (q[0] == 0.0f && q[1] == 0.0f && q[2] == 0.0f && q[3] == 0.0f) {
        debug_StdPrintfDummy("orient null");
        return 0;
    }
    sceVu0ScaleVector(w, q, -1.0f);
    if ((float)(_RotyGV(dir, w) < 0 ? -_RotyGV(dir, w) : _RotyGV(dir, w)) < deg) {
        return 1;
    }
    return 0;
}

void ACTGetWish_FromPad(GObj *self, float *dir)
{
    Act *s = GOBJ_ACT(self);

    s->wish2.ll |= 0x10;
    s->wish2.ll |= 8;

    s->wish3.ll |= 0x80000;
    s->wish3.ll |= 0x40000;
    s->wish3.ll |= 0x20000;

    s->wish3.ll |= 0x1000;
    s->wish3.ll |= 0x2000;
    s->wish3.ll |= 0x400000;
    s->wish3.ll |= 0x800000;
    s->wish3.ll |= 0x8000000;
    s->wish3.ll |= 0x10000000;
    s->wish3.ll |= 0x40000000;
    s->wish2.ll |= 0x400000;
    s->wish2.ll |= 0x2000000;
    s->wish2.ll |= 0x4000000;
    s->wish2.ll |= 0x8000000;

    s->wish2.ll |= 1ULL << 56;

    s->wish2.ll |= 0x40000000;

    s->wish2.ll |= 1ULL << 34;
    s->wish2.ll |= 1ULL << 35;
    s->wish2.ll |= 1ULL << 36;
    s->wish2.ll |= 1ULL << 37;
    s->wish2.ll |= 1ULL << 38;
    s->wish2.ll |= 1ULL << 39;

    s->wish3.ll |= 0x4000;
    s->wish3.ll |= 0x8000;
    s->wish3.ll |= 0x10000;
    s->wish2.ll |= 0x800000;
    s->wish2.ll |= 0x1000000;

    s->wish2.ll |= 1ULL << 46;
    s->wish2.ll |= 1ULL << 48;
    s->wish2.ll |= 1ULL << 47;

    s->wish3.ll |= 0x80;
    s->wish3.ll |= 0x100;
    s->wish2.ll |= 1ULL << 32;

    switch ((unsigned int)s->actMode) {
    case 1:
        if (s->modeFrame >= 181) {
            s->wish2.ll |= 0x20;
        }
        break;
    case 4:
    case 5:
    case 18:
    case 62:
        s->wish3.ll |= 0x10;
        s->wish3.ll |= 8;
        s->wish3.ll |= 0x20;
        s->wish3.ll |= 0x40;
        s->wish3.ll |= 0x200;
        s->wish3.ll |= 0x400;
        s->wish3.ll |= 0x800;
        break;
    case 13:
        s->wish2.ll |= 0x80000;
        break;
    }

    if ((s->wish1.ll & 0x3000) && chkOrient((char *)s, dir, 80.0f)) {
        if (self == boyGObj) {
            s->wish2.ll |= 1ULL << 44;
            if (s->pad.trg & 0x10) {
                s->wish2.ll |= 1ULL << 45;
            }
        } else {
            s->wish2.ll |= 1ULL << 44;
        }
    }

    if (((int)(s->wish1.ll >> 8) & 1) && chkOrient((char *)s, dir, 80.0f)) {
        s->wish2.ll |= 1ULL << 40;
    }

    if (((int)(s->wish0.ll >> 61) & 1) && (s->pad.trg & 0x10)) {
        s->wish2.ll |= 0x20000000;
    }

    if (((int)(s->wish0.ll >> 32) & 1) && chkOrient((char *)s, dir, 80.0f)) {
        if (self == boyGObj) {
            if (s->pad.trg & 0x10) {
                s->wish2.ll |= 1ULL << 41;

                s->wish2.ll |= 0x80000000;
            }
        } else {
            s->wish2.ll |= 1ULL << 41;
            s->wish2.ll |= 1ULL << 49;
            s->wish2.ll |= 1ULL << 50;
            s->wish2.ll |= 1ULL << 51;
        }
    }

    if (((int)(s->wish1.ll >> 10) & 1) && chkOrient((char *)s, dir, 80.0f)) {
        s->wish2.ll |= 1ULL << 42;
    }

    s->wish3.ll |= 0x200000;

    if (((int)(s->wish1.ll >> 52) & 1) && chkOrient((char *)s, dir, 60.0f)) {
        s->wish3.ll |= 0x100000;
    }

    if (0.1f < s->stick.mag || ((int)(s->flags18.ll >> 56) & 1)) {
        s->wish2.ll |= 2;
        s->wish2.ll |= 4;
    }

    if (s->pad.trg & 0x10) {
        s->wish2.ll |= 0x40;
        if (0.1f < s->stick.mag) {
            s->wish2.ll |= 0x80;

            s->wish2.ll |= 0x100;
            GOBJ_WORK(self)->padWish[0] = dir[0];
            GOBJ_WORK(self)->padWish[1] = dir[1];
            GOBJ_WORK(self)->padWish[2] = dir[2];
        }
        s->wish2.ll |= 0x200;
    }

    if (s->pad.trg & 0x80) {
        /* both arms set the same bit */
        if (self->kind == 1) {
            s->wish2.ll |= 0x400;
        } else {
            s->wish2.ll |= 0x400;
        }

        if (0.1f < s->stick.mag) {
            s->wish2.ll |= 0x800;
        }
    }

    if ((60 - systemStatus[0] * 10) / systemStatus[1] / 4 < s->flags20.w.handFreeFrame &&
        (s->pad.now & 8)) {
        s->flags18.ll |= 1ULL << 37;
    }

    if (s->pad.now & 8) {
        s->wish2.ll |= 0x1000;
        s->wish3.ll |= 0x1000000;
        s->wish3.ll |= 0x2000000;
        s->wish3.ll |= 0x4000000;
        s->wish2.ll |= 0x10000000;
        s->wish2.ll |= 0x200000;
        s->wish3.ll |= 0x20000000;
    }

    if (s->pad.trg & 8) {
        s->wish2.ll |= 0x2000;
    }

    if (s->pad.now & 0x20) {
        s->wish2.ll |= 1ULL << 58;
        s->wish2.ll |= 1ULL << 59;
        s->wish2.ll |= 1ULL << 60;
        s->wish2.ll |= 1ULL << 61;
        s->wish2.ll |= 1ULL << 62;
        s->wish2.ll |= 1ULL << 63;
        s->wish3.ll |= 1;
    }

    if (s->pad.trg & 0x20) {
        s->wish3.ll |= 4;
    }

    if (s->pad.now & 0x20) {
        float u[4];
        GObj *o;

        ACTSearchGObj(self, 19, 45, (int *)&o, u, 100.0f);

        if (o != 0 && CheckCarryableItem(o)) {
            s->nextItem.i = (int)o;
            s->wish3.ll |= 2;
        }
        s->wish2.ll |= 0x80000;
        s->wish2.ll |= 0x100000;
    }

    if ((s->pad.trg & 0x10) ||
        (0.1f < s->stick.mag && (s->stick.angle >= -45 && s->stick.angle <= 45))) {
        s->wish2.ll |= 1ULL << 33;
    }

    if (0.1f < s->stick.mag) {
        s->wish2.ll |= 0x4000;
    }

    if (self == boyGObj) {
        if (s->pad.trg & 0x40) {
            if (0.1f < s->stick.mag && (s->stick.angle >= -45 && s->stick.angle <= 45)) {
                s->wish2.ll |= 0x8000;
            } else if (0.1f < s->stick.mag && (s->stick.angle >= 46 && s->stick.angle <= 134)) {
                s->wish2.ll |= 0x20000;
            } else if (0.1f < s->stick.mag && s->stick.angle >= -134 && s->stick.angle <= -46) {
                s->wish2.ll |= 0x40000;
            }
            s->wish2.ll |= 0x10000;
        }
    }

    if (s->pad.trg & 0x20) {
        s->wish2.ll |= 1ULL << 57;
        s->wish2.ll |= 1ULL << 55;
    }

    if ((int)(s->wish2.ll >> 59) & 1) {
        if ((int)(s->wish1.ll >> 27) & 1) {
            *(int *)((char *)GOBJ_ACT(self)->enemy + 0x2C0) = 1;
        }
    } else {
        *(int *)((char *)GOBJ_ACT(self)->enemy + 0x2C0) = 0;
    }
}
