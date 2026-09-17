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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order layout_texture.c's inline tail has. */
void lt_switch_layout(int no);
int lt_current_property_item(void);
int lt_link_layout(int dir);
int lt_prev_layout(int stage);
int lt_next_layout(int stage);
void lt_mask_property(int idx, int flag);
void lt_default_mask_property(int idx, int flag);
int lt_fade_status(void);
void lt_set_item_select_func(int val);
void lt_set_fade_mode(int val);

void default_item_select(int no);
void display_primary_texture_layout(int no, int sel);
void display_texture_fade_cancel_chk(int from, int to);
void lt_analog2Pad(void);

#endif /* LAYOUT_TEXTURE_H */
