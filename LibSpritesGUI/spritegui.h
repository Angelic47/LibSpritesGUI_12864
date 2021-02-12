#ifndef __SPRITESGUI__
#define __SPRITESGUI__

#include "spritesgui_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union _SPGUI_RENDERBUFFER
{
	SPGUI_UINT8 data[2];
	SPGUI_UINT16 buffer;
} SPGUI_RENDERBUFFER, * PSPGUI_RENDERBUFFER;

extern SPGUI_LAYER_FIRST spgui_firstLayer;
extern SPGUI_LAYER spgui_layer[4];

SPGUI_VOID spgui_portable_outputData(SPGUI_BYTE data);

SPGUI_VOID spgui_render();
SPGUI_VOID spgui_set_sprite(SPGUI_UINT8 id, PSPGUI_SPRITE sprite);
SPGUI_VOID spgui_set_layer_sprite(PSPGUI_LAYER_FIRST layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id);
SPGUI_VOID spgui_set_layer_alpha(PSPGUI_LAYER layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id);
SPGUI_VOID spgui_set_layer_sprite_and_alpha(PSPGUI_LAYER layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id);
SPGUI_VOID spgui_set_layer_mode(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE mode);
SPGUI_VOID spgui_set_layer_offset_x(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE x);
SPGUI_VOID spgui_set_layer_offset_y(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE y);

#ifdef __cplusplus
}
#endif

#endif
