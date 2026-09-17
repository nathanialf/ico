#include "common.h"
#include "itou_common.h"
#include "sugiCommon.h"
#include "act_bird.h"
#include "memory.h"
#include "pad.h"
#include "gobj.h"
#include "act.h"
#include "lightning.h"
#include "DisplayP2O.h"
#include "StageAnimation.h"
#include "geometryManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "tableSin.h"
#include "wireLetter.h"
#include <math.h>
#include <libvu0.h>
#include <string.h>
#include <stdio.h>
#include "typedef.h"

/* kept local: this TU's uses of ExecMotionOrient do not fit the prototype in motionOrientManager.h */
extern void ExecMotionOrient();
/* kept local: this TU's uses of iosOmSendMail do not fit the prototype in obj_manager.h */
extern void iosOmSendMail(void *a0);
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
/* kept local: this TU's uses of SetMotionRequest do not fit the prototype in motionOrientManager.h */
extern int SetMotionRequest(void *a0, int id, void *work);
extern char D_00555788[];
extern void *D_0063A438;
/* kept local: this TU's uses of InitMotionOrient do not fit the prototype in motionOrientManager.h */
extern void InitMotionOrient(void *o, int a1, int a2, int a3, int a4, int a5);

inline float vector_angle_degree(void *a0, void *a1)
{
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a0);
    sceVu0Normalize(v1, a1);
    return radians_to_degrees(acosf(sceVu0InnerProduct(v0, v1)));
}

void interp_vector_sa(float *dst, float *a, float *b, float sa)
{
    float na[4];
    float nb[4];
    float va[4];
    float vb[4];
    float sum[4];
    float ang;
    /* fraction of the full angle that the `sa` step covers; a separate local
       from the parameter is what ROM's register file shows (`sa` dies at the
       divide, and this one lives on through the three GetTableSin calls). */
    float rate;

    sceVu0Normalize(na, a);
    sceVu0Normalize(nb, b);
    ang = acosf(sceVu0InnerProduct(na, nb));
    if (ang < sa) {
        sceVu0CopyVector(dst, nb);
        return;
    }

    rate = sa / ang;
    sceVu0ScaleVectorXYZ(va, na, GetTableSin((short)((1.0f - rate) * ang * 10430.378f)));
    sceVu0ScaleVectorXYZ(vb, nb, GetTableSin((short)(rate * ang * 10430.378f)));
    sceVu0AddVector(sum, va, vb);
    sceVu0DivVector(dst, sum, GetTableSin((short)(ang * 10430.378f)));
}

/* kept local: this TU's uses of _GetLengthXZ do not fit the prototype in Matrix.h */
extern float _GetLengthXZ(void *a, void *b);

typedef struct BirdMailEntry {
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} BirdMailEntry;

typedef struct BirdMailQueue {
    /* 0x00 */ int unk0;
    /* 0x04 */ int num;
    /* 0x08 */ BirdMailEntry e[1];
} BirdMailQueue;

typedef struct {
    float f[8];
} BirdMotBlock;

void birdBeforeFunc(char *self)
{
    char *act = *(char **)(self + 0x164);
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    float there[4];
    float here[4];
    int i;
    BirdMailQueue *q = (BirdMailQueue *)(self + 0x54);

    for (i = 0; i < q->num; i++) {
        BirdMailEntry *e = &q->e[i];
        float len;

        GetRootPosition(there, e->data);
        GetRootPosition(here, self);
        len = _GetLengthXZ(there, here);
        switch (e->mail) {
        case 0x1A7:
            if (len < 200.0f) {
                *(char *)(w + 0x10) = 1;
                GetRootPosition(w + 0x20, e->data);
            }
            break;

        case 0x1A8:
            if (len < 250.0f) {
                *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            }
            break;

        case 0xA: {
            int st = *(int *)(*(int *)(self + 0x15C) + 0x4A0);

            if (st >= 0x473 && st <= 0x475) {
                *(int *)(act + 0x130) = SetMotionRequest(self, 0x142, act + 0x620);
            }
            break;
        }

        case 0x7:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A:
        case 0x1B:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A3:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A4:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A5:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A6:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;
        }
    }
    q->num = 0;
    *(BirdMotBlock *)(act + 0x620) = *(BirdMotBlock *)(*(int *)(self + 0x15C) + 0x180);
}

