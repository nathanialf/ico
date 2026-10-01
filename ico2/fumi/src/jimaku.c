#include "cdvd.h"
#include "message.h"
#include "thread.h"
#include "Texture.h"
#include "main.h"

struct jNode {
    char _0[4];
    int status;
    int field8;
    int fieldC;
    char _10[4];
    int field14;
};

struct jWayGroup { /* jimakuRing element, stride 0x18 */
    int f0;
    int f4;
    int f8;
    int fC;
    struct jWayGroup *node; /* the next group in the ring */
    char *buf;              /* 0x14 its 0x8C40 read buffer */
};

/* The TU's .bss, in ROM run order (VMA 0x6C1E80..0x6E50A4): the four-group
   read ring, the groups' CD read buffers (64-byte aligned as DMA targets,
   which puts them at +0x80 past the 0x60-byte ring; MAIN.MAP pads the
   object's .bss to a 64-byte boundary) and three semaphore records of iosSemaCreate's 13 words:
   read done (signalled by jimakuHandler), shown five frames (jimakuDisp) and
   one per frame (jimakuDisp). */
static struct jWayGroup jimakuRing[4];

static char jimakuBuf[4][0x8C40] __attribute__((aligned(64)));

static int jimakuReadSema[13];

static int jimakuShownSema[13];

static int jimakuFrameSema[13];

#include "jimaku.h"
#include "gflag.h"

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

/* .data, owned by jimaku.o, 0x2A2FD0..0x2A50C0 (= MAIN.MAP jimaku.o .data
   0x20F0, line 5856, which names all four at these offsets), all zero: the
   subtitle thread's record and its 8 KB stack, the manager's message queue
   and the request the script actors hand it.
   .sdata, 0x63A960..0x63A9A0 (= MAIN.MAP's 0x40, line 7097, naming jimakuOn
   and jimakuMsgBuf): the display time in frames, the display flag, jimakuOn,
   display_texture's colour initialiser (a 4-byte template, so .sdata,
   reached by %hi/%lo), then jimakuMgrNext's strings and jimakuMsgBuf. */
char jimakuThread[112] = {0};

char jimakuThreadStack[8192] = {0};

int jimakuMsgQ[12] = {0};

JimakuArg jimaku_msg = {0};

static int jimakuDispTime = 120; /* derived name */

static int jimakuDispOn = 0; /* derived name */

int jimakuOn = 1;

/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_StartPacketPri(int pri);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_SetAlpha(long long a0, long long a1, long long a2);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_SetGsReg(long long a0, long long a1);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_SetZWrite(int a0);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_SetZTest(int a0);
/* kept local: z is unsigned int here, long long in GifPacket.h */
extern void gif_SpriteSensitiveOffset(int *r, unsigned int z, int *uv, unsigned char *col,
                                      int prim);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOffset differs) */
extern void gif_EndPacket(void);

