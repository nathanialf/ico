/*
 * ico2/common/include/haveParentSimpleObj.h
 *
 * The declarations of what haveParentSimpleObj.c.inc defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef HAVEPARENTSIMPLEOBJ_H
#define HAVEPARENTSIMPLEOBJ_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order haveParentSimpleObj.c's inline tail has. */
int InitParentSimpleObjGeo(void);

#endif /* HAVEPARENTSIMPLEOBJ_H */
