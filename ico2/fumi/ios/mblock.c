#include "memory.h"
#include "mblock.h"
#include <string.h>
#include "ios.h"

/* the free node list */
MBlockNode *free_mblock_list = 0;

inline void init_mblock(MBlock *mb)
{
    mb->head = 0;
    mb->total = 0;
}

static MBlockNode *new_mblock_node(unsigned int size)
{
    MBlockNode *node;

    if (size > 8192) {
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
            node = iosMallocDebug(ios_partition_inflate, 8192, "ios/mblock.c", 32);
            if (node == 0) {
                return 0;
            }
            node->buf = iosMallocDebug(ios_partition_inflate, 8192, "ios/mblock.c", 34);
            if (node->buf == 0) {
                iosFree(node);
                return 0;
            }
            node->size = 8192;
        } else {
            node = free_mblock_list;
            free_mblock_list = node->next;
        }
    }
    node->used = 0;
    node->next = 0;
    return node;
}

static inline int enough_space(MBlock *mb, unsigned int size) /* derived name */
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

static void reuse_mblock1(MBlockNode *node)
{
    if (node->size <= 8192) {
        MBlockNode *tmp = free_mblock_list;
        free_mblock_list = node;
        node->next = tmp;
        return;
    }
    iosFree(node->buf);
}

inline void reuse_mblock(MBlock *mb)
{
    MBlockNode *node = mb->head;
    if (node != 0) {
        do {
            MBlockNode *next = node->next;
            reuse_mblock1(node);
            node = next;
        } while (node != 0);
        init_mblock(mb);
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
