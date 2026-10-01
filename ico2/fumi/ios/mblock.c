#include "memory.h"
#include "mblock.h"
#include <string.h>
#include "ios.h"

/* .sdata, owned by mblock.o: the free node list (MAIN.MAP global) */
int free_mblock_list = 0;

extern MBlockNode *new_mblock_node(unsigned int size);

inline void init_mblock(int *a0)
{
    a0[0] = 0;
    a0[1] = 0;
}

/* listing lines 16-51 */
MBlockNode *new_mblock_node(unsigned int size)
{
    MBlockNode *node;

    if (size > 0x2000) {
        node = iosMallocDebug(ios_partition_inflate, sizeof(MBlockNode), "ios/mblock.c", 21);
        if (node == 0) {
            return 0;
        }
        node->buf = iosMallocDebug(ios_partition_inflate, size, "ios/mblock.c", 23);
        if (node->buf == 0) {
            iosFree(node);
            return 0;
        }
        node->size = size;
    } else {
        if (free_mblock_list == 0) {
            node = iosMallocDebug(ios_partition_inflate, 0x2000, "ios/mblock.c", 32);
            if (node == 0) {
                return 0;
            }
            node->buf = iosMallocDebug(ios_partition_inflate, 0x2000, "ios/mblock.c", 34);
            if (node->buf == 0) {
                iosFree(node);
                return 0;
            }
            node->size = 0x2000;
        } else {
            node = (MBlockNode *)free_mblock_list;
            free_mblock_list = (int)node->next;
        }
    }
    node->used = 0;
    node->next = 0;
    return node;
}

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
        int tmp = free_mblock_list;
        free_mblock_list = (int)a0;
        a0[3] = tmp;
        return;
    }
    return iosFree(*a0);
}

inline void reuse_mblock(int *a0)
{
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