/* --- act_bird.c's own small helpers, census rows 74-107 -----------------
 * SRCFILE.TXT attributes instructions inside subBirdBrainMain to
 * act_bird.c lines 74/75, 79/80, 86, 91, 96 and 104-106: five helper
 * bodies that are only ever inlined, so none of them has a MAIN.MAP
 * symbol and the names below are ours, chosen for what the rows do. */

extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixY(void *dst, void *src, float ang);
extern void sceVu0InversMatrix(void *dst, void *src);
extern void apply_matrix_w1(void *dst, void *m, void *src);

/* rows 74-75: a point 100 units along `dir` from `p`. */
static __inline__ void point_ahead(float *dst, float *p, float *dir)
{
    float v[4];

    sceVu0ScaleVector(v, dir, 100.0f);
    sceVu0AddVector(dst, p, v);
}

/* row 80 */
static __inline__ float rand_range(float a, float b)
{
    return random_unit() * (b - a) + a;
}

/* row 86 */
static __inline__ float rand_flip(float v)
{
    if (random_unit() <= 0.5f) {
        v = -v;
    }
    return v;
}

/* row 91 */
static __inline__ float rand_range_rad(float a, float b)
{
    return degrees_to_radians(rand_range(a, b));
}

/* row 96 */
static __inline__ float rand_small_turn(void)
{
    return degrees_to_radians(rand_flip(rand_range(1.0f, 2.0f)));
}

/* rows 104-106: turn `v` about Y by `ang` radians. */
static __inline__ void rotate_y(float *v, float ang)
{
    float m[16];
    float mr[16];

    sceVu0UnitMatrix(m);
    sceVu0RotMatrixY(mr, m, ang);
    apply_matrix_w1(v, mr, v);
}

void trans_bird(void *self, float *w)
{
    float down[4] = {0.0f, -1.0f, 0.0f, 0.0f};
    float pos[4];
    float dir[4];
    float fwd[4];
    float dv[4];

    w[4] = (w[0] - w[2]) * w[6] + w[2];
    w[5] = (w[1] - w[3]) * w[6] + w[3];
    w[6] = w[6] + w[7];
    if (w[6] > 1.0f) {
        w[6] = 1.0f;
    }
    GetRootPosition(pos, self);
    _GetMotionDirection(dir, self);
    sceVu0ScaleVectorXYZ(fwd, dir, w[4] * 0.7f);
    sceVu0ScaleVectorXYZ(dv, down, w[5]);
    sceVu0AddVector(fwd, fwd, dv);
    sceVu0AddVector(pos, pos, fwd);
    SetRootPosition(self, pos);
}

/* The wall/floor clip request this TU hands to ClipWall and ClipFloor: the
 * same 0xC0 record the other actor TUs carry, with the two result words the
 * bird reads and the contact normal at 0xA0. */
typedef struct BirdClipWork {
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ float pos[4];
    /* 0x30 */ char _30[0x40];
    /* 0x70 */ float radius;
    /* 0x74 */ char _74[0x14];
    /* 0x88 */ int wallHit;
    /* 0x8C */ char _8c[0x08];
    /* 0x94 */ int floorHit;
    /* 0x98 */ char _98[0x08];
    /* 0xA0 */ float normal[4];
    /* 0xB0 */ char _b0[0x10];
} BirdClipWork;

extern void ClipWall(void *w);
extern void ClipFloor(void *w);
extern int GetFloorAttribute(void *w);
extern void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
extern void pbga_start(void *slot, int n);
extern void _CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void sceVu0CopyVector(void *dst, void *src);
extern float _GetLength(void *a, void *b);
extern void debug_StdPrintfDummy(const char *fmt, ...);
extern int IdentityQuaternion[];
extern int D_0028F4C0[];
extern int matrixptr;
extern char *D_00639EC0;
extern int D_0063A064;
extern int D_0063A068;
extern void Debug_WireString_Bird(float *pos, char *fmt, ...);

