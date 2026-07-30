#include "common.h"

#include "ico/types.h"

typedef union { int w[2]; long long d; } DmaTag;
extern int D_004C7710[];
extern int D_0063378C;
extern int D_00276214[];
extern void func_00244980();
extern void func_00122BA0(void *req);

/* The file manager's request queue is keyed on an object's 0x15C sub-state.
 * file_Init / file_LoadCDFile take that block directly; the file_LoadFile /
 * func_0010ECB0 layer takes the owning GObj and hands down its 0x15C. */

void file_Init(void *req)
{
    func_00122BA0(req);
}

void file_LoadCDFile(void *req)
{
    func_00122BA0(req);
}

void file_LoadFile(GObj *self) {
    file_LoadCDFile(GOBJ_SUB(self));
}

void func_0010ECB0(GObj *self) {
    file_LoadFile(self);
}

void func_0010ECB8(GObj *self) {
    file_Init(GOBJ_SUB(self));
}

void func_0010ECC0(GObj *self) {
    func_0010ECB8(self);
}

void func_0010ECC8(void)
{
    func_00244980(D_0063378C, D_00276214[0]);
}

void func_0010ECD8(void) {}

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010ECE0);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010EE90);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F5B8);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F5D8);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F630);

void func_0010F710(void)
{
    register int *base = D_004C7710;
    register int *p = (int *)base[4];
    base[6] = 0;
    base[7] = 0;
    base[4] = (int)(p + 2);
    base[3] = (int)p;
    base[5] = (int)p;
    p[2] = 0x11000000;
    base[6] = (int)(p + 3);
    base[7] = (int)(p + 4);
    base[4] = (int)(p + 6);
    ((DmaTag *)(p + 6))->d = 0xE;
    base[4] = (int)(p + 8);
}

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F768);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F880);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010F9A8);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010FB28);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010FCC0);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_0010FF28);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_00110050);

INCLUDE_ASM("asm/nonmatchings/src/FileManager", func_001101E0);

