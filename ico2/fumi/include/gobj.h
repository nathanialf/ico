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

void add_gobj_to_head(char *g, int a1, int a2);
void add_gobj_to_tail(int a0, int a1, int a2);
void cut_gobj_link(int a0);
void isysGObjActiveLink(int bit, int set);
char *isysGObjAdd(char *owner, int a1, int a2);
void isysGObjAlloc(int n);
void *isysGObjGetExist_begin(void);
void *isysGObjGetExist_next(void *gobj);
void isysGObjInit(int n);
void isysGObjKindTableAdd(char *g, int kind);
void isysGObjKindTableRemove(char *g);
void isysGObjMoveAfterGObj(char *self, char *other);
void isysGObjRemove(char *g);
void isysGObjRemoveAll(void);
void *isysGObjSearchFromObjKindID_begin(int kind);
void *isysGObjSearchFromObjKindID_next(char *g);
void *isysGObjSearchFromObjLayoutID(int a0);
int isysGetNbAllocedGObjs(void);

#endif /* GOBJ_H */
