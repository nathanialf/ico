#include "common.h"

extern int iosMsgSend(void *a, void *b, int c);
extern int D_0027D308[];
typedef union { long long ll; struct { int lo, hi; } w; } McHdr;

int iosMcIconWriteIconsys(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 6;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int iosMcIconWriteIcon(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int _iosMcIconWriteIconsys(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137DB8(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 8;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137E00(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 9;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137E48(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xA;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137E90(void *a0, int a1) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xB;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137ED8(void *a0) {
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xC;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0027D308, a0, 0);
}

int func_00137F20(void *a0) {
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
extern void soundAllocIopHeap(int);

/* parked: needs real matching (packed-struct copy regalloc, stride 0x18C).
 * See tough_nuts/func_00138100/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00138100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00138218);
