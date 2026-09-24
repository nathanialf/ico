#include "common.h"
#include "shockdriver.h"
#include <libpad.h>

typedef struct {
    int count;
    int *arr;
    int level; /* 0x8, the level the decoders read; Init_ShockDriver clears it */
} ShockMgr;

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

typedef struct VibDecode {
    /* 0x0 */ unsigned char *buf;
    /* 0x4 */ unsigned short pos;
    /* 0x6 */ unsigned short acc;
    /* 0x8 */ unsigned short prev;
    /* 0xA */ unsigned short len;
    /* 0xC */ short time;
    /* 0xE */ short cnt;
} VibDecode;

typedef struct SHOCKREQUEST {
    /* 0x00 */ unsigned char flags;
    /* 0x01 */ unsigned char b1;
    /* 0x02 */ unsigned char b2;
    /* 0x03 */ unsigned char b3;
    /* 0x04 */ VibDecode shot;
    /* 0x14 */ VibDecode wave;
    /* 0x24 */ unsigned char c24;
    /* 0x25 */ unsigned char c25;
    /* 0x26 */ unsigned char shotRep;
    /* 0x27 */ unsigned char waveRep;
    /* 0x28 */ int key;
    /* 0x2C */ int arg;
    /* 0x30 */ struct SHOCKREQUEST *prev;
    /* 0x34 */ struct SHOCKREQUEST *next;
    /* 0x38 */ unsigned char voice;
    /* 0x39 */ unsigned char pad39[7];
} SHOCKREQUEST;

/* A voice-set file as ReadShockFile loads it: this 16-byte record, then the
 * file image (charFileManager.c:788-792 in the listing allocate size + 16 and
 * read to p + 16).  The image's halfwords at +2, +6 and +10 are the word
 * offsets of the wave, shot and voice tables, and +8 is the voice count
 * ShockDriver_GetShockVoice bounds by.  Field names are ours.  The image start
 * is a union of views: ROM stores it (shockdriver.c:114) ahead of the three
 * header loads, which needs that store to alias them, and a union member is
 * the alias-set-0 access that gives it (c-common.c:3172-3176). */
struct ShockVoiceSet {
    /* 0x0 */ union {
        int *word;
        unsigned short *half;
    } top;

    /* 0x4 */ int *wave;
    /* 0x8 */ int *shot;
    /* 0xC */ int *voice;
};

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

int Vibration_ShotDecode(SHOCKREQUEST *p, int level)
{
    unsigned char *q;
    int ret = 0;
    int n;
    unsigned short pos;
    unsigned char c;

    if ((p->flags & 1) == 0) {
        return 0;
    }
    if (p->shot.buf == 0) {
        p->flags &= 0xFE;
        return 0;
    }
    for (;;) {
        q = p->shot.buf + p->shot.pos;
        c = *q;
        if (p->shot.cnt != 0) {
            p->shot.time = p->shot.time + 1;
            if (c & 0x40) {
                if (p->b2 >> 7) {
                    if ((p->b2 >> 4) == 0xF) {
                        ret = 1;
                    } else {
                        ret = 0;
                    }
                    if (p->shot.time % ((p->b2 >> 4) - 5) != 0) {
                        ret = 1;
                    }
                } else {
                    ret = (p->shot.time % (9 - (p->b2 >> 4))) == 0;
                }
            }
            if (p->shot.time >= p->shot.len) {
                p->shot.cnt = 0;
                p->shot.pos = p->shot.pos + 1;
                c = p->shot.buf[p->shot.pos];
                if (c == 0x80) {
                    p->flags &= 0xFE;
                }
            }
            break;
        }

        if (c == 0x80) {
            p->flags &= 0xFE;
            break;
        }
        if (c & 0x80) {
            switch (c & 0x3F) {
            case 0x3F:
                p->shot.pos = p->shot.pos + ((signed char)q[1] + 2);
                if (level != 0) {
                    ((void (*)(SHOCKREQUEST *, unsigned char *))level)(p,
                                                                       p->shot.buf + p->shot.pos);
                }
                break;
            case 1:
                p->shot.pos = p->shot.pos + (signed char)q[1];
                break;
            case 2:
                p->shotRep = q[1];
                p->shot.pos = p->shot.pos + 2;
                break;
            case 3:
                pos = p->shot.pos;
                if (p->shotRep != 0) {
                    p->shotRep = p->shotRep - 1;
                    p->shot.pos = pos + (signed char)q[1];
                } else {
                    p->shot.pos = pos + 2;
                }
                break;
            }
        } else {
            n = c & 0x3F;
            p->shot.len = (p->shot.acc + n) * p->b3 / 64;
            p->shot.prev = p->shot.time;
            p->shot.cnt = p->shot.len - p->shot.time;
            p->shot.acc = p->shot.acc + n;
            if (p->shot.cnt <= 0) {
                p->shot.len = p->shot.time + 1;
                p->shot.cnt = 1;
            }
        }
    }
    return ret;
}