void display_texture(JimTex *t)
{
    JimCol col = {128, 128, 128, 128};
    int dst[4];
    int src[4];

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
    col.r = ~GlobalStageSetting.reductionCol[0];
    col.g = ~GlobalStageSetting.reductionCol[1];
    col.b = ~GlobalStageSetting.reductionCol[2];
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

int jimakuHandler(int self, JimakuArg *p)
{
    JimakuSub *sub = &p->sub;
    struct jWayGroup *g;
    int size = 0x8440;
    int left;
    int n;

    while (sub->unk34 != (sub->n + 3) % 4) {
        g = &jimakuRing[sub->unk34];
        if (g->f4 == 2) {
            g->f4 = 3;
            break;
        }
        /* WHAT THE BYTES PIN: the read loop tests before its first pass and
           takes its byte count by copy from a variable set outside the
           outer loop. cse1 cannot see that value where the entry test
           stands, so the test's edge past the loop lives through gcse and
           is folded only after it: gcse then puts %hi(jimakuBuf) in the
           loop's preheader once per record (0x0017CC0C) and reloads unk34
           on both exits of the loop, as ROM does. What they cannot pin is
           the variable's name. */
        left = size;
        while (left > 0) {
            n = (0x8C40 < left) ? 0x8C40 : left;
            jimakuBuf[sub->unk34][0] = -1;
            jimakuBuf[sub->unk34][1] = -1;
            iosCdvdBackGroundReadJimaku(self, (int)jimakuBuf[sub->unk34], n);
            left -= n;
        }
        jimakuRing[sub->unk34].f0 = sub->unk2C++;
        jimakuRing[sub->unk34].f4 = 4;
        iosCdvdBackGroundMgrSeek(sub->unk40, sub->unk2C * 0x8800);
        sub->unk34 = (sub->unk34 + 1) % 4;
    }
    if (systemStatus[10] != 0) {
        iosSemaReferStatus(jimakuReadSema);
        if (jimakuReadSema[9] > 0) {
            iosSemaSignal(jimakuReadSema);
        }
    }
    return 0;
}

extern char jimakuFileName[][32];

void jimakuMgrBegin(JimakuArg *p)
{
    JimakuSub *sub = &p->sub;
    int st = 0;
    int i;
    struct jWayGroup *g;

    if (systemStatus[10] != 0) {
        return;
    }
    systemStatus[10] = 1;
    iosSemaCreate(jimakuReadSema, 0, 1, 0);
    iosSemaCreate(jimakuShownSema, 0, 1, 0);
    iosSemaCreate(jimakuFrameSema, 0, 1, 0);
    for (i = 0; i < 4; i++) {
        g = &jimakuRing[i];
        g->node = &jimakuRing[(i + 1) % 4];
        g->buf = jimakuBuf[i];
    }
    sub->n = 0;
    jimakuRing[0].f0 = -1;
    jimakuRing[0].f4 = 3;
    jimakuRing[0].f8 = -1;
    sub->unk34 = 1;
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
    if (gFlagGameClear != 0) {
        st = st + 1;
    }
    sub->unk40 =
        (void *)iosCdvdBackGroundMgrAdd(jimakuFileName[st], jimakuHandler, p, 0, 0, 0, 0, 0);
    {
        JimakuSub *q = &p->sub;
        int m;

        iosCdvdBackGroundMgrSeek(q->unk40, q->unk2C * 0x8800);
        m = (q->unk34 = (q->n + 1) % 4);
        while (m != q->n) {
            jimakuRing[m].f0 = -1;
            jimakuRing[m].f4 = 3;
            jimakuRing[m].f8 = -1;
            m = (m + 1) % 4;
        }
    }
}

/* kept local: agrees with mv_defs.h, which this TU does not include */
extern void __assert(const char *file, int line, const char *expr);

/* The DEBUG build's switch to print the way groups' states after each Next
   (name ours); retail builds it as 0. */
#ifdef DEBUG
#define JIMAKU_DEBUG_DUMP (debug_font_flag & 0x400)
#else
#define JIMAKU_DEBUG_DUMP 0
#endif

void jimakuMgrNext(JimakuArg *p)
{
    char buf[16];
    JimakuSub *sub = &p->sub;
    struct jWayGroup *g = &jimakuRing[sub->n];

    while (g->node->f4 != 4) {
        if (iosSemaWait(jimakuReadSema) < 0) {
            return;
        }
    }
    if (iosSemaWait(jimakuReadSema) < 0) {
        return;
    }
    g->node->f4 = 1;
    sprintf(buf, "jimaku%02d.tm2", (sub->n + 1) % 4);
    g->node->f8 = tex_InitTexture(buf, g->node->buf);
    tex_SetSamplingType(tex_GetTextureData(g->node->f8), 1, 1);
    g->node->fC = lock_execIcoMisc;
    if (g->node->f8 == -1) {
        debug_StdPrintfDummy("already exist\n");
        debug_assert(__FILE__, 688);
        __assert(__FILE__, 688, "0");
    }
    sub->n = (sub->n + 1) % 4;
    if (iosSemaWait(jimakuShownSema) < 0) {
        return;
    }
    g->f4 = 2;
    if (g->f8 >= 0) {
        tex_FreeTexture(g->f8);
    }
    sub->unk3C = jimakuBuf[sub->n];
    jimakuDispOn = 1;
    /* The listing's rows 705 to 714 carry no code, and the ROM's second and
     * third returns take `ld $31` from the epilogue where the build without
     * this block takes the next statement's constant into the second one's
     * slot: reorg predicts a branch to the epilogue taken when a loop-begin
     * note stands just before it (mostly_true_jump), so a loop compiled out
     * at the end of the function is what the bytes pin: here the DEBUG
     * build's dump, whose switch retail builds as 0. Its strings are the
     * .sdata's ">%d", " %d" and "\n" after the assert's "0", which no
     * instruction reads in retail or in the January listing. What they
     * cannot pin: the values printed; the four way groups' states and the
     * mark on the current one are ours. */
    if (JIMAKU_DEBUG_DUMP) {
        int m;

        for (m = 0; m < 4; m++) {
            debug_StdPrintfDummy(m == sub->n ? ">%d" : " %d", jimakuRing[m].f4);
        }
        debug_StdPrintfDummy("\n");
    }
}

void jimakuMgrJump(JimakuArg *p)
{
    JimakuSub *q = &p->sub;
    int m;

    iosCdvdBackGroundMgrSeek(q->unk40, q->unk2C * 0x8800);
    m = (q->unk34 = (q->n + 1) % 4);
    while (m != q->n) {
        jimakuRing[m].f0 = -1;
        jimakuRing[m].f4 = 3;
        jimakuRing[m].f8 = -1;
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
    iosSemaDelete(jimakuFrameSema);
    iosSemaDelete(jimakuShownSema);
    iosSemaDelete(jimakuReadSema);
}

int jimakuMsgBuf[2] = {0};

inline void jimakuManager(void)
{
    JimakuArg *msg;

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
            debug_StdPrintfDummy("jimakuManager: recv command %d error.", msg->cmd);
            break;
        }
        msg->done = 1;
    }
}

