/*
 * ico2/sugipon/include/attackCheckBoundary.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what attackCheckBoundary.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ATTACKCHECKBOUNDARY_H
#define ATTACKCHECKBOUNDARY_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order attackCheckBoundary.c's inline tail has. */
int InitAttackCheckBoundaryGeo(int unused, void *obj);
void AttackCheckBoundaryGeo(void *a0);
void AttackCheckBoundaryDL(struct GObj *obj);
void actAttackCheckBoundaryStart(struct GObj *self);
float GetAttackCheckBoundaryRadius(struct GObj *a0);
char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r);
int GetAttackCheckBoundaryManagerStatus(struct GObj *a0);
void SetAttackCheckBoundaryAttribute(char *a0, int a1);

/* RECONSTRUCTION: the attribute word of a cloth layout record has a type of
   its own. The ROM's schedule of InitAttackCheckBoundaryManagerGeo loads
   rec->attr (line 61) above the roster store `mgr->list[i].obj = g` (line
   214), while that store must still precede the first sub-object chase
   (line 62) and the attribute store must force the second chase (line 218)
   to reload; with the roster handle and both chases int (the engine's
   int-handle reading, GOBJ_SUB), only an attribute load outside int's alias
   set is free to rise (the compiler's sched2 dump gives int set 2 and this
   enum its own set). Only the type is attested: the table holds 96 and 128
   here and the developers' enumerator names are not recoverable. */
typedef enum { CLOTH_ATTR_NONE = 0 } ClothAttr;

/* RECONSTRUCTION: one record of layoutClothDef (MAIN.MAP line 6655, member
   layout-cloth-def.o, .rodata; the retail table is 36 records, 0xEA0 bytes).
   The name string and the four corner points are the table's own bytes; this
   TU reads the first two corners, the attribute and the boundary count, and
   InitFlagGeo reads the rest. The generated layout-cloth-def member compiles
   against this record. */
typedef struct {    /* field names derived */
    char name[32];  /* 0x00 */
    float pt[4][3]; /* 0x20 */
    int kind;       /* 0x50, the cloth type in the low four bits (InitFlagGeo's switch) */
    ClothAttr attr; /* 0x54 */
    int rows;       /* 0x58, the cloth's rows (ClothCfg num) */
    int count;      /* 0x5C, the columns, and the boundaries a manager lays out */
    float length;   /* 0x60, the cloth's length, shared out over the columns */
    float weight;   /* 0x64, the fall added to each point a step (ClothCfg weight) */
} LayoutClothDef; /* derived name */

extern const LayoutClothDef layoutClothDef[];

#endif /* ATTACKCHECKBOUNDARY_H */
