#include "common.h"
#include "r5900.h"
#include "vu0.h"

extern int D_0062BEA0;

void MakeBoundingBox(void) {
    D_0062BEA0 = 0;
}

int MakePacket(void) {
    return D_0062BEA0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", AllocPObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", InitPObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", FreePObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D3C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D7F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D910);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DDC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DF20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DF40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E008);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E048);

extern int D_0054A960[];

void *func_0023E158(void) {
    return D_0054A960;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E168);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E500);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E6E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E7D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EA68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EAC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EE78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EFE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F490);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FB20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FBE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FC08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FCD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FDD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE50);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FED0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FF18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FFA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FFC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FFF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240008);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240038);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240050);

void func_00240080(void *a0, void *a1) {
    QCOPY16_NO_NOP("$a2");
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240090);

void func_002400B8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400C8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400D8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400E8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002400F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240198);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240240);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002402E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240390);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002403E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240408);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002404B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240578);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002405E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002406E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002408D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240918);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240938);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240980);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002409C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240A28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240AB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240B18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240B50);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240B78);

extern int D_0054A9F8_alias[] __asm__("D_0054A9F8");

int func_00240C58(int a0) {
    int old = D_0054A9F8_alias[0];
    D_0054A9F8_alias[0] = a0;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240C68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240E40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240E78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240EA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240F78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241060);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241148);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241210);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241300);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002413F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002414B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241588);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002415A8);

void func_002415C8(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

int func_002415D8(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002415E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241640);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241698);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002416F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241778);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241790);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002418B8);

extern int D_0054AA90[];
extern void func_00242078(int a0);

void func_002418E0(int a0) {
    D_0054AA90[0] = 0;
    func_00242078(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002418F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241930);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241990);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241A10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241A88);

int func_00241AB0(void) {
    return -1;
}

int func_00241AB8(void) {
    return -1;
}

int func_00241AC0(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241AC8);

int func_00241B78(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241B80);

int func_00241B98(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241BA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241BC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241BF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241C40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241C80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241CC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241E58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242078);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242138);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002422D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242300);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002423A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002423C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002423F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002424F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002426A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002426F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002427A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002428E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242978);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242B68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242C40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242D10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242DA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242E38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242E90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002430F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243180);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002431F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002435A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002435F8);

extern int D_0054AB24[];
extern void func_00100540(int a0);

void func_00243628(void) {
    func_00100540(D_0054AB24[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243638);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002437D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002438A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243B28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244150);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244760);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244938);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244AE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244B00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244CB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244CD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244F40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245060);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245080);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245288);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002453E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245580);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002457C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002459B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002459D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245B68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246608);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246690);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246700);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246778);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002469F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246A30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246EA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246EC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246FE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247008);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247200);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247330);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002473A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002474B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247548);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247608);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247650);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002476A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002476F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247880);

/* func_00247908 — hand-written PS2 EE syscall stub: syscall number in $v1,
 * then `syscall 0`. .set noreorder keeps the bare nop in the jr delay slot. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247908\n"
    "    addiu      $3, $0, 0x74\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247908\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247918);

/* func_00247968 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247968\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247968\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247978 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247978\n"
    "    addiu      $3, $0, -0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247978\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247988 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247988\n"
    "    addiu      $3, $0, 0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247988\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247998 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247998\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247998\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479A8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479A8\n"
    "    addiu      $3, $0, 0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479A8\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002479B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002479C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002479D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002479E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247A00);

void func_00247D80(int *a0, int *a1) {
    a1[2] = a0[4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247D90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247DA8);

extern int D_00710DD8[];

void *func_00247DC8(void) {
    return D_00710DD8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248090);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002480A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002480C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002480F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248118);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248250);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002482D0);

/* Hand-written EE assembly (NOT a C-match target) — a cache / INTC
 * critical-section module:
 *   func_002483F8  DCache hit-writeback-invalidate loop (cache 0x18 / sync).
 *   func_002484A4  + func_002484AC are ONE routine splat over-split: the ISR.
 *                  Its real entry is func_002484A4 + 0x4 (the addiu $sp,-0x10),
 *                  which func_002484D0 installs via %hi/%lo(func_002484A4 + 0x4);
 *                  the body ends with `ei` (enable interrupts, COP0).
 *   func_002484D0  installs that ISR and toggles INTC enable.
 * `ei`, `cache`, and the address-of-instruction callback cannot be emitted by
 * ee-gcc. func_002484A4 is short enough to author inline below; the rest stay
 * as assembled .s (byte-identical via INCLUDE_ASM). */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002483F8);

