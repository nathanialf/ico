/*
 * ico2/sugipon/include/motionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

#include "typedef.h"

/* An object and one of its nodes: the motion work opens with the parent
   it is linked to, the rootUpdates return the one they stand on, and the
   wall-hit record at ClipBuf+0x80 is one followed by the hit count.  GetPureVerticalPlane reads it as its `int *cfg` argument (see
   getVerticalElementOfWallNormal in src/motionManager2) and the character
   record keeps a copy at +0xE0.  The object/node pair is its own member: the
   ROM copies it as an eight-byte block and the count as a separate word. */
typedef struct {
    char *obj; /* the object (a GObj) */
    int node;  /* the node index in its geometry */
} ObjNode;     /* derived name */

typedef struct {
    ObjNode o;
    void *n;
} WallCfg;

/* RECONSTRUCTION: the 0xC0-byte field/wall clip request block.  The sweep
   radius at +0x70 is _wallHitReaction's initialiser's single non-zero
   element; +0x74 is the element filter _wallCollisionPreProcess copies in
   from the root block, +0x80 and +0x8C the wall and floor the search hit, each
   an object node and the element, as fieldCollision.h's ClipWork has them.
   The block is quadword aligned: the ROM's constant initialiser of one
   (checkWallSideState's, at 0x61FD00 in .rodata) sits on a 16-byte boundary
   after EditRotEmphasys's 8-aligned strings, the alignment of the points the
   block opens with. */
typedef struct {
    float pt[3][4]; /* 0x00 the start, end and clipped points */
    char _30[0x40];
    float rad;      /* 0x70 sweep radius */
    WallCfg filter; /* 0x74 the element the search skips */
    WallCfg wall;   /* 0x80 the wall the search hit */
    WallCfg floor;  /* 0x8C the floor the search hit */
    int attr;       /* 0x98 */
    char _9C[0x4];
    Vec16 normal; /* 0xA0 the hit plane */
    char _B0[0x10];
} __attribute__((aligned(16))) ClipBuf;

/* RECONSTRUCTION, names ours: a node's 0x40-byte IK state: the blend rate
   _getFinalMatrix eases toward its target, the heading, pitch and pitch step
   of the look turn, and the node's three quaternions. */
typedef struct {
    float rate; /* 0x00 */
    short h;    /* 0x04 */
    short _6;
    short p; /* 0x08 */
    short _A[2];
    short dp;     /* 0x0E */
    float q[4];   /* 0x10 */
    float q20[4]; /* 0x20 */
    float q30[4]; /* 0x30 */
} MotIk;          /* derived name */

/* RECONSTRUCTION, names ours: one entry of a node's interp limit table, in
   degrees: the heading, pitch and bank limits _getFinalMatrix's turns are
   clamped to, read at 12-byte steps (the table's +0x30 and +0x48 headings are
   entries 4 and 6). */
typedef struct {
    float h;
    float p;
    float b;
} MotLimAng; /* derived name */

/* RECONSTRUCTION, names ours: the motion work's root block (the motion work
   + 0xA0, up to its motion-control block at + 0x470), the record skelRoot
   points at.  The position, translation, rotation and the last position are
   what every rootUpdate reads and writes; the wall records are the ones the
   hit tests keep; the lift pair and the turn at + 0x300 are _getFinalMatrix's.
   Fields from the access widths and offsets in this file; names offset-derived
   where nothing names them. */
