/* charFileName.h -- the character-file id table's bound.
 *
 * Provenance: the retail ELF bakes the message at D_00619370 (.rodata,
 * VMA 0x00619370, rom offset 0x519370), which reads
 * "commmon/include/charFileName.h" followed by EUC-JP text asking the reader
 * to raise MAX_CHARS.  The path is hand typed into that message, three m's
 * and all: it is not a __FILE__ expansion, so it fixes the header's name and
 * its directory (common/include) but says nothing about the -I spelling the
 * compiler saw.  charFileManager.c prints it whenever a character id reaches
 * the table's bound, and the three sites that do compare against 1637, which
 * is therefore MAX_CHARS.
 *
 * baserom/pal/SRCFILE.TXT carries no rows for this file, so nothing else in
 * it is recoverable: a header that emits no instructions leaves no rows.  Only
 * the bound is written here.
 */
#ifndef CHARFILENAME_H
#define CHARFILENAME_H

#define MAX_CHARS 1637

#endif
