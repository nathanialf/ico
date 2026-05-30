#include "matching.h"

struct D275 {
    char pad[0xEC];
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
};
extern struct D275 D_00275120;

void func_001EF9A8(float f12, float f13, int a0)
{
    D_00275120.field_EC = (int)f12;
    D_00275120.field_F0 = (int)f13;
    D_00275120.field_F8 = a0;
}
