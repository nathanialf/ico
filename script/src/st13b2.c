#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", actSt13b2Generator);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226C80);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226D50);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226E70);

void func_00226EE8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x74); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_00226F90(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x64); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void func_00227038(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_002270D8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227178);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002271F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227268);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002272F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002273A0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227748);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227860);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227960);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227A68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227D58);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227DC0);