int Vibration_WaveDecode(SHOCKREQUEST *p, int level)
{
    unsigned char *q;
    int sum = 0;
    int ret = 0;
    int num = 0;
    int n;
    unsigned short pos;
    unsigned char c;

    if ((p->flags & 0x10) == 0) {
        return 0;
    }
    if (p->wave.buf == 0) {
        p->flags &= 0xEF;
        return 0;
    }
    for (;;) {
        q = p->wave.buf + p->wave.pos;
        c = *q;
        if (p->wave.cnt != 0) {
            p->wave.time = p->wave.time + 1;
            n = (p->c24 * (p->wave.len - p->wave.time) + p->c25 * (p->wave.time - p->wave.prev)) /
                p->wave.cnt;
            ret = n * p->b2 / 255;
            if (p->wave.time >= p->wave.len) {
                p->wave.cnt = 0;
                p->wave.pos = p->wave.pos + 2;
                p->c24 = p->c25;
                c = p->wave.buf[p->wave.pos];
                if (c == 0x80) {
                    p->flags &= 0xEF;
                }
            }
            break;
        }

        if (c == 0x80) {
            p->flags &= 0xEF;
            break;
        }
        if (c & 0x80) {
            switch (c & 0x3F) {
            case 0x3F:
                p->shot.pos = p->shot.pos + ((signed char)q[1] + 2);
                if (level != 0) {
                    ((void (*)(SHOCKREQUEST *, unsigned char *))level)(p, q);
                }
                break;
            case 0:
                p->wave.pos = p->wave.pos + (signed char)q[1];
                break;
            case 1:
                p->waveRep = q[1];
                p->wave.pos = p->wave.pos + 2;
                break;
            case 2:
                pos = p->wave.pos;
                if (p->waveRep != 0) {
                    p->waveRep = p->waveRep - 1;
                    p->wave.pos = pos + (signed char)q[1];
                } else {
                    p->wave.pos = pos + 2;
                }
                break;
            }
        } else {
            n = c & 0x3F;
            p->c25 = q[1];
            p->wave.prev = p->wave.time;
            p->wave.len = (p->wave.acc + n) * p->b3 / 64;
            p->wave.cnt = p->wave.len - p->wave.time;
            p->wave.acc = p->wave.acc + n;
            if (p->wave.cnt <= 0) {
                p->wave.cnt = 0;
                p->wave.pos = p->wave.pos + 2;
                num = num + 1;
                sum = sum + p->c25;
            } else if (num != 0) {
                p->c25 = sum / num;
                p->wave.len = p->wave.time + 1;
                p->wave.cnt = 1;
                p->wave.pos = p->wave.pos - 2;
                p->wave.acc = p->wave.acc - n;
                num = 0;
                sum = 0;
            }
        }
    }
    return ret;
}

extern char D_00551D98[]; /* "voice error? %d\n" */
/* Declared void ahead of their definitions: Shock_Request's inlined call sets
 * no return value (local-alloc then gives the next byte load $2, as the ROM). */
extern void Vibration_SetDecodeData(void *a0, int a1, int a2, unsigned char a3, unsigned char a4);
extern void ShockRequestBox_Regst(struct PadNode **head, struct PadNode *new_node);

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ShockDriver_GetShockVoice (row 88), with ShockDriver_GetShockVoiceSet (rows 77-79)
 * inlined inside it, and ShockRequestBox_Request into Shock_Request; each keeps its
 * plain definition at its own ROM position and the caller inlines these static
 * stand-ins, which collapse at layout. */
