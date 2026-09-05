#include "common.h"

struct jSub {       /* sub-object at offset 0xC of the argument */
    char  _0[0x2C];
    int   field2C;
    int   n;
    int   field34;
    char  _38[4];
    void *field3C;
    void *field40;
};
struct jArg {       /* the object queued on jimakuMsgQ */
    int   cmd;        /* 0x0 command: 0 begin, 1 next, 2 jump, 3 end */
    int   _4;
    int   done;       /* 0x8 cleared while the manager services it, 1 when finished */
    struct jSub sub;  /* 0xC */
};
struct jNode {
    char  _0[4];
    int   status;
    int   field8;
    int   fieldC;
    char  _10[4];
    int   field14;
};
struct jWayGroup {  /* D_006C1E80 element, stride 0x18 */
    int   f0;
    int   f4;
    int   f8;
    char  _c[4];
    struct jNode *node;
    char  _14[4];
};
extern void iosCdvdBackGroundMgrSeek(char *self, int val);
extern void iosCdvdBackGroundRead();
extern struct jWayGroup D_006C1E80[];
extern void iosCdvdBackGroundMgrSeek__pn(void *a0, int a1) __asm__("iosCdvdBackGroundMgrSeek");
extern void jimakuMgrNext(struct jArg *p);
extern char D_006E5000[];
extern char D_006E5038[];
extern char D_006E5070[];
extern void iosCdvdBackGroundMgrDelete(char *self);
extern int iosSemaDelete(int *self);
extern int jimakuMsgQ[];
extern int iosMsgSend(int *self, int a1, int a2);
extern int D_0028F4E8[];
extern int D_0028F4C0[];
extern int D_0063A960;
extern void iosMsgSend__pn(void *a0, void *a1, int a2) __asm__("iosMsgSend");
extern void jimakuMgrEnd__pn() __asm__("jimakuMgrEnd");
extern int jimakuMsgBuf[2];
extern char D_005540F8[];
extern void iosMsgQueueCreate(int *q, int *buf, int n);
extern int iosMsgRecv(int *q, void *out, int mode);
extern void jimakuMgrBegin(struct jArg *p);
extern int D_0063A964;
extern int jimakuOn;
/* prototypes: their order is the inline tail's emission order */
void jimakuManager(void);
void jimakuUndisp(void);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", display_texture);
void iosCdvdBackGroundReadJimaku(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    iosCdvdBackGroundRead(self, a1, large);
    iosCdvdBackGroundMgrSeek(self, *(int *)((char *)self + 0x110) + size);
}
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuHandler);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrBegin);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrNext);
void jimakuMgrJump(struct jArg *p)
{
    struct jSub *q = &p->sub;
    int m;

    iosCdvdBackGroundMgrSeek__pn(q->field40, q->field2C * 0x8800);
    m = (q->field34 = (q->n + 1) % 4);
    while (m != q->n) {
        D_006C1E80[m].f0 = -1;
        D_006C1E80[m].f4 = 3;
        D_006C1E80[m].f8 = -1;
        m = (m + 1) % 4;
    }
    jimakuMgrNext(p);
}
void jimakuMgrEnd(int *p)
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
void jimakuNext(int *p) {
    if (D_0028F4E8[0] != 0) {
        *p = 1;
        iosMsgSend(jimakuMsgQ, p, 0);
    }
}
void jimakuJump(int a0) {
    int *w = (int *)(a0 + 0xC);
    if (D_0028F4C0[10] == 0) return;
    {
        int v = w[14];
        if (v == -1) {
            D_0063A960 = ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) << 2;
        } else {
            D_0063A960 = v;
        }
    }
    *(int *)a0 = 2;
    iosMsgSend__pn(jimakuMsgQ, (void *)a0, 0);
}
void jimakuEnd(void)
{
    D_0028F4E8[0] = 0;
    jimakuMgrEnd__pn();
}
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuDisp);
inline void jimakuUndisp(void)
{
    D_0063A964 = 0;
    jimakuOn = 0;
}
