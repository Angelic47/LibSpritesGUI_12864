#ifndef __SPRITESGUI_TYPES__
#define __SPRITESGUI_TYPES__

#ifdef __cplusplus
extern "C" {
#endif

// SpritesGUI �������ݽṹ����

// ������������(��λ: �������)
#define SPGUI_MARCO_NAMEDTABLE_X 16
#define SPGUI_MARCO_NAMEDTABLE_Y 8

// ����Ԫ�ظ���
#define SPGUI_MARCO_MAXSPRITE 256

typedef unsigned short SPGUI_UINT16;
typedef unsigned long SPGUI_UINT32;
typedef unsigned char SPGUI_UINT8;
typedef unsigned char SPGUI_BYTE;
typedef void SPGUI_VOID;

typedef SPGUI_UINT8 SPGUI_SPRITEID;

typedef SPGUI_UINT8 SPGUI_LAYER_MODE;
#define SPGUI_LAYER_MODE_LANDSCAPE 0
#define SPGUI_LAYER_MODE_PORTRAIT 1

typedef SPGUI_UINT8 SPGUI_POSITIONX;
typedef SPGUI_UINT8 SPGUI_POSITIONY;

// ����ͼ��, 8 * 8
// ������ȡģ, 1byteΪ����8����, һ��8bytes
typedef struct _SPGUI_SPRITE
{
	SPGUI_UINT8 data[8];
} SPGUI_SPRITE, *PSPGUI_SPRITE;

// ��������ݽṹ
typedef struct _SPGUI_SPRITES_LIST
{
	SPGUI_SPRITE sprites[SPGUI_MARCO_MAXSPRITE];
} SPGUI_SPRITES_LIST, *PSPGUI_SPRITES_LIST;

// �������������ݽṹ
typedef union _SPGUI_NAMED_TABLE
{
	SPGUI_SPRITEID sprites_landscape[SPGUI_MARCO_NAMEDTABLE_X * 2][SPGUI_MARCO_NAMEDTABLE_Y];
	SPGUI_SPRITEID sprites_portrait[SPGUI_MARCO_NAMEDTABLE_X][SPGUI_MARCO_NAMEDTABLE_Y * 2];
} SPGUI_NAMED_TABLE, *PSPGUI_NAMED_TABLE;

// ����ͼ���ײ�ṹ, �ײ�û��͸����
typedef struct _SPGUI_LAYER_FIRST
{
	SPGUI_NAMED_TABLE main;
	SPGUI_LAYER_MODE mode;
	SPGUI_POSITIONX posx;
	SPGUI_POSITIONY posy;
} SPGUI_LAYER_FIRST, * PSPGUI_LAYER_FIRST;


// ����ͼ��ṹ, ÿ��ͼ��������������
typedef struct _SPGUI_LAYER
{
	SPGUI_LAYER_FIRST basiclayer;
	SPGUI_NAMED_TABLE alpha;
} SPGUI_LAYER, * PSPGUI_LAYER;

#ifdef __cplusplus
}
#endif

#endif
