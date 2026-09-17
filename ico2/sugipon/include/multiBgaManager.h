/*
 * ico2/sugipon/include/multiBgaManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what multiBgaManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MULTIBGAMANAGER_H
#define MULTIBGAMANAGER_H

typedef struct {
    float f0;        /* 0x00 */
    char pad04[0xC]; /* 0x04 */
    char m10[0x10];  /* 0x10 */
    char m20[0x10];  /* 0x20 */
    char m30[0x10];  /* 0x30 */
    int obj;         /* 0x40 */
    int x44;         /* 0x44 */
    char pad48[0x8]; /* 0x48 */
} BgaDisp;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order multiBgaManager.c's inline tail has. */
void EntryMultiBgaManagerNoKind(BgaDisp *bga, int no, void *pos);
void DispMultiBgaManagerWithKind(int kind, BgaDisp *base, int n);

void EntryMultiBgaManager(BgaDisp *bga, int no, int kind, void *pos, void *rot);
void *InitMultiBgaManager(int n);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    long long w[8]; /* 0x00 */
    int obj;        /* 0x40 */
    int stay;       /* 0x44 */
    long long w48;  /* 0x48 */
} MultiBga;

#endif /* MULTIBGAMANAGER_H */
