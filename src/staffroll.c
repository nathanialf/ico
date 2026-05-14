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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x006331A8"))) const char D_006331A8[11] = "0";
__attribute__((section(".sdata.0x006331B3"))) char D_006331B3 = 0;
__attribute__((section(".sdata.0x006331B4"))) int D_006331B4 = 0;
__attribute__((section(".sdata.0x006331B8"))) const char D_006331B8[8] = "Lead: ";
__attribute__((section(".sdata.0x006331C0"))) unsigned int D_006331C0 = 0x00000020;
__attribute__((section(".sdata.0x006331C4"))) unsigned int D_006331C4 = 0x00000430;
__attribute__((section(".sdata.0x006331C8"))) const char D_006331C8[8] = "SL";
__attribute__((section(".sdata.0x006331D0"))) const char D_006331D0[8] = "TH";
__attribute__((section(".sdata.0x006331D8"))) const char D_006331D8[8] = "D2";
__attribute__((section(".sdata.0x006331E0"))) const char D_006331E0[8] = "D1";
__attribute__((section(".sdata.0x006331E8"))) const char D_006331E8[8] = "DE";
__attribute__((section(".sdata.0x006331F0"))) const char D_006331F0[8] = "AT";
__attribute__((section(".sdata.0x006331F8"))) const char D_006331F8[8] = "RO";
__attribute__((section(".sdata.0x00633200"))) const char D_00633200[8] = "WA";
__attribute__((section(".sdata.0x00633208"))) const char D_00633208[8] = "ST";

__attribute__((section(".rodata.0x00617378"))) const char D_00617378[24] = "src/staffroll.c";

