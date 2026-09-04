#include "common.h"

/* spider 0x7F0 view (local; 0x20/0x24 also read as packed ushort elsewhere) */
typedef struct { char _0[0x20]; unsigned short f_20; char _pad22[2]; int f_24; char _pad28[0xC]; int f_34; } SpiderGeo;

int InitSpiderLayoutGeo(void *a0, void *a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    q->f_20 = *(unsigned short *)((char *)a1 + 0x30);
    q->f_24 = *(short *)((char *)a1 + 0x32);
    return 1;
}

int WakeUpLayoutedSpiders(void *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    unsigned short *q = *(unsigned short **)((char *)p + 0x7F0);
    *(unsigned short *)a0 = q[0x10];
    *(unsigned short *)((char *)a0 + 2) = q[0x12];
    return 1;
}

void getCallPoint(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    q->f_34 = a1;
}

extern int IsActCharDead(void *);
extern void *iosFree(int, int, void *, int);
extern float _GetRandom(void);
extern void subAP1BrainMain(int, int);
extern char D_00612A30[];
extern float D_006296B0;
extern int D_0062A310;

struct D0061 { char _0[0x10]; int f10; char _14[0xC]; };
extern struct D0061 D_0061D730[];

typedef struct {
    long long d0;
    long long d8;
    long long d10;
    long long d18;
    long long d20;
    long long d28;
    int f30;
    int _34;
    long long d38;
} SpiderReq;

typedef struct {
    int f0;
    char _4[0x1C];
    int f20;
    int *f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
} SpiderMgr;

SpiderMgr *CallSpidersToReviveEnemy(int arg0, SpiderReq *obj) {
    SpiderReq buf;
    SpiderMgr *mgr;
    int idx;
    int i;
    int count;
    float base;

    mgr = iosFree(D_0062A310, 0x40, D_00612A30, 0x2B);
    buf = *obj;
    idx = obj->f30;
    count = D_0061D730[idx].f10;
    i = 0;
    mgr->f20 = count;
    mgr->f34 = idx;
    mgr->f24 = iosFree(D_0062A310, count * 4, D_00612A30, 0x2F);
    mgr->f28 = 0;
    mgr->f0 = -1;
    mgr->f2C = 0;
    mgr->f30 = 0;
    mgr->f38 = -1;
    mgr->f3C = 0;
    if (i < count) {
        float one = 1.0f;
        base = D_006296B0;
        while (i < count) {
            int r;
            *(float *)((char *)&buf + 0x14) = (2.0f * _GetRandom() - one) * base;
            r = IsActCharDead(&buf);
            mgr->f24[i] = r;
            i++;
            subAP1BrainMain(r, 0);
        }
    }
    return mgr;
}


extern void func_001B8470(int);
extern void subAP1BrainMain(int, int);
extern void playSEConditionID(void *, int);

void SpiderLayoutGeo(void *a0) {
    char *s2 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int count = *(int *)(s2 + 0x20);
    int i;
    *(int *)(s2 + 0x28) = 1;
    for (i = 0; i < count; i++) {
        int *arr = *(int **)(s2 + 0x24);
        func_001B8470(arr[i]);
        arr = *(int **)(s2 + 0x24);
        subAP1BrainMain(arr[i], 1);
    }
    playSEConditionID(a0, 0x65);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DispAllMemberOfSpider);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", SetSpiderGroupReviveStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DeleteSpiderFromLayoutGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", GetNearestOfLayoutSpiders);

extern void gamesysObjInfoUniqDataSet(void *a0);
extern void debug_StdPrintfDummy(char *fmt, int val);
extern char D_0062D740[];

void CheckSpidersInsideOfReviveRange(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x3C) = 1;
    gamesysObjInfoUniqDataSet(a0);
    debug_StdPrintfDummy(D_0062D740, *(int *)((char *)a0 + 0x8));
}

int RestoreSpiderLayoutGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *r = *(int **)((char *)q + 0x24);
    int v = r[a1];
    r[a1] = 0;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", RestoreSpiderLayoutExtGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", MemorySpiderLayout);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_10;  /* 0x10 */
} S_0061D730;  /* stride 0x20 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612B70;  /* stride 0x4 */

/* end struct shapes */
