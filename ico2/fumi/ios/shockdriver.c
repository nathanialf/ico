#include "shockdriver.h"
#include <libpad.h>
#include "debug.h"

struct PadNode { /* field names derived */
    char pad[48];
    struct PadNode *prev;
    struct PadNode *next;
}; /* derived name */

typedef struct ShockReq { /* field names derived */
    /* 0x0 */ unsigned short out;
    /* 0x2 */ unsigned short acc;
    /* 0x4 */ unsigned char type;
    /* 0x5 */ unsigned char val;
} ShockReq; /* derived name */

typedef struct VibDecode { /* field names derived */
    /* 0x0 */ unsigned char *buf;
    /* 0x4 */ unsigned short pos;
    /* 0x6 */ unsigned short acc;
    /* 0x8 */ unsigned short prev;
    /* 0xA */ unsigned short len;
    /* 0xC */ short time;
    /* 0xE */ short cnt;
} VibDecode; /* derived name */

typedef struct SHOCKREQUEST { /* field names derived */
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
} SHOCKREQUEST; /* derived name */

/* A voice-set file as ReadShockFile loads it: this 16-byte record, then the
 * file image (charFileManager.c allocates size + 16 and reads to p + 16).  The
 * image's halfwords at +2, +6 and +10 are the word offsets of the shot, wave
 * and voice tables, and +8 is the voice count ShockDriver_GetShockVoice bounds
 * by.  The image start is a union of its word and halfword views. */
struct ShockVoiceSet { /* field names derived */

    /* 0x0 */ union {
        int *word;
        unsigned short *half;
    } top;

    /* 0x4 */ int *shot;
    /* 0x8 */ int *wave;
    /* 0xC */ int *voice;
}; /* derived name */

typedef struct ShockParam { /* field names derived */
    /* 0x0 */ unsigned char voice;
    /* 0x1 */ unsigned char b1;
    /* 0x2 */ unsigned char b2;
    /* 0x3 */ unsigned char b3;
} ShockParam; /* derived name */

typedef struct ShockRequestBox { /* field names derived */
    /* 0x0 */ void *head;
    /* 0x4 */ void *(*alloc)(void *, int);
    /* 0x8 */ void (*free)(SHOCKREQUEST *, void *);
    /* 0xC */ void *arg;
} ShockRequestBox; /* derived name */

/* .data, all zero: the voice set manager record and the request pool.
   .sdata, all zero: the current manager, the common and stage voice sets
   charFileManager loads, the manager's two-slot voice set table and the
   request allocator record. */
int ShockDriver[4] = {0};

char ShockRequest[1024] = {0};

ShockMgr *System_shock_driver = 0;

char *ShockVoiceSetCommon = 0;

char *ShockVoiceSetStage = 0;

int ShockVoiceSetBuf[2] = {0};

int ShockRequestMemory[2] = {0};

