/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Menu.c												**/
/** Author: Polarix														**/
/** Description: Menu component interface.								**/
/*************************************************************************/
//=======================================================================//
//= Include files.														=//
//=======================================================================//
#include "SGUI_Menu.h"

//=======================================================================//
//= User Macro definition.												=//
//=======================================================================//

//=======================================================================//
//= Static variable define.												=//
//=======================================================================//
static SGUI_BMP_RESOURCE_DEFINE(
	SGUI_MENU_ICON_MOVEUP,
	5, 3,
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	1,
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_BMP_SCAN_MODE_DHPV,
	0x04,0x06,0x07,0x06,0x04);
static SGUI_BMP_RESOURCE_DEFINE(
	SGUI_MENU_ICON_MOVEDOWN,
	5, 3,
	#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	1,
	#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
	SGUI_BMP_SCAN_MODE_DHPV,
	0x01,0x03,0x07,0x03,0x01);

//=======================================================================//
//= Function define.													=//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Menu_Initialize								**/
/** Purpose:		Initialize a menu structure data.					**/
/** Params:																**/
/**	@ pstObj[in]:	Pointer of menu data will be initialized.			**/
/** @ pstFontRes[in]: Font resource object pointer.						**/
/** @ pstItemsData[in]: List items data array.							**/
/** @ iItemsCount[in]: Number of list item data.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Menu_Initialize(SGUI_MENU* pstObj, const SGUI_RECT* cpstLayout, const SGUI_MENU_PALETTE_INIT_PARAM* cpstPaletteInit, const SGUI_FONT_RES* pstFontRes, SGUI_ITEMS_ITEM* pstItemsData, SGUI_INT iItemsCount)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT						sItemstLayout;
	SGUI_MENU_PALETTE_INIT_PARAM	stSubPalette;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstFontRes) && (NULL != cpstPaletteInit))
	{
		// Save layout.
		SGUI_SystemIF_MemoryCopy(&(pstObj->stLayout), cpstLayout, sizeof(SGUI_RECT));

		// Save Palette
		SGUI_SystemIF_MemoryCopy(&(stSubPalette),cpstPaletteInit,sizeof(SGUI_MENU_PALETTE_INIT_PARAM));
		#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
		stSubPalette.stItemBase.uiDepthBits	= stSubPalette.uiDepthBits;
		stSubPalette.stMenu.uiDepthBits		= stSubPalette.uiDepthBits;
		#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
		pstObj->stPalette = stSubPalette.stMenu;

		// Initialize member object pointer.
		pstObj->pstFontRes = pstFontRes;
		pstObj->stItems.pstFirstItem = NULL;
		sItemstLayout.iX = pstObj->stLayout.iX+1;
		sItemstLayout.iY = pstObj->stLayout.iY+SGUI_MENU_ICON_MOVEUP.iHeight+1;
		sItemstLayout.iWidth = pstObj->stLayout.iWidth-2;
		sItemstLayout.iHeight = pstObj->stLayout.iHeight-(SGUI_MENU_ICON_MOVEUP.iHeight+SGUI_MENU_ICON_MOVEDOWN.iHeight+2);
		SGUI_ItemsBase_Initialize(&(pstObj->stItems), &sItemstLayout, &(stSubPalette.stItemBase), pstObj->pstFontRes, pstItemsData, iItemsCount);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Menu_Repaint									**/
