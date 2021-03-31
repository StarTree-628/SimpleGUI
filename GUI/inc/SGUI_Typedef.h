#ifndef _INCLUDE_GUI_TYPEDEF_H_
#define _INCLUDE_GUI_TYPEDEF_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "stdint.h"
#include "stddef.h"
#include <stdbool.h>
#include <SGUI_Config.h>
//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		SGUI_DEVPF_IF_DEFINE(R, FN, PARAM)		typedef R(*FN)PARAM

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef char							SGUI_INT8;
typedef	unsigned char					SGUI_UINT8;
typedef int16_t							SGUI_INT16;
typedef uint16_t						SGUI_UINT16;
typedef int32_t							SGUI_INT32;
typedef	uint32_t						SGUI_UINT32;

typedef	int								SGUI_INT;
typedef unsigned int					SGUI_UINT;
typedef long							SGUI_LONG;
typedef unsigned long					SGUI_ULONG;
typedef unsigned char					SGUI_BYTE;
typedef const unsigned char				SGUI_CBYTE;
typedef size_t							SGUI_SIZE;

typedef char*							SGUI_SZSTR;
typedef const char*						SGUI_CSZSTR;
typedef char							SGUI_CHAR;
typedef const char						SGUI_CCHAR;

typedef void*							SGUI_PTR;

#define	SGUI_INVALID_INDEX				(-1)
typedef	SGUI_UINT32						SGUI_ROM_ADDRESS;

#define	SGUI_BOOL						SGUI_INT
#define SGUI_FALSE						(0)
#define SGUI_TRUE						(!SGUI_FALSE)

#define SGUI_COLOR_TRANS                (-1)
/******
 * Deprecated!
 * Prepared to delete this guy!
 * DO NOT USE THIS MACRO ANY MORE!
 */
#define SGUI_COLOR_FRGCLR               (0x0A)
#define SGUI_COLOR_BKGCLR               (0)

typedef struct
{
	SGUI_INT							iX;
	SGUI_INT							iY;
	SGUI_INT							iWidth;
	SGUI_INT							iHeight;
}SGUI_RECT;

typedef struct
{
	SGUI_INT							iWidth;
	SGUI_INT							iHeight;
}SGUI_AREA_SIZE;

typedef struct
{
	SGUI_INT							iX;
	SGUI_INT							iY;
}SGUI_POINT;

typedef struct
{
	SGUI_INT							iMin;
	SGUI_INT							iMax;
}SGUI_RANGE;

typedef SGUI_INT8 SGUI_COLOR ;

typedef enum
{
	SGUI_DRAW_NORMAL =					0,
	SGUI_DRAW_REVERSE =					1,
}SGUI_DRAW_MODE;

typedef enum
{
	SGUI_RIGHT =						0,
	SGUI_CENTER,
	SGUI_LEFT,
}SGUI_ALIG_MODE;

// Palette color value, 16Bit for RGB555 or RGB565.
typedef SGUI_UINT16                     SGUI_PALETTE_COLOUR;
// Palette color value, 16Bit for RGB888.
//typedef SGUI_UINT32                     SGUI_PALETTE_COLOUR;

// Screen device operation interface type declare.
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_INITIALIZE,				(void));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_CLEAR,					(void));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_SET_POINT,				(SGUI_INT iX, SGUI_INT iY, SGUI_COLOR iColor));
SGUI_DEVPF_IF_DEFINE(SGUI_COLOR,		SGUI_FN_IF_GET_POINT,				(SGUI_INT iX, SGUI_INT iY));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_SET_BYTE,				(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_GET_BYTE,				(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_REFRESH,					(void));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_SET_PALETTE,             (SGUI_PALETTE_COLOUR, SGUI_PALETTE_COLOUR, SGUI_PALETTE_COLOUR));

// System function interface type declare.
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_GET_RTC,					(SGUI_INT iYear, SGUI_INT iMounth, SGUI_INT iDay, SGUI_INT iWeekDay, SGUI_INT iHour, SGUI_INT iMinute, SGUI_INT iSecond));

typedef struct
{
	//Screen display area size in pixel.
	SGUI_AREA_SIZE						stSize;
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	// Screen display pixel depth in bit count(eg. 4(bits) means 16 grayscale)
    SGUI_UINT8                          uiDepthBits;
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    #if SGUI_CONF_BMP_DATA_BUFFER_SIZE>0
	//Bitmap data buffer.
	SGUI_BYTE							arrBmpDataBuffer[SGUI_CONF_BMP_DATA_BUFFER_SIZE];
	#endif // SGUI_CONF_BMP_DATA_BUFFER_SIZE
    //Engine & device initialize function.
    SGUI_FN_IF_INITIALIZE				fnInitialize;
    //Clear screen function.
    SGUI_FN_IF_CLEAR					fnClear;
    //Set pixel value function.
    SGUI_FN_IF_SET_POINT				fnSetPixel;
    //Get pixel value function.
    SGUI_FN_IF_GET_POINT				fnGetPixel;
    // Sync display buffer data to screen device.
    SGUI_FN_IF_REFRESH					fnSyncBuffer;
    // Set palette function.
    SGUI_FN_IF_SET_PALETTE			    fnSetPalette;
}SGUI_SCR_DEV;
// Bitmap operation Interface type declare
struct _bmp_res;
SGUI_DEVPF_IF_DEFINE(SGUI_COLOR,        SGUI_FN_IF_BMP_GET_PIXEL,   (const struct _bmp_res* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY));
typedef struct _bmp_res
{
	SGUI_INT							iWidth;
    SGUI_INT							iHeight;
    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    SGUI_UINT8                          uiDepthBits;
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    SGUI_FN_IF_BMP_GET_PIXEL            fnGetPixel;
    //SGUI_COLOR                          (*fnGetPixel)(const struct _bmp_res* pstBitmapData,SGUI_UINT8 uiX,SGUI_UINT8 uiY);
    const SGUI_BYTE*					pData;
}SGUI_BMP_RES;

// Font operation Interface type declare
struct _font_res;
SGUI_DEVPF_IF_DEFINE(SGUI_CSZSTR,       SGUI_FN_IF_STEP_NEXT,               (SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode));
SGUI_DEVPF_IF_DEFINE(void,              SGUI_FN_IF_GET_BITMAP,              (SGUI_BMP_RES* pBitmapData,SGUI_UINT32 uiCode,SGUI_BOOL bDryRun));

typedef struct _font_res
{
    SGUI_INT							iHeight;
    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    SGUI_UINT8                          uiDepthBits;
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_FN_IF_GET_BITMAP               fnGetBitmap;
	SGUI_FN_IF_STEP_NEXT                fnStepNext;
}SGUI_FONT_RES;


#endif // _INCLUDE_GUI_TYPEDEF_H_
