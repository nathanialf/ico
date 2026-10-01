/*
 * ico2/seki/include/DisplayP2O.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DisplayP2O.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DISPLAYP2O_H
#define DISPLAYP2O_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order DisplayP2O.c's inline tail has. */
void p2o_SetDefaultEnviroment(void);

#include "typedef.h"

/* The display's view of the model record ico2/common/src/PObj.c builds (its
 * PObj) and of the 0x180-byte part record the model's 0x40 points at (its
 * PObjSub).  Sub15C + 0x854 holds the object's model and + 0x858 the shadow
 * model.  A part keeps its vertices and normals, its polygon and strip lists,
 * its morph targets (reg_setShape adds them in by the object's weights), its
 * own matrix and two vertex buffers: RegistPacket.c keeps the rest pose in
 * them, Shadow.c the two caps of a shadow volume. */
typedef struct PObjPart { /* field names derived */
    char pad00[144];
    char *vtx;             /* 0x90 */
    unsigned int vtxCount; /* 0x94 */
    char pad98[8];
    char *nrm;             /* 0xA0 */
    unsigned int nrmCount; /* 0xA4 */
    char padA8[44];
    int shapeCount; /* 0xD4 */
    char padD8[12];
    int matCount; /* 0xE4 */
    char padE8[8];
    void *polys;            /* 0xF0 */
    unsigned int polyCount; /* 0xF4 */
    char padF8[8];
    void *strips;            /* 0x100 */
    unsigned int stripCount; /* 0x104 */
    char pad108[12];
    int lineCount; /* 0x114 */
    char pad118[8];
    char **morphs;           /* 0x120 */
    unsigned int morphCount; /* 0x124 */
    char pad128[8];
    float mtx[4][4]; /* 0x130 */
    char pad170[4];
    char *vtxSave; /* 0x174 */
    char *nrmSave; /* 0x178 */
    char pad17C[4];
} PObjPart;

typedef struct PObjModel { /* field names derived */
    char name[36];         /* 0x00 */
    int pad24;
    Sub15C *dobj; /* 0x28 */
    short pad2C;
    signed char partCount; /* 0x2E */
    signed char disp;      /* 0x2F */

    union {
        long long bits; /* bits 16 and 17 the display type, bit 26 the shadow off */

        struct {
            short id;
            short pad32;
            float lightScale; /* 0x34, scales the colours of the lights */
        } s;
    } mode; /* 0x30 */

    float ambientScale; /* 0x38 */
    float shadowLength; /* 0x3C */
    PObjPart *parts;    /* 0x40 */
    char *boxes;        /* 0x44, eight vectors a part */
    char *groups;       /* 0x48, 48 bytes a part */
    char pad4C[4];
    float box[8][4]; /* 0x50 */
} PObjModel;

void p2o_DispVU1(GObj *self);
void p2o_DispVU1DObj(void *req);
void p2o_DispVU1DObjMulti(void *req);
void p2o_DispVU1Default(GObj *self);
void p2o_DispVU1Multi(GObj *self);
void p2o_MakePacket(Sub15C *a0);
void p2o_TransMicroProgram(void);

#endif /* DISPLAYP2O_H */
