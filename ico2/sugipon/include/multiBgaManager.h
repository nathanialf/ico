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

/* One multi-BGA slot: the frame its animation has reached (below 0 while the
   slot is idle), the position, the drift added to the position every frame
   (zero unless entered sensitive), the rotation quaternion, the animation and
   whether it stays on its last frame.  The record is quadword aligned, as its
   vectors are: stageMultiBgaManager.o's .bss, which opens with an array of
   these, starts on 16 bytes after spiderGroupManager's run ends 8 short of
   it, in retail as in MAIN.MAP. */
typedef struct {    /* field names derived */
    float frame;    /* 0x00 */
    float pad04[3]; /* 0x04 */
    float pos[4];   /* 0x10 */
    float vel[4];   /* 0x20 */
    float rot[4];   /* 0x30 */
    int kind;       /* 0x40, -1 for none */
    int stay;       /* 0x44 */
    int pad48[2];   /* 0x48 */
} __attribute__((aligned(16))) BgaDisp;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order multiBgaManager.c's inline tail has. */
void EntryMultiBgaManagerNoKind(BgaDisp *bga, int no, void *pos);
void DispMultiBgaManagerWithKind(int kind, BgaDisp *base, int n);
void EntryMultiBgaManager(BgaDisp *bga, int no, int kind, void *pos, void *rot);
BgaDisp *InitMultiBgaManager(int n);
void EntryMultiBgaManagerSensitive(BgaDisp *bga, int no, int kind, void *pos, void *rot, void *vel);

/* the state every slot starts from (MAIN.MAP multiBgaManager.o .data): idle,
   at the origin, not drifting, unrotated, no animation, not staying.  It is
   the slot's fields without the slot's quadword alignment (the object sits on
   8 bytes in the ROM's .data), so a slot is reset by copying it through the
   slot's type, which is what gives the ROM's quadword copy. */
typedef struct {    /* field names derived */
    float frame;    /* 0x00 */
    float pad04[3]; /* 0x04 */
    float pos[4];   /* 0x10 */
    float vel[4];   /* 0x20 */
    float rot[4];   /* 0x30 */
    int kind;       /* 0x40 */
    int stay;       /* 0x44 */
    int pad48[2];   /* 0x48 */
} BgaAnimeState;

extern BgaAnimeState InitialBgaMultiAnimeState;

#endif /* MULTIBGAMANAGER_H */
