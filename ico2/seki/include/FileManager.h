/*
 * ico2/seki/include/FileManager.h
 *
 * The declarations of what FileManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

void file_Init(void);
int file_LoadFile(void **adr, char *fname, int area);

#endif /* FILEMANAGER_H */
