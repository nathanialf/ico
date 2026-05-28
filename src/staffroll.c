/* staffroll.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_0063319C;
extern float D_006331A0;
extern const char D_006331A8[11];
extern unsigned char D_006331B3;
extern int D_006331B4;
extern int D_00633198;
extern int D_004BD980[];   /* defined as unsigned char[16] in box_data.c */
extern int D_00633EDC;
extern float D_00633EE0;
extern float D_00633EE4;
extern int D_00633EE8;
extern int D_00633EEC;
extern const char D_006331B8[8];
extern unsigned int D_006331C0;
extern unsigned int D_006331C4;
extern const char D_006331C8[8];
extern const char D_006331D0[8];
extern const char D_006331D8[8];
extern const char D_006331E0[8];
extern const char D_006331E8[8];
extern const char D_006331F0[8];
extern const char D_006331F8[8];
extern const char D_00633200[8];
extern const char D_00633208[8];

const char D_00617378[24] = "src/staffroll.c";

/* Trailing .word 0 of jtbl_00617390 (gcc emits 7 entries; original ELF
 * has 8 with trailing zero). Placed at offset 0x6173AC. */
__attribute__((section(".rodata.0x006173AC"))) static const int pad_jtbl_00617390 = 0;

/* EUC-JP: "staff roll 領域不足\n" */
const char D_00617360[24] = "staff roll \316\316\260\350\311\324\302\255\n";
const char D_006173B0[24] = "Masatsuka Saeki ";
const char D_006173C8[16] = "Fumiya Takeno ";
const char D_006173D8[16] = "{R}Akira Sato ";
const char D_006173E8[24] = "{R}<Supervisor> ";
const char D_00617400[24] = "{R}Yasuhide Kobayashi ";
const char D_00617418[32] = "{R}<Executive Producer> ";
const char D_00617438[16] = "{R}Kenji Kaido ";
const char D_00617448[24] = "{R}< Producer > ";
const char D_00617460[24] = "{R}< Director > ";
const char D_00617478[24] = "PlayStation Monitors ";
const char D_00617490[24] = "Kyouko Nakamura ";
const char D_006174A8[16] = "Takashi Sato ";
const char D_006174B8[24] = "Makoto Sekiguchi ";
const char D_006174D0[16] = "Yoshiyuki Seki ";
const char D_006174E0[24] = "Yoshiaki Tazaki ";
const char D_006174F8[24] = "Ryouko Minamisawa ";
const char D_00617510[16] = "Ayako Kojima ";
const char D_00617520[24] = "Chihiro Shimozawa ";
const char D_00617538[24] = "Yukie Tachibana ";
const char D_00617550[16] = "Mayumi Suzaki ";
const char D_00617560[24] = "Atsushi Matsushita ";
const char D_00617578[24] = "Ryouichi Hasekgawa ";
const char D_00617590[16] = "Chikashi Aoki ";
const char D_006175A0[24] = "Hiroshi Takekawa ";
const char D_006175B8[16] = "Taku Nishijima ";
const char D_006175C8[24] = "Kentaro Nakagoshi ";
const char D_006175E0[16] = "Masamichi Seki ";
const char D_006175F0[24] = "Masami Nakazawa ";
const char D_00617608[24] = "Noritaka Shimasaka ";
const char D_00617620[24] = "Nobuaki Yamazaki ";
const char D_00617638[24] = "Yasuhiro Takahama ";
const char D_00617650[16] = "Tsutomu Hamura ";
const char D_00617660[16] = "Susumu Abe ";
const char D_00617670[24] = "Yasuharu Yoshizawa ";
const char D_00617688[24] = "Kiyoko Koyanagi ";
const char D_006176A0[24] = "Hiroyuki Fujita ";
const char D_006176B8[16] = "Hajime Saito ";
const char D_006176C8[24] = "Masanori Takano ";
const char D_006176E0[16] = "Kenichi Koike ";
const char D_006176F0[24] = "{R}Shuji Hiramatsu ";
const char D_00617708[24] = "{R}< Special Thanks > ";
const char D_00617720[32] = "Patrick Seybold, Tina Casalino ";
const char D_00617740[24] = "Public Relations: ";
const char D_00617758[16] = "Molly Smith ";
const char D_00617768[32] = "Director of Public Relations: ";
const char D_00617788[16] = "Maggie Rojas ";
const char D_00617798[32] = "Product Marketing Specialist: ";
const char D_006177B8[16] = "John Koller ";
const char D_006177C8[24] = "Product Manager: ";
const char D_006177E0[24] = "Ami Matsumura-Blaire ";
const char D_006177F8[24] = "Director of Marketing: ";
const char D_00617810[16] = "Andrew House ";
const char D_00617820[40] = "Senior Vice-President of Marketing: ";
const char D_00617848[16] = "Lee Cummings ";
const char D_00617858[16] = "Will Shepard ";
const char D_00617868[16] = "Randy Miranda ";
const char D_00617878[16] = "Joel Manzano ";
const char D_00617888[24] = "Andrew Jennings ";
const char D_006178A0[16] = "Ryan Gorospe ";
const char D_006178B0[16] = "Lenny Gordon ";
const char D_006178C0[16] = "Raymond Chung ";
const char D_006178D0[24] = "Ericson Babaran ";
const char D_006178E8[16] = "Testers: ";
const char D_006178F8[24] = "Andrew Woodworth ";
const char D_00617910[16] = "Eric Ippolito ";
const char D_00617920[32] = "Project Coordinator, FPQA: ";
const char D_00617940[16] = "Nicole Nokes ";
const char D_00617950[24] = "Project Manager, FPQA: ";
const char D_00617968[16] = "Ara Demirjian ";
const char D_00617978[32] = "Technical Coordinator, FPQA: ";
const char D_00617998[24] = "Christian Arends ";
const char D_006179B0[32] = "Usability Manager, FPQA: ";
const char D_006179D0[16] = "Sam Bradley ";
const char D_006179E0[24] = "Core Manager, FPQA: ";
const char D_006179F8[24] = "Ritchard Markelz ";
const char D_00617A10[24] = "Senior Manager, FPQA: ";
const char D_00617A28[24] = "Michael Blackledge ";
const char D_00617A40[24] = "Director, FPQA: ";
const char D_00617A58[16] = "Ken Chan ";
const char D_00617A68[16] = "Ron Allen ";
const char D_00617A78[24] = "Assistant Producers: ";
const char D_00617A90[16] = "Darren Yager ";
const char D_00617AA0[16] = "Producer: ";
const char D_00617AB0[16] = "Connie Booth ";
const char D_00617AC0[40] = "Director of Product Development: ";
const char D_00617AE8[16] = "Shuhei Yoshida ";
const char D_00617AF8[32] = "VP of Product Development: ";
const char D_00617B18[16] = "< SCEA Staff > ";
const char D_00617B28[16] = "Masaaki Doi ";
const char D_00617B38[16] = "Mikiko Okai ";
const char D_00617B48[24] = "{R}Tsubasa Inaba ";
const char D_00617B60[32] = "{R}< Overseas Coordination > ";
const char D_00617B80[24] = "{R}Hironori Komiya ";
const char D_00617B98[40] = "{R}<Cover/Software Manual Design> ";
const char D_00617BC0[16] = "Kazuaki Komiya ";
const char D_00617BD0[24] = "{R}Tomoko Inoue ";
const char D_00617BE8[24] = "{R}< Promotion > ";
const char D_00617C00[24] = "Youko Matsuyama ";
const char D_00617C18[16] = "Ryota Kawanaka ";
const char D_00617C28[16] = "Rie Shishido ";
const char D_00617C38[24] = "Chisako Nishitani ";
const char D_00617C50[16] = "Kentaro Mitomo ";
const char D_00617C60[16] = "Kentaro Anzai ";
const char D_00617C70[16] = "Atsushi Sakai ";
const char D_00617C80[16] = "Hirokazu Konno ";
const char D_00617C90[16] = "Junya Watari ";
const char D_00617CA0[16] = "Junpei Kato ";
const char D_00617CB0[16] = "Ema Ueoka ";
const char D_00617CC0[16] = "Yu Tokunou ";
const char D_00617CD0[24] = "{R}Kenji Komata ";
const char D_00617CE8[16] = "{R}QA Staff: ";
const char D_00617CF8[16] = "{R}Koji Ota ";
const char D_00617D08[16] = "QA Manager: ";
const char D_00617D18[24] = "{R}< SCEJ QA Team > ";
const char D_00617D30[16] = "Asako Sanada ";
const char D_00617D40[16] = "Koji Mitsuda ";
const char D_00617D50[24] = "ToshitakeTsuchikura ";
const char D_00617D68[16] = "Satoru Fukui ";
const char D_00617D78[24] = "{R}Junichi Kobayashi ";
const char D_00617D90[32] = "{R}<Technical Cooperation> ";
const char D_00617DB0[16] = "( A.M.L. ) ";
const char D_00617DC0[16] = "{R}Hideo Sato ";
const char D_00617DD0[24] = "{R}< Sub Titles > ";
const char D_00617DE8[24] = "{R}Hideki Yoshida ";
const char D_00617E00[24] = "{R}Recording Engineer: ";
const char D_00617E18[24] = "{R}Shinsaku Tanaka ";
const char D_00617E30[40] = "{R}(TOHOKUSHINSHA FILM CORPORATION) ";
const char D_00617E58[24] = "{R}Miho Kawagoe ";
const char D_00617E70[24] = "{R}Voice Production: ";
const char D_00617E88[24] = "{R}Misa Watanabe ";
const char D_00617EA0[24] = "{R}Voice of the QUEEN: ";
const char D_00617EB8[24] = "{R}Rieko Takahashi ";
const char D_00617ED0[24] = "{R}Voice of YORDA: ";
const char D_00617EE8[24] = "{R}Kazuhiro Shindou ";
const char D_00617F00[16] = "Voice of ICO: ";
const char D_00617F10[32] = "{R}< Voice Actors & Actress > ";
const char D_00617F30[24] = "Roland Herrington ";
const char D_00617F48[16] = "Engineer: ";
const char D_00617F58[16] = "{R}(in London) ";
const char D_00617F68[24] = "{R}MASTER ROCK STUDIO ";
const char D_00617F80[16] = "{R}Studio: ";
const char D_00617F90[24] = "{R}Recording Studio: ";
const char D_00617FA8[40] = "{R}(TOUSHITU SEISAKU CO., LTD.) ";
const char D_00617FD0[24] = "{R}Emari Mamiya ";
const char D_00617FE8[32] = "{R}(ORTUS PRODUCTIONS JAPAN) ";
const char D_00618008[24] = "{R}Lynne Hobday ";
const char D_00618020[32] = "{R}Recording Coordination: ";
const char D_00618040[16] = "{R}Arranger: ";
const char D_00618050[16] = "{R}Pentagon ";
const char D_00618060[24] = "{R}Michiru Ohshima ";
const char D_00618078[16] = "{R}Composer: ";
const char D_00618088[24] = "{R}George Asahi ";
const char D_006180A0[24] = "{R}Music Supervisor: ";
const char D_006180B8[24] = "Keiichi Kitahara ";
const char D_006180D0[24] = "{R}Sound Effects: ";
const char D_006180E8[24] = "{R}Masaaki Kaneko ";
const char D_00618100[24] = "Sound Designer: ";
const char D_00618118[24] = "{R}< Music & Sound > ";
const char D_00618130[16] = "{R}Scripting: ";
const char D_00618140[24] = "{R}Toshihiro Ito ";
const char D_00618158[24] = "{R}Tools Program: ";
const char D_00618170[16] = "Takuya Seki ";
const char D_00618180[24] = "{R}Visual Program: ";
const char D_00618198[16] = "{R}Takuya Seki ";
const char D_006181A8[32] = "{R}Draw Engine Program: ";
const char D_006181C8[16] = "Jinji Horagai ";
const char D_006181D8[24] = "{R}YORDA A.I. Program: ";
const char D_006181F0[24] = "{R}Hajime Sugiyama ";
const char D_00618208[32] = "{R}Motion System Program: ";
const char D_00618228[16] = "Toshihiro Ito ";
const char D_00618238[24] = "Hajime Sugiyama ";
const char D_00618250[24] = "{R}Shotaro Omori ";
const char D_00618268[32] = "{R}Characters&Objects Program: ";
const char D_00618288[16] = "Fumiaki Hara ";
const char D_00618298[24] = "{R}Jinji Horagai ";
const char D_006182B0[24] = "System Program: ";
const char D_006182C8[24] = "{R}< Programmers > ";
const char D_006182E0[24] = "Kazuhiro Numata ";
const char D_006182F8[16] = "Chika Fukui ";
const char D_00618308[24] = "{R}Character Design: ";
const char D_00618320[16] = "Kaihei Hayano ";
const char D_00618330[16] = "Mikiko Takeda ";
const char D_00618340[24] = "Taijurou Hachiya ";
const char D_00618358[24] = "Atsushi Morioka ";
const char D_00618370[16] = "Katsuhiko Abe ";
const char D_00618380[24] = "Mitsuhiro Shimooki ";
const char D_00618398[16] = "Chikara Ueno ";
const char D_006183A8[16] = "Nanako Ohmura ";
const char D_006183B8[24] = "{R}Kazuhiro Numata ";
const char D_006183D0[24] = "{R}Background Artists: ";
const char D_006183E8[24] = "{R}(Key Animator) ";
const char D_00618400[24] = "{R}(SmokeMan,ICO) ";
const char D_00618418[24] = "{R}Mizuki Muramatsu ";
const char D_00618430[16] = "{R}(ICO,QUEEN) ";
const char D_00618440[24] = "{R}Takeshi Ambe ";
const char D_00618458[16] = "{R}(YORDA,ICO) ";
const char D_00618468[24] = "{R}Atsuko Fukuyama ";
const char D_00618480[24] = "Character Animation: ";
const char D_00618498[24] = "{R}< Graphic Artists > ";
const char D_006184B0[16] = "Tsutomu Kouno ";
const char D_006184C0[16] = "Kei Kuwabara ";
const char D_006184D0[24] = "{R}Junichi Hosono ";
const char D_006184E8[24] = "{R}< Planners > ";
const char D_00618500[16] = "{R}Fumito Ueda ";
const char D_00618510[24] = "{R}< Game Design > ";
const char D_00618528[40] = "{#FFFFFF80}{R} ICO Staff  ";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/staffroll", func_001B8388);
void func_001FB4A8(void);
int func_001B8210(void);
int func_001B8388(void);