/* rows 256-263: point the bird `ang` radians round from where it faces. */
static __inline__ void turn_bird(void *self, float ang)
{
    float d[4];

    _GetMotionDirection(d, self);
    rotate_y(d, ang);
    SetMotionDirection(self, d);
}

/* rows 279-288: restart the flap wave from where it currently stands. */
static __inline__ void set_wave(float *w, float a, float b, float step)
{
    w[0] = a;
    w[1] = b;
    w[7] = step;

    w[2] = w[4];
    w[3] = w[5];
    w[6] = 0.0f;
}

/* census: ito/src/act_bird.c subBirdBrainMain, def line 314.
   Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
void subBirdBrainMain(void *volatile gobj)
{
    float startPos[4];
    float lastPos[4];
    float wave[8];
    float homePos[4];
    float pos[4];
    float dir[4];
    float mtx[4][4];
    char *bw;
    char *act;
    int frames;
    int lastHit;
    int count;
    int ticks;
    int away;
    int lastState;
    int state;
    float sign;
    float yaw;
    float rot;
    float hover;
    float travel;

    bw = *(char **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    frames = 0;

    lastHit = 0;
    count = 1;
    ticks = 0;

    hover = 0.0f;

    yaw = hover;
    rot = hover;
    travel = hover;

    away = 0;

    act = *(char **)((char *)gobj + 0x164);

    _ACTWait(1);

    GetRootPosition(startPos, gobj);
    GetRootPosition(lastPos, gobj);

    lastState = *(int *)(*(int *)((char *)gobj + 0x15C) + 0x4A0);
    /* Vestigial in the shipped build: the loop opens by reading the same field
       into `state`, so everything but the volatile GObj load is dead here.  The
       ROM keeps that load (act_bird.c:349 in SRCFILE.TXT, the second
       `lw $v1,0($sp)` of the loop preheader), which is what proves the second
       read was written. */
    state = *(int *)(*(int *)((char *)gobj + 0x15C) + 0x4A0);
    while (1) {
        int changed;
        int hit;
        int hold;
        int blocked;
        int noAvoid;
        float phase;

        state = *(int *)(*(int *)((char *)gobj + 0x15C) + 0x4A0);
        phase = *(float *)(*(int *)((char *)gobj + 0x15C) + 0x4AC);
        hit = *(int *)(*(int *)((char *)gobj + 0x15C) + 0x4CC);

        changed = 0;

        blocked = 0;

        sign = 1.0f;

        GetRootPosition(pos, gobj);
        _GetMotionDirection(dir, gobj);
        GetRootMatrix(mtx, gobj);

        if (state != lastState) {
            count = 1;
            changed = 1;

            ticks = 0;
        } else {
            if (lastHit != 0) {
                count++;
            }
        }

        hold = (changed != 0 || hit != 0);
        ticks++;

        noAvoid = 0;
        if (bw[0x10] != 0) {
            switch (state) {
            case 1139:
            case 1140:
            case 1141:
            case 1142:
                break;
            default:
                noAvoid = 1;
                break;
            }
        }

        if (noAvoid == 0 && state != 1134 && state != 1138) {
            BirdClipWork wf;

            float len = 100.0f;

            float rad = 50.0f;
            float fwd;
            BirdClipWork wr;
            BirdClipWork wl;
            float tr[4];
            float tl[4];
            float avoid[4];
            float nd[4];
            float nrm[4];

            if (state == 1139 || state == 1140) {
                fwd = 300.0f;
            } else {
                fwd = 50.0f;
                len = 50.0f;
                rad = 10.0f;
            }

            wf.radius = rad;
            CopyVector(wf.from, pos);
            sceVu0ScaleVectorXYZ(wf.to, mtx[2], fwd);
            sceVu0AddVector(wf.to, wf.to, pos);
            ClipWall(&wf);

            wr.radius = rad;
            CopyVector(wr.from, pos);
            sceVu0ScaleVectorXYZ(tr, mtx[0], len);
            sceVu0AddVector(wr.to, pos, tr);
            ClipWall(&wr);

            wl.radius = rad;
            CopyVector(wl.from, pos);
            sceVu0ScaleVectorXYZ(tl, mtx[0], -len);
            sceVu0AddVector(wl.to, pos, tl);
            ClipWall(&wl);

            if (wf.wallHit != 0 || wr.wallHit != 0 || wl.wallHit != 0) {
                blocked = 1;

                if (wr.wallHit != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tr, -1.0f);
                    sign = -1.0f;
                } else if (wl.wallHit != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tl, -1.0f);
                    sign = 1.0f;
                } else {
                    sceVu0Normalize(nrm, wf.normal);

                    CopyVector(avoid, nrm);
                    sign = 1.0f;
                    if (sceVu0InnerProduct(mtx[0], nrm) < 0.0f) {
                        sign = -1.0f;
                    }
                }

                travel = 0.0f;

                rot = sign * rand_range_rad(1.0f, 2.0f);
                interp_vector_sa(nd, dir, avoid, degrees_to_radians(5.0f));
                SetMotionDirection(gobj, nd);
            }
        }

        switch (state) {
        case 1137:
            Debug_WireString_Bird(pos, "EAT");
            if (hold != 0) {
                yaw = rand_range_rad(10.0f, 50.0f) / 3.0f;
                if (blocked != 0) {
                    yaw = yaw * sign;
                } else if (random_unit() <= 0.5f) {
                    yaw = -yaw;
                }
            }
            if (phase >= 6.0f && phase < 9.0f) {
                turn_bird(gobj, yaw);
            }

        case 1134:
            if ((char *)gobj == D_00639EC0) {
                Debug_WireString_Bird(pos, "STOP TGT");
                break;
            }
            if (hit != 0) {
                Debug_WireString_Bird(pos, "STOP FIN");

                if (bw[0x10] != 0) {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 321, act + 0x620);
                        break;
                    }
                    if (random_unit() <= 0.5f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 317, act + 0x620);
                        break;
                    }
                    *(int *)(act + 0x130) = SetMotionRequest(gobj, 318, act + 0x620);
                    break;
                } else {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 321, act + 0x620);
                        break;
                    }
                    if (r < 0.4f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 320, act + 0x620);
                        break;
                    }
                    if (r < 0.7f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 319, act + 0x620);
                        break;
                    }
                    if (random_unit() <= 0.7f) {
                        *(int *)(act + 0x130) = SetMotionRequest(gobj, 317, act + 0x620);
                        break;
                    }
                    *(int *)(act + 0x130) = SetMotionRequest(gobj, 318, act + 0x620);
                    break;
                }
            } else {
                char buf[1024];

                sprintf(buf, "STOP NO FIN %d,%1.1f",
                        *(int *)(*(int *)((char *)gobj + 0x15C) + 0x4A0),
                        *(float *)(*(int *)((char *)gobj + 0x15C) + 0x4AC));
                Debug_WireString_Bird(pos, buf);
                break;
            }

        case 1135:
        case 1136:
            Debug_WireString_Bird(pos, "STEP");
            if (hold != 0) {
                int q = 3;

                if (bw[0x10] != 0) {
                    float v[4];

                    yaw = rand_range_rad(40.0f, 70.0f) / q;

                    sceVu0SubVector(v, pos, bw + 0x20);
                    if (sceVu0InnerProduct(mtx[0], v) < 0.0f) {
                        yaw = -yaw;
                    }
                } else {
                    yaw = rand_range_rad(60.0f, 90.0f) / q;
                    if (blocked != 0) {
                        yaw = yaw * sign;
                    } else if (random_unit() <= 0.5f) {
                        yaw = -yaw;
                    }
                }
            }
            if (phase >= 3.0f && phase < 6.0f) {
                turn_bird(gobj, yaw);
            }
            if (hit == 0) {
                break;
            }
            *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);

            bw[0x10] = 0;
            break;

        case 1138:
            Debug_WireString_Bird(pos, "GROOM");

            *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);
            break;

        case 1139:
            Debug_WireString_Bird(pos, "FLY S");
            if (changed != 0) {
                float a = rand_range(180.0f, 300.0f) / 9.0f;
                float b = rand_range(120.0f, 230.0f) / 9.0f;

                wave[4] = 0.0f;
                wave[5] = 0.0f;
                set_wave(wave, a, b, 0.2f);
                rot = rand_small_turn();

                travel = 0.0f;
                CopyVector(homePos, pos);
                away = 0;
            }

            if (phase >= 7.0f) {
                trans_bird(gobj, wave);
                turn_bird(gobj, rot);
            }
            *(int *)(act + 0x130) = SetMotionRequest(gobj, 321, act + 0x620);
            break;

        case 1140:
            Debug_WireString_Bird(pos, "FLY");
            if (changed != 0) {
                if (random_unit() <= 0.5f) {
                    pbga_start(bw + 0x30, 512);
                    _CopyVector(*(char **)(bw + 0x30) + 0x20, pos);
                    CopyQuaternion(*(char **)(bw + 0x30) + 0x30, IdentityQuaternion);
                }
            }
            if (changed != 0 || hover >= 80.0f) {
                float a = rand_range(72.0f, 120.0f) / 3.0f;
                float b = rand_range(48.0f, 92.0f) / 3.0f * 0.5f;
                float p = 0.5f;

                if (pos[1] < homePos[1] - 400.0f) {
                    p = 1.0f;
                }
                if (homePos[1] + 400.0f < pos[1]) {
                    p = 0.0f;
                }
                if (random_unit() <= p) {
                    b = -b;
                }

                set_wave(wave, a, b, 1.0f / 60.0f);
                hover = wave[6];
            }

            if (travel > 100.0f) {
                rot = rand_small_turn();
                travel = 0.0f;
            }

            if (away == 0 && _GetLengthXZ(pos, homePos) > 2000.0f) {
                away = 1;
            }

            if (away != 0) {
                float v[4];

                if (_GetLengthXZ(pos, homePos) < 800.0f) {
                    away = 0;
                } else {
                    sceVu0SubVector(v, homePos, pos);

                    if (vector_angle_degree(v, dir) > 5.0f) {
                        rot = degrees_to_radians(2.0f);
                        if (sceVu0InnerProduct(v, mtx[0]) < 0.0f) {
                            rot = degrees_to_radians(-2.0f);
                        }
                    }

                    travel = 0.0f;
                }
            }

            trans_bird(gobj, wave);
            turn_bird(gobj, rot);

            travel = travel + 1.0f;
            GetRootPosition(pos, gobj);
            _GetMotionDirection(dir, gobj);

            {
                float up[4];
                float ahead[4];
                BirdClipWork cf;
                float sv[4];
                float im[4][4];
                float p2[4];
                float sv2[4];
                float sx;
                float sy;
                int attr;

                memset(up, 0, 16);
                up[1] = 180.0f;

                sceVu0ScaleVector(ahead, dir, 100.0f);
                CopyVector(cf.from, pos);
                sceVu0AddVector(cf.to, cf.from, up);
                sceVu0AddVector(cf.to, cf.to, ahead);
                ClipFloor(&cf);
                attr = GetFloorAttribute(&cf);
                if (cf.floorHit != 0 && attr != 64 && attr != 80) {
                    *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);
                }

                apply_matrix_w1(sv, (char *)matrixptr + 0x100, pos);
                sv[0] = sv[0] / sv[3] - 2048.0f;
                sv[1] = sv[1] / sv[3] - 2048.0f;

                sx = sv[0] / (D_0063A064 / 2);
                sy = sv[1] / (D_0063A068 / 2);
                if (sv[3] > 0.0f && __builtin_fabsf(sx) < 0.6f && sy > -1.3f && sy < 0.5f) {
                    float dy;

                    sceVu0InversMatrix(im, (char *)matrixptr + 0x80);
                    point_ahead(p2, pos, im[1]);
                    apply_matrix_w1(sv2, (char *)matrixptr + 0x100, p2);
                    sv2[1] = sv2[1] / sv2[3] - 2048.0f;
                    dy = __builtin_fabsf(sv2[1] - sv[1]) / D_0063A068;

                    if (dy > 0.5f &&
                        (*(int *)(bw + 0x30) == 0 || ((float *)*(int *)(bw + 0x30))[1] > 100.0f)) {
                        pbga_start(bw + 0x30, 512);
                        _CopyVector(*(char **)(bw + 0x30) + 0x20, pos);
                        CopyQuaternion(*(char **)(bw + 0x30) + 0x30, IdentityQuaternion);
                    }
                }
            }

            hover = hover + 1.0f;
            break;

        case 1141:
            Debug_WireString_Bird(pos, "FLY E1");
            if (changed != 0) {
                float a = rand_range(340.0f, 565.0f) / 28.0f * 0.6f;
                float b = -rand_range(225.0f, 250.0f) / 28.0f * 0.6f;

                set_wave(wave, a, b, 1.0f / 7.0f);
                if (random_unit() <= 0.5f) {
                    pbga_start(bw + 0x30, 512);
                    _CopyVector(*(char **)(bw + 0x30) + 0x20, pos);
                    CopyQuaternion(*(char **)(bw + 0x30) + 0x30, IdentityQuaternion);
                }
            }

            trans_bird(gobj, wave);

            if (count >= 3) {
                *(int *)(act + 0x130) = SetMotionRequest(gobj, 321, act + 0x620);
            }
            break;

        case 1142: {
            float p[4];
            float q[4];
            BirdClipWork cd;

            Debug_WireString_Bird(pos, "FLY E2");
            if (changed != 0) {
                wave[5] = 0.0f;
                set_wave(wave, 0.0f, 0.0f, 0.2f);
            }

            if (phase >= 0.0f && phase < 5.0f) {
                trans_bird(gobj, wave);
            }

            GetRootPosition(p, gobj);
            CopyVector(cd.from, p);
            GetRootPosition(cd.to, gobj);
            cd.to[1] = cd.to[1] + 50.0f;
            ClipFloor(&cd);
            if (cd.floorHit != 0) {
                float lim = -6.0f;

                float y = cd.pos[1] + lim;
                /* Nothing reads `q` again; the ROM emits the store all the
                   same (act_bird.c:793, `swc1 $f0,0x364($sp)`), so the 2001
                   source carried it. */
                q[1] = lim;
                if (y < p[1]) {
                    p[1] = y;
                    SetRootPosition(gobj, p);
                }
            }

            if (hit != 0) {
                *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);
            }
            break;
        }

        default:
            *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);
            break;
        }

        if (state != 1139) {
            float rp[4];

            if ((*(int *)(*(int *)((char *)gobj + 0x15C) + 0x484) & 0x400) ||
                CheckFloorAttribute(gobj, 64) || CheckFloorAttribute(gobj, 80)) {
                GetRootPosition(rp, gobj);
                rp[1] = *(float *)(*(int *)((char *)gobj + 0x15C) + 0x640);
                SetDirectRootPositionNoFitting(gobj, rp);
                *(int *)(act + 0x130) = SetMotionRequest(gobj, 172, act + 0x620);
                EntryStageMultiBgaManager(498, rp, IdentityQuaternion);
            }
        }

        {
            float rp[4];

            GetRootPosition(rp, gobj);
            frames++;
            if (_GetLength(rp, lastPos) < 3.0f) {
            } else {
                frames = 0;
            }

            sceVu0CopyVector(lastPos, rp);
        }

        if (state == 1140 &&
            (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f < (float)frames &&
            (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f < (float)ticks) {
            debug_StdPrintfDummy("bird reset\n");
            InitMotionOrient(gobj, 0x975, 0x9A3, -1, -1, 0x46E);

            SetDirectRootPosition(gobj, startPos);
            *(int *)(act + 0x130) = SetMotionRequest(gobj, 316, act + 0x620);
        }

        lastState = state;

        lastHit = hit;
        _ACTWait(1);
    }
}

inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        Debug_StickControl(gobj);
        _ACTWait(1);
    }
}

inline void subBirdCollision(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        _ACTWait(1);
    }
}

inline void actBirdStart(void *a0)
{
    char *w;

    w = (char *)actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(subBirdBrainMain, 20);
    actCreateSubThread(subBirdControl, 21);
    actCreateSubThread(subBirdCollision, 21);
    *(int *)(w + 0x130) = SetMotionRequest(a0, 0x10E, w + 0x620);
}

/* libvu0 sceVu0MulMatrix; the repo carries it under its vendor placeholder. */

void Debug_WireString_Bird(float *pos, char *fmt, ...)
{
    float m[16];
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;

    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    m[3] = m[7] = m[11] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
    sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    MatrixDrive_PushMatrix();
    vsprintf(buf, fmt, args);
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(buf);
    MatrixDrive_PopMatrix();
    MatrixDrive_PopMatrix();
}

extern char *D_00639ED0;
/* kept local: this TU's uses of CorrectStickInfo do not fit the prototype in boyact.h */
extern int CorrectStickInfo(void *dir, void *stick);

void Debug_StickControl(char *self)
{
    float dir[4];
    char *ext = *(char **)(self + 0x164);

    if (self == D_00639EC0) {
        char *pad = ext + 0x2D8;
        char *stick = ext + 0x338;

        iosPadConnect(pad, 0, 0, ext + 0x1E8);
        iosPadRead(pad);
        iosPadGetStick(pad, stick, 0, 2, 2, 0);
        _GetMotionDirection(dir, self);
        *(int *)(ext + 0x340) = CorrectStickInfo(dir, stick);
        if (*(float *)(ext + 0x34C) > 0.001f) {
            ConvertStickToAbsCoord(ext + 0x120, stick);
        }
    } else if (self == D_00639ED0) {
        iosPadConnect(ext + 0x2D8, 0, 1, ext + 0x1E8);
    } else {
        iosPadConnect(ext + 0x2D8, 0, 1, ext + 0x1E8);
    }
}