void jimakuBegin(JimakuArg *msg)
{
    msg->cmd = 0;
    iosMsgSend(jimakuMsgQ, msg, 1);
}

void jimakuNext(JimakuArg *msg)
{
    if (systemStatus[10] != 0) {
        msg->cmd = 1;
        iosMsgSend(jimakuMsgQ, msg, 0);
    }
}

void jimakuJump(JimakuArg *msg)
{
    JimakuSub *sub = &msg->sub;
    if (systemStatus[10] == 0)
        return;
    {
        int v = sub->unk38;

        if (v == -1) {
            jimakuDispTime = ((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) << 2;
        } else {
            jimakuDispTime = v;
        }
    }
    msg->cmd = 2;
    iosMsgSend(jimakuMsgQ, msg, 0);
}

void jimakuEnd(JimakuArg *msg)
{
    systemStatus[10] = 0;
    jimakuMgrEnd();
}

/* the 0x70-byte layout-texture property records (LtProperty in
   src/layout_texture.c); jimaku owns entries 434 and 435. */
typedef struct {
    char _0[0x1C];
    int f1C; /* 0x1C */
    char _20[0x70 - 0x20];
} JimakuLayout;

extern JimakuLayout texProperty[];
extern char D_00318DD8[];
extern char D_00318E48[];
extern void display_texture(JimTex *t);

void jimakuDisp(JimakuArg *msg)
{
    struct jWayGroup *g = &jimakuRing[msg->sub.n];
    int c;

    if (systemStatus[10] == 0) {
        return;
    }
    c = g->fC;
    if ((unsigned int)(c + jimakuDispTime) < (unsigned int)lock_execIcoMisc) {
        jimakuDispOn = 0;
    }
    if ((unsigned int)(c + 5) < (unsigned int)lock_execIcoMisc) {
        iosSemaReferStatus(jimakuShownSema);
        if (jimakuShownSema[9] > 0) {
            iosSemaSignal(jimakuShownSema);
        }
    }
    if (systemStatus[10] != 0) {
        iosSemaReferStatus(jimakuFrameSema);
        if (jimakuFrameSema[9] > 0) {
            iosSemaSignal(jimakuFrameSema);
        }
    }
    if (jimakuDispOn != 0) {
        int v = g->f8;
        texProperty[435].f1C = v;
        texProperty[434].f1C = v;
        if (v < 0) {
            return;
        }
        if (jimakuOn != 0) {
            display_texture(D_00318DD8);
            display_texture(D_00318E48);
        }
    }
}

inline void jimakuUndisp(JimakuArg *msg)
{
    jimakuDispOn = 0;
    jimakuOn = 0;
}
