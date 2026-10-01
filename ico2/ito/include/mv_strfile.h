/*
 * ico2/ito/include/mv_strfile.h
 *
 * The declarations of what mv_strfile.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_STRFILE_H
#define MV_STRFILE_H

int strFileClose(char *self);
int strFileOpen(char *self, char *name);
int strFileRead(char *self, void *buf, int n, int *eof);

#endif /* MV_STRFILE_H */
