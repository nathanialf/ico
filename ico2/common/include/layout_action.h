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

/* layout_action.o's globals (MAIN.MAP): the frame count main keeps from a
   stage's start (the game loop's start button needs 11), the boot flag, the
   pause enable, the title demo toggle, the game loop's pause-request count,
   the stage the title demo leaves to (main stores -2 after a movie, e3 95,
   la_game_demo -1 to 1) and the flag boyact sets from the boy's pad that the
   pause-request count follows. */
extern int startStagePauseDisableTimer;
extern int layout_boot_flag;
extern int enable_game_pause;
extern int title_demo_mode;
extern int laoutActionPauseRequest;
extern unsigned int stage_after_skipping_demo;
extern int layoutActPushStartNew;
/* mc, the memory-card request block (MAIN.MAP global), is declared by each
   user in its own view of the block: common/src/debug.c's McReq record,
   layout_action.c's word array. */

void _la_mask_preview_info(void);
int _la_mcard_error_check(void *a0);
int _la_set_current_port_2(void *p, int a1);
int _la_set_current_port_lock_2(void *p, int a1);
void _la_set_preview_info();

/* The layout actions the texture layout's tables call, in the order the ROM
   emits them: each is an `inline` definition that gcc defers to the end of
   the object and outputs in first-declaration order, so this list is that
   order (the PAL listing places the definitions at their own lines). */
int la_boot_memory_card_check(void);
int la_boot_no_memory_card(int a0, int a1);
int la_boot_no_free_area(int a0, int a1);
int la_boot_confirm_memory_card(void);
int la_scei_logo(int a0);
int la_title_demo(void);
int la_mc_preview_info(void);
int la_mc_current_slot(void);
int la_mc_load_current_slot_select(void);
int la_mc_save_current_slot_select(void);
int la_general_mc_confirm(void);
int la_save_confirm_no_memory_card(int a0);
int la_save_confirm_no_free_area(int a0);
int la_format_processing(int a0);
int la_save_confirm_complete(int a0, int a1);
int la_save_confirm_fail(void);
int la_format_confirm_fail(void);
int la_delete_start_check(int a0);
int la_delete_confirm(int a0, int a1);
int la_delete_confirm_complete(void);
int la_delete_confirm_fail(void);
int la_game_loading(int a0);
void la_playtime_count(void);
int la_game_demo(int a0);
int la_game_demo_pause(int a0);
int la_game_pause(int a0);
int la_switching_stage(void);
int la_save_confirm_yesno(void);

#endif /* LAYOUT_ACTION_H */
