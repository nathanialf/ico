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

extern void add_gobj_to_head(char *g, int a1, int a2);
extern void add_gobj_to_tail(int a0, int a1, int a2);
extern void cut_gobj_link(int a0);
extern void isysGObjActiveLink(int bit, int set);
extern char *isysGObjAdd(char *owner, int a1, int a2);
extern void isysGObjAlloc(int n);
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *gobj);
extern void isysGObjInit(int n);
extern void isysGObjKindTableAdd(char *g, int kind);
extern void isysGObjKindTableRemove(char *g);
extern void isysGObjMoveAfterGObj(char *self, char *other);
extern void isysGObjRemove(char *g);
extern void isysGObjRemoveAll(void);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(char *g);
extern void *isysGObjSearchFromObjLayoutID(int a0);
extern int isysGetNbAllocedGObjs(void);

#endif /* GOBJ_H */
