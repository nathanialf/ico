#include "common.h"
#include "ico/types.h"

/* act-game 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; char _pad34[0x54]; int f_88, f_8C, f_90; char _pad94[0xEC]; int f_180; } AGState;

extern void BoxBarSoundOn(void *, int);
extern int func_002610F0(void);
extern int checkHit();
extern void func_001927F8(void *, int, void *, void *);
extern void debug_assertMessage(void *msg, ...);
extern float func_0023FE70(void *, void *);
extern void func_00240038(void *a0, void *a1, float a2);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void CylinderCollisionWithControlDynamics(void *, void *);
extern int GetDifferenceFromWallUpperPlane(void *);
extern void func_00260568(void *a0, int a1, int a2);
extern int DebugDisp1CollisionWithColor(void *a0, void *a1);
extern void *subCommonIdle(void *a0);
extern void ClipWallBoxStop(void *);
extern int func_001668B0(int, int);
extern void fzMagnitudefv(void *out, int n, void *vec);
extern void dispPlane(void *, void *);
extern int *ContinueCorrectPosition(int *a0);
extern void func_001FE250(void *, int, int);
extern float RotateAccordingToStick_PatternThree(void *a0, void *a1);
extern void func_00191DB8(void *a0, float a1);
extern void func_001920A8(void *, void *);
extern void *D_00629DE4;
extern void *D_00629DE8;
extern float D_00628DD4;
extern float D_00628DD8;
extern char D_005523C0[];

typedef struct { char _0[0x188]; int f_188; int f_18C; } AGAnim2; /* stride 0x190 */
extern AGAnim2 D_0055DA10_a[] __asm__("D_0055DA10");

typedef struct { long long q; } __attribute__((packed)) AGUq;

#define AGQ(o) (*(unsigned long long *)(p + (o)))

