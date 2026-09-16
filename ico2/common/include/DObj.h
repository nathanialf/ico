/*
 * ico2/common/include/DObj.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DObj.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DOBJ_H
#define DOBJ_H

extern char *CSVSYSTEM_InitDObj(int id, float *lay);
extern void LinkParentOfDObj(void *gobj, void *info);
extern void UnlinkParentOfDObj(void *a0);
extern void initPolygonState(char *d, float *lay);

#endif /* DOBJ_H */
