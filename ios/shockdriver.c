#include "common.h"

typedef struct { int count; int *arr; } ShockMgr;

struct PadNode {
    char pad[0x30];
    struct PadNode *prev;
    struct PadNode *next;
};

typedef struct ShockReq {
    /* 0x0 */ unsigned short out;
    /* 0x2 */ unsigned short acc;
    /* 0x4 */ unsigned char type;
    /* 0x5 */ unsigned char val;
} ShockReq;

typedef struct SHOCKREQUEST {
    /* 0x00 */ unsigned char flags;
    /* 0x01 */ unsigned char b1;
    /* 0x02 */ unsigned char b2;
    /* 0x03 */ unsigned char b3;
    /* 0x04 */ unsigned char pad04[0x24];
    /* 0x28 */ int key;
    /* 0x2C */ int arg;
    /* 0x30 */ struct SHOCKREQUEST *prev;
    /* 0x34 */ struct SHOCKREQUEST *next;
    /* 0x38 */ unsigned char voice;
    /* 0x39 */ unsigned char pad39[7];
} SHOCKREQUEST;

typedef struct ShockVoiceSet {
    /* 0x0 */ int unk0;
    /* 0x4 */ int *wave;
    /* 0x8 */ int *shot;
} ShockVoiceSet;

typedef struct ShockParam {
    /* 0x0 */ unsigned char voice;
    /* 0x1 */ unsigned char b1;
    /* 0x2 */ unsigned char b2;
    /* 0x3 */ unsigned char b3;
} ShockParam;

typedef struct ShockRequestBox {
    /* 0x0 */ void *head;
    /* 0x4 */ void *(*alloc)(void *, int);
    /* 0x8 */ void (*free)(SHOCKREQUEST *, void *);
    /* 0xC */ void *arg;
} ShockRequestBox;

extern ShockMgr *System_shock_driver;
INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Vibration_ShotDecode);
INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Vibration_WaveDecode);
INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Shock_Request);
extern void scePadSetActDirect(int a0, int a1, void *box);

void Shock_SetMotor(int a0, int a1, ShockReq *box, int a3, int a4)
{
    int n = a1 & 0xFF;
    int type = a0 & 0xFF;
    int cur = box->out;
    int diff = n - cur;
    int r = n;
    short w;
    int sum;
    unsigned int outv;

    if (diff <= 0) goto Ldec;
    if (diff >= 0x29) goto Lff;
    if (n >= 0x3D) goto L40;
    if (cur >= 0x3D) goto L40;
    if (cur >= 0x33) goto Lquad;
Lff:
    r = 0xFF;
    goto Ltail;
Lquad:
    diff = 0x3C - n;
    diff = (diff * 0xFF) * diff / 0x64;
    r = (cur < diff) ? diff : n;
    goto Ltail;
L40:
    diff = diff * 0xFF / 0x28;
    r = (cur < diff) ? diff : n;
    goto Ltail;
Ldec:
    if (diff >= 0) goto Ltail;
    if (diff < -0x1E) {
        r = 0;
        goto Ltail;
    }
    diff = diff * 0xFF / 0x1E + 0xFF;
    r = (diff < cur) ? diff : n;
Ltail:
    n = r & 0xFF;
    sum = box->acc + n;
    box->acc = sum;
    if ((short)sum >= 0x40B) {
        box->acc = 0x40A;
    } else if ((short)sum < 0) {
        box->acc = 0;
    }
    w = (short)box->acc;
    outv = ((unsigned int)w << 8) / 0x40B;
    box->type = type;
    box->acc = (unsigned int)(w * 3) >> 2;
    box->val = n;
    box->out = outv;
    if (a3 >= 0) {
        scePadSetActDirect(a3, a4, &box->type);
    }
}
void Init_ShockVoiceSet(int **a0, int *a1) {
    /* The empty loop is a basic-block boundary, and it is the only thing found
     * that keeps `sw a1,0(a0)` in ROM's first slot: the store has no successors
     * so sched2 gives it priority 0 and sinks it to slot 9 behind the three
     * `lhu` latencies.  Making the loads and the store conflict would also pin
     * it, but no typing does: the store's access type is a pointer and the
     * loads' is `unsigned short`, and every combination measured (short/char/int
     * store types, volatile loads, struct-typed header, four statement orders)
     * leaves them in different alias sets, or regresses.  Not retired. */
    do { } while (0);
    a0[0] = a1;
    a0[3] = a1 + *(unsigned short *)((char *)a1 + 0xA);
    a0[1] = a1 + *(unsigned short *)((char *)a1 + 0x2);
    a1 = a1 + *(unsigned short *)((char *)a1 + 0x6);
    a0[2] = a1;
}
void Vibration_SetDecodeData(void *a0, int a1, int a2, unsigned char a3, unsigned char a4) {
    char *p = (char *)a0;
    p[0x3] = a4;
    p[0x0] = 0x11;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x14) = a2;
    p[0x2] = a3;
    *(short *)(p + 0x8) = 0;
    *(short *)(p + 0x12) = 0;
    *(short *)(p + 0x10) = 0;
    *(short *)(p + 0xC) = 0;
    *(short *)(p + 0xA) = 0;
    p[0x26] = 0;
    *(short *)(p + 0x18) = 0;
    *(short *)(p + 0x22) = 0;
    *(short *)(p + 0x20) = 0;
    *(short *)(p + 0x1C) = 0;
    *(short *)(p + 0x1A) = 0;
    p[0x27] = 0;
    p[0x24] = 0;
}
extern int dumyAllocFunc();

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * Init_ShockRequestBox into Init_Player, so it is a public `inline` of the deferred
 * tail; until the tail's asm member (Init_Shock) is C the copy is emitted in
 * place as a plain function at its ROM position and the caller inlines this
 * static stand-in, which collapses at layout. */
