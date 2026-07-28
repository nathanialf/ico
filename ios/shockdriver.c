#include "common.h"

typedef struct { int count; int *arr; } ShockMgr;

typedef struct ShockReq {
    /* 0x0 */ unsigned short out;
    /* 0x2 */ unsigned short acc;
    /* 0x4 */ unsigned char type;
    /* 0x5 */ unsigned char val;
} ShockReq;





extern int *D_00632190;
struct PadNode {
    char pad[0x30];
    struct PadNode *prev;
    struct PadNode *next;
};
extern int iosThreadInit();
extern int D_006A6DB0[];
extern int ShockDriver_GetShockVoiceMax(int a0, int a1);

void Vibration_ShotDecode(int key)
{
    if (key == 0)
    {
        return;
    }
    for (;;)
    {
        int *p = D_006A6DB0;
        int *entry;
        int i = 0xF;
        while (1)
        {
            if (*p == key)
            {
                goto found;
            }
            i--;
            if (i == -1)
            {
                goto notfound;
            }
            p = (int *)((char *) p + 0x18);
        }
    notfound:
        entry = 0;
        goto check;
    found:
        entry = p;
    check:
        if (entry == 0)
        {
            break;
        }
        ShockDriver_GetShockVoiceMax(entry[0x4 / 4], key);
        entry[0] = 0;
    }
}

void Vibration_WaveDecode(void)
{
    int *p = D_006A6DB0;
    int i;
    for (i = 0xF; i != -1; i--) {
        int x = p[0];
        if (x != 0) {
            ShockDriver_GetShockVoiceMax(p[1], x);
            p[0] = 0;
        }
        p = (int *)((char *)p + 0x18);
    }
}

int *Shock_Request(int key, unsigned int val)
{
    int *p = D_006A6DB0;
    int *rv;
    int i;
    val = val & 0xFF;
    i = 0xF;
    while (1) {
        if (*p == key) goto found;
        i--;
        if (i == -1) goto notfound;
        p = (int *)((char *)p + 0x18);
    }
notfound:
    rv = 0;
    goto end;
found:
    rv = p;
end:
    if (rv != 0) {
        *(unsigned char *)((char *)rv + 0x14) = val;
    }
    return rv;
}

extern char D_00281630[];
extern int D_006A6D90[];
extern void iosMsgQueueDestroy(int *a, int *b, int c);
extern void iosMsgRecv(int *a, void *b, int c);
extern void iosPadRead(void);

void Shock_SetMotor(void)
{
    int local_buf;
    iosMsgQueueDestroy(D_00281630, D_006A6D90, 8);
    while (1) {
        iosMsgRecv(D_00281630, &local_buf, 1);
        iosPadRead();
    }
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", func_0013BA68);

void Init_ShockVoiceSet(void) {}

void Vibration_SetDecodeData(void) {}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockRequestBox);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_Clear);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_Regst);

extern void func_0024EBC8(int a0, int a1, void *box);

void ShockRequestBox_Request(int a0, int a1, ShockReq *box, int a3, int a4)
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
        func_0024EBC8(a3, a4, &box->type);
    }
}

void ShockRequestBox_DecodeRequest(int **a0, int *a1) {
    do { } while (0);
    a0[0] = a1;
    a0[3] = a1 + *(unsigned short *)((char *)a1 + 0xA);
    a0[1] = a1 + *(unsigned short *)((char *)a1 + 0x2);
    a1 = a1 + *(unsigned short *)((char *)a1 + 0x6);
    a0[2] = a1;
}

void ShockRequestBox_EndRequestFree(void *a0, int a1, int a2, char a3, char a4) {
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

void ShockRequestBox_VoiceSetUseRequestFree(int *a0, int a1, int a2, int a3)
{
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)&iosThreadInit;
    }
    a0[2] = a2;
    a0[3] = a3;
}

void ShockRequestBox_GetRequest(int *self)
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

void ShockRequestBox_RequestCancel(struct PadNode **head, struct PadNode *new_node) {
    struct PadNode *old = *head;
    new_node->prev = (struct PadNode *)0;
    new_node->next = old;
    if (old != (struct PadNode *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockRequestBox_RequestDirectCancel);

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockDriver);

extern int iosThreadGetPri(void *a0, int *p);

int *ShockDriver_VoiceSet_NumberRegist(int **a0) {
    int *p; unsigned char b;
    if (a0 != 0) {
        p = *a0;
        if (p != 0) {
            do {
                b = *(unsigned char *)p;
                if (b == 0) p = (int *)iosThreadGetPri(a0, p);
                else        p = (int *)p[0x34 / 4];
            } while (p != 0);
        }
    }
    return *a0;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockDriver_VoiceSet_Regist);

int *ShockDriver_VoiceSet_Remove(int **head_ptr, int key)
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

int ShockDriver_GetShockVoiceMax(int a0_, int a1) {
    int *a0 = (int *)a0_;
    int *node;
    int *next;
    int *prev;
    int (*fn)(int *, int);
    node = ShockDriver_VoiceSet_Remove((int **)a0, a1);
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

int ShockDriver_GetShockVoiceSet(int *a0, int *a1) {
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

void ShockDriver_GetShockVoice(int *a0, int a1, int a2)
{
    int *b;
    int i;
    if (a0 == 0) return;
    if (a1 == 0) return;
    b = a0;
    a0 = 0;
    b[1] = a1;
    D_00632190 = (ShockMgr *)b;
    b[0] = a2;
    for (i = 0; i < a2; i++) *(int *)(b[1] + i*4) = 0;
    b[2] = 0;
}

int Init_ShockEmulator(unsigned int idx, int val)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = val;
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", ShockEmulator_EmulationShot);

int ShockEmulator_EmulationWave(unsigned int idx)
{
    int *base = (int *)D_00632190;
    if (idx >= (unsigned int)base[0]) return -1;
    ((int *)base[1])[idx] = 0;
    return idx;
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Init_ShockRequestAlloc);

int Get_ShockRequestStruct(unsigned idx) {
    int *base = (int *)D_00632190;
    if (idx >= (unsigned)base[0]) return 0;
    return ((int *)base[1])[idx];
}

INCLUDE_ASM("asm/nonmatchings/ios/shockdriver", Reset_ShockRequestStruct);

void ShockRevice_Wave(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}

int Init_Shock(int a0, int a1)
{
    return a1;
}

