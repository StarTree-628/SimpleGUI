#ifndef _INCLUDE_GUI_FONT_H_
#define _INCLUDE_GUI_FONT_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define FONT_LIB_ADDR					0X00000
// Max font size is 64 pix, maximum of font data size is 64 * 8 = 512 Bytes.
#define TEXT_NUMBER_STR_LENGTH_MAX		(12)
#define TEXT_PLACEHOLDER_CHARACTER		('*')
#define SGUI_IS_VISIBLE_CHAR(C)			((C>0x1F) && (C<0x7F))

#define SGUI_TEXT_DECODER_ASCII         SGUI_Text_StepNext_ASCII
#define SGUI_TEXT_DECODER_GB2312        SGUI_Text_StepNext_GB2312
#define SGUI_TEXT_DECODER_UTF8          SGUI_Text_StepNext_UTF8

#define SGUI_TEXT_INDEXMAPPER_DIRECT    SGUI_Text_IndexMapper_Direct

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern SGUI_CSZSTR		SGUI_EMPTY_STRING;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			SGUI_Text_GetTextExtent(SGUI_CSZSTR cszTextBuffer, const SGUI_FONT_RES* pstFontRes, SGUI_AREA_SIZE* pstTextExtent);
void			SGUI_Text_DrawText(SGUI_SCR_DEV* pstDeviceIF, SGUI_CSZSTR cszTextBuffer, const SGUI_FONT_RES* pstFontRes, SGUI_RECT* pstDisplayArea, SGUI_POINT* pstInnerPos, SGUI_COLOR eFontColor);
SGUI_SIZE		SGUI_Text_DrawMultipleLinesText(SGUI_SCR_DEV* pstDeviceIF, SGUI_CSZSTR szTextBuffer, const SGUI_FONT_RES* pstFontRes, SGUI_RECT* pstDisplayArea, SGUI_INT iTopOffset, SGUI_COLOR eFontColor);
SGUI_SIZE		SGUI_Text_GetMultiLineTextLines(SGUI_CSZSTR cszText, const SGUI_FONT_RES* pstFontRes, SGUI_SIZE uiDisplayAreaWidth);
SGUI_SIZE       SGUI_Text_StringLength(SGUI_CSZSTR cszText,const SGUI_FONT_RES* pstFontRes);
SGUI_CSZSTR     SGUI_Text_StepNext_ASCII(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode);
SGUI_CSZSTR     SGUI_Text_StepNext_GB2312(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode);
SGUI_CSZSTR     SGUI_Text_StepNext_UTF8(SGUI_CSZSTR cszSrc, SGUI_UINT32* puiCode);
SGUI_UINT32     SGUI_Text_IndexMapper_Direct(SGUI_UINT32 uiCode);

#endif