static inline int getShockVoiceSet(unsigned idx)
{
    if (idx >= (unsigned)System_shock_driver->count)
        return 0;
    return System_shock_driver->arr[idx];
}

static inline int getShockVoice(int voice, int n)
{
    int set = getShockVoiceSet(voice);
    return (set != 0 && (unsigned)n < *(unsigned short *)(*(int *)set + 8))
               ? *(int *)(set + 0xC) + n * 4
               : 0;
}

static inline SHOCKREQUEST *requestBoxRequest(ShockRequestBox *box, ShockParam *p, ShockParam v,
                                              int key, int arg)
{
    ShockVoiceSet *vs;
    SHOCKREQUEST *req;
    int wave;
    int shot;
    int t;

    if (System_shock_driver == 0)
        return 0;
    if (box == 0)
        return 0;

    vs = (ShockVoiceSet *)System_shock_driver->arr[v.voice];
    if (vs == 0)
        return 0;

    req = box->alloc(box->arg, arg);
    if (req == 0)
        return 0;

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
    if (t >= 0x100)
        t = 0xFF;
    req->b3 = t;
    ShockRequestBox_Regst((struct PadNode **)box, (struct PadNode *)req);
    return req;
}

SHOCKREQUEST *Shock_Request(ShockRequestBox *box, int level, ShockParam v, int key, int arg)
{
    ShockParam *p;
    SHOCKREQUEST *req;

    p = (ShockParam *)getShockVoice(v.voice, level);
    if (p == 0) {
        debug_StdPrintfDummy(D_00551D98, v.voice);
        return 0;
    }
    req = requestBoxRequest(box, p, v, key, arg);
    if (req != 0) {
        *(ShockParam **)((char *)req + 0x3C) = p;
    }
    return req;
}

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

    if (diff <= 0)
        goto Ldec;
    if (diff >= 0x29)
        goto Lff;
    if (n >= 0x3D)
        goto L40;
    if (cur >= 0x3D)
        goto L40;
    if (cur >= 0x33)
        goto Lquad;
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
    if (diff >= 0)
        goto Ltail;
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

void Init_ShockVoiceSet(ShockVoiceSet *set, int *data)
{
    set->top.word = data;
    set->voice = data + ((unsigned short *)data)[5];
    set->wave = data + ((unsigned short *)data)[1];
    set->shot = data + ((unsigned short *)data)[3];
}

void Vibration_SetDecodeData(void *a0, int a1, int a2, unsigned char a3, unsigned char a4)
{
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
    int *node = (int *)self[0];
    if (self[0x8 / 4] == 0) {
        goto end;
    }
    if (node == 0) {
        goto end;
    }
    do {
        int *cur = node;
        node = (int *)node[0x34 / 4];
        (*(void (**)(int, int))((char *)self + 8))((int)cur, self[0xC / 4]);
    } while (node != 0);
end:
    self[0] = 0;
}

