/*
 * sce/libgraph/libgraph.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libgraph.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBGRAPH_LIBGRAPH_H
#define SCE_LIBGRAPH_LIBGRAPH_H

/* PMODE / SMODE2 / DISPFB / DISPLAY / BGCOLOR, one qword each. */
typedef struct {
    long long pmode;   /* 0x00 */
    long long smode2;  /* 0x08 */
    long long dispfb;  /* 0x10 */
    long long display; /* 0x18 */
    long long bgcolor; /* 0x20 */
} sceGsDispEnv;

/* Four (register-address, data) pairs: TEXFLUSH-or-NOP, TEX1_1, TEX0_1, CLAMP_1. */
typedef struct {
    long long texflush;      /* 0x00 */
    long long texflush_addr; /* 0x08 */
    long long tex1;          /* 0x10 */
    long long tex1_addr;     /* 0x18 */
    long long tex0;          /* 0x20 */
    long long tex0_addr;     /* 0x28 */
    long long clamp;         /* 0x30 */
    long long clamp_addr;    /* 0x38 */
} sceGsTexEnv;

/* Eight (register-address, data) pairs: FRAME_1, ZBUF_1, XYOFFSET_1, SCISSOR_1,
   PRMODECONT, COLCLAMP, DTHE, TEST_1.  Same pair convention as graph007. */
typedef struct {
    long long frame;           /* 0x00 */
    long long frame_addr;      /* 0x08 */
    long long zbuf;            /* 0x10 */
    long long zbuf_addr;       /* 0x18 */
    long long xyoffset;        /* 0x20 */
    long long xyoffset_addr;   /* 0x28 */
    long long scissor;         /* 0x30 */
    long long scissor_addr;    /* 0x38 */
    long long prmodecont;      /* 0x40 */
    long long prmodecont_addr; /* 0x48 */
    long long colclamp;        /* 0x50 */
    long long colclamp_addr;   /* 0x58 */
    long long dthe;            /* 0x60 */
    long long dthe_addr;       /* 0x68 */
    long long test;            /* 0x70 */
    long long test_addr;       /* 0x78 */
} sceGsDrawEnv;

/* The (data, address) register pair list sceGsSetDefClear fills: six GS
   register writes, TEST_1 / PRIM / RGBAQ / XYZ2 / XYZ2 / TEST_1. */
typedef struct {
    unsigned long long test_1;       /* 0x00 */
    unsigned long long test_1_addr;  /* 0x08 */
    unsigned long long prim;         /* 0x10 */
    unsigned long long prim_addr;    /* 0x18 */
    unsigned long long rgbaq;        /* 0x20 */
    unsigned long long rgbaq_addr;   /* 0x28 */
    unsigned long long xyz2_0;       /* 0x30 */
    unsigned long long xyz2_0_addr;  /* 0x38 */
    unsigned long long xyz2_1;       /* 0x40 */
    unsigned long long xyz2_1_addr;  /* 0x48 */
    unsigned long long test_1r;      /* 0x50 */
    unsigned long long test_1r_addr; /* 0x58 */
} sceGsClear;

void *sceGsGetGParam(void);     /* definition in sce/ */
unsigned long sceGsGetIMR(void); /* definition in sce/ */
void sceGsPutDispEnv(void *a0); /* definition in sce/ */
int sceGsPutDrawEnv(void *a0);  /* definition in sce/ */
unsigned long sceGsPutIMR(unsigned long imr); /* definition in sce/ */

void sceGsResetGraph(
    short mode, short inter, short omode,
    short ffmd); /* definition in sce/; the ROM sign-extends all four with sll/sra */

void sceGsResetPath(void);                      /* dominant spelling at 4 sites */
int sceGsSetDefAlphaEnv(long long *a0, int a1); /* definition in sce/ */

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx,
                        short dy); /* definition in sce/ */

int sceGsSetDefClear(sceGsClear *cl, short ztst, short x, short y, short w, short h,
                     unsigned char r, unsigned char g, unsigned char b, unsigned char a,
                     unsigned int z); /* definition in sce/ */

int sceGsSetDefDrawEnv(sceGsDrawEnv *env, short psm, short w, short h, short ztst,
                       short zpsm); /* definition in sce/ */

int sceGsSetDefTexEnv(sceGsTexEnv *env, short flush, short tbp, short tbw, short psm, short tw,
                      short th, short tfx, short cbp, short cpsm, short cld,
                      short flt); /* definition in sce/ */
int sceGsSwapDBuff(void *a0, int a1);              /* definition in sce/ */
int sceGsSyncPath(int mode, unsigned short timeout); /* definition in sce/ */
int sceGsSyncV(void);                              /* definition in sce/ */
short sceGszbufaddr(short a0, short a1, short a2); /* definition in sce/ */

#endif /* SCE_LIBGRAPH_LIBGRAPH_H */
