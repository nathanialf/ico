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
#include "GsBase.h"
#include "Matrix.h"
#include "stageMultiBgaManager.h"
#include "boyact.h"
#include "quaternion.h"
#include "main.h"
#include "fieldCollision.h"
#include "itou_sub.h"
#include "motionOrientManager.h"
#include "ios.h"
#include "debug.h"
#include "obj_manager.h"

static void Debug_StickControl(GObj *self);

#ifdef VERSION_JUN26
static void Debug_WireString_Bird(float *pos, char *str);
#else
static void Debug_WireString_Bird(float *pos, char *fmt, ...);
#endif

inline float vector_angle_degree(void *a, void *b)
{
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a);
    sceVu0Normalize(v1, b);
    return radians_to_degrees(acosf(sceVu0InnerProduct(v0, v1)));
}

static void interp_vector_sa(float *dst, float *a, float *b, float sa)
{
    float na[4];
    float nb[4];
    float va[4];
    float vb[4];
    float sum[4];
    float ang;
    /* fraction of the full angle that the `sa` step covers */
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

#ifdef VERSION_NTSC
void birdBeforeFunc(GObj *self)
{
    Act *act = GOBJ_ACT(self);
    BirdWork *w = GOBJ_SUB(self)->work;
    float there[4];
    float here[4];
    int i;
    GObjMailQueue *q = (GObjMailQueue *)&self->mailBox;

    for (i = 0; i < q->num; i++) {
        GObjMailEntry *e = &q->e[i];
        float len;

        GetRootPosition(there, e->data);
        GetRootPosition(here, self);
        len = _GetLengthXZ(there, here);
        switch (e->mail) {
        case 393:
            if (len < 200.0f) {
                w->scared = 1;
                GetRootPosition(w->scarer, e->data);
            }
            break;

        case 394:
            if (len < 250.0f) {
                act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            }
            break;

        case 10: {
            int st = GOBJ_SUB(self)->ctrl.motion;

            if (st >= 1078 && st <= 1080) {
                act->motReq = SetMotionRequest(self, 290, act->env.motOriReq);
            }
            break;
        }

        case 7:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;

        case 26:
        case 27:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;

        case 389:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;

        case 390:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;

        case 391:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;

        case 392:
            act->motReq = SetMotionRequest(self, 289, act->env.motOriReq);
            break;
        }
    }
    q->num = 0;
    /* the actor's motion orient request, refreshed from the copy the
       sub-object keeps at 0x180 */
    act->env.motOriReq = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
}
#else
void birdBeforeFunc(GObj *self)
{
    Act *act = GOBJ_ACT(self);
    BirdWork *w = GOBJ_SUB(self)->work;
    float there[4];
    float here[4];
    int i;
    GObjMailQueue *q = (GObjMailQueue *)&self->mailBox;

    for (i = 0; i < q->num; i++) {
        GObjMailEntry *e = &q->e[i];
        float len;

        GetRootPosition(there, e->data);
        GetRootPosition(here, self);
        len = _GetLengthXZ(there, here);
        switch (e->mail) {
#ifdef VERSION_AUG6
        case 389:
#else
#ifdef VERSION_JUN26
        case 373:
#else
        case 423:
#endif
#endif
            if (len < 200.0f) {
                w->scared = 1;
                GetRootPosition(w->scarer, e->data);
            }
            break;

#ifdef VERSION_AUG6
        case 390:
            if (len < 250.0f) {
                act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
#else
#ifdef VERSION_JUN26
        case 374:
            if (len < 250.0f) {
                act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
#else
        case 424:
            if (len < 250.0f) {
                act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
#endif
#endif
            }
            break;

        case 10: {
            int st = GOBJ_SUB(self)->ctrl.motion;

#ifdef VERSION_AUG6
            if (st >= 1080 && st <= 1082) {
                act->motReq = SetMotionRequest(self, 288, act->env.motOriReq);
#else
#ifdef VERSION_JUN26
            if (st >= 1158 && st <= 1160) {
                act->motReq = SetMotionRequest(self, 277, act->env.motOriReq);
#else
            if (st >= 1139 && st <= 1141) {
                act->motReq = SetMotionRequest(self, 322, act->env.motOriReq);
#endif
#endif
            }
            break;
        }

        case 7:
#ifdef VERSION_AUG6
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
#else
#ifdef VERSION_JUN26
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
#else
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
#endif
#endif
            break;

        case 26:
        case 27:
#ifdef VERSION_AUG6
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
            break;

        case 385:
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
            break;

        case 386:
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
            break;

        case 387:
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
            break;

        case 388:
            act->motReq = SetMotionRequest(self, 287, act->env.motOriReq);
#else
#ifdef VERSION_JUN26
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
            break;

        case 369:
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
            break;

        case 370:
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
            break;

        case 371:
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
            break;

        case 372:
            act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
#else
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 419:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 420:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 421:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
            break;

        case 422:
            act->motReq = SetMotionRequest(self, 321, act->env.motOriReq);
#endif
#endif
            break;
        }
    }
    q->num = 0;
    /* the actor's motion orient request, refreshed from the copy the
       sub-object keeps at 0x180 */
    act->env.motOriReq = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
#ifdef VERSION_JUN26
    /* the second pad's test keys: reset the bird to its home, or scare it */
    if (pad[1].flags & 0x800) {
        InitMotionOrient(self, 2120, 2165, -1, -1, 1153);
        SetDirectRootPosition(self, ((BirdWork *)GOBJ_SUB(self)->work)->home);
        act->motReq = SetMotionRequest(self, 271, act->env.motOriReq);
    }
    if (pad[1].flags & 0x100) {
        act->motReq = SetMotionRequest(self, 276, act->env.motOriReq);
    }
#endif
}
#endif

/* --- act_bird.c's own small helpers, inlined into subBirdBrainMain --- */

/* a point 100 units along `dir` from `p` */
static __inline__ void point_ahead(float *dst, float *p, float *dir) /* derived name */
{
    float v[4];

    sceVu0ScaleVector(v, dir, 100.0f);
    sceVu0AddVector(dst, p, v);
}

static __inline__ float rand_range(float a, float b) /* derived name */
{
    return random_unit() * (b - a) + a;
}

static __inline__ float rand_flip(float v) /* derived name */
{
    if (random_unit() <= 0.5f) {
        v = -v;
    }
    return v;
}

static __inline__ float rand_range_rad(float a, float b) /* derived name */
{
    return degrees_to_radians(rand_range(a, b));
}

static __inline__ float rand_small_turn(void) /* derived name */
{
    return degrees_to_radians(rand_flip(rand_range(1.0f, 2.0f)));
}

/* turn `v` about Y by `ang` radians */
static __inline__ void rotate_y(float *v, float ang) /* derived name */
{
    float m[16];
    float mr[16];

    sceVu0UnitMatrix(m);
    sceVu0RotMatrixY(mr, m, ang);
    apply_matrix_w1(v, mr, v);
}

static void trans_bird(void *self, float *w)
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

/* point the bird `ang` radians round from where it faces */
static __inline__ void turn_bird(void *self, float ang) /* derived name */
{
    float d[4];

    _GetMotionDirection(d, self);
    rotate_y(d, ang);
    SetMotionDirection(self, d);
}

/* restart the flap wave from where it currently stands */
static __inline__ void set_wave(float *w, float a, float b, float step) /* derived name */
{
    w[0] = a;
    w[1] = b;
    w[7] = step;

    w[2] = w[4];
    w[3] = w[5];
    w[6] = 0.0f;
}

#ifdef VERSION_NTSC
/* Actor sub-thread body: the actor scheduler resumes this frame after every
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
    BirdWork *bw;
    Act *act;
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

    bw = GOBJ_SUB(gobj)->work;
    frames = 0;

    lastHit = 0;
    count = 1;
    ticks = 0;

    hover = 0.0f;

    yaw = hover;
    rot = hover;
    travel = hover;

    away = 0;

    act = GOBJ_ACT(gobj);

    _ACTWait(1);

    GetRootPosition(startPos, gobj);
    GetRootPosition(lastPos, gobj);

    lastState = GOBJ_SUB(gobj)->ctrl.motion;
    /* the loop opens by reading the same field into `state` again */
    state = GOBJ_SUB(gobj)->ctrl.motion;
    while (1) {
        int changed;
        int hit;
        int hold;
        int blocked;
        int noAvoid;
        float phase;

        state = GOBJ_SUB(gobj)->ctrl.motion;
        phase = GOBJ_SUB(gobj)->ctrl.animFrame;
        hit = GOBJ_SUB(gobj)->ctrl.frameEnd;

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
        if (bw->scared != 0) {
            switch (state) {
            case 1078:
            case 1079:
            case 1080:
            case 1081:
                break;
            default:
                noAvoid = 1;
                break;
            }
        }

        if (noAvoid == 0 && state != 1073 && state != 1077) {
            ClipWork wf;

            float len = 100.0f;

            float rad = 50.0f;
            float fwd;
            ClipWork wr;
            ClipWork wl;
            float tr[4];
            float tl[4];
            float avoid[4];
            float nd[4];
            float nrm[4];

            if (state == 1078 || state == 1079) {
                fwd = 300.0f;
            } else {
                fwd = 50.0f;
                len = 50.0f;
                rad = 10.0f;
            }

            wf.radius = rad;
            CopyVector(wf.pt[0], pos);
            sceVu0ScaleVectorXYZ(wf.pt[1], mtx[2], fwd);
            sceVu0AddVector(wf.pt[1], wf.pt[1], pos);
            ClipWall(&wf);

            wr.radius = rad;
            CopyVector(wr.pt[0], pos);
            sceVu0ScaleVectorXYZ(tr, mtx[0], len);
            sceVu0AddVector(wr.pt[1], pos, tr);
            ClipWall(&wr);

            wl.radius = rad;
            CopyVector(wl.pt[0], pos);
            sceVu0ScaleVectorXYZ(tl, mtx[0], -len);
            sceVu0AddVector(wl.pt[1], pos, tl);
            ClipWall(&wl);

            if (wf.wall.elem != 0 || wr.wall.elem != 0 || wl.wall.elem != 0) {
                blocked = 1;

                if (wr.wall.elem != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tr, -1.0f);
                    sign = -1.0f;
                } else if (wl.wall.elem != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tl, -1.0f);
                    sign = 1.0f;
                } else {
                    sceVu0Normalize(nrm, &wf.normal);

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
        case 1076:
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

        case 1073:
            if (gobj == CurrentTargetGObj) {
                Debug_WireString_Bird(pos, "STOP TGT");
                break;
            }
            if (hit != 0) {
                Debug_WireString_Bird(pos, "STOP FIN");

                if (bw->scared != 0) {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
                        act->motReq = SetMotionRequest(gobj, 289, act->env.motOriReq);
                        break;
                    }
                    if (random_unit() <= 0.5f) {
                        act->motReq = SetMotionRequest(gobj, 285, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 286, act->env.motOriReq);
                    break;
                } else {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
                        act->motReq = SetMotionRequest(gobj, 289, act->env.motOriReq);
                        break;
                    }
                    if (r < 0.4f) {
                        act->motReq = SetMotionRequest(gobj, 288, act->env.motOriReq);
                        break;
                    }
                    if (r < 0.7f) {
                        act->motReq = SetMotionRequest(gobj, 287, act->env.motOriReq);
                        break;
                    }
                    if (random_unit() <= 0.7f) {
                        act->motReq = SetMotionRequest(gobj, 285, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 286, act->env.motOriReq);
                    break;
                }
            } else {
                char buf[1024];

                sprintf(buf, "STOP NO FIN %d,%1.1f", GOBJ_SUB(gobj)->ctrl.motion,
                        GOBJ_SUB(gobj)->ctrl.animFrame);
                Debug_WireString_Bird(pos, buf);
                break;
            }

        case 1074:
        case 1075:
            Debug_WireString_Bird(pos, "STEP");
            if (hold != 0) {
                int q = 3;

                if (bw->scared != 0) {
                    float v[4];

                    yaw = rand_range_rad(40.0f, 70.0f) / q;

                    sceVu0SubVector(v, pos, bw->scarer);
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
            act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);

            bw->scared = 0;
            break;

        case 1077:
            Debug_WireString_Bird(pos, "GROOM");

            act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
            break;

        case 1078:
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
            act->motReq = SetMotionRequest(gobj, 289, act->env.motOriReq);
            break;

        case 1079:
            Debug_WireString_Bird(pos, "FLY");
            if (changed != 0) {
                if (random_unit() <= 0.5f) {
                    pbga_start(&bw->bga, 441);
                    _CopyVector(bw->bga->pos, pos);
                    CopyQuaternion(bw->bga->rot, IdentityQuaternion);
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
                ClipWork cf;
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
                CopyVector(cf.pt[0], pos);
                sceVu0AddVector(cf.pt[1], cf.pt[0], up);
                sceVu0AddVector(cf.pt[1], cf.pt[1], ahead);
                ClipFloor(&cf);
                attr = GetFloorAttribute(&cf);
                if (cf.floor.elem != 0 && attr != 64 && attr != 80) {
                    act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
                }

                apply_matrix_w1(sv, (char *)matrixptr + 0x100, pos);
                sv[0] = sv[0] / sv[3] - 2048.0f;
                sv[1] = sv[1] / sv[3] - 2048.0f;

                sx = sv[0] / (ScreenWidth / 2);
                sy = sv[1] / (ScreenHeight / 2);
                if (sv[3] > 0.0f && __builtin_fabsf(sx) < 0.6f && sy > -1.3f && sy < 0.5f) {
                    float dy;

                    sceVu0InversMatrix(im, (char *)matrixptr + 128);
                    point_ahead(p2, pos, im[1]);
                    apply_matrix_w1(sv2, (char *)matrixptr + 0x100, p2);
                    sv2[1] = sv2[1] / sv2[3] - 2048.0f;
                    dy = __builtin_fabsf(sv2[1] - sv[1]) / ScreenHeight;

                    if (dy > 0.5f && (bw->bga == 0 || bw->bga->frame > 100.0f)) {
                        pbga_start(&bw->bga, 441);
                        _CopyVector(bw->bga->pos, pos);
                        CopyQuaternion(bw->bga->rot, IdentityQuaternion);
                    }
                }
            }

            hover = hover + 1.0f;
            break;

        case 1080:
            Debug_WireString_Bird(pos, "FLY E1");
            if (changed != 0) {
                float a = rand_range(340.0f, 565.0f) / 28.0f * 0.6f;
                float b = -rand_range(225.0f, 250.0f) / 28.0f * 0.6f;

                set_wave(wave, a, b, 1.0f / 7.0f);
                if (random_unit() <= 0.5f) {
                    pbga_start(&bw->bga, 441);
                    _CopyVector(bw->bga->pos, pos);
                    CopyQuaternion(bw->bga->rot, IdentityQuaternion);
                }
            }

            trans_bird(gobj, wave);

            if (count >= 3) {
                act->motReq = SetMotionRequest(gobj, 289, act->env.motOriReq);
            }
            break;

        case 1081: {
            float p[4];
            float q[4];
            ClipWork cd;

            Debug_WireString_Bird(pos, "FLY E2");
            if (changed != 0) {
                wave[5] = 0.0f;
                set_wave(wave, 0.0f, 0.0f, 0.2f);
            }

            if (phase >= 0.0f && phase < 5.0f) {
                trans_bird(gobj, wave);
            }

            GetRootPosition(p, gobj);
            CopyVector(cd.pt[0], p);
            GetRootPosition(cd.pt[1], gobj);
            cd.pt[1][1] = cd.pt[1][1] + 50.0f;
            ClipFloor(&cd);
            if (cd.floor.elem != 0) {
                float lim = -6.0f;

                float y = cd.pt[2][1] + lim;
                /* nothing reads `q` after this */
                q[1] = lim;
                if (y < p[1]) {
                    p[1] = y;
                    SetRootPosition(gobj, p);
                }
            }

            if (hit != 0) {
                act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
            }
            break;
        }

        default:
            act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
            break;
        }

        if (state != 1078) {
            float rp[4];

            if ((GOBJ_SUB(gobj)->ctrl.flags & 0x400) || CheckFloorAttribute(gobj, 64) ||
                CheckFloorAttribute(gobj, 80)) {
                GetRootPosition(rp, gobj);
                rp[1] = GOBJ_SUB(gobj)->ctrl.waterY;
                SetDirectRootPositionNoFitting(gobj, rp);
                act->motReq = SetMotionRequest(gobj, 153, act->env.motOriReq);
                EntryStageMultiBgaManager(428, rp, IdentityQuaternion);
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

        if (state == 1079 &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)frames &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)ticks) {
            debug_StdPrintfDummy("bird reset\n");
            InitMotionOrient(gobj, 2119, 2165, -1, -1, 1073);

            SetDirectRootPosition(gobj, startPos);
            act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
        }

        lastState = state;

        lastHit = hit;
        _ACTWait(1);
    }
}
#else
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
void subBirdBrainMain(void *volatile gobj)
{
#ifndef VERSION_JUN26
    float startPos[4];
    float lastPos[4];
#endif
    float wave[8];
    float homePos[4];
    float pos[4];
    float dir[4];
    float mtx[4][4];
    BirdWork *bw;
    Act *act;
#ifdef VERSION_JUN26
    int lastHit;
    int count;
#else
    int frames;
    int lastHit;
    int count;
    int ticks;
#endif
    int away;
    int lastState;
    int state;
    float sign;
    float yaw;
    float rot;
    float hover;
    float travel;

    bw = GOBJ_SUB(gobj)->work;
#ifndef VERSION_JUN26
    frames = 0;
#endif

    lastHit = 0;
    count = 1;
#ifndef VERSION_JUN26
    ticks = 0;
#endif

    hover = 0.0f;

    yaw = hover;
    rot = hover;
    travel = hover;

    away = 0;

    act = GOBJ_ACT(gobj);

    _ACTWait(1);

#ifndef VERSION_JUN26
    GetRootPosition(startPos, gobj);
    GetRootPosition(lastPos, gobj);
#endif

    lastState = GOBJ_SUB(gobj)->ctrl.motion;
    /* the loop opens by reading the same field into `state` again */
    state = GOBJ_SUB(gobj)->ctrl.motion;
    while (1) {
        int changed;
        int hit;
        int hold;
        int blocked;
        int noAvoid;
        float phase;

        state = GOBJ_SUB(gobj)->ctrl.motion;
        phase = GOBJ_SUB(gobj)->ctrl.animFrame;
        hit = GOBJ_SUB(gobj)->ctrl.frameEnd;

        changed = 0;

        blocked = 0;

        sign = 1.0f;

        GetRootPosition(pos, gobj);
        _GetMotionDirection(dir, gobj);
        GetRootMatrix(mtx, gobj);

        if (state != lastState) {
            count = 1;
            changed = 1;

#ifndef VERSION_JUN26
            ticks = 0;
#endif
        } else {
            if (lastHit != 0) {
                count++;
            }
        }

        hold = (changed != 0 || hit != 0);
#ifndef VERSION_JUN26
        ticks++;
#endif

        noAvoid = 0;
        if (bw->scared != 0) {
            switch (state) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            case 1158:
            case 1159:
            case 1160:
            case 1161:
#else
            case 1080:
            case 1081:
            case 1082:
            case 1083:
#endif
#else
            case 1139:
            case 1140:
            case 1141:
            case 1142:
#endif
                break;
            default:
                noAvoid = 1;
                break;
            }
        }

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        if (noAvoid == 0 && state != 1153 && state != 1157) {
#else
        if (noAvoid == 0 && state != 1075 && state != 1079) {
#endif
#else
        if (noAvoid == 0 && state != 1134 && state != 1138) {
#endif
            ClipWork wf;

            float len = 100.0f;

            float rad = 50.0f;
            float fwd;
            ClipWork wr;
            ClipWork wl;
            float tr[4];
            float tl[4];
            float avoid[4];
            float nd[4];
            float nrm[4];

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            if (state == 1158 || state == 1159) {
#else
            if (state == 1080 || state == 1081) {
#endif
#else
            if (state == 1139 || state == 1140) {
#endif
                fwd = 300.0f;
            } else {
                fwd = 50.0f;
                len = 50.0f;
                rad = 10.0f;
            }

            wf.radius = rad;
            CopyVector(wf.pt[0], pos);
            sceVu0ScaleVectorXYZ(wf.pt[1], mtx[2], fwd);
            sceVu0AddVector(wf.pt[1], wf.pt[1], pos);
            ClipWall(&wf);

            wr.radius = rad;
            CopyVector(wr.pt[0], pos);
            sceVu0ScaleVectorXYZ(tr, mtx[0], len);
            sceVu0AddVector(wr.pt[1], pos, tr);
            ClipWall(&wr);

            wl.radius = rad;
            CopyVector(wl.pt[0], pos);
            sceVu0ScaleVectorXYZ(tl, mtx[0], -len);
            sceVu0AddVector(wl.pt[1], pos, tl);
            ClipWall(&wl);

            if (wf.wall.elem != 0 || wr.wall.elem != 0 || wl.wall.elem != 0) {
                blocked = 1;

                if (wr.wall.elem != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tr, -1.0f);
                    sign = -1.0f;
                } else if (wl.wall.elem != 0) {
                    sceVu0ScaleVectorXYZ(avoid, tl, -1.0f);
                    sign = 1.0f;
                } else {
                    sceVu0Normalize(nrm, &wf.normal);

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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1156:
#else
        case 1078:
#endif
#else
        case 1137:
#endif
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

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1153:
#else
        case 1075:
#endif
#else
        case 1134:
#endif
            if (gobj == CurrentTargetGObj) {
                Debug_WireString_Bird(pos, "STOP TGT");
                break;
            }
            if (hit != 0) {
                Debug_WireString_Bird(pos, "STOP FIN");

                if (bw->scared != 0) {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 276, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 287, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 321, act->env.motOriReq);
#endif
                        break;
                    }
                    if (random_unit() <= 0.5f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 272, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 273, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 283, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 317, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 318, act->env.motOriReq);
#endif
                    break;
                } else {
                    float r = random_unit();
                    if (r < 0.25f) {
                        break;
                    }
                    if (r < 0.28f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 276, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 287, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 321, act->env.motOriReq);
#endif
                        break;
                    }
                    if (r < 0.4f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 275, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 286, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 320, act->env.motOriReq);
#endif
                        break;
                    }
                    if (r < 0.7f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 274, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 285, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 319, act->env.motOriReq);
#endif
                        break;
                    }
                    if (random_unit() <= 0.7f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        act->motReq = SetMotionRequest(gobj, 272, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 273, act->env.motOriReq);
#else
                        act->motReq = SetMotionRequest(gobj, 283, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 284, act->env.motOriReq);
#endif
#else
                        act->motReq = SetMotionRequest(gobj, 317, act->env.motOriReq);
                        break;
                    }
                    act->motReq = SetMotionRequest(gobj, 318, act->env.motOriReq);
#endif
                    break;
                }
            } else {
                char buf[1024];

                sprintf(buf, "STOP NO FIN %d,%1.1f", GOBJ_SUB(gobj)->ctrl.motion,
                        GOBJ_SUB(gobj)->ctrl.animFrame);
                Debug_WireString_Bird(pos, buf);
                break;
            }

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1154:
        case 1155:
#else
        case 1076:
        case 1077:
#endif
#else
        case 1135:
        case 1136:
#endif
            Debug_WireString_Bird(pos, "STEP");
            if (hold != 0) {
                int q = 3;

                if (bw->scared != 0) {
                    float v[4];

                    yaw = rand_range_rad(40.0f, 70.0f) / q;

                    sceVu0SubVector(v, pos, bw->scarer);
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            act->motReq = SetMotionRequest(gobj, 271, act->env.motOriReq);
#else
            act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
#endif
#else
            act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
#endif

            bw->scared = 0;
            break;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1157:
            Debug_WireString_Bird(pos, "GROOM");

            act->motReq = SetMotionRequest(gobj, 271, act->env.motOriReq);
            break;

        case 1158:
#else
        case 1079:
            Debug_WireString_Bird(pos, "GROOM");

            act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
            break;

        case 1080:
#endif
#else
        case 1138:
            Debug_WireString_Bird(pos, "GROOM");

            act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
            break;

        case 1139:
#endif
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            break;

#ifdef VERSION_JUN26
        case 1159:
#else
        case 1081:
#endif
#else
            act->motReq = SetMotionRequest(gobj, 321, act->env.motOriReq);
            break;

        case 1140:
#endif
            Debug_WireString_Bird(pos, "FLY");
            if (changed != 0) {
                if (random_unit() <= 0.5f) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                    pbga_start(&bw->bga, 508);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    pbga_start(&bw->bga, 404);
#else
                    pbga_start(&bw->bga, 440);
#endif
#else
                    pbga_start(&bw->bga, 512);
#endif
#endif
                    _CopyVector(bw->bga->pos, pos);
                    CopyQuaternion(bw->bga->rot, IdentityQuaternion);
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

#ifndef VERSION_JUN26
            travel = travel + 1.0f;
#endif
            GetRootPosition(pos, gobj);
            _GetMotionDirection(dir, gobj);

            {
                float up[4];
                float ahead[4];
                ClipWork cf;
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
                CopyVector(cf.pt[0], pos);
                sceVu0AddVector(cf.pt[1], cf.pt[0], up);
                sceVu0AddVector(cf.pt[1], cf.pt[1], ahead);
                ClipFloor(&cf);
                attr = GetFloorAttribute(&cf);
                if (cf.floor.elem != 0 && attr != 64 && attr != 80) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    act->motReq = SetMotionRequest(gobj, 271, act->env.motOriReq);
#else
                    act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
#endif
#else
                    act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
#endif
                }

                apply_matrix_w1(sv, (char *)matrixptr + 0x100, pos);
                sv[0] = sv[0] / sv[3] - 2048.0f;
                sv[1] = sv[1] / sv[3] - 2048.0f;

                sx = sv[0] / (ScreenWidth / 2);
                sy = sv[1] / (ScreenHeight / 2);
                if (sv[3] > 0.0f && __builtin_fabsf(sx) < 0.6f && sy > -1.3f && sy < 0.5f) {
                    float dy;

                    sceVu0InversMatrix(im, (char *)matrixptr + 128);
                    point_ahead(p2, pos, im[1]);
                    apply_matrix_w1(sv2, (char *)matrixptr + 0x100, p2);
                    sv2[1] = sv2[1] / sv2[3] - 2048.0f;
                    dy = __builtin_fabsf(sv2[1] - sv[1]) / ScreenHeight;

                    if (dy > 0.5f && (bw->bga == 0 || bw->bga->frame > 100.0f)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                        pbga_start(&bw->bga, 508);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        pbga_start(&bw->bga, 404);
#else
                        pbga_start(&bw->bga, 440);
#endif
#else
                        pbga_start(&bw->bga, 512);
#endif
#endif
                        _CopyVector(bw->bga->pos, pos);
                        CopyQuaternion(bw->bga->rot, IdentityQuaternion);
                    }
                }
            }

            hover = hover + 1.0f;
            break;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1160:
#else
        case 1082:
#endif
#else
        case 1141:
#endif
            Debug_WireString_Bird(pos, "FLY E1");
            if (changed != 0) {
                float a = rand_range(340.0f, 565.0f) / 28.0f * 0.6f;
                float b = -rand_range(225.0f, 250.0f) / 28.0f * 0.6f;

                set_wave(wave, a, b, 1.0f / 7.0f);
                if (random_unit() <= 0.5f) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                    pbga_start(&bw->bga, 508);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    pbga_start(&bw->bga, 404);
#else
                    pbga_start(&bw->bga, 440);
#endif
#else
                    pbga_start(&bw->bga, 512);
#endif
#endif
                    _CopyVector(bw->bga->pos, pos);
                    CopyQuaternion(bw->bga->rot, IdentityQuaternion);
                }
            }

            trans_bird(gobj, wave);

            if (count >= 3) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                act->motReq = SetMotionRequest(gobj, 276, act->env.motOriReq);
#else
                act->motReq = SetMotionRequest(gobj, 287, act->env.motOriReq);
#endif
#else
                act->motReq = SetMotionRequest(gobj, 321, act->env.motOriReq);
#endif
            }
            break;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        case 1161: {
#else
        case 1083: {
#endif
#else
        case 1142: {
#endif
            float p[4];
            float q[4];
            ClipWork cd;

#ifndef VERSION_JUN26
            Debug_WireString_Bird(pos, "FLY E2");
#endif
            if (changed != 0) {
                wave[5] = 0.0f;
                set_wave(wave, 0.0f, 0.0f, 0.2f);
            }

            if (phase >= 0.0f && phase < 5.0f) {
                trans_bird(gobj, wave);
            }

            GetRootPosition(p, gobj);
            CopyVector(cd.pt[0], p);
            GetRootPosition(cd.pt[1], gobj);
            cd.pt[1][1] = cd.pt[1][1] + 50.0f;
            ClipFloor(&cd);
            if (cd.floor.elem != 0) {
                float lim = -6.0f;

                float y = cd.pt[2][1] + lim;
                /* nothing reads `q` after this */
                q[1] = lim;
                if (y < p[1]) {
                    p[1] = y;
                    SetRootPosition(gobj, p);
                }
            }

            if (hit != 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                act->motReq = SetMotionRequest(gobj, 271, act->env.motOriReq);
#else
                act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
#endif
#else
                act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
#endif
            }
            break;
        }

        default:
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            act->motReq = SetMotionRequest(gobj, 271, act->env.motOriReq);
#else
            act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
#endif
#else
            act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
#endif
            break;
        }

#ifdef VERSION_JUN26
        if (GOBJ_SUB(gobj)->ctrl.flags & 0x400) {
            act->motReq = SetMotionRequest(gobj, 276, act->env.motOriReq);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        if (GOBJ_SUB(gobj)->ctrl.flags & 0x400) {
            act->motReq = SetMotionRequest(gobj, 287, act->env.motOriReq);
#else
        if (state != 1139) {
            float rp[4];

            if ((GOBJ_SUB(gobj)->ctrl.flags & 0x400) || CheckFloorAttribute(gobj, 64) ||
                CheckFloorAttribute(gobj, 80)) {
                GetRootPosition(rp, gobj);
                rp[1] = GOBJ_SUB(gobj)->ctrl.waterY;
                SetDirectRootPositionNoFitting(gobj, rp);
                act->motReq = SetMotionRequest(gobj, 172, act->env.motOriReq);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                EntryStageMultiBgaManager(494, rp, IdentityQuaternion);
#else
                EntryStageMultiBgaManager(498, rp, IdentityQuaternion);
#endif
            }
#endif
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

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        if (state == 1081 &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)frames &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)ticks) {
            debug_StdPrintfDummy("bird reset\n");
            InitMotionOrient(gobj, 2094, 2138, -1, -1, 1075);

            SetDirectRootPosition(gobj, startPos);
            act->motReq = SetMotionRequest(gobj, 282, act->env.motOriReq);
#else
        if (state == 1140 &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)frames &&
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f < (float)ticks) {
            debug_StdPrintfDummy("bird reset\n");
            InitMotionOrient(gobj, 2421, 2467, -1, -1, 1134);

            SetDirectRootPosition(gobj, startPos);
            act->motReq = SetMotionRequest(gobj, 316, act->env.motOriReq);
#endif
#endif
        }

        lastState = state;

        lastHit = hit;
        _ACTWait(1);
    }
}
#endif

#ifndef VERSION_JUN26
inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        Act *act = GOBJ_ACT(gobj);
#endif
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

inline void actBirdStart(void *gobj)
{
    Act *act;

    act = (Act *)actInitialize(gobj);
    _ACTWait(1);
    actCreateSubThread(subBirdBrainMain, 20);
    actCreateSubThread(subBirdControl, 21);
    actCreateSubThread(subBirdCollision, 21);
#ifdef VERSION_NTSC
    act->motReq = SetMotionRequest(gobj, 238, act->env.motOriReq);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    act->motReq = SetMotionRequest(gobj, 236, act->env.motOriReq);
#else
    act->motReq = SetMotionRequest(gobj, 270, act->env.motOriReq);
#endif
#endif
}

static void Debug_WireString_Bird(float *pos, char *fmt, ...)
{
    float m[16];
    char buf[256];
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;

    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 128));
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
#endif

static void Debug_StickControl(GObj *self)
{
    float dir[4];
    Act *ext = GOBJ_ACT(self);

    if (self == CurrentTargetGObj) {
        iosPadConnect(&ext->pad, 0, 0, &ext->padConf);
        iosPadRead(&ext->pad);
        iosPadGetStick(&ext->pad, &ext->stick, 0, 2, 2, 0);
        _GetMotionDirection(dir, self);
        ext->stick.angle = CorrectStickInfo(dir, &ext->stick);
        if (ext->stick.mag > 0.001f) {
            ConvertStickToAbsCoord(ext->dir, &ext->stick);
        }
    } else if (self == CurrentTargetGObjSub) {
        iosPadConnect(&ext->pad, 0, 1, &ext->padConf);
    } else {
        iosPadConnect(&ext->pad, 0, 1, &ext->padConf);
    }
}

void BirdGeo(void *self)
{
    ExecMotionOrient(self);
}

#ifdef VERSION_NTSC
void BirdDL(void *gobj)
{
    BirdWork *w;

    p2o_DispVU1Default(gobj);
    w = GOBJ_SUB(gobj)->work;
    if (w->bga != 0) {
        if (stage_DispBgAnimation(&w->bga) != 0) {
            w->bga = 0;
        }
    }
    if (stage_no == 82) {
        lightning_test();
    }
}
#else
#ifdef VERSION_JUN26
void _ACTSendMailToBird(void *obj, int mail, void *data)
{
    iosOmSendMail(obj, mail, data);
}

/* a label drawn in wire letters 50 above pos, facing the camera */
static void Debug_WireString_Bird(float *pos, char *str)
{
    float m[16];

    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 128));
    m[3] = m[7] = m[11] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
    sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(str);
    MatrixDrive_PopMatrix();
    MatrixDrive_PopMatrix();
}

inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        Act *act = GOBJ_ACT(gobj);

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

inline void actBirdStart(void *gobj)
{
    Act *act;

    act = (Act *)actInitialize(gobj);
    _ACTWait(1);
    actCreateSubThread(subBirdBrainMain, 20);
    actCreateSubThread(subBirdControl, 21);
    actCreateSubThread(subBirdCollision, 21);
    act->motReq = SetMotionRequest(gobj, 225, act->env.motOriReq);
}
#else
void BirdDL(void *gobj)
{
    BirdWork *w;

    p2o_DispVU1Default(gobj);
    w = GOBJ_SUB(gobj)->work;
    if (w->bga != 0) {
        if (stage_DispBgAnimation(&w->bga) != 0) {
            w->bga = 0;
        }
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_AUG6)
    if (stage_no == 82) {
#else
    if (stage_no == 84) {
#endif
        lightning_test();
    }
}
#endif
#endif

inline BirdWork *InitBirdGeo(GObj *gobj, void *home)
{
    BirdWork *w;

    w = iosMallocDebug(ios_partition_sugipon, sizeof(BirdWork), __FILE__,
                       LN(978, 978, 978, 978, 959, 922));
    memset(w, 0, sizeof(BirdWork));
    CopyVector(w->home, home);
    w->scared = 0;
#ifdef VERSION_NTSC
    InitMotionOrient(gobj, 2119, 2165, -1, -1, 1073);
#else
#ifdef VERSION_AUG6
    InitMotionOrient(gobj, 2094, 2138, -1, -1, 1075);
#else
#ifdef VERSION_JUN26
    InitMotionOrient(gobj, 2120, 2165, -1, -1, 1153);
#else
    InitMotionOrient(gobj, 2421, 2467, -1, -1, 1134);
#endif
#endif
#endif

    GOBJ_SUB(gobj)->ctrl.floorFit = 1;
    GOBJ_SUB(gobj)->ctrl.cliffWallCheck = 0;
    GOBJ_SUB(gobj)->ctrl.wallReact = 1;
    GOBJ_SUB(gobj)->ctrl.catchBoy = 0;
    /* the animation frame at 0x4AC and the word after it start at the same
       random frame */
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x49C))->f = random_unit() * 100.0f;
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4A0))->f = ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x49C))->f;
    GOBJ_SUB(gobj)->ctrl.waterDrag = 0;
#else
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4AC))->f = random_unit() * 100.0f;
    ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4B0))->f = ((IntFloat *)((int)GOBJ_SUB(gobj) + 0x4AC))->f;
    GOBJ_SUB(gobj)->ctrl.waterDrag = 0;
    SetLodLevel(gobj, 3);
#endif
    return w;
}

inline void BirdAI(void) {}

#ifdef VERSION_JUN26
inline void BirdDL(void *gobj)
{
    BirdWork *w;

    p2o_DispVU1Default(gobj);
    w = GOBJ_SUB(gobj)->work;
    if (w->bga != 0) {
        if (stage_DispBgAnimation(&w->bga) != 0) {
            w->bga = 0;
        }
    }
}
#else
void _ACTSendMailToBird(void *obj, int mail, void *data)
{
    iosOmSendMail(obj, mail, data);
}
#endif

inline void _ACTSendMailToBirdAll(int mail, void *data)
{
    void *obj = isysGObjSearchFromObjKindID_begin(32);
    while (obj != 0) {
        _ACTSendMailToBird(obj, mail, data);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
