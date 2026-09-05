#include "common.h"

extern int D_0063A470;
extern void iosFree();
typedef struct MBlockNode {
    char *buf;
    unsigned int size;
    unsigned int used;
    struct MBlockNode *next;
} MBlockNode;
typedef struct MBlock {
    MBlockNode *head;
    unsigned int total;
} MBlock;
extern MBlockNode *new_mblock_node(unsigned int size);
extern int strlen(const char *s);
extern void memcpy(void *dst, const void *src, unsigned int n);
/* prototypes: their order is the inline tail's emission order */
void init_mblock(int *a0);
void *new_segment(MBlock *mb, unsigned int len);
void reuse_mblock(int *a0);
char *strdup_mblock(MBlock *mb, const char *str);
inline void init_mblock(int *a0) {
    a0[0] = 0;
    a0[1] = 0;
}
INCLUDE_ASM("asm/nonmatchings/ios/mblock", new_mblock_node);

/* listing lines 55-66 */
static inline int enough_space(MBlock *mb, unsigned int size)
{
    MBlockNode *node = mb->head;
    unsigned int end;

    if (node == 0)
        return 0;

    end = node->used + size;

    if (end < node->used)
        return 0;

    return end <= node->size;
}
inline void *new_segment(MBlock *mb, unsigned int len)
{
    MBlockNode *node;
    char *p;
    unsigned int size;

    size = (len + 7) & ~7;

    if (!enough_space(mb, size)) {
        node = new_mblock_node(size);
        node->next = mb->head;
        mb->head = node;
        mb->total += node->size;
    } else {
        node = mb->head;
    }
    p = node->buf + node->used;
    node->used += size;
    return p;
}
void reuse_mblock1(int *a0)
{
    if ((unsigned int)a0[1] < 0x2001) {
        int tmp = D_0063A470;
        D_0063A470 = (int)a0;
        a0[3] = tmp;
        return;
    }
    return iosFree(*a0);
}
inline void reuse_mblock(int *a0) {
    int *node = (int *)a0[0];
    if (node != 0) {
        do {
            int *next = (int *)node[3];
            reuse_mblock1(node);
            node = next;
        } while (node != 0);
        init_mblock(a0);
    }
}
inline char *strdup_mblock(MBlock *mb, const char *str)
{
    int len;
    char *p;

    len = strlen(str) + 1;
    p = (char *)new_segment(mb, len);
    memcpy(p, str, len);
    return p;
}
