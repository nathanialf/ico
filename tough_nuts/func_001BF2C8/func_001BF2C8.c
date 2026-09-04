
const char D_006186A0[16] = "src/box.c";
const char D_00618818[16] = "b_mantle";
const char D_00618828[16] = "tape_boro";
const char D_00618640[40] = "height: %f   dist: %f  ofs: %f %x \n";
const char D_006186B0[24] = "front pos: %f, %f, %f\n";
const char D_006186C8[24] = "rear  pos: %f, %f, %f\n";
const char D_00618708[24] = "box die!!!\n";
const char D_00618740[32] = "near wall to %f, %f, %f\n";
const char D_00618760[16] = "BOXREINIT\n";
const char D_00618808[16] = "%f, %f, %f\n";
const char D_00618668[56] = "\244\263\244\316\303\317\267\301\244\317\244\252\244\253\244\267\244\244\244\307\244\271(100cm\244\313\266\350\300\332\244\351\244\354\244\306\244\244\244\336\244\273\244\363)\n";
const char D_00618770[120] = "\033[36m\310\242\244\254\303\317\314\314\244\316\314\265\244\244\244\310\244\263\244\355\244\313\275\351\264\374\307\333\303\326\244\265\244\354\244\306\244\244\244\336\244\271\241\243\n\306\260\272\356\244\254\312\335\276\332\244\307\244\255\244\336\244\273\244\363(\245\263\245\352\245\270\245\347\245\363\304\352\265\301\244\350\244\352\301\260\244\313\310\242\244\254\244\242\244\352\244\336\244\273\244\363\244\253?)\033[m\n";
const char D_006187E8[16] = "\310\242\275\351\264\374\277\345\304\354\307\333\303\326\n";
const char D_006187F8[16] = "\310\242\275\351\264\374\304\314\276\357\307\333\303\326\n";
extern float D_00631168;
void func_00104508(void *buf, void *self);
void func_00105F00(void *dst, void *src);
int func_001684C8(void *struct_arg);
void func_00103C48(void *arg, void *self, int flag, float v, float maxv, float scale, float zero);
void func_00102858(void *arg);
void func_001BE558(int arg, int *self);
int func_001BF148(void *self, int code);
void func_001BD138(void *self);
void func_001BEF58(void *self);
int func_001BE120(void *self);
void func_001BE6A8(void *self);
void func_001A6E28(const char *fmt, ...);
void memset(int p, int q, int r);
void _ApplyMatrix(void *a, int b, void *c);
void func_0010D838(void *self, void *p);
void func_00102870(void *self, void *p);
extern float D_0063118C;
void func_001BF2C8(int *self)
{
  int local[4];
  int *sub = (int *) ((int *) self[0x15C / 4])[0x800 / 4];
  register int state asm("$5");
  state = sub[0x20 / 4];
  if (((unsigned) (state + 1)) >= 8)
  {
    goto default_case;
  }
  switch (state + 1)
  {
    case 0:
      goto default_case;

    case 1:
    {
      register int *q asm("$4");
      register int *p15c asm("$2");
      if (sub[0x58 / 4] == 0)
      {
        goto end_no_reload;
      }
      func_001BF148(self, 6);
      p15c = (int *) self[0x15C / 4];
      q = (int *) p15c[0x800 / 4];
      if (q[0x11C / 4] == 0)
      {
        goto skip_body;
      }
      {
        float v = ((*((float *) (((char *) q) + 0x48))) * D_0063118C) / (*((float *) (((char *) q) + 0x124)));
        *((short *) (((char *) q) + 0x120)) = (short) ((int) (((float) (*((short *) (((char *) q) + 0x120)))) - v));
 do { } while (0);
      }
      skip_body:
      q = local;

      memset((int) q, 0, 0x10);
      *((float *) (((char *) local) + 0x8)) = 1.0f;
      {
        int *p15c = (int *) self[0x15C / 4];
        _ApplyMatrix(((char *) p15c) + 0x520, p15c[0xC / 4], local);
      }
      goto end_reload;
    }

    case 2:

    case 7:
      func_001BD138(self);
      goto end_reload;

    case 3:

    case 4:
      func_001BEF58(self);
      goto end_reload;

    case 5:
      if (func_001BE120(self) != 0)
    {
      ((int *) ((int *) self[0x15C / 4])[0x800 / 4])[0x20 / 4] = 0;
      func_0010D838(self, ((char *) ((int *) self[0x15C / 4])) + 0x60);
      func_00102870(self, local);
      ((int *) self[0x15C / 4])[0x78 / 4] = 1;
    }
      goto end_reload;

    case 6:
      func_001BE6A8(self);
      goto end_reload;

  }

  default_case:
  func_001A6E28(D_00618708);

  end_reload:
  state = sub[0x20 / 4];

  end_no_reload:
  if (state != 6)
  {
    int *p180 = (int *) sub[0x180 / 4];
    if (p180[0x16C / 4] != 0)
    {
      p180[0x16C / 4] = 0;
    }
  }

}
