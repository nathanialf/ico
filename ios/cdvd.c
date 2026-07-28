#include "common.h"

union U001325D8
{
    long long ll;
    int i[2];
};

typedef struct CdvdRec {
    char pad0[0x78];
    long long x78;
    char pad80[0x290 - 0x80];
    int x290;
    int x294;
    char pad298[0x2A8 - 0x298];
    int x2A8;
    char pad2AC[0x2E8 - 0x2AC];
} CdvdRec;







extern int D_00633C7C;
extern char D_006A5C80[];
extern int D_00631F64;
extern void iosMsgRecv();
extern int D_0027E4F0[];
extern int func_0024DA80();
extern int func_0024D7B0();
extern void func_001354B8();
extern void func_0024A1E0();
extern char D_0062FC79[];
extern int func_00265168();
extern char D_00631F70[];

/* normalise+register helper (== iosCdvdLoadPackFile); static-inlined into the
 * ReadDir loop so gcc's inliner handles the buf address (testing remat). */;
extern void func_00264DF8();
static inline int cdvd_normpath(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    func_00264DF8(buf, D_00631F70, a0);
    c = buf[0];
    do
    {
        int t = ((int) c) << (nc = 24);
        int sc = t >> 24;
        if (sc == '/')
        {
            *p = '\\';
        }
        else
        {
            int r = sc - 0x20;
            if ((D_0062FC79[sc] & 2) == 0)
            {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return func_00265168(a0, buf);
}
extern int D_00275120[];
extern int D_00633C60;
extern CdvdRec D_006812D0[];

int iosCdvdMgrSearchFile(void) {
    int count = D_00633C60;
    int i;
    for (i = 0; i < count; i++) {
        CdvdRec *b = &D_006812D0[i];
        int f5 = D_00275120[57];
        int f8 = 1;
        if (b->x2A8 != 0) {
            f8 = b->x290;
            f5 = b->x294;
        }
        b->x78 = (b->x78 & ~0xE0) | (f8 << 5) | (f5 << 6);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrStStop);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrLoad);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", temp_loadfunc);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrPackLoad);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131480);

void func_00131560(int a0)
{
    int *self = (int *) a0;
    long long err;
    self[0xC / 4] = 0;
    err = func_0024DA80(a0);
    if (err == 0)
    {
        self[0xC / 4] = func_0024D7B0();
    }
    func_0024A1E0(self[0x160 / 4]);
    func_001354B8(self[0x15C / 4]);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001315A8);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131780);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131818);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdManager);

extern char D_005569D0[];
extern char D_005569F8[];
extern extern void debug_assertMessage();
extern int func_00135580(int a0, void *buf, int n);

void iosCdvdDiskReady(int *a0, void *buf, int n)
{
    char *p = (char *) buf;
    long long ret;
    for (;;)
    {
        ret = func_00135580(a0[0x15C / 4], p, n);
        if (ret <= 0)
        {
            break;
        }
        p += ret;
        n -= ret;
    }
    debug_assertMessage(D_005569D0, a0[0x24 / 4]);
    if (ret < 0)
    {
        debug_assertMessage(D_005569F8);
    }
}

extern unsigned char D_006A64B8[];
extern void iosCdvdManager(int *a0, void *buf, int n);

void iosCdvdLoad(int *a0, void *a1, int a2)
{
    if (a1 != 0)
    {
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdDiskReady(a0, a1, a2);
        }
        else
        {
            iosCdvdManager(a0, a1, a2);
        }
        return;
    }
    while (a2 > 0)
    {
        int n = (a2 < 0x401) ? a2 : 0x400;
        void *buf = D_006A64B8;
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdDiskReady(a0, buf, n);
        }
        else
        {
            iosCdvdManager(a0, buf, n);
        }
        a2 -= n;
    }
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdPackLoad);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgrAdd);

extern unsigned char D_0027E4C0[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void iosCdvdBackGroundMgr(int a0, int a1)
{
    union U001325D8 *p = (union U001325D8 *) a0;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (a1 & 1);
    iosMsgSend(D_0027E4C0, (void *) a0, 0);
}

void iosCdvdDirectStOpen(void *a0) {
    *(int *)((char *)a0 + 4) = 2;
    iosMsgSend(D_0027E4C0, a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132630);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132930);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132B90);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132DC0);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132FF0);

void func_001331D8(int a0)
{
    int *self = (int *) a0;
    int err;
    /* statement boundary: keep this store out of the following call's
     * setup so it isn't reordered into the jal delay slot. */
    do { self[0xC / 4] = 0; } while (0);
    err = func_0024DA80(a0);
    if (err == 0)
    {
        self[0xC / 4] = func_0024D7B0();
    }
    return func_0024A1E0(self[0x160 / 4]);
}

int iosCdvdLoadPackFile(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    func_00264DF8(buf, D_00631F70, a0);
    c = buf[0];
    do
    {
        /* `nc = 24` (the sign-extend shift count) writes the next-char temp at
         * the loop top, splitting its live range from `c` so the carried byte
         * keeps its own register with the copy in the bnez delay slot. */
        int t = ((int) c) << (nc = 24);
        int sc = t >> 24;
        if (sc == '/')
        {
            *p = '\\';
        }
        else
        {
            int r = sc - 0x20;
            if ((D_0062FC79[sc] & 2) == 0)
            {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return func_00265168(a0, buf);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdDiskStatusGet);

int iosCdvdBackGroundMgrDelete(int a0)
{
    int local = a0;
    iosMsgRecv(D_0027E4F0, &local, 1);
    return 1;
}

extern char D_00276300[];

void iosCdvdBackGroundMgrNotDiskReadyPauseSet(int a0, unsigned char *a1, int a2) {
    int buf[4];
    *(unsigned long *)D_00276300 = (*(unsigned long *)D_00276300 & ~1UL) | (a0 & 1);
    func_00265168((int)(D_00276300 + 0x34), a1);
    *(int *)(D_00276300 + 0x20) = a2;
    *(int *)(D_00276300 + 0x18) = 0;
    *(int *)(D_00276300 + 0x1C) = 0;
    iosCdvdDirectStOpen(D_00276300);
    buf[0] = (int)D_00276300;
    iosMsgRecv(D_0027E4F0, buf, 1);
}

int iosCdvdBackGroundMgrDeleteRequestGet(void) {
    return D_00631F64;
}

void iosCdvdBackGroundMgrEntryNum(char *self) {
    *(int *)(self + 0x108) |= 2;
}

int iosCdvdBackGroundMgrSeek(void *a0, int a1) {
    int *p = (int *)((char *)a0 + 0x108);
    return *p = (*p & ~0x10) | ((a1 & 1) << 4);
}

int iosCdvdBackGroundRead(void)
{
    char *p = D_006A5C80;
    char *limit = p + 0x834;
    int count = 0;
    do {
        if (*p != 0) {
            count += (*(unsigned int *)(p + 0x108) >> 1) & 1;
        }
        p += 0x12C;
    } while ((int)p < (int)limit);
    return count;
}

int iosCdvdBackGroundReadIOPm(void)
{
    char *p = D_006A5C80;
    char *limit = p + 0x834;
    int count = 0;
    do {
        char b = *p;
        int new_count = count + 1;
        p += 0x12C;
        if (b != 0) {
            count = new_count;
        }
    } while ((int)p < (int)limit);
    return count;
}

void func_00133500(char *self, int val) {
    *(int *)(self + 0x110) = val;
}

int func_00133508(void) {
    return D_00633C7C;
}

