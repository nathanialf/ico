#include "common.h"

typedef struct { int count; int *arr; } ShockMgr;
extern ShockMgr *D_0062A490;

extern int D_006A0930[];
extern int ShockDriver_GetShockVoiceMax(int a0, int a1);

void Vibration_ShotDecode(int key)
{
    if (key == 0)
    {
        return;
    }
    for (;;)
    {
        int *p = D_006A0930;
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
    int *p = D_006A0930;
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
    int *p = D_006A0930;
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

extern int D_006A0910[];
extern void iosMsgQueueDestroy(int *a, int *b, int c);
extern void iosMsgRecv(int *a, void *b, int c);
extern void iosPadRead(void);

extern char D_0027D9B0[];

void Shock_SetMotor(void)
{
    int local_buf;
    iosMsgQueueDestroy(D_0027D9B0, D_006A0910, 8);
    while (1) {
        iosMsgRecv(D_0027D9B0, &local_buf, 1);
        iosPadRead();
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", func_0013B550);

void Init_ShockVoiceSet(void) {
}

void Vibration_SetDecodeData(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockRequestBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Clear);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Regst);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Request);

void ShockRequestBox_DecodeRequest(int **a0, int *a1) {
    do { } while (0);
    a0[0] = a1;
    a0[3] = a1 + *(unsigned short *)((char *)a1 + 0xA);
    a0[1] = a1 + *(unsigned short *)((char *)a1 + 0x2);
    a1 = a1 + *(unsigned short *)((char *)a1 + 0x6);
    a0[2] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_EndRequestFree);

extern void iosThreadInit(void);

void ShockRequestBox_VoiceSetUseRequestFree(int *a0, int a1, int a2, int a3) {
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)iosThreadInit;
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

void ShockRequestBox_RequestCancel(void *a0, void *a1) {
    void *head = *(void **)a0;
    *(int *)((char *)a1 + 0x30) = 0;
    *(void **)((char *)a1 + 0x34) = head;
    if (head) {
        *(void **)((char *)head + 0x30) = a1;
    }
    *(void **)a0 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_RequestDirectCancel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockDriver);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_NumberRegist);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_Regist);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoice);

int Init_ShockEmulator(int a0, int a1) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return -1;
body:
    D_0062A490->arr[a0] = a1;
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockEmulator_EmulationShot);

int ShockEmulator_EmulationWave(int a0) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return -1;
body:
    D_0062A490->arr[a0] = 0;
    return a0;
}

int Init_ShockRequestAlloc(int a0) {
    int p;
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    p = 0;
    goto check;
body:
    p = D_0062A490->arr[a0];
check:
    if (p != 0) {
        p = *(int *)p;
        return *(unsigned short *)(p + 8);
    }
    return 0;
}


int Get_ShockRequestStruct(int a0) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return 0;
body:
    return D_0062A490->arr[a0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Reset_ShockRequestStruct);

void ShockRevice_Wave(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}

int Init_Shock(int a0, int a1) {
    return a1;
}
