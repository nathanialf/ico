#ifndef ISYS_GOBJ_PROCESS_H
#define ISYS_GOBJ_PROCESS_H

#include "matching.h"
#include "regpin.h"

__attribute__((section(".rodata.0x00557AD0"))) const char D_00557AD0[24] = "isys/gobj_process.c";

__attribute__((section(".rodata.0x00557AE8"))) const char D_00557AE8[40] = "isys:not enough memory for GObj\n";
__attribute__((section(".rodata.0x00557B10"))) const char D_00557B10[16] = "id %d %x %x \n";
__attribute__((section(".rodata.0x00557B20"))) const char D_00557B20[40] = "isys:not enough memory for GObjProcess\n";
__attribute__((section(".rodata.0x00557B48"))) const char D_00557B48[24] = "isys:null GObjProcess\n";

extern int   D_00632008;
extern int   D_00633CA8;
extern int   D_00633CAC;
extern int   func_0013A0F8(int a0, int a1, char *file, int line);

#endif
