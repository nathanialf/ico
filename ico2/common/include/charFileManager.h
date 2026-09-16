/*
 * ico2/common/include/charFileManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what charFileManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CHARFILEMANAGER_H
#define CHARFILEMANAGER_H

void CSVSYSTEM_ReadCharFiles(char *d, int id);
int GetPObjAddress(int obj);

#endif /* CHARFILEMANAGER_H */
