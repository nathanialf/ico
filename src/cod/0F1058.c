extern int D_00633708;

struct Slot {
    int pad[4];
    int self_ptr;
    int pad2[1];
};
extern struct Slot D_0070D4D8[];

int func_001F1058(volatile int *self)
{
    int slot = D_00633708;
    D_0070D4D8[slot].self_ptr = (int)self;
    ((int *)self[0x57])[0x11C] = slot;
    ((int *)self[0x57])[0x13C] = 0;
    ((int *)self[0x57])[0x13B] = 0;
    ((int *)self[0x57])[0x154] = 0;
    D_00633708 = slot + 1;
    return slot;
}
