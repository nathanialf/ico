#include "common.h"
#include "cdvd.h"
#include "message.h"
#include "thread.h"
#include "Texture.h"

struct jSub { /* sub-object at offset 0xC of the argument */
    char _0[0x2C];
    int field2C;
    int n;
    int field34;
    char _38[4];
    void *field3C;
    void *field40;
};

struct jArg { /* the object queued on jimakuMsgQ */
    int cmd;  /* 0x0 command: 0 begin, 1 next, 2 jump, 3 end */
    int _4;
    int done;        /* 0x8 cleared while the manager services it, 1 when finished */
    struct jSub sub; /* 0xC */
};

struct jNode {
    char _0[4];
    int status;
    int field8;
    int fieldC;
    char _10[4];
    int field14;
};

struct jWayGroup { /* D_006C1E80 element, stride 0x18 */
    int f0;
    int f4;
    int f8;
    int fC;
    struct jWayGroup *node; /* the next group in the ring */
    char *buf;              /* 0x14 its 0x8C40 read buffer */
};

extern struct jWayGroup D_006C1E80[];
extern void jimakuMgrNext(struct jArg *p);
extern char D_006E5000[];
extern char D_006E5038[];
extern char D_006E5070[];
extern int jimakuMsgQ[];
extern int D_0028F4E8[];
extern int D_0028F4C0[];
extern int D_0063A960;
extern int jimakuMsgBuf[2];
extern char D_005540F8[];
extern void jimakuMgrBegin(struct jArg *p);
extern int D_0063A964;
extern int jimakuOn;

#include "jimaku.h"

typedef struct JimTex {
    char _0[0x1C];
    int tex; /* 0x1C */
    char _20[0x24];
    int centre; /* 0x44 */
    int h;      /* 0x48 */
    int w;      /* 0x4C */
    int y;      /* 0x50 */
    int x;      /* 0x54 */
    char _58[4];
    int u;  /* 0x5C */
    int tw; /* 0x60 */
    int th; /* 0x64 */
    int v;  /* 0x68 */
} JimTex;

typedef struct JimCol {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} JimCol;

extern JimCol D_0063A970[];
extern unsigned char D_0028F720[];
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int reg, long long v);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int on);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int on);
/* kept local: this TU's uses of gif_SpriteSensitiveOffset do not fit the prototype in GifPacket.h */
extern void gif_SpriteSensitiveOffset(int *dst, unsigned int rgba, int *src, JimCol *col, int flag);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);

void display_texture(JimTex *t)
{
    JimCol col;
    int dst[4];
    int src[4];

    col = D_0063A970[0];
    src[0] = (t->u << 4) + 8;
    src[1] = (t->v << 4) + 8;
    src[2] = t->th << 4;
    src[3] = t->tw << 4;
    dst[2] = t->w << 4;
    dst[3] = t->h << 3;
    if (dst[2] == 0)
        dst[2] = src[2];
    if (dst[3] == 0)
        dst[3] = src[3] >> 1;
    dst[3] = dst[3] * 2;
    if (t->centre != 0)
        dst[0] = (10240 - dst[2]) / 2 - 5120;
    else
        dst[0] = (t->x - 320) << 4;
    dst[1] = (t->y - 112) << 4;
    tex_TransTexture(t->tex, 11);
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 7, 0);
    gif_SetGsReg(74, 0);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    col.r = ~D_0028F720[0xD0];
    col.g = ~D_0028F720[0xD4];
    col.b = ~D_0028F720[0xD8];
    gif_SpriteSensitiveOffset(dst, 0xFFFFFF9B, src, &col, 1);
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_EndPacket();
}

void iosCdvdBackGroundReadJimaku(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1)
        large = v1;
    large = ((large >> 11) + 1) << 11;
    iosCdvdBackGroundRead(self, a1, large);
    iosCdvdBackGroundMgrSeek(self, *(int *)((char *)self + 0x110) + size);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/jimaku", jimakuHandler);

extern char D_006C1F00[][0x8C40];
extern int NonLinearCameraMove;
extern int D_0063AA00;
extern char D_0055FBD0[][32];
extern int jimakuHandler(int self, struct jArg *p);

