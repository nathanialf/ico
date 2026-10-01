/*
 * ico2/fumi/include/mcdata.h
 *
 * The declarations of what mcdata.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MCDATA_H
#define MCDATA_H

struct McMgr;

int iosMcIconWriteIconsys(struct McMgr *self, int *p);
int iosMcIconWriteIcon(struct McMgr *self, int *p);

#endif /* MCDATA_H */
