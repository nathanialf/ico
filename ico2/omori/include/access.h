/*
 * ico2/omori/include/access.h
 *
 * The declarations of what access.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACCESS_H
#define ACCESS_H

/* the data file path of a stage (-1 for the common data), packed or not */
char *GetDataFileName(int no, int isDF);
char *GetDataFileName2(const char *name, int isDF);

#endif /* ACCESS_H */
