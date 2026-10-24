/* charFileName.h -- the character-file id table's bound.
 *
 * charFileManager.c prints a message naming "commmon/include/charFileName.h"
 * and asking for MAX_CHARS to be raised whenever a character id reaches the
 * table's bound.
 */
#ifndef CHARFILENAME_H
#define CHARFILENAME_H

#if defined(VERSION_JPN) || defined(VERSION_KOR)
#define MAX_CHARS 1621
#else
#ifdef VERSION_NTSC
#define MAX_CHARS 1582
#else
#ifdef VERSION_AUG6
#define MAX_CHARS 1576
#else
#ifdef VERSION_JUN26
#define MAX_CHARS 1500 /* InitCharFileManager clears 30000 bytes of 20-byte entries */
/* the rows of the model-path table (modelData) ReadSkeltonFile and
   ReadCollisionFile search; the name is the one ReadSkeltonFile's
   "Too Many ModelDataID_NUMBER exists." message gives it */
#define ModelDataID_NUMBER 1474
#else
#define MAX_CHARS 1637
#endif
#endif
#endif
#endif

#endif