void jimakuMgrBegin(struct jArg *p)
{
    struct jSub *sub = &p->sub;
    int st = 0;
    int i;
    struct jWayGroup *g;

    if (D_0028F4C0[10] != 0) {
        return;
    }
    D_0028F4C0[10] = 1;
    iosSemaCreate(D_006E5000, 0, 1, 0);
    iosSemaCreate(D_006E5038, 0, 1, 0);
    iosSemaCreate(D_006E5070, 0, 1, 0);
    for (i = 0; i < 4; i++) {
        g = &D_006C1E80[i];
        g->node = &D_006C1E80[(i + 1) % 4];
        g->buf = D_006C1F00[i];
    }
    sub->n = 0;
    D_006C1E80[0].f0 = -1;
    D_006C1E80[0].f4 = 3;
    D_006C1E80[0].f8 = -1;
    sub->field34 = 1;
    switch (NonLinearCameraMove) {
    case 2:
        st = 0;
        break;
    case 3:
        st = 2;
        break;
    case 4:
        st = 4;
        break;
    case 5:
        st = 6;
        break;
    case 6:
        st = 8;
        break;
    }
    if (D_0063AA00 != 0) {
        st = st + 1;
    }
    sub->field40 = (void *)iosCdvdBackGroundMgrAdd(D_0055FBD0[st], jimakuHandler, p, 0, 0, 0, 0, 0);
    {
        struct jSub *q = &p->sub;
        int m;

        iosCdvdBackGroundMgrSeek(q->field40, q->field2C * 0x8800);
        m = (q->field34 = (q->n + 1) % 4);
        while (m != q->n) {
            D_006C1E80[m].f0 = -1;
            D_006C1E80[m].f4 = 3;
            D_006C1E80[m].f8 = -1;
            m = (m + 1) % 4;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/jimaku", jimakuMgrNext);

void jimakuMgrJump(struct jArg *p)
{
    struct jSub *q = &p->sub;
    int m;

    iosCdvdBackGroundMgrSeek(q->field40, q->field2C * 0x8800);
    m = (q->field34 = (q->n + 1) % 4);
    while (m != q->n) {
        D_006C1E80[m].f0 = -1;
        D_006C1E80[m].f4 = 3;
        D_006C1E80[m].f8 = -1;
        m = (m + 1) % 4;
    }
    jimakuMgrNext(p);
}

/* K&R definition: it declares no prototype, which is what lets jimakuEnd
 * below tail-call this function with no argument, as ROM does. */
void jimakuMgrEnd(p) int *p;

{
    int val = p[0x4C / 4];
    if (val != 0) {
        iosCdvdBackGroundMgrDelete(val);
    }
    iosSemaDelete(D_006E5070);
    iosSemaDelete(D_006E5038);
    iosSemaDelete(D_006E5000);
}

inline void jimakuManager(void)
{
    struct jArg *msg;

    iosMsgQueueCreate(jimakuMsgQ, jimakuMsgBuf, 2);
    while (1) {
        iosMsgRecv(jimakuMsgQ, &msg, 1);
        msg->done = 0;
        switch (msg->cmd) {
        case 0:
            jimakuMgrBegin(msg);
            break;
        case 1:
            jimakuMgrNext(msg);
            break;
        case 2:
            jimakuMgrJump(msg);
            break;
        case 3:
            jimakuMgrEnd((int *)msg);
            break;
        default:
            debug_StdPrintfDummy(D_005540F8, msg->cmd);
            break;
        }
        msg->done = 1;
    }
}

void jimakuBegin(int a0)
{
    *(int *)a0 = 0;
    iosMsgSend(jimakuMsgQ, a0, 1);
}

void jimakuNext(int *p)
{
    if (D_0028F4E8[0] != 0) {
        *p = 1;
        iosMsgSend(jimakuMsgQ, p, 0);
    }
}

void jimakuJump(int a0)
{
    int *w = (int *)(a0 + 0xC);
    if (D_0028F4C0[10] == 0)
        return;
    {
        int v = w[14];
        if (v == -1) {
            D_0063A960 = ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) << 2;
        } else {
            D_0063A960 = v;
        }
    }
    *(int *)a0 = 2;
    iosMsgSend(jimakuMsgQ, a0, 0);
}

void jimakuEnd(void)
{
    D_0028F4E8[0] = 0;
    jimakuMgrEnd();
}

extern int lock_execIcoMisc;

/* the 0x70-byte layout-texture property records (LtProperty in
   src/layout_texture.c); jimaku owns entries 434 and 435. */
typedef struct {
    char _0[0x1C];
    int f1C; /* 0x1C */
    char _20[0x70 - 0x20];
} JimakuLayout;

extern JimakuLayout D_0030CFF8[];
extern char D_00318DD8[];
extern char D_00318E48[];
extern void display_texture(JimTex *t);

void jimakuDisp(char *self)
{
    struct jWayGroup *g = &D_006C1E80[*(int *)(self + 0x3C)];
    int c;

    if (D_0028F4C0[10] == 0) {
        return;
    }
    c = g->fC;
    if ((unsigned int)(c + D_0063A960) < (unsigned int)lock_execIcoMisc) {
        D_0063A964 = 0;
    }
    if ((unsigned int)(c + 5) < (unsigned int)lock_execIcoMisc) {
        iosSemaReferStatus(D_006E5038);
        if (((int *)D_006E5038)[9] > 0) {
            iosSemaSignal(D_006E5038);
        }
    }
    if (D_0028F4C0[10] != 0) {
        iosSemaReferStatus(D_006E5070);
        if (((int *)D_006E5070)[9] > 0) {
            iosSemaSignal(D_006E5070);
        }
    }
    if (D_0063A964 != 0) {
        int v = g->f8;
        D_0030CFF8[435].f1C = v;
        D_0030CFF8[434].f1C = v;
        if (v < 0) {
            return;
        }
        if (jimakuOn != 0) {
            display_texture(D_00318DD8);
            display_texture(D_00318E48);
        }
    }
}

inline void jimakuUndisp(void)
{
    D_0063A964 = 0;
    jimakuOn = 0;
}
