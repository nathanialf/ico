/*
 * ico2/common/include/charFileManager.h
 *
 * The declarations of what charFileManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CHARFILEMANAGER_H
#define CHARFILEMANAGER_H

/* charFileManager.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void ReadSoundSqFile(void *h, int name, int size, int id, int kind, int word08, int seg);
void ReadSoundAdpcmFile(void *h, int name, int size, int id, int kind, int word08, int seg);
void InitCharFileManager(void);
void ResetCharFileManager(void);

struct Sub15C;

void CSVSYSTEM_ReadCharFiles(struct Sub15C *rec, int id);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
/* texture-path: one texture file, 0x20 bytes. Readers: kanban.c,
 * layout_texture.c. Owner: ico2/common/include/charFileManager.h. */
typedef struct {   /* field names derived */
    char path[32]; /* 0x00 */
} TexRec;          /* derived name */
#else
/* texture-path: one texture file, 0x34 bytes (JPN, KOR and CN 0x30, in .rodata). Readers:
 * ico2/common/src/charFileManager.c (TexRec, PAL), kanban.c, layout_texture.c.
 * Owner: ico2/common/include/charFileManager.h. */
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
typedef struct {   /* field names derived */
    char path[48]; /* 0x00 */
} TexRec;          /* derived name */
#else
typedef struct {    /* field names derived */
    char path[48];  /* 0x00 */
    int cameraMove; /* 0x30, compared with NonLinearCameraMove */
} TexRec;           /* derived name */
#endif
#endif

/* model-path: one model, 0x8C bytes, indexed by the model id. Reader:
 * ico2/common/src/PObj.c (InitPObj, AllocPObj, MakePacket), charFileManager.c
 * (ReadSkeltonFile, ReadCollisionFile: the two paths). */
typedef struct PObjMdl { /* field names derived */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    char modelPath[64];  /* 0x00, the model file, no C reader */
    char shadowPath[64]; /* 0x40, the shadow model file, no C reader */
    char path[48];       /* 0x80, the skeleton file, "NULL" for none */
    char collPath[64];   /* 0xB0, the collision file */
#ifdef VERSION_JUN26
    char clothName[32]; /* 0xF0, a cloth set ("NULL" for none), no C reader */
    char name110[32];   /* 0x110, "NULL" in every row, no C reader */
    float offset[3];    /* 0x130, InitPObj adds it to every vertex and box corner */
    float lightScale;   /* 0x13C, copied into the PObj at 0x34 */
    float ambientScale; /* 0x140, copied into the PObj at 0x38 */
    float shadowLength; /* 0x144, copied into the PObj at 0x3C */
#else
    float offset[3];    /* 0xF0, InitPObj adds it to every vertex and box corner */
    float lightScale;   /* 0xFC, copied into the PObj at 0x34 */
    float ambientScale; /* 0x100, copied into the PObj at 0x38 */
    float shadowLength; /* 0x104, copied into the PObj at 0x3C */
#endif
#else
    char path[48];      /* 0x00, the skeleton file, "NULL" for none */
    char collPath[64];  /* 0x30, the collision file */
    float offset[3];    /* 0x70, InitPObj adds it to every vertex and box corner */
    float lightScale;   /* 0x7C, copied into the PObj at 0x34 */
    float ambientScale; /* 0x80, copied into the PObj at 0x38 */
    float shadowLength; /* 0x84, copied into the PObj at 0x3C */
    /* 0x88, read as bits */
#endif
    unsigned int pktKind : 4; /* the packet header's kind, 4 for none */
    unsigned int shade : 4;   /* MakePacket's tag bits 18-21, the PObj's shade */
    unsigned int lod : 4;     /* MakePacket's tag bits 22-25, the PObj's level of detail */
    unsigned int : 20;
} PObjMdl; /* derived name */

/* the data-only members texture-path and model-path */
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
extern const TexRec texFile[];
#else
#ifdef VERSION_JUN26
extern const TexRec texFile[];
#else
extern TexRec texFile[];
#endif
#endif

extern PObjMdl modelData[];

#endif /* CHARFILEMANAGER_H */
