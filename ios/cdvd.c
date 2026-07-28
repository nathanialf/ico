#include "common.h"







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
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrSearchFile);

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

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdDiskReady);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdLoad);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdPackLoad);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgrAdd);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgr);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdDirectStOpen);

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

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgrNotDiskReadyPauseSet);

int iosCdvdBackGroundMgrDeleteRequestGet(void) {
    return D_00631F64;
}

void iosCdvdBackGroundMgrEntryNum(char *self) {
    *(int *)(self + 0x108) |= 2;
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgrSeek);

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

