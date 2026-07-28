
const char D_00555ED8[16] = "src/Texture.c";
const char D_005565C8[24] = "%8s:SIZE=%3dX%3d";
const char D_005565E0[24] = "/%d Name:%s x:x%d";
const char D_00556620[48] = "No.              Name   Size MIP IMG CL US";
const char D_00556650[32] = "%03d%18s%7d:%1d/%1d:%s:%s:%s";
const char D_00556670[16] = "   %17s %7d ";
const char D_00556680[24] = "TotalTextureSize";
const char D_00556728[16] = " Fog Strength ";
const char D_00556738[16] = " Fog Far      ";
const char D_00556748[16] = " Fog Near     ";
const char D_00556758[16] = " Fog Offset A ";
const char D_00556768[16] = " Fog Color A  ";
const char D_00556778[16] = " Fog Color B  ";
const char D_00556788[16] = " Fog Color G  ";
const char D_00556798[16] = " Fog Color R  ";
const char D_005567A8[16] = " Fog On/Off   ";
const char D_005567C0[16] = "Fog Tool";
const char D_005563F0[64] = "TEXTURE BROKEN. \"%s\"\n    I:%d C:%d iadr:%p cadr:%p hadr:%p\n";
const char D_005564E0[48] = "tex_TransTexture:INVALID TEXTURE ID. %d/%d\n";
const char D_00556580[72] = "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n";
const char D_005567D0[16] = "Fog %s => %s\n";
const char D_005567E0[16] = "Fog %s => %d\n";
const char D_00555EA0[56] = "tex_loadImage:\310\275\312\314\244\307\244\255\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\325\245\251\241\274\245\336\245\303\245\310\244\307\244\271.\n";
const char D_00555EE8[56] = "tex_loadImage:\245\306\245\257\245\271\245\301\245\343\244\316\245\265\245\244\245\272\244\254\302\347\244\255\244\271\244\256\244\336\244\271.\n";
const char D_00556010[64] = "DIRECT\244\307\244\342CLUT\244\307\244\342\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\277\245\244\245\327\244\254\273\330\304\352\244\265\244\354\244\336\244\267\244\277.\n";
const char D_00556050[56] = "tex_transTM2:\245\337\245\303\245\327\245\336\245\303\245\327\245\306\245\257\245\271\245\301\245\343\244\316\313\347\277\364\244\254\302\277\244\271\244\256\244\336\244\271.\n";
const char D_00556088[72] = "\245\306\245\257\245\271\245\301\245\343\244\254\262\365\244\354\244\306\244\244\244\336\244\271.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n";
const char D_005563A0[80] = "tex_makeTexturePacket:\245\306\245\257\245\271\245\301\245\343\244\316\245\346\241\274\245\266\241\274\245\271\245\332\241\274\245\271\245\325\245\251\241\274\245\336\245\303\245\310\244\254\260\333\276\357\244\307\244\271.'%s'\n";
const char D_00556430[56] = "\033[31m\245\321\245\271\244\316\260\343\244\246\306\261\314\276\244\316\245\306\245\257\245\271\245\301\245\343\244\362\306\311\244\337\271\376\244\342\244\246\244\310\244\267\244\336\244\267\244\277.\n";
const char D_00556478[64] = "\245\306\245\257\245\271\245\301\245\343\244\254\302\277\244\271\244\256\244\336\244\271.\245\306\245\257\245\271\245\301\245\343\245\352\245\271\245\310\316\316\260\350\244\362\301\375\244\344\244\267\244\306\244\257\244\300\244\265\244\244\n";
const char D_005564B8[40] = "\245\306\245\257\245\271\245\301\245\343 \"%s\" \244\254\244\337\244\304\244\253\244\352\244\336\244\273\244\363.\n";
const char D_00556510[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d\n";
const char D_00556548[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d:%s\n";
extern void func_001FBAA8(int a0, int a1, int a2);
extern void func_001FB8B8(void);
extern void func_0012CEF8(void);
void func_0012BBE8(int a0);
extern unsigned int D_00276268[];
extern const char D_00556088[];
extern const char D_00631DD8[];
void func_0012C050(unsigned char *, unsigned char *);
void func_0012C3D0(unsigned char *a0, unsigned char *a1)
{
  int row;
  int slot13;
  for (row = 0; row < 7; row++)
  {
    int col;
    for (col = 12; col >= 0; col--)
    {
      *((short *) ((((a1 + (row * 0x24)) + 0x10C) + 0x18) - (col * 2))) = 0;
    }

  }

  *((short *) (a1 + 0xE8)) = 0;
  {
    int col;
    for (col = 12; col >= 0; col--)
    {
      *((short *) (((a1 + 0xEC) + 0x18) - (col * 2))) = 0;
    }

  }
  slot13 = a0[0x13];
  if (slot13 == 0)
  {
    return;
  }
  if (slot13 < 4)
  {
  }
  else
    if (slot13 < 6)
  {
    func_0012C050(a0, a1);
  }
  else
  {
    func_001A6E28(D_00556088, a1, a0[0x12], *((int *) (a1 + 0x108)), *((int *) (a1 + 0xE4)), a1);
    func_001AD768("src/Texture.c", 0x443);
    func_00263FF0("src/Texture.c", D_00631DD8, 0x443);
  }
  func_0012C050(a0, a1);
}

int func_0012FCE0(int a0);
void func_0012FD30(void);
