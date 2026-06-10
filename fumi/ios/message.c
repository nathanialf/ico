#include "common.h"

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_00261188(unsigned int addr, const char *fmt, ...);
extern const char D_00551678[];

int deq_mes_th(int a0, int a1, int size, const char *file, int line)
{
    unsigned int p;

    if (size <= 16) {
        return iosFree(a0, a1, file, line);
    }
    a1 -= 0x10;
    size = ((size + 15) / 16) * 16;
    p = iosFree(a0, a1 + size, file, line);
    if (p % size) {
        unsigned int q = size - p % size;
        p += q;
        func_00261188(p - 0x10, D_00551678, q);
    }
    return p;
}

extern void func_00100540(int a0);

void iosMsgQueueCreate(int *a0) {
    int *node = (int *)a0[4];
    if (node) {
        int next = node[0x11];
        int arg = a0[0xB];
        a0[4] = next;
        node[0x11] = 0;
        func_00100540(arg);
    }
}

extern int D_006A0510[];
extern void debug_assertMessage(const char *fmt, ...);
extern void func_001AAD00(const char *file, int line);
extern void func_00260380(const char *file, int line, const char *expr);
extern const char D_0062C268[];
extern int func_00100520(int *p);

extern char D_00551910[];

extern char D_00551920[];

void iosMsgQueueDestroy(int *self, int a1, int a2)
{
    int ret;
    self[0x4 / 4] = 0;
    self[0x8 / 4] = 0;
    self[0x10 / 4] = 0;
    self[0x1C / 4] = 0;
    self[0x0 / 4] = a1;
    self[0x18 / 4] = (self[0xC / 4] = a2);
    self[0x24 / 4] = 1;
    ret = func_00100520((int *)((char *) self + 0x14));
    self[0x2C / 4] = ret;
    if (ret < 0)
    {
        func_001AAD00(D_00551910, 0x78);
        func_00260380(D_00551910, 0x78, D_0062C268);
    }
    {
        int idx = self[0x2C / 4];
        D_006A0510[idx] = (int) self;
        debug_assertMessage(D_00551920, idx, self);
    }
}

extern int func_00100530(int x);
extern const char D_0062C270[];

void send_signal_message(int *self)
{
    int idx;
    debug_assertMessage(D_0062C270, self);
    idx = self[0x2C / 4];
    if (idx < 0) {
        func_001AAD00(D_00551910, 0x88);
        func_00260380(D_00551910, 0x88, D_0062C268);
        idx = self[0x2C / 4];
    }
    D_006A0510[idx] = 0;
    func_00100530(idx);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/message", iosMsgSetEvent);

extern void debug_assertMessage(const char *fmt, ...);
extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_0013D1E8(int a0, int a1, void *a2, int a3, int a4, int a5, int a6);
extern void iosThreadJoin(int a0);
extern void func_00100200(int a0, void *entry, int a2);
extern int func_00100A70(int a0);
extern void iosMsgSetEvent(void);
extern int controler_stable_check(int a0);
extern const char D_0062C280[];
extern int D_0062A304;

extern char D_00551958[];

extern char D_00551970[];

extern char D_00551980[];

void func_00139F80(int a0, int a1, int a2)
{
    int *s0;
    if (a1 == 0)
    {
        debug_assertMessage(D_00551958);
    }
    s0 = (int *) iosFree(D_0062A304, 0x40C0, D_00551910, 0x1C5);
    func_0013D1E8((int) s0, 4, (void *) iosMsgSetEvent, (int) s0,
                  (int)((char *) s0 + 0x70), 0x4000, 0xB);
    s0[0x4090 / 4] = a1;
    s0[0x4094 / 4] = a2;
    s0[0x4098 / 4] = a0;
    iosThreadJoin((int) s0);
    debug_assertMessage(D_00551970);
    func_00100200(a0, (void *) controler_stable_check, -1);
    {
        int r = func_00100A70(a0);
        debug_assertMessage(D_0062C280, r);
    }
    debug_assertMessage(D_00551980);
}

extern int D_006A0510[];

void iosMsgInit(void) {
    int i;
    for (i = 0xFF; i >= 0; i--) {
        D_006A0510[i] = 0;
    }
}

extern void debug_assertMessage(const char *fmt, ...);
extern void func_001AAD00(const char *file, int line);
extern void func_00260380(const char *file, int line, const char *expr);
extern const char D_0062C268[];
extern int func_00100590(int a0, int *buf);
extern void func_00100560(int a0);

extern char D_00551930[];

extern char D_00551948[];

int iosMsgSend(int *self, int a1, int a2)
{
    int buf[8];
    if (self == 0)
    {
        debug_assertMessage(D_00551930);
        func_001AAD00(D_00551910, 0x125);
        func_00260380(D_00551910, 0x125, D_0062C268);
    }
    func_00100590(self[0x2C / 4], buf);
    if (self[0x8 / 4] == buf[0x4 / 4])
    {
        if (a2 != 1)
        {
            debug_assertMessage(D_00551948);
            return -1;
        }
        func_00100560(self[0x2C / 4]);
    }
    ((int *) self[0])[(self[0x4 / 4] + self[0x8 / 4]) % buf[0x4 / 4]] = a1;
    self[0x8 / 4] += 1;
    if (buf[0xC / 4] > 0)
    {
        func_00100540(self[0x2C / 4]);
    }
    return 0;
}

int iosMsgRecv(int *self, int *a1, int a2)
{
    int buf[8];
    if (self == 0)
    {
        debug_assertMessage(D_00551930);
        func_001AAD00(D_00551910, 0x149);
        func_00260380(D_00551910, 0x149, D_0062C268);
    }
    func_00100590(self[0x2C / 4], buf);
    if (self[0x8 / 4] == 0)
    {
        if (a2 != 1)
        {
            return -1;
        }
        func_00100560(self[0x2C / 4]);
    }
    *a1 = ((int *) self[0])[self[0x4 / 4]];
    self[0x4 / 4] = (self[0x4 / 4] + 1) % buf[0x4 / 4];
    self[0x8 / 4] -= 1;
    if (self[0x8 / 4] == buf[0x4 / 4] && buf[0xC / 4] > 0)
    {
        func_00100540(self[0x2C / 4]);
    }
    return 0;
}

void iosMsgQueueDestroyAll(void) {
    int *p;
    int i;
    int **q = (int **)D_006A0510;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            send_signal_message(p);
        }
        i--;
    } while (i >= 0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A0510;  /* stride 0x4 */

/* end struct shapes */
