#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Init);

int dl_Clear(void) {
    return 0x14;
}

extern int D_00629F5C;

int dl_Swap(void) {
    return (0x3200 / D_00629F5C) / 2;
}

extern int D_0062BAE0, D_0062BAE4, D_0062BAE8, D_0062BAEC, D_0062BAF0;

void dl_PushPriority(void) {
    D_0062BAE0 = 0;
    D_0062BAF0 = 0x80;
    D_0062BAEC = 0x80;
    D_0062BAE8 = 0x80;
    D_0062BAE4 = 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PopPriority);

extern int D_0062C25C;
extern int D_0062C260;
extern int D_0070A7C8[];
extern int D_0070A5C0[];
extern void func_001F8848(void);
extern void gif_SpriteSensitive(void);
extern void pac_openDmaTag(void);

void dl_Debug(void)
{
    int flag = D_0062C25C ^ 1;
    int *src = (int *)((char *)D_0070A7C8 + flag * 0x34);
    char *dst = (char *)D_0070A5C0;
    int i;
    D_0062C25C = flag;
    D_0062C260 = 0;
    for (i = 0xC; i >= 0; i--) {
        int v = *src;
        *(int *)dst = 0;
        src++;
        *(int *)(dst + 0x24) = v;
        *(int *)(dst + 0x20) = v;
        dst += 0x28;
    }
    func_001F8848();
    gif_SpriteSensitive();
    pac_openDmaTag();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_CloseDma);

extern int D_0062BB00;
extern int D_0070A830[];
extern void debug_StdPrintfDummy();
extern void func_001AAD00(char *file, int line);
extern void __assert(char *file, int line, void *expr);
extern char D_006136B0[];
extern char D_00613698[];
extern char D_0062D988[];

void dl_Out(void) {
    if (D_0062BB00 < 7) {
        int i = D_0062BB00;
        D_0070A830[i] = D_0062C260;
        D_0062BB00 = i + 1;
    } else {
        debug_StdPrintfDummy(D_006136B0);
        func_001AAD00(D_00613698, 0x20E);
        __assert(D_00613698, 0x20E, D_0062D988);
    }
}

extern int D_0062BB00;
extern int D_0070A830[];
extern void debug_StdPrintfDummy();
extern void func_001AAD00(char *file, int line);
extern void __assert(char *file, int line, void *expr);
extern char D_006136D8[];
extern char D_00613698[];
extern char D_0062D988[];

void dl_SetDLPriority(void) {
    if (D_0062BB00 > 0) {
        int i = D_0062BB00 - 1;
        D_0062BB00 = i;
        D_0062C260 = D_0070A830[i];
    } else {
        debug_StdPrintfDummy(D_006136D8);
        func_001AAD00(D_00613698, 0x220);
        __assert(D_00613698, 0x220, D_0062D988);
    }
}

extern int D_00613700[];
extern void debug_StdPrintfDummy(int *a0, int a1);

void dl_OpenDma(void)
{
    int *entry = &D_0070A5C0[D_0062C260 * 10];
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_StdPrintfDummy(D_00613700, count - 1);
}

typedef struct {
    int          f_0;    /* 0x00 */
    int          f_4;    /* 0x04 */
    long long    f_8;    /* 0x08 */
    unsigned int f_10;   /* 0x10 */
    int          pad_14; /* 0x14 */
    long long    f_18;   /* 0x18 */
    int          pad_20; /* 0x20 */
    int          f_24;   /* 0x24 */
} DlEntry;   /* stride 0x28 */

void dl_GetPri(void) {
    DlEntry *e = &((DlEntry *)D_0070A5C0)[D_0062C260];
    unsigned long long t0 = (unsigned long long)(e->f_8 & 0x7FFFFFFF) << 32;
    unsigned long long kind = e->f_18;
    unsigned long long val;
    unsigned long long tag;
    unsigned long long out;
    long long *fp;

    if (kind == 6) goto count_er;
    if (kind < 7) {
        if (kind == 0) goto count_er;
        val = e->f_10;
        goto load_fp;
    }
    if (kind == 7) goto count7;
    val = e->f_10;
    goto load_fp;

count_er:
    fp = (long long *)e->f_4;
    val = (unsigned long long)(((unsigned int)(e->f_24 - (int)fp) >> 4) - 1);
    if (val == 0) { e->f_24 -= 16; e->f_0 = 0; return; }
    goto dispatch;

count7:
    fp = (long long *)e->f_4;
    val = (unsigned long long)(((unsigned int)(e->f_24 - (int)fp) >> 4) - 1);
    goto dispatch;

load_fp:
    fp = (long long *)e->f_4;

dispatch:
    switch (kind) {
    case 0: tag = 0x10000000ULL; break;
    case 1: tag = t0 | 0x20000000ULL; break;
    case 2: tag = t0 | 0x30000000ULL; break;
    case 3: tag = t0 | 0x40000000ULL; break;
    case 4: out = val | t0; goto do_store;
    case 5: tag = t0 | 0x50000000ULL; break;
    case 6: tag = 0x60000000ULL; break;
    case 7: tag = 0x70000000ULL; break;
    default: goto skip_store;
    }
    out = val | tag;
do_store:
    *fp = out;
skip_store:
    fp[1] = 0;
    e->f_0 = 0;
}


extern void iosMallocCheckLeak2(int a0);

void func_001F8660(void) {
    int i;
    for (i = 0; i < 2; i++) {
        int *p = (int *)((char *)D_0070A7C8 + i * 0x34);
        int j;
        for (j = 0xC; j >= 0; j--) {
            iosMallocCheckLeak2(*p);
            p++;
        }
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned int       f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned int       f_24;  /* 0x24 */
} S_0070A5C0;  /* stride 0x28 */

typedef struct {
    char               f_0;  /* 0x00 */
    char               f_1;  /* 0x01 */
} S_004C3750;  /* stride 0x2 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070A830;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613750;  /* stride 0x4 */

/* end struct shapes */
