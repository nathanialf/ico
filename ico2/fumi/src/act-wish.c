#include "common.h"

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

extern void *test_CURRENTROOT(char *a0);
extern void sceVu0ScaleVector(float *dst, float *src, float k);
extern int _RotyGV(void *a0, void *a1);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void *D_00639EA0;
extern int CurrentTargetGObj;
extern int D_0028F4C0[];
extern void ACTSearchGObj(char *a0, float a1, int a2, int a3, char **a4, float *a5);
extern int CheckCarryableItem(char *a0);

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
    char *s = (char *)*(int *)(a0 + 0x164);
    float deg;

    v[0] = ((float *)test_CURRENTROOT(a0))[0];
    v[1] = ((float *)test_CURRENTROOT(a0))[1];
    v[2] = ((float *)test_CURRENTROOT(a0))[2];

    WISH(s + 0x488) |= 1ULL << 37;
    WISH(s + 0x488) |= 1ULL << 36;
    WISH(s + 0x488) |= 1ULL << 33;

    WISH(s + 0x498) |= 2;

    if ((*(int *)(s + 0x2E0) & 0x20) ||
        *(float *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x340) < 0.9) {
        WISH(s + 0x498) |= 4;
    }
    WISH(s + 0x490) |= 1ULL << 63;
    WISH(s + 0x498) |= 1;

    WISH(s + 0x490) |= 1ULL << 62;

    WISH(s + 0x490) |= 1ULL << 55;
    WISH(s + 0x490) |= 1ULL << 56;
    WISH(s + 0x490) |= 1ULL << 57;
    WISH(s + 0x490) |= 1ULL << 58;
    WISH(s + 0x498) |= 0x20;
    WISH(s + 0x498) |= 0x40;
    WISH(s + 0x498) |= 0x400;
    WISH(s + 0x498) |= 0x800;
    WISH(s + 0x498) |= 0x1000;
    WISH(s + 0x488) |= 1ULL << 59;
    WISH(s + 0x488) |= 1ULL << 62;
    WISH(s + 0x488) |= 1ULL << 63;
    WISH(s + 0x490) |= 1;
    WISH(s + 0x490) |= 2;

    WISH(s + 0x490) |= 1ULL << 34;

    if (a0 == D_00639EA4) {
        if (0.1f < *(float *)(s + 0x34C) && ((int)(WISH(s + 0x480) >> 5) & 1) &&
            chkOrient(s, a1, u, 80.0f)) {
            if (!(*(int *)(s + 0x2E0) & 8) || D_00639EA8 == 0 ||
                *(int *)(*(char **)(*(char **)(D_00639EA8 + 0x164) + 0x688) + 0x3A0) == 0) {
                WISH(s + 0x490) |= 0x20;
            }
        }
    } else {
        WISH(s + 0x490) |= 0x20;
    }

    WISH(s + 0x490) |= 0x800;
    WISH(s + 0x490) |= 0x1000;
    WISH(s + 0x490) |= 0x2000;
    WISH(s + 0x490) |= 0x4000;
    WISH(s + 0x490) |= 0x8000;
    WISH(s + 0x490) |= 0x10000;
    WISH(s + 0x490) |= 0x20000;
    WISH(s + 0x498) |= 0x4000;

    WISH(s + 0x490) |= 1ULL << 59;
    WISH(s + 0x490) |= 1ULL << 60;
    WISH(s + 0x490) |= 1ULL << 61;
    WISH(s + 0x488) |= 1ULL << 60;
    WISH(s + 0x488) |= 1ULL << 61;

    WISH(s + 0x490) |= 0x1000000;
    WISH(s + 0x490) |= 0x4000000;
    WISH(s + 0x490) |= 0x2000000;

    WISH(s + 0x490) |= 1ULL << 50;
    WISH(s + 0x490) |= 1ULL << 51;
    WISH(s + 0x490) |= 1ULL << 49;
    WISH(s + 0x490) |= 0x80;
    if (0.1f < *(float *)(s + 0x34C) && (*(int *)(s + 0x340) >= -45 && *(int *)(s + 0x340) <= 45)) {
        WISH(s + 0x490) |= 0x200;
        WISH(s + 0x490) |= 0x100;
    }

    switch (*(unsigned int *)(s + 0x34)) {
    case 1:
        if (*(int *)(s + 0x4C) >= 181) {
            WISH(s + 0x488) |= 1ULL << 38;
        }
        break;
    case 4:
    case 5:
    case 18:
    case 62:
        WISH(s + 0x490) |= 1ULL << 46;
        WISH(s + 0x490) |= 1ULL << 45;
        WISH(s + 0x490) |= 1ULL << 47;
        WISH(s + 0x490) |= 1ULL << 48;
        WISH(s + 0x490) |= 1ULL << 52;
        WISH(s + 0x490) |= 1ULL << 53;
        WISH(s + 0x490) |= 1ULL << 54;
        break;
    case 13:
        WISH(s + 0x488) |= 1ULL << 54;
        break;
    }

    if (WISH(s + 0x480) & 0xC00000) {
        if (a0 == D_00639EA4) {
            if (chkOrient(s, a1, u, 80.0f)) {
                WISH(s + 0x490) |= 0x400000;
                if (*(int *)(s + 0x2E0) & 0x10) {
                    WISH(s + 0x490) |= 0x800000;
                }
            }
        } else {
            WISH(s + 0x490) |= 0x400000;
        }
    }

    if (((int)(WISH(s + 0x480) >> 18) & 1) && chkOrient(s, a1, u, 80.0f)) {
        WISH(s + 0x490) |= 0x40000;
    }

    if (((int)(WISH(s + 0x480) >> 3) & 1) && (*(int *)(s + 0x2E0) & 0x10) &&
        chkOrient(s, a1, u, 90.0f)) {
        WISH(s + 0x490) |= 8;
    }

    if (((int)(WISH(s + 0x478) >> 32) & 1) && chkOrient(s, a1, u, 80.0f)) {
        if (a0 == D_00639EA4) {
            if (*(int *)(s + 0x2E0) & 0x10) {
                WISH(s + 0x490) |= 0x80000;

                WISH(s + 0x490) |= 0x40;
            }
        } else {
            WISH(s + 0x490) |= 0x80000;
            WISH(s + 0x490) |= 0x8000000;
            WISH(s + 0x490) |= 0x10000000;
            WISH(s + 0x490) |= 0x20000000;
            if (a0 == D_00639EA8 && D_00639EA0 == 0 &&
                (WISH(s + 0x20) & (0xC000ULL << 23)) == (0xC000ULL << 23)) {
                WISH(s + 0x490) &= ~0x80000;
            }
        }
    }

    if (((int)(WISH(s + 0x480) >> 20) & 1) && chkOrient(s, a1, u, 80.0f)) {
        WISH(s + 0x490) |= 0x100000;
    }

    if (a0 == D_00639EA8 && D_00639EA0 != 0) {
        if (!(*(int *)(s + 0x2E0) & 0x10)) {
            WISH(s + 0x490) &= ~0x80000;
            WISH(s + 0x490) &= ~0x100000;
        }
    }

    WISH(s + 0x498) |= 0x10;

    if (((int)(WISH(s + 0x488) >> 3) & 1) && chkOrient(s, a1, u, 60.0f)) {
        WISH(s + 0x498) |= 8;
    }

    if (0.1f < *(float *)(s + 0x34C) || ((int)(WISH(s + 0x20) >> 3) & 1)) {
        WISH(s + 0x488) |= 1ULL << 34;
        WISH(s + 0x488) |= 1ULL << 35;
    }

    if (*(int *)(s + 0x2E4) & 0x10) {
        WISH(s + 0x488) |= 1ULL << 39;
        if (0.1f < *(float *)(s + 0x34C)) {
            WISH(s + 0x488) |= 1ULL << 40;

            WISH(s + 0x488) |= 1ULL << 41;
            *(float *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x350) = a1[0];
            *(float *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x354) = a1[1];
            *(float *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x358) = a1[2];
        }
        WISH(s + 0x488) |= 1ULL << 42;
        WISH(s + 0x488) |= 1ULL << 43;
    }

    if (*(int *)(s + 0x2E4) & 0x80) {
        /* Both arms set the same bit; gcc cross-jumps them and drops the
           branch, leaving the compare's two operands as dead instructions --
           which is exactly what ROM has here. */
        if (*(int *)(a0 + 0xC) == 1) {
            WISH(s + 0x488) |= 1ULL << 44;
        } else {
            WISH(s + 0x488) |= 1ULL << 44;
        }

        if (0.1f < *(float *)(s + 0x34C)) {
            WISH(s + 0x488) |= 1ULL << 45;
        }
    }

    if ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] / 4 < *(int *)(s + 0x28) &&
        (*(int *)(s + 0x2E0) & 8)) {
        WISH(s + 0x18) |= 1ULL << 43;
    }

    if (*(int *)(s + 0x2E0) & 8) {
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x4A0) == 0xBA) {
            *(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x38C) =
                (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] / 6;
        }
        if (*(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x390) == 0) {
            *(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x390) =
                (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x50 / 0x3C;
        }
        WISH(s + 0x488) |= 1ULL << 46;
        WISH(s + 0x498) |= 0x80;
        WISH(s + 0x498) |= 0x100;
        WISH(s + 0x498) |= 0x200;
        WISH(s + 0x488) |= 1ULL << 56;
        WISH(s + 0x488) |= 1ULL << 58;
        WISH(s + 0x488) |= 1ULL << 57;
        WISH(s + 0x498) |= 0x2000;
        if (!(0.1f < *(float *)(s + 0x34C))) {
            WISH(s + 0x490) |= 4;
            WISH(s + 0x490) |= 0x10;
        }
    }

    if (*(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x688) + 0x390) != 0) {
        WISH(s + 0x488) |= 1ULL << 46;
    }

    if (CurrentTargetGObj == 1 ? (*(int *)(s + 0x2E4) & 8) != 0 : (*(int *)(s + 0x2E0) & 8) != 0) {
        WISH(s + 0x488) |= 1ULL << 47;
    }

    if (CurrentTargetGObj == 1 ? (*(int *)(s + 0x2E4) & 8) != 0 : (*(int *)(s + 0x2E0) & 8) == 0) {
        WISH(s + 0x488) |= 1ULL << 48;
    }

    if (*(int *)(s + 0x2E0) & 0x20) {
        WISH(s + 0x490) |= 1ULL << 36;
        WISH(s + 0x490) |= 1ULL << 37;
        WISH(s + 0x490) |= 1ULL << 38;
        WISH(s + 0x490) |= 1ULL << 39;
        WISH(s + 0x490) |= 1ULL << 40;
        WISH(s + 0x490) |= 1ULL << 41;
        WISH(s + 0x490) |= 1ULL << 42;
    }

    if (*(int *)(s + 0x2E4) & 0x20) {
        WISH(s + 0x490) |= 1ULL << 44;
    }

    if (*(int *)(s + 0x2E0) & 0x20) {
        ACTSearchGObj(a0, 100.0f, 0x13, 0x2D, &o, u);

        if (o != 0 && CheckCarryableItem(o)) {
            deg = a0 == D_00639EA4 ? 60.0f : 80.0f;
            p[0] = ((float *)test_CURRENTROOT(o))[0];
            p[1] = ((float *)test_CURRENTROOT(o))[1];
            p[2] = ((float *)test_CURRENTROOT(o))[2];
            if (p[1] > v[1] && (float)(p[1] - v[1] < 0.0f ? -(p[1] - v[1]) : (p[1] - v[1])) < deg) {
                *(int *)(s + 0x184) = (int)o;
                WISH(s + 0x490) |= 1ULL << 43;
            }
        }
        WISH(s + 0x488) |= 1ULL << 54;
        WISH(s + 0x488) |= 1ULL << 55;
    }

    if (*(int *)(s + 0x2E0) & 0x10) {
        WISH(s + 0x490) |= 0x400;
    }

    if (0.1f < *(float *)(s + 0x34C)) {
        WISH(s + 0x488) |= 1ULL << 49;
    }

    if (a0 == D_00639EA4) {
        if (*(int *)(s + 0x2E4) & 0x40) {
            if (0.1f < *(float *)(s + 0x34C) &&
                (*(int *)(s + 0x340) >= -45 && *(int *)(s + 0x340) <= 45)) {
                WISH(s + 0x488) |= 1ULL << 50;
            } else if (0.1f < *(float *)(s + 0x34C) &&
                       (*(int *)(s + 0x340) >= 46 && *(int *)(s + 0x340) <= 134)) {
                WISH(s + 0x488) |= 1ULL << 52;
            } else if (0.1f < *(float *)(s + 0x34C) && *(int *)(s + 0x340) >= -134 &&
                       *(int *)(s + 0x340) <= -46) {
                WISH(s + 0x488) |= 1ULL << 53;
            }
            WISH(s + 0x488) |= 1ULL << 51;
        }
    }

    if (*(int *)(s + 0x2E4) & 0x20) {
        WISH(s + 0x490) |= 1ULL << 35;
        WISH(s + 0x490) |= 1ULL << 33;
    }

    if ((int)(WISH(s + 0x490) >> 37) & 1) {
        if ((int)(WISH(s + 0x480) >> 37) & 1) {
            *(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x680) + 0x2C0) = 1;
        }
    } else {
        *(int *)(*(char **)(*(int *)(a0 + 0x164) + 0x680) + 0x2C0) = 0;
    }
}
