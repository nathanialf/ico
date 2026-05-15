#ifndef ATTACKHIT_H
#define ATTACKHIT_H

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

/* sdata */
__attribute__((section(".sdata.0x00632DBC"))) int D_00632DBC = 0;

/* ASCII rodata */
__attribute__((section(".rodata.0x0055A4B0"))) const char D_0055A4B0[16] = "flag ok\n";
__attribute__((section(".rodata.0x0055A4C0"))) const char D_0055A4C0[16] = "group ok\n";
__attribute__((section(".rodata.0x0055A4D0"))) const char D_0055A4D0[16] = "invincible ok\n";
__attribute__((section(".rodata.0x0055A4E0"))) const char D_0055A4E0[16] = "geometry ok\n";
__attribute__((section(".rodata.0x0055A4F0"))) const char D_0055A4F0[16] = "id equal error\n";
__attribute__((section(".rodata.0x0055A500"))) const char D_0055A500[24] = "mail send ok [%d]\n";
__attribute__((section(".rodata.0x0055A518"))) const char D_0055A518[16] = "src/attackhit.c";
__attribute__((section(".rodata.0x0055A528"))) const char D_0055A528[16] = "gop!=NULL";
__attribute__((section(".rodata.0x0055A538"))) const char D_0055A538[48] = "brainStatusDefaultSet: brain target area over\n";

/* EUC-JP: "ブレインレベルのオーバーライドに失敗しました\n" */
__attribute__((section(".rodata.0x0055A568"))) const char D_0055A568[48] = "\245\326\245\354\245\244\245\363\245\354\245\331\245\353\244\316\245\252\241\274\245\320\241\274\245\351\245\244\245\311\244\313\274\272\307\324\244\267\244\336\244\267\244\277\n";

/* Int / float / double rodata */
__attribute__((section(".rodata.0x0055A3F0"))) unsigned int D_0055A3F0[28] = {
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
__attribute__((section(".rodata.0x0055A460"))) unsigned int D_0055A460[20] = {
    0x00000001, 0x00000000, 0x00000004, 0x00000001,
    0x0000002E, 0x00000001, 0x00000035, 0x00000001,
    0x00000034, 0x00000001, 0x00000034, 0x00000001,
    0x0000003D, 0x00000001, 0x00000002, 0x00000003,
    0x0000003E, 0x00000001, 0xFFFFFFFF, 0x00000000,
};
__attribute__((section(".rodata.0x0055A598"))) const double D_0055A598 = 1.9;
__attribute__((section(".rodata.0x0055A5A0"))) const double D_0055A5A0 = 0.002;
__attribute__((section(".rodata.0x0055A5A8"))) const float D_0055A5A8[2] = { 89128.96f, 0.955f };
__attribute__((section(".rodata.0x0055A5B0"))) const double D_0055A5B0[2] = { 1.9, 0.0 };

/* Cross-TU symbols referenced from this TU */
extern void func_00180F40(int *buf, int self, int arg);
extern void func_001A6E28(const char *msg);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);

/* Intra-TU forward decls (defined via INCLUDE_ASM or below) */
void func_00181960(int *buf);
void func_00181BB8(void);
void func_00181BC0(void);
void func_00181BC8(int a0);

#endif
