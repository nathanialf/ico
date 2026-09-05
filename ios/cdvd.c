#include "common.h"

union U001325D8
{
    long long ll;
    int i[2];
};

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdStManager);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrSearchFile);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrStStart);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrStStop);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrLoad);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", temp_loadfunc);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrPackLoad);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdStRead);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdHandlerReadNoInflate);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdHandlerReadInflate);
extern unsigned char D_006B83B8[];
extern void iosCdvdHandlerReadInflate(int *a0, void *buf, int n);
extern void iosCdvdHandlerReadNoInflate(int *a0, void *buf, int n);

void iosCdvdHandlerRead(int *a0, void *a1, int a2)
{
    if (a1 != 0)
    {
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdHandlerReadInflate(a0, a1, a2);
        }
        else
        {
            iosCdvdHandlerReadNoInflate(a0, a1, a2);
        }
        return;
    }
    while (a2 > 0)
    {
        int n = (a2 < 0x401) ? a2 : 0x400;
        void *buf = D_006B83B8;
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdHandlerReadInflate(a0, buf, n);
        }
        else
        {
            iosCdvdHandlerReadNoInflate(a0, buf, n);
        }
        a2 -= n;
    }
}
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", unifile_read_func);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdUnifileInfoGet);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdManager);
extern unsigned char CdvdMsgQ[];
extern void iosMsgSend(void *a0, void *a1, int a2);