void BirdGeo(int a0, int a1, int a2, int a3)
{
    ExecMotionOrient(a0, a1, a2, a3);
}

extern int stage_no;

/* census: ito/src/act_bird.c BirdDL, def line 1024 */
void BirdDL(void *gobj)
{
    char *w;

    p2o_DispVU1Default(gobj);
    w = *(char **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    if (*(int *)(w + 0x30) != 0) {
        if (stage_DispBgAnimation(w + 0x30) != 0) {
            *(int *)(w + 0x30) = 0;
        }
    }
    if (stage_no == 0x54) {
        lightning_test();
    }
}

inline char *InitBirdGeo(char *a0, void *a1)
{
    char *w;

    w = iosMallocDebug(D_0063A438, 0x40, D_00555788, 978);
    memset(w, 0, 0x40);
    CopyVector(w, a1);
    w[0x10] = 0;
    InitMotionOrient(a0, 0x975, 0x9A3, -1, -1, 0x46E);

    *(int *)(*(int *)(a0 + 0x15C) + 0x544) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x54C) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x548) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x550) = 0;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f = random_unit() * 100.0f;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4B0))->f =
        ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f;
    *(int *)(*(int *)(a0 + 0x15C) + 0x4C4) = 0;
    SetLodLevel(a0, 3);
    return w;
}

inline void BirdAI(void) {}

void _ACTSendMailToBird(void *a0, void *a1, void *a2)
{
    iosOmSendMail(a0);
}

inline void _ACTSendMailToBirdAll(void *a0, void *a1)
{
    void *obj = isysGObjSearchFromObjKindID_begin(32);
    while (obj != 0) {
        _ACTSendMailToBird(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
