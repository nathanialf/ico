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

static inline unsigned char chkOrient(char *s, float *dir, float *w, float deg)
{
    float *q = (float *)(s + 0x4B0);

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

void ACTGetWish_FromPad(char *a0, float *a1)
{
    float v[4];
    float u[4];
    float p[4];
    char *o;
    Act *s = GOBJ_ACT(a0);
    float deg;

    v[0] = test_CURRENTROOT(a0)[0];
    v[1] = test_CURRENTROOT(a0)[1];
    v[2] = test_CURRENTROOT(a0)[2];

    s->wish2.ll |= 1ULL << 37;
    s->wish2.ll |= 1ULL << 36;
    s->wish2.ll |= 1ULL << 33;

    s->wish4.ll |= 2;

    if ((s->f_2E0 & 0x20) || GOBJ_WORK(a0)->f_340 < 0.9) {
        s->wish4.ll |= 4;
    }
    s->wish3.ll |= 1ULL << 63;
    s->wish4.ll |= 1;

    s->wish3.ll |= 1ULL << 62;

    s->wish3.ll |= 1ULL << 55;
    s->wish3.ll |= 1ULL << 56;
    s->wish3.ll |= 1ULL << 57;
    s->wish3.ll |= 1ULL << 58;
    s->wish4.ll |= 0x20;
    s->wish4.ll |= 0x40;
    s->wish4.ll |= 0x400;
    s->wish4.ll |= 0x800;
    s->wish4.ll |= 0x1000;
    s->wish2.ll |= 1ULL << 59;
    s->wish2.ll |= 1ULL << 62;
    s->wish2.ll |= 1ULL << 63;
    s->wish3.ll |= 1;
    s->wish3.ll |= 2;

    s->wish3.ll |= 1ULL << 34;

    if (a0 == boyGObj) {
        if (0.1f < s->f_34C && ((int)(s->wish1.ll >> 5) & 1) &&
            chkOrient((char *)s, a1, u, 80.0f)) {
            if (!(s->f_2E0 & 8) || girlGObj == 0 || GOBJ_WORK(girlGObj)->f_3A0 == 0) {
                s->wish3.ll |= 0x20;
            }
        }
    } else {
        s->wish3.ll |= 0x20;
    }

    s->wish3.ll |= 0x800;
    s->wish3.ll |= 0x1000;
    s->wish3.ll |= 0x2000;
    s->wish3.ll |= 0x4000;
    s->wish3.ll |= 0x8000;
    s->wish3.ll |= 0x10000;
    s->wish3.ll |= 0x20000;
    s->wish4.ll |= 0x4000;

    s->wish3.ll |= 1ULL << 59;
    s->wish3.ll |= 1ULL << 60;
    s->wish3.ll |= 1ULL << 61;
    s->wish2.ll |= 1ULL << 60;
    s->wish2.ll |= 1ULL << 61;

    s->wish3.ll |= 0x1000000;
    s->wish3.ll |= 0x4000000;
    s->wish3.ll |= 0x2000000;

    s->wish3.ll |= 1ULL << 50;
    s->wish3.ll |= 1ULL << 51;
    s->wish3.ll |= 1ULL << 49;
    s->wish3.ll |= 0x80;
    if (0.1f < s->f_34C && (s->f_340 >= -45 && s->f_340 <= 45)) {
        s->wish3.ll |= 0x200;
        s->wish3.ll |= 0x100;
    }

    switch ((unsigned int)s->unk34) {
    case 1:
        if (s->f_4C >= 181) {
            s->wish2.ll |= 1ULL << 38;
        }
        break;
    case 4:
    case 5:
    case 18:
    case 62:
        s->wish3.ll |= 1ULL << 46;
        s->wish3.ll |= 1ULL << 45;
        s->wish3.ll |= 1ULL << 47;
        s->wish3.ll |= 1ULL << 48;
        s->wish3.ll |= 1ULL << 52;
        s->wish3.ll |= 1ULL << 53;
        s->wish3.ll |= 1ULL << 54;
        break;
    case 13:
        s->wish2.ll |= 1ULL << 54;
        break;
    }

    if (s->wish1.ll & 0xC00000) {
        if (a0 == boyGObj) {
            if (chkOrient((char *)s, a1, u, 80.0f)) {
                s->wish3.ll |= 0x400000;
                if (s->f_2E0 & 0x10) {
                    s->wish3.ll |= 0x800000;
                }
            }
        } else {
            s->wish3.ll |= 0x400000;
        }
    }

    if (((int)(s->wish1.ll >> 18) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        s->wish3.ll |= 0x40000;
    }

    if (((int)(s->wish1.ll >> 3) & 1) && (s->f_2E0 & 0x10) && chkOrient((char *)s, a1, u, 90.0f)) {
        s->wish3.ll |= 8;
    }

    if (((int)(s->wish0.ll >> 32) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        if (a0 == boyGObj) {
            if (s->f_2E0 & 0x10) {
                s->wish3.ll |= 0x80000;

                s->wish3.ll |= 0x40;
            }
        } else {
            s->wish3.ll |= 0x80000;
            s->wish3.ll |= 0x8000000;
            s->wish3.ll |= 0x10000000;
            s->wish3.ll |= 0x20000000;
            if (a0 == girlGObj && girlControlMode == 0 &&
                (s->flags20.ll & (0xC000ULL << 23)) == (0xC000ULL << 23)) {
                s->wish3.ll &= ~0x80000;
            }
        }
    }

    if (((int)(s->wish1.ll >> 20) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        s->wish3.ll |= 0x100000;
    }

    if (a0 == girlGObj && girlControlMode != 0) {
        if (!(s->f_2E0 & 0x10)) {
            s->wish3.ll &= ~0x80000;
            s->wish3.ll &= ~0x100000;
        }
    }

    s->wish4.ll |= 0x10;

    if (((int)(s->wish2.ll >> 3) & 1) && chkOrient((char *)s, a1, u, 60.0f)) {
        s->wish4.ll |= 8;
    }

    if (0.1f < s->f_34C || ((int)(s->flags20.ll >> 3) & 1)) {
        s->wish2.ll |= 1ULL << 34;
        s->wish2.ll |= 1ULL << 35;
    }

    if (s->unk2E4 & 0x10) {
        s->wish2.ll |= 1ULL << 39;
        if (0.1f < s->f_34C) {
            s->wish2.ll |= 1ULL << 40;

            s->wish2.ll |= 1ULL << 41;
            GOBJ_WORK(a0)->f_350 = a1[0];
            GOBJ_WORK(a0)->f_354 = a1[1];
            GOBJ_WORK(a0)->f_358 = a1[2];
        }
        s->wish2.ll |= 1ULL << 42;
        s->wish2.ll |= 1ULL << 43;
    }

    if (s->unk2E4 & 0x80) {
        /* Both arms set the same bit; gcc cross-jumps them and drops the
           branch, leaving the compare'(char *)s two operands as dead instructions --
           which is exactly what ROM has here. */
        if (*(int *)(a0 + 0xC) == 1) {
            s->wish2.ll |= 1ULL << 44;
        } else {
            s->wish2.ll |= 1ULL << 44;
        }

        if (0.1f < s->f_34C) {
            s->wish2.ll |= 1ULL << 45;
        }
    }

    if ((0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 4 < s->f_28 && (s->f_2E0 & 8)) {
        s->flags18.ll |= 1ULL << 43;
    }

    if (s->f_2E0 & 8) {
        if (GOBJ_SUB(a0)->f_4A0 == 0xBA) {
            GOBJ_WORK(a0)->f_38C = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 6;
        }
        if (GOBJ_WORK(a0)->f_390 == 0) {
            GOBJ_WORK(a0)->f_390 = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0x50 / 0x3C;
        }
        s->wish2.ll |= 1ULL << 46;
        s->wish4.ll |= 0x80;
        s->wish4.ll |= 0x100;
        s->wish4.ll |= 0x200;
        s->wish2.ll |= 1ULL << 56;
        s->wish2.ll |= 1ULL << 58;
        s->wish2.ll |= 1ULL << 57;
        s->wish4.ll |= 0x2000;
        if (!(0.1f < s->f_34C)) {
            s->wish3.ll |= 4;
            s->wish3.ll |= 0x10;
        }
    }

    if (GOBJ_WORK(a0)->f_390 != 0) {
        s->wish2.ll |= 1ULL << 46;
    }

    if (optionControlType == 1 ? (s->unk2E4 & 8) != 0 : (s->f_2E0 & 8) != 0) {
        s->wish2.ll |= 1ULL << 47;
    }

    if (optionControlType == 1 ? (s->unk2E4 & 8) != 0 : (s->f_2E0 & 8) == 0) {
        s->wish2.ll |= 1ULL << 48;
    }

    if (s->f_2E0 & 0x20) {
        s->wish3.ll |= 1ULL << 36;
        s->wish3.ll |= 1ULL << 37;
        s->wish3.ll |= 1ULL << 38;
        s->wish3.ll |= 1ULL << 39;
        s->wish3.ll |= 1ULL << 40;
        s->wish3.ll |= 1ULL << 41;
        s->wish3.ll |= 1ULL << 42;
    }

    if (s->unk2E4 & 0x20) {
        s->wish3.ll |= 1ULL << 44;
    }

    if (s->f_2E0 & 0x20) {
        ACTSearchGObj(a0, 0x13, 0x2D, &o, u, 100.0f);

        if (o != 0 && CheckCarryableItem(o)) {
            deg = a0 == boyGObj ? 60.0f : 80.0f;
            p[0] = test_CURRENTROOT(o)[0];
            p[1] = test_CURRENTROOT(o)[1];
            p[2] = test_CURRENTROOT(o)[2];
            if (p[1] > v[1] && (float)(p[1] - v[1] < 0.0f ? -(p[1] - v[1]) : (p[1] - v[1])) < deg) {
                s->nextItem.i = (int)o;
                s->wish3.ll |= 1ULL << 43;
            }
        }
        s->wish2.ll |= 1ULL << 54;
        s->wish2.ll |= 1ULL << 55;
    }

    if (s->f_2E0 & 0x10) {
        s->wish3.ll |= 0x400;
    }

    if (0.1f < s->f_34C) {
        s->wish2.ll |= 1ULL << 49;
    }

    if (a0 == boyGObj) {
        if (s->unk2E4 & 0x40) {
            if (0.1f < s->f_34C && (s->f_340 >= -45 && s->f_340 <= 45)) {
                s->wish2.ll |= 1ULL << 50;
            } else if (0.1f < s->f_34C && (s->f_340 >= 46 && s->f_340 <= 134)) {
                s->wish2.ll |= 1ULL << 52;
            } else if (0.1f < s->f_34C && s->f_340 >= -134 && s->f_340 <= -46) {
                s->wish2.ll |= 1ULL << 53;
            }
            s->wish2.ll |= 1ULL << 51;
        }
    }

    if (s->unk2E4 & 0x20) {
        s->wish3.ll |= 1ULL << 35;
        s->wish3.ll |= 1ULL << 33;
    }

    if ((int)(s->wish3.ll >> 37) & 1) {
        if ((int)(s->wish1.ll >> 37) & 1) {
            *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x2C0) = 1;
        }
    } else {
        *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x2C0) = 0;
    }
}