/* func_002484A4 — hand-written: bare-return entry whose delay slot doubles as
 * the prologue (addiu $sp,-0x10) of the ISR installed at func_002484A4+0x4.
 * .set noreorder keeps the addiu in the jr delay slot as written. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002484A4\n"
    "    jr         $31\n"
    "    addiu      $29, $29, -0x10\n"
    "endlabel func_002484A4\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002484AC);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002484D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248538);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248590);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248630);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002487C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248900);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248980);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002489F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248A30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248BB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002490C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249160);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002491D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249340);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249620);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249818);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002498E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249AC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249CB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249D48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249DE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249E10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249E48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249FD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A078);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A0C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A228);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A498);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A538);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A5B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A7A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A858);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A8B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A908);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A988);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AA00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AA38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AAA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AAF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AB28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AC48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AD68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AEA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AF58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B010);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B1A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B250);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B2B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B308);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B360);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B430);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B498);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B500);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B5D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B788);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B7B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B930);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BA68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BAA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BB58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BC30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BCC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BDE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BF60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BFD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C0B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C108);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C3E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C470);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C5C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C7B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CA40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CBA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CC70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CD88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CE10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D010);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D300);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D418);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D5D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DC00);

int func_0024DE40(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DE48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DEC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DF10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DF60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DF78);

int func_0024DF98(int **a0) {
    return a0[0x10][0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DFA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DFB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E060);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E088);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E0D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E100);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E118);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E128);

int func_0024E140(int **a0) {
    return a0[0x10][0x33];
}

int func_0024E150(int **a0) {
    return a0[0x10][0x34];
}

void *func_0024E160(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_0024E170(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E180);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E190);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E1A8);

void func_0024E1C0(int *a0) {
    a0[3] = a0[2];
}

void func_0024E1D0(int *a0) {
    a0[2] = a0[3];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E1E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E248);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E3E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E510);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E6C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E730);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E740);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E7C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E818);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E8E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E8F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E920);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E978);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EA50);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EA70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EBC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EF10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F0B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F220);

extern void func_0024E920(void *a0);
extern int D_00628F38[];

void func_0024F2C0(void) {
    func_0024E920(D_00628F38);
}

extern int D_00628F68[];
extern int D_00628F80[];
extern int D_00628FB8[];

void func_0024F2D0(void) {
    func_0024E920(D_00628F68);
}

void func_0024F2E0(void) {
    func_0024E920(D_00628F80);
}

void func_0024F2F0(void) {
    func_0024E920(D_00628FB8);
}

extern void func_00254A88(void *a0);
extern void func_00254B70(void *a0);

void func_0024F300(int **a0) {
    func_00254A88((char *)a0[0x10] + 0x4C);
}

void func_0024F310(int **a0) {
    func_00254B70((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024FD08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250128);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002502B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250330);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002503C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250480);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250600);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002506B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002507B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002508B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250A08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250AF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250BD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250D88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250EB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250FC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251088);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002510B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251298);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002512B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251678);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002517A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002519A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251A70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251F98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002521A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002522E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002523B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252468);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252620);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252758);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002529D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252A40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252AB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252BD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252D58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252F88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002530A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253188);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253238);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002533D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002534B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253570);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253950);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002539F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253EC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254088);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002542B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254478);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002547A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002547E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254800);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254898);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002548E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254930);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254988);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002549B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254A20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254A88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254B70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254CC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254D90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254FC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254FE0);

extern int D_00715CC0[];

void *func_00254FF8(void) {
    return D_00715CC0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255008);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255038);

extern int D_00717F80[];
extern int D_00718180[];
extern int D_00717F40[];

void *func_00255050(void) {
    return D_00717F80;
}

void *func_00255060(void) {
    return D_00718180;
}

int func_00255070(void) {
    return D_00717F40[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255080);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002550A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255580);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255618);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255A38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002565E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002567C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256960);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256A98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256CD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256E18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256F20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256FF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257190);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002572F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257380);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257570);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002576E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002579F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257C10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257DE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258168);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002581F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258490);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258650);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258900);

extern void func_00258688(int a0);

void func_00258948(void) {
    func_00258688(0);
}

void func_00258950(void) {
    func_00258688(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002589C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002589F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258A10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258A40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258A68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258AF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258B88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258BF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258CF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258E50);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258FB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259040);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259070);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259088);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002590A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002590B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002590E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259108);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259208);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002592C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259350);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002593F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259668);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259710);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259740);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002597C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259B80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259CB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259D58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259E68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A040);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A080);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A0B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A140);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A180);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A208);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A280);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A2E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A340);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A3B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A3E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A450);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A490);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A4A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A528);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A578);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A5C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A610);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A678);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A768);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025AA90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025ABD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B3A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B8D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BCB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BDF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BF48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025C898);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025C9A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025C9C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CC70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CC90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CD78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CDA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D038);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D8D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025DF38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025DF98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025E568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EAA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EBD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EC78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EEB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EF10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EF78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F388);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F4A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F5A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F640);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F6E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F718);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F7A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F8B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F940);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FB78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FBD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FC38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FE30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FF90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002600A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002600F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002601B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260240);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002602D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260340);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260380);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002603B8);

extern int D_0054D504[];

int func_002603E0(void) {
    return D_0054D504[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002603F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260424);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002604B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260628);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260668);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002606B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002610E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002610F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261188);

int func_002611F8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261200);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261288);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002613B4);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002614F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026160C);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261900);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261AC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261B10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261B80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261E80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261F00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261FB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264520);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265130);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265188);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265298);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002652B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002652D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002654F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002666C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002667C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266890);

extern void func_002666C0(void);
extern void func_002673A8(int a0, void *a1);

void func_00266970(int a0) {
    func_002673A8(a0, func_002666C0);
}

void func_00266980(void) {
    func_00266970(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266990);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266A20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266B40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266E60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266FD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002673A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267440);

extern int D_0062A818[];

void *func_002674C8(void) {
    return D_0062A818;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002674D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267508);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267530);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002678D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268050);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026808C);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026816C);

void func_00268270(void) {
}

void func_00268278(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268280);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268470);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002685B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268640);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268700);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268738);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268A68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268E70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268FF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269230);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002692A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002692C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269480);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002694B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269518);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269588);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269618);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269708);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002697C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002697E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269818);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269840);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002698C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002698E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269950);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002699D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269A38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269A58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026A958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026A988);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026A9B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026ABD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AC08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026ACF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AEE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AFA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B0B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B118);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B730);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B7B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B7C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B8F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B908);
