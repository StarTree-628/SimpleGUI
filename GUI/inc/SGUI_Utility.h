#ifndef __INCLUDE_GUI_UTILITY_H__
#define __INCLUDE_GUI_UTILITY_H__

//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Common.h"

//=======================================================================//
//= User Macro definition.												=//
//=======================================================================//
// Character Utilities
#define		SGUI_ISDIGIT(C)							(((C>='0')&&(C<='9'))?true:false)
#define		SGUI_ISALPHA(C)							((((C>='A')&&(C<='Z'))||((C>='a')&&(C<='z')))?true:false)
#define		SGUI_ISHEXDIGIT(C)						((((C>='A')&&(C<='F'))||((C>='a')&&(C<='f'))||((C>='0')&&(C<='9')))?true:false)
#define		SGUI_ISUPPER(C)							(((C>='A')&&(C<='Z'))?true:false)
#define		SGUI_TOUPPER(C)							(SGUI_ISUPPER(C)?(C):(C-32))
// Variable Utilities
#define		SGUI_SWAP(A, B)							{A=A^B; B=A^B; A=A^B;}
#define		SGUI_MAXCOLOR(D)						(1<<(D))-1
#define		SGUI_MAX_OF(A, B)						(A>B?A:B)
#define		SGUI_MIN_OF(A, B)						(A<B?A:B)
#define		LAYOUT(POBJ)							((POBJ)->stParam.stLayout)
// Curve Utilities
#define		RANGE_SIZE(RANGE)						((RANGE).iMax-(RANGE).iMin+1)
// Rectangle Utilities
#define 	RECT_X_START(ST)						((ST).iX)
#define 	RECT_X_END(RECT)						(((RECT).iX + (RECT).iWidth - 1))
#define 	RECT_Y_START(ST)						((ST).iY)
#define 	RECT_Y_END(RECT)						(((RECT).iY + (RECT).iHeight - 1))
#define 	RECT_WIDTH(ST)							((ST).iWidth)
#define 	RECT_HEIGHT(ST)							((ST).iHeight)
#define 	RECT_VALID_WIDTH(DATA, POS)				((RECT_X_START(POS)>0)?RECT_WIDTH(DATA):(RECT_WIDTH(DATA)+RECT_X_START(POS)))
#define		RECT_VALID_HEIGHT(DATA, POS)			((RECT_Y_START(POS)>0)?RECT_HEIGHT(DATA):(RECT_HEIGHT(DATA)+RECT_Y_START(POS)))
// Bitmap Utilities
#define	SGUI_BMP_RESOURCE_DECLARE(NAME)						extern const SGUI_BMP_RES NAME
#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
#define	SGUI_BMP_RESOURCE_DEFINE(NAME, W, H, D, FGP, ...)	const SGUI_BYTE NAME##DATA[] = {__VA_ARGS__};\
															const SGUI_BMP_RES NAME = {W, H, D, FGP, NAME##DATA}
#else
#define	SGUI_BMP_RESOURCE_DEFINE(NAME, W, H, FGP, ...)		const SGUI_BYTE NAME##DATA[] = {__VA_ARGS__};\
															const SGUI_BMP_RES NAME = {W, H, FGP, NAME##DATA}
#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
// Font Utilities
#define SGUI_FONT(NAME)									 SGUI_FONT_##NAME
#define SGUI_FONT_REF(NAME)								 &SGUI_FONT(NAME)
#define SGUI_FONT_RESOURCE_DECLARE(NAME)					extern const SGUI_FONT_RES SGUI_FONT(NAME)

#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	#define SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(NAME,WIDTH,HEIGHT,DEPTH,BLOCKSIZE,DECODER,INDEXMAPPER,SCANMODE,...) \
		static void SGUI_Resource_GetBitmap_##NAME(SGUI_BMP_RES* pBitmapData,SGUI_UINT32 uiCode,SGUI_BOOL bDryRun);\
		const SGUI_BYTE	 DATA_##NAME[]={__VA_ARGS__};\
		const SGUI_FONT_RES SGUI_FONT_##NAME={HEIGHT,DEPTH,SGUI_Resource_GetBitmap_##NAME,DECODER};\
		static void SGUI_Resource_GetBitmap_##NAME(SGUI_BMP_RES* pBitmapData,SGUI_UINT32 uiCode,SGUI_BOOL bDryRun)\
		{\
			SGUI_INT iCharIndex = INDEXMAPPER(uiCode);\
			if(NULL != pBitmapData) {\
				pBitmapData->iHeight	 = SGUI_FONT_##NAME.iHeight;\
				pBitmapData->iWidth	  = WIDTH;\
				pBitmapData->uiDepthBits = SGUI_FONT_##NAME.uiDepthBits;\
				if(!bDryRun) {\
					pBitmapData->fnGetPixel = SCANMODE;\
					pBitmapData->pData	  = DATA_##NAME + iCharIndex*BLOCKSIZE;\
				}\
			}\
		}
#else
	#define SGUI_INTERNAL_MONOSPACE_FONT_RESOURCE_DEFINE(NAME,WIDTH,HEIGHT,BLOCKSIZE,DECODER,INDEXMAPPER,SCANMODE,...) \
		static void SGUI_Resource_GetBitmap_##NAME(SGUI_BMP_RES* pBitmapData,SGUI_UINT32 uiCode,SGUI_BOOL bDryRun);\
		const SGUI_BYTE	 DATA_##NAME[]={__VA_ARGS__};\
		const SGUI_FONT_RES SGUI_FONT_##NAME={HEIGHT,SGUI_Resource_GetBitmap_##NAME,DECODER};\
		static void SGUI_Resource_GetBitmap_##NAME(SGUI_BMP_RES* pBitmapData,SGUI_UINT32 uiCode,SGUI_BOOL bDryRun)\
		{\
			SGUI_INT iCharIndex = INDEXMAPPER(uiCode);\
			if(NULL != pBitmapData) {\
				pBitmapData->iHeight	 = SGUI_FONT_##NAME.iHeight;\
				pBitmapData->iWidth	  = WIDTH;\
				if(!bDryRun) {\
					pBitmapData->fnGetPixel = SCANMODE;\
					pBitmapData->pData	  = DATA_##NAME + iCharIndex*BLOCKSIZE;\
				}\
			}\
	}
#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED

//=======================================================================//
//= Public function declaration.										=//
//=======================================================================//
void					SGUI_Common_AdaptDisplayInfo(SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos);
SGUI_INT				SGUI_Common_IntegerToStringWithDecimalPoint(SGUI_INT iInteger, SGUI_INT iDecimalPlaces, SGUI_SZSTR pszStringBuffer, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_SIZE			   SGUI_Common_IntegerToString(SGUI_INT iInteger, SGUI_SZSTR pszStringBuffer, SGUI_UINT uiBase, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_UINT			   SGUI_Common_ConvertStringToUnsignedInteger(SGUI_SZSTR szString, SGUI_CHAR** ppcEndPointer, SGUI_UINT uiBase);
SGUI_INT				SGUI_Common_ConvertStringToInteger(SGUI_SZSTR szString, SGUI_CHAR** ppcEndPointer, SGUI_UINT uiBase);

#endif // __INCLUDE_GUI_UTILITY_H__
