/*
 * ico2/fumi/include/way_tool.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what way_tool.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WAY_TOOL_H
#define WAY_TOOL_H

void ExtractWayData(int stage_no);
void cursor_control(volatile int a0);
int group_create(void);
int play_way(void);
int point_delete(void);
int point_insert(void);
int point_nige(void);
int quick_load_wpfile(void);
int quick_save_wpfile(void);
int wp_print_out(void);

#endif /* WAY_TOOL_H */
