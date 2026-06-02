/* jimaku.c */

extern int D_00632514;
extern int D_00632518;
extern int D_0063251C;
extern int D_00632520;
extern int D_00632524;
extern unsigned int D_00632528[8];
extern int D_0063252C;
extern int D_00632530;
extern int D_00632534;
extern int D_00632538;
extern int D_0063253C;
extern int D_00632540;
extern int D_00632544;
extern char D_00632548[8];
extern int D_00632550;
extern int D_00632554;
extern int D_00632558;
extern int D_0063255C;
extern int D_00632560;
extern int D_00632564;
extern int D_00632568;
extern int D_0063256C;
extern int D_00632570;
extern int D_00632574;
extern int D_00632578;
extern int D_0063257C;
extern int D_00632580;
extern int D_00632584;
extern int D_00632588;
extern int D_0063258C;
extern char D_00632590[8];

const char D_00559B68[16] = "jimaku%02d.tm2";
const char D_00559B78[16] = "already exist\n";
const char D_00559B88[16] = "src/jimaku.c";
const char D_00559B98[40] = "jimakuManager: recv command %d error.";
const char D_00559BC0[16] = "GetWay_begin\n";
const char D_00559BD0[16] = "gid t:%d m:%d\n";
const char D_00559BE0[16] = "same_group\n";
const char D_00559BF0[64] = "other_group\n\000\000\000\000gid:%d = tgid:%d, mgid:%d\n\000\000\000\000\000\000!!cant reach!!\n";
const char D_00559C30[16] = "wp:%p %p\n";
const char D_00559C40[16] = "gid:%d %d\n";
const char D_00559C50[16] = "direction:%d\n";
const char D_00559C60[16] = "skip wp\n";
const char D_00559C70[32] = "delete guide point at avoid\n";
const char D_00559C90[16] = "left way %d\n";
const char D_00559CA0[16] = "right way %d\n";
const char D_00559CB0[16] = "up way %d\n";
const char D_00559CC0[32] = "delete guide point group:%d\n";
const char D_00559CE0[40] = "illigal way \000\000\000\000WGROUP STAT OTHER\n\000\000\000\000\000";
const char D_00559D08[16] = "short cut 2:%p\n";
const char D_00559D18[24] = "delete guide point\n";
const char D_00559D30[80] = "short cut 1:%p\n\000WGROUP STAT SAME\n\000\000\000\000\000\000\000wp %p myway %p pos %p\n\000\000wgroup stat:%d\n";
const char D_00559D80[16] = "goal wp1\n";
const char D_00559D90[16] = "bilist:%p\n";

extern char D_006CF030[];
extern char D_006CEFF8[];
extern char D_006CEFC0[];

extern int D_00631A00;

struct jNode {
    char  _0[4];
    int   status;
    int   field8;
    int   fieldC;
    char  _10[4];
    int   field14;
};

struct jWayGroup {  /* D_006ABE40 element, stride 0x18 */
    int   f0;
    int   f4;
    int   f8;
    char  _c[4];
    struct jNode *node;
    char  _14[4];
};

struct jSub {       /* sub-object at offset 0xC of the argument */
    char  _0[0x2C];
    int   field2C;
    int   n;
    int   field34;
    char  _38[4];
    void *field3C;
    void *field40;
};

struct jArg {
    char  _0[0xC];
    struct jSub sub;
};

struct jBig { char _[0x8C40]; };

extern struct jWayGroup D_006ABE40[];
extern struct jBig D_006ABEC0[];

extern void func_00133450(int val);
extern void func_0013DA88(char *p);
extern void func_00133500(void *a, int b);
extern int  func_0013DB00(void *);
extern int  func_0012FD30(void *buf, int x);
extern int  func_0012FE08(int);
extern void func_0012FE38(int, int, int);
extern int  func_00264DF8(void *buf, const char *fmt, int n);
extern int  func_001A6E28(const char *);
extern int  func_001AD768(const char *, int);
extern int  func_00263FF0(const char *, int, void *);
extern void func_0012DE80(int);

#include "include_asm.h"

void func_00176808(struct jArg *p)
{
    char buf[16];
    struct jSub *q = &p->sub;
    struct jWayGroup *wg = &D_006ABE40[q->n];
    int ww;

    while (wg->node->status != 4) {
        if (func_0013DB00(D_006CEFC0) < 0) return;
    }
    if (func_0013DB00(D_006CEFC0) < 0) return;

    wg->node->status = 1;
    func_00264DF8(buf, D_00559B68, (q->n + 1) % 4);
    ww = func_0012FD30(buf, wg->node->field14);
    wg->node->field8 = ww;
    func_0012FE38(func_0012FE08(ww), 1, 1);
    wg->node->fieldC = D_00631A00;
    if (wg->node->field8 == -1) {
        func_001A6E28(D_00559B78);
        func_001AD768(D_00559B88, 0x272);
        func_00263FF0(D_00559B88, 0x272, D_00632528);
    }

    q->n = (q->n + 1) % 4;
    if (func_0013DB00(D_006CEFF8) < 0) return;

    wg->f4 = 2;
    if (wg->f8 >= 0) {
        func_0012DE80(wg->f8);
    }

    D_00632514 = 1;
    q->field3C = &D_006ABEC0[q->n];
    do { } while (0); /* required: epilogue ld-ra scheduling */
}

void func_001769D0(struct jArg *p)
{
    struct jSub *q = &p->sub;
    int m;

    func_00133500(q->field40, q->field2C * 0x8800);
    m = (q->field34 = (q->n + 1) % 4);
    while (m != q->n) {
        D_006ABE40[m].f0 = -1;
        D_006ABE40[m].f4 = 3;
        D_006ABE40[m].f8 = -1;
        m = (m + 1) % 4;
    }
    func_00176808(p);
}

void func_00176AA0(int *p)
{
    int val = p[0x4C / 4];
    if (val != 0) {
        func_00133450(val);
    }
    func_0013DA88(D_006CF030);
    func_0013DA88(D_006CEFF8);
    func_0013DA88(D_006CEFC0);
}
