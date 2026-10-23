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

static inline unsigned char chkOrient(char *s, float *dir, float *w, float deg) /* derived name */
{
    float *q = (float *)(s + 0x4A0);

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
    float v[4];
    float u[4];
    float p[4];
    GObj *o;
    Act *s = GOBJ_ACT(self);

    v[0] = test_CURRENTROOT(self)[0];
    v[1] = test_CURRENTROOT(self)[1];
    v[2] = test_CURRENTROOT(self)[2];

    s->wish2.ll |= 1ULL << 36;
    s->wish2.ll |= 1ULL << 35;

    s->wish3.ll |= 1ULL << 56;

    if ((s->pad.now & 0x20) || GOBJ_WORK(self)->stickMag < 0.9) {
        s->wish3.ll |= 1ULL << 57;
    }
    s->wish3.ll |= 1ULL << 54;
    s->wish3.ll |= 1ULL << 55;

    s->wish3.ll |= 1ULL << 53;

    s->wish3.ll |= 1ULL << 47;
    s->wish3.ll |= 1ULL << 48;
    s->wish3.ll |= 1ULL << 49;
    s->wish3.ll |= 1ULL << 60;
    s->wish3.ll |= 1ULL << 61;
    s->wish4.ll |= 2;
    s->wish4.ll |= 4;
    s->wish2.ll |= 1ULL << 54;
    s->wish2.ll |= 1ULL << 57;
    s->wish2.ll |= 1ULL << 58;
    s->wish2.ll |= 1ULL << 59;
    s->wish2.ll |= 1ULL << 60;

    s->wish3.ll |= 0x8000000;

    s->wish3.ll |= 1;

    s->wish3.ll |= 0x10;
    s->wish3.ll |= 0x20;
    s->wish3.ll |= 0x40;
    s->wish3.ll |= 0x80;
    s->wish3.ll |= 0x100;
    s->wish3.ll |= 0x200;
    s->wish3.ll |= 0x400;
    s->wish4.ll |= 0x10;

    s->wish3.ll |= 1ULL << 50;
    s->wish3.ll |= 1ULL << 51;
    s->wish3.ll |= 1ULL << 52;
    s->wish2.ll |= 1ULL << 55;
    s->wish2.ll |= 1ULL << 56;

    s->wish3.ll |= 0x20000;
    s->wish3.ll |= 0x80000;
    s->wish3.ll |= 0x40000;

    s->wish3.ll |= 1ULL << 42;
    s->wish3.ll |= 1ULL << 43;
    s->wish3.ll |= 4;

    switch ((unsigned int)s->actMode) {
    case 1:
        if (s->modeFrame >= 181) {
            s->wish2.ll |= 1ULL << 37;
        }
        break;
    case 4:
    case 5:
    case 18:
    case 62:
        s->wish3.ll |= 1ULL << 39;
        s->wish3.ll |= 1ULL << 38;
        s->wish3.ll |= 1ULL << 40;
        s->wish3.ll |= 1ULL << 41;
        s->wish3.ll |= 1ULL << 44;
        s->wish3.ll |= 1ULL << 45;
        s->wish3.ll |= 1ULL << 46;
        break;
    case 13:
        s->wish2.ll |= 1ULL << 51;
        break;
    }

    if (s->wish1.ll & 0x18000) {
        if (self == boyGObj) {
            if (chkOrient((char *)s, dir, u, 80.0f)) {
                s->wish3.ll |= 0x8000;
                if (s->pad.trg & 0x10) {
                    s->wish3.ll |= 0x10000;
                }
            }
        } else {
            s->wish3.ll |= 0x8000;
        }
    }

    if (((int)(s->wish1.ll >> 11) & 1) && chkOrient((char *)s, dir, u, 80.0f)) {
        s->wish3.ll |= 0x800;
    }

    if (((int)(s->wish0.ll >> 62) & 1) && (s->pad.trg & 0x10)) {
        s->wish2.ll |= 1ULL << 62;
    }

    if (((int)(s->wish0.ll >> 32) & 1) && chkOrient((char *)s, dir, u, 80.0f)) {
        if (self == boyGObj) {
            if (s->pad.trg & 0x10) {
                s->wish3.ll |= 0x1000;

                s->wish3.ll |= 2;
            }
        } else {
            s->wish3.ll |= 0x1000;
            s->wish3.ll |= 0x100000;
            s->wish3.ll |= 0x200000;
            s->wish3.ll |= 0x400000;
            if (self == girlGObj && (s->flags20.ll & 0xC000) == 0xC000) {
                s->wish3.ll &= ~0x1000;
            }
        }
    }

    if (((int)(s->wish1.ll >> 13) & 1) && chkOrient((char *)s, dir, u, 80.0f)) {
        s->wish3.ll |= 0x2000;
    }

    s->wish3.ll |= 1ULL << 59;

    if (((int)(s->wish1.ll >> 58) & 1) && chkOrient((char *)s, dir, u, 60.0f)) {
        s->wish3.ll |= 1ULL << 58;
    }

    if (0.1f < s->stick.mag || ((int)(s->flags18.ll >> 57) & 1)) {
        s->wish2.ll |= 1ULL << 33;
        s->wish2.ll |= 1ULL << 34;
    }

    if (s->pad.trg & 0x10) {
        s->wish2.ll |= 1ULL << 38;
        if (0.1f < s->stick.mag) {
            s->wish2.ll |= 1ULL << 39;

            s->wish2.ll |= 1ULL << 40;
            GOBJ_WORK(self)->padWish[0] = dir[0];
            GOBJ_WORK(self)->padWish[1] = dir[1];
            GOBJ_WORK(self)->padWish[2] = dir[2];
        }
        s->wish2.ll |= 1ULL << 41;
    }

    if (s->pad.trg & 0x80) {
        /* both arms set the same bit */
        if (self->kind == 1) {
            s->wish2.ll |= 1ULL << 42;
        } else {
            s->wish2.ll |= 1ULL << 42;
        }

        if (0.1f < s->stick.mag) {
            s->wish2.ll |= 1ULL << 43;
        }
    }

    if ((60 - systemStatus[0] * 10) / systemStatus[1] / 4 < s->flags20.w.handFreeFrame &&
        (s->pad.now & 8)) {
        s->flags18.ll |= 1ULL << 38;
    }

    if (s->pad.now & 8) {
        if (GOBJ_SUB(self)->ctrl.motion == 184) {
            GOBJ_WORK(self)->noInterpTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 6;
        }
        if (GOBJ_WORK(self)->wishHoldTimer == 0) {
            GOBJ_WORK(self)->wishHoldTimer =
                (60 - systemStatus[0] * 10) / systemStatus[1] * 80 / 60;
        }
        s->wish2.ll |= 1ULL << 44;
        s->wish3.ll |= 1ULL << 62;
        s->wish3.ll |= 1ULL << 63;
        s->wish4.ll |= 1;
        s->wish2.ll |= 1ULL << 61;
        s->wish2.ll |= 1ULL << 63;
        s->wish2.ll |= 1ULL << 53;
        s->wish4.ll |= 8;
    }

    if (GOBJ_WORK(self)->wishHoldTimer != 0) {
        s->wish2.ll |= 1ULL << 44;
    }

    if (s->pad.trg & 8) {
        s->wish2.ll |= 1ULL << 45;
    }

    if (s->pad.now & 0x20) {
        s->wish3.ll |= 1ULL << 29;
        s->wish3.ll |= 1ULL << 30;
        s->wish3.ll |= 1ULL << 31;
        s->wish3.ll |= 1ULL << 32;
        s->wish3.ll |= 1ULL << 33;
        s->wish3.ll |= 1ULL << 34;
        s->wish3.ll |= 1ULL << 35;
    }

    if (s->pad.trg & 0x20) {
        s->wish3.ll |= 1ULL << 37;
    }

    if (s->pad.now & 0x20) {
        ACTSearchGObj(self, 19, 45, (int *)&o, u, 100.0f);

        if (o != 0 && CheckCarryableItem(o)) {
            p[0] = test_CURRENTROOT(o)[0];
            p[1] = test_CURRENTROOT(o)[1];
            p[2] = test_CURRENTROOT(o)[2];
            if (p[1] > v[1] &&
                (float)(p[1] - v[1] < 0.0f ? -(p[1] - v[1]) : (p[1] - v[1])) < 60.0f) {
                s->nextItem.i = (int)o;
                s->wish3.ll |= 1ULL << 36;
            }
        }
        s->wish2.ll |= 1ULL << 51;
        s->wish2.ll |= 1ULL << 52;
    }

    if ((s->pad.trg & 0x10) ||
        (0.1f < s->stick.mag && (s->stick.angle >= -45 && s->stick.angle <= 45))) {
        s->wish3.ll |= 8;
    }

    if (0.1f < s->stick.mag) {
        s->wish2.ll |= 1ULL << 46;
    }

    if (self == boyGObj) {
        if (s->pad.trg & 0x40) {
            if (0.1f < s->stick.mag && (s->stick.angle >= -45 && s->stick.angle <= 45)) {
                s->wish2.ll |= 1ULL << 47;
            } else if (0.1f < s->stick.mag && (s->stick.angle >= 46 && s->stick.angle <= 134)) {
                s->wish2.ll |= 1ULL << 49;
            } else if (0.1f < s->stick.mag && s->stick.angle >= -134 && s->stick.angle <= -46) {
                s->wish2.ll |= 1ULL << 50;
            }
            s->wish2.ll |= 1ULL << 48;
        }
    }

    if (s->pad.trg & 0x20) {
        s->wish3.ll |= 0x10000000;
        s->wish3.ll |= 0x4000000;
    }

    if ((int)(s->wish3.ll >> 30) & 1) {
        if ((int)(s->wish1.ll >> 30) & 1) {
            *(int *)((char *)GOBJ_ACT(self)->enemy + 0x2C0) = 1;
        }
    } else {
        *(int *)((char *)GOBJ_ACT(self)->enemy + 0x2C0) = 0;
    }
}
