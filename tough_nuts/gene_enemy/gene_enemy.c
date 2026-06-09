#include "common.h"

extern unsigned char D_006CCE50[];
extern void func_00260568(void *a0, int a1, int a2);

void effect_end_func(void) {
    func_00260568(D_006CCE50, 0, 0xD50);
}

extern int D_00629C90;

int bossCtrlBeforeFunc(void) {
    int x = D_00629C90;
    int r = 0;
    if (x == 0x54 || x == 3 || x == 0x2E) {
        r = 1;
    }
    return r;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void actInitialize();
extern void _ACTWait(int a0);
extern void CylinderCollisionWithControlDynamics(void *o, void *param);
extern void debug_assertMessage(char *msg, int n);
extern void actCreateSubThread(void *entry, int a1);
extern void func_001952A0(void);
extern int D_0062C0B8;
extern int D_0062C0B4;
extern char D_00556338[];

typedef struct {
    float a;
    float b;
    float c;
    int d;
} CylParam;

void BossEnemyFunc(void) {
    int count = 0;
    void *o;
    int i;
    CylParam cyl;

    actInitialize();
    _ACTWait(1);
    D_0062C0B8 = 0;
    D_0062C0B4 = 0;
    o = isysGObjSearchFromObjLayoutID(0x21);
    if (o != 0) {
        do {
            cyl.a = 4294967296.0f;
            cyl.b = 4294967296.0f;
            cyl.c = 4294967296.0f;
            cyl.d = 0;
            count++;
            CylinderCollisionWithControlDynamics(o, &cyl);
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    debug_assertMessage(D_00556338, count);
    for (i = 0; i < count; i++) {
        actCreateSubThread(func_001952A0, 0x15);
    }
}

extern void actInitialize_ext_charcter(void *a0);
extern int iosFree(void *ptr, int a1, char *file, int line);
extern void func_00240080(void *a0, void *a1);
extern void apply_matrix_w1(void *a0, void *a1);
extern void *D_0062A310;
extern char D_00556348[];
extern char D_00556358[];
extern signed char D_006CCE60[];
extern char D_005551F0[];
extern char D_00555F00[];

int gene_enemy(void *a0) {
    int ret;
    unsigned int k;
    signed char *base;
    signed char *e;
    char *m;
    char *q;
    char *r;

    ret = iosFree(D_0062A310, 0, D_00556348, 0x16F);
    actInitialize(a0);
    actInitialize_ext_charcter(a0);
    debug_assertMessage(D_00556358, 0x35);

    base = D_006CCE60;
    m = base + 0x20;
    q = D_005551F0;
    r = D_00555F00;
    k = 0;
    do {
        e = base + k * 0x40;
        *(int *)e = 0;
        if (e[4] == 1) {
            e[4] = 2;
        }
        func_00240080(m, q);
        apply_matrix_w1(m - 0x10, q - 0x30);
        *(char **)(e + 0x30) = r;
        q += 0x40;
        m += 0x40;
        r += 0x10;
        k++;
    } while (k < 0x35);
    return ret;
}

extern unsigned char D_006CCE50[];

void BossCtrlGeo(void) {
    D_006CCE50[0] = 1;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern int clip_floor_1(void *o);
extern signed char D_006CCE60[];

int itou_boss_gflag_init(void) {
    unsigned int s1 = 0;
    int s2 = 0;
    void *o;
    unsigned int i;

    if (isysGObjSearchFromObjLayoutID(0x3F) != 0) {
        i = 0;
        do {
            if (D_006CCE60[i * 0x40 + 4] >= 2) {
                s1++;
            }
            i++;
        } while (i < 0x35);
    }
    o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            if (clip_floor_1(o) == 0) {
                s2++;
            }
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    return s1 >= 0x35 && s2 == 0;
}

void InqCapsuleGhostBossStage(void) {
}
