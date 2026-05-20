/* debug.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern char D_00631A20[48];
extern char D_00631A50[16];
extern char D_00631A60[16];
extern char D_00631A70[48];
extern char D_00631AA0[16];
extern char D_006328C0[8];
extern const char D_006328C8[8];
extern const char D_006328D0[8];
extern const char D_006328D8[8];
extern const char D_006328E0[8];
extern const char D_006328E8[8];
extern const char D_006328F0[8];
extern const char D_006328F8[];
extern const char D_00632900[8];
extern const char D_00632908[8];
extern const char D_00632910[8];
extern const char D_00632918[8];
extern const char D_00632920[8];
extern const char D_00632928[8];
extern const char D_00632930[8];
extern const char D_00632938[8];
extern const char D_00632940[8];
extern const char D_00632948[8];
extern const char D_00632950[8];
extern const char D_00632958[8];
extern const char D_00632960[8];
extern const char D_00632968[8];
extern const char D_00632970[8];
extern const char D_00632978[8];
extern const char D_00632980[8];
extern const char D_00632988[8];
extern const char D_00632990[8];
extern const char D_00632998[8];
extern const char D_006329A0[8];
extern const char D_006329A8[8];
extern const char D_006329B0[8];
extern const char D_006329B8[8];
extern const char D_006329C0[8];
extern const char D_006329C8[8];
extern const char D_006329D0[8];
extern const char D_006329D8[8];
extern unsigned int D_006329E0;
extern const char D_006329F8[];
extern const char D_00632A00[];
extern unsigned int D_00632A0C;
extern const char D_00632A10[8];
extern const char D_00632A18[8];
extern unsigned int D_00632A20;
extern unsigned int D_00632A24;
extern int D_00632A28;
extern int D_00632A2C;
extern unsigned int D_00632A30;
extern int D_00632C90;
extern int D_00632C94;
extern int D_00632C98;
extern int D_00632CB4;
extern int D_00632CB8;
extern int D_00632CC0;
extern int D_00632CC4;
extern int D_00632CCC;
extern int D_00632CD0;
extern int D_00632CD8;
extern int D_00632CDC;
extern int D_00632CE4;
extern int D_00632CE8;
extern int D_00632CF0;
extern int D_00632CF4;
extern int D_00632CFC;
extern int D_00632D00;
extern int D_00632D0C;
extern int D_00632D10;
extern int D_00632D18;
extern int D_00632D1C;
extern int D_00632D20;
extern int D_00632D24;
extern int D_00632D30;
extern int D_00632D34;
extern int D_00632D38;
extern int D_00632D3C;
extern int D_00632D40;
extern int D_00632D44;
extern int D_00632D5C;
extern int D_00632D60;
extern int D_00632D64;
extern int D_00632D6C;
extern int D_00632D70;
extern int D_00632D74;
extern int D_00632D78;
extern int D_00632D7C;
extern int D_00632D88;
extern int D_00632D90;
extern int D_00632D98;
extern int D_00632D9C;
extern int D_00632DA0;
extern int D_00632DA4;
extern int D_00632DA8;
extern int D_00632DAC;
extern int D_00632DB8;

__attribute__((section(".data.0x004B3B10"))) const char D_004B3B10[24] = "08/18/01 22:22:20";
__attribute__((section(".rodata.0x00553730"))) const char D_00553730[8] = "0.%d";
__attribute__((section(".rodata.0x00553738"))) const char D_00553738[8] = "e+%d";
__attribute__((section(".rodata.0x00553740"))) const char D_00553740[8] = "e%d";
__attribute__((section(".rodata.0x00614330"))) const char D_00614330[24] = " IGNORE DODGE       ";
__attribute__((section(".rodata.0x00614348"))) const char D_00614348[24] = " ONE HIT ONLY       ";
__attribute__((section(".rodata.0x00614360"))) const char D_00614360[24] = " LWSKYOMI LOOKONLY  ";
__attribute__((section(".rodata.0x00614378"))) const char D_00614378[24] = " GIRL DETOUR        ";
__attribute__((section(".rodata.0x00614390"))) const char D_00614390[24] = " DISP ESCORT BALL   ";
__attribute__((section(".rodata.0x006143A8"))) const char D_006143A8[24] = " ENEMY FLY WITH GIRL";
__attribute__((section(".rodata.0x006143C0"))) const char D_006143C0[24] = " ENEMY BATTLE TYPE  ";
__attribute__((section(".rodata.0x006143D8"))) const char D_006143D8[24] = " DISP ENEMY STATE   ";
__attribute__((section(".rodata.0x006143F0"))) const char D_006143F0[24] = " CHAIN SLOW  SPEED  ";
__attribute__((section(".rodata.0x00614408"))) const char D_00614408[24] = " CHAIN CYCLE SPEED  ";
__attribute__((section(".rodata.0x00614420"))) const char D_00614420[24] = " NEW QUEEN BATTLE   ";
__attribute__((section(".rodata.0x00614438"))) const char D_00614438[24] = " DEBUG SUB THREAD   ";
__attribute__((section(".rodata.0x00614450"))) const char D_00614450[24] = " STICK SIMULATE     ";
__attribute__((section(".rodata.0x00614468"))) const char D_00614468[24] = " STICK INPUT        ";
__attribute__((section(".rodata.0x00614480"))) const char D_00614480[24] = " DISPLAY BRIGHTNESS ";
__attribute__((section(".rodata.0x00614498"))) const char D_00614498[24] = " DispMesh           ";
__attribute__((section(".rodata.0x006144B0"))) const char D_006144B0[24] = " DispParticle       ";
__attribute__((section(".rodata.0x006144C8"))) const char D_006144C8[24] = " DispLwsModel       ";
__attribute__((section(".rodata.0x006144E0"))) const char D_006144E0[24] = " DispNormalModel    ";
__attribute__((section(".rodata.0x006144F8"))) const char D_006144F8[24] = " DispClusterModel   ";
__attribute__((section(".rodata.0x00614510"))) const char D_00614510[24] = " FullScreenEffect   ";
__attribute__((section(".rodata.0x00614528"))) const char D_00614528[24] = " Scissoring         ";
__attribute__((section(".rodata.0x00614540"))) const char D_00614540[24] = " ShadowOff          ";
__attribute__((section(".rodata.0x00614558"))) const char D_00614558[24] = " LightVolume        ";
__attribute__((section(".rodata.0x00614570"))) const char D_00614570[24] = " Specular           ";
__attribute__((section(".rodata.0x00614588"))) const char D_00614588[24] = " Bounding           ";
__attribute__((section(".rodata.0x006145A0"))) const char D_006145A0[24] = " RippleRoughness    ";
__attribute__((section(".rodata.0x006145B8"))) const char D_006145B8[24] = " Camera             ";
__attribute__((section(".rodata.0x006145D0"))) const char D_006145D0[24] = " Jimaku Test        ";
__attribute__((section(".rodata.0x006145E8"))) const char D_006145E8[24] = " SnapForm           ";
__attribute__((section(".rodata.0x00614600"))) const char D_00614600[24] = " SnapSize           ";
__attribute__((section(".rodata.0x00614618"))) const char D_00614618[24] = " SnapShotNum        ";
__attribute__((section(".rodata.0x00614630"))) const char D_00614630[24] = " WayTool            ";
__attribute__((section(".rodata.0x00614648"))) const char D_00614648[24] = " GBrainInfo         ";
__attribute__((section(".rodata.0x00614660"))) const char D_00614660[24] = " BrainOnOff         ";
__attribute__((section(".rodata.0x00614678"))) const char D_00614678[24] = " BrainBar           ";
__attribute__((section(".rodata.0x00614690"))) const char D_00614690[24] = " Fly Limit Info     ";
__attribute__((section(".rodata.0x006146A8"))) const char D_006146A8[24] = " MotionSlopeInterp  ";
__attribute__((section(".rodata.0x006146C0"))) const char D_006146C0[24] = " MotionDebugTgt     ";
__attribute__((section(".rodata.0x006146D8"))) const char D_006146D8[24] = " MotionDebugWin     ";
__attribute__((section(".rodata.0x006146F0"))) const char D_006146F0[24] = " MotionInterporate  ";
__attribute__((section(".rodata.0x00614708"))) const char D_00614708[24] = " MotionActNode      ";
__attribute__((section(".rodata.0x00614720"))) const char D_00614720[24] = " CharaTarget        ";
__attribute__((section(".rodata.0x00614738"))) const char D_00614738[24] = " FaceWInterpRatio   ";
__attribute__((section(".rodata.0x00614750"))) const char D_00614750[24] = " ClothInfo          ";
__attribute__((section(".rodata.0x00614768"))) const char D_00614768[24] = " Skelton            ";
__attribute__((section(".rodata.0x00614780"))) const char D_00614780[24] = " CollisionOldProc   ";
__attribute__((section(".rodata.0x00614798"))) const char D_00614798[24] = " CollisionRayDisp   ";
__attribute__((section(".rodata.0x006147B0"))) const char D_006147B0[24] = " FieldCollision     ";
__attribute__((section(".rodata.0x006147C8"))) const char D_006147C8[24] = " WallHitColDisp     ";
__attribute__((section(".rodata.0x006147E0"))) const char D_006147E0[24] = " WallCheck          ";
__attribute__((section(".rodata.0x006147F8"))) const char D_006147F8[24] = " SE SLOT DISP       ";
__attribute__((section(".rodata.0x00614810"))) const char D_00614810[24] = " ADPCM PLAY         ";
__attribute__((section(".rodata.0x00614828"))) const char D_00614828[24] = " DebugMemoryBar     ";
__attribute__((section(".rodata.0x00614840"))) const char D_00614840[24] = " DebugBarScale      ";
__attribute__((section(".rodata.0x00614858"))) const char D_00614858[24] = " DebugBarStartItem  ";
__attribute__((section(".rodata.0x00614870"))) const char D_00614870[24] = " DebugBarProfileType";
__attribute__((section(".rodata.0x00614888"))) const char D_00614888[24] = " DebugBar           ";
__attribute__((section(".rodata.0x006148A0"))) const char D_006148A0[24] = " KIND ROUTINE OLD   ";
__attribute__((section(".rodata.0x006148B8"))) const char D_006148B8[24] = " WireString         ";
__attribute__((section(".rodata.0x006148D0"))) const char D_006148D0[24] = " MemPartition       ";
__attribute__((section(".rodata.0x006148E8"))) const char D_006148E8[24] = " Printf             ";
__attribute__((section(".rodata.0x00614900"))) const char D_00614900[24] = " DebugFont3         ";
__attribute__((section(".rodata.0x00614918"))) const char D_00614918[24] = " DebugFont2         ";
__attribute__((section(".rodata.0x00614930"))) const char D_00614930[24] = " DebugFont          ";
__attribute__((section(".rodata.0x00614948"))) const char D_00614948[24] = " DebugFrameStep     ";
__attribute__((section(".rodata.0x00614960"))) const char D_00614960[24] = " IgnoreDemoCamera   ";
__attribute__((section(".rodata.0x00614978"))) const char D_00614978[24] = " NTSC/PAL           ";
__attribute__((section(".rodata.0x00614990"))) const char D_00614990[24] = " FrameStep          ";
__attribute__((section(".rodata.0x00614A50"))) const char D_00614A50[24] = "thisIsYourStartStage";
__attribute__((section(".rodata.0x00614B58"))) const char D_00614B58[24] = "thisIsYourDebugOption";
__attribute__((section(".rodata.0x00614D40"))) const char D_00614D40[16] = "ico2Data/%s";
__attribute__((section(".rodata.0x00614F60"))) const char D_00614F60[40] = "A:%p W:%1.2f%% W~%1.2f%% W_:%1.2f%%";
__attribute__((section(".rodata.0x00614F88"))) const char D_00614F88[16] = "C%03d G%03d F%d";
__attribute__((section(".rodata.0x00614F98"))) const char D_00614F98[24] = "P%d S%d A%d(%d) T%d(%d)";
__attribute__((section(".rodata.0x00614FC0"))) const char D_00614FC0[24] = "snapshot/snap%07d.tm2";
__attribute__((section(".rodata.0x00614FD8"))) const char D_00614FD8[24] = "snapshot/snap%07d.bmp";
__attribute__((section(".rodata.0x00615060"))) const char D_00615060[24] = "(addr 0x%08x <fl>) : ";
__attribute__((section(".rodata.0x00615078"))) const char D_00615078[24] = "(addr 0x%08x <%2d>) : ";
__attribute__((section(".rodata.0x00615178"))) const char D_00615178[16] = "DEBUG MODE";
__attribute__((section(".rodata.0x006151A8"))) const char D_006151A8[16] = "%c%s : %s(%d)";
__attribute__((section(".rodata.0x006151B8"))) const char D_006151B8[16] = "%c%s : %d";
__attribute__((section(".rodata.0x00615238"))) const char D_00615238[16] = "stage select";
__attribute__((section(".rodata.0x00615248"))) const char D_00615248[16] = "%s? Yes:O No:X";
__attribute__((section(".rodata.0x00615258"))) const char D_00615258[16] = "now formatting";
__attribute__((section(".rodata.0x00615268"))) const char D_00615268[16] = "Unformat";
__attribute__((section(".rodata.0x00615278"))) const char D_00615278[24] = "now unformatting";
__attribute__((section(".rodata.0x00615290"))) const char D_00615290[48] = "not insert memory card or unformatted %d";
__attribute__((section(".rodata.0x006152C0"))) const char D_006152C0[24] = "%s file not found";
__attribute__((section(".rodata.0x006152D8"))) const char D_006152D8[24] = "%s Directory not found";
__attribute__((section(".rodata.0x006152F0"))) const char D_006152F0[48] = "segID %d check sum err rom:%d != load:%d";
__attribute__((section(".rodata.0x00615320"))) const char D_00615320[32] = "%s handler func ret err code";
__attribute__((section(".rodata.0x00615340"))) const char D_00615340[16] = "memory over";
__attribute__((section(".rodata.0x00615350"))) const char D_00615350[32] = "memory card another err %d";
__attribute__((section(".rodata.0x006153C8"))) const char D_006153C8[24] = "FILE LIST";
__attribute__((section(".rodata.0x00615440"))) const char D_00615440[16] = "SAVE NO.";
__attribute__((section(".rodata.0x006154C8"))) const char D_006154C8[24] = "DATA NOT FOUND";
__attribute__((section(".rodata.0x00615670"))) const char D_00615670[16] = "delete %s file";
__attribute__((section(".rodata.0x00615680"))) const char D_00615680[16] = "delete %s";
__attribute__((section(".rodata.0x006156A8"))) const char D_006156A8[16] = "UNFORMAT";
__attribute__((section(".rodata.0x006156E8"))) const char D_006156E8[16] = "Formatted";
__attribute__((section(".rodata.0x006156F8"))) const char D_006156F8[16] = "Unformatted";
__attribute__((section(".rodata.0x00615730"))) const char D_00615730[40] = "Memory card port 0: %s free:%d Kbytes";
__attribute__((section(".rodata.0x00615770"))) const char D_00615770[16] = "ADPCM LIST";
__attribute__((section(".rodata.0x00615780"))) const char D_00615780[16] = "%3s %6x %6x %s";
__attribute__((section(".rodata.0x00615790"))) const char D_00615790[24] = "CD LOAD INFO COMMON";
__attribute__((section(".rodata.0x006157A8"))) const char D_006157A8[24] = "CD LOAD INFO STAGE";
__attribute__((section(".rodata.0x006157C0"))) const char D_006157C0[24] = "CHARACTER DEBUG INFO";
__attribute__((section(".rodata.0x006157D8"))) const char D_006157D8[24] = "CHARACTER PAD2 CONTROL";
__attribute__((section(".rodata.0x00615810"))) const char D_00615810[32] = "[%s] %4d %4d %4d";
__attribute__((section(".rodata.0x00615880"))) const char D_00615880[16] = "move dst";
__attribute__((section(".rodata.0x00615890"))) const char D_00615890[16] = "move src";
__attribute__((section(".rodata.0x006158A0"))) const char D_006158A0[16] = "move all";
__attribute__((section(".rodata.0x006158B0"))) const char D_006158B0[16] = "Collision Test";
__attribute__((section(".rodata.0x006158C0"))) const char D_006158C0[16] = "HIT: %p,%d";
__attribute__((section(".rodata.0x006158D0"))) const char D_006158D0[16] = "ATTR: %x";
__attribute__((section(".rodata.0x006158E0"))) const char D_006158E0[16] = "SRC: %f, %f, %f";
__attribute__((section(".rodata.0x006158F0"))) const char D_006158F0[16] = "DST: %f, %f, %f";
__attribute__((section(".rodata.0x00615900"))) const char D_00615900[24] = "Tsuresari Time Zero";
__attribute__((section(".rodata.0x00615918"))) const char D_00615918[16] = "DispBall";
__attribute__((section(".rodata.0x00615928"))) const char D_00615928[16] = "Pad2 Control";
__attribute__((section(".rodata.0x00615938"))) const char D_00615938[16] = "Chara Info";
__attribute__((section(".rodata.0x00615948"))) const char D_00615948[16] = "LoadINFO";
__attribute__((section(".rodata.0x00615958"))) const char D_00615958[16] = "BackStage Test";
__attribute__((section(".rodata.0x00615968"))) const char D_00615968[16] = "Ending Demo";
__attribute__((section(".rodata.0x00615978"))) const char D_00615978[16] = "Game Over";
__attribute__((section(".rodata.0x00615988"))) const char D_00615988[16] = "REVERB TEST";
__attribute__((section(".rodata.0x00615998"))) const char D_00615998[16] = "ADPCM TEST";
__attribute__((section(".rodata.0x006159A8"))) const char D_006159A8[16] = "STAFF ROLL TEST";
__attribute__((section(".rodata.0x006159B8"))) const char D_006159B8[16] = "Memory Card";
__attribute__((section(".rodata.0x006159C8"))) const char D_006159C8[16] = "Snap Shot";
__attribute__((section(".rodata.0x006159D8"))) const char D_006159D8[16] = "TextureList";
__attribute__((section(".rodata.0x006159E8"))) const char D_006159E8[16] = "Effect Tool";
__attribute__((section(".rodata.0x006159F8"))) const char D_006159F8[16] = "Motion Viewer";
__attribute__((section(".rodata.0x00615A08"))) const char D_00615A08[16] = "Camera Editor";
__attribute__((section(".rodata.0x00615A18"))) const char D_00615A18[16] = "Way Test";
__attribute__((section(".rodata.0x00615A28"))) const char D_00615A28[16] = "Stage Setting";
__attribute__((section(".rodata.0x00615A38"))) const char D_00615A38[16] = "Target Object";
__attribute__((section(".rodata.0x00615A48"))) const char D_00615A48[16] = "Stage Select";
__attribute__((section(".rodata.0x00615A58"))) const char D_00615A58[16] = "Free Camera";
__attribute__((section(".rodata.0x00615A68"))) const char D_00615A68[16] = "Debug Mode";
__attribute__((section(".rodata.0x00615A78"))) const char D_00615A78[40] = "A553/A580/B2432 THROUGH FLOOR @ SLOPE";
__attribute__((section(".rodata.0x00615AA0"))) const char D_00615AA0[32] = "B2421   FLARE CLAMP FAIL";
__attribute__((section(".rodata.0x00615AC0"))) const char D_00615AC0[24] = "B2373   ENEMY FAIL FLY";
__attribute__((section(".rodata.0x00615AD8"))) const char D_00615AD8[24] = "B1897   SPIDER ALIVE";
__attribute__((section(".rodata.0x00615AF0"))) const char D_00615AF0[16] = "DISC VER.%s %s";
__attribute__((section(".rodata.0x00615B00"))) const char D_00615B00[16] = "Aug 20 2001";
__attribute__((section(".rodata.0x00615B10"))) const char D_00615B10[16] = "22:01:44";
__attribute__((section(".rodata.0x00615B20"))) const char D_00615B20[24] = "FIXED BUG ID LIST";
__attribute__((section(".rodata.0x00615B38"))) const char D_00615B38[16] = "DEBUG MENU";
__attribute__((section(".rodata.0x00615B48"))) const char D_00615B48[24] = "cdrom0:\\";
__attribute__((section(".rodata.0x00616360"))) const char D_00616360[16] = "TRAP exception";
__attribute__((section(".rodata.0x00616370"))) const char D_00616370[32] = "ARITHMETIC OVERFLOW exception";
__attribute__((section(".rodata.0x00616390"))) const char D_00616390[32] = "COPROCESSOR UNUSABLE exception";
__attribute__((section(".rodata.0x006163B0"))) const char D_006163B0[32] = "RESERVE OPERATION exception";
__attribute__((section(".rodata.0x006163D0"))) const char D_006163D0[40] = "BUS ERROR exception LOAD OR STORE";
__attribute__((section(".rodata.0x006163F8"))) const char D_006163F8[32] = "BUS ERROR exception OPERATION";
__attribute__((section(".rodata.0x00616418"))) const char D_00616418[32] = "ADDRESS ERROR exception STORE";
__attribute__((section(".rodata.0x00616438"))) const char D_00616438[48] = "ADDRESS ERROR exception LOAD or OPERATION";
__attribute__((section(".rodata.0x00616468"))) const char D_00616468[32] = "TLB NOT MATCH exception STORE";
__attribute__((section(".rodata.0x00616488"))) const char D_00616488[48] = "TLB NOT MATCH exception LOAD or OPERATION";
__attribute__((section(".rodata.0x006164B8"))) const char D_006164B8[24] = "TLB MOD exception";
__attribute__((section(".rodata.0x00616510"))) const char D_00616510[16] = "TRTABLE.BIN";
__attribute__((section(".rodata.0x006165D8"))) const char D_006165D8[16] = "TRFILE.TXT";
__attribute__((section(".rodata.0x00616698"))) const char D_00616698[16] = "SRCFILE.TXT";
__attribute__((section(".rodata.0x00616880"))) const char D_00616880[16] = "object target";
__attribute__((section(".rodata.0x00616890"))) const char D_00616890[16] = "GObj address:%p";
__attribute__((section(".rodata.0x006168A0"))) const char D_006168A0[48] = "gamesysObjInfoEmptyAreaSearch not area found";

/* String rodata migrated from debug_data.c */
__attribute__((section(".rodata.0x00614A10"))) const char D_00614A10[64] = "==== Save start stage =======================================\n";
__attribute__((section(".rodata.0x00614A68"))) const char D_00614A68[56] = "debug_SaveStartStageFile: host file open error.\n";
__attribute__((section(".rodata.0x00614AD8"))) const char D_00614AD8[64] = "=============================================================\n";
__attribute__((section(".rodata.0x00614B18"))) const char D_00614B18[64] = "==== Save Debug Option ======================================\n";
__attribute__((section(".rodata.0x00614B70"))) const char D_00614B70[56] = "debug_SaveDebugOptionFile: host file open error.\n";
__attribute__((section(".rodata.0x00614BA8"))) const char D_00614BA8[32] = "Save Debug Option file.\n";
__attribute__((section(".rodata.0x00614BC8"))) const char D_00614BC8[64] = "==== Try to read Debug Option file. =========================\n";
__attribute__((section(".rodata.0x00614C08"))) const char D_00614C08[64] = "debug_GetDebugOption:No Debug Option file. Setting to default.\n";
__attribute__((section(".rodata.0x00614CC0"))) const char D_00614CC0[64] = "debug_GetDebugOption:Found Debug Option file, But illegal.\n";
__attribute__((section(".rodata.0x00614D00"))) const char D_00614D00[32] = "Found Debug Option file.\n";
__attribute__((section(".rodata.0x00614D20"))) const char D_00614D20[16] = "%s => %d\n";
__attribute__((section(".rodata.0x00614D50"))) const char D_00614D50[24] = "file is not exist(%s)\n";
__attribute__((section(".rodata.0x00614DA8"))) const char D_00614DA8[32] = " to seki area.(%2.1f%%)\n";
__attribute__((section(".rodata.0x00614DC8"))) const char D_00614DC8[40] = " to sugi area.(%2.1f%%/%2.1f%%)\n";
__attribute__((section(".rodata.0x00614DF0"))) const char D_00614DF0[48] = " to static object area.(%2.1f%%/%2.1f%%)\n";
__attribute__((section(".rodata.0x00614E20"))) const char D_00614E20[48] = " to static motion area.(%2.1f%%/%2.1f%%)\n";
__attribute__((section(".rodata.0x00614E50"))) const char D_00614E50[48] = " to dynamic motion area.(%2.1f%%/%2.1f%%)\n";
__attribute__((section(".rodata.0x00614E80"))) const char D_00614E80[32] = " to hara-area.(%2.1f%%)\n";
__attribute__((section(".rodata.0x00614EA0"))) const char D_00614EA0[32] = " to oomori area.(%2.1f%%)\n";
__attribute__((section(".rodata.0x00614EC0"))) const char D_00614EC0[24] = " to horagai-area.\n";
__attribute__((section(".rodata.0x00614ED8"))) const char D_00614ED8[24] = " to sound-area.\n";
__attribute__((section(".rodata.0x00614EF0"))) const char D_00614EF0[32] = " to sound_semi-area.\n";
__attribute__((section(".rodata.0x00614FB0"))) const char D_00614FB0[16] = "Snapx4:%d:%p\n";
__attribute__((section(".rodata.0x00614FF0"))) const char D_00614FF0[48] = "debug_SnapShot:host file open error.(%s:%d)\n";
__attribute__((section(".rodata.0x00615020"))) const char D_00615020[40] = "debug_SnapShot:host file close error.\n";
__attribute__((section(".rodata.0x00615048"))) const char D_00615048[24] = "%p (%p %p %p %p)\n";
__attribute__((section(".rodata.0x006150D8"))) const char D_006150D8[24] = "debug_PrintFontf error\n";
__attribute__((section(".rodata.0x006150F0"))) const char D_006150F0[16] = "%f %f %f %f\n";
__attribute__((section(".rodata.0x00615100"))) const char D_00615100[24] = "VF%02d:%f %f %f %f\n";
__attribute__((section(".rodata.0x00615118"))) const char D_00615118[24] = "VF%02d:%8x %8x %8x %8x\n";
__attribute__((section(".rodata.0x00615130"))) const char D_00615130[32] = "VI%02d:%08x %08x %08x %08x\n";
__attribute__((section(".rodata.0x00615150"))) const char D_00615150[32] = "VS%02d:%08x %08x %08x %08x\n";
__attribute__((section(".rodata.0x006151C8"))) const char D_006151C8[16] = "debug%s => %s\n";
__attribute__((section(".rodata.0x006151D8"))) const char D_006151D8[16] = "debug%s => %d\n";
__attribute__((section(".rodata.0x006151E8"))) const char D_006151E8[64] = "debug_SelectCsvWindowVal: func return string length over\n";
__attribute__((section(".rodata.0x00615228"))) const char D_00615228[16] = "stage:%d\n";
__attribute__((section(".rodata.0x006153B8"))) const char D_006153B8[16] = "%s %d bytes\n";
__attribute__((section(".rodata.0x00615758"))) const char D_00615758[24] = "REVERB DEPTH %d%%\n";
__attribute__((section(".rodata.0x006157F0"))) const char D_006157F0[16] = ">>%8s = %d\n";
__attribute__((section(".rodata.0x00615800"))) const char D_00615800[16] = "  %8s = %d\n";
__attribute__((section(".rodata.0x00616568"))) const char D_00616568[40] = "No information.(\"%s\" can't read.)\n";
__attribute__((section(".rodata.0x00616620"))) const char D_00616620[24] = "%08x:%010d:%04x:%04x\n";
__attribute__((section(".rodata.0x00616638"))) const char D_00616638[40] = "%x:source Offset %d stack:%d ra:%d\n";
__attribute__((section(".rodata.0x00616660"))) const char D_00616660[16] = "0x%x: %s\n";
__attribute__((section(".rodata.0x00616670"))) const char D_00616670[40] = "%s:%08x %s:%08x %s:%08x %s:%08x \n";
__attribute__((section(".rodata.0x006166D8"))) const char D_006166D8[24] = "print phase: %d\n";
__attribute__((section(".rodata.0x006166F0"))) const char D_006166F0[40] = "IOS Reports Critical Error Message.\n";
__attribute__((section(".rodata.0x00616718"))) const char D_00616718[24] = "  PC:%p BVA:%p BPA:%p\n";
__attribute__((section(".rodata.0x00616730"))) const char D_00616730[40] = "stack:%p stackSize:%d raOffset:%d\n";
__attribute__((section(".rodata.0x00616758"))) const char D_00616758[32] = "%s=%8.8x_%8.8x_%8.8x_%8.8x\n";
__attribute__((section(".rodata.0x00616778"))) const char D_00616778[24] = "called exception\n";
__attribute__((section(".rodata.0x00616790"))) const char D_00616790[24] = "%s  (code = %d)\n";
__attribute__((section(".rodata.0x006167A8"))) const char D_006167A8[16] = "CAUSE %p\n";
__attribute__((section(".rodata.0x006167B8"))) const char D_006167B8[24] = "Frame buffer: %d\n";
__attribute__((section(".rodata.0x006167D0"))) const char D_006167D0[16] = "IOP DEAD\n";
__attribute__((section(".rodata.0x00616818"))) const char D_00616818[48] = "----------------------------------------------\n";
__attribute__((section(".rodata.0x006168D0"))) const char D_006168D0[40] = "gamesys: gamesysObjInfoPosSet:%d - %d \n";
__attribute__((section(".rodata.0x006168F8"))) const char D_006168F8[24] = "write size %d\n";

