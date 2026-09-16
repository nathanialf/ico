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

extern void default_item_select(int no);
extern void display_primary_texture_layout(int no, int sel);
extern void display_texture_fade_cancel_chk(int from, int to);
extern void lt_analog2Pad(void);
extern int lt_current_property_item(void);
extern int lt_fade_status(void);
extern int lt_link_layout(int dir);
extern void lt_set_item_select_func(int val);
extern void lt_switch_layout(int no);

#endif /* LAYOUT_TEXTURE_H */
