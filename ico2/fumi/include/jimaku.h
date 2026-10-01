/*
 * ico2/fumi/include/jimaku.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what jimaku.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef JIMAKU_H
#define JIMAKU_H

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for jimaku.c and the 7 script TUs that queue subtitles; jimaku.c's own copy (jSub/jArg) had the same layout. */
typedef struct JimakuSub {
    char unk00[0x2C]; /* 0x0C */
    int unk2C;        /* 0x38 */
    int n;            /* 0x3C */
    int unk34;        /* 0x40 */
    int unk38;        /* 0x44 */
    void *unk3C;      /* 0x48 */
    void *unk40;      /* 0x4C */
} JimakuSub;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for jimaku.c and the 7 script TUs that queue subtitles; jimaku.c's own copy (jSub/jArg) had the same layout. */
typedef struct JimakuArg {
    int cmd;       /* 0x00 */
    int unk04;     /* 0x04 */
    int done;      /* 0x08 */
    JimakuSub sub; /* 0x0C */
} JimakuArg;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order jimaku.c's inline tail has. */
void jimakuManager(void);
void jimakuUndisp(JimakuArg *msg);

void jimakuBegin(JimakuArg *msg);
void jimakuEnd(JimakuArg *msg);
void jimakuJump(JimakuArg *msg);

/* jimaku.c's globals (MAIN.MAP's jimaku.o names) */
extern char jimakuThread[];
extern char jimakuThreadStack[];
extern int jimakuMsgQ[];
extern int jimakuOn;
extern int jimakuMsgBuf[2];
extern JimakuArg jimaku_msg;

void jimakuMgrBegin(JimakuArg *p);
void jimakuMgrNext(JimakuArg *p);
void jimakuDisp(JimakuArg *msg);

#endif /* JIMAKU_H */