void ShockRequestBox_Regst(struct PadNode **head, struct PadNode *new_node)
{
    struct PadNode *old = *head;
    new_node->prev = (struct PadNode *)0;
    new_node->next = old;
    if (old != (struct PadNode *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}

SHOCKREQUEST *ShockRequestBox_Request(ShockRequestBox *box, ShockParam *p, ShockParam v, int key,
                                      int arg)
{
    ShockVoiceSet *vs;
    SHOCKREQUEST *req;
    int wave;
    int shot;
    int t;

    if (System_shock_driver == 0)
        return 0;
    if (box == 0)
        return 0;

    vs = (ShockVoiceSet *)System_shock_driver->arr[v.voice];
    if (vs == 0)
        return 0;

    req = box->alloc(box->arg, arg);
    if (req == 0)
        return 0;

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
    if (t >= 0x100)
        t = 0xFF;
    req->b3 = t;
    ShockRequestBox_Regst((struct PadNode **)box, (struct PadNode *)req);
    return req;
}

extern int Vibration_WaveDecode(SHOCKREQUEST *p, int level);
extern int Vibration_ShotDecode(SHOCKREQUEST *p, int level);

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ShockRequestBox_DecodeRequest into Shock_Decode, so it is a public `inline` of the deferred
 * tail; until the tail's asm member (Init_Shock) is C the copy is emitted in
 * place as a plain function at its ROM position and the caller inlines this
 * static stand-in, which collapses at layout. */
static inline int decodeRequestBox(ShockRequestBox *box, unsigned char *pFlags,
                                   unsigned char *pLevel)
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
        sum += Vibration_WaveDecode(p, System_shock_driver->level);
        flags |= Vibration_ShotDecode(p, System_shock_driver->level);
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

int ShockRequestBox_DecodeRequest(ShockRequestBox *box, unsigned char *pFlags,
                                  unsigned char *pLevel)
{
    return decodeRequestBox(box, pFlags, pLevel);
}

inline SHOCKREQUEST *requestFree(ShockRequestBox *box, SHOCKREQUEST *req);

int *ShockRequestBox_EndRequestFree(int **a0)
{
    int *p;
    unsigned char b;
    if (a0 != 0) {
        p = *a0;
        if (p != 0) {
            do {
                b = *(unsigned char *)p;
                if (b == 0)
                    p = (int *)requestFree((ShockRequestBox *)a0, (SHOCKREQUEST *)p);
                else
                    p = (int *)p[0x34 / 4];
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
    if (head_ptr == 0)
        goto fail;
    p = *head_ptr;
    if (p == 0)
        goto fail;
    do {
        if (p[0x28 / 4] == key) {
            return p;
        }
        p = (int *)p[0x34 / 4];
    } while (p != 0);
fail:
    return 0;
}

int ShockRequestBox_RequestCancel(int a0_, int a1)
{
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

int ShockRequestBox_RequestDirectCancel(int *a0, int *a1)
{
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

/* What the bytes pin (listing lines 34-43, here and in Init_Shock's inlined
   copy): after the guards the manager is reached through the global it has
   just been stored in, which is the copy of the pointer the ROM keeps in a
   second register ($8 here, $4 in Init_Shock) and the reason Init_Shock
   reloads the table pointer before its loop. What they cannot pin: whether
   the store at line 37 and the accesses after it were spelled through the
   global or through a local the developer loaded from it. */
void Init_ShockDriver(ShockMgr *m, int *arr, int num)
{
    int i;
    if (m == 0)
        return;
    if (arr == 0)
        return;
    System_shock_driver = m;
    System_shock_driver->count = num;
    System_shock_driver->arr = arr;
    for (i = 0; i < num; i++)
        System_shock_driver->arr[i] = 0;
    System_shock_driver->level = 0;
}

int ShockDriver_VoiceSet_NumberRegist(unsigned int idx, int val)
{
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned int)base[0])
        return -1;
    ((int *)base[1])[idx] = val;
    return idx;
}

int ShockDriver_VoiceSet_Regist(int value)
{
    int i;
    for (i = 0; i < System_shock_driver->count; i++) {
        if (System_shock_driver->arr[i] == 0)
            break;
    }
    if (i == System_shock_driver->count)
        return -1;
    System_shock_driver->arr[i] = value;
    return i;
}

int ShockDriver_VoiceSet_Remove(unsigned int idx)
{
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned int)base[0])
        return -1;
    ((int *)base[1])[idx] = 0;
    return idx;
}

int ShockDriver_GetShockVoiceMax(int a0)
{
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

int ShockDriver_GetShockVoiceSet(unsigned idx)
{
    int *base = (int *)System_shock_driver;
    if (idx >= (unsigned)base[0])
        return 0;
    return ((int *)base[1])[idx];
}

int ShockDriver_GetShockVoice(int a0, int a1)
{
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

void Init_ShockEmulator(short *a0)
{
    a0[1] = 0;
    a0[0] = 0;
}

int ShockEmulator_EmulationShot(int a0, int a1)
{
    return a1;
}

unsigned short ShockEmulator_EmulationWave(short *a0, int a1)
{
    int sum = (unsigned short)a0[1] + a1;
    unsigned int q;
    short w;
    a0[1] = sum;
    if ((short)sum >= 0x40B)
        a0[1] = 0x40A;
    else if ((short)sum < 0)
        a0[1] = 0;
    w = a0[1];
    q = ((unsigned int)(w << 8)) / 0x40B;
    a0[0] = q;
    a0[1] = ((unsigned int)(w * 3)) >> 2;
    return (unsigned short)a0[0];
}

/* RECONSTRUCTION (the name is ours): the request pool header ShockRequestMemory
   holds, a count and the pool's base. The base is a pointer field: its store
   must not alias the count's, or Init_Shock's inlined copy could not issue it
   ahead of the count store as the ROM does (listing lines 637-638). */
typedef struct {
    int num;
    char *buf;
} ShockReqAlloc;

void Init_ShockRequestAlloc(ShockReqAlloc *a0, char *a1, int a2)
{
    int i;
    if (a0 != 0 && a1 != 0) {
        a0->num = a2;
        a0->buf = a1;
        for (i = 0; i < a2; i++) {
            a1[i * 0x40] = 0;
        }
    } else {
        a0->num = 0;
    }
}

void *Get_ShockRequestStruct(int *a0)
{
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

void Reset_ShockRequestStruct(char *p)
{
    *p = 0;
}

int ShockRevice_Wave(int a0, int a1)
{
    int diff = a0 - a1;

    if (diff <= 0)
        goto Ldec;
    if (diff >= 0x29)
        goto Lff;
    if (a0 >= 0x3D)
        goto L40;
    if (a1 >= 0x3D)
        goto L40;
    if (a1 >= 0x33)
        goto Lquad;
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
    if (diff >= 0)
        goto Lend;
    if (diff < -0x1E) {
        a0 = 0;
        goto Lend;
    }
    diff = diff * 0xFF / 0x1E + 0xFF;
    a0 = (diff < a1) ? diff : a0;
Lend:
    return a0;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * Init_ShockDriver and Init_ShockRequestAlloc into Init_Shock, so both are public
 * `inline`s; each keeps its plain definition at its own ROM position above and the
 * caller inlines this static stand-in, which collapses at layout. */
static inline void initShockDriver(ShockMgr *m, int *arr, int num)
{
    int i;
    if (m == 0)
        return;
    if (arr == 0)
        return;
    System_shock_driver = m;
    System_shock_driver->count = num;
    System_shock_driver->arr = arr;
    for (i = 0; i < num; i++)
        System_shock_driver->arr[i] = 0;
    System_shock_driver->level = 0;
}

static inline void initShockRequestAlloc(ShockReqAlloc *a0, char *a1, int a2)
{
    int i;
    if (a0 != 0 && a1 != 0) {
        a0->num = a2;
        a0->buf = a1;
        for (i = 0; i < a2; i++) {
            a1[i * 0x40] = 0;
        }
    } else {
        a0->num = 0;
    }
}

void Init_Shock(void)
{
    initShockDriver((ShockMgr *)ShockDriver, ShockVoiceSetBuf, 2);
    initShockRequestAlloc((ShockReqAlloc *)ShockRequestMemory, ShockRequest, 0x10);
}

int Shock_SetShockVoiceSet(int idx, int val)
{
    int *base = (int *)System_shock_driver;
    int *array;
    if ((unsigned int)idx < (unsigned int)base[0])
        goto store;
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
    initShockRequestBox(box, (int)Get_ShockRequestStruct, (int)Reset_ShockRequestStruct,
                        (int)ShockRequestMemory);
}

void Init_Controler(short *a0)
{
    a0[1] = 0;
    a0[0] = 0;
}

void Shock_RequestClear(int *self)
{
    int *node = (int *)self[0];
    if (self[0x8 / 4] == 0) {
        goto end;
    }
    if (node == 0) {
        goto end;
    }
    do {
        int *cur = node;
        node = (int *)node[0x34 / 4];
        (*(void (**)(int, int))((char *)self + 8))((int)cur, self[0xC / 4]);
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

void Vibration_SetDecodeEnd(unsigned char *p, int a1, int a2)
{
    if (a1)
        *p &= 0xFE;
    if (a2)
        *p &= 0xEF;
}
