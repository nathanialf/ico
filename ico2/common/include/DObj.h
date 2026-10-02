/*
 * ico2/common/include/DObj.h
 *
 * The declarations of what DObj.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DOBJ_H
#define DOBJ_H

#include "sceneManager.h"

struct Sub15C;
struct ObjNode;

/* DObj.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void FreeDObj(void);
void LinkParentOfDObj(void *obj, struct ObjNode *link);
void UnlinkParentOfDObj(void *obj);
struct Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay);

#endif /* DOBJ_H */
