/* Vendor SCE library run, attribution INFERRED: libscf.a.  Neither disc map names an
 * archive for these 21 functions (MAIN.MAP is an older link whose .text ends before
 * them; SRCFILE.TXT carries them with symbols but no source paths).  The sceScf
 * family is the public SDK's libscf, GetRomName and IsT10K feed
 * sceScfSetT10kConfig, and the BCD date helpers feed sceScfGetGMTfromRTC and
 * sceScfGetLocalTimefromRTC, so the run is treated as one library.  VMA
 * 0x272878..0x273228. */
#include "common.h"

INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", GetRomName);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", IsT10K);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetLanguage);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfSetT10kConfig);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetAspect);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetSpdif);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetTimeZone);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetDateNotation);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetSummerTime);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetTimeNotation);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", tobcd);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", frombcd);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", convertfrombcd);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", converttobcd);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", adddate);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", subdate);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", addhour);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", subhour);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", AdjustTime);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetGMTfromRTC);
INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfGetLocalTimefromRTC);
