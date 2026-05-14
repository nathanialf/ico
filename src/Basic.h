#ifndef BASIC_H
#define BASIC_H

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

__attribute__((section(".rodata.0x0061A890"))) char D_0061A890[24] = "set partition first!\n";
__attribute__((section(".rodata.0x0061A8A8"))) char D_0061A8A8[24] = "src/Basic.c";

extern int   D_00633780;
extern int   D_00633784;
extern int   D_00632014;
extern int   D_00632024;
extern int   D_00633788[];
extern void  func_00139598(void *p);
extern void  func_001A6E28(char *p);
extern void  func_001AD768(char *buf, int sz);
extern void  func_00263FF0(char *buf, int sz, int *list);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_00139D78(int a0, int a1, char *a2, int a3);

#endif