struct MotRoot {
    float pos[4];   /* 0x0 */
    float trans[4]; /* 0x10 */
    char _pad20[0x10];
    float quat[4]; /* 0x30 */
    char _pad40[0x10];
    short twist; /* 0x50 */
    char _pad52[0x2];
    float twistRate; /* 0x54 */
    char _pad58[0x8];
    float up[4];      /* 0x60 */
    float savePos[4]; /* 0x70 */
    ObjNode hitObj;   /* 0x80 */
    char _pad88[0x8];
    float move[4]; /* 0x90 */
    char _padA0[0x20];
    float height; /* 0xC0 */
    char _padC4[0xC];
    float delta[4];  /* 0xD0 */
    WallCfg wall;    /* 0xE0 */
    int wallCount;   /* 0xEC */
    WallCfg wallF0;  /* 0xF0 */
    int f_FC;        /* 0xFC */
    WallCfg wall100; /* 0x100 */
    char _pad10C[0x14];
    WallCfg filter; /* 0x120 */
    char _pad12C[0x4];
    Vec16 plane; /* 0x130 */
    char _pad140[0x4];
    void *f_144; /* 0x144 */
    char _pad148[0x8];
    float last[4]; /* 0x150 */
    float v160[4]; /* 0x160 */
    float v170[4]; /* 0x170 */
    int f_180;     /* 0x180 */
    char _pad184[0xC];
    float v190[4]; /* 0x190 */
    float v1A0[4]; /* 0x1A0 */
    float v1B0[4]; /* 0x1B0 */
    float v1C0[4]; /* 0x1C0 */
    float f_1D0;   /* 0x1D0 */
    char _pad1D4[0x2C];
    int f_200;     /* 0x200 */
    int f_204;     /* 0x204 */
    float lift[2]; /* 0x208 */
    char _pad210[0x20];
    int f_230; /* 0x230 */
    int f_234; /* 0x234 */
    char _pad238[0x8];
    float v240[4]; /* 0x240 */
    float q250[4]; /* 0x250 */
    char _pad260[0x30];
    int f_290; /* 0x290 */
    int f_294; /* 0x294 */
    char _pad298[0x8];
    float v2A0[4]; /* 0x2A0 */
    float q2B0[4]; /* 0x2B0 */
    float f_2C0;   /* 0x2C0 */
    int f_2C4;     /* 0x2C4 */
    int f_2C8;     /* 0x2C8 */
    char _pad2CC[0x4];
    float q2D0[4]; /* 0x2D0 */
    int f_2E0;     /* 0x2E0 */
    char _pad2E4[0xC];
    float v2F0[4]; /* 0x2F0 */
    short h;       /* 0x300 */
    short p;       /* 0x302 */
    short b;       /* 0x304 */
    char _pad306[0x2];
    int f_308; /* 0x308 */
    int f_30C; /* 0x30C */
    int f_310; /* 0x310 */
    int f_314; /* 0x314 */
    int f_318; /* 0x318 */
    int f_31C; /* 0x31C */
    int f_320; /* 0x320 */
    int f_324; /* 0x324 */
    char _pad328[0x4];
    int f_32C;   /* 0x32C */
    int f_330;   /* 0x330 */
    int f_334;   /* 0x334 */
    float f_338; /* 0x338 */
    char _pad33C[0x14];
    float v350[4]; /* 0x350 */
    int f_360;     /* 0x360 */
    int f_364;     /* 0x364 */
    char _pad368[0x8];
    float v370[4]; /* 0x370 */
    int f_380;     /* 0x380 */
    char *f_384;   /* 0x384 */
    int f_388;     /* 0x388 */
    char _pad38C[0x4];
    float q390[4];      /* 0x390 */
    float v3A0[4];      /* 0x3A0 */
    float f_3B0;        /* 0x3B0 */
    unsigned int f_3B4; /* 0x3B4 */
    float f_3B8;        /* 0x3B8 */
    float f_3BC;        /* 0x3BC */
    float f_3C0;        /* 0x3C0 */
    float f_3C4;        /* 0x3C4 */
    float f_3C8;        /* 0x3C8 */
    char _pad3CC[0x4];
};

/* the 0x08C counter (cleared by shiftMotionData, stepped by
   UpdateFrameCounter) is not an int to the scheduler: in shiftMotionData its
   store does not precede the inlined int table read the other int stores do,
   so its lvalue has an alias set of its own, which a 32-bit enumerated type
   gives (motionOrientManager.c). */
enum MotOriStep { MOTORI_STEP_0 };

/* RECONSTRUCTION, names ours: the motion work's motion-control block (the
   motion work + 0x470), the record skelMotCtrl points at: the stream, the
   status flags, the motion number and the root-update mode the assert in
   _getGeometryOfMotion prints ("ID", "rootUpdateMode"), the wall and cliff
   distances and normals the hit tests leave.  Names offset-derived where
   nothing names them. */
