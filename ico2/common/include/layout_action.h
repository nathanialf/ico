/*
 * ico2/common/include/layout_action.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what layout_action.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LAYOUT_ACTION_H
#define LAYOUT_ACTION_H

void _la_mask_preview_info(void);
int _la_mcard_error_check(void *a0);
int _la_set_current_port_2(void *p, int a1);
int _la_set_current_port_lock_2(void *p, int a1);
void _la_set_preview_info();
void la_playtime_count(void);

#endif /* LAYOUT_ACTION_H */
