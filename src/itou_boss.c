#include "common.h"

typedef struct {
    float a;
    float b;
    float c;
    int d;
} CylParam;


extern int D_00631990;
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", effect_end_func);

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_00198000);

int bossCtrlBeforeFunc(void)
{
    int v = D_00631990;
    int r = 0;
    if (v == 0x54) goto yes;
    if (v == 3) goto yes;
    if (v != 0x2E) goto no;
yes:
    r = 1;
no:
    return r;
}

extern void CylinderCollisionWithControlDynamics(void *o, void *param);
extern char D_0055C168[];
extern int D_00633DC4;
extern int D_00633DC8;
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void actInitialize();
extern void debug_assertMessage(char *msg, int n);
extern void func_00197B30(void);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void BossEnemyFunc(void) {
    int count = 0;
    void *o;
    int i;
    CylParam cyl;

    actInitialize();
    _ACTWait(1);
    D_00633DC8 = 0;
    D_00633DC4 = 0;
    o = isysGObjSearchFromObjLayoutID(0x21);
    if (o != 0) {
        do {
            cyl.a = 4294967296.0f;
            cyl.b = 4294967296.0f;
            cyl.c = 4294967296.0f;
            cyl.d = 0;
            count++;
            CylinderCollisionWithControlDynamics(o, &cyl);
            *(int *)((char *)*(void **)((char *)o + 0x15C) + 0x74) = 0;
            o = isysGObjSearchFromObjKindID_begin(o);
        } while (o != 0);
    }
    debug_assertMessage(D_0055C168, count);
    for (i = 0; i < count; i++) {
        actCreateSubThread(func_00197B30, 0x15);
    }
}

extern char D_0055B030[];
extern char D_0055BD40[];
extern char D_0055C178[];
extern char D_0055C188[];
extern void *D_00632010;
extern signed char D_006D35F0[];
extern void actInitialize();
extern void actInitialize_ext_charcter(void *a0);
extern void apply_matrix_w1(void *a0, void *a1);
extern void debug_assertMessage(char *msg, int n);
extern int func_0013A0F8(void *ptr, int a1, char *file, int line);
extern void func_00243B60(void *a0, void *a1);

int gene_enemy(void *a0) {
    int ret;
    unsigned int k;
    signed char *base;
    signed char *e;
    char *m;
    char (*q_arr)[];
    char *q;
    char *r;

    ret = func_0013A0F8(D_00632010, 0, D_0055C178, 0x15E);
    actInitialize(a0);
    actInitialize_ext_charcter(a0);
    debug_assertMessage(D_0055C188, 0x35);

    base = D_006D35F0;
    m = (char *)base + 0x20;
    q_arr = (char (*)[])&D_0055B030;
    r = D_0055BD40;
    q = *q_arr;
    k = 0;
    do {
        e = base + k * 0x40;
        *(int *)e = 0;
        if (e[4] == 1) {
            e[4] = 2;
        }
        func_00243B60(m, q);
        apply_matrix_w1(m - 0x10, q - 0x30);
        *(char **)(e + 0x30) = r;
        q += 0x40;
        m += 0x40;
        r += 0x10;
        k++;
    } while (k < 0x35);
    return ret;
}

extern unsigned char D_006D35E0[];

void BossCtrlGeo(void) {
    D_006D35E0[0] = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_00198338);

