#include "spritesgui_types.h"
#include "spritegui.h"

SPGUI_LAYER_FIRST spgui_firstLayer;
SPGUI_LAYER spgui_layer[4];

SPGUI_SPRITES_LIST spgui_spriteList;

/*
SPGUI_BYTE spgui_get_byte(PSPGUI_LAYER_FIRST layer, SPGUI_UINT8 x, SPGUI_UINT8 ydiv8)
{
	SPGUI_UINT8 spritesid;
	SPGUI_UINT8 ydelta;
	SPGUI_UINT8 xdelta;
	SPGUI_UINT8 ypos;
	SPGUI_RENDERBUFFER buffer;
	switch (layer->mode)
	{
	case SPGUI_LAYER_MODE_LANDSCAPE:
		x += layer->posx;
		xdelta = x & 0x07;
		x = x >> 3;
		spritesid = layer->main.sprites_landscape[x][ydiv8];
		return spgui_spriteList.sprites[spritesid].data[xdelta];
	case SPGUI_LAYER_MODE_PORTRAIT:
		xdelta = x & 0x07;
		x = x >> 3;
		ypos = ydiv8 * 8 + layer->posy;
		ydelta = ypos & 0x07;
		ypos = ypos >> 3;
		spritesid = layer->main.sprites_portrait[x][ypos & 0xf];
		buffer.data[0] = spgui_spriteList.sprites[spritesid].data[xdelta];
		ypos += 1;
		spritesid = layer->main.sprites_portrait[x][ypos & 0xf];
		buffer.data[1] = spgui_spriteList.sprites[spritesid].data[xdelta];
		buffer.buffer >>= ydelta;
		return buffer.data[0];
	default:
		// shouldn't be happen
		return 0;
	}
}

SPGUI_BYTE spgui_get_alpha(PSPGUI_LAYER layer, SPGUI_UINT8 x, SPGUI_UINT8 ydiv8)
{
	SPGUI_UINT8 spritesid;
	SPGUI_UINT8 ydelta;
	SPGUI_UINT8 xdelta;
	SPGUI_UINT8 ypos;
	SPGUI_RENDERBUFFER buffer;
	switch (layer->basiclayer.mode)
	{
	case SPGUI_LAYER_MODE_LANDSCAPE:
		x += layer->basiclayer.posx;
		xdelta = x & 0x07;
		x = x >> 3;
		spritesid = layer->alpha.sprites_landscape[x][ydiv8];
		return spgui_spriteList.sprites[spritesid].data[xdelta];
	case SPGUI_LAYER_MODE_PORTRAIT:
		xdelta = x & 0x07;
		x = x >> 3;
		ypos = ydiv8 * 8 + layer->basiclayer.posy;
		ydelta = ypos & 0x07;
		ypos = ypos >> 3;
		spritesid = layer->alpha.sprites_portrait[x][ypos & 0xf];
		buffer.data[0] = spgui_spriteList.sprites[spritesid].data[xdelta];
		ypos += 1;
		spritesid = layer->alpha.sprites_portrait[x][ypos & 0xf];
		buffer.data[1] = spgui_spriteList.sprites[spritesid].data[xdelta];
		buffer.buffer >>= ydelta;
		return buffer.data[0];
	default:
		// shouldn't be happen
		return 0;
	}
}

SPGUI_VOID spgui_render()
{
	SPGUI_BYTE renderByteResult;

	SPGUI_BYTE renderingByte;
	SPGUI_BYTE renderingAlpha;

	SPGUI_UINT8 x, ydiv8, layer;

	for (ydiv8 = 0; ydiv8 < 8; ydiv8++)
	{
		for (x = 0; x < 128; x++)
		{
			renderByteResult = spgui_get_byte(&spgui_firstLayer, x, ydiv8);

			for (layer = 0; layer < 4; layer++)
			{
				renderingByte = spgui_get_byte(&(spgui_layer[layer]), x, ydiv8);
				renderingAlpha = spgui_get_alpha(&(spgui_layer[layer]), x, ydiv8);
				renderByteResult = (renderingByte & renderingAlpha) | (~renderingAlpha & renderByteResult);
			}

			spgui_portable_outputData(renderByteResult);
		}
	}
}
*/

SPGUI_VOID spgui_set_sprite(SPGUI_UINT8 id, PSPGUI_SPRITE sprite)
{
	SPGUI_UINT8 i;
	for (i = 0; i < 8; i++)
		spgui_spriteList.sprites[id].data[i] = sprite->data[i];
}

SPGUI_VOID spgui_set_layer_sprite(PSPGUI_LAYER_FIRST layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id)
{
	switch (layer->mode)
	{
	case SPGUI_LAYER_MODE_LANDSCAPE:
		layer->main.sprites_landscape[x][y] = id;
		break;
	case SPGUI_LAYER_MODE_PORTRAIT:
		layer->main.sprites_portrait[x][y] = id;
		break;
	default:
		break;
	}
}

SPGUI_VOID spgui_set_layer_alpha(PSPGUI_LAYER layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id)
{
	switch (layer->basiclayer.mode)
	{
	case SPGUI_LAYER_MODE_LANDSCAPE:
		layer->alpha.sprites_landscape[x][y] = id;
		break;
	case SPGUI_LAYER_MODE_PORTRAIT:
		layer->alpha.sprites_portrait[x][y] = id;
		break;
	default:
		break;
	}
}

SPGUI_VOID spgui_set_layer_sprite_and_alpha(PSPGUI_LAYER layer, SPGUI_UINT8 x, SPGUI_UINT8 y, SPGUI_UINT8 id)
{
	spgui_set_layer_sprite(layer, x, y, id);
	spgui_set_layer_alpha(layer, x, y, id);
}

SPGUI_VOID spgui_set_layer_mode(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE mode)
{
	layer->mode = mode;
}

SPGUI_VOID spgui_set_layer_offset_x(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE x)
{
	layer->posx = x;
}

SPGUI_VOID spgui_set_layer_offset_y(PSPGUI_LAYER_FIRST layer, SPGUI_LAYER_MODE y)
{
	layer->posy = y;
}
