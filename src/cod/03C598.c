struct Node {
    char pad[0x30];
    struct Node *prev;
    struct Node *next;
};

void func_0013C598(struct Node **head, struct Node *new_node) {
    struct Node *old = *head;
    new_node->prev = (struct Node *)0;
    new_node->next = old;
    if (old != (struct Node *)0) {
        old->prev = new_node;
    }
    *head = new_node;
}
