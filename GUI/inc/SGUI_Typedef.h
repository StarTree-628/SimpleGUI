#ifndef __INCLUDE_GUI_TYPEDEF_H__
#define __INCLUDE_GUI_TYPEDEF_H__
//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
#include "stdint.h"
#include "stddef.h"
#include <stdbool.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define 	RECTANGLE_X_START(ST)			((ST).PosX)
#define 	RECTANGLE_X_END(ST)				(((ST).PosX + (ST).Width - 1))
#define 	RECTANGLE_Y_START(ST)			((ST).PosY)
#define 	RECTANGLE_Y_END(ST)				(((ST).PosY + (ST).Height - 1))
#define 	RECTANGLE_WIDTH(ST)				((ST).Width)
#define 	RECTANGLE_HEIGHT(ST)			((ST).Height)
#define 	RECTANGLE_VALID_WIDTH(ST)		((RECTANGLE_X_START(ST)>0)?RECTANGLE_WIDTH(ST):(RECTANGLE_WIDTH(ST)+RECTANGLE_X_START(ST)))
#define		RECTANGLE_VALID_HEIGHT(ST)		((RECTANGLE_Y_START(ST)>0)?RECTANGLE_HEIGHT(ST):(RECTANGLE_HEIGHT(ST)+RECTANGLE_Y_START(ST)))

#define SGUI_ENGINE_ACTION_DEF(R, FN, PARAM)	typedef R(*FN)PARAM

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
typedef unsigned char					SGUI_BYTE;
typedef const unsigned char				SGUI_CBYTE;
typedef size_t							SGUI_SIZE;

typedef char*							SGUI_SZSTR;
typedef const char*						SGUI_CSZSTR;
typedef char							SGUI_CHAR;
typedef const char						SGUI_CCHAR;

typedef void*							SGUI_PTR;

typedef SGUI_SIZE						SGUI_INDEX;
#define	SGUI_INVALID_INDEX				(-1)
typedef	SGUI_UINT32						SGUI_ROM_ADDRESS;

#define	SGUI_BOOL						SGUI_INT
#define SGUI_FALSE						(0)
#define SGUI_TRUE						(!SGUI_FALSE)

typedef struct
{
	SGUI_INT							PosX;
	SGUI_INT							PosY;
	SGUI_INT							Width;
	SGUI_INT							Height;
}SGUI_RECT_AREA;

typedef struct
{
	SGUI_INT							Width;
	SGUI_INT							Height;
}SGUI_AREA_SIZE;

typedef struct
{
	SGUI_INT							PosX;
	SGUI_INT							PosY;
}SGUI_POINT;

typedef struct
{
	SGUI_UINT16							Year;
	SGUI_UINT16							Month;
	SGUI_UINT16							Day;
	SGUI_UINT16							Hour;
	SGUI_UINT16							Minute;
	SGUI_UINT16							Second;
}SGUI_TIME;

typedef enum
{
	SGUI_COLOR_BKGCLR   = 0,
	SGUI_COLOR_FRGCLR   = 1,
	SGUI_COLOR_TRANS    = 2,
}SGUI_COLOR;

typedef enum
{
	SGUI_DRAW_NORMAL    = 0,
	SGUI_DRAW_REVERSE   = 1,
}SGUI_DRAW_MODE;

// Declare data source flag here.
typedef enum
{
	SGUI_FONT_SRC_NONE	= 0,
	SGUI_FONT_SRC_H6,
	SGUI_FONT_SRC_H8,
	SGUI_FONT_SRC_H12,
	SGUI_FONT_SRC_H16,
	//SGUI_FONT_SRC_H24,
	SGUI_FONT_SRC_H32,

	SGUI_NOTICE_ICON_16PIX,
	SGUI_NOTICE_ICON_24PIX,
	SGUI_FONT_SRC_UNKNOWN,
}SGUI_FLASH_DATA_SOURCE;

typedef struct
{
	SGUI_FLASH_DATA_SOURCE				Source;
	SGUI_ROM_ADDRESS					StartAddr;
	SGUI_SIZE							Length;
}SGUI_BMP_DATA;