/** Purpose:		Refresh list display.								**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ pstObj[in]:	Pointer of menu structure will be refreshed.		**/
/** Return:			None.												**/
/** Notice:			This function will refresh all list display on		**/
/**					screen, include edge, items, title and scrollbar.	**/
/*************************************************************************/
void SGUI_Menu_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_MENU* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT				stIconArea;
	SGUI_POINT				stIconInnerPos;
	SGUI_MENU_PALETTE*	  pstPalette;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stIconInnerPos.iX =		0;
	stIconInnerPos.iY =		0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstObj)
	{
		pstPalette = &(pstObj->stPalette);
		#ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
		// Mapping Color
		if(pstPalette->uiDepthBits != pstDeviceIF->uiDepthBits){
			pstPalette->eBorder = SGUI_Basic_MapColor(pstPalette->uiDepthBits,pstPalette->eBorder,pstDeviceIF->uiDepthBits);
			pstPalette->uiDepthBits = pstDeviceIF->uiDepthBits;
		}
		#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED

		/* Clear list item display area. */
		SGUI_Basic_DrawRectangle(pstDeviceIF, pstObj->stLayout.iX, pstObj->stLayout.iY, pstObj->stLayout.iWidth, pstObj->stLayout.iHeight, pstPalette->eBorder, pstObj->stItems.stPalette.eBackgroundColor);
		// Paint items.
		//SGUI_ItemsBase_Resize(&(pstObj->stItems));
		SGUI_ItemsBase_Repaint(pstDeviceIF, &(pstObj->stItems));
		/* Paint arrow icon. */
		stIconArea.iWidth = 5;
		stIconArea.iHeight = 3;
		stIconArea.iX = pstObj->stLayout.iX+((pstObj->stLayout.iWidth-stIconArea.iWidth)/2);
		if(SGUI_Menu_CanScrollUp(pstObj))
		{
			stIconArea.iY = pstObj->stLayout.iY+1;
			SGUI_Basic_DrawAlphaBitMap(pstDeviceIF, &stIconArea, &stIconInnerPos, &SGUI_MENU_ICON_MOVEUP, pstPalette->eDirectionIconColor);
		}
		if(SGUI_Menu_CanScrollDown(pstObj))
		{
			stIconArea.iY = RECT_Y_END(pstObj->stItems.stLayout)+1;
			SGUI_Basic_DrawAlphaBitMap(pstDeviceIF, &stIconArea, &stIconInnerPos, &SGUI_MENU_ICON_MOVEDOWN, pstPalette->eDirectionIconColor);
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Menu_FitLayout									**/
/** Purpose:		Resize menu to best fit size order by position and	**/
/**					screen size.										**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ pstObj[in]:	Pointer of menu structure will be refreshed.		**/
/** Return:			None.												**/
/** Notice:			This function must called after initialize.			**/
/*************************************************************************/
void SGUI_Menu_Resize(SGUI_MENU* pstObj, const SGUI_RECT* cpstNewLayout)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT				stItemsLayout;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != cpstNewLayout))
	{
		pstObj->stLayout.iX = cpstNewLayout->iX;
		pstObj->stLayout.iY = cpstNewLayout->iY;
		pstObj->stLayout.iWidth = cpstNewLayout->iWidth;
		pstObj->stLayout.iHeight = cpstNewLayout->iHeight;
		stItemsLayout.iX = cpstNewLayout->iX+1;
		stItemsLayout.iY = cpstNewLayout->iY+SGUI_MENU_ICON_MOVEUP.iHeight+1;
		stItemsLayout.iWidth = cpstNewLayout->iWidth-2;
		stItemsLayout.iHeight = cpstNewLayout->iHeight-(SGUI_MENU_ICON_MOVEUP.iHeight+SGUI_MENU_ICON_MOVEDOWN.iHeight+2);
		SGUI_ItemsBase_Resize(&(pstObj->stItems), &stItemsLayout);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Menu_PopupSubMenu								**/
/** Purpose:		Resize menu to best fit size order by position and	**/
/**					screen size.										**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ pstObj[in]:	Pointer of menu structure will be refreshed.		**/
/**	@ cpstParentItemLayout[in]:	Pointer of parent menu item, sub menu	**/
/** 				layout will update order by parent item layout.		**/
/** Return:			None.												**/
/** Notice:			For 		**/
/**					screen, include edge, items, title and scrollbar.	**/
/*************************************************************************/
void SGUI_Menu_PopupSubMenu(SGUI_SCR_DEV* pstDeviceIF, SGUI_MENU* pstObj, const SGUI_RECT* cpstParentItemLayout)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT				iFullHeight;
	SGUI_INT				iVisibleHeight;
	SGUI_RECT				stLayout;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (pstObj->stItems.iCount >0))
	{
		/* Calculate a virtual height when display all items. */
		iFullHeight = pstObj->stItems.iCount*ITEM_HEIGHT(pstObj->pstFontRes);
		iFullHeight = iFullHeight+SGUI_MENU_ICON_MOVEUP.iHeight+SGUI_MENU_ICON_MOVEDOWN.iHeight+2;

		stLayout.iX = RECT_X_END(*cpstParentItemLayout)+1;
		iVisibleHeight = pstDeviceIF->stSize.iHeight-cpstParentItemLayout->iY-1;
		if((iVisibleHeight < iFullHeight) && (cpstParentItemLayout->iY > (pstDeviceIF->stSize.iHeight/2)))
		{
			iVisibleHeight = cpstParentItemLayout->iY+cpstParentItemLayout->iHeight+1;
			stLayout.iY = iVisibleHeight-iFullHeight-1;
			if(stLayout.iY<0)
			{
				stLayout.iY = 0;
			}
		}
		else
		{
			stLayout.iY = cpstParentItemLayout->iY;
		}
		stLayout.iWidth = cpstParentItemLayout->iWidth+2;
		if(iFullHeight > iVisibleHeight)
		{
			stLayout.iHeight = iVisibleHeight;
		}
		else
		{
			stLayout.iHeight = iFullHeight;
		}
		SGUI_Menu_Resize(pstObj, &stLayout);
	}
}
