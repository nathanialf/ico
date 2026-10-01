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

/* layout_texture.o's .sdata globals: current_layout_id and
   lt_item_select_disable (MAIN.MAP), and the continue screen's decided flag */
extern int lt_continue_selected;
extern int current_layout_id;
extern int lt_item_select_disable;
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
void exec_layout_texture(void);
void init_layout_texture(int stage);

/* texture-layout: one texture layout, 0x38 bytes. Readers:
 * ico2/common/src/layout_texture.c (LtProp), kanban.c (KanbanProp),
 * kanbanBoot.c, layout_action.c. Owner: ico2/common/include/layout_texture.h. */
typedef struct {       /* field names derived */
    int first;         /* 0x00, the first tex-property row */
    int last;          /* 0x04 */
    float fadeInTime;  /* 0x08, seconds the layout fades in over, 0 for at once */
    float fadeOutTime; /* 0x0C, seconds it fades out over */
    float colR;        /* 0x10, the backdrop sprite colour, 0 to 1 */
    float colG;        /* 0x14 */
    float colB;        /* 0x18 */
    float colA;        /* 0x1C */
    void (*proc)();    /* 0x20, the selection handler, called with the select flag and item */
    int word24;        /* 0x24 */
    int defaultItem;   /* 0x28, copied into curItem */
    int curItem;       /* 0x2C */
    int link;          /* 0x30, the next layout, -1 for none */
    int word34;        /* 0x34 */
} LtProp;              /* derived name */

#endif /* LAYOUT_TEXTURE_H */
