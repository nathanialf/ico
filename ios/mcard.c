#include "common.h"

typedef union { long long ll; struct { int lo, hi; } w; } McHdr;

typedef union { long long ll; struct { int lo, hi; } w; } McTestVal;

INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrGetInfo);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerWrite);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcHandlerRead);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrChdirProduct);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrSaveSeg);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrLoadSeg);
extern void iosMcMgrSaveSeg(void *a0, int a1);

void iosMcMgrSaveProductBlock(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrSaveSeg(a0, 0);
}
extern void iosMcMgrLoadSeg(void *a0, int a1);

void iosMcMgrLoadProductBlock(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrLoadSeg(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcMgrGetBlockSaveInfo);
INCLUDE_ASM("asm/nonmatchings/ios/mcard", iosMcManager);
extern int D_006BC8C0[];
extern char D_0063A490[];
extern int D_0063A47C;
extern int D_0063A488;
extern int CreateSema(int *param);
extern int WaitSema(int sema);
extern int DeleteSema(int sema);
extern int sceMcSync(int mode, int *cmd, int *result);
extern void debug_StdPrintfDummy(char *fmt, ...);

void iosMcMgrSync(void *mp)
{
    D_006BC8C0[4] = 1;
    D_006BC8C0[1] = 1;
    D_006BC8C0[2] = 0;
    D_0063A47C = CreateSema(D_006BC8C0);
    debug_StdPrintfDummy(D_0063A490, D_0063A47C);
    do {
        WaitSema(D_0063A47C);
        D_0063A488++;
    } while (sceMcSync(1, (int *)((char *)mp + 0x30), (int *)((char *)mp + 0x10)) == 0);
    DeleteSema(D_0063A47C);
    D_0063A47C = -1;
}
void iosMcTest(void) {}
int iosMcSync(unsigned long *a0)
{
    unsigned long x = *a0;
    char y = x;
    unsigned long z = y & 1ul;
    y = z;
    return -((int)y);
}
extern char D_0029B9E8[];
extern int iosMsgSend(void *a0, void *a1, int a2);

int iosMcGetInfo(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 0;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
int iosMcFormat(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 3;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
int iosMcUnformat(void *a0) {
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 4;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}
extern int D_0029B9E8__pn[] __asm__("D_0029B9E8");

int iosMcGetDir(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 6;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
extern int D_0029B9E8__pn[] __asm__("D_0029B9E8");

int iosMcDelete(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcSaveIconBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcSaveProductBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 8;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcLoadProductBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 9;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcSaveGameBlock(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xA;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcLoadGameBlock(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xB;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcChdirProduct(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xC;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
int iosMcGetBlockSaveInfo(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xD;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8__pn, a0, 0);
}
typedef struct { char b[0x40]; } McBlk;

typedef struct {
    char unk0[0x190];
    int soundMode;
    int outputMode;
    int unk198;
    int gobj;
    char blk[0x40];
    char unk1E0[8];
    int cameraMove;
    int unk1EC;
} McSaveRec;

extern McSaveRec D_0029B5F0[];
extern char D_0029BC00[];
extern int D_0063A538;
extern int CurrentTargetGObj;
extern int D_0028F4C0[];
extern int NonLinearCameraMove;
extern int soundOutputModeGet(void);

int product_write(int *self)
{
    (D_0029B5F0 + self[2])->soundMode = D_0028F4C0[11];
    (D_0029B5F0 + self[2])->outputMode = soundOutputModeGet();
    (D_0029B5F0 + self[2])->unk198 = D_0063A538;
    (D_0029B5F0 + self[2])->gobj = CurrentTargetGObj;
    (D_0029B5F0 + self[2])->cameraMove = NonLinearCameraMove;
    (D_0029B5F0 + self[2])->unk1EC = D_0028F4C0[0];
    *(McBlk *)(D_0029B5F0 + self[2])->blk = *(McBlk *)D_0029BC00;
    iosMcHandlerWrite((int)self, (int)(D_0029B5F0 + self[2]), 0x1F0);
    return 0;
}
int product_read(int *self) {
    int idx = self[0x8 / 4];
    iosMcHandlerRead((int)self, (int)&D_0029B5F0[idx], 0x1F0);
    return self[0x10 / 4];
}
extern int CurrentTargetGObjSub;
extern int D_00639EA0;

int gameblock_write(int self, void *buf)
{
    iosMcHandlerWrite(self, buf, 0x63F4);
    iosMcHandlerWrite(self, &CurrentTargetGObjSub, 4);
    iosMcHandlerWrite(self, &D_00639EA0, 4);
    return 0;
}
extern int D_0028F4EC[];
extern void soundOutputModeSet(int mode);

int gameblock_read(int *self, void *buf)
{
    iosMcHandlerRead((int)self, (int)buf, 0x63F4);
    D_0028F4EC[0] = (D_0029B5F0 + self[2])->soundMode;
    soundOutputModeSet((D_0029B5F0 + self[2])->outputMode);
    D_0063A538 = (D_0029B5F0 + self[2])->unk198;
    CurrentTargetGObj = (D_0029B5F0 + self[2])->gobj;
    *(McBlk *)D_0029BC00 = *(McBlk *)(D_0029B5F0 + self[2])->blk;
    iosMcHandlerRead((int)self, (int)&CurrentTargetGObjSub, 4);
    iosMcHandlerRead((int)self, (int)&D_00639EA0, 4);
    return self[4];
}