/* Float rodata migrated from debug_data.c */
__attribute__((section(".rodata.0x00614D30"))) const float D_00614D30[4] = { 2.5e+06f, 1.5625e+05f, 9e+03f, 2.6e+02f };

/* String-pool rodata migrated from debug_data.c */
__attribute__((section(".rodata.0x006149A8"))) const char D_006149A8[104] = "src/debug.c\000\000\000\000\000ico_debug.log\000\000\000log-file opened.\n\000\000\000\000\000\000\000log-file appended.\n\000\000\000\000\000log-file closed.\n\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "debug_mcSaveMainBlock:既に設定された数以上のデータを保存してる
" */
__attribute__((section(".rodata.0x00615400"))) const char D_00615400[64] = "debug_mcSaveMainBlock:\264\373\244\313\300\337\304\352\244\265\244\354\244\277\277\364\260\312\276\345\244\316\245\307\241\274\245\277\244\362\312\335\302\270\244\267\244\306\244\353\n";
/* EUC-JP: "debug_mcLoadMainBlock:既に設定された数以上のデータを保存してる
" */
__attribute__((section(".rodata.0x00615488"))) const char D_00615488[64] = "debug_mcLoadMainBlock:\264\373\244\313\300\337\304\352\244\265\244\354\244\277\277\364\260\312\276\345\244\316\245\307\241\274\245\277\244\362\312\335\302\270\244\267\244\306\244\353\n";
/* EUC-JP: "関数トレース用のテーブルファイル[[36m%s[m]が読めません。(0x%x)
" */
__attribute__((section(".rodata.0x00616520"))) const char D_00616520[72] = "\264\330\277\364\245\310\245\354\241\274\245\271\315\321\244\316\245\306\241\274\245\326\245\353\245\325\245\241\245\244\245\353[\033[36m%s\033[m]\244\254\306\311\244\341\244\336\244\273\244\363\241\243(0x%x)\n";
/* EUC-JP: "関数トレースのファイル[[36m%s[m]が読めません。(0x%x)
" */
__attribute__((section(".rodata.0x006165E8"))) const char D_006165E8[56] = "\264\330\277\364\245\310\245\354\241\274\245\271\244\316\245\325\245\241\245\244\245\353[\033[36m%s\033[m]\244\254\306\311\244\341\244\336\244\273\244\363\241\243(0x%x)\n";
/* EUC-JP: "ソースファイル[[36m%s[m]が読めません。(0x%x)
" */
__attribute__((section(".rodata.0x006166A8"))) const char D_006166A8[48] = "\245\275\241\274\245\271\245\325\245\241\245\244\245\353[\033[36m%s\033[m]\244\254\306\311\244\341\244\336\244\273\244\363\241\243(0x%x)\n";
/* EUC-JP: "[36m強制ハング処理が呼ばれました。情報は次の通り。
" */
__attribute__((section(".rodata.0x006167E0"))) const char D_006167E0[56] = "\033[36m\266\257\300\251\245\317\245\363\245\260\275\350\315\375\244\254\270\306\244\320\244\354\244\336\244\267\244\277\241\243\276\360\312\363\244\317\274\241\244\316\304\314\244\352\241\243\n";

