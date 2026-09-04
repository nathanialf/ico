#include "common.h"

extern int D_004C3850[];

int enemy_Initialize(void) {
    int idx = D_004C3850[0];
    int sub = D_004C3850[4] + 0xFFF80000;
    return ((&D_004C3850[idx])[1] - sub) >> 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", enemy_GetPositionTable);

extern char D_0062BB18[8];
extern int D_0070A850[];

int func_001F8BF0(int idx, int sub_idx)
{
    register int factor;
    if (idx < 0 || idx >= *(int *)D_0062BB18) return 0;
    factor = 0x6C;
    return *(int *)((char *)D_0070A850 + idx * factor + sub_idx * 4);
}

typedef struct EnNode { char pad[0x34]; struct EnNode *prev; struct EnNode *next; } EnNode;
extern EnNode *D_0062A4D4;
extern EnNode *D_0062A4D8;
extern char D_00613790[];
extern void debug_StdPrintfDummy();

void func_001F8C30(EnNode *node) {
    if (node == 0) { debug_StdPrintfDummy(D_00613790); return; }
    if (node->next) goto L60;
    if (node->prev == 0) goto L7C;
    goto L68;
L60:
    node->next->prev = node->prev;
L68:
    if (node->prev == 0) goto L7C;
    node->prev->next = node->next;
L7C:
    if (node == D_0062A4D4) D_0062A4D4 = node->prev;
    if (node == D_0062A4D8) D_0062A4D8 = node->next;
}

void func_001F8CA8(EnNode *node) {
    func_001F8C30(node);
}
