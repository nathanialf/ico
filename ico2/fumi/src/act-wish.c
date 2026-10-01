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

/* The wish/flag words the pad handler ORs into the actor's sub-record are a
   64-bit word that the engine also reads a word at a time; declaring them as
   the union makes every one of those stores alias the 32-bit loads around
   them, which is what ROM's reload pattern shows (a plain
   `*(unsigned long long *)` spelling lets gcc keep the actor-root pointer
   live across the whole flag pile: 154 diffs vs 34 here). */
typedef union {
    unsigned long long ll;
    int i[2];
} WISHW;

#define WISH(p) (((WISHW *)(p))->ll)

/* The actor-root slot at +0x164 is an `int` field (the GObj work pointer is
   stored as an int throughout this engine -- cf. GobjProc's `g->f164 = 0`), so
   the chain reads it with `*(int *)`.  That is not cosmetic: an `int` load is in
   the same alias set as the `int` stores through the +0x688 sub-record, so gcc
   must re-load it after each of them, which is ROM's three-load shape at
   0x0014F844/0x0014F85C/0x0014F884.  Spelling it `*(char **)` puts it in the
   pointer alias set, gcc CSEs the three loads into one and hoists it into the
   line-586 branch delay slot -- two instructions short of ROM. */

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

    WISH((char *)s + 0x488) |= 1ULL << 37;
    WISH((char *)s + 0x488) |= 1ULL << 36;
    WISH((char *)s + 0x488) |= 1ULL << 33;

    WISH((char *)s + 0x498) |= 2;

    if ((s->f_2E0 & 0x20) || GOBJ_WORK(a0)->f_340 < 0.9) {
        WISH((char *)s + 0x498) |= 4;
    }
    WISH((char *)s + 0x490) |= 1ULL << 63;
    WISH((char *)s + 0x498) |= 1;

    WISH((char *)s + 0x490) |= 1ULL << 62;

    WISH((char *)s + 0x490) |= 1ULL << 55;
    WISH((char *)s + 0x490) |= 1ULL << 56;
    WISH((char *)s + 0x490) |= 1ULL << 57;
    WISH((char *)s + 0x490) |= 1ULL << 58;
    WISH((char *)s + 0x498) |= 0x20;
    WISH((char *)s + 0x498) |= 0x40;
    WISH((char *)s + 0x498) |= 0x400;
    WISH((char *)s + 0x498) |= 0x800;
    WISH((char *)s + 0x498) |= 0x1000;
    WISH((char *)s + 0x488) |= 1ULL << 59;
    WISH((char *)s + 0x488) |= 1ULL << 62;
    WISH((char *)s + 0x488) |= 1ULL << 63;
    WISH((char *)s + 0x490) |= 1;
    WISH((char *)s + 0x490) |= 2;

    WISH((char *)s + 0x490) |= 1ULL << 34;

    if (a0 == boyGObj) {
        if (0.1f < s->f_34C && ((int)(WISH((char *)s + 0x480) >> 5) & 1) &&
            chkOrient((char *)s, a1, u, 80.0f)) {
            if (!(s->f_2E0 & 8) || girlGObj == 0 || GOBJ_WORK(girlGObj)->f_3A0 == 0) {
                WISH((char *)s + 0x490) |= 0x20;
            }
        }
    } else {
        WISH((char *)s + 0x490) |= 0x20;
    }

    WISH((char *)s + 0x490) |= 0x800;
    WISH((char *)s + 0x490) |= 0x1000;
    WISH((char *)s + 0x490) |= 0x2000;
    WISH((char *)s + 0x490) |= 0x4000;
    WISH((char *)s + 0x490) |= 0x8000;
    WISH((char *)s + 0x490) |= 0x10000;
    WISH((char *)s + 0x490) |= 0x20000;
    WISH((char *)s + 0x498) |= 0x4000;

    WISH((char *)s + 0x490) |= 1ULL << 59;
    WISH((char *)s + 0x490) |= 1ULL << 60;
    WISH((char *)s + 0x490) |= 1ULL << 61;
    WISH((char *)s + 0x488) |= 1ULL << 60;
    WISH((char *)s + 0x488) |= 1ULL << 61;

    WISH((char *)s + 0x490) |= 0x1000000;
    WISH((char *)s + 0x490) |= 0x4000000;
    WISH((char *)s + 0x490) |= 0x2000000;

    WISH((char *)s + 0x490) |= 1ULL << 50;
    WISH((char *)s + 0x490) |= 1ULL << 51;
    WISH((char *)s + 0x490) |= 1ULL << 49;
    WISH((char *)s + 0x490) |= 0x80;
    if (0.1f < s->f_34C && (s->f_340 >= -45 && s->f_340 <= 45)) {
        WISH((char *)s + 0x490) |= 0x200;
        WISH((char *)s + 0x490) |= 0x100;
    }

    switch ((unsigned int)s->unk34) {
    case 1:
        if (s->f_4C >= 181) {
            WISH((char *)s + 0x488) |= 1ULL << 38;
        }
        break;
    case 4:
    case 5:
    case 18:
    case 62:
        WISH((char *)s + 0x490) |= 1ULL << 46;
        WISH((char *)s + 0x490) |= 1ULL << 45;
        WISH((char *)s + 0x490) |= 1ULL << 47;
        WISH((char *)s + 0x490) |= 1ULL << 48;
        WISH((char *)s + 0x490) |= 1ULL << 52;
        WISH((char *)s + 0x490) |= 1ULL << 53;
        WISH((char *)s + 0x490) |= 1ULL << 54;
        break;
    case 13:
        WISH((char *)s + 0x488) |= 1ULL << 54;
        break;
    }

    if (WISH((char *)s + 0x480) & 0xC00000) {
        if (a0 == boyGObj) {
            if (chkOrient((char *)s, a1, u, 80.0f)) {
                WISH((char *)s + 0x490) |= 0x400000;
                if (s->f_2E0 & 0x10) {
                    WISH((char *)s + 0x490) |= 0x800000;
                }
            }
        } else {
            WISH((char *)s + 0x490) |= 0x400000;
        }
    }

    if (((int)(WISH((char *)s + 0x480) >> 18) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        WISH((char *)s + 0x490) |= 0x40000;
    }

    if (((int)(WISH((char *)s + 0x480) >> 3) & 1) && (s->f_2E0 & 0x10) &&
        chkOrient((char *)s, a1, u, 90.0f)) {
        WISH((char *)s + 0x490) |= 8;
    }

    if (((int)(WISH((char *)s + 0x478) >> 32) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        if (a0 == boyGObj) {
            if (s->f_2E0 & 0x10) {
                WISH((char *)s + 0x490) |= 0x80000;

                WISH((char *)s + 0x490) |= 0x40;
            }
        } else {
            WISH((char *)s + 0x490) |= 0x80000;
            WISH((char *)s + 0x490) |= 0x8000000;
            WISH((char *)s + 0x490) |= 0x10000000;
            WISH((char *)s + 0x490) |= 0x20000000;
            if (a0 == girlGObj && girlControlMode == 0 &&
                (WISH((char *)s + 0x20) & (0xC000ULL << 23)) == (0xC000ULL << 23)) {
                WISH((char *)s + 0x490) &= ~0x80000;
            }
        }
    }

    if (((int)(WISH((char *)s + 0x480) >> 20) & 1) && chkOrient((char *)s, a1, u, 80.0f)) {
        WISH((char *)s + 0x490) |= 0x100000;
    }

    if (a0 == girlGObj && girlControlMode != 0) {
        if (!(s->f_2E0 & 0x10)) {
            WISH((char *)s + 0x490) &= ~0x80000;
            WISH((char *)s + 0x490) &= ~0x100000;
        }
    }

    WISH((char *)s + 0x498) |= 0x10;

    if (((int)(WISH((char *)s + 0x488) >> 3) & 1) && chkOrient((char *)s, a1, u, 60.0f)) {
        WISH((char *)s + 0x498) |= 8;
    }

    if (0.1f < s->f_34C || ((int)(WISH((char *)s + 0x20) >> 3) & 1)) {
        WISH((char *)s + 0x488) |= 1ULL << 34;
        WISH((char *)s + 0x488) |= 1ULL << 35;
    }

    if (s->unk2E4 & 0x10) {
        WISH((char *)s + 0x488) |= 1ULL << 39;
        if (0.1f < s->f_34C) {
            WISH((char *)s + 0x488) |= 1ULL << 40;

            WISH((char *)s + 0x488) |= 1ULL << 41;
            GOBJ_WORK(a0)->f_350 = a1[0];
            GOBJ_WORK(a0)->f_354 = a1[1];
            GOBJ_WORK(a0)->f_358 = a1[2];
        }
        WISH((char *)s + 0x488) |= 1ULL << 42;
        WISH((char *)s + 0x488) |= 1ULL << 43;
    }

    if (s->unk2E4 & 0x80) {
        /* Both arms set the same bit; gcc cross-jumps them and drops the
           branch, leaving the compare'(char *)s two operands as dead instructions --
           which is exactly what ROM has here. */
        if (*(int *)(a0 + 0xC) == 1) {
            WISH((char *)s + 0x488) |= 1ULL << 44;
        } else {
            WISH((char *)s + 0x488) |= 1ULL << 44;
        }

        if (0.1f < s->f_34C) {
            WISH((char *)s + 0x488) |= 1ULL << 45;
        }
    }

    if ((0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 4 < s->f_28 && (s->f_2E0 & 8)) {
        WISH((char *)s + 0x18) |= 1ULL << 43;
    }

    if (s->f_2E0 & 8) {
        if (GOBJ_SUB(a0)->f_4A0 == 0xBA) {
            GOBJ_WORK(a0)->f_38C = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 6;
        }
        if (GOBJ_WORK(a0)->f_390 == 0) {
            GOBJ_WORK(a0)->f_390 = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0x50 / 0x3C;
        }
        WISH((char *)s + 0x488) |= 1ULL << 46;
        WISH((char *)s + 0x498) |= 0x80;
        WISH((char *)s + 0x498) |= 0x100;
        WISH((char *)s + 0x498) |= 0x200;
        WISH((char *)s + 0x488) |= 1ULL << 56;
        WISH((char *)s + 0x488) |= 1ULL << 58;
        WISH((char *)s + 0x488) |= 1ULL << 57;
        WISH((char *)s + 0x498) |= 0x2000;
        if (!(0.1f < s->f_34C)) {
            WISH((char *)s + 0x490) |= 4;
            WISH((char *)s + 0x490) |= 0x10;
        }
    }

    if (GOBJ_WORK(a0)->f_390 != 0) {
        WISH((char *)s + 0x488) |= 1ULL << 46;
    }

    if (optionControlType == 1 ? (s->unk2E4 & 8) != 0 : (s->f_2E0 & 8) != 0) {
        WISH((char *)s + 0x488) |= 1ULL << 47;
    }

    if (optionControlType == 1 ? (s->unk2E4 & 8) != 0 : (s->f_2E0 & 8) == 0) {
        WISH((char *)s + 0x488) |= 1ULL << 48;
    }

    if (s->f_2E0 & 0x20) {
        WISH((char *)s + 0x490) |= 1ULL << 36;
        WISH((char *)s + 0x490) |= 1ULL << 37;
        WISH((char *)s + 0x490) |= 1ULL << 38;
        WISH((char *)s + 0x490) |= 1ULL << 39;
        WISH((char *)s + 0x490) |= 1ULL << 40;
        WISH((char *)s + 0x490) |= 1ULL << 41;
        WISH((char *)s + 0x490) |= 1ULL << 42;
    }

    if (s->unk2E4 & 0x20) {
        WISH((char *)s + 0x490) |= 1ULL << 44;
    }

    if (s->f_2E0 & 0x20) {
        ACTSearchGObj(a0, 0x13, 0x2D, &o, u, 100.0f);

        if (o != 0 && CheckCarryableItem(o)) {
            deg = a0 == boyGObj ? 60.0f : 80.0f;
            p[0] = test_CURRENTROOT(o)[0];
            p[1] = test_CURRENTROOT(o)[1];
            p[2] = test_CURRENTROOT(o)[2];
            if (p[1] > v[1] && (float)(p[1] - v[1] < 0.0f ? -(p[1] - v[1]) : (p[1] - v[1])) < deg) {
                *(int *)((char *)s + 0x184) = (int)o;
                WISH((char *)s + 0x490) |= 1ULL << 43;
            }
        }
        WISH((char *)s + 0x488) |= 1ULL << 54;
        WISH((char *)s + 0x488) |= 1ULL << 55;
    }

    if (s->f_2E0 & 0x10) {
        WISH((char *)s + 0x490) |= 0x400;
    }

    if (0.1f < s->f_34C) {
        WISH((char *)s + 0x488) |= 1ULL << 49;
    }

    if (a0 == boyGObj) {
        if (s->unk2E4 & 0x40) {
            if (0.1f < s->f_34C && (s->f_340 >= -45 && s->f_340 <= 45)) {
                WISH((char *)s + 0x488) |= 1ULL << 50;
            } else if (0.1f < s->f_34C && (s->f_340 >= 46 && s->f_340 <= 134)) {
                WISH((char *)s + 0x488) |= 1ULL << 52;
            } else if (0.1f < s->f_34C && s->f_340 >= -134 && s->f_340 <= -46) {
                WISH((char *)s + 0x488) |= 1ULL << 53;
            }
            WISH((char *)s + 0x488) |= 1ULL << 51;
        }
    }

    if (s->unk2E4 & 0x20) {
        WISH((char *)s + 0x490) |= 1ULL << 35;
        WISH((char *)s + 0x490) |= 1ULL << 33;
    }

    if ((int)(WISH((char *)s + 0x490) >> 37) & 1) {
        if ((int)(WISH((char *)s + 0x480) >> 37) & 1) {
            *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x2C0) = 1;
        }
    } else {
        *(int *)((char *)GOBJ_ACT(a0)->f_680 + 0x2C0) = 0;
    }
}
