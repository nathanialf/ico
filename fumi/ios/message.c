#include "common.h"

/* .rodata carved from blob 0x44F1F8 (VMA 0x551910..0x551994) */
const char D_00551910[0x10] = "ios/message.c";
const char D_00551920[0x10] = "sema[%d] = %p\n";
const char D_00551930[0x18] = "msg:null message queue\n";
const char D_00551948[0x10] = "MSG NO SEND\n";
const char D_00551958[0x18] = "evt:null message queue\n";
const char D_00551970[0x10] = "where is here\n";
const char D_00551980[0x14] = "evt:signal added\n";

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void sprintf(unsigned int addr, const char *fmt, ...);
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
        sprintf(p - 0x10, D_00551678, q);
    }
    return p;
}

extern void SignalSema(int a0);

void iosMsgQueueCreate(int *a0) {
    int *node = (int *)a0[4];
    if (node) {
        int next = node[0x11];
        int arg = a0[0xB];
        a0[4] = next;
        node[0x11] = 0;
        SignalSema(arg);
    }
}

extern int D_006A0510[];
extern void debug_StdPrintfDummy(const char *fmt, ...);
extern void func_001AAD00(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);
extern const char D_0062C268[];
extern int CreateSema(int *p);



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
    ret = CreateSema((int *)((char *) self + 0x14));
    self[0x2C / 4] = ret;
    if (ret < 0)
    {
        func_001AAD00(D_00551910, 0x78);
        __assert(D_00551910, 0x78, D_0062C268);
    }
    {
        int idx = self[0x2C / 4];
        D_006A0510[idx] = (int) self;
        debug_StdPrintfDummy(D_00551920, idx, self);
    }
}

extern int DeleteSema(int x);
extern const char D_0062C270[];

void send_signal_message(int *self)
{
    int idx;
    debug_StdPrintfDummy(D_0062C270, self);
    idx = self[0x2C / 4];
    if (idx < 0) {
        func_001AAD00(D_00551910, 0x88);
        __assert(D_00551910, 0x88, D_0062C268);
        idx = self[0x2C / 4];
    }
    D_006A0510[idx] = 0;
    DeleteSema(idx);
}

extern int GetThreadId(void);
extern int func_0013D3C8(unsigned int a0);
extern void iosSemaCreate(void);
extern const char D_0062C278[];
extern int D_0062A408;
extern int ReferSemaStatus(int a0, int *buf);

void iosMsgSetEvent(void)
{
    int buf[8];
    int *ret = (int *) func_0013D3C8(GetThreadId());
    int *base = (int *) ret[0x34 / 4];

    D_0062A408 = (int) ret;
    debug_StdPrintfDummy(D_0062C278, ret[0x30 / 4], base[0x4094 / 4]);

    for (;;) {
        int *self;
        int val;
        iosSemaCreate();
        self = (int *) base[0x4090 / 4];
        val = base[0x4094 / 4];
        if (self == 0) {
            debug_StdPrintfDummy(D_00551930);
            func_001AAD00(D_00551910, 0x125);
            __assert(D_00551910, 0x125, D_0062C268);
        }
        ReferSemaStatus(self[0x2C / 4], buf);
        if (self[0x8 / 4] == buf[0x4 / 4]) {
            debug_StdPrintfDummy(D_00551948);
            continue;
        }
        ((int *) self[0])[(self[0x4 / 4] + self[0x8 / 4]) % buf[0x4 / 4]] = val;
        self[0x8 / 4] += 1;
        if (buf[0xC / 4] > 0) {
            SignalSema(self[0x2C / 4]);
        }
        if (!D_00551910) {
        }
    }
}

extern void debug_StdPrintfDummy(const char *fmt, ...);
extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_0013D1E8(int a0, int a1, void *a2, int a3, int a4, int a5, int a6);
extern void iosThreadJoin(int a0);
extern void func_00100200(int a0, void *entry, int a2);
extern int func_00100A70(int a0);
extern void iosMsgSetEvent(void);
extern int signal_handler(int a0);
extern const char D_0062C280[];
extern int D_0062A304;




void func_00139F80(int a0, int a1, int a2)
{
    int *s0;
    if (a1 == 0)
    {
        debug_StdPrintfDummy(D_00551958);
    }
    s0 = (int *) iosFree(D_0062A304, 0x40C0, D_00551910, 0x1C5);
    func_0013D1E8((int) s0, 4, (void *) iosMsgSetEvent, (int) s0,
                  (int)((char *) s0 + 0x70), 0x4000, 0xB);
    s0[0x4090 / 4] = a1;
    s0[0x4094 / 4] = a2;
    s0[0x4098 / 4] = a0;
    iosThreadJoin((int) s0);
    debug_StdPrintfDummy(D_00551970);
    func_00100200(a0, (void *) signal_handler, -1);
    {
        int r = func_00100A70(a0);
        debug_StdPrintfDummy(D_0062C280, r);
    }
    debug_StdPrintfDummy(D_00551980);
}

extern int D_006A0510[];

void iosMsgInit(void) {
    int i;
    for (i = 0xFF; i >= 0; i--) {
        D_006A0510[i] = 0;
    }
}

extern void debug_StdPrintfDummy(const char *fmt, ...);
extern void func_001AAD00(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);
extern const char D_0062C268[];
extern int ReferSemaStatus(int a0, int *buf);
extern void WaitSema(int a0);



int iosMsgSend(int *self, int a1, int a2)
{
    int buf[8];
    if (self == 0)
    {
        debug_StdPrintfDummy(D_00551930);
        func_001AAD00(D_00551910, 0x125);
        __assert(D_00551910, 0x125, D_0062C268);
    }
    ReferSemaStatus(self[0x2C / 4], buf);
    if (self[0x8 / 4] == buf[0x4 / 4])
    {
        if (a2 != 1)
        {
            debug_StdPrintfDummy(D_00551948);
            return -1;
        }
        WaitSema(self[0x2C / 4]);
    }
    ((int *) self[0])[(self[0x4 / 4] + self[0x8 / 4]) % buf[0x4 / 4]] = a1;
    self[0x8 / 4] += 1;
    if (buf[0xC / 4] > 0)
    {
        SignalSema(self[0x2C / 4]);
    }
    return 0;
}

int iosMsgRecv(int *self, int *a1, int a2)
{
    int buf[8];
    if (self == 0)
    {
        debug_StdPrintfDummy(D_00551930);
        func_001AAD00(D_00551910, 0x149);
        __assert(D_00551910, 0x149, D_0062C268);
    }
    ReferSemaStatus(self[0x2C / 4], buf);
    if (self[0x8 / 4] == 0)
    {
        if (a2 != 1)
        {
            return -1;
        }
        WaitSema(self[0x2C / 4]);
    }
    *a1 = ((int *) self[0])[self[0x4 / 4]];
    self[0x4 / 4] = (self[0x4 / 4] + 1) % buf[0x4 / 4];
    self[0x8 / 4] -= 1;
    if (self[0x8 / 4] == buf[0x4 / 4] && buf[0xC / 4] > 0)
    {
        SignalSema(self[0x2C / 4]);
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
