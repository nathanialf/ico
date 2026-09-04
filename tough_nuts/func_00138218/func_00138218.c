#include "common.h"

extern int iosMsgSend(void *a, void *b, int c);
extern int D_0027D308[];
typedef union { long long ll; struct { int lo, hi; } w; } McHdr;

int iosMcGetDir(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 6;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcDelete(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcSaveIconBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcSaveProductBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 8;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcLoadProductBlock(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 9;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcSaveGameBlock(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xA;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcLoadGameBlock(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xB;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcChdirProduct(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xC;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcGetBlockSaveInfo(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xD;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

typedef struct { long long x[8]; } __attribute__((packed)) Blk40_001383F8;
typedef struct { char pad[0x140]; int f140; int f144; int f148; Blk40_001383F8 f14C; } Elem_001383F8;
typedef struct { char p[8]; int idx; } McSelf_F68;

extern Elem_001383F8 D_0027CFE0[];
extern void func_00135F88(void *a0, int a1, int a2);
extern unsigned int D_iconParam[] __asm__("D_0027126C");
extern unsigned char D_0027D500[];
extern unsigned int D_0062A410;
extern int soundReverbDepthGet(void);
extern void iosMcHandlerWrite(int self, int p, int sz);

int func_00137F68(void *self) {
    {
        int e = ((int *)self)[2] * 0x18C;
        e += (int)D_0027CFE0;
        *(int *)(e + 0x140) = D_iconParam[0];
    }
    D_0027CFE0[((int *)self)[2]].f144 = soundReverbDepthGet();
    D_0027CFE0[((int *)self)[2]].f148 = D_0062A410;
    *(Blk40_001383F8 *)((char *)&D_0027CFE0[0].f14C + ((int *)self)[2] * 0x18C) =
        *(Blk40_001383F8 *)D_0027D500;
    func_00135F88(self, (int)&D_0027CFE0[((int *)self)[2]], 0x18C);
    return 0;
}

int func_00138098(int *self)
{
    int idx = self[0x8 / 4];
    iosMcHandlerWrite((int)self, (int)((char *)D_0027CFE0 + idx * 0x18C), 0x18C);
    return self[0x10 / 4];
}

extern void func_00135F88(void *a0, int a1, int a2);

int func_001380E0(void *a0, int a1) {
    func_00135F88(a0, a1, 0x63FC);
    return 0;
}

extern unsigned int D_00274EEC_a[] __asm__("D_0027126C");
extern unsigned char D_0027D500[];
extern unsigned int D_0062A410;
extern void soundOutputModeSet(int);

int func_00138100(void *self, int a1) {
    iosMcHandlerWrite((int)self, a1, 0x63FC);
    {
        int e = ((int *)self)[2] * 0x18C;
        e += (int)D_0027CFE0;
        D_iconParam[0] = *(int *)(e + 0x140);
    }
    soundOutputModeSet(D_0027CFE0[((int *)self)[2]].f144);
    {
        int p = ((int *)self)[2] * 0x18C;
        int e = p + (int)D_0027CFE0;
        int v = *(int *)(e + 0x148);
        *(Blk40_001383F8 *)D_0027D500 =
            *(Blk40_001383F8 *)((char *)&D_0027CFE0[0].f14C + p);
        D_0062A410 = v;
    }
    return ((int *)self)[4];
}

extern void iosMallocResetPartition(void);
extern int iosCdvdChgFileName(void *a1, void (*cb)(void), int *buf, int, int, int, int, int);
extern int func_00137B50(void *a0);
extern int iosCdvdBackGroundMgrEntryNum(void *a0);
extern int D_0062BF88;

int func_00138218(void *a0, void *a1) {
    int buf[4];
    int s3;
    int acc = 0;
    buf[0] = (*(int *)((char *)a1 + 0x20) + 0x7FF) / 0x800 * 0x800;
    s3 = iosCdvdChgFileName(a1, iosMallocResetPartition, buf, 0, 0, 0, 0, 0);
    if (buf[0] > 0) {
        do {
            int chunk;
            buf[1] = 0;
            do {
                func_00137B50(a0);
                chunk = buf[1];
            } while (chunk == 0);
            acc += chunk;
            if (*(int *)((char *)a1 + 0x20) < acc)
                chunk -= acc - *(int *)((char *)a1 + 0x20);
            func_00135F88(a0, buf[2], chunk);
            D_0062BF88 = 1;
        } while (buf[0] > 0);
    }
    iosCdvdBackGroundMgrEntryNum((void *)s3);
    return 0;
}
