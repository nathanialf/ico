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

/* texture-path: one texture file, 0x20 bytes. Readers: kanban.c,
 * layout_texture.c. Owner: ico2/common/include/charFileManager.h. */
typedef struct {   /* field names derived */
    char path[32]; /* 0x00 */
} TexRec;          /* derived name */

/* model-path: one model, 0x14C bytes, indexed by the model id. Reader:
 * ico2/common/src/PObj.c (InitPObj, AllocPObj, MakePacket), charFileManager.c
 * (ReadSkeltonFile, ReadCollisionFile: the skeleton and collision paths). */
typedef struct PObjMdl { /* field names derived */
    char modelPath[64];  /* 0x00, derived name: the model file, no C reader */
    char shadowPath[64]; /* 0x40, derived name: the shadow model file, no C reader */
    char path[48];       /* 0x80, the skeleton file, "NULL" for none */
    char collPath[64];   /* 0xB0, the collision file */
    char clothName[32];  /* 0xF0, derived name: a cloth set ("NULL" for none), no C reader */
    char name110[32];    /* 0x110, derived name: "NULL" in every row, no C reader */
    float offset[3];     /* 0x130, InitPObj adds it to every vertex and box corner */
    float lightScale;    /* 0x13C, copied into the PObj at 0x34 */
    float ambientScale;  /* 0x140, copied into the PObj at 0x38 */
    float shadowLength;  /* 0x144, copied into the PObj at 0x3C */
    /* 0x148, read as bits */
    unsigned int pktKind : 4; /* the packet header's kind, 4 for none */
    unsigned int shade : 4;   /* MakePacket's tag bits 18-21, the PObj's shade */
    unsigned int lod : 4;     /* MakePacket's tag bits 22-25, the PObj's level of detail */
    unsigned int : 20;
} PObjMdl; /* derived name */

/* the data-only members texture-path and model-path */
extern const TexRec texFile[];
extern PObjMdl modelData[];

#endif /* CHARFILEMANAGER_H */