static inline void initShockRequestBox(int *a0, int a1, int a2, int a3)
{
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)&dumyAllocFunc;
    }
    a0[2] = a2;
    a0[3] = a3;
}
void Init_ShockRequestBox(int *a0, int a1, int a2, int a3)
{
    initShockRequestBox(a0, a1, a2, a3);
}
void ShockRequestBox_Clear(int *self)
{
    int *node = (int *) self[0];
    if (self[0x8 / 4] == 0)
    {
        goto end;
    }
    if (node == 0)
    {
        goto end;
    }
    do
    {
        int *cur = node;
        node = (int *) node[0x34 / 4];
        (*(void (**)(int, int))((char *) self + 8))((int) cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}
void ShockRequestBox_Regst(struct PadNode **head, struct PadNode *new_node) {
    struct PadNode *old = *head;
    new_node->prev = (struct PadNode *)0;
    new_node->next = old;
    if (old != (struct PadNode *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}
SHOCKREQUEST *ShockRequestBox_Request(ShockRequestBox *box, ShockParam *p, ShockParam v, int key, int arg)
{
    ShockVoiceSet *vs;
    SHOCKREQUEST *req;
    int wave;
    int shot;
    int t;

    if (System_shock_driver == 0) return 0;
    if (box == 0) return 0;

    vs = (ShockVoiceSet *)System_shock_driver->arr[v.voice];
    if (vs == 0) return 0;

    req = box->alloc(box->arg, arg);
    if (req == 0) return 0;

    req->voice = v.voice;
    req->arg = arg;
    req->key = key;

    if (p->voice != 0xFF) {
        wave = (int)vs->wave + vs->wave[p->voice];
    } else {
        wave = 0;
    }
    if (p->b1 != 0xFF) {
        shot = (int)vs->shot + vs->shot[p->b1];
    } else {
        shot = 0;
    }
    Vibration_SetDecodeData(req, wave, shot, 0xFF, 0x40);
    req->b1 = v.b1;
    t = p->b2 * v.b2 / 0xFF;
    req->b2 = (t < 0x100) ? t : 0xFF;
    t = p->b3 * v.b3 / 0x40;
    if (t >= 0x100) t = 0xFF;
    req->b3 = t;
    ShockRequestBox_Regst((struct PadNode **)box, (struct PadNode *)req);
    return req;
}
extern int Vibration_WaveDecode(SHOCKREQUEST *p, int level);
extern int Vibration_ShotDecode(SHOCKREQUEST *p, int level);
extern int *ShockRequestBox_EndRequestFree(int **a0);

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ShockRequestBox_DecodeRequest into Shock_Decode, so it is a public `inline` of the deferred
 * tail; until the tail's asm member (Init_Shock) is C the copy is emitted in
 * place as a plain function at its ROM position and the caller inlines this
 * static stand-in, which collapses at layout. */
static inline int decodeRequestBox(ShockRequestBox *box, unsigned char *pFlags, unsigned char *pLevel)
{
    SHOCKREQUEST *p;
    int flags = 0;
    int sum = 0;
    int count;

    if (box == 0) {
        return 0;
    }
    p = (SHOCKREQUEST *)box->head;
    count = 0;
    while (p != 0) {
        count++;
        sum += Vibration_WaveDecode(p, ((int *)System_shock_driver)[2]);
        flags |= Vibration_ShotDecode(p, ((int *)System_shock_driver)[2]);
        p = p->next;
    }
    count |= sum << 16;
    if (sum >= 0x100) {
        sum = 0xFF;
    }
    *pLevel = sum;
    *pFlags = flags;
    ShockRequestBox_EndRequestFree((int **)box);
    return count;
}
int ShockRequestBox_DecodeRequest(ShockRequestBox *box, unsigned char *pFlags, unsigned char *pLevel)
{
    return decodeRequestBox(box, pFlags, pLevel);
}
inline SHOCKREQUEST *requestFree(ShockRequestBox *box, SHOCKREQUEST *req);

int *ShockRequestBox_EndRequestFree(int **a0) {
    int *p; unsigned char b;
    if (a0 != 0) {
        p = *a0;
        if (p != 0) {
            do {
                b = *(unsigned char *)p;
                if (b == 0) p = (int *)requestFree((ShockRequestBox *)a0, (SHOCKREQUEST *)p);
                else        p = (int *)p[0x34 / 4];
            } while (p != 0);
        }
    }
    return *a0;
}
inline SHOCKREQUEST *requestFree(ShockRequestBox *box, SHOCKREQUEST *req)
{
    SHOCKREQUEST *p;

    if (req->prev != 0) {
        req->prev->next = req->next;
    } else {
        box->head = req->next;
    }
    if (req->next != 0) {
        req->next->prev = req->prev;
    }
    p = req;
    req = req->next;
    if (box->free != 0) {
        box->free(p, box->arg);
    }
    return req;
}
void *ShockRequestBox_VoiceSetUseRequestFree(ShockRequestBox *box, int voice)
{
    SHOCKREQUEST *p;
    if (box != 0) {
        p = (SHOCKREQUEST *)box->head;
        if (p != 0) {
            do {
                if (p->voice == voice) {
                    p = requestFree(box, p);
                } else {
                    p = p->next;
                }
            } while (p != 0);
        }
    }
    return box->head;
}
int *ShockRequestBox_GetRequest(int **head_ptr, int key)
{
    int *p;
    if (head_ptr == 0) goto fail;
    p = *head_ptr;
    if (p == 0) goto fail;
    do {
        if (p[0x28 / 4] == key) {
            return p;
        }
        p = (int *)p[0x34 / 4];
    } while (p != 0);
fail:
    return 0;
}
int ShockRequestBox_RequestCancel(int a0_, int a1) {
    int *a0 = (int *)a0_;
    int *node;
    int *next;
    int *prev;
    int (*fn)(int *, int);
    node = ShockRequestBox_GetRequest((int **)a0, a1);
    if (node == 0) {
        return 0;
    }
    prev = (int *)node[0x30 / 4];
    if (prev != 0) {
        prev[0x34 / 4] = node[0x34 / 4];
        next = (int *)node[0x34 / 4];
    } else {
        next = (int *)node[0x34 / 4];
        a0[0] = (int)next;
    }
    if (next != 0) {
        next[0x30 / 4] = node[0x30 / 4];
    }
    fn = (int (*)(int *, int))a0[8 / 4];
    if (fn != 0) {
        fn(node, a0[0xC / 4]);
    }
    return 1;
}
int ShockRequestBox_RequestDirectCancel(int *a0, int *a1) {
    int *next;
    int *prev;
    int (*fn)(int *, int);
    if (a1 == 0) {
        return 0;
    }
    prev = (int *)a1[0x30 / 4];
    if (prev != 0) {
        prev[0x34 / 4] = a1[0x34 / 4];
        next = (int *)a1[0x34 / 4];
    } else {
        next = (int *)a1[0x34 / 4];
        a0[0] = (int)next;
    }
    if (next != 0) {
        next[0x30 / 4] = a1[0x30 / 4];
    }
    fn = (int (*)(int *, int))a0[8 / 4];
    if (fn != 0) {
        fn(a1, a0[0xC / 4]);
    }
    return 1;
}

extern int ShockDriver[4];
extern int ShockVoiceSetBuf[2];
extern int ShockRequestMemory[2];
extern char ShockRequest[];

void Init_ShockDriver(int *a0, int a1, int a2)
{
    int *b;
    int i;
    if (a0 == 0) return;
    if (a1 == 0) return;
    b = a0;
    a0 = 0;
    b[1] = a1;
    System_shock_driver = (ShockMgr *)b;
    b[0] = a2;
    for (i = 0; i < a2; i++) *(int *)(b[1] + i*4) = 0;
    b[2] = 0;
}
int ShockDriver_VoiceSet_NumberRegist(unsigned int idx, int val)
{
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = val;
    return idx;
}
int ShockDriver_VoiceSet_Regist(int value) {
    int i;
    for (i = 0; i < System_shock_driver->count; i++) {
        if (System_shock_driver->arr[i] == 0) break;
    }
    if (i == System_shock_driver->count) return -1;
    System_shock_driver->arr[i] = value;
    return i;
}
int ShockDriver_VoiceSet_Remove(unsigned int idx)
{
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = 0;
    return idx;
}
int ShockDriver_GetShockVoiceMax(int a0) {
    int p;
    if ((unsigned int)a0 < (unsigned int)System_shock_driver->count) {
        goto body;
    }
    p = 0;
    goto check;
body:
    p = System_shock_driver->arr[a0];
check:
    if (p != 0) {
        p = *(int *)p;
        return *(unsigned short *)(p + 8);
    }
    return 0;
}
int ShockDriver_GetShockVoiceSet(unsigned idx) {
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned)base[0]) return 0;
    return ((int *)base[1])[idx];
}
int ShockDriver_GetShockVoice(int a0, int a1) {
    int p;
    if ((unsigned int)a0 < (unsigned int)System_shock_driver->count) {
        goto body;
    }
    p = 0;
    goto check;
body:
    p = System_shock_driver->arr[a0];
check:
    if (p == 0) {
        goto ret_a;
    }
    if ((unsigned int)a1 >= (unsigned int)*(unsigned short *)(*(int *)p + 8)) {
        goto ret_b;
    }
    return *(int *)(p + 0xC) + a1 * 4;
ret_b:
    return 0;
ret_a:
    return 0;
}
void Init_ShockEmulator(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}
int ShockEmulator_EmulationShot(int a0, int a1)
{
    return a1;
}
unsigned short ShockEmulator_EmulationWave(short *a0, int a1) {
    int sum = (unsigned short)a0[1] + a1;
    unsigned int q;
    short w;
    a0[1] = sum;
    if ((short)sum >= 0x40B) a0[1] = 0x40A;
    else if ((short)sum < 0) a0[1] = 0;
    w = a0[1];
    q = ((unsigned int)(w << 8)) / 0x40B;
    a0[0] = q;
    a0[1] = ((unsigned int)(w * 3)) >> 2;
    return (unsigned short)a0[0];
}
void Init_ShockRequestAlloc(int *a0, char *a1, int a2) {
    int i;
    if (a0 != 0 && a1 != 0) {
        a0[0] = a2;
        a0[1] = (int)a1;
        for (i = 0; i < a2; i++) {
            a1[i * 0x40] = 0;
        }
    } else {
        a0[0] = 0;
    }
}
void *Get_ShockRequestStruct(int *a0) {
    unsigned char *p = (unsigned char *)a0[1];
    int i;
    for (i = 0; i < a0[0]; i++) {
        if (*p == 0) {
            return p;
        }
        p += 0x40;
    }
    return 0;
}
void Reset_ShockRequestStruct(char *p) {
    *p = 0;
}
int ShockRevice_Wave(int a0, int a1)
{
    int diff = a0 - a1;

    if (diff <= 0) goto Ldec;
    if (diff >= 0x29) goto Lff;
    if (a0 >= 0x3D) goto L40;
    if (a1 >= 0x3D) goto L40;
    if (a1 >= 0x33) goto Lquad;
Lff:
    a0 = 0xFF;
    goto Lend;
Lquad:
    diff = 0x3C - a0;
    diff = (diff * 0xFF) * diff / 0x64;
    a0 = (a1 < diff) ? diff : a0;
    goto Lend;
L40:
    diff = diff * 0xFF / 0x28;
    a0 = (a1 < diff) ? diff : a0;
    goto Lend;
Ldec:
    if (diff >= 0) goto Lend;
    if (diff < -0x1E) {
        a0 = 0;
        goto Lend;
    }
    diff = diff * 0xFF / 0x1E + 0xFF;
    a0 = (diff < a1) ? diff : a0;
Lend:
    return a0;
}
INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_Shock);

int Shock_SetShockVoiceSet(int idx, int val)
{
    int *base = (int *)System_shock_driver;
    int *array;
    if ((unsigned int)idx < (unsigned int)base[0]) goto store;
    idx = -1;
    goto end;
store:
    array = (int *)base[1];
    array[idx] = val;
end:
    return idx;
}

void Init_Player(int *box)
{
    initShockRequestBox(box, (int)Get_ShockRequestStruct,
                         (int)Reset_ShockRequestStruct, (int)ShockRequestMemory);
}
void Init_Controler(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}
void Shock_RequestClear(int *self)
{
    int *node = (int *) self[0];
    if (self[0x8 / 4] == 0)
    {
        goto end;
    }
    if (node == 0)
    {
        goto end;
    }
    do
    {
        int *cur = node;
        node = (int *) node[0x34 / 4];
        (*(void (**)(int, int))((char *) self + 8))((int) cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}
void Shock_Decode(ShockRequestBox *box, unsigned char *pFlags, unsigned char *pLevel)
{
    decodeRequestBox(box, pFlags, pLevel);
}
int dumyAllocFunc(void)
{
    return 0;
}
void Vibration_SetDecodeEnd(unsigned char *p, int a1, int a2) {
    if (a1) *p &= 0xFE;
    if (a2) *p &= 0xEF;
}