__attribute__((section(".rodata.0x006173B0"))) const char D_006173B0[24] = "Masatsuka Saeki ";
__attribute__((section(".rodata.0x006173C8"))) const char D_006173C8[16] = "Fumiya Takeno ";
__attribute__((section(".rodata.0x006173D8"))) const char D_006173D8[16] = "{R}Akira Sato ";
__attribute__((section(".rodata.0x006173E8"))) const char D_006173E8[24] = "{R}<Supervisor> ";
__attribute__((section(".rodata.0x00617400"))) const char D_00617400[24] = "{R}Yasuhide Kobayashi ";
__attribute__((section(".rodata.0x00617418"))) const char D_00617418[32] = "{R}<Executive Producer> ";
__attribute__((section(".rodata.0x00617438"))) const char D_00617438[16] = "{R}Kenji Kaido ";
__attribute__((section(".rodata.0x00617448"))) const char D_00617448[24] = "{R}< Producer > ";
__attribute__((section(".rodata.0x00617460"))) const char D_00617460[24] = "{R}< Director > ";
__attribute__((section(".rodata.0x00617478"))) const char D_00617478[24] = "PlayStation Monitors ";
__attribute__((section(".rodata.0x00617490"))) const char D_00617490[24] = "Kyouko Nakamura ";
__attribute__((section(".rodata.0x006174A8"))) const char D_006174A8[16] = "Takashi Sato ";
__attribute__((section(".rodata.0x006174B8"))) const char D_006174B8[24] = "Makoto Sekiguchi ";
__attribute__((section(".rodata.0x006174D0"))) const char D_006174D0[16] = "Yoshiyuki Seki ";
__attribute__((section(".rodata.0x006174E0"))) const char D_006174E0[24] = "Yoshiaki Tazaki ";
__attribute__((section(".rodata.0x006174F8"))) const char D_006174F8[24] = "Ryouko Minamisawa ";
__attribute__((section(".rodata.0x00617510"))) const char D_00617510[16] = "Ayako Kojima ";
__attribute__((section(".rodata.0x00617520"))) const char D_00617520[24] = "Chihiro Shimozawa ";
__attribute__((section(".rodata.0x00617538"))) const char D_00617538[24] = "Yukie Tachibana ";
__attribute__((section(".rodata.0x00617550"))) const char D_00617550[16] = "Mayumi Suzaki ";
__attribute__((section(".rodata.0x00617560"))) const char D_00617560[24] = "Atsushi Matsushita ";
__attribute__((section(".rodata.0x00617578"))) const char D_00617578[24] = "Ryouichi Hasekgawa ";
__attribute__((section(".rodata.0x00617590"))) const char D_00617590[16] = "Chikashi Aoki ";
__attribute__((section(".rodata.0x006175A0"))) const char D_006175A0[24] = "Hiroshi Takekawa ";
__attribute__((section(".rodata.0x006175B8"))) const char D_006175B8[16] = "Taku Nishijima ";
__attribute__((section(".rodata.0x006175C8"))) const char D_006175C8[24] = "Kentaro Nakagoshi ";
__attribute__((section(".rodata.0x006175E0"))) const char D_006175E0[16] = "Masamichi Seki ";
__attribute__((section(".rodata.0x006175F0"))) const char D_006175F0[24] = "Masami Nakazawa ";
__attribute__((section(".rodata.0x00617608"))) const char D_00617608[24] = "Noritaka Shimasaka ";
__attribute__((section(".rodata.0x00617620"))) const char D_00617620[24] = "Nobuaki Yamazaki ";
__attribute__((section(".rodata.0x00617638"))) const char D_00617638[24] = "Yasuhiro Takahama ";
__attribute__((section(".rodata.0x00617650"))) const char D_00617650[16] = "Tsutomu Hamura ";
__attribute__((section(".rodata.0x00617660"))) const char D_00617660[16] = "Susumu Abe ";
__attribute__((section(".rodata.0x00617670"))) const char D_00617670[24] = "Yasuharu Yoshizawa ";
__attribute__((section(".rodata.0x00617688"))) const char D_00617688[24] = "Kiyoko Koyanagi ";
__attribute__((section(".rodata.0x006176A0"))) const char D_006176A0[24] = "Hiroyuki Fujita ";
__attribute__((section(".rodata.0x006176B8"))) const char D_006176B8[16] = "Hajime Saito ";
__attribute__((section(".rodata.0x006176C8"))) const char D_006176C8[24] = "Masanori Takano ";
__attribute__((section(".rodata.0x006176E0"))) const char D_006176E0[16] = "Kenichi Koike ";
__attribute__((section(".rodata.0x006176F0"))) const char D_006176F0[24] = "{R}Shuji Hiramatsu ";
__attribute__((section(".rodata.0x00617708"))) const char D_00617708[24] = "{R}< Special Thanks > ";
__attribute__((section(".rodata.0x00617720"))) const char D_00617720[32] = "Patrick Seybold, Tina Casalino ";
__attribute__((section(".rodata.0x00617740"))) const char D_00617740[24] = "Public Relations: ";
__attribute__((section(".rodata.0x00617758"))) const char D_00617758[16] = "Molly Smith ";
__attribute__((section(".rodata.0x00617768"))) const char D_00617768[32] = "Director of Public Relations: ";
__attribute__((section(".rodata.0x00617788"))) const char D_00617788[16] = "Maggie Rojas ";
__attribute__((section(".rodata.0x00617798"))) const char D_00617798[32] = "Product Marketing Specialist: ";
__attribute__((section(".rodata.0x006177B8"))) const char D_006177B8[16] = "John Koller ";
__attribute__((section(".rodata.0x006177C8"))) const char D_006177C8[24] = "Product Manager: ";
__attribute__((section(".rodata.0x006177E0"))) const char D_006177E0[24] = "Ami Matsumura-Blaire ";
__attribute__((section(".rodata.0x006177F8"))) const char D_006177F8[24] = "Director of Marketing: ";
__attribute__((section(".rodata.0x00617810"))) const char D_00617810[16] = "Andrew House ";
__attribute__((section(".rodata.0x00617820"))) const char D_00617820[40] = "Senior Vice-President of Marketing: ";
__attribute__((section(".rodata.0x00617848"))) const char D_00617848[16] = "Lee Cummings ";
__attribute__((section(".rodata.0x00617858"))) const char D_00617858[16] = "Will Shepard ";
__attribute__((section(".rodata.0x00617868"))) const char D_00617868[16] = "Randy Miranda ";
__attribute__((section(".rodata.0x00617878"))) const char D_00617878[16] = "Joel Manzano ";
__attribute__((section(".rodata.0x00617888"))) const char D_00617888[24] = "Andrew Jennings ";
__attribute__((section(".rodata.0x006178A0"))) const char D_006178A0[16] = "Ryan Gorospe ";
__attribute__((section(".rodata.0x006178B0"))) const char D_006178B0[16] = "Lenny Gordon ";
__attribute__((section(".rodata.0x006178C0"))) const char D_006178C0[16] = "Raymond Chung ";
__attribute__((section(".rodata.0x006178D0"))) const char D_006178D0[24] = "Ericson Babaran ";
__attribute__((section(".rodata.0x006178E8"))) const char D_006178E8[16] = "Testers: ";
__attribute__((section(".rodata.0x006178F8"))) const char D_006178F8[24] = "Andrew Woodworth ";
__attribute__((section(".rodata.0x00617910"))) const char D_00617910[16] = "Eric Ippolito ";
__attribute__((section(".rodata.0x00617920"))) const char D_00617920[32] = "Project Coordinator, FPQA: ";
__attribute__((section(".rodata.0x00617940"))) const char D_00617940[16] = "Nicole Nokes ";
__attribute__((section(".rodata.0x00617950"))) const char D_00617950[24] = "Project Manager, FPQA: ";
__attribute__((section(".rodata.0x00617968"))) const char D_00617968[16] = "Ara Demirjian ";
__attribute__((section(".rodata.0x00617978"))) const char D_00617978[32] = "Technical Coordinator, FPQA: ";
__attribute__((section(".rodata.0x00617998"))) const char D_00617998[24] = "Christian Arends ";
__attribute__((section(".rodata.0x006179B0"))) const char D_006179B0[32] = "Usability Manager, FPQA: ";
__attribute__((section(".rodata.0x006179D0"))) const char D_006179D0[16] = "Sam Bradley ";
__attribute__((section(".rodata.0x006179E0"))) const char D_006179E0[24] = "Core Manager, FPQA: ";
__attribute__((section(".rodata.0x006179F8"))) const char D_006179F8[24] = "Ritchard Markelz ";
__attribute__((section(".rodata.0x00617A10"))) const char D_00617A10[24] = "Senior Manager, FPQA: ";
__attribute__((section(".rodata.0x00617A28"))) const char D_00617A28[24] = "Michael Blackledge ";
__attribute__((section(".rodata.0x00617A40"))) const char D_00617A40[24] = "Director, FPQA: ";
__attribute__((section(".rodata.0x00617A58"))) const char D_00617A58[16] = "Ken Chan ";
__attribute__((section(".rodata.0x00617A68"))) const char D_00617A68[16] = "Ron Allen ";
__attribute__((section(".rodata.0x00617A78"))) const char D_00617A78[24] = "Assistant Producers: ";
__attribute__((section(".rodata.0x00617A90"))) const char D_00617A90[16] = "Darren Yager ";
__attribute__((section(".rodata.0x00617AA0"))) const char D_00617AA0[16] = "Producer: ";
__attribute__((section(".rodata.0x00617AB0"))) const char D_00617AB0[16] = "Connie Booth ";
__attribute__((section(".rodata.0x00617AC0"))) const char D_00617AC0[40] = "Director of Product Development: ";
__attribute__((section(".rodata.0x00617AE8"))) const char D_00617AE8[16] = "Shuhei Yoshida ";
__attribute__((section(".rodata.0x00617AF8"))) const char D_00617AF8[32] = "VP of Product Development: ";
__attribute__((section(".rodata.0x00617B18"))) const char D_00617B18[16] = "< SCEA Staff > ";
__attribute__((section(".rodata.0x00617B28"))) const char D_00617B28[16] = "Masaaki Doi ";
__attribute__((section(".rodata.0x00617B38"))) const char D_00617B38[16] = "Mikiko Okai ";
__attribute__((section(".rodata.0x00617B48"))) const char D_00617B48[24] = "{R}Tsubasa Inaba ";
__attribute__((section(".rodata.0x00617B60"))) const char D_00617B60[32] = "{R}< Overseas Coordination > ";
__attribute__((section(".rodata.0x00617B80"))) const char D_00617B80[24] = "{R}Hironori Komiya ";
__attribute__((section(".rodata.0x00617B98"))) const char D_00617B98[40] = "{R}<Cover/Software Manual Design> ";
__attribute__((section(".rodata.0x00617BC0"))) const char D_00617BC0[16] = "Kazuaki Komiya ";
__attribute__((section(".rodata.0x00617BD0"))) const char D_00617BD0[24] = "{R}Tomoko Inoue ";
__attribute__((section(".rodata.0x00617BE8"))) const char D_00617BE8[24] = "{R}< Promotion > ";
__attribute__((section(".rodata.0x00617C00"))) const char D_00617C00[24] = "Youko Matsuyama ";
__attribute__((section(".rodata.0x00617C18"))) const char D_00617C18[16] = "Ryota Kawanaka ";
__attribute__((section(".rodata.0x00617C28"))) const char D_00617C28[16] = "Rie Shishido ";
__attribute__((section(".rodata.0x00617C38"))) const char D_00617C38[24] = "Chisako Nishitani ";
__attribute__((section(".rodata.0x00617C50"))) const char D_00617C50[16] = "Kentaro Mitomo ";
__attribute__((section(".rodata.0x00617C60"))) const char D_00617C60[16] = "Kentaro Anzai ";
__attribute__((section(".rodata.0x00617C70"))) const char D_00617C70[16] = "Atsushi Sakai ";
__attribute__((section(".rodata.0x00617C80"))) const char D_00617C80[16] = "Hirokazu Konno ";
__attribute__((section(".rodata.0x00617C90"))) const char D_00617C90[16] = "Junya Watari ";
__attribute__((section(".rodata.0x00617CA0"))) const char D_00617CA0[16] = "Junpei Kato ";
__attribute__((section(".rodata.0x00617CB0"))) const char D_00617CB0[16] = "Ema Ueoka ";
__attribute__((section(".rodata.0x00617CC0"))) const char D_00617CC0[16] = "Yu Tokunou ";
__attribute__((section(".rodata.0x00617CD0"))) const char D_00617CD0[24] = "{R}Kenji Komata ";
__attribute__((section(".rodata.0x00617CE8"))) const char D_00617CE8[16] = "{R}QA Staff: ";
__attribute__((section(".rodata.0x00617CF8"))) const char D_00617CF8[16] = "{R}Koji Ota ";
__attribute__((section(".rodata.0x00617D08"))) const char D_00617D08[16] = "QA Manager: ";
__attribute__((section(".rodata.0x00617D18"))) const char D_00617D18[24] = "{R}< SCEJ QA Team > ";
__attribute__((section(".rodata.0x00617D30"))) const char D_00617D30[16] = "Asako Sanada ";
__attribute__((section(".rodata.0x00617D40"))) const char D_00617D40[16] = "Koji Mitsuda ";
__attribute__((section(".rodata.0x00617D50"))) const char D_00617D50[24] = "ToshitakeTsuchikura ";
__attribute__((section(".rodata.0x00617D68"))) const char D_00617D68[16] = "Satoru Fukui ";
__attribute__((section(".rodata.0x00617D78"))) const char D_00617D78[24] = "{R}Junichi Kobayashi ";
__attribute__((section(".rodata.0x00617D90"))) const char D_00617D90[32] = "{R}<Technical Cooperation> ";
__attribute__((section(".rodata.0x00617DB0"))) const char D_00617DB0[16] = "( A.M.L. ) ";
__attribute__((section(".rodata.0x00617DC0"))) const char D_00617DC0[16] = "{R}Hideo Sato ";
__attribute__((section(".rodata.0x00617DD0"))) const char D_00617DD0[24] = "{R}< Sub Titles > ";
__attribute__((section(".rodata.0x00617DE8"))) const char D_00617DE8[24] = "{R}Hideki Yoshida ";
__attribute__((section(".rodata.0x00617E00"))) const char D_00617E00[24] = "{R}Recording Engineer: ";
__attribute__((section(".rodata.0x00617E18"))) const char D_00617E18[24] = "{R}Shinsaku Tanaka ";
__attribute__((section(".rodata.0x00617E30"))) const char D_00617E30[40] = "{R}(TOHOKUSHINSHA FILM CORPORATION) ";
__attribute__((section(".rodata.0x00617E58"))) const char D_00617E58[24] = "{R}Miho Kawagoe ";
__attribute__((section(".rodata.0x00617E70"))) const char D_00617E70[24] = "{R}Voice Production: ";
__attribute__((section(".rodata.0x00617E88"))) const char D_00617E88[24] = "{R}Misa Watanabe ";
__attribute__((section(".rodata.0x00617EA0"))) const char D_00617EA0[24] = "{R}Voice of the QUEEN: ";
__attribute__((section(".rodata.0x00617EB8"))) const char D_00617EB8[24] = "{R}Rieko Takahashi ";
__attribute__((section(".rodata.0x00617ED0"))) const char D_00617ED0[24] = "{R}Voice of YORDA: ";
__attribute__((section(".rodata.0x00617EE8"))) const char D_00617EE8[24] = "{R}Kazuhiro Shindou ";
__attribute__((section(".rodata.0x00617F00"))) const char D_00617F00[16] = "Voice of ICO: ";
__attribute__((section(".rodata.0x00617F10"))) const char D_00617F10[32] = "{R}< Voice Actors & Actress > ";
__attribute__((section(".rodata.0x00617F30"))) const char D_00617F30[24] = "Roland Herrington ";
__attribute__((section(".rodata.0x00617F48"))) const char D_00617F48[16] = "Engineer: ";
__attribute__((section(".rodata.0x00617F58"))) const char D_00617F58[16] = "{R}(in London) ";
__attribute__((section(".rodata.0x00617F68"))) const char D_00617F68[24] = "{R}MASTER ROCK STUDIO ";
__attribute__((section(".rodata.0x00617F80"))) const char D_00617F80[16] = "{R}Studio: ";
__attribute__((section(".rodata.0x00617F90"))) const char D_00617F90[24] = "{R}Recording Studio: ";
__attribute__((section(".rodata.0x00617FA8"))) const char D_00617FA8[40] = "{R}(TOUSHITU SEISAKU CO., LTD.) ";
__attribute__((section(".rodata.0x00617FD0"))) const char D_00617FD0[24] = "{R}Emari Mamiya ";
__attribute__((section(".rodata.0x00617FE8"))) const char D_00617FE8[32] = "{R}(ORTUS PRODUCTIONS JAPAN) ";
__attribute__((section(".rodata.0x00618008"))) const char D_00618008[24] = "{R}Lynne Hobday ";
__attribute__((section(".rodata.0x00618020"))) const char D_00618020[32] = "{R}Recording Coordination: ";
__attribute__((section(".rodata.0x00618040"))) const char D_00618040[16] = "{R}Arranger: ";
__attribute__((section(".rodata.0x00618050"))) const char D_00618050[16] = "{R}Pentagon ";
__attribute__((section(".rodata.0x00618060"))) const char D_00618060[24] = "{R}Michiru Ohshima ";
__attribute__((section(".rodata.0x00618078"))) const char D_00618078[16] = "{R}Composer: ";
__attribute__((section(".rodata.0x00618088"))) const char D_00618088[24] = "{R}George Asahi ";
__attribute__((section(".rodata.0x006180A0"))) const char D_006180A0[24] = "{R}Music Supervisor: ";
__attribute__((section(".rodata.0x006180B8"))) const char D_006180B8[24] = "Keiichi Kitahara ";
__attribute__((section(".rodata.0x006180D0"))) const char D_006180D0[24] = "{R}Sound Effects: ";
__attribute__((section(".rodata.0x006180E8"))) const char D_006180E8[24] = "{R}Masaaki Kaneko ";
__attribute__((section(".rodata.0x00618100"))) const char D_00618100[24] = "Sound Designer: ";
__attribute__((section(".rodata.0x00618118"))) const char D_00618118[24] = "{R}< Music & Sound > ";
__attribute__((section(".rodata.0x00618130"))) const char D_00618130[16] = "{R}Scripting: ";
__attribute__((section(".rodata.0x00618140"))) const char D_00618140[24] = "{R}Toshihiro Ito ";
__attribute__((section(".rodata.0x00618158"))) const char D_00618158[24] = "{R}Tools Program: ";
__attribute__((section(".rodata.0x00618170"))) const char D_00618170[16] = "Takuya Seki ";
__attribute__((section(".rodata.0x00618180"))) const char D_00618180[24] = "{R}Visual Program: ";
__attribute__((section(".rodata.0x00618198"))) const char D_00618198[16] = "{R}Takuya Seki ";
__attribute__((section(".rodata.0x006181A8"))) const char D_006181A8[32] = "{R}Draw Engine Program: ";
__attribute__((section(".rodata.0x006181C8"))) const char D_006181C8[16] = "Jinji Horagai ";
__attribute__((section(".rodata.0x006181D8"))) const char D_006181D8[24] = "{R}YORDA A.I. Program: ";
__attribute__((section(".rodata.0x006181F0"))) const char D_006181F0[24] = "{R}Hajime Sugiyama ";
__attribute__((section(".rodata.0x00618208"))) const char D_00618208[32] = "{R}Motion System Program: ";
__attribute__((section(".rodata.0x00618228"))) const char D_00618228[16] = "Toshihiro Ito ";
__attribute__((section(".rodata.0x00618238"))) const char D_00618238[24] = "Hajime Sugiyama ";
__attribute__((section(".rodata.0x00618250"))) const char D_00618250[24] = "{R}Shotaro Omori ";
__attribute__((section(".rodata.0x00618268"))) const char D_00618268[32] = "{R}Characters&Objects Program: ";
__attribute__((section(".rodata.0x00618288"))) const char D_00618288[16] = "Fumiaki Hara ";
__attribute__((section(".rodata.0x00618298"))) const char D_00618298[24] = "{R}Jinji Horagai ";
__attribute__((section(".rodata.0x006182B0"))) const char D_006182B0[24] = "System Program: ";
__attribute__((section(".rodata.0x006182C8"))) const char D_006182C8[24] = "{R}< Programmers > ";
__attribute__((section(".rodata.0x006182E0"))) const char D_006182E0[24] = "Kazuhiro Numata ";
__attribute__((section(".rodata.0x006182F8"))) const char D_006182F8[16] = "Chika Fukui ";
__attribute__((section(".rodata.0x00618308"))) const char D_00618308[24] = "{R}Character Design: ";
__attribute__((section(".rodata.0x00618320"))) const char D_00618320[16] = "Kaihei Hayano ";
__attribute__((section(".rodata.0x00618330"))) const char D_00618330[16] = "Mikiko Takeda ";
__attribute__((section(".rodata.0x00618340"))) const char D_00618340[24] = "Taijurou Hachiya ";
__attribute__((section(".rodata.0x00618358"))) const char D_00618358[24] = "Atsushi Morioka ";
__attribute__((section(".rodata.0x00618370"))) const char D_00618370[16] = "Katsuhiko Abe ";
__attribute__((section(".rodata.0x00618380"))) const char D_00618380[24] = "Mitsuhiro Shimooki ";
__attribute__((section(".rodata.0x00618398"))) const char D_00618398[16] = "Chikara Ueno ";
__attribute__((section(".rodata.0x006183A8"))) const char D_006183A8[16] = "Nanako Ohmura ";
__attribute__((section(".rodata.0x006183B8"))) const char D_006183B8[24] = "{R}Kazuhiro Numata ";
__attribute__((section(".rodata.0x006183D0"))) const char D_006183D0[24] = "{R}Background Artists: ";
__attribute__((section(".rodata.0x006183E8"))) const char D_006183E8[24] = "{R}(Key Animator) ";
__attribute__((section(".rodata.0x00618400"))) const char D_00618400[24] = "{R}(SmokeMan,ICO) ";
__attribute__((section(".rodata.0x00618418"))) const char D_00618418[24] = "{R}Mizuki Muramatsu ";
__attribute__((section(".rodata.0x00618430"))) const char D_00618430[16] = "{R}(ICO,QUEEN) ";
__attribute__((section(".rodata.0x00618440"))) const char D_00618440[24] = "{R}Takeshi Ambe ";
__attribute__((section(".rodata.0x00618458"))) const char D_00618458[16] = "{R}(YORDA,ICO) ";
__attribute__((section(".rodata.0x00618468"))) const char D_00618468[24] = "{R}Atsuko Fukuyama ";
__attribute__((section(".rodata.0x00618480"))) const char D_00618480[24] = "Character Animation: ";
__attribute__((section(".rodata.0x00618498"))) const char D_00618498[24] = "{R}< Graphic Artists > ";
__attribute__((section(".rodata.0x006184B0"))) const char D_006184B0[16] = "Tsutomu Kouno ";
__attribute__((section(".rodata.0x006184C0"))) const char D_006184C0[16] = "Kei Kuwabara ";
__attribute__((section(".rodata.0x006184D0"))) const char D_006184D0[24] = "{R}Junichi Hosono ";
__attribute__((section(".rodata.0x006184E8"))) const char D_006184E8[24] = "{R}< Planners > ";
__attribute__((section(".rodata.0x00618500"))) const char D_00618500[16] = "{R}Fumito Ueda ";
__attribute__((section(".rodata.0x00618510"))) const char D_00618510[24] = "{R}< Game Design > ";
__attribute__((section(".rodata.0x00618528"))) const char D_00618528[40] = "{#FFFFFF80}{R} ICO Staff  ";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "staff roll 領域不足
" */
__attribute__((section(".rodata.0x00617360"))) const char D_00617360[24] = "staff roll \316\316\260\350\311\324\302\255\n";
