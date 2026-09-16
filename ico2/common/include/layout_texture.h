/*
 * ico2/common/include/layout_texture.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what layout_texture.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LAYOUT_TEXTURE_H
#define LAYOUT_TEXTURE_H

void default_item_select(int no);
void display_primary_texture_layout(int no, int sel);
void display_texture_fade_cancel_chk(int from, int to);
void lt_analog2Pad(void);
int lt_current_property_item(void);
int lt_fade_status(void);
int lt_link_layout(int dir);
void lt_set_item_select_func(int val);
void lt_switch_layout(int no);

#endif /* LAYOUT_TEXTURE_H */
