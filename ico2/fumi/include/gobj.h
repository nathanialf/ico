/*
 * ico2/fumi/include/gobj.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gobj.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJ_H
#define GOBJ_H

struct GObj;

/* gobj.c's functions in the order the ROM emits them: gcc 2.9 writes the
   out-of-line copies of the file's plain-inline functions in first-declaration
   order, and these are their first declarations.  The functions that hand an
   object back return it as the untyped handle every caller takes. */
void isysGObjKindTableInit(void);
void isysGObjInit(int n);
void cut_gobj_link(struct GObj *p);
void isysGObjRemoveAll(void);
void add_gobj_to_tail(struct GObj *g, int a1, int a2);
void add_gobj_to_head(struct GObj *g, int a1, int a2);
void isysGObjMove(struct GObj *g, unsigned char a1, int a2);
void isysGObjMoveHead(struct GObj *g, unsigned char a1, int a2);
void *isysGObjAddAfterGObj(void (*fn)(struct GObj *), struct GObj *other);
void *isysGObjAddBeforeGObj(void (*fn)(struct GObj *), struct GObj *other);
int isysGetNbAllocedGObjs(void);
void isysGObjAlloc(int n);
void isysGObjRemove(struct GObj *g);
void isysGObjKindTableAdd(struct GObj *g, int kind);
void isysGObjKindTableRemove(struct GObj *g);
void isysGObjMoveAfterGObj(struct GObj *self, struct GObj *other);
void isysGObjMoveBeforeGObj(struct GObj *self, struct GObj *other);
void *isysGObjAdd(void (*fn)(struct GObj *), int a1, int a2);
void *isysGObjAddHead(void (*fn)(struct GObj *), int a1, int a2);
void *isysGObjSearchFromObjLayoutID(int a0);
void *isysGObjSearchFromObjKindID_begin(int kind);
void *isysGObjSearchFromObjKindID_next(struct GObj *g);
void *isysGObjSearchFromLabelTypeID(int a0);
void *isysGObjGetExist_begin(void);
void *isysGObjGetExist_next(struct GObj *start);
void isysGObjActiveLink(int bit, int set);
void isysGObjActiveDlLink(int a0, int a1);
extern int debugKindOld;

#endif /* GOBJ_H */
