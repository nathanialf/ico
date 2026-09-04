#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", setMailTarget);

extern void GetRootMatrixByDObj(int *buf, int x);
extern int actEnemy_GetClingTarget(int *a0);
extern float WayLengthOfPos_Pos(int *mtx, int a1);
extern int isysGObjSearchFromObjKindID_next(int obj);
extern int isysGObjSearchFromObjLayoutID(int id);
extern float D_00629784;
extern int D_00629DE8;

static inline float seMail_dh(int a0, int *mb) {
    int ma[4];
    if (a0 == 0) {
        return -1.0f;
    }
    GetRootMatrixByDObj(ma, a0);
    return WayLengthOfPos_Pos(ma, (int) mb);
}

static inline float seMail_obj(int obj, int target) {
    int mtx0[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootMatrixByDObj(mtx0, obj);
    return seMail_dh(target, mtx0);
}

int seMail(float *a0) {
    int obj;
    int target;
    int best = 0;
    float thresh;
    float zero;

    obj = isysGObjSearchFromObjLayoutID(4);
    thresh = *(volatile float *)&D_00629784;
    while (obj != 0 && actEnemy_GetClingTarget((int *)obj) == 0) {
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
    if (obj == 0) {
        goto end;
    }
    zero = 0.0f;
    do {
        float dist;
        target = D_00629DE8;
        dist = seMail_obj(obj, target);
        if ((zero <= dist) && (dist < thresh)) {
            thresh = dist;
            best = obj;
        }
        do {
            obj = isysGObjSearchFromObjKindID_next(obj);
            if (obj == 0) {
                goto end;
            }
        } while (actEnemy_GetClingTarget((int *)obj) == 0);
    } while (1);
end:
    *a0 = thresh;
    return best;
}


extern int D_0062BB64;

int seMailTargetDistCheck(void) {
    return D_0062BB64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202578);

extern float WayLengthOfPos_Pos(int *mtx, int a1);
float func_00202638(int a0, int a1) {
    int buf[4];
    if (a0 == 0) {
        return -1.0f;
    }
    GetRootMatrixByDObj(buf, a0);
    return WayLengthOfPos_Pos(buf, a1);
}

float func_00202688(int a0, int a1) {
    int mb[4];
    if (a1 == 0) {
        return -1.0f;
    }
    GetRootMatrixByDObj(mb, a1);
    return seMail_dh(a0, mb);
}


extern void GetRootMatrixByDObj(int *buf, int x);
extern int WayPointWithRangeFromPos(int *buf, int zero, float f);

int func_002026E0(int a0, float f)
{
    int buf[4];
    if (a0 == 0) {
        return -1;
    }
    GetRootMatrixByDObj(buf, a0);
    return WayPointWithRangeFromPos(buf, 0, f);
}

int func_00202728(int a0, int a1) {
    float x = *(float *)(a0 + 4);
    float y = *(float *)(a1 + 4);
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

extern char D_004C7CF0[];
extern char D_004C6FF0[];
extern int D_0062BB74, D_0062BB78;
typedef struct { int f0,f4,f8,fC,f10,f14,f18,f1C,f20,f24,f28,f2C,f30,f34,f38,f3C; } E40;
typedef struct { int f0,f4,f8,fC,f10,f14,f18,f1C,f20,f24,f28,f2C,f30; } E34;
void func_00202760(void) {
    E40 *p = (E40 *)D_004C7CF0;
    E34 *q;
    int i;
    for (i = 0; i < 0xD7; i++) {
        p->f4 = i; p->f0 = 0; p->f8 = 0; p->fC = 0; p->f20 = -1;
        p++;
    }
    q = (E34 *)D_004C6FF0;
    for (i = 0; i < 0x40; i++) {
        q->f4 = i; q->f0 = 0; q->f8 = 0; q->fC = 0; q->f10 = 0; q->f14 = 0;
        q->f18 = 0; q->f1C = 0; q->f28 = 0; q->f20 = -1; q->f24 = -1;
        q++;
    }
    D_0062BB74 = 0;
    D_0062BB78 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_002027F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/seMail", func_00202868);

extern char D_004C6FF0[];
extern int D_0062BB78;
extern void NearestEnemyFromGirl(int a0);

int DeleteWayGroup(int a0) {
    char *e = &D_004C6FF0[a0 * 0x34];
    char *head;
    if (*(int *)e != 1) {
        return 1;
    }
    head = *(char **)(e + 8);
    if (head != 0) {
        char *node = head;
        do {
            NearestEnemyFromGirl(*(int *)(node + 4));
            node = *(char **)(node + 0xC);
        } while (node != 0);
    }
    *(int *)e = 0;
    D_0062BB78--;
    return 0;
}

extern char D_004C6FF0[];

void CloseWayGroup(int a0) {
    int *elem = (int *)(D_004C6FF0 + a0 * 0x34);
    int *next = (int *)elem[2];
    int *prev = (int *)elem[3];
    elem[5] = 1;
    next[2] = (int)prev;
    prev[3] = (int)next;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C7018;  /* stride 0x34 */

/* end struct shapes */
