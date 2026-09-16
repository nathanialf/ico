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

extern void ExtractWayData(int stage_no);
extern void cursor_control(volatile int a0);
extern int group_create(void);
extern int play_way(void);
extern int point_delete(void);
extern int point_insert(void);
extern int point_nige(void);
extern int quick_load_wpfile(void);
extern int quick_save_wpfile(void);
extern int wp_print_out(void);

#endif /* WAY_TOOL_H */
