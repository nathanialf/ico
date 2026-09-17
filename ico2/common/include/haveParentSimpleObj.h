/*
 * ico2/common/include/haveParentSimpleObj.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what haveParentSimpleObj.c.inc defines, in the order the
 * coalescing TU's prototype block carried them; every type here is read from
 * the ROM's calling convention at the call sites.
 */

#ifndef HAVEPARENTSIMPLEOBJ_H
#define HAVEPARENTSIMPLEOBJ_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order haveParentSimpleObj.c's inline tail has. */
int InitParentSimpleObjGeo(void);

#endif /* HAVEPARENTSIMPLEOBJ_H */
