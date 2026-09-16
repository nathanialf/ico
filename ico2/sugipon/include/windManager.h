/*
 * ico2/sugipon/include/windManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what windManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WINDMANAGER_H
#define WINDMANAGER_H

float GetRegularizedWindSpeed(void *pos);
void ReinitWindManager(void);
void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h);

#endif /* WINDMANAGER_H */