void iosCdvdLoad(int a0, int a1)
{
    union U001325D8 *p = (union U001325D8 *) a0;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (a1 & 1);
    iosMsgSend(CdvdMsgQ, (void *) a0, 0);
}
void iosCdvdPackLoad(void *a0) {
    *(int *)((char *)a0 + 4) = 2;
    iosMsgSend(CdvdMsgQ, a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundMgrAdd);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", cdWait);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundRead);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdBackGroundReadIOPm);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdDirectStOpen);
void iosCdvdDirectStClose(int *self) {
    int err;
    self[0xC / 4] = 0;
    err = sceCdStStop();
    if (err == 0) {
        self[0xC / 4] = sceCdGetError();
    }
    sceSifFreeIopHeap(self[0x164 / 4]);
}
extern char D_00637E69[];
extern char D_0063A3A0[];
extern void sprintf();
extern int strcpy();

int iosCdvdChgFileName(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    sprintf(buf, D_0063A3A0, a0);
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
            if ((D_00637E69[sc] & 2) == 0)
            {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return strcpy(a0, buf);
}
/* iosCdvdSrhBuff is the directory cache: D_0063A36C records of 0x30 bytes,
 * and D_00298E68 is iosCdvdSrhBuff[0].name (the ROM addresses the name column
 * through its own symbol).  */
typedef struct
{
    int lsn;
    int size;
    char name[0x28];
} CdSrhEnt;
extern CdSrhEnt iosCdvdSrhBuff[];
extern char D_00298E68[];
extern char D_00550C58[];
extern char D_0063A398[];
extern int D_0063A36C;
extern int strcmp();
extern void debug_assert();
extern void __assert();

int iosCdvdGetFileLsn(char *name, int *size)
{
    int i;

    for (i = 0; i < D_0063A36C; i++)
    {
        if (strcmp(name, D_00298E68 + i * 0x30) == 0) goto found;
    }
    debug_assert(D_00550C58, 749);
    __assert(D_00550C58, 749, D_0063A398);
found:
    *size = iosCdvdSrhBuff[i].size;
    return iosCdvdSrhBuff[i].lsn;
}
extern int CdvdMsgQ_LoadEnd[];
extern void iosMsgRecv();

int iosCdvdSync(int a0)
{
    int local = a0;
    iosMsgRecv(CdvdMsgQ_LoadEnd, &local, 1);
    return 1;
}
extern char iosCdvd[];
void iosCdvdLoadPackFile(int a0, char *name, int a2) {
    int buf[4];
    *(long long *)iosCdvd = (*(long long *)iosCdvd & ~1LL) | (a0 & 1);
    strcpy(iosCdvd + 0x38, name);
    *(int *)(iosCdvd + 0x24) = a2;
    *(int *)(iosCdvd + 0x1C) = 0;
    *(int *)(iosCdvd + 0x20) = 0;
    iosCdvdPackLoad(iosCdvd);
    buf[0] = (int)iosCdvd;
    iosMsgRecv(CdvdMsgQ_LoadEnd, buf, 1);
}
extern int D_0063A384;

int iosCdvdDiskStatusGet(void) {
    return D_0063A384;
}
void iosCdvdBackGroundMgrDelete(char *self) {
    *(int *)(self + 0x108) |= 2;
}
int iosCdvdBackGroundMgrNotDiskReadyPauseSet(void *a0, int a1) {
    int *p = (int *)((char *)a0 + 0x108);
    return *p = (*p & ~0x10) | ((a1 & 1) << 4);
}
extern char D_006B7B80[];

int iosCdvdBackGroundMgrDeleteRequestGet(void)
{
    char *p = D_006B7B80;
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
int iosCdvdBackGroundMgrEntryNum(void)
{
    char *p = D_006B7B80;
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
void iosCdvdBackGroundMgrSeek(char *self, int val) {
    *(int *)(self + 0x110) = val;
}
extern int D_0063C17C;

int iosCdvdBackGroundMgrGetRunning(void) {
    return D_0063C17C;
}
extern char D_00550FD8[];
extern void debug_StdPrintfDummy();
extern int sceCdStRead(int a0, int a1, int a2, void *a3);

int iosCdvdDirectStRead(int a0, int a1, int a2, int *a3) {
    int local, result;
    *a3 = 0;
    result = sceCdStRead(a2 >> 11, a1, 1, &local) << 11;
    if (local != 0) { debug_StdPrintfDummy(D_00550FD8, local); *a3 = 1; }
    return result;
}
/* The inflate handler's read callback (installed by iosCdvdMgrStStart): hand
 * the decoder at most as many bytes as are still left in the streamed file --
 * its total length at +0x13C minus the bytes already consumed at +0x28.  */
long long inflate_cd_read_func(void *buf, long long size, int *self)
{
    long long rest;
    long long len;

    rest = (unsigned int) (self[0x13C / 4] - self[0x28 / 4]);

    if (rest < size) len = rest; else len = size;

    if (len != 0)
        iosCdvdHandlerReadNoInflate(self, buf, len);

    return len;
}
extern int D_0063C17C;

void iosCdvdBackGroundMgrInit(void)
{
    char *p = D_006B7B80;
    int i;
    p += 0x708;
    for (i = 6; i >= 0; i--) {
        *p = 0;
        p -= 0x12C;
    }
    D_0063C17C = 0;
}
typedef int (*BgFunc)(char *self, int arg);

void iosCdvdBackGroundMgr(void)
{
    char *bg = D_006B7B80;
    int i;
    unsigned int flag;
    BgFunc func;

    for (i = 6; i >= 0; i--, bg += 0x12C)
    {
        if (*bg == 0 || ((flag = *(unsigned int *) (bg + 0x108)) & 1) != 0) continue;
        D_0063C17C = (int) bg;
        if (((flag >> 1) & 1) == 0)
        {
            if ((func = *(BgFunc *) (bg + 0x100)) != 0)
            {
                if (func(bg, *(int *) (bg + 0x104)) > 0)
                    *(int *) (bg + 0x100) = 0;
            }
        }
        else
        {
            if ((func = *(BgFunc *) (bg + 0x124)) != 0)
                func(bg, *(int *) (bg + 0x128));
            *bg = 0;
        }
        D_0063C17C = 0;
    }
}
/* The record sceCdSearchFile fills in: it writes 0x24 bytes of it (lsn, size,
 * the name column and the date), and the stack slot it is given is 0x30.  */
typedef struct
{
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int reserved;
} CdlFILE;
extern char D_00550CC8[];
extern char D_00550CD8[];
extern int D_0063A374;
extern int sceCdDiskReady(int mode);
extern int sceCdGetDiskType(void);
extern int sceCdSearchFile(CdlFILE *fp, const char *name);

void iosCdvdDiskReadyBlock(void)
{
    if (sceCdDiskReady(1) != 2)
    {
        CdlFILE fp;
        char file[32];
        *(long long *) file = *(long long *) D_00550CC8;
        *(int *) (file + 8) = *(int *) (D_00550CC8 + 8);
        iosCdvdChgFileName((int) file);
        debug_StdPrintfDummy(D_00550CD8, D_00550CC8, file);
        do
        {
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != D_0063A374 || sceCdSearchFile(&fp, file) == 0);
    }
}
