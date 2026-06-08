#include "common.h"

/* jimaku 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; char _pad34[0x308]; int f_33C; } JimakuState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", display_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", iosCdvdBackGroundReadJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuMgrNext);

extern void *D_00629DE8;

void jimakuMgrJump(int a0) {
    if (D_00629DE8) {
        void *p = *(void **)((char *)D_00629DE8 + 0x164);
        void *q = *(void **)((char *)p + 0x678);
        *(int *)((char *)q + 0x3A4) = a0;
    }
}

void jimakuMgrEnd(void) {
    if (D_00629DE8) {
        void *p = *(void **)((char *)D_00629DE8 + 0x164);
        void *q = *(void **)((char *)p + 0x678);
        *(int *)((char *)q + 0x3A4) = 0;
    }
}

extern void _ACTWait(int a0);

void jimakuBegin(volatile int a0) {
    JimakuState *p = *(JimakuState **)(a0 + 0x164);
    p->f_33C = 0;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuNext);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuJump);

int jimakuEnd(void *a0, void *a1) {
    return (int)(*(float *)((char *)a0 + 0x20) - *(float *)((char *)a1 + 0x20));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", jimakuDisp);

extern void ACTLookTargetSystem_Exec(void);
extern void debug_assertMessage(void *a0);
extern void Vibration_ShotDecode(int a0);
extern char D_00553BE0[];

void jimakuManager(int a0) {
    volatile int home = a0;
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00553BE0);
    Vibration_ShotDecode(7);
}

void jimakuUndisp(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x624) = 0;
}

extern char D_00553DD8[];

void func_00173D00(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_assertMessage(D_00553DD8);
    s0 = new_var;
    s0[0x30 / 4] = 0x4;
    _ACTWait(0);
}

extern void ACTLookTargetSystem_Exec(void);
void func_00173D48(void *a0) {
    void *volatile q = a0;
    ACTLookTargetSystem_Exec();
}

extern int D_00629DE4;

int func_00173D68(int a0, int a1)
{
    int p = D_00629DE4;
    int q = (int)D_00629DE8;
    if ((a0 == p && a1 == q) || (a0 == q && a1 == p)) {
        JimakuState *obj = *(JimakuState **)(q + 0x164);
        if (obj->f_30 == 0x4E)
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173DB0);

extern void inflate_codes(int a0, int a1, int a2);
extern void huft_build(void *a0, int a1);

void func_00173F48(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    inflate_codes(self, a1, large);
    huft_build((void *)self, *(int *)((char *)self + 0x110) + size);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_00173FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/jimaku", func_001741B0);

struct jNode {
    char  _0[4];
    int   status;
    int   field8;
    int   fieldC;
    char  _10[4];
    int   field14;
};

struct jWayGroup {  /* D_006A5900 element, stride 0x18 */
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

extern struct jWayGroup D_006A5900[];
extern struct jBig D_006A5980[];
extern char D_006C8A80[];
extern char D_006C8AB8[];
extern char D_006C8AF0[];
extern char D_00553E58[];
extern char D_00553E68[];
extern char D_00553E78[];
extern int D_00629D00;
extern int D_0062A7F4;
extern unsigned int D_0062C688[];
extern int  func_0013D5E8(void *);
extern int  func_00261188(void *buf, const char *fmt, int n);
extern int  func_0012FC08(void *buf, int x);
extern int  func_0012FCE0(int);
extern void func_0012FD10(int, int, int);
extern int  func_001AAD00(const char *, int);
extern int  func_00260380(const char *, int, void *);
extern void tex_printTexture(int);

void func_001743B8(struct jArg *p)
{
    char buf[16];
    struct jSub *q = &p->sub;
    struct jWayGroup *wg = &D_006A5900[q->n];
    int ww;

    while (wg->node->status != 4) {
        if (func_0013D5E8(D_006C8A80) < 0) return;
    }
    if (func_0013D5E8(D_006C8A80) < 0) return;

    wg->node->status = 1;
    func_00261188(buf, D_00553E58, (q->n + 1) % 4);
    ww = func_0012FC08(buf, wg->node->field14);
    wg->node->field8 = ww;
    func_0012FD10(func_0012FCE0(ww), 1, 1);
    wg->node->fieldC = D_00629D00;
    if (wg->node->field8 == -1) {
        debug_assertMessage(D_00553E68);
        func_001AAD00(D_00553E78, 0x272);
        func_00260380(D_00553E78, 0x272, D_0062C688);
    }

    q->n = (q->n + 1) % 4;
    if (func_0013D5E8(D_006C8AB8) < 0) return;

    wg->f4 = 2;
    if (wg->f8 >= 0) {
        tex_printTexture(wg->f8);
    }

    D_0062A7F4 = 1;
    q->field3C = &D_006A5980[q->n];
    do { } while (0); /* required: epilogue ld-ra scheduling */
}

void func_00174580(struct jArg *p)
{
    struct jSub *q = &p->sub;
    int m;

    huft_build(q->field40, q->field2C * 0x8800);
    m = (q->field34 = (q->n + 1) % 4);
    while (m != q->n) {
        D_006A5900[m].f0 = -1;
        D_006A5900[m].f4 = 3;
        D_006A5900[m].f8 = -1;
        m = (m + 1) % 4;
    }
    func_001743B8(p);
}

extern void iosCdvdBackGroundMgrEntryNum(int val);
extern void func_0013D570(char *p);

void func_00174650(int *p)
{
    int val = p[0x4C / 4];
    if (val != 0) {
        iosCdvdBackGroundMgrEntryNum(val);
    }
    func_0013D570(D_006C8AF0);
    func_0013D570(D_006C8AB8);
    func_0013D570(D_006C8A80);
}

extern int D_00286810[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void func_00174698(void *a0) {
    *(int *)a0 = 0;
    iosMsgSend(D_00286810, a0, 1);
}

extern int D_00271268[];

void func_001746B8(int *a0) {
    if (D_00271268[0]) {
        a0[0] = 1;
        iosMsgSend(D_00286810, a0, 0);
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_006A5900;  /* stride 0x18 */

/* end struct shapes */
