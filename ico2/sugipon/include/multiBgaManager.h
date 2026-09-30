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

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them.
   The record is a quadword-aligned one, as the vectors in its first 0x40
   bytes are (BgaAnimeState's layout): stageMultiBgaManager.o's .bss, which
   opens with an array of these, starts on 16 bytes after spiderGroupManager's
   run ends 8 short of it, in retail as in MAIN.MAP. */
typedef struct {
    long long w[8]; /* 0x00 */
    int obj;        /* 0x40 */
    int stay;       /* 0x44 */
    long long w48;  /* 0x48 */
} __attribute__((aligned(16))) MultiBga;

/* the state every animation slot starts from, as its fields read: the scale
   word, the identity rotation, the position and the homogeneous offset, then
   no object and not staying (MAIN.MAP multiBgaManager.o .data) */
typedef struct {
    float scale[4];  /* 0x00 */
    float rot[4];    /* 0x10 */
    float pos[4];    /* 0x20 */
    float offset[4]; /* 0x30 */
    int obj;         /* 0x40 */
    int stay;        /* 0x44 */
    int pad48[2];    /* 0x48 */
} BgaAnimeState;

extern BgaAnimeState InitialBgaMultiAnimeState;

#endif /* MULTIBGAMANAGER_H */
