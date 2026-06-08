#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", iosMcIconWriteIconsys);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", iosMcIconWriteIcon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", _iosMcIconWriteIconsys);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137DB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137E00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137E48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137E90);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137F20);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00137F68);

extern void iosMcHandlerWrite(int self, int p, int sz);
extern int D_0027CFE0[];

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

typedef struct { long long x[8]; } __attribute__((packed)) Blk40_001383F8;
typedef struct { char pad[0x140]; int f140; int f144; int f148; Blk40_001383F8 f14C; } Elem_001383F8;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00138100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcdata", func_00138218);