SGUI_ENGINE_ACTION_DEF(SGUI_INT,	SGUI_ENGINE_ACTION_FN_INITIALIZE,	(void));
SGUI_ENGINE_ACTION_DEF(void,		SGUI_ENGINE_ACTION_FN_CLEAR,		(void));
SGUI_ENGINE_ACTION_DEF(void,		SGUI_ENGINE_ACTION_FN_SET_POINT,	(SGUI_INT iX, SGUI_INT iY, SGUI_INT iColor));
SGUI_ENGINE_ACTION_DEF(SGUI_INT,	SGUI_ENGINE_ACTION_FN_GET_POINT,	(SGUI_INT iX, SGUI_INT iY));
SGUI_ENGINE_ACTION_DEF(SGUI_INT,	SGUI_ENGINE_ACTION_FN_SET_BYTE,		(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_ENGINE_ACTION_DEF(SGUI_INT,	SGUI_ENGINE_ACTION_FN_GET_BYTE,		(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_ENGINE_ACTION_DEF(void,		SGUI_ENGINE_ACTION_FN_REFRESH,		(void));
SGUI_ENGINE_ACTION_DEF(void,		SGUI_ENGINE_ACTION_FN_GET_RTC,		(SGUI_INT iYear, SGUI_INT iMounth, SGUI_INT iDay, SGUI_INT iWeekDay, SGUI_INT iHour, SGUI_INT iMinute, SGUI_INT iSecond));
SGUI_ENGINE_ACTION_DEF(SGUI_PTR,	SGUI_ENGINE_ACTION_FN_HEAP_MEM,		(SGUI_SIZE sSize));
SGUI_ENGINE_ACTION_DEF(void,		SGUI_ENGINE_ACTION_FN_FREE_MEM,		(SGUI_PTR pMemory));
SGUI_ENGINE_ACTION_DEF(SGUI_PTR,	SGUI_ENGINE_ACTION_FN_SET_MEM,		(SGUI_PTR pHead, SGUI_INT iValue, SGUI_SIZE sSize));
SGUI_ENGINE_ACTION_DEF(SGUI_PTR,	SGUI_ENGINE_ACTION_FN_COPY_MEM,		(SGUI_PTR pSrc, SGUI_PTR pDest, SGUI_SIZE sSize));
SGUI_ENGINE_ACTION_DEF(SGUI_SIZE,	SGUI_ENGINE_ACTION_FN_READ_FLASH,	(SGUI_INT iSourceID, SGUI_ROM_ADDRESS adStartAddr, SGUI_SIZE sReadSize, SGUI_BYTE* pOutputBuffer));
SGUI_ENGINE_ACTION_DEF(SGUI_SZSTR,	SGUI_ENGINE_ACTION_FN_STR_CPY,		(SGUI_SZSTR szDest, SGUI_CSZSTR cszSource));
SGUI_ENGINE_ACTION_DEF(SGUI_SZSTR,	SGUI_ENGINE_ACTION_FN_STR_N_CPY,	(SGUI_SZSTR szDest, SGUI_CSZSTR cszSource, SGUI_SIZE sLength));

typedef struct
{
    //Engine & device initialize function.
	SGUI_ENGINE_ACTION_FN_INITIALIZE	fnInitialize;
    //Clear screen function.
	SGUI_ENGINE_ACTION_FN_CLEAR			fnClearScreen;
    //Set pixel value function.
    SGUI_ENGINE_ACTION_FN_SET_POINT		fnSetPixel;
    //Get pixel value function.
	SGUI_ENGINE_ACTION_FN_GET_POINT		fnGetPixel;
	// Refresh screen display.
	SGUI_ENGINE_ACTION_FN_REFRESH		fnRefreshScreen;
}SGUI_ENGINE_DEVICE_IF;

typedef struct
{
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
	// Allocate heap memory
	SGUI_ENGINE_ACTION_FN_HEAP_MEM		fnMalloc;
	// Free heap memory
	SGUI_ENGINE_ACTION_FN_FREE_MEM		fnFree;
#endif
	// Set memory block value.
	SGUI_ENGINE_ACTION_FN_SET_MEM		fnMemSet;
	// Copy memory bloc.
	SGUI_ENGINE_ACTION_FN_COPY_MEM		fnMemCpy;
	// Copy string.
	SGUI_ENGINE_ACTION_FN_STR_CPY		fnStrCpy;
	// Copy specified length string.
	SGUI_ENGINE_ACTION_FN_STR_N_CPY		fnStrNCpy;
	// Read data form flash(internal or external)
	SGUI_ENGINE_ACTION_FN_READ_FLASH	fnReadFlashData;

}SGUI_ENGINE_SYS_IF;

typedef struct
{
    //Simple GUI extern functions.
	SGUI_ENGINE_DEVICE_IF				stActions;
	// Simple GUI system functions.
	SGUI_ENGINE_SYS_IF					stSystemFunctions;
}SGUI_IF_OBJ;

#endif // __INCLUDE_GUI_TYPEDEF_H__