int Vibration_ShotDecode(SHOCKREQUEST *p, void (*callback)(SHOCKREQUEST *req, unsigned char *cmd))
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
                if (callback != 0) {
                    callback(p, p->shot.buf + p->shot.pos);
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

int Vibration_WaveDecode(SHOCKREQUEST *p, void (*callback)(SHOCKREQUEST *req, unsigned char *cmd))
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
                if (callback != 0) {
                    callback(p, q);
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

/* declared void ahead of its definition */
extern void ShockRequestBox_Regst(struct PadNode **head, struct PadNode *new_node);

/* file-static copies of ShockDriver_GetShockVoiceSet, ShockDriver_GetShockVoice
 * and ShockRequestBox_Request, which Shock_Request inlines */
static inline int getShockVoiceSet(unsigned idx) /* derived name */
{
    if (idx >= (unsigned)System_shock_driver->count)
        return 0;
    return System_shock_driver->arr[idx];
}

static inline int getShockVoice(int voice, int n) /* derived name */
{
    int set = getShockVoiceSet(voice);
    return (set != 0 && (unsigned)n < *(unsigned short *)(*(int *)set + 8))
               ? *(int *)(set + 0xC) + n * 4
               : 0;
}

static inline SHOCKREQUEST *requestBoxRequest(ShockRequestBox *box, ShockParam *p, ShockParam v,
                                              int key, int arg) /* derived name */
{
    ShockVoiceSet *vs;
    SHOCKREQUEST *req;
    int shot;
    int wave;
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
        shot = (int)vs->shot + vs->shot[p->voice];
    } else {
        shot = 0;
    }
    if (p->b1 != 0xFF) {
        wave = (int)vs->wave + vs->wave[p->b1];
    } else {
        wave = 0;
    }
    Vibration_SetDecodeData(req, shot, wave, 0xFF, 0x40);
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

SHOCKREQUEST *Shock_Request(ShockRequestBox *box, int voice, ShockParam v, int key, int arg)
{
    ShockParam *p;
    SHOCKREQUEST *req;

    p = (ShockParam *)getShockVoice(v.voice, voice);
    if (p == 0) {
        debug_StdPrintfDummy("voice error? %d\n", v.voice);
        return 0;
    }
    req = requestBoxRequest(box, p, v, key, arg);
    if (req != 0) {
        *(ShockParam **)((char *)req + 0x3C) = p;
    }
    return req;
}

void Shock_SetMotor(int flags, int level, ShockReq *box, int port, int slot)
{
    int n = level & 0xFF;
    int type = flags & 0xFF;
    int cur = box->out;
    int diff = n - cur;
    int r = n;
    short w;
    int sum;
    unsigned int outv;

    if (diff <= 0)
        goto Ldec;
    if (diff >= 41)
        goto Lff;
    if (n >= 61)
        goto L40;
    if (cur >= 61)
        goto L40;
    if (cur >= 51)
        goto Lquad;
Lff:
    r = 0xFF;
    goto Ltail;
Lquad:
    diff = 60 - n;
    diff = (diff * 0xFF) * diff / 100;
    r = (cur < diff) ? diff : n;
    goto Ltail;
L40:
    diff = diff * 0xFF / 40;
    r = (cur < diff) ? diff : n;
    goto Ltail;
Ldec:
    if (diff >= 0)
        goto Ltail;
    if (diff < -30) {
        r = 0;
        goto Ltail;
    }
    diff = diff * 0xFF / 30 + 0xFF;
    r = (diff < cur) ? diff : n;
Ltail:
    n = r & 0xFF;
    sum = box->acc + n;
    box->acc = sum;
    if ((short)sum >= 1035) {
        box->acc = 1034;
    } else if ((short)sum < 0) {
        box->acc = 0;
    }
    w = (short)box->acc;
    outv = ((unsigned int)w << 8) / 1035;
    box->type = type;
    box->acc = (unsigned int)(w * 3) >> 2;
    box->val = n;
    box->out = outv;
    if (port >= 0) {
        scePadSetActDirect(port, slot, &box->type);
    }
}

void Init_ShockVoiceSet(ShockVoiceSet *set, int *data)
{
    set->top.word = data;
    set->voice = data + ((unsigned short *)data)[5];
    set->shot = data + ((unsigned short *)data)[1];
    set->wave = data + ((unsigned short *)data)[3];
}

void Vibration_SetDecodeData(void *req, int shot, int wave, unsigned char b2, unsigned char b3)
{
    char *p = (char *)req;
    p[0x3] = b3;
    p[0x0] = 0x11;
    *(int *)(p + 0x4) = shot;
    *(int *)(p + 0x14) = wave;
    p[0x2] = b2;
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

/* a file-static copy of Init_ShockRequestBox, which Init_Player inlines */
static inline void initShockRequestBox(int *box, int alloc, int free, int arg) /* derived name */
{
    box[0] = 0;
    if (alloc) {
        box[1] = alloc;
    } else {
        box[1] = (int)&dumyAllocFunc;
    }
    box[2] = free;
    box[3] = arg;
}

void Init_ShockRequestBox(int *box, int alloc, int free, int arg)
{
    initShockRequestBox(box, alloc, free, arg);
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
    int shot;
    int wave;
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
        shot = (int)vs->shot + vs->shot[p->voice];
    } else {
        shot = 0;
    }
    if (p->b1 != 0xFF) {
        wave = (int)vs->wave + vs->wave[p->b1];
    } else {
        wave = 0;
    }
    Vibration_SetDecodeData(req, shot, wave, 0xFF, 0x40);
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

/* a file-static copy of ShockRequestBox_DecodeRequest, which Shock_Decode
 * inlines */
static inline int decodeRequestBox(ShockRequestBox *box, unsigned char *pFlags,
                                   unsigned char *pLevel) /* derived name */
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
        sum += Vibration_WaveDecode(p, System_shock_driver->callback);
        flags |= Vibration_ShotDecode(p, System_shock_driver->callback);
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

static inline SHOCKREQUEST *requestFree(ShockRequestBox *box, SHOCKREQUEST *req);

int *ShockRequestBox_EndRequestFree(int **box)
{
    int *p;
    unsigned char b;
    if (box != 0) {
        p = *box;
        if (p != 0) {
            do {
                b = *(unsigned char *)p;
                if (b == 0)
                    p = (int *)requestFree((ShockRequestBox *)box, (SHOCKREQUEST *)p);
                else
                    p = (int *)p[0x34 / 4];
            } while (p != 0);
        }
    }
    return *box;
}

static inline SHOCKREQUEST *requestFree(ShockRequestBox *box, SHOCKREQUEST *req)
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

int ShockRequestBox_RequestCancel(int boxp, int key)
{
    int *box = (int *)boxp;
    int *node;
    int *next;
    int *prev;
    int (*fn)(int *, int);
    node = ShockRequestBox_GetRequest((int **)box, key);
    if (node == 0) {
        return 0;
    }
    prev = (int *)node[0x30 / 4];
    if (prev != 0) {
        prev[0x34 / 4] = node[0x34 / 4];
        next = (int *)node[0x34 / 4];
    } else {
        next = (int *)node[0x34 / 4];
        box[0] = (int)next;
    }
    if (next != 0) {
        next[0x30 / 4] = node[0x30 / 4];
    }
    fn = (int (*)(int *, int))box[8 / 4];
    if (fn != 0) {
        fn(node, box[0xC / 4]);
    }
    return 1;
}

int ShockRequestBox_RequestDirectCancel(int *box, int *req)
{
    int *next;
    int *prev;
    int (*fn)(int *, int);
    if (req == 0) {
        return 0;
    }
    prev = (int *)req[0x30 / 4];
    if (prev != 0) {
        prev[0x34 / 4] = req[0x34 / 4];
        next = (int *)req[0x34 / 4];
    } else {
        next = (int *)req[0x34 / 4];
        box[0] = (int)next;
    }
    if (next != 0) {
        next[0x30 / 4] = req[0x30 / 4];
    }
    fn = (int (*)(int *, int))box[8 / 4];
    if (fn != 0) {
        fn(req, box[0xC / 4]);
    }
    return 1;
}

/* the driver manager's setup, which Init_ShockDriver and Init_Shock
   inline; after the guards the manager is reached through the global it
   has just been stored in */
static inline void initShockDriver(ShockMgr *m, int *arr, int num) /* derived name */
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
    System_shock_driver->callback = 0;
}

void Init_ShockDriver(ShockMgr *m, int *arr, int num)
{
    initShockDriver(m, arr, num);
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

int ShockDriver_GetShockVoiceMax(int idx)
{
    int p;
    if ((unsigned int)idx < (unsigned int)System_shock_driver->count) {
        goto body;
    }
    p = 0;
    goto check;
body:
    p = System_shock_driver->arr[idx];
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

int ShockDriver_GetShockVoice(int idx, int n)
{
    int p;
    if ((unsigned int)idx < (unsigned int)System_shock_driver->count) {
        goto body;
    }
    p = 0;
    goto check;
body:
    p = System_shock_driver->arr[idx];
check:
    if (p == 0) {
        goto ret_a;
    }
    if ((unsigned int)n >= (unsigned int)*(unsigned short *)(*(int *)p + 8)) {
        goto ret_b;
    }
    return *(int *)(p + 0xC) + n * 4;
ret_b:
    return 0;
ret_a:
    return 0;
}

void Init_ShockEmulator(short *emu)
{
    emu[1] = 0;
    emu[0] = 0;
}

int ShockEmulator_EmulationShot(int emu, int level)
{
    return level;
}

unsigned short ShockEmulator_EmulationWave(short *emu, int level)
{
    int sum = (unsigned short)emu[1] + level;
    unsigned int q;
    short w;
    emu[1] = sum;
    if ((short)sum >= 1035)
        emu[1] = 1034;
    else if ((short)sum < 0)
        emu[1] = 0;
    w = emu[1];
    q = ((unsigned int)(w << 8)) / 1035;
    emu[0] = q;
    emu[1] = ((unsigned int)(w * 3)) >> 2;
    return (unsigned short)emu[0];
}

/* the request pool header ShockRequestMemory holds: a count and the pool's
   base */
typedef struct { /* field names derived */
    int num;
    char *buf;
} ShockReqAlloc; /* derived name */

/* the request pool's setup, which Init_ShockRequestAlloc and Init_Shock
   inline */
static inline void initShockRequestAlloc(ShockReqAlloc *alloc, char *buf,
                                         int num) /* derived name */
{
    int i;
    if (alloc != 0 && buf != 0) {
        alloc->num = num;
        alloc->buf = buf;
        for (i = 0; i < num; i++) {
            buf[i * 64] = 0;
        }
    } else {
        alloc->num = 0;
    }
}

void Init_ShockRequestAlloc(ShockReqAlloc *alloc, char *buf, int num)
{
    initShockRequestAlloc(alloc, buf, num);
}

void *Get_ShockRequestStruct(int *alloc)
{
    unsigned char *p = (unsigned char *)alloc[1];
    int i;
    for (i = 0; i < alloc[0]; i++) {
        if (*p == 0) {
            return p;
        }
        p += 64;
    }
    return 0;
}

void Reset_ShockRequestStruct(char *p)
{
    *p = 0;
}

int ShockRevice_Wave(int level, int cur)
{
    int diff = level - cur;

    if (diff <= 0)
        goto Ldec;
    if (diff >= 41)
        goto Lff;
    if (level >= 61)
        goto L40;
    if (cur >= 61)
        goto L40;
    if (cur >= 51)
        goto Lquad;
Lff:
    level = 0xFF;
    goto Lend;
Lquad:
    diff = 60 - level;
    diff = (diff * 0xFF) * diff / 100;
    level = (cur < diff) ? diff : level;
    goto Lend;
L40:
    diff = diff * 0xFF / 40;
    level = (cur < diff) ? diff : level;
    goto Lend;
Ldec:
    if (diff >= 0)
        goto Lend;
    if (diff < -30) {
        level = 0;
        goto Lend;
    }
    diff = diff * 0xFF / 30 + 0xFF;
    level = (diff < cur) ? diff : level;
Lend:
    return level;
}

void Init_Shock(void)
{
    initShockDriver((ShockMgr *)ShockDriver, ShockVoiceSetBuf, 2);
    initShockRequestAlloc((ShockReqAlloc *)ShockRequestMemory, ShockRequest, 16);
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

void Init_Controler(short *motor)
{
    motor[1] = 0;
    motor[0] = 0;
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

void Vibration_SetDecodeEnd(unsigned char *p, int shotEnd, int waveEnd)
{
    if (shotEnd)
        *p &= 0xFE;
    if (waveEnd)
        *p &= 0xEF;
}
