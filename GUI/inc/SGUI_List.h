#ifndef __INCLUDE_SGUI_List_H__
#define __INCLUDE_SGUI_List_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
#include "SGUI_ScrollBar.h"
#include "SGUI_ItemsBase.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct
{
    SGUI_UINT8                  uiDepthBits;
    SGUI_ITEMS_BASE_PALETTE     stItemBase;
    SGUI_SCROLLBAR_PALETTE      stScrollBar;
    SGUI_COLOR                  eBorderColor;
    SGUI_COLOR                  eBackgroundColor;
    SGUI_COLOR                  eTitleTextColor;
} SGUI_LIST_PALETTE;
typedef struct
{
	SGUI_RECT					stLayout;
	SGUI_ITEMS_BASE				stItems;
	SGUI_CSZSTR					szTitle;
	SGUI_SCROLLBAR_STRUCT		stScrollBar;
	const SGUI_FONT_RES*        pstFontRes;
	SGUI_LIST_PALETTE           stPallete;
}SGUI_LIST_STRUCT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			SGUI_List_Initialize(SGUI_LIST_STRUCT* pstObj, const SGUI_FONT_RES* pstFontRes, SGUI_ITEMS_ITEM* pstItemsData, SGUI_INT iItemsCount, SGUI_LIST_PALETTE* pstPallete);
void			SGUI_List_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_LIST_STRUCT* pstObj);

#endif // __INCLUDE_SGUI_List_H__
