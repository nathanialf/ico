/*
 * sce/libsndn2/sound.h  (derived name: named after the member, sound.o)
 *
 * The declarations sound.c needs ahead of their definitions: the Sg reverb
 * entry points the parameter controller calls, the _Sg DMA helper and the
 * fake-body vab opener.  Each prototype is the signature of its definition
 * in sound.c, which includes this header.
 */
#ifndef SCE_LIBSNDN2_SOUND_H
#define SCE_LIBSNDN2_SOUND_H

void SgSetReverbType(int a0, int a1);
void SgSetReverbDepth(int a0, int a1, int a2);
void SgSetReverbDelaytime(int a0, int a1);
void SgSetReverbFeedback(int a0, int a1);
void _SgDmaCommon(int cmd, int a1, void *a2, void *a3);
int SgVabOpenFakeBody(int *a0, int a1);

#endif /* SCE_LIBSNDN2_SOUND_H */