#include "include_asm.h"
#include "matching.h"

extern void func_001AD748(const char *, int, char *);
extern void func_00263FF0(const char *, int, const char *);
extern void func_001AD768(const char *, int);
extern void func_00268DA0(char *buf, const char *fmt, void *va);

void func_001A2D78(const char *fmt, ...) {
    char buf[0x100];
    func_00268DA0(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    func_001AD748(D_006149A8, 0x503, buf);
    func_00263FF0(D_006149A8, 0x503, D_006329F8);
    func_001AD768(D_006149A8, 0x504);
    func_00263FF0(D_006149A8, 0x504, D_00632A00);
}

/* Matched body inlined from src/cod/0A2E10.c during TU coalesce. */
extern int D_00632A04;
void func_001A2E10(void) {
    volatile char buf[256];
    D_00632A04 = -1;
    KEEP_LIVE_MEM(buf);
}

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2E24);

extern void func_00268DA0(char *buf, const char *fmt, void *va);
extern void *func_0026527C(char *buf);
extern void func_00247C30(int target, char *buf, void *info);

void func_001A2E28(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    func_00268DA0(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = func_0026527C(buf);
    func_00247C30(D_00632A04, buf, info);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2E80);
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A2FA0);

/* Matched body inlined from src/cod/0A31C0.c during TU coalesce.
 * D_00632A0C is already declared above (extern'd by the sweep). */
extern int func_00100230(int a, int b, int c);
extern void func_00100250(int a, int b);
extern void func_001AA688(void);
extern void func_00100B40(int a);

void func_001A31C0(void)
{
    if ((int)D_00632A0C != -1) {
        func_00100250(1, D_00632A0C);
    }
    D_00632A0C = func_00100230(1, (int)func_001AA688, -1);
    func_00100B40(1);
}

INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3204);
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3208);
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3340);
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3394);
INCLUDE_ASM("asm/nonmatchings/src/debug", func_001A3398);
