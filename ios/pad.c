#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/pad", controler_stable_check);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevInit);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevReadFunc);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadRead);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadNormalizeStick);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetStick_func);
INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadActRequest);
extern unsigned char padDevMgrMsgQ[];
extern int iosMsgSend(void *a0, int a1, int a2);

int iosPadDevRead(void) {
    iosMsgSend(padDevMgrMsgQ, 0, 0);
    return 0;
}
extern unsigned char iosPadDev[];

int iosPadGetPort(int a0, int a1) {
    return *(int *)&iosPadDev[a1 * 0x200];
}
int iosPadGetSlot(int a0, int a1) {
    int *base = (int *)&iosPadDev[a1 * 0x200];
    return base[1];
}
int iosPadGetDevice(int a, int b)
{
    int *p = iosPadDev;
    int count = 0;
    do {
        count++;
        if (p[0] == a) {
            if (p[1] == b) {
                return p[2];
            }
        }
        p = (int *)((char *)p + 0x200);
    } while (count < 2);
    return -1;
}
int iosPadConnect(void *a0, int a1, int a2, int a3) {
    int *p = (int *)a0;
    p[1] = a3;
    p[0] = (int)&iosPadDev[a2 * 0x200];
    return 0;
}
extern void _PushVu0Registers();
extern void _PopVu0Registers();
extern int iosPadGetStick_func(void *dev, void *out, int mode, int a3, int a4, int a5);

int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5)
{
    int rv;
    _PushVu0Registers();
    rv = iosPadGetStick_func(dev, out, mode, a3, a4, a5);
    _PopVu0Registers();
    return rv;
}
typedef union { float f[4]; long long ll[2]; } Vec4;
extern int matrixptr;
extern void sceVu0TransposeMatrix(void *a0, void *a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);

void iosPadStickCameraCoord(void *a0, float *a1)
{
    Vec4 v = {{ a1[3], 0.0f, -a1[4], 0.0f }};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}
extern int D_0063C19C;

void iosPadEnable(void)
{
    D_0063C19C = 1;
}
void iosPadDisable(void) {
    D_0063C19C = 0;
}
int iosPadEnableGet(void) {
    return D_0063C19C;
}
extern int ShockVoiceSetCommon;
extern unsigned char D_006BCD58[];
extern void Init_Controler(void *a0);
extern void Init_Player(void *a0);
extern void Init_Shock();
extern int Shock_SetShockVoiceSet(int a0, int a1);
extern void memset(void *a0, int a1, int a2);

void iosPadActInit(void) {
    unsigned char *base;
    unsigned char *p;
    int i;
    memset(D_006BCD58, 0, 0x180);
    Init_Shock();
    Shock_SetShockVoiceSet(0, ShockVoiceSetCommon);
    base = iosPadDev;
    p = base + 0x1B8;
    i = 1;
    do {
        Init_Controler(p);
        i--;
        Init_Player(p - 0x14);
        p += 0x200;
    } while (i >= 0);
}
extern int D_006BCD58__pn[] __asm__("D_006BCD58");
extern int ShockRequestBox_RequestCancel(int a0, int a1);

void iosPadActStop(int key)
{
    if (key == 0)
    {
        return;
    }
    for (;;)
    {
        int *p = D_006BCD58__pn;
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
        ShockRequestBox_RequestCancel(entry[0x4 / 4], key);
        entry[0] = 0;
    }
}
void iosPadActStopAll(void)
{
    int *p = D_006BCD58__pn;
    int i;
    for (i = 0xF; i != -1; i--) {
        int x = p[0];
        if (x != 0) {
            ShockRequestBox_RequestCancel(p[1], x);
            p[0] = 0;
        }
        p = (int *)((char *)p + 0x18);
    }
}
int *iosPadActVolumeSet(int key, unsigned int val)
{
    int *p = D_006BCD58__pn;
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
extern char D_0029C0B0__pn[] __asm__("padDevMgrMsgQ");
extern int D_006BCD38[];
extern void iosMsgQueueCreate(int *a, int *b, int c);
extern void iosMsgRecv(int *a, void *b, int c);
extern void iosPadDevReadFunc(void);

void iosPadDevManager(void)
{
    int local_buf;
    iosMsgQueueCreate(D_0029C0B0__pn, D_006BCD38, 8);
    while (1) {
        iosMsgRecv(D_0029C0B0__pn, &local_buf, 1);
        iosPadDevReadFunc();
    }
}
typedef struct {
    unsigned char mode;
    unsigned char b1;
    unsigned char volume;
    unsigned char b3;
} ShockPrm;

typedef struct {
    int key;            /* 0x00 */
    int box;            /* 0x04 */
    int player;         /* 0x08 */
    ShockPrm prm;       /* 0x0C */
    short life;         /* 0x10 */
    short tick;         /* 0x12 */
    unsigned char volume; /* 0x14 */
    unsigned char pad[3];
} PadAct;

typedef struct ShockRequest {
    ShockPrm prm;                   /* 0x00 */
    unsigned char pad[0x38];
    struct ShockRequest *org;       /* 0x3C */
} ShockRequest;

extern ShockRequest *ShockRequestBox_GetRequest(int box, int key);
extern int Shock_Request(int box, int player, ShockPrm prm, int key, int a4);

static inline void setRequestVolume(ShockRequest *req, unsigned int volume)
{
    unsigned int v;
    v = volume * req->org->prm.volume / 255;
    if (v > 255) {
        v = 255;
    }
    req->prm.volume = v;
}

void iosPadActTickProc(void)
{
    PadAct *p = (PadAct *)D_006BCD58;
    int i;
    for (i = 0xF; i != -1; i--) {
        if (p->key != 0) {
            ShockRequest *req = ShockRequestBox_GetRequest(p->box, p->key);
            if (req == 0) {
                p->tick++;
                if (p->life == 0 || p->tick < p->life) {
                    Shock_Request(p->box, p->player, p->prm, p->key, 0);
                } else {
                    p->key = 0;
                }
            } else {
                setRequestVolume(req, p->volume);
            }
        }
        p++;
    }
}
void iosPadDisconWait(void) {}
void iosPadErrorWait(void) {}
