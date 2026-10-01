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

/* The functions way_tool.c defines `inline`, in the order its end-of-file block
 * emits their out-of-line copies: gcc 2.9 defers a plain-inline definition to
 * the end of the object and writes the copies in first-declaration order, so
 * this block is read from the ROM. */
int play_way(void);
int point_nige(void);
int quick_save_wpfile(void);
void cursor_control(volatile int a0);

void ExtractWayData(int stage_no);
int group_create(void);
int point_delete(void);
int point_insert(void);
int quick_load_wpfile(void);
int wp_print_out(void);

int debug_WayTool(void);

#endif /* WAY_TOOL_H */