void ACTGame_SaveActorInformation(void *gobj) {
    float v0[4];
    float box1[48];
    float vD0[4];
    float vE0[4];
    float vF0[4];
    float v100[4];
    float box2[48];
    float v1D0[4];
    float v1E0[4];
    float v1F0[4];
    float box3[48];
    float v2C0[4];
    float v2D0[4];
    float v2E0[4];
    float v2F0[4];
    char *p = *(char **)((char *)gobj + 0x164);
    int i;

    if ((int)(AGQ(0x468) >> 38) & 1) {
        if ((int)(AGQ(0x478) >> 38) & 1) BoxBarSoundOn(gobj, 0xAE);
    }
    if ((int)(AGQ(0x468) >> 39) & 1) {
        if ((int)(AGQ(0x478) >> 39) & 1) BoxBarSoundOn(gobj, 0xAF);
    }
    if ((int)(AGQ(0x468) >> 40) & 1) {
        if ((int)(AGQ(0x478) >> 40) & 1) BoxBarSoundOn(gobj, 0xB0);
    }
    if ((int)(AGQ(0x468) >> 41) & 1) {
        if ((int)(AGQ(0x478) >> 41) & 1) BoxBarSoundOn(gobj, 0xB1);
    }
    if ((int)(AGQ(0x468) >> 42) & 1) {
        if ((int)(AGQ(0x478) >> 42) & 1) {
            if (*(int *)((char *)gobj + 0xC) == 4) {
                if (func_002610F0() & 1) {
                    BoxBarSoundOn(gobj, 0xBA);
                } else {
                    BoxBarSoundOn(gobj, 0xBC);
                }
            } else {
                BoxBarSoundOn(gobj, 0xBA);
            }
        }
    }
    if ((int)(AGQ(0x468) >> 43) & 1) {
        if ((int)(AGQ(0x478) >> 43) & 1) BoxBarSoundOn(gobj, 0xBB);
    }
    if ((int)(AGQ(0x468) >> 48) & 1) {
        long long t48 = *(unsigned short *)(p + 0x47E);
        if ((int)t48 & 1) BoxBarSoundOn(gobj, 0x104);
    }
    if (gobj != D_00629DE4) {
        if ((int)(AGQ(0x468) >> 47) & 1) {
            if ((int)(AGQ(0x478) >> 47) & 1) BoxBarSoundOn(gobj, 0x103);
        }
        if ((int)(AGQ(0x468) >> 49) & 1) {
            if ((int)(AGQ(0x478) >> 49) & 1) BoxBarSoundOn(gobj, 0x105);
        }
        if ((int)(AGQ(0x468) >> 50) & 1) {
            if ((int)(AGQ(0x478) >> 50) & 1) BoxBarSoundOn(gobj, 0x106);
        }
    }
    if ((int)(AGQ(0x468) >> 52) & 1) {
        if ((int)(AGQ(0x478) >> 52) & 1) BoxBarSoundOn(gobj, 0xB8);
    }
    if ((int)(AGQ(0x468) >> 51) & 1) {
        if ((int)(AGQ(0x478) >> 51) & 1) {
            void *h = *(void **)(*(char **)((char *)gobj + 0x164) + 0x130);
            int t = 0;
            int r;
            if (h == 0 || (r = checkHit(h)) == 0) t = 1;
            r = t;
            if (r) {
                BoxBarSoundOn(gobj, 0xB7);
            } else {
                BoxBarSoundOn(gobj, 0xB6);
            }
        }
    }
    if ((int)(AGQ(0x468) >> 53) & 1) {
        if ((int)(AGQ(0x478) >> 53) & 1) BoxBarSoundOn(gobj, 0x13C);
    }
    if ((int)(AGQ(0x468) >> 54) & 1) {
        if ((int)(AGQ(0x478) >> 54) & 1) BoxBarSoundOn(gobj, 0x15A);
    }
    if ((int)(AGQ(0x468) >> 57) & 1) {
        if ((int)(AGQ(0x478) >> 57) & 1) BoxBarSoundOn(gobj, 0xBE);
    }
    if ((int)(AGQ(0x468) >> 58) & 1) {
        if ((int)(AGQ(0x478) >> 58) & 1) BoxBarSoundOn(gobj, 0xBF);
    }
    if ((int)(AGQ(0x468) >> 59) & 1) {
        if ((int)(AGQ(0x478) >> 59) & 1) BoxBarSoundOn(gobj, 0xC1);
    }
    if ((int)(AGQ(0x468) >> 60) & 1) {
        if ((int)(AGQ(0x478) >> 60) & 1) BoxBarSoundOn(gobj, 0xC2);
    }
    if ((int)(AGQ(0x468) >> 61) & 1) {
        if ((int)(AGQ(0x478) >> 61) & 1)
            func_001927F8(gobj, 0xF4, gobj, *(char **)(*(char **)((char *)gobj + 0x164) + 0x678) + 0x720);
    }
    if ((int)(AGQ(0x468) >> 62) & 1) {
        if ((int)(AGQ(0x478) >> 62) & 1)
            func_001927F8(gobj, 0xF5, gobj, *(char **)(*(char **)((char *)gobj + 0x164) + 0x678) + 0x750);
    }
    if ((int)(AGQ(0x468) >> 63) & 1) {
        if ((int)(AGQ(0x478) >> 63) & 1)
            func_001927F8(gobj, 0xF6, gobj, *(char **)(*(char **)((char *)gobj + 0x164) + 0x678) + 0x780);
    }
    if ((int)(AGQ(0x468) >> 55) & 1) {
        if ((int)(AGQ(0x478) >> 55) & 1) {
            BoxBarSoundOn(gobj, 0x9F);
            BoxBarSoundOn(gobj, 0x9E);
        }
    }
    if ((int)(AGQ(0x468) >> 56) & 1) {
        long long t56 = *(unsigned char *)(p + 0x47F);
        if ((int)t56 & 1) BoxBarSoundOn(gobj, 0x98);
    }

    if (((int)(AGQ(0x470) >> 4) & 1) && ((int)(AGQ(0x480) >> 4) & 1)) {
        BoxBarSoundOn(gobj, 0xC5);
        debug_assertMessage(D_005523C0);
    } else if (*(int *)(p + 0x30) == 0x2B) {
        BoxBarSoundOn(gobj, 0xC6);
    }
    if ((int)(AGQ(0x470) >> 5) & 1) {
        if ((int)(AGQ(0x480) >> 5) & 1) BoxBarSoundOn(gobj, 0xC7);
    }
    if ((int)(AGQ(0x470) >> 6) & 1) {
        if ((int)(AGQ(0x480) >> 6) & 1) BoxBarSoundOn(gobj, 0xC8);
    }
    if ((int)(AGQ(0x470) >> 7) & 1) {
        if ((int)(AGQ(0x480) >> 7) & 1) BoxBarSoundOn(gobj, 0xC9);
    }
    if ((int)(AGQ(0x470) >> 8) & 1) {
        if ((int)(AGQ(0x480) >> 8) & 1) BoxBarSoundOn(gobj, 0xCC);
    }
    if ((int)(AGQ(0x470) >> 9) & 1) {
        if ((int)(AGQ(0x480) >> 9) & 1) BoxBarSoundOn(gobj, 0xCD);
    }
    if ((int)(AGQ(0x470) >> 10) & 1) {
        if ((int)(AGQ(0x480) >> 10) & 1) BoxBarSoundOn(gobj, 0xCE);
    }
    if ((int)(AGQ(0x470) >> 29) & 1) {
        if ((int)(AGQ(0x480) >> 29) & 1) BoxBarSoundOn(gobj, 0x71);
    }
    if ((int)(AGQ(0x470) >> 31) & 1) {
        if ((int)(AGQ(0x480) >> 31) & 1) BoxBarSoundOn(gobj, 0x72);
    }
    if ((int)(AGQ(0x470) >> 33) & 1) {
        if ((int)(AGQ(0x480) >> 33) & 1) BoxBarSoundOn(gobj, 0x79);
    }
    if ((int)(AGQ(0x470) >> 32) & 1) {
        long long t32 = *(unsigned int *)(p + 0x484);
        if ((int)t32 & 1) BoxBarSoundOn(gobj, 0x76);
    }
    if ((int)(AGQ(0x470) >> 34) & 1) {
        if ((int)(AGQ(0x480) >> 34) & 1) BoxBarSoundOn(gobj, 0x7A);
    }
    if ((int)(AGQ(0x470) >> 35) & 1) {
        if ((int)(AGQ(0x480) >> 35) & 1) BoxBarSoundOn(gobj, 0x7B);
    }
    if ((int)(AGQ(0x470) >> 36) & 1) {
        if ((int)(AGQ(0x480) >> 36) & 1) BoxBarSoundOn(gobj, 0x73);
    }
    if ((int)(AGQ(0x470) >> 37) & 1) {
        if ((int)(AGQ(0x480) >> 37) & 1) {
            BoxBarSoundOn(gobj, 0x74);
            BoxBarSoundOn(gobj, 0x75);
        }
    }
    if ((int)(AGQ(0x470) >> 26) & 1) {
        if ((int)(AGQ(0x480) >> 26) & 1) BoxBarSoundOn(gobj, 0x6E);
    }
    if ((int)(AGQ(0x470) >> 27) & 1) {
        if ((int)(AGQ(0x480) >> 27) & 1) BoxBarSoundOn(gobj, 0x6F);
    }
    if ((int)(AGQ(0x470) >> 28) & 1) {
        if ((int)(AGQ(0x480) >> 28) & 1) BoxBarSoundOn(gobj, 0x70);
    }
    if (*(int *)(p + 0x470) & 1) {
        if (*(int *)(p + 0x480) & 1) {
            if (gobj == D_00629DE8) {
                if (*(int *)(*(char **)((char *)gobj + 0x164) + 0x30) == 0x71) BoxBarSoundOn(gobj, 0x6A);
            } else {
                BoxBarSoundOn(gobj, 0x6A);
            }
        }
    }
    if ((int)(AGQ(0x470) >> 1) & 1) {
        if ((int)(AGQ(0x480) >> 1) & 1) BoxBarSoundOn(gobj, 0x12D);
    }
    if ((int)(AGQ(0x470) >> 2) & 1) {
        if ((int)(AGQ(0x480) >> 2) & 1) BoxBarSoundOn(gobj, 0x12E);
    }
    if ((int)(AGQ(0x470) >> 11) & 1) {
        if ((int)(AGQ(0x480) >> 11) & 1) BoxBarSoundOn(gobj, 0x126);
    }
    if ((int)(AGQ(0x470) >> 12) & 1) {
        if ((int)(AGQ(0x480) >> 12) & 1) BoxBarSoundOn(gobj, 0x127);
    }
    if ((int)(AGQ(0x470) >> 13) & 1) {
        if ((int)(AGQ(0x480) >> 13) & 1) BoxBarSoundOn(gobj, 0x128);
    }
    if ((int)(AGQ(0x470) >> 15) & 1) {
        if ((int)(AGQ(0x480) >> 15) & 1) BoxBarSoundOn(gobj, 0x129);
    }
    if ((int)(AGQ(0x470) >> 16) & 1) {
        if ((int)(AGQ(0x480) >> 16) & 1) BoxBarSoundOn(gobj, 0x129);
    }
    if ((int)(AGQ(0x470) >> 20) & 1) {
        if ((int)(AGQ(0x480) >> 20) & 1) BoxBarSoundOn(gobj, 0x126);
    }
    if ((int)(AGQ(0x470) >> 21) & 1) {
        if ((int)(AGQ(0x480) >> 21) & 1) BoxBarSoundOn(gobj, 0x127);
    }
    if ((int)(AGQ(0x470) >> 22) & 1) {
        if ((int)(AGQ(0x480) >> 22) & 1) BoxBarSoundOn(gobj, 0x128);
    }
    if ((int)(AGQ(0x470) >> 47) & 1) {
        if ((int)(AGQ(0x480) >> 47) & 1) BoxBarSoundOn(gobj, 0x29);
    }
    if ((int)(AGQ(0x470) >> 48) & 1) {
        long long u48 = *(unsigned short *)(p + 0x486);
        if ((int)u48 & 1) BoxBarSoundOn(gobj, 0x7E);
    }
    if ((int)(AGQ(0x470) >> 49) & 1) {
        if ((int)(AGQ(0x480) >> 49) & 1) BoxBarSoundOn(gobj, 0x7F);
    }
    if ((int)(AGQ(0x470) >> 54) & 1) {
        if ((int)(AGQ(0x480) >> 54) & 1) BoxBarSoundOn(gobj, 0x115);
    }
    if ((int)(AGQ(0x470) >> 55) & 1) {
        if ((int)(AGQ(0x480) >> 55) & 1) BoxBarSoundOn(gobj, 0x117);
    }
    if ((int)(AGQ(0x470) >> 56) & 1) {
        long long u56 = *(unsigned char *)(p + 0x487);
        if ((int)u56 & 1) goto snd113;
    }
    if ((int)(AGQ(0x470) >> 57) & 1) {
        if ((int)(AGQ(0x480) >> 57) & 1) {
snd113:
            BoxBarSoundOn(gobj, 0x113);
        }
    }
    if ((int)(AGQ(0x470) >> 45) & 1) {
        if ((int)(AGQ(0x480) >> 45) & 1) BoxBarSoundOn(gobj, 0x119);
    }
    if ((int)(AGQ(0x470) >> 46) & 1) {
        if ((int)(AGQ(0x480) >> 46) & 1) BoxBarSoundOn(gobj, 0x86);
    }
    if ((int)(AGQ(0x470) >> 38) & 1) {
        if ((int)(AGQ(0x480) >> 38) & 1) BoxBarSoundOn(gobj, 0x113);
    }
    if ((int)(AGQ(0x470) >> 39) & 1) {
        if ((int)(AGQ(0x480) >> 39) & 1) BoxBarSoundOn(gobj, 0x118);
    }
    if ((int)(AGQ(0x470) >> 40) & 1) {
        if ((int)(AGQ(0x480) >> 40) & 1) BoxBarSoundOn(gobj, 0x11E);
    }
    if ((int)(AGQ(0x470) >> 41) & 1) {
        if ((int)(AGQ(0x480) >> 41) & 1) BoxBarSoundOn(gobj, 0x11F);
    }
    if ((int)(AGQ(0x470) >> 42) & 1) {
        if ((int)(AGQ(0x480) >> 42) & 1) BoxBarSoundOn(gobj, 0x120);
    }
    if ((int)(AGQ(0x470) >> 43) & 1) {
        if ((int)(AGQ(0x480) >> 43) & 1) BoxBarSoundOn(gobj, 0x121);
    }
    if ((int)(AGQ(0x470) >> 44) & 1) {
        if ((int)(AGQ(0x480) >> 44) & 1) BoxBarSoundOn(gobj, 0x122);
    }
    if ((int)(AGQ(0x478) >> 1) & 1) {
        if ((int)(AGQ(0x488) >> 1) & 1) BoxBarSoundOn(gobj, 0x52);
    }
    if ((int)(AGQ(0x478) >> 2) & 1) {
        if ((int)(AGQ(0x488) >> 2) & 1) BoxBarSoundOn(gobj, 0x53);
    }
    if ((int)(AGQ(0x470) >> 62) & 1) {
        if ((int)(AGQ(0x480) >> 62) & 1) {
            BoxBarSoundOn(gobj, 0x43);
            *(int *)(p + 0x40) = 0x5F;
        }
    }
    if ((int)(AGQ(0x470) >> 63) & 1) {
        if ((int)(AGQ(0x480) >> 63) & 1) {
            BoxBarSoundOn(gobj, 0x43);
            *(int *)(p + 0x40) = 0x61;
        }
    }
    if (*(int *)(p + 0x478) & 1) {
        if (*(int *)(p + 0x488) & 1) {
            BoxBarSoundOn(gobj, 0x43);
            *(int *)(p + 0x40) = 0x63;
        }
    }
    if ((int)(AGQ(0x470) >> 17) & 1) {
        if ((int)(AGQ(0x480) >> 17) & 1) BoxBarSoundOn(gobj, 0x12A);
    }
    if ((int)(AGQ(0x470) >> 18) & 1) {
        if ((int)(AGQ(0x480) >> 18) & 1) BoxBarSoundOn(gobj, 0x12B);
    }
    if ((int)(AGQ(0x470) >> 19) & 1) {
        if ((int)(AGQ(0x480) >> 19) & 1) BoxBarSoundOn(gobj, 0x12C);
    }
    if ((int)(AGQ(0x470) >> 53) & 1) {
        if ((int)(AGQ(0x480) >> 53) & 1) BoxBarSoundOn(gobj, 0x97);
    }
    if ((int)(AGQ(0x478) >> 3) & 1) {
        if ((int)(AGQ(0x488) >> 3) & 1) BoxBarSoundOn(gobj, 0x167);
    }
    if ((int)(AGQ(0x478) >> 4) & 1) {
        if ((int)(AGQ(0x488) >> 4) & 1) {
            char *q = p + 0x4B0;
            char *d;
            float f;
            f = func_0023FE70(*(char **)((char *)gobj + 0x15C) + 0x120, q);
            func_00240038(v0, q, -f);
            d = *(char **)((char *)gobj + 0x15C) + 0x120;
            func_0023FFF0(d, d, v0);
            CylinderCollisionWithControlDynamics(gobj, p + 0x530);
        }
    }
    if (*(int *)(*(char **)(*(char **)((char *)gobj + 0x164) + 0x670) + 0x29C) > 0) {
        BoxBarSoundOn(gobj, 0x67);
    }
    {
        char *dobj = *(char **)((char *)gobj + 0x15C);
        if (((AGAnim2 *)(*(int *)(dobj + 0x490) * 0x190 + (char *)D_0055DA10_a))->f_188 < 0) {
            if (GetDifferenceFromWallUpperPlane(gobj)) {
                char *c;
                int idx;
                void *w;
                func_00260568(box1, 0, 0xC0);
                idx = DebugDisp1CollisionWithColor(gobj, (void *)0x33);
                c = (char *)((idx << 6) + *(int *)(*(char **)((char *)gobj + 0x15C) + 0xC));
                vE0[0] = *(float *)(c + 0x30);
                vE0[1] = *(float *)(c + 0x34);
                vE0[2] = *(float *)(c + 0x38);
                idx = DebugDisp1CollisionWithColor(gobj, (void *)0x2F);
                c = (char *)((idx << 6) + *(int *)(*(char **)((char *)gobj + 0x15C) + 0xC));
                vF0[0] = *(float *)(c + 0x30);
                vF0[1] = *(float *)(c + 0x34);
                vF0[2] = *(float *)(c + 0x38);
                func_0023FFF0(vD0, vE0, vF0);
                func_00240038(vD0, vD0, 0.5f);
                vD0[1] += 50.0f;
                func_00240038(v100, subCommonIdle(gobj), 50.0f);
                func_0023FFF0(box1, vD0, v100);
                func_00240038(v100, subCommonIdle(gobj), -50.0f);
                func_0023FFF0((char *)box1 + 0x10, vD0, v100);
                *(int *)((char *)box1 + 0x70) = 0;
                ClipWallBoxStop(box1);
                if (func_001668B0(*(int *)((char *)box1 + 0x98), 0x2000)) {
                    BoxBarSoundOn(gobj, 0x12F);
                }
                if (func_001668B0(*(int *)((char *)box1 + 0x98), 0x20000)) {
                    if (*(int *)(p + 0x67C)) {
                        if (GetDifferenceFromWallUpperPlane(gobj)) {
                            *(AGUq *)(*(char **)(p + 0x67C)) = *(AGUq *)((char *)box1 + 0x80);
                            *(int *)(*(char **)(p + 0x67C) + 8) = *(int *)((char *)box1 + 0x88);
                            func_001927F8(gobj, 0x116, gobj, *(char **)(p + 0x67C));
                        }
                    }
                }
            }
        }
    }
    {
        char *dobj = *(char **)((char *)gobj + 0x15C);
        if (((AGAnim2 *)(*(int *)(dobj + 0x490) * 0x190 + (char *)D_0055DA10_a))->f_18C & 1) {
            int flag1, flag2, hit;
            float *r;
            void *w;
            func_00260568(box2, 0, 0xC0);
            hit = 0;
            r = (float *)ContinueCorrectPosition(gobj);
            v1D0[0] = r[0];
            r = (float *)ContinueCorrectPosition(gobj);
            v1D0[1] = r[1];
            r = (float *)ContinueCorrectPosition(gobj);
            v1D0[2] = r[2];
            func_00240038(v1E0, subCommonIdle(gobj), -50.0f);
            func_0023FFF0(box2, v1D0, v1E0);
            func_00240038(v1E0, subCommonIdle(gobj), 50.0f);
            func_0023FFF0((char *)box2 + 0x10, v1D0, v1E0);
            flag1 = 0;
            flag2 = 0;
            *(int *)((char *)box2 + 0x70) = 0;
            ClipWallBoxStop(box2);
            if (func_001668B0(*(int *)((char *)box2 + 0x98), 0x400)) flag1 = 1;
            if (func_001668B0(*(int *)((char *)box2 + 0x98), 0xC000)) flag2 = 1;
            if (flag1 || flag2) {
                func_001FE250(v1F0, *(int *)((char *)box2 + 0x80), *(int *)((char *)box2 + 0x88));
                w = ContinueCorrectPosition(gobj);
                if (RotateAccordingToStick_PatternThree(v1F0, w) < 400.0f) hit = 1;
            }
            if (flag1) {
                if (hit) BoxBarSoundOn(gobj, 0x82);
            }
            if (flag2) {
                if (hit) BoxBarSoundOn(gobj, 0x120);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if ((int)(AGQ(0x20) >> 18) & 1) {
            char *c;
            int idx;
            void *w;
            int n;
            func_00260568(box3, 0, 0xC0);
            idx = DebugDisp1CollisionWithColor(gobj, (void *)0x33);
            c = (char *)((idx << 6) + *(int *)(*(char **)((char *)gobj + 0x15C) + 0xC));
            v2C0[0] = *(float *)(c + 0x30);
            v2C0[1] = *(float *)(c + 0x34);
            v2C0[2] = *(float *)(c + 0x38);
            idx = DebugDisp1CollisionWithColor(gobj, (void *)0x2F);
            c = (char *)((idx << 6) + *(int *)(*(char **)((char *)gobj + 0x15C) + 0xC));
            v2D0[0] = *(float *)(c + 0x30);
            v2D0[1] = *(float *)(c + 0x34);
            v2D0[2] = *(float *)(c + 0x38);
            func_0023FFF0(v1F0, v2C0, v2D0);
            func_00240038(v1F0, v1F0, 0.5f);
            v1F0[1] += 50.0f;
            func_00240038(v2E0, subCommonIdle(gobj), 50.0f);
            func_00191DB8(v2E0, D_00628DD4);
            func_0023FFF0(box3, v1F0, v2E0);
            func_00240038(v2E0, subCommonIdle(gobj), 50.0f);
            func_00191DB8(v2E0, D_00628DD8);
            func_0023FFF0((char *)box3 + 0x10, v1F0, v2E0);
            if (i == 1) {
                func_001920A8(box3, (char *)box3 + 0x10);
            }
            *(int *)((char *)box3 + 0x70) = 0;
            ClipWallBoxStop(box3);
            n = *(int *)((char *)box3 + 0x88);
            if (n) {
                fzMagnitudefv(v2F0, n, (char *)box3 + 0x80);
                dispPlane(gobj, v2F0);
                AGQ(0x20) &= 0xFFFFFFFFFFFBFFFFULL;
                break;
            }
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DeleteActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", EXITDATA_GetNextPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObj);

extern int InitIcoMisc(void *a0);
extern int D_00629C90;
extern void func_0019A4B8(void *a0, int a1, int a2);

void ACTGame_SetActors_Debug(void *a0) {
    int r = InitIcoMisc(a0);
    func_0019A4B8(a0, D_00629C90, r);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryConnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryDisconnectHand);

extern void *subCommonIdle(void *a0);
extern int Draw2DLineSeg_Start(int a0);
extern void ReleaseItem(int a0, void *a1);
extern void func_00240038(void *a0, void *a1, float a2);
extern int D_00271240[];
extern float D_0028E614;
extern char D_0062C3C8[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand_WithMail);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCheckView);

extern int *ContinueCorrectPosition(int *a0);
extern void GetRootMatrixByDObj(char *a0, char *a1);
extern float HandyCamera_TargetMoveType(int *a0, int a1);
extern float before_DrawLine(void *a0, void *a1);
extern void func_0018A1D8(float *a0, float *a1, int a2);
extern void *func_0018A370(void);
extern float D_0028E618[];
extern float D_00628DEC;
extern void *D_00629DE4;
extern void *D_00629DE8;

void ACTGameView_Loop(void)
{
    float buf0[4];
    float buf1[4];
    int buf2[4];
    float neg1;
    void *p;
    int q;
    float e;

    if (D_00629DE4 != 0 && D_00629DE8 != 0) {
        GetRootMatrixByDObj((char *)buf0, (char *)D_00629DE4);
        GetRootMatrixByDObj((char *)buf1, (char *)D_00629DE8);
        if (!(HandyCamera_TargetMoveType((int *)buf0, (int)buf1) < D_00628DEC)) {
            if (!(0.0f < before_DrawLine(buf2, ContinueCorrectPosition((int *)D_00629DE8)))) {
                neg1 = -1.0f;
                func_00240038(buf0, func_0018A370(), neg1);
                func_00240038(buf1, ContinueCorrectPosition((int *)D_00629DE8), neg1);
                e = D_0028E618[0];
                q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
                func_0018A1D8(buf0, buf1,
                              (int)(e * (float)q / 60.0f));
            }
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_LwsEffectProcess);

extern void ACTGame_LwsEffectProcess(void *ctx);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern char D_00552200[];
extern char D_0062C3C0[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", _ACTGame_SearchGObj);


extern void *D_00629DE4;

int ACTLookTarget_Exec(char *a0) {
    long long v;
    if (a0 == 0) {
        goto ret0;
    }
    if (a0 != D_00629DE4) {
        goto ret0;
    }
    a0 = *(char **)(a0 + 0x164);
    if (a0 == 0) {
        goto ret0;
    }
    v = *(long long *)(a0 + 0x20);
    v = v << 15;
    return (int)(v >> 32) & 1;
ret0:
    return 0;
}

void ACTParaStatus_Clear(int a0) {
    GOBJ_SUB(a0)->f_534 = 1;
    GOBJ_SUB(a0)->f_53C = 1;
    GOBJ_SUB(a0)->f_538 = 1;
    GOBJ_SUB(a0)->f_7C = 1;
}

void ACTParaStatus_Exec(void *a0) {
    GOBJ_SUB(a0)->f_534 = 0;
    GOBJ_SUB(a0)->f_53C = 0;
    GOBJ_SUB(a0)->f_538 = 0;
    GOBJ_SUB(a0)->f_7C = 0;
}

typedef struct { char _[0x186]; unsigned short f186; char _pad[8]; } ACTCharStat;
extern ACTCharStat D_0055DA10[];

int _ACTCharStatus_Clear(void *a0) {
    ACTCharStat *t = D_0055DA10;
    int idx = GOBJ_SUB(a0)->f_490;
    return t[idx].f186 & 7;
}

int GetSkeltonOrient(void *a0, void *a1) {
    int i0 = (*(int **)((char *)a0 + 0x15C))[0x490 / 4];
    int i1 = (*(int **)((char *)a1 + 0x15C))[0x490 / 4];
    ACTCharStat *e0 = &D_0055DA10[i0];
    ACTCharStat *e1 = &D_0055DA10[i1];
    int b0 = (*(unsigned int *)((char *)e0 + 0x188) >> 15) & 1;
    int b1 = (*(unsigned int *)((char *)e1 + 0x188) >> 15) & 1;
    return b0 & b1;
}

extern int D_0055A2D8[][10];
extern void func_001433F0(int idx, char *tmp_a, char *tmp_b);
extern void disp_memory_partition_bar(char *self, char *other, int v, char *tmp_a, char *tmp_b);

void ACTGame_InnerVelocityUpdate(char *self, char *other, int idx)
{
    char tmp_a[0x10];
    char tmp_b[0x10];
    func_001433F0(idx, tmp_a, tmp_b);
    disp_memory_partition_bar(self, other, D_0055A2D8[idx][9], tmp_a, tmp_b);
}

extern void func_00260568(void *a0, int a1, int a2);
extern float D_00628DF0;
extern void func_00240038(void *a0, void *a1, float a2);

void ACTGame_BeforeFunc(int *a0, int a1, void *a2, int a3) {
    char buf0[0x10];
    char buf1[0x10];
    func_00260568(buf1, 0, 0x10);
    *(float *)(buf1 + 4) = (float)a3 * D_00628DF0 / 180.0f;
    func_00240038(buf0, a2, -1.0f);
    disp_memory_partition_bar((char *)a0[2], (char *)a0[3], a1, buf0, buf1);
}

int FunctionAboutClingedStatus(void *a0) {
    float f = *(float *)(*(char **)((char *)a0 + 0x164) + 0x1D0);
    if (f <= 20.0f) {
        return 1;
    }
    return 0;
}

extern void *D_00629DE8;
int ACTEnvGetTest(void) {
    void *q;
    if (D_00629DE8 == 0) return 0;
    q = *(void **)((char *)D_00629DE8 + 0x164);
    return (int)(*(unsigned long long *)((char *)q + 0x18) >> 36) & 1;
}

extern int DebugDisp1CollisionWithColor(void *a0, void *a1);

/* The engine stores component floats through an int/float union so the
 * float stores may-alias the surrounding int traffic (single swc1, no
 * -fno-strict-aliasing override). */
typedef union { int i; float f; } IntFloat;

void ActOrientTest(float *dst, char *obj, void *a2)
{
    int idx = DebugDisp1CollisionWithColor(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}

extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void func_0023FE98(void *a0, void *a1);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void SetRootMatrixWithTransOffsetByDObj(void *a0, void *a1, void *a2, float a3);

void GetGirlHandlinkClInfo(void *a0, void *a1, void *a2, float farg0, float farg1) {
    float buf0[4];
    float buf18[4];
    float buf16[4];

    ActOrientTest(buf0, a0, a1);
    func_00240008(buf16, a2, buf0);
    if (farg1 < MatrixDrive_GetTurnYAngleXZ(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        func_0023FE98(buf16, buf16);
        func_00240038(buf16, buf16, farg1);
        func_0023FFF0(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *) ((char *) a2 + 4)) {
            buf18[1] = *(float *) ((char *) a2 + 4);
        }
        SetRootMatrixWithTransOffsetByDObj(a0, a1, buf18, 1.0f);
        return;
    }
    SetRootMatrixWithTransOffsetByDObj(a0, a1, a2, farg0);
}


extern int D_006A3F70[];

void hand_able_connect(void) {
    D_006A3F70[0x12C] = 0;
    D_006A3F70[0x12D] = 0;
}

void ACTGame_CommonLoop(char *a0)
{
    long long mask1 = ~((long long)0x800 << 32);
    long long mask2 = ~((long long)0x1000 << 32);
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p = *p & mask1 & mask2;
}

void GetOtherStageGirlOrient(void *a0) {
    long long *p = (long long *)((char *)*(void **)((char *)a0 + 0x164) + 0x18);
    *p |= (long long)0x8000 << 28;
    *p |= (long long)0x8000 << 29;
}

extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void GetTarget(void)
{
    char *s = *(char **)((char *)D_00629DE8 + 0x164);
    _ACTGame_SearchGObj(D_00629DE8, 0, 4, 6, D_00629DE4, 0, 0);
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 5, D_00629DE8, 0, 0);
    *(long long *)(s + 0x18) |= (long long)0x8000 << 21;
}

void ACTLookTargetSystem_Exec(void)
{
    char *s = *(char **)((char *)D_00629DE8 + 0x164);
    _ACTGame_SearchGObj(D_00629DE8, 0, 4, 0, 0, 0, 0);
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 0, 0, 0, 0);
    *(long long *)(s + 0x18) &= ~((long long)0x8000 << 21);
}

void ACTItemThrow(float *a0, float *a1)
{
    float *q = (float *)((int *)D_00629DE4)[0x59];
    a0[0] = q[0x4F0/4];
    a0[1] = q[0x4F4/4];
    a0[2] = q[0x4F8/4];
    a1[0] = q[0x4B0/4];
    a1[1] = q[0x4B4/4];
    a1[2] = q[0x4B8/4];
}

int ACTItemWatchMotion(void)
{
    int *player = D_00629DE4;
    unsigned int state = *(int *)(*(char **)((char *)player + 0x164) + 0x30);
    void *o;
    unsigned long *b;
    unsigned long bit;
    int rv;
    if (state == 0) {
        goto ret0;
    }
    if (state < 4) {
        goto lt4;
    }
    if (state >= 0x4D) {
        goto ret0;
    }
    if (state < 0x4B) {
        rv = 0;
        goto end;
    }
    return 1;
lt4:
    o = D_00629DE8;
    if (o != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
bittest:
    b = *(unsigned long **)((char *)o + 0x164);
    bit = (b[3] >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
end:
    return rv;
}

int ACTGame_InsertCamera_GirlIsPinch(void)
{
    void *g = D_00629DE8;
    AGState *a = *(AGState **)((char *)g + 0x164);
    unsigned int type = a->f_30;
    unsigned long bit;
    int rv;
    if (type == 0x45) {
        return 1;
    }
    if (type >= 0x46) {
        goto upper;
    }
    if (type >= 4) {
        goto ret0;
    }
    if (type == 0) {
        goto ret0;
    }
    if (g != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
upper:
    if (type >= 0x4F) {
        goto ret0;
    }
    if (type < 0x4D) {
        goto ret0;
    }
    return 1;
bittest:
    bit = (*(unsigned long *)((char *)a + 0x18) >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
    return rv;
}

/* NEAR-MISS (rc21, W3 convergence). LOGIC + STRUCTURE recovered. Dev shape:
 *   int updateHMC(void) {
 *       char *mgr = D_00629DE4;
 *       int state, idx;
 *       if (mgr == 0) return 0;
 *       state = *(int *)(*(int *)(mgr + 0x164) + 0x30);
 *       if (state != 0x4B && state != 0x55) return 0;         // §3.3 beql(0x4B)/bnel(0x55)
 *       idx = *(int *)(*(int *)(mgr + 0x15C) + 0x490);
 *       return ((AGHmc *)(idx * 0x190 + (char *)D_0055DA10_a))->f_15C == 1;
 *   }
 * Matched: gp_rel D_00629DE4 null test, ->f_164->f_30 state load, the beql(state==0x4B)
 * / bnel(state==0x55) OR pair (with mgr->f_15C reloaded in the beql delay), idx =
 * (mgr->f_15C)->f_490, D_0055DA10 stride-0x190 index + mult. Residual (rc21) is the
 * multi-exit FUNNEL + branch-likely + bool form: ROM funnels ALL exits through a shared
 * .L48F64 (v0=0, falls into) .L48F68 (`jr v0`): the null path -> L48F64, state-fail ->
 * L48F68 (v0=0), and the final `->f_15C == 1` is a BRANCH `beq val,1,.L48F68; addiu v0,1`
 * (v0 funneled). gcc instead: `bnel mgr,zero` (branch-likely) + a SEPARATE early `jr ra`
 * for the null-return, and computes `== 1` ARITHMETICALLY (`xori v0,1; sltiu v0,1`).
 * Addressing: ROM keeps &D_0055DA10 as the base with `lw 0x15C(base)`; gcc folds
 * &D+0x15C into the %lo displacement. NEXT LEVER: §8.3 goto-funnel all returns through
 * one label so v0 carries the result and the ==1 stays a branch; block the branch-likely
 * null exit. NOT a floor. */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", updateHMC);

void RequestChangeHandMode(float *a0, float *a1)
{
    float *q = (float *)((int *)D_00629DE4)[0x59];
    a0[0] = q[0x500/4];
    a0[1] = q[0x504/4];
    a0[2] = q[0x508/4];
    a1[0] = q[0x510/4];
    a1[1] = q[0x514/4];
    a1[2] = q[0x518/4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTNotNeedCameraOffset);

/* per-action-state attribute table (stride 0x50), indexed by AGState.f_30 */
typedef struct { char _pad0[0x4C]; unsigned int f_4C; } ActStateAttr;
extern ActStateAttr D_00557188[];

int ACTGameCollisionOn(void *a0)
{
    AGState *s = *(AGState **)((char *)a0 + 0x164);
    if (a0 == D_00629DE4) {
        unsigned int off = s->f_30 * 0x50;
        off += (unsigned int)D_00557188;
        if ((((ActStateAttr *)off)->f_4C >> 6) & 1) {
            return s->f_180;
        }
    }
    return 0;
}

extern int ACTGame_DisconnectHand(void);
extern int dispInsectNet(int *self);

int ACTGameCollisionOff(int *self)
{
    unsigned long new_var;
    int ret = 0;
    new_var = ACTGame_DisconnectHand();
    if (new_var != 0)
    {
        ret = dispInsectNet(self);
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CheckItemMotion);

extern void func_00260568(void *dst, int val, int len);
extern void func_00240080(void *buf, int x);
extern void ClipWallBoxStop(void *buf);
extern void fzMagnitudefv(void *out, int n, void *vec);

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    float _80;
    char _84[0x04];
    int _88;
    char _8c[0x0C];
    int _98;
    char _9c[0x24];
} HandWork;

int ACTGame_CheckHandMotion(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget, int *flagout) {
    HandWork work;
    int flag;
    int rv;
    int cnt;

    func_00260568(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    func_00240080(&work, (int) hand0);
    func_00240080((char *) &work + 0x10, (int) hand1);
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 0;
    }
    ClipWallBoxStop(&work);
    if (flagout != 0) {
        *flagout = work._98;
    }
    cnt = work._88;
    if (cnt == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *) ((char *) posout + 0) = work._20;
        *(float *) ((char *) posout + 4) = work._24;
        *(float *) ((char *) posout + 8) = work._28;
    }
    if (cnt != 0 && magtarget != 0) {
        fzMagnitudefv(magtarget, cnt, &work._80);
    }
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 1;
    }
    return rv & 0xFF;
}


extern void func_00260568(void *dst, int val, int n);
extern void func_00240080(void *buf, int x);
extern void ClipWallBoxStop(void *buf);

/* unaligned 64-bit copy via packed struct (ldl/ldr + sdl/sdr) */
typedef struct { long long w; } __attribute__((packed)) U64ag;

int ACTGame_StageChangeGObjID(int a0, int a1, int *a2, char *a3)
{
    char buf[0xC0];
    func_00260568(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    func_00240080(buf, a0);
    func_00240080(buf + 0x10, a1);
    ClipWallBoxStop(buf);
    if (a2 != 0) {
        *a2 = *(int *)(buf + 0x98);
    }
    if (a3 != 0) {
        *(U64ag *)a3 = *(U64ag *)(buf + 0x80);
        *(int *)(a3 + 8) = *(int *)(buf + 0x88);
    }
    return *(int *)(buf + 0x88) != 0;
}

extern void ChangeFieldCollisionDebugMode(void *buf);
extern int D_0062A558;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObjDirect);


extern int ClipWallFieldCheckCB(void *buf);
extern int func_001668B0(int a0, int a1);
extern int D_0062A55C;

typedef struct { char _pad[0x15C]; char *unk15C; } FlagObj;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_LIFEPINCH);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", SetDirectRootPositionWithNodePointLimit);

int ACTGameView_Init(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006A3F70[0x4B0 / 4]; i++) {
        if (D_006A3F70[i] == a1) {
            return *((unsigned char *)&D_006A3F70[i] + 0x190);
        }
    }
    return 0;
}

int ACTCharctrl_Lock(int a0, int a1) {
    int i;
    for (i = 0; i < D_006A3F70[0x12C]; i++) {
        if (D_006A3F70[i] == a1) {
            return *(unsigned char *)((char *)D_006A3F70 + i * 4 + 0x320);
        }
    }
    return 0;
}

extern char D_0060AF70[];

int ACTCharctrl_Unlock(int a0)
{
    char *base;
    int rv;
    if (a0 != 0) {
        base = D_0060AF70;
        base = base - (-(checkHit(a0) * 0x24));
        rv = *(int *)(base + 0x1C);
    } else {
        rv = 0;
    }
    return rv;
}

int ACTGame_ConnectHand(char *a0) {
    int r = 0;
    void *next = *(void **)(*(char **)(a0 + 0x164) + 0x130);
    if (next == 0 || checkHit(next) == 0) {
        r = 1;
    }
    return r;
}

extern int checkHit(void);
int ACTGame_DisconnectHand(void) {
    return checkHit() == 1;
}

extern const float D_0063226C_flt[] __asm__("D_0062C3D4");
extern int *isysGObjSearchFromObjLayoutID(int);
extern int *ContinueCorrectPosition(int *);
extern float HandyCamera_TargetMoveType(int *, int);
extern int *isysGObjSearchFromObjKindID_begin(int *);

int *PAIR_GetPosition_BOY(int a0, int a1) {
    float best_val = D_0063226C_flt[0];
    int *best = 0;
    int *node;

    node = isysGObjSearchFromObjLayoutID(a1);
    if (node != 0) {
        do {
            float val = HandyCamera_TargetMoveType(ContinueCorrectPosition(node), a0);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
    return best;
}

void PAIR_IsStatus_BOY_PULL(void *a0) {
    AGState *p = *(AGState **)((char *)a0 + 0x164);
    p->f_88 = 0;
    p->f_90 = 0;
    p->f_8C = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_190;  /* 0x190 */
    unsigned int       f_320;  /* 0x320 */
    unsigned int       f_4B0;  /* 0x4B0 */
    unsigned int       f_4B4;  /* 0x4B4 */
} S_006A3F70;  /* stride 0x4 */

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0027DED0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005523F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552430;  /* stride 0x4 */

/* end struct shapes */