void func_001B84C8(void) {
    int n;
    int v;
    float a, c;
    int state;

    if (D_00633EE8 != 0) {
        register float fee0 __asm__("$f1") = D_00633EE0;
        register int v0 __asm__("$2");
        n = 0;
        v0 = (int)((float)D_004BD980[0] - fee0);
        D_004BD980[0] = v0;
        if (v0 < -0x1400) {
            D_004BD980[0] = -0x1400;
            n = 1;
        }
        {
            register float fee4 __asm__("$f1") = D_00633EE4;
            v0 = (int)((float)D_00633EDC - fee4);
        }
        D_00633EDC = v0;
        if (v0 < 0x280) {
            D_00633EDC = 0x280;
            n++;
        }
        if (n == 2) D_00633EE8 = 0;
    }

    {
        int b3 = D_006331B3;
        int b4 = D_006331B4;
        int r;
        if (b3 < b4) {
            b3 += 2;
            r = (b4 < b3) ? b4 : b3;
        } else {
            b3 -= 2;
            r = (b3 < b4) ? b4 : b3;
        }
        a = D_006331A0;
        c = D_0063319C;
        *(volatile unsigned char *)&D_006331B3 = r;
    }

    if (c < a) {
        c += 0.5f;
        D_0063319C = c;
        if (a < c) {
            D_0063319C = a;
        }
    } else {
        c -= 0.5f;
        D_0063319C = c;
        if (c < a) {
            D_0063319C = a;
        }
    }

    state = D_00633EEC;
    if ((unsigned)state >= 7) return;

    switch (state) {
    case 0:
        func_001FB4A8();
        D_006331B3 = 0;
        D_00633EEC = D_00633EEC + 1;
        /* fallthrough */
    case 1:
        D_006331A0 = 0;
        if (D_006331B3 != D_006331B4) return;
        if (D_0063319C != D_006331A0) return;
        D_00633EEC = D_00633EEC + 1;
        return;
    case 2:
        func_001B8210();
        if (func_001B8388() == 0) return;
        D_00633EEC = D_00633EEC + 1;
        return;
    case 3:
        if (func_001B8210() != 0) return;
        D_00633EEC = D_00633EEC + 1;
        return;
    case 4:
        D_006331B4 = 0;
        D_006331A0 = 0;
        if (D_006331B3 != 0) return;
        D_00633EEC = state + 1;
        return;
    case 5:
        if (D_0063319C != 0.0f) return;
        D_00633EEC = state + 1;
        return;
    case 6:
        D_00633198 = 0;
        return;
    }
}
void func_001B86C0(void)
{
    register int a __asm__("$3") = D_004BD980[0] + 0x1400;
    register int one __asm__("$2") = 1;
    register int b4 __asm__("$6") = 0xFF;
    int b;
    D_00633EE8 = one;
    D_00633EE0 = (float)(a / 30);
    b = D_00633EDC - 0x280;
    D_00633EE4 = (float)(b / 30);
    D_006331B4 = b4;
}