struct MotCtrl {
    int stream;         /* 0x0 */
    int f_4;            /* 0x4 */
    int f_8;            /* 0x8 */
    int f_C;            /* 0xC */
    int f_10;           /* 0x10 */
    unsigned int flags; /* 0x14 */
    int f_18;           /* 0x18 */
    int *f_1C;          /* 0x1C */
    int *f_20;          /* 0x20 */
    int f_24;           /* 0x24 */
    int f_28;           /* 0x28 */
    int f_2C;           /* 0x2C */
    int motion;         /* 0x30 */
    int f_34;           /* 0x34 */
    int f_38;           /* 0x38 */
    float f_3C;         /* 0x3C */
    float f_40;         /* 0x40 */
    float f_44;         /* 0x44 */
    float f_48;         /* 0x48 */
    float f_4C;         /* 0x4C */
    float f_50;         /* 0x50 */
    int f_54;           /* 0x54 */
    int f_58;           /* 0x58 */
    int f_5C;           /* 0x5C */
    int f_60;           /* 0x60 */
    int f_64;           /* 0x64 */
    int rootUpdateMode; /* 0x68 */
    int f_6C;           /* 0x6C */
    int f_70;           /* 0x70 */
    int f_74;           /* 0x74 */
    char _pad78[0x4];
    int f_7C;             /* 0x7C */
    int f_80;             /* 0x80 */
    int f_84;             /* 0x84 */
    int f_88;             /* 0x88 */
    enum MotOriStep f_8C; /* 0x8C */
    int f_90;             /* 0x90 */
    int f_94;             /* 0x94 */
    int f_98;             /* 0x98 */
    int f_9C;             /* 0x9C */
    int f_A0;             /* 0xA0 */
    int f_A4;             /* 0xA4 */
    char _padA8[0x8];
    float v0B0[4]; /* 0xB0 */
    float v0C0[4]; /* 0xC0 */
    int f_D0;      /* 0xD0 */
    int f_D4;      /* 0xD4 */
    int f_D8;      /* 0xD8 */
    int f_DC;      /* 0xDC */
    int f_E0;      /* 0xE0 */
    int f_E4;      /* 0xE4 */
    int f_E8;      /* 0xE8 */
    float f_EC;    /* 0xEC */
    float f_F0;    /* 0xF0 */
    int f_F4;      /* 0xF4 */
    int f_F8;      /* 0xF8 */
    int f_FC;      /* 0xFC */
    int f_100;     /* 0x100 */
    int f_104;     /* 0x104 */
    int f_108;     /* 0x108 */
    int f_10C;     /* 0x10C */
    float f_110;   /* 0x110 */
    float f_114;   /* 0x114 */
    char _pad118[0x8];
    float v120[4]; /* 0x120 */
    float f_130;   /* 0x130 */
    float f_134;   /* 0x134 */
    float f_138;   /* 0x138 */
    char _pad13C[0x4];
    float v140[4]; /* 0x140 */
    float v150[4]; /* 0x150 */
    float v160[4]; /* 0x160 */
    float f_170;   /* 0x170 */
    float f_174;   /* 0x174 */
    float f_178;   /* 0x178 */
    int f_17C;     /* 0x17C */
    int f_180;     /* 0x180 */
    int f_184;     /* 0x184 */
    int f_188;     /* 0x188 */
    char _pad18C[0x4];
    int f_190; /* 0x190 */
    int f_194; /* 0x194 */
    int f_198; /* 0x198 */
    int f_19C; /* 0x19C */
    int f_1A0; /* 0x1A0 */
    int f_1A4; /* 0x1A4 */
    char _pad1A8[0x4];
    int f_1AC; /* 0x1AC */
    char _pad1B0[0x4];
    int f_1B4; /* 0x1B4 */
    int f_1B8; /* 0x1B8 */
    int f_1BC; /* 0x1BC */
    int f_1C0; /* 0x1C0 */
    char _pad1C4[0x8];
    int f_1CC;   /* 0x1CC */
    float f_1D0; /* 0x1D0 */
    float f_1D4; /* 0x1D4 */
    char *obj;   /* 0x1D8 */
    int f_1DC;   /* 0x1DC */
    int f_1E0;   /* 0x1E0 */
    char _pad1E4[0xC];
};

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionManager.c's inline tail has. */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(char *a0, int a1);
int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f);
void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k);
void _checkCliffAndWall(void);
void _getFinalMatrix(int id);
int adjustSideWall(ClipBuf *w, int a1, int a2);
int checkActPointWithHeight(int kind, float h);
void checkCliffState(int a0);
void checkWallSideState(void);
void checkWallState(int flag);
void clearCollisionStatus(void);
int findActPoint(int *list);
void getFinalMatrixWithNaturalGeometry(int id);
void _wallHitReaction(ClipBuf *w, void *pos, void *last, int noSlide);

#endif /* MOTIONMANAGER_H */
