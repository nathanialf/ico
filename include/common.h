#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"

/* JTEXT(s): identity marker for Japanese string literals.
 *
 * Use when a `const char[]` contains Japanese (or other non-ASCII)
 * text written as `\xNN` hex escapes preserving the original
 * codepage bytes. ICO uses EUC-JP for in-game text; other PS2
 * titles use Shift-JIS. The macro is a no-op identity — its call
 * site is grep-able and signals that the developer ran
 * tools/decode_sjis.py to confirm the string's meaning before
 * committing the bytes as typed source.
 *
 * Example (ICO, EUC-JP encoded):
 *     const char D_X[24] = JTEXT("Light:NULL\xa4\xcb\xa4\xca\xa4\xc3"
 *                                "\xa4\xc6\xa4\xf3\xa4\xc7\n");
 *     // decoded: "Light:NULLになってんで\n"
 */
#ifndef JTEXT
#define JTEXT(s) s
#endif

#endif /* COMMON_H */
